#!/usr/bin/env python3
"""Measure typed coverage: how much of the decompiled C speaks in structs.

Byte-matching is the repo's outward oracle; this is the inward one. m2c's C reproduces
retail instruction-for-instruction while spelling every field as
`*(int *)((char *)p + 12)`, which satisfies the matching build and is useless to another
compiler on another machine. Two numbers come
out of here:

  * **typed** -- field accesses written as a member of a *recovered* class (one that
    `data/reflection.json`, `config/SLUS-20836/authoritative-fields.tsv` or the class hierarchy names)
    rather than an offset cast, a member of automatch's synthetic `struct G`, or a member of
    a type the metadata does not know. This is the progress bar and the gated count.
  * **typeable** -- of the offset casts that remain, the ones on the function's own receiver
    (`arg0`/`this`) at an offset where the receiver class -- taken from the function's
    `<Class>_<Method>` name, or the class of a member function -- has a reflected field. It is a
    *mechanically convertible subset* of the raw casts, not a ceiling: casts on other variables, on
    receivers the name does not reveal, or at unreflected offsets are convertible by hand and are not
    counted.

A member function -- written out of its class (`void igRenderer::setVisualContext(...) {`,
`igMetaObject *Gap::Gui::igRenderer::getMeta() const {`, a constructor `Gap::Core::igObject::igObject() {`), in a
namespace block, or in its class's body -- is a function of that class: its `this->x` and its bare reads of a
reflected field of the class or a base (`_visualContext`, `_pos.vec[1]`, `_pos.set(v)`) are recovered accesses, as
`self->x` is in the free function, unless a parameter or local of that name hides the field; so is a read through a
typed member of the class (`_visualContext->_mode`). A whole-vector operation on a typed field (`a->_pos += b`) is
one access.

A converted class's code reaches the fields the free-function form spelled out through members the headers define
inline, so each use counts the reflected-field accesses of the inline body it runs: an inline member called on an
object of known class (`_Meta->isValid()`, `meta->isValid()`, a bare inline member of the class), counted on the
object's class. A member whose class has a destructor (igSmartPointer<T>, igStringRef) is a one-word holder: what
its inline members do to the word counts as accesses of the field -- its assignment (`_poolName = name` reads the
old string to release it and stores the new), a constructor's default construction of it (the C form's
`self->_poolName = 0`), and its destruction. A converted class whose destructor the compiler writes (a `__dt__` name
of compiler-names.tsv, no `Class::~Class` in src/) counts its implicit destructor once, and a destructor src
defines counts the compiler's part after its body: at each class level with a destructor, the vtable store, then
each holder member's destruction (the `this != 0` test on its address, its release). So writing a class's
functions as its members never lowers the count.

Comments and string literals are blanked before counting, so `p->field` in a prose
comment or a format string is not an access. The per-folder table shows where the raw
casts remain (`src/engine`, `src/game`, `src/unmatched`, ...).

The types used for a field are not invented: where the matched C already accesses a
(class, offset) with a particular cast, that cast *is* the type (it is byte-exact by
construction), and the reflection metadata supplies the field's name. So a conversion
cannot change codegen unless the type was chosen wrongly, which is what `make check`
catches.

Usage:
    typed_coverage.py                       # the numbers, and the per-folder table
    typed_coverage.py --by-class            # where the recovered and convertible accesses are
    typed_coverage.py --json out.json       # machine-readable detail
    typed_coverage.py --untyped src/x.c     # every untyped access in one file
"""

import argparse
import bisect
import srctext
import collections
import glob
import json
import os
import re
import sys

# Reflection's field types are MetaField *classes*; this is the C type they denote. The
# size is what matters for codegen; where the matched code disagrees, the code wins (see
# the module docstring) and the disagreement is reported.
META_TO_C = {
    "igIntMetaField": "int",
    "igEnumMetaField": "int",
    "igUnsignedIntMetaField": "unsigned int",
    "igBoolMetaField": "int",
    "igShortMetaField": "short",
    "igUnsignedShortMetaField": "unsigned short",
    "igLongMetaField": "long long",
    "igUnsignedLongMetaField": "unsigned long long",
    "igCharMetaField": "char",
    "igUnsignedCharMetaField": "unsigned char",
    "igFloatMetaField": "float",
    "igDoubleMetaField": "double",
    "igStringMetaField": "int",          # a handle/pointer, 4 bytes
    "igObjectRefMetaField": "int",       # ditto: a reference, not inline data
    "igRawRefMetaField": "int",
    "igMemoryRefMetaField": "int",
    "igStructMetaField": "int",
    "igVec2fMetaField": "int",           # 8 bytes inline, accessed as words
    "igVec3fMetaField": "int",
    "igVec4fMetaField": "int",
    "igMatrix44fMetaField": "int",
    "igIntArrayMetaField": "int",
    "igFloatArrayMetaField": "int",
    "igCharArrayMetaField": "int",
    "igUnsignedCharArrayMetaField": "int",
    "igEnumArrayMetaField": "int",
    "igShortArrayMetaField": "int",
    "igBoolArrayMetaField": "int",
    "igUnsignedIntArrayMetaField": "int",
    "igUnsignedShortArrayMetaField": "int",
    "igVec4fArrayMetaField": "int",
    "igObjectRefArrayMetaField": "int",
}

# A definition head: a free function (`int igFoo_Bar(...) {`) or a member function written out of its class,
# its class qualified by namespaces or not (`void igRenderer::setVisualContext(...) {`,
# `igMetaObject *Gap::Gui::igRenderer::getMeta() const {`); the scope is the receiver's class.
FUNC_RE = re.compile(
    r"^(?P<ret>[A-Za-z_][\w \t\*]*?[\s\*])(?P<scope>(?:[A-Za-z_]\w*\s*::\s*)+)?(?P<name>\w+)\s*"
    r"\((?P<args>[^;{)]*)\)\s*(?:const\s*)?\{",
    re.M)
# a constructor or destructor written out of its class (`Gap::Core::igObject::igObject() {`, `igRenderer::~igRenderer()`,
# with or without a member-initialiser list): no return type, its class's name for a name
SPECIAL_RE = re.compile(
    r"^[ \t]*(?P<scope>(?:[A-Za-z_]\w*\s*::\s*)*(?P<cls>[A-Za-z_]\w*)\s*::\s*)(?P<name>~?(?P=cls))\s*"
    r"\((?P<args>[^;{)]*)\)\s*(?::[^;{]*)?\{",
    re.M)
