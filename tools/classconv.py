#!/usr/bin/env python3
"""classconv.py — convert one batch of flat classes to `Gap::<Library>::` classes from a spec file.

    python3 tools/classconv.py <spec.py> {tables,memberize,splice,decls,rekey,all} [<class> ...]

Without classes, every class of the spec, in its order. Run from the repository root. The steps are those of
docs/engine/member-conversion.md ("Converting a class, in order"), for every class of the batch:

  tables     the class's row in config/converted-classes.tsv, its `rows` in config/class-members.tsv (after its
             last row there) and its `typed` fields in config/typed-fields.tsv; for a spec with `add`, the rows
             and typed fields the converted class lacks (a row it has declares the same: a function of the same
             signature, whatever its access label, specifiers, parameter names, defaults and spacing), each after
             the row the spec lists before it
  memberize  each C function a hand body replaces becomes an empty stub with the member's parameters (its row's,
             defaults dropped), then tools/memberize.py --apply renames every mapped C name and `g_<Class>_<datum>`
             to its member. A `gen` member no C name maps is the function at its role's retail address (the
             generator's `--list`: a field adder symbols.txt calls `FUN_00153ef0`); a hand body's member no C
             function becomes, and the class does not define yet, stops the run with its name
  splice     tools/gen_odl_source.py's boilerplate (`gen`) and the hand `bodies` replace the memberized
             definitions (a definition's head in code, never in a comment or string; an overload's, static or
             not, by its signature); a metafield's descriptor creator and `getMetaField` are igen's; a
             bootstrap class's constructors, copy slot and `__bootstrapDestruct` are written in the kit's form
             over their C definitions, in a namespace block joined with the library's block right before or after
             it, and their unit-objects.json keys renamed to the compiler names; igen's file-scope field tables go
             (the generator keeps them function-local); a static datum's definition takes its declared type;
             `memberize.py --respell` last
  decls      the C-name declarations `memberize.py --check` reports unneeded are deleted (after the
             splice, which drops the last C users of the bootstrap names)
  rekey      `memberize.py --rekey --apply`: the row names the touched units' objects now spell otherwise (a
             template instance or a class renamed or retired, a `stripped` body the object no longer compiles);
             a unit that does not compile yet keeps its names, reported, for a later `--rekey`
  all        the five in order

A run that fails leaves src/, include/ and config/ as it found them. A step changes the text it rewrites and
nothing else: the blank lines around a table it drops or a definition it writes stay as the file had them. The
rows of touched units, the compiler-name map and the checks are the caller's (member-conversion.md).

A spec file is Python defining SPECS = {<class>: dict(...)}; `import classconv` gives it the shared pieces
(COMMON, GEN, STRINGS, array_spec). The keys of a class's dict:

  add      the class is converted already: the spec adds members to it (the `rows` and `typed` the class lacks
           join the tables, its `map`/`extra`/`data` C names become members; `gen` defaults to none, no
           descriptor or bootstrap bodies are written, and its other C names are not reported unmapped)
  lib      library namespace (default "Core"); base: the parent class (a bootstrap class's constructors);
           cxxbase: the kit template instance the class derives from over its registered parent
           (converted-classes.tsv's third column, `igTDataList<igObject *>`)
  rows     class-members.tsv declarations, in the kit header's order
  typed    [(field, C++ type)] rows for typed-fields.tsv
  map      {C suffix: member} for `<Class>_<suffix>` functions; extra: {C name: member} for other C names
  keep     C suffixes that stay free functions (memberize leaves them; anything else unmapped is reported)
  data     {datum suffix: member} for `g_<Class>_<suffix>`
  gen      members whose definitions the generator writes (default GEN)
  bodies   {member: definition}, `{C}` the class (the definition of that member is replaced); `ctor` and `dtor`
           (here and as `map`/`extra` members) are the constructor and the destructor the class declares out of
           line, whose C forms are stubbed to the receiver (the destructor's delete flag dropped), memberized to
           `C::C()`/`C::~C()` and spliced like any other hand body
  overloads   a `map`/`extra` member and its `bodies` key may be the overload's full declaration
           (`void removeInfo(const char *infoName);`), matched to the class's rows (the spec's and
           class-members.tsv's) by signature: name, parameter types and `const`, whatever the spelling's access
           labels, `virtual`/`static`/`inline`, parameter names, defaults, `const` placement and spacing.
           memberize gets the row's signature, the stub the row's parameters, and the splice replaces the
           definition of that signature. A bare name the class overloads, or a declaration two rows fit, stops
           the run
  boot     {Init|CopyConstruct|Construct|Clone|Destruct: definition} overriding the default bootstrap bodies
           (str.format: `{C}` the class, `{B}` the base, braces doubled)
  boot_names  {Init|CopyConstruct|Construct|Destruct: C name} for a bootstrap class whose C names do not
           start with the class's (`ObjectPointerList_Init` for __internalNonRefCountedObjectList)
  descriptor  write igen's metafield descriptor (`arkRegisterMetaValidate`, `getMetaField`); default: the class
           name ends in MetaField
"""
import argparse
import collections
import importlib.util
import json
import os
import re
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)
import cxxscope  # noqa: E402
import demangle  # noqa: E402
import memberize  # noqa: E402

SYMBOLS = "config/SLUS-20836/symbols.txt"
UNIT_OBJECTS = "config/SLUS-20836/unit-objects.json"
# a library's source directories (the DataPump classes are igCore's in the kit and live in retail's own library file)
LIBRARY_DIRS = {"Core": ("src/engine/core", "src/engine/datapump"), "Math": "src/engine/maths",
                "Attrs": "src/engine/attrs",
                "Gfx": "src/engine/gfx", "Sg": "src/engine/scenegraph", "Gui": "src/engine/gui",
                "Insight": "src/engine/insight", "Viewer": "src/engine/viewer"}

# the C names every reflected class shares, and the members they become
COMMON = {"GetMetaObject": "getClassTypeSafe", "GetVTable": "retrieveVTablePointer", "EnsureRegistered": "arkRegister",
          "Register": "arkRegisterInternal", "GetMetaObjectFunction": "getClassMetaSafe",
          "InitFields": "arkRegisterInitialize", "CreateDefaultDescriptor": "arkRegisterMetaValidate",
          "GetDefaultDescriptor": "getMetaField", "GetPublishedMetaObject": "getClassMeta", "GetMeta": "getMeta",
          "GetDescriptor": "getGenericMetaField", "ValueFromString": "setMemoryByString",
          "ValueToString": "getStringFromMemory", "GetSize": "computeSize", "GetAlignment": "computeRequiredAlignment"}
