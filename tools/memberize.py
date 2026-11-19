#!/usr/bin/env python3
"""memberize.py — rewrite free `<Class>_<Method>` functions and `g_<Class>_…` data as members of their class.

The table names each conversion, one per line, tab-separated (blank lines and `#` comments skipped):

    <C name>   <member>

<member> is `Class::name` (its declaration is read from config/class-members.tsv, object macros such as
`IG_ABSTRACT_OBJECT_DEFINE(Class)` expanded from the headers that define them), or a full signature
(`static CallbackArray *igRenderer::arkRegisterInternal()`, `void igRenderer::setVisualContext(igVisualContext
*context)`, `igMetaObject *igRenderer::getMeta() const`, `static igMetaObject *igRenderer::_Meta`), whose
declaration is added to config/class-members.tsv when the class does not declare it yet. The class may be
qualified by its namespaces (`Gap::Gui::igRenderer`); the source then spells it that way. Several C names may
name one member (an alias a header declares for the same address, such as a published accessor).

For each conversion, across every source, header and `.inc` fragment of src/ and include/:

  * the definition: its head becomes `T Class::name(...)` (a `(void)` list becomes `()`); for an instance member
    the C function's first parameter is the receiver and goes. In the body the receiver is `this`, written
    without a local copy of it (a copy changes register allocation): `self->field` becomes `field` when `field`
    is a field or member of the class (`this->field` where a parameter or local of that name hides it) and the
    receiver's declared type reads it with the same type; any other `self->x` becomes `((T *)this)->x` for a
    receiver declared as some other type `T` (a dispatch view), else `this->x`; a bare `self` becomes `this`
    (cast to `T *` where it was declared as `T`). A receiver the body assigns or takes the address of is
    refused. A C function whose parameters already equal the member's (an instance member whose receiver was
    unused) keeps its list. A member the class defines inline (its declaration has a body) loses the C
    definition instead;
  * a static datum's definition `T g_x;` becomes `T Class::name;`;
  * calls and uses in C++: inside a member function of the class the bare `name(...)`; a static member elsewhere
    `Class::name(...)` (and `Class::name` as a value); an instance call `C_name(obj, a)` becomes `obj->name(a)`,
    the receiver cast to the class (`((Class *)expr)->name(a)`) unless it is declared as the class or one of its
    subclasses (`obj->name(a)`), `&x` becomes `x.name(a)`, and a call on the function's own receiver inside a
    member of the class is the bare `name(a)`;
  * calls in C (a `.c` unit, a fragment or header only C units read) keep the C name: the link renames every
    compiler name to its `symbols.txt` name, so the C name still resolves. The C prototype in the home header is
    kept for them; every other declaration of the C name (`extern "C"` lines, C-linkage blocks, a unity header's
    own prototypes) goes, and an `#ifdef __cplusplus`/`#endif` pair or `extern "C" { }` block left empty goes
    with it;
  * comments naming the C name name `Class::name`;
  * config/SLUS-20836/unit-objects.json: in the unit that places the function or datum, its `emitted`/`data`
    key (or the row's `symbol`) becomes the compiler name (demangle.mangle: `setVisualContext__10igRendererFP15
    igVisualContext`), which is how tools/compiler_names.py binds the compiler name to the `symbols.txt` key;
    `externals` and `data` rows of the C names in other units go (the compiler-name map resolves them), and a
    `duplicates` key is renamed. `python3 tools/compiler_names.py --write` then regenerates the map, and
    `python3 tools/whole_file_rows.py --cxx` writes the `duplicates` rows of units that emit a copy of an inline
    member.

It refuses the batch, before writing anything, when a C name has no definition (and is not an alias of one that
has), a file-scope `static` is named (it stays a free function), the member is not declared and the table gives
no signature, the declaration and the C definition disagree in parameters, an instance member is used as a value
or called without a receiver, or the receiver is assigned or has its address taken.

Dry run by default (`--diff` shows the source changes); `--apply` writes. Then regenerate
include/dw4/support/reflected.h (`python3 scripts/gen_type_headers.py`) when config/class-members.tsv changed,
and verify each touched unit with tools/check.py.

  memberize.py table.tsv                 # what would change
  memberize.py table.tsv --diff          # ...with the source diff
  memberize.py table.tsv --apply         # do it
"""
import argparse
import collections
import difflib
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "scripts"))
import declarations  # noqa: E402
import units  # noqa: E402
from demangle import mangle  # noqa: E402
from typed_coverage import local_names  # noqa: E402
import check_struct_conflicts as csc  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GAME = "SLUS-20836"
SOURCE_EXTS = (".c", ".cpp", ".h", ".hpp", ".inc")
_WORD = re.compile(r"[A-Za-z_]\w*")


class Refused(Exception):
    pass


class Conversion:
    """One C name and the member it becomes."""

    def __init__(self, cname, cls, name, kind, static, const, inline, ret, params, declaration):
        self.cname, self.cls, self.name, self.kind = cname, cls, name, kind
        self.static, self.const, self.inline = static, const, inline
        self.ret, self.params = ret, params            # normalised types (declarations.Types)
        self.declaration = declaration                 # the class-members.tsv text to add, or None
        self.mangled = None
        self.va = None

    @property
    def base(self):
        """The class's own name, without its namespaces."""
        return self.cls.rsplit("::", 1)[-1]

    @property
    def qualified(self):
        return "%s::%s" % (self.cls, self.name)


def _read(path):
    with open(path, errors="surrogateescape") as fh:
        return fh.read()


def _write(path, text):
    with open(path, "w", errors="surrogateescape") as fh:
        fh.write(text)