# an identifier that is not a member of another object (`->x`, `.x`, `C::x`) nor a call
IDENT_RE = re.compile(r"(?<![\w.>:])([A-Za-z_]\w*)\b(?!\s*\()")
CAST_RE = re.compile(r"\*\(\s*([A-Za-z_][\w \t\*]*?)\s*\*\s*\)\s*\(")
MEMBER_RE = re.compile(r"\b(\w+)\s*->\s*(\w+)")
# `((T *)base)->field` -- an explicit cast around a temporary, which the passes in
# `scripts/` emit when the object's class comes from reflection rather than the
# variable's declaration (`(void *)(igMetaObject_GetFieldAt(...))` has no declared type).
CAST_OPEN_RE = re.compile(r"\(\s*\(\s*([A-Za-z_]\w*)\s*\*\s*\)")
ARROW_RE = re.compile(r"\s*->\s*(\w+)")
CAST_MEMBER_RE = re.compile(r"\(\s*\(\s*([A-Za-z_]\w*)\s*\*\s*\)\s*(\w+)\s*\)\s*->\s*(\w+)")
# `igMetaObject *g = ...` / `struct G *g = ...` -- the declared type of a pointer is the
# strongest evidence for what a member access on it means, and it is what catches the
# conversion of automatch's synthetic layout into a recovered class.
DECL_RE = re.compile(r"\b(?:struct\s+)?([A-Za-z_]\w*)\s*\*+\s*(\w+)\s*(?:=|;|,|\))")
# `const igObject &other` / `igObject &o = ...` -- a reference to a class: `other._refCount` reads the class's field
# as `p->_refCount` does through a pointer
REF_DECL_RE = re.compile(r"\b(?:struct\s+)?([A-Za-z_]\w*)\s*(?:const\s*)?&\s*([A-Za-z_]\w*)\s*(?=[=;,)])")
DOT_RE = re.compile(r"(?<![\w.>:])([A-Za-z_]\w*)\s*\.\s*([A-Za-z_]\w*)\b(?!\s*\()")
OFFSET_RE = re.compile(r"[+\-]\s*(\d+)\s*$")
# a declaration at the start of a statement, `int start = ...;` / `igVisualContext *old;`
LOCAL_DECL_RE = re.compile(r"(?:^|[;{}(])\s*(?:const\s+|unsigned\s+|signed\s+|struct\s+)*[A-Za-z_]\w*"
                           r"(?:\s*<[^<>;{}()]*>)?[\s\*&]+([A-Za-z_]\w*)\s*(?=[;=,\[)])", re.M)
_NOT_A_TYPE = frozenset(("return", "case", "goto", "else", "sizeof", "delete", "new", "throw", "do"))


def local_names(signature, body):
    """The parameter and local names of one function (its parameter list and its body), which a bare
    identifier of the same name in the body means rather than a field of the receiver."""
    names = {p.strip().split("[")[0].split()[-1].lstrip("*&") for p in signature.split(",")
             if p.strip() and p.strip() != "void" and re.search(r"[\s\*&]", p.strip())}
    for m in LOCAL_DECL_RE.finditer(body):
        head = m.group(0).lstrip(";{}( \t\n").split()
        if head and head[0] not in _NOT_A_TYPE:
            names.add(m.group(1))
    return names


def load_classes(path):
    """{class name: {"fields": [(offset, name, ctype)], "handle": str}}."""
    data = json.load(open(path))
    out = {}
    for handle, o in data["classes"].items():
        fields = []
        for f in o.get("fields") or []:
            fields.append((f["offset"], f["name"],
                           META_TO_C.get(f["type"], "int"), f["type"]))
        fields.sort()
        out[o["class"]] = {"handle": handle, "fields": fields,
                           "by_offset": {off: (nm, ct) for off, nm, ct, _ in fields}}
    # Authoritative fields reflection does not list (config/SLUS-20836/authoritative-fields.tsv).
    overlay = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(path))), "config",
                           "SLUS-20836",
                           "authoritative-fields.tsv")
    if os.path.exists(overlay):
        for line in open(overlay):
            if line.strip() and not line.startswith("#"):
                cls, off, mtype, fname = line.rstrip("\n").split("\t")[:4]
                c = out.setdefault(cls, {"handle": "", "fields": [], "by_offset": {}})
                c["fields"].append((int(off), fname, META_TO_C.get(mtype, "int"), mtype))
                c["fields"].sort()
    # Reflection lists only a class's own fields; the generated include/dw4/support/reflected.h merges the
    # ancestors' (data/class-hierarchy.tsv), so a member inherited from a base class is typed too.
    base = {}
    hier = os.path.join(os.path.dirname(os.path.abspath(path)), "class-hierarchy.tsv")
    if os.path.exists(hier):
        for line in open(hier):
            if line.strip() and not line.startswith("#"):
                f = line.rstrip("\n").split("\t")
                if len(f) >= 2:
                    base[f[0]] = f[1]
    own = {name: list(c["fields"]) for name, c in out.items()}
    for name, c in out.items():
        seen, cur, merged = {name}, base.get(name), list(own[name])
        while cur and cur not in seen:
            seen.add(cur)
            merged.extend(own.get(cur, []))
            cur = base.get(cur)
        merged.sort()
        c["fields"] = merged
        c["by_offset"] = {off: (nm, ct) for off, nm, ct, _ in merged}
    return out


def class_of(name):
    """The class a function name implies for its first argument, or None.

    The repo's naming is `<Class>_<Method>` (`igMetaEnum_GetNameCount`), so the receiver
    type is recoverable from the name alone; a member function (`igRenderer::setVisualContext`,
    `Gap::Gui::igRenderer::getMeta`) names its class before the last `::`. Names with no
    underscore (`sceMtapPortOpen`) imply nothing and are left untyped.
    """
    if "::" in name:
        return name.rsplit("::", 2)[-2]
    if name.startswith("Gap__"):
        # `Gap__Bec__<Class>__vfunc_N`: the class is the segment before `__vfunc_`
        parts = name.split("__")
        if len(parts) >= 3 and parts[-1].startswith("vfunc_"):
            return parts[-2]
    if "_" not in name:
        return None
    return name.rsplit("_", 1)[0]


_COMMENT_OR_STRING_RE = re.compile(
    r"/\*.*?\*/"                      # block comment
    r"|//[^\n]*"                      # line comment
    r"|\"(?:\\.|[^\"\\\n])*\""        # string literal
    r"|'(?:\\.|[^'\\\n])*'",          # character literal
    re.S)


def strip_comments_and_strings(text):
    """`text` with every comment and string/character literal blanked to spaces.

    Length and newlines are preserved, so spans and line numbers computed on the result
    index the original file. Blanking rather than deleting is what keeps `--untyped`'s
    excerpts correct.
    """
    def blank(m):
        s = m.group(0)
        return "".join("\n" if ch == "\n" else " " for ch in s)
    return _COMMENT_OR_STRING_RE.sub(blank, text)


def split_functions(text):
    """[(name, args, body_start, body_end)] for the definitions in `text`, each running to the next one: top-level
    ones and the member functions a class defines in its body (`Class::name`)."""
    found = {}
    for m in list(FUNC_RE.finditer(text)) + list(SPECIAL_RE.finditer(text)):
        found.setdefault(m.start(), (re.sub(r"\s+", "", m.group("scope") or "") + m.group("name"), m.group("args")))
    heads = sorted(found)
    for m in _CLASS_RE.finditer(text):
        close = _close_brace(text, m.end() - 1)
        if close < 0:
            continue
        for item in class_members(text[m.end():close]):
            if item[0] != "method":
                continue
            start, opened = m.end() + item[2], m.end() + item[3]
            at = bisect.bisect_left(heads, start)
            if not (at < len(heads) and heads[at] < opened):    # not a head at the line's start, already found
                found.setdefault(start, (m.group("name") + "::" + item[1], method_parts(text[start:opened])[0]))
    starts = sorted(found)
    return [found[pos] + (pos, starts[i + 1] if i + 1 < len(starts) else len(text)) for i, pos in enumerate(starts)]


