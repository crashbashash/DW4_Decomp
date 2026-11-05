#!/usr/bin/env python3
"""Check descriptor typing across reassignment of an initializer temporary."""
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class DescriptorLifetimes(unittest.TestCase):
    def check_source(self, body):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "Fixture.c").write_text("void Fixture_InitFields(void) {\n" + body + "\n}\n")
            reflection = root / "reflection.json"
            reflection.write_text(json.dumps({"classes": {"fixture": {
                "class": "Fixture", "fields": [
                    {"name": "buffer", "type": "igMemoryRefMetaField"},
                    {"name": "object", "type": "igObjectRefMetaField"},
                ],
            }}}))
            return subprocess.run([
                sys.executable, str(ROOT / "scripts/retype_initfields.py"),
                "--check", "--src", str(root), "--reflection", str(reflection),
            ], cwd=ROOT, capture_output=True, text=True)

    def test_reused_temporary_has_a_new_descriptor_type(self):
        result = self.check_source("""
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igMemoryRefMetaField *)field)->_memType = 0;
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)field)->_metaObject = 0;
""")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn("checked 2 emitted member accesses", result.stdout)

    def test_wrong_type_before_reassignment_is_rejected(self):
        result = self.check_source("""
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field)->_metaObject = 0;
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)field)->_metaObject = 0;
""")
        self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
        self.assertIn("k=0", result.stdout)

    def test_wrong_type_after_reassignment_is_rejected(self):
        result = self.check_source("""
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igMemoryRefMetaField *)field)->_memType = 0;
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igMemoryRefMetaField *)field)->_memType = 0;
""")
        self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
        self.assertIn("k=1", result.stdout)

    def test_unrelated_assignment_ends_the_known_descriptor_lifetime(self):
        result = self.check_source("""
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igMemoryRefMetaField *)field)->_memType = 0;
    field = other;
    ((igObjectRefMetaField *)field)->_metaObject = 0;
""")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn("checked 1 emitted member accesses", result.stdout)


if __name__ == "__main__":
    unittest.main()
