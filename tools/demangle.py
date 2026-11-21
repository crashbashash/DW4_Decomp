"""MWCC 3.0b52 compiler names: `demangle` reads one, `mangle` writes one.

MWCC for the PS2 encodes a C++ name the way cfront did (the scheme CodeWarrior keeps on every target):

    <name>__[<scope>][C]F<parameters>       a function; `C` for a const member, no `F` for a datum
    <scope>      <length><identifier>               one class or namespace: `10igRenderer`
                 Q<count><length><identifier>...    a qualified one: `Q33Gap3Gui10igRenderer`
    <name>       __ct / __dt / __vt / __RTTI        constructor, destructor, vtable, type descriptor
                 __nw, __dl, __as, __eq, ...        an operator (`OPERATORS`)
                 __op<type>                         a conversion operator

A parameter is a builtin code (`i` int, `Ui` unsigned int, `c` char, `Sc` signed char, `f`, `d`, `r` long
double, `x` long long, `b` bool, `w` wchar_t, `v` void, `e` the ellipsis), a scope (a class or enum), `P` pointer
to, `R` reference to, `C`/`V` const/volatile, `A<n>_` array of n, `F<parameters>_<return>` a function type, or
`M<scope><type>` pointer to member. A template class's identifier carries its arguments in angle brackets,
each a type in this encoding or an integer: `25igSmartPointer<8igObject>`, `9ObjRef<5>`. An empty parameter list
is `v`. The mangled name records the scope, not whether each part of it is a namespace or a class; `demangle`
reads `std`, `Gap` and `Gap::<library>` as namespaces and the rest as classes.

The C++ form of a type is the spelling a declaration would use for it: `igVisualContext *`, `const char *`,
`int (*)(lua_State *)`, `igSmartPointer<igObject>`; `mangle` accepts any such spelling (including `void` for an
empty list and `struct`/`class`/`enum` keywords).
"""
import re
from dataclasses import dataclass

BUILTINS = {
    "v": "void", "c": "char", "Sc": "signed char", "Uc": "unsigned char", "s": "short", "Us": "unsigned short",
    "i": "int", "Ui": "unsigned int", "l": "long", "Ul": "unsigned long", "x": "long long",
    "Ux": "unsigned long long", "f": "float", "d": "double", "r": "long double", "b": "bool", "w": "wchar_t",
    "e": "...",
}
_BUILTIN_CODES = {spelling: code for code, spelling in BUILTINS.items()}

OPERATORS = {
    "__nw": "operator new", "__dl": "operator delete", "__nwa": "operator new[]", "__dla": "operator delete[]",
    "__as": "operator=", "__eq": "operator==", "__ne": "operator!=", "__lt": "operator<", "__gt": "operator>",
    "__le": "operator<=", "__ge": "operator>=", "__pl": "operator+", "__mi": "operator-", "__ml": "operator*",
    "__dv": "operator/", "__md": "operator%", "__er": "operator^", "__ad": "operator&", "__or": "operator|",
    "__co": "operator~", "__nt": "operator!", "__apl": "operator+=", "__ami": "operator-=", "__amu": "operator*=",
    "__adv": "operator/=", "__amd": "operator%=", "__aer": "operator^=", "__aad": "operator&=",
    "__aor": "operator|=", "__ls": "operator<<", "__rs": "operator>>", "__als": "operator<<=",
    "__ars": "operator>>=", "__aa": "operator&&", "__oo": "operator||", "__pp": "operator++",
    "__mm": "operator--", "__cm": "operator,", "__rm": "operator->*", "__rf": "operator->", "__cl": "operator()",
    "__vc": "operator[]",
}
_OPERATOR_CODES = {spelling: code for code, spelling in OPERATORS.items()}
SPECIALS = {"__ct": "ctor", "__dt": "dtor", "__vt": "vt", "__RTTI": "rtti"}


class MangleError(ValueError):
    """A name or type outside the encoding."""


# ---- types: ("builtin", code) | ("named", (segment, ...)) | ("ptr", t) | ("ref", t) | ("cv", "C"/"V"/"CV", t)
#      | ("array", n, t) | ("func", return, (param, ...)) | ("member", scope, t); a segment is (identifier, args)
#      with args a tuple of types and ints, or None for a plain identifier