def matching_paren(text, open_idx):
    depth = 0
    for i in range(open_idx, len(text)):
        if text[i] == "(":
            depth += 1
        elif text[i] == ")":
            depth -= 1
            if depth == 0:
                return i
    return -1


SYNTH_RE = re.compile(r"struct\s+(\w+)\s*\{([^}]*)\}\s*;")


def synthetic_structs(text):
    """{struct name: [(offset, field)]} for the local `struct G` idiom automatch emits.

    `struct G { char pad[36]; int f; };` -- a layout with no meaning, but an *access
    shape* that already compiles on another machine, which is why it is measured
    separately from a recovered class.
    """
    out = {}
    for m in SYNTH_RE.finditer(text):
        fields, off = [], 0
        for decl in m.group(2).split(";"):
            decl = decl.strip()
            pm = re.match(r"char\s+pad\s*\[\s*(\d+)\s*\]", decl)
            if pm:
                off += int(pm.group(1))
                continue
            fm = re.match(r"([A-Za-z_][\w ]*?)\s*\*?\s*(\w+)$", decl)
            if fm:
                fields.append((off, fm.group(2)))
                off += 4
        out[m.group(1)] = fields
    return out


def accesses(text):
    """Every field access in `text`: (kind, type, offset, base, span).

    kind is "cast" for `*(T *)(base + N)` and "member" for `x->field`.  `base` is the
    expression the offset is applied to, normalised to its innermost identifier when it is
    a plain deref chain, so `*(int *)((char *)(arg0) + 12)` yields base "arg0".
    """
    out = []
    pos = 0
    while True:
        m = CAST_RE.search(text, pos)
        if not m:
            break
        open_idx = m.end() - 1
        close = matching_paren(text, open_idx)
        if close < 0:
            pos = m.end()
            continue
        expr = text[open_idx + 1:close].strip()
        pos = close
        # the offset is the trailing `+ N`; everything before it is the base
        base = expr
        offset = None
        om = OFFSET_RE.search(expr)
        if om:
            offset = int(om.group(1))
            if expr[om.start()] == "-":
                offset = -offset
            base = expr[:om.start()].strip()
        # The root is the innermost identifier the expression is built from.  m2c nests
        # these (`*(int *)((char *)(arg0) + 52)`), and taking the *first* word instead
        # picks up a cast type ("int"), which silently classified nothing.
        root = re.sub(r"\(\s*[A-Za-z_][\w \t\*]*\s*\*\s*\)", "", expr).strip()
        while root.startswith("(") and matching_paren(root, 0) == len(root) - 1:
            root = root[1:-1].strip()
        root = re.sub(r"\(\s*[A-Za-z_][\w \t\*]*\s*\*\s*\)", "", root).strip()
        ident = re.search(r"\b([A-Za-z_]\w*)\b", root)
        out.append(("cast", m.group(1).strip(), offset,
                    ident.group(1) if ident else None, (m.start(), close + 1)))
    # `((T *)expr)->field`: the cast wraps any expression, including a nested reference access
    # (`((beMessenger *)p->_messenger)->_intList`), which is how an arena handle is followed.
    for m in CAST_OPEN_RE.finditer(text):
        close = matching_paren(text, m.start())
        if close < 0:
            continue
        fm = ARROW_RE.match(text, close + 1)
        if fm:
            out.append(("castmember", fm.group(1), None, m.group(1), (m.start(), fm.end())))
    for m in MEMBER_RE.finditer(text):
        # the member *name* goes in the type slot; a member access has no offset cast
        out.append(("member", m.group(2), None, m.group(1), (m.start(), m.end())))
    out.sort(key=lambda a: a[4][0])
    return out


TEMPLATE_RE = re.compile(r"template\s*<\s*(?:class|typename)\s+(\w+)\s*>\s*(?:struct|class)\s+(\w+)")


def template_arguments(text):
    """{parameter: [types the file instantiates it with]}, so a member read through a template
    parameter counts as a member of the class the template holds. `igSmartPointer<igProbe>`
    makes `T *o; o->_refCount` a read of `igProbe`."""
    found = {}
    for param, name in TEMPLATE_RE.findall(text):
        args = re.findall(r"\b%s\s*<\s*(?:struct\s+)?(\w+)\s*\*?\s*>" % re.escape(name), text)
        found.setdefault(param, []).extend(a for a in args if a != param)
    return found


# ---- what a member's typed code reaches through inline and implicit members ------------------------------
# A converted class's member writes `_Meta->isValid()`, `_visualContext = context` or nothing at all (an implicit
# destructor) where the free function it was spelled `g->_validity & 4`, the reference count arithmetic and a
# `<Class>_Destroy` body. The compiled code still makes those reads, on typed objects, through the inline members
# and template the headers define: each use counts the accesses of the inline body it runs, as if written there.
_CONDITIONAL_RE = re.compile(r"^[ \t]*#[ \t]*(ifdef|ifndef|if|elif|else|endif)\b(.*)$")
_DEFINE_RE = re.compile(r"^[ \t]*#[ \t]*define[ \t]+(\w+)\(([^)]*)\)((?:[^\n]*\\\n)*[^\n]*)", re.M)
_CLASS_RE = re.compile(r"(?:template\s*<\s*(?:class|typename)\s+(?P<tparam>\w+)\s*>\s*)?"
                       r"\b(?:struct|class)\s+(?P<name>[A-Za-z_]\w*)\s*(?::(?P<bases>[^{;()]*))?\{")
_FREE_INLINE_RE = re.compile(r"^[ \t]*(?:static\s+)?inline\s+[^;{}()]*?\b(?P<name>\w+)\s*\((?P<params>[^;{)]*)\)\s*\{",
                             re.M)
_CALL_RE = re.compile(r"(?:\b(?P<base>\w+)\s*(?P<op>->|\.)\s*)?(?<![\w~])(?P<name>[A-Za-z_]\w*)\s*\((?P<args>[^()]*)\)")
_ASSIGN_RE = re.compile(r"(?<![\w.>])(?:this\s*->\s*)?(?P<name>[A-Za-z_]\w*)\s*=(?!=)")
_SMART_RE = re.compile(r"^igSmartPointer\s*<\s*(?:struct\s+)?([\w:]+)\s*>$")
_KEYWORDS = frozenset(("if", "while", "for", "switch", "return", "sizeof", "do", "else", "case", "new", "delete"))


def cxx_view(text):
    """`text` as C++ reads it: of an `#ifdef __cplusplus` / `#ifndef __cplusplus` conditional only the arm C++
    compiles stays, the other arm's lines are blanked; other conditionals keep every arm."""
    out, stack, live = [], [], True
    for line in text.split("\n"):
        m = _CONDITIONAL_RE.match(line)
        if m:
            word, rest = m.group(1), m.group(2).strip()
            if word in ("ifdef", "ifndef", "if"):
                cxx = rest == "__cplusplus" and word != "if"
                stack.append((cxx, live))
                if cxx:
                    live = live and word == "ifdef"
            elif word in ("else", "elif") and stack and stack[-1][0]:
                live = stack[-1][1] and not live
            elif word == "endif" and stack:
                live = stack.pop()[1]
            out.append("")
            continue
        out.append(line if live else "")
    return "\n".join(out)


