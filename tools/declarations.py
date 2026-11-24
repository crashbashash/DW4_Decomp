#!/usr/bin/env python3
"""declarations.py — where the C symbols are declared, and whether each declaration states the real type.

The convention: a symbol is declared once, in a header, with the type its definition has, and the file
that defines it includes that header. Every declaration in src/ and include/ is read here (comments,
strings, preprocessor lines and `#if 0` arms blanked; class and function bodies skipped) and judged
against the definitions in src/. Five kinds of debt come out of it; tools/progress.py counts them in the
debt ratchet (docs/engine/debt-ratchet.md) and fails a function's `declarations` readable check when a
symbol its body uses carries one of the first three:

local extern   a declaration, in a unit's own text, of a symbol another unit defines. A unit's own text is
               its file (`.c`, `.cpp`), the `.inc` fragments it includes and any header outside
               `include/` no other unit includes (a library's unity header such as CoreLibrary.h); a
               header under `include/` is a subject home even while one unit includes it. A declaration there is a
               function prototype, `extern` data at file scope, or `extern` inside a function body. A
               prototype of the unit's own symbol (a C++ unit's `extern "C"` linkage line, a library
               header's own prototypes) is not one. Neither is a declaration of an unnamed placeholder
               (`FUN_<va>`, `DAT_<va>`) or of a symbol with no C definition that only one unit declares:
               until it is named or decompiled, the unit that uses it is its home. A copy the owner
               approved (a `local-decl` row of config/source-approvals.tsv, docs/engine/source-approvals.md:
               the symbol and how many copies of it the tree keeps) is not counted and does not fail a
               function, while the tree holds exactly that many; any other count, or none, voids the row. An approved copy
               is no `varargs` or type-conflict debt either: what it states differently from the
               definition is the reason it is kept.
varargs        a prototype that does not state the parameters of a symbol that has them: a whole list of
               `(...)`, unless a C definition of the symbol is itself variadic (a symbol with no C
               definition counts: `(...)` states no type, and no definition says the list is variable),
               or a C `()` list for a function whose C definition takes parameters.
type conflict  a declaration whose type differs from the symbol's C definition, compared after
               normalising whitespace, parameter names, `struct`/`class`/`union`/`enum` keywords, integer
               spellings (`unsigned int` = `unsigned`), typedefs with one meaning across the tree,
               macros every definition of which only decorates (a calling convention, a memory model, an
               attribute or nothing: libpng's `PNGAPI`, zlib's `FAR`), array parameters (= pointers) and
               top-level `const` on parameters and return types: data
               type, array against scalar or array length, return type, parameter count and types. A
               function is compared when both sides have C linkage (a C++ declaration with other
               parameters is another overload); data is always compared. A `(...)` list and a C `()`
               list compare the return type only (the first is the varargs debt; the second states no
               parameters). A symbol with no C definition, or whose C definitions disagree with each
               other, has nothing to compare against and never counts here. A difference found that way
               is checked again as the compiler reads both sides: the definition in each unit that
               compiles it, the declaration in those of them that include it (else in each unit that does),
               with the object-like macros defined before each expanded (not function-like ones, nor one
               `#undef`-ed or defined under a condition other than an include guard, `#if 0`/`#if 1` or
               `__cplusplus`) and the typedefs that unit sees, so a typedef the tree spells two ways reads
               as each unit defines it. It counts only when they still differ. The C `()` check of
               varargs reads the definition the same way.
header conflict a symbol declared in two or more headers whose declarations disagree with each other
               (functions with C linkage and data; definitions not needed, so assembly symbols count).
named placeholder
               a `FUN_<va>`/`DAT_<va>` identifier in the code of src/ or include/ (macro bodies included) whose
               address config/SLUS-20836/symbols.txt or data-names.tsv gives a recovered name: the build binds
               it by address, so it links either way, and a rename keyed on the old name passes it by.

Stock library source (src/third_party/) is its authors' text: its declarations are not counted and do not
fail a function, but its definitions are the reference for the code that calls into it.

    python3 tools/declarations.py                          # the five counts
    python3 tools/declarations.py --list varargs [PATH]    # local | varargs | conflicts | headers | placeholders | members

`--list local` also prints the approved copies, marked `[approved #anchor]`, so they stay visible.
"""
import argparse
import bisect
import collections
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import sourceapprovals  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
UNIT_EXT = (".c", ".cpp")
FRAGMENT_EXT = (".inc",)
HEADER_EXT = (".h", ".hpp")
STOCK = "src/third_party/"
PATCH_DIR = "src/sony/libkernl/kpatch/"
TMP_PREFIX = "dw4u_"

_COMMENT_OR_STRING = re.compile(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\\n])*\"|'(?:\\.|[^'\\\n])*'", re.S)
_LINKAGE = re.compile(r'\bextern\s*"C(\+\+)?"')
_DIRECTIVE = re.compile(r"[ \t]*#[ \t]*(\w+)(.*)")
_INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]*"([^"]+)"', re.M)
_ATTR = re.compile(r"\b(?:__attribute__|__declspec)\s*\(\((?:[^()]|\([^()]*\))*\)\)|\b__declspec\s*\([^()]*\)"
                   r"|\b(?:__asm__|__asm|asm)\s*\([^()]*\)")
_DECORATION = re.compile(r"\b(?:__cdecl|_cdecl|__stdcall|_stdcall|__fastcall|_fastcall|__pascal|__export|__import"
                         r"|__far|_far|far|__near|_near|near|__huge|_huge|huge)\b")
_STORAGE = re.compile(r"\b(?:extern|static|inline|__inline__|__inline|register|virtual|explicit|mutable|"
                      r"__extern_C|__extern_CPP)\b")
_ELABORATED = re.compile(r"\b(?:struct|class|union|enum|typename)\b")
_TOKEN = re.compile(r"[A-Za-z_]\w*|\.\.\.|\S")
_INT_WORDS = {"int", "char", "short", "long", "unsigned", "signed"}
_TYPE_WORDS = _INT_WORDS | {"void", "float", "double", "bool", "_Bool", "const", "volatile", "struct", "class",
                            "union", "enum", "typename", "extern", "static", "inline", "register"}
_NAME_BEFORE_PAREN = re.compile(r"(operator\s*\S+|~?[A-Za-z_]\w*(?:\s*::\s*~?[A-Za-z_]\w*)*)\s*$")
_SKIP_STATEMENT = re.compile(r"(?:template|using|friend|namespace|static_assert|asm|__asm|__asm__|operator|return)\b")
_BLOCK_EXTERN = re.compile(r"(?<=[;{}])\s*((?:__extern_C|extern)\b[^;{}]*);")
_LANG_ANY, _LANG_C, _LANG_CXX = 0, 1, 2
PLACEHOLDER = re.compile(r"(?:FUN|DAT)_[0-9a-fA-F]{6,8}")


# ---- text --------------------------------------------------------------------------------------------
def _cpp_kind(directive, rest):
    rest = rest.strip()
    if directive == "ifdef":
        return "cxx" if rest == "__cplusplus" else "other"
    if directive == "ifndef":
        return "nocxx" if rest == "__cplusplus" else "other"
    if re.fullmatch(r"defined\s*\(?\s*__cplusplus\s*\)?", rest):
        return "cxx"
    if re.fullmatch(r"!\s*defined\s*\(?\s*__cplusplus\s*\)?", rest):
        return "nocxx"
    return {"0": "zero", "1": "one"}.get(rest, "other")