# the members whose definitions tools/gen_odl_source.py writes
GEN = ["getClassTypeSafe", "retrieveVTablePointer", "arkRegister", "arkRegisterInternal", "arkRegisterInitialize"]
STRINGS = ["virtual int setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir);",
           "virtual igStringRef getStringFromMemory(const void *srcMem, igDirectory *dir);"]
# the bootstrap class's C names (IG_BOOTSTRAP_OBJECT_DEFINE), written by `boot_bodies`
BOOT = ("Clone", "Construct", "Init", "CopyConstruct", "Destruct")

DESCRIPTOR = ("void {C}::arkRegisterMetaValidate()\n{{\n    {C} *metaField;\n\n    if (_MetaField == 0) {{\n"
              "        _MetaField = ({C} *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector("
              "kIGMemoryPoolHandleMetaData));\n        metaField = _MetaField;\n        if (metaField != 0) {{\n"
              "            getMetaFieldTypes()->append(metaField);\n"
              "            {{\n                ::igObject *held = (::igObject *)_MetaField;\n"
              "                held->release();\n            }}\n"
              "            _MetaField->_internalIndex = (short)(getMetaFieldTypes()->_count - 1);\n"
              "            _MetaField->validate();\n        }}\n    }}\n}}")
GETMF = "{C} *{C}::getMetaField()\n{{\n    if (_MetaField == 0)\n        arkRegister();\n    return _MetaField;\n}}"


class ConvError(Exception):
    pass


# ---------------------------------------------------------------------------------------------------- text


def block_end(text, brace):
    """The index past the brace closing the one at `brace`; string and character literals and comments skipped."""
    depth, j = 0, brace
    while j < len(text):
        ch = text[j]
        if ch in "\"'":
            j += 1
            while text[j] != ch:
                j += 2 if text[j] == "\\" else 1
        elif text.startswith("/*", j):
            j = text.index("*/", j) + 1
        elif text.startswith("//", j):
            j = text.index("\n", j)
        elif ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                return j + 1
        j += 1
    raise ConvError("unbalanced braces from offset %d" % brace)


def code_text(text):
    """`text` with every comment and string or character literal blanked to spaces (newlines kept), so that
    an offset in it is the same offset in `text`: a definition's head is searched for in code only (a comment
    naming `igFoo::size (the count)` before a definition is no head)."""
    out, j, n = list(text), 0, len(text)

    def blank(lo, hi):
        for k in range(lo, hi):
            if out[k] != "\n":
                out[k] = " "

    while j < n:
        ch = text[j]
        if ch in "\"'":
            k = j + 1
            while k < n and text[k] != ch:
                k += 2 if text[k] == "\\" else 1
            blank(j + 1, min(k, n))
            j = k + 1
        elif text.startswith("/*", j):
            k = text.find("*/", j + 2)
            k = n if k < 0 else k + 2
            blank(j, k)
            j = k
        elif text.startswith("//", j):
            k = text.find("\n", j)
            k = n if k < 0 else k
            blank(j, k)
            j = k
        else:
            j += 1
    return "".join(out)


def find_c_def(text, cname):
    """(start, end) of the file-scope definition of the C function `cname`, or None."""
    m = re.search(r"^(?![ \t])[^\n;{}()]*\b%s\s*\([^;{]*?\)\s*\{" % re.escape(cname), code_text(text), re.M)
    if not m:
        return None
    return m.start(), block_end(text, m.end() - 1)


# a definition's head: at the start of a line, before the qualified name nothing but its type (a use inside an
# expression, `if (Gap::Gfx::igImage::isIndexed(f)) {` or `x = igFoo::k_num;`, or after a keyword, `return X::m(a)`,
# is none)
TYPE_PREFIX = r"^[ \t]*(?!(?:return|else|case|goto|delete|throw|new)\b)(?:[\w:<>,*& \t]*[ \t*&])?(?:\w+::)*"
DEF_HEAD = TYPE_PREFIX + r"%s::(?P<name>%s)\s*\((?P<params>[^;{]*?)\)(?P<tail>[^;{]*)\{"


def member_name(member):
    """The name a spec member names: `name` itself, or the one an overload's full declaration declares."""
    m = re.search(r"(~?\w+)\s*\(", member)
    return m.group(1) if m else member


_ACCESS = r"^\s*(?:(?:public|protected|private)\s*:(?!:)\s*)*"
# the words a parameter's type may end with: never its name
_TYPE_WORDS = frozenset(("const", "volatile", "unsigned", "signed", "int", "char", "short", "long", "float", "double",
                         "void", "bool", "wchar_t"))


def _top_split(text, sep):
    """`text` split at each `sep` outside parentheses, angle brackets, brackets and braces."""
    out, depth, start = [], 0, 0
    for i, ch in enumerate(text):
        if ch in "(<[{":
            depth += 1
        elif ch in ")>]}":
            depth -= 1
        elif ch == sep and depth == 0:
            out.append(text[start:i])
            start = i + 1
    out.append(text[start:])
    return out


def param_type(p):
    """One parameter's type as a signature compares it: its default and its name dropped, `struct`/`class` and
    spacing normalised, a top-level `const` dropped and the base type's `const` written first
    (`char const *name = 0` -> `const char*`)."""
    p = " ".join(_top_split(p, "=")[0].split())
    fp = re.match(r"^(.*\(\s*[*&]+)\s*[A-Za-z_]\w*\s*(\).*)$", p)          # a function pointer `R (*name)(args)`
    if fp:
        p = fp.group(1) + fp.group(2)
    else:
        m = re.match(r"^(?P<type>.*?(?:[\w>]\s+|[*&]\s*))(?P<name>[A-Za-z_]\w*)(?P<arr>(?:\s*\[[^\]]*\])*)$", p)
        if m and m.group("name") not in _TYPE_WORDS and \
                re.sub(r"\b(?:const|volatile)\b|[\s*&]", "", m.group("type")):
            p = m.group("type") + ("*" if m.group("arr") else "")
    p = re.sub(r"\b(?:struct|class|union|enum|typename)\s+", "", p).strip()
    depth, base_end = 0, len(p)
    for i, ch in enumerate(p):
        depth += {"<": 1, "(": 1, ">": -1, ")": -1}.get(ch, 0)
        if depth == 0 and ch in "*&":
            base_end = i
            break
    base, rest = p[:base_end], p[base_end:]
    if re.search(r"\bconst\b", base):
        base = "const " + " ".join(re.sub(r"\bconst\b", " ", base).split())
    rest = re.sub(r"\s*\bconst\s*$", "", rest)
    return re.sub(r"\s*([*&<>,()\[\]])\s*", r"\1", " ".join((base + rest).split()))