_BUILTIN_RE = re.compile(r"^(?:unsigned|signed|char|short|int|long|float|double|bool|void|size_t)\b")


def _member_type(decl):
    """(kind, type) of a member declaration's type text: ("smart", T) for `igSmartPointer<T>`, ("ptr", T) for a
    pointer to T, ("object", T) for an object of class T (`igStringRef`), or None."""
    decl = re.sub(r"\b(?:static|struct|class|const|mutable|volatile)\b", " ", decl).strip()
    smart = _SMART_RE.match(re.sub(r"\s+", " ", decl))
    if smart:
        return "smart", smart.group(1).rsplit("::", 1)[-1]
    m = re.match(r"^([A-Za-z_][\w:]*)\s*\*$", decl)
    if m:
        return "ptr", m.group(1).rsplit("::", 1)[-1]
    m = re.match(r"^([A-Za-z_][\w:]*)$", decl)
    return ("object", m.group(1).rsplit("::", 1)[-1]) if m and not _BUILTIN_RE.match(m.group(1)) else None


def initializers(text):
    """[(name, arguments)] of a constructor's member-initialiser list (`p(0), _count(n)`, the text after its `:`)."""
    out, depth, start = [], 0, 0
    for i, ch in enumerate(text + ","):
        if ch in "(<":
            depth += 1
        elif ch in ")>":
            depth -= 1
        elif ch == "," and depth == 0:
            m = re.match(r"^\s*([A-Za-z_][\w:]*)\s*\((.*)\)\s*$", text[start:i], re.S)
            if m:
                out.append((m.group(1).rsplit("::", 1)[-1], m.group(2)))
            start = i + 1
    return out


_METHOD_NAME_RE = re.compile(r"(operator\s*[^\s(]+|operator\s+[\w\s\*]+?|~?\w+)\s*$")


def class_members(body):
    """The members a class body declares at its own depth, in order: ("method", name, start, open, close) for a
    function defined in the class (its declaration starts at `start`, its body runs from the `{` at `open` to the
    `}` at `close`), ("data", type text, name) for a data member."""
    at, start = 0, 0
    while at < len(body):
        ch = body[at]
        if ch == "{":
            head = body[start:at]
            close = _close_brace(body, at)
            if close < 0:
                return
            paren = head.find("(")
            if paren > 0 and not re.search(r"\b(?:struct|class|union|enum)\b", head[:paren]):
                name = _METHOD_NAME_RE.search(head[:paren])
                if name:
                    key = re.sub(r"\s+", " ", name.group(1)).replace("operator =", "operator=")
                    yield "method", key, start, at, close
            at, start = close + 1, close + 1
            if body[start:start + 1] == ";":
                at = start = start + 1
            continue
        if ch in ";:":
            stmt = body[start:at]
            if ch == ":" and (body[at:at + 2] == "::" or body[at - 1:at] == ":"):
                at += 1
                continue
            if ch == ":" and re.search(r"\)\s*(?:const\s*)?$", stmt):
                at += 1                     # a constructor's member-initialiser list, not an access label
                continue
            if ch == ";" and "(" not in stmt:
                m = re.match(r"^\s*(.*?)\b(\w+)\s*(?:\[[^\]]*\]\s*)*$", stmt, re.S)
                if m:
                    yield "data", m.group(1), m.group(2)
            start = at + 1
        at += 1


def method_parts(head):
    """(parameter text, member-initialiser text or "") of an inline function's declaration up to its body."""
    paren = head.find("(")
    pclose = matching_paren(head, paren)
    init = re.match(r"\s*(?:const\s*)?:(.*)$", head[pclose + 1:], re.S)
    return head[paren + 1:pclose], init.group(1) if init else ""


def _params(text):
    """{name: type} of a parameter list's pointer parameters (`T *next`, `igObject *o`)."""
    out = {}
    for p in text.split(","):
        m = re.match(r"^\s*(?:const\s+|struct\s+|class\s+)*([A-Za-z_][\w:]*)\s*\*+\s*&?\s*(\w+)\s*$", p)
        if m:
            out[m.group(2)] = m.group(1).rsplit("::", 1)[-1]
    return out


def _close_brace(text, open_idx):
    depth = 0
    for i in range(open_idx, len(text)):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return i
    return -1