def clean(text):
    """(code, line languages): comments, strings and preprocessor lines blanked, the dead arm of
    `#if 0`/`#if 1` blanked too, `extern "C"` spelled `__extern_C`; the line structure kept. The language
    of a line is _LANG_C or _LANG_CXX inside an arm of `#ifdef __cplusplus`, else _LANG_ANY."""
    text = _LINKAGE.sub(lambda m: ("__extern_CPP" if m.group(1) else "__extern_C").ljust(len(m.group(0))), text)
    text = _COMMENT_OR_STRING.sub(lambda m: "".join("\n" if c == "\n" else " " for c in m.group(0)), text)
    if "#" not in text:
        return text, None
    lines = text.split("\n")
    langs = [_LANG_ANY] * len(lines)
    stack, continued = [], False
    for i, line in enumerate(lines):
        if continued or _DIRECTIVE.match(line):
            if not continued:
                m = _DIRECTIVE.match(line)
                word = m.group(1)
                if word in ("if", "ifdef", "ifndef"):
                    stack.append([_cpp_kind(word, m.group(2)), False])
                elif word == "else" and stack:
                    stack[-1][1] = True
                elif word == "elif" and stack:
                    stack[-1] = ["other", False]
                elif word == "endif" and stack:
                    stack.pop()
            continued = line.rstrip().endswith("\\")
            lines[i] = " " * len(line)
            continue
        dead = c = cxx = False
        for kind, in_else in stack:
            dead |= (kind == "zero" and not in_else) or (kind == "one" and in_else)
            c |= (kind == "cxx" and in_else) or (kind == "nocxx" and not in_else)
            cxx |= (kind == "cxx" and not in_else) or (kind == "nocxx" and in_else)
        if dead or (c and cxx):
            lines[i] = " " * len(line)
        elif c or cxx:
            langs[i] = _LANG_C if c else _LANG_CXX
    return "\n".join(lines), langs


def _split_top(s, sep=","):
    parts, depth, start = [], 0, 0
    for i, ch in enumerate(s):
        if ch in "([{<":
            depth += 1
        elif ch in ")]}>":
            depth -= 1
        elif ch == sep and depth == 0:
            parts.append(s[start:i])
            start = i + 1
    parts.append(s[start:])
    return parts


def _first_paren(s):
    depth = 0
    for i, ch in enumerate(s):
        if ch == "<":
            depth += 1
        elif ch == ">":
            depth -= 1
        elif ch == "(" and depth <= 0:
            return i
    return -1


def _close(s, i, open_="(", close=")"):
    depth = 0
    for k in range(i, len(s)):
        if s[k] == open_:
            depth += 1
        elif s[k] == close:
            depth -= 1
            if depth == 0:
                return k
    return len(s) - 1


def _top_equals(s):
    depth = 0
    for i, ch in enumerate(s):
        if ch in "([{<":
            depth += 1
        elif ch in ")]}>":
            depth -= 1
        elif ch == "=" and depth == 0 and s[i + 1:i + 2] != "=" and s[i - 1:i] not in ("=", "!", "<", ">"):
            return i
    return -1


def directive_lines(text):
    """[(directive, rest) or None] for each line of `text`: the preprocessor line starting there (comments
    blanked, continuation lines joined onto it), None for any other line or a continuation."""
    text = _COMMENT_OR_STRING.sub(
        lambda m: m.group(0) if m.group(0)[0] in "\"'" else "".join("\n" if c == "\n" else " " for c in m.group(0)),
        text)
    lines = text.split("\n")
    out, i = [None] * len(lines), 0
    while i < len(lines):
        m = _DIRECTIVE.match(lines[i])
        if m:
            start, full = i, lines[i]
            while full.rstrip().endswith("\\") and i + 1 < len(lines):
                i += 1
                full = full.rstrip()[:-1] + " " + lines[i]
            m = _DIRECTIVE.match(full)
            out[start] = (m.group(1), m.group(2))
        i += 1
    return out


_WORD = re.compile(r"[A-Za-z_]\w*")


def expand(text, macros):
    """`text` with the object-like `macros` ({name: body}) replaced until none is left, or None when the
    replacement does not settle (macros that name each other)."""
    if not macros:
        return text
    for _ in range(16):
        new = _WORD.sub(lambda m: " %s " % macros[m.group(0)] if m.group(0) in macros else m.group(0), text)
        if new == text:
            return text
        text = new
    return None


def decoration_macros(texts):
    """The object-like macros every definition of which, in any arm of any file, only decorates a
    declaration: a calling convention, a memory model, an attribute or nothing (libpng's `PNGAPI`, zlib's
    `FAR`). Whichever of them the compiler takes, they add nothing to a type."""
    bodies, opaque = collections.defaultdict(set), set()
    for text in texts:
        if "#" not in text:
            continue
        for d in directive_lines(text):
            if not d or d[0] not in ("define", "undef"):
                continue
            m = re.match(r"\s*([A-Za-z_]\w*)(\()?(.*)", d[1], re.S)
            if not m:
                continue
            if d[0] == "undef" or m.group(2):
                opaque.add(m.group(1))
            else:
                bodies[m.group(1)].add(m.group(3).strip())
    return {name for name, found in bodies.items()
            if name not in opaque and name not in _TYPE_WORDS
            and not any(_DECORATION.sub(" ", _ATTR.sub(" ", b)).strip() for b in found)}


# ---- types -------------------------------------------------------------------------------------------
def _canon_int(words):
    unsigned = "unsigned" in words
    if "char" in words:
        return ("unsigned " if unsigned else "signed " if "signed" in words else "") + "char"
    if "short" in words:
        return ("unsigned " if unsigned else "") + "short"
    longs = words.count("long")
    if longs:
        return ("unsigned " if unsigned else "") + ("long long" if longs > 1 else "long")
    return "unsigned" if unsigned else "int"


