#!/usr/bin/env python3
"""cxx_sweep.py — search the source spellings of one C or C++ function for a byte match.

The decomp-permuter parses C only (pycparser), so a C++ unit, or a C file its parser refuses, gets no
permuter run. This tool works on tokens with a light grammar layer instead: it finds the function body,
its local declarations, statements, blocks and expressions, and tolerates C++ syntax (classes,
templates, `::`, references, casts) without parsing all of C++. It applies a fixed set of rewrites
inside the target function and scores each candidate with the repository's own verifier.

Score = the instruction words that differ from retail, plus a size penalty when the lengths differ;
0 is a match.

  function mode (default)  `tools/verify.py` `verify_one` with the config dir's tables: what
                           `tools/check.py --function VA --cand FILE --symbols ... --units ...`
                           reports. The unit profile decides compiler and flags.
  whole-file mode          (--whole-file) the whole file compiled under the unit profile through
                           tools/cc.py, as tools/whole_file_rows.py does; the score is the words of
                           that function's body that differ from retail, relocated fields masked.

Moves (inside the target function only; `--moves` selects them by number):
   1 reorder local declarations (one moved within its run, or every order of a run of up to 4)
   2 move a declaration into or out of a block scope; split or merge a multi-declarator line; split
     or merge an initialised declaration and its first assignment
   3 swap adjacent independent statements (no name or memory one writes is read or written by the other)
   4 move an assignment into a following loop test or condition, and the reverse
   5 reuse an existing dead local for a repeated subexpression before a statement
   6 introduce a temporary for a subexpression, and inline a single-use temporary back
   7 split `a = b op c op d` into two statements, and the reverse
   8 swap commutative operands; `x == 0` <-> `!x`, `x != 0` <-> `x` in a condition
   9 for / while / guarded do-while / goto-loop rewrites of a loop
  10 wrap an expression or an if/else chain that yields a value in a `static inline` helper,
     defined just above the function

Honesty: a candidate that adds a statement with no effect, an empty `if` or block, an unused local, an
address-of the original did not have, `volatile`, `asm`, a cast of an lvalue through a pointer
(`*(T *)&x`) or a `do { } while (0)` wrapper is rejected before it is compiled, and no move emits one.
In a `.c` file a candidate that puts a declaration after a statement in a block (C89) is refused too.

Search: best-first with a beam over the scored candidates, random restarts from the best ones after
`--patience` rounds without progress, a time and evaluation budget, deterministic for a `--seed`
(within the same budget of evaluations). Output: the best source as `<stem>.sweep.<score><ext>` beside
the input (or in --out-dir), the best `--keep` candidates in `<stem>.sweep/`, a log of the move
sequences in `<stem>.sweep.log`, and a one-line summary on stdout.

Usage:
  python3 tools/cxx_sweep.py CAND.c FUNCTION [--va 0xVA] [--config DIR] [--jobs 4] [--time 600]
  python3 tools/cxx_sweep.py CAND.cpp FUNCTION --whole-file [--config DIR]
  python3 tools/cxx_sweep.py CAND.cpp FUNCTION --score-only        # round-trip the unchanged source
  python3 tools/cxx_sweep.py CAND.c FUNCTION --list-moves          # the first ring of candidates
"""
import argparse
import concurrent.futures
import itertools
import json
import os
import random
import re
import subprocess
import sys
import threading
import time

HERE = os.path.dirname(os.path.abspath(__file__))


class ParseError(Exception):
    pass


# ---------------------------------------------------------------- lexer

KEYWORDS = {
    "alignas", "asm", "__asm__", "__asm", "auto", "bool", "break", "case", "catch", "char", "class", "const",
    "const_cast", "continue", "default", "delete", "do", "double", "dynamic_cast", "else", "enum",
    "explicit", "extern", "false", "float", "for", "friend", "goto", "if", "inline", "__inline", "int",
    "long", "mutable", "namespace", "new", "operator", "private", "protected", "public", "register",
    "reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_cast", "struct",
    "switch", "template", "this", "throw", "true", "try", "typedef", "typeid", "typename", "union",
    "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "__restrict", "restrict",
    "_Bool", "__int64",
}
TYPE_KEYWORDS = {"void", "char", "short", "int", "long", "float", "double", "signed", "unsigned", "bool",
                 "wchar_t", "__int64", "_Bool"}
CV = {"const", "volatile", "__restrict", "restrict"}
STORAGE = {"static", "extern", "register", "auto", "inline", "__inline", "typedef", "mutable", "virtual",
           "explicit", "friend"}
TAGS = {"struct", "union", "enum", "class"}
ASSIGN_OPS = {"=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>="}
OPEN = {"(": ")", "[": "]", "{": "}"}
CLOSE = {")": "(", "]": "[", "}": "{"}
BIN = {"*": 13, "/": 13, "%": 13, "+": 12, "-": 12, "<<": 11, ">>": 11, "<": 10, ">": 10, "<=": 10,
       ">=": 10, "==": 9, "!=": 9, "&": 8, "^": 7, "|": 6, "&&": 5, "||": 4}
COMMUTATIVE = {"+", "*", "&", "|", "^", "==", "!="}
STMT_KEYWORDS = {"if", "else", "while", "do", "for", "switch", "return", "break", "continue", "goto", "case",
                 "default", "try", "catch", "throw", "delete", "new", "sizeof"}

_TOKEN = re.compile(r"""
 (?P<ws>\s+)
|(?P<comment>//[^\n]*|/\*.*?\*/)
|(?P<string>L?"(?:[^"\\\n]|\\.)*")
|(?P<char>L?'(?:[^'\\\n]|\\.)*')
|(?P<number>0[xX][0-9a-fA-F]+[uUlL]*|(?:\d+\.\d*|\.\d+|\d+)(?:[eE][+-]?\d+)?[uUlLfF]*)
|(?P<ident>[A-Za-z_$][A-Za-z0-9_$]*)
|(?P<punct>\.\.\.|<<=|>>=|->\*|::|->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\||\+=|-=|\*=|/=|%=|&=|\|=|\^=|\.\*|[{}()\[\];,.<>+\-*/%&|^!~?:=\#])
""", re.S | re.X)


class Tok:
    __slots__ = ("kind", "text", "start", "end")

    def __init__(self, kind, text, start, end):
        self.kind, self.text, self.start, self.end = kind, text, start, end

    def __repr__(self):
        return "Tok(%s,%r)" % (self.kind, self.text)


def tokenize(text):
    toks, pos, n, line_start = [], 0, len(text), True
    while pos < n:
        if text[pos] == "#" and line_start:
            end = pos
            while True:
                nl = text.find("\n", end)
                if nl < 0:
                    end = n
                    break
                if text[nl - 1] == "\\" or (text[nl - 1] == "\r" and text[nl - 2] == "\\"):
                    end = nl + 1
                    continue
                end = nl
                break
            toks.append(Tok("pp", text[pos:end], pos, end))
            pos, line_start = end, False
            continue
        m = _TOKEN.match(text, pos)
        if not m:
            toks.append(Tok("punct", text[pos], pos, pos + 1))
            pos, line_start = pos + 1, False
            continue
        kind = m.lastgroup
        toks.append(Tok(kind, m.group(), pos, m.end()))
        if kind in ("ws", "comment"):
            if "\n" in m.group():
                line_start = True
        else:
            line_start = False
        pos = m.end()
    return toks


def norm(text):
    """The text as its significant tokens, one space apart: comments and layout do not count."""
    return " ".join(t.text for t in tokenize(text) if t.kind not in ("ws", "comment"))


class Source:
    """A file's text, its tokens, and the bracket pairs of its significant tokens."""

    def __init__(self, text):
        self.text = text
        self.toks = tokenize(text)
        self.sig = [t for t in self.toks if t.kind not in ("ws", "comment", "pp")]
        self.pair = {}
        stack = []
        for i, t in enumerate(self.sig):
            if t.kind != "punct":
                continue
            if t.text in OPEN:
                stack.append(i)
            elif t.text in CLOSE:
                if not stack or self.sig[stack[-1]].text != CLOSE[t.text]:
                    raise ParseError("unbalanced %r at offset %d" % (t.text, t.start))
                j = stack.pop()
                self.pair[i], self.pair[j] = j, i
        if stack:
            raise ParseError("unclosed %r" % self.sig[stack[-1]].text)

    def span(self, a, b):
        """Text of significant tokens a..b-1 (with the layout between them)."""
        if b <= a:
            return ""
        return self.text[self.sig[a].start:self.sig[b - 1].end]

    def cs(self, i):
        return self.sig[i].start

    def ce(self, i):
        return self.sig[i - 1].end

    def edit(self, edits):
        """Apply (start, end, new) character edits that do not overlap -> new text."""
        out, pos = [], 0
        for s, e, new in sorted(edits, key=lambda x: (x[0], x[1])):
            if s < pos:
                raise ParseError("overlapping edits")
            out.append(self.text[pos:s])
            out.append(new)
            pos = e
        out.append(self.text[pos:])
        return "".join(out)

    def indent_at(self, char_pos):
        line = self.text.rfind("\n", 0, char_pos) + 1
        lead = self.text[line:char_pos]
        return lead if lead.strip() == "" else "    "


# ---------------------------------------------------------------- types seen in the file


def collect_types(text, include_dirs=(), seen=None, depth=0):
    """Type names (typedefs, tags, classes) and struct fields of `text` and the headers it includes.

    -> (names: set, fields: {struct: {field: (base, stars)}}, alias: {name: name}, bases: {struct: [base]})
    """
    names, fields, alias, bases = set(), {}, {}, {}
    seen = set() if seen is None else seen
    for m in re.finditer(r'^\s*#\s*include\s*"([^"]+)"', text, re.M):
        if depth > 6:
            break
        for d in include_dirs:
            p = os.path.normpath(os.path.join(d, m.group(1)))
            if os.path.isfile(p):
                if p not in seen:
                    seen.add(p)
                    try:
                        sub = open(p, errors="replace").read()
                    except OSError:
                        break
                    n2, f2, a2, b2 = collect_types(sub, (os.path.dirname(p),) + tuple(include_dirs), seen,
                                                   depth + 1)
                    names |= n2
                    fields.update(f2)
                    alias.update(a2)
                    bases.update(b2)
                break
    try:
        src = Source(text)
    except ParseError:
        return names, fields, alias, bases
    S = src.sig
    n = len(S)
    i = 0
    while i < n:
        t = S[i].text
        if t in TAGS and i + 1 < n and S[i + 1].kind == "ident":
            tag = S[i + 1].text
            names.add(tag)
            j = i + 2
            if j < n and S[j].text == ":":       # base classes
                k = j + 1
                while k < n and S[k].text != "{" and S[k].text != ";":
                    if S[k].kind == "ident" and S[k].text not in KEYWORDS:
                        bases.setdefault(tag, []).append(S[k].text)
                    k += 1
                j = k
            if j < n and S[j].text == "{":
                fields[tag] = struct_fields(src, j, names)
                close = src.pair[j]
                # typedef struct X {...} Y;
                k = close + 1
                start = i - 1
                if start >= 0 and S[start].text == "typedef":
                    while k < n and S[k].text != ";":
                        if S[k].kind == "ident" and S[k].text not in KEYWORDS:
                            names.add(S[k].text)
                            alias[S[k].text] = tag
                        k += 1
                i = j + 1
                continue
            i += 2
            continue
        if t == "typedef":
            k = i + 1
            depth_ = 0
            last = None
            while k < n and not (S[k].text == ";" and depth_ == 0):
                if S[k].text in OPEN:
                    if S[k].text == "{":
                        k = src.pair[k] + 1
                        continue
                    depth_ += 1
                elif S[k].text in CLOSE:
                    depth_ -= 1
                elif S[k].kind == "ident" and S[k].text not in KEYWORDS:
                    if last is None or depth_ <= 1:
                        last = (S[k].text, k)
                k += 1
            if last:
                names.add(last[0])
                # typedef A B;  -> alias B -> A
                body = [x for x in S[i + 1:last[1]] if x.kind == "ident" and x.text not in KEYWORDS]
                stars = sum(1 for x in S[i + 1:last[1]] if x.text == "*")
                if len(body) == 1 and stars == 0:
                    alias[last[0]] = body[0].text
            i += 1
            continue
        if t == "template":
            i += 1
            continue
        i += 1
    return names, fields, alias, bases


def struct_fields(src, lb, names):
    """{field: (base, stars, is_array)} of the struct body at `lb` (methods and nested types skipped)."""
    S = src.sig
    rb = src.pair[lb]
    out = {}
    i = lb + 1
    while i < rb:
        j = i
        while j < rb and S[j].text not in (";", "{"):
            if S[j].text in OPEN:
                j = src.pair[j] + 1
            else:
                j += 1
        if j < rb and S[j].text == "{":         # method body or nested type
            j = src.pair[j] + 1
            if j < rb and S[j].text == ";":
                j += 1
            i = j
            continue
        toks = S[i:j]
        i = j + 1
        while len(toks) >= 2 and toks[0].text in ("public", "private", "protected") and toks[1].text == ":":
            toks = toks[2:]
        if not toks or toks[0].text in ("public", "private", "protected", "typedef", "friend", "using",
                                         "template", "enum", "static"):
            continue
        texts = [t.text for t in toks]
        if ":" in texts and texts[0] in ("public", "private", "protected"):
            continue
        # spec + declarators
        k = 0
        base = None
        while k < len(toks):
            x = toks[k].text
            if x in CV or x in STORAGE:
                k += 1
                continue
            if x in TYPE_KEYWORDS:
                base = (base + " " + x) if base and base.split()[-1] in TYPE_KEYWORDS else x
                k += 1
                continue
            if x in TAGS and k + 1 < len(toks):
                base = toks[k + 1].text
                k += 2
                continue
            if toks[k].kind == "ident" and base is None:
                base = x
                k += 1
                while k + 1 < len(toks) and toks[k].text == "::":
                    base = toks[k + 1].text
                    k += 2
                if k < len(toks) and toks[k].text == "<":
                    d = 0
                    while k < len(toks):
                        d += toks[k].text.count("<") if toks[k].text in ("<", "<<") else 0
                        d -= 2 if toks[k].text == ">>" else (1 if toks[k].text == ">" else 0)
                        k += 1
                        if d <= 0:
                            break
                continue
            break
        if base is None:
            continue
        base = canon_base(base)
        for part in split_top(toks[k:], ","):
            stars = 0
            name = None
            is_array = False
            func = False
            for q, x in enumerate(part):
                if x.text == "*":
                    stars += 1
                elif x.text == "&":
                    pass
                elif x.kind == "ident" and x.text not in CV and name is None:
                    name = x.text
                    if q + 1 < len(part) and part[q + 1].text == "(":
                        func = True
                elif x.text == "[" and name is not None:
                    is_array = True
                elif x.text == ":":
                    break
            if name and not func:
                out[name] = (base, stars, is_array)
    return out