def param_types(params):
    """The types of a parameter list (param_type each; `void` alone is none)."""
    out = [param_type(p) for p in _top_split(params, ",") if p.strip()]
    return [] if out == ["void"] else out


def _closing(text, open_):
    """The index of the parenthesis closing the one at `open_`, or None."""
    depth = 0
    for i in range(open_, len(text)):
        depth += {"(": 1, ")": -1}.get(text[i], 0)
        if depth == 0:
            return i
    return None


def signature(decl):
    """(name, parameter types, const) of a function's declaration, definition head or class-members.tsv row —
    access labels, `virtual`/`static`/`inline`, parameter names, defaults and spacing aside — or None for a bare
    name or a datum."""
    m = re.search(r"(~?[A-Za-z_]\w*)\s*\(", decl)
    close = _closing(decl, m.end() - 1) if m else None
    if close is None:
        return None
    return m.group(1), tuple(param_types(decl[m.end():close])), re.match(r"\s*const\b", decl[close + 1:]) is not None


def same_member(a, b):
    """Whether two spec member keys name one member: by name when either is a bare name (declared_row refuses a
    bare name the class overloads), else by signature."""
    if "(" not in a or "(" not in b:
        return member_name(a) == member_name(b)
    return signature(a) == signature(b)


def declared_row(rows, member):
    """The row of `rows` (class-members.tsv rows) declaring spec member `member`, or None when none does: a bare
    name the one function of that name, a full declaration the function of its signature (the one of its name and
    parameters when its `const` is the only difference). A bare name that names overloads, or a declaration two
    rows fit, is ambiguous (ConvError)."""
    name = member_name(member)
    decls = collections.OrderedDict()
    for r in rows:
        s = signature(r)
        if s and s[0] == name:
            decls.setdefault(s, r)
    if "(" not in member:
        if len(decls) > 1:
            raise ConvError("`%s` names %d overloads (%s): key it by its declaration"
                            % (member, len(decls), "; ".join(declaration(r) for r in decls.values())))
        return next(iter(decls.values()), None)
    want = signature(member)
    if want in decls:
        return decls[want]
    loose = [r for s, r in decls.items() if s[:2] == want[:2]]
    if len(loose) > 1:
        raise ConvError("`%s` fits %d rows (%s)" % (member, len(loose), "; ".join(declaration(r) for r in loose)))
    return loose[0] if loose else None


def member_defs(text, cls, name):
    """The (start, head match) of each definition of `cls::name` in `text`, in order: heads searched for in code
    only (code_text), a comment before a definition on its line kept out of it."""
    code = code_text(text)
    for m in re.finditer(DEF_HEAD % (re.escape(cls), name), code, re.M):
        start = m.start()
        lead = len(code[start:m.end()]) - len(code[start:m.end()].lstrip(" \t"))
        if code[start:start + lead] != text[start:start + lead]:
            start += lead
        yield start, m


def replace_member(text, cls, member, body):
    """`text` with the first definition of `cls::member` replaced by `body`, and whether there was one. A member
    given as a full declaration (an overload) is the definition of its signature (the one of its parameters when
    `const` is the only difference): a static overload and a member one of one name differ in their parameters,
    never in the definition's head."""
    want = signature(member) if "(" in member else None
    found = []
    for start, m in member_defs(text, cls, re.escape(member_name(member))):
        have = (m.group("name"), tuple(param_types(m.group("params"))), bool(re.match(r"\s*const\b", m.group("tail"))))
        if want is None or have == want:
            found = [(start, m)]
            break
        if have[:2] == want[:2]:
            found.append((start, m))
    if len(found) != 1:
        return text, False
    start, m = found[0]
    return text[:start] + body.rstrip("\n") + text[block_end(text, m.end() - 1):], True


def declaration(row):
    """What a class-members.tsv (or typed-fields.tsv) row declares: its access labels dropped and its spacing
    normalised (`public: virtual  int f();` and `virtual int f();` declare the same); a row of labels only is
    itself."""
    return " ".join(re.sub(_ACCESS, "", row).split()) or " ".join(row.split())


def row_key(row):
    """What makes two class-members.tsv rows one: a function's signature, else its declaration."""
    s = signature(re.sub(r"\{.*\}\s*;?\s*$", "", declaration(row)))
    return ("function",) + s if s else declaration(row)


def qualified_member(q, member):
    """The memberize table's spelling of a spec member: `Gap::Lib::Class::name`, or an overload's full signature
    with the class qualified (`void Gap::Core::igFoo::remove(const char *name)`), its access labels, defaults,
    pure specifier and inline body dropped."""
    if "(" not in member:
        return "%s::%s" % (q, member)
    decl = re.sub(_ACCESS, "", member).strip()
    decl = re.sub(r"\s*(?:\{.*\}|=\s*0)?\s*;?\s*$", "", decl, flags=re.S)
    name = member_name(decl)
    at = re.search(r"\b%s\s*\(" % re.escape(name), decl)
    close = _closing(decl, at.end() - 1)
    params = ", ".join(" ".join(_top_split(p, "=")[0].split()) for p in _top_split(decl[at.end():close], ","))
    return "%s%s::%s(%s%s" % (decl[:at.start()], q, name, params, decl[close:])


def fragment_pieces(text, cls):
    """{member: definition text} of `cls`'s definitions in a gen_odl_source fragment (the first of each name)."""
    out = {}
    for start, m in member_defs(text, cls, r"~?\w+"):
        out.setdefault(m.group("name"), text[start:block_end(text, m.end() - 1)])
    return out


