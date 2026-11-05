#!/usr/bin/env python3
"""initfields_gen.py [--out DIR] [--order auto|keep] [--verify] [--dry-run] FILE... — retarget a verified C
translation unit of the reflection boilerplate families (`<Class>_InitFields`, and through
`getvtable_stack_gen.py --retarget` the `<Class>_GetVTable` accessors) to the build profile its unit records.

Why.  Phase 3b (docs/engine/build-profiles.md): a unit compiled with exceptions on keeps a 12-byte exception
index record for every function with a frame or a call, and only the C++ front end emits one.  The matched
C bodies of these families therefore verify `code-only` (`exc=missing`) in such units.  The code bytes are
right; the translation unit is the wrong language.  A unit whose compiler differs from the one the body was
shaped for can also disagree on the saved-register order: MWCC 3.0-011126 assigns s0, s1, s2 ... in
declaration order, the 2003 beta (`combat`) in reverse declaration order, so the same statements need the
locals declared in the unit compiler's order.

What it does, per file:
  1. parses the C unit: header comment, `#include`s, struct/union/typedef definitions, prototypes, extern
     data, and the single function definition with its local declarations;
  2. gives every K&R prototype (`int f();`) the parameter list its call sites imply — C++ has no unprototyped
     calls — by typing each argument expression against the locals, structs, externs and the reflected
     headers (`include/dw4/reflected.h`); sites that disagree fall back to `(...)`; a callee whose result is
     stored in a typed pointer gets that return type, and a `(void *)` cast on such a store becomes the
     target's own pointer type (C++ does not convert `void *` implicitly);
  3. orders the local declarations for the unit compiler (`--order auto`: `temp_sN` names carry the retail
     saved register; the default compiler wants s0, s1, s2 ... first-to-last, `combat` last-to-first) or
     keeps them (`--order keep`);
  4. writes `<name>.cpp` (unit exceptions on) or `<name>.c` (off) with the declarations in an `extern "C"`
     block and the body otherwise unchanged, next to the input (a `.c` -> `.cpp` rename goes through
     `git mv` when the input is tracked) or under --out;
  5. with --verify runs tools/verify.py under the unit profile; if the first order fails, it tries the other
     declaration orders (bounded) and keeps the first that verifies `cat=match`; otherwise it reports
     `nomatch` and leaves the input untouched (the candidate stays under --out when given).

The generator never invents names: every identifier comes from the input file.  It does not claim a match;
the report line per file is the verifier's.
"""
import argparse
import itertools
import os
import re
import subprocess
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import unitprofiles  # noqa: E402

DEFAULT_COMPILER = "local/mwcps2/3.0-011126/mwccps2.exe"
DEFAULT_FLAGS = "-O3 -Iinclude"

# ----------------------------------------------------------------------------- source model

PROTO_RE = re.compile(r"^(?P<ret>(?:extern\s+)?(?:struct\s+\w+|[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*?)\s*\**)\s*(?P<name>\b[A-Za-z_]\w*)\s*\((?P<args>[^)]*)\)\s*;\s*(?P<cmt>/\*.*\*/)?\s*$")
EXTERN_RE = re.compile(r"^extern\s+(?P<type>(?:struct\s+\w+|[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*?)\s*\**)\s*(?P<name>[A-Za-z_]\w*)\s*(?P<arr>\[[^\]]*\])?\s*;\s*(?P<cmt>/\*.*\*/)?\s*$")
DEF_RE = re.compile(r"^(?P<ret>(?:struct\s+\w+|[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*?)\s*\**)\s*(?P<name>[A-Za-z_]\w*)\s*\(\s*(?:void)?\s*\)\s*\{\s*$")
DECL_RE = re.compile(r"^\s+(?P<type>(?:struct\s+\w+|[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*?)\s*\**)\s*(?P<name>[A-Za-z_]\w*)\s*(?P<arr>\[[^\]]*\])?\s*;\s*(?:/\*.*\*/)?\s*$")
MULTI_DECL_RE = re.compile(r"^\s+(?P<type>(?:struct\s+\w+|[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*?))\s+(?P<list>\**\s*[A-Za-z_]\w*(?:\s*\[[^\]]*\])?(?:\s*,\s*\**\s*[A-Za-z_]\w*(?:\s*\[[^\]]*\])?)+)\s*;\s*$")
MEMBER_RE = re.compile(r"(?P<type>(?:struct\s+\w+|union\s+\w+|[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*?)\s*\**)\s*(?P<name>[A-Za-z_]\w*)\s*(?P<arr>\[[^\]]*\])?\s*(?::\s*\d+)?\s*;")