class Types:
    """Type normalisation with the tree's typedefs: a typedef name stands for its target when every
    typedef of that name in the tree agrees. A translation unit's view (`parent` the tree's) takes the
    typedefs that unit sees first and falls back to the tree's for names it has none of."""

    def __init__(self, parent=None):
        self.raw = collections.defaultdict(set)
        self._resolved = {}
        self.parent = parent
        self.decoration = parent.decoration if parent is not None else set()

    def known(self, name):
        return name in self.raw or (self.parent is not None and self.parent.known(name))

    _MODE = re.compile(r"__attribute__\s*\(\(\s*(?:__)?mode(?:__)?\s*\(\s*(?:__)?(QI|HI|SI|DI|SF|DF)(?:__)?\s*\)\s*\)\)")
    _MODE_TYPE = {"QI": "char", "HI": "short", "SI": "int", "DI": "long long", "SF": "float", "DF": "double"}

    def add_typedef(self, stmt):
        # gcc's `typedef int DItype __attribute__((mode(DI)))` declares the mode's type, not the written one
        mode = self._MODE.search(stmt)
        body = _ATTR.sub(" ", stmt)
        body = re.sub(r"^\s*typedef\b", "", body).strip()
        if mode:
            unsigned = re.match(r"\s*unsigned\b", body)
            body = re.sub(r"^\s*(?:unsigned\s+|signed\s+)?(?:int|char|short|long|float|double)\b(?:\s+(?:int|long))*",
                          ("unsigned " if unsigned else "") + self._MODE_TYPE[mode.group(1)], body, count=1)
        p = _first_paren(body)
        if p >= 0:                                    # function or function-pointer typedef: opaque
            m = re.search(r"\(\s*[*&]?\s*([A-Za-z_]\w*)\s*\)", body[p:]) or _NAME_BEFORE_PAREN.search(body[:p])
            if m:
                self.raw[m.group(1)].add(None)
            return
        parts = _split_top(body)
        base = None
        for i, part in enumerate(parts):
            m = re.match(r"(.*?)([*&\s]*)([A-Za-z_]\w*)\s*((?:\[[^\]]*\]\s*)*)$", part.strip(), re.S)
            if not m:
                return
            if i == 0:
                head = m.group(1)
                head = re.sub(r"\{\}", " ", head)
                base = head
                tag = re.match(r"\s*(?:const\s+)?(?:struct|class|union|enum)\s+([A-Za-z_]\w*)\s*(?::[^*&]*)?$", head)
                if re.match(r"\s*(?:struct|class|union|enum)\s*$", head):
                    base = m.group(3)                 # an anonymous record: the typedef name is its name
                elif tag:
                    base = tag.group(1)
            name = m.group(3)
            target = (base + " " + m.group(2) + ("*" if m.group(4) else "")).strip()
            if target != name:
                self.raw[name].add(target)

    def resolve(self, name, depth=0):
        if name in self._resolved:
            return self._resolved[name]
        if name not in self.raw and self.parent is not None:
            return self.parent.resolve(name, depth)
        targets = self.raw.get(name)
        out = None
        if targets and None not in targets and depth < 8:
            self._resolved[name] = None                # cycle guard
            seen = {self.norm(t, depth + 1) for t in targets}
            out = seen.pop() if len(seen) == 1 else None
        self._resolved[name] = out
        return out

    def norm(self, t, depth=0):
        t = _ATTR.sub(" ", t)
        t = _ELABORATED.sub(" ", t)
        t = _STORAGE.sub(" ", t)
        out, run = [], []
        for tk in _TOKEN.findall(t):
            if tk in _INT_WORDS:
                run.append(tk)
                continue
            if run:
                out.append(_canon_int(run))
                run = []
            if tk in self.decoration:
                continue
            if tk not in ("const", "volatile") and (tk[0].isalpha() or tk[0] == "_"):
                resolved = self.resolve(tk, depth) if self.known(tk) else None
                if resolved and resolved != tk:
                    out.append(resolved)
                    continue
            out.append(tk)
        if run:
            out.append(_canon_int(run))
        s = " ".join(out)
        s = re.sub(r"\s*([*&<>,()\[\]])\s*", r"\1", s)
        # `const T` and `T const` are one type
        s = re.sub(r"^const ([^*&]+?)(?=$|[*&])", r"\1 const", s)
        return s.strip()

    def strip_top_cv(self, t):
        """`t` without the qualifiers that are not part of a function's type (parameter, return)."""
        star = max(t.rfind("*"), t.rfind("&"))
        head, tail = t[:star + 1], t[star + 1:]
        if star < 0:
            return re.sub(r"\s*\b(?:const|volatile)\b\s*", " ", t).strip()
        return head + re.sub(r"\s*\b(?:const|volatile)\b\s*", " ", tail).rstrip()

    def param(self, p):
        """A parameter's type without its name; None for an empty or `void` one."""
        eq = _top_equals(p)
        p = (p[:eq] if eq >= 0 else p).strip()
        if p in ("", "void"):
            return None
        if p == "...":
            return "..."
        m = re.match(r"(.*?)\(\s*([*&])\s*(?:[A-Za-z_]\w*)?\s*((?:\[[^\]]*\]\s*)*)\)\s*\((.*)\)\s*$", p, re.S)
        if m:
            inner = [self.param(q) for q in _split_top(m.group(4))]
            return "%s(%s)(%s)" % (self.strip_top_cv(self.norm(m.group(1))), m.group(2),
                                   ",".join(q for q in inner if q is not None))
        array = "[" in p
        p = re.sub(r"\[[^\]]*\]", " ", p).strip()
        toks = _TOKEN.findall(p)
        if len(toks) >= 2 and re.fullmatch(r"[A-Za-z_]\w*", toks[-1]) and toks[-1] not in _TYPE_WORDS:
            rest = [t for t in toks[:-1] if t not in ("const", "volatile", "struct", "class", "union", "enum")]
            if rest and not (len(toks) >= 2 and toks[-2] == "::"):
                p = p[:p.rfind(toks[-1])]
        t = self.strip_top_cv(self.norm(p))
        return t + "*" if array else t

    def params(self, text, unspecified_empty):
        """A tuple of parameter types, or None for a C `()` list (no parameters stated)."""
        if not text.strip():
            return None if unspecified_empty else ()
        out = [self.param(q) for q in _split_top(text)]
        return tuple(q for q in out if q is not None)


# ---- declarations ------------------------------------------------------------------------------------
class Decl:
    __slots__ = ("name", "kind", "ret", "params", "type", "dims", "path", "line", "is_def", "static",
                 "explicit_c", "lang", "block", "file_c", "text")

    def __init__(self, **kw):
        for k in self.__slots__:
            setattr(self, k, kw.get(k))

    @property
    def bare_varargs(self):
        return self.kind == "func" and self.params == ("...",)

    @property
    def variadic(self):
        return self.kind == "func" and bool(self.params) and self.params[-1] == "..."

    def signature(self):
        if self.kind == "func":
            return "%s %s(%s)" % (self.ret, self.name, "?" if self.params is None else ", ".join(self.params))
        return "%s %s%s" % (self.type, self.name, "".join("[%s]" % d for d in self.dims))


def _parse(stmt, types, is_def, unspecified_empty):
    """[Decl fields dict] for one statement or definition head (bodies collapsed to `{}`)."""
    s = _ATTR.sub(" ", stmt).strip()
    explicit_c = False
    if s.startswith("__extern_C"):
        explicit_c, s = True, s[len("__extern_C"):].strip()
    elif s.startswith("__extern_CPP"):
        s = s[len("__extern_CPP"):].strip()
    if not s or _SKIP_STATEMENT.match(s):
        return []
    if s.startswith("typedef"):
        return []
    eq = _top_equals(s)
    head = s if eq < 0 else s[:eq]
    p = _first_paren(head)
    prefix = head[:p] if p >= 0 else head
    flags = set(re.findall(r"\b(extern|static)\b", prefix)) | ({"extern"} if explicit_c else set())
    common = dict(explicit_c=explicit_c, static="static" in flags, is_def=is_def)
    if p >= 0:
        after = head[p + 1:].lstrip()
        if re.match(r"[*&]\s*(?:const\s+)?[A-Za-z_]\w*\s*(?:\[[^\]]*\]\s*)*\)\s*\(", after):
            # a function pointer: `ret (*name[N])(params)`
            m = re.match(r"[*&]\s*(?:const\s+)?([A-Za-z_]\w*)\s*((?:\[[^\]]*\]\s*)*)\)\s*\((.*)\)", after, re.S)
            if not m:
                return []
            inner = types.params(m.group(3), unspecified_empty)
            t = "%s(*)(%s)" % (types.strip_top_cv(types.norm(prefix)), "?" if inner is None else ",".join(inner))
            dims = tuple(d.strip() for d in re.findall(r"\[([^\]]*)\]", m.group(2)))
            return [dict(common, name=m.group(1), kind="data", type=t, dims=dims,
                         is_def=is_def or "extern" not in flags or eq >= 0)]
        m = _NAME_BEFORE_PAREN.search(prefix)
        if not m or "::" in m.group(1) or m.group(1).startswith(("operator", "~")):
            return []
        name = m.group(1)
        ret = _STORAGE.sub(" ", prefix[:m.start()]).strip()
        if not ret or name in _TYPE_WORDS or not re.search(r"[A-Za-z_]", ret):
            return []
        close = _close(head, p)
        tail = head[close + 1:].strip()
        if tail.startswith("("):                       # a function returning a function pointer: skip
            return []
        # an old-style definition states its parameters' types after the list: compare its return only
        params = None if is_def and ";" in tail else types.params(head[p + 1:close], unspecified_empty)
        if params and any(q != "..." and re.fullmatch(r"[-\d.x]+|&.*|\w+\(.*", q) for q in params):
            return []                                  # `Type object(1, &x);`: a constructed object
        return [dict(common, name=name, kind="func", ret=types.strip_top_cv(types.norm(ret)), params=params)]
    # data: `type a, *b, c[4]`
    out, base = [], None
    for i, part in enumerate(_split_top(s)):
        e = _top_equals(part)
        has_init = e >= 0 or "{}" in part
        part = (part[:e] if e >= 0 else part).strip()
        m = re.match(r"(.*?)([A-Za-z_]\w*)\s*((?:\[[^\]]*\]\s*)*)$", part, re.S)
        if not m:
            return out
        if i == 0:
            base_full = m.group(1)
            if not re.search(r"[A-Za-z_]", _STORAGE.sub(" ", base_full)) or m.group(2) in _TYPE_WORDS:
                return []
            if re.fullmatch(r"\s*(?:struct|class|union|enum)\s*", _STORAGE.sub(" ", base_full)):
                return []                              # `struct Foo;`
            if "{}" in base_full:
                return []                              # a record defined with its variable: a view, not a symbol
            base = base_full.rstrip(" \t\n*&")
            stars = base_full[len(base):]
        else:
            if base is None or not re.fullmatch(r"[\s*&]*", m.group(1)):
                return out
            stars = m.group(1)
        name = m.group(2)
        if "::" in name:
            continue
        dims = tuple(d.strip() for d in re.findall(r"\[([^\]]*)\]", m.group(3)))
        out.append(dict(common, name=name, kind="data", type=types.norm(base + " " + stars), dims=dims,
                        is_def=is_def or has_init or "extern" not in flags))
    return out