def ns(lib, body):
    return "namespace Gap {\nnamespace %s {\n\n%s\n}\n}\n" % (lib, body.rstrip("\n"))


def decl_of(rows, member):
    """(static, return type, parameter list without defaults) of the first row declaring `member`, or None (a
    constructor's name is not its destructor's)."""
    for r in rows:
        r = re.sub(_ACCESS, "", r).split("{", 1)[0]    # an inline body naming the member is no declaration
        m = re.match(r"((?:virtual|static|inline)\s+)*(.*?)(?<![\w~])%s\s*\(" % re.escape(member), r)
        close = _closing(r, m.end() - 1) if m else None
        if close is not None:
            params = ", ".join(_top_split(p, "=")[0].strip() for p in _top_split(r[m.end():close], ","))
            return "static" in (m.group(1) or ""), m.group(2).strip(), params.strip()
    return None


def stub_head(cls, cname, decl):
    """The C head of `cname` with the member's parameters (`decl` from decl_of)."""
    static, ret, params = decl
    if static:
        return "%s %s(%s)" % (ret, cname, params or "void")
    return "%s %s(%s *self%s)" % (ret, cname, cls, (", " + params) if params else "")


def stub_text(text, cname, head):
    """`text` with the C definition of `cname` emptied under `head` (the member's parameters, the C form's return
    type: memberize casts the uses whose type the member's return changes), and whether it had one."""
    span = find_c_def(text, cname)
    if not span:
        return text, False
    ret = text[span[0]:text.index(cname, span[0])].strip()
    head = "%s%s%s" % (ret, "" if ret.endswith("*") else " ", head[head.index(cname):])
    return text[:span[0]] + head + "\n{\n}" + text[span[1]:], True


FILE_TABLES = (r"(?m)^(static )?(igMetaObjectCallback |FieldFactory |const char \*|igMetaField \*\*|int )"
               r"g_%s_(callbackList|ctorTable|fieldTable|fieldDescriptors|fieldHandles|fieldOffsets)\[\] = \{[^}]*\};"
               r"[ \t]*(?:\n|$)")


def drop_file_tables(text, cls):
    """igen keeps the registrar's and the field adder's tables function-local: the file-scope C ones go, each with
    the blank lines after it when a blank line comes before it (one table between two paragraphs leaves one
    separator), and the namespace blocks of one library a table separated become one (cxxscope.merge_blocks). The
    file's other blank lines and blocks stay as they are."""
    pat = re.compile(FILE_TABLES % re.escape(cls))
    while True:
        m = pat.search(text)
        if not m:
            return text
        end = m.end()
        if m.start() == 0 or text[:m.start()].endswith("\n\n"):
            end = re.compile(r"(?:[ \t]*\n)*").match(text, end).end()
        text = cxxscope.merge_blocks(text[:m.start()] + text[end:], {m.start()})


def boot_bodies(C, base):
    """{C suffix: (definition, member, parameters)} of a bootstrap class's constructors, copy slot and destruct."""
    return {
        "Clone": ("igObject *{C}::cloneViaMetadata(int copyMode)\n{{\n    if (g_objectSystem->active != 0) {{\n"
                  "        arkRegister();\n        return igObject::cloneViaMetadata(copyMode);\n    }}\n"
                  "    return new (igObject_AllocateRawStorageDefault(sizeof({C}), 0), 0) {C}(*this);\n}}\n",
                  "cloneViaMetadata", ["int"]),
        "Construct": ("{C}::{C}(bool boot) : {B}(boot)\n{{\n    new (this, 0) {C};\n}}\n", "__ct__", ["bool"]),
        "Init": ("{C}::{C}()\n{{\n}}\n", "__ct__", []),
        "CopyConstruct": ("{C}::{C}(const {C} &other) : {B}(other)\n{{\n}}\n", "__ct__", ["const Gap::{L}::{C} &"]),
        "Destruct": ("void {C}::__bootstrapDestruct()\n{{\n    {B}::__bootstrapDestruct();\n}}\n",
                     "__bootstrapDestruct", []),
    }


def boot_key(lib, cls, member, params):
    """The compiler name of a bootstrap body (`params` already formatted)."""
    name = cls if member == "__ct__" else member
    return demangle.mangle("Gap::%s::%s::%s" % (lib, cls, name), params)


# ------------------------------------------------------------------------------------------- array metafields


def array_spec(cls, element, ctype, set_default=None, lib="Core", sizeof=None):
    """The spec of a fixed-size array metafield in the kit's IG_ARRAY_IMPL form: `element` the element's
    metafield, `ctype` its C type, `set_default` the overload retail keeps ("all": fill every element, "index":
    set one, None)."""
    rows = ["IG_OBJECT_DEFINE(%s)" % cls, "IG_METAFIELD_SETUP(%s)" % cls,
            "private: static igMetaField *k_num;",
            "inline void setNum(int numParam) { _num = numParam; }",
            "inline int getNum() const { return _num; }",
            "virtual unsigned short computeSize();",
            "virtual void endianSwapMemory(void *mem, int num) const;"]
    bodies = {"computeSize": "unsigned short {C}::computeSize()\n{\n    return getNum() * sizeof(%s);\n}"
                             % (sizeof or ctype),
              "endianSwapMemory": "void {C}::endianSwapMemory(void *mem, int num) const\n{\n"
                                  "    %s::getMetaField()->endianSwapMemory(mem, getNum() * num);\n}" % element}
    m = dict(COMMON, SwapBytes="endianSwapMemory")
    if set_default == "all":
        rows.append("void setDefault(%s val);" % ctype)
        bodies["setDefault"] = ("void {C}::setDefault(%s val)\n{\n    %s *mem;\n    int i;\n\n"
                                "    setDefaultMemory(0);\n    mem = (%s *)_default;\n"
                                "    for (i = 0; i < getNum(); i++) {\n        mem[i] = val;\n    }\n}"
                                % (ctype, ctype, ctype))
    elif set_default == "index":
        rows.append("void setDefault(unsigned int index, %s val);" % ctype)
        bodies["setDefault"] = ("void {C}::setDefault(unsigned int index, %s val)\n{\n    setDefaultMemory(0);\n"
                                "    ((%s *)_default)[index] = val;\n}" % (ctype, ctype))
    if set_default:
        m.update(SetDefaultValue="setDefault", SetDefaultAll="setDefault", SetDefaultElement="setDefault")
    return dict(lib=lib, rows=rows, map=m, keep=("Create",), bodies=bodies,
                data={"metaObject": "_Meta", "descriptor": "_MetaField", "numMetaField": "k_num"})