def split_top(toks, sep):
    parts, cur, d = [], [], 0
    for t in toks:
        if t.text in OPEN:
            d += 1
        elif t.text in CLOSE:
            d -= 1
        if t.text == sep and d == 0:
            parts.append(cur)
            cur = []
        else:
            cur.append(t)
    parts.append(cur)
    return parts


def canon_base(base):
    return " ".join(w for w in base.split() if w not in CV and w not in TAGS)


# ---------------------------------------------------------------- the function and its statements


class Node:
    def __init__(self, kind, s, e, **kw):
        self.kind, self.s, self.e = kind, s, e
        self.parent = None
        self.__dict__.update(kw)

    def children(self):
        if self.kind == "block":
            return list(self.items)
        out = []
        for k in ("then", "els", "body"):
            v = getattr(self, k, None)
            if v is not None:
                out.append(v)
        out.extend(getattr(self, "extra", []))
        return out

    def walk(self):
        yield self
        for c in self.children():
            yield from c.walk()

    def __repr__(self):
        return "Node(%s,%d,%d)" % (self.kind, self.s, self.e)


class Declarator:
    def __init__(self, s, e, name, name_idx, eq, prefix):
        self.s, self.e, self.name, self.name_idx, self.eq = s, e, name, name_idx, eq
        self.prefix = prefix          # token texts between the spec and the name ('*', 'const', '&')

    @property
    def init(self):
        return (self.eq + 1, self.e) if self.eq is not None else None


class Function:
    """The target function: its name token, parameter list, body and parsed statement tree."""

    def __init__(self, src, name, types=frozenset(), cxx=False):
        self.src, self.name, self.types, self.cxx = src, name, set(types) | TYPE_KEYWORDS, cxx
        self.locate(name)
        self.body = self.block(self.lb)
        self.params = self.parse_params()
        self.decls = [n for n in self.body.walk() if n.kind == "decl"]
        self.locals = {}
        for d in self.decls:
            if d.storage & {"extern", "static", "typedef"}:
                continue
            for dc in d.decls:
                if dc.name:
                    self.locals[dc.name] = (d, dc)
        for n in self.body.walk():
            if n.kind == "for" and n.for_decl is not None:
                for dc in n.for_decl.decls:
                    if dc.name:
                        self.locals[dc.name] = (n.for_decl, dc)
        self.param_names = [p[1] for p in self.params if p[1]]
        self.escaped = self.address_taken()

    # -- location
    def locate(self, name):
        S, src = self.src.sig, self.src
        parts = name.split("::")
        last = parts[-1]
        for i, t in enumerate(S):
            if t.kind != "ident" or t.text != last or i + 1 >= len(S) or S[i + 1].text != "(":
                continue
            if i > 0 and S[i - 1].text in (".", "->"):
                continue
            k = i
            ok = True
            for p in reversed(parts[:-1]):
                if k < 2 or S[k - 1].text != "::" or S[k - 2].text != p:
                    ok = False
                    break
                k -= 2
            if not ok:
                continue
            rp = src.pair.get(i + 1)
            if rp is None:
                continue
            j = rp + 1
            while j < len(S) and S[j].text in ("const", "volatile", "throw", "noexcept"):
                if S[j].text == "throw" and j + 1 < len(S) and S[j + 1].text == "(":
                    j = src.pair[j + 1] + 1
                else:
                    j += 1
            if j < len(S) and S[j].text == ":":
                while j < len(S) and S[j].text not in ("{", ";"):
                    j = src.pair[j] + 1 if S[j].text in ("(", "[") else j + 1
            if j < len(S) and S[j].text == "{":
                self.name_idx, self.qual_start, self.lp, self.rp = i, k, i + 1, rp
                self.lb, self.rb = j, src.pair[j]
                st = k
                while st > 0 and S[st - 1].text not in (";", "}", "{"):
                    st -= 1
                self.start = st
                return
        raise ParseError("no definition of %s" % name)

    @property
    def start_char(self):
        return self.src.sig[self.start].start

    def return_type(self):
        toks = [t for t in self.src.sig[self.start:self.qual_start]
                if t.text not in STORAGE and t.kind != "string" and t.text != "template"]
        return " ".join(t.text for t in toks).replace(" *", " *").strip()

    def parse_params(self):
        S = self.src.sig
        out = []
        if self.rp == self.lp + 1:
            return out
        for part in self.split_commas(self.lp + 1, self.rp):
            a, b = part
            if b - a == 1 and S[a].text in ("void", "..."):
                continue
            spec_end, storage = self.spec_end(a, b)
            dc = self.declarator(spec_end, b)
            if dc.name:
                ty = (self.src.span(a, spec_end) + " " + " ".join(dc.prefix)).strip()
                out.append((ty, dc.name, self.type_of_decl(a, spec_end, dc)))
            else:
                out.append((self.src.span(a, b), None, None))
        return out

    def split_commas(self, a, b):
        S, out, start, i = self.src.sig, [], a, a
        while i < b:
            if S[i].text in OPEN:
                i = self.src.pair[i] + 1
                continue
            if S[i].text == "<" and i > a and S[i - 1].text in self.types:
                d = 0
                while i < b:
                    d += 1 if S[i].text == "<" else (-1 if S[i].text == ">" else (-2 if S[i].text == ">>" else 0))
                    i += 1
                    if d <= 0:
                        break
                continue
            if S[i].text == ",":
                out.append((start, i))
                start = i + 1
            i += 1
        out.append((start, b))
        return out

    # -- statements
    def block(self, lb):
        S, src = self.src.sig, self.src
        rb = src.pair[lb]
        items, i = [], lb + 1
        while i < rb:
            st = self.stmt(i)
            if st.e <= i:
                raise ParseError("no progress at %d" % i)
            items.append(st)
            i = st.e
        if i != rb:
            raise ParseError("block overrun")
        n = Node("block", lb, rb + 1, items=items)
        for it in items:
            it.parent = n
        return n

    def end_of(self, i, stop=";"):
        S = self.src.sig
        while i < len(S) and S[i].text != stop:
            if S[i].text in OPEN:
                i = self.src.pair[i] + 1
            elif S[i].text in CLOSE:
                raise ParseError("unexpected %r" % S[i].text)
            else:
                i += 1
        if i >= len(S):
            raise ParseError("no %r" % stop)
        return i

    def paren(self, i):
        S = self.src.sig
        if S[i].text != "(":
            raise ParseError("expected ( at %r" % S[i].text)
        return self.src.pair[i]

    def stmt(self, i):
        S = self.src.sig
        t = S[i].text
        node = None
        if t == "{":
            return self.block(i)
        if t == ";":
            return Node("empty", i, i + 1)
        if t == "if":
            rp = self.paren(i + 1)
            then = self.stmt(rp + 1)
            e, els, else_idx = then.e, None, None
            if e < len(S) and S[e].text == "else":
                else_idx = e
                els = self.stmt(e + 1)
                e = els.e
            node = Node("if", i, e, cond=(i + 2, rp), then=then, els=els, else_idx=else_idx)
        elif t in ("while", "switch"):
            rp = self.paren(i + 1)
            body = self.stmt(rp + 1)
            node = Node(t, i, body.e, cond=(i + 2, rp), body=body)
        elif t == "do":
            body = self.stmt(i + 1)
            if S[body.e].text != "while":
                raise ParseError("do without while")
            rp = self.paren(body.e + 1)
            if S[rp + 1].text != ";":
                raise ParseError("do-while without ;")
            node = Node("do", i, rp + 2, body=body, cond=(body.e + 2, rp), while_idx=body.e)
        elif t == "for":
            lp = i + 1
            rp = self.paren(lp)
            semis = []
            k = lp + 1
            while k < rp:
                if S[k].text in OPEN:
                    k = self.src.pair[k] + 1
                    continue
                if S[k].text == ";":
                    semis.append(k)
                k += 1
            if len(semis) != 2:
                raise ParseError("for without two ;")
            body = self.stmt(rp + 1)
            for_decl = None
            if self.is_decl(lp + 1, semis[0]):
                for_decl = self.decl(lp + 1, semis[0])
            node = Node("for", i, body.e, init=(lp + 1, semis[0]), cond=(semis[0] + 1, semis[1]),
                        step=(semis[1] + 1, rp), body=body, for_decl=for_decl, rp=rp)
        elif t == "return":
            k = self.end_of(i)
            node = Node("return", i, k + 1, expr=(i + 1, k))
        elif t in ("break", "continue"):
            node = Node("jump", i, i + 2, what=t)
        elif t == "goto":
            node = Node("goto", i, i + 3, label=S[i + 1].text)
        elif t in ("case", "default"):
            k = i + 1
            while S[k].text != ":":
                k = self.src.pair[k] + 1 if S[k].text in OPEN else k + 1
            node = Node("case", i, k + 1)
        elif t == "try":
            blk = self.block(i + 1)
            e = blk.e
            extra = [blk]
            while e < len(S) and S[e].text == "catch":
                rp = self.paren(e + 1)
                b = self.block(rp + 1)
                extra.append(b)
                e = b.e
            node = Node("other", i, e, extra=extra)
        elif S[i].kind == "ident" and t not in KEYWORDS and S[i + 1].text == ":":
            node = Node("label", i, i + 2, name=t)
        else:
            k = self.end_of(i)
            if self.is_decl(i, k):
                node = self.decl(i, k)
                node.e = k + 1
            else:
                node = Node("expr", i, k + 1, expr=(i, k))
        for c in node.children():
            c.parent = node
        return node

    def skip_qualified(self, j, limit):
        S = self.src.sig
        if S[j].text == "::":
            j += 1
        j += 1
        while j + 1 < limit and S[j].text == "::" and S[j + 1].kind == "ident":
            j += 2
        if j < limit and S[j].text == "<":
            d = 0
            while j < limit:
                x = S[j].text
                d += 1 if x == "<" else (-1 if x == ">" else (-2 if x == ">>" else 0))
                j += 1
                if d <= 0:
                    break
            if j < limit and S[j].text == "::":
                return self.skip_qualified(j + 1, limit) if S[j + 1].kind == "ident" else j
        return j

    def is_decl(self, i, k):
        S = self.src.sig
        if i >= k:
            return False
        t = S[i].text
        if t in STMT_KEYWORDS or t in ("this", "operator"):
            return False
        if t in TYPE_KEYWORDS or t in CV or t in TAGS or t in STORAGE or t == "typename":
            return True
        if S[i].kind != "ident" and t != "::":
            return False
        j = self.skip_qualified(i, k)
        known = (t in self.types) or (S[j - 1].text in self.types)
        if j < k and S[j - 1].text == ">":
            known = True
        q = j
        while q < k and S[q].text in ("*", "&", "const", "volatile"):
            q += 1
        if q == j:
            return q < k and S[q].kind == "ident" and S[q].text not in KEYWORDS and \
                (q + 1 == k or S[q + 1].text in ("=", ",", "[", "(", ";"))
        if not known:
            # `A *b;` / `A *b = c;` as an expression would discard a product or assign to an rvalue
            return q < k and S[q].kind == "ident" and S[q].text not in KEYWORDS and j == i + 1 and \
                all(S[x].text == "*" for x in range(j, q)) and \
                (q + 1 == k or S[q + 1].text in ("=", ",", "["))
        if q < k and S[q].text == "(" and q + 1 < k and S[q + 1].text == "*":
            return True
        return q < k and S[q].kind == "ident" and S[q].text not in KEYWORDS

    def spec_end(self, i, k):
        S = self.src.sig
        j, seen, storage = i, False, set()
        while j < k:
            t = S[j].text
            if t in STORAGE:
                storage.add(t)
                j += 1
            elif t in CV or t == "typename":
                j += 1
            elif t in TYPE_KEYWORDS:
                j += 1
                seen = True
            elif t in TAGS:
                j += 1
                if j < k and S[j].kind == "ident":
                    j = self.skip_qualified(j, k)
                if j < k and S[j].text == "{":
                    j = self.src.pair[j] + 1
                seen = True
            elif (S[j].kind == "ident" or t == "::") and not seen:
                j = self.skip_qualified(j, k)
                seen = True
            elif t == "extern" or S[j].kind == "string":
                j += 1
            else:
                break
        return j, storage

    def declarator(self, a, b):
        S = self.src.sig
        name = name_idx = eq = None
        prefix = []
        i = a
        while i < b:
            t = S[i]
            if t.text == "=" and eq is None:
                eq = i
                break
            if name is None:
                if t.kind == "ident" and t.text not in CV and t.text not in KEYWORDS:
                    name, name_idx = t.text, i
                elif t.text in ("*", "&", "const", "volatile"):
                    prefix.append(t.text)
                elif t.text == "(":
                    pass
            i += 1
        return Declarator(a, b, name, name_idx, eq, prefix)

    def decl(self, i, k):
        j, storage = self.spec_end(i, k)
        decls = [self.declarator(a, b) for a, b in self.split_commas(j, k)]
        return Node("decl", i, k, spec=(i, j), decls=decls, storage=storage)

    # -- types of locals
    def type_of_decl(self, a, spec_end, dc):
        S = self.src.sig
        base = []
        for t in S[a:spec_end]:
            if t.text in STORAGE or t.text in CV or t.text in TAGS or t.text == "typename":
                continue
            base.append(t.text)
        if not base:
            return None
        if dc.name_idx is not None and dc.name_idx + 1 < dc.e and S[dc.name_idx + 1].text in ("[", "("):
            return None
        if any(S[x].text == "(" for x in range(dc.s, dc.name_idx or dc.s)):
            return None
        stars = dc.prefix.count("*")
        return (canon_base(" ".join(base)).replace(" :: ", "::"), stars)

    def local_type(self, name):
        if name in self.locals:
            d, dc = self.locals[name]
            return self.type_of_decl(d.spec[0], d.spec[1], dc)
        for ty, nm, tt in self.params:
            if nm == name:
                return tt
        return None

    def local_type_text(self, name):
        """The declared type of a local or parameter as text (`Obj *`), or None for arrays and the like."""
        S = self.src.sig
        if name in self.locals:
            d, dc = self.locals[name]
            if self.type_of_decl(d.spec[0], d.spec[1], dc) is None:
                return None
            spec = " ".join(t.text for t in S[d.spec[0]:d.spec[1]] if t.text not in STORAGE)
            return (spec + " " + " ".join(dc.prefix)).strip()
        for ty, nm, tt in self.params:
            if nm == name:
                return ty if tt is not None else None
        return None

    def is_unary(self, i):
        S = self.src.sig
        if i == 0:
            return True
        p = S[i - 1]
        if p.kind in ("ident", "number", "string", "char"):
            return p.text in KEYWORDS and p.text not in ("this", "true", "false")
        return p.text not in (")", "]")

    def address_taken(self):
        out = set()
        S = self.src.sig
        for i in range(self.lb, self.rb):
            if S[i].text == "&" and self.is_unary(i) and S[i + 1].kind == "ident":
                out.add(S[i + 1].text)
        return out


