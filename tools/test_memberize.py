#!/usr/bin/env python3
"""tools/memberize.py rewrites free `<Class>_<Method>` functions and data as members, on a small tree."""
import json
import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import memberize  # noqa: E402

TREE = {
    "include/dw4/core/macros.h": (
        "#define OBJ_COMMON(C) \\\n"
        "    protected: static struct Meta *_Meta; \\\n"
        "    public: static void arkRegister(); \\\n"
        "    static inline struct Meta *getClassMeta() { return _Meta; }\n"),
    "include/dw4/support/reflected.h": (
        "#ifdef __cplusplus\n#include \"dw4/core/macros.h\"\n#endif\n"
        "typedef struct igObject {\n    int _vtable;\n    unsigned int _refCount;\n} igObject;\n"
        "#ifdef __cplusplus\ntypedef struct Widget : public igObject {\n#else\n"
        "typedef struct Widget {\n    int _vtable;\n    unsigned int _refCount;\n#endif\n"
        "    int _count;\n    struct Ctx * _ctx;\n} Widget;\n"
        "#ifdef __cplusplus\ntypedef struct Gadget : public Widget {\n#else\n"
        "typedef struct Gadget {\n    int _vtable;\n#endif\n    int _extra;\n} Gadget;\n"),
    "include/dw4/game/WidgetView.h": (
        "struct Ctx;\nclass WidgetView {\npublic:\n    virtual void notify();\n    int _vt;\n    int _rc;\n"
        "    int _count;\n    Ctx *_ctx;\n};\n"),
    "include/dw4/game/Widget.h": (
        "struct Widget;\nstruct Ctx;\n#ifdef __cplusplus\n#include \"dw4/game/WidgetView.h\"\n#endif\n"
        "#ifdef __cplusplus\nextern \"C\" {\n#endif\n"
        "extern struct Meta *g_Widget_meta;\n"
        "int Widget_GetCount(struct Widget *self);\n"
        "void Widget_EnsureRegistered(void);\n"
        "#ifdef __cplusplus\nvoid Widget_Attach(WidgetView *view, struct Ctx *ctx);\n#endif\n"
        "#ifdef __cplusplus\n}\n#endif\n"),
    "src/game/Game.h": (
        "#include \"dw4/support/reflected.h\"\n#include \"dw4/game/Widget.h\"\n"
        "extern \"C\" struct Meta *Widget_GetMeta(void);\n"
        "extern \"C\" struct Meta *FUN_00100040(void);\n"
        "struct Holder { igObject *item; };\n"),
    "src/game/Game.cpp": "#include \"src/game/Game.h\"\n#include \"src/game/Widget.inc\"\n"
                         "#include \"src/game/Users.inc\"\n",
    "src/game/Widget.inc": (
        "struct Meta *g_Widget_meta;\n\n"
        "/* Widget_GetMeta registers on first use */\n"
        "struct Meta *Widget_GetMeta(void) {\n"
        "    if (g_Widget_meta == 0)\n        Widget_EnsureRegistered();\n    return g_Widget_meta;\n}\n\n"
        "void Widget_EnsureRegistered(void) {\n}\n\n"
        "struct Meta *FUN_00100040(void) {\n    return g_Widget_meta;\n}\n\n"
        "int Widget_GetCount(Widget *self) {\n    int _count = 1;\n    return self->_count + _count;\n}\n\n"
        "void Widget_Attach(WidgetView *view, struct Ctx *ctx) {\n"
        "    view->_ctx = ctx;\n    view->notify();\n    Widget_GetCount((Widget *)view);\n}\n"),
    "src/game/Users.inc": (
        "typedef struct Meta *(*MetaFunction)(void);\n"
        "static MetaFunction g_parents[] = { FUN_00100040, 0 };\n"
        "int Users_Total(Widget *w, Gadget *g, Holder *holder, igObject *o) {\n"
        "    Widget local;\n"
        "    return Widget_GetCount(w) + Widget_GetCount(g) + Widget_GetCount(holder->item)\n"
        "        + Widget_GetCount((Widget *)o) + Widget_GetCount(&local);\n}\n"),
    "src/game/user.c": (
        "#include \"dw4/support/reflected.h\"\n#include \"dw4/game/Widget.h\"\n"
        "int User_Count(struct Widget *w) {\n    return Widget_GetCount(w);\n}\n"),
    "config/class-members.tsv": "# class\tdeclaration\nWidget\tOBJ_COMMON(Widget)\nWidget\tint getCount();\n",
    "config/SLUS-20836/symbols.txt": (
        "00100000 000020 Widget_GetMeta\n00100020 000008 Widget_EnsureRegistered\n00100040 000008 FUN_00100040\n"
        "00100060 000020 Widget_GetCount\n00100080 000030 Widget_Attach\n001000c0 000040 Users_Total\n"
        "00200000 000010 User_Count\n"),
    "config/SLUS-20836/data-names.tsv": "0x00300000\tg_Widget_meta\tclass-meta\n",
}
ROWS = {
    "0x00100000": {"whole_file": True,
                   "emitted": {"Widget_EnsureRegistered": "0x00100020", "FUN_00100040": "0x00100040",
                               "Widget_GetCount": "0x00100060", "Widget_Attach": "0x00100080",
                               "Users_Total": "0x001000c0"},
                   "data": {"g_Widget_meta": "0x00300000"}},
    "0x00400000": {"whole_file": True, "emitted": {},
                   "externals": {"Widget_GetCount": "0x00100060"}, "data": {"g_Widget_meta": "0x00300000"}},
}
TABLE = ("Widget_GetMeta\tstatic struct Meta *Widget::getClassTypeSafe()\n"
         "Widget_EnsureRegistered\tWidget::arkRegister\n"
         "FUN_00100040\tWidget::getClassMeta\n"
         "Widget_GetCount\tWidget::getCount\n"
         "Widget_Attach\tvoid Widget::attach(struct Ctx *ctx)\n"
         "g_Widget_meta\tWidget::_Meta\n")