# ---------------------------------------------------------------------------------------------------- tree


class Tree:
    """The repository the batch rewrites."""

    # what a step may write: the sources, the headers and the tables
    TRANSACTIONAL = ("src", "include", "config")

    def __init__(self, root=ROOT):
        self.root = root
        self._symbols = None

    def path(self, rel):
        return os.path.join(self.root, rel)

    def read(self, rel):
        with open(self.path(rel)) as f:
            return f.read()

    def write(self, rel, text):
        with open(self.path(rel), "w") as f:
            f.write(text)

    def run(self, args):
        r = subprocess.run([sys.executable] + args, cwd=self.root, capture_output=True, text=True)
        out = r.stdout + r.stderr
        if r.returncode:
            raise ConvError("%s failed:\n%s" % (" ".join(args), out[-3000:]))
        return out

    def _load_symbols(self):
        if self._symbols is None:
            self._symbols = []
            for line in self.read(SYMBOLS).splitlines():
                p = line.split()
                if len(p) >= 3:
                    try:
                        self._symbols.append((int(p[0], 16), p[2]))
                    except ValueError:
                        pass
            self._symbols.sort()
        return self._symbols

    def symbols(self, cls):
        """`cls`'s `<cls>_<suffix>` functions of symbols.txt, as suffixes in address order."""
        return [n[len(cls) + 1:] for _va, n in self._load_symbols() if n.startswith(cls + "_")]

    def symbol_at(self, va):
        """The symbols.txt name of the function at `va`, or None."""
        return next((n for v, n in self._load_symbols() if v == va), None)

    def snapshot(self):
        """{path: bytes} of every file a step may write (TRANSACTIONAL), for `restore`."""
        out = {}
        for top in self.TRANSACTIONAL:
            for d, _dirs, files in os.walk(self.path(top)):
                for f in files:
                    p = os.path.join(d, f)
                    with open(p, "rb") as fh:
                        out[os.path.relpath(p, self.root)] = fh.read()
        return out

    def restore(self, snap):
        """Put the files back as `snapshot` read them: changed and deleted ones rewritten, new ones removed; the
        paths restored."""
        now = self.snapshot()
        changed = sorted(p for p in set(snap) | set(now) if snap.get(p) != now.get(p))
        for p in changed:
            if p in snap:
                os.makedirs(os.path.dirname(self.path(p)), exist_ok=True)
                with open(self.path(p), "wb") as fh:
                    fh.write(snap[p])
            else:
                os.unlink(self.path(p))
        self._symbols = None
        return changed

    def files(self, lib):
        dirs = LIBRARY_DIRS.get(lib)
        if dirs is None:
            raise ConvError("no source directory for library %s (classconv.LIBRARY_DIRS)" % lib)
        if isinstance(dirs, str):
            dirs = (dirs,)
        return sorted(os.path.join(d, f) for d in dirs for f in os.listdir(self.path(d))
                      if f.endswith((".inc", ".cpp", ".h")))

    def files_naming(self, lib, word):
        return [p for p in self.files(lib) if word in self.read(p)]

    def append_rows(self, rel, cls, rows):
        """`rows` (`cls\\t<row>` lines) into a tab table after `cls`'s last row, else at the end."""
        lines = self.read(rel).split("\n")
        if lines and lines[-1] == "":
            lines.pop()
        at = max((i for i, l in enumerate(lines) if l.split("\t", 1)[0] == cls), default=len(lines) - 1) + 1
        lines[at:at] = ["%s\t%s" % (cls, r) for r in rows]
        self.write(rel, "\n".join(lines) + "\n")

    def add_rows(self, rel, cls, rows):
        """The `rows` of `cls` a tab table lacks, in their order among the ones it has: a new row goes after the
        row `rows` lists before it, before the first one it has when none precedes it, and after `cls`'s last
        row when the table has none of `rows`; the rows added. A row the table has is one declaring the same
        (row_key: a function of the same signature, whatever its access label, specifiers, parameter names,
        defaults and spacing; another row of the same declaration), so that adding is idempotent and never
        duplicates one."""
        lines = self.read(rel).split("\n")
        if lines and lines[-1] == "":
            lines.pop()
        have = {}
        for i, l in enumerate(lines):
            if l.split("\t", 1)[0] == cls:
                have.setdefault(row_key(l.split("\t", 1)[1] if "\t" in l else ""), i)
        inserts, pending, queued, anchor = collections.defaultdict(list), [], set(), None
        for r in rows:
            key = row_key(r)
            if key in have:
                if pending:
                    inserts[have[key] if anchor is None else anchor + 1] += pending
                    pending = []
                anchor = have[key]
            elif key not in queued:
                queued.add(key)
                pending.append("%s\t%s" % (cls, r))
        if pending:
            inserts[(anchor if anchor is not None else max(have.values(), default=len(lines) - 1)) + 1] += pending
        for at in sorted(inserts, reverse=True):
            lines[at:at] = inserts[at]
        if inserts:
            self.write(rel, "\n".join(lines) + "\n")
        return [l.split("\t", 1)[1] for at in sorted(inserts) for l in inserts[at]]

    def rekey(self, pairs):
        """Rename unit-objects.json keys `old` -> `new` in every unit row listing them (memberize.rekey_rows, the one
        renaming of row names), in place and in order; the names no row lists."""
        text = self.read(UNIT_OBJECTS)
        data = json.loads(text, object_pairs_hook=collections.OrderedDict)
        rows = collections.OrderedDict((k, r) for k, r in data.items() if isinstance(r, dict))
        listed = {r.get("symbol") for r in rows.values()}
        listed |= {k for r in rows.values() for f in memberize._ROW_FIELDS if isinstance(r.get(f), (dict, list))
                   for k in r[f]}
        memberize.rekey_rows(rows, dict(pairs))
        self.write(UNIT_OBJECTS, json.dumps(data, indent=2, ensure_ascii=False) + ("\n" if text.endswith("\n") else ""))
        return [old for old, _new in pairs if old not in listed]