def _cv(quals, t):
    return ("cv", quals, t) if quals else t


# ---- reading the encoding ----------------------------------------------------------------------------------

class _Reader:
    def __init__(self, text):
        self.text, self.at = text, 0

    def peek(self, n=1):
        return self.text[self.at:self.at + n]

    def take(self, n=1):
        part = self.text[self.at:self.at + n]
        if len(part) != n:
            raise MangleError("truncated")
        self.at += n
        return part

    def number(self):
        found = re.match(r"[1-9]\d*", self.text[self.at:])
        if not found:
            raise MangleError("length expected")
        self.at += len(found.group(0))
        return int(found.group(0))

    def done(self):
        return self.at == len(self.text)


def _segment(identifier):
    """(identifier, args) of one `<length>` identifier: the template arguments read back to types."""
    if not identifier.endswith(">"):
        if not re.fullmatch(r"[A-Za-z_$][\w$]*", identifier):
            raise MangleError("identifier expected")
        return identifier, None
    open_ = identifier.index("<")
    head, body = identifier[:open_], identifier[open_ + 1:-1]
    if not re.fullmatch(r"[A-Za-z_$][\w$]*", head):
        raise MangleError("template identifier expected")
    args, depth, start = [], 0, 0
    for i, ch in enumerate(body + ","):
        if ch == "<":
            depth += 1
        elif ch == ">":
            depth -= 1
        elif ch == "," and depth == 0:
            part = body[start:i]
            if re.fullmatch(r"-?\d+", part):
                args.append(int(part))
            else:
                reader = _Reader(part)
                args.append(_read_type(reader))
                if not reader.done():
                    raise MangleError("template argument expected")
            start = i + 1
    return head, tuple(args)


def _read_scope(reader):
    if reader.peek() == "Q":
        reader.take()
        count = int(reader.take())
        if count < 2:
            raise MangleError("qualified name of fewer than two parts")
    else:
        count = 1
    return tuple(_segment(reader.take(reader.number())) for _ in range(count))


def _read_params(reader, stop):
    params = []
    while not reader.done() and reader.peek() != stop:
        params.append(_read_type(reader))
    if params == [("builtin", "v")]:
        return ()
    if ("builtin", "v") in params:
        raise MangleError("void parameter")
    return tuple(params)


def _read_type(reader):
    ch = reader.peek()
    if ch in ("C", "V"):
        quals = ""
        while reader.peek() in ("C", "V") and reader.peek():
            quals += reader.take()
        return ("cv", quals, _read_type(reader))
    if ch == "P":
        reader.take()
        return ("ptr", _read_type(reader))
    if ch == "R":
        reader.take()
        return ("ref", _read_type(reader))
    if ch == "A":
        reader.take()
        n = reader.number()
        if reader.take() != "_":
            raise MangleError("array bound")
        return ("array", n, _read_type(reader))
    if ch == "F":
        reader.take()
        params = _read_params(reader, "_")
        if reader.take() != "_":
            raise MangleError("function type")
        return ("func", _read_type(reader), params)
    if ch == "M":
        reader.take()
        scope = _read_scope(reader)
        return ("member", scope, _read_type(reader))
    if ch == "Q" or ch.isdigit():
        return ("named", _read_scope(reader))
    if ch in ("U", "S"):
        code = reader.take(2)
    else:
        code = reader.take()
    if code not in BUILTINS:
        raise MangleError("unknown type code %r" % code)
    return ("builtin", code)


# ---- writing the encoding ----------------------------------------------------------------------------------

def _encode_segment(segment):
    identifier, args = segment
    if args is not None:
        identifier += "<%s>" % ",".join(str(a) if isinstance(a, int) else _encode(a) for a in args)
    return "%d%s" % (len(identifier), identifier)


def _encode_scope(scope):
    parts = "".join(_encode_segment(s) for s in scope)
    if len(scope) == 1:
        return parts
    if len(scope) > 9:
        raise MangleError("qualified name of more than nine parts")
    return "Q%d%s" % (len(scope), parts)


def _encode_params(params):
    return "".join(_encode(p) for p in params) or "v"


