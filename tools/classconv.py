#!/usr/bin/env python3
"""classconv.py — convert one batch of flat classes to `Gap::<Library>::` classes from a spec file.

    python3 tools/classconv.py <spec.py> {tables,memberize,splice,decls,all} [<class> ...]

Without classes, every class of the spec, in its order. Run from the repository root. The steps are those of
docs/engine/member-conversion.md ("Converting a class, in order"), for every class of the batch:

  tables     the class's row in config/converted-classes.tsv, its `rows` in config/class-members.tsv (after its
             last row there) and its `typed` fields in config/typed-fields.tsv
  memberize  each C function a hand body replaces becomes an empty stub with the member's parameters, then
             tools/memberize.py --apply renames every mapped C name and `g_<Class>_<datum>` to its member
  splice     tools/gen_odl_source.py's boilerplate (`gen`) and the hand `bodies` replace the memberized
             definitions; a metafield's descriptor creator and `getMetaField` are igen's; a bootstrap class's
             constructors, copy slot and `__bootstrapDestruct` are written in the kit's form over their C
             definitions and their unit-objects.json keys renamed to the compiler names; igen's file-scope
             field tables go (the generator keeps them function-local); a static datum's definition takes its
             declared type; `memberize.py --respell` last
  decls      the C-name declarations `memberize.py --check` reports unneeded are deleted (after the
             splice, which drops the last C users of the bootstrap names)
  all        the four in order

The rows of touched units, the compiler-name map and the checks are the caller's (member-conversion.md).

A spec file is Python defining SPECS = {<class>: dict(...)}; `import classconv` gives it the shared pieces
(COMMON, GEN, STRINGS, array_spec). The keys of a class's dict:

  lib      library namespace (default "Core"); base: the parent class (a bootstrap class's constructors);
           cxxbase: the kit template instance the class derives from over its registered parent
           (converted-classes.tsv's third column, `igTDataList<igObject *>`)
  rows     class-members.tsv declarations, in the kit header's order
  typed    [(field, C++ type)] rows for typed-fields.tsv
  map      {C suffix: member} for `<Class>_<suffix>` functions; extra: {C name: member} for other C names
  keep     C suffixes that stay free functions (memberize leaves them; anything else unmapped is reported)
  data     {datum suffix: member} for `g_<Class>_<suffix>`
  gen      members whose definitions the generator writes (default GEN)
  bodies   {member: definition}, `{C}` the class; a member may name several overloads only through `bodies`
           keyed `member` (the first definition of that name is replaced)
  boot     {Init|CopyConstruct|Construct|Clone|Destruct: definition} overriding the default bootstrap bodies
           (str.format: `{C}` the class, `{B}` the base, braces doubled)
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
import demangle  # noqa: E402

SYMBOLS = "config/SLUS-20836/symbols.txt"
UNIT_OBJECTS = "config/SLUS-20836/unit-objects.json"
LIBRARY_DIRS = {"Core": "src/engine/core", "Math": "src/engine/maths", "Attrs": "src/engine/attrs",
                "Gfx": "src/engine/gfx", "Sg": "src/engine/scenegraph"}

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
              "            MetaRefList_AppendRetained(getMetaFieldTypes(), (::igObject *)metaField);\n"
              "            {{\n                ::igObject *held = (::igObject *)_MetaField;\n"
              "                held->_refCount = (int)held->_refCount - 1;\n"
              "                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {{\n"
              "                    igObject_Destroy(held);\n                }}\n            }}\n"
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


def find_c_def(text, cname):
    """(start, end) of the file-scope definition of the C function `cname`, or None."""
    m = re.search(r"^(?![ \t])[^\n;{}()]*\b%s\s*\([^;{]*?\)\s*\{" % re.escape(cname), text, re.M)
    if not m:
        return None
    return m.start(), block_end(text, m.end() - 1)


def member_def_re(cls, member):
    return re.compile(r"^[^\n;{}]*\b%s::%s\s*\([^;{]*?\)[^;{]*\{" % (re.escape(cls), re.escape(member)), re.M)


def replace_member(text, cls, member, body):
    """`text` with the first definition of `cls::member` replaced by `body`, and whether there was one."""
    m = member_def_re(cls, member).search(text)
    if not m:
        return text, False
    return text[:m.start()] + body.rstrip("\n") + text[block_end(text, m.end() - 1):], True


def fragment_pieces(text, cls):
    """{member: definition text} of `cls`'s definitions in a gen_odl_source fragment (the first of each name)."""
    out = {}
    for m in re.finditer(r"^[^\n;{}]*\b%s::(~?\w+)\s*\([^;{]*?\)[^;{]*\{" % re.escape(cls), text, re.M):
        out.setdefault(m.group(1), text[m.start():block_end(text, m.end() - 1)])
    return out