# ---- the table and the class declarations -----------------------------------------------------------
def read_table(path):
    """[(C name, member text, line)] of a conversion table."""
    rows = []
    for n, line in enumerate(_read(path).splitlines(), 1):
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        parts = line.rstrip("\n").split("\t")
        if len(parts) < 2 or not parts[0].strip() or not parts[1].strip():
            raise Refused("%s:%d: a row is `<C name>\\t<member>`" % (path, n))
        rows.append((parts[0].strip(), parts[1].strip(), n))
    return rows


def class_members(root):
    """{class: [declaration]} from config/class-members.tsv, or None when the table does not exist."""
    path = os.path.join(root, "config", "class-members.tsv")
    if not os.path.exists(path):
        return None
    out = collections.defaultdict(list)
    for line in _read(path).splitlines():
        if line.strip() and not line.startswith("#") and "\t" in line:
            cls, decl = line.rstrip("\n").split("\t", 1)
            out[cls.strip()].append(decl.strip())
    return out


def declared_members(cls, rows, macros, types):
    """[declarations.Member] a class's class-members.tsv rows declare, object macros expanded."""
    text = declarations.expand_function_macros("\n".join(rows), macros)
    code, _langs = declarations.clean("class %s {\n%s\n};\n" % (cls, text))
    found, _defined, _bodies = declarations.member_scan(code, "config/class-members.tsv", types, macros)
    for m in found:
        m.cls = cls
    return found


_SIGNATURE = re.compile(r"^(?P<lead>(?:static\s+|inline\s+)*)(?P<ret>.*?)\b(?P<cls>(?:[A-Za-z_]\w*::)+)"
                        r"(?P<name>~?[A-Za-z_]\w*)\s*(?P<rest>(?:\(.*\)\s*(?:const)?)?)\s*;?$", re.S)


def conversions(rows, members, macros, types):
    """[Conversion] for the table rows -> (conversions, errors)."""
    out, errors, cache = [], [], {}
    for cname, text, line in rows:
        m = _SIGNATURE.match(text.strip())
        if not m:
            errors.append("table line %d: `%s` is neither `Class::name` nor a member signature" % (line, text))
            continue
        cls, name = m.group("cls")[:-2], m.group("name")
        base = cls.rsplit("::", 1)[-1]
        if base not in cache:
            cache[base] = declared_members(base, (members or {}).get(base, []), macros, types)
        same = [d for d in cache[base] if d.name == name]
        full = bool(m.group("ret").strip() or m.group("rest").strip() or m.group("lead").strip())
        declaration = None
        if full:
            lead, ret, rest = m.group("lead"), m.group("ret").strip(), m.group("rest").strip()
            decl_text = "%s%s%s%s%s;" % ("static " if "static" in lead.split() else "", ret,
                                          "" if ret.endswith(("*", "&")) else " ", name, rest)
            parsed = declared_members(base, [decl_text], macros, types)
            if not parsed:
                errors.append("table line %d: cannot read `%s`" % (line, text))
                continue
            want = parsed[0]
            match = [d for d in same if d.kind == want.kind and d.params == want.params and d.const == want.const]
            if match:
                want = match[0]
            elif members is None:
                errors.append("table line %d: %s::%s is not declared and config/class-members.tsv does not exist "
                              "(scripts/gen_type_headers.py reads the class declarations from it)" % (line, base, name))
                continue
            else:
                declaration = decl_text
        elif len(same) == 1:
            want = same[0]
        elif not same:
            errors.append("table line %d: %s declares no member %s in config/class-members.tsv: give the full "
                          "signature" % (line, base, name))
            continue
        else:
            errors.append("table line %d: %s declares %d members named %s: give the full signature"
                          % (line, base, len(same), name))
            continue
        out.append(Conversion(cname, cls, name, want.kind, bool(want.static), bool(want.const), bool(want.inline),
                              want.ret, tuple(want.params or ()), declaration))
    return out, errors


def compiler_name(conv):
    """The MWCC b52 name of a conversion's member."""
    if conv.kind == "data":
        return mangle(conv.qualified, None)
    params = [re.sub(r"\s*:\s*:\s*", "::", p) for p in conv.params]
    return mangle(conv.qualified, params, conv.const)


# ---- the tree --------------------------------------------------------------------------------------
def source_files(root):
    out = []
    for top in ("src", "include"):
        for dirpath, dirs, files in os.walk(os.path.join(root, top)):
            dirs.sort()
            if os.sep + "third_party" in dirpath:
                continue
            for f in sorted(files):
                if f.endswith(SOURCE_EXTS) and not f.startswith(units.TMP_PREFIX):
                    out.append(os.path.relpath(os.path.join(dirpath, f), root).replace(os.sep, "/"))
    return out


def c_reads(index, rel):
    """Whether a C unit compiles file `rel` (a `.c` file, a fragment it includes, a header it reaches)."""
    if rel.endswith(".c"):
        return True
    if rel.endswith((".h", ".hpp")):
        return declarations._LANG_C in index.header_langs.get(rel, ())
    return any(index.units[u]["lang"] == declarations._LANG_C for u in index.unit_of.get(rel, ()))


def cxx_reads(index, rel):
    if rel.endswith(".cpp"):
        return True
    if rel.endswith(".c"):
        return False
    if rel.endswith((".h", ".hpp")):
        return declarations._LANG_CXX in index.header_langs.get(rel, ()) or not index.header_langs.get(rel)
    owners = index.unit_of.get(rel, ())
    return not owners or any(index.units[u]["lang"] == declarations._LANG_CXX for u in owners)