class Inlines:
    """The inline members and free inline functions the headers define, and the classes' typed members: what a use
    of a member runs, as reflected-field accesses on typed objects.

    A member whose class has a destructor (igStringRef, igSmartPointer<T>) is a *holder*: a one-word object whose
    word is the reflected field. What its inline members do to that word (`p = next`, `releaseString(p)`) are
    accesses of the field, as the C form spelled them on `self->_field`. Counter keys `(class, "." + word)` stand for
    a use of a class's own data member `word` inside its inline member; `through` maps them onto the field."""

    def __init__(self, texts, fields, polymorphic=()):
        self.fields = fields                    # {class: set(reflected field names)}, ancestors merged
        self.polymorphic = set(polymorphic)     # the classes with a vtable (config/converted-classes.tsv)
        self.methods = {}                       # (class, name) -> (params {name: type}, body)
        self.free = {}                          # name -> (params, body), the first definition
        self.members = collections.defaultdict(dict)    # class -> {member: (kind, type)}
        self.data = collections.defaultdict(set)        # class -> its data members' names
        self.bases = collections.defaultdict(list)
        self.templates = {}                     # class -> its template parameter
        self._cache = {}
        self._nontrivial = {}
        macros = {}
        views = [cxx_view(strip_comments_and_strings(t)) for t in texts]
        for text in views:
            for m in _DEFINE_RE.finditer(text):
                macros[m.group(1)] = ([p.strip() for p in m.group(2).split(",") if p.strip()],
                                      m.group(3).replace("\\\n", "\n"))
        for text in views:
            for m in _FREE_INLINE_RE.finditer(text):
                close = _close_brace(text, m.end() - 1)
                if close > 0:
                    self.free.setdefault(m.group("name"), (_params(m.group("params")), text[m.end():close]))
            for m in _CLASS_RE.finditer(text):
                close = _close_brace(text, m.end() - 1)
                if close < 0:
                    continue
                name = m.group("name")
                if m.group("tparam"):
                    self.templates[name] = m.group("tparam")
                for base in (m.group("bases") or "").split(","):
                    words = re.findall(r"[A-Za-z_][\w:]*", base)
                    if words and words[-1] not in ("public", "private", "protected", "virtual"):
                        self.bases[name].append(words[-1].rsplit("::", 1)[-1])
                self._read_body(name, self._expand(text[m.end():close], macros))

    @staticmethod
    def _expand(body, macros, depth=0):
        if depth > 3:
            return body

        def one(m):
            params, text = macros[m.group(1)]
            args = [a.strip() for a in m.group(2).split(",")]
            for p, a in zip(params, args):
                text = re.sub(r"\b%s\b" % re.escape(p), a, text)
            return text + ";"
        names = [n for n in macros if n in body]
        if not names:
            return body
        new = re.sub(r"\b(%s)\s*\(([^()]*)\)" % "|".join(map(re.escape, names)), one, body)
        return Inlines._expand(new, macros, depth + 1) if new != body else body

    def _read_body(self, cls, body):
        """The class body's members at its own depth: data members' types, inline functions' bodies (a
        constructor's member initialisers, `p(0)`, read as the assignments `p = (0);` that open its body)."""
        for item in class_members(body):
            if item[0] == "data":
                self.data[cls].add(item[2])
                typed = _member_type(item[1])
                if typed:
                    self.members[cls].setdefault(item[2], typed)
                continue
            _kind, key, start, opened, close = item
            params, init = method_parts(body[start:opened])
            prologue = "".join("%s = (%s);\n" % pair for pair in initializers(init))
            self.methods.setdefault((cls, key), (_params(params), prologue + body[opened + 1:close]))

    def member(self, cls, name, seen=None):
        """(kind, type) of `cls`'s member `name`, its bases' included, or None."""
        seen = seen or set()
        if cls in seen or cls is None:
            return None
        seen.add(cls)
        if name in self.members.get(cls, {}):
            return self.members[cls][name]
        for b in self.bases.get(cls, ()):
            found = self.member(b, name, seen)
            if found:
                return found
        return None

    def method(self, cls, name, seen=None):
        """(class defining it, params, body) of the inline member `name` of `cls` or a base, or None."""
        seen = seen or set()
        if cls in seen or cls is None:
            return None
        seen.add(cls)
        if (cls, name) in self.methods:
            return (cls,) + self.methods[(cls, name)]
        for b in self.bases.get(cls, ()):
            found = self.method(b, name, seen)
            if found:
                return found
        return None

    def run(self, cls, name, binding=(), depth=0):
        """Counter{(class, field)} of the reflected-field accesses a call of the inline member `name` on a `cls`
        object makes (its own fields counted on `cls`, as `self->_field` counts on the pointer's class, wherever the
        member is defined), with the template parameter bound (`binding`, ((parameter, type),)); empty when it is
        not inline."""
        found = self.method(cls, name)
        if found is None:
            return collections.Counter()
        owner, params, body = found
        key = (cls, name, binding)
        if key not in self._cache:
            self._cache[key] = collections.Counter()      # a recursion reads nothing more
            self._cache[key] = self._body(owner, params, body, dict(binding), depth,
                                          cls if cls in self.fields else owner)
        return self._cache[key]

    def run_free(self, name, args, depth=0):
        """The accesses of a call of the free inline function `name` whose pointer arguments have the classes
        `args` (None where unknown): an access through a parameter is one on its argument's class."""
        if name not in self.free or depth > 4:
            return collections.Counter()
        params, body = self.free[name]
        names = list(params)
        typed = dict(params)
        for i, a in enumerate(args[:len(names)]):
            if a:
                typed[names[i]] = a
        return self._body(None, typed, body, {}, depth + 1)

    def _body(self, owner, params, body, binding, depth, receiver=None):
        out = collections.Counter()
        if depth > 4:
            return out
        receiver = receiver or owner
        bind = lambda t: binding.get(t, t)  # noqa: E731
        types = {v: bind(t) for v, t in params.items()}
        for t, v in DECL_RE.findall(body):
            if t not in _NOT_A_TYPE:
                types.setdefault(v, bind(t))
        if owner:
            for name, (kind, t) in self.members.get(owner, {}).items():
                if kind == "ptr":
                    types.setdefault(name, bind(t))
        for base, field in MEMBER_RE.findall(body):
            cls = receiver if base == "this" else types.get(base)
            if cls and field in self.fields.get(cls, ()):
                out[(cls, field)] += 1
            elif base == "this" and owner and field in self.data.get(owner, ()):
                out[(owner, "." + field)] += 1
        if owner:
            local = local_names(",".join(params), body)
            fields, words = self.fields.get(receiver, ()), self.data.get(owner, ())
            for m in IDENT_RE.finditer(body):
                name = m.group(1)
                if name in local or name in params:
                    continue
                if name in fields:
                    out[(receiver, name)] += 1
                elif name in words:
                    out[(owner, "." + name)] += 1
        for m in _CALL_RE.finditer(body):
            name, base = m.group("name"), m.group("base")
            if name in _KEYWORDS:
                continue
            if base is None and owner and self.method(receiver, name):
                out.update(self.run(receiver, name, tuple(sorted(binding.items())), depth + 1))
            elif base is None and name in self.free:
                args = [types.get(a.strip()) for a in m.group("args").split(",")]
                out.update(self.run_free(name, args, depth))
            elif base is not None and types.get(base):
                out.update(self.run(types[base], name, (), depth + 1))
        return out

    def holder(self, cls, name):
        """(holder class, template binding) of `cls`'s member `name` (a base's included) when it is an object
        whose class has a destructor -- an igSmartPointer<T>, an igStringRef -- or None."""
        found = self.member(cls, name)
        if not found:
            return None
        kind, t = found
        if kind == "smart":
            return "igSmartPointer", ((self.templates.get("igSmartPointer", "T"), t),)
        if kind == "object" and self.method(t, "~" + t):
            return t, ()
        return None

    def through(self, top, member, holder, operation):
        """The accesses of the holder member `member` of a `top` object running the holder's inline `operation`
        (`operator=`, its constructor, its destructor): each use of the holder's word is one of the field."""
        out = collections.Counter()
        cls, binding = holder
        for (owner, field), n in self.run(cls, operation, binding).items():
            if not field.startswith("."):
                out[(owner, field)] += n
            elif owner == cls and member in self.fields.get(top, ()):
                out[(top, member)] += n
        return out

    def constructed(self, cls, initialized=()):
        """What a constructor of `cls` does to the holder members `cls` declares: each is constructed, from its
        member initialiser (`initialized`, one store) or by its default constructor."""
        out = collections.Counter()
        for name in self.members.get(cls, {}):
            holder = self.holder(cls, name)
            if holder and name in self.fields.get(cls, ()):
                if name in initialized:
                    out[(cls, name)] += 1
                else:
                    out.update(self.through(cls, name, holder, holder[0]))
        return out

    def nontrivial(self, cls, defined=()):
        """Whether the compiler writes a destructor for `cls`: the source defines one (`defined`, the
        `Class::~Class` names of src/, or an inline one), it holds a member with a destructor, or a base does."""
        if cls not in self._nontrivial:
            self._nontrivial[cls] = False       # a cycle adds nothing
            self._nontrivial[cls] = ("%s::~%s" % (cls, cls) in defined or (cls, "~" + cls) in self.methods or
                                     any(self.holder(cls, n) for n in self.members.get(cls, {})) or
                                     any(self.nontrivial(b, defined) for b in self.bases.get(cls, ())))
        return self._nontrivial[cls]

    def implicit_destructor(self, cls, defined=(), top=None, seen=None):
        """The accesses the compiler writes into a destructor of a `top` object at the level of `cls`: a polymorphic
        class with a destructor stores its vtable, then each holder member is destroyed -- the destructor's
        `this != 0` test on the member's address, then its body -- and the bases follow, inlined, up to one whose
        destructor the source defines (`defined`), which is called."""
        top, seen = top or cls, seen or set()
        out = collections.Counter()
        if cls in seen:
            return out
        seen.add(cls)
        fields = self.fields.get(top, ())
        if cls in self.polymorphic and "_vtable" in fields and self.nontrivial(cls, defined):
            out[(top, "_vtable")] += 1
        for name in self.members.get(cls, {}):
            holder = self.holder(cls, name)
            if holder:
                if name in fields:
                    out[(top, name)] += 1
                out.update(self.through(top, name, holder, "~" + holder[0]))
        for b in self.bases.get(cls, ()):
            if "%s::~%s" % (b, b) not in defined:
                out.update(self.implicit_destructor(b, defined, top, seen))
        return out