def ns(lib, body):
    return "namespace Gap {\nnamespace %s {\n\n%s\n}\n}\n" % (lib, body.rstrip("\n"))


def decl_of(rows, member):
    """(static, return type, parameter list) of the first row declaring `member`, or None."""
    for r in rows:
        r = re.sub(r"^\s*(public|protected|private)\s*:\s*", "", r)
        m = re.match(r"((?:virtual|static|inline)\s+)*(.*?)\b%s\s*\(([^)]*)\)" % re.escape(member), r)
        if m:
            return "static" in (m.group(1) or ""), m.group(2).strip(), m.group(3).strip()
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


FILE_TABLES = (r"\n(static )?(igMetaObjectCallback |FieldFactory |const char \*|igMetaField \*\*|int )"
               r"g_%s_(callbackList|ctorTable|fieldTable|fieldDescriptors|fieldHandles|fieldOffsets)\[\] = \{[^}]*\};"
               r"(?=\n)")


def drop_file_tables(text, cls):
    """igen keeps the registrar's and the field adder's tables function-local: the file-scope C ones go."""
    pat = re.compile(FILE_TABLES % re.escape(cls))
    while True:
        new = pat.sub("", text)
        if new == text:
            return re.sub(r"\n\n\n+", "\n\n", text)
        text = new