BASE_WORDS = {"int", "char", "short", "long", "unsigned", "signed", "float", "double", "void", "bool", "const", "volatile"}


def norm(t):
    """Normalise a type spelling: one space between words, `*` separated by one space, no trailing blanks."""
    t = t.replace("*", " * ")
    t = re.sub(r"\s+", " ", t).strip()
    t = t.replace(" * ", " *").replace("* *", "**")
    t = re.sub(r"\s*\*", " *", t)
    t = re.sub(r"\*\s+\*", "**", t)
    return t.strip()


def is_ptr(t):
    return t.endswith("*")


def deref(t):
    t = t.strip()
    return norm(t[:-1]) if t.endswith("*") else "int"


class Struct:
    def __init__(self, tag, members):
        self.tag = tag
        self.members = members           # name -> (type, is_array)


class Unit:
    def __init__(self):
        self.head = []                   # leading comment lines
        self.includes = []
        self.types = []                  # struct/union/typedef definition texts, in order
        self.structs = {}                # tag or typedef name -> Struct
        self.protos = []                 # dicts: ret, name, args (None for K&R), cmt, text
        self.externs = []                # dicts: type, name, arr, cmt, text
        self.fn = None                   # dict: ret, name, decls (list of dicts), body (list of lines)
        self.other = []                  # top-level lines kept verbatim (static tables ...)


def parse_struct_members(body):
    members = {}
    depth = 0
    # flatten nested aggregates: a nested `struct { ... } name;` is one member of unknown layout
    out = []
    i = 0
    while i < len(body):
        c = body[i]
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
        if depth == 0:
            out.append(c)
        i += 1
    for m in MEMBER_RE.finditer("".join(out)):
        if m.group("type").strip() in ("struct", "union"):
            continue
        members[m.group("name")] = (norm(m.group("type")), bool(m.group("arr")))
    return members


