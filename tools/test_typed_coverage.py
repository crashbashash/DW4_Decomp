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

    def measure(self, source, converted, reflection=REFLECTION):
        with tempfile.TemporaryDirectory() as tree:
            files = dict(HEADERS, **{"src/gui/r.cpp": source})
            files["data/reflection.json"] = json.dumps(reflection)
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
                         {"igMetaObject": 1, "igRenderer": 6, "igVisualContext": 9, "igObject": 1})
        self.assertGreaterEqual(member["recovered"], flat["recovered"])

    def test_where_the_member_form_counts_them(self):
        stats = self.measure(MEMBER, True)
        per = {name: fc["recovered"] for (_path, name), fc in stats["per_function"].items()}
        # isValid() reads _validity; two bare reads, operator= (it reads the member's word and stores it, and makes
        # five reference-count accesses) and a read through the typed member; the constructor's bare field; the
        # implicit destructor tests the member's address, reads its word and releases it (three accesses)
        self.assertEqual(per, {"igRenderer::getClassTypeSafe": 1, "Gap::Gui::igRenderer::setVisualContext": 10,
                               "Gap::Core::igObject::igObject": 1, "igRenderer::~igRenderer": 5})

    def test_a_destructor_the_source_defines_is_not_counted_twice(self):
        stats = self.measure(MEMBER + "Gap::Gui::igRenderer::~igRenderer() {\n}\n", True)
        self.assertNotIn(("(implicit)", "igRenderer::~igRenderer"), stats["per_function"])

    def test_a_constructor_reads_through_a_reference_and_stores_the_vtable(self):
        # the C form spelled the vtable store and read its source through a pointer; the constructor's store is
        # the compiler's, and it reads its source through a reference
        reflection = json.loads(json.dumps(REFLECTION))
        reflection["classes"]["0x1"]["fields"].insert(0, {"offset": 0, "name": "_vtable",
                                                          "type": "igObjectRefMetaField"})
        flat = self.measure("igObject *igObject_CopyConstructHeader(igObject *self, igObject *source) {\n"
                            "    self->_vtable = (int)&g_igObject_vtable[0];\n"
                            "    self->_refCount = source->_refCount;\n    return self;\n}\n", False, reflection)
        member = self.measure("Gap::Core::igObject::igObject(const igObject &other) {\n"
                              "    _refCount = other._refCount;\n    other.x = 0;\n}\n"
                              "int f(igObject &o, int &n) {\n    return o._refCount + n;\n}\n", True, reflection)
        self.assertEqual(flat["by_class"]["igObject"], 3)
        self.assertEqual(member["by_class"]["igObject"], 4)
        per = {name: fc["recovered"] for (_path, name), fc in member["per_function"].items()}
        self.assertEqual(per["Gap::Core::igObject::igObject"], 3)
        self.assertEqual(per["f"], 1)
        self.assertEqual(member["other_members"], 1)          # `other.x`: no field of the class

    def test_cxx_view_keeps_the_cplusplus_arm(self):
        text = "#ifdef __cplusplus\nstruct A : public B {\n#else\nstruct A {\n#endif\n  int x;\n};\n"
        self.assertEqual(tc.cxx_view(text).split("\n"), ["", "struct A : public B {", "", "", "", "  int x;", "};", ""])


def measure_tree(files):
    """tc.measure over a scratch tree holding `files` ({relative path: text})."""
    with tempfile.TemporaryDirectory() as tree:
        for rel, text in files.items():
            os.makedirs(os.path.dirname(os.path.join(tree, rel)), exist_ok=True)
            with open(os.path.join(tree, rel), "w") as fh:
                fh.write(text)
        return tc.measure(os.path.join(tree, "data", "reflection.json"), os.path.join(tree, "src"))


def per_function(stats):
    return {name: fc["recovered"] for (_path, name), fc in stats["per_function"].items() if fc["recovered"]}


