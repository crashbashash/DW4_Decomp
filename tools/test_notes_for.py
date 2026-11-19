#!/usr/bin/env python3
"""tools/notes_for.py finds a function by its compiler name or its C++ member name, as by its symbol."""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import notes_for  # noqa: E402


class Members(unittest.TestCase):
    def test_a_compiler_name_resolves_to_its_symbol(self):
        self.assertEqual(notes_for.resolve("runString__Q33Gap3Lua10igLuaStateFPCc"),
                         (0x246620, 0x54, "igLuaState_RunString"))

    def test_a_member_name_resolves_with_or_without_its_namespaces(self):
        for query in ("igLuaState::runString", "Gap::Lua::igLuaState::runString"):
            self.assertEqual(notes_for.resolve(query), (0x246620, 0x54, "igLuaState_RunString"), query)
        self.assertEqual(notes_for.member_names("igLuaState::runString"),
                         {"runString__Q33Gap3Lua10igLuaStateFPCc": 0x246620})

    def test_a_plain_name_is_no_member(self):
        self.assertEqual(notes_for.member_names("igLuaState_RunString"), {})

    def test_definition_heads(self):
        self.assertEqual(notes_for.member_of_head("int Gap::Lua::igLuaState::runString(const char *source) "),
                         "igLuaState::runString")
        self.assertEqual(notes_for.member_of_head("Widget::~Widget()"), "Widget::~Widget")
        self.assertIsNone(notes_for.member_of_head("int igLuaState_RunString(igLuaState *self)"))


if __name__ == "__main__":
    unittest.main()