def parse_unit(text):
    u = Unit()
    lines = text.split("\n")
    i = 0
    n = len(lines)
    in_head = True
    while i < n:
        line = lines[i]
        s = line.strip()
        if in_head and (s.startswith("/*") or s.startswith("*") or s.startswith("//") or s == ""):
            if s.startswith("/*") or s.startswith("*") or s.startswith("//"):
                u.head.append(line)
            i += 1
            continue
        in_head = False
        if s == "":
            i += 1
            continue
        if s.startswith("#include"):
            u.includes.append(line)
            i += 1
            continue
        if s.startswith("/*") and "*/" in s and not re.search(r";\s*$", s):
            u.other.append(line)       # a stray comment between declarations
            i += 1
            continue
        m = re.match(r"^(typedef\s+)?(struct|union)\s+(\w+)?\s*\{", s) or re.match(r"^(typedef\s+)?(struct|union)\s*\{", s)
        if m:
            # collect until the closing `};`
            j = i
            depth = 0
            buf = []
            while j < n:
                buf.append(lines[j])
                depth += lines[j].count("{") - lines[j].count("}")
                if depth == 0 and lines[j].rstrip().endswith(";"):
                    break
                j += 1
            txt = "\n".join(buf)
            tm = re.match(r"^(typedef\s+)?(struct|union)\s+(\w+)?\s*\{(.*)\}\s*(\w+)?\s*;", txt, re.S)
            members = parse_struct_members(tm.group(4))
            st = Struct(tm.group(3), members)
            if tm.group(3):
                u.structs[tm.group(3)] = st
            if tm.group(5):
                u.structs[tm.group(5)] = st
            u.types.append(txt)
            i = j + 1
            continue
        m = re.match(r"^typedef\s+(.+?)\s+(\w+)\s*;", s)
        if m:
            u.types.append(line)
            i += 1
            continue
        m = DEF_RE.match(s)
        if m and u.fn is None:
            # function definition: body until a line that is exactly `}`
            j = i + 1
            body = []
            while j < n and lines[j].rstrip() != "}":
                body.append(lines[j])
                j += 1
            decls = []
            k = 0
            while k < len(body):
                dm = DECL_RE.match(body[k])
                mm = MULTI_DECL_RE.match(body[k])
                if dm and "=" not in body[k]:
                    decls.append({"type": norm(dm.group("type")), "name": dm.group("name"),
                                  "arr": dm.group("arr") or "", "text": body[k],
                                  "names": [(dm.group("name"), norm(dm.group("type")), bool(dm.group("arr")))]})
                    k += 1
                elif mm and "=" not in body[k]:
                    base = norm(mm.group("type"))
                    names = []
                    for part in mm.group("list").split(","):
                        pm = re.match(r"^\s*(\**)\s*([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*$", part)
                        if not pm:
                            names = None
                            break
                        names.append((pm.group(2), norm(base + " " + pm.group(1)), bool(pm.group(3))))
                    if names is None:
                        break
                    decls.append({"type": base, "name": names[0][0], "arr": "", "text": body[k], "names": names})
                    k += 1
                elif body[k].strip() == "" and decls:
                    # blank lines may separate declaration groups; stop at the first statement
                    nb = k
                    while nb < len(body) and body[nb].strip() == "":
                        nb += 1
                    if nb < len(body) and (DECL_RE.match(body[nb]) or MULTI_DECL_RE.match(body[nb])) and "=" not in body[nb]:
                        k = nb
                        continue
                    k = nb
                    break
                else:
                    break
            u.fn = {"ret": norm(m.group("ret")), "name": m.group("name"), "decls": decls,
                    "body": body[k:], "pre": body[:k]}
            i = j + 1
            continue
        m = EXTERN_RE.match(s)
        if m and "(" not in s.split("/*")[0]:
            u.externs.append({"type": norm(m.group("type")), "name": m.group("name"), "arr": m.group("arr") or "",
                              "cmt": m.group("cmt") or "", "text": line})
            i += 1
            continue
        m = PROTO_RE.match(s)
        if m:
            args = m.group("args").strip()
            u.protos.append({"ret": norm(m.group("ret").replace("extern", "")), "name": m.group("name"),
                             "args": None if args == "" else args, "cmt": m.group("cmt") or "", "text": line})
            i += 1
            continue
        u.other.append(line)
        i += 1
    return u


# ----------------------------------------------------------------------------- reflected headers

_REFLECTED = {}


def reflected_structs():
    """{typedef name: Struct} for include/dw4/reflected.h (members carry `/* +off` comments)."""
    if _REFLECTED:
        return _REFLECTED
    path = os.path.join(ROOT, "include", "dw4", "reflected.h")
    if not os.path.exists(path):
        return _REFLECTED
    text = open(path, errors="replace").read()
    for m in re.finditer(r"typedef struct (\w+) \{(.*?)\} \1;", text, re.S):
        _REFLECTED[m.group(1)] = Struct(m.group(1), parse_struct_members(m.group(2)))
    return _REFLECTED


# ----------------------------------------------------------------------------- expression typing

