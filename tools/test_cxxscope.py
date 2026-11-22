#!/usr/bin/env python3
"""tools/cxxscope.py: a converted class's definitions are written inside its namespaces, as the kit and igen write
them, by tools/memberize.py and tools/gen_odl_source.py alike."""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cxxscope  # noqa: E402
import gen_odl_source  # noqa: E402
import units  # noqa: E402

TEXT = ("int free_before(void) { return 0; }\n\n"
        "/* the root's constructor */\n"
        "Gap::Core::igObject::igObject() {\n    _refCount = 1;\n}\n\n"
        "/* slot 0 */\n"
        "void Gap::Core::igObject::destruct()\n{\n}\n\n"
        "Gap::Core::igObject *Gap::Core::igObject::cloneViaMetadata(int mode) {\n    return this;\n}\n\n"
        "igMetaObject *Gap::Core::igObject::_Meta;\n\n"
        "int free_between(void) { return Gap::Core::igObject::_Meta != 0; }\n\n"
        "void Gap::Gui::igRenderer::draw() {\n}\n")


class Respell(unittest.TestCase):
    def test_qualified_heads_go_into_their_namespaces(self):
        out = cxxscope.respell(TEXT)
        self.assertEqual(out, (
            "int free_before(void) { return 0; }\n\n"
            "namespace Gap {\nnamespace Core {\n\n"
            "/* the root's constructor */\n"
            "igObject::igObject() {\n    _refCount = 1;\n}\n\n"
            "/* slot 0 */\n"
            "void igObject::destruct()\n{\n}\n\n"
            "igObject *igObject::cloneViaMetadata(int mode) {\n    return this;\n}\n\n"
            "igMetaObject *igObject::_Meta;\n"
            "}\n}\n\n"
            "int free_between(void) { return Gap::Core::igObject::_Meta != 0; }\n\n"
            "namespace Gap {\nnamespace Gui {\n\n"
            "void igRenderer::draw() {\n}\n"
            "}\n}\n"))
        # the definitions are where the tools find them
        self.assertEqual([n for n, _s, _e in units.definitions(out)],
                         ["free_before", "igObject::igObject", "destruct", "cloneViaMetadata", "free_between", "draw"])

    def test_respelling_twice_changes_nothing(self):
        once = cxxscope.respell(TEXT)
        self.assertEqual(cxxscope.respell(once), once)

    def test_a_new_member_next_to_a_block_joins_it(self):
        text = cxxscope.respell("void Gap::Gui::igRenderer::draw() {\n}\n") + \
            "\nvoid Gap::Gui::igRenderer::traverse() {\n}\n"
        self.assertEqual(cxxscope.respell(text), "namespace Gap {\nnamespace Gui {\n\nvoid igRenderer::draw() {\n}\n\n"
                                                 "void igRenderer::traverse() {\n}\n}\n}\n")

    def test_blocks_the_file_had_keep_their_bounds(self):
        # igObject_tail2.inc's two adjacent Core blocks (around `operator new`), and reflected.h's one block per
        # class, were merged on every run although nothing in them was respelled
        text = ("namespace Gap {\nnamespace Core {\n\nvoid igObject::a() {\n}\n}\n}\n\n"
                "namespace Gap {\nnamespace Core {\n\nvoid igObject::b() {\n}\n}\n}\n")
        self.assertEqual(cxxscope.respell(text), text)
        respelled = cxxscope.respell(text + "\nvoid Gap::Gui::igRenderer::draw() {\n}\n")
        self.assertTrue(respelled.startswith(text))

    def test_a_merge_keeps_the_blank_lines_between_the_definitions(self):
        text = ("namespace Gap {\nnamespace Gui {\n\nvoid igRenderer::draw() {\n}\n}\n}\n\n\n\n"
                "void Gap::Gui::igRenderer::traverse() {\n}\n")
        self.assertEqual(cxxscope.respell(text), "namespace Gap {\nnamespace Gui {\n\nvoid igRenderer::draw() {\n}\n"
                                                 "\n\n\nvoid igRenderer::traverse() {\n}\n}\n}\n")

    def test_generated_fragments_have_the_same_spelling(self):
        lines = ["igMetaObject *igRenderer::_Meta;", "", "void igRenderer::arkRegister()", "{", "}", ""]
        fragment = gen_odl_source.render_fragment([("igRenderer", lines)], {"igRenderer": "Gui"}, "Gui")
        body = fragment.split(" */\n", 1)[1]
        self.assertEqual(body, "namespace Gap {\nnamespace Gui {\n\nigMetaObject *igRenderer::_Meta;\n\n"
                               "void igRenderer::arkRegister()\n{\n}\n}\n}\n")
        self.assertEqual(cxxscope.respell(body), body)


if __name__ == "__main__":
    unittest.main()