# ---------------------------------------------------------------- reads and writes


class Effects:
    """Names and memory a token span reads and writes; `MEM` stands for memory and anything not local."""

    def __init__(self, fn):
        self.fn = fn
        self.S = fn.src.sig

    def is_local(self, name):
        return (name in self.fn.locals or name in self.fn.param_names) and name not in self.fn.escaped

    def of(self, a, b, pending=False):
        """(reads, writes) of tokens a..b. `pending`: a call whose argument list runs past b has not
        happened yet, so it neither reads nor writes memory."""
        S, fn = self.S, self.fn
        R, W = set(), set()
        for i in range(a, b):
            t = S[i]
            if t.kind == "ident":
                if i > 0 and S[i - 1].text in (".", "->"):
                    continue
                if t.text in KEYWORDS or (t.text in fn.types and not self.is_local(t.text)):
                    continue
                if pending and i + 1 < len(S) and S[i + 1].text == "(" and fn.src.pair[i + 1] >= b:
                    continue
                if i + 1 < len(S) and S[i + 1].text == "(" and not self.is_local(t.text):
                    R.add("MEM")
                    W.add("MEM")
                    continue
                R.add(t.text)
                if not self.is_local(t.text):
                    R.add("MEM")
            elif t.text in ("->", "["):
                R.add("MEM")
            elif t.text == "*" and fn.is_unary(i):
                R.add("MEM")
            elif t.text == "(" and i > 0 and S[i - 1].text == ")" :
                R.add("MEM")          # call through a pointer
                W.add("MEM")
            if t.text in ("new", "delete", "throw"):
                R.add("MEM")
                W.add("MEM")
        for i in range(a, b):
            x = S[i].text
            if x in ASSIGN_OPS:
                lo = self.lhs_start(i, a)
                W |= self.target(lo, i)
            elif x in ("++", "--"):
                if i > a and (S[i - 1].kind == "ident" or S[i - 1].text in (")", "]")) and \
                        S[i - 1].text not in KEYWORDS:
                    lo = self.lhs_start(i, a)
                    W |= self.target(lo, i)
                else:
                    hi = i + 1
                    while hi < b and (S[hi].kind == "ident" or S[hi].text in (".", "->", "::")):
                        hi += 1
                        if hi < b and S[hi].text in ("[", "("):
                            hi = self.fn.src.pair[hi] + 1
                    W |= self.target(i + 1, hi)
        return R, W

    def lhs_start(self, i, a):
        S, fn = self.S, self.fn
        j = i - 1
        while j >= a:
            t = S[j]
            if t.text in (")", "]"):
                j = fn.src.pair[j] - 1
                continue
            if t.kind == "ident" and t.text not in KEYWORDS or t.text in (".", "->", "::") or t.kind == "number":
                j -= 1
                continue
            if t.text == "*" and fn.is_unary(j):
                j -= 1
                continue
            if t.text == "this":
                j -= 1
                continue
            break
        return j + 1

    def target(self, lo, hi):
        S = self.S
        toks = [S[k] for k in range(lo, hi)]
        while len(toks) >= 2 and toks[0].text == "(" and toks[-1].text == ")":
            toks = toks[1:-1]
        idents = [t for t in toks if t.kind == "ident" and t.text not in KEYWORDS]
        if len(toks) == 1 and toks[0].kind == "ident":
            name = toks[0].text
            return {name} if self.is_local(name) else {name, "MEM"}
        if any(t.text in ("->", "[", "*", "(", "this") for t in toks) or not idents:
            return {"MEM"}
        name = idents[0].text
        return {name} if self.is_local(name) else {name, "MEM"}

    def node(self, n):
        R, W = self.of(n.s, n.e)
        if n.kind == "decl":
            for dc in n.decls:
                if dc.name:
                    W.add(dc.name)
        if n.kind == "for" and n.for_decl is not None:
            for dc in n.for_decl.decls:
                if dc.name:
                    W.add(dc.name)
        return R, W


def has_control(fn, n):
    """True when the node is or holds a jump, a label or a case: something that ties it to its place."""
    S = fn.src.sig
    if n.kind in ("label", "case", "jump", "goto", "return"):
        return True
    for i in range(n.s, n.e):
        t = S[i]
        if t.text in ("return", "break", "continue", "goto", "case", "default", "throw"):
            return True
        if t.kind == "ident" and t.text not in KEYWORDS and i + 1 < n.e and S[i + 1].text == ":" and \
                (i == n.s or S[i - 1].text in (";", "{", "}", ":")):
            return True
    return False


def independent(fx, a, b):
    Ra, Wa = fx.node(a)
    Rb, Wb = fx.node(b)
    return not (Wa & (Rb | Wb)) and not (Wb & Ra)


def has_side_effects(fn, a, b):
    S = fn.src.sig
    for i in range(a, b):
        t = S[i].text
        if t in ASSIGN_OPS or t in ("++", "--", "new", "delete", "throw"):
            return True
        if t == "(" and i > a and (S[i - 1].kind == "ident" and S[i - 1].text not in KEYWORDS
                                   and S[i - 1].text not in fn.types or S[i - 1].text == ")"):
            return True
    return False


def ident_uses(fn, name, a=None, b=None):
    """Indices of the tokens that name the variable `name` (member names after . or -> excluded)."""
    S = fn.src.sig
    a = fn.lb if a is None else a
    b = fn.rb if b is None else b
    return [i for i in range(a, b) if S[i].kind == "ident" and S[i].text == name
            and not (i > 0 and S[i - 1].text in (".", "->", "::"))]


# ---------------------------------------------------------------- expressions


class Expr:
    def __init__(self, kind, s, e, op=None, kids=()):
        self.kind, self.s, self.e, self.op, self.kids = kind, s, e, op, list(kids)
        self.parent = None
        for k in self.kids:
            k.parent = self

    def walk(self):
        yield self
        for k in self.kids:
            yield from k.walk()

    def prec(self, S):
        if self.kind == "bin":
            return BIN[S[self.op].text]
        if self.kind == "cond":
            return 3
        if self.kind == "assign":
            return 2
        if self.kind == "comma":
            return 1
        return 20 if self.kind in ("prim", "paren", "post", "call", "index", "member") else 15


class ExprParser:
    def __init__(self, fn, a, b):
        self.fn, self.S, self.i, self.b = fn, fn.src.sig, a, b

    def peek(self):
        return self.S[self.i].text if self.i < self.b else None

    def parse(self):
        e = self.comma()
        if self.i != self.b:
            raise ParseError("trailing tokens in expression")
        return e

    def comma(self):
        l = self.assign()
        while self.peek() == ",":
            op = self.i
            self.i += 1
            r = self.assign()
            l = Expr("comma", l.s, r.e, op, [l, r])
        return l

    def assign(self):
        l = self.cond()
        if self.peek() in ASSIGN_OPS:
            op = self.i
            self.i += 1
            r = self.assign()
            return Expr("assign", l.s, r.e, op, [l, r])
        return l

    def cond(self):
        c = self.binary(4)
        if self.peek() == "?":
            q = self.i
            self.i += 1
            a = self.comma()
            if self.peek() != ":":
                raise ParseError("?: without :")
            self.i += 1
            b = self.assign()
            return Expr("cond", c.s, b.e, q, [c, a, b])
        return c

    def binary(self, minp):
        l = self.unary()
        while self.peek() in BIN and BIN[self.peek()] >= minp:
            op = self.i
            p = BIN[self.peek()]
            self.i += 1
            r = self.binary(p + 1)
            l = Expr("bin", l.s, r.e, op, [l, r])
        return l

    def is_cast(self, i):
        S, fn = self.S, self.fn
        if S[i].text != "(":
            return False
        rp = fn.src.pair[i]
        if rp >= self.b or rp + 1 >= self.b:
            return False
        first = S[i + 1]
        if not (first.text in TYPE_KEYWORDS or first.text in CV or first.text in TAGS
                or (first.kind == "ident" and first.text in fn.types and not (first.text in fn.locals))):
            return False
        for k in range(i + 1, rp):
            if S[k].kind not in ("ident",) and S[k].text not in ("*", "&", "::", "<", ">", ","):
                return False
        nxt = S[rp + 1]
        return nxt.kind in ("ident", "number", "string", "char") or nxt.text in ("(", "*", "&", "-", "!", "~", "++", "--", "::")

    def unary(self):
        S = self.S
        t = self.peek()
        if t is None:
            raise ParseError("expression ends early")
        if t in ("-", "+", "!", "~", "*", "&", "++", "--"):
            op = self.i
            self.i += 1
            x = self.unary()
            return Expr("unary", op, x.e, op, [x])
        if t == "sizeof":
            s = self.i
            self.i += 1
            if self.peek() == "(":
                rp = self.fn.src.pair[self.i]
                self.i = rp + 1
                return Expr("prim", s, self.i)
            x = self.unary()
            return Expr("prim", s, x.e)
        if t in ("new", "delete", "throw"):
            raise ParseError("new/delete/throw not handled")
        if t == "(" and self.is_cast(self.i):
            s = self.i
            rp = self.fn.src.pair[self.i]
            self.i = rp + 1
            x = self.unary()
            return Expr("cast", s, x.e, s, [x])
        return self.postfix()

    def postfix(self):
        S, pair = self.S, self.fn.src.pair
        p = self.primary()
        while True:
            t = self.peek()
            if t == "(":
                lp = self.i
                rp = pair[lp]
                self.i = lp + 1
                args = []
                while self.i < rp:
                    sub = ExprParser(self.fn, self.i, rp)
                    a = sub.assign()
                    args.append(a)
                    self.i = sub.i
                    if self.i < rp:
                        if S[self.i].text != ",":
                            raise ParseError("bad argument list")
                        self.i += 1
                self.i = rp + 1
                p = Expr("call", p.s, self.i, lp, [p] + args)
            elif t == "[":
                lb = self.i
                rb = pair[lb]
                idx = ExprParser(self.fn, lb + 1, rb).parse()
                self.i = rb + 1
                p = Expr("index", p.s, self.i, lb, [p, idx])
            elif t in (".", "->"):
                op = self.i
                self.i += 1
                if self.peek() == "~":
                    self.i += 1
                if self.i >= self.b or S[self.i].kind != "ident":
                    raise ParseError("member name expected")
                self.i += 1
                p = Expr("member", p.s, self.i, op, [p])
            elif t in ("++", "--"):
                op = self.i
                self.i += 1
                p = Expr("post", p.s, self.i, op, [p])
            else:
                return p

    def primary(self):
        S = self.S
        t = self.peek()
        s = self.i
        if t is None:
            raise ParseError("expression ends early")
        tok = S[self.i]
        if t == "(":
            rp = self.fn.src.pair[self.i]
            inner = ExprParser(self.fn, self.i + 1, rp).parse()
            self.i = rp + 1
            return Expr("paren", s, self.i, None, [inner])
        if t in ("static_cast", "reinterpret_cast", "const_cast", "dynamic_cast"):
            self.i += 1
            d = 0
            while self.i < self.b:
                x = S[self.i].text
                d += 1 if x == "<" else (-1 if x == ">" else (-2 if x == ">>" else 0))
                self.i += 1
                if d <= 0:
                    break
            if self.peek() != "(":
                raise ParseError("cast without (")
            rp = self.fn.src.pair[self.i]
            inner = ExprParser(self.fn, self.i + 1, rp).parse()
            self.i = rp + 1
            return Expr("cxxcast", s, self.i, None, [inner])
        if tok.kind in ("number", "char"):
            self.i += 1
            return Expr("prim", s, self.i)
        if tok.kind == "string":
            while self.i < self.b and S[self.i].kind == "string":
                self.i += 1
            return Expr("prim", s, self.i)
        if tok.kind == "ident" or t == "::":
            if t == "::":
                self.i += 1
            self.i += 1
            while self.i + 1 < self.b and S[self.i].text == "::" and S[self.i + 1].kind == "ident":
                self.i += 2
            return Expr("prim", s, self.i)
        raise ParseError("unexpected %r in expression" % t)


def parse_expr(fn, a, b):
    try:
        return ExprParser(fn, a, b).parse() if b > a else None
    except (ParseError, IndexError, KeyError):
        return None


def expr_pure(fn, e):
    for x in e.walk():
        if x.kind in ("assign", "call", "post") or (x.kind == "unary" and fn.src.sig[x.op].text in ("++", "--")):
            return False
    return True


def expression_regions(fn):
    """(a, b, bool_context) for every expression span of the function body."""
    out = []
    for n in fn.body.walk():
        if n.kind == "expr" or n.kind == "return":
            a, b = n.expr
            out.append((a, b, False))
        elif n.kind in ("if", "while", "do", "switch"):
            out.append((n.cond[0], n.cond[1], n.kind != "switch"))
        elif n.kind == "for":
            if n.for_decl is None:
                out.append((n.init[0], n.init[1], False))
            out.append((n.cond[0], n.cond[1], True))
            out.append((n.step[0], n.step[1], False))
        if n.kind == "decl":
            for dc in n.decls:
                if dc.init:
                    out.append((dc.init[0], dc.init[1], False))
    return [r for r in out if r[1] > r[0]]


