#!/usr/bin/env python3
"""What tools/typed_coverage.py attributes to a class."""
import json
import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import typed_coverage as tc  # noqa: E402


class TemplateArguments(unittest.TestCase):
    def test_a_parameter_resolves_to_what_the_file_instantiates(self):
        text = "template <class T> struct Holder { T *p; };\nHolder<igProbe> held(0);\n"
        self.assertEqual(tc.template_arguments(text), {"T": ["igProbe"]})

    def test_struct_keyword_and_pointer_are_ignored(self):
        text = "template <class T> struct Holder { T *p; };\nHolder<struct igProbe *> held(0);\n"
        self.assertEqual(tc.template_arguments(text), {"T": ["igProbe"]})

    def test_the_template_itself_is_not_an_argument(self):
        text = "template <class T> struct Holder { Holder(const Holder<T> &o); T *p; };\n"
        self.assertEqual(tc.template_arguments(text), {"T": []})

    def test_a_file_without_templates_has_none(self):
        self.assertEqual(tc.template_arguments("struct S { int a; };\n"), {})


class MemberFunctions(unittest.TestCase):
    def test_a_member_head_is_a_function_of_its_class(self):
        text = ("int igFoo_Get(igFoo *self) {\n    return self->_n;\n}\n"
                "void igRenderer::setVisualContext(igVisualContext *context) {\n    _visualContext = context;\n}\n"
                "igMetaObject *Gap::Gui::igRenderer::getMeta() const {\n    return _Meta;\n}\n")
        names = [n for n, _args, _s, _e in tc.split_functions(text)]
        self.assertEqual(names, ["igFoo_Get", "igRenderer::setVisualContext", "Gap::Gui::igRenderer::getMeta"])
        self.assertEqual([tc.class_of(n) for n in names], ["igFoo", "igRenderer", "igRenderer"])

    def test_locals_and_parameters_hide_fields(self):
        body = "{\n    int _count = 1;\n    igVisualContext *old;\n    return _count;\n}\n"
        self.assertEqual(tc.local_names("igVisualContext *context, int n", body), {"context", "n", "_count", "old"})
        self.assertNotIn("_count", tc.local_names("void", "{\n    return _count;\n}\n"))

    def test_bare_field_reads_in_a_member_are_recovered(self):
        with tempfile.TemporaryDirectory() as tree:
            os.makedirs(os.path.join(tree, "data"))
            os.makedirs(os.path.join(tree, "src", "gui"))
            with open(os.path.join(tree, "data", "reflection.json"), "w") as fh:
                json.dump({"classes": {"0x1": {"class": "igRenderer", "fields": [
                    {"offset": 8, "name": "_visualContext", "type": "igObjectRefMetaField"}]}}}, fh)
            with open(os.path.join(tree, "src", "gui", "r.cpp"), "w") as fh:
                fh.write("void igRenderer::setVisualContext(igVisualContext *context) {\n"
                         "    if (_visualContext != context)\n        _visualContext = context;\n"
                         "    other->_visualContext = 0;\n}\n"
                         "void igRenderer::hide(int _visualContext) {\n    _visualContext = 0;\n"
                         "    this->_visualContext = 0;\n}\n")
            stats = tc.measure(os.path.join(tree, "data", "reflection.json"), os.path.join(tree, "src"))
        # two bare reads, `this->_visualContext` and (as for any function of the class) a pointer of unread type
        # reaching a field of the class's name; the parameter of that name hides the field
        self.assertEqual(stats["recovered"], 4)
        self.assertEqual(stats["by_class"], {"igRenderer": 4})


REFLECTION = {"classes": {
    "0x1": {"class": "igObject", "fields": [{"offset": 4, "name": "_refCount", "type": "igUnsignedIntMetaField"}]},
    "0x2": {"class": "igMetaObject", "fields": [{"offset": 36, "name": "_validity", "type": "igIntMetaField"}]},
    "0x3": {"class": "igVisualContext", "fields": [{"offset": 8, "name": "_mode", "type": "igIntMetaField"}]},
    "0x4": {"class": "igRenderer", "fields": [
        {"offset": 8, "name": "_visualContext", "type": "igObjectRefMetaField"}]}}}