def _normal_type(t):
    return re.sub(r"\s+", "", re.sub(r"\b(?:struct|class|union|const)\b", "", t or ""))


class Classes:
    """Fields, bases and member names of the classes the tree declares (C++ view)."""

    def __init__(self, root, index):
        self.fields = collections.defaultdict(dict)          # class -> {field: normalised type}
        self.bases = {}
        reflected = os.path.join("include", "dw4", "support", "reflected.h")
        for rel, code in index._cxx.items():
            if not rel.endswith((".h", ".hpp")) or ("class " not in code and "struct " not in code):
                continue
            text = csc.strip_comments(code)
            for kind, name, base, body, _line in csc.bodies(text):
                if name in self.bases and rel != reflected:
                    continue                                  # the reflected class wins over a view of its name
                view = csc.parse_view(kind, name, base, body, {}, {}, rel, 0)
                self.bases[name] = [b.split("::")[-1] for b in view.base]
                self.fields[name] = {m.name: _normal_type(m.type) for m in view.members if m.name != "<vptr>"}

    def all_fields(self, cls, seen=None):
        seen = seen or set()
        if cls in seen:
            return {}
        seen.add(cls)
        out = {}
        for b in self.bases.get(cls, ()):
            out.update(self.all_fields(b, seen))
        out.update(self.fields.get(cls, {}))
        return out

    def derives(self, cls, base, depth=0):
        if cls == base:
            return True
        return depth < 32 and any(self.derives(b, base, depth + 1) for b in self.bases.get(cls, ()))


# ---- one file ---------------------------------------------------------------------------------------
_ARROW = re.compile(r"\s*->\s*([A-Za-z_]\w*)")
_ASSIGNED = re.compile(r"\s*(?:=(?!=)|\+\+|--|[-+*/%&|^]=|<<=|>>=)")
_CAST = re.compile(r"^\(\s*(?:struct\s+|class\s+)?([A-Za-z_][\w:]*)\s*\*\s*\)\s*(.+)$", re.S)
_POSTFIX = re.compile(r"^[A-Za-z_]\w*(?:\s*(?:->|\.)\s*[A-Za-z_]\w*|\s*\[[^\[\]]*\])*$")
_MEMBER_HEAD = re.compile(r"([A-Za-z_][\w:]*)\s*::\s*~?[A-Za-z_]\w*\s*\($")


def _strip_parens(e):
    e = e.strip()
    while e.startswith("(") and declarations._close(e, 0) == len(e) - 1:
        e = e[1:-1].strip()
    return e


def _arg_spans(clean, open_, close):
    """[(start, end)] of each argument of the call whose parentheses are at `open_` and `close`, blanks trimmed."""
    out, depth, at = [], 0, open_ + 1
    for i in range(open_ + 1, close + 1):
        ch = clean[i]
        if ch in "([{":
            depth += 1
        elif ch in ")]}" and i < close:
            depth -= 1
        if (ch == "," and depth == 0) or i == close:
            s, e = at, i
            while s < e and clean[s].isspace():
                s += 1
            while e > s and clean[e - 1].isspace():
                e -= 1
            if s < e or out or ch == ",":
                out.append((s, e))
            at = i + 1
    return out


def _split_args(text):
    if not text.strip():
        return []
    return [a.strip() for a in declarations._split_top(text)]


def _declared_type(ident, text):
    """The class a pointer `ident` is declared as in `text` (a function's head and body), or None."""
    m = re.search(r"\b(?:struct\s+|class\s+)?([A-Za-z_]\w*)\s*\*\s*%s\b\s*[,;=)\[]" % re.escape(ident), text)
    return m.group(1) if m else None


class FileRewrite:
    """The edits of one file."""

    def __init__(self, rel, text):
        self.rel, self.text = rel, text
        self.clean = units._clean(text)
        self.defs = units.definitions(text)
        self.edits = []                                # (start, end, replacement)
        self.deletes = []                              # (start, end) of whole lines

    def enclosing(self, pos):
        for name, start, end in self.defs:
            if start <= pos < end:
                return name, start, end
        return None

    def head_end(self, start):
        return self.clean.index("{", start)

    def result(self):
        deletes = sorted(self.deletes)
        kept = [(s, e, r) for s, e, r in self.edits if not any(ds <= s and e <= de for ds, de in deletes)]
        spans = sorted(kept + [(s, e, "") for s, e in deletes])
        out, at = [], 0
        for s, e, r in spans:
            if s < at:
                raise Refused("%s: two edits overlap at line %d" % (self.rel, self.text.count("\n", 0, s) + 1))
            out.append(self.text[at:s])
            out.append(r)
            at = e
        out.append(self.text[at:])
        return tidy("".join(out))


def tidy(text):
    """Drop the `#ifdef __cplusplus`/`#endif` pairs and `extern "C" { }` blocks the removals left empty."""
    for _ in range(4):
        new = re.sub(r'(?m)^[ \t]*#[ \t]*ifdef[ \t]+__cplusplus[ \t]*\n(?:[ \t]*\n)*[ \t]*#[ \t]*endif[^\n]*\n', "",
                     text)
        new = re.sub(r'(?m)^[ \t]*extern[ \t]+"C"[ \t]*\{[ \t]*\n(?:[ \t]*\n)*[ \t]*\}[ \t]*\n', "", new)
        if new == text:
            return text
        text = new
    return text