# ---------------------------------------------------------------- type inference (small)


class Types:
    def __init__(self, names, fields, alias, bases):
        self.names, self.fields, self.alias, self.bases = names, fields, alias, bases

    def canon(self, base):
        seen = set()
        while base in self.alias and base not in seen:
            seen.add(base)
            base = self.alias[base]
        return base

    def field(self, struct, name, depth=0):
        struct = self.canon(struct)
        f = self.fields.get(struct, {})
        if name in f:
            b, s, arr = f[name]
            return (self.canon(b), s + (1 if arr else 0))
        if depth < 6:
            for base in self.bases.get(struct, []):
                r = self.field(base, name, depth + 1)
                if r:
                    return r
        return None


def infer(fn, types, e):
    """(base, stars) of an expression, or None when it is not known."""
    S = fn.src.sig
    if e is None:
        return None
    if e.kind == "prim":
        if e.e - e.s == 1 and S[e.s].kind == "ident":
            t = fn.local_type(S[e.s].text)
            return (types.canon(t[0]), t[1]) if t else None
        return None
    if e.kind == "paren":
        return infer(fn, types, e.kids[0])
    if e.kind == "member":
        t = infer(fn, types, e.kids[0])
        if t is None:
            return None
        op = S[e.op].text
        if (op == "->" and t[1] != 1) or (op == "." and t[1] != 0):
            return None
        return types.field(t[0], S[e.e - 1].text)
    if e.kind == "index":
        t = infer(fn, types, e.kids[0])
        return (t[0], t[1] - 1) if t and t[1] > 0 else None
    if e.kind == "unary" and S[e.op].text == "*":
        t = infer(fn, types, e.kids[0])
        return (t[0], t[1] - 1) if t and t[1] > 0 else None
    if e.kind == "cast":
        rp = fn.src.pair[e.s]
        toks = [t.text for t in S[e.s + 1:rp]]
        base = [x for x in toks if x not in CV and x not in TAGS and x not in ("*", "&")]
        if not base:
            return None
        return (types.canon(canon_base(" ".join(base))), toks.count("*"))
    return None


# ---------------------------------------------------------------- the move set


class Ctx:
    """One parse of a candidate: the source, the function and the helpers the moves use."""

    def __init__(self, text, name, types, cxx, rng=None):
        self.src = Source(text)
        self.fn = Function(self.src, name, types.names, cxx)
        self.types = types
        self.cxx = cxx
        self.fx = Effects(self.fn)
        self.S = self.src.sig

    def text_of(self, n):
        return self.src.span(n.s, n.e)

    def item_text(self, a, b):
        return self.src.span(a, b)

    def blocks(self):
        return [n for n in self.fn.body.walk() if n.kind == "block"]

    def insert_before(self, n, stmt):
        pos = self.src.cs(n.s)
        return (pos, pos, stmt + "\n" + self.src.indent_at(pos))

    def remove(self, n):
        s = self.src.cs(n.s)
        e = self.src.ce(n.e)
        t = self.src.text
        k = s
        while k > 0 and t[k - 1] in " \t":
            k -= 1
        if k > 0 and t[k - 1] == "\n":
            k -= 1
        return (k, e, "")

    def replace_tokens(self, a, b, new):
        return (self.src.cs(a), self.src.ce(b), new)

    def loops_around(self, n):
        out = []
        p = n.parent
        while p is not None:
            if p.kind in ("while", "do", "for"):
                out.append(p)
            p = p.parent
        return out

    def fresh(self, stem):
        used = {t.text for t in self.src.sig if t.kind == "ident"}
        for k in itertools.count():
            nm = "%s%d" % (stem, k)
            if nm not in used:
                return nm


def rebuild(ctx, items, order):
    src = ctx.src
    starts = [src.cs(it.s) for it in items]
    ends = [src.ce(it.e) for it in items]
    texts = [src.text[s:e] for s, e in zip(starts, ends)]
    seps = [src.text[ends[k]:starts[k + 1]] for k in range(len(items) - 1)]
    new = texts[order[0]]
    for k in range(1, len(order)):
        new += seps[k - 1] + texts[order[k]]
    return src.edit([(starts[0], ends[-1], new)])


def decl_runs(block):
    runs, cur = [], []
    for k, it in enumerate(block.items):
        if it.kind == "decl":
            cur.append(k)
        else:
            if len(cur) > 1:
                runs.append(cur)
            cur = []
    if len(cur) > 1:
        runs.append(cur)
    return runs


def order_valid(ctx, items, order):
    """A new order keeps every pair whose relative order changed independent."""
    pos = {o: k for k, o in enumerate(order)}
    for i in range(len(items)):
        for j in range(i + 1, len(items)):
            if pos[i] > pos[j] and not independent(ctx.fx, items[i], items[j]):
                return False
    return True


def m1_decl_order(ctx):
    for blk in ctx.blocks():
        for run in decl_runs(blk):
            items = [blk.items[k] for k in run]
            n = len(items)
            names = lambda o: ",".join(items[k].decls[0].name or "?" for k in o)
            seen = set()
            if n <= 4:
                for order in itertools.permutations(range(n)):
                    if list(order) == list(range(n)) or not order_valid(ctx, items, order):
                        continue
                    seen.add(order)
                    yield "1 decl-order %s" % names(order), rebuild(ctx, items, order)
            for i in range(n):
                for j in range(n):
                    if i == j:
                        continue
                    order = list(range(n))
                    x = order.pop(i)
                    order.insert(j, x)
                    order = tuple(order)
                    if order in seen or not order_valid(ctx, items, order):
                        continue
                    seen.add(order)
                    yield "1 decl-order %s" % names(order), rebuild(ctx, items, order)


def decl_spec_text(ctx, d):
    return ctx.src.span(d.spec[0], d.spec[1])


def declarator_without_init(ctx, dc):
    end = dc.eq if dc.eq is not None else dc.e
    return ctx.src.span(dc.s, end)


def simple_declarator(ctx, d, dc):
    """A declarator whose initialiser can become a plain assignment."""
    S = ctx.S
    if d.storage or any(S[k].text == "const" for k in range(d.spec[0], d.spec[1])) or "&" in dc.prefix:
        return False
    if "const" in dc.prefix:
        return False
    if dc.name_idx is None or dc.eq is None:
        return False
    if any(S[k].text in ("[", "(") for k in range(dc.name_idx + 1, dc.eq)):
        return False
    if dc.e > dc.eq + 1 and S[dc.eq + 1].text == "{":
        return False
    return True


def lead_decl_end(blk):
    k = 0
    while k < len(blk.items) and blk.items[k].kind == "decl":
        k += 1
    return k


def m2_decl_scope(ctx):
    fn, S, src = ctx.fn, ctx.S, ctx.src
    all_names = {}
    for d in fn.decls:
        for dc in d.decls:
            if dc.name:
                all_names[dc.name] = all_names.get(dc.name, 0) + 1
    for p in fn.param_names:
        all_names[p] = all_names.get(p, 0) + 1
    unique = lambda d: all(dc.name and all_names.get(dc.name) == 1 for dc in d.decls)
    blocks = ctx.blocks()
    for blk in blocks:
        for k, it in enumerate(blk.items):
            if it.kind != "decl" or it.storage & {"extern", "static", "typedef"}:
                continue
            # split a multi-declarator line
            if len(it.decls) > 1:
                spec = decl_spec_text(ctx, it)
                ind = src.indent_at(src.cs(it.s))
                parts = ["%s %s;" % (spec, src.span(dc.s, dc.e)) for dc in it.decls]
                new = ("\n" + ind).join(parts)
                yield "2 split-decl %s" % ",".join(dc.name or "?" for dc in it.decls), \
                    src.edit([ctx.replace_tokens(it.s, it.e, new)])
            # merge with the next declaration of the same spec
            if k + 1 < len(blk.items):
                nx = blk.items[k + 1]
                if nx.kind == "decl" and norm(decl_spec_text(ctx, nx)) == norm(decl_spec_text(ctx, it)) \
                        and not nx.storage:
                    new = "%s %s, %s;" % (decl_spec_text(ctx, it),
                                          ", ".join(src.span(dc.s, dc.e) for dc in it.decls),
                                          ", ".join(src.span(dc.s, dc.e) for dc in nx.decls))
                    yield "2 merge-decl %s+%s" % (it.decls[0].name, nx.decls[0].name), \
                        src.edit([(src.cs(it.s), src.ce(nx.e), new)])
            # split `T x = e;` into `T x;` and `x = e;`
            if len(it.decls) == 1 and simple_declarator(ctx, it, it.decls[0]):
                dc = it.decls[0]
                decl_text = "%s %s;" % (decl_spec_text(ctx, it), declarator_without_init(ctx, dc))
                assign = "%s = %s;" % (dc.name, src.span(dc.eq + 1, dc.e))
                ind = src.indent_at(src.cs(it.s))
                yield "2 split-init %s" % dc.name, \
                    src.edit([ctx.replace_tokens(it.s, it.e, decl_text + "\n" + ind + assign)])
                # the assignment placed after the run of declarations
                end = lead_decl_end(blk)
                if end > k + 1 and blk is not None:
                    later = blk.items[k + 1:end]
                    Ra, Wa = ctx.fx.of(dc.eq + 1, dc.e)
                    Wa = Wa | {dc.name}
                    ok = True
                    for o in later:
                        Ro, Wo = ctx.fx.node(o)
                        if (Wa & (Ro | Wo)) or (Wo & Ra):
                            ok = False
                    if ok:
                        last = blk.items[end - 1]
                        pos = src.ce(last.e)
                        yield "2 split-init-after-decls %s" % dc.name, src.edit([
                            ctx.replace_tokens(it.s, it.e, decl_text),
                            (pos, pos, "\n" + ind + assign)])
            # merge `T x;` with a following `x = e;`
            if len(it.decls) == 1 and it.decls[0].eq is None and it.decls[0].name:
                dc = it.decls[0]
                for j in range(k + 1, min(len(blk.items), k + 6)):
                    nx = blk.items[j]
                    e = parse_expr(ctx.fn, *nx.expr) if nx.kind == "expr" else None
                    if e is not None and e.kind == "assign" and S[e.op].text == "=" and \
                            e.kids[0].kind == "prim" and S[e.kids[0].s].text == dc.name and \
                            not ident_uses(fn, dc.name, e.kids[1].s, e.kids[1].e):
                        between = blk.items[k + 1:j]
                        if all(o.kind == "decl" for o in between) and all(
                                not ident_uses(fn, dc.name, o.s, o.e) for o in between):
                            Rr, Wr = ctx.fx.of(e.kids[1].s, e.kids[1].e)
                            if all(not (ctx.fx.node(o)[1] & Rr) and not (Wr & ctx.fx.node(o)[0])
                                   for o in between):
                                new = "%s %s = %s;" % (decl_spec_text(ctx, it), declarator_without_init(ctx, dc),
                                                       src.span(e.kids[1].s, e.kids[1].e))
                                yield "2 merge-init %s" % dc.name, src.edit([
                                    ctx.replace_tokens(it.s, it.e, new), ctx.remove(nx)])
                        break
                    if nx.kind != "decl" or ident_uses(fn, dc.name, nx.s, nx.e):
                        break
            if not unique(it):
                continue
            # move out of a nested block into the enclosing block's declarations
            if blk is not fn.body and all(dc.eq is None for dc in it.decls):
                outer = blk.parent
                while outer is not None and outer.kind != "block":
                    outer = outer.parent
                if outer is not None:
                    end = lead_decl_end(outer)
                    text = ctx.text_of(it)
                    if end:
                        pos = src.ce(outer.items[end - 1].e)
                        ins = (pos, pos, "\n" + src.indent_at(src.cs(outer.items[0].s)) + text)
                    else:
                        pos = src.cs(outer.items[0].s) if outer.items else src.ce(outer.s + 1)
                        ins = (pos, pos, text + "\n" + src.indent_at(pos))
                    yield "2 decl-out %s" % it.decls[0].name, src.edit([ctx.remove(it), ins])
            # move into the one nested block that holds every use
            if all(dc.eq is None for dc in it.decls):
                uses = []
                for dc in it.decls:
                    uses += ident_uses(fn, dc.name)
                uses = [u for u in uses if not (it.s <= u < it.e)]
                if not uses:
                    continue
                inner = None
                for b2 in blocks:
                    if b2 is blk:
                        continue
                    if all(b2.s < u < b2.e - 1 for u in uses) and (inner is None or b2.s > inner.s):
                        if blk.s < b2.s < blk.e:
                            inner = b2
                if inner is None or not inner.items:
                    continue
                # the uses must not sit in a loop around `inner` but inside `blk` (the value would cross iterations)
                p = inner.parent
                crossing = False
                while p is not None and p is not blk:
                    if p.kind in ("while", "do", "for"):
                        crossing = True
                    p = p.parent
                if crossing:
                    continue
                end = lead_decl_end(inner)
                text = ctx.text_of(it)
                if end:
                    pos = src.ce(inner.items[end - 1].e)
                    ins = (pos, pos, "\n" + src.indent_at(src.cs(inner.items[0].s)) + text)
                else:
                    pos = src.cs(inner.items[0].s)
                    ins = (pos, pos, text + "\n" + src.indent_at(pos))
                yield "2 decl-in %s" % it.decls[0].name, src.edit([ctx.remove(it), ins])


def swappable(ctx, n):
    return n.kind not in ("label", "case", "jump", "goto", "return", "empty") and not has_control(ctx.fn, n)


def m3_swap(ctx):
    for blk in ctx.blocks():
        for k in range(len(blk.items) - 1):
            a, b = blk.items[k], blk.items[k + 1]
            if a.kind == "decl" and b.kind == "decl":
                continue          # move 1 owns declaration order
            if not ctx.cxx and (a.kind == "decl") != (b.kind == "decl"):
                continue          # C89: declarations stay ahead of statements
            if not (swappable(ctx, a) and swappable(ctx, b)):
                continue
            if not independent(ctx.fx, a, b):
                continue
            yield "3 swap %s | %s" % (norm(ctx.text_of(a))[:30], norm(ctx.text_of(b))[:30]), \
                rebuild(ctx, [a, b], (1, 0))


