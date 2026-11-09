"""Tests for scripts/check_doc_function_names.py: which documents may name functions, and that names exist."""
import os
import sys
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "scripts"))
import check_doc_function_names as chk  # noqa: E402

SUBJECTS = {"docs/s.md": {"FUN_00000010"}}
SYMBOLS = {"FUN_00000020", "Gap__X__vfunc_01"}


class DocFunctionNames(unittest.TestCase):
    def test_names_are_found_but_placeholders_are_not(self):
        self.assertEqual(chk.named_functions("`FUN_00130060` and Gap__Core__igObject__vfunc_10"),
                         ["FUN_00130060", "Gap__Core__igObject__vfunc_10"])
        self.assertEqual(chk.named_functions("FUN_XXXXXXXX, Class__vfunc_NN and DAT_00555048"), [])

    def test_a_method_document_names_nothing(self):
        self.assertEqual(chk.check_text("docs/m.md", "the shape", SUBJECTS, SYMBOLS), [])
        self.assertEqual(len(chk.check_text("docs/m.md", "FUN_00000020", SUBJECTS, SYMBOLS)), 1)

    def test_a_subject_document_needs_current_names(self):
        self.assertEqual(chk.check_text("docs/s.md", "FUN_00000020 Gap__X__vfunc_01", SUBJECTS, SYMBOLS), [])
        self.assertEqual(len(chk.check_text("docs/s.md", "FUN_00000030", SUBJECTS, SYMBOLS)), 1)

    def test_a_retired_name_is_kept_only_by_its_row(self):
        self.assertEqual(chk.check_text("docs/s.md", "FUN_00000010", SUBJECTS, SYMBOLS), [])

    def test_a_new_document_is_a_method_document(self):
        with tempfile.TemporaryDirectory() as root:
            os.makedirs(os.path.join(root, "docs"))
            with open(os.path.join(root, "docs", "new.md"), "w") as fh:
                fh.write("FUN_00000020\n")
            self.assertEqual(len(chk.check_tree(root, {}, SYMBOLS)), 1)

    def test_a_missing_listed_document_is_reported(self):
        with tempfile.TemporaryDirectory() as root:
            os.makedirs(os.path.join(root, "docs"))
            self.assertEqual(len(chk.check_tree(root, {"docs/gone.md": set()}, SYMBOLS)), 1)

    def test_the_shipped_documents_are_clean(self):
        self.assertEqual(chk.check_tree(), [])


if __name__ == "__main__":
    unittest.main()
