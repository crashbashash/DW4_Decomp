#!/usr/bin/env python3
"""Tests of tools/cxx_sweep.py: the grammar layer, each move, the honesty filter and the search.

No compiler is needed: the search runs against a fake scorer.
"""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cxx_sweep as cs


def types_of(text):
    return cs.Types(*cs.collect_types(text))


def ctx_of(text, name, cxx=False):
    return cs.Ctx(text, name, types_of(text), cxx)


def moves_of(text, name, move, cxx=False):
    return list(cs.MOVES[move](ctx_of(text, name, cxx)))


def body(text, name, cxx=False):
    """The function's body as normalised tokens."""
    ctx = ctx_of(text, name, cxx)
    return cs.norm(ctx.src.span(ctx.fn.lb + 1, ctx.fn.rb))


def bodies(results, name, cxx=False):
    return {body(t, name, cxx) for _, t in results}


C_SAMPLE = """typedef struct Node { int n; struct Node *next; int *d; } Node;
extern int g;
int f(Node *p, int k) {
    int i, s = 0;
    Node *q;
    q = p->next;
    for (i = 0; i < q->n; i++) {
        int t;
        t = q->d[i];
        s += t;
    }
    if (s == 0) return -1;
    return s;
}
"""

CXX_SAMPLE = """namespace Gap { namespace Core {
template <class T> struct Holder { T *p; Holder(T *q) : p(q) {} ~Holder(); };
class igObject { public: int f8; igObject *next; virtual int count() const; };
class igList : public igObject { public: int _count; igObject **_data; };
} }
using namespace Gap::Core;
struct Scope { Scope(); ~Scope(); };
extern "C" int Gap__Core__igList__find(igList *self, igObject *&out, int key) {
    Scope guard;
    int i = 0;
    Holder<igObject> h(self);
    igObject *o;
    while (i < self->_count) {
        o = static_cast<igObject *>(self->_data[i]);
        if (o->f8 == key) { out = o; return i; }
        i++;
    }
    return ::Gap::Core::igList::npos + (int)reinterpret_cast<long>(h.p);
}
int igList::size() const { return _count; }
"""


class GrammarTest(unittest.TestCase):
    def test_c_declarations_and_statements(self):
        ctx = ctx_of(C_SAMPLE, "f")
        fn = ctx.fn
        self.assertEqual(set(fn.locals), {"i", "s", "q", "t"})
        self.assertEqual(fn.param_names, ["p", "k"])
        self.assertEqual([n.kind for n in fn.body.items], ["decl", "decl", "expr", "for", "if", "return"])
        loop = fn.body.items[3]
        self.assertEqual(ctx.src.span(*loop.cond), "i < q->n")
        self.assertEqual([n.kind for n in loop.body.items], ["decl", "expr", "expr"])
        self.assertEqual(fn.local_type("q"), ("Node", 1))
        self.assertEqual(cs.infer(fn, ctx.types, cs.parse_expr(fn, *self.span_of(ctx, "q->d[i]"))), ("int", 0))

    def span_of(self, ctx, text):
        S = ctx.S
        want = cs.norm(text)
        for a in range(ctx.fn.lb, ctx.fn.rb):
            for b in range(a + 1, min(ctx.fn.rb, a + 12)):
                if cs.norm(ctx.src.span(a, b)) == want:
                    return a, b
        raise AssertionError(text)

    def test_cxx_function_with_classes_templates_and_references(self):
        ctx = ctx_of(CXX_SAMPLE, "Gap__Core__igList__find", cxx=True)
        fn = ctx.fn
        self.assertEqual(set(fn.locals), {"guard", "i", "h", "o"})
        self.assertEqual(fn.param_names, ["self", "out", "key"])
        self.assertEqual([n.kind for n in fn.body.items], ["decl", "decl", "decl", "decl", "while", "return"])
        self.assertEqual(fn.local_type("o"), ("igObject", 1))
        e = cs.parse_expr(fn, *fn.body.items[5].expr)
        self.assertIsNotNone(e)
        self.assertEqual(e.kind, "bin")
        # an inherited field is found through the base class
        self.assertEqual(ctx.types.field("igList", "f8"), ("int", 0))

    def test_qualified_member_definition(self):
        ctx = ctx_of(CXX_SAMPLE, "igList::size", cxx=True)
        self.assertEqual([n.kind for n in ctx.fn.body.items], ["return"])

    def test_declaration_is_not_a_call(self):
        text = "int g(int);\nint f(int a) {\n    g(a);\n    return a;\n}\nint h() { return f(1); }\n"
        ctx = ctx_of(text, "f")
        self.assertEqual(ctx.src.span(ctx.fn.lb, ctx.fn.lb + 1), "{")
        self.assertEqual([n.kind for n in ctx.fn.body.items], ["expr", "return"])

    def test_effects(self):
        ctx = ctx_of(C_SAMPLE, "f")
        fx = ctx.fx
        q_assign = ctx.fn.body.items[2]
        R, W = fx.node(q_assign)
        self.assertEqual(W, {"q"})
        self.assertIn("MEM", R)
        self.assertIn("p", R)

    def test_unknown_type_pointer_declaration(self):
        text = "void f(void) {\n    Unknown *x;\n    x = 0;\n    g(x);\n}\n"
        ctx = ctx_of(text, "f", cxx=True)
        self.assertEqual(ctx.fn.body.items[0].kind, "decl")