def _statement_start(clean, pos):
    """Where the file-scope statement holding `pos` starts: after the last `;`, `{` or `}` before it, past the
    blanks and preprocessor lines that come first."""
    at = max(clean.rfind(";", 0, pos), clean.rfind("}", 0, pos), clean.rfind("{", 0, pos)) + 1
    while True:
        while at < pos and clean[at].isspace():
            at += 1
        if at < pos and clean[at] == "#" and not clean[clean.rfind("\n", 0, at) + 1:at].strip():
            end = clean.find("\n", at)
            while end > 0 and clean[end - 1] == "\\":
                end = clean.find("\n", end + 1)
            at = pos if end < 0 or end > pos else end + 1
            continue
        return at


def _line_span(text, start, end):
    """(start, end) of the whole lines holding text[start:end], or None when other code shares them."""
    ls = text.rfind("\n", 0, start) + 1
    le = text.find("\n", end)
    le = len(text) if le < 0 else le + 1
    before, after = text[ls:start], text[end:le]
    if re.sub(r'extern\s*"C(?:\+\+)?"', "", before).strip() or after.strip():
        return None
    return ls, le


class Planner:
    def __init__(self, root, convs, index, classes):
        self.root, self.convs, self.index, self.classes = root, convs, index, classes
        self.by_cname = {c.cname: c for c in convs}
        self.errors, self.notes = [], []
        self.c_callers = collections.defaultdict(set)   # C name -> files that keep calling it
        self.defined = {}                               # C name -> file defining it
        self.inline_users = collections.defaultdict(set)

    def qual(self, conv, inside):
        """How code names a member: bare inside a member of its class, else qualified."""
        return conv.name if inside == conv.cls or (inside and inside.rsplit("::", 1)[-1] == conv.base) \
            else conv.qualified

    def member_class_of(self, fr, ctx):
        """The class of the out-of-class member function enclosing a use (`T Class::name(...) {`), or None."""
        if ctx is None:
            return None
        _name, start, _end = ctx
        head = fr.clean[start:fr.head_end(start)]
        p = declarations._first_paren(head)
        m = _MEMBER_HEAD.search(re.sub(r"\s+", " ", head[:p + 1])) if p >= 0 else None
        return m.group(1) if m else None

    def plan_file(self, fr):
        c_side, cxx_side = c_reads(self.index, fr.rel), cxx_reads(self.index, fr.rel)
        names = set(self.by_cname)
        for m in re.finditer(r"\b(%s)\b" % "|".join(re.escape(n) for n in sorted(names, key=len, reverse=True)),
                             fr.clean):
            cname, pos, end = m.group(1), m.start(), m.end()
            conv = self.by_cname[cname]
            prev = fr.clean[max(0, pos - 3):pos].rstrip()
            if prev.endswith((".", "->", "::")):
                continue                                # a member of something else
            line_start = fr.clean.rfind("\n", 0, pos) + 1
            if fr.clean[line_start:pos].lstrip().startswith("#"):
                continue                                # a macro name or test
            ctx = fr.enclosing(pos)
            in_head = ctx is not None and pos < fr.head_end(ctx[1])
            if ctx is not None and not in_head:
                self.plan_use(fr, conv, pos, end, ctx, c_side and not cxx_side)
            else:
                self.plan_file_scope(fr, conv, pos, end, c_side, cxx_side)
        for start, end in self.comment_spans(fr):
            for w in _WORD.finditer(fr.text, start, end):
                conv = self.by_cname.get(w.group(0))
                if conv is not None:
                    fr.edits.append((w.start(), w.end(), conv.qualified))

    @staticmethod
    def comment_spans(fr):
        out, i = [], 0
        for m in re.finditer(r"/\*.*?\*/|//[^\n]*", fr.text, re.S):
            if fr.clean[m.start()] == " ":              # blanked: a comment, not a `/*` inside a string
                out.append((m.start(), m.end()))
        return out

    def plan_use(self, fr, conv, pos, end, ctx, c_only):
        if c_only:
            self.c_callers[conv.cname].add(fr.rel)
            return
        inside = self.member_class_of(fr, ctx)
        after = re.match(r"\s*\(", fr.clean[end:])
        if conv.kind == "data" or conv.static:
            fr.edits.append((pos, end, self.qual(conv, inside)))
            if conv.inline and conv.kind == "func" and not after:
                self.inline_users[conv.qualified].add(fr.rel)
            return
        if not after:
            self.errors.append("%s:%d: instance member %s is used as a value (%s); convert that use by hand"
                               % (fr.rel, fr.text.count("\n", 0, pos) + 1, conv.qualified, conv.cname))
            return
        open_ = end + after.end() - 1
        close = declarations._close(fr.clean, open_)
        spans = _arg_spans(fr.clean, open_, close)
        if len(spans) != len(conv.params) + 1:
            self.errors.append("%s:%d: %s(...) passes %d arguments; instance member %s takes a receiver and %d"
                               % (fr.rel, fr.text.count("\n", 0, pos) + 1, conv.cname, len(spans), conv.qualified,
                                  len(conv.params)))
            return
        receiver = self.receiver(fr, conv, fr.text[spans[0][0]:spans[0][1]], ctx, inside)
        # the receiver and the name are replaced; the other arguments keep their text (and their own edits)
        stop = spans[1][0] if len(spans) > 1 else close
        fr.edits.append((pos, stop, (receiver or "") + conv.name + "("))

    def receiver(self, fr, conv, expr, ctx, inside):
        """The object expression with its `->`/`.` for an instance call, or None for a bare call (the enclosing
        member's own `this`, its class or a subclass of it being the member's)."""
        e = _strip_parens(expr)
        cast = _CAST.match(e)
        bare = _strip_parens(cast.group(2)) if cast else e
        if bare == "this" and inside is not None and self.classes.derives(inside.rsplit("::", 1)[-1], conv.base):
            return None
        if e == "this":
            return "this->"
        if cast:
            inner = bare if _POSTFIX.match(bare) else "(%s)" % bare
            return "((%s *)%s)->" % (conv.cls, inner)
        if e.startswith("&") and _POSTFIX.match(e[1:].strip()):
            return e[1:].strip() + "."
        if re.fullmatch(r"[A-Za-z_]\w*", e):
            declared = _declared_type(e, fr.text[ctx[1]:ctx[2]])
            if declared and self.classes.derives(declared, conv.base):
                return e + "->"
        return "((%s *)%s)->" % (conv.cls, e if _POSTFIX.match(e) else "(%s)" % e)

    def def_params(self, fr, ctx):
        """[(declared type, name)] of a definition's parameters."""
        head = fr.text[ctx[1]:fr.head_end(ctx[1])]
        p = declarations._first_paren(head)
        close = declarations._close(head, p)
        out = []
        for a in _split_args(head[p + 1:close]):
            if a in ("", "void"):
                continue
            m = re.match(r"(.*?)([A-Za-z_]\w*)\s*((?:\[[^\]]*\]\s*)*)$", a, re.S)
            out.append((m.group(1).strip(), m.group(2)) if m else (a, None))
        return out

    def plan_file_scope(self, fr, conv, pos, end, c_side, cxx_side):
        stmt_start = _statement_start(fr.clean, pos)
        head = fr.clean[stmt_start:pos]
        nxt = re.compile(r"\s*(\S?)").match(fr.clean, end).group(1)
        is_extern = re.search(r"\bextern\b", head) is not None
        if conv.kind == "data" and not is_extern and "=" not in head and "(" not in head and "&" not in head \
                and re.search(r"[A-Za-z_]", head):
            return                                       # the datum's definition (plan_definition)
        declaration = (nxt == "(" and "=" not in head and conv.kind == "func") or \
                      (conv.kind == "data" and is_extern and "=" not in head)
        if declaration:
            stmt_end = fr.clean.find(";", end)
            if c_side and self.c_callers.get(conv.cname) is not None and not cxx_only(fr, pos):
                return                                   # C still calls it: its C prototype stays
            span = _line_span(fr.clean, stmt_start, stmt_end + 1)
            if span is None:
                self.errors.append("%s:%d: the declaration of %s shares its line with other code: remove it by hand"
                                   % (fr.rel, fr.text.count("\n", 0, pos) + 1, conv.cname))
            else:
                fr.deletes.append(span)
            return
        if c_side and not cxx_side:
            self.c_callers[conv.cname].add(fr.rel)
            return
        if conv.kind == "func" and not conv.static:
            self.errors.append("%s:%d: instance member %s is used as a value (%s); convert that use by hand"
                               % (fr.rel, fr.text.count("\n", 0, pos) + 1, conv.qualified, conv.cname))
            return
        fr.edits.append((pos, end, conv.qualified))
        if conv.inline:
            self.inline_users[conv.qualified].add(fr.rel)

    def plan_definition(self, fr, conv):
        """The definition of a converted C name in `fr`, or False when `fr` has none."""
        if conv.kind == "data":
            for m in re.finditer(r"\b%s\b" % re.escape(conv.cname), fr.clean):
                if fr.enclosing(m.start()):
                    continue
                stmt_start = _statement_start(fr.clean, m.start())
                head = fr.clean[stmt_start:m.start()]
                if re.search(r"\bextern\b|[=(&]", head) or not re.search(r"[A-Za-z_]", head) or \
                        fr.clean[max(0, m.start() - 3):m.start()].rstrip().endswith((".", "->", "::")):
                    continue
                if re.search(r"\bstatic\b", head):
                    raise Refused("%s: %s is a file-scope static: it stays a free datum" % (fr.rel, conv.cname))
                fr.edits.append((m.start(), m.end(), conv.qualified))
                return True
            return False
        for name, start, end in fr.defs:
            if name != conv.cname:
                continue
            brace = fr.head_end(start)
            head = fr.clean[start:brace]
            if re.search(r"\bstatic\b", head[:declarations._first_paren(head)]):
                raise Refused("%s: %s is a file-scope static: it stays a free function" % (fr.rel, conv.cname))
            if conv.inline:
                p = declarations._first_paren(head)
                ret = self.index.types.strip_top_cv(self.index.types.norm(declarations._STORAGE.sub(
                    " ", head[:head.rfind(conv.cname, 0, p)])))
                if conv.ret is not None and ret != conv.ret:
                    self.notes.append("%s returned %s, %s returns %s: a use of it as a function pointer has the "
                                      "member's type now and may need its parameter's type spelled"
                                      % (conv.cname, ret or "nothing", conv.qualified, conv.ret))
                span = _line_span(fr.text, start, end)
                if span is None:
                    raise Refused("%s: %s's definition shares its lines with other code" % (fr.rel, conv.cname))
                ls, le = span
                if fr.text[le:le + 1] == "\n" and (ls == 0 or fr.text[ls - 2:ls] == "\n\n"):
                    le += 1                              # and the blank line after it
                fr.deletes.append((ls, le))
                return True
            self.rewrite_definition(fr, conv, (name, start, end))
            return True
        return False

    def rewrite_definition(self, fr, conv, ctx):
        name, start, end = ctx
        brace = fr.head_end(start)
        head = fr.text[start:brace]
        p = declarations._first_paren(head)
        close = declarations._close(head, p)
        params = self.def_params(fr, ctx)
        receiver = None
        if conv.kind == "func" and not conv.static and len(params) == len(conv.params) + 1:
            receiver = params[0]
            params = params[1:]
        elif len(params) != len(conv.params):
            raise Refused("%s: %s takes %d parameters, %s declares %d%s" % (
                fr.rel, conv.cname, len(params), conv.qualified, len(conv.params),
                "" if conv.static else " (and an instance member's receiver)"))
        types = self.index.types
        got = tuple(types.param(t + " " + (n or "")) for t, n in params)
        if got != tuple(conv.params):
            raise Refused("%s: %s's parameters (%s) are not %s's (%s)" % (
                fr.rel, conv.cname, ", ".join(got), conv.qualified, ", ".join(conv.params)))
        ret = head[:head.rfind(conv.cname, 0, p)].rstrip()
        ret_norm = types.strip_top_cv(types.norm(declarations._STORAGE.sub(" ", ret)))
        if ret_norm != conv.ret and conv.ret is not None:
            self.notes.append("%s: %s returns %s, %s is declared to return %s: the head takes the declaration's"
                              % (fr.rel, conv.cname, ret_norm or "nothing", conv.qualified, conv.ret))
            ret = conv.ret.replace("*", " *").replace("  ", " ").strip()
        plist = ", ".join(("%s %s" % (t, n) if not t.endswith(("*", "&")) else "%s%s" % (t, n)) if n else t
                          for t, n in params)
        new_head = "%s%s%s(%s)%s%s" % (ret, "" if ret.endswith(("*", "&")) or not ret else " ", conv.qualified,
                                       plist, " const" if conv.const else "", head[close + 1:])
        fr.edits.append((start, brace, new_head))
        if receiver is not None:
            self.rewrite_receiver(fr, conv, ctx, receiver, head[p + 1:close])

    def rewrite_receiver(self, fr, conv, ctx, receiver, signature):
        rtype, rname = receiver
        _name, start, end = ctx
        brace = fr.head_end(start)
        declared = re.sub(r"\b(?:struct|class|const)\b|\*|&", " ", rtype).split()
        rclass = declared[-1] if declared else conv.base
        same = rclass == conv.base or rclass == conv.cls
        body = fr.clean[brace:end]
        shadowed = local_names(signature, body) - {rname}
        members = self.classes.all_fields(conv.base)
        view_fields = members if same else self.classes.all_fields(rclass)
        member_names = set(members) | {c.name for c in self.convs if c.base == conv.base} | \
            self.declared_names.get(conv.base, set())
        cast = "this" if same else "((%s *)this)" % _pointee(rtype)
        for m in re.finditer(r"\b%s\b" % re.escape(rname), body):
            pos, after = brace + m.start(), brace + m.end()
            before = fr.clean[max(start, pos - 3):pos].rstrip()
            if before.endswith((".", "->", "::")):
                continue
            line = fr.text.count("\n", 0, pos) + 1
            arrow = _ARROW.match(fr.clean, after)
            address = fr.clean[max(start, pos - 1):pos] == "&" and fr.clean[max(start, pos - 2):pos] != "&&"
            if _ASSIGNED.match(fr.clean, after) or before.endswith(("++", "--")) or (address and not arrow):
                raise Refused("%s:%d: %s assigns or takes the address of its receiver `%s`: it cannot become `this`"
                              % (fr.rel, line, conv.cname, rname))
            if arrow:
                field = arrow.group(1)
                hit = field in member_names and (same or (field in view_fields and field in members and
                                                          view_fields[field] == members[field]))
                if hit:
                    fr.edits.append((pos, arrow.end(), ("this->" + field) if field in shadowed else field))
                else:
                    fr.edits.append((pos, arrow.end(), "%s->%s" % (cast, field)))
                continue
            casted = re.search(r"\)\s*$", fr.clean[max(start, pos - 40):pos]) and \
                re.search(r"\(\s*(?:struct\s+|class\s+)?[A-Za-z_][\w:]*\s*\*+\s*\)\s*$", fr.clean[max(start, pos - 60):pos])
            fr.edits.append((pos, after, "this" if same or casted else "(%s *)this" % _pointee(rtype)))