# ---------------------------------------------------------------------------------------------------- steps


def lib_of(spec):
    return spec.get("lib", "Core")


def gen_of(spec):
    """The members whose definitions the generator writes: none for a spec adding members to a converted class."""
    return spec.get("gen", [] if spec.get("add") else GEN)


def is_descriptor(cls, spec):
    return spec.get("descriptor", not spec.get("add") and cls.endswith("MetaField"))


def step_tables(tree, classes, specs):
    converted = {}
    for l in tree.read("config/converted-classes.tsv").split("\n"):
        p = l.split("\t")
        if len(p) > 1 and not l.startswith("#"):
            converted[p[0]] = p[1]
    for c in classes:
        spec = specs[c]
        if spec.get("add"):
            # members added to a converted class: the rows and typed fields it lacks, the ones it has kept
            if c not in converted:
                raise ConvError("%s is not converted: a spec with `add` adds members to a converted class" % c)
            if converted[c] != lib_of(spec):
                raise ConvError("%s is converted in library %s, the spec says %s" % (c, converted[c], lib_of(spec)))
            tree.add_rows("config/class-members.tsv", c, spec.get("rows", []))
            tree.add_rows("config/typed-fields.tsv", c, ["%s\t%s" % ft for ft in spec.get("typed", ())])
            continue
        if c in converted:
            raise ConvError("%s is converted already (a spec adding members to it sets `add`)" % c)
        tree.append_rows("config/converted-classes.tsv", c,
                         ["\t".join([lib_of(spec)] + ([spec["cxxbase"]] if spec.get("cxxbase") else []))])
        tree.append_rows("config/class-members.tsv", c, spec["rows"])
        if spec.get("typed"):
            tree.append_rows("config/typed-fields.tsv", c, ["%s\t%s" % ft for ft in spec["typed"]])


# the members the object macros declare (include/dw4/core/igObjectMacros.h), as decl_of reads a row
MACRO_DECLS = {"_instantiateFromPool": (True, "{C} *", "igMemoryPoolView *pool"),
               "getMetaField": (True, "{C} *", ""),
               "arkRegisterMetaValidate": (True, "void", ""),
               "arkRegisterInitialize": (True, "void", ""),
               "retrieveVTablePointer": (True, "void *", "")}


def member_decl(cls, rows, member):
    """decl_of the row of `rows` declaring `member` (declared_row; an overload's own full declaration when no row
    does), else the object macros' declaration of it."""
    row = declared_row(rows, member)
    d = decl_of([row or member] if "(" in member or row else rows, member_name(member))
    if d is None and member in MACRO_DECLS:
        static, ret, params = MACRO_DECLS[member]
        d = static, ret.replace("{C}", cls), params
    return d


def class_rows(tree, c, spec):
    """The class-members.tsv rows of `c`: the table's, then the spec's (those the tables step has not written)."""
    rows = []
    for line in tree.read("config/class-members.tsv").split("\n"):
        p = line.split("\t", 1)
        if len(p) == 2 and p[0] == c:
            rows.append(p[1])
    return rows + list(spec.get("rows", ()))


def check_keys(tree, c, spec):
    """Each member a spec key names (`map`, `extra`, `bodies`) is one row of the class or none (a new member):
    a bare name of overloads, or a declaration two rows fit, stops the run (declared_row)."""
    rows = class_rows(tree, c, spec)
    for member in list(spec.get("map", {}).values()) + list(spec.get("extra", {}).values()) + \
            list(spec.get("bodies", {})):
        try:
            declared_row(rows, member)
        except ConvError as e:
            raise ConvError("%s: %s" % (c, e))


def generator_roles(tree, classes, specs):
    """{class: {member: address}} of the boilerplate roles tools/gen_odl_source.py reads from the retail registrar
    (`arkRegisterInitialize=0x153ef0`), for the classes whose `gen` the generator writes."""
    classes = [c for c in classes if gen_of(specs[c])]
    if not classes:
        return {}
    out = {}
    args = ["tools/gen_odl_source.py", "--list"] + [a for c in classes for a in ("--class", c)]
    for line in tree.run(args).splitlines():
        p = line.split()
        if p and p[0] in classes:
            out[p[0]] = {m: int(va, 16) for m, va in re.findall(r"(\w+)=0x([0-9a-fA-F]+)", line)}
    return out


def c_names(tree, c, spec, roles=None):
    """[(C name, member)] of the functions of class `c` the batch converts: `extra`'s, the `<c>_<suffix>` of
    symbols.txt that `map` names, and for a `gen` member no other C name maps the function at the address the
    retail registrar gives its role (`roles`, generator_roles: a field adder symbols.txt calls `FUN_00153ef0`)."""
    pairs = list(spec.get("extra", {}).items())
    pairs += [("%s_%s" % (c, n), spec["map"][n]) for n in tree.symbols(c) if n in spec.get("map", {})]
    have = {member_name(m) for _cname, m in pairs}
    for member in gen_of(spec):
        va = (roles or {}).get(member)
        if va is None or member in have:
            continue
        cname = tree.symbol_at(va)
        if cname is None:
            raise ConvError("%s::%s: symbols.txt has no function at 0x%x, its retail role" % (c, member, va))
        other = next((m for n, m in pairs if n == cname), None)
        if other is not None:
            raise ConvError("%s::%s: its retail role 0x%x is %s, which the spec maps to %s"
                            % (c, member, va, cname, other))
        pairs.append((cname, member))
        have.add(member)
    return pairs


def defines_member(tree, c, spec, name):
    """Whether the class's library defines `c::name` already."""
    return any(next(member_defs(tree.read(p), c, re.escape(name)), None)
               for p in tree.files_naming(lib_of(spec), "%s::%s" % (c, name)))


def unbacked_members(tree, c, spec, pairs, roles=None):
    """The members whose definition the spec writes (a hand body, a generator role) that no C function becomes
    and the class does not define yet: the splice would have nothing to write them over."""
    have = {member_name(m) for _cname, m in pairs}
    wanted = {member_name(m) for m in spec.get("bodies", {})}
    wanted |= {m for m in gen_of(spec) if m in (roles or {})}
    return sorted(m for m in wanted - have if not defines_member(tree, c, spec, m))