def header_texts(roots):
    """The texts of every header under `roots` (include/, src/)."""
    out = []
    for root in roots:
        for path in sorted(glob.glob(os.path.join(root, "**", "*.h"), recursive=True)):
            try:
                out.append(srctext.read(path, errors="replace"))
            except (FileNotFoundError, UnicodeDecodeError):
                continue
    return out


def converted_classes(root):
    """The classes of config/converted-classes.tsv: Alchemy's polymorphic Gap classes."""
    path = os.path.join(root, "config", "converted-classes.tsv")
    if not os.path.exists(path):
        return set()
    with open(path) as fh:
        return {line.split("\t")[0].strip() for line in fh if line.strip() and not line.startswith("#") and "\t" in line}


def implicit_destructors(root, defined):
    """The converted classes whose destructor the compiler writes (a `__dt__` compiler name of
    config/SLUS-20836/compiler-names.tsv on a class of config/converted-classes.tsv) and the source does not define
    (`defined`, the `Class::~Class` names of src/)."""
    from demangle import demangle
    out = []
    converted = converted_classes(root)
    names = os.path.join(root, "config", "SLUS-20836", "compiler-names.tsv")
    if not (converted and os.path.exists(names)):
        return out
    with open(names) as fh:
        compiled = [line.split("\t", 1)[0] for line in fh if line.startswith("__dt__")]
    for name in compiled:
        d = demangle(name)
        cls = d.class_name if d else None
        if cls in converted and "%s::~%s" % (cls, cls) not in defined and cls not in out:
            out.append(cls)
    return out


