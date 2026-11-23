#!/usr/bin/env python3
"""tools/memberize.py rewrites free `<Class>_<Method>` functions and data as members, on a small tree."""
import json
import io
import os
import re
import sys
import tempfile
import unittest
from unittest import mock

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
        # a comment's prose keeps the C name: it is still the symbol's retail name
        self.assertIn("/* Widget_GetMeta registers on first use */", widget)

    def test_comment_prose_keeps_the_c_name_and_a_code_span_names_the_member(self):
        # src/game/beNDMWLoadCtrl2.cpp's "kept local: igObjectList_SetCount has no include/dw4 home" had become
        # "kept local: Gap::Core::igObjectList::setCount has no include/dw4 home"
        self.append("src/game/Users.inc", "/* kept local: Widget_EnsureRegistered has no include/dw4 home. */\n"
                                          "// Widget_EnsureRegistered registers the class\n"
                                          "/* reached through ` Widget_EnsureRegistered ` and `Widget_GetCount` */\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        users = self.read("src/game/Users.inc")
        self.assertIn("/* kept local: Widget_EnsureRegistered has no include/dw4 home. */\n"
                      "// Widget_EnsureRegistered registers the class\n", users)
        # a code span names the member as code does, unless code still calls the C name (user.c calls GetCount)
        self.assertIn("/* reached through ` Widget::arkRegister ` and `Widget_GetCount` */", users)

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

    def test_a_receiver_reused_as_a_local(self):
        self.append("src/game/Widget.inc",
                    "int Widget_Next(Widget *self, Widget *other) {\n    int n = self->_count;\n"
                    "    if (n != 0) {\n        self = other;\n        n += self->_count;\n    }\n    return n;\n}\n"
                    "int Widget_Last(Widget *self, Widget *other) {\n    int n = self->_count;\n"
                    "    if (n != 0) {\n        self = other;\n    }\n    return self->_count + n;\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000010 Widget_Next\n00100110 000010 Widget_Last\n")
        write(self.table, TABLE + "Widget_Next\tint Widget::next(Widget *other)\n"
              "Widget_Last\tint Widget::last(Widget *other)\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        widget = self.read("src/game/Widget.inc")
        self.assertIn("int Widget::next(Widget *other) {\n    int n = _count;\n    if (n != 0) {\n"
                      "        Widget *self = other;\n        n += self->_count;\n    }\n    return n;\n}", widget)
        self.assertIn("int Widget::last(Widget *other) {\n    Widget *self;\n    int n = _count;\n    if (n != 0) {\n"
                      "        self = other;\n    }\n    return self->_count + n;\n}", widget)

    def test_a_receiver_assigned_in_a_loop_that_read_it_is_refused(self):
        self.append("src/game/Widget.inc",
                    "int Widget_Walk(Widget *self, Widget *other) {\n    int n = 0;\n"
                    "    while (n < 4) {\n        n += self->_count;\n        self = other;\n    }\n    return n;\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000010 Widget_Walk\n")
        write(self.table, TABLE + "Widget_Walk\tint Widget::walk(Widget *other)\n")
        before = self.read("src/game/Widget.inc")
        self.assertEqual(self.run_tool("--apply"), 2)
        self.assertEqual(before, self.read("src/game/Widget.inc"))

    def test_a_receiver_assigned_in_an_expression_is_refused(self):
        path = os.path.join(self.root, "src", "game", "Widget.inc")
        write(path, self.read("src/game/Widget.inc")
              + "int Widget_Next(Widget *self) {\n    return (self = 0) != 0;\n}\n")
        write(self.table, TABLE + "Widget_Next\tint Widget::next()\n")
        before = self.read("src/game/Widget.inc")
        self.assertEqual(self.run_tool("--apply"), 2)
        self.assertEqual(before, self.read("src/game/Widget.inc"))

    def test_two_overloads_of_one_member_in_one_table(self):
        self.append("src/game/Widget.inc",
                    "\nint Widget_FindByKey(Widget *self, int key) {\n    return self->_count == key;\n}\n"
                    "\nint Widget_FindByName(Widget *self, const char *name) {\n    return name != 0;\n}\n")
        self.append("src/game/Users.inc", "int Users_Find(Widget *w) {\n"
                    "    return Widget_FindByKey(w, 1) + Widget_FindByName(w, \"a\");\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000010 Widget_FindByKey\n"
                    "00100110 000010 Widget_FindByName\n")
        write(self.table, TABLE + "Widget_FindByKey\tint Widget::find(int key)\n"
              "Widget_FindByName\tint Widget::find(const char *name)\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        widget = self.read("src/game/Widget.inc")
        self.assertIn("int Widget::find(int key) {\n    return _count == key;\n}", widget)
        self.assertIn("int Widget::find(const char *name) {\n    return name != 0;\n}", widget)
        self.assertIn("return w->find(1) + w->find(\"a\");", self.read("src/game/Users.inc"))
        members = self.read("config/class-members.tsv")
        self.assertIn("Widget\tint find(int key);\n", members)
        self.assertIn("Widget\tint find(const char *name);\n", members)

    def test_a_prototype_returning_a_template_instance_is_a_declaration(self):
        # include/dw4/core/igResource.h's `igSmartPointer<struct igObject> igResource_GetDirectory(void *directory,
        # const char *name);` was read as a call and rewritten into `igSmartPointer<struct igObject>
        # ((Gap::Core::igResource *)(void *directory))->getDirectory(const char *name);`
        self.append("src/game/Game.h", "template <class T> struct Ptr { T *p; };\n")
        header = self.read("include/dw4/game/Widget.h").replace(
            "void Widget_EnsureRegistered(void);\n",
            "void Widget_EnsureRegistered(void);\n"
            "#ifdef __cplusplus\nPtr<struct Ctx> Widget_Find(void *self, const char *name);\n#endif\n")
        write(os.path.join(self.root, "include", "dw4", "game", "Widget.h"), header)
        self.append("src/game/Widget.inc", "Ptr<Ctx> Widget_Find(void *self, const char *name) {\n    Ptr<Ctx> out;\n"
                                           "    out.p = ((Widget *)self)->_ctx;\n    return out;\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000010 Widget_Find\n")
        write(self.table, TABLE + "Widget_Find\tPtr<Ctx> Widget::find(const char *name)\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        self.assertNotIn("Widget_Find", self.read("include/dw4/game/Widget.h"))
        self.assertNotIn("find", self.read("include/dw4/game/Widget.h"))
        self.assertIn("Ptr<Ctx> Widget::find(const char *name) {", self.read("src/game/Widget.inc"))

    def test_an_undeclared_short_member_is_refused(self):
        write(self.table, TABLE + "User_Count\tWidget::count\n")
        self.assertEqual(self.run_tool(), 2)

    def test_a_static_inline_overload_forwarding_to_the_c_name_goes_with_its_callers(self):
        path = os.path.join(self.root, "src", "game", "Game.h")
        write(path, self.read("src/game/Game.h") + "static inline int Widget_GetCount(WidgetView *view) "
              "{ return Widget_GetCount((Widget *)view); }\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        # every C++ call is a member call now, so the overload serves no code; C (user.c) keeps the prototype
        self.assertNotIn("Widget_GetCount", self.read("src/game/Game.h"))
        self.assertIn("int Widget::getCount() {", self.read("src/game/Widget.inc"))
        self.assertIn("int Widget_GetCount(struct Widget *self);", self.read("include/dw4/game/Widget.h"))

    def test_macro_bodies_and_class_body_members_call_the_member(self):
        self.append("src/game/Users.inc",
                    "#define COUNT_OF(w) Widget_GetCount(w)\n"
                    "#define TWICE(a, w) { \\\n    a = Widget_GetCount((Widget *)w); \\\n"
                    "    a += Widget_GetCount(holder); }\n"
                    "struct Counter { static int count(Gadget *g) { return Widget_GetCount(g); }\n"
                    "    static void touch(Gadget *g) { Widget_GetCount(g); } };\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        users = self.read("src/game/Users.inc")
        self.assertIn("#define COUNT_OF(w) ((Widget *)(w))->getCount()\n", users)
        self.assertIn("    a = ((Widget *)(w))->getCount(); \\\n    a += ((Widget *)holder)->getCount(); }\n", users)
        # a call in a member a class body defines is no declaration: it is rewritten, not removed
        self.assertIn("return ((Widget *)g)->getCount(); }\n", users)
        self.assertIn("static void touch(Gadget *g) { ((Widget *)g)->getCount(); } };\n", users)
        # macros expanded by C++ name the member; --check counts them as users
        self.assertEqual(memberize.macro_body("#define X(a, b) f(a)\n", 16), frozenset(("a", "b")))
        self.assertIsNone(memberize.macro_body("#define X(a, b) f(a)\n", 9))
        self.assertEqual(memberize.macro_body("#define Y \\\n  f()\n", 14), frozenset())

    def test_a_private_member_is_reached_by_its_c_name_outside_its_class(self):
        self.append("config/class-members.tsv", "Widget\tprivate: void release();\n")
        self.append("src/game/Widget.inc",
                    "void Widget_Release(Widget *self) {\n    self->_count = 0;\n}\n\n"
                    "void Widget::reset() {\n    Widget_Release(this);\n}\n")
        self.append("src/game/Users.inc", "void Users_Drop(Widget *w) {\n    Widget_Release(w);\n}\n")
        self.append("include/dw4/game/Widget.h", "#ifdef __cplusplus\nextern \"C\" void Widget_Release(struct Widget *self);\n#endif\n")
        self.append("config/SLUS-20836/symbols.txt", "00100200 000010 Widget_Release\n")
        write(self.table, TABLE + "Widget_Release\tWidget::release\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        widget = self.read("src/game/Widget.inc")
        self.assertIn("void Widget::release() {\n    _count = 0;\n}\n", widget)
        self.assertIn("void Widget::reset() {\n    release();\n}\n", widget)
        # outside the class the private member is out of reach: the C name and its prototype stay
        self.assertIn("    Widget_Release(w);\n", self.read("src/game/Users.inc"))
        self.assertIn("Widget_Release(struct Widget *self);", self.read("include/dw4/game/Widget.h"))

    def test_gap_qualified_parameters_and_rows_in_their_class(self):
        write(os.path.join(self.root, "config", "converted-classes.tsv"), "Widget\tGame\n")
        self.append("config/class-members.tsv", "Gadget\tint extra();\n")
        self.append("src/game/Widget.inc",
                    "void Widget_Merge(Gap::Game::Widget *self, Gap::Game::Widget *other) {\n"
                    "    self->_count = other->_count;\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100200 000010 Widget_Merge\n")
        write(self.table, TABLE + "Widget_Merge\tvoid Widget::merge(Widget *other)\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        # a Gap-qualified parameter is the member's bare class in the class's scope
        self.assertIn("void Widget::merge(Widget *other) {\n    _count = other->_count;\n}\n",
                      self.read("src/game/Widget.inc"))
        members = self.read("config/class-members.tsv")
        self.assertIn("Widget\tvoid merge(Widget *other);\nGadget\tint extra();\n", members)

    def test_a_virtual_function_is_never_called_through_the_vtable_by_its_c_name(self):
        write(os.path.join(self.root, "config", "class-members.tsv"),
              self.read("config/class-members.tsv") + "Widget\tvirtual void reset();\n")
        write(os.path.join(self.root, "src", "game", "Widget.inc"), self.read("src/game/Widget.inc")
              + "void Widget_Reset(Widget *self) {\n}\n")
        write(os.path.join(self.root, "src", "game", "Users.inc"), self.read("src/game/Users.inc")
              + "void Users_Reset(Gadget *g) {\n    Widget_Reset((Widget *)g);\n}\n"
              + "void Gadget::poke() {\n    Widget_Reset(this);\n}\n")
        write(os.path.join(self.root, "src", "game", "Game.h"), self.read("src/game/Game.h")
              + "extern \"C\" void Widget_Reset(Widget *self);\n")
        write(self.table, TABLE + "Widget_Reset\tWidget::reset\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        self.assertIn("void Widget::reset() {\n}", self.read("src/game/Widget.inc"))
        users = self.read("src/game/Users.inc")
        # outside the class the call keeps the C name (and its declaration); a subclass's own call is qualified
        self.assertIn("    Widget_Reset((Widget *)g);", users)
        self.assertIn("void Gadget::poke() {\n    Widget::reset();\n}", users)
        self.assertIn("extern \"C\" void Widget_Reset(Widget *self);", self.read("src/game/Game.h"))

    def append(self, rel, text):
        write(os.path.join(self.root, rel), self.read(rel) + text)

    def constructors(self):
        """A constructor pair: Widget's, and Gadget's, which constructs its Widget base first."""
        self.append("config/class-members.tsv", "Widget\tWidget();\nGadget\tGadget();\n")
        self.append("src/game/Widget.inc",
                    "Widget *Widget_Init(Widget *self) {\n    self->_vtable = (int)&g_Widget_vtable[0];\n"
                    "    self->_count = 0;\n    return self;\n}\n\n"
                    "Gadget *Gadget_Init(Gadget *self) {\n    Widget_Init((Widget *)self);\n"
                    "    self->_vtable = (int)&g_Gadget_vtable[0];\n    self->_extra = 1;\n    return self;\n}\n")
        # a class still written as a flat struct probes its vtable through the C name
        self.append("src/game/Users.inc", "int Users_Probe(void) {\n    int o[2];\n"
                                          "    Widget_Init((Widget *)o);\n    return o[0];\n}\n")
        self.append("include/dw4/game/Widget.h", "#ifdef __cplusplus\nextern \"C\" {\n#endif\n"
                                                 "struct Widget *Widget_Init(struct Widget *self);\n"
                                                 "#ifdef __cplusplus\n}\n#endif\n")
        self.append("src/game/Game.h", "extern \"C\" Widget *Widget_Init(Widget *self);\n"
                                       "extern \"C\" Gadget *Gadget_Init(Gadget *self);\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000020 Widget_Init\n00100140 000020 Gadget_Init\n")
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        rows["0x00100000"]["emitted"].update({"Widget_Init": "0x00100100", "Gadget_Init": "0x00100140"})
        write(os.path.join(self.root, "config", "SLUS-20836", "unit-objects.json"), json.dumps(rows, indent=2))
        write(self.table, TABLE + "Widget_Init\tWidget::Widget\nGadget_Init\tGadget::Gadget\n")

    def test_a_constructor_loses_what_the_compiler_writes(self):
        self.constructors()
        self.assertEqual(self.run_tool("--apply"), 0)
        widget = self.read("src/game/Widget.inc")
        # the vtable stamp and `return self;` are the compiler's; so is the base's construction, first
        self.assertIn("Widget::Widget() {\n    _count = 0;\n}\n", widget)
        self.assertIn("Gadget::Gadget() {\n    _extra = 1;\n}\n", widget)
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        self.assertEqual(rows["0x00100000"]["emitted"]["__ct__6WidgetFv"], "0x00100100")
        self.assertEqual(rows["0x00100000"]["emitted"]["__ct__6GadgetFv"], "0x00100140")

    def test_the_boundary_keeps_the_home_prototype_while_a_flat_struct_uses_the_c_name(self):
        self.constructors()
        self.assertEqual(self.run_tool("--apply"), 0)
        self.assertIn("    Widget_Init((Widget *)o);", self.read("src/game/Users.inc"))
        self.assertIn("struct Widget *Widget_Init(struct Widget *self);", self.read("include/dw4/game/Widget.h"))
        game = self.read("src/game/Game.h")
        # Game.cpp reads the home header: its own copy goes; nothing calls Gadget_Init by its C name any more
        self.assertNotIn("Widget_Init", game)
        self.assertNotIn("Gadget_Init", game)

    def test_a_constructor_constructing_its_base_late_is_refused(self):
        self.constructors()
        # a statement of the class's own before the base's construction: C++ cannot write that order
        text = self.read("src/game/Widget.inc").replace(
            "    Widget_Init((Widget *)self);\n    self->_vtable = (int)&g_Gadget_vtable[0];\n    self->_extra = 1;\n",
            "    self->_extra = 1;\n    Widget_Init((Widget *)self);\n    self->_vtable = (int)&g_Gadget_vtable[0];\n")
        write(os.path.join(self.root, "src", "game", "Widget.inc"), text)
        self.assertEqual(self.run_tool(), 2)

    def test_an_implicit_destructor_goes_and_delete_destroys(self):
        write(os.path.join(self.root, "config", "converted-classes.tsv"), "Widget\tGame\n")
        self.append("src/game/Widget.inc",
                    "/* Widget_Destroy: release, then free */\n"
                    "Widget *Widget_Destroy(Widget *self, short deleteFlag) {\n    if (self != 0) {\n"
                    "        self->_vtable = (int)&g_Widget_vtable[0];\n        if (deleteFlag > 0)\n"
                    "            Memory_Free(self);\n    }\n    return self;\n}\n")
        self.append("src/game/Users.inc",
                    "void Users_Drop(Gap::Game::Widget *w, int o[2]) {\n    Widget_Destroy(w, 1);\n"
                    "    Widget_Destroy((Widget *)o, 0);\n}\n")
        self.append("src/game/Game.h", "extern \"C\" Widget *Widget_Destroy(Widget *self, short deleteFlag);\n")
        write(self.table, TABLE + "Widget_Destroy\tWidget::~Widget\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        widget = self.read("src/game/Widget.inc")
        self.assertNotIn("Widget_Destroy", widget)
        self.assertNotIn("release, then free", widget)
        users = self.read("src/game/Users.inc")
        self.assertIn("    delete w;\n    Widget_Destroy((Widget *)o, 0);\n", users)
        self.assertIn("Widget_Destroy", self.read("src/game/Game.h"))      # the flat probe's prototype
        # the converted class lives in its namespace: its definitions are written inside it
        self.assertIn("namespace Gap {\nnamespace Game {\n\nstruct Meta *Widget::_Meta;\n", widget)
        self.assertIn("int Widget::getCount() {", widget)
        self.assertTrue(widget.endswith("}\n}\n}\n"))

    def test_an_out_of_line_destructor_takes_its_head_over_a_stub(self):
        # VisualCtx: igVisualContext declares `~igVisualContext()`; classconv empties FUN_00150af0 to its receiver
        # (its hand body follows in the splice), and memberize writes the destructor's head over the stub
        self.append("config/class-members.tsv", "Widget\tvirtual ~Widget();\n")
        self.append("src/game/Widget.inc", "Widget *Widget_Destroy(Widget *self, short deleteFlag) {\n"
                                           "    if (deleteFlag > 0)\n        Memory_Free(self);\n    return self;\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000020 Widget_Destroy\n")
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        rows["0x00100000"]["emitted"]["Widget_Destroy"] = "0x00100100"
        write(os.path.join(self.root, "config", "SLUS-20836", "unit-objects.json"), json.dumps(rows, indent=2))
        write(self.table, TABLE + "Widget_Destroy\tWidget::~Widget\n")
        before = self.read("src/game/Widget.inc")
        self.assertEqual(self.run_tool("--apply"), 2)               # a user body: written by hand
        self.assertEqual(before, self.read("src/game/Widget.inc"))
        write(os.path.join(self.root, "src/game/Widget.inc"),
              before.replace("Widget *Widget_Destroy(Widget *self, short deleteFlag) {\n    if (deleteFlag > 0)\n"
                             "        Memory_Free(self);\n    return self;\n}\n",
                             "Widget *Widget_Destroy(Widget *self)\n{\n}\n"))
        self.assertEqual(self.run_tool("--apply"), 0)
        self.assertIn("Widget::~Widget()\n{\n}\n", self.read("src/game/Widget.inc"))
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        self.assertEqual(rows["0x00100000"]["emitted"]["__dt__6WidgetFv"], "0x00100100")

    def test_a_flat_struct_pointer_is_cast_to_the_converted_class_and_back(self):
        # the flat struct Widget (the C view) and Gap::Game::Widget are two types: a flat pointer passed as the
        # receiver or as a Widget * argument is cast to the Gap class, and a converted body passes `this` to C as
        # the flat struct
        write(os.path.join(self.root, "config", "converted-classes.tsv"), "Widget\tGame\n")
        self.append("config/class-members.tsv", "Widget\tvoid take(Widget *other);\nWidget\tvoid poke(::Widget *flat);\n")
        self.append("src/game/Game.h", "extern \"C\" void Widget_Helper(Widget *w);\n"
                                       "extern \"C\" void Widget_Take(Widget *self, Widget *other);\n")
        self.append("src/game/Widget.inc",
                    "void Widget_Take(Widget *self, Widget *other) {\n    Widget_Helper(self);\n"
                    "    Widget_Helper((Widget *)self);\n    self->_count = other->_count;\n}\n\n"
                    "namespace Gap {\nnamespace Game {\n\nvoid Widget::poke(::Widget *flat) {\n"
                    "    Widget_Take(flat, (::Widget *)this);\n    Widget_Take((::Widget *)this, flat);\n}\n}\n}\n")
        self.append("src/game/Users.inc",
                    "void Users_Give(Widget *w, Widget *o, Gap::Game::Widget *g, void *v) {\n"
                    "    Widget_Take(w, o);\n    Widget_Take(g, (Widget *)o);\n    Widget_Take(g, g);\n"
                    "    Widget_Take(g, w + 1);\n    Widget_Take(g, (Gap::Game::Widget *)v);\n    Widget_Take(g, 0);\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000020 Widget_Take\n")
        write(self.table, TABLE + "Widget_Take\tWidget::take\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        widget = self.read("src/game/Widget.inc")
        self.assertIn("void Widget::take(Widget *other) {\n    Widget_Helper((::Widget *)this);\n"
                      "    Widget_Helper((::Widget *)this);\n    _count = other->_count;\n}\n", widget)
        # in Gap's scope the bare name is the Gap class; a cast of `this` to the flat struct goes
        self.assertIn("void Widget::poke(::Widget *flat) {\n    ((Widget *)flat)->take(this);\n"
                      "    take((Widget *)flat);\n}\n", widget)
        users = self.read("src/game/Users.inc")
        self.assertIn("    ((Gap::Game::Widget *)w)->take((Gap::Game::Widget *)o);\n"
                      "    g->take((Gap::Game::Widget *)o);\n    g->take(g);\n"
                      "    g->take((Gap::Game::Widget *)(w + 1));\n    g->take((Gap::Game::Widget *)v);\n"
                      "    g->take(0);\n", users)
        # a flat receiver is no Gap object either
        self.assertIn("((Gap::Game::Widget *)w)->getCount()", users)

    def test_check_reports_a_c_name_declaration_nothing_needs(self):
        self.assertEqual(self.run_tool("--apply"), 0)
        write(os.path.join(self.root, "config", "converted-classes.tsv"), "Widget\tGame\n")
        write(os.path.join(self.root, "config", "SLUS-20836", "compiler-names.tsv"),
              "getCount__6WidgetFv\t0x00100060\tWidget_GetCount\nattach__6WidgetFP3Ctx\t0x00100080\tWidget_Attach\n")
        self.assertEqual(self.run_tool("--check"), 0)
        # Widget_GetCount: user.c still calls it, through Widget.h; a declaration of Widget_Attach left behind
        # serves no code
        self.append("src/game/Game.h", "extern \"C\" void Widget_Attach(WidgetView *view, struct Ctx *ctx);\n")
        self.assertEqual(self.run_tool("--check"), 1)
        found = memberize.boundary_report(self.root)
        self.assertEqual(len(found), 1)
        self.assertRegex(found[0], r"^src/game/Game.h:\d+: Widget_Attach: C-name declaration no longer needed: no "
                                   r"unconverted code")

    def test_a_protected_static_is_read_outside_its_class_through_its_public_getter(self):
        self.append("src/game/Users.inc", "struct Meta *Users_Meta(void) {\n    return g_Widget_meta;\n}\n"
                                          "void Users_Reset(void) {\n    g_Widget_meta = 0;\n}\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        users = self.read("src/game/Users.inc")
        self.assertIn("return Widget::getClassMeta();", users)
        # a write cannot go through the getter: it keeps the C name
        self.assertIn("g_Widget_meta = 0;", users)

    def test_a_pointer_passed_for_a_reference_is_dereferenced(self):
        # the C form took a pointer to the value; the member takes the kit's reference
        self.append("config/class-members.tsv", "Widget\tvoid setValue(const Vec &v);\n")
        self.append("src/game/Game.h", "struct Vec { float f[3]; Vec(float x); };\n"
                                       "extern \"C\" void Widget_SetValue(Widget *self, const Vec &v);\n")
        self.append("src/game/Widget.inc", "void Widget_SetValue(Widget *self, const Vec &v) {\n}\n")
        self.append("src/game/Users.inc",
                    "void Users_Set(Widget *w, struct S *s) {\n    float a[3];\n    Vec v(0.0f);\n"
                    "    Widget_SetValue(w, a);\n    Widget_SetValue(w, (const float *)&s);\n"
                    "    Widget_SetValue(w, Vec(1.0f).f);\n    Widget_SetValue(w, v);\n"
                    "    Widget_SetValue(w, a + 1);\n}\n"
                    "void Users_Pass(Widget *w, Vec *value, int *q) {\n    Widget_SetValue(w, *value);\n"
                    "    Widget_SetValue(w, *(Vec *)q);\n    Widget_SetValue(w, *(value));\n}\n"
                    "void Users_Local(Widget *w, Vec other, int n) {\n"
                    "    Widget_SetValue(w, &other);\n    Widget_SetValue(w, &n);\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000020 Widget_SetValue\n")
        write(self.table, TABLE + "Widget_SetValue\tWidget::setValue\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        users = self.read("src/game/Users.inc")
        self.assertIn("    w->setValue(*(const Vec *)a);\n    w->setValue(*(const Vec *)&s);\n"
                      "    w->setValue(Vec(1.0f));\n    w->setValue(v);\n"
                      "    w->setValue(*(const Vec *)(a + 1));\n", users)
        # an argument already written as the value is not dereferenced again
        self.assertIn("    w->setValue(*value);\n    w->setValue(*(Vec *)q);\n    w->setValue(*(value));\n", users)
        # the address of a value declared as the referenced type is the value; another type's is dereferenced
        self.assertIn("    w->setValue(other);\n    w->setValue(*(const Vec *)&n);\n", users)

    def test_a_static_whose_return_type_changed_keeps_its_uses_types(self):
        # the C form returned an int (and the member a pointer): an assignment of the result and a field table
        # naming the function keep the C type through a cast
        self.append("config/class-members.tsv", "Widget\tstatic Widget *make();\n")
        self.append("src/game/Game.h", "extern \"C\" int Widget_Make(void);\n")
        self.append("src/game/Widget.inc", "int Widget_Make(void) {\n    return 0;\n}\n")
        self.append("src/game/Users.inc",
                    "typedef Widget *(*Factory)(void);\n"
                    "static Factory g_factories[] = {\n    Widget_Make,\n    (Factory)Widget_Make,\n};\n"
                    "void Users_Make(int *p) {\n    *p = Widget_Make();\n    p[1] = (int)Widget_Make();\n"
                    "    if (Widget_Make() == 0) {\n    }\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000020 Widget_Make\n")
        write(self.table, TABLE + "Widget_Make\tWidget::make\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        self.assertIn("Widget *Widget::make() {", self.read("src/game/Widget.inc"))
        users = self.read("src/game/Users.inc")
        self.assertIn("    (Factory)Widget::make,\n    (Factory)Widget::make,\n", users)
        self.assertIn("    *p = (int)Widget::make();\n    p[1] = (int)Widget::make();\n"
                      "    if (Widget::make() == 0) {\n", users)

    def test_a_converted_static_returning_its_class_keeps_flat_holders_flat(self):
        # the C form returned the flat struct, the member the Gap class: an assignment to a holder at file scope
        # (declared as the flat struct) casts the result back to it; one in Gap's scope takes the class as is
        write(os.path.join(self.root, "config", "converted-classes.tsv"), "Widget\tGame\n")
        self.append("config/class-members.tsv", "Widget\tstatic Widget *make();\n")
        self.append("src/game/Game.h", "extern \"C\" Widget *Widget_Make(void);\n")
        self.append("src/game/Widget.inc", "Widget *Widget_Make(void) {\n    return 0;\n}\n")
        self.append("src/game/Users.inc",
                    "Widget *g_made;\nvoid Users_Make(void) {\n    g_made = Widget_Make();\n"
                    "    if (Widget_Make() == 0) {\n    }\n}\n"
                    "namespace Gap {\nnamespace Game {\nvoid Users_Gap(Widget *w) {\n    w = Widget_Make();\n}\n}\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000020 Widget_Make\n")
        write(self.table, TABLE + "Widget_Make\tWidget::make\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        users = self.read("src/game/Users.inc")
        self.assertIn("    g_made = (Widget *)Gap::Game::Widget::make();\n"
                      "    if (Gap::Game::Widget::make() == 0) {\n", users)
        self.assertIn("    w = Gap::Game::Widget::make();\n", users)

    def test_an_integer_the_member_takes_as_a_pointer_is_cast_at_its_calls(self):
        # the C forms take the pool as an int (one in its definition, one only in its prototype, as classconv
        # leaves it after retyping the definition): the heads take the member's pointer, each call drops its int
        # cast where the argument already has the pointer's type and casts it to the pointer otherwise
        self.append("config/class-members.tsv",
                    "Widget\tstatic Widget *make(struct Pool *pool);\nWidget\tstatic Widget *build(struct Pool *pool);\n")
        self.append("src/game/Game.h", "extern \"C\" Widget *Widget_Make(int pool);\n"
                                       "extern \"C\" Widget *Widget_Build(int pool);\n"
                                       "extern \"C\" struct Pool *Pool_Get(int which);\n")
        self.append("src/game/Widget.inc", "Widget *Widget_Make(int pool) {\n    return 0;\n}\n"
                                           "Widget *Widget_Build(struct Pool *pool) {\n    return 0;\n}\n")
        self.append("src/game/Users.inc",
                    "typedef Widget *(*Factory)(int);\n"
                    "static Factory g_factories[] = {\n    Widget_Make,\n};\n"
                    "void Users_Make(Widget *w, int n) {\n    Widget_Make((int)Pool_Get(3));\n"
                    "    Widget_Make((int)w);\n    Widget_Make(0);\n    Widget_Make(n + 4);\n"
                    "    Widget_Build((int)(Pool_Get(1)));\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000020 Widget_Make\n00100120 000020 Widget_Build\n")
        write(self.table, TABLE + "Widget_Make\tWidget::make\nWidget_Build\tWidget::build\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        widget = self.read("src/game/Widget.inc")
        self.assertIn("Widget *Widget::make(Pool *pool) {", widget)
        self.assertIn("Widget *Widget::build(struct Pool *pool) {", widget)
        users = self.read("src/game/Users.inc")
        self.assertIn("    (Factory)Widget::make,\n", users)
        self.assertIn("    Widget::make(Pool_Get(3));\n    Widget::make((Pool *)w);\n    Widget::make(0);\n"
                      "    Widget::make((Pool *)(n + 4));\n    Widget::build(Pool_Get(1));\n", users)

    def test_an_integer_passed_for_an_enum_parameter_is_cast(self):
        # FUN_0017f080's draw: the C form took the primitive as an int, the member the kit's IG_GFX_DRAW; a nested
        # enum (igFile::OpenMode) is cast to its owner's spelling outside the class
        write(os.path.join(self.root, "config", "converted-classes.tsv"), "Widget\tGame\n")
        self.append("src/game/Game.h",
                    "typedef enum IG_GFX_DRAW {\n"
                    "    IG_GFX_DRAW_POINTS, IG_GFX_DRAW_LINES, IG_GFX_DRAW_DRAWMULTIPLE = 8192\n} IG_GFX_DRAW;\n"
                    "extern \"C\" void Widget_Draw(Widget *self, int primitive, int count);\n"
                    "extern \"C\" void Widget_SetMode(Widget *self, int mode);\n")
        self.append("config/class-members.tsv", "Widget\tenum Mode { kRead, kWrite };\n"
                                                "Widget\tvoid draw(IG_GFX_DRAW primitive, int count);\n"
                                                "Widget\tvoid setMode(Mode mode);\n"
                                                "Widget\tvirtual void configure(IG_GFX_DRAW primitive);\n")
        self.append("src/game/Widget.inc", "void Widget_Draw(Widget *self, IG_GFX_DRAW primitive, int count) {\n}\n"
                                           "void Widget_SetMode(Widget *self, Mode mode) {\n}\n"
                                           "void Widget_Configure(Widget *self, IG_GFX_DRAW primitive) {\n}\n")
        self.append("src/game/Users.inc",
                    "void Users_Draw(Gap::Game::Widget *w, int primitive, IG_GFX_DRAW kind, int n) {\n"
                    "    Widget_Draw(w, primitive, 3);\n    Widget_Draw(w, IG_GFX_DRAW_LINES, 3);\n"
                    "    Widget_Draw(w, kind, n);\n    Widget_Draw(w, IG_GFX_DRAW_DRAWMULTIPLE | n, 3);\n"
                    "    Widget_Draw(w, 0, 3);\n    Widget_SetMode(w, n);\n"
                    "    Widget_SetMode(w, Gap::Game::Widget::kWrite);\n}\n"
                    "void Gadget::redo(int primitive) {\n    Widget_Configure(this, primitive);\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000020 Widget_Draw\n00100120 000020 Widget_SetMode\n"
                                                     "00100140 000020 Widget_Configure\n")
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        rows["0x00100000"]["emitted"]["Widget_SetMode"] = "0x00100120"
        write(os.path.join(self.root, "config", "SLUS-20836", "unit-objects.json"), json.dumps(rows, indent=2))
        write(self.table, TABLE + "Widget_Draw\tWidget::draw\nWidget_SetMode\tWidget::setMode\n"
                                  "Widget_Configure\tWidget::configure\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        users = self.read("src/game/Users.inc")
        self.assertIn("    w->draw((IG_GFX_DRAW)primitive, 3);\n    w->draw(IG_GFX_DRAW_LINES, 3);\n"
                      "    w->draw(kind, n);\n    w->draw((IG_GFX_DRAW)(IG_GFX_DRAW_DRAWMULTIPLE | n), 3);\n"
                      "    w->draw((IG_GFX_DRAW)0, 3);\n    w->setMode((Gap::Game::Widget::Mode)n);\n"
                      "    w->setMode(Gap::Game::Widget::kWrite);\n", users)
        # a subclass's direct call of the virtual base (FUN_0017f080's configure)
        self.assertIn("    Widget::configure((IG_GFX_DRAW)primitive);\n", users)
        # MWCC names the nested enum by its owner (setOpenMode__Q33Gap4Core6igFileFQ43Gap4Core6igFile8OpenMode)
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        self.assertEqual(rows["0x00100000"]["emitted"]["setMode__Q33Gap4Game6WidgetFQ43Gap4Game6Widget4Mode"],
                         "0x00100120")

    def test_the_address_of_a_temporary_is_the_temporary(self):
        # igImage::setName(igStringRef): the C form took `const igStringRef *`, its callers `&igStringRef(...)`
        self.append("src/game/Game.h", "struct igStringRef { char *p; igStringRef(const char *s); };\n"
                                       "extern \"C\" void Widget_SetName(Widget *self, const igStringRef *name);\n")
        self.append("config/class-members.tsv", "Widget\tvoid setName(igStringRef name);\n")
        self.append("src/game/Widget.inc", "void Widget_SetName(Widget *self, igStringRef name) {\n}\n")
        self.append("src/game/Users.inc",
                    "void Users_Name(Widget *w, int arg1) {\n"
                    "    Widget_SetName(w, &igStringRef((const char *)arg1));\n"
                    "    Widget_SetName(w, &igStringRef(\"SphereImage\"));\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000020 Widget_SetName\n")
        write(self.table, TABLE + "Widget_SetName\tWidget::setName\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        users = self.read("src/game/Users.inc")
        self.assertIn("    w->setName(igStringRef((const char *)arg1));\n"
                      "    w->setName(igStringRef(\"SphereImage\"));\n", users)

    def test_a_pointer_passed_for_a_typedef_template_reference_is_the_held_value(self):
        # igRegistry::getValue(..., igStringObjRef &strVal, ...): the C form took `igStringObj **`
        self.append("src/game/Game.h",
                    "template <class T> struct igSmartPointer { T *p; };\nstruct igStringObj;\n"
                    "typedef igSmartPointer<igStringObj> igStringObjRef;\n"
                    "extern \"C\" bool Widget_GetText(Widget *self, int section, igStringObj **out);\n"
                    "extern \"C\" bool Widget_GetFlag(Widget *self, int section, unsigned char *out);\n")
        self.append("config/class-members.tsv", "Widget\tbool getText(int section, igStringObjRef &strVal);\n"
                                                "Widget\tbool getFlag(int section, unsigned char &boolVal);\n")
        self.append("src/game/Widget.inc", "bool Widget_GetText(Widget *self, int section, igStringObjRef &strVal) {\n"
                                           "    return section != 0;\n}\n"
                                           "bool Widget_GetFlag(Widget *self, int section, unsigned char &boolVal) {\n"
                                           "    return section != 0;\n}\n")
        self.append("src/game/Users.inc",
                    "void Users_Text(Widget *w) {\n    igSmartPointer<igStringObj> value(make());\n"
                    "    igStringObjRef infoSection;\n    igStringObj *text;\n    bool flag;\n    unsigned char byte;\n"
                    "    Widget_GetText(w, 1, (igStringObj **)&value);\n    Widget_GetText(w, 1, &infoSection.p);\n"
                    "    Widget_GetText(w, 2, &text);\n"
                    "    Widget_GetFlag(w, 3, (unsigned char *)&flag);\n    Widget_GetFlag(w, 3, &byte);\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000020 Widget_GetText\n00100120 000020 Widget_GetFlag\n")
        write(self.table, TABLE + "Widget_GetText\tWidget::getText\nWidget_GetFlag\tWidget::getFlag\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        users = self.read("src/game/Users.inc")
        self.assertIn("    w->getText(1, value);\n    w->getText(1, infoSection);\n"
                      "    w->getText(2, *(igStringObjRef *)&text);\n"
                      "    w->getFlag(3, *(unsigned char *)&flag);\n    w->getFlag(3, byte);\n", users)

    def test_arguments_take_the_members_order_where_the_c_prototype_differs(self):
        # igRegistry_GetValueFloat(registry, section, key, out, create, defaultValue) is the kit's
        # getValue(sectionHandle, valueName, floatVal, defaultVal, createValue)
        self.append("src/game/Game.h", "extern \"C\" bool Widget_GetValueFloat(Widget *self, int section, "
                                       "const char *key, float *out, int create, float defaultValue);\n")
        self.append("config/class-members.tsv", "Widget\tbool getValue(int sectionHandle, const char *valueName, "
                                                "float &floatVal, float defaultVal, unsigned char createValue);\n")
        self.append("src/game/Widget.inc",
                    "bool Widget_GetValueFloat(Widget *self, int sectionHandle, const char *valueName, "
                    "float &floatVal, float defaultVal, unsigned char createValue) {\n"
                    "    return createValue != 0;\n}\n")
        self.append("src/game/Users.inc",
                    "void Users_Float(Widget *w, int section, const char *key) {\n    float value;\n"
                    "    if (Widget_GetValueFloat(w, section, key, &value, 0, 0.0f)) {\n    }\n"
                    "    Widget_GetValueFloat(w, Widget_GetCount(w), key, &value, section + 1, "
                    "(float)Widget_GetCount(w));\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000020 Widget_GetValueFloat\n")
        write(self.table, TABLE + "Widget_GetValueFloat\tWidget::getValue\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        users = self.read("src/game/Users.inc")
        self.assertIn("    if (w->getValue(section, key, value, 0.0f, 0)) {\n", users)
        # the arguments' own rewrites move with them
        self.assertIn("    w->getValue(w->getCount(), key, value, (float)w->getCount(), section + 1);\n", users)

    def test_an_order_the_types_and_names_cannot_settle_is_refused(self):
        self.append("src/game/Game.h", "extern \"C\" void Widget_Mix(Widget *self, float a, int b, int c);\n")
        self.append("config/class-members.tsv", "Widget\tvoid mix(int x, int y, float z);\n")
        self.append("src/game/Widget.inc", "void Widget_Mix(Widget *self, int x, int y, float z) {\n}\n")
        self.append("src/game/Users.inc", "void Users_Mix(Widget *w) {\n    Widget_Mix(w, 1.0f, 2, 3);\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000020 Widget_Mix\n")
        write(self.table, TABLE + "Widget_Mix\tWidget::mix\n")
        before = self.read("src/game/Users.inc")
        self.assertEqual(self.run_tool("--apply"), 2)
        self.assertEqual(before, self.read("src/game/Users.inc"))

    def test_operator_new_members_and_their_callers(self):
        # igObject_AllocateRawStorage / igObject_AllocateRawStorageDefault are the kit's igObject::operator new(size_t,
        # size_t, igMemoryPool *) pair; the table rows were refused as "neither `Class::name` nor a member signature"
        write(os.path.join(self.root, "config", "converted-classes.tsv"), "Widget\tGame\n")
        self.append("config/class-members.tsv",
                    "Widget\tstatic void *operator new(unsigned int size, void *memory, void *unused) { return memory; }\n"
                    "Widget\tstatic void operator delete(void *memory) { Pool_Free(memory); }\n")
        self.append("src/game/Game.h", "typedef unsigned int size_t;\nstruct Pool;\n"
                    "extern \"C\" char *Widget_AllocateRawStorage(unsigned int size, unsigned int prefix_size, "
                    "struct Pool *requested_pool);\n"
                    "extern \"C\" void *Widget_AllocateRawStorageDefault(unsigned int size, unsigned int prefix);\n")
        self.append("src/game/Widget.inc",
                    "char *Widget_AllocateRawStorage(unsigned int size, unsigned int prefix_size, Pool *requested_pool) {\n"
                    "    if (requested_pool == 0) {\n        return 0;\n    }\n"
                    "    return (char *)requested_pool + prefix_size;\n}\n\n"
                    "void *Widget_AllocateRawStorageDefault(unsigned int size,unsigned int prefix)"
                    "{return Widget_AllocateRawStorage(size,prefix,0);}\n")
        self.append("src/game/Users.inc", "void *Users_Make(Pool *pool) {\n"
                                          "    return Widget_AllocateRawStorage(0x34, 0, pool);\n}\n"
                                          "void *Users_MakeDefault(int size) {\n"
                                          "    return Widget_AllocateRawStorageDefault(size, 0);\n}\n")
        self.append("config/SLUS-20836/symbols.txt",
                    "00100200 000070 Widget_AllocateRawStorage\n00100270 000010 Widget_AllocateRawStorageDefault\n")
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        rows["0x00100000"]["emitted"].update({"Widget_AllocateRawStorage": "0x00100200",
                                              "Widget_AllocateRawStorageDefault": "0x00100270"})
        write(os.path.join(self.root, "config", "SLUS-20836", "unit-objects.json"), json.dumps(rows, indent=2))
        write(self.table, "Widget_AllocateRawStorage\tvoid *Widget::operator new(size_t cSize, size_t allocSize, "
                          "Pool *mp)\n"
                          "Widget_AllocateRawStorageDefault\tvoid *Widget::operator new(size_t cSize, size_t allocSize)\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        widget = self.read("src/game/Widget.inc")
        self.assertIn("void *Widget::operator new(unsigned int size, unsigned int prefix_size, Pool *requested_pool) {",
                      widget)
        # inside the class the other allocator is called bare
        self.assertIn("void *Widget::operator new(unsigned int size, unsigned int prefix)"
                      "{return operator new(size,prefix,0);}", widget)
        users = self.read("src/game/Users.inc")
        self.assertIn("    return Gap::Game::Widget::operator new(0x34, 0, pool);\n", users)
        self.assertIn("    return Gap::Game::Widget::operator new(size, 0);\n", users)
        self.assertNotIn("Widget_AllocateRawStorage", self.read("src/game/Game.h"))
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        self.assertEqual(rows["0x00100000"]["emitted"]["__nw__Q33Gap4Game6WidgetFUiUiP4Pool"], "0x00100200")
        self.assertEqual(rows["0x00100000"]["emitted"]["__nw__Q33Gap4Game6WidgetFUiUi"], "0x00100270")
        members = self.read("config/class-members.tsv")
        self.assertIn("Widget\tstatic void *operator new(size_t cSize, size_t allocSize, Pool *mp);\n", members)
        self.assertIn("Widget\tstatic void *operator new(size_t cSize, size_t allocSize);\n", members)

    def test_a_key_naming_a_class_converted_since_as_flat_is_renamed(self):
        # igImage::platformLoad(igFile *) was keyed `…FP6igFile` while igFile was flat; once igFile is a Gap
        # class, the compiler names it `…FPQ33Gap4Core6igFile`
        write(os.path.join(self.root, "config", "converted-classes.tsv"), "Widget\tGame\nGadget\tGame\n")
        self.append("config/class-members.tsv", "Gadget\tvirtual unsigned char load(Widget *file);\n"
                                                "Gadget\tvoid keep(::Widget *flat);\n")
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        rows["0x00400000"]["emitted"] = {"load__Q33Gap4Game6GadgetFP6Widget": "0x00400010",
                                         "keep__Q33Gap4Game6GadgetFP6Widget": "0x00400020"}
        write(os.path.join(self.root, "config", "SLUS-20836", "unit-objects.json"), json.dumps(rows, indent=2))
        self.assertEqual(memberize.main(["--check", "--root", self.root]), 1)
        self.assertEqual(memberize.main(["--rekey", "--apply", "--root", self.root]), 0)
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        # a parameter the declaration spells as the flat struct keeps its name
        self.assertEqual(rows["0x00400000"]["emitted"], {"load__Q33Gap4Game6GadgetFPQ33Gap4Game6Widget": "0x00400010",
                                                         "keep__Q33Gap4Game6GadgetFP6Widget": "0x00400020"})
        self.assertEqual(memberize.main(["--check", "--root", self.root]), 0)

    def test_a_template_instance_naming_a_class_converted_since_is_renamed_from_the_object(self):
        # 0x1493e0 placed `__dt__32igSmartPointer<14igVertexStream>Fv` at 0x14aaf0; once igVertexStream converted, the
        # unit's members (in Gap::Gfx) instantiate igSmartPointer<Gap::Gfx::igVertexStream>, and --rekey left the
        # key. Another unit still destroys a flat igSmartPointer<igObject>: only the objects tell them apart.
        write(os.path.join(self.root, "config", "converted-classes.tsv"),
              "igObject\tCore\nigVertexStream\tGfx\nigVertexArray2Helper\tGfx\nigMediaFile\tCore\n")
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        rows["0x00100000"]["emitted"]["__dt__32igSmartPointer<14igVertexStream>Fv"] = "0x0014aaf0"
        rows["0x00100000"]["stripped"] = ["__dt__25igSmartPointer<8igObject>Fv",
                                          "__dt__38igSmartPointer<20igVertexArray2Helper>Fv"]
        rows["0x00400000"]["emitted"] = {"__dt__25igSmartPointer<8igObject>Fv": "0x00400010",
                                         "getElementMeta__Q33Gap4Core28igTObjectList<11igMediaFile>CFv": "0x00400020"}
        write(os.path.join(self.root, "config", "SLUS-20836", "unit-objects.json"), json.dumps(rows, indent=2))
        objects = {
            "0x00100000": {"__dt__42igSmartPointer<Q33Gap3Gfx14igVertexStream>Fv", "__dt__25igSmartPointer<8igObject>Fv",
                           "__dt__48igSmartPointer<Q33Gap3Gfx20igVertexArray2Helper>Fv"},
            "0x00400000": {"__dt__25igSmartPointer<8igObject>Fv",
                           "getElementMeta__Q33Gap4Core39igTObjectList<Q33Gap4Core11igMediaFile>CFv"}}
        with mock.patch.object(memberize, "unit_object_names", lambda root, unit, row: objects[unit], create=True):
            self.assertEqual(memberize.main(["--rekey", "--apply", "--root", self.root]), 0)
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        emitted = rows["0x00100000"]["emitted"]
        self.assertEqual(emitted.get("__dt__42igSmartPointer<Q33Gap3Gfx14igVertexStream>Fv"), "0x0014aaf0")
        self.assertNotIn("__dt__32igSmartPointer<14igVertexStream>Fv", emitted)
        self.assertEqual(rows["0x00100000"]["stripped"], ["__dt__25igSmartPointer<8igObject>Fv",
                                                          "__dt__48igSmartPointer<Q33Gap3Gfx20igVertexArray2Helper>Fv"])
        self.assertEqual(rows["0x00400000"]["emitted"], {
            "__dt__25igSmartPointer<8igObject>Fv": "0x00400010",
            "getElementMeta__Q33Gap4Core39igTObjectList<Q33Gap4Core11igMediaFile>CFv": "0x00400020"})

    def test_names_of_classes_the_tree_no_longer_declares_follow_the_object(self):
        # IGBFile renamed ScopedLock to the kit's igScopeLock and retired igSemaphoreView: 0x2b5d50's `stripped`
        # kept __dt__10ScopedLockFv and __dt__33igSmartPointer<15igSemaphoreView>Fv, which its object no longer has
        self.append("src/game/Game.h", "struct igScopeLock { int held; };\n")
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        rows["0x00100000"]["emitted"]["__dt__40igSmartPointer<Q33Gap4Core11igSemaphore>Fv"] = "0x002ba970"
        rows["0x00100000"]["stripped"] = ["__dt__10ScopedLockFv", "__dt__25igSmartPointer<8igObject>Fv",
                                          "__dt__33igSmartPointer<15igSemaphoreView>Fv"]
        write(os.path.join(self.root, "config", "SLUS-20836", "unit-objects.json"), json.dumps(rows, indent=2))
        objects = {"0x00100000": {"__dt__11igScopeLockFv", "__dt__25igSmartPointer<8igObject>Fv",
                                  "__dt__40igSmartPointer<Q33Gap4Core11igSemaphore>Fv"}}
        with mock.patch.object(memberize, "unit_object_names", lambda root, unit, row: objects[unit]):
            self.assertEqual(memberize.main(["--rekey", "--apply", "--root", self.root]), 0)
        row = json.loads(self.read("config/SLUS-20836/unit-objects.json"))["0x00100000"]
        self.assertEqual(row["stripped"], ["__dt__11igScopeLockFv", "__dt__25igSmartPointer<8igObject>Fv"])
        self.assertEqual(row["emitted"]["__dt__40igSmartPointer<Q33Gap4Core11igSemaphore>Fv"], "0x002ba970")

    def test_a_c_head_naming_a_nested_enum_by_its_owner_is_the_members(self):
        # IGBFile2: igIGBFile_OpenFile(..., igFile::OpenMode mode) was refused as "(char const*, igFile : :
        # OpenMode) are not Gap::Core::igIGBFile::open's (char const*, OpenMode)": igIGBFile derives from igFile
        write(os.path.join(self.root, "config", "converted-classes.tsv"), "Widget\tGame\nGadget\tGame\n")
        self.append("config/class-members.tsv", "Widget\tenum Mode { kRead, kWrite };\n"
                                                "Gadget\tint open(const char *fileName, Mode mode);\n")
        self.append("src/game/Game.h", "extern \"C\" int Gadget_Open(Gadget *self, const char *name, int mode);\n")
        self.append("src/game/Widget.inc", "int Gadget_Open(Gadget *self, const char *name, Widget::Mode mode) {\n"
                                           "    return mode;\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000020 Gadget_Open\n")
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        rows["0x00100000"]["emitted"]["Gadget_Open"] = "0x00100100"
        write(os.path.join(self.root, "config", "SLUS-20836", "unit-objects.json"), json.dumps(rows, indent=2))
        write(self.table, TABLE + "Gadget_Open\tGadget::open\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        # the body moves into the class's namespaces (cxxscope.respell), its head keeping the C form's spelling
        self.assertIn("int Gadget::open(const char *name, Widget::Mode mode) {\n    return mode;\n}",
                      self.read("src/game/Widget.inc"))
        rows = json.loads(self.read("config/SLUS-20836/unit-objects.json"))
        self.assertEqual(rows["0x00100000"]["emitted"]["open__Q33Gap4Game6GadgetFPCcQ43Gap4Game6Widget4Mode"],
                         "0x00100100")

    def test_a_c_head_of_layout_compatible_types_takes_the_members(self):
        # GfxConverters: FUN_0016f690(unsigned *, unsigned char *, int, ImagePalette *) was refused against
        # igPsx2ImageConvert::pal_8_To_rgba_8888(unsigned char *dest, const unsigned char *source, int nSample,
        # void *misc); CoreFiles2's int for an unsigned size, Psx2VC2's int for a bool
        self.append("config/class-members.tsv",
                    "Widget\tstatic void convert(unsigned char *dest, const unsigned char *source, int nSample, "
                    "void *misc);\n"
                    "Widget\tvoid reserve(unsigned int size, bool enable);\n")
        self.append("src/game/Game.h", "struct ImagePalette { int used; unsigned int colors[16]; };\n"
                                       "extern \"C\" void FUN_00100100(unsigned int *dst, unsigned char *src, int n, "
                                       "ImagePalette *palette);\n"
                                       "extern \"C\" void Widget_Reserve(Widget *self, int size, int enable);\n")
        self.append("src/game/Widget.inc",
                    "void FUN_00100100(unsigned int *dst, unsigned char *src, int n, ImagePalette *palette) {\n"
                    "    palette->used = 1;\n    while (n-- > 0)\n        *dst++ = palette->colors[*src++];\n}\n"
                    "void Widget_Reserve(Widget *self, int size, int enable) {\n"
                    "    self->_count = enable ? size : 0;\n}\n")
        self.append("src/game/Users.inc",
                    "void Users_Convert(Widget *w, unsigned int *buf, unsigned char *bytes, ImagePalette *pal) {\n"
                    "    FUN_00100100(buf, bytes, 4, pal);\n    FUN_00100100((unsigned int *)bytes, bytes + 1, 4, pal);\n"
                    "    Widget_Reserve(w, 8, 1);\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000020 FUN_00100100\n00100120 000020 Widget_Reserve\n")
        write(self.table, TABLE + "FUN_00100100\tWidget::convert\nWidget_Reserve\tWidget::reserve\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        widget = self.read("src/game/Widget.inc")
        self.assertIn("void Widget::convert(unsigned char *dest, const unsigned char *source, int n, void *misc) {\n"
                      "    unsigned int *dst = (unsigned int *)dest;\n"
                      "    unsigned char *src = (unsigned char *)source;\n"
                      "    ImagePalette *palette = (ImagePalette *)misc;\n"
                      "    palette->used = 1;\n", widget)
        self.assertIn("void Widget::reserve(unsigned int size, bool enable) {\n    _count = enable ? size : 0;\n}",
                      widget)
        users = self.read("src/game/Users.inc")
        self.assertIn("    Widget::convert((unsigned char *)buf, bytes, 4, pal);\n"
                      "    Widget::convert((unsigned char *)bytes, bytes + 1, 4, pal);\n"
                      "    w->reserve(8, 1);\n", users)

    def test_a_c_head_whose_parameter_means_something_else_is_refused(self):
        # GfxImage's FUN_00156340(const igStringRef *) for igImage::setName(igStringRef), CoreFiles's
        # igFile_SkipToChar(long long) for readPastChar(char) unless the table row states the member's signature
        self.append("src/game/Game.h", "struct igStringRef { char *p; };\n")
        self.append("config/class-members.tsv", "Widget\tvoid setName(igStringRef name);\n"
                                                "Widget\tvoid readPastChar(char c);\n")
        self.append("src/game/Widget.inc", "void Widget_SetName(Widget *self, const igStringRef *name) {\n}\n"
                                           "void Widget_SkipToChar(Widget *self, long long c) {\n}\n")
        self.append("config/SLUS-20836/symbols.txt", "00100100 000020 Widget_SetName\n"
                                                     "00100120 000020 Widget_SkipToChar\n")
        before = self.read("src/game/Widget.inc")
        for row, message in (("Widget_SetName\tWidget::setName\n",
                              "parameter 1 is a pointer (igStringRef const*) where the member takes a value "
                              "(igStringRef)"),
                             ("Widget_SkipToChar\tWidget::readPastChar\n",
                              "parameter 1 is a 64-bit integer (long long) where the member takes an integer (char) "
                              "(a table row giving the member's signature retypes it)")):
            write(self.table, TABLE + row)
            err = io.StringIO()
            with mock.patch("sys.stderr", err):
                self.assertEqual(self.run_tool("--apply"), 2)
            self.assertIn(message, err.getvalue())
            self.assertEqual(before, self.read("src/game/Widget.inc"))
        write(self.table, TABLE + "Widget_SkipToChar\tvoid Widget::readPastChar(char c)\n")
        self.assertEqual(self.run_tool("--apply"), 0)
        self.assertIn("void Widget::readPastChar(char c) {\n}", self.read("src/game/Widget.inc"))


class Helpers(unittest.TestCase):
    MACROS = {"OBJ_BOOT": (("C",), "public: C(); virtual void __bootstrapDestruct(); "
                                   "protected: static struct Meta *_Meta; public: "
                                   "static inline struct Meta *getClassMeta() { return _Meta; }")}

    def test_a_deletion_between_two_blocks_leaves_one_block(self):
        # an inline member's C definition between two blocks of a class converted earlier goes; the blocks it
        # separated become one, and two blocks nothing was deleted between keep their bounds
        block = "namespace Gap {\nnamespace Core {\n\nvoid igObject::%s()\n{\n}\n}\n}\n"
        text = block % "a" + "\nint FUN_00100040(void) {\n    return 0;\n}\n\n" + block % "b" + "\n" + block % "c"
        fr = memberize.FileRewrite("src/x.inc", text)
        start = text.index("int FUN_00100040")
        fr.deletes.append((start, text.index("namespace", start)))
        self.assertEqual(fr.result(), "namespace Gap {\nnamespace Core {\n\nvoid igObject::a()\n{\n}\n\n"
                                      "void igObject::b()\n{\n}\n}\n}\n\n" + block % "c")

    def test_a_virtual_a_macro_declares_is_virtual(self):
        rows = ["OBJ_BOOT(Widget)", "void reset();"]
        types = memberize.declarations.Types()
        self.assertTrue(memberize.declares_virtual(rows, "__bootstrapDestruct", (), self.MACROS, types, "Widget"))
        self.assertEqual(memberize.declared_access(rows, "_Meta", self.MACROS), "protected")
        self.assertIsNone(memberize.declared_access(rows, "reset", self.MACROS))
        self.assertEqual(memberize.public_getter(rows, "_Meta", self.MACROS), "getClassMeta")

    def test_a_non_virtual_overload_of_a_virtual_name_is_not_virtual(self):
        rows = ["virtual void resetFields(int flag);", "void resetFields();"]
        types = memberize.declarations.Types()
        self.assertTrue(memberize.declares_virtual(rows, "resetFields", ("int",), None, types, "Widget"))
        self.assertFalse(memberize.declares_virtual(rows, "resetFields", (), None, types, "Widget"))

    def test_a_read_is_neither_assigned_nor_addressed(self):
        clean = "x = g; g = 1; f(&g); g == 2; g += 1; ++g;"
        reads = [memberize._is_read(clean, m.start(), m.end()) for m in re.finditer(r"\bg\b", clean)]
        self.assertEqual(reads, [True, False, False, True, False, False])

    def test_a_string_literal_argument_is_kept(self):
        text = 'f(o, "name", 0)'
        clean = 'f(o,       , 0)'
        spans = memberize._arg_spans(clean, 1, len(text) - 1, text)
        self.assertEqual([text[s:e] for s, e in spans], ["o", '"name"', "0"])


class CompilerNames(unittest.TestCase):
    """The compiler names MWCC emits for the core file classes' members (config/SLUS-20836/compiler-names.tsv)."""
    MEMBERS = {
        "igFile": ["enum OpenMode { kRead, kWrite, kDefaultOpenMode };", "void setOpenMode(OpenMode openMode);",
                   "virtual void freadAsynchronous(void *ptr, int sizeInBytes, igIOCallbackFunction *callback, "
                   "int token);"],
        "igMediaFile": ["public: virtual int open(OpenMode e = kDefaultOpenMode);"],
        "igMedia": ["virtual int open(int fileHandle, igStringRef name, igFile::OpenMode openMode) = 0;"],
        "igImage": ["virtual unsigned char platformLoad(igFile *file);"],
        "igExternalDirEntry": ["bool resolve(igResolveFunction *resolveFunction);"],
    }
    LIBS = {"igFile": "Core", "igMediaFile": "Core", "igMedia": "Core", "igImage": "Gfx", "igExternalDirEntry": "Core",
            "igObject": "Core"}
    TYPEDEFS = ["typedef void igIOCallbackFunction(int requestID, int result);\n",
                "/* resolve */ typedef bool igResolveFunction(igExternalDirEntry *externalEntry);\n"]

    def name(self, cls, member, converted=None):
        types = memberize.declarations.Types()
        converted = self.LIBS if converted is None else converted
        scope = memberize.NameScope(self.MEMBERS, {"igMediaFile": ["igFile"]}, self.TYPEDEFS, types)
        d = [m for m in memberize.declared_members(cls, self.MEMBERS[cls], None, types) if m.name == member][0]
        conv = memberize.Conversion("C", "Gap::%s::%s" % (self.LIBS[cls], cls), member, "func", False, False, False,
                                    d.ret, tuple(d.params), None)
        conv.raw_params = memberize.declared_raw_params(self.MEMBERS[cls], member, conv.params, False, None, types, cls)
        return memberize.compiler_name(conv, converted, scope)

    def test_a_nested_enum_is_named_by_its_owner(self):
        self.assertEqual(self.name("igFile", "setOpenMode"),
                         "setOpenMode__Q33Gap4Core6igFileFQ43Gap4Core6igFile8OpenMode")
        # found in a base class, or qualified by the declaration
        self.assertEqual(self.name("igMediaFile", "open"), "open__Q33Gap4Core11igMediaFileFQ43Gap4Core6igFile8OpenMode")
        self.assertEqual(self.name("igMedia", "open"),
                         "open__Q33Gap4Core7igMediaFi11igStringRefQ43Gap4Core6igFile8OpenMode")

    def test_a_function_typedef_is_its_type(self):
        self.assertEqual(self.name("igFile", "freadAsynchronous"), "freadAsynchronous__Q33Gap4Core6igFileFPviPFii_vi")
        self.assertEqual(self.name("igExternalDirEntry", "resolve"),
                         "resolve__Q33Gap4Core18igExternalDirEntryFPFPQ33Gap4Core18igExternalDirEntry_b")

    def test_a_converted_parameter_class_is_its_gap_class(self):
        self.assertEqual(self.name("igImage", "platformLoad"), "platformLoad__Q33Gap3Gfx7igImageFPQ33Gap4Core6igFile")
        flat = {k: v for k, v in self.LIBS.items() if k != "igFile"}
        self.assertEqual(self.name("igImage", "platformLoad", flat), "platformLoad__Q33Gap3Gfx7igImageFP6igFile")


if __name__ == "__main__":
    unittest.main()