def _skip_block(s, i):
    depth = 0
    for m in re.compile(r"[{}]").finditer(s, i):
        depth += 1 if m.group(0) == "{" else -1
        if depth == 0:
            return m.end()
    return len(s)


_STATEMENT_END = re.compile(r"[{};]")
# `int f(a, b) int a;`: the head of an old-style definition up to its first parameter declaration
_KR_HEAD = re.compile(r"\s*[A-Za-z_][\w\s*]*?\b[A-Za-z_]\w*\s*\(\s*[A-Za-z_]\w*(?:\s*,\s*[A-Za-z_]\w*)*\s*\)"
                      r"\s*[A-Za-z_][^;{}()=]*$")


def statements(code):
    """[(text, offset, is_definition, extern_c_block, in_namespace, body, body_offset)] for the top-level
    statements of `code`: declarations ending in `;` and function definitions (the head, with the body).
    `extern "C"` and namespace blocks are transparent; class, enum and initialiser bodies are collapsed to
    `{}`."""
    out, frames, pieces, start, at, i = [], [], [], 0, 0, 0
    while True:
        m = _STATEMENT_END.search(code, i)
        if not m:
            break
        ch, j = m.group(0), m.start()
        if not pieces:
            at = start
        if ch == ";":
            text = "".join(pieces) + code[start:j]
            if not pieces and _KR_HEAD.match(text):
                # an old-style definition, `int f(a, b) int a; char *b; {`: its parameter declarations
                # belong to the head
                brace = code.find("{", j)
                between = code[j + 1:brace] if brace >= 0 else ""
                if brace >= 0 and re.fullmatch(r"(?:[^;{}()]+;)*\s*", between):
                    i = brace
                    continue
            out.append((text, at, False, "C" in frames, "N" in frames, None, None))
            pieces, start, i = [], j + 1, j + 1
        elif ch == "}":
            if frames:
                frames.pop()
            pieces, start, i = [], j + 1, j + 1
        else:
            head = "".join(pieces) + code[start:j]
            bare = head.strip()
            if not pieces and bare == "__extern_C":
                frames.append("C")
                start = i = j + 1
                continue
            if not pieces and re.fullmatch(r"(?:inline\s+)?namespace(?:\s+[A-Za-z_]\w*)?|__extern_CPP", bare):
                frames.append("X" if bare == "__extern_CPP" else "N")
                start = i = j + 1
                continue
            end = _skip_block(code, j)
            is_function = ("(" in bare and _top_equals(bare) < 0
                           and not re.match(r"(?:typedef\s+)?(?:struct|class|union|enum)\b[^(]*$", bare))
            if is_function and not pieces:
                out.append((head, at, True, "C" in frames, "N" in frames, code[j:end], j))
                pieces, start, i = [], end, end
            else:
                pieces.append(code[start:j] + "{}")
                start = i = end
    return out


def scan(text):
    """(cleaned code, line languages, top-level statements) of one file's text."""
    code, langs = clean(text)
    return code, langs, statements(code)


def typedef_statements(scanned):
    """The `typedef` statements of one scanned file (`scan`)."""
    out = []
    for text_, _offset, is_def, _c, _ns, _body, _at in scanned[2]:
        stripped = text_.strip()
        if not is_def and re.match(r"(?:__extern_C\s+)?typedef\b", stripped):
            out.append(re.sub(r"^__extern_C\s+", "", stripped))
    return out


def parse_file(scanned, rel, types, file_is_c):
    """[Decl] for every declaration and definition in one scanned file (`scan`)."""
    code, langs, stmts = scanned
    newlines = [m.start() for m in re.finditer("\n", code)]
    out = []

    def add(stmt, offset, is_def, c_block, block):
        lead = len(stmt) - len(stmt.lstrip())
        line = bisect.bisect_right(newlines, offset + lead) + 1
        lang = langs[line - 1] if langs is not None else _LANG_ANY
        for f in _parse(stmt, types, is_def, unspecified_empty=file_is_c(lang)):
            out.append(Decl(path=rel, line=line, lang=lang, block=block, text=stmt,
                            **dict(f, explicit_c=f["explicit_c"] or c_block)))

    for text_, offset, is_def, c_block, in_ns, body, body_offset in stmts:
        if in_ns and not c_block and not text_.lstrip().startswith("__extern_C"):
            continue                                   # a namespace member is not a C symbol
        add(text_, offset, is_def, c_block, False)
        if body is not None and "extern" in body:
            for m in _BLOCK_EXTERN.finditer(body):
                add(m.group(1), body_offset + m.start(1), False, c_block, True)
    return out


# ---- members -----------------------------------------------------------------------------------------
_CLASS_HEAD = re.compile(r"(?:typedef\s+)?(?:struct|class)\s+([A-Za-z_]\w*)\s*(?::[^;{}()]*)?$")
_NAMESPACE_HEAD = re.compile(r"namespace\s+([A-Za-z_]\w*)$")
_ACCESS = re.compile(r"^\s*(?:(?:public|private|protected)\s*:\s*)+")
_FUNCTION_MACRO = re.compile(r"\s*([A-Za-z_]\w*)\(([^()]*)\)(.*)", re.S)
_SCOPE_PREFIX = re.compile(r"\b(?:[A-Za-z_]\w*\s*::\s*)+")


class Member:
    """A member function or static data member: declared in a class body (`static`, and `inline` when the body
    defines it), or defined out of its class."""
    __slots__ = ("cls", "name", "kind", "ret", "params", "const", "static", "inline", "path", "line")

    def __init__(self, **kw):
        for k in self.__slots__:
            setattr(self, k, kw.get(k))

    def signature(self):
        if self.kind == "data":
            return "%s %s::%s" % (self.ret, self.cls, self.name)
        return "%s %s::%s(%s)%s" % (self.ret, self.cls, self.name, ", ".join(self.params),
                                    " const" if self.const else "")


def function_macros(texts):
    """{name: (parameters, body)} of the function-like macros of `texts` defined one way only: an object macro
    such as Alchemy's `IG_OBJECT_DEFINE(CLASSNAME)` declares members, so a class body is read expanded."""
    found = collections.defaultdict(set)
    for text in texts:
        if "#" not in text or "define" not in text:
            continue
        for d in directive_lines(text):
            if d and d[0] == "define":
                m = _FUNCTION_MACRO.match(d[1])
                if m:
                    found[m.group(1)].add((tuple(p.strip() for p in m.group(2).split(",") if p.strip()),
                                           m.group(3).strip()))
    return {name: bodies.pop() for name, bodies in found.items() if len(bodies) == 1}