def _encode(t):
    kind = t[0]
    if kind == "builtin":
        return t[1]
    if kind == "named":
        return _encode_scope(t[1])
    if kind == "ptr":
        return "P" + _encode(t[1])
    if kind == "ref":
        return "R" + _encode(t[1])
    if kind == "cv":
        return t[1] + _encode(t[2])
    if kind == "array":
        return "A%d_%s" % (t[1], _encode(t[2]))
    if kind == "func":
        return "F%s_%s" % (_encode_params(t[2]), _encode(t[1]))
    if kind == "member":
        return "M" + _encode_scope(t[1]) + _encode(t[2])
    raise MangleError("type %r" % (t,))


# ---- the C++ spelling --------------------------------------------------------------------------------------

def _format_segment(segment):
    identifier, args = segment
    if args is None:
        return identifier
    inner = ", ".join(str(a) if isinstance(a, int) else format_type(a) for a in args)
    return "%s<%s%s>" % (identifier, inner, " " if inner.endswith(">") else "")


def _format_scope(scope):
    return "::".join(_format_segment(s) for s in scope)


def _render(t, inner):
    kind = t[0]
    if kind in ("builtin", "named"):
        base = BUILTINS[t[1]] if kind == "builtin" else _format_scope(t[1])
        return base + (" " + inner if inner else "")
    if kind == "cv":
        words = " ".join({"C": "const", "V": "volatile"}[q] for q in t[1])
        target = t[2]
        if target[0] in ("builtin", "named"):
            return words + " " + _render(target, inner)
        if target[0] in ("ptr", "member"):
            # a const pointer: the qualifier follows its `*`
            return _render_ptr(target, inner, words)
        return _render(target, inner)  # cv on a function or array type has no spelling of its own
    if kind == "ptr" or kind == "member":
        return _render_ptr(t, inner, "")
    if kind == "ref":
        return _render(t[1], "&" + (inner or ""))
    if kind == "array":
        inner = "(%s)" % inner if _POINTER_DECLARATOR.match(inner or "") else (inner or "")
        return _render(t[2], "%s[%d]" % (inner, t[1]))
    if kind == "func":
        inner = "(%s)" % inner if _POINTER_DECLARATOR.match(inner or "") else (inner or "")
        return _render(t[1], "%s(%s)" % (inner, ", ".join(format_type(p) for p in t[2])))
    raise MangleError("type %r" % (t,))


# a declarator a function or array suffix must not bind to first: `*`, `&`, `Foo::*`
_POINTER_DECLARATOR = re.compile(r"[*&]|[A-Za-z_$][\w$:<>, ]*::\*")


def _render_ptr(t, inner, words):
    star = "*" if t[0] == "ptr" else _format_scope(t[1]) + "::*"
    if words:
        star += words + (" " if inner else "")
    return _render(t[-1], star + (inner or ""))


def format_type(t):
    """The C++ spelling of a type tree."""
    return _render(t, "")


# ---- reading the C++ spelling ------------------------------------------------------------------------------

_TOKEN = re.compile(r"\s*(::|\.\.\.|[A-Za-z_$][\w$]*|-?\d+|[*&()\[\]<>,])")
_BUILTIN_WORDS = {"void", "char", "short", "int", "long", "float", "double", "bool", "wchar_t", "signed",
                  "unsigned"}


