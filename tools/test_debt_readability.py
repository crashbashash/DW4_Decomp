#!/usr/bin/env python3
"""The debt ratchet tracks readability without refusing a byte-matching change."""
import contextlib
import io
import os
import sys
import tempfile
import unittest
from unittest import mock

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import progress  # noqa: E402


def state(**rises):
    counters = {k: 10 for k, _ in progress.DEBT_COUNTERS}
    counters.update(rises)
    return {"debt": {"counters": counters,
                     "baseline": {k: {"value": 10, "reason": None} for k, _ in progress.DEBT_COUNTERS}}}


def quiet(fn, *args):
    with contextlib.redirect_stdout(io.StringIO()):
        return fn(*args)


class ReadableAssembly(unittest.TestCase):
    def measure(self, name, category):
        progress._READABLE.clear()
        self.addCleanup(progress._READABLE.clear)
        return progress.readable([(0x100000, 16, name)], {name: "src/newlib/memchr.S"},
                                 {0x100000: (category,)})

    def test_a_named_approved_source_is_readable(self):
        result = self.measure("memchr", "assembly")
        self.assertEqual((result["names"], result["bytes"], result["matched_functions"]), ({"memchr"}, 16, 1))

    def test_an_unnamed_approved_source_is_not(self):
        result = self.measure("FUN_00100000", "assembly")
        self.assertEqual((result["names"], result["failing"]["name"]["functions"]), (set(), 1))

    def test_an_asm_body_is_not_counted(self):
        result = self.measure("memchr", "asm-body")
        self.assertEqual((result["names"], result["matched_functions"]), (set(), 0))


class Ratchet(unittest.TestCase):
    def setUp(self):
        folder = tempfile.TemporaryDirectory()
        self.addCleanup(folder.cleanup)
        patch = mock.patch.object(progress, "DEBT_BASELINE", os.path.join(folder.name, "baseline.json"))
        patch.start()
        self.addCleanup(patch.stop)

    def test_readability_counters_may_rise(self):
        d = state(**{k: 99 for k in progress.READABILITY_COUNTERS})
        self.assertEqual(quiet(progress.debt_check, d), 0)

    def test_a_correctness_counter_still_refuses(self):
        d = state(**{"mismatch.functions": 11})
        self.assertEqual(quiet(progress.debt_check, d), 1)

    def test_recording_a_readability_rise_needs_no_reason(self):
        d = state(**{k: 99 for k in progress.READABILITY_COUNTERS})
        self.assertNotEqual(quiet(progress.debt_record, d, None), 1)

    def test_recording_a_correctness_rise_needs_a_reason(self):
        d = state(**{"mismatch.functions": 11})
        self.assertEqual(quiet(progress.debt_record, d, None), 1)

    def test_a_new_reason_keeps_the_earlier_one_and_skips_readability(self):
        import json
        d = state(**{"mismatch.functions": 11, "fun_dat_refs": 12})
        d["debt"]["baseline"]["mismatch.functions"]["reason"] = "first"
        quiet(progress.debt_record, d, "second")
        saved = json.load(open(progress.DEBT_BASELINE))["counters"]
        self.assertEqual(saved["mismatch.functions"], {"value": 11, "reason": "first second"})
        self.assertEqual(saved["fun_dat_refs"], 12)


class FreeMethods(unittest.TestCase):
    def test_class_named_functions_of_cpp_units_count(self):
        syms = [(0x100, 16, "igNode_Update"), (0x110, 8, "igNode_GetMeta"), (0x120, 4, "p2SetViewport"),
                (0x130, 4, "Gap__Sg__igNode__vfunc_21"), (0x140, 4, "igNode_Helper"), (0x150, 4, "FUN_00100150"),
                (0x160, 4, "__dt__6igNodeFv")]
        paths = {"igNode_Update": "src/engine/sg/Sg.cpp", "igNode_GetMeta": "src/engine/sg/Sg.cpp",
                 "p2SetViewport": "src/engine/p2gs.c", "Gap__Sg__igNode__vfunc_21": "src/engine/sg/Sg.cpp",
                 "igNode_Helper": "src/engine/p2gs.c", "FUN_00100150": "src/engine/sg/Sg.cpp",
                 "__dt__6igNodeFv": "src/engine/sg/Sg.cpp"}
        # free functions only in C++ units, named for a known class; slot-named virtuals apart
        self.assertEqual(progress.method_shaped(syms, paths, {"igNode"}), (2, 24, 1))

    def test_source_accuracy_counts_the_stand_ins(self):
        root = tempfile.mkdtemp()
        os.makedirs(os.path.join(root, "src", "engine"))
        os.makedirs(os.path.join(root, "src", "third_party"))
        os.makedirs(os.path.join(root, "include", "dw4", "support"))
        open(os.path.join(root, "src", "engine", "igNode_tail2.inc"), "w").write(
            "/* matching construct: sweep — order */\n"
            "struct igNodeDispatchView { virtual void d0(); virtual void d1(); virtual int vX(int); };\n"
            "struct ListView { int f12; char pad[4]; };\n"
            "extern \"C\" const char text_hello[];\n"
            "int igNode_GetMetaObject(void) { return 0; }\n"
            "int igNode_Update(void) { return 0; }\n")
        open(os.path.join(root, "src", "third_party", "x.c"), "w").write("struct AView { int f4; };\n")
        open(os.path.join(root, "include", "dw4", "support", "reflected.h"), "w").write(
            "    int _parent;                                   /* +8    igObjectRefMetaField */\n"
            "    int _count;                                    /* +12   igIntMetaField */\n")
        with mock.patch.object(progress, "ROOT", root), mock.patch.object(progress, "SRC", os.path.join(root, "src")):
            c = progress.source_accuracy()
        self.assertEqual(c, {"virtual_views.types": 1, "virtual_views.slots": 3, "boilerplate.functions": 1,
                             "layout.tail_fragments": 1, "matching_constructs": 1, "views.local": 1,
                             "members.offset_named": 1, "strings.externs": 1, "reflected.untyped_refs": 1})


if __name__ == "__main__":
    unittest.main()