class MoveTest(unittest.TestCase):
    def test_m1_reorder_declarations(self):
        text = "void f(void) {\n    int a;\n    int b;\n    int c;\n    a = 1; b = 2; c = 3; g(a, b, c);\n}\n"
        got = bodies(moves_of(text, "f", 1), "f")
        self.assertIn("int c ; int a ; int b ; a = 1 ; b = 2 ; c = 3 ; g ( a , b , c ) ;", got)
        self.assertEqual(len(got), 5)            # every other order of three

    def test_m1_keeps_dependent_initialisers(self):
        text = "void f(int *p) {\n    int a = *p;\n    int b = a + 1;\n    g(a, b);\n}\n"
        self.assertEqual(moves_of(text, "f", 1), [])

    def test_m2_split_and_merge_declarators(self):
        text = "void f(void) {\n    int a, b;\n    a = 1; b = 2; g(a, b);\n}\n"
        got = bodies(moves_of(text, "f", 2), "f")
        self.assertIn("int a ; int b ; a = 1 ; b = 2 ; g ( a , b ) ;", got)
        text2 = "void f(void) {\n    int a;\n    int b;\n    a = 1; b = 2; g(a, b);\n}\n"
        self.assertIn("int a , b ; a = 1 ; b = 2 ; g ( a , b ) ;", bodies(moves_of(text2, "f", 2), "f"))

    def test_m2_declaration_into_and_out_of_a_block(self):
        text = "void f(int n) {\n    int t;\n    if (n) {\n        t = n;\n        g(t);\n    }\n}\n"
        got = bodies(moves_of(text, "f", 2), "f")
        self.assertIn("if ( n ) { int t ; t = n ; g ( t ) ; }", got)
        text2 = "void f(int n) {\n    int a;\n    a = n;\n    if (n) {\n        int t;\n        t = n;\n        g(t, a);\n    }\n}\n"
        self.assertIn("int a ; int t ; a = n ; if ( n ) { t = n ; g ( t , a ) ; }", bodies(moves_of(text2, "f", 2), "f"))

    def test_m2_split_initialiser(self):
        text = "void f(int *p) {\n    int a = *p;\n    g(a);\n}\n"
        self.assertIn("int a ; a = * p ; g ( a ) ;", bodies(moves_of(text, "f", 2), "f"))

    def test_m3_swap_independent_only(self):
        text = "void f(int *p, int *q) {\n    int a;\n    int b;\n    a = p[0];\n    b = q[1];\n    g(a, b);\n}\n"
        got = bodies(moves_of(text, "f", 3), "f")
        self.assertEqual(got, {"int a ; int b ; b = q [ 1 ] ; a = p [ 0 ] ; g ( a , b ) ;"})
        dep = "void f(int *p) {\n    int a;\n    a = p[0];\n    p[1] = a;\n}\n"
        self.assertEqual(moves_of(dep, "f", 3), [])
        store = "void f(int *p, int *q) {\n    int a;\n    p[0] = 1;\n    a = q[0];\n    g(a);\n}\n"
        self.assertEqual(moves_of(store, "f", 3), [])        # a store and a load may alias

    def test_m4_assignment_into_loop_test_and_back(self):
        text = ("typedef struct A { int n; } A;\nvoid f(A **pp) {\n    A *a = *pp;\n    int i = 0;\n"
                "    while (i < a->n) {\n        i++;\n    }\n}\n")
        got = bodies(moves_of(text, "f", 4), "f")
        self.assertIn("A * a ; int i = 0 ; while ( i < ( a = * pp ) -> n ) { i ++ ; }", got)
        back = ("typedef struct A { int n; } A;\nvoid f(A **pp) {\n    A *a;\n    int i = 0;\n"
                "    while (i < (a = *pp)->n) {\n        i++;\n    }\n}\n")
        self.assertIn("A * a ; int i = 0 ; a = * pp ; while ( i < a -> n ) { i ++ ; }",
                      bodies(moves_of(back, "f", 4), "f"))

    def test_m4_refuses_a_value_the_loop_changes(self):
        text = "void f(int *p) {\n    int x;\n    x = *p;\n    while (x) {\n        x--;\n    }\n}\n"
        self.assertEqual([l for l, _ in moves_of(text, "f", 4) if "into-test" in l], [])

    def test_m5_reuse_a_dead_local(self):
        text = ("typedef struct L { int n; int *d; } L;\ntypedef struct T { L *f8; L *f12; } T;\n"
                "int h(int);\nint f(T *a, int r) {\n    L *l;\n    int v;\n    l = a->f12;\n    v = l->n;\n"
                "    h(a->f8->d[r]);\n    return v + a->f8->n;\n}\n")
        got = bodies(moves_of(text, "f", 5), "f")
        self.assertIn("L * l ; int v ; l = a -> f12 ; v = l -> n ; l = a -> f8 ; h ( l -> d [ r ] ) ; "
                      "return v + a -> f8 -> n ;", got)
        # `l` is still read after the call: not dead
        live = text.replace("return v + a->f8->n;", "return v + l->n + a->f8->n;")
        self.assertNotIn("l = a -> f8", " ".join(bodies(moves_of(live, "f", 5), "f")))

    def test_m6_introduce_and_inline_temporary(self):
        text = "typedef struct S { int n; } S;\nint g(int);\nint f(S *s) {\n    int r;\n    r = g(s->n);\n    return r;\n}\n"
        got = bodies(moves_of(text, "f", 6), "f")
        self.assertIn("int r ; int t0 ; t0 = s -> n ; r = g ( t0 ) ; return r ;", got)
        tmp = "typedef struct S { int n; } S;\nint g(int);\nint f(S *s) {\n    int t;\n    t = s->n;\n    return g(t);\n}\n"
        self.assertIn("return g ( s -> n ) ;", bodies(moves_of(tmp, "f", 6), "f"))

    def test_m7_split_and_merge(self):
        text = "int f(int b, int c, int d) {\n    int a;\n    a = b + c + d;\n    return a;\n}\n"
        got = bodies(moves_of(text, "f", 7), "f")
        self.assertIn("int a ; a = b + c ; a = a + d ; return a ;", got)
        self.assertIn("int a ; a = b ; a += c + d ; return a ;", got)
        merged = "int f(int b, int c, int d) {\n    int a;\n    a = b + c;\n    a = a * d;\n    return a;\n}\n"
        self.assertIn("int a ; a = ( b + c ) * d ; return a ;", bodies(moves_of(merged, "f", 7), "f"))

    def test_m8_operands(self):
        text = "int f(int x, int y) {\n    if (x == 0) return y + 1;\n    if (y != 0) return 2;\n    return !x;\n}\n"
        got = bodies(moves_of(text, "f", 8), "f")
        self.assertIn("if ( ! x ) return y + 1 ; if ( y != 0 ) return 2 ; return ! x ;", got)
        self.assertIn("if ( x == 0 ) return 1 + y ; if ( y != 0 ) return 2 ; return ! x ;", got)
        self.assertIn("if ( x == 0 ) return y + 1 ; if ( y ) return 2 ; return ! x ;", got)
        self.assertIn("if ( x == 0 ) return y + 1 ; if ( y != 0 ) return 2 ; return x == 0 ;", got)
        self.assertIn("if ( 0 == x ) return y + 1 ; if ( y != 0 ) return 2 ; return ! x ;", got)

    def test_m9_loops(self):
        text = "void f(int n) {\n    int i;\n    i = 0;\n    while (i < n) {\n        g(i);\n        i++;\n    }\n}\n"
        got = bodies(moves_of(text, "f", 9), "f")
        self.assertIn("int i ; for ( i = 0 ; i < n ; i ++ ) { g ( i ) ; }", got)
        self.assertIn("int i ; i = 0 ; if ( i < n ) do { g ( i ) ; i ++ ; } while ( i < n ) ;", got)
        loop = "void f(int n) {\n    int i;\n    for (i = 0; i < n; i++) {\n        g(i);\n    }\n    g(n);\n}\n"
        got = bodies(moves_of(loop, "f", 9), "f")
        self.assertIn("int i ; i = 0 ; while ( i < n ) { g ( i ) ; i ++ ; } g ( n ) ;", got)
        self.assertIn("int i ; i = 0 ; goto test0 ; loop0 : g ( i ) ; i ++ ; test0 : if ( i < n ) goto loop0 ; "
                      "g ( n ) ;", got)
        self.assertIn("int i ; i = 0 ; if ( i < n ) do { g ( i ) ; i ++ ; } while ( i < n ) ; g ( n ) ;", got)

    def test_m9_refuses_continue(self):
        text = "void f(int n) {\n    int i;\n    for (i = 0; i < n; i++) {\n        if (g(i)) continue;\n        g(n);\n    }\n}\n"
        labels = [l for l, _ in moves_of(text, "f", 9)]
        self.assertNotIn("9 for-to-while", labels)

    def test_m10_inline_helper(self):
        text = ("typedef struct O { int *name; } O;\nextern int D[4];\nvoid g(int *);\n"
                "void f(O *o) {\n    int *nm = o->name ? o->name : D;\n    g(nm);\n}\n")
        res = moves_of(text, "f", 10)
        self.assertEqual(len(res), 1)
        out = res[0][1]
        self.assertIn("static inline int *sweep_part0(O *o) {\n    return o->name ? o->name : D;\n}\n\nvoid f(O *o)", out)
        self.assertIn("int *nm = sweep_part0(o);", out)
        chain = "int f(int a, int b) {\n    int r;\n    if (a) r = b; else r = 0;\n    return r;\n}\n"
        out = [t for l, t in moves_of(chain, "f", 10) if "helper-if" in l][0]
        self.assertIn("static inline int sweep_part0(int a, int b) {\n    if (a) return b;\n    else return 0;\n}", out)
        self.assertIn("r = sweep_part0(a, b);", out)