def rekey_row(row, old, new):
    """Rename the key `old` to `new` in one unit-objects.json row, in place and in order; whether it was there."""
    hit = False
    for sec in ("emitted", "data", "duplicates", "anon", "stripped"):
        m = row.get(sec)
        if isinstance(m, dict) and old in m:
            row[sec] = collections.OrderedDict((new if k == old else k, v) for k, v in m.items())
            hit = True
    return hit


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

    def symbols(self, cls):
        """`cls`'s `<cls>_<suffix>` functions of symbols.txt, as suffixes in address order."""
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
        return [n[len(cls) + 1:] for _va, n in self._symbols if n.startswith(cls + "_")]

    def files(self, lib):
        d = LIBRARY_DIRS.get(lib)
        if d is None:
            raise ConvError("no source directory for library %s (classconv.LIBRARY_DIRS)" % lib)
        return sorted(os.path.join(d, f) for f in os.listdir(self.path(d))
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

    def rekey(self, pairs):
        """Rename unit-objects.json keys `old` -> `new` in whichever unit rows list them; the names not found."""
        text = self.read(UNIT_OBJECTS)
        data = json.loads(text, object_pairs_hook=collections.OrderedDict)
        missing = []
        for old, new in pairs:
            if not any(rekey_row(row, old, new) for row in data.values() if isinstance(row, dict)):
                missing.append(old)
        self.write(UNIT_OBJECTS, json.dumps(data, indent=2, ensure_ascii=False) + ("\n" if text.endswith("\n") else ""))
        return missing


# ---------------------------------------------------------------------------------------------------- steps


def lib_of(spec):
    return spec.get("lib", "Core")


def is_descriptor(cls, spec):
    return spec.get("descriptor", cls.endswith("MetaField"))


def step_tables(tree, classes, specs):
    converted = {l.split("\t", 1)[0] for l in tree.read("config/converted-classes.tsv").split("\n")}
    for c in classes:
        if c in converted:
            raise ConvError("%s is converted already" % c)
        spec = specs[c]
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
    """decl_of `member` in `rows`, else the object macros' declaration of it."""
    d = decl_of(rows, member)
    if d is None and member in MACRO_DECLS:
        static, ret, params = MACRO_DECLS[member]
        d = static, ret.replace("{C}", cls), params
    return d


def stub(tree, cls, spec):
    """Each C function a hand body or the generator replaces becomes an empty definition with the member's
    parameters (memberize refuses a C form whose parameters differ from the member's)."""
    pairs = [("%s_%s" % (cls, s), m) for s, m in spec["map"].items()] + list(spec.get("extra", {}).items())
    for cname, member in pairs:
        if member not in spec.get("bodies", {}) and member not in spec.get("gen", GEN):
            continue
        d = member_decl(cls, spec["rows"], member)
        if d is None:
            continue
        for path in tree.files_naming(lib_of(spec), cname):
            text, ok = stub_text(tree.read(path), cname, stub_head(cls, cname, d))
            if ok:
                tree.write(path, text)
                break


def memberize_table(tree, classes, specs):
    """The memberize rows of the batch, and the class's C names neither mapped nor kept."""
    table, unmapped = [], []
    for c in classes:
        spec = specs[c]
        q = "Gap::%s::%s" % (lib_of(spec), c)
        for g, m in spec.get("data", {}).items():
            table.append(("g_%s_%s" % (c, g), "%s::%s" % (q, m)))
        for cname, m in spec.get("extra", {}).items():
            table.append((cname, "%s::%s" % (q, m)))
        for n in tree.symbols(c):
            if n in spec["map"]:
                table.append(("%s_%s" % (c, n), "%s::%s" % (q, spec["map"][n])))
            elif n not in spec.get("keep", ()) and n not in BOOT:
                unmapped.append("%s_%s" % (c, n))
    return table, unmapped


def step_memberize(tree, classes, specs):
    for c in classes:
        stub(tree, c, specs[c])
    table, unmapped = memberize_table(tree, classes, specs)
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
        text = re.sub(r"^[^\n;{}()]*?\b%s::%s;" % (re.escape(cls), name), "%s%s::%s;" % (t, cls, name), text,
                      flags=re.M)
    return text


def splice_class(tree, c, spec, frag):
    """Write the generator's and the hand definitions of one class over its memberized ones."""
    lib = lib_of(spec)
    if "%s: not written" % c in frag and spec.get("gen", GEN):
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
            t = re.sub(r"^[^\n;{}()]*?\b%s::_MetaField;" % c, "%s *%s::_MetaField;" % (c, c), t, flags=re.M)
        t = respell_data(t, c, spec["rows"])
        for member in spec.get("gen", GEN):
            if member in gen and member not in hand:
                t, ok = replace_member(t, c, member, gen[member])
                if ok:
                    done.add(member)
        for member, body in hand.items():
            t, ok = replace_member(t, c, member, body)
            if ok:
                done.add(member)
        tree.write(path, drop_file_tables(t, c))
    wanted = (set(spec.get("gen", GEN)) & set(gen)) | set(spec.get("bodies", {}))
    missing = sorted(wanted - done)
    print("%s: spliced %d%s" % (c, len(done), (" MISSING " + " ".join(missing)) if missing else ""))
    if "Construct" in tree.symbols(c):
        splice_boot(tree, c, spec)


def splice_boot(tree, c, spec):
    """A bootstrap class's constructors, copy slot and bootstrap destruct, in the kit's form."""
    lib = lib_of(spec)
    bodies = boot_bodies(c, spec["base"])
    for n, override in spec.get("boot", {}).items():
        bodies[n] = (override,) + bodies[n][1:]
    names = tree.symbols(c)
    rekeys = []
    for n, (body, member, params) in bodies.items():
        if n not in names:
            continue
        cname = "%s_%s" % (c, n)
        body = body.format(C=c, B=spec["base"])
        params = [p.format(C=c, L=lib) for p in params]
        for path in tree.files_naming(lib, cname):
            t = tree.read(path)
            span = find_c_def(t, cname)
            if span:
                tree.write(path, t[:span[0]] + ns(lib, body) + "\n" + t[span[1]:])
                rekeys.append((cname, boot_key(lib, c, member, params)))
                break
        else:
            print("%s: no definition of %s" % (c, cname))
    for old in tree.rekey(rekeys):
        print("%s: no unit-objects key %s" % (c, old))


def step_splice(tree, classes, specs):
    args = ["tools/gen_odl_source.py"]
    for c in classes:
        args += ["--class", c]
    frag = tree.run(args)
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


def load_specs(path):
    sys.path.insert(0, HERE)
    s = importlib.util.spec_from_file_location("classconv_spec", path)
    mod = importlib.util.module_from_spec(s)
    s.loader.exec_module(mod)
    return mod.SPECS


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("spec", help="the batch's spec file (Python defining SPECS)")
    ap.add_argument("step", choices=("tables", "memberize", "splice", "decls", "all"))
    ap.add_argument("classes", nargs="*", help="the classes to convert (default: the spec's, in order)")
    ap.add_argument("--root", default=ROOT)
    a = ap.parse_args(argv)
    specs = load_specs(a.spec)
    classes = a.classes or list(specs)
    unknown = [c for c in classes if c not in specs]
    if unknown:
        ap.error("not in the spec: " + " ".join(unknown))
    tree = Tree(a.root)
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
    except ConvError as e:
        print("classconv: %s" % e, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