def assignment_of(ctx, n):
    """(name, rhs_a, rhs_b, kind) when `n` is `x = e;` or `T x = e;` with x a plain local."""
    S, fn = ctx.S, ctx.fn
    if n.kind == "expr":
        e = parse_expr(fn, *n.expr)
        if e is not None and e.kind == "assign" and S[e.op].text == "=" and e.kids[0].kind == "prim" \
                and e.kids[0].e - e.kids[0].s == 1 and S[e.kids[0].s].kind == "ident":
            name = S[e.kids[0].s].text
            if ctx.fx.is_local(name):
                return name, e.kids[1].s, e.kids[1].e, "expr"
    if n.kind == "decl" and len(n.decls) == 1 and simple_declarator(ctx, n, n.decls[0]):
        dc = n.decls[0]
        if ctx.fx.is_local(dc.name):
            return dc.name, dc.eq + 1, dc.e, "decl"
    return None


def first_use_in(ctx, name, a, b):
    uses = ident_uses(ctx.fn, name, a, b)
    return uses[0] if uses else None


def unconditional(ctx, a, at):
    """No short-circuit, conditional or comma operator decides whether token `at` of a..b runs."""
    return not any(ctx.S[k].text in ("&&", "||", "?", ",") for k in range(a, at))


def m4_assign_into_test(ctx):
    fn, S, src, fx = ctx.fn, ctx.S, ctx.src, ctx.fx
    for blk in ctx.blocks():
        items = blk.items
        for k, loop in enumerate(items):
            if loop.kind not in ("while", "for", "if", "switch"):
                continue
            ca, cb = loop.cond
            if cb <= ca:
                continue
            # forward: the assignment some items back, the items between independent of it
            for j in range(k - 1, max(-1, k - 7), -1):
                asg = assignment_of(ctx, items[j])
                if asg is None:
                    if not swappable(ctx, items[j]):
                        break
                    continue
                name, ra, rb, form = asg
                use = first_use_in(ctx, name, ca, cb)
                if use is None or not unconditional(ctx, ca, use):
                    continue
                if ident_uses(fn, name, ra, rb):
                    continue
                between = items[j + 1:k]
                Rr, Wr = fx.of(ra, rb)
                ok = all(swappable(ctx, o) and not ident_uses(fn, name, o.s, o.e)
                         and not (fx.node(o)[1] & (Rr - {"MEM"})) and not (Wr & fx.node(o)[0])
                         for o in between)
                if not ok:
                    continue
                if loop.kind in ("while", "for"):
                    if has_side_effects(fn, ra, rb):
                        continue
                    lo = loop.body.s if loop.kind == "while" else loop.cond[1]
                    Rl, Wl = fx.of(lo, loop.e)
                    Rc, Wc = fx.of(ca, cb)
                    if name in Wl | Wc or ((Rr - {"MEM"}) & (Wl | Wc)):
                        continue
                if form == "decl" and ctx.cxx is False and j + 1 < len(items) and \
                        any(o.kind != "decl" for o in between):
                    pass
                rhs = src.span(ra, rb)
                edits = [(src.cs(use), src.ce(use + 1), "(%s = %s)" % (name, rhs))]
                if form == "decl":
                    d = items[j]
                    edits.append(ctx.replace_tokens(d.s, d.e, "%s %s;" % (
                        decl_spec_text(ctx, d), declarator_without_init(ctx, d.decls[0]))))
                else:
                    edits.append(ctx.remove(items[j]))
                yield "4 into-test %s -> %s" % (name, loop.kind), src.edit(edits)
            # reverse: hoist `(x = e)` out of the condition
            for i in range(ca, cb):
                if S[i].text != "(" or src.pair[i] >= cb:
                    continue
                rp = src.pair[i]
                if not (S[i + 1].kind == "ident" and S[i + 2].text == "=" and fx.is_local(S[i + 1].text)):
                    continue
                inner = parse_expr(fn, i + 1, rp)
                if inner is None or inner.kind != "assign":
                    continue
                if not unconditional(ctx, ca, i):
                    continue
                name = S[i + 1].text
                ra, rb = i + 3, rp
                if loop.kind in ("while", "for") and has_side_effects(fn, ra, rb):
                    continue
                if loop.kind == "for" and loop.for_decl is not None:
                    continue
                stmt = "%s = %s;" % (name, src.span(ra, rb))
                yield "4 out-of-test %s <- %s" % (name, loop.kind), src.edit([
                    (src.cs(i), src.ce(rp + 1), name), ctx.insert_before(loop, stmt)])


def chains(ctx, a, b):
    """Member-access chains in tokens a..b -> list of (start, end) for every prefix with a load."""
    S, fn, src = ctx.S, ctx.fn, ctx.src
    out = []
    i = a
    while i < b:
        t = S[i]
        if t.kind == "ident" and t.text not in KEYWORDS and not (i > a and S[i - 1].text in (".", "->", "::")) \
                and not (i + 1 < b and S[i + 1].text in ("(", "::")):
            j = i + 1
            while j < b:
                if S[j].text in (".", "->") and j + 1 < b and S[j + 1].kind == "ident":
                    if j + 2 < b and S[j + 2].text == "(":
                        break
                    j += 2
                    out.append((i, j))
                elif S[j].text == "[":
                    rb = src.pair[j]
                    if rb > b:
                        break
                    inner = S[j + 1:rb]
                    if not all(x.kind in ("ident", "number") or x.text in ("+", "-", "*") for x in inner):
                        break
                    j = rb + 1
                    out.append((i, j))
                else:
                    break
            i = j
            continue
        i += 1
    out = [(s, e) for s, e in out if not is_target(ctx, s, e)]
    # ((T *)chain) groups
    for i in range(a, b):
        if S[i].text == "(" and i + 1 < b and S[i + 1].text == "(" and src.pair[i] < b:
            rp = src.pair[i]
            e = parse_expr(fn, i + 1, rp)
            if e is not None and e.kind == "cast" and e.kids[0].kind in ("member", "index", "prim"):
                out.append((i, rp + 1))
    return out


def is_target(ctx, s, e):
    """The chain at s..e is written (an assignment target, ++/-- operand) or has its address taken."""
    S = ctx.S
    after = S[e].text if e < len(S) else ""
    before = S[s - 1].text if s > 0 else ""
    if after in ASSIGN_OPS or after in ("++", "--") or before in ("++", "--"):
        return True
    return before == "&" and ctx.fn.is_unary(s - 1)


def occurrences(ctx, key, a, b):
    """Token starts of the chains in a..b whose normalised text is `key`."""
    return [(s, e) for s, e in chains(ctx, a, b) if norm(ctx.src.span(s, e)) == key]


def innermost_item(ctx, idx):
    best = None
    for blk in ctx.blocks():
        if blk.s < idx < blk.e - 1:
            for it in blk.items:
                if it.s <= idx < it.e and (best is None or it.s >= best.s and it.e <= best.e):
                    best = it
    return best


def dead_at(ctx, name, item, start_tok):
    """True when `name` is not read from token `start_tok` on before being written again, and no loop
    around `item` mentions it (its value would cross an iteration)."""
    fn, S = ctx.fn, ctx.S
    for lp in ctx.loops_around(item):
        if ident_uses(fn, name, lp.s, lp.e):
            return False
    uses = [u for u in ident_uses(fn, name) if u >= start_tok]
    for u in uses:
        # a plain `name = ...` write (not `name == ...`)
        if S[u + 1].text == "=" and (S[u - 1].text in (";", "{", "}", ")") or S[u - 1].text == "("):
            rhs_end = ctx.fn.end_of(u)
            if not ident_uses(fn, name, u + 2, rhs_end):
                return True
        return False
    return True


def type_ok(ctx, want, got):
    if want is None or got is None:
        # C++ refuses a pointer assignment between unrelated types; C, and any scalar, converts silently
        return ctx.cxx and want is not None and want[1] > 0 and got is None
    return (ctx.types.canon(want[0]), want[1]) == (ctx.types.canon(got[0]), got[1])


def m5_reuse_local(ctx):
    fn, S, src, fx = ctx.fn, ctx.S, ctx.src, ctx.fx
    all_chains = chains(ctx, fn.lb + 1, fn.rb)
    counts = {}
    for s, e in all_chains:
        counts.setdefault(norm(src.span(s, e)), []).append((s, e))
    local_names = [n for n in list(fn.locals) + fn.param_names if fx.is_local(n)]
    seen = set()
    for key, occ in sorted(counts.items()):
        if len(occ) < 2:
            continue
        s0, e0 = occ[0]
        expr = parse_expr(fn, s0, e0)
        if expr is None or not expr_pure(fn, expr):
            continue
        ety = infer(fn, ctx.types, expr)
        bases = {S[k].text for k in range(s0, e0) if S[k].kind == "ident" and not S[k - 1].text in (".", "->")}
        for s, e in occ:
            item = innermost_item(ctx, s)
            if item is None or item.kind in ("while", "do", "for") or \
                    item.kind == "decl" and any(dc.name in bases for dc in item.decls):
                continue
            if (key, item.s) in seen:
                continue
            seen.add((key, item.s))
            region_occ = [o for o in occurrences(ctx, key, item.s, item.e)]
            for l in local_names:
                if l in bases:
                    continue
                d = fn.locals.get(l)
                if d is not None and d[0].s >= item.s:
                    continue
                lt = fn.local_type(l)
                if not type_ok(ctx, lt, ety):
                    continue
                if not dead_at(ctx, l, item, item.s):
                    continue
                if fx.node(item)[1] & {l}:
                    pass
                edits = [ctx.insert_before(item, "%s = %s;" % (l, src.span(s0, e0)))]
                edits += [(src.cs(a), src.ce(b), l) for a, b in region_occ]
                if any(a < b2 and a2 < b for (a, b) in region_occ for (a2, b2) in region_occ if (a, b) != (a2, b2)):
                    continue
                if ctx.fn.src.sig and isinstance(item.parent, Node) and item.parent.kind != "block":
                    continue
                yield "5 reuse %s = %s" % (l, key), src.edit(edits)


def m6_temporaries(ctx):
    fn, S, src, fx = ctx.fn, ctx.S, ctx.src, ctx.fx
    # introduce
    seen = set()
    for s, e in chains(ctx, fn.lb + 1, fn.rb):
        key = norm(src.span(s, e))
        item = innermost_item(ctx, s)
        if item is None or item.kind in ("decl", "while", "do", "for") or (key, item.s) in seen:
            continue
        if item.parent is None or item.parent.kind != "block":
            continue
        seen.add((key, item.s))
        expr = parse_expr(fn, s, e)
        if expr is None or not expr_pure(fn, expr):
            continue
        ty = infer(fn, ctx.types, expr)
        if ty is None:
            continue
        occ = occurrences(ctx, key, item.s, item.e)
        if any(a < b2 and a2 < b for (a, b) in occ for (a2, b2) in occ if (a, b) != (a2, b2)):
            continue
        name = ctx.fresh("t")
        body = fn.body
        end = lead_decl_end(body)
        ind = src.indent_at(src.cs(body.items[0].s)) if body.items else "    "
        decl = "%s %s%s;" % (ty[0], "*" * ty[1], name) if ty[1] else "%s %s;" % (ty[0], name)
        if end:
            pos = src.ce(body.items[end - 1].e)
            dedit = (pos, pos, "\n" + ind + decl)
        else:
            pos = src.cs(body.items[0].s)
            dedit = (pos, pos, decl + "\n" + ind)
        if body.items and item is body.items[0] and not end:
            continue
        edits = [dedit, ctx.insert_before(item, "%s = %s;" % (name, src.span(s, e)))]
        edits += [(src.cs(a), src.ce(b), name) for a, b in occ]
        try:
            yield "6 temp %s = %s" % (name, key), src.edit(edits)
        except ParseError:
            continue
    # inline a single-use temporary
    for name, (d, dc) in list(fn.locals.items()):
        if not fx.is_local(name) or d.storage:
            continue
        uses = [u for u in ident_uses(fn, name) if not (d.s <= u < d.e)]
        writes = []
        reads = []
        for u in uses:
            if S[u + 1].text == "=" and S[u - 1].text in (";", "{", "}"):
                writes.append(u)
            else:
                reads.append(u)
        if dc.eq is not None:
            if writes or len(reads) != 1 or len(d.decls) != 1:
                continue
            ra, rb = dc.eq + 1, dc.e
            wnode = d
        else:
            if len(writes) != 1 or len(reads) != 1:
                continue
            wnode = innermost_item(ctx, writes[0])
            if wnode is None or wnode.kind != "expr" or wnode.s != writes[0]:
                continue
            ra, rb = writes[0] + 2, wnode.e - 1
        r = reads[0]
        if r < wnode.e:
            continue
        expr = parse_expr(fn, ra, rb)
        if expr is None or not expr_pure(fn, expr):
            continue
        rnode = innermost_item(ctx, r)
        if rnode is None or rnode.parent is not wnode.parent:
            continue
        blk = wnode.parent
        if blk is None or blk.kind != "block":
            continue
        ia, ib = blk.items.index(wnode), blk.items.index(rnode)
        Rr, Wr = fx.of(ra, rb)
        between = blk.items[ia + 1:ib]
        if any(has_control(fn, o) for o in between):
            continue
        if any((fx.node(o)[1] & Rr) for o in between):
            continue
        # inside the reading statement, the use must come before any write it holds
        Rb, Wb = fx.of(rnode.s, r, pending=True)
        if Wb & Rr:
            continue
        rhs = src.span(ra, rb)
        if expr.prec(S) < 15:
            rhs = "(%s)" % rhs
        edits = [(src.cs(r), src.ce(r + 1), rhs)]
        if dc.eq is not None:
            edits.append(ctx.remove(d))
        else:
            edits.append(ctx.remove(wnode))
            if len(d.decls) == 1:
                edits.append(ctx.remove(d))
            else:
                idx = d.decls.index(dc)
                if idx + 1 < len(d.decls):
                    edits.append((src.cs(dc.s), src.cs(d.decls[idx + 1].s), ""))
                else:
                    edits.append((src.ce(d.decls[idx - 1].e), src.ce(dc.e), ""))
        try:
            yield "6 inline %s" % name, src.edit(edits)
        except ParseError:
            continue