def _pointee(t):
    """`igRendererDispatchView` for a parameter type `igRendererDispatchView *`."""
    return re.sub(r"\s*\*\s*$", "", t.replace("const ", "")).strip()


def cxx_only(fr, pos):
    """Whether position `pos` of a file is inside an `#ifdef __cplusplus` arm (C does not read it)."""
    depth = []
    for m in re.finditer(r"(?m)^[ \t]*#[ \t]*(ifdef|ifndef|if|else|elif|endif)\b(.*)$", fr.text[:pos]):
        word, rest = m.group(1), m.group(2).strip()
        if word.startswith("if"):
            depth.append("cxx" if (word == "ifdef" and rest == "__cplusplus") else
                         "c" if (word == "ifndef" and rest == "__cplusplus") else "other")
        elif word == "else" and depth:
            depth[-1] = {"cxx": "c", "c": "cxx"}.get(depth[-1], "other")
        elif word == "endif" and depth:
            depth.pop()
    return "cxx" in depth


# ---- unit-objects.json ------------------------------------------------------------------------------
def symbol_addresses(root):
    """{name: va} from symbols.txt and data-names.tsv."""
    out = {}
    config = os.path.join(root, "config", GAME)
    for table, col in (("data-names.tsv", 1), ("symbols.txt", 2)):
        path = os.path.join(config, table)
        if not os.path.exists(path):
            continue
        for row in _read(path).splitlines():
            parts = row.split()
            if len(parts) > col and not row.startswith("#"):
                try:
                    out.setdefault(parts[col], int(parts[0], 16))
                except ValueError:
                    continue
    return out