TOKEN_RE = re.compile(r"\s*(?:(?P<num>0[xX][0-9a-fA-F]+[uUlL]*|\d+\.\d*(?:[eE][-+]?\d+)?[fF]?|\.\d+[fF]?|\d+[uUlL]*)"
                      r"|(?P<id>[A-Za-z_]\w*)|(?P<op>->|<<|>>|<=|>=|==|!=|&&|\|\||[-+*/%&|^~!<>=?:,.()\[\]]))")


def tokenize(expr):
    toks = []
    pos = 0
    while pos < len(expr):
        m = TOKEN_RE.match(expr, pos)
        if not m or m.end() == pos:
            if expr[pos:].strip() == "":
                break
            raise ValueError("cannot tokenize %r" % expr[pos:pos + 20])
        pos = m.end()
        if m.group("num"):
            toks.append(("num", m.group("num")))
        elif m.group("id"):
            toks.append(("id", m.group("id")))
        else:
            toks.append(("op", m.group("op")))
    return toks


class Typer:
    """Types C expressions against a unit's declarations; records the argument types of every call."""

    def __init__(self, unit):
        self.u = unit
        self.refl = reflected_structs()
        self.locals = {}
        for d in unit.fn["decls"]:
            for name, ty, arr in d.get("names", [(d["name"], d["type"], bool(d["arr"]))]):
                self.locals[name] = (ty, arr)
        # declarations left in the body (`int *pa = (int *)&o;`, `int *p; int *a1; int t;` on one line)
        for line in unit.fn["body"]:
            for piece in line.split(";"):
                m = re.match(r"^\s*(?P<type>(?:struct\s+\w+|[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*?)\s*\**)\s*(?P<name>[A-Za-z_]\w*)\s*(?P<arr>\[[^\]]*\])?\s*(=|$)", piece)
                if not m or m.group("type").split()[0] in ("return", "goto", "else"):
                    continue
                ty = norm(m.group("type"))
                if ty.split()[0] in BASE_WORDS or ty.startswith("struct ") or ty.split()[0] in self.u.structs or ty.split()[0] in self.refl:
                    self.locals.setdefault(m.group("name"), (ty, bool(m.group("arr"))))
        self.externs = {e["name"]: (e["type"], bool(e["arr"])) for e in unit.externs}
        self.rets = {p["name"]: p["ret"] for p in unit.protos}
        self.calls = {}                  # callee -> list of [arg types]

    def struct(self, t):
        t = norm(t)
        tag = t.replace("struct ", "").replace("union ", "").strip()
        if tag in self.u.structs:
            return self.u.structs[tag]
        return self.refl.get(tag)

    def member(self, t, name):
        st = self.struct(deref(t) if is_ptr(t) else t)
        if st and name in st.members:
            mt, arr = st.members[name]
            return mt + (" *" if arr else "")
        return "int"

    # -- parser (precedence climbing; returns a type string)
    def type_of(self, expr):
        self.toks = tokenize(expr)
        self.pos = 0
        t = self.p_comma()
        return t

    def peek(self):
        return self.toks[self.pos] if self.pos < len(self.toks) else ("eof", "")

    def take(self, val=None):
        t = self.peek()
        if val is not None and t[1] != val:
            raise ValueError("expected %r at %r" % (val, self.toks[self.pos:self.pos + 5]))
        self.pos += 1
        return t

    def p_comma(self):
        t = self.p_assign()
        while self.peek()[1] == ",":
            self.take()
            t = self.p_assign()
        return t

    def p_assign(self):
        lhs = self.p_cond()
        if self.peek()[1] == "=" or self.peek()[1] in ("+=", "-="):
            self.take()
            self.p_assign()
            return lhs
        return lhs

    def p_cond(self):
        t = self.p_binary(0)
        if self.peek()[1] == "?":
            self.take()
            a = self.p_comma()
            self.take(":")
            self.p_cond()
            return a
        return t

    PREC = [("||",), ("&&",), ("|",), ("^",), ("&",), ("==", "!="), ("<", ">", "<=", ">="), ("<<", ">>"),
            ("+", "-"), ("*", "/", "%")]

    def p_binary(self, level):
        if level == len(self.PREC):
            return self.p_unary()
        t = self.p_binary(level + 1)
        while self.peek()[0] == "op" and self.peek()[1] in self.PREC[level]:
            op = self.take()[1]
            r = self.p_binary(level + 1)
            if op in ("||", "&&", "==", "!=", "<", ">", "<=", ">="):
                t = "int"
            elif op in ("<<", ">>", "*", "/", "%", "^", "|", "&"):
                t = t if not is_ptr(t) else "int"
                if r in ("double", "float") and op in ("*", "/"):
                    t = r
            else:   # + -
                if is_ptr(t):
                    t = t
                elif is_ptr(r):
                    t = r
                elif "double" in (t, r):
                    t = "double"
                elif "float" in (t, r):
                    t = "float"
        return t

    def p_unary(self):
        tok = self.peek()
        if tok[0] == "op" and tok[1] in ("-", "+", "!", "~"):
            self.take()
            t = self.p_unary()
            return "int" if tok[1] == "!" else t
        if tok[0] == "op" and tok[1] == "&":
            self.take()
            t = self.p_unary()
            return norm(t + " *")
        if tok[0] == "op" and tok[1] == "*":
            self.take()
            t = self.p_unary()
            return deref(t)
        if tok[0] == "op" and tok[1] == "(":
            # cast or parenthesised expression
            save = self.pos
            self.take()
            if self.is_type_start():
                ty = self.p_typename()
                self.take(")")
                self.p_unary()
                return ty
            self.pos = save
        return self.p_postfix()

    def is_type_start(self):
        tok = self.peek()
        if tok[0] != "id":
            return False
        if tok[1] in BASE_WORDS or tok[1] in ("struct", "union"):
            return True
        if tok[1] in self.u.structs or tok[1] in self.refl:
            # a typedef name followed by `*` or `)` is a cast
            nxt = self.toks[self.pos + 1] if self.pos + 1 < len(self.toks) else ("eof", "")
            return nxt[1] in ("*", ")")
        return False

    def p_typename(self):
        words = []
        while self.peek()[0] == "id":
            words.append(self.take()[1])
        stars = ""
        while self.peek()[1] == "*":
            self.take()
            stars += "*"
        return norm(" ".join(words) + " " + stars)

    def p_postfix(self):
        tok = self.take()
        if tok[0] == "num":
            v = tok[1]
            if v.lower().startswith("0x"):
                t = "int"
            elif "." in v or "e" in v.lower():
                t = "float" if v.lower().endswith("f") else "double"
            else:
                t = "int"
        elif tok[0] == "id":
            name = tok[1]
            if self.peek()[1] == "(":
                self.take()
                args = []
                if self.peek()[1] != ")":
                    while True:
                        args.append(self.p_assign())
                        if self.peek()[1] == ",":
                            self.take()
                            continue
                        break
                self.take(")")
                self.calls.setdefault(name, []).append(args)
                t = self.rets.get(name, "int")
            elif name in self.locals:
                ty, arr = self.locals[name]
                t = norm(ty + " *") if arr else ty
            elif name in self.externs:
                ty, arr = self.externs[name]
                t = norm(ty + " *") if arr else ty
            elif name in self.rets:
                t = "fn:" + name
            else:
                t = "int"
        elif tok[1] == "(":
            t = self.p_comma()
            self.take(")")
        else:
            raise ValueError("unexpected token %r" % (tok,))
        while True:
            nxt = self.peek()
            if nxt[1] == "[":
                self.take()
                self.p_comma()
                self.take("]")
                t = deref(t)
            elif nxt[1] == ".":
                self.take()
                t = self.member(t, self.take()[1])
            elif nxt[1] == "->":
                self.take()
                t = self.member(t, self.take()[1])
            else:
                break
        return t