def flatten(S, e, prec):
    if e.kind == "bin" and BIN[S[e.op].text] == prec:
        l_ops, l_terms = flatten(S, e.kids[0], prec)
        return l_ops + [e.op], l_terms + [e.kids[1]]
    return [], [e]


def m7_split_merge(ctx):
    fn, S, src, fx = ctx.fn, ctx.S, ctx.src, ctx.fx
    for blk in ctx.blocks():
        for k, it in enumerate(blk.items):
            asg = assignment_of(ctx, it)
            if asg is None:
                continue
            name, ra, rb, form = asg
            rhs = parse_expr(fn, ra, rb)
            if rhs is None or rhs.kind != "bin" or S[rhs.op].text in ("&&", "||"):
                continue
            prec = BIN[S[rhs.op].text]
            if prec < 6 or prec in (9, 10):
                continue
            ops, terms = flatten(S, rhs, prec)
            for cut in range(1, len(terms)):
                rest_uses = any(ident_uses(fn, name, t.s, t.e) for t in terms[cut:])
                if rest_uses:
                    continue
                first = src.span(terms[0].s, terms[cut - 1].e)
                rest = src.span(ops[cut - 1] + 1, terms[-1].e)
                op = S[ops[cut - 1]].text
                head = "%s = %s;" % (name, first) if form == "expr" else None
                if form == "decl":
                    d = it
                    head = "%s %s = %s;" % (decl_spec_text(ctx, d), declarator_without_init(ctx, d.decls[0]), first)
                ind = src.indent_at(src.cs(it.s))
                for tail in ("%s = %s %s %s;" % (name, name, op, rest), "%s %s= %s;" % (name, op, rest)):
                    yield "7 split %s at %s" % (name, op), src.edit([ctx.replace_tokens(it.s, it.e,
                                                                                     head + "\n" + ind + tail)])
            continue
        for k in range(len(blk.items) - 1):
            a, b = blk.items[k], blk.items[k + 1]
            asg = assignment_of(ctx, a)
            if asg is None or b.kind != "expr":
                continue
            name, ra, rb, form = asg
            e = parse_expr(fn, *b.expr)
            if e is None or e.kind != "assign" or not (e.kids[0].kind == "prim" and S[e.kids[0].s].text == name):
                continue
            opx = S[e.op].text
            if opx == "=":
                r = e.kids[1]
                if r.kind != "bin" or not (r.kids[0].kind == "prim" and S[r.kids[0].s].text == name
                                           and r.kids[0].e - r.kids[0].s == 1):
                    continue
                op = S[r.op].text
                y = r.kids[1]
                ytext = src.span(y.s, y.e)
                yprec = y.prec(S)
            elif opx in ASSIGN_OPS:
                op = opx[:-1]
                y = e.kids[1]
                ytext = src.span(y.s, y.e)
                yprec = y.prec(S)
            else:
                continue
            if op not in BIN or ident_uses(fn, name, y.s, y.e):
                continue
            x = parse_expr(fn, ra, rb)
            if x is None:
                continue
            xtext = src.span(ra, rb)
            if x.prec(S) < BIN[op]:
                xtext = "(%s)" % xtext
            if yprec <= BIN[op]:
                ytext = "(%s)" % ytext
            merged = "%s %s %s" % (xtext, op, ytext)
            if form == "expr":
                new = "%s = %s;" % (name, merged)
            else:
                new = "%s %s = %s;" % (decl_spec_text(ctx, a), declarator_without_init(ctx, a.decls[0]), merged)
            yield "7 merge %s %s" % (name, op), src.edit([ctx.replace_tokens(a.s, a.e, new), ctx.remove(b)])


def wrap(text, e, S, need):
    return "(%s)" % text if e.prec(S) < need else text


def m8_operands(ctx):
    fn, S, src = ctx.fn, ctx.S, ctx.src
    for a, b, boolctx in expression_regions(fn):
        root = parse_expr(fn, a, b)
        if root is None:
            continue
        for e in root.walk():
            parent = e.parent
            in_bool = (parent is None and boolctx) or (
                parent is not None and (
                    (parent.kind == "bin" and S[parent.op].text in ("&&", "||"))
                    or (parent.kind == "unary" and S[parent.op].text == "!")
                    or (parent.kind == "cond" and parent.kids[0] is e)))
            txt = lambda x: src.span(x.s, x.e)
            if e.kind == "bin" and S[e.op].text in COMMUTATIVE and all(expr_pure(fn, k) for k in e.kids):
                op = S[e.op].text
                p = BIN[op]
                L, R = e.kids
                new = "%s %s %s" % (wrap(txt(R), R, S, p), op, wrap(txt(L), L, S, p + 1))
                yield "8 swap-operands %s" % op, src.edit([(src.cs(e.s), src.ce(e.e), new)])
            if e.kind == "bin" and S[e.op].text in ("==", "!="):
                L, R = e.kids
                zero = None
                if R.kind == "prim" and src.span(R.s, R.e) == "0":
                    zero = L
                elif L.kind == "prim" and src.span(L.s, L.e) == "0":
                    zero = R
                if zero is not None:
                    if S[e.op].text == "==":
                        new = "!" + wrap(txt(zero), zero, S, 15)
                        if parent is not None and parent.kind in ("bin",) and BIN[S[parent.op].text] > 9:
                            new = "(%s)" % new
                        yield "8 eq0-to-not", src.edit([(src.cs(e.s), src.ce(e.e), new)])
                    elif in_bool:
                        new = txt(zero)
                        if parent is not None and parent.kind == "unary":
                            new = wrap(new, zero, S, 15)
                        else:
                            new = wrap(new, zero, S, 6)
                        yield "8 ne0-to-bare", src.edit([(src.cs(e.s), src.ce(e.e), new)])
            if e.kind == "unary" and S[e.op].text == "!":
                x = e.kids[0]
                if x.kind == "unary" and S[x.op].text == "!":
                    continue
                new = "%s == 0" % wrap(txt(x), x, S, 10)
                if parent is not None and not in_bool and parent.kind not in ("assign", "paren", "call", "comma") \
                        or (parent is not None and parent.kind == "unary"):
                    new = "(%s)" % new
                yield "8 not-to-eq0", src.edit([(src.cs(e.s), src.ce(e.e), new)])
            if in_bool and not (e.kind == "bin" and S[e.op].text in ("==", "!=", "<", ">", "<=", ">=", "&&", "||")) \
                    and not (e.kind == "unary" and S[e.op].text == "!") and e.kind != "paren" \
                    and not (e.kind == "prim" and S[e.s].kind == "number"):
                new = "%s != 0" % wrap(txt(e), e, S, 10)
                if parent is not None and (parent.kind == "unary" or parent.kind == "bin"):
                    new = "(%s)" % new
                yield "8 bare-to-ne0", src.edit([(src.cs(e.s), src.ce(e.e), new)])


def has_own_continue(ctx, loop):
    """A `continue` that belongs to this loop (not to a loop nested in it)."""
    for n in loop.body.walk():
        if n.kind == "jump" and n.what == "continue":
            p = n.parent
            while p is not None and p is not loop and p.kind not in ("while", "do", "for"):
                p = p.parent
            if p is loop:
                return True
    return False


def has_own_break(ctx, loop):
    for n in loop.body.walk():
        if n.kind == "jump" and n.what == "break":
            p = n.parent
            while p is not None and p is not loop and p.kind not in ("while", "do", "for", "switch"):
                p = p.parent
            if p is loop:
                return True
    return False


def body_parts(ctx, body):
    """(open, inner text, close) of a loop body, braces added when it is a single statement."""
    src = ctx.src
    if body.kind == "block":
        if not body.items:
            return None
        return src.span(body.items[0].s, body.items[-1].e), src.indent_at(src.cs(body.items[0].s))
    return ctx.text_of(body), src.indent_at(src.cs(body.s)) + "    "


def m9_loops(ctx):
    fn, S, src, fx = ctx.fn, ctx.S, ctx.src, ctx.fx
    for blk in ctx.blocks():
        items = blk.items
        for k, loop in enumerate(items):
            ind = src.indent_at(src.cs(loop.s))
            # while -> for, taking the last body statement as the step and an earlier assignment as the init
            if loop.kind == "while" and loop.body.kind == "block" and len(loop.body.items) >= 2 \
                    and not has_own_continue(ctx, loop):
                step = loop.body.items[-1]
                if step.kind == "expr":
                    Rs, Ws = fx.node(step)
                    wnames = Ws - {"MEM"}
                    cond_names = fx.of(*loop.cond)[0]
                    if len(wnames) == 1 and (wnames & cond_names) and "MEM" not in Ws:
                        var = next(iter(wnames))
                        cond = src.span(*loop.cond)
                        steptext = src.span(step.s, step.e - 1)
                        rest = body_parts(ctx, Node("block", loop.body.s, loop.body.e, items=loop.body.items[:-1]))
                        inner = rest[0]
                        brace_end = src.ce(loop.body.e)
                        new_head = "for (%%s; %s; %s) {\n%s%s\n%s}" % (cond, steptext, rest[1], inner, ind)
                        yield "9 while-to-for %s" % var, src.edit([ctx.replace_tokens(loop.s, loop.e, new_head % "")])
                        for j in range(k - 1, max(-1, k - 7), -1):
                            asg = assignment_of(ctx, items[j])
                            if asg is not None and asg[0] == var:
                                between = items[j + 1:k]
                                if all(swappable(ctx, o) and not ident_uses(fn, var, o.s, o.e)
                                       and not (fx.node(o)[1] & fx.of(asg[1], asg[2])[0])
                                       for o in between):
                                    init = "%s = %s" % (var, src.span(asg[1], asg[2]))
                                    edits = [ctx.replace_tokens(loop.s, loop.e, new_head % init)]
                                    if asg[3] == "decl":
                                        d = items[j]
                                        edits.append(ctx.replace_tokens(d.s, d.e, "%s %s;" % (
                                            decl_spec_text(ctx, d), declarator_without_init(ctx, d.decls[0]))))
                                    else:
                                        edits.append(ctx.remove(items[j]))
                                    yield "9 while-to-for+init %s" % var, src.edit(edits)
                                break
                            if not swappable(ctx, items[j]):
                                break
            # for -> while
            if loop.kind == "for" and not has_own_continue(ctx, loop) and loop.for_decl is None:
                init = src.span(*loop.init)
                cond = src.span(*loop.cond) or "1"
                step = src.span(*loop.step)
                parts = body_parts(ctx, loop.body)
                if parts is not None:
                    inner, bind = parts
                    tail = ("\n%s%s;" % (bind, step)) if step else ""
                    new = ("%s;\n%s" % (init, ind) if init else "") + \
                        "while (%s) {\n%s%s%s\n%s}" % (cond, bind, inner, tail, ind)
                    yield "9 for-to-while", src.edit([ctx.replace_tokens(loop.s, loop.e, new)])
                    if loop.cond[1] > loop.cond[0]:
                        new = ("%s;\n%s" % (init, ind) if init else "") + \
                            "if (%s) do {\n%s%s%s\n%s} while (%s);" % (cond, bind, inner, tail, ind, cond)
                        yield "9 for-to-guarded-do", src.edit([ctx.replace_tokens(loop.s, loop.e, new)])
                        if not has_own_break(ctx, loop) and k + 1 < len(items):
                            top, test = ctx.fresh("loop"), ctx.fresh("test")
                            if test == top:
                                test = top + "_test"
                            new = ("%s;\n%s" % (init, ind) if init else "") + \
                                "goto %s;\n%s%s:\n%s%s%s\n%s%s:\n%sif (%s) goto %s;" % (
                                    test, ind, top, bind, inner, tail, ind, test, ind, cond, top)
                            yield "9 for-to-goto", src.edit([ctx.replace_tokens(loop.s, loop.e, new)])
                # init out of the for head
                if init:
                    new = "%s;\n%sfor (; %s" % (init, ind, src.span(loop.init[1] + 1, loop.body.e))
                    yield "9 for-init-out", src.edit([ctx.replace_tokens(loop.s, loop.e, new)])
            # `x = e; for (; ...)` -> `for (x = e; ...)`
            if loop.kind == "for" and loop.init[1] == loop.init[0] and k > 0:
                asg = assignment_of(ctx, items[k - 1])
                if asg is not None and asg[3] == "expr":
                    new = "for (%s = %s%s" % (asg[0], src.span(asg[1], asg[2]), src.span(loop.init[1], loop.e))
                    yield "9 for-init-in", src.edit([ctx.remove(items[k - 1]),
                                                     ctx.replace_tokens(loop.s, loop.e, new)])
            # while -> guarded do-while, and back
            if loop.kind == "while":
                cond = src.span(*loop.cond)
                new = "if (%s) do %s while (%s);" % (cond, ctx.text_of(loop.body), cond)
                yield "9 while-to-guarded-do", src.edit([ctx.replace_tokens(loop.s, loop.e, new)])
            if loop.kind == "if" and loop.els is None:
                inner = loop.then
                if inner.kind == "block" and len(inner.items) == 1:
                    inner = inner.items[0]
                if inner.kind == "do" and norm(src.span(*inner.cond)) == norm(src.span(*loop.cond)):
                    new = "while (%s) %s" % (src.span(*loop.cond), ctx.text_of(inner.body))
                    yield "9 guarded-do-to-while", src.edit([ctx.replace_tokens(loop.s, loop.e, new)])


def free_locals(ctx, a, b):
    fn, S = ctx.fn, ctx.S
    out = []
    for i in range(a, b):
        t = S[i]
        if t.kind == "ident" and not (i > 0 and S[i - 1].text in (".", "->", "::")) and \
                (t.text in fn.locals or t.text in fn.param_names) and t.text not in out:
            out.append(t.text)
    return out


def helper_ok(ctx, a, b):
    S = ctx.S
    for i in range(a, b):
        if S[i].text in ("this", "&", "++", "--", "return", "break", "continue", "goto") or S[i].text in ASSIGN_OPS:
            if S[i].text == "&" and not ctx.fn.is_unary(i):
                continue
            return False
    return True


