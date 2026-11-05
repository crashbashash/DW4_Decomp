#!/usr/bin/env python3
"""tools/buildcache.py: keys change with every input, hits are exact, and the store stays bounded."""
import json
import os
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import buildcache


class Keys(unittest.TestCase):
    def test_sha_length_prefix_prevents_boundary_forgery(self):
        self.assertNotEqual(buildcache.sha("ab", "c"), buildcache.sha("a", "bc"))
        self.assertEqual(buildcache.sha("a", 1), buildcache.sha("a", 1))

    def test_file_and_tree_digests_follow_content(self):
        with tempfile.TemporaryDirectory() as d:
            p = Path(d) / "a.h"
            p.write_text("one")
            first = buildcache.fresh_sha(str(p))
            tree1 = buildcache.tree_sha(d)
            buildcache._memo.clear()
            p.write_text("two")
            self.assertNotEqual(first, buildcache.fresh_sha(str(p)))
            self.assertNotEqual(tree1, buildcache.tree_sha(d))
            self.assertEqual("missing", buildcache.fresh_sha(str(Path(d) / "absent")))

    def test_tree_digest_skips_the_requested_extensions_only(self):
        with tempfile.TemporaryDirectory() as d:
            (Path(d) / "x.c").write_text("1")
            (Path(d) / "y.h").write_text("2")
            buildcache._memo.clear()
            a = buildcache.tree_sha(d, skip_ext=(".c",))
            (Path(d) / "x.c").write_text("changed")
            buildcache._memo.clear()
            self.assertEqual(a, buildcache.tree_sha(d, skip_ext=(".c",)))
            (Path(d) / "y.h").write_text("changed")
            buildcache._memo.clear()
            self.assertNotEqual(a, buildcache.tree_sha(d, skip_ext=(".c",)))

    def test_tool_closure_includes_what_check_imports(self):
        names = {os.path.basename(p) for p in buildcache.module_closure("check.py")}
        self.assertTrue({"check.py", "verify.py", "units.py", "unitobjects.py", "buildcache.py"} <= names)

    def test_disabled_by_flag_and_environment(self):
        old = os.environ.pop("DW4_NOCACHE", None)
        try:
            self.assertTrue(buildcache.enabled(False))
            self.assertFalse(buildcache.enabled(True))
            os.environ["DW4_NOCACHE"] = "1"
            self.assertFalse(buildcache.enabled(False))
        finally:
            os.environ.pop("DW4_NOCACHE", None)
            if old is not None:
                os.environ["DW4_NOCACHE"] = old


class UnitProfile(unittest.TestCase):
    def test_profile_is_per_unit_and_follows_its_rows(self):
        default = "local/mwcps2/3.0-011126/mwccps2.exe"
        a = buildcache.unit_profile_sha(0x0040ee60, "-O3 -Iinclude", default)   # a unit with its own compiler row, flags and group
        b = buildcache.unit_profile_sha(0x00100240, "-O3 -Iinclude", default)   # a plain unit
        self.assertNotEqual(a, b)
        self.assertEqual(a, buildcache.unit_profile_sha(0x0040ee60, "-O3 -Iinclude", default))
        # a member of the same unit-objects group shares the owner's settings
        self.assertEqual(buildcache.unit_profile_sha(0x0040f6a0, "-O3 -Iinclude", default),
                         buildcache.unit_profile_sha(0x0040ee60, "-O3 -Iinclude", default))


class StoreBehaviour(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.TemporaryDirectory()
        self.saved = buildcache.CACHE_DIR
        buildcache.CACHE_DIR = self.dir.name

    def tearDown(self):
        buildcache.CACHE_DIR = self.saved
        self.dir.cleanup()

    def test_round_trip_counts_and_pruning(self):
        s = buildcache.Store("t", True)
        self.assertIsNone(s.get("k1"))
        s.put("k1", "matched")
        s.put("k2", "matched")
        s.save()
        s2 = buildcache.Store("t", True)
        self.assertEqual("matched", s2.get("k1"))
        s2.save()    # a partial run merges: k2 was not used but is kept (the build-option tests must not wipe the tree's answers)
        s3 = buildcache.Store("t", True)
        self.assertEqual("matched", s3.get("k1"))
        self.assertEqual("matched", s3.get("k2"))
        s3.save(prune=True)    # a complete whole-tree run prunes: the store cannot grow without bound
        s4 = buildcache.Store("t", True)
        self.assertEqual("matched", s4.get("k1"))
        self.assertEqual("matched", s4.get("k2"))
        s5 = buildcache.Store("t", True)
        self.assertEqual("matched", s5.get("k1"))
        s5.save(prune=True)    # only k1 used this run
        s6 = buildcache.Store("t", True)
        self.assertEqual("matched", s6.get("k1"))
        self.assertIsNone(s6.get("k2"))
        self.assertEqual((1, 1), (s6.hits, s6.misses))

    def test_disabled_store_never_reads_or_writes(self):
        s = buildcache.Store("t", True)
        s.put("k", "v")
        s.save()
        off = buildcache.Store("t", False)
        self.assertIsNone(off.get("k"))
        off.put("k2", "v")
        off.save()
        self.assertEqual(["t.json"], os.listdir(self.dir.name))
        self.assertNotIn("k2", json.load(open(os.path.join(self.dir.name, "t.json")))["entries"])
        self.assertIn("off", off.summary("things"))

    def test_corrupt_or_old_store_is_ignored(self):
        Path(self.dir.name, "t.json").write_text("{not json")
        self.assertIsNone(buildcache.Store("t", True).get("k"))
        Path(self.dir.name, "t.json").write_text(json.dumps({"version": 0, "entries": {"k": "v"}}))
        self.assertIsNone(buildcache.Store("t", True).get("k"))


if __name__ == "__main__":
    unittest.main()