def expand_function_macros(text, macros):
    """`text` with each invocation of a function-like macro in `macros` replaced by its body (arguments
    substituted), until none is left. A call whose argument count is not the macro's is no invocation: the
    preprocessor would reject it, so it names something else (newlib's three-argument `unlink` macro beside
    igGuiComponent's `unlink()`)."""
    if not macros:
        return text
    pattern = re.compile(r"\b(%s)\s*\(" % "|".join(re.escape(n) for n in sorted(macros, key=len, reverse=True)))
    for _ in range(8):
        out, at, changed = [], 0, False
        for m in pattern.finditer(text):
            if m.start() < at:
                continue
            close = _close(text, m.end() - 1)
            params, body = macros[m.group(1)]
            args = [a.strip() for a in _split_top(text[m.end():close])]
            if args == [""] and not params:
                args = []
            if len(args) != len(params) and "..." not in params:
                continue
            sub = dict(zip(params, args))
            out.append(text[at:m.start()])
            out.append(" %s " % _WORD.sub(lambda w: sub.get(w.group(0), w.group(0)), body))
            at, changed = close + 1, True
        if not changed:
            return text
        out.append(text[at:])
        text = "".join(out)
    return text


def _cxx_view(code, langs):
    """Cleaned code as a C++ compiler reads it: the lines only C reads (`#ifndef __cplusplus` arms) blanked."""
    if langs is None:
        return code
    lines = code.split("\n")
    return "\n".join(" " * len(line) if lang == _LANG_C else line for line, lang in zip(lines, langs))


def _parse_member(stmt, cls, types, path, line, out_of_class):
    """A Member for one member declaration or definition head (`static void arkRegister()`,
    `bool isValid() const`, `igMetaObject *igRenderer::_Meta`), or None. `out_of_class` heads name their
    class (`T Class::name(...)`), and the class they name is returned with them."""
    s = _ACCESS.sub("", _ATTR.sub(" ", stmt)).strip()
    if not s or re.match(r"(?:friend|typedef|using|template|enum|struct|class|union|operator)\b", s):
        return None
    eq = _top_equals(s)
    head = (s if eq < 0 else s[:eq]).strip()
    p = _first_paren(head)
    if p < 0:
        m = re.match(r"(.*?[\s*&])((?:[A-Za-z_]\w*\s*::\s*)*)([A-Za-z_]\w*)\s*((?:\[[^\]]*\]\s*)*)$", head, re.S)
        if not m or (out_of_class and not m.group(2)) or (not out_of_class and "static" not in m.group(1).split()):
            return None
        owner = re.sub(r"\s+", "", m.group(2))[:-2] if out_of_class else cls
        ret = types.norm(_SCOPE_PREFIX.sub("", _STORAGE.sub(" ", m.group(1))) + "".join("*" for _ in
                                                                                        re.findall(r"\[", m.group(4))))
        return Member(cls=owner, name=m.group(3), kind="data", ret=ret, params=(), const=False,
                      static=not out_of_class, inline=False, path=path, line=line)
    if re.match(r"[*&]\s*(?:const\s+)?[A-Za-z_]\w*\s*(?:\[[^\]]*\]\s*)*\)\s*\(", head[p + 1:].lstrip()):
        return None                                    # a function-pointer field
    m = _NAME_BEFORE_PAREN.search(head[:p])
    if not m:
        return None
    qualified = re.sub(r"\s+", "", m.group(1))
    if out_of_class != ("::" in qualified):
        return None
    owner, name = (qualified.rsplit("::", 1) if out_of_class else (cls, qualified))
    if name.startswith("operator") or name in _TYPE_WORDS:
        return None
    close = _close(head, p)
    tail = head[close + 1:]
    raw = _STORAGE.sub(" ", head[:m.start()]).strip()
    special = name.lstrip("~") == owner.rsplit("::", 1)[-1]
    if not raw and not special:
        return None                                    # a macro invocation or an expression, not a declaration
    params = types.params(_SCOPE_PREFIX.sub("", head[p + 1:close]), False)
    return Member(cls=owner, name=name, kind="func", ret=types.strip_top_cv(types.norm(_SCOPE_PREFIX.sub("", raw))),
                  params=params, const=bool(re.match(r"\s*const\b", tail)),
                  static=bool(re.search(r"\bstatic\b", head[:m.start()])), inline=False, path=path, line=line)


def member_scan(code, rel, types, macros):
    """([class body member Member], [out-of-class member Member], {class: [(path, line)] of its bodies}) for one
    file's C++ view (`_cxx_view`): class bodies are read with the function-like macros expanded, nested classes
    and namespaces qualify their names."""
    declared, defined, bodies = [], [], collections.defaultdict(list)
    newlines = [m.start() for m in re.finditer("\n", code)]

    def line_of(offset):
        return bisect.bisect_right(newlines, offset) + 1

    def scope(text, i, end, ns, cls, where):
        start, tail = i, False
        while True:
            m = _STATEMENT_END.search(text, i, end)
            if not m:
                return end
            ch, j = m.group(0), m.start()
            head = text[start:j].strip()
            first = start + len(text[start:j]) - len(text[start:j].lstrip())
            if ch == "}":
                return j + 1
            if ch == ";":
                if not tail and head:
                    if cls is not None:
                        member = _parse_member(head, cls, types, rel, where(first), False)
                        if member:
                            declared.append(member)
                    elif "::" in head:
                        member = _parse_member(head, None, types, rel, where(first), True)
                        if member and member.kind == "data":
                            member.cls = "::".join(ns + [member.cls])
                            defined.append(member)
                start, i, tail = j + 1, j + 1, False
                continue
            close = _skip_block(text, j)
            bare = _ACCESS.sub("", head).strip()
            namespace = _NAMESPACE_HEAD.match(bare)
            record = _CLASS_HEAD.match(bare)
            if bare in ("__extern_C", "__extern_CPP"):
                scope(text, j + 1, end, ns, cls, where)
                start = i = close
            elif namespace and cls is None:
                scope(text, j + 1, end, ns + [namespace.group(1)], None, where)
                start = i = close
            elif record:
                name = "::".join(([cls] if cls else ns) + [record.group(1)])
                bodies[name].append((rel, where(j)))
                inner = text[j + 1:close - 1]
                expanded = expand_function_macros(inner, macros)
                if expanded == inner:
                    scope(text, j + 1, close - 1, ns, name, where)
                else:                                  # what an object macro declares is on the class head's line
                    head_line = where(j)
                    scope(expanded, 0, len(expanded), ns, name, lambda _offset: head_line)
                start, i, tail = close, close, True
            elif "(" in bare and _top_equals(bare) < 0 and not tail:
                if cls is not None:
                    member = _parse_member(bare, cls, types, rel, where(first), False)
                    if member:
                        member.inline = True
                        declared.append(member)
                elif "::" in bare:
                    member = _parse_member(re.sub(r"\)\s*:[^{}]*$", ")", bare), None, types, rel, where(first), True)
                    if member and member.kind == "func":
                        member.cls = "::".join(ns + [member.cls])
                        defined.append(member)
                start = i = close
            else:
                i = close                              # an initialiser, an enum or union body: part of the statement

    scope(code, 0, len(code), [], None, line_of)
    return declared, defined, bodies