def m10_inline_helper(ctx):
    fn, S, src = ctx.fn, ctx.S, ctx.src
    pos = fn.start_char
    def make(rt, args, body):
        name = ctx.fresh("sweep_part")
        params = []
        for v in args:
            ty = fn.local_type_text(v)
            if ty is None:
                return None
            params.append("%s%s%s" % (ty, "" if ty.endswith("*") or ty.endswith("&") else " ", v))
        helper = "static inline %s%s%s(%s) {\n    %s\n}\n\n" % (
            rt, "" if rt.endswith("*") else " ", name, ", ".join(params) or "void", body)
        return name, helper
    for n in fn.body.walk():
        target = None
        if n.kind == "decl" and len(n.decls) == 1 and n.decls[0].eq is not None and not n.storage:
            dc = n.decls[0]
            if dc.name_idx is not None and S[dc.name_idx + 1].text == "=":
                target = (dc.eq + 1, dc.e, fn.local_type_text(dc.name))
        elif n.kind == "expr":
            e = parse_expr(fn, *n.expr)
            if e is not None and e.kind == "assign" and S[e.op].text == "=" and e.kids[0].kind == "prim":
                target = (e.kids[1].s, e.kids[1].e, fn.local_type_text(S[e.kids[0].s].text))
        elif n.kind == "return" and n.expr[1] > n.expr[0]:
            rt = fn.return_type()
            target = (n.expr[0], n.expr[1], rt if rt and rt != "void" else None)
        if target is not None and target[2]:
            a, b, rt = target
            e = parse_expr(fn, a, b)
            if e is not None and e.kind in ("cond", "bin", "call", "unary", "cast") and helper_ok(ctx, a, b):
                if e.kind == "call" and all(k.kind == "prim" for k in e.kids):
                    pass
                else:
                    made = make(rt, free_locals(ctx, a, b), "return %s;" % src.span(a, b))
                    if made:
                        name, helper = made
                        call = "%s(%s)" % (name, ", ".join(free_locals(ctx, a, b)))
                        yield "10 helper %s" % name, src.edit([(pos, pos, helper),
                                                               (src.cs(a), src.ce(b), call)])
        # if/else chain assigning one local, or returning in every branch
        if n.kind == "if" and n.els is not None and n.parent is not None and \
                (n.parent.kind == "block" or n.parent.kind not in ("if",)):
            arms, conds, cur, ok, var = [], [], n, True, None
            mode = None
            while ok:
                arm = cur.then
                if arm.kind == "block" and len(arm.items) == 1:
                    arm = arm.items[0]
                conds.append(cur.cond)
                arms.append(arm)
                nxt = cur.els
                if nxt is None:
                    ok = False
                    break
                if nxt.kind == "if":
                    cur = nxt
                    continue
                if nxt.kind == "block" and len(nxt.items) == 1:
                    nxt = nxt.items[0]
                arms.append(nxt)
                break
            if not ok or len(arms) != len(conds) + 1:
                continue
            values = []
            for arm in arms:
                if arm.kind == "return" and arm.expr[1] > arm.expr[0] and mode in (None, "return"):
                    mode = "return"
                    values.append(arm.expr)
                elif arm.kind == "expr" and mode in (None, "assign"):
                    e = parse_expr(fn, *arm.expr)
                    if e is None or e.kind != "assign" or S[e.op].text != "=" or e.kids[0].kind != "prim":
                        values = None
                        break
                    v = S[e.kids[0].s].text
                    if var not in (None, v):
                        values = None
                        break
                    var, mode = v, "assign"
                    values.append((e.kids[1].s, e.kids[1].e))
                else:
                    values = None
                    break
            if not values:
                continue
            rt = fn.local_type_text(var) if mode == "assign" else fn.return_type()
            if not rt or rt == "void":
                continue
            spans = list(conds) + values
            if not all(helper_ok(ctx, a, b) for a, b in spans):
                continue
            args = []
            for a, b in spans:
                for v in free_locals(ctx, a, b):
                    if v not in args:
                        args.append(v)
            lines = []
            for i, (c, v) in enumerate(zip(conds, values)):
                lines.append("%sif (%s) return %s;" % ("" if i == 0 else "else ", src.span(*c), src.span(*v)))
            lines.append("else return %s;" % src.span(*values[-1]))
            made = make(rt, args, "\n    ".join(lines))
            if not made:
                continue
            name, helper = made
            call = "%s(%s)" % (name, ", ".join(args))
            stmt = ("%s = %s;" % (var, call)) if mode == "assign" else "return %s;" % call
            yield "10 helper-if %s" % name, src.edit([(pos, pos, helper), ctx.replace_tokens(n.s, n.e, stmt)])


MOVES = {1: m1_decl_order, 2: m2_decl_scope, 3: m3_swap, 4: m4_assign_into_test, 5: m5_reuse_local,
         6: m6_temporaries, 7: m7_split_merge, 8: m8_operands, 9: m9_loops, 10: m10_inline_helper}


def generate(text, name, types, cxx, moves=None):
    """[(label, new_text)] for every move of `text`, in a fixed order; [] when the function does not parse."""
    try:
        ctx = Ctx(text, name, types, cxx)
    except (ParseError, IndexError, KeyError):
        return []
    out = []
    for num in sorted(moves or MOVES):
        try:
            for label, new in MOVES[num](ctx):
                if new != text:
                    out.append((label, new))
        except (ParseError, IndexError, KeyError, ValueError):
            continue
    return out


# ---------------------------------------------------------------- honesty


def function_facts(text, name, types, cxx):
    """The counts the honesty filter compares, for the function and the helpers it calls."""
    src = Source(text)
    fns = [Function(src, name, types.names, cxx)]
    called = {t.text for t in src.sig[fns[0].lb:fns[0].rb] if t.kind == "ident"}
    for helper in sorted(set(re.findall(r"\bstatic\s+inline\s+[^;{()]*?\b(sweep_part\d+)\s*\(", text))):
        if helper in called:
            try:
                fns.append(Function(src, helper, types.names, cxx))
            except ParseError:
                pass
    facts = {"volatile": 0, "asm": 0, "address_of": {}, "pun_cast": 0, "do_while0": 0, "empty_if": 0,
             "empty_block": 0, "no_effect": 0, "unused_locals": {}, "mixed_decls": 0}
    for fn in fns:
        S = fn.src.sig
        for i in range(fn.lp, fn.rb):
            t = S[i].text
            if t == "volatile":
                facts["volatile"] += 1
            if t in ("asm", "__asm__", "__asm"):
                facts["asm"] += 1
            if t == "&" and fn.is_unary(i) and i > fn.lb:
                j = i + 1
                while j < fn.rb and (S[j].kind == "ident" or S[j].text in (".", "->", "::")):
                    j += 1
                key = " ".join(x.text for x in S[i + 1:j]) or S[i + 1].text
                facts["address_of"][key] = facts["address_of"].get(key, 0) + 1
            # *(T *)&x
            if t == "*" and fn.is_unary(i) and S[i + 1].text == "(":
                rp = fn.src.pair.get(i + 1)
                if rp and rp > i + 2 and S[rp - 1].text == "*" and rp + 1 < len(S) and S[rp + 1].text == "&":
                    facts["pun_cast"] += 1
        for n in fn.body.walk():
            if n.kind == "do" and norm(fn.src.span(*n.cond)) in ("0", "0 ) ;"):
                facts["do_while0"] += 1
            if n.kind == "if":
                for arm in (n.then, n.els):
                    if arm is not None and (arm.kind == "empty" or (arm.kind == "block" and not arm.items)):
                        facts["empty_if"] += 1
            if n.kind == "block" and n is not fn.body and not n.items and not (
                    n.parent is not None and n.parent.kind == "if"):
                facts["empty_block"] += 1
            if n.kind == "empty":
                facts["no_effect"] += 1
            if n.kind == "expr":
                a, b = n.expr
                eff = any(S[k].text in ASSIGN_OPS or S[k].text in ("++", "--", "new", "delete", "throw")
                          for k in range(a, b))
                eff = eff or any(S[k].text == "(" and k > a and (S[k - 1].kind == "ident" or S[k - 1].text in (")", ">"))
                                 and S[k - 1].text not in KEYWORDS and S[k - 1].text not in fn.types
                                 for k in range(a, b))
                if not eff:
                    facts["no_effect"] += 1
        names = dict(fn.locals)
        for nm, (d, dc) in names.items():
            reads = 0
            for u in ident_uses(fn, nm):
                if d.s <= u < d.e and u == dc.name_idx:
                    continue
                if S[u + 1].text == "=" and S[u - 1].text in (";", "{", "}", ",", "("):
                    continue
                reads += 1
            if reads == 0:
                key = fn.name + ":" + nm
                facts["unused_locals"][key] = 1
        for p_ty, p_nm, _ in fn.params:
            if p_nm and fn.name.startswith("sweep_part") and not ident_uses(fn, p_nm):
                facts["unused_locals"][fn.name + ":" + p_nm] = 1
        if not cxx:
            for blk in fn.body.walk():
                if blk.kind == "block":
                    seen_stmt = False
                    for it in blk.items:
                        if it.kind == "decl":
                            if seen_stmt:
                                facts["mixed_decls"] += 1
                        else:
                            seen_stmt = True
    return facts


def honesty(orig_facts, cand_text, name, types, cxx):
    """[] when the candidate adds none of the refused shapes, else the reasons."""
    try:
        f = function_facts(cand_text, name, types, cxx)
    except (ParseError, IndexError, KeyError):
        return ["does not parse"]
    why = []
    for k in ("volatile", "asm", "pun_cast", "do_while0", "empty_if", "empty_block", "no_effect"):
        if f[k] > orig_facts[k]:
            why.append(k)
    for key, n in f["address_of"].items():
        if n > orig_facts["address_of"].get(key, 0):
            why.append("address_of " + key)
    orig_unused = {k.split(":", 1)[1] for k in orig_facts["unused_locals"]}
    for key in f["unused_locals"]:
        if key.split(":", 1)[1] not in orig_unused:
            why.append("unused_local " + key)
    if f["mixed_decls"] > orig_facts["mixed_decls"]:
        why.append("declaration after statement (C89)")
    return why


# ---------------------------------------------------------------- scoring

SIZE_PENALTY = 20
WORD_LINE = re.compile(r"^\s*(?:!!)?\s*(?:[\w ]*?\s)?\[\s*\d+\]\s+retail\s+[0-9a-f]+", re.M)
SIZE_LINE = re.compile(r"size: retail (\d+), ours (\d+)")
EXTENT_LINE = re.compile(r"object symbol (\d+) bytes in a section of \d+, retail (\d+)")


def score_report(report):
    """The search score of a verify report: 0 for MATCH, None when it does not compile."""
    head = report.split("\n", 1)[0]
    if head.startswith("MATCH"):
        return 0
    if head.startswith("compile failed") or "compile failed" in head:
        return None
    n = len(WORD_LINE.findall(report))
    for m in SIZE_LINE.finditer(report):
        n += SIZE_PENALTY + abs(int(m.group(1)) - int(m.group(2))) // 4
    for m in EXTENT_LINE.finditer(report):
        n += SIZE_PENALTY + abs(int(m.group(1)) - int(m.group(2))) // 4
    return max(n, 1)


def find_repo(explicit=None):
    cands = [explicit, os.environ.get("DW4_DECOMP"), os.path.dirname(HERE)]
    p = HERE
    for _ in range(6):
        cands.append(os.path.join(p, "DW4_Decomp"))
        p = os.path.dirname(p)
    for c in cands:
        if c and os.path.isfile(os.path.join(c, "tools", "check.py")) and os.path.isfile(
                os.path.join(c, "tools", "verify.py")):
            return os.path.abspath(c)
    raise SystemExit("cxx_sweep: cannot find the DW4_Decomp repository (pass --repo)")


def config_files(config):
    out = {}
    for key, fname in (("symbols", "symbols.txt"), ("units", "units.tsv"), ("unit_objects", "unit-objects.json"),
                       ("unit_flags", "unit-flags.tsv"), ("unit_compilers", "unit-compilers.tsv")):
        p = os.path.join(config, fname)
        out[key] = p if os.path.exists(p) else None
    return out


class CheckScorer:
    """tools/check.py --function semantics, in-process (verify.verify_one on units.standalone)."""

    def __init__(self, repo, va, name, config):
        sys.path.insert(0, os.path.join(repo, "tools"))
        import check
        import units
        import verify
        self.check, self.units, self.verify = check, units, verify
        self.va, self.name = va, name
        self.cfg = config_files(config)

    def __call__(self, path):
        c = self.cfg
        src, tmp = self.units.standalone(path, self.name, symbols=c["symbols"], unit_objects=c["unit_objects"])
        try:
            ok, report = self.verify.verify_one(
                self.va, src, flags=self.check.FLAGS_DEFAULT, elf=self.check.ELF_DEFAULT, symbols=c["symbols"],
                mwcc=self.check.MWCC_DEFAULT, wibo=self.check.WIBO_DEFAULT, unit_flags=c["unit_flags"],
                unit_compilers=c["unit_compilers"], unit_objects=c["unit_objects"], units=c["units"])
        except Exception as error:      # a verifier exception is a failed candidate, never a dead sweep
            return None, "error: %s" % error
        finally:
            if tmp and os.path.exists(tmp):
                os.remove(tmp)
        return score_report(report), report


