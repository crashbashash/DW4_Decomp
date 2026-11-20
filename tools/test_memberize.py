#!/usr/bin/env python3
"""tools/memberize.py rewrites free `<Class>_<Method>` functions and data as members, on a small tree."""
import json
import os
import re
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


class Helpers(unittest.TestCase):
    MACROS = {"OBJ_BOOT": (("C",), "public: C(); virtual void __bootstrapDestruct(); "
                                   "protected: static struct Meta *_Meta; public: "
                                   "static inline struct Meta *getClassMeta() { return _Meta; }")}

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


if __name__ == "__main__":
    unittest.main()
