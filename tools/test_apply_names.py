#!/usr/bin/env python3
"""apply_names.py renames a function's derived `thunk_<name>` everywhere its sources say it."""
import json
import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import apply_names  # noqa: E402


class DerivedThunk(unittest.TestCase):
    def test_thunk_key_in_unit_objects_follows_its_target(self):
        with tempfile.TemporaryDirectory() as tree:
            config = os.path.join(tree, "config", "SLUS-20836")
            os.makedirs(os.path.join(config, "names"))
            os.makedirs(os.path.join(tree, "src", "engine"))
            with open(os.path.join(config, "symbols.txt"), "w") as f:
                f.write("00143140 000008 thunk_FUN_00143150\n00143150 000048 FUN_00143150\n")
            with open(os.path.join(config, "names", "Test.tsv"), "w") as f:
                f.write("0x00143150\tigWidget_GetMetaObject\tengine\n")
            with open(os.path.join(tree, "src", "engine", "Widget.c"), "w") as f:
                f.write("void FUN_00143150(void) {}\nvoid thunk_FUN_00143150(void) { FUN_00143150(); }\n")
            unit_objects = os.path.join(config, "unit-objects.json")
            with open(unit_objects, "w") as f:
                json.dump({"0x00143140": {"emitted": {"thunk_FUN_00143150": "0x00143140",
                                                      "FUN_00143150": "0x00143150"}}}, f)
            code = apply_names.main([
                "--names", os.path.join(config, "names"), "--symbols", os.path.join(config, "symbols.txt"),
                "--src", os.path.join(tree, "src"), "--asm", os.path.join(tree, "asm"), "--apply", "--no-regen"])
            self.assertEqual(code, 0)
            emitted = json.load(open(unit_objects))["0x00143140"]["emitted"]
            self.assertEqual(emitted, {"thunk_igWidget_GetMetaObject": "0x00143140",
                                       "igWidget_GetMetaObject": "0x00143150"})
            source = open(os.path.join(tree, "src", "engine", "Widget.c")).read()
            self.assertIn("void thunk_igWidget_GetMetaObject(void) { igWidget_GetMetaObject(); }", source)


if __name__ == "__main__":
    unittest.main()