PROBE = {
    "data/reflection.json": json.dumps({"classes": {
        "0x1": {"class": "igBase", "fields": [{"offset": 8, "name": "_base", "type": "igIntMetaField"}]},
        "0x2": {"class": "igProbe", "fields": [
            {"offset": 12, "name": "_n", "type": "igIntMetaField"},
            {"offset": 16, "name": "_pos", "type": "igVec3fMetaField"},
            {"offset": 28, "name": "_arr", "type": "igIntArrayMetaField"}]}}}),
    "data/class-hierarchy.tsv": "igProbe\tigBase\n",
    "include/dw4/probe.h": (
        "struct igVec3f {\n    float vec[3];\n"
        "    void set(const float *v) { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; }\n"
        "    igVec3f &operator+=(const igVec3f &o) { vec[0] += o.vec[0]; return *this; }\n};\n"
        "class igBase {\npublic:\n    int _base;\n};\n"
        "class igProbe : public igBase {\npublic:\n    int _n;\n    igVec3f _pos;\n    int _arr[4];\n"
        "    int get(igVec3f *v, igProbe *a);\n    int shadow(int _n);\n};\n"),
}
# the same reads written as a free function, as a member function in a namespace block, and in the class body:
# a whole-vector operation (`_pos.set(...)`, `a->_pos += *v`) is one access, an inherited field (`_base`) is the
# class's, and a parameter or local of a field's name hides it
PROBE_FREE = (
    "int igProbe_Get(igProbe *self, igVec3f *v, igProbe *a) {\n    self->_pos.set(v->vec);\n    a->_pos += *v;\n"
    "    return self->_n + self->_base + self->_pos.vec[1] + self->_arr[2];\n}\n"
    "int igProbe_Shadow(igProbe *self, int _n) {\n    int _base = 1;\n    return _n + _base + self->_arr[0];\n}\n")
PROBE_GET = ("get(igVec3f *v, igProbe *a) {\n    _pos.set(v->vec);\n    a->_pos += *v;\n"
             "    return _n + _base + _pos.vec[1] + this->_arr[2];\n}\n")
PROBE_SHADOW = "shadow(int _n) {\n    int _base = 1;\n    return _n + _base + _arr[0];\n}\n"
PROBE_MEMBER = ("namespace Gap {\nnamespace Core {\n\nint igProbe::" + PROBE_GET + "\nint igProbe::" + PROBE_SHADOW +
                "\n}\n}\n")
PROBE_INLINE = ("namespace Gap {\nnamespace Core {\nclass igProbe : public igBase {\npublic:\n    int " +
                PROBE_GET.replace("\n", "\n    ") + "int " + PROBE_SHADOW.replace("\n", "\n    ") + "};\n}\n}\n")


class ImplicitThis(unittest.TestCase):
    """A member function of a class reads the class's (and its bases') fields through the implicit `this` as the
    free function did through its receiver pointer."""

    def measure(self, source):
        return measure_tree(dict(PROBE, **{"src/probe.cpp": source}))

    def test_a_free_function_and_its_member_forms_count_the_same(self):
        free, member, inline = self.measure(PROBE_FREE), self.measure(PROBE_MEMBER), self.measure(PROBE_INLINE)
        self.assertEqual(per_function(free), {"igProbe_Get": 6, "igProbe_Shadow": 1})
        self.assertEqual(per_function(member), {"igProbe::get": 6, "igProbe::shadow": 1})
        self.assertEqual(per_function(inline), {"igProbe::get": 6, "igProbe::shadow": 1})
        self.assertEqual(free["by_class"], {"igProbe": 7})
        self.assertEqual(member["by_class"], free["by_class"])
        self.assertEqual(inline["by_class"], free["by_class"])

    def test_a_whole_vector_operation_is_one_access(self):
        stats = self.measure("void igProbe::move(igVec3f *v, igProbe *a) {\n    a->_pos += *v;\n"
                             "    _pos.set(v->vec);\n    _pos = *v;\n}\n")
        self.assertEqual(per_function(stats), {"igProbe::move": 3})

    def test_in_class_bodies_are_split_from_the_function_before(self):
        text = "int f(void) {\n    return 0;\n}\nstruct S {\n    int g() { return 1; }\n    S() : x(0) {}\n    int x;\n};\n"
        self.assertEqual([(n, a) for n, a, _s, _e in tc.split_functions(text)],
                         [("f", "void"), ("S::g", ""), ("S::S", "")])