def rename_rows(rows, convs, placing):
    """Rename the placing unit's key of each conversion to its compiler name and drop the C names' rows elsewhere
    -> [change]. `placing` is {C name: row key} of the unit that places it. The placing unit's `emitted` key of a
    function (its `symbol`, for the row's owner) and `data` key of a datum are the binding; a `duplicates` key is
    the copy's compiler name; any other `externals` or `data` row of a C name goes."""
    changes = []
    cnames = {c.cname: c for c in convs}
    for unit, row in rows.items():
        for field in ("emitted", "duplicates", "externals", "data"):
            entries = row.get(field)
            if not isinstance(entries, dict):
                continue
            out = {}
            for name, addr in entries.items():
                conv = cnames.get(name)
                if conv is None or not isinstance(addr, str) or int(addr, 16) != conv.va:
                    out[name] = addr
                    continue
                own = placing.get(conv.cname) == unit and field == ("emitted" if conv.kind == "func" else "data")
                if own or field == "duplicates":
                    out[conv.mangled] = addr
                    changes.append("%s %s: %s -> %s" % (unit, field, name, conv.mangled))
                else:
                    changes.append("%s %s: %s dropped (tools/compiler_names.py resolves %s)"
                                   % (unit, field, name, conv.mangled))
            if out != entries:
                row[field] = out
        for conv in convs:
            if conv.kind == "func" and placing.get(conv.cname) == unit and int(unit, 16) == conv.va and \
                    row.get("symbol", conv.cname) in cnames:
                if row.get("symbol") != conv.mangled:
                    changes.append("%s symbol: %s -> %s" % (unit, row.get("symbol", conv.cname), conv.mangled))
                row["symbol"] = conv.mangled
    return changes