class HonestyTest(unittest.TestCase):
    BASE = ("typedef struct S { int n; } S;\nint g(int);\nint f(S *s, int k) {\n    int a;\n"
            "    a = s->n;\n    if (k) a = g(a);\n    return a;\n}\n")

    def reasons(self, new_body, cxx=False):
        text = self.BASE
        types = types_of(text)
        facts = cs.function_facts(text, "f", types, cxx)
        start = text.index("{\n    int a;")
        cand = text[:start] + "{\n" + new_body + "\n}\n"
        return cs.honesty(facts, cand, "f", types, cxx)

    def test_original_passes(self):
        self.assertEqual(self.reasons("    int a;\n    a = s->n;\n    if (k) a = g(a);\n    return a;"), [])

    def test_refusals(self):
        cases = {
            "no_effect": "    int a;\n    a = s->n;\n    a;\n    if (k) a = g(a);\n    return a;",
            "empty_if": "    int a;\n    a = s->n;\n    if (k) {}\n    if (k) a = g(a);\n    return a;",
            "empty_block": "    int a;\n    a = s->n;\n    {}\n    if (k) a = g(a);\n    return a;",
            "unused_local": "    int a;\n    int b;\n    a = s->n;\n    if (k) a = g(a);\n    return a;",
            "address_of": "    int a;\n    a = s->n;\n    if (k) a = g(*&a);\n    return a;",
            "volatile": "    volatile int a;\n    a = s->n;\n    if (k) a = g(a);\n    return a;",
            "asm": "    int a;\n    a = s->n;\n    asm(\"nop\");\n    if (k) a = g(a);\n    return a;",
            "pun_cast": "    int a;\n    a = s->n;\n    if (k) a = g(*(int *)&a);\n    return a;",
            "do_while0": "    int a;\n    do { a = s->n; } while (0);\n    if (k) a = g(a);\n    return a;",
            "declaration after statement": "    int a;\n    a = s->n;\n    int b;\n    b = 0;\n    if (k) a = g(a + b);\n    return a;",
        }
        for want, body in cases.items():
            with self.subTest(want):
                why = self.reasons(body)
                self.assertTrue(any(w.startswith(want) for w in why), (want, why))

    def test_existing_shapes_stay_allowed(self):
        text = "int g(int *);\nint f(void) {\n    int a;\n    g(&a);\n    do { a--; } while (0);\n    return a;\n}\n"
        types = types_of(text)
        facts = cs.function_facts(text, "f", types, False)
        self.assertEqual(cs.honesty(facts, text, "f", types, False), [])

    def test_no_move_emits_a_refused_shape(self):
        for text, name, cxx in ((C_SAMPLE, "f", False), (CXX_SAMPLE, "Gap__Core__igList__find", True)):
            types = types_of(text)
            facts = cs.function_facts(text, name, types, cxx)
            for label, new in cs.generate(text, name, types, cxx):
                why = [w for w in cs.honesty(facts, new, name, types, cxx)
                       if not w.startswith(("unused_local", "declaration after"))]
                self.assertEqual(why, [], label)