def write(path, text):
    with open(path, "w") as fh:
        fh.write(text)


class Memberize(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.root = self.tmp.name
        for rel, text in TREE.items():
            path = os.path.join(self.root, rel)
            os.makedirs(os.path.dirname(path), exist_ok=True)
            write(path, text)
        write(os.path.join(self.root, "config", "SLUS-20836", "unit-objects.json"), json.dumps(ROWS, indent=2))
        self.table = os.path.join(self.root, "table.tsv")
        write(self.table, TABLE)

    def tearDown(self):
        self.tmp.cleanup()

    def read(self, rel):
        with open(os.path.join(self.root, rel)) as fh:
            return fh.read()

    def run_tool(self, *extra):
        return memberize.main([self.table, "--root", self.root, *extra])

    def test_dry_run_writes_nothing(self):
        before = {rel: self.read(rel) for rel in TREE}
        self.assertEqual(self.run_tool(), 0)
        self.assertEqual(before, {rel: self.read(rel) for rel in TREE})

    def test_definitions(self):
        self.assertEqual(self.run_tool("--apply"), 0)
        widget = self.read("src/game/Widget.inc")
        self.assertIn("struct Meta *Widget::_Meta;", widget)
        self.assertIn("struct Meta *Widget::getClassTypeSafe() {\n    if (_Meta == 0)\n        arkRegister();\n"
                      "    return _Meta;\n}", widget)
        self.assertIn("void Widget::arkRegister() {", widget)
        self.assertNotIn("FUN_00100040", widget)          # an inline member: the class defines it
        # the receiver's field is read bare unless a local hides it; never through a copy of `this`
        self.assertIn("int Widget::getCount() {\n    int _count = 1;\n    return this->_count + _count;\n}", widget)
        # a receiver declared as a view: its field of the same type is the class's, its virtual goes through it
        self.assertIn("void Widget::attach(struct Ctx *ctx) {\n    _ctx = ctx;\n"
                      "    ((WidgetView *)this)->notify();\n    getCount();\n}", widget)
        self.assertIn("/* Widget::getClassTypeSafe registers on first use */", widget)

    def test_callers(self):
        self.assertEqual(self.run_tool("--apply"), 0)
        users = self.read("src/game/Users.inc")
        self.assertIn("{ Widget::getClassMeta, 0 }", users)
        self.assertIn("return w->getCount() + g->getCount() + ((Widget *)holder->item)->getCount()\n"
                      "        + ((Widget *)o)->getCount() + local.getCount();", users)
        # C keeps calling the C name, through the prototype the home header keeps for it
        self.assertIn("return Widget_GetCount(w);", self.read("src/game/user.c"))
        header = self.read("include/dw4/game/Widget.h")
        self.assertIn("int Widget_GetCount(struct Widget *self);", header)
        self.assertNotIn("Widget_EnsureRegistered", header)
        self.assertNotIn("g_Widget_meta", header)
        self.assertNotIn("Widget_Attach", header)
        self.assertNotIn("#ifdef __cplusplus\n#endif", header)
        game = self.read("src/game/Game.h")
        self.assertNotIn("Widget_GetMeta", game)
        self.assertNotIn("FUN_00100040", game)

    def test_rows_and_declarations(self):
        self.assertEqual(self.run_tool("--apply"), 0)
        rows = json.loads(self.read(os.path.join("config", "SLUS-20836", "unit-objects.json")))
        self.assertEqual(rows["0x00100000"]["emitted"], {
            "arkRegister__6WidgetFv": "0x00100020", "getClassMeta__6WidgetFv": "0x00100040",
            "getCount__6WidgetFv": "0x00100060", "attach__6WidgetFP3Ctx": "0x00100080",
            "Users_Total": "0x001000c0"})
        self.assertEqual(rows["0x00100000"]["symbol"], "getClassTypeSafe__6WidgetFv")
        self.assertEqual(rows["0x00100000"]["data"], {"_Meta__6Widget": "0x00300000"})
        # another unit's bindings of the C names go: the compiler-name map resolves the members
        self.assertEqual(rows["0x00400000"]["externals"], {})
        self.assertEqual(rows["0x00400000"]["data"], {})
        members = self.read("config/class-members.tsv")
        self.assertIn("Widget\tstatic struct Meta *getClassTypeSafe();\n", members)
        self.assertIn("Widget\tvoid attach(struct Ctx *ctx);\n", members)
        self.assertEqual(members.count("getCount"), 1)

    def test_a_receiver_assigned_is_refused(self):
        path = os.path.join(self.root, "src", "game", "Widget.inc")
        write(path, self.read("src/game/Widget.inc")
              + "int Widget_Next(Widget *self) {\n    self = 0;\n    return 0;\n}\n")
        write(self.table, TABLE + "Widget_Next\tint Widget::next()\n")
        before = self.read("src/game/Widget.inc")
        self.assertEqual(self.run_tool("--apply"), 2)
        self.assertEqual(before, self.read("src/game/Widget.inc"))

    def test_an_undeclared_short_member_is_refused(self):
        write(self.table, TABLE + "User_Count\tWidget::count\n")
        self.assertEqual(self.run_tool(), 2)


if __name__ == "__main__":
    unittest.main()