POOL = {
    "data/reflection.json": json.dumps({"classes": {
        "0x1": {"class": "igObject", "fields": [{"offset": 0, "name": "_vtable", "type": "igObjectRefMetaField"},
                                                {"offset": 4, "name": "_refCount", "type": "igUnsignedIntMetaField"}]},
        "0x2": {"class": "igPool", "fields": [{"offset": 8, "name": "_size", "type": "igIntMetaField"},
                                              {"offset": 12, "name": "_poolName", "type": "igStringMetaField"}]}}}),
    "data/class-hierarchy.tsv": "igPool\tigObject\n",
    "config/converted-classes.tsv": "igObject\tCore\nigPool\tCore\n",
    "config/SLUS-20836/compiler-names.tsv": "__dt__Q33Gap4Core6igPoolFv\t0x00100000\tigPool_Destroy\n",
    "include/dw4/pool.h": (
        "static inline void releaseString(const char *s) {\n    if (s != 0) StringChunk_Release(s);\n}\n"
        "struct igStringRef {\n    char *p;\n    igStringRef() : p(0) {}\n    ~igStringRef() { releaseString(p); }\n"
        "    igStringRef &operator=(const char *chars) {\n        char *interned = (char *)StringPool_Intern(chars);\n"
        "        releaseString(p);\n        p = interned;\n        return *this;\n    }\n};\n"
        "namespace Gap { namespace Core {\nclass igPool : public Gap::Core::igObject {\npublic:\n    int _size;\n"
        "    igStringRef _poolName;\n    igPool();\n    void setPool(const char *name);\n};\n}}\n"),
}
# the C form spelled what the compiler writes for a member with a destructor (igStringRef): the constructor's clear,
# the assignment's release of the old string, the destructor's test of the member's address and its release
POOL_FREE = (
    "igPool *igPool_Construct(igPool *self) {\n    self->_vtable = (int)g_igPool_vtable;\n"
    "    self->_poolName = 0;\n    self->_size = 4;\n    return self;\n}\n"
    "void igPool_SetPool(igPool *self, const char *name) {\n    char *previous = (char *)self->_poolName;\n"
    "    release(previous);\n    self->_poolName = (int)intern(name);\n}\n"
    "igPool *igPool_Destroy(igPool *self, short flags) {\n    if (self != 0) {\n"
    "        self->_vtable = (int)g_igPool_vtable;\n        if (&self->_poolName != 0) {\n"
    "            char *p = (char *)self->_poolName;\n            release(p);\n        }\n    }\n    return self;\n}\n")
POOL_MEMBER = ("namespace Gap {\nnamespace Core {\n\nigPool::igPool()\n{\n    _size = 4;\n}\n\n"
               "void igPool::setPool(const char *name)\n{\n    _poolName = name;\n}\n\n}\n}\n")


class Holders(unittest.TestCase):
    """A member whose class has a destructor is constructed, assigned and destroyed by that class's inline members;
    what they do to its word counts as the C form's accesses of the field."""

    def measure(self, source, converted):
        files = dict(POOL, **{"src/pool.cpp": source})
        if not converted:
            del files["config/converted-classes.tsv"], files["config/SLUS-20836/compiler-names.tsv"]
        return measure_tree(files)

    def test_the_member_form_counts_what_the_free_form_counted(self):
        free, member = self.measure(POOL_FREE, False), self.measure(POOL_MEMBER, True)
        self.assertEqual(per_function(free), {"igPool_Construct": 3, "igPool_SetPool": 2, "igPool_Destroy": 3})
        # the constructor: its vtable store, the default-constructed _poolName, `_size`; setPool: operator= reads
        # the old string and stores the new; the implicit destructor: the vtable, _poolName's address and its word
        self.assertEqual(per_function(member), {"igPool::igPool": 3, "igPool::setPool": 2, "igPool::~igPool": 3})
        self.assertEqual(member["by_class"], free["by_class"])

    def test_a_member_initialiser_constructs_the_member_once(self):
        stats = self.measure("igPool::igPool(const char *name) : _poolName(name) {\n}\n", True)
        self.assertEqual(per_function(stats)["igPool::igPool"], 2)

    def test_a_destructor_the_source_defines_adds_the_compilers_part(self):
        stats = self.measure(POOL_MEMBER + "Gap::Core::igPool::~igPool() {\n    _size = 0;\n}\n", True)
        self.assertEqual(per_function(stats)["Gap::Core::igPool::~igPool"], 4)
        self.assertNotIn(("(implicit)", "igPool::~igPool"), stats["per_function"])


class ClassMembers(unittest.TestCase):
    def test_an_initialiser_list_is_not_an_access_label(self):
        body = "\n    char *p;\n    H() : p(0) {}\npublic:\n    ~H() { release(p); }\n"
        self.assertEqual([i[:2] for i in tc.class_members(body)], [("data", "char *"), ("method", "H"), ("method", "~H")])

    def test_initializers(self):
        self.assertEqual(tc.initializers(" Base(a, b), p((T *)o.p), n(0) "),
                         [("Base", "a, b"), ("p", "(T *)o.p"), ("n", "0")])


if __name__ == "__main__":
    unittest.main()