class SearchTest(unittest.TestCase):
    TEXT = ("typedef struct A { int n; int *d; } A;\nint h(int);\nint f(A **pp, int k) {\n    A *a = *pp;\n"
            "    int i = 0;\n    int s;\n    s = 0;\n    while (i < a->n) {\n        s = s + a->d[i] + k;\n        i++;\n    }\n"
            "    return h(s);\n}\n")
    TARGET = "for ( i = 0 ; i < ( a = * pp ) -> n ; i ++ )"

    def fake_scorer(self):
        target = self.TARGET

        def score(path):
            with open(path) as fh:
                text = fh.read()
            key = cs.norm(text)
            if target in key:
                return 0, "fake 0"
            n = 10 - (3 if "( a = * pp )" in key else 0) - (3 if "for (" in key else 0)
            return n, "fake %d" % n
        return score

    def run_sweep(self, seed, tmp):
        types = types_of(self.TEXT)
        sw = cs.Sweep(self.TEXT, "f", types, False, self.fake_scorer(), tmp, ".c", jobs=2, beam=2, seed=seed,
                      budget=0, max_evals=400, keep=5, max_neighbors=40, patience=2)
        best = sw.run()
        return best, sw

    def test_search_reaches_the_known_optimum_deterministically(self):
        import tempfile
        with tempfile.TemporaryDirectory() as tmp:
            b1, s1 = self.run_sweep(7, tmp)
            b2, s2 = self.run_sweep(7, tmp)
        self.assertEqual(b1.score, 0)
        self.assertIn(self.TARGET, cs.norm(b1.text))
        self.assertEqual(b1.moves, b2.moves)
        self.assertEqual(s1.evals, s2.evals)

    def test_score_report(self):
        self.assertEqual(cs.score_report("MATCH  0x1 f 8B cat=match"), 0)
        self.assertIsNone(cs.score_report("compile failed: x"))
        rep = "DIFFER 0x1 f 140B\n   size: retail 140, ours 144\n   [  5] retail 1  ours 2\n   [  9] retail 1  ours 2"
        self.assertEqual(cs.score_report(rep), 2 + cs.SIZE_PENALTY + 1)
        grp = "DIFFER emitted object: 2 complete bodies\nDIFFER emitted 0x2 g 8B 0 relocs\n   !![32] retail 0c ours 0d"
        self.assertEqual(cs.score_report(grp), 1)


if __name__ == "__main__":
    unittest.main()