class _Parser:
    def __init__(self, text):
        self.tokens, at = [], 0
        while at < len(text):
            found = _TOKEN.match(text, at)
            if not found:
                if text[at:].strip():
                    raise MangleError("cannot read %r" % text)
                break
            self.tokens.append(found.group(1))
            at = found.end()
        self.at = 0

    def peek(self, offset=0):
        at = self.at + offset
        return self.tokens[at] if at < len(self.tokens) else None

    def take(self, expected=None):
        token = self.peek()
        if token is None or (expected is not None and token != expected):
            raise MangleError("expected %r, found %r" % (expected, token))
        self.at += 1
        return token

    def done(self):
        return self.at == len(self.tokens)

    def scope(self):
        segments = [self.segment()]
        while self.peek() == "::" and self.peek(1) not in (None, "*"):
            self.take("::")
            segments.append(self.segment())
        return tuple(segments)

    def segment(self):
        identifier = self.take()
        if not re.fullmatch(r"[A-Za-z_$][\w$]*", identifier):
            raise MangleError("identifier expected, found %r" % identifier)
        if self.peek() != "<":
            return identifier, None
        self.take("<")
        args = []
        while self.peek() != ">":
            if re.fullmatch(r"-?\d+", self.peek() or ""):
                args.append(int(self.take()))
            else:
                args.append(self.type_())
            if self.peek() == ",":
                self.take(",")
        self.take(">")
        return identifier, tuple(args)

    def specifiers(self):
        quals, words, named = "", [], None
        while True:
            token = self.peek()
            if token in ("const", "volatile"):
                self.take()
                quals += "C" if token == "const" else "V"
            elif token in ("struct", "class", "enum", "union", "typename"):
                self.take()
            elif token in _BUILTIN_WORDS and named is None:
                words.append(self.take())
            elif (token is not None and re.fullmatch(r"[A-Za-z_$][\w$]*", token) and not words and named is None):
                named = self.scope()
            else:
                break
        if named is not None:
            base = ("named", named)
        else:
            base = ("builtin", _builtin_code(words))
        # MWCC writes a qualifier as `C` then `V`
        return _cv("".join(q for q in "CV" if q in quals), base)

    def type_(self):
        if self.peek() == "...":
            self.take()
            return ("builtin", "e")
        return self.declarator(self.specifiers())

    def declarator(self, base):
        token = self.peek()
        if token == "*":
            self.take()
            return self.declarator(self._qualified(("ptr", base)))
        if token == "&":
            self.take()
            return self.declarator(("ref", base))
        if (token is not None and re.fullmatch(r"[A-Za-z_$][\w$]*", token)
                and self._member_pointer_ahead()):
            scope = self.scope()
            self.take("::")
            self.take("*")
            return self.declarator(self._qualified(("member", scope, base)))
        if token == "(" and self.peek(1) in ("*", "&", "(") or (token == "(" and self._member_pointer_ahead(1)):
            # a grouped declarator: the suffixes after it apply first
            self.take("(")
            start, depth = self.at, 1
            while depth:
                token = self.take()
                depth += {"(": 1, ")": -1}.get(token, 0)
            end = self.at
            outer = self.suffixes(base)
            resume = self.at
            self.at = start
            result = self.declarator(outer)
            if self.at != end - 1:
                raise MangleError("grouped declarator")
            self.at = resume
            return result
        return self.suffixes(base)

    def _member_pointer_ahead(self, offset=0):
        at = offset
        while True:
            token = self.peek(at)
            if token is None or not re.fullmatch(r"[A-Za-z_$][\w$]*", token):
                return False
            at += 1
            if self.peek(at) == "<":
                depth = 0
                while True:
                    token = self.peek(at)
                    if token is None:
                        return False
                    depth += {"<": 1, ">": -1}.get(token, 0)
                    at += 1
                    if depth == 0:
                        break
            if self.peek(at) != "::":
                return False
            if self.peek(at + 1) == "*":
                return True
            at += 1

    def _qualified(self, t):
        quals = ""
        while self.peek() in ("const", "volatile"):
            quals += "C" if self.take() == "const" else "V"
        return _cv("".join(q for q in "CV" if q in quals), t)

    def suffixes(self, base):
        wrappers = []
        while self.peek() in ("(", "["):
            if self.take() == "[":
                n = int(self.take())
                self.take("]")
                wrappers.append(("array", n))
            else:
                wrappers.append(("func", self.parameters()))
        for wrapper in reversed(wrappers):
            base = ("array", wrapper[1], base) if wrapper[0] == "array" else ("func", base, wrapper[1])
        return base

    def parameters(self):
        params = []
        while self.peek() != ")":
            params.append(self.type_())
            if self.peek() == ",":
                self.take(",")
        self.take(")")
        return () if params == [("builtin", "v")] else tuple(params)


def _builtin_code(words):
    """The code of a builtin type spelled by `words` in any order (`long unsigned int`)."""
    if not words:
        raise MangleError("type expected")
    unsigned, signed = "unsigned" in words, "signed" in words
    longs, shorts = words.count("long"), words.count("short")
    rest = [w for w in words if w not in ("unsigned", "signed", "long", "short")]
    if len(rest) > 1 or (rest and rest[0] != "int" and (longs + shorts and rest[0] != "double")) \
            or (unsigned and signed):
        raise MangleError("unknown builtin %r" % " ".join(words))
    base = rest[0] if rest else "int"
    if base == "double" and longs == 1:
        spelling = "long double"
    elif base == "int" and (longs or shorts):
        spelling = {(1, 0): "long", (2, 0): "long long", (0, 1): "short"}.get((longs, shorts), "?")
    elif longs or shorts:
        spelling = "?"
    else:
        spelling = base
    if unsigned:
        spelling = "unsigned " + spelling
    elif signed and spelling == "char":
        spelling = "signed char"
    if spelling not in _BUILTIN_CODES or (unsigned and _BUILTIN_CODES[spelling][0] != "U"):
        raise MangleError("unknown builtin %r" % " ".join(words))
    return _BUILTIN_CODES[spelling]