def measure(reflection="data/reflection.json", src="src"):
    """The two numbers, plus what could be converted and where.

    Called by tools/progress.py as well as by the CLI, so the published figure and the
    one this tool prints can never disagree.
    """
    classes = load_classes(reflection)
    root = os.path.dirname(os.path.dirname(os.path.abspath(reflection)))
    converted = converted_classes(root)
    inlines = Inlines(header_texts([os.path.join(root, "include"), src]),
                      {name: {f[1] for f in c["fields"]} for name, c in classes.items()}, converted)
    defined_destructors = set()
    user_destructors = []           # (class, per-function counter, per-folder counter) of a destructor src defines
    # `dw4u_*` are the transient one-function splits tools/units.py writes while a check
    # runs; they duplicate a unit's function and may vanish mid-walk, so they are not units.
    files = sorted(p for p in glob.glob(os.path.join(src, "**", "*.c"), recursive=True) +
                   glob.glob(os.path.join(src, "**", "*.cpp"), recursive=True)
                   if not os.path.basename(p).startswith("dw4u_"))
    observed = collections.defaultdict(collections.Counter)
    stats = dict(total=0, offset_casts=0, recovered=0, synthetic=0, other_members=0,
                 typeable=0, by_class={}, typeable_by_class={}, accesses=[],
                 files=len(files), parsed=0,
                 pairs=0, conflicting_pairs=0, per_function={}, by_folder={})
    for path in files:
        # Comments and literals are blanked first: a `p->field` in prose, or in a format
        # string, is not an access.
        try:
            text = strip_comments_and_strings(srctext.read(path, errors="replace"))
        except FileNotFoundError:        # removed between the walk and the read
            continue
        folder = os.path.relpath(path, src).split(os.sep)[0]
        if folder.endswith((".c", ".cpp")):
            folder = "."                      # a file at the root of src/
        ff = stats["by_folder"].setdefault(
            folder, dict(total=0, offset_casts=0, recovered=0, synthetic=0,
                         other_members=0, files=0))
        ff["files"] += 1

        def credit(found, fc, ff=ff):
            """Count the accesses an inline or implicit member makes (Inlines) as recovered ones."""
            for (owner, field), n in found.items():
                if field.startswith("."):
                    continue                # a holder's own word, counted through the field that holds it
                ff["total"] += n
                stats["recovered"] += n
                ff["recovered"] += n
                fc["recovered"] += n
                stats["by_class"][owner] = stats["by_class"].get(owner, 0) + n

        synth_structs = synthetic_structs(text)
        template_args = template_arguments(text)
        fns = split_functions(text)
        if fns:
            stats["parsed"] += 1
        for name, signature, start, end in fns:
            body = text[start:end]
            cls = class_of(name)
            rec = classes.get(cls) if cls else None
            decls = {var: t for t, var in DECL_RE.findall(body)}
            for var, declared in list(decls.items()):
                if declared in template_args:
                    decls[var] = next((a for a in template_args[declared] if a in classes), declared)
            # a name declared again in a later block (igen's `{ T *metaField = ...; }` per field) has the type
            # of the declaration before the access
            placed = collections.defaultdict(list)
            for m in DECL_RE.finditer(body):
                t = m.group(1)
                if t in template_args:
                    t = next((a for a in template_args[t] if a in classes), t)
                placed[m.group(2)].append((m.start(), t))

            def declared_at(var, at):
                before = [t for p, t in placed.get(var, ()) if p < at]
                return before[-1] if before else decls.get(var)

            # overloads (a class's constructors) share one entry
            fc = stats["per_function"].setdefault((path, name), collections.Counter())
            shadowed = local_names(signature, body)
            if "::~" in name:
                defined_destructors.add("::".join(name.rsplit("::", 2)[-2:]))
                user_destructors.append((cls, fc, ff))

            def typed_member(var):
                """(kind, class) of a member of a member function's class that `var` names (not a local), or
                None."""
                if "::" not in name or not cls or var in shadowed or var in decls:
                    return None
                return inlines.member(cls, var)

            def held(var):
                """(holder, binding) of a holder member (Inlines.holder) of a member function's class that `var`
                names, or None."""
                return inlines.holder(cls, var) if typed_member(var) else None

            # a holder member assigned (`_poolName = name`, igStringRef::operator=) or running one of its inline
            # members (`_poolName.ref()`) is counted through what that member does to its word -- a release reads
            # it, a store writes it -- not as one bare read of the name
            opened = body.find("{")
            holder_uses = []                # (accesses, end of the holder's name)
            for m in _ASSIGN_RE.finditer(body, max(0, opened)):
                holder = held(m.group("name"))
                if holder and inlines.method(holder[0], "operator="):
                    holder_uses.append((inlines.through(cls, m.group("name"), holder, "operator="), m.end("name")))
            for m in _CALL_RE.finditer(body, max(0, opened)):
                holder = held(m.group("base")) if m.group("op") == "." else None
                if holder and inlines.method(holder[0], m.group("name")):
                    holder_uses.append((inlines.through(cls, m.group("base"), holder, m.group("name")),
                                        m.end("base")))
            consumed = {end for _found, end in holder_uses}

            for kind, ctype, offset, base, span in accesses(body):
                if kind == "member" and base == "this" and span[1] in consumed:
                    continue
                ff["total"] += 1
                if kind == "member":
                    member, decl_class = ctype, declared_at(base, span[0])
                    if decl_class is None and base in ("arg0", "this"):
                        decl_class = cls
                    if decl_class is None and typed_member(base):
                        decl_class = typed_member(base)[1]      # through a typed member (`_visualContext->x`)
                    if decl_class and decl_class in synth_structs and \
                            any(f[1] == member for f in synth_structs[decl_class]):
                        stats["synthetic"] += 1
                        ff["synthetic"] += 1
                        fc["synthetic"] += 1
                    elif decl_class in classes and \
                            any(f[1] == member for f in classes[decl_class]["fields"]):
                        stats["recovered"] += 1
                        ff["recovered"] += 1
                        fc["recovered"] += 1
                        stats["by_class"][decl_class] = stats["by_class"].get(decl_class, 0) + 1
                    elif rec and any(f[1] == member for f in rec["fields"]):
                        stats["recovered"] += 1
                        ff["recovered"] += 1
                        fc["recovered"] += 1
                        stats["by_class"][cls] = stats["by_class"].get(cls, 0) + 1
                    else:
                        stats["other_members"] += 1
                        ff["other_members"] += 1
                        fc["other"] += 1
                    continue
                if kind == "castmember":
                    member, decl_class = ctype, base
                    if decl_class in classes and \
                            any(f[1] == member for f in classes[decl_class]["fields"]):
                        stats["recovered"] += 1
                        ff["recovered"] += 1
                        fc["recovered"] += 1
                        stats["by_class"][decl_class] = \
                            stats["by_class"].get(decl_class, 0) + 1
                    else:
                        stats["other_members"] += 1
                        ff["other_members"] += 1
                        fc["other"] += 1
                    continue
                stats["offset_casts"] += 1
                ff["offset_casts"] += 1
                fc["raw"] += 1
                if rec is None or offset is None or base not in ("arg0", "this"):
                    continue
                field = rec["by_offset"].get(offset)
                if not field:
                    continue
                observed[(cls, offset)][ctype] += 1
                stats["typeable"] += 1
                stats["typeable_by_class"][cls] = stats["typeable_by_class"].get(cls, 0) + 1
                stats["accesses"].append({"file": path, "function": name, "class": cls,
                                          "offset": offset, "field": field[0],
                                          "cast_type": ctype})
            # a reference to a class reads its fields with `.`, as a pointer does with `->` (`other._refCount` in
            # `igObject(const igObject &other)`)
            refs = {var: t for t, var in REF_DECL_RE.findall(body) if t in classes and var not in decls}
            if refs:
                for m in DOT_RE.finditer(body):
                    if m.group(1) not in refs:
                        continue
                    ref_class = refs[m.group(1)]
                    ff["total"] += 1
                    if any(f[1] == m.group(2) for f in classes[ref_class]["fields"]):
                        stats["recovered"] += 1
                        ff["recovered"] += 1
                        fc["recovered"] += 1
                        stats["by_class"][ref_class] = stats["by_class"].get(ref_class, 0) + 1
                    else:
                        stats["other_members"] += 1
                        ff["other_members"] += 1
                        fc["other"] += 1
            # a constructor of a converted (polymorphic) class stores the class's vtable into `_vtable`: the
            # compiler writes the store the C form spelled (`self->_vtable = (int)&g_X_vtable[0]`)
            if rec and cls in converted and name.rsplit("::", 2)[-2:] == [cls, cls] and \
                    any(f[1] == "_vtable" for f in rec["fields"]):
                ff["total"] += 1
                stats["recovered"] += 1
                ff["recovered"] += 1
                fc["recovered"] += 1
                stats["by_class"][cls] = stats["by_class"].get(cls, 0) + 1
            # and constructs the holder members the class declares (`self->_poolName = 0` in the C form), from the
            # member-initialiser list or by their default constructors
            if cls and "::" in name and name.rsplit("::", 2)[-2:] == [cls, cls]:
                init = re.search(r"\)\s*:(.*)$", body[:max(0, opened)], re.S)
                credit(inlines.constructed(cls, {n for n, _a in initializers(init.group(1))} if init else ()), fc)
            if rec and "::" in name:
                # a member function reads its class's fields by their bare names (`_visualContext`), not
                # through a pointer: each use of a field name that is not a parameter, a local or a member
                # of another object is an access on the receiver
                fields = {f[1] for f in rec["fields"]}
                for m in IDENT_RE.finditer(body, max(0, opened)):
                    if m.group(1) in fields and m.group(1) not in shadowed and m.end(1) not in consumed:
                        ff["total"] += 1
                        stats["recovered"] += 1
                        ff["recovered"] += 1
                        fc["recovered"] += 1
                        stats["by_class"][cls] = stats["by_class"].get(cls, 0) + 1
            # what the body runs through inline members: `_Meta->isValid()`, `meta->isValid()`, a bare inline member
            # of the class, a typed member's (`_visualContext->x()`), and a holder member's (above)
            for m in _CALL_RE.finditer(body, max(0, opened)):
                call, base, op = m.group("name"), m.group("base"), m.group("op")
                if call in _KEYWORDS:
                    continue
                if base is None:
                    if "::" in name and call not in shadowed:
                        credit(inlines.run(cls, call), fc)
                    continue
                owner = cls if base in ("this", "arg0") and op == "->" else decls.get(base) if op == "->" else None
                member = typed_member(base) if owner is None and base not in ("this", "arg0") else None
                if member and member[0] in ("ptr", "smart") and op == "->":
                    credit(inlines.run(member[1], call), fc)
                elif owner:
                    credit(inlines.run(owner, call), fc)
            for found, _end in holder_uses:
                credit(found, fc)
    # the compiler's part of a destructor the source defines: the members' destruction and the bases' destructors
    for cls, fc, ff in user_destructors:
        for (owner, _field), n in inlines.implicit_destructor(cls, defined_destructors).items():
            ff["total"] += n
            stats["recovered"] += n
            ff["recovered"] += n
            fc["recovered"] += n
            stats["by_class"][owner] = stats["by_class"].get(owner, 0) + n
    # an implicit destructor has no text: its member releases are counted once for the class whose destructor the
    # compiled code holds
    implicit = implicit_destructors(root, defined_destructors)
    if implicit:
        ff = stats["by_folder"].setdefault("(implicit)", dict(total=0, offset_casts=0, recovered=0, synthetic=0,
                                                              other_members=0, files=0))
        for cls in implicit:
            fc = stats["per_function"].setdefault(("(implicit)", "%s::~%s" % (cls, cls)), collections.Counter())
            for (owner, _field), n in inlines.implicit_destructor(cls, defined_destructors).items():
                ff["total"] += n
                stats["recovered"] += n
                ff["recovered"] += n
                fc["recovered"] += n
                stats["by_class"][owner] = stats["by_class"].get(owner, 0) + n
    stats["total"] = (stats["offset_casts"] + stats["recovered"] + stats["synthetic"] +
                      stats["other_members"])
    for ff in stats["by_folder"].values():
        ff["recovered_pct"] = round(100.0 * ff["recovered"] / max(1, ff["total"]), 2)
    stats["pairs"] = len(observed)
    stats["conflicting_pairs"] = sum(1 for v in observed.values() if len(v) > 1)
    stats["recovered_pct"] = round(100.0 * stats["recovered"] / max(1, stats["total"]), 2)
    stats["typeable_pct"] = round(100.0 * stats["typeable"] / max(1, stats["total"]), 2)
    return stats


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--reflection", default="data/reflection.json")
    ap.add_argument("--src", default="src")
    ap.add_argument("--json")
    ap.add_argument("--by-class", action="store_true")
    ap.add_argument("--untyped", metavar="FILE", help="list the untyped accesses in one file")
    ap.add_argument("--baseline", default="config/typed-coverage.json",
                    help="recorded coverage this run is compared against")
    ap.add_argument("--check", action="store_true",
                    help="fail unless this run matches the baseline (what CI runs)")
    ap.add_argument("--update-baseline", action="store_true",
                    help="record this run as the baseline (commit the result)")
    args = ap.parse_args()

    if args.untyped:
        raw = open(args.untyped).read()
        for kind, ctype, offset, base, span in accesses(strip_comments_and_strings(raw)):
            if kind == "cast":
                print("  %-16s +%-6s base=%-12s %s"
                      % (ctype, offset, base, raw[span[0]:span[1]][:60]))
        return

    # One analysis, used by the report, the baseline gate and tools/progress.py, so the
    # published figure and the checked one can never disagree.
    t = measure(args.reflection, args.src)
    total, recovered = t["total"], t["recovered"]
    by_class = collections.Counter(t["by_class"])

    print("typed coverage")
    print("  field accesses in matched C: %d" % total)
    print("    offset casts (untyped):        %5d (%.1f%%)" % (t["offset_casts"], 100.0 * t["offset_casts"] / max(1, total)))
    print("    members on a *recovered* class:%5d (%.1f%%)" % (recovered, t["recovered_pct"]))
    print("    members on a synthetic layout:%5d (%.1f%%)   (automatch's `struct G`)" % (t["synthetic"], 100.0 * t["synthetic"] / max(1, total)))
    print("    other member accesses:        %5d (%.1f%%)" % (t["other_members"], 100.0 * t["other_members"] / max(1, total)))
    print("  raw casts on the named receiver at a reflected offset (mechanically convertible): %d (%.1f%% of accesses)"
          % (t["typeable"], t["typeable_pct"]))
    print("  files parsed: %d of %d" % (t["parsed"], t["files"]))
    print("  distinct (class, offset) pairs with both evidence sources: %d" % t["pairs"])
    print("  pairs where the matched C uses more than one cast type: %d "
          "(a conversion has to pick one, or leave them raw)" % t["conflicting_pairs"])
    print("\n  by top-level src folder (comments and string literals excluded):")
    print("    %-12s %6s %9s %9s %9s %9s %7s" % ("folder", "files", "accesses", "recovered",
                                                "raw", "synthetic", "typed%"))
    for folder, ff in sorted(t["by_folder"].items(), key=lambda kv: -kv[1]["total"]):
        print("    %-12s %6d %9d %9d %9d %9d %6.1f%%"
              % (folder, ff["files"], ff["total"], ff["recovered"], ff["offset_casts"],
                 ff["synthetic"], ff["recovered_pct"]))
    if args.by_class:
        print("\n  recovered accesses by class (what the baseline tracks):")
        for cls, n in by_class.most_common(25):
            print("    %-42s %4d" % (cls, n))
        print("\n  raw casts on the named receiver at a reflected offset, by class (convertible now):")
        for cls, n in collections.Counter(t["typeable_by_class"]).most_common(10):
            print("    %-42s %4d" % (cls, n))

    measured = {"recovered": recovered, "total": total,
                "offset_casts": t["offset_casts"], "synthetic": t["synthetic"],
                "by_class": dict(by_class), "typeable": t["typeable"],
                "by_folder": {k: {kk: vv for kk, vv in v.items()}
                              for k, v in sorted(t["by_folder"].items())}}

    if args.update_baseline:
        json.dump({"note": "Baseline for tools/typed_coverage.py --check. The gate is on the "
                           "*count* of recovered accesses, never on the percentage: the m2c loop "
                           "keeps adding matched (and so untyped) C, so the ratio can fall while "
                           "the count only grows. Update it deliberately with --update-baseline "
                           "and commit, so every change in coverage is a reviewed diff.",
                   **measured}, open(args.baseline, "w"), indent=1, sort_keys=True)
        print("\nrecorded baseline: %s (%d recovered of %d accesses)" % (args.baseline, recovered, total))
        return

    if args.check:
        try:
            base = json.load(open(args.baseline))
        except FileNotFoundError:
            print("typed coverage: no baseline at %s — run --update-baseline" % args.baseline)
            raise SystemExit(1)
        was = base.get("recovered", 0)
        base_class = base.get("by_class", {})
        moved = {k for k in set(base_class) | set(by_class)
                 if base_class.get(k, 0) != by_class.get(k, 0)}
        if recovered == was and not moved:
            print("typed coverage: %d recovered accesses, baseline matches" % recovered)
            return
        if recovered == was:
            # the count held but the accesses changed owner -- still a change worth reviewing,
            # otherwise a class could lose its typing invisibly
            print("typed coverage: MOVED — %d recovered accesses unchanged, but %d class(es) differ"
                  % (recovered, len(moved)))
            for cls in sorted(moved):
                print("    %-42s %+d" % (cls, by_class.get(cls, 0) - base_class.get(cls, 0)))
            print("    run --update-baseline and commit %s to record it" % args.baseline)
            raise SystemExit(1)
        print("typed coverage: %s — %d recovered accesses, baseline %d (%+d)"
              % ("REGRESSION" if recovered < was else "GAIN", recovered, was, recovered - was))
        for cls in sorted(set(base.get("by_class", {})) | set(by_class)):
            delta = by_class.get(cls, 0) - base.get("by_class", {}).get(cls, 0)
            if delta:
                print("    %-42s %+d" % (cls, delta))
        print("    %d of %d accesses are still raw casts" % (t["offset_casts"], total))
        if recovered < was:
            print("    a drop means typing was removed, or moved to another class: restore it, "
                  "or update the baseline deliberately if the move was intended")
        else:
            print("    run --update-baseline and commit %s, so the gain is recorded"
                  % args.baseline)
        raise SystemExit(1)

    if args.json:
        json.dump(measured, open(args.json, "w"), indent=1, sort_keys=True)
        print("\nwrote %s" % args.json)


if __name__ == "__main__":
    main()