def stub(tree, cls, spec, pairs):
    """Each C function (`pairs`, c_names) a hand body or the generator replaces becomes an empty definition with
    the member's parameters (memberize refuses a C form whose parameters differ from the member's)."""
    rows = class_rows(tree, cls, spec)
    for cname, member in pairs:
        if not any(same_member(member, b) for b in spec.get("bodies", {})) and member not in gen_of(spec):
            continue
        d = member_decl(cls, rows, member)
        if d is None:
            continue
        for path in tree.files_naming(lib_of(spec), cname):
            text, ok = stub_text(tree.read(path), cname, stub_head(cls, cname, d))
            if ok:
                tree.write(path, text)
                break


def memberize_table(tree, classes, specs, roles=None):
    """The memberize rows of the batch, and the class's C names neither mapped nor kept (none for a spec adding
    members to a converted class, whose other C names are its members already)."""
    table, unmapped = [], []
    for c in classes:
        spec = specs[c]
        q = "Gap::%s::%s" % (lib_of(spec), c)
        for g, m in spec.get("data", {}).items():
            table.append(("g_%s_%s" % (c, g), "%s::%s" % (q, m)))
        pairs = c_names(tree, c, spec, (roles or {}).get(c))
        rows = class_rows(tree, c, spec)
        table += [(cname, qualified_member(q, (declared_row(rows, m) or m) if "(" in m else m)) for cname, m in pairs]
        if not spec.get("add"):
            mapped = {cname for cname, _m in pairs}
            unmapped += ["%s_%s" % (c, n) for n in tree.symbols(c)
                         if "%s_%s" % (c, n) not in mapped and n not in spec.get("keep", ()) and n not in BOOT]
    return table, unmapped


def step_memberize(tree, classes, specs):
    for c in classes:
        check_keys(tree, c, specs[c])
    roles = generator_roles(tree, classes, specs)
    pairs = {c: c_names(tree, c, specs[c], roles.get(c)) for c in classes}
    unbacked = ["%s::%s" % (c, m) for c in classes
                for m in unbacked_members(tree, c, specs[c], pairs[c], roles.get(c))]
    if unbacked:
        raise ConvError("no C function becomes %s: name it in the spec's `map` or `extra`" % ", ".join(unbacked))
    for c in classes:
        stub(tree, c, specs[c], pairs[c])
    table, unmapped = memberize_table(tree, classes, specs, roles)
    for n in unmapped:
        print("unmapped: %s" % n)
    tree.run(["scripts/gen_type_headers.py"])
    with tempfile.NamedTemporaryFile("w", suffix=".tsv", delete=False) as f:
        f.writelines("%s\t%s\n" % row for row in table)
    try:
        out = tree.run(["tools/memberize.py", f.name, "--apply"])
    finally:
        os.unlink(f.name)
    if "refused" in out:
        raise ConvError("memberize refused:\n" + "\n".join(l for l in out.splitlines() if "refused" in l))
    print(out.rstrip())


def static_data(rows):
    """{name: type} of the static data members `rows` declare (`private: static igMetaField *k_num;`)."""
    out = {}
    for r in rows:
        m = re.match(r"^(?:(?:public|protected|private)\s*:\s*)?static\s+([^();=]*?)\s*\b(\w+)\s*;$", r.strip())
        if m:
            t = m.group(1)
            out[m.group(2)] = t + ("" if t.endswith("*") else " ")
    return out


def respell_data(text, cls, rows):
    """A static datum's definition memberize left in its C type (`int igX::k_y;`) in the declared type."""
    for name, t in static_data(rows).items():
        text = re.sub(TYPE_PREFIX + r"%s::%s;" % (re.escape(cls), name), "%s%s::%s;" % (t, cls, name), text,
                      flags=re.M)
    return text


def splice_class(tree, c, spec, frag):
    """Write the generator's and the hand definitions of one class over its memberized ones."""
    lib = lib_of(spec)
    if "%s: not written" % c in frag and gen_of(spec):
        # a class whose registration the spec writes by hand (`gen` empty, the bodies igen's form) needs no generator
        raise ConvError("generator: " + re.search(r"%s: not written: .*" % re.escape(c), frag).group(0))
    gen = fragment_pieces(frag, c)
    hand = {m: b.replace("{C}", c) for m, b in spec.get("bodies", {}).items()}
    if is_descriptor(c, spec):
        hand.setdefault("arkRegisterMetaValidate", DESCRIPTOR.format(C=c))
        hand.setdefault("getMetaField", GETMF.format(C=c))
    done = set()
    for path in tree.files_naming(lib, "%s::" % c):
        t = tree.read(path)
        if is_descriptor(c, spec):
            t = re.sub(TYPE_PREFIX + r"%s::_MetaField;" % c, "%s *%s::_MetaField;" % (c, c), t, flags=re.M)
        t = respell_data(t, c, spec.get("rows", ()))
        for member in gen_of(spec):
            if member in gen and member not in hand:
                t, ok = replace_member(t, c, member, gen[member])
                if ok:
                    done.add(member)
        for member, body in hand.items():
            t, ok = replace_member(t, c, member, body)
            if ok:
                done.add(member)
        tree.write(path, drop_file_tables(t, c))
    wanted = (set(gen_of(spec)) & set(gen)) | set(spec.get("bodies", {}))
    missing = sorted(wanted - done)
    print("%s: spliced %d%s" % (c, len(done), (" MISSING " + " ".join(missing)) if missing else ""))
    if not spec.get("add") and "Construct" in boot_cnames(tree, c, spec):
        splice_boot(tree, c, spec)


def boot_cnames(tree, c, spec):
    """{BOOT suffix: C name} of the bootstrap bodies `c` has: `<c>_<suffix>` from symbols.txt, or the spec's
    `boot_names`."""
    out = {n: "%s_%s" % (c, n) for n in tree.symbols(c) if n in BOOT}
    out.update(spec.get("boot_names", {}))
    return out