# the kit's function typedefs, which a compiler name spells out: `igCompareFunction *` is the pointer to its type
TYPEDEFS = {"igCompareFunction": ("int", "(const void *, const void *)")}


def parse_type(text):
    """The type tree of a C++ type spelling (`const char *`, `int (*)(lua_State *)`)."""
    for name, (ret, args) in TYPEDEFS.items():
        text = re.sub(r"\b(?:Gap::)?%s\s*\*" % name, "%s (*)%s" % (ret, args), text)
    parser = _Parser(text)
    t = parser.type_()
    if not parser.done():
        raise MangleError("cannot read %r" % text)
    return t


def encode_type(text):
    """The MWCC encoding of a C++ type spelling: `igVisualContext *` -> `P15igVisualContext`."""
    return _encode(parse_type(text))


# ---- names -------------------------------------------------------------------------------------------------

def _is_namespace(prefix):
    """Whether the scope parts `prefix` name a namespace: `std`, `Gap` and `Gap::<library>`."""
    names = [identifier for identifier, _args in prefix]
    if any(args is not None for _identifier, args in prefix):
        return False
    return names == ["std"] or names == ["Gap"] or (len(names) == 2 and names[0] == "Gap")


@dataclass(frozen=True)
class Demangled:
    mangled: str
    namespaces: tuple           # ('Gap', 'Gui')
    class_name: object          # 'igRenderer', 'igLuaGlue::Class', 'igSmartPointer<igObject>' or None
    name: str                   # 'setVisualContext', '~igRenderer', 'igRenderer', 'operator delete', '__vt'
    params: tuple               # the C++ spelling of each parameter; () for a datum or an empty list
    const: bool
    special: object             # None, 'ctor', 'dtor', 'vt', 'rtti', 'operator', 'conversion'
    data: bool                  # no function encoding: a static data member, a vtable or a type descriptor

    @property
    def qualified(self):
        """`Gap::Gui::igRenderer::setVisualContext`."""
        return "::".join(self.namespaces + ((self.class_name,) if self.class_name else ()) + (self.name,))

    @property
    def class_base(self):
        """The innermost class's identifier without its template arguments (`igSmartPointer`), or None."""
        if not self.class_name:
            return None
        return _split_scope(self.class_name)[-1].split("<")[0]

    @property
    def signature(self):
        """`Gap::Gui::igRenderer::setVisualContext(Gap::Gfx::igVisualContext *)`; a datum's qualified name."""
        if self.data:
            return self.qualified
        return "%s(%s)%s" % (self.qualified, ", ".join(self.params), " const" if self.const else "")


def _split_scope(text):
    """The `::` parts of a qualified C++ name, template arguments kept whole."""
    parts, depth, start, i = [], 0, 0, 0
    while i < len(text):
        ch = text[i]
        if ch == "<":
            depth += 1
        elif ch == ">":
            depth -= 1
        elif depth == 0 and text.startswith("::", i):
            parts.append(text[start:i].strip())
            start = i + 2
            i += 1
        i += 1
    parts.append(text[start:].strip())
    return parts