def split_control(piece):
    """`if (COND) REST` / `while (COND) REST` / `else REST` -> [COND, REST...] expressions; plain text -> [text]."""
    out = []
    piece = piece.strip()
    while True:
        piece = re.sub(r"^(else\s*)+", "", piece).strip()
        m = re.match(r"^(if|while)\s*\(", piece)
        if not m:
            break
        depth, j = 0, m.end() - 1
        while j < len(piece):
            depth += (piece[j] == "(") - (piece[j] == ")")
            j += 1
            if depth == 0:
                break
        out.append(piece[m.end():j - 1])
        piece = piece[j:].strip()
    piece = re.sub(r"^(return|goto)\b", "", piece).strip()
    if piece and not piece.endswith(":"):
        out.append(piece)
    return out


def statements(body):
    """Yield (line index, expression text) for every expression of every statement (control keywords and
    braces stripped, so one-line compound statements are covered too)."""
    for k, line in enumerate(body):
        s = re.sub(r"/\*.*?\*/", "", line).strip()
        if not s or s.startswith("//") or s.startswith("asm") or s.endswith(":") and ";" not in s:
            continue
        s = s.replace("{", " ").replace("}", " ")
        for piece in s.split(";"):
            for expr in split_control(piece):
                if expr.strip():
                    yield k, expr.strip()