# ---- the index ---------------------------------------------------------------------------------------
class Index:
    """Every declaration and definition under `root`/src and `root`/include, the translation units they
    belong to, and the debt each declaration carries."""

    def __init__(self, root=ROOT, approvals=None):
        """`approvals` is {symbol: (count, evidence)} of the `local-decl` rows; None reads them from the
        tree's config/source-approvals.tsv."""
        self.root = root
        if approvals is None:
            table = sourceapprovals.load(os.path.join(root, "config", "source-approvals.tsv"))
            approvals = {symbol: row for (kind, symbol), row in table.items() if kind == sourceapprovals.LOCAL_DECL}
        self.approvals = approvals
        self.types = Types()
        self.texts, self.includes = {}, {}
        for top in ("src", "include"):
            for dirpath, dirs, files in os.walk(os.path.join(root, top)):
                dirs.sort()
                for f in sorted(files):
                    if f.startswith(TMP_PREFIX) or not f.endswith(UNIT_EXT + FRAGMENT_EXT + HEADER_EXT):
                        continue
                    path = os.path.join(dirpath, f)
                    rel = os.path.relpath(path, root).replace(os.sep, "/")
                    if rel.startswith(PATCH_DIR):
                        continue
                    try:
                        with open(path, errors="replace") as fh:
                            self.texts[rel] = fh.read()
                    except OSError:
                        continue
        for rel, text in self.texts.items():
            self.includes[rel] = [t for t in (self._resolve(rel, inc) for inc in _INCLUDE.findall(text)) if t]
        self.types.decoration.update(decoration_macros(self.texts.values()))
        # units: each .c/.cpp with the `.inc` fragments it includes; headers reached from it
        self.units, self.unit_of = {}, collections.defaultdict(list)
        self.header_langs = collections.defaultdict(set)
        for rel in self.texts:
            if not rel.startswith("src/") or not rel.endswith(UNIT_EXT):
                continue
            lang = _LANG_C if rel.endswith(".c") else _LANG_CXX
            files, headers = [rel], []
            self._closure(rel, files, headers, set([rel]))
            self.units[rel] = dict(lang=lang, files=files, headers=headers)
            for f in files:
                self.unit_of[f].append(rel)
            for h in headers:
                self.header_langs[h].add(lang)
        for rel in self.texts:                         # a fragment nothing includes is its own unit
            if rel.startswith("src/") and rel.endswith(FRAGMENT_EXT) and rel not in self.unit_of:
                files, headers = [rel], []
                self._closure(rel, files, headers, set([rel]))
                self.units[rel] = dict(lang=_LANG_CXX, files=files, headers=headers)
                for f in files:
                    self.unit_of[f].append(rel)
        scanned = {rel: scan(text) for rel, text in self.texts.items()}
        self.typedefs = {rel: typedef_statements(s) for rel, s in scanned.items()}
        for stmts in self.typedefs.values():
            for stmt in stmts:
                self.types.add_typedef(stmt)
        self._scopes, self._unit_files, self._directives = {}, {}, {}
        self._placeholders = self._member_conflicts = None
        self._cxx = {rel: _cxx_view(s[0], s[1]) for rel, s in scanned.items() if not self.stock(rel)}
        self.decls = {rel: parse_file(s, rel, self.types, self._file_is_c(rel)) for rel, s in scanned.items()}
        self._judge()

    def _resolve(self, rel, inc):
        for base in (os.path.dirname(rel), "include", ""):
            cand = os.path.normpath(os.path.join(base, inc)).replace(os.sep, "/")
            if cand in self.texts:
                return cand
        return None

    def _closure(self, rel, files, headers, seen):
        for inc in self.includes.get(rel, ()):
            if inc in seen:
                continue
            seen.add(inc)
            (headers if inc.endswith(HEADER_EXT) else files).append(inc)
            self._closure(inc, files, headers, seen)

    def _file_is_c(self, rel):
        """f(line language) -> whether `()` in that line means "parameters not stated" (C)."""
        if rel.endswith(HEADER_EXT):
            langs = None
        else:
            langs = {self.units[u]["lang"] for u in self.unit_of.get(rel, ())} or {_LANG_CXX}
        def is_c(lang):
            if lang != _LANG_ANY:
                return lang == _LANG_C
            reach = langs if langs is not None else self.header_langs.get(rel, set())
            return _LANG_C in reach
        return is_c

    def stock(self, rel):
        return rel.startswith(STOCK)

    def _decl_c(self, d):
        """Whether a declaration gives its symbol C linkage (in the unit or some unit that includes it)."""
        if d.explicit_c or d.lang == _LANG_C:
            return True
        if d.lang == _LANG_CXX:
            return False
        if d.path.endswith(HEADER_EXT):
            return _LANG_C in self.header_langs.get(d.path, ())
        return any(self.units[u]["lang"] == _LANG_C for u in self.unit_of.get(d.path, ()))

    def _judge(self):
        # definitions: the C definition of each symbol
        c_names = collections.defaultdict(set)         # unit -> names declared `extern "C"` it sees
        for u, info in self.units.items():
            for f in info["files"] + info["headers"]:
                c_names[u].update(d.name for d in self.decls.get(f, ()) if d.explicit_c)
        self.unit_defs = {u: set() for u in self.units}
        defs, defined = collections.defaultdict(list), set()
        for rel, decls in self.decls.items():
            for d in decls:
                if not d.is_def:
                    continue
                for u in self.unit_of.get(rel, ()):
                    self.unit_defs[u].add(d.name)
                if d.static:
                    continue
                defined.add(d.name)
                if d.kind == "func":
                    if not (self._decl_c(d) or any(d.name in c_names[u] for u in self.unit_of.get(rel, ()))):
                        continue
                defs[d.name].append(d)
        self.variadic = {n for n, ds in defs.items() if any(d.variadic for d in ds)}
        self.definition = {}
        for n, ds in defs.items():
            sigs = {self._sig(d) for d in ds}
            if len(sigs) == 1:
                self.definition[n] = ds[0]
        # the debt of each declaration
        self.local, self.varargs, self.conflicts = [], [], []
        self.bad = set()                               # ids of declarations that fail a function
        header_units = collections.defaultdict(set)
        for u, info in self.units.items():
            for h in info["headers"]:
                header_units[h].add(u)
        self.header_units = header_units
        candidates, consumers = [], collections.defaultdict(set)
        for rel, decls in self.decls.items():
            if self.stock(rel):
                continue
            if rel.endswith(HEADER_EXT):
                # a header outside include/ that only one unit includes (a library's unity header) is
                # that unit's own text; a header under include/ is a home however many units include it
                single = len(header_units.get(rel, ())) == 1 and not rel.startswith("include/")
                units_here = tuple(header_units[rel]) if single else ()
            else:
                units_here = tuple(self.unit_of.get(rel, ()))
            own = set().union(*(self.unit_defs[u] for u in units_here)) if units_here else set()
            for d in decls:
                if d.is_def:
                    continue
                if units_here and d.name not in own and not all(self._dead_in(d, u) for u in units_here):
                    candidates.append(d)
                    consumers[d.name].update(units_here)
                if self.unprototyped(d):
                    self.varargs.append(d)
                    self.bad.add(id(d))
                if self.conflicts_with_definition(d):
                    self.conflicts.append(d)
                    self.bad.add(id(d))
        # an unnamed placeholder, or a symbol still in assembly that one unit uses, has its
        # declaration where it is used until it is named or decompiled
        counted = [d for d in candidates
                   if not (PLACEHOLDER.fullmatch(d.name) or (d.name not in defined and len(consumers[d.name]) == 1))]
        self.local_declared = collections.Counter(d.name for d in counted)
        self.local_listing = []                        # (declaration, evidence anchor of its approval or None)
        approved = set()
        for d in counted:
            row = self.approvals.get(d.name)
            if row is not None and row[0] == self.local_declared[d.name]:
                self.local_listing.append((d, row[1]))
                approved.add(id(d))
                continue
            self.local_listing.append((d, None))
            self.local.append(d)
            self.bad.add(id(d))
        # an approved copy is kept as written, and what it states differently from the definition (a
        # `volatile`, `long` for `int`, no parameters) is why it is kept: it is no other debt either
        if approved:
            self.varargs = [d for d in self.varargs if id(d) not in approved]
            self.conflicts = [d for d in self.conflicts if id(d) not in approved]
            self.bad -= approved
        by_name = collections.defaultdict(lambda: collections.defaultdict(set))
        for rel, decls in self.decls.items():
            if not rel.endswith(HEADER_EXT) or self.stock(rel):
                continue
            for d in decls:
                if not d.is_def and (d.kind == "data" or self._decl_c(d)):
                    by_name[d.name][self._sig(d)].add(rel)
        self.header_conflicts = sorted(n for n, sigs in by_name.items()
                                       if len(sigs) > 1 and len(set().union(*sigs.values())) > 1)
        self._unit_bad = {}

    def _dead_in(self, d, unit):
        lang = self.units[unit]["lang"]
        return d.lang != _LANG_ANY and d.lang != lang

    def _sig(self, d):
        if d.kind == "func":
            return ("func", d.ret, d.params)
        return ("data", d.type, d.dims)

    def unprototyped(self, d):
        """Whether declaration `d` leaves its parameters unstated where the symbol has fixed ones: `(...)`
        unless a C definition is variadic (counted with no C definition too), or a C `()` for a function
        whose C definition takes parameters (as the units that define it read it)."""
        if d.kind != "func" or d.is_def:
            return False
        if d.bare_varargs:
            return d.name not in self.variadic
        target = self.definition.get(d.name)
        if not (d.params is None and target is not None and target.kind == "func" and bool(target.params)):
            return False
        return not self._agrees_as_compiled(d, target, lambda _decl, defn: defn.kind == "func" and not defn.params)

    def conflicts_with_definition(self, d):
        """Whether declaration `d` states a type its symbol's C definition does not have: read with the
        tree's typedefs, and again, when that finds a difference, as the units that define the symbol read
        both (their object-like macros expanded, their own meaning of a typedef the tree spells two ways)."""
        target = self.definition.get(d.name)
        if target is None or target is d or not self._differs(d, target):
            return False
        return not self._agrees_as_compiled(d, target, lambda decl, defn: not self._differs(decl, defn))

    def _differs(self, d, target):
        """Whether declaration `d` and definition `target`, as parsed, state different types."""
        if d.kind == "func" and target.kind == "func":
            if not self._decl_c(d):
                return False
            if d.ret != target.ret:
                return True
            if d.params is None or target.params is None or d.bare_varargs:
                return False
            return d.params != target.params
        if d.kind == "func" or target.kind == "func":
            # a function declared as data or the reverse; only for C-linkage functions
            fn = d if d.kind == "func" else target
            return self._decl_c(fn)
        if d.type != target.type or len(d.dims) != len(target.dims):
            return True
        return any(a and b and a != b and re.fullmatch(r"0x[0-9a-fA-F]+|\d+", a) and
                   re.fullmatch(r"0x[0-9a-fA-F]+|\d+", b) and int(a, 0) != int(b, 0)
                   for a, b in zip(d.dims, target.dims))

    # ---- a translation unit's view ----
    def _seen_by(self, rel):
        """The units whose compiler reads file `rel`."""
        return sorted(self.header_units.get(rel, ()) if rel.endswith(HEADER_EXT) else self.unit_of.get(rel, ()))

    def _reads(self, u, rel):
        if u not in self._unit_files:
            self._unit_files[u] = set(self.units[u]["files"]) | set(self.units[u]["headers"])
        return rel in self._unit_files[u]

    def _scope(self, u):
        """Unit `u` as its compiler sees it: `types`, a view over the typedefs of every file it includes;
        `order`, for each file it reaches, the preprocessing position of each line; `defines`, its
        object-like macros as [(position, name, body)]; `unsure`, the names it cannot expand (function-like,
        `#undef`, or defined under a condition this cannot decide: only include guards, `#if 0`/`#if 1` and
        `__cplusplus` are decided)."""
        if u in self._scopes:
            return self._scopes[u]
        info = self.units[u]
        types = Types(self.types)
        for f in info["files"] + info["headers"]:
            for stmt in self.typedefs.get(f, ()):
                types.add_typedef(stmt)
        scope = dict(types=types, order={}, defines=[], unsure=set())
        is_cxx, position = info["lang"] == _LANG_CXX, [0]
        decided = {"zero": "dead", "one": "live", "cxx": "live" if is_cxx else "dead",
                   "nocxx": "dead" if is_cxx else "live"}

        def walk(rel, uncertain):
            if rel in scope["order"]:
                return
            if rel not in self._directives:
                self._directives[rel] = directive_lines(self.texts[rel])
            lines = self._directives[rel]
            order = scope["order"][rel] = []

            def advance(upto):                         # number the lines up to `upto` in reading order
                while len(order) <= upto:
                    position[0] += 1
                    order.append(position[0])

            at = [i for i, d in enumerate(lines) if d]
            stack = []
            for k, i in enumerate(at):
                advance(i)
                word, rest = lines[i]
                dead = "dead" in stack
                if word in ("if", "ifdef", "ifndef"):
                    state = "dead" if dead else decided.get(_cpp_kind(word, rest), "unknown")
                    nxt = lines[at[k + 1]] if k + 1 < len(at) else None
                    if (not dead and word == "ifndef" and nxt and nxt[0] == "define"
                            and nxt[1].split()[:1] == rest.split()[:1]):
                        state = "live"                 # an include guard
                    stack.append(state)
                elif word == "elif" and stack:
                    stack[-1] = "dead" if stack[-1] == "live" else "unknown"
                elif word == "else" and stack:
                    stack[-1] = {"live": "dead", "dead": "live"}.get(stack[-1], "unknown")
                elif word == "endif" and stack:
                    stack.pop()
                elif dead:
                    continue
                elif word in ("define", "undef"):
                    m = re.match(r"\s*([A-Za-z_]\w*)(\()?(.*)", rest, re.S)
                    if not m:
                        continue
                    name, body = m.group(1), m.group(3).strip()
                    if (word == "undef" or m.group(2) or uncertain or "unknown" in stack or "#" in body
                            or name in _WORD.findall(body)):
                        scope["unsure"].add(name)
                    else:
                        scope["defines"].append((order[i], name, body))
                elif word == "include":
                    m = re.match(r'\s*"([^"]+)"', rest)
                    target = m and self._resolve(rel, m.group(1))
                    if target:
                        walk(target, uncertain or "unknown" in stack)
            advance(len(lines) - 1)

        walk(u, False)
        self._scopes[u] = scope
        return scope

    def _as_seen(self, d, u):
        """Declaration or definition `d` as unit `u`'s compiler reads it: the object-like macros defined
        before it expanded, and the unit's typedefs; None when that cannot be told."""
        scope = self._scope(u)
        order = scope["order"].get(d.path)
        if order is None or d.line > len(order) or d.text is None:
            return None
        at = order[d.line - 1]
        bodies = collections.defaultdict(set)
        for position, name, body in scope["defines"]:
            if position < at:
                bodies[name].add(body)
        macros = {n: b.pop() for n, b in bodies.items() if len(b) == 1 and n not in scope["unsure"]}
        text = expand(d.text, macros)
        if text is None:
            return None
        is_c = d.lang == _LANG_C or (d.lang == _LANG_ANY and self.units[u]["lang"] == _LANG_C)
        for f in _parse(text, scope["types"], d.is_def, unspecified_empty=is_c):
            if f["name"] == d.name and f["kind"] == d.kind:
                return Decl(path=d.path, line=d.line, lang=d.lang, block=d.block, text=text,
                            **dict(f, explicit_c=f["explicit_c"] or d.explicit_c))
        return None

    def _agrees_as_compiled(self, d, target, same):
        """Whether `same(declaration, definition)` holds with both read as their compilers read them: the
        definition in each unit that compiles it, the declaration in those of them that include it (in
        each unit that reads it when none does). False when any of them cannot be read."""
        def_units = self._seen_by(target.path)
        decl_units = [u for u in def_units if self._reads(u, d.path)] or self._seen_by(d.path)
        if not def_units or not decl_units:
            return False
        defs = [self._as_seen(target, u) for u in def_units]
        decls = [self._as_seen(d, u) for u in decl_units]
        if None in defs or None in decls:
            return False
        return all(same(a, b) for a in decls for b in defs)

    def counts(self):
        return {"decl.local_externs": len(self.local), "decl.varargs": len(self.varargs),
                "decl.type_conflicts": len(self.conflicts), "decl.header_conflicts": len(self.header_conflicts),
                "decl.named_placeholders": len(self.named_placeholders()),
                "decl.member_conflicts": len(self.member_conflicts())}

    def member_conflicts(self):
        """[(definition Member, reason)]: each member defined out of its class (`T Class::name(...) {`,
        `T *Class::datum;`) that no declaration in its class body states the same way: no member of that name,
        parameters and constness, a different return or data type, or one body of the class (another unit's
        view of it) declaring the name only otherwise. Read in each file's C++ view, class bodies with their
        object macros expanded and every type normalised as for the C symbols; a definition whose class has no
        body in the tree is not judged."""
        if self._member_conflicts is not None:
            return self._member_conflicts
        macros = function_macros(self.texts.values())
        declared, defined, bodies = [], [], collections.defaultdict(list)
        scanned = set()

        def read(rel):
            scanned.add(rel)
            d, f, b = member_scan(self._cxx[rel], rel, self.types, macros)
            declared.extend(d)
            defined.extend(f)
            for name, at in b.items():
                bodies[name].extend(at)

        for rel, code in sorted(self._cxx.items()):
            if "::" in code:
                read(rel)
        wanted = {d.cls.rsplit("::", 1)[-1] for d in defined}
        if wanted:
            heads = re.compile(r"\b(?:struct|class)\s+(?:%s)\b[^;{}()]*\{" % "|".join(sorted(wanted)))
            for rel, code in sorted(self._cxx.items()):
                if rel not in scanned and heads.search(code):
                    read(rel)
        by_class = collections.defaultdict(list)
        for m in declared:
            by_class[m.cls].append(m)
        out = []
        for d in defined:
            names = [q for q in bodies if q == d.cls] or [q for q in bodies if q.endswith("::" + d.cls)
                                                           or d.cls.endswith("::" + q)]
            if not names:
                continue
            same = [m for q in names for m in by_class[q] if m.name == d.name and m.kind == d.kind]
            match = [m for m in same if m.params == d.params and m.const == d.const]
            if not match:
                out.append((d, "no declaration of %s in its class states it" % d.name if not same else
                            "its class declares %s otherwise: %s" % (
                                d.name, "; ".join("%s (%s:%d)" % (m.signature(), m.path, m.line) for m in same))))
            elif all(m.ret != d.ret for m in match):
                m = match[0]
                out.append((d, "declared as %s (%s:%d)" % (m.signature(), m.path, m.line)))
            else:
                views = {(m.path, m.cls) for m in same} - {(m.path, m.cls) for m in match}
                if views:
                    path, cls = sorted(views)[0]
                    out.append((d, "%s's body in %s declares %s otherwise" % (cls, path, d.name)))
        self._member_conflicts = out
        return out

    def named_placeholders(self):
        """[(path, line, placeholder, name)]: each `FUN_<va>`/`DAT_<va>` in the code of src/ and include/
        (comments and strings blanked, preprocessor lines kept) whose address the symbol map
        (config/SLUS-20836/symbols.txt) or the data names (data-names.tsv) give a recovered name. The build
        binds such a call by address, so it links either way, and a rename keyed on the old name passes it by."""
        if self._placeholders is None:
            names = {}
            config = os.path.join(self.root, "config", "SLUS-20836")
            for table, col in (("data-names.tsv", 1), ("symbols.txt", 2)):
                try:
                    with open(os.path.join(config, table)) as fh:
                        for row in fh:
                            parts = row.split()
                            if len(parts) > col and not row.startswith("#"):
                                names[int(parts[0], 16)] = parts[col]
                except (OSError, ValueError):
                    continue
            names = {va: n for va, n in names.items() if not PLACEHOLDER.search(n)}
            out = []
            for rel in sorted(self.texts):
                if self.stock(rel) or not PLACEHOLDER.search(self.texts[rel]):
                    continue
                code = _COMMENT_OR_STRING.sub(lambda m: "".join("\n" if c == "\n" else " " for c in m.group(0)),
                                              self.texts[rel])
                for m in re.finditer(r"\b(?:FUN|DAT)_([0-9a-fA-F]{6,8})\b", code):
                    name = names.get(int(m.group(1), 16))
                    if name:
                        out.append((rel, code.count("\n", 0, m.start()) + 1, m.group(0), name))
            self._placeholders = out
        return self._placeholders

    def unit_key(self, path):
        rel = os.path.relpath(os.path.abspath(path), self.root).replace(os.sep, "/")
        return rel

    def bad_names(self, path):
        """The names a function in `path`'s unit may not use: each is declared, in the text the compiler
        sees for that unit, by a local extern, a `(...)` prototype of a non-variadic symbol, or with a type
        its definition does not have."""
        rel = self.unit_key(path)
        if rel in self._unit_bad:
            return self._unit_bad[rel]
        out = set()
        for u in self.unit_of.get(rel, ()) or ([rel] if rel in self.units else ()):
            info = self.units[u]
            for f in info["files"] + info["headers"]:
                if self.stock(f):
                    continue
                out.update(d.name for d in self.decls.get(f, ()) if id(d) in self.bad and not self._dead_in(d, u))
        self._unit_bad[rel] = frozenset(out)
        return self._unit_bad[rel]