HEADERS = {
    "include/dw4/core/igSmartPointer.h": (
        "static inline void igRelease(igObject *o) {\n    if (o != 0) {\n        o->_refCount = o->_refCount - 1;\n"
        "        if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);\n    }\n}\n"
        "template <class T> struct igSmartPointer {\n    T *p;\n    igSmartPointer() : p(0) {}\n"
        "    ~igSmartPointer() { igRelease(p); }\n    operator T *() const { return p; }\n"
        "    igSmartPointer &operator=(T *next) {\n        T *o;\n"
        "        if (next != 0) next->_refCount = next->_refCount + 1;\n        o = p;\n        if (o != 0) {\n"
        "            o->_refCount = o->_refCount - 1;\n"
        "            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);\n        }\n"
        "        p = next;\n        return *this;\n    }\n};\n"),
    "include/dw4/support/reflected.h": (
        "#define IG_OBJECT_COMMON(C) \\\n    protected: static igMetaObject *_Meta; \\\n"
        "    public: static igMetaObject *getClassTypeSafe();\n"
        "typedef struct igMetaObject {\n    int _validity;\n#ifdef __cplusplus\n"
        "    bool isValid() const { return (_validity & 4) ? true : false; }\n#endif\n} igMetaObject;\n"
        "namespace Gap { namespace Gui {\nclass igRenderer : public Gap::Core::igObject {\npublic:\n"
        "    igSmartPointer<igVisualContext> _visualContext;\n    IG_OBJECT_COMMON(igRenderer)\n"
        "    void setVisualContext(igVisualContext *context);\n};\n}}\n"),
}
FLAT = (
    "igMetaObject *igRenderer_GetMetaObject(void) {\n    igMetaObject *g = g_igRenderer_metaObject;\n"
    "    if (!g || ((g->_validity & 4) != 0) == false)\n        igRenderer_EnsureRegistered();\n"
    "    return g_igRenderer_metaObject;\n}\n"
    "void igRenderer_SetVisualContext(igRenderer *self, igVisualContext *context) {\n"
    "    igVisualContext *old = self->_visualContext;\n    if (old != context) {\n"
    "        if (context != 0) context->_refCount = context->_refCount + 1;\n"
    "        if (old != 0) {\n            old->_refCount = old->_refCount - 1;\n"
    "            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);\n        }\n"
    "        self->_visualContext = context;\n        context->_mode = 0;\n    }\n}\n"
    "igRenderer *igRenderer_Destroy(igRenderer *self, short deleteFlag) {\n    igVisualContext *context;\n"
    "    if (self != 0) {\n        context = self->_visualContext;\n        if (context != 0) {\n"
    "            context->_refCount = context->_refCount - 1;\n"
    "            if ((context->_refCount & 0x7FFFFF) == 0) igObject_Destroy(context);\n        }\n    }\n"
    "    return self;\n}\n"
    "igObject *igObject_InitHeader(igObject *p) {\n    p->_refCount = 1;\n    return p;\n}\n")
MEMBER = (
    "namespace Gap {\nnamespace Gui {\n\nigMetaObject *igRenderer::getClassTypeSafe()\n{\n"
    "    if ((_Meta == 0) || !_Meta->isValid())\n        arkRegister();\n    return _Meta;\n}\n\n}\n}\n"
    "void Gap::Gui::igRenderer::setVisualContext(igVisualContext *context)\n{\n"
    "    if (_visualContext != context) {\n        _visualContext = context;\n"
    "        _visualContext->_mode = 0;\n    }\n}\n"
    "Gap::Core::igObject::igObject() {\n    _refCount = 1;\n}\n")


class Conversion(unittest.TestCase):
    """A class's functions written as its members count the accesses their free-function form counted: through
    inline members, a smart-pointer member's operators, typed members, constructors and implicit destructors."""

    def measure(self, source, converted):
        with tempfile.TemporaryDirectory() as tree:
            files = dict(HEADERS, **{"src/gui/r.cpp": source})
            files["data/reflection.json"] = json.dumps(REFLECTION)
            files["data/class-hierarchy.tsv"] = ("igMetaObject\tigObject\nigVisualContext\tigObject\n"
                                                 "igRenderer\tigObject\n")
            if converted:
                files["config/converted-classes.tsv"] = "igObject\tCore\nigRenderer\tGui\n"
                files["config/SLUS-20836/compiler-names.tsv"] = (
                    "__dt__Q33Gap3Gui10igRendererFv\t0x00230f70\tigRenderer_Destroy\n")
            for rel, text in files.items():
                os.makedirs(os.path.dirname(os.path.join(tree, rel)), exist_ok=True)
                with open(os.path.join(tree, rel), "w") as fh:
                    fh.write(text)
            return tc.measure(os.path.join(tree, "data", "reflection.json"), os.path.join(tree, "src"))

    def test_the_member_form_counts_what_the_free_form_counted(self):
        flat, member = self.measure(FLAT, False), self.measure(MEMBER, True)
        self.assertEqual(flat["by_class"], {"igMetaObject": 1, "igRenderer": 3, "igVisualContext": 9, "igObject": 1})
        self.assertEqual(member["by_class"],
                         {"igMetaObject": 1, "igRenderer": 4, "igVisualContext": 9, "igObject": 1})
        self.assertGreaterEqual(member["recovered"], flat["recovered"])

    def test_where_the_member_form_counts_them(self):
        stats = self.measure(MEMBER, True)
        per = {name: fc["recovered"] for (_path, name), fc in stats["per_function"].items()}
        # isValid() reads _validity; three bare reads, operator= (five reference-count accesses) and a read through
        # the typed member; the constructor's bare field; the implicit destructor reads and releases the member
        self.assertEqual(per, {"igRenderer::getClassTypeSafe": 1, "Gap::Gui::igRenderer::setVisualContext": 9,
                               "Gap::Core::igObject::igObject": 1, "igRenderer::~igRenderer": 4})

    def test_a_destructor_the_source_defines_is_not_counted_twice(self):
        stats = self.measure(MEMBER + "Gap::Gui::igRenderer::~igRenderer() {\n}\n", True)
        self.assertNotIn(("(implicit)", "igRenderer::~igRenderer"), stats["per_function"])

    def test_cxx_view_keeps_the_cplusplus_arm(self):
        text = "#ifdef __cplusplus\nstruct A : public B {\n#else\nstruct A {\n#endif\n  int x;\n};\n"
        self.assertEqual(tc.cxx_view(text).split("\n"), ["", "struct A : public B {", "", "", "", "  int x;", "};", ""])


if __name__ == "__main__":
    unittest.main()