def unify(types):
    """One type for a parameter from the argument types of every site, or None when they conflict."""
    ts = set(types)
    if len(ts) == 1:
        return ts.pop()
    if all(is_ptr(t) or t.startswith("fn:") for t in ts):
        return "void *"
    if ts <= {"int", "unsigned int", "unsigned char", "char", "short", "unsigned short", "long", "unsigned long"}:
        return "int"
    return None


def infer_prototypes(unit):
    """Type the body; return ({callee: (ret, [param types] | None)}, {local name: pointer type to cast to})."""
    typer = Typer(unit)
    stores = {}                            # callee -> set of target pointer types it is stored into
    cast_fix = []                          # (line index, var, target type) for `var = (void *)(call)`
    for k, expr in statements(unit.fn["body"]):
        try:
            typer.type_of(expr)
        except ValueError:
            continue
        m = re.match(r"^([A-Za-z_]\w*)\s*=\s*(\((?:struct\s+)?[A-Za-z_]\w*\s*\*+\))?\s*\(?\s*([A-Za-z_]\w*)\s*\(", expr)
        if m and m.group(1) in typer.locals and m.group(3) in typer.rets:
            target = typer.locals[m.group(1)][0]
            if is_ptr(target) and target != "void *":
                stores.setdefault(m.group(3), set()).add(target)
                if m.group(2) and norm(m.group(2)[1:-1]) == "void *":
                    cast_fix.append((k, m.group(1), target))
    protos = {}
    for p in unit.protos:
        name = p["name"]
        if p["args"] is not None:
            protos[name] = (p["ret"], p["args"])
            continue
        sites = typer.calls.get(name, [])
        ret = p["ret"]
        if sites:
            arity = {len(s) for s in sites}
            if len(arity) != 1:
                params = None
            else:
                params = []
                for i in range(arity.pop()):
                    t = unify([s[i] for s in sites])
                    if t is None:
                        params = None
                        break
                    if t in ("float", "double"):
                        # a floating literal in an unprototyped C call is passed with the default
                        # promotion in integer registers; only a variadic tail keeps that in C++
                        params.append("...")
                        break
                    params.append(t)
        else:
            params = []                 # only taken by address
        if name in stores and len(stores[name]) == 1 and ret in ("int", "void *"):
            ret = next(iter(stores[name]))
        protos[name] = (ret, params)

    def fn_pointer(t):
        """`fn:NAME` / `fn:NAME *` (a function passed by name or by address) -> pointer to its prototype."""
        m = re.match(r"^fn:([A-Za-z_]\w*)( \*)?$", t)
        if not m:
            return t
        ret, params = protos.get(m.group(1), ("int", []))
        if params is None:
            sig = "..."
        elif isinstance(params, str):
            sig = params
        else:
            sig = ", ".join(fn_pointer(x) for x in params) or "void"
        return "%s (*)(%s)" % (ret, sig)

    for name, (ret, params) in list(protos.items()):
        if isinstance(params, list):
            protos[name] = (ret, [fn_pointer(x) for x in params])
    return protos, cast_fix, typer