def splice_boot(tree, c, spec):
    """A bootstrap class's constructors, copy slot and bootstrap destruct, in the kit's form: each over its C
    definition, in its namespaces' block, joined with a block of the library right before or after it
    (cxxscope.merge_blocks); the blank lines around it stay."""
    lib = lib_of(spec)
    bodies = boot_bodies(c, spec["base"])
    for n, override in spec.get("boot", {}).items():
        bodies[n] = (override,) + bodies[n][1:]
    cnames = boot_cnames(tree, c, spec)
    rekeys = []
    for n, (body, member, params) in bodies.items():
        if n not in cnames:
            continue
        cname = cnames[n]
        body = body.format(C=c, B=spec["base"])
        params = [p.format(C=c, L=lib) for p in params]
        for path in tree.files_naming(lib, cname):
            t = tree.read(path)
            span = find_c_def(t, cname)
            if span:
                end = span[1] + 1 if t[span[1]:span[1] + 1] == "\n" else span[1]
                block = ns(lib, body)
                tree.write(path, cxxscope.merge_blocks(t[:span[0]] + block + t[end:],
                                                       {span[0], span[0] + len(block)}))
                rekeys.append((cname, boot_key(lib, c, member, params)))
                break
        else:
            print("%s: no definition of %s" % (c, cname))
    for old in tree.rekey(rekeys):
        print("%s: no unit-objects key %s" % (c, old))


def step_splice(tree, classes, specs):
    for c in classes:
        check_keys(tree, c, specs[c])
    args = ["tools/gen_odl_source.py"]
    for c in classes:
        if gen_of(specs[c]):
            args += ["--class", c]
    frag = tree.run(args) if len(args) > 1 else ""
    for c in classes:
        splice_class(tree, c, specs[c], frag)
    tree.run(["tools/memberize.py", "--respell", "--apply"])
    # a list's element field and the like store the descriptor as a word
    for lib in sorted({lib_of(specs[c]) for c in classes}):
        for path in tree.files(lib):
            t = tree.read(path)
            n = re.sub(r"_memType = (Gap::\w+::\w+::getMetaField\(\);)", r"_memType = (int)\1", t)
            if n != t:
                tree.write(path, n)
        drop_empty_fragments(tree, lib)


def drop_empty_fragments(tree, lib):
    """A library fragment (`.inc`) the conversion left empty (an inline's retail copy it held is the compiler's
    now) goes, and with it the `#include` naming it; the paths dropped."""
    dropped = [p for p in tree.files(lib) if p.endswith(".inc") and not tree.read(p).strip()]
    if not dropped:
        return []
    for path in tree.files(lib):
        if path in dropped:
            continue
        t = tree.read(path)
        n = "".join(l for l in t.splitlines(True)
                    if not any(l.strip() == '#include "%s"' % d for d in dropped))
        if n != t:
            tree.write(path, n)
    for path in dropped:
        os.unlink(tree.path(path))
        print("%s: empty, dropped with its #include" % path)
    return dropped


def leftover_declarations(report):
    """{path: {line}} of the C-name declarations a `memberize.py --check` report names."""
    out = collections.defaultdict(set)
    for line in report.splitlines():
        m = re.match(r"^(\S+):(\d+): \S+: C-name declaration no longer needed", line)
        if m:
            out[m.group(1)].add(int(m.group(2)))
    return out


def step_decls(tree):
    """Delete the C-name declarations the conversion left unneeded (memberize --check), one line each."""
    r = subprocess.run([sys.executable, "tools/memberize.py", "--check"], cwd=tree.root, capture_output=True,
                       text=True)
    for path, lines in sorted(leftover_declarations(r.stdout).items()):
        text = tree.read(path).split("\n")
        tree.write(path, "\n".join(l for i, l in enumerate(text, 1) if i not in lines))
        print("%s: %d declaration%s dropped" % (path, len(lines), "" if len(lines) == 1 else "s"))


def step_rekey(tree):
    """The touched units' row names their objects now spell otherwise (memberize.py --rekey --apply)."""
    print(tree.run(["tools/memberize.py", "--rekey", "--apply"]).rstrip())


def special_members(c, spec):
    """`spec` with its `ctor` and `dtor` members named as C++ names them: `extra`/`map` values and `bodies` keys
    `ctor` are the constructor `c`, `dtor` the destructor `~c` (a constructor or destructor the class declares out
    of line, whose body is a hand body: its C form is stubbed, memberized and spliced as any other)."""
    names = {"ctor": c, "dtor": "~" + c}
    out = dict(spec)
    for key in ("extra", "map"):
        if key in spec:
            out[key] = {k: names.get(v, v) for k, v in spec[key].items()}
    if "bodies" in spec:
        out["bodies"] = {names.get(k, k): v for k, v in spec["bodies"].items()}
    return out


def load_specs(path):
    sys.path.insert(0, HERE)
    s = importlib.util.spec_from_file_location("classconv_spec", path)
    mod = importlib.util.module_from_spec(s)
    s.loader.exec_module(mod)
    return {c: special_members(c, spec) for c, spec in mod.SPECS.items()}


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("spec", help="the batch's spec file (Python defining SPECS)")
    ap.add_argument("step", choices=("tables", "memberize", "splice", "decls", "rekey", "all"))
    ap.add_argument("classes", nargs="*", help="the classes to convert (default: the spec's, in order)")
    ap.add_argument("--root", default=ROOT)
    a = ap.parse_args(argv)
    specs = load_specs(a.spec)
    classes = a.classes or list(specs)
    unknown = [c for c in classes if c not in specs]
    if unknown:
        ap.error("not in the spec: " + " ".join(unknown))
    tree = Tree(a.root)
    # a run that fails leaves the tree as it found it: the stubs, rows and rewrites of its steps go
    snap = tree.snapshot()
    try:
        if a.step in ("all", "tables"):
            step_tables(tree, classes, specs)
        if a.step in ("all", "memberize"):
            step_memberize(tree, classes, specs)
        if a.step in ("all", "splice"):
            step_splice(tree, classes, specs)
        tree.run(["scripts/gen_type_headers.py"])
        if a.step in ("all", "decls"):
            step_decls(tree)
        if a.step in ("all", "rekey"):
            step_rekey(tree)
    except BaseException as e:
        restored = tree.restore(snap)
        if not isinstance(e, ConvError):
            raise
        print("classconv: %s" % e, file=sys.stderr)
        print("classconv: nothing written (%d file%s restored)" % (len(restored), "" if len(restored) == 1 else "s"),
              file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
