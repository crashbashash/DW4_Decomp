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
name one member (an alias a header declares for the same address, such as a published accessor), and one table
may convert overloads of one name, each row giving its full signature (`igObjectList::search` by field kind). A
class's `operator new`/`operator delete` (`void *igObject::operator new(size_t cSize, size_t allocSize,
igMemoryPoolView *mp)`) is a static member like any other: `__nw__…` its compiler name, `Gap::Core::igObject::
operator new(a, b, c)` its call outside the class, `operator new(a, b, c)` inside it.

For each conversion, across every source, header and `.inc` fragment of src/ and include/:

  * the definition: its head becomes `T Class::name(...)` (a `(void)` list becomes `()`); for an instance member
    the C function's first parameter is the receiver and goes. In the body the receiver is `this`, written
    without a local copy of it (a copy changes register allocation): `self->field` becomes `field` when `field`
    is a field or member of the class (`this->field` where a parameter or local of that name hides it) and the
    receiver's declared type reads it with the same type; any other `self->x` becomes `((T *)this)->x` for a
    receiver declared as some other type `T` (a dispatch view), else `this->x`; a bare `self` becomes `this`
    (cast to `T *` where it was declared as `T`, to `::Class *` where it was the flat struct of a converted class,
    except returned). A converted class's body moving in from file scope keeps what its types meant: a bare
    `Class` there was the flat struct and becomes `::Class`. A body that reuses its receiver's variable once done
    with it (a statement `self = (T *)r.p;`) keeps it as a local of the receiver's type from there on, declared by
    that assignment (`T *self = ...;`, or at the body's top when a later use is outside its block); a receiver
    assigned inside an expression or a loop that read it before, incremented or having its address taken is
    refused. A C function whose parameters already equal the member's (an instance member whose receiver was
    unused) keeps its list; a type spelled by its owner (`igFile::OpenMode` in a subclass of igFile, a Gap
    class's `Gap::Lib::` scope) is the member's. A C parameter of another type of one layout takes the member's
    type (retyped_params): an integer for another integer, an enum or `bool` keeps its C name; a pointer to
    another type becomes the member's parameter, and the body's first line declares the C name from it
    (`unsigned int *dst = (unsigned int *)dest;`), the C name keeping the member's type where the member names
    the parameter as a local or field does; callers cast a pointer argument the member's type does not take
    implicitly. A 64-bit integer for a narrower one needs the table row to state the member's signature. A
    member the class defines inline (its declaration has a body) loses the C
    definition instead. A class of config/converted-classes.tsv is `Gap::<Library>::Class` (the table may name it
    bare), and its definitions are written inside its namespaces, `namespace Gap { namespace <Library> {` around
    `T Class::name(...)` (tools/cxxscope.py, the spelling of the kit's .cpp files and of igen's ODLSource, which
    tools/gen_odl_source.py writes too; adjacent definitions share one block);
  * a constructor (`Class::Class`, declared in class-members.tsv) from its C form `T *Class_Init(T *self, ...)`:
    the head has no return type, and what MWCC writes in a C++ constructor goes from the body: the store of the
    vtable into the receiver, the closing `return self;`, and a first statement constructing a base class by its
    C name (this batch's constructor or one the compiler-name map binds), which C++ does implicitly (with
    arguments, the member initialiser ` : Base(args)`); a base constructed after other statements is refused;
  * a destructor (`Class::~Class`): Alchemy's are implicit (the class declares none; the compiler writes the
    vtable stamp, each member's release and the delete where an object is destroyed), so the C body
    `Class_Destroy(self, flag)` goes, with its comment; a destructor the class declares out of line takes the
    head `Class::~Class()` over a C form emptied to its head (tools/classconv.py's stub of a hand body: the user
    body is written by hand) and is refused over any other. `Class_Destroy(p, 1)` on a pointer declared as the
    Gap class (or a subclass) becomes `delete p`;
  * a static datum's definition `T g_x;` becomes `T Class::name;`;
  * calls and uses in C++: inside a member function of the class the bare `name(...)`; a static member elsewhere
    `Class::name(...)` (and `Class::name` as a value); an instance call `C_name(obj, a)` becomes `obj->name(a)`,
    the receiver cast to the class (`((Class *)expr)->name(a)`) unless it is declared as the class or one of its
    subclasses (`obj->name(a)`), `&x` becomes `x.name(a)` (`((Class *)&x)->name(a)` for a converted class), and a
    call on the function's own receiver inside a member of the class is the bare `name(a)`. For a converted class
    the flat struct of the same name is another type: a receiver declared as it (or a flat subclass) is cast to
    the Gap class too (`Class` alone in Gap's scope), and so is an argument for a `Class *` parameter that is not
    declared as the Gap class or a Gap subclass, while a cast of `this` to the flat struct passed there goes;
  * a call's arguments take the member's order where the C prototype orders them otherwise
    (igRegistry_GetValueFloat's `create, defaultValue` for the kit's `defaultVal, createValue`): each member
    parameter takes the C argument whose type fits it and whose name matches it (`create` begins `createValue`);
    the C order stands while it fits and no other order matches more names, and a call whose order the types and
    names leave open is refused;
  * an argument for a reference parameter `const T &` where the C form took a pointer to the value is
    dereferenced (`*(const T *)v`, its own pointer cast dropped), a temporary's array member (`T(...).vec`) is the
    temporary, and a name declared as `T` (or a typedef of it: `igStringObjRef` for `igSmartPointer<igStringObj>`)
    stays, as does the address of one (`&x`, `(igStringObj **)&x`, `&x.p`), which becomes `x`;
  * the address of a temporary (`&igStringRef(name)`, where the C form took `const igStringRef *`) passed for a
    parameter taking the class by value or reference is the temporary (`igStringRef(name)`), which the compiler
    builds in place as before;
  * an argument for an enum parameter (a nested one such as igFile's `OpenMode`, or one at file scope such as
    `IG_GFX_DRAW`) is cast to it (`(IG_GFX_DRAW)primitive`, `(Gap::Core::igFile::OpenMode)n` outside the class)
    unless it is an enumerator of it, a cast to it, a name declared as it or a call returning it;
  * a static member whose return type differs from the C definition's keeps its uses' types: a call assigned
    where the C form's integer went is cast back to it (`*p = (int)Class::make()`), and the member named in an
    array initialiser of a function-pointer typedef (a field table) is cast to that typedef;
  * a parameter the C form (its definition or a prototype) takes as an integer where the member takes a pointer
    (a factory's memory pool passed as `int`) is the member's type in the head, and each call's argument is
    cast: `(int)E` becomes `E` where E already has the pointer type (a cast, a local or parameter, a function's
    or member's declared return), else `(T *)E`; a literal `0` stays; the function named as a value is a static
    member whose type changed (cast in a field table, as above);
  * a virtual function (its class-members.tsv row says `virtual`) called by its C name runs that implementation,
    not the object's override, so it never becomes `obj->name(a)`: a call on `this` inside a member of the class
    or a subclass becomes the qualified `Class::name(a)`, and every other use keeps the C name, with its
    declarations (the base call of an override not converted yet);
  * calls in C (a `.c` unit, a fragment or header only C units read) keep the C name: the link renames every
    compiler name to its `symbols.txt` name, so the C name still resolves. So do a constructor's or destructor's
    calls on objects of classes still written as flat structs (a GetVTable probe, an unconverted subclass), and a
    call of a private member (`private:` on its class-members.tsv row) outside its class or of a protected one
    outside the class and its subclasses: the kit reaches those only through the class's own inlines;
  * a call in a `#define`'s replacement text (its continuation lines included) or in a member function a class
    body defines is a call like any other, its receiver cast to the class (a macro parameter parenthesised);
    a statement names the C name as a declaration only when a type comes before the name (a template instance's
    too: `igSmartPointer<struct igObject> igResource_GetDirectory(void *directory, const char *name);`);
  * the boundary: while any code still names the C name, its prototype stays in its home header (a header under
    include/, the one named for the class first), and in another header only where a user's unit does not read
    the home header; every other declaration of the C name (`extern "C"` lines, C-linkage blocks, a unity
    header's own prototypes), and all of them once nothing names it, goes, and an `#ifdef __cplusplus`/`#endif`
    pair or `extern "C" { }` block left empty goes with it; so does a `static inline` C++ overload forwarding
    another pointer type to the C name once no C++ code names it. `--check` reports a declaration of a
    converted member's C name (compiler-names.tsv, a converted class) that rule would remove, exit status 1;
  * comments keep the C name, which stays the symbol's retail name (symbols.txt); only a code span holding just the
    C name (`` `igObjectList_SetCount` ``) names the member as code now does (`igObjectList::setCount`), unless code
    still uses the C name;
  * config/SLUS-20836/unit-objects.json: in the unit that places the function or datum, its `emitted`/`data`
    key (or the row's `symbol`) becomes the compiler name (demangle.mangle: `setVisualContext__10igRendererFP15
    igVisualContext`), which is how tools/compiler_names.py binds the compiler name to the `symbols.txt` key;
    the parameter types are spelled as the class's scope finds them (NameScope): a type nested in the class or
    a base qualified by its owner (`Q43Gap4Core6igFile8OpenMode`), a function or function-pointer typedef as its
    type (`igIOCallbackFunction *` is `PFii_v`), a converted class as its Gap class. A key of a converted
    class's member whose parameter names a class converted since as its flat struct (`…FP6igFile` once igFile is
    `Gap::Core::igFile`) is renamed to the name the compiler now emits (`…FPQ33Gap4Core6igFile`) by every batch
    and by `--rekey`; `--check` reports one. Some names only the unit's object settles, so `--rekey` compiles each
    whole-file unit holding one and renames a name its object no longer has, in every field of the row: a template
    instance naming a converted class as its flat struct (`__dt__32igSmartPointer<14igVertexStream>Fv`) is whichever
    instance the unit's source spells (the Gap class's inside its namespaces, the flat struct's at file scope), the
    object's one name that differs from it only in Gap scopes (`__dt__42igSmartPointer<Q33Gap3Gfx14igVertexStream>
    Fv`); a name naming a class the tree no longer declares (a view retired, a helper renamed) is the object's one
    name the row does not list that differs from it only in the classes it names (`__dt__11igScopeLockFv` for
    `__dt__10ScopedLockFv`), and a `stripped` name with no such name goes (`__dt__33igSmartPointer<15igSemaphore
    View>Fv` once igSemaphoreView is retired: the object no longer compiles that body); `--check` compiles nothing
    and does not report these. `externals` and `data` rows of the C names in other units go (the
    compiler-name map resolves them), and a `duplicates` key is renamed. `python3 tools/compiler_names.py
    --write` then regenerates the map, and `python3 tools/whole_file_rows.py --cxx` writes the `duplicates` rows
    of units that emit a copy of an inline member.

It refuses the batch, before writing anything, when a C name has no definition (and is not an alias of one that
has), a file-scope `static` is named (it stays a free function), the member is not declared and the table gives
no signature, the declaration and the C definition disagree in their parameters' number or in what one means (a
pointer for a value or a reference, a float for an integer; the message names the parameter), a C prototype
orders the parameters in a way the types and names leave open (above), an
instance member is used as a value or called without a receiver, or the receiver is assigned where it cannot
become a local (above) or has its address taken.

Dry run by default (`--diff` shows the source changes); `--apply` writes. Then regenerate
include/dw4/support/reflected.h (`python3 scripts/gen_type_headers.py`) when config/class-members.tsv changed,
and verify each touched unit with tools/check.py.

  memberize.py table.tsv                 # what would change
  memberize.py table.tsv --diff          # ...with the source diff
  memberize.py table.tsv --apply         # do it
  memberize.py --respell [--apply]       # every `T Gap::Lib::Class::m(...)` definition into its namespaces
  memberize.py --check                   # C-name declarations nothing needs any more, stale compiler names
  memberize.py --rekey [--apply]         # rename the stale names of unit-objects.json (compiles the units)
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
import compiler_names  # noqa: E402
import cxxscope  # noqa: E402
import declarations  # noqa: E402
import units  # noqa: E402
from demangle import demangle, mangle, map_scopes  # noqa: E402
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

    def __init__(self, cname, cls, name, kind, static, const, inline, ret, params, declaration, virtual=False):
        self.cname, self.cls, self.name, self.kind = cname, cls, name, kind
        self.static, self.const, self.inline = static, const, inline
        self.ret, self.params = ret, params            # normalised types (declarations.Types)
        self.declaration = declaration                 # the class-members.tsv text to add, or None
        self.virtual = virtual                         # a virtual function: a call by its C name is not virtual
        self.implicit = False                          # a destructor the class does not declare: the compiler's
        self.mangled = None
        self.va = None
        self.access = None                             # `private`/`protected` from its class-members.tsv row
        self.getter = None                             # a public static inline `{ return name; }` of the class
        self.c_params = {}                             # index -> (C type, member type) the definition retyped
        self.stated = False                            # the table row gives the member's signature
        self.raw_params = None                         # the parameters as its declaration spells them, names kept
        self.order = None                              # member index -> C argument index, where the C order differs

    @property
    def base(self):
        """The class's own name, without its namespaces."""
        return self.cls.rsplit("::", 1)[-1]

    @property
    def qualified(self):
        return "%s::%s" % (self.cls, self.name)

    @property
    def special(self):
        """"ctor" for a constructor (`Class::Class`), "dtor" for a destructor (`Class::~Class`), else None."""
        if self.name == self.base:
            return "ctor"
        return "dtor" if self.name == "~" + self.base else None


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


# a class's allocation functions, which declarations.py does not read as members: written as a stand-in identifier
# for the scan and named back after it
_ALLOCATORS = {"operator new": "__memberize_operator_nw", "operator delete": "__memberize_operator_dl",
               "operator new[]": "__memberize_operator_nwa", "operator delete[]": "__memberize_operator_dla"}
_ALLOCATOR = re.compile(r"\boperator\s*(new|delete)\b(\s*\[\s*\])?")


def allocator_name(text):
    """`operator new` / `operator delete[]` for a spelling of a class allocation function, else None."""
    m = _ALLOCATOR.fullmatch(text.strip())
    return "operator %s%s" % (m.group(1), "[]" if m.group(2) else "") if m else None


def declared_members(cls, rows, macros, types):
    """[declarations.Member] a class's class-members.tsv rows declare, object macros expanded. A class's
    `operator new`/`operator delete` (static, as C++ makes them) is one too."""
    text = declarations.expand_function_macros("\n".join(rows), macros)
    text = _ALLOCATOR.sub(lambda m: _ALLOCATORS[allocator_name(m.group(0))], text)
    code, _langs = declarations.clean("class %s {\n%s\n};\n" % (cls, text))
    found, _defined, _bodies = declarations.member_scan(code, "config/class-members.tsv", types, macros)
    names = {stand_in: name for name, stand_in in _ALLOCATORS.items()}
    for m in found:
        m.cls = cls
        if m.name in names:
            m.name, m.static = names[m.name], True
    return found


_SIGNATURE = re.compile(r"^(?P<lead>(?:static\s+|inline\s+|virtual\s+)*)(?P<ret>.*?)\b(?P<cls>(?:[A-Za-z_]\w*::)+)"
                        r"(?P<name>~?[A-Za-z_]\w*|operator\s*(?:new|delete)\b(?:\s*\[\s*\])?)"
                        r"\s*(?P<rest>(?:\(.*\)\s*(?:const)?)?)\s*;?$", re.S)


_ACCESS = re.compile(r"\b(public|protected|private)\s*:(?!:)\s*")


def row_statements(rows, macros=None):
    """[(access, declaration)] of class-members.tsv rows in table order, object macros expanded: a row's leading
    label (none is public) holds for the row, and a label inside a macro's body for the rest of that row."""
    out = []
    for row in rows:
        m = _ACCESS.match(row.lstrip())
        access = m.group(1) if m else "public"
        body = row.lstrip()[m.end():] if m else row
        body = declarations.expand_function_macros(body, macros) if macros else body
        at, depth, start = 0, 0, 0
        while at < len(body):
            c = body[at]
            if depth == 0:
                label = _ACCESS.match(body, at)
                if label and not body[start:at].strip():
                    access, at = label.group(1), label.end()
                    start = at
                    continue
            if c == "{":
                depth += 1
            elif c == "}":
                depth -= 1
                if depth == 0:
                    out.append((access, body[start:at + 1].strip()))
                    start = at + 1
            elif c == ";" and depth == 0:
                out.append((access, body[start:at + 1].strip()))
                start = at + 1
            at += 1
        if body[start:].strip():
            out.append((access, body[start:].strip()))
    return out


def _names(statement, name):
    return re.search(r"(?:^|[\s*&:~])%s\s*(?:\(|;|\[|$)" % re.escape(name), statement)


def declares_virtual(rows, name, params=None, macros=None, types=None, cls="C"):
    """Whether class-members.tsv rows of class `cls` declare function `name` virtual (object macros expanded);
    with `params`, the overload taking those parameters (a non-virtual overload of a virtual name is not)."""
    for _access, stmt in row_statements(rows, macros):
        if not (re.match(r"(?:inline\s+)?virtual\b", stmt) and re.search(r"[\s*&]%s\s*\(" % re.escape(name), stmt)):
            continue
        if params is None:
            return True
        found = declared_members(cls, [stmt if stmt.endswith((";", "}")) else stmt + ";"], macros, types)
        if any(d.name == name and tuple(d.params or ()) == tuple(params) for d in found):
            return True
    return False


def declared_raw_params(rows, name, params, const=False, macros=None, types=None, cls="C"):
    """The parameters as the class-members.tsv row of function `name` taking `params` (normalised) spells them,
    names and defaults included (`igFile::OpenMode openMode`), or None when no row declares it."""
    call = re.compile(r"(?:^|[\s*&:~])%s\s*\(" % re.escape(name))
    for _access, stmt in row_statements(rows, macros):
        m = call.search(stmt)
        if not m:
            continue
        found = declared_members(cls, [stmt if stmt.endswith((";", "}")) else stmt + ";"], macros, types)
        if any(d.name == name and tuple(d.params or ()) == tuple(params) and bool(d.const) == bool(const)
               for d in found):
            close = declarations._close(stmt, m.end() - 1)
            return [a for a in _split_args(stmt[m.end():close]) if a not in ("", "void")]
    return None


def declared_access(rows, name, macros=None):
    """The access (`private`, `protected`) class-members.tsv rows give member `name` (object macros expanded),
    or None for public."""
    for access, stmt in row_statements(rows, macros):
        if _names(stmt, name):
            return access if access != "public" else None
    return None


def public_getter(rows, name, macros=None):
    """The public static inline function of class-members.tsv rows whose body is `{ return name; }` (the kit's
    `getClassMeta()` for `_Meta`), or None."""
    for access, stmt in row_statements(rows, macros):
        m = re.match(r"static\s+inline\s+[^;{]*?\b([A-Za-z_]\w*)\s*\(\s*\)\s*\{\s*return\s+%s\s*;\s*\}$"
                     % re.escape(name), stmt)
        if m and access == "public":
            return m.group(1)
    return None


def _is_read(clean, pos, end):
    """Whether the name at clean[pos:end] is read only: not assigned, incremented or having its address taken."""
    before = clean[:pos].rstrip()
    after = clean[end:].lstrip()
    if before.endswith(("&", "++", "--")) and not before.endswith("&&"):
        return False
    return not (re.match(r"(?:[-+*/%&|^]|<<|>>)?=(?!=)", after) or after.startswith(("++", "--")))


def conversions(rows, members, macros, types):
    """[Conversion] for the table rows -> (conversions, errors)."""
    out, errors, cache = [], [], {}
    for cname, text, line in rows:
        m = _SIGNATURE.match(text.strip())
        if not m:
            errors.append("table line %d: `%s` is neither `Class::name` nor a member signature" % (line, text))
            continue
        cls, name = m.group("cls")[:-2], allocator_name(m.group("name")) or m.group("name")
        base = cls.rsplit("::", 1)[-1]
        if base not in cache:
            cache[base] = declared_members(base, (members or {}).get(base, []), macros, types)
        same = [d for d in cache[base] if d.name == name]
        full = bool(m.group("ret").strip() or m.group("rest").strip() or m.group("lead").strip())
        declaration = None
        if full:
            lead, ret, rest = m.group("lead"), m.group("ret").strip(), m.group("rest").strip()
            decl_text = "%s%s%s%s%s%s;" % ("static " if "static" in lead.split() or allocator_name(name) else "",
                                            "virtual " if "virtual" in lead.split() else "", ret,
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
        elif not same and name == "~" + base:
            # an Alchemy class declares no destructor: the compiler writes it (the vtable stamp, each member's
            # release, the delete), so the source has no body for it
            conv = Conversion(cname, cls, name, "func", False, False, False, None, (), None)
            conv.implicit = True
            out.append(conv)
            continue
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
        class_rows = (members or {}).get(base, []) + ([declaration] if declaration else [])
        virtual = want.kind == "func" and not want.static and declares_virtual(
            class_rows, name, tuple(want.params or ()), macros, types, base)
        conv = Conversion(cname, cls, name, want.kind, bool(want.static), bool(want.const), bool(want.inline),
                          want.ret, tuple(want.params or ()), declaration, virtual)
        conv.access = declared_access(class_rows, name, macros)
        conv.stated = full
        if conv.kind == "func":
            conv.raw_params = declared_raw_params(class_rows, name, conv.params, conv.const, macros, types, base)
        if conv.kind == "data" and conv.access:
            conv.getter = public_getter(class_rows, name, macros)
        out.append(conv)
    return out, errors


_BUILTIN_WORDS = frozenset(("const", "volatile", "unsigned", "signed", "int", "char", "short", "long", "float",
                            "double", "void", "bool", "wchar_t", "struct", "class", "union", "enum", "typename"))


def _strip_comments(text):
    return re.sub(r"/\*.*?\*/|//[^\n]*", " ", text, flags=re.S)


def _enumerators(body):
    return frozenset(m.group(1) for m in (re.match(r"\s*([A-Za-z_]\w*)", e) for e in body.split(",")) if m)


class NameScope:
    """What the types of a member's parameters name, for its compiler name and its callers' arguments: the types
    a class declares inside it in config/class-members.tsv (`enum OpenMode {…}` of igFile, a nested typedef), the
    classes' bases, the tree's function and function-pointer typedefs (`typedef void igIOCallbackFunction(int,
    int);`) and its enums at file scope (`typedef enum IG_GFX_DRAW {…} IG_GFX_DRAW;`)."""

    _NESTED = re.compile(r"(?:typedef\s+)?(enum|struct|class|union)\s+([A-Za-z_]\w*)\s*(?:\{(.*)\}|:[^;{]*\{.*\}|;)",
                         re.S)
    _NESTED_TYPEDEF = re.compile(r"typedef\s+([^;{}()]*?)\s*\b([A-Za-z_]\w*)\s*;$", re.S)
    _FUNCTION = re.compile(r"\btypedef\s+([^;{}()]*?)\(\s*\*\s*([A-Za-z_]\w*)\s*\)\s*\(([^;{}()]*)\)\s*;"
                           r"|\btypedef\s+([^;{}()]*?)\b([A-Za-z_]\w*)\s*\(([^;{}()]*)\)\s*;")
    _ENUM = re.compile(r"\benum\s+([A-Za-z_]\w*)\s*\{([^{}]*)\}|\btypedef\s+enum\s*\{([^{}]*)\}\s*([A-Za-z_]\w*)\s*;")

    def __init__(self, members=None, bases=None, texts=(), types=None):
        self.bases = bases or {}
        self.types = types
        self.nested = collections.defaultdict(dict)     # class -> {name: ("enum", enumerators) | ("record", None)
        for cls, rows in (members or {}).items():       #                 | ("typedef", target)}
            for _access, stmt in row_statements(rows):
                m = self._NESTED.match(stmt)
                if m:
                    body = m.group(3) if m.group(1) == "enum" else None
                    self.nested[cls][m.group(2)] = ("enum", _enumerators(body or "")) if m.group(1) == "enum" \
                        else ("record", None)
                    continue
                m = self._NESTED_TYPEDEF.match(stmt)
                if m and not re.search(r"\b(?:enum|struct|class|union)\s*\{", m.group(1)):
                    self.nested[cls][m.group(2)] = ("typedef", m.group(1).strip())
        functions = collections.defaultdict(set)        # name -> {(return, (parameter, ...), is a pointer)}
        enums = collections.defaultdict(set)            # name -> {enumerators}
        for text in texts:
            if "typedef" not in text and "enum" not in text:
                continue
            code = _strip_comments(text)
            for m in self._FUNCTION.finditer(code):
                pointer = m.group(2) is not None
                ret, name, args = (m.group(1), m.group(2), m.group(3)) if pointer else m.group(4, 5, 6)
                functions[name].add((re.sub(r"\s+", " ", ret).strip(), tuple(
                    a.strip() for a in _split_args(args) if a.strip() not in ("", "void")), pointer))
            for m in self._ENUM.finditer(code):
                enums[m.group(1) or m.group(4)].add(_enumerators(m.group(2) if m.group(1) else m.group(3)))
        self.functions = {n: next(iter(f)) for n, f in functions.items() if len(f) == 1}
        self.enums = {n: next(iter(e)) for n, e in enums.items() if len(e) == 1}

    def nested_owner(self, cls, name, depth=0):
        """(class, kind entry) of the class among `cls` and its bases that declares type `name`, or None."""
        found = self.nested.get(cls, {}).get(name)
        if found is not None:
            return cls, found
        if depth < 32:
            for b in self.bases.get(cls, ()):
                hit = self.nested_owner(b, name, depth + 1)
                if hit:
                    return hit
        return None

    def enum_of(self, cls, t):
        """(owner class or None, enumerators) when parameter type `t` (normalised) of a member of `cls` is an enum
        (a nested one, or one at file scope), else None."""
        if not re.fullmatch(r"[A-Za-z_]\w*", t or ""):
            return None
        hit = self.nested_owner(cls, t)
        if hit:
            return (hit[0], hit[1][1]) if hit[1][0] == "enum" else None
        return (None, self.enums[t]) if t in self.enums else None

    def param_type(self, p):
        """A parameter's type without its name or default, its spelling kept (`igFile::OpenMode`)."""
        p = p.strip()
        eq = declarations._top_equals(p)
        p = (p[:eq] if eq >= 0 else p).strip()
        m = re.match(r"(.*?[\w>*&\s])\s*\b([A-Za-z_]\w*)\s*((?:\[[^\]]*\]\s*)*)$", p, re.S)
        if m and m.group(2) not in _BUILTIN_WORDS and re.search(r"[A-Za-z_>]", m.group(1)) and \
                not m.group(1).rstrip().endswith("::") and m.group(1).strip() not in ("const", "volatile", "struct",
                                                                                         "class", "union", "enum"):
            p = m.group(1).strip() + ("*" if m.group(3) else "")
        return p

    def spelled(self, t, raw, cls, converted, gap, depth=0):
        """The C++ spelling MWCC mangles for parameter type `t` (normalised, `conv.params`) of a member of class
        `cls`, `raw` its declaration's spelling: a function (pointer) typedef is its type (`void (*)(int, int)`);
        a type nested in the class or a base is qualified by its owner (`igFile::OpenMode`), as is one the
        declaration qualifies; with `gap` (a member of a Gap class), a converted class is its Gap class."""
        t = re.sub(r"\s*:\s*:\s*", "::", t)
        qualifier = {}
        for m in re.finditer(r"((?:[A-Za-z_]\w*\s*::\s*)+)([A-Za-z_]\w*)", raw or ""):
            qualifier[m.group(2)] = re.sub(r"\s+", "", m.group(1))[:-2]
        fn = re.fullmatch(r"(?:const\s*)?([A-Za-z_]\w*)\s*((?:[*&]|\s|const)*)", t)
        if fn and depth < 8 and fn.group(1) in self.functions and fn.group(1) not in qualifier and \
                not self.nested_owner(cls, fn.group(1)):
            ret, args, pointer = self.functions[fn.group(1)]
            declarator = ("*" if pointer else "") + re.sub(r"\s|const", "", fn.group(2))
            inner = [self.spelled(self.types.param(a) if self.types else self.param_type(a), self.param_type(a),
                                  cls, converted, gap, depth + 1) for a in args]
            ret_t = self.types.strip_top_cv(self.types.norm(ret)) if self.types else ret
            return "%s (%s)(%s)" % (self.spelled(ret_t, ret, cls, converted, gap, depth + 1), declarator or "*",
                                    ", ".join(inner))

        def name(m):
            word = m.group(1)
            if word in _BUILTIN_WORDS:
                return word
            if word in qualifier:
                parts = qualifier[word].split("::")
                if gap and parts[0] in converted:
                    parts = ["Gap", converted[parts[0]]] + parts
                return "::".join(parts + [word])
            hit = self.nested_owner(cls, word) if depth < 8 else None
            if hit:
                owner, (kind, target) = hit
                if kind == "typedef":
                    return self.spelled(self.types.norm(target) if self.types else target, target, owner, converted,
                                        gap, depth + 1)
                return "%s::%s" % ("Gap::%s::%s" % (converted[owner], owner) if gap and owner in converted
                                   else owner, word)
            if gap and word in converted:
                return "Gap::%s::%s" % (converted[word], word)
            return word
        return re.sub(r"(?<![\w:])([A-Za-z_]\w*)\b", name, t)


def compiler_name(conv, converted=None, scope=None):
    """The MWCC b52 name of a conversion's member. Its parameter types are spelled as the class scope finds them
    (NameScope.spelled): a type nested in the class or a base qualified by its owner (`Q43Gap4Core6igFile8OpenMode`),
    a typedef'd function pointer as its type (`PFii_v`), and in a member of a Gap class a converted class as that
    Gap class (`converted` is {class: library namespace})."""
    if conv.kind == "data":
        return mangle(conv.qualified, None)
    scope = scope or NameScope()
    gap = bool(converted) and conv.cls.startswith("Gap::")
    raw = getattr(conv, "raw_params", None) or ()
    params = [scope.spelled(p, raw[i] if i < len(raw) else None, conv.base, converted or {}, gap)
              for i, p in enumerate(conv.params)]
    return mangle(conv.qualified, params, conv.const)


def converted_classes(root):
    """{class: library namespace} of config/converted-classes.tsv; the root igObject is implied by any row."""
    path = os.path.join(root, "config", "converted-classes.tsv")
    out = {}
    if os.path.exists(path):
        for line in _read(path).splitlines():
            parts = line.split("\t")
            if len(parts) in (2, 3) and not line.startswith("#") and parts[0].strip():
                out[parts[0].strip()] = parts[1].strip()
    if out:
        out.setdefault("igObject", "Core")
    return out


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
_CAST = re.compile(r"^\(\s*(?:struct\s+|class\s+)?((?:::\s*)?[A-Za-z_][\w:]*)\s*\*\s*\)\s*(.+)$", re.S)
_CAST_AT = re.compile(r"\(\s*(?:struct\s+|class\s+)?((?:::\s*)?[A-Za-z_][\w:]*)\s*\*\s*\)")
# a cast to a pointer type, multiword or template (`(unsigned char *)`, `(igStringObj **)`, `(const Vec *)`)
_POINTER_CAST = (r"\(\s*(?:const\s+)?(?:(?:unsigned|signed|short|long)\s+)*[A-Za-z_][\w:]*(?:\s*<[^()]*>)?"
                 r"(?:\s+const)?\s*\*+\s*\)\s*")
_POSTFIX = re.compile(r"^[A-Za-z_]\w*(?:\s*(?:->|\.)\s*[A-Za-z_]\w*|\s*\[[^\[\]]*\])*$")
_INTEGERS = ("int", "unsigned int", "short", "unsigned short", "long", "unsigned long", "char", "unsigned char")
_MEMBER_HEAD = re.compile(r"([A-Za-z_][\w:]*)\s*::\s*(?:~?[A-Za-z_]\w*|operator\s*(?:new|delete)\b(?:\s*\[\s*\])?)"
                          r"\s*\($")
_CODE_SPAN = re.compile(r"`\s*([A-Za-z_]\w*)\s*`")   # a backquoted identifier in a comment


_WIDE = ("long long", "unsigned long long")
_KIND_NAMES = {"pointer": "a pointer", "reference": "a reference", "integer": "an integer", "wide": "a 64-bit integer",
               "float": "a float", "double": "a double", "value": "a value"}


def param_kind(t, is_enum=lambda t: False):
    """How a parameter of normalised type `t` is passed and read: "pointer" (a pointer, a function pointer),
    "reference", "integer" (an integer of at most 32 bits, `bool`, an enum: one register), "wide" (`long long`),
    "float", "double", or "value" (a class or struct by value)."""
    t = (t or "").strip()
    if t.endswith("&"):
        return "reference"
    if t.endswith("*") or "(*)" in t:
        return "pointer"
    if t in _INTEGERS + ("unsigned", "signed char", "bool", "wchar_t") or is_enum(t):
        return "integer"
    if t in _WIDE:
        return "wide"
    return t if t in ("float", "double") else "value"


def retyped_params(c_params, params, is_enum=lambda t: False, stated=False):
    """The parameters a C form declares otherwise than its member (normalised, one list as long as the other) ->
    ({index: (C type, member type)}, None), or ({}, (index, reason)) for the first the member's type cannot take.
    One layout takes the other: a pointer for another pointer, an integer for another integer (an enum, `bool`,
    `unsigned`), an integer for a pointer (a memory pool passed as `int`); with `stated` (the table row gives the
    member's signature) also a 64-bit integer for a narrower one and back. Anything else (a pointer for a value or
    a reference, a float for an integer) means something else."""
    out = {}
    for i, (c, m) in enumerate(zip(c_params, params)):
        if c == m:
            continue
        kc, km = param_kind(c, is_enum), param_kind(m, is_enum)
        if (kc, km) in (("pointer", "pointer"), ("integer", "integer")) or \
                (kc, km) == ("integer", "pointer") and c in _INTEGERS + ("unsigned",) or \
                (stated and {kc, km} <= {"integer", "wide"}):
            out[i] = (c, m)
            continue
        hint = " (a table row giving the member's signature retypes it)" if {kc, km} <= {"integer", "wide"} else ""
        return {}, (i, "is %s (%s) where the member takes %s (%s)%s" % (_KIND_NAMES[kc], c, _KIND_NAMES[km], m, hint))
    return out, None


def _literal(e):
    """Whether `e` is an integer literal, which a cast may precede without parentheses."""
    return re.fullmatch(r"-?\s*(?:0[xX][0-9a-fA-F]+|\d+)[uUlL]*", e.strip()) is not None


def _fit(c, m, is_enum):
    """How well an argument the C form declares as type `c` fits a member parameter of type `m` (normalised):
    3 the same type; 2 a pointer to the value the member takes (by reference or by value); 1 another integer
    (or an enum), another pointer, a pointer to another type for a reference, an integer for a pointer; 0 not."""
    if c == m:
        return 3
    if c.endswith("*") and (m.endswith("&") and _normal_type(c[:-1]) == _normal_type(m[:-1]) or
                            _normal_type(c[:-1]) == _normal_type(m)):
        return 2
    if c.endswith("*") and (m.endswith(("*", "&"))):
        return 1
    if c in _INTEGERS + ("bool",) and (m in _INTEGERS + ("bool",) or m.endswith("*") or is_enum(m)):
        return 1
    return 0


def _name_fit(a, b):
    """2 for parameters of one name, 1 when one name begins the other (`create`, `createValue`), else 0."""
    if not a or not b:
        return 0
    a, b = a.lower(), b.lower()
    if a == b:
        return 2
    return 1 if min(len(a), len(b)) >= 3 and (a.startswith(b) or b.startswith(a)) else 0


def argument_order(c_params, c_names, params, names, is_enum=lambda t: False):
    """The member's parameter order over a C form's (`order[i]` the C argument the member's i-th parameter takes),
    or None when the C order is the member's. Each member parameter takes a C argument whose type fits it
    (`_fit`); the C order stands while it fits and no other order matches more parameter names; another order
    must fit and name-match best (types breaking a tie of names). Raises ValueError when several orders do."""
    n = len(params)
    if len(c_params) != n or n < 2:
        return None
    fits = [[_fit(c_params[j], params[i], is_enum) for j in range(n)] for i in range(n)]
    found = []

    def walk(i, used, order):
        if i == n:
            found.append(tuple(order))
            return
        for j in range(n):
            if j not in used and fits[i][j]:
                walk(i + 1, used | {j}, order + [j])
    walk(0, frozenset(), [])
    if not found:
        return None

    def score(order):
        return (sum(_name_fit(c_names[j], names[i]) for i, j in enumerate(order)),
                sum(fits[i][j] for i, j in enumerate(order)))
    best = max(score(o) for o in found)
    same = tuple(range(n))
    if same in found and score(same)[0] == best[0]:
        return None
    top = [o for o in found if score(o) == best]
    if len(top) > 1:
        raise ValueError(top)
    return top[0]


def _param_names(text, name):
    """The parameter names of the declaration of function `name` in `text` (None for an unnamed one)."""
    m = re.search(r"\b%s\s*\(" % re.escape(name), text or "")
    if not m:
        return None
    close = declarations._close(text, m.end() - 1)
    out = []
    for a in _split_args(text[m.end():close]):
        if a in ("", "void"):
            continue
        eq = declarations._top_equals(a)
        a = (a[:eq] if eq >= 0 else a).strip()
        w = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*$", a)
        words = re.findall(r"[A-Za-z_]\w*", a)
        out.append(w.group(1) if w and len(words) > 1 and w.group(1) not in _BUILTIN_WORDS else None)
    return out


def _postfix_expr(e):
    """Whether `e` is one postfix expression (a name or parenthesised group followed by calls, subscripts and
    member accesses), which a cast may precede without parentheses."""
    m = re.match(r"(?:::\s*)?[A-Za-z_][\w:]*", e)
    if m:
        i = m.end()
    elif e.startswith("("):
        i = declarations._close(e, 0) + 1
    else:
        return False
    while i and i < len(e):
        m = re.compile(r"\s*(?:->|\.)\s*[A-Za-z_]\w*|\s*([(\[])").match(e, i)
        if not m:
            return False
        if m.group(1):
            i = declarations._close(e, m.start(1), *(("[", "]") if m.group(1) == "[" else ("(", ")"))) + 1
        else:
            i = m.end()
    return i == len(e)


def _strip_parens(e):
    e = e.strip()
    while e.startswith("(") and declarations._close(e, 0) == len(e) - 1:
        e = e[1:-1].strip()
    return e


def _arg_spans(clean, open_, close, text=None):
    """[(start, end)] of each argument of the call whose parentheses are at `open_` and `close`, blanks trimmed.
    `text` is the source `clean` was made from: a string literal, blank in `clean`, is not a blank to trim."""
    def blank(k):
        return clean[k].isspace() and (text is None or text[k].isspace())

    out, depth, at = [], 0, open_ + 1
    for i in range(open_ + 1, close + 1):
        ch = clean[i]
        if ch in "([{":
            depth += 1
        elif ch in ")]}" and i < close:
            depth -= 1
        if (ch == "," and depth == 0) or i == close:
            s, e = at, i
            while s < e and blank(s):
                s += 1
            while e > s and blank(e - 1):
                e -= 1
            if s < e or out or ch == ",":
                out.append((s, e))
            at = i + 1
    return out


_DEFINE = re.compile(r"[ \t]*#[ \t]*define[ \t]+[A-Za-z_]\w*(\([^()]*\))?")


def macro_body(clean, pos):
    """The parameter names of the `#define` whose replacement text holds `pos` (its continuation lines included),
    or None when `pos` is not in one (outside a macro, or its name or parameter list)."""
    start = clean.rfind("\n", 0, pos) + 1
    while start > 0:                                     # back to the first line of a `\`-continued logical line
        prev = clean.rfind("\n", 0, start - 1) + 1
        if clean[prev:start - 1].rstrip(" \t\r").endswith("\\"):
            start = prev
        else:
            break
    m = _DEFINE.match(clean, start)
    if not m or pos < m.end():
        return None
    params = m.group(1) or ""
    return frozenset(p.strip() for p in params.strip("()").split(",") if p.strip())


def _split_args(text):
    if not text.strip():
        return []
    return [a.strip() for a in declarations._split_top(text)]


def _declared_type(ident, text):
    """The class a pointer `ident` is declared as in `text` (a function's head and body), as spelled
    (`igObject`, `::igObject`, `Gap::Core::igObject`), or None."""
    m = re.search(r"(?:\b(?:struct|class)\s+)?((?:::\s*)?(?:[A-Za-z_]\w*\s*::\s*)*[A-Za-z_]\w*)\s*\*\s*%s\b\s*[,;=)\[]"
                  % re.escape(ident), text)
    return re.sub(r"\s+", "", m.group(1)) if m else None


def _base_name(spelled):
    return spelled.rsplit("::", 1)[-1]


class FileRewrite:
    """The edits of one file."""

    def __init__(self, rel, text):
        self.rel, self.text = rel, text
        self.clean = units._clean(text)
        self.defs = units.definitions(text)
        self.edits = []                                # (start, end, replacement)
        self.deletes = []                              # (start, end) of whole lines
        self.moves = []                                # (argument spans, order): a call's arguments in member order
        self.gap_blocks = [(m.end(), units._match_brace(self.clean, m.end() - 1))
                           for m in re.finditer(r"\bnamespace\s+Gap\s*\{", self.clean)]

    def enclosing(self, pos):
        for name, start, end in self.defs:
            if start <= pos < end:
                return name, start, end
        return None

    def head_end(self, start):
        return self.clean.index("{", start)

    def result(self):
        """The text with the edits and deletions; two namespace blocks of one library a deletion left with only
        blanks between become one (cxxscope.merge_blocks), the file's other blocks keeping their bounds."""
        deletes = sorted(self.deletes)

        def dropped(s, e):
            return any(ds <= s and e <= de for ds, de in deletes)
        kept = [(s, e, r) for s, e, r in self.edits if not dropped(s, e)]
        moves = [(spans, order) for spans, order in self.moves if not dropped(spans[0][0], spans[-1][1])]
        marked = self._render(0, len(self.text), kept + [(s, e, "\0") for s, e in deletes], moves).split("\0")
        joins = {sum(len(piece) for piece in marked[:i]) for i in range(1, len(marked))}
        return tidy(cxxscope.merge_blocks("".join(marked), joins))

    def _render(self, start, end, edits, moves):
        """text[start:end] with the edits and moves inside it applied. A move writes a call's arguments in another
        order (`order[i]` the argument written i-th), each with the edits inside it; the separators stay."""
        tops = [m for m in moves if not any(o is not m and o[0][0][0] <= m[0][0][0] and m[0][-1][1] <= o[0][-1][1]
                                            for o in moves)]
        regions = [(spans[0][0], spans[-1][1]) for spans, _order in tops]
        items = [(s, e, r, None) for s, e, r in edits if not any(rs <= s and e <= re_ for rs, re_ in regions)]
        items += [(rs, re_, "", move) for (rs, re_), move in zip(regions, tops)]
        out, at = [], start
        for s, e, r, move in sorted(items, key=lambda x: x[:3]):
            if s < at:
                raise Refused("%s: two edits overlap at line %d" % (self.rel, self.text.count("\n", 0, s) + 1))
            out.append(self.text[at:s])
            at = e
            if move is None:
                out.append(r)
                continue
            spans, order = move
            inner = [x for x in edits if s <= x[0] and x[1] <= e]
            if any(not any(a <= x[0] and x[1] <= b for a, b in spans) for x in inner):
                raise Refused("%s:%d: an edit between the arguments of a call whose arguments change places"
                              % (self.rel, self.text.count("\n", 0, s) + 1))
            pieces = [self._render(a, b, [x for x in inner if a <= x[0] and x[1] <= b],
                                   [m for m in moves if m is not move and a <= m[0][0][0] and m[0][-1][1] <= b])
                      for a, b in spans]
            for k, j in enumerate(order):
                out.append(pieces[j])
                if k + 1 < len(spans):
                    out.append(self.text[spans[k][1]:spans[k + 1][0]])
        out.append(self.text[at:end])
        return "".join(out)


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


_NOT_A_TYPE = frozenset(("return", "else", "do", "case", "throw", "delete", "new", "sizeof", "goto"))


def _declares(head):
    """Whether the text of a statement before a function's name declares it (`extern "C" int `, `T *`, a template
    instance `igSmartPointer<struct igObject> `), rather than calling it (an empty head, `return `, `if (x && `,
    `a > `)."""
    if "=" in head or head.count("(") != head.count(")"):
        return False
    head = re.sub(r"[\s*&]*$", "", head)
    if head.endswith(">"):
        depth, at = 0, len(head) - 1
        while at >= 0:
            depth += {">": 1, "<": -1}.get(head[at], 0)
            if depth == 0:
                break
            at -= 1
        if at < 0:
            return False
        head = head[:at]                                 # the template's name declares like a type's
    m = re.search(r"([A-Za-z_]\w*)\s*$", head)
    return m is not None and m.group(1) not in _NOT_A_TYPE


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
        self.declaration_sites = []                     # (file, conversion, position, statement start, end)
        self.base_ctors = {}                            # C name -> class of the constructor it is
        self.boundary = {}                              # C name -> files whose declaration of it stays
        self.comment_names = []                         # (file, start, end, conversion) of a C name in a comment
        self.converted = {}                              # class -> library namespace (converted-classes.tsv)
        self.scope = NameScope()                         # nested types, typedefs and enums the members name

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

    # A converted class has two types of one name: the flat struct `igObject` (the C view, at file scope) and the
    # class `Gap::Core::igObject`. Neither converts to the other, so where the conversion moves a pointer from one
    # to the other it writes the cast the source then needs.
    def gap_scope(self, fr, pos, ctx=None):
        """Whether an unqualified class name at `pos` finds a Gap class: inside a `namespace Gap {` block or the
        body of a member of a Gap class (`T Gap::Core::igObject::f(...) {`)."""
        if any(s <= pos < e for s, e in fr.gap_blocks):
            return True
        inside = self.member_class_of(fr, ctx if ctx is not None else fr.enclosing(pos))
        return bool(inside and re.match(r"(?:::)?Gap::", inside))

    def gap_class(self, spelled, gap):
        """The converted class a declared type names (`Gap::Core::igObject`, or bare `igObject` where `gap`), or
        None for a flat struct (`::igObject`, a bare name at file scope) or a class not converted."""
        if not spelled:
            return None
        spelled = re.sub(r"\s+", "", spelled)
        base = _base_name(spelled)
        if base not in self.converted:
            return None
        if re.match(r"(?:::)?Gap::", spelled):
            return base
        return base if gap and not spelled.startswith("::") else None

    def spell(self, cls, gap):
        """How code at a place names converted class `cls` (bare): bare in Gap's scope, else qualified."""
        return cls if gap or cls not in self.converted else "Gap::%s::%s" % (self.converted[cls], cls)

    def unqualified(self, t, cls):
        """Parameter type `t` (normalised) as a member of class `cls` names it, so that a C form's spelling and
        the member's compare: `::` written whole (declarations.Types spells `igFile : : OpenMode`), a converted
        class's `Gap::<Library>::` scope dropped (`Gap::Core::igIGBFile *` is `igIGBFile *` in the class's scope)
        and a type nested in `cls` or a base named bare (`igFile::OpenMode` is `OpenMode` in igIGBFile, which
        derives from igFile)."""
        if not t:
            return t

        def short(m):
            parts = m.group(0).split("::")
            if len(parts) >= 3 and parts[0] == "Gap" and parts[2] in self.converted:
                parts = parts[2:]
            if len(parts) > 1:
                hit = self.scope.nested_owner(cls, parts[-1])
                if hit and hit[0] == parts[-2]:
                    parts = parts[-1:]
            return "::".join(parts)
        return re.sub(r"(?<![\w:])(?:[A-Za-z_]\w*::)+[A-Za-z_]\w*", short, re.sub(r"\s*:\s*:\s*", "::", t))

    def is_enum(self, t, cls):
        """Whether parameter type `t` (normalised) of a member of `cls` is an enum: one the class, a base or the
        qualifying class declares, or one at file scope."""
        parts = re.sub(r"\s*:\s*:\s*", "::", t or "").split("::")
        if len(parts) > 1:
            hit = self.scope.nested.get(parts[-2], {}).get(parts[-1])
            return bool(hit) and hit[0] == "enum"
        return self.scope.enum_of(cls, t) is not None

    def gap_receiver(self, conv, inside, gap):
        """Whether `this` in the member function enclosing a use is a `conv` object of the Gap class."""
        return inside is not None and self.classes.derives(_base_name(inside), conv.base) and \
            (gap or not conv.cls.startswith("Gap::"))

    def gap_argument(self, fr, span, cls, ctx, inside, gap):
        """Edits giving an argument passed for a parameter `cls *` (a converted class) that type: a flat pointer
        (cast to the flat struct, or declared as one) is cast to the Gap class; a cast of `this` drops where `this`
        is already one."""
        s, e = span
        while s < e and fr.clean[s] == "(" and declarations._close(fr.clean, s) == e - 1:
            s, e = s + 1, e - 1                          # (x): the expression inside
        expr = fr.text[s:e].strip()
        cast = _CAST_AT.match(fr.clean, s)
        if cast:
            if self.gap_class(cast.group(1), gap) is not None:
                return
            rest = _strip_parens(fr.text[cast.end():e])
            if rest == "this" and self.classes.derives(_base_name(inside or ""), cls) and gap:
                fr.edits.append((s, e, "this"))
            else:
                fr.edits.append((cast.start(), cast.end(), "(%s *)" % self.spell(cls, gap)))
            return
        if expr in ("0", "NULL", "nullptr"):
            return
        if expr == "this" and inside is not None and gap and self.classes.derives(_base_name(inside), cls):
            return
        if re.fullmatch(r"[A-Za-z_]\w*", expr) and ctx is not None:
            declared = self.gap_class(_declared_type(expr, fr.text[ctx[1]:ctx[2]]), gap)
            if declared is not None and self.classes.derives(declared, cls):
                return
        if _POSTFIX.match(expr):
            fr.edits.append((s, s, "(%s *)" % self.spell(cls, gap)))
        else:
            fr.edits.append((s, s, "(%s *)(" % self.spell(cls, gap)))
            fr.edits.append((e, e, ")"))

    def spellings(self, t, spelled=None):
        """A regex alternation of the spellings of normalised type `t`: itself, `spelled` (the declaration's) and
        every typedef name the tree resolves to it (`igStringObjRef` for `igSmartPointer<igStringObj>`)."""
        if getattr(self, "_typedef_names", None) is None:
            self._typedef_names = collections.defaultdict(set)
            types = self.index.types
            for name in list(types.raw):
                target = types.resolve(name)
                if target and target != name:
                    self._typedef_names[_normal_type(target)].add(name)
        names = {t, spelled or t} | self._typedef_names.get(_normal_type(t), set())

        def pattern(s):
            out, prev = [], None
            for tok in re.findall(r"[A-Za-z_]\w*|::|\S", s):
                word = re.match(r"\w", tok) is not None
                if out:
                    out.append(r"\s+" if word and prev else r"\s*")
                out.append(re.escape(tok))
                prev = word
            return "".join(out)
        return "|".join(pattern(n) for n in sorted(names, key=len, reverse=True) if n)

    def declared_value(self, fr, name, t, ctx, spelled=None, after=r"[,;=(\[)]"):
        """Whether `name` is declared in the function at `ctx` (its head or body) as a value or reference of
        normalised type `t`, alone or after other declarators of that type (`Vec a, b`)."""
        if ctx is None:
            return False
        return re.search(r"(?<![\w:])(?:const\s+)?(?:%s)(?:\s+const)?(?:\s+|\s*&\s*)"
                         r"(?:[A-Za-z_]\w*\s*(?:=\s*[^,;()]*)?,\s*)*%s\s*%s"
                         % (self.spellings(t, spelled), re.escape(name), after), fr.clean[ctx[1]:ctx[2]]) is not None

    def temporary_argument(self, fr, span, t, spelled=None):
        """An argument `&T(...)` (the address of a temporary the C form took a pointer to) passed for a parameter
        `T`, `const T &` or `T &` is the temporary `T(...)`: the compiler builds it in place, as it did for the
        pointer. -> whether it was one."""
        s, e = span
        k = s
        while k < e and (fr.clean[k] == "(" and declarations._close(fr.clean, k) == e - 1 or fr.clean[k].isspace()):
            k, e = (k + 1, e - 1) if fr.clean[k] == "(" else (k + 1, e)
        m = re.compile(r"&\s*(?:%s)\s*\(" % self.spellings(t, spelled)).match(fr.clean, k, e)
        if not m or declarations._close(fr.clean, m.end() - 1) != e - 1:
            return False
        j = k + 1
        while fr.clean[j].isspace():
            j += 1
        fr.edits.append((k, j, ""))
        return True

    def ref_argument(self, fr, span, t, const, ctx, spelled=None):
        """Edits giving an argument passed for a reference parameter `const t &` (`t` normalised, `spelled` as the
        declaration writes it), where the C form took a pointer to the value: a temporary's array member
        (`t(...).vec`) or address (`&t(...)`) is the temporary, a name declared as `t` stays, an argument already
        written as the value (`*p`, `*(t *)p`) stays, the address of a local or parameter declared as `t`
        (`&count` for an `int &`, `(igStringObj **)&value` or `&value.p` for an `igStringObjRef &` holding a
        smart pointer) is the name, and any other pointer (a float array, a cast to one, a stand-in struct's
        address) is dereferenced as a `t` (`*(const t *)v`), its own pointer cast dropped."""
        s, e = span
        spelled = spelled or t
        expr = fr.text[s:e].strip()
        if self.temporary_argument(fr, span, t, spelled):
            return
        head = re.compile(r"(?:%s)\s*\(" % self.spellings(t, spelled)).match(fr.clean, s, e)
        if head:
            close = declarations._close(fr.clean, head.end() - 1)
            if re.fullmatch(r"\s*\.\s*[A-Za-z_]\w*\s*", fr.text[close + 1:e]):
                fr.edits.append((close + 1, e, ""))
                return
        bare = _strip_parens(expr)
        if re.fullmatch(r"[A-Za-z_]\w*", bare) and self.declared_value(fr, bare, t, ctx, spelled):
            return
        deref = re.match(r"\*\s*(?:%s)?" % _POINTER_CAST, bare)
        if deref and _POSTFIX.match(_strip_parens(bare[deref.end():])):
            return
        amp = re.fullmatch(r"(?:%s)?\(?\s*&\s*([A-Za-z_]\w*)(\s*\.\s*p)?\s*\)?" % _POINTER_CAST, bare)
        if amp and (amp.group(0).count("(") - amp.group(0).count(")")) in (0, 1) and \
                self.declared_value(fr, amp.group(1), t, ctx, spelled, r"[,;=)(]"):
            fr.edits.append((s, e, amp.group(1)))       # the address of a value declared as `t`: the value
            return
        cast = re.match(_POINTER_CAST, expr)
        start = s + (cast.end() if cast else 0)
        inner = expr[start - s:]
        deref = "*(%s%s *)" % ("const " if const else "", spelled)
        if _POSTFIX.match(inner) or re.fullmatch(r"&\s*[A-Za-z_]\w*(?:\s*\[[^\[\]]*\])*", inner):
            fr.edits.append((s, start, deref))
        else:
            fr.edits.append((s, start, deref + "("))
            fr.edits.append((e, e, ")"))

    def enum_argument(self, fr, span, t, owner, enumerators, ctx, inside, gap):
        """An argument for a parameter of enum type `t` (nested in class `owner`, or at file scope for None) is
        cast to it unless it already has that type: an enumerator of it, a cast to it, a name declared as it or a
        call returning it; an integer (a literal, an `int` variable, an expression) is cast, as C++ takes no
        integer for an enum (`(IG_GFX_DRAW)primitive`, `(Gap::Core::igFile::OpenMode)5`)."""
        s, e = span
        expr = fr.text[s:e].strip()
        bare = _strip_parens(expr)
        own = re.compile(r"(?:(?:[A-Za-z_]\w*\s*::\s*)*%s)" % re.escape(t))
        cast = re.match(r"\(\s*(?:enum\s+)?%s\s*\)\s*" % own.pattern, bare)
        if cast and (_postfix_expr(bare[cast.end():]) or _literal(bare[cast.end():])):
            return
        name = re.fullmatch(r"(?:[A-Za-z_]\w*\s*::\s*)*([A-Za-z_]\w*)", bare)
        if name and (name.group(1) in enumerators or (
                re.fullmatch(r"[A-Za-z_]\w*", bare) and ctx is not None and re.search(
                    r"(?<![\w:])(?:enum\s+)?%s\s+(?:[A-Za-z_]\w*\s*(?:=\s*[^,;()]*)?,\s*)*%s\s*[,;=)]"
                    % (own.pattern, re.escape(bare)), fr.clean[ctx[1]:ctx[2]]))):
            return
        if re.search(r"\)\s*$", bare) and (self.expr_type(fr, bare, ctx) or "").split("::")[-1] == t:
            return
        if owner is None or (inside is not None and self.classes.derives(_base_name(inside), owner)):
            spelled = t
        else:
            spelled = "%s::%s" % (self.spell(owner, gap), t)
        if _postfix_expr(expr) or _literal(expr):
            fr.edits.append((s, s, "(%s)" % spelled))
        else:
            fr.edits.append((s, s, "(%s)(" % spelled))
            fr.edits.append((e, e, ")"))

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
            macro = macro_body(fr.clean, pos)
            if macro is not None:
                self.plan_macro_use(fr, conv, pos, end, macro, c_side and not cxx_side)
                continue
            if fr.clean[line_start:pos].lstrip().startswith("#"):
                continue                                # a macro name or test
            ctx = fr.enclosing(pos)
            in_head = ctx is not None and pos < fr.head_end(ctx[1])
            if ctx is not None and not in_head:
                self.plan_use(fr, conv, pos, end, ctx, c_side and not cxx_side)
            else:
                self.plan_file_scope(fr, conv, pos, end, c_side, cxx_side)
        for start, end in self.comment_spans(fr):
            for span in _CODE_SPAN.finditer(fr.text, start, end):
                conv = self.by_cname.get(span.group(1))
                if conv is not None:
                    self.comment_names.append((fr, span.start(1), span.end(1), conv))

    def rename_comments(self):
        """A comment's prose keeps the C name: it is still the function's or datum's retail name (symbols.txt, which
        the compiler-name map binds the member to), so the comment still names the symbol. A code span holding
        just the C name (`` `igObjectList_SetCount` ``) quotes the identifier code used, and names the member as
        code does now (`igObjectList::setCount`), unless code still uses the C name."""
        for fr, start, end, conv in self.comment_names:
            if not self.c_callers.get(conv.cname):
                fr.edits.append((start, end, "%s::%s" % (conv.base, conv.name)))

    @staticmethod
    def comment_spans(fr):
        out, i = [], 0
        for m in re.finditer(r"/\*.*?\*/|//[^\n]*", fr.text, re.S):
            if fr.clean[m.start()] == " ":              # blanked: a comment, not a `/*` inside a string
                out.append((m.start(), m.end()))
        return out

    def plan_macro_use(self, fr, conv, pos, end, params, c_only):
        """A use in a `#define`'s replacement text, which the C++ code expanding it compiles: a call becomes the
        member call on its receiver cast to the class (a macro parameter's type is the expansion's, unknown here,
        and is parenthesised), the other arguments as at any call."""
        if c_only or conv.virtual or conv.special or conv.access:
            self.c_callers[conv.cname].add(fr.rel)
            return
        gap = any(s <= pos < e for s, e in fr.gap_blocks)
        after = re.match(r"\s*\(", fr.clean[end:])
        if conv.kind == "data" or conv.static:
            fr.edits.append((pos, end, conv.qualified))
            self.retype_call(fr, conv, end, None, None, gap)
            return
        if not after:
            self.errors.append("%s:%d: instance member %s is used as a value (%s); convert that use by hand"
                               % (fr.rel, fr.text.count("\n", 0, pos) + 1, conv.qualified, conv.cname))
            return
        open_ = end + after.end() - 1
        close = declarations._close(fr.clean, open_)
        spans = _arg_spans(fr.clean, open_, close, fr.text)
        if len(spans) != len(conv.params) + 1:
            self.errors.append("%s:%d: %s(...) passes %d arguments; instance member %s takes a receiver and %d"
                               % (fr.rel, fr.text.count("\n", 0, pos) + 1, conv.cname, len(spans), conv.qualified,
                                  len(conv.params)))
            return
        expr = _strip_parens(fr.text[spans[0][0]:spans[0][1]].strip())
        cls = self.spell(conv.base, gap) if conv.cls.startswith("Gap::") else conv.cls
        cast = _CAST.match(expr)
        if cast:
            bare = _strip_parens(cast.group(2))
            inner = bare if _POSTFIX.match(bare) and bare not in params else "(%s)" % bare
        else:
            inner = expr if _POSTFIX.match(expr) and expr not in params else "(%s)" % expr
        stop = spans[1][0] if len(spans) > 1 else close
        fr.edits.append((pos, stop, "((%s *)%s)->%s(" % (cls, inner, conv.name)))
        self.typed_arguments(fr, conv, spans[1:], None, None, gap)

    def may_access(self, conv, inside):
        """Whether a member function of class `inside` may name `conv`'s member: any for a public one, the class's
        own for a private one, the class's and its subclasses' for a protected one."""
        if not conv.access:
            return True
        if inside is None:
            return False
        own = inside.rsplit("::", 1)[-1]
        return own == conv.base if conv.access == "private" else self.classes.derives(own, conv.base)

    def plan_use(self, fr, conv, pos, end, ctx, c_only):
        if c_only:
            self.c_callers[conv.cname].add(fr.rel)
            return
        inside = self.member_class_of(fr, ctx)
        if conv.access and not self.may_access(conv, inside):
            if conv.getter and _is_read(fr.clean, pos, end):
                # the kit reads a protected `_Meta` outside its class through the public `getClassMeta()`
                fr.edits.append((pos, end, "%s::%s()" % (conv.cls, conv.getter)))
                return
            # outside the class (a private member) or its subclasses (a protected one) the member is out of
            # reach: the caller still names the C name until it is written the kit's way (igObject::release())
            self.c_callers[conv.cname].add(fr.rel)
            return
        after = re.match(r"\s*\(", fr.clean[end:])
        if conv.special:
            self.plan_special_use(fr, conv, pos, end, after, ctx)
            return
        if conv.virtual:
            self.plan_virtual_use(fr, conv, pos, end, after, inside)
            return
        if conv.kind == "data" or conv.static:
            fr.edits.append((pos, end, self.retyped_cast(fr, conv, pos, after) + self.qual(conv, inside)))
            if conv.inline and conv.kind == "func" and not after:
                self.inline_users[conv.qualified].add(fr.rel)
            self.retype_call(fr, conv, end, ctx, inside, self.gap_scope(fr, pos, ctx))
            return
        if not after:
            self.errors.append("%s:%d: instance member %s is used as a value (%s); convert that use by hand"
                               % (fr.rel, fr.text.count("\n", 0, pos) + 1, conv.qualified, conv.cname))
            return
        open_ = end + after.end() - 1
        close = declarations._close(fr.clean, open_)
        spans = _arg_spans(fr.clean, open_, close, fr.text)
        if len(spans) != len(conv.params) + 1:
            self.errors.append("%s:%d: %s(...) passes %d arguments; instance member %s takes a receiver and %d"
                               % (fr.rel, fr.text.count("\n", 0, pos) + 1, conv.cname, len(spans), conv.qualified,
                                  len(conv.params)))
            return
        gap = self.gap_scope(fr, pos, ctx)
        receiver = self.receiver(fr, conv, fr.text[spans[0][0]:spans[0][1]], ctx, inside, gap)
        # the receiver and the name are replaced; the other arguments keep their text (and their own edits), cast
        # to a converted class's Gap type where a parameter is a pointer to one
        stop = spans[1][0] if len(spans) > 1 else close
        fr.edits.append((pos, stop, (receiver or "") + conv.name + "("))
        self.typed_arguments(fr, conv, spans[1:], ctx, inside, gap)

    def retype_call(self, fr, conv, end, ctx, inside=None, gap=False):
        """A static member's call at `end` (after its name): its arguments as at any call (typed_arguments)."""
        after = re.match(r"\s*\(", fr.clean[end:])
        if conv.kind != "func" or not after:
            return
        open_ = end + after.end() - 1
        self.typed_arguments(fr, conv, _arg_spans(fr.clean, open_, declarations._close(fr.clean, open_), fr.text),
                             ctx, inside, gap)

    def typed_arguments(self, fr, conv, spans, ctx, inside, gap):
        """A call's arguments in the member's order (conv.order: the C form ordered them otherwise), each cast where
        its parameter needs: to a converted class's Gap type for a pointer to one, a pointer to the value for a
        reference (`ref_argument`), the temporary for a class taken by value (`temporary_argument`), an integer
        for an enum (`enum_argument`), an integer the member takes as a pointer (`retyped_arguments`)."""
        if conv.order and len(spans) == len(conv.order):
            fr.moves.append((list(spans), conv.order))
            spans = [spans[j] for j in conv.order]
        self.retyped_arguments(fr, conv, spans, ctx)
        raw = conv.raw_params or ()
        for i, (span, param) in enumerate(zip(spans, conv.params)):
            spelled = None
            if i < len(raw):
                spelled = re.sub(r"\s+", " ", re.sub(r"\b(?:const|volatile|struct|class|union|enum)\b|&", " ",
                                                     self.scope.param_type(raw[i]))).strip()
                spelled = spelled if spelled and "*" not in spelled else None
            ref = re.fullmatch(r"((?:(?:unsigned|signed|short|long) )*[A-Za-z_][\w:]*(?:<[^&*]*>)?)( const)?&",
                               param or "")
            if ref:
                self.ref_argument(fr, span, ref.group(1), bool(ref.group(2)), ctx, spelled)
                continue
            if re.fullmatch(r"[A-Za-z_][\w:]*(?:<[^&*]*>)?", param or "") and param not in _BUILTIN_WORDS:
                enum = self.scope.enum_of(conv.base, param)
                if enum:
                    self.enum_argument(fr, span, param, enum[0], enum[1], ctx, inside, gap)
                else:
                    self.temporary_argument(fr, span, param, spelled)
                continue
            if not conv.cls.startswith("Gap::"):
                continue
            pointee = re.fullmatch(r"([A-Za-z_]\w*)(?: const)?\*", param or "")
            if pointee and pointee.group(1) in self.converted:
                self.gap_argument(fr, span, pointee.group(1), ctx, inside, gap)

    def plan_special_use(self, fr, conv, pos, end, after, ctx):
        """A call of a constructor's or destructor's C name. The calls a converted subclass's constructor made of
        its base's went with its definition (an implicit base construction); a destructor called with a positive
        delete flag on a pointer declared as the Gap class (or a subclass) is `delete p`. Every other call
        constructs or destroys an object of a class still written as a flat struct (a GetVTable probe, an
        unconverted subclass): the C name stays, and with it the prototype in its home header."""
        if after and conv.special == "dtor":
            open_ = end + after.end() - 1
            close = declarations._close(fr.clean, open_)
            spans = _arg_spans(fr.clean, open_, close, fr.text)
            if len(spans) == 2 and re.fullmatch(r"\(?\s*[1-9]\d*\s*\)?", fr.clean[spans[1][0]:spans[1][1]]):
                e = _strip_parens(fr.text[spans[0][0]:spans[0][1]])
                declared = re.search(r"\bGap\s*::\s*\w+\s*::\s*(\w+)\s*\*\s*%s\b" % re.escape(e),
                                     fr.text[ctx[1]:ctx[2]]) if re.fullmatch(r"\w+", e) else None
                if declared and self.classes.derives(declared.group(1), conv.base):
                    stmt = re.match(r"\s*;", fr.clean[close + 1:])
                    if stmt:
                        fr.edits.append((pos, close + 1, "delete %s" % e))
                        return
        self.c_callers[conv.cname].add(fr.rel)

    def plan_virtual_use(self, fr, conv, pos, end, after, inside):
        """A use of a virtual function's C name runs that class's implementation, not the object's override:
        inside a member of the class or a subclass, a call on `this` becomes the qualified, non-virtual
        `Class::name(a)`; anywhere else the C name stays (its declaration with it), since `obj->name(a)` would
        dispatch through the vtable."""
        if after and inside is not None and self.classes.derives(inside.rsplit("::", 1)[-1], conv.base):
            open_ = end + after.end() - 1
            close = declarations._close(fr.clean, open_)
            spans = _arg_spans(fr.clean, open_, close, fr.text)
            if len(spans) == len(conv.params) + 1:
                e = _strip_parens(fr.text[spans[0][0]:spans[0][1]])
                cast = _CAST.match(e)
                if (_strip_parens(cast.group(2)) if cast else e) == "this":
                    stop = spans[1][0] if len(spans) > 1 else close
                    fr.edits.append((pos, stop, "%s::%s(" % (conv.base, conv.name)))
                    ctx = fr.enclosing(pos)
                    self.typed_arguments(fr, conv, spans[1:], ctx, inside, self.gap_scope(fr, pos, ctx))
                    return
        self.c_callers[conv.cname].add(fr.rel)

    def drop_forwarders(self, frs):
        """A `static inline` C++ overload of a converted C name that forwards to it (`igObject_IsKindOf(View *o, …)
        { return igObject_IsKindOf((igObject *)o, …); }`) existed for C++ callers passing another type; those calls
        are member calls now, so it goes unless C++ code still names the C name (a boundary use)."""
        for rel, fr in frs.items():
            for name, start, end in fr.defs:
                if name not in self.by_cname:
                    continue
                head = fr.clean[start:fr.head_end(start)]
                lead = head[:declarations._first_paren(head)]
                if not (re.search(r"\bstatic\b", lead) and re.search(r"\binline\b", lead)):
                    continue
                if any(cxx_reads(self.index, f) for f in self.c_callers.get(name, ())):
                    continue
                span = _line_span(fr.text, start, end)
                if span is not None:
                    fr.deletes.append(span)

    def settle_declarations(self):
        """Each converted C name's declarations: none stays when no use keeps the C name; else the home header's
        stays (boundary_sites), with any other a user's unit needs because it does not read the home header."""
        by_name = collections.defaultdict(list)
        for site in self.declaration_sites:
            by_name[site[1].cname].append(site)
        for cname, sites in sorted(by_name.items()):
            conv = sites[0][1]
            listed = [(fr.rel, cxx_only(fr, pos)) for fr, _conv, pos, _s, _e in sites]
            keep, notes = boundary_sites(self.index, conv.base, listed, self.c_callers.get(cname, set()))
            self.notes.extend("%s: %s" % (cname, n) for n in notes)
            self.boundary[cname] = sorted({listed[i][0] for i in keep})
            for i, (fr, _conv, pos, stmt_start, stmt_end) in enumerate(sites):
                if i in keep:
                    continue
                span = _line_span(fr.clean, stmt_start, stmt_end + 1)
                if span is None:
                    self.errors.append("%s:%d: the declaration of %s shares its line with other code: remove it by "
                                       "hand" % (fr.rel, fr.text.count("\n", 0, pos) + 1, cname))
                else:
                    fr.deletes.append(span)

    def receiver(self, fr, conv, expr, ctx, inside, gap):
        """The object expression with its `->`/`.` for an instance call, or None for a bare call (the enclosing
        member's own `this`, its class or a subclass of it being the member's). A converted class's receiver is
        cast to its Gap class unless it is declared as that class or a Gap subclass: a flat struct pointer (the C
        view of the same name) is another type."""
        gap_conv = conv.cls.startswith("Gap::")
        cls = self.spell(conv.base, gap) if gap_conv else conv.cls
        e = _strip_parens(expr)
        cast = _CAST.match(e)
        bare = _strip_parens(cast.group(2)) if cast else e
        if bare == "this" and self.gap_receiver(conv, inside, gap):
            return None
        if e == "this" and not gap_conv:
            return "this->"
        if cast:
            inner = bare if _POSTFIX.match(bare) else "(%s)" % bare
            return "((%s *)%s)->" % (cls, inner)
        if e.startswith("&") and _POSTFIX.match(e[1:].strip()):
            return ("((%s *)&%s)->" % (cls, e[1:].strip())) if gap_conv else e[1:].strip() + "."
        if re.fullmatch(r"[A-Za-z_]\w*", e):
            declared = _declared_type(e, fr.text[ctx[1]:ctx[2]])
            base = self.gap_class(declared, gap) if gap_conv else declared and _base_name(declared)
            if base and self.classes.derives(base, conv.base):
                return e + "->"
        return "((%s *)%s)->" % (cls, e if _POSTFIX.match(e) else "(%s)" % e)

    def retyped_arguments(self, fr, conv, spans, ctx):
        """The arguments of a call whose parameter the C form declared otherwise than the member (conv.c_params).
        An integer the member takes as a pointer (a memory pool passed as `int`): `(int)E` becomes `E` where E
        already has the member's type, else `(T *)E`; an argument without the integer cast is cast (`0` stays).
        A pointer to another type: `pointer_argument`. An integer of another type converts implicitly (an enum's
        is typed_arguments' cast)."""
        for i, (s, e) in enumerate(spans):
            if i not in conv.c_params:
                continue
            c_type, m_type = conv.c_params[i]
            if param_kind(c_type) == "pointer":
                self.pointer_argument(fr, conv, i, (s, e), ctx)
                continue
            if c_type not in _INTEGERS + ("unsigned",) or not m_type.endswith("*"):
                continue
            arg = fr.text[s:e]
            m = re.fullmatch(r"\(\s*(%s)\s*\)\s*(.+)" % "|".join(re.escape(t) for t in _INTEGERS), arg, re.S)
            expr = m.group(2) if m else arg
            if not m and _strip_parens(expr) in ("0", "NULL"):
                continue
            bare = _strip_parens(expr)
            if not _postfix_expr(bare):
                bare = "(%s)" % bare
            if self.expr_type(fr, expr, ctx) == m_type:
                if m:
                    fr.edits.append((s, e, bare))
                continue
            fr.edits.append((s, e, "(%s *)%s" % (m_type[:-1], bare)))

    def pointer_argument(self, fr, conv, i, span, ctx):
        """An argument for parameter `i`, which the C form declared as a pointer to another type than the member's
        (`unsigned int *dst` for `unsigned char *dest`): cast to the member's type (`(unsigned char *)dst`, an
        argument's own pointer cast replaced), unless the C type converts to it implicitly (the member takes
        `void *` or adds `const`), the argument is a null pointer or is declared as or cast to the member's type.
        A converted class's pointer is gap_argument's."""
        c_type, m_type = conv.c_params[i]
        pointee = re.sub(r"\s*\bconst\b\s*", "", m_type[:-1]).strip()
        if pointee == "void" or (conv.cls.startswith("Gap::") and pointee in self.converted) or \
                _normal_type(c_type) == _normal_type(m_type) and "const" not in c_type:
            return
        s, e = span
        arg = fr.text[s:e]
        bare = _strip_parens(arg)
        if bare in ("0", "NULL", "nullptr"):
            return
        raw = conv.raw_params or ()
        spelled = self.scope.param_type(raw[i]) if i < len(raw) else m_type.replace("*", " *")
        types = self.index.types

        def same(declared):
            got = types.param(declared)
            return got == m_type or ("const" in m_type and _normal_type(got) == _normal_type(m_type))
        cast = re.match(_POINTER_CAST, arg)
        if cast:
            if not same(arg[1:arg.index(")")]):
                fr.edits.append((s, s + cast.end(), "(%s)" % spelled))
            return
        if re.fullmatch(r"[A-Za-z_]\w*", bare) and ctx is not None:
            declared = re.search(r"([A-Za-z_][\w\s:<>]*?[\s*]*\*)\s*%s\s*[,;=)\[]" % re.escape(bare),
                                 fr.text[ctx[1]:ctx[2]])
            if declared and same(declared.group(1)):
                return
        fr.edits.append((s, e, "(%s)%s" % (spelled, bare if _postfix_expr(bare) else "(%s)" % bare)))

    def expr_type(self, fr, expr, ctx):
        """The normalised type of a simple expression where it can be read off the tree: a cast, a local or
        parameter, a free function's return or a class member's (class-members.tsv); else None."""
        e = _strip_parens(expr)
        cast = _CAST.match(e)
        if cast:
            return _normal_type(cast.group(1).split("::")[-1]) + "*"
        if re.fullmatch(r"[A-Za-z_]\w*", e) and ctx is not None:
            t = _declared_type(e, fr.text[ctx[1]:ctx[2]])
            return t.split("::")[-1] + "*" if t else None
        call = re.fullmatch(r"(?:.*(->|\.|::)\s*)?([A-Za-z_]\w*)\s*\((.*)\)", e, re.S)
        if not call or declarations._close(e, e.index("(", call.start(3) - 1)) != len(e) - 1:
            return None
        name = call.group(2)
        if call.group(1):
            rets = {r for r in self.member_returns().get(name, ())}
        else:
            rets = {d.ret for ds in self.index.decls.values() for d in ds
                    if d.name == name and d.kind == "func" and d.ret}
        rets = {_normal_type(r) for r in rets}
        return rets.pop() if len(rets) == 1 else None

    def member_returns(self):
        """{member name: {return types}} of the class-members.tsv rows."""
        if getattr(self, "_member_returns", None) is None:
            self._member_returns = collections.defaultdict(set)
            for rows in (getattr(self, "members", None) or {}).values():
                for r in rows:
                    r = re.sub(r"^\s*(?:public|protected|private)\s*:\s*", "", r)
                    m = re.match(r"(?:(?:virtual|static|inline)\s+)*([A-Za-z_][\w:<>\s]*?[\s*&]+)([A-Za-z_]\w*)\s*\(",
                                 r)
                    if m:
                        self._member_returns[m.group(2)].add(m.group(1).strip())
        return self._member_returns

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
        if conv.kind == "func" and any(name == conv.cname and start <= pos < fr.head_end(start)
                                       for name, start, _end in fr.defs):
            return                                       # a definition's head (plan_definition)
        stmt_start = _statement_start(fr.clean, pos)
        head = fr.clean[stmt_start:pos]
        nxt = re.compile(r"\s*(\S?)").match(fr.clean, end).group(1)
        is_extern = re.search(r"\bextern\b", head) is not None
        if conv.kind == "data" and not is_extern and "=" not in head and "(" not in head and "&" not in head \
                and re.search(r"[A-Za-z_]", head):
            return                                       # the datum's definition (plan_definition)
        declaration = (nxt == "(" and conv.kind == "func" and _declares(head)) or \
                      (conv.kind == "data" and is_extern and "=" not in head)
        if declaration:
            # whether it stays is known once every file is read: the home header keeps it while an unconverted
            # caller still uses the C name (settle_declarations)
            self.declaration_sites.append((fr, conv, pos, stmt_start, fr.clean.find(";", end)))
            return
        if (c_side and not cxx_side) or conv.virtual or conv.special or conv.access:
            self.c_callers[conv.cname].add(fr.rel)
            return
        if conv.kind == "func" and not conv.static:
            if nxt == "(":                               # a call in code the definition scan does not see (a
                self.plan_macro_use(fr, conv, pos, end, frozenset(), False)   # member defined in a class body)
                return
            self.errors.append("%s:%d: instance member %s is used as a value (%s); convert that use by hand"
                               % (fr.rel, fr.text.count("\n", 0, pos) + 1, conv.qualified, conv.cname))
            return
        fr.edits.append((pos, end, self.retyped_cast(fr, conv, pos, nxt == "(") + conv.qualified))
        self.retype_call(fr, conv, end, None, None, any(s <= pos < e for s, e in fr.gap_blocks))
        if conv.inline:
            self.inline_users[conv.qualified].add(fr.rel)

    def retyped_cast(self, fr, conv, pos, called):
        """The cast keeping a use of static member `conv` the type its C form had, where the definition's return
        type changed (`c_ret`, rewrite_definition) or a parameter did (`c_params`): a call assigned where the C
        form's integer went (`*(int *)p = Class::getMetaField()`) is cast back to it, as is one assigned at file
        scope where the C form returned the converted class's flat struct (`g = (igMetaEnum *)Gap::Core::
        igMetaEnum::createMetaEnum(…)`, a holder still declared flat), and the member named as a
        value in an array initialiser of a function-pointer typedef (a field table's `FieldFactory`) is cast to
        that type. A use already cast keeps its cast."""
        c_ret = getattr(conv, "c_ret", None)
        if (c_ret is None and not conv.c_params) or conv.kind != "func" or not conv.static:
            return ""
        before = fr.clean[:pos].rstrip()
        if before.endswith(")"):
            return ""
        if called:
            if c_ret in _INTEGERS and (conv.ret or "").endswith("*") and before.endswith("=") and \
                    not before.endswith(("==", "!=", "<=", ">=")):
                return "(%s)" % c_ret
            if c_ret and c_ret not in _INTEGERS and _base_name(c_ret.rstrip("* ")) in self.converted and \
                    before.endswith("=") and not before.endswith(("==", "!=", "<=", ">=")) and \
                    not self.gap_scope(fr, pos):
                return "(%s)" % c_ret.replace("*", " *").strip()
            return ""
        table = re.search(r"\b([A-Za-z_]\w*)\s+[A-Za-z_]\w*\s*\[[^\]]*\]\s*=\s*\{[^;{}]*$", before[-4000:])
        if table and table.group(1) not in _INTEGERS and table.group(1) not in ("void", "char", "float", "double"):
            return "(%s)" % table.group(1)
        return ""

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
                if re.search(r"\binline\b", head[:declarations._first_paren(head)]) and \
                        re.search(r"\b%s\s*\(" % re.escape(conv.cname), fr.clean[brace:end]):
                    continue                             # a C++ overload forwarding to the C name: one of its users
                raise Refused("%s: %s is a file-scope static: it stays a free function" % (fr.rel, conv.cname))
            if conv.inline or conv.implicit:
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
                if conv.implicit:
                    ls = cxxscope._lead_comments(fr.text, fr.clean, ls)   # its comment describes that body
                if fr.text[le:le + 1] == "\n" and (ls == 0 or fr.text[ls - 2:ls] == "\n\n"):
                    le += 1                              # and the blank line after it
                fr.deletes.append((ls, le))
                if conv.implicit:
                    self.notes.append("%s was %s's implicit destructor: its body goes, the compiler writes it where "
                                      "an object of the class is destroyed (`delete`, a local's scope end)"
                                      % (conv.cname, conv.cls))
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
        if conv.special == "dtor":
            # a destructor the class declares out of line: its user body is written by hand over the C form, which
            # is emptied to its head first (classconv's stub); the C form's receiver and delete flag go
            if fr.clean[brace:end].strip().strip("{}").strip() or not 1 <= len(params) <= 2:
                raise Refused("%s: %s declares an out-of-line destructor: its user body is written by hand (a "
                              "classconv hand body, which empties %s to its head first)"
                              % (fr.rel, conv.cls, conv.cname))
            receiver, params = params[0], []
        elif conv.kind == "func" and not conv.static and len(params) == len(conv.params) + 1:
            receiver = params[0]
            params = params[1:]
        elif len(params) != len(conv.params):
            raise Refused("%s: %s takes %d parameters, %s declares %d%s" % (
                fr.rel, conv.cname, len(params), conv.qualified, len(conv.params),
                "" if conv.static else " (and an instance member's receiver)"))
        types = self.index.types
        # spelled as the class's scope names them: `Gap::Lib::Class *` at file scope is the member's bare `Class *`,
        # `igFile::OpenMode` the bare `OpenMode` of a class deriving from igFile
        got = tuple(self.unqualified(types.param(t + " " + (n or "")), conv.base) for t, n in params)
        want = tuple(self.unqualified(q, conv.base) for q in conv.params)
        if got != want:
            retyped, refusal = retyped_params(got, want, lambda t: self.is_enum(t, conv.base), conv.stated)
            moved = [i for i, (c, m) in retyped.items() if not (c in _INTEGERS and m.endswith("*"))]
            if refusal is None and conv.order is not None and moved:
                refusal = (moved[0], "is declared in the C order, which the member's callers do not keep")
            if refusal is not None:
                i, why = refusal
                raise Refused("%s: %s's parameters (%s) are not %s's (%s): parameter %d %s; write its head by hand" % (
                    fr.rel, conv.cname, ", ".join(got), conv.qualified, ", ".join(want), i + 1, why))
            conv.c_params.update(retyped)
            params = self.retyped_head(fr, conv, ctx, params, retyped)
        ret = head[:head.rfind(conv.cname, 0, p)].rstrip()
        initializer = ""
        if conv.special == "ctor":
            if receiver is None:
                raise Refused("%s: %s has no receiver: a constructor's C form takes the object first"
                              % (fr.rel, conv.cname))
            ret = ""                                     # a constructor returns nothing: `return self;` goes
            initializer = self.constructor_body(fr, conv, ctx, receiver[1])
        elif conv.special == "dtor":
            ret = ""
        else:
            ret_norm = types.strip_top_cv(types.norm(declarations._STORAGE.sub(" ", ret)))
            if ret_norm != conv.ret and conv.ret is not None:
                self.notes.append("%s: %s returns %s, %s is declared to return %s: the head takes the declaration's"
                                  % (fr.rel, conv.cname, ret_norm or "nothing", conv.qualified, conv.ret))
                ret = conv.ret.replace("*", " *").replace("  ", " ").strip()
                conv.c_ret = ret_norm                    # its uses keep the C type (retyped_cast)
            elif conv.static and conv.cls.startswith("Gap::") and (ret_norm or "").endswith("*") and \
                    _base_name(ret_norm.rstrip("* ")) in self.converted and not self.gap_scope(fr, start, ctx):
                conv.c_ret = ret_norm                    # it returned the flat struct, which file-scope holders keep
        plist = ", ".join(("%s %s" % (t, n) if not t.endswith(("*", "&")) else "%s%s" % (t, n)) if n else t
                          for t, n in params)
        if conv.cls.startswith("Gap::"):                 # in the class's scope a converted class is its bare name
            plist = re.sub(r"\bGap\s*::\s*\w+\s*::\s*(\w+)\b",
                           lambda m: m.group(1) if m.group(1) in self.converted else m.group(0), plist)
        new_head = "%s%s%s(%s)%s%s%s" % (ret, "" if ret.endswith(("*", "&")) or not ret else " ", conv.qualified,
                                         plist, " const" if conv.const else "", initializer, head[close + 1:])
        fr.edits.append((start, brace, new_head))
        if conv.cls.startswith("Gap::") and not self.gap_scope(fr, start, ctx):
            self.keep_flat_names(fr, brace, end)
        if receiver is not None:
            self.rewrite_receiver(fr, conv, ctx, receiver, head[p + 1:close])

    def retyped_head(self, fr, conv, ctx, params, retyped):
        """The definition's parameters [(declared type, name)] once the head takes the member's types where the C
        form's differ (retyped_params), the body keeping what it read. An integer the member takes as a pointer or
        as another integer (an enum, `bool`, `unsigned`) is the member's type under the C name. A pointer to
        another type is the member's parameter (`unsigned char *dest`), and the body's first line declares the C
        name as the C type from it (`unsigned int *dst = (unsigned int *)dest;`); where the member names no
        parameter, or names it as the C form, a local or a field of the class does, the C name takes the
        member's type and the body reads it as that."""
        _name, start, end = ctx
        brace = fr.head_end(start)
        raw = conv.raw_params or ()
        names = (_param_names("f(%s)" % ", ".join(raw), "f") or []) if raw else []
        taken = local_names("", fr.clean[brace:end]) | {n for _t, n in params if n} | \
            set(self.classes.all_fields(conv.base)) | self.declared_names.get(conv.base, set())
        indent = re.search(r"\n([ \t]*)\S", fr.text[brace:end])
        indent = indent.group(1) if indent and indent.group(1) else "    "
        out, locals_ = [], []
        for i, (t, n) in enumerate(params):
            if i not in retyped:
                out.append((t, n))
                continue
            c, m = retyped[i]
            spelled = self.scope.param_type(raw[i]) if i < len(raw) else m.replace("*", " *")
            if c in _INTEGERS + ("unsigned",) and m.endswith("*"):
                out.append((m[:-1] + " *", n))           # a memory pool passed as `int`: callers cast
                continue
            mn = names[i] if i < len(names) else None
            if param_kind(c) == "pointer" and n and mn and mn not in taken:
                out.append((spelled, mn))
                local = t.strip()
                if conv.cls.startswith("Gap::") and not self.gap_scope(fr, start, ctx) and self.converted:
                    local = re.sub(r"(?<!::)\b(%s)\b" % "|".join(re.escape(k) for k in sorted(
                        self.converted, key=len, reverse=True)), r"::\1", local)
                locals_.append("\n%s%s%s = (%s)%s;" % (indent, local if local.endswith("*") else local + " ", n,
                                                         local, mn))
                self.notes.append("%s: %s's parameter %s is %s's %s %s: the body reads it as the local %s %s"
                                  % (fr.rel, conv.cname, n, conv.qualified, spelled, mn, local, n))
                continue
            out.append((spelled, n))
            self.notes.append("%s: %s's parameter %s (%s) takes %s's type %s: check what the body reads"
                              % (fr.rel, conv.cname, n, c, conv.qualified, spelled))
        if locals_:
            fr.edits.append((brace + 1, brace + 1, "".join(locals_)))
        return out

    def keep_flat_names(self, fr, start, end):
        """A body moving from file scope into a Gap class keeps what its types meant: a bare converted class's name
        there was the flat struct (`(igObject *)x`), and inside the class it would be the Gap class, so it becomes
        `::igObject`."""
        if not self.converted:
            return
        names = re.compile(r"\b(?:%s)\b" % "|".join(re.escape(n) for n in sorted(self.converted, key=len,
                                                                                  reverse=True)))
        for m in names.finditer(fr.clean, start, end):
            p = m.start()
            if re.search(r"(?:::|\.|->)\s*$", fr.clean[max(start, p - 4):p]) or \
                    re.compile(r"\s*::").match(fr.clean, m.end()):
                continue
            fr.edits.append((p, p, " ::" if fr.clean[p - 1] == "<" else "::"))

    _VTABLE_STAMP = r"^[ \t]*(?:%s\s*->\s*\w+|\*\s*\([^()]*\)\s*\(?\s*%s\s*\)?)\s*=[^;]*(?:vtable|vtbl|__vt__)[^;]*;[ \t]*$"

    def constructor_body(self, fr, conv, ctx, rname):
        """The statements of a constructor's C body the compiler writes in a C++ constructor go: the store of the
        vtable into the receiver (MWCC stamps it), the closing `return self;`, and a first statement calling a
        base class's constructor by its C name (this batch's or one the compiler-name map binds), which C++ makes
        implicitly — with arguments it becomes the member-initialiser ` : Base(args)`, returned."""
        _name, start, end = ctx
        brace = fr.head_end(start)
        first, initializer = True, ""
        at = fr.clean.find("\n", brace) + 1
        while 0 < at < end:
            stop = fr.clean.find("\n", at)
            stop = end if stop < 0 or stop > end else stop
            line = fr.clean[at:stop]
            whole = (at, min(stop + 1, len(fr.text)))
            stripped = line.strip()
            if not stripped or stripped == "}":
                at = stop + 1
                continue
            lineno = fr.text.count("\n", 0, at) + 1
            if re.match(self._VTABLE_STAMP % (re.escape(rname), re.escape(rname)), line):
                fr.deletes.append(whole)
            elif re.fullmatch(r"return\s*\(?\s*%s\s*\)?\s*;" % re.escape(rname), stripped):
                fr.deletes.append(whole)
            elif re.match(r"return\b", stripped):
                raise Refused("%s:%d: %s returns something other than its receiver: it is no constructor"
                              % (fr.rel, lineno, conv.cname))
            else:
                call = re.fullmatch(r"(\w+)\s*\(\s*(?:\(\s*[\w:\s]+\*\s*\)\s*)?\(?\s*%s\s*\)?\s*(?:,(.*))?\)\s*;"
                                    % re.escape(rname), stripped, re.S)
                base = self.base_ctors.get(call.group(1)) if call else None
                if base and base != conv.base and self.classes.derives(conv.base, base):
                    if not first:
                        raise Refused("%s:%d: %s constructs its base %s after other statements: C++ constructs the "
                                      "base first" % (fr.rel, lineno, conv.cname, base))
                    fr.deletes.append(whole)
                    if call.group(2) and call.group(2).strip():
                        initializer = " : %s(%s)" % (base, fr.text[at:stop].split(",", 1)[1].rsplit(")", 1)[0].strip())
                first = False
            at = stop + 1
        return initializer

    def rewrite_receiver(self, fr, conv, ctx, receiver, signature):
        rtype, rname = receiver
        _name, start, end = ctx
        brace = fr.head_end(start)
        declared = re.sub(r"\b(?:struct|class|const)\b|\*|&", " ", rtype).split()
        spelled = declared[-1] if declared else conv.base
        rclass = _base_name(spelled)
        same = rclass == conv.base
        # a receiver declared as the flat struct of a converted class (`igObject *object` at file scope) passed on
        # bare still has the flat type: `this` is the Gap class's, so the use is `(::igObject *)this`
        flat = same and conv.cls.startswith("Gap::") and \
            self.gap_class(spelled, self.gap_scope(fr, start, ctx)) is None
        body = fr.clean[brace:end]
        shadowed = local_names(signature, body) - {rname}
        members = self.classes.all_fields(conv.base)
        view_fields = members if same else self.classes.all_fields(rclass)
        member_names = set(members) | {c.name for c in self.convs if c.base == conv.base} | \
            self.declared_names.get(conv.base, set())
        cast = "this" if same else "((%s *)this)" % _pointee(rtype)
        reused = self.reused_receiver(fr, conv, ctx, rtype, rname)
        for m in re.finditer(r"\b%s\b" % re.escape(rname), body):
            pos, after = brace + m.start(), brace + m.end()
            before = fr.clean[max(start, pos - 3):pos].rstrip()
            if before.endswith((".", "->", "::")):
                continue
            if reused is not None and pos >= reused:
                continue                                 # the local that takes the receiver's name, as it was
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
                re.search(r"\(\s*(?:struct\s+|class\s+)?(?:::\s*)?[A-Za-z_][\w:]*\s*\*+\s*\)\s*$",
                          fr.clean[max(start, pos - 60):pos])
            returned = re.search(r"\breturn\s*$", fr.clean[max(start, pos - 12):pos]) and \
                re.compile(r"\s*;").match(fr.clean, after)
            if casted or (same and (not flat or returned)):
                fr.edits.append((pos, after, "this"))
            else:
                fr.edits.append((pos, after, "(::%s *)this" % conv.base if same else "(%s *)this" % _pointee(rtype)))

    def reused_receiver(self, fr, conv, ctx, rtype, rname):
        """Where a body that reuses its receiver's variable starts using it as a local, or None.

        A C body may assign its receiver once it no longer needs it (`self = (T *)r.p;`), which `this` cannot
        take. From that statement on, the name is a local of the receiver's declared type: the assignment
        declares it (`T *self = (T *)r.p;`) when every later use is inside its block, else the body's first
        line does; the uses before it are the receiver's. Refused (the caller's check): a first assignment
        inside an expression (`f(self = x)`) or a compound one; here, a loop holding both the assignment and a
        receiver use before it, whose next pass would read the local as the receiver."""
        _name, start, end = ctx
        brace = fr.head_end(start)
        uses, first = [], None
        for m in re.finditer(r"\b%s\b" % re.escape(rname), fr.clean[brace:end]):
            pos, after = brace + m.start(), brace + m.end()
            if fr.clean[max(start, pos - 3):pos].rstrip().endswith((".", "->", "::")):
                continue
            if first is None and re.compile(r"\s*=(?!=)").match(fr.clean, after) and \
                    fr.clean[:pos].rstrip()[-1:] in (";", "{", "}"):
                first = pos
            uses.append(pos)
        if first is None:
            return None
        for m in re.finditer(r"\b(for|while|do)\b", fr.clean[brace:first]):
            loop, at = brace + m.start(), brace + m.end()
            if m.group(1) != "do":
                depth, at = 0, fr.clean.index("(", at)
                while True:
                    depth += {"(": 1, ")": -1}.get(fr.clean[at], 0)
                    at += 1
                    if depth == 0:
                        break
            while fr.clean[at].isspace():
                at += 1
            stop = units._match_brace(fr.clean, at) if fr.clean[at] == "{" else fr.clean.index(";", at) + 1
            if loop <= first < stop and any(loop <= p < first for p in uses):
                raise Refused("%s:%d: %s assigns its receiver `%s` in a loop that reads it as the receiver first: "
                              "it cannot become `this`" % (fr.rel, fr.text.count("\n", 0, first) + 1, conv.cname,
                                                           rname))
        decl = rtype.strip()
        if conv.cls.startswith("Gap::") and not self.gap_scope(fr, start, ctx) and self.converted:
            names = "|".join(re.escape(n) for n in sorted(self.converted, key=len, reverse=True))
            decl = re.sub(r"(?<!::)\b(%s)\b" % names, r"::\1", decl)
        decl = decl if decl.endswith(("*", "&")) else decl + " "
        depth, open_ = 0, brace
        for k in range(first - 1, brace, -1):            # the block holding the assignment
            if fr.clean[k] == "}":
                depth += 1
            elif fr.clean[k] == "{":
                if depth == 0:
                    open_ = k
                    break
                depth -= 1
        if all(p < units._match_brace(fr.clean, open_) for p in uses if p > first):
            fr.edits.append((first, first + len(rname), decl + rname))
        else:
            fr.edits.append((brace + 1, brace + 1, "\n    %s%s;" % (decl, rname)))
        return first


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


# ---- the boundary: C names a converted member keeps -------------------------------------------------------
def units_reading(index, rel):
    """The translation units that read file `rel` (itself, the units including a fragment, those reaching a
    header)."""
    if rel in index.units:
        return [rel]
    if index.unit_of.get(rel):
        return list(index.unit_of[rel])
    return [u for u, info in index.units.items() if rel in info["headers"]]


def boundary_sites(index, base, sites, users):
    """Which declarations of a converted member's C name stay -> (set of indexes into `sites`, notes).

    `sites` are the declarations, [(file, inside an `#ifdef __cplusplus` arm)]; `users` the files whose code still
    names the C name (a C caller, an unconverted subclass's direct call of a virtual default, a flat struct's
    construction or destruction). None stays without a user. With users, the home header's stays (a header under
    include/, the one named for the class first), and another only where a user's unit does not read the home
    header (or, a C unit, reads it only inside `#ifdef __cplusplus`): that unit's own declaration stays for it."""
    if not users or not sites:
        return set(), ([] if not users else ["used in %s and declared nowhere" % ", ".join(sorted(users))])
    order = sorted(range(len(sites)), key=lambda i: (not sites[i][0].startswith("include/"),
                                                     os.path.splitext(os.path.basename(sites[i][0]))[0] != base,
                                                     sites[i][0]))
    home = order[0]
    keep, notes = {home}, []
    for user in sorted(users):
        for unit in units_reading(index, user):
            info = index.units[unit]
            c_unit = info["lang"] == declarations._LANG_C

            def serves(i):
                rel, cxx = sites[i]
                return (rel in info["files"] or rel in info["headers"]) and not (c_unit and cxx)
            if any(serves(i) for i in keep):
                continue
            found = [i for i in order if serves(i)]
            if found:
                keep.add(found[0])
                notes.append("%s keeps its declaration: %s (through %s) does not read %s"
                             % (sites[found[0]][0], unit, user, sites[home][0]))
            else:
                notes.append("no declaration of it reaches %s (unit %s)" % (user, unit))
    return keep, notes


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


_ROW_FIELDS = ("emitted", "duplicates", "externals", "data", "anon", "stripped")


def _flat_form(mangled, converted):
    """`mangled` with each converted class's Gap scope (`Q33Gap4Core6igFile`) written as the flat class (`6igFile`),
    the lengths of the template instances holding one recomputed (`42igSmartPointer<Q33Gap3Gfx14igVertexStream>`
    is `32igSmartPointer<14igVertexStream>`)."""
    def flat(scope, _depth):
        if len(scope) >= 3 and scope[0] == ("Gap", None) and scope[1][1] is None and scope[2][1] is None and \
                converted.get(scope[2][0]) == scope[1][0]:
            return scope[2:]
        return scope
    return map_scopes(mangled, flat) or mangled


def _gap_template_form(mangled, converted):
    """`mangled` with each converted class a template argument names as its flat struct
    (`__dt__32igSmartPointer<14igVertexStream>Fv`) written as its Gap class
    (`__dt__42igSmartPointer<Q33Gap3Gfx14igVertexStream>Fv`)."""
    def gap(scope, depth):
        if depth and scope[0][1] is None and scope[0][0] in converted:
            return (("Gap", None), (converted[scope[0][0]], None)) + scope
        return scope
    return map_scopes(mangled, gap) or mangled


def stale_keys(rows, members, macros, types, converted, scope):
    """{key: compiler name} of the unit-objects.json keys of converted classes' members whose parameter names a
    class converted after them as its flat struct (`platformLoad__Q33Gap3Gfx7igImageFP6igFile`, written while igFile
    was flat): in the Gap class's scope the parameter's class is now the Gap class
    (`…FPQ33Gap4Core6igFile`), which is the name the compiler emits. A parameter the declaration spells as the
    flat struct (`::igFile *`) keeps it."""
    if not converted:
        return {}
    flat = re.compile(r"(?<![\w:])(%s)\b" % "|".join(re.escape(c) for c in sorted(converted, key=len, reverse=True)))
    keys = set()
    for row in rows.values():
        for field in _ROW_FIELDS:
            if isinstance(row.get(field), dict):
                keys.update(row[field])
        if row.get("symbol"):
            keys.add(row["symbol"])
    declared, out = {}, {}
    for key in sorted(keys):
        d = demangle(key) if "__" in key else None
        if d is None or d.data or d.class_name not in converted or d.namespaces[:1] != ("Gap",) or \
                not any(flat.search(p) for p in d.params):
            continue
        cls = d.class_name
        if cls not in declared:
            declared[cls] = declared_members(cls, (members or {}).get(cls, []), macros, types)
        for m in declared[cls]:
            if m.kind != "func" or m.name != d.name or len(m.params or ()) != len(d.params) or bool(m.const) != d.const:
                continue
            conv = Conversion(key, "Gap::%s::%s" % (converted[cls], cls), m.name, "func", bool(m.static),
                              bool(m.const), bool(m.inline), m.ret, tuple(m.params or ()), None)
            conv.raw_params = declared_raw_params((members or {}).get(cls, []), m.name, conv.params, m.const, macros,
                                                  types, cls)
            try:
                new = compiler_name(conv, converted, scope)
            except ValueError:
                continue
            if new != key and _flat_form(new, converted) == _flat_form(key, converted):
                out[key] = new
    return out


def rekey_rows(rows, renames, unit_renames=None):
    """Rename unit-objects.json keys in place, in order -> ([change], {row key}): `renames` {old: new} in every row,
    `unit_renames` {row key: {old: new}} in that row only (a `stripped` list's names too; a new name None drops the
    old one)."""
    changes, touched = [], set()
    for unit, row in rows.items():
        here = dict(renames)
        here.update((unit_renames or {}).get(unit, {}))
        for field in _ROW_FIELDS:
            entries = row.get(field)
            if not isinstance(entries, (dict, list)) or not any(k in here for k in entries):
                continue
            if isinstance(entries, dict):
                row[field] = {here.get(k, k): v for k, v in entries.items() if here.get(k, k) is not None}
            else:
                row[field] = [here.get(k, k) for k in entries if here.get(k, k) is not None]
            for k in entries:
                if k in here:
                    changes.append("%s %s: %s %s" % (unit, field, k, "dropped" if here[k] is None
                                                     else "-> " + here[k]))
                    touched.add(unit)
        if row.get("symbol") in here and here[row["symbol"]] is not None:
            changes.append("%s symbol: %s -> %s" % (unit, row["symbol"], here[row["symbol"]]))
            row["symbol"] = here[row["symbol"]]
            touched.add(unit)
    return changes, touched


def declared_classes(root):
    """The class, struct, union and enum names src/ and include/ (third-party sources too) declare or define, and
    the typedef names: the names a compiler name's scopes may still name."""
    out = set()
    patterns = (re.compile(r"\b(?:struct|class|union|enum)\s+([A-Za-z_]\w*)"), re.compile(r"\}\s*([A-Za-z_]\w*)\s*;"),
                re.compile(r"\btypedef\b[^;{}]*?\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*;"))
    for top in ("src", "include"):
        for dirpath, _dirs, files in os.walk(os.path.join(root, top)):
            for f in files:
                if f.endswith(SOURCE_EXTS):
                    text = _read(os.path.join(dirpath, f))
                    for pattern in patterns:
                        out.update(pattern.findall(text))
    return out


def _scope_classes(mangled):
    """The class identifiers a compiler name's scopes name (its class, its parameters', its template arguments'),
    its namespaces (`Gap::<library>`, `std`) aside."""
    out = set()

    def collect(scope, _depth):
        names = [identifier for identifier, _args in scope]
        if names[:1] == ["Gap"]:
            names = names[2:]
        elif names[:1] == ["std"]:
            names = names[1:]
        out.update(names)
        return scope
    map_scopes(mangled, collect)
    return out


def _shape(mangled):
    """`mangled` with every class its scopes name written as one stand-in, a class template keeping its name
    (`__dt__33igSmartPointer<15igSemaphoreView>Fv` and `__dt__40igSmartPointer<Q33Gap4Core11igSemaphore>Fv` are one
    shape, `__dt__10ScopedLockFv` and `__dt__11igScopeLockFv` another)."""
    def stand_in(scope, _depth):
        identifier, args = scope[-1]
        return ((identifier if args is not None else "_", args),)
    return map_scopes(mangled, stand_in) or mangled


def object_keys(rows, converted, declared):
    """{row key: [name]} of the unit-objects.json names only the unit's object can settle (object_renames): a
    template instance whose argument names a converted class as its flat struct (`__dt__32igSmartPointer<14igVertex
    Stream>Fv`, `getElementMeta__Q33Gap4Core34igTObjectList<14igMediaFile>CFv`: which instance the unit compiles
    depends on where its source spells it, inside a Gap namespace or a Gap class's member the Gap class, at file scope
    the flat struct), and in a whole-file row a name whose scopes name a class the tree no longer declares (`declared`,
    declared_classes: a view retired, `__dt__33igSmartPointer<15igSemaphoreView>Fv`, or a helper renamed,
    `__dt__10ScopedLockFv` once it is the kit's igScopeLock)."""
    out = {}
    for unit, row in rows.items():
        names = [k for field in _ROW_FIELDS if isinstance(row.get(field), (dict, list)) for k in row[field]]
        names += [row["symbol"]] if row.get("symbol") else []
        found = [k for k in names if "<" in k and _gap_template_form(k, converted) != k]
        if row.get("whole_file"):
            found += [k for k in names if k not in found and _scope_classes(k) - declared]
        if found:
            out[unit] = found
    return out


def object_renames(rows, converted, declared, object_names):
    """{row key: {old: new}} of the names (object_keys) a unit's object no longer has -> (renames, notes). Each
    becomes the one name of the object that differs from it only in converted classes' Gap scopes
    (`__dt__42igSmartPointer<Q33Gap3Gfx14igVertexStream>Fv` for `__dt__32igSmartPointer<14igVertexStream>Fv`), else
    the one name of the object the row does not list that differs from it only in the classes it names (_shape:
    `__dt__11igScopeLockFv` for `__dt__10ScopedLockFv`); a `stripped` name with neither goes (None: the object
    no longer compiles that body, `__dt__33igSmartPointer<15igSemaphoreView>Fv` once the view is retired).
    `object_names(row key, row)` is the set of names the unit's object defines and references, or None when it cannot
    be compiled."""
    out, notes = {}, []
    for unit, stale in sorted(object_keys(rows, converted, declared).items()):
        row = rows[unit]
        names = object_names(unit, row)
        if names is None:
            notes.append("%s: the unit could not be compiled here, its names stay (%s)" % (unit, ", ".join(stale)))
            continue
        others = {k for field in _ROW_FIELDS if field != "stripped" and isinstance(row.get(field), (dict, list))
                  for k in row[field]}
        others |= {row["symbol"]} if row.get("symbol") else set()
        listed = others | set(row.get("stripped") or ())
        flat, shapes, claimed = {}, {}, set()
        for n in names:
            flat.setdefault(_flat_form(n, converted), set()).add(n)
            if n not in listed:
                shapes.setdefault(_shape(n), set()).add(n)
        for key in stale:
            if key in names:
                continue
            found = (flat.get(_flat_form(key, converted), set()) - {key} or shapes.get(_shape(key), set())) - claimed
            if len(found) == 1:
                new = found.pop()
                claimed.add(new)
                out.setdefault(unit, {})[key] = new
            elif not found and key not in others:
                out.setdefault(unit, {})[key] = None
            else:
                notes.append("%s: %s is not in the unit's object, which has %s" % (
                    unit, key, " and ".join(sorted(found)) if found else "no name of that instance"))
    return out, notes


_UNIT_SOURCES = {}


def unit_object_names(root, unit, row):
    """The names the object of a whole-file row's unit defines and references, compiled as tools/check.py builds it
    (tools/project.py compile_unit: the source units.scan finds for the owner, under the unit's profile), or None
    when it cannot be."""
    import cc
    import project
    import verify
    if not row.get("whole_file") or os.path.abspath(root) != ROOT:
        return None
    config = os.path.join(root, "config", GAME)
    if root not in _UNIT_SOURCES:
        _UNIT_SOURCES[root] = units.scan(os.path.join(root, "src"), os.path.join(config, "symbols.txt"),
                                         os.path.join(config, "unit-objects.json"))
    owner = verify.load_symbols(os.path.join(config, "symbols.txt"))[1].get(int(unit, 16), (None,))[0]
    source = _UNIT_SOURCES[root].get(owner)
    if source is None:
        return None
    out = os.path.join(cc.scratch_dir(), "memberize-%s.o" % unit)
    if project.compile_unit(project.DEFAULT_VERSION, owner, os.path.join(root, source), out, quiet=True):
        return None
    return set(verify.object_syms(out)[0])


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
    converted = converted_classes(root)
    planner.converted = converted
    scope = planner.scope = NameScope(members, classes.bases, index.texts.values(), index.types)
    for conv in convs:
        if "::" not in conv.cls and conv.cls in converted:
            conv.cls = "Gap::%s::%s" % (converted[conv.cls], conv.cls)   # a converted class lives in Gap::<Lib>
        conv.mangled = compiler_name(conv, converted, scope)
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
    planner.base_ctors = base_constructors(root, convs)
    planner.members = members
    # a C prototype taking an integer where the member takes a pointer (`X_CreateInstance(int allocator)`, whose
    # definition classconv may have retyped already): its callers' arguments are cast (retyped_arguments); one
    # ordering its parameters otherwise (igRegistry_GetValueFloat's `create, defaultValue` for the kit's
    # `defaultVal, createValue`): its callers' arguments take the member's order (argument_order)
    wanted = {c.cname for c in convs if c.kind == "func"}
    protos = collections.defaultdict(list)
    for ds in index.decls.values():
        for d in ds:
            if d.name in wanted and d.kind == "func" and d.params is not None:
                protos[d.name].append((tuple(p for p in d.params if p != "void"), _param_names(d.text, d.name)))
    for conv in convs:
        names = _param_names("f(%s)" % ", ".join(conv.raw_params or ()), "f") or [None] * len(conv.params)
        orders = set()
        want = tuple(planner.unqualified(p, conv.base) for p in conv.params)
        for ps, c_names in protos.get(conv.cname, ()):
            c_names = c_names if c_names and len(c_names) == len(ps) else [None] * len(ps)
            if not conv.static and not conv.special and len(ps) == len(conv.params) + 1:
                ps, c_names = ps[1:], c_names[1:]       # the receiver
            ps = tuple(planner.unqualified(p, conv.base) for p in ps)
            if ps == want:
                continue                                 # the member's own form (classconv's stub)
            try:
                order = argument_order(ps, c_names, want, names,
                                       lambda t, cls=conv.base: planner.is_enum(t, cls))
            except ValueError as e:
                raise Refused("%s (%s) orders its parameters otherwise than %s (%s), and their types and names fit "
                              "%d orders (%s): rewrite its calls by hand" % (
                                  conv.cname, ", ".join(ps), conv.qualified, ", ".join(want), len(e.args[0]),
                                  "; ".join(", ".join(str(j + 1) for j in o) for o in e.args[0])))
            if order is not None:
                orders.add(order)
                ps = tuple(ps[j] for j in order)
            if len(ps) == len(want):
                retyped, refusal = retyped_params(ps, want, lambda t, cls=conv.base: planner.is_enum(t, cls),
                                                  conv.stated)
                conv.c_params.update(retyped if refusal is None else {})
        if len(orders) > 1:
            raise Refused("%s's C prototypes order its parameters in different ways" % conv.cname)
        conv.order = orders.pop() if orders else None
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
        # several C names of one member are aliases; overloads (one name, other parameters) are members apart
        by_member[(conv.kind, conv.qualified, conv.params, conv.const)].append(conv)
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
    planner.drop_forwarders(second)
    planner.settle_declarations()
    planner.rename_comments()
    if planner.errors:
        raise Refused("\n".join(planner.errors))
    new_texts = {}
    for rel, fr in second.items():
        text = fr.result() if (fr.edits or fr.deletes) else fr.text
        if text != originals[rel]:
            new_texts[rel] = cxxscope.respell(text) if cxx_reads(index, rel) else text
    placing = placing_rows(rows, convs, planner.defined, index, addresses)
    changes = rename_rows(rows, convs, placing) if rows else []
    # members of converted classes whose parameter names a class this tree converted since their keys were written
    more, rekeyed = rekey_rows(rows, stale_keys(rows, members, macros, index.types, converted, scope))
    changes += more
    for conv in convs:
        if conv.cname in planner.defined and conv.cname not in placing:
            planner.notes.append("%s has no whole-file row placing it: its compiler name %s is in no row"
                                 % (conv.cname, conv.mangled))
    adds = sorted({(c.base, c.declaration) for c in convs if c.declaration})
    planner.units = touched_rows(new_texts, index, rows, addresses, set(placing.values()))
    planner.units += sorted(rekeyed - set(planner.units))
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


def base_constructors(root, convs):
    """{C name: class} of the constructors a converted class's C constructor may call first: this batch's and
    those the compiler-name map binds (`__ct__…` at the C name's address)."""
    out = {c.cname: c.base for c in convs if c.special == "ctor"}
    for compiled, (_va, retail) in compiler_names.load(os.path.join(root, "config", GAME, "symbols.txt")).items():
        if compiled.startswith("__ct__"):
            d = demangle(compiled)
            if d and d.class_name:
                out.setdefault(retail, d.class_name)
    return out


def tree_stale_keys(root, index=None):
    """(unit-objects.json rows, {stale key: compiler name}) of the tree (stale_keys)."""
    index = index or declarations.Index(root, approvals={})
    rows_path = os.path.join(root, "config", GAME, "unit-objects.json")
    rows = json.loads(_read(rows_path)) if os.path.exists(rows_path) else {}
    members = class_members(root)
    scope = NameScope(members, Classes(root, index).bases, index.texts.values(), index.types)
    return rows, stale_keys(rows, members, declarations.function_macros(index.texts.values()), index.types,
                            converted_classes(root), scope)


def boundary_report(root, index=None):
    """The declarations of converted members' C names that nothing needs any more -> [finding].

    A converted member's C name is the retail name config/SLUS-20836/compiler-names.tsv gives a compiler name of a
    class in config/converted-classes.tsv. Each declaration of it in src/ and include/ is weighed as memberize
    weighs it (boundary_sites): one stays in the home header while an unconverted user still names it, plus one
    for a user's unit that does not read the home header; every other is reported."""
    index = index or declarations.Index(root, approvals={})
    converted = converted_classes(root)
    cnames = {}
    for compiled, (_va, retail) in compiler_names.load(os.path.join(root, "config", GAME, "symbols.txt")).items():
        d = demangle(compiled)
        if d and d.class_name in converted and retail != compiled:
            cnames.setdefault(retail, d.class_name)
    if not cnames:
        return []
    pattern = re.compile(r"\b(%s)\b" % "|".join(re.escape(n) for n in sorted(cnames, key=len, reverse=True)))
    sites, users, defined = collections.defaultdict(list), collections.defaultdict(set), set()
    for rel in source_files(root):
        text = index.texts.get(rel)
        if text is None:
            text = _read(os.path.join(root, rel))
        if not pattern.search(text):
            continue
        fr = FileRewrite(rel, text)
        for m in pattern.finditer(fr.clean):
            cname, pos, end = m.group(1), m.start(), m.end()
            if fr.clean[max(0, pos - 3):pos].rstrip().endswith((".", "->", "::")):
                continue
            if macro_body(fr.clean, pos) is not None:
                users[cname].add(rel)                    # a macro's replacement text: code that expands it
                continue
            if fr.clean[fr.clean.rfind("\n", 0, pos) + 1:pos].lstrip().startswith("#"):
                continue
            ctx = fr.enclosing(pos)
            if ctx is not None and pos < fr.head_end(ctx[1]):
                if ctx[0] == cname:
                    defined.add(cname)                   # a C definition: not converted (an alias's own body)
                continue
            if ctx is not None:
                users[cname].add(rel)
                continue
            stmt_start = _statement_start(fr.clean, pos)
            head = fr.clean[stmt_start:pos]
            nxt = re.compile(r"\s*(\S?)").match(fr.clean, end).group(1)
            if (nxt == "(" and _declares(head)) or (re.search(r"\bextern\b", head) and "=" not in head):
                sites[cname].append((rel, cxx_only(fr, pos), fr.text.count("\n", 0, pos) + 1))
            else:
                users[cname].add(rel)
    findings = []
    for cname, listed in sorted(sites.items()):
        if cname in defined:
            continue
        keep, _notes = boundary_sites(index, cnames[cname], [(rel, cxx) for rel, cxx, _l in listed],
                                      users.get(cname, set()))
        home = [listed[i][0] for i in sorted(keep)]
        for i, (rel, _cxx, line) in enumerate(listed):
            if i not in keep:
                why = ("its users read %s" % ", ".join(home)) if users.get(cname) else \
                    "no unconverted code names it any more (it is a member of %s)" % cnames[cname]
                findings.append("%s:%d: %s: C-name declaration no longer needed: %s" % (rel, line, cname, why))
    return findings


def respell_tree(root):
    """{file: new text} of the C++ sources whose Gap-qualified definitions go into their namespaces
    (tools/cxxscope.py)."""
    out = {}
    for rel in source_files(root):
        if not rel.endswith((".cpp", ".inc", ".h", ".hpp")):
            continue
        text = _read(os.path.join(root, rel))
        if "Gap" not in text:
            continue
        new = cxxscope.respell(text)
        if new != text:
            out[rel] = new
    return out


def insert_member_rows(path, adds):
    """Add `(class, declaration)` rows to class-members.tsv, each after its class's last row (in `adds` order), or at
    the end for a class with no row yet."""
    with open(path) as fh:
        lines = fh.readlines()
    if lines and not lines[-1].endswith("\n"):
        lines[-1] += "\n"
    for cls, decl in adds:
        at = None
        for i, line in enumerate(lines):
            if not line.startswith("#") and line.split("\t", 1)[0] == cls:
                at = i + 1
        row = "%s\t%s\n" % (cls, decl)
        if at is None:
            lines.append(row)
        else:
            lines.insert(at, row)
    with open(path, "w") as fh:
        fh.writelines(lines)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("table", nargs="?", help="tab-separated `<C name>\\t<member>` rows")
    ap.add_argument("--root", default=ROOT, help="the tree to rewrite (default: this repository)")
    ap.add_argument("--apply", action="store_true", help="write the changes (default: dry run)")
    ap.add_argument("--diff", action="store_true", help="print the source changes as a unified diff")
    ap.add_argument("--check", action="store_true",
                    help="report each converted member's C-name declaration nothing needs any more (exit 1)")
    ap.add_argument("--respell", action="store_true",
                    help="put every Gap-qualified out-of-line definition into its namespaces (no table)")
    ap.add_argument("--rekey", action="store_true",
                    help="rename the unit-objects.json keys of converted members whose parameter names a class "
                         "converted since as its flat struct, and the names a unit's object now spells otherwise: a "
                         "template instance of a converted class, a class renamed or retired, a stripped body gone "
                         "(compiles those units; no table)")
    a = ap.parse_args(argv)
    root = os.path.abspath(a.root)
    if a.check:
        index = declarations.Index(root, approvals={})
        findings = boundary_report(root, index)
        for f in findings:
            print(f)
        _rows, stale = tree_stale_keys(root, index)
        for old, new in sorted(stale.items()):
            print("config/%s/unit-objects.json: %s: the compiler names it %s (memberize.py --rekey --apply)"
                  % (GAME, old, new))
        print("memberize --check: %d C-name declaration%s no longer needed" % (len(findings),
                                                                             "" if len(findings) == 1 else "s")
              + (", %d stale compiler-name key%s" % (len(stale), "" if len(stale) == 1 else "s") if stale else ""))
        return 1 if findings or stale else 0
    if a.respell:
        new_texts = respell_tree(root)
        print("%d source files to respell" % len(new_texts))
        show_and_write(root, new_texts, a)
        return 0
    if a.rekey:
        rows, stale = tree_stale_keys(root)
        unit_renames, notes = object_renames(rows, converted_classes(root), declared_classes(root),
                                             lambda unit, row: unit_object_names(root, unit, row))
        changes, touched = rekey_rows(rows, stale, unit_renames)
        for c in changes:
            print("  unit-objects.json " + c)
        for n in notes:
            print("note: " + n)
        print("%d unit-objects.json changes" % len(changes))
        if not a.apply:
            print("\n(dry run — re-run with --apply)")
            return 0
        if changes:
            status = write_rows(root, rows)
            if status:
                return status
            print("next:\n" + "\n".join("  python3 tools/whole_file_rows.py --unit-va %s --cxx --write" % key
                                        for key in sorted(touched)))
        return 0
    if not a.table:
        ap.error("give a conversion table, --respell, --rekey or --check")
    try:
        new_texts, rows, changes, adds, convs, planner = plan(root, a.table)
    except Refused as e:
        print("memberize: refused, nothing was written:\n" + str(e), file=sys.stderr)
        return 2
    for conv in convs:
        print("  %-40s -> %s%s%s  [%s]" % (conv.cname, "static " if conv.static else "", conv.qualified,
                                           " (inline)" if conv.inline else " (implicit)" if conv.implicit else "",
                                           conv.mangled))
    print("%d source files to rewrite, %d unit-objects.json changes, %d class-members.tsv rows to add"
          % (len(new_texts), len(changes), len(adds)))
    for rel in sorted(new_texts):
        print("  " + rel)
    for c in changes:
        print("  unit-objects.json " + c)
    for cls, decl in adds:
        print("  class-members.tsv %s\t%s" % (cls, decl))
    for cname, files in sorted(planner.c_callers.items()):
        kept = planner.boundary.get(cname)
        print("note: %s keeps its C name in %s (C code, a direct call of a virtual function, a flat struct's "
              "construction or destruction, a non-public member out of the caller's reach): %s"
              % (cname, ", ".join(sorted(files)),
                 "its declaration stays in " + ", ".join(kept) if kept else "no declaration of it is left"))
    for member, files in sorted(planner.inline_users.items()):
        print("note: %s is inline and its address is taken in %s: those units compile a copy of it (a "
              "`duplicates` row)" % (member, ", ".join(sorted(files))))
    for n in planner.notes:
        print("note: " + n)
    if not show_and_write(root, new_texts, a):
        return 0
    if adds:
        insert_member_rows(os.path.join(root, "config", "class-members.tsv"), adds)
    print("memberize: rewrote %d files, %d row changes, %d declarations added" % (len(new_texts), len(changes),
                                                                                 len(adds)))
    if changes:
        status = write_rows(root, rows)
        if status:
            return status
    steps = []
    if adds:
        steps.append("python3 scripts/gen_type_headers.py          # class-members.tsv changed")
    steps.append("python3 tools/memberize.py --rekey --apply      # once the bodies compile: the row names the "
                 "objects now spell otherwise")
    steps += ["python3 tools/whole_file_rows.py --unit-va %s --cxx --write" % key for key in planner.units]
    steps.append("python3 tools/check.py --function <unit va> --cand <unit file>   # each touched unit")
    steps.append("python3 tools/memberize.py --check              # no C-name declaration left over")
    steps.append("make check-fresh && make link-fresh")
    print("next, in this order:\n" + "\n".join("  " + s for s in steps))
    return 0


def write_rows(root, rows):
    """Write unit-objects.json and regenerate the compiler-name map from it -> exit status."""
    with open(os.path.join(root, "config", GAME, "unit-objects.json"), "w") as fh:
        fh.write(json.dumps(rows, indent=2) + "\n")
    names_tool = os.path.join(root, "tools", "compiler_names.py")
    if os.path.exists(names_tool):
        return subprocess.run([sys.executable, names_tool, "--write"], cwd=root).returncode
    return 0


def show_and_write(root, new_texts, a):
    """Print the diff when asked; write the texts with --apply -> whether they were written."""
    if a.diff:
        for rel in sorted(new_texts):
            old = _read(os.path.join(root, rel))
            sys.stdout.writelines(difflib.unified_diff(old.splitlines(True), new_texts[rel].splitlines(True),
                                                       "a/" + rel, "b/" + rel))
    if not a.apply:
        print("\n(dry run — re-run with --apply)")
        return False
    for rel, text in new_texts.items():
        _write(os.path.join(root, rel), text)
    return True


if __name__ == "__main__":
    sys.exit(main())
