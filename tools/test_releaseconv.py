#!/usr/bin/env python3
"""Tests for tools/releaseconv.py: the open reference-count idioms written as the kit's ref()/release()."""
import os
import sys
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import releaseconv as rc  # noqa: E402


class ReleaseTest(unittest.TestCase):
    def test_a_guarded_release_becomes_the_static_release(self):
        text = ("void f(igNode *node) {\n"
                "    if (node != 0) {\n"
                "        node->_refCount = node->_refCount - 1;\n"
                "        if ((node->_refCount & 0x7FFFFF) == 0) {\n"
                "            igObject_Destroy(node);\n"
                "        }\n"
                "    }\n"
                "}\n")
        new, sites = rc.convert(text)
        self.assertEqual(new, "void f(igNode *node) {\n    igObject::release(node);\n}\n")
        self.assertEqual([(s.kind, s.form, s.line, s.new_lines) for s in sites],
                         [("release", "static", 3, (2, 2))])

    def test_the_decompiled_spellings_are_one_release(self):
        for dec, test in (
                ("p->_refCount = (int)p->_refCount - 1;",
                 "if (((unsigned long long)((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {"),
                ("p->_refCount = (int)((int) (p->_refCount - 1));",
                 "if (((unsigned long long)(long long)p->_refCount & 0x7fffffULL) == 0) {"),
                ("--p->_refCount;", "if ((p->_refCount & 0x7fffff) == 0) {")):
            text = "    %s\n    %s\n        igObject_Destroy((igObject *)p);\n    }\n" % (dec, test)
            new, _sites = rc.convert(text)
            self.assertEqual(new, "    p->release();\n", dec)

    def test_an_unbraced_test_and_a_guard_holding_more_keep_the_guard(self):
        text = ("    if (p) {\n"
                "        --p->_refCount;\n"
                "        if ((p->_refCount & 0x7fffff) == 0) igObject_Destroy(p);\n"
                "        p = 0;\n"
                "    }\n")
        new, sites = rc.convert(text)
        self.assertEqual(new, "    if (p) {\n        p->release();\n        p = 0;\n    }\n")
        self.assertEqual(sites[0].form, "member")

    def test_member_and_keep_overrides(self):
        text = ("    if (a->_b != 0) {\n"
                "        a->_b->_refCount = a->_b->_refCount - 1;\n"
                "        if ((a->_b->_refCount & 0x7FFFFF) == 0) igObject_Destroy(a->_b);\n"
                "    }\n"
                "    q->_refCount = q->_refCount + 1;\n")
        new, _sites = rc.convert(text, member={2})
        self.assertEqual(new, "    if (a->_b != 0) {\n        a->_b->release();\n    }\n    q->ref();\n")
        new, sites = rc.convert(text, keep={2, 5})
        self.assertEqual(new, text)
        self.assertEqual([s.form for s in sites], ["keep", "keep"])

    def test_a_test_on_another_object_or_word_is_left(self):
        text = ("    p->_refCount = p->_refCount - 1;\n"
                "    if ((q->_refCount & 0x7FFFFF) == 0) igObject_Destroy(q);\n"
                "    v->f4 = v->f4 - 1;\n"
                "    if ((v->f4 & 0x7FFFFF) == 0) igObject_Destroy((igObject *)v);\n"
                "    r->_refCount = r->_refCount - 2;\n")
        new, sites = rc.convert(text)
        self.assertEqual(new, text)
        self.assertEqual(sites, [])


class RefTest(unittest.TestCase):
    def test_increments(self):
        text = ("    if (p != 0) {\n"
                "        p->_refCount = p->_refCount + 1;\n"
                "    }\n"
                "    if (q != 0)\n"
                "        ++q->_refCount;\n"
                "    (*pp)->_refCount++;\n")
        new, sites = rc.convert(text)
        self.assertEqual(new, "    igObject::ref(p);\n    igObject::ref(q);\n    (*pp)->ref();\n")
        self.assertEqual([s.form for s in sites], ["static", "static", "member"])

    def test_only_a_postfix_receiver_is_the_object(self):
        text = "    ((igNode *)p)->_refCount = ((igNode *)p)->_refCount + 1;\n"
        self.assertEqual(rc.convert(text)[0], "    ((igNode *)p)->ref();\n")
        # `*` and a cast bind looser than `->`: these read another word
        for text in ("    *(igNode **)slot->_refCount += 1;\n", "    (igNode *)p->_refCount += 1;\n"):
            self.assertEqual(rc.convert(text)[0], text)

    def test_a_macro_body_is_left(self):
        text = ("#define ADD(o) do { if (o != 0) { o->_refCount = o->_refCount + 1; } } while (0)\n"
                "#define DROP(o) \\\n    do { \\\n        --o->_refCount; \\\n"
                "        if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); \\\n    } while (0)\n")
        self.assertEqual(rc.convert(text)[0], text)


class HelperTest(unittest.TestCase):
    def test_a_helper_call_becomes_the_static_release(self):
        text = ("    igRelease((igObject *)self->_vc);\n"
                "    if (old != 0) igRelease(old);\n")
        new, sites = rc.convert(text)
        self.assertEqual(new, "    igObject::release((igObject *)self->_vc);\n"
                              "    if (old != 0) igObject::release(old);\n")
        self.assertEqual([(s.kind, s.form, s.line, s.new_lines) for s in sites],
                         [("helper", "static", 1, (1, 1)), ("helper", "static", 2, (2, 2))])

    def test_a_view_and_a_kept_call(self):
        text = "    igRelease(entry);\n    igRelease(list);\n    igRelease(name);\n"
        new, sites = rc.convert(text, keep={3}, view={1: "igVirtualObject"})
        self.assertEqual(new, "    igVirtualObject::release(entry);\n    igObject::release(list);\n"
                              "    igRelease(name);\n")
        self.assertEqual([s.form for s in sites], ["view", "static", "keep"])

    def test_definitions_macros_and_other_names_are_left(self):
        text = ("static inline void igRelease(igObject *o) {\n}\n"
                "template <class T> static inline void igRelease(igTDataList<T> *o) {\n}\n"
                "#define DROP(o) igRelease(o)\n"
                "    p->igRelease(o);\n    myigRelease(o);\n")
        self.assertEqual(rc.convert(text), (text, []))

    def test_sites_keep_text_order_with_open_releases(self):
        text = ("    igRelease(a);\n"
                "    if (b != 0) {\n        b->_refCount = b->_refCount + 1;\n    }\n")
        _new, sites = rc.convert(text)
        self.assertEqual([(s.kind, s.line) for s in sites], [("helper", 1), ("ref", 3)])


if __name__ == "__main__":
    unittest.main()