# ----------------------------------------------------------------------------- declaration order

def saved_register(name):
    m = re.match(r"^temp_s(\d)(?:_\d+)?$", name)
    return int(m.group(1)) if m else None


def orders(decls, compiler):
    """Candidate declaration orders for a compiler, most likely first.  Each is a list of indices."""
    idx = list(range(len(decls)))
    regs = [saved_register(d["name"]) for d in decls]
    s_idx = [i for i in idx if regs[i] is not None]
    o_idx = [i for i in idx if regs[i] is None]
    asc = sorted(s_idx, key=lambda i: (regs[i], i))
    desc = sorted(s_idx, key=lambda i: (-regs[i], i))
    out = [idx]
    if compiler == "3.0-011126":
        out += [asc + o_idx, o_idx + asc, desc + o_idx, o_idx + desc]
    else:
        out += [desc + o_idx, o_idx + desc, asc + o_idx, o_idx + asc]
    out.append(idx[::-1])
    if len(decls) <= 6:
        for p in itertools.permutations(idx):
            out.append(list(p))
    seen, uniq = set(), []
    for o in out:
        if tuple(o) not in seen:
            seen.add(tuple(o))
            uniq.append(o)
    return uniq


# ----------------------------------------------------------------------------- emission

def render(unit, protos, cast_fix, order, cxx, note):
    fn = unit.fn
    out = []
    if unit.head:
        head = list(unit.head)
        if note:
            # append the retarget note inside the closing comment
            last = head[-1]
            if last.rstrip().endswith("*/"):
                head[-1] = last.rstrip()[:-2].rstrip()
                head.append(" * " + note + " */")
            else:
                head.append("/* " + note + " */")
        out += head
    elif note:
        out.append("/* " + note + " */")
    out += unit.includes
    out += unit.types
    decl_lines = []
    for p in unit.protos:
        ret, params = protos[p["name"]]
        if params is None:
            sig = "..."
        elif isinstance(params, str):
            sig = params
        elif not params:
            sig = "void"
        else:
            sig = ", ".join(params)
        r = ret + ("" if ret.endswith("*") else " ")
        decl_lines.append("%s%s(%s);%s" % (r, p["name"], sig, (" " + p["cmt"]) if p["cmt"] else ""))
    for e in unit.externs:
        decl_lines.append(e["text"].strip())
    r = fn["ret"] + ("" if fn["ret"].endswith("*") else " ")
    decl_lines.append("%s%s(void);" % (r, fn["name"]))
    if cxx:
        out.append('extern "C" {')
        out += decl_lines
        out.append("}")
    else:
        out += decl_lines
    out += unit.other
    out.append("%s%s(void) {" % (r, fn["name"]))
    decls = fn["decls"]
    for i in order:
        out.append(decls[i]["text"])
    body = list(fn["body"])
    for k, var, target in cast_fix:
        body[k] = re.sub(r"(\b%s\s*=\s*)\(void \*\)" % re.escape(var), lambda m: m.group(1) + "(%s)" % target, body[k], count=1)
    if decls and body and body[0].strip() != "":
        out.append("")
    out += body
    out.append("}")
    return "\n".join(out) + "\n"


def verify(va, path, pure=False):
    cmd = [sys.executable, os.path.join(ROOT, "tools", "verify.py"), "0x%x" % va, path]
    if pure:
        cmd += ["--unit-flags", "/dev/null", "--unit-compilers", "/dev/null"]
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    lines = (r.stdout or r.stderr).splitlines() or ["?"]
    head = lines[0]
    if head.startswith("compile failed"):
        errs = [l.strip() for l in lines if "error" in l.lower()]
        head += ": " + " | ".join(errs[:2])
    return head