def placing_rows(rows, convs, definers, index, addresses):
    """{C name: row key} of the unit placing each converted function or datum: the row whose owner or `emitted`
    key is the function's address; for a datum, the row of the unit that compiles its definition."""
    out = {}
    owner_units = {}
    for unit, row in rows.items():
        emitted = {int(a, 16) for a in (row.get("emitted") or {}).values() if isinstance(a, str)}
        for conv in convs:
            if conv.kind == "func" and conv.va is not None and (int(unit, 16) == conv.va or conv.va in emitted):
                out[conv.cname] = unit
    by_va = collections.defaultdict(set)
    for name, va in addresses.items():
        by_va[va].add(name)
    for conv in convs:
        if conv.kind != "data" or conv.cname not in definers:
            continue
        compiled_by = set(index.unit_of.get(definers[conv.cname], ())) or {definers[conv.cname]}
        for unit, row in rows.items():
            if conv.cname not in (row.get("data") or {}):
                continue
            if unit not in owner_units:
                owner_units[unit] = unit_of_row(unit, row, index, by_va)
            if owner_units[unit] in compiled_by:
                out[conv.cname] = unit
    return out


def unit_of_row(unit, row, index, by_va):
    """The translation unit (`src/...cpp`) a row's owner function is defined in, or None."""
    names = set(by_va.get(int(unit, 16), ()))
    if row.get("symbol"):
        names.add(row["symbol"])
    for u, info in index.units.items():
        for f in info["files"]:
            text = index.texts.get(f, "")
            if any(n in text for n in names) and any(d[0] in names for d in units.definitions(text)):
                return u
    return None


# ---- main -------------------------------------------------------------------------------------------
def plan(root, table):
    """-> (new texts {rel: text}, row changes, class-members rows to add, conversions, planner)."""
    index = declarations.Index(root, approvals={})
    macros = declarations.function_macros(index.texts.values())
    members = class_members(root)
    convs, errors = conversions(read_table(table), members, macros, index.types)
    if errors:
        raise Refused("\n".join(errors))
    classes = Classes(root, index)
    planner = Planner(root, convs, index, classes)
    planner.declared_names = {}
    for conv in convs:
        planner.declared_names.setdefault(conv.base, {d.name for d in declared_members(
            conv.base, (members or {}).get(conv.base, []), macros, index.types)})
    addresses = symbol_addresses(root)
    rows_path = os.path.join(root, "config", GAME, "unit-objects.json")
    rows = json.loads(_read(rows_path)) if os.path.exists(rows_path) else {}
    for conv in convs:
        conv.mangled = compiler_name(conv)
        conv.va = addresses.get(conv.cname)
        if conv.va is None:
            for row in rows.values():
                for field in ("emitted", "data", "externals", "duplicates"):
                    if isinstance((row.get(field) or {}).get(conv.cname), str):
                        conv.va = int(row[field][conv.cname], 16)
    originals = {}
    for rel in source_files(root):
        text = _read(os.path.join(root, rel))
        if any(c.cname in text for c in convs):
            originals[rel] = text
    # 1. the definitions: heads, receivers, data definitions, inline members' C copies removed
    first = {rel: FileRewrite(rel, text) for rel, text in originals.items()}
    for conv in convs:
        found = [rel for rel, fr in sorted(first.items()) if planner.plan_definition(fr, conv)]
        if len(found) > 1:
            raise Refused("%s is defined in %s" % (conv.cname, ", ".join(found)))
        if found:
            planner.defined[conv.cname] = found[0]
    by_member = collections.defaultdict(list)
    for conv in convs:
        by_member[(conv.kind, conv.qualified)].append(conv)
    for key, group in by_member.items():
        if not any(c.cname in planner.defined for c in group):
            raise Refused("no definition of %s in src/ (%s)" % (key[1], ", ".join(c.cname for c in group)))
        vas = {c.va for c in group if c.va is not None}
        if len(vas) > 1:
            raise Refused("%s's C names are at different addresses" % key[1])
        for c in group:
            c.va = c.va if c.va is not None else (vas.pop() if vas else None)
    # 2. every other use, read in the text the definitions now have (a converted body calls through `this`);
    #    C callers first, since whether a C prototype stays depends on them
    second = {rel: FileRewrite(rel, fr.result() if (fr.edits or fr.deletes) else fr.text)
              for rel, fr in first.items()}
    for rel in sorted(second, key=lambda rel: (not c_reads(index, rel) or cxx_reads(index, rel), rel)):
        planner.plan_file(second[rel])
    if planner.errors:
        raise Refused("\n".join(planner.errors))
    new_texts = {}
    for rel, fr in second.items():
        text = fr.result() if (fr.edits or fr.deletes) else fr.text
        if text != originals[rel]:
            new_texts[rel] = text
    placing = placing_rows(rows, convs, planner.defined, index, addresses)
    changes = rename_rows(rows, convs, placing) if rows else []
    for conv in convs:
        if conv.cname in planner.defined and conv.cname not in placing:
            planner.notes.append("%s has no whole-file row placing it: its compiler name %s is in no row"
                                 % (conv.cname, conv.mangled))
    adds = sorted({(c.base, c.declaration) for c in convs if c.declaration})
    planner.units = touched_rows(new_texts, index, rows, addresses, set(placing.values()))
    return new_texts, rows, changes, adds, convs, planner