def _demangle_at(mangled, split):
    """The reading of `mangled` with its name ending at `split` (where its `__` starts), or None."""
    head, reader = mangled[:split], _Reader(mangled[split + 2:])
    if not head:
        return None
    scope, const, params = (), False, None
    try:
        if reader.peek() in ("Q",) or reader.peek().isdigit():
            scope = _read_scope(reader)
        if reader.peek() == "C" and reader.peek(2) == "CF":
            reader.take()
            const = True
        if reader.peek() == "F":
            reader.take()
            params = _read_params(reader, None)
        elif const or not scope:
            return None
        if not reader.done():
            return None
    except MangleError:
        return None
    special = None
    class_parts = scope
    namespace_parts = ()
    # a constructor, destructor, vtable or type descriptor belongs to a class: its last scope part is one
    for n in range(len(scope) - (head in SPECIALS), 0, -1):
        if _is_namespace(scope[:n]):
            namespace_parts, class_parts = scope[:n], scope[n:]
            break
    class_name = _format_scope(class_parts) if class_parts else None
    name = head
    if head in SPECIALS:
        special = SPECIALS[head]
        if special in ("ctor", "dtor"):
            if not class_parts or params is None:
                return None
            base = class_parts[-1][0]
            name = ("~" if special == "dtor" else "") + base
        elif params is not None or not scope:
            return None
    elif head in OPERATORS:
        special, name = "operator", OPERATORS[head]
    elif head.startswith("__op") and len(head) > 4:
        try:
            target = _Reader(head[4:])
            t = _read_type(target)
            if not target.done():
                return None
        except MangleError:
            return None
        special, name = "conversion", "operator " + format_type(t)
    elif not re.fullmatch(r"[A-Za-z_$][\w$]*", head):
        return None
    return Demangled(mangled, tuple(_format_segment(s) for s in namespace_parts), class_name, name,
                     tuple(format_type(p) for p in params) if params is not None else (), const, special,
                     params is None)


def demangle(mangled):
    """The `Demangled` reading of an MWCC compiler name, or None for a name that is not one (a C name, a
    numbered label, `Gap__Gui__igTextElement__vfunc_23`)."""
    if not mangled or mangled[0] in "@." or "__" not in mangled[1:]:
        return None
    start = 2 if mangled.startswith("__") else 1
    at = mangled.find("__", start)
    while at != -1:
        found = _demangle_at(mangled, at)
        if found is not None:
            return found
        at = mangled.find("__", at + 1)
    return None


def _name_code(name, scope_segments):
    if name.startswith("~"):
        if not scope_segments or scope_segments[-1][0] != name[1:].strip():
            raise MangleError("destructor %r of another class" % name)
        return "__dt"
    if scope_segments and name == scope_segments[-1][0]:
        return "__ct"
    if name.startswith("operator"):
        spelling = re.sub(r"\s+", " ", name).replace("operator ", "operator", 1) \
            if not re.match(r"operator\s+(new|delete)\b", name) else re.sub(r"\s+", " ", name)
        spelling = spelling.replace(" []", "[]")
        if spelling in _OPERATOR_CODES:
            return _OPERATOR_CODES[spelling]
        if name[len("operator")].isspace():
            return "__op" + encode_type(name[len("operator"):].strip())
        raise MangleError("unknown operator %r" % name)
    if not re.fullmatch(r"[A-Za-z_$][\w$]*", name):
        raise MangleError("name expected, found %r" % name)
    return name


def mangle(qualified_name, params, const=False):
    """The MWCC compiler name of `qualified_name` (`Gap::Gui::igRenderer::setVisualContext`) with `params`, the
    C++ spelling of each parameter (a sequence; empty for `()`); `params=None` for a datum
    (`igRenderer::_Meta` -> `_Meta__10igRenderer`, `Gap::Gui::igRenderer::__vt` -> `__vt__Q33Gap3Gui10igRenderer`).
    `const` marks a const member function."""
    parts = _split_scope(qualified_name)
    name, scope_text = parts[-1], parts[:-1]
    scope = tuple(_Parser(part).segment() if _Parser(part).tokens else None for part in scope_text)
    if any(s is None for s in scope):
        raise MangleError("empty scope in %r" % qualified_name)
    for text, segment in zip(scope_text, scope):
        if _format_segment(segment).replace(" ", "") != text.replace(" ", "") and "<" not in text:
            raise MangleError("cannot read scope %r" % text)
    code = _name_code(name, scope)
    if params is None:
        if const:
            raise MangleError("a datum is not const-qualified in its name")
        if not scope:
            return name
        return "%s__%s" % (code, _encode_scope(scope))
    if const and not scope:
        raise MangleError("a free function is not const")
    encoded = _encode_params(tuple(parse_type(p) for p in params))
    return "%s__%s%sF%s" % (code, _encode_scope(scope) if scope else "", "C" if const else "", encoded)