def address_of(name):
    for line in open(os.path.join(ROOT, "config/SLUS-20836/symbols.txt")):
        p = line.split()
        if len(p) >= 3 and p[2] == name:
            return int(p[0], 16)
    raise KeyError(name)


def rename_tracked(old, new):
    """`git mv` when the old file is tracked (keeps the rename in history), plain rename otherwise.
    Concurrent generators contend for the index lock, so a failed `git mv` is retried briefly."""
    if subprocess.run(["git", "-C", ROOT, "ls-files", "--error-unmatch", old], capture_output=True).returncode != 0:
        os.replace(old, new)
        return
    for attempt in range(100):
        r = subprocess.run(["git", "-C", ROOT, "mv", "-f", old, new], capture_output=True, text=True)
        if r.returncode == 0:
            return
        if "index.lock" not in r.stderr:
            raise RuntimeError("git mv %s -> %s failed: %s" % (old, new, r.stderr.strip()))
        time.sleep(0.2)
    raise RuntimeError("git mv %s -> %s: index lock held for too long" % (old, new))


def retarget(path, out_dir=None, order_mode="auto", do_verify=False, dry_run=False, max_tries=64, log=print):
    """Retarget one file.  Returns (status, verifier head line or reason)."""
    text = open(path).read()
    unit = parse_unit(text)
    if unit.fn is None:
        return "skip", "no function definition found"
    name = unit.fn["name"]
    va = address_of(name)
    res = unitprofiles.resolve(va, DEFAULT_FLAGS, DEFAULT_COMPILER)
    compiler = os.path.basename(os.path.dirname(res.profile.compiler))
    cxx = res.profile.exceptions == "on"
    protos, cast_fix, typer = infer_prototypes(unit)
    note = None
    if cxx and not path.endswith(".cpp"):
        note = ("C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail "
                "keeps this function's exception index record, which only the C++ front end emits.")
    ext = ".cpp" if cxx else ".c"
    folder = out_dir or os.path.dirname(os.path.abspath(path))
    target = os.path.join(folder, name + ext)
    cand = orders(unit.fn["decls"], compiler) if order_mode == "auto" else [list(range(len(unit.fn["decls"])))]
    if not do_verify:
        cand = cand[:1]
    tmp = target if out_dir else os.path.join(folder, name + ".retarget" + ext)
    last = None
    for n, order in enumerate(cand[:max_tries]):
        src = render(unit, protos, cast_fix, order, cxx, note)
        if dry_run:
            return "dry-run", target
        open(tmp, "w").write(src)
        if not do_verify:
            last = "written"
            break
        head = verify(va, tmp)
        last = head
        if "cat=match" in head and "override=foreign" not in head:
            break
        if n == 0 and ("compile failed" in head or "cat=code-only" in head and "exc=" not in head):
            break                                           # reordering will not fix a compile error
    else:
        head = last
    ok = (not do_verify) or ("cat=match" in last and "override=foreign" not in last)
    if out_dir:
        return ("match" if ok else "nomatch"), last
    if not ok:
        os.remove(tmp)
        return "nomatch", last
    if os.path.abspath(path) != os.path.abspath(target):
        rename_tracked(path, target)
    os.replace(tmp, target)
    return "match", last


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=None, help="write candidates here instead of beside the input (no rename)")
    ap.add_argument("--order", choices=("auto", "keep"), default="auto")
    ap.add_argument("--verify", action="store_true", help="verify under the unit profile; search declaration orders")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("files", nargs="+")
    a = ap.parse_args()
    for f in a.files:
        try:
            status, info = retarget(f, a.out, a.order, a.verify, a.dry_run)
        except (ValueError, KeyError, IndexError, AttributeError) as e:
            status, info = "error", repr(e)
        print("%s\t%s\t%s" % (status, os.path.relpath(f, ROOT), info))


if __name__ == "__main__":
    main()