def touched_rows(new_texts, index, rows, addresses, placing):
    """The row keys of the whole-file units whose text the conversion changed, the placing units first: the
    units tools/whole_file_rows.py --cxx writes the rows of."""
    touched = set()
    for rel in new_texts:
        touched.update(index.unit_of.get(rel, ()))
    owners = {}
    for name, va in addresses.items():
        key = "0x%08x" % va
        if key in rows:
            owners.setdefault(name, key)
    out = set()
    for u in touched:
        for f in index.units[u]["files"]:
            for name, _s, _e in units.definitions(index.texts.get(f, "")):
                if name in owners:
                    out.add(owners[name])
    for key, row in rows.items():
        if row.get("symbol") and any(row["symbol"] in index.texts.get(f, "")
                                     for u in touched for f in index.units[u]["files"]):
            out.add(key)
    return sorted(out, key=lambda key: (key not in placing, key))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("table", help="tab-separated `<C name>\\t<member>` rows")
    ap.add_argument("--root", default=ROOT, help="the tree to rewrite (default: this repository)")
    ap.add_argument("--apply", action="store_true", help="write the changes (default: dry run)")
    ap.add_argument("--diff", action="store_true", help="print the source changes as a unified diff")
    a = ap.parse_args(argv)
    root = os.path.abspath(a.root)
    try:
        new_texts, rows, changes, adds, convs, planner = plan(root, a.table)
    except Refused as e:
        print("memberize: refused, nothing was written:\n" + str(e), file=sys.stderr)
        return 2
    for conv in convs:
        print("  %-40s -> %s%s%s  [%s]" % (conv.cname, "static " if conv.static else "", conv.qualified,
                                           " (inline)" if conv.inline else "", conv.mangled))
    print("%d source files to rewrite, %d unit-objects.json changes, %d class-members.tsv rows to add"
          % (len(new_texts), len(changes), len(adds)))
    for rel in sorted(new_texts):
        print("  " + rel)
    for c in changes:
        print("  unit-objects.json " + c)
    for cls, decl in adds:
        print("  class-members.tsv %s\t%s" % (cls, decl))
    for cname, files in sorted(planner.c_callers.items()):
        print("note: C keeps calling %s (%s): its C prototype stays" % (cname, ", ".join(sorted(files))))
    for member, files in sorted(planner.inline_users.items()):
        print("note: %s is inline and its address is taken in %s: those units compile a copy of it (a "
              "`duplicates` row)" % (member, ", ".join(sorted(files))))
    for n in planner.notes:
        print("note: " + n)
    if a.diff:
        for rel in sorted(new_texts):
            old = _read(os.path.join(root, rel))
            sys.stdout.writelines(difflib.unified_diff(old.splitlines(True), new_texts[rel].splitlines(True),
                                                       "a/" + rel, "b/" + rel))
    if not a.apply:
        print("\n(dry run — re-run with --apply)")
        return 0
    for rel, text in new_texts.items():
        _write(os.path.join(root, rel), text)
    if changes:
        with open(os.path.join(root, "config", GAME, "unit-objects.json"), "w") as fh:
            fh.write(json.dumps(rows, indent=2) + "\n")
    if adds:
        with open(os.path.join(root, "config", "class-members.tsv"), "a") as fh:
            fh.writelines("%s\t%s\n" % row for row in adds)
    print("memberize: rewrote %d files, %d row changes, %d declarations added" % (len(new_texts), len(changes),
                                                                                 len(adds)))
    names_tool = os.path.join(root, "tools", "compiler_names.py")
    if changes and os.path.exists(names_tool):
        r = subprocess.run([sys.executable, names_tool, "--write"], cwd=root)
        if r.returncode:
            return r.returncode
    steps = []
    if adds:
        steps.append("python3 scripts/gen_type_headers.py          # class-members.tsv changed")
    steps += ["python3 tools/whole_file_rows.py --unit-va %s --cxx --write" % key for key in planner.units]
    steps.append("python3 tools/check.py --function <unit va> --cand <unit file>   # each touched unit")
    steps.append("make check-fresh && make link-fresh")
    print("next, in this order:\n" + "\n".join("  " + s for s in steps))
    return 0


if __name__ == "__main__":
    sys.exit(main())
