#!/usr/bin/env python3
"""declarations.py — where the C symbols are declared, and whether each declaration states the real type.

The convention: a symbol is declared once, in a header, with the type its definition has, and the file
that defines it includes that header. Every declaration in src/ and include/ is read here (comments,
strings, preprocessor lines and `#if 0` arms blanked; class and function bodies skipped) and judged
against the definitions in src/. Four kinds of debt come out of it; tools/progress.py counts them in the
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
               until it is named or decompiled, the unit that uses it is its home.
varargs        a prototype that does not state the parameters of a symbol that has them: a whole list of
               `(...)`, unless a C definition of the symbol is itself variadic (a symbol with no C
               definition counts: `(...)` states no type, and no definition says the list is variable),
               or a C `()` list for a function whose C definition takes parameters.
type conflict  a declaration whose type differs from the symbol's C definition, compared after
               normalising whitespace, parameter names, `struct`/`class`/`union`/`enum` keywords, integer
               spellings (`unsigned int` = `unsigned`), typedefs with one meaning across the tree,
               array parameters (= pointers) and top-level `const` on parameters and return types: data
               type, array against scalar or array length, return type, parameter count and types. A
               function is compared when both sides have C linkage (a C++ declaration with other
               parameters is another overload); data is always compared. A `(...)` list and a C `()`
               list compare the return type only (the first is the varargs debt; the second states no
               parameters). A symbol with no C definition, or whose C definitions disagree with each
               other, has nothing to compare against and never counts here.
header conflict a symbol declared in two or more headers whose declarations disagree with each other
               (functions with C linkage and data; definitions not needed, so assembly symbols count).

Stock library source (src/third_party/) is its authors' text: its declarations are not counted and do not
fail a function, but its definitions are the reference for the code that calls into it.

    python3 tools/declarations.py                          # the four counts
    python3 tools/declarations.py --list varargs [PATH]    # local | varargs | conflicts | headers
"""
import argparse
import bisect
import collections
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

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
    typedef of that name in the tree agrees."""

    def __init__(self):
        self.raw = collections.defaultdict(set)
        self._resolved = {}

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
            if tk not in ("const", "volatile") and (tk[0].isalpha() or tk[0] == "_"):
                resolved = self.resolve(tk, depth) if tk in self.raw else None
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
                 "explicit_c", "lang", "block", "file_c")

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


def collect_typedefs(scanned, types):
    for text_, _offset, is_def, _c, _ns, _body, _at in scanned[2]:
        stripped = text_.strip()
        if not is_def and re.match(r"(?:__extern_C\s+)?typedef\b", stripped):
            types.add_typedef(re.sub(r"^__extern_C\s+", "", stripped))


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
            out.append(Decl(path=rel, line=line, lang=lang, block=block,
                            **dict(f, explicit_c=f["explicit_c"] or c_block)))

    for text_, offset, is_def, c_block, in_ns, body, body_offset in stmts:
        if in_ns and not c_block and not text_.lstrip().startswith("__extern_C"):
            continue                                   # a namespace member is not a C symbol
        add(text_, offset, is_def, c_block, False)
        if body is not None and "extern" in body:
            for m in _BLOCK_EXTERN.finditer(body):
                add(m.group(1), body_offset + m.start(1), False, c_block, True)
    return out


# ---- the index ---------------------------------------------------------------------------------------
class Index:
    """Every declaration and definition under `root`/src and `root`/include, the translation units they
    belong to, and the debt each declaration carries."""

    def __init__(self, root=ROOT):
        self.root = root
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
        for s in scanned.values():
            collect_typedefs(s, self.types)
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
        for d in candidates:
            # an unnamed placeholder, or a symbol still in assembly that one unit uses, has its
            # declaration where it is used until it is named or decompiled
            if PLACEHOLDER.fullmatch(d.name) or (d.name not in defined and len(consumers[d.name]) == 1):
                continue
            self.local.append(d)
            self.bad.add(id(d))
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
        whose C definition takes parameters."""
        if d.kind != "func" or d.is_def:
            return False
        if d.bare_varargs:
            return d.name not in self.variadic
        target = self.definition.get(d.name)
        return d.params is None and target is not None and target.kind == "func" and bool(target.params)

    def conflicts_with_definition(self, d):
        """Whether declaration `d` states a type its symbol's C definition does not have."""
        target = self.definition.get(d.name)
        if target is None or target is d:
            return False
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

    def counts(self):
        return {"decl.local_externs": len(self.local), "decl.varargs": len(self.varargs),
                "decl.type_conflicts": len(self.conflicts), "decl.header_conflicts": len(self.header_conflicts)}

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
    ap.add_argument("--list", choices=("local", "varargs", "conflicts", "headers"))
    ap.add_argument("path", nargs="?", help="with --list: only declarations in files under this path")
    a = ap.parse_args(argv)
    idx = index()
    if not a.list:
        for k, v in idx.counts().items():
            print("%-24s %d" % (k, v))
        return 0
    if a.list == "headers":
        for n in idx.header_conflicts:
            print(n)
        return 0
    rows = {"local": idx.local, "varargs": idx.varargs, "conflicts": idx.conflicts}[a.list]
    want = a.path and os.path.relpath(os.path.abspath(a.path), ROOT).replace(os.sep, "/")
    for d in rows:
        if want and not (d.path == want or d.path.startswith(want.rstrip("/") + "/")):
            continue
        extra = ""
        if a.list == "conflicts":
            t = idx.definition[d.name]
            extra = "   defined %s:%d as %s" % (t.path, t.line, t.signature())
        print("%s:%d: %s%s" % (d.path, d.line, d.signature(), extra))
    return 0


if __name__ == "__main__":
    sys.exit(main())
