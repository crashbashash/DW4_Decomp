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
                     "baseline": {k: {"value": 10, "reason": None} for k, _ in progress.DEBT_COUNTERS}},
            "categories": {"recorded": True, "warning": None}}


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

    def test_a_stale_category_table_asks_for_a_check_run(self):
        # NearMiss4's tree: data/check-categories.tsv had 20463 rows for 20464 decompiled units (a function added
        # since the last check), and --debt-check listed every counter the table gives as rising or unavailable
        table = os.path.join(os.path.dirname(progress.DEBT_BASELINE), "check-categories.tsv")
        with open(table, "w") as fh:
            fh.write("# va\tname\tcategory\tdiagnostic\n00100000\tone\tmatch\t-\n")
        with mock.patch.object(progress, "CATEGORIES_TSV", table):
            categories = progress.categorise([(0x100000, 8, "one"), (0x100008, 8, "two")])
        d = state(**dict({k: None for k in progress.CATEGORY_COUNTERS}, **{"unmatched.functions": 11}))
        d["categories"] = categories
        out = io.StringIO()
        with contextlib.redirect_stdout(out):
            self.assertEqual(progress.debt_check(d), 1)
        text = out.getvalue()
        self.assertIn("data/check-categories.tsv", text)
        self.assertIn("check.py", text)
        for k in progress.CATEGORY_COUNTERS:
            self.assertNotIn(k, text)
        self.assertIn("unmatched.functions", text)      # a counter the table does not give is still checked


class Publishing(unittest.TestCase):
    """progress.py with no flag prints and writes nothing (ImageConvert's bare run rewrote PROGRESS.md and
    docs/progress.json, which it then reverted); --write (`make progress`) writes them."""

    def test_only_write_writes(self):
        folder = tempfile.TemporaryDirectory()
        self.addCleanup(folder.cleanup)
        paths = {name: os.path.join(folder.name, name) for name in ("PROGRESS.md", "progress.json", "README.md")}
        with open(paths["README.md"], "w") as fh:
            fh.write("<!-- progress:start -->old<!-- progress:end -->\n")
        bytes_ = dict(fully_matched=1, total=4, matched=2, assembly=0, functions_assembly=0, functions_asm_body=0,
                      asm_body=0)
        d = {"functions": dict(fully_matched=1, total=2, matched=1), "code_bytes": bytes_,
             "link": {"from_c_pct": 50.0}, "categories": {"recorded": True}}
        with mock.patch.multiple(progress, collect=lambda: d, render_md=lambda d: "page\n",
                                 readme_block=lambda d: "<!-- progress:start -->new<!-- progress:end -->",
                                 PROGRESS_MD=paths["PROGRESS.md"], PROGRESS_JSON=paths["progress.json"],
                                 README=paths["README.md"]):
            self.assertEqual(quiet(progress.main, []), 0)
            self.assertFalse(os.path.exists(paths["PROGRESS.md"]) or os.path.exists(paths["progress.json"]))
            self.assertIn("old", open(paths["README.md"]).read())
            self.assertEqual(quiet(progress.main, ["--write"]), 0)
            self.assertEqual(open(paths["PROGRESS.md"]).read(), "page\n")
            self.assertTrue(os.path.exists(paths["progress.json"]))
            self.assertIn("new", open(paths["README.md"]).read())


class FreeMethods(unittest.TestCase):
    def test_class_named_functions_of_cpp_units_count(self):
        syms = [(0x100, 16, "igCamera_Update"), (0x110, 8, "igCamera_GetMeta"), (0x120, 4, "p2SetViewport"),
                (0x130, 4, "Gap__Sg__igCamera__vfunc_21"), (0x140, 4, "igCamera_Helper"), (0x150, 4, "FUN_00100150"),
                (0x160, 4, "__dt__8igCameraFv")]
        paths = {"igCamera_Update": "src/engine/sg/Sg.cpp", "igCamera_GetMeta": "src/engine/sg/Sg.cpp",
                 "p2SetViewport": "src/engine/p2gs.c", "Gap__Sg__igCamera__vfunc_21": "src/engine/sg/Sg.cpp",
                 "igCamera_Helper": "src/engine/p2gs.c", "FUN_00100150": "src/engine/sg/Sg.cpp",
                 "__dt__8igCameraFv": "src/engine/sg/Sg.cpp"}
        # free functions only in C++ units, named for a known class; slot-named virtuals apart
        self.assertEqual(progress.method_shaped(syms, paths, {"igCamera"}), (2, 24, 1))

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

    def test_a_typed_field_is_not_an_untyped_reference(self):
        text = ("typedef struct igRenderer {\n"
                "    int _visualContext;                            /* +8    igObjectRefMetaField */\n"
                "} igRenderer;\n"
                "typedef struct igOther {\n"
                "    int _visualContext;                            /* +8    igObjectRefMetaField */\n"
                "} igOther;\n")
        self.assertEqual(progress.untyped_refs(text, set()), 2)
        self.assertEqual(progress.untyped_refs(text, {("igRenderer", "_visualContext")}), 1)

    def test_typed_fields_reads_the_table(self):
        path = os.path.join(tempfile.mkdtemp(), "typed-fields.tsv")
        open(path, "w").write("# header\tx\ty\nigRenderer\t_visualContext\tigSmartPointer<igVisualContext>\n")
        self.assertEqual(progress.typed_fields(path), {("igRenderer", "_visualContext")})


if __name__ == "__main__":
    unittest.main()