class WholeFileScorer:
    """Compile the whole file under the unit profile (tools/cc.py, as tools/whole_file_rows.py does) and
    count the words of one function's body that differ from retail, relocated fields masked."""

    def __init__(self, repo, va, name, config, object_symbol=None):
        sys.path.insert(0, os.path.join(repo, "tools"))
        import cc
        import check
        import unitprofiles
        import verify
        import whole_file_rows
        self.cc, self.verify, self.wfr = cc, verify, whole_file_rows
        self.repo, self.va, self.name, self.object_symbol = repo, va, name, object_symbol
        c = config_files(config)
        res = unitprofiles.resolve(va, check.FLAGS_DEFAULT, check.MWCC_DEFAULT, units=c["units"],
                                   unit_flags=c["unit_flags"], unit_compilers=c["unit_compilers"],
                                   symbols=c["symbols"])
        self.profile = res.profile
        self.flags = unitprofiles.command_flags(res.profile)
        self.wibo = check.WIBO_DEFAULT
        self.retail = whole_file_rows.Retail(check.ELF_DEFAULT)
        by_name, by_va = verify.load_symbols(c["symbols"])
        self.size = by_va[va][1]

    def pick(self, functions):
        if self.object_symbol:
            return functions.get(self.object_symbol)
        if self.name in functions:
            return functions[self.name]
        plain = self.name.split("__")[-1]
        cands = [f for n, f in functions.items() if n.startswith(plain + "__") or n == plain]
        if not cands:
            cands = list(functions.values())
        best, best_d = None, None
        for f in cands:
            d = self.diff(f)
            if best_d is None or d < best_d:
                best, best_d = f, d
        return best

    def diff(self, f):
        n = 0
        words = len(f.words)
        want = self.size // 4
        for i in range(min(words, want)):
            if (self.retail.word(self.va + 4 * i) ^ f.words[i]) & f.masks[i]:
                n += 1
        if words != want:
            n += SIZE_PENALTY + abs(words - want)
        return n

    def __call__(self, path):
        obj = os.path.join(self.cc.scratch_dir(), "wf_%d_%d.o" % (os.getpid(), threading.get_ident()))
        if os.path.exists(obj):
            os.remove(obj)
        argv = self.cc.compile_argv(self.wibo, self.profile.compiler, self.flags, path, obj)
        env = dict(os.environ, MWCIncludes=os.path.dirname(os.path.abspath(path)))
        done = subprocess.run(argv, cwd=self.repo, capture_output=True, text=True, env=env)
        if not os.path.exists(obj):
            return None, "compile failed: " + (done.stdout + done.stderr)[-400:]
        try:
            _syms, _headers, functions = self.wfr.text_functions(obj)
            f = self.pick(functions)
            if f is None:
                return None, "function not in the object"
            d = self.diff(f)
            return d, "%s %s: %d words differ (masked), %d/%d words" % (
                "MATCH" if d == 0 else "DIFFER", f.name, d, len(f.words), self.size // 4)
        finally:
            if os.path.exists(obj):
                os.remove(obj)


# ---------------------------------------------------------------- search


class State:
    __slots__ = ("text", "score", "moves", "key", "serial")

    def __init__(self, text, score, moves, key, serial):
        self.text, self.score, self.moves, self.key, self.serial = text, score, moves, key, serial


class Sweep:
    def __init__(self, text, name, types, cxx, scorer, work, ext, jobs=4, beam=4, seed=0, budget=600,
                 max_evals=0, keep=10, max_neighbors=150, patience=3, moves=None, log=None):
        self.text0, self.name, self.types, self.cxx = text, name, types, cxx
        self.scorer, self.work, self.ext = scorer, work, ext
        self.jobs, self.beam, self.rng = jobs, beam, random.Random(seed)
        self.budget, self.max_evals, self.keep = budget, max_evals, keep
        self.max_neighbors, self.patience, self.moves = max_neighbors, patience, moves
        self.log = log or (lambda s: None)
        self.facts0 = function_facts(text, name, types, cxx)
        self.seen = {}
        self.states = []
        self.expanded = set()
        self.evals = 0
        self.rejected = 0
        self.failed = 0
        self.serial = itertools.count()
        self.lock = threading.Lock()
        self.t0 = time.time()

    def elapsed(self):
        return time.time() - self.t0

    def out_of_budget(self):
        return (self.budget and self.elapsed() > self.budget) or (self.max_evals and self.evals >= self.max_evals)

    def score_texts(self, texts):
        def one(arg):
            k, text = arg
            path = os.path.join(self.work, "c%d_%d%s" % (os.getpid(), k, self.ext))
            with open(path, "w") as fh:
                fh.write(text)
            try:
                return self.scorer(path)
            finally:
                if os.path.exists(path):
                    os.remove(path)
        base = next(self.serial) * 100000
        with concurrent.futures.ThreadPoolExecutor(max_workers=max(1, self.jobs)) as ex:
            return list(ex.map(one, [(base + i, t) for i, t in enumerate(texts)]))

    def neighbours(self, state):
        """The honest, not yet scored candidates one move from `state` (a refused one is remembered)."""
        out, dupes = [], set()
        for label, text in generate(state.text, self.name, self.types, self.cxx, self.moves):
            key = norm(text)
            if key in self.seen:
                continue
            if key in dupes:
                continue
            dupes.add(key)
            why = honesty(self.facts0, text, self.name, self.types, self.cxx)
            if why:
                self.rejected += 1
                self.seen[key] = None
                continue
            out.append((state.moves + [label], text, key))
        return out

    def add(self, text, score, moves, key):
        st = State(text, score, moves, key, next(self.serial))
        self.seen[key] = st
        self.states.append(st)
        return st

    def ranked(self):
        return sorted((s for s in self.states if s.score is not None), key=lambda s: (s.score, len(s.moves), s.serial))

    def run(self):
        key0 = norm(self.text0)
        (s0, report0), = self.score_texts([self.text0])
        self.evals += 1
        if s0 is None:
            raise SystemExit("cxx_sweep: the input does not score: %s" % report0.splitlines()[0] if report0 else "")
        root = self.add(self.text0, s0, [], key0)
        self.start_score = s0
        self.start_report = report0
        best = root
        self.log("start score %d  (%s)" % (s0, report0.split("\n", 1)[0]))
        stale = 0
        forced = []
        while best.score > 0 and not self.out_of_budget():
            pool = [s for s in self.ranked() if s.key not in self.expanded]
            pick = forced + [s for s in pool if s not in forced][:max(0, self.beam - len(forced))]
            forced = []
            if not pick:
                break
            batch, taken = [], set()
            for st in pick:
                self.expanded.add(st.key)
                ring = self.neighbours(st)
                ring = [r for r in ring if r[2] not in taken]
                if len(ring) > self.max_neighbors:
                    ring = self.rng.sample(ring, self.max_neighbors)
                    self.expanded.discard(st.key)      # the rest of its ring is drawn from later
                for r in ring:
                    taken.add(r[2])
                batch.extend(ring)
            if self.max_evals:
                batch = batch[:max(0, self.max_evals - self.evals)]
            if not batch:
                stale += 1
            else:
                results = self.score_texts([t for _, t, _ in batch])
                self.evals += len(batch)
                improved = False
                for (moves, text, key), (score, report) in zip(batch, results):
                    if score is None:
                        self.failed += 1
                        self.seen[key] = None
                        continue
                    st = self.add(text, score, moves, key)
                    if score < best.score:
                        best = st
                        improved = True
                        self.log("[%6.1fs %5d evals] score %d  <- %s" % (self.elapsed(), self.evals, score,
                                                                       " ; ".join(moves)))
                        if score == 0:
                            break
                stale = 0 if improved else stale + 1
            self.checkpoint()
            if stale >= self.patience and best.score > 0:
                stale = 0
                restart = self.restart()
                if restart is not None:
                    forced = [restart]
        self.best = best
        self.checkpoint()
        return best

    def restart(self):
        """A random walk of 1-3 honest moves from one of the best states, scored and expanded next."""
        top = self.ranked()[:max(1, self.keep)]
        st = self.rng.choice(top)
        text, moves = st.text, list(st.moves)
        for _ in range(self.rng.randint(1, 3)):
            ring = [(l, t) for l, t in generate(text, self.name, self.types, self.cxx, self.moves)
                    if not honesty(self.facts0, t, self.name, self.types, self.cxx)]
            if not ring:
                break
            label, text = self.rng.choice(ring)
            moves.append(label)
        key = norm(text)
        if key in self.seen and self.seen[key] is not None:
            return self.seen[key] if self.seen[key].key not in self.expanded else None
        (score, report), = self.score_texts([text])
        self.evals += 1
        if score is None:
            return None
        self.log("[%6.1fs %5d evals] restart at score %d <- %s" % (self.elapsed(), self.evals, score,
                                                                   " ; ".join(moves)))
        return self.add(text, score, moves, key)

    def checkpoint(self):
        pass


# ---------------------------------------------------------------- command line


def load_symbol(symbols, name=None, va=None):
    for ln in open(symbols):
        p = ln.split()
        if len(p) < 3 or ln.startswith("#"):
            continue
        v = int(p[0], 16)
        if (va is not None and v == va) or (va is None and (p[2] == name or (len(p) > 3 and p[3] == name))):
            return v, p[2]
    return None


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("source", help="candidate C or C++ file")
    ap.add_argument("function", help="the function to rewrite (its name in the source; Class::method works)")
    ap.add_argument("--va", help="retail address (default: the function's row in the config's symbols.txt)")
    ap.add_argument("--symbol", help="the symbols.txt name, when it differs from the source name")
    ap.add_argument("--config", help="config dir with symbols.txt, units.tsv, unit-*.tsv, unit-objects.json "
                                     "(default config/SLUS-20836 of the repository)")
    ap.add_argument("--whole-file", action="store_true",
                    help="score the function's body inside the whole file's object (masked words)")
    ap.add_argument("--object-symbol", help="the function's name in the object (whole-file mode)")
    ap.add_argument("--repo", help="the DW4_Decomp checkout (default: found from this script or DW4_DECOMP)")
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--beam", type=int, default=4, help="states expanded per round")
    ap.add_argument("--seed", type=int, default=0)
    ap.add_argument("--time", type=float, default=600, help="time budget in seconds (0 = none)")
    ap.add_argument("--max-evals", type=int, default=0, help="evaluation budget (0 = none)")
    ap.add_argument("--max-neighbors", type=int, default=150, help="candidates sampled per expanded state")
    ap.add_argument("--patience", type=int, default=3, help="rounds without progress before a random restart")
    ap.add_argument("--keep", type=int, default=10, help="best candidates kept on disk")
    ap.add_argument("--moves", help="comma-separated move numbers (default: all)")
    ap.add_argument("--out-dir", help="where the results go (default: beside the source)")
    ap.add_argument("--score-only", action="store_true", help="score the unchanged source and stop")
    ap.add_argument("--list-moves", action="store_true", help="print the first ring of candidates and stop")
    a = ap.parse_args(argv)

    source = os.path.abspath(a.source)
    out_dir = os.path.abspath(a.out_dir) if a.out_dir else os.path.dirname(source)
    repo = find_repo(a.repo)
    config = os.path.abspath(a.config) if a.config else os.path.join(repo, "config", "SLUS-20836")
    os.chdir(repo)
    text = open(source).read()
    stem, ext = os.path.splitext(os.path.basename(source))
    cxx = ext.lower() in (".cpp", ".cc", ".cxx", ".cp")
    inc = [os.path.dirname(source), os.path.join(repo, "include"), os.path.join(repo, "src")]
    types = Types(*collect_types(text, inc))
    moves = [int(x) for x in a.moves.split(",")] if a.moves else None

    if a.list_moves:
        facts = function_facts(text, a.function, types, cxx)
        for label, new in generate(text, a.function, types, cxx, moves):
            why = honesty(facts, new, a.function, types, cxx)
            print("%-60s %s" % (label[:60], "REFUSED " + ",".join(why) if why else "ok"))
        return 0

    symbols = os.path.join(config, "symbols.txt")
    hit = load_symbol(symbols, va=int(a.va, 0)) if a.va else load_symbol(symbols, name=a.symbol or a.function)
    if hit is None:
        raise SystemExit("cxx_sweep: %s is not in %s (pass --va)" % (a.va or a.function, symbols))
    va, symname = hit
    scorer = (WholeFileScorer(repo, va, symname, config, a.object_symbol) if a.whole_file
              else CheckScorer(repo, va, symname, config))

    work_abs = os.path.join(out_dir, stem + ".sweep", "work")
    os.makedirs(work_abs, exist_ok=True)
    work = os.path.relpath(work_abs, repo)
    if len(work) > 60:
        import tempfile
        work = tempfile.mkdtemp(prefix="sw")
    if a.score_only:
        path = os.path.join(work, "c0" + ext)
        with open(path, "w") as fh:
            fh.write(text)
        try:
            score, report = scorer(path)
        finally:
            os.remove(path)
        print(report)
        print("cxx_sweep: %s 0x%x score %s (%s mode)" % (a.function, va, score,
                                                        "whole-file" if a.whole_file else "function"))
        return 0 if score == 0 else 1

    log_path = os.path.join(out_dir, stem + ".sweep.log")
    logfh = open(log_path, "a")

    def log(line):
        logfh.write(line + "\n")
        logfh.flush()
        print(line, flush=True)

    log("== cxx_sweep %s %s 0x%x mode=%s seed=%d jobs=%d beam=%d time=%s config=%s" % (
        os.path.basename(source), a.function, va, "whole-file" if a.whole_file else "function", a.seed,
        a.jobs, a.beam, a.time, config))
    sweep = Sweep(text, a.function, types, cxx, scorer, work, ext, jobs=a.jobs, beam=a.beam, seed=a.seed,
                  budget=a.time, max_evals=a.max_evals, keep=a.keep, max_neighbors=a.max_neighbors,
                  patience=a.patience, moves=moves, log=log)
    keep_dir = os.path.join(out_dir, stem + ".sweep")

    def checkpoint():
        ranked = sweep.ranked()[:a.keep]
        for f in os.listdir(keep_dir):
            if re.match(r"^rank\d+\.", f):
                os.remove(os.path.join(keep_dir, f))
        index = []
        for r, st in enumerate(ranked, 1):
            fn = "rank%02d.%d%s" % (r, st.score, ext)
            with open(os.path.join(keep_dir, fn), "w") as fh:
                fh.write(st.text)
            index.append({"file": fn, "score": st.score, "moves": st.moves})
        with open(os.path.join(keep_dir, "best.json"), "w") as fh:
            json.dump(index, fh, indent=1)

    sweep.checkpoint = checkpoint
    best = sweep.run()
    out = os.path.join(out_dir, "%s.sweep.%d%s" % (stem, best.score, ext))
    with open(out, "w") as fh:
        fh.write(best.text)
    log("best score %d after %d moves: %s" % (best.score, len(best.moves), " ; ".join(best.moves) or "(none)"))
    summary = ("cxx_sweep: %s 0x%x start %d -> best %d in %d evals, %.0fs (%d refused, %d failed to compile); "
               "moves: %s -> %s" % (a.function, va, sweep.start_score, best.score, sweep.evals, sweep.elapsed(),
                                    sweep.rejected, sweep.failed, " ; ".join(best.moves) or "(none)",
                                    os.path.relpath(out)))
    log(summary)
    logfh.close()
    try:
        os.rmdir(work_abs)
    except OSError:
        pass
    return 0 if best.score == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