_INDEX = {}


def index(root=ROOT):
    if root not in _INDEX:
        _INDEX[root] = Index(root)
    return _INDEX[root]


_MEMBER_ACCESS = re.compile(r"(?:\.|->|::)\s*~?[A-Za-z_]\w*")
_IDENT = re.compile(r"\b[A-Za-z_]\w*\b")


def used_bad(body, bad):
    """The names in `bad` that `body` uses (not as a member after `.`, `->` or `::`)."""
    if not bad:
        return set()
    found = bad.intersection(_IDENT.findall(body))
    if not found:
        return found
    return bad.intersection(_IDENT.findall(_MEMBER_ACCESS.sub(" ", body)))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--list", choices=("local", "varargs", "conflicts", "headers", "placeholders", "members"))
    ap.add_argument("path", nargs="?", help="with --list: only declarations in files under this path")
    a = ap.parse_args(argv)
    idx = index()
    if not a.list:
        for k, v in idx.counts().items():
            print("%-24s %d" % (k, v))
        return 0
    if a.list == "members":
        for d, why in idx.member_conflicts():
            print("%s:%d: %s: %s" % (d.path, d.line, d.signature(), why))
        return 0
    if a.list == "headers":
        for n in idx.header_conflicts:
            print(n)
        return 0
    want = a.path and os.path.relpath(os.path.abspath(a.path), ROOT).replace(os.sep, "/")
    if a.list == "placeholders":
        for path, line, placeholder, name in idx.named_placeholders():
            if not want or path == want or path.startswith(want.rstrip("/") + "/"):
                print("%s:%d: %s is %s" % (path, line, placeholder, name))
        return 0
    rows = {"local": idx.local_listing, "varargs": idx.varargs, "conflicts": idx.conflicts}[a.list]
    for d in rows:
        approved = None
        if a.list == "local":
            d, approved = d
        if want and not (d.path == want or d.path.startswith(want.rstrip("/") + "/")):
            continue
        extra = ""
        if a.list == "conflicts":
            t = idx.definition[d.name]
            extra = "   defined %s:%d as %s" % (t.path, t.line, t.signature())
        if approved:
            extra = "   [approved %s]" % approved
        print("%s:%d: %s%s" % (d.path, d.line, d.signature(), extra))
    return 0


if __name__ == "__main__":
    sys.exit(main())
