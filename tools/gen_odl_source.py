#!/usr/bin/env python3
"""gen_odl_source.py — write a library's reflection boilerplate the way Alchemy's code generator wrote it.

The original libraries did not hand-write their registration code. `igen.exe` (alchemy-kit_202309
`bin/igen.exe`; each library's project runs it once and compiles its `ODLSource.cpp` next to the class
files) wrote, for every class of the library, the boilerplate the class macros of
include/dw4/core/igObjectMacros.h declare. Its templates are readable in the executable's strings and are
DW4's boilerplate statement for statement (docs/engine/reflection-registration.md, "Generated
boilerplate"). This tool is the igen equivalent: it reads what each class registers from the retail
code and writes the library's fragment in igen's shape, as ordinary source.

Per class, in retail address order (the order the linker kept them; functions the retail linker
dead-stripped are not written):

  `_Meta`, `k_<field>` definitions        the metaobject handle and the field handles
  getClassTypeLazy()                       `<Class>_GetOrCreateMetaObject`
  getClassTypeSafe()                       `_Meta`, registered on first use
  retrieveVTablePointer()                  the vtable read through a temporary (a converted class only)
  arkRegister()                            the static-init wrapper of arkRegisterInternal
  arkRegisterInternal()                    the library latch, then igArkRegister's eleven arguments
  arkRegisterInitialize()                  the field adder (instFuncs/names/enumStorage/offsets tables)

`getClassMetaSafe` and `getClassMeta` are inline members (the macros define them); MWCC writes their
out-of-line copies itself where their address is taken.

Where the facts come from:

  * the registrar call (`igMetaObject_RegisterClass`, `jal` in the function holding the class's
    `register_site` in data/reflection.json) gives every role: argument 1 the `_Meta` handle, 2 and 3
    the parent's registrar and accessor, 4 `getClassMetaSafe`, 5 the name, 6 the instance size, 7
    `retrieveVTablePointer`, stack 0 `arkRegisterInitialize`, stack 16 the `regFunctions` list; the
    accessor's jump gives `getClassTypeSafe`, whose call gives `arkRegister`;
  * the field adder's own code (asm/<symbol>.s, traced symbolically) gives the per-field statements,
    the fields reflection lists give the tables, and the field handle each `k_` names;
  * a call or reference to another class's role is written as that class's member when the class is in
    member form (generated in this run, declared with an object macro in config/class-members.tsv, or
    listed in config/converted-classes.tsv), otherwise by its config/SLUS-20836/symbols.txt name (or the
    member config/SLUS-20836/compiler-names.tsv binds the address to).

The metaobject services keep the names the tree gives them (`igMetaObject_CreateFields` for igen's
`metaObject->instantiateAndAppendFields`): SERVICES lists them with igen's spelling, and a service the
tree defines as a member (compiler-names.tsv) is written as the member call.

Usage:
  tools/gen_odl_source.py --library Gui [--out FILE] [--members] [--write-members]
  tools/gen_odl_source.py --class igRenderer [--class ...] [--out FILE]
  tools/gen_odl_source.py --library Gui --list        # the classes, their roles and what cannot be written

A class whose field adder holds a statement the generator has no template for is reported and left out
(`--list` names the statement); nothing is written for it. `--members` prints the config/class-members.tsv
rows the written classes need (the object macro and one `k_` handle per field), `--write-members` puts
them into the table.
"""
import argparse
import bisect
import json
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cxxscope  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GAME = "SLUS-20836"
VADDR_BASE, FILE_BASE = 0x100000, 0x80
IMAGE_LO, IMAGE_HI = 0x100000, 0x600000

# The metaobject services the boilerplate calls: the tree's name, igen's spelling (for the docstring
# and the report) and the role the tracer gives each.
SERVICES = {
    "igMetaObject_RegisterClass": "Gap::Core::igArkRegister",
    "igMetaObject_RunStaticInit": "Gap::Core::igArkRegister (the static-init form)",
    "igMetaObject_Create": "igMetaObject::instantiateFromPoolAnnotated",
    "igMetaObject_CreateInstance": "_Meta->createInstance",
    "Memory_GetAllocatorBySelector": "kIGMemoryPoolMetaData",
    "igMetaObject_GetFieldCount": "metaObject->getMetaFieldCount",
    "igMetaObject_CreateFields": "metaObject->instantiateAndAppendFields",
    "igMetaObject_GetFieldAt": "metaObject->getIndexedMetaField",
    "igMetaObject_NameFields": "metaObject->setMetaFieldBasicPropertiesAndValidateAll",
    "igMetaObject_FindFieldByName": "metaObject->getMetaField",
    "ObjectPointerList_FindIndex": "metaObject->getMetaFields()->find",
    "igMetaObject_FinalizeAndReplaceField": "metaObject->validateAndSetMetaField",
    "igObject_Destroy": "metaField->release",
}

# igObject's virtual slot igen's override clones the inherited field through (createCopy(kDeepCopy)).
CLONE_SLOT = 19
CLONE_NAME = "CloneViaMetadata"

# Saved and argument registers of the EE ABI the tracer follows.
ARG_REGS = ("a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3")
CALLER_SAVED = ("v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
                "t8", "t9", "at")
ROLE_ORDER = ("_instantiateFromPool", "getClassTypeLazy", "getClassTypeSafe", "retrieveVTablePointer", "arkRegister",
              "arkRegisterInternal", "getClassMetaSafe", "arkRegisterInitialize")


# The members the object macros declare, as (return type, parameter types).
ROLE_SIGNATURES = {
    "_instantiateFromPool": (None, ["igMemoryPoolView *"]),
    "getClassTypeLazy": ("igMetaObject *", []),
    "getClassTypeSafe": ("igMetaObject *", []),
    "retrieveVTablePointer": ("void *", []),
    "arkRegister": ("void", []),
    "arkRegisterInternal": ("CallbackArray *", []),
    "getClassMetaSafe": ("igMetaObject *", []),
    "getClassMeta": ("igMetaObject *", []),
    "arkRegisterInitialize": ("void", []),
    "arkRegisterMetaValidate": ("void", []),
}


class Unsupported(Exception):
    """A statement the generator has no igen template for."""


# ----------------------------------------------------------------------------- inputs

def load_symbols(path):
    """-> (sorted [va], {va: (name, size)}, {name: va}) from symbols.txt (`va size name [display]`)."""
    by_va, by_name = {}, {}
    for line in open(path):
        if line.startswith("#") or not line.strip():
            continue
        parts = line.split()
        va, size, name = int(parts[0], 16), int(parts[1], 16), parts[2]
        by_va[va] = (name, size)
        by_name[name] = va
    return sorted(by_va), by_va, by_name


def load_compiler_names(path):
    """{va: mangled} from config/<GAMEID>/compiler-names.tsv (`<mangled> <va> <symbols key>`); empty when
    the table is absent or holds only its header."""
    out = {}
    if path and os.path.exists(path):
        for line in open(path):
            if line.startswith("#") or not line.strip():
                continue
            parts = line.rstrip("\n").split("\t")
            out.setdefault(int(parts[1], 16), parts[0])
    return out


def load_table(path, columns):
    rows = []
    if path and os.path.exists(path):
        with open(path) as fh:
            for line in fh:
                if line.startswith("#") or not line.strip():
                    continue
                rows.append(line.rstrip("\n").split("\t", columns - 1))
    return rows


INSN_RE = re.compile(r"/\* ([0-9a-f]{8}): (\S+)\s*([^*]*?)\s*\*/")


def read_asm(asm_dir, name):
    """[(va, mnemonic, [operands])] of asm/<name>.s (the split's disassembly comments)."""
    path = os.path.join(asm_dir, name + ".s")
    out = []
    for m in INSN_RE.finditer(open(path, errors="replace").read()):
        ops = [o.strip() for o in m.group(3).split(",")] if m.group(3) else []
        out.append((int(m.group(1), 16), m.group(2), ops))
    return out


class Image:
    """The retail executable: words, strings and gp."""

    def __init__(self, path):
        self.data = open(path, "rb").read()
        self.gp = self._gp()

    def _gp(self):
        img = self.data
        e_shoff, = struct.unpack_from("<I", img, 0x20)
        e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", img, 0x2e)
        shstr = struct.unpack_from("<IIIIIIIIII", img, e_shoff + e_shstrndx * e_shentsize)
        for i in range(e_shnum):
            sh = struct.unpack_from("<IIIIIIIIII", img, e_shoff + i * e_shentsize)
            name = img[shstr[4] + sh[0]:img.index(b"\0", shstr[4] + sh[0])]
            if name == b".reginfo":
                return struct.unpack_from("<I", img, sh[4] + 20)[0]
        return None

    def word(self, va):
        off = va - VADDR_BASE + FILE_BASE
        if not 0 <= off <= len(self.data) - 4:
            return None
        return struct.unpack_from("<I", self.data, off)[0]

    def string(self, va):
        """The NUL-terminated printable string at `va`, or None."""
        off = va - VADDR_BASE + FILE_BASE
        if not 0 <= off < len(self.data):
            return None
        end = self.data.find(b"\0", off, off + 512)
        if end <= off:
            return None
        raw = self.data[off:end]
        if all(32 <= b < 127 for b in raw):
            return raw.decode("ascii")
        return None


# ----------------------------------------------------------------------------- the tracer

def s16(text):
    v = int(text, 0)
    return v - 0x10000 if 0x8000 <= v <= 0xFFFF and not text.startswith("-") else v


def mem_operand(text):
    m = re.match(r"(-?(?:0x)?[0-9a-fA-F]+)\((\w+)\)", text)
    return int(m.group(1), 0), m.group(2)


def add(value, k):
    """`value + k` for the tracer's values."""
    if k == 0:
        return value
    if value is None:
        return None
    if value[0] == "k":
        return ("k", (value[1] + k) & 0xFFFFFFFF)
    if value[0] == "sp":
        return ("sp", value[1] + k)
    if value[0] == "add":
        return ("add", value[1], value[2] + k)
    return ("add", value, k)


def trace(insns, image):
    """Run a straight-line function symbolically -> [event].

    Values are tuples: ("k", n) a constant, ("sp", off) a stack address, ("g", va) the word loaded from
    a global, ("ret", i) the result of call i, ("fld", base, off) a word loaded through a value,
    ("add", value, k), ("f", bits) a float constant, ("x",) anything else. Events are calls (target,
    the eight argument registers, the stack words), virtual calls through `jalr`, stores through a
    non-stack base, and conditional branches; a call that a branch can skip is marked `cond`.
    """
    regs = {"zero": ("k", 0), "sp": ("sp", 0), "gp": ("k", image.gp)}
    fregs = {}
    stack = {}
    events = []
    cond_until = None
    i = 0

    def get(r):
        return regs.get(r, ("x",))

    def step(va, mn, ops):
        nonlocal cond_until
        if mn == "nop":
            return
        if mn == "lui":
            regs[ops[0]] = ("k", (int(ops[1], 0) << 16) & 0xFFFFFFFF)
        elif mn in ("addiu", "daddiu"):
            regs[ops[0]] = add(get(ops[1]), s16(ops[2]))
        elif mn == "ori":
            v = get(ops[1])
            regs[ops[0]] = ("k", v[1] | int(ops[2], 0)) if v[0] == "k" else ("x",)
        elif mn == "li":
            regs[ops[0]] = ("k", int(ops[1], 0) & 0xFFFFFFFF)
        elif mn == "move":
            regs[ops[0]] = get(ops[1])
        elif mn in ("addu", "daddu"):
            a, b = get(ops[1]), get(ops[2])
            if b == ("k", 0):
                regs[ops[0]] = a
            elif a == ("k", 0):
                regs[ops[0]] = b
            elif b[0] == "k":
                regs[ops[0]] = add(a, b[1])
            else:
                regs[ops[0]] = ("x",)
        elif mn in ("lw", "lh", "lhu", "lb", "lbu", "ld", "lq"):
            off, base = mem_operand(ops[1])
            b = get(base)
            if mn in ("ld", "lq") and b[0] == "sp":
                regs[ops[0]] = ("x",)   # epilogue restore
            elif b[0] == "k":
                # a global's value, tagged with the load: a re-read is a different value
                regs[ops[0]] = ("g", (b[1] + off) & 0xFFFFFFFF, va)
            elif b[0] == "sp":
                regs[ops[0]] = stack.get(b[1] + off, ("x",))
            elif mn == "lw":
                regs[ops[0]] = ("fld", b, off)
            else:
                regs[ops[0]] = ("x",)
        elif mn == "lwc1":
            off, base = mem_operand(ops[1])
            b = get(base)
            fregs[ops[0]] = ("f", image.word((b[1] + off) & 0xFFFFFFFF)) if b[0] == "k" else ("x",)
        elif mn == "mtc1":
            v = get(ops[0])
            fregs[ops[1]] = ("f", v[1]) if v[0] == "k" else ("x",)
        elif mn in ("sw", "sh", "sb", "sd", "sq", "swc1"):
            off, base = mem_operand(ops[1])
            b = get(base)
            v = fregs.get(ops[0], ("x",)) if mn == "swc1" else get(ops[0])
            if b[0] == "sp":
                stack[b[1] + off] = v
            else:
                width = {"sw": 4, "sh": 2, "sb": 1, "sd": 8, "sq": 16, "swc1": "f"}[mn]
                events.append({"k": "store", "va": va, "w": width, "base": b, "off": off, "val": v})
        elif mn in ("jal", "j", "jalr"):
            here = get("sp")[1] if get("sp")[0] == "sp" else 0
            event = {"k": "call" if mn != "jalr" else "vcall", "va": va,
                     "target": int(ops[0], 0) if mn != "jalr" else get(ops[-1]),
                     "args": [get(r) for r in ARG_REGS],
                     "fargs": [fregs.get("$f%d" % n, ("x",)) for n in range(12, 20)],
                     "stack": {off - here: v for off, v in stack.items()}, "frame": dict(stack),
                     "cond": cond_until is not None and va < cond_until, "tail": mn == "j"}
            events.append(event)
            for r in CALLER_SAVED:
                regs[r] = ("x",)
            regs["v0"] = ("ret", len(events) - 1)
        elif mn in ("bnez", "beqz", "beq", "bne", "bgez", "bltz", "blez", "bgtz", "b"):
            target = int(ops[-1], 0)
            events.append({"k": "branch", "va": va, "op": mn, "val": get(ops[0]) if mn != "b" else None,
                           "target": target})
            cond_until = target if cond_until is None or target > cond_until else cond_until
        elif mn == "jr":
            return "end"
        elif ops:
            # arithmetic the boilerplate only uses on a value it then tests (the release mask)
            dest = ops[0]
            if dest in regs or re.match(r"[a-z][0-9a-z]$", dest):
                regs[dest] = ("op", mn, get(ops[1]) if len(ops) > 1 else None)
        return None

    while i < len(insns):
        va, mn, ops = insns[i]
        if mn in ("jal", "j", "jalr", "jr") or mn in ("bnez", "beqz", "beq", "bne", "bgez", "bltz",
                                                         "blez", "bgtz", "b"):
            if i + 1 < len(insns):
                step(*insns[i + 1])   # the delay slot runs before the transfer
            end = step(va, mn, ops)
            i += 2
            if end or mn == "j":
                break
            continue
        step(va, mn, ops)
        i += 1
    return events


# ----------------------------------------------------------------------------- roles

class Library:
    """Every reflected class's boilerplate roles, read from the retail registrars."""

    def __init__(self, root=ROOT, asm_dir=None, elf=None, reflection=None, symbols=None):
        self.root = root
        self.asm_dir = asm_dir or os.path.join(root, "asm")
        self.image = Image(elf or os.path.join(root, "orig", GAME, "SLUS_208.36"))
        self.reflection = json.load(open(reflection or os.path.join(root, "data", "reflection.json")))
        self.sorted_va, self.by_va, self.by_name = load_symbols(
            symbols or os.path.join(root, "config", GAME, "symbols.txt"))
        self.svc = {name: self.by_name.get(name) for name in SERVICES}
        self.svc_by_va = {va: name for name, va in self.svc.items() if va is not None}
        self.parent = {row[0]: row[1].split("\t")[0] for row in
                       load_table(os.path.join(root, "data", "class-hierarchy.tsv"), 2) if len(row) == 2}
        self.fields_of = {info["class"]: info.get("fields") or [] for info in self.reflection["classes"].values()}
        self.classes = {}
        self.meta_owner = {}
        self.role_at = {}
        self.problems = {}
        seen = set()
        for handle, info in sorted(self.reflection["classes"].items()):
            cls = info["class"]
            if cls in seen or not info.get("register_site"):
                continue
            seen.add(cls)
            try:
                roles = self._roles(cls, info)
            except (Unsupported, OSError, KeyError, IndexError) as exc:
                self.problems[cls] = str(exc)
                continue
            self.classes[cls] = roles
            self.meta_owner[roles["meta"]] = cls
            for role in ROLE_ORDER:
                if roles.get(role):
                    self.role_at[roles[role]] = (cls, role)
        # a parent accessor is the published getClassMeta copy: `return <Parent>::_Meta`
        for cls, roles in self.classes.items():
            acc = roles["args"]["parentAccessor"]
            if acc and acc not in self.role_at:
                owner = self._returns_meta(acc)
                if owner:
                    self.role_at[acc] = (owner, "getClassMeta")
        self._data_names = None

    def name_at(self, va):
        return self.by_va[va][0] if va in self.by_va else None

    def containing(self, va):
        i = bisect.bisect_right(self.sorted_va, va) - 1
        if i >= 0:
            start = self.sorted_va[i]
            if va < start + self.by_va[start][1]:
                return start
        return None

    def asm(self, va):
        return read_asm(self.asm_dir, self.name_at(va))

    def _returns_meta(self, va):
        """The class whose `_Meta` the accessor at `va` returns (`lui; jr ra; lw v0,lo`), or None."""
        try:
            insns = self.asm(va)
        except OSError:
            return None
        if len(insns) > 4:
            return None
        regs, loaded = {}, None
        for _va, mn, ops in insns:
            if mn == "lui":
                regs[ops[0]] = int(ops[1], 0) << 16
            elif mn == "lw" and ops[0] == "v0":
                off, base = mem_operand(ops[1])
                if base in regs:
                    loaded = (regs[base] + off) & 0xFFFFFFFF
        return self.meta_owner.get(loaded)

    def _roles(self, cls, info):
        site = int(info["register_site"], 16)
        reg = self.containing(site)
        if reg is None:
            raise Unsupported("no symbol holds the register site 0x%x" % site)
        events = trace(self.asm(reg), self.image)
        calls = [e for e in events if e["k"] == "call"]
        regcall = [e for e in calls if e["target"] == self.svc["igMetaObject_RegisterClass"]]
        if not regcall:
            raise Unsupported("registrar 0x%x does not call igMetaObject_RegisterClass" % reg)
        rc = regcall[0]
        a = rc["args"]

        def const(v, what):
            if v[0] != "k":
                raise Unsupported("registrar argument %s is not a constant" % what)
            return v[1]

        args = {
            "abstract": const(a[0], "abstract"),
            "meta": const(a[1], "meta"),
            "parentRegister": const(a[2], "parent registrar"),
            "parentAccessor": const(a[3], "parent accessor"),
            "metaSafe": const(a[4], "accessor"),
            "name": const(a[5], "name"),
            "size": const(a[6], "size"),
            "vtable": const(a[7], "vtable getter"),
            "initialize": const(rc["stack"].get(0, ("k", 0)), "field adder"),
            "user": const(rc["stack"].get(8, ("k", 0)), "user callback"),
            "regFunctions": const(rc["stack"].get(16, ("k", 0)), "callback list"),
        }
        latch = [e["target"] for e in calls if e is not rc and not e["cond"]]
        roles = {"class": cls, "info": info, "args": args, "meta": args["meta"],
                 "arkRegisterInternal": reg, "latch": latch[0] if latch else None,
                 "getClassMetaSafe": args["metaSafe"] or None,
                 "retrieveVTablePointer": args["vtable"] or None,
                 "arkRegisterInitialize": args["initialize"] or None}
        if self.image.string(args["name"]) != cls:
            raise Unsupported("registrar names %r" % self.image.string(args["name"]))
        # getClassMetaSafe jumps to getClassTypeSafe, which calls arkRegister when the handle is not valid
        safe = None
        if roles["getClassMetaSafe"]:
            ev = trace(self.asm(roles["getClassMetaSafe"]), self.image)
            targets = [e["target"] for e in ev if e["k"] == "call"]
            safe = targets[0] if targets else None
        roles["getClassTypeSafe"] = safe
        if safe:
            ev = trace(self.asm(safe), self.image)
            targets = [e["target"] for e in ev if e["k"] == "call"]
            roles["arkRegister"] = targets[0] if targets else None
        # getClassTypeLazy, when the linker kept it, sits just before getClassTypeSafe, and
        # _instantiateFromPool just before both
        if safe:
            first = safe
            prev = self.previous(first)
            if prev is not None and self._is_lazy(prev, args["meta"]):
                roles["getClassTypeLazy"] = first = prev
            prev = self.previous(first)
            if prev is not None and roles.get("arkRegister") and \
                    self._is_instantiate(prev, args["meta"], roles["arkRegister"]):
                roles["_instantiateFromPool"] = prev
        return roles

    def previous(self, va):
        i = self.sorted_va.index(va)
        return self.sorted_va[i - 1] if i else None

    def _events(self, va):
        try:
            return trace(self.asm(va), self.image)
        except OSError:
            return []

    def _is_lazy(self, va, meta):
        ev = self._events(va)
        targets = [e["target"] for e in ev if e["k"] == "call"]
        stores = [e for e in ev if e["k"] == "store" and e["base"][0] == "k"
                  and (e["base"][1] + e["off"]) & 0xFFFFFFFF == meta]
        return self.svc["igMetaObject_Create"] in targets and bool(stores)

    def _is_instantiate(self, va, meta, ark_register):
        """`arkRegister(); return _Meta->createInstance(pool);`"""
        calls = [e for e in self._events(va) if e["k"] == "call"]
        return len(calls) == 2 and calls[0]["target"] == ark_register \
            and calls[1]["target"] == self.svc["igMetaObject_CreateInstance"] \
            and is_global(calls[1]["args"][0], meta)

    def library_of(self, cls):
        """`Gui` for a class whose registrar calls GuiLibrary_MarkRegistered; the latch's own symbol name
        while the latch has no library name."""
        latch = self.classes[cls]["latch"]
        name = self.name_at(latch) if latch else None
        m = re.match(r"(\w+?)Library_MarkRegistered$", name or "")
        return m.group(1) if m else name

    def unit_names(self, va):
        """{address: name} the unit holding `va` binds in config/<GAMEID>/unit-objects.json."""
        self.data_name(0)
        i = bisect.bisect_right(self._unit_starts, va) - 1
        return self._unit_rows[self._unit_starts[i]] if i >= 0 else {}

    def data_name(self, va):
        """The tree's name of the datum at `va` (a unit's `data` row, else config/<GAMEID>/data-names.tsv)."""
        if self._data_names is None:
            self._data_names = {}
            cfg = os.path.join(self.root, "config", GAME)
            for row in load_table(os.path.join(cfg, "data-names.tsv"), 3):
                if len(row) >= 2:
                    self._data_names[int(row[0], 16)] = row[1]
            path = os.path.join(cfg, "unit-objects.json")
            self._unit_rows = {}
            if os.path.exists(path):
                for key, entry in json.load(open(path)).items():
                    for name, at in (entry.get("data") or {}).items():
                        self._data_names[int(at, 16)] = name
                    bound = self._unit_rows.setdefault(int(key, 16), {})
                    for part in ("emitted", "externals", "duplicates", "data"):
                        for name, at in (entry.get(part) or {}).items():
                            bound.setdefault(int(at, 16), name)
            self._unit_starts = sorted(self._unit_rows)
        return self._data_names.get(va)

    def library_classes(self, lib):
        out = [c for c in self.classes if self.library_of(c) == lib]
        return sorted(out, key=lambda c: min(v for v in role_vas(self.classes[c])))


def role_vas(roles):
    return [roles[r] for r in ROLE_ORDER if roles.get(r)]


# ----------------------------------------------------------------------------- declarations

class Prototypes:
    """Parameter types of the functions the boilerplate calls, read from the tree's headers."""

    def __init__(self, root):
        texts = []
        for base in ("include", "src"):
            for dirpath, _dirs, files in os.walk(os.path.join(root, base)):
                for f in files:
                    if f.endswith(".h"):
                        texts.append(open(os.path.join(dirpath, f), errors="replace").read())
        self.text = "\n".join(texts)
        self.cache = {}

    def params(self, name):
        return self.signature(name)[1]

    def signature(self, name):
        """-> (return type, [parameter type]) of the first declaration of `name`, or (None, None)."""
        if name not in self.cache:
            m = re.search(r"(?m)^([^\n;{}()#]*?)\b%s\s*\(([^;{}]*?)\)\s*;" % re.escape(name), self.text)
            out = (None, None)
            if m:
                inner = re.sub(r"\s+", " ", m.group(2)).strip()
                ret = re.sub(r'^(extern\s+"C"\s+|extern\s+|static\s+|inline\s+)+', "", m.group(1).strip())
                out = (param_type(ret + " x"),
                       [] if inner in ("", "void") else [param_type(p) for p in split_params(inner)])
            self.cache[name] = out
        return self.cache[name]


def split_params(text):
    out, depth, cur = [], 0, ""
    for ch in text:
        if ch == "," and depth == 0:
            out.append(cur)
            cur = ""
            continue
        depth += ch in "(<"
        depth -= ch in ")>"
        cur += ch
    out.append(cur)
    return [p.strip() for p in out]


def param_type(decl):
    """`struct igMetaField *self` -> `igMetaField *`; `const int &value` -> `const int &`."""
    decl = re.sub(r"\bstruct\s+", "", decl).strip()
    m = re.match(r"(.*?[\s\*&])\s*([A-Za-z_]\w*)$", decl)
    t = m.group(1) if m and m.group(1).strip() not in ("", "const", "unsigned", "signed") else decl
    t = re.sub(r"\s+", " ", t).strip()
    return re.sub(r"\s*([\*&])", r" \1", t).replace("* *", "**")


class Sources:
    """The tree's current definition of a function, for one the generator keeps as it is."""

    def __init__(self, root):
        self.files = []
        for dirpath, _dirs, files in os.walk(os.path.join(root, "src")):
            if os.sep + "third_party" in dirpath:
                continue
            self.files.extend(os.path.join(dirpath, f) for f in sorted(files)
                              if f.endswith((".c", ".cpp", ".inc")))
        self.texts = {}

    def text(self, path):
        if path not in self.texts:
            self.texts[path] = open(path, errors="replace").read()
        return self.texts[path]

    def locate(self, name):
        """-> (path, start, end) of the definition of `name` in src/, or None."""
        sys.path.insert(0, os.path.join(ROOT, "tools"))
        import units
        for path in self.files:
            text = self.text(path)
            if name not in text:
                continue
            for nm, start, end in units.definitions(text):
                if nm == name:
                    return path, start, end
        return None

    def definition(self, name):
        found = self.locate(name)
        if found is None:
            raise Unsupported("%s has no definition in src/ to keep" % name)
        path, start, end = found
        return self.text(path)[start:end].strip("\n").split("\n")

    def unit_with_fragment(self, latch, fragment, root=ROOT):
        """A compilable text for `fragment` in its library's unit: the unit file up to its first
        fragment (its headers, pragmas and front data), the library latch the boilerplate calls, then
        the fragment. None when no unit file defines the latch."""
        found = self.locate(latch)
        if found is None:
            return None
        path, start, end = found
        holder = os.path.relpath(path, root)
        sys.path.insert(0, os.path.join(ROOT, "tools"))
        import units
        text = self.text(path)
        starts = [s for _n, s, _e in units.definitions(text)]
        # what precedes the holder's first definition (its data), then the latch itself
        latch_part = text[:min(starts) if starts else len(text)] + text[start:end] + "\n"
        if holder.endswith(".inc"):
            line = '#include "%s"' % holder
            unit = next((p for p in self.files if p.endswith((".c", ".cpp")) and line in self.text(p)), None)
            if unit is None:
                return None
            utext = self.text(unit)
            first = re.search(r'(?m)^\s*#include "[^"]+\.inc"', utext)
            prefix = utext[:first.start()] + latch_part
        else:
            prefix = latch_part
        out = prefix + fragment
        if prefix.count("#pragma push") > prefix.count("#pragma pop"):
            out += "#pragma pop\n"
        return out


REFLECTED_STRUCT_RE = re.compile(r"typedef struct (\w+)\b[^{]*\{(.*?)\n\} \1;", re.S)
MEMBER_LINE_RE = re.compile(r"^\s+(.+?)\s+(\**)(\w+)(\[\d+\])?;\s+/\* \+(\d+)\s", re.M)


def reflected_layouts(path):
    """{struct: {offset: (member, C type)}} from include/dw4/support/reflected.h."""
    out = {}
    text = open(path).read()
    for m in REFLECTED_STRUCT_RE.finditer(text):
        fields = out.setdefault(m.group(1), {})
        for f in MEMBER_LINE_RE.finditer(m.group(2)):
            fields.setdefault(int(f.group(5)), (f.group(3), f.group(1) + (" " + f.group(2) if f.group(2) else "")))
    return out


# ----------------------------------------------------------------------------- rendering

def float_literal(bits):
    value = struct.unpack("<f", struct.pack("<I", bits))[0]
    text = repr(value)
    if "e" not in text and "." not in text:
        text += ".0"
    return text + "f"


def field_handle_name(field):
    return "k_" + field.lstrip("_")


class Writer:
    def __init__(self, lib, members_form, converted, compiler_names, prototypes, layouts, sources,
                 member_rows=None):
        self.lib = lib
        self.members_form = members_form          # classes written as members
        self.converted = converted                # {class: Gap namespace}
        self.compiler_names = compiler_names
        self.protos = prototypes
        self.layouts = layouts
        self.sources = sources
        self.member_rows = member_rows or {}      # {class: [class-members.tsv declaration]}
        self.handles_of = {}
        self.undeclared = set()

    def member_signature(self, qualified):
        """-> [parameter type] of the non-static member function `Gap::<lib>::<class>::<member>` as its
        class's class-members.tsv row declares it (its own class or the nearest ancestor that does), or
        None when no row declares it or it is static."""
        m = re.match(r"Gap::\w+::(\w+)::(\w+)$", qualified)
        if not m:
            return None
        cls, member = m.groups()
        while cls:
            for decl in self.member_rows.get(cls, ()):
                decl = re.sub(r"^\s*(public|protected|private)\s*:\s*", "", decl)
                d = re.match(r"((?:\w+\s+)*)[\w:<>\s\*&]*?\b%s\s*\(([^)]*)\)" % re.escape(member), decl)
                if not d:
                    continue
                if "static" in d.group(1).split():
                    return None
                inner = d.group(2).strip()
                return [] if inner in ("", "void") else [param_type(p) for p in split_params(inner)]
            cls = self.lib.parent.get(cls) if self.lib is not None else None
        return None

    def derives(self, cls, base):
        """Is `cls` the class `base` or one of its descendants?"""
        while cls:
            if cls == base:
                return True
            cls = self.lib.parent.get(cls) if self.lib is not None else None
        return False

    # --- names

    def qualified(self, cls):
        lib = self.converted.get(cls)
        return "Gap::%s::%s" % (lib, cls) if lib else cls

    def function(self, va, here=None):
        """The source spelling of a reference to the function at `va` from class `here`'s code."""
        role = self.lib.role_at.get(va)
        if role and role[0] in self.members_form and not (role[1] == "retrieveVTablePointer"
                                                           and role[0] not in self.converted):
            cls, member = role
            if cls == here:
                return member
            return "%s::%s" % (self.qualified(cls), member)
        if va in self.compiler_names:
            demangled = demangle_name(self.compiler_names[va])
            if demangled:
                return demangled
        if here is not None:
            # the name the class's own unit binds the address to (another unit's copy of an
            # accessor is often known there under a name of its own)
            alias = self.lib.unit_names(self.lib.classes[here]["arkRegisterInternal"]).get(va)
            if alias:
                return alias
        name = self.lib.name_at(va)
        if name is None:
            raise Unsupported("no symbol at 0x%x" % va)
        return name

    def callback(self, va, here, typedef, want):
        """A function the registrar is handed, cast to the registrar's `typedef` when its own type
        differs from `want` (return type, parameter types)."""
        name = self.function(va, here)
        role = self.lib.role_at.get(va)
        macro = re.match(r"Gap::\w+::(\w+)::(\w+)$", name)
        if role and (name == role[1] or name.endswith("::" + role[1])):
            have = ROLE_SIGNATURES.get(role[1])
        elif macro and macro.group(2) in ROLE_SIGNATURES:
            # a member the object macros declare (a metafield's arkRegisterMetaValidate), bare in its class
            have = ROLE_SIGNATURES[macro.group(2)]
            if macro.group(1) == here:
                name = macro.group(2)
        else:
            have = self.protos.signature(name)
            if have == (None, None) and "::" not in name:
                self.undeclared.add(name)
        return name if have == want else "(%s)%s" % (typedef, name)

    # --- the registrar

    def register(self, cls, roles):
        a = roles["args"]
        lines = []
        reg_list = []
        if a["regFunctions"]:
            at = a["regFunctions"]
            while True:
                w = self.lib.image.word(at)
                if not w:
                    break
                reg_list.append(self.callback(w, cls, "igMetaObjectCallback", ("void", [])))
                at += 4
            reg_list.append("0")
        latch = self.lib.name_at(roles["latch"]) if roles["latch"] else None
        lines.append("CallbackArray *%s::arkRegisterInternal()" % cls)
        lines.append("{")
        if reg_list:
            lines.append("    static igMetaObjectCallback regFunctions[] = { %s };" % ", ".join(reg_list))
            lines.append("")
        if latch:
            lines.append("    %s();" % latch)
        vtable = self.callback(a["vtable"], cls, "igMetaObjectGetVTableFunction", ("int", [])) \
            if a["vtable"] else "0"
        args = [
            "true" if a["abstract"] else "false",
            "&_Meta",
            self.callback(a["parentRegister"], cls, "igMetaObjectRegisterFunction", ("CallbackArray *", []))
            if a["parentRegister"] else "0",
            self.callback(a["parentAccessor"], cls, "igMetaObjectGetFunction", ("igMetaObject *", []))
            if a["parentAccessor"] else "0",
            "(igMetaObjectCallback)getClassMetaSafe",
            '"%s"' % cls,
            "sizeof(%s)" % cls if roles.get("sized") else "%d" % a["size"],
            vtable,
            "&arkRegisterInitialize" if a["initialize"] else "0",
            self.callback(a["user"], cls, "igMetaObjectCallback", ("void", [])) if a["user"] else "0",
            "regFunctions" if reg_list else "0",
        ]
        lines.append("    return igMetaObject_RegisterClass(")
        for i, arg in enumerate(args):
            lines.append("        %s%s" % (arg, "," if i + 1 < len(args) else ""))
        lines.append("    );")
        lines.append("}")
        return lines

    # --- the field adder

    def initialize(self, cls, roles, handles):
        info = roles["info"]
        # the field order of the tables (reflection lists them as the field adder's tables do)
        fields = list(info.get("fields") or [])
        events = trace(self.lib.asm(roles["arkRegisterInitialize"]), self.lib.image)
        svc = self.lib.svc
        calls = [e for e in events if e["k"] == "call"]
        # igen caches _Meta in a local and counts the inherited fields first; an adder without fields
        # (a class that only sets a metaobject property) reads _Meta where it uses it
        meta = next((v for e in events for v in values_of(e) for g in globals_in(v)
                     if is_global(g, roles["meta"]) for v in [g]), None)
        counted = bool(calls) and calls[0]["target"] == svc["igMetaObject_GetFieldCount"] \
            and meta is not None and calls[0]["args"][0] == meta
        if fields and not counted:
            raise Unsupported("the adder does not start with the field count of _Meta")
        start = ("ret", events.index(calls[0])) if counted else None
        ctx = {"meta": meta, "start": start, "cls": cls, "names": {}, "types": {}, "used": set(),
               "own_meta": roles["meta"]}
        if meta is not None:
            ctx["names"][meta] = "metaObject"
            ctx["types"][meta] = "igMetaObject"
        if counted:
            ctx["names"][start] = "start"
        # results consumed by a later event are written inline there
        consumed = {}
        for i, e in enumerate(events):
            for v in values_of(e):
                for r in rets_in(v):
                    consumed.setdefault(r, i)
        body = []
        block = None          # the open per-field block: (kind, lines)
        tables = None
        i = 0
        while i < len(events):
            e = events[i]
            if e["k"] == "branch":
                i += 1
                continue
            if e["k"] == "call" and e["target"] == svc["igMetaObject_GetFieldCount"]:
                i += 1
                continue
            if e["k"] == "call" and e["target"] == svc["igMetaObject_CreateFields"]:
                if e["args"][0] != meta or e["args"][2][0] != "k":
                    raise Unsupported("CreateFields with an unexpected argument")
                count = e["args"][2][1]
                ctors = self.word_table(e["args"][1][1], count)
                expect = [f["ctor"] for f in fields]
                if ctors != expect[:count] or count != len(fields):
                    raise Unsupported("the constructor table does not list the reflected fields")
                body.append("    igMetaObject_CreateFields(metaObject, instFuncs, %d);" % count)
                i += 1
                continue
            if e["k"] == "call" and e["target"] == svc["igMetaObject_NameFields"]:
                close(body, block)
                block = None
                a = e["args"]
                if a[0] != meta or a[4] != start:
                    raise Unsupported("NameFields with an unexpected argument")
                tables = self.name_tables(cls, fields, a[1][1], a[2][1], a[3][1], handles)
                body.append("    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);")
                i += 1
                continue
            if e["k"] == "call" and e["target"] == svc["igMetaObject_GetFieldAt"]:
                a = e["args"]
                idx = field_index(a[1], start)
                if a[0] != meta or idx is None or idx >= len(fields):
                    raise Unsupported("GetFieldAt with an unexpected index")
                close(body, block)
                mtype = self.field_type(fields[idx]["type"])
                ctx["names"][("ret", i)] = "metaField"
                ctx["types"][("ret", i)] = mtype
                block = ["    {", "        %s *metaField = (%s *)igMetaObject_GetFieldAt(metaObject, start + %d);"
                         % (mtype, mtype, idx)]
                i += 1
                continue
            if e["k"] == "call" and e["target"] == svc["igMetaObject_FindFieldByName"]:
                i = self.override(events, i, ctx, body, block, handles)
                block = None
                continue
            # a statement inside the open block (or at function level)
            if e["k"] == "call" and consumed.get(("ret", i)) is not None:
                i += 1        # written where its result is used
                continue
            line = self.statement(e, i, events, ctx)
            (block if block is not None else body).append(("        " if block is not None else "    ") + line)
            i += 1
        if counted and tables is None:
            raise Unsupported("the adder never names its fields")
        out = ["void %s::arkRegisterInitialize()" % cls, "{"]
        if counted:
            out.extend(tables)
        if meta is not None:
            out.append("    igMetaObject *metaObject = _Meta;\t// cache in a local variable")
        if counted:
            out.append("    int start = igMetaObject_GetFieldCount(metaObject);")
        if meta is not None:
            out.append("")
        out.extend(body)
        out.append("}")
        return out

    def word_table(self, va, count):
        return [self.lib.image.word(va + 4 * k) for k in range(count)]

    def field_type(self, metafield):
        """The metafield class's reflected struct, or its nearest ancestor's when it has none."""
        cls = metafield
        while cls and cls not in self.layouts:
            cls = self.lib.parent.get(cls)
        return cls or "igMetaField"

    def name_tables(self, cls, fields, names_va, handles_va, offsets_va, handles):
        n = len(fields)
        names = [self.lib.image.string(w) for w in self.word_table(names_va, n)]
        if names != [f["name"] for f in fields]:
            raise Unsupported("the name table does not list the reflected fields")
        hvas = self.word_table(handles_va, n)
        if hvas != [f["desc"] for f in fields]:
            raise Unsupported("the handle table does not list the reflected handles")
        offsets = [struct.unpack("<i", struct.pack("<I", w))[0] for w in self.word_table(offsets_va, n)]
        if offsets != [f["offset"] for f in fields]:
            raise Unsupported("the offset table does not list the reflected offsets")
        # a factory declared with its own class or argument type is cast to the table's type
        ctors = [self.callback(f["ctor"], cls, "FieldFactory", ("igMetaField *", ["igMemoryPoolView *"]))
                 for f in fields]
        for f in fields:
            handles.setdefault(f["desc"], field_handle_name(f["name"]))
        return [
            "    static FieldFactory instFuncs[] = { %s };" % ", ".join(ctors),
            "    static const char *names[] = { %s };" % ", ".join('"%s"' % f["name"] for f in fields),
            "    static igMetaField **enumStorage[] = { %s };"
            % ", ".join("&" + field_handle_name(f["name"]) for f in fields),
            "    static int offsets[] = { %s };" % ", ".join(str(o) for o in offsets),
        ]

    def override(self, events, i, ctx, body, block, handles):
        """igen's override of an inherited field: find it, clone it, set it, put the copy in its place."""
        svc = self.lib.svc
        close(body, block)
        find = events[i]
        name = self.lib.image.string(find["args"][1][1]) if find["args"][1][0] == "k" else None
        if find["args"][0] != ctx["meta"] or name is None:
            raise Unsupported("an override with an unexpected lookup")
        found = ("ret", i)
        seq = [e for e in events[i + 1:]]
        # FindIndex(metaObject->_metaFields, metaField)
        j = i + 1
        e = events[j]
        if not (e["k"] == "call" and e["target"] == svc["ObjectPointerList_FindIndex"]
                and e["args"][0] == ("fld", ctx["meta"], 40) and e["args"][1] == found):
            raise Unsupported("an override without the index lookup")
        index = ("ret", j)
        j += 1
        e = events[j]
        if not (e["k"] == "vcall" and e["target"] == ("fld", ("fld", found, 0), 8 + 4 * CLONE_SLOT)
                and e["args"][0] == found and e["args"][1][0] == "k"):
            raise Unsupported("an override without the clone")
        copy_mode = e["args"][1][1]
        clone = ("ret", j)
        mtype = self.override_type(ctx["cls"], name)
        ctx["names"][clone] = "metaField"
        ctx["types"][clone] = mtype
        ctx["names"][found] = "metaField"
        ctx["types"][found] = mtype
        ctx["names"][index] = "metaIndex"
        lines = ["    {",
                 "        %s *metaField = (%s *)igMetaObject_FindFieldByName(metaObject, \"%s\");"
                 % (mtype, mtype, name),
                 "        int metaIndex = ObjectPointerList_FindIndex("
                 "(__internalNonRefCountedObjectList *)metaObject->_metaFields, (int)metaField);",
                 "        metaField = (%s *)((igObjectDispatchView *)metaField)->%s(%d);"
                 % (mtype, CLONE_NAME, copy_mode)]
        j += 1
        while j < len(events):
            e = events[j]
            if e["k"] == "branch":
                j += 1
                continue
            if e["k"] == "call" and e["target"] == svc["igMetaObject_FinalizeAndReplaceField"]:
                if e["args"] != [ctx["meta"], index, clone] + e["args"][3:]:
                    raise Unsupported("an override replaced with unexpected arguments")
                lines.append("        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, %s);"
                             % self.cast_to("igMetaField *", "metaField", mtype + " *"))
                j += 1
                # the copy's release: refcount store, the masked test, the destroy call
                if j < len(events) and events[j]["k"] == "store" and events[j]["base"] == clone \
                        and events[j]["off"] == 4:
                    j += 1
                    while j < len(events) and events[j]["k"] == "branch":
                        j += 1
                    e = events[j]
                    if not (e["k"] == "call" and e["target"] == svc["igObject_Destroy"] and e["cond"]):
                        raise Unsupported("an override without the release of its copy")
                    lines.extend(["        metaField->_refCount = metaField->_refCount - 1;",
                                  "        if (((unsigned long long)(long long)metaField->_refCount & 0x7fffffULL) == 0) {",
                                  "            igObject_Destroy(%s);"
                                  % self.cast_to("igObject *", "metaField", mtype + " *"),
                                  "        }"])
                    j += 1
                lines.append("    }")
                body.extend(lines)
                return j
            if e["k"] == "store" and e["base"] == clone and e["off"] == 28 and e["val"][0] == "k":
                # the overridden field's handle: the class's own k_<field>
                handles.setdefault(e["val"][1], field_handle_name(name))
                lines.append("        metaField->_externalEnumStorage = (int)&%s;" % field_handle_name(name))
                j += 1
                continue
            if e["k"] == "call" and any(v == ("ret", j) for k2 in range(j + 1, len(events))
                                        for v in values_of(events[k2])):
                j += 1
                continue
            lines.append("        " + self.statement(e, j, events, ctx))
            j += 1
        raise Unsupported("an override that is never put in place")

    def override_type(self, cls, field):
        """The metafield class of the inherited field `field`, from the ancestor that reflects it."""
        base = self.lib.parent.get(cls)
        while base:
            for f in self.lib.fields_of.get(base, ()):
                if f["name"] == field:
                    return self.field_type(f["type"])
            base = self.lib.parent.get(base)
        return "igMetaField"

    def cast_to(self, want, expr, have):
        """`expr` cast to `want`, a C prototype's parameter type. The fragment is written inside Gap's
        namespaces, where a converted class's bare name is its Gap class: the flat struct the C service
        takes is spelled `::Class` there."""
        if want is None or have is None or norm_type(want) == norm_type(have):
            return expr
        want = re.sub(r"(?<![\w:])([A-Za-z_]\w*)", lambda m: "::" + m.group(1)
                      if m.group(1) in self.converted else m.group(1), want.strip())
        return "(%s)%s" % (want, expr)

    def statement(self, e, i, events, ctx):
        if e["k"] == "call":
            return self.call_expr(e, i, events, ctx) + ";"
        if e["k"] == "store":
            base = e["base"]
            if base in ctx["names"]:
                name, owner = ctx["names"][base], ctx["types"].get(base, "igMetaField")
            elif is_global(base, ctx["own_meta"]):
                name, owner = "_Meta", "igMetaObject"
            else:
                raise Unsupported("a store through an unknown base")
            member, ctype = self.member_at(owner, e["off"], e["w"])
            val = e["val"]
            if val[0] == "k" and val[1] in self.lib.by_va and "*" not in ctype and "(" not in ctype:
                # a function stored in a member reflection types as a word: the member is the kit's
                # function pointer (setGetMetaEnumFunction, setInvarianceFunction), so the store is
                # one of a pointer -- as a word MWCC would keep the address in a register for a reuse
                return "*(void (**)())&%s->%s = (void (*)())%s;" % (name, member,
                                                                   self.function(val[1], ctx["cls"]))
            value = self.value(val, ctype, events, ctx, e)
            return "%s->%s = %s;" % (name, member, value)
        raise Unsupported("a %s the generator has no template for" % e["k"])

    def member_at(self, owner, off, width):
        layout = self.layouts.get(self.field_type(owner)) or {}
        if off not in layout:
            raise Unsupported("no member of %s at +%d" % (owner, off))
        return layout[off]

    def returns(self, va, here):
        """The return type of the function at `va` as the source spells the call, or None."""
        name = self.function(va, here)
        role = self.lib.role_at.get(va)
        if role and (name == role[1] or name.endswith("::" + role[1])):
            ret = ROLE_SIGNATURES[role[1]][0]
            return ret if ret is not None else role[0] + " *"
        return self.protos.signature(name)[0]

    def call_expr(self, e, i, events, ctx):
        if e["k"] != "call":
            raise Unsupported("a virtual call outside an override")
        name = self.function(e["target"], ctx["cls"])
        role = self.lib.role_at.get(e["target"])
        receiver = None
        if role and role[0] in self.members_form:
            params = ["igMemoryPoolView *"] if role[1] == "_instantiateFromPool" else []
        else:
            params = self.member_signature(name)
            if params is not None:
                # a member function of a converted class: the first argument register holds `this`,
                # written as the Gap class (a receiver of another type is cast to it)
                cls = name.split("::")[-2]
                this = e["args"][0]
                if this in ctx["names"] and self.derives(ctx["types"].get(this), cls):
                    receiver = ctx["names"][this]
                elif this in ctx["names"]:
                    receiver = "((%s *)%s)" % (cls, ctx["names"][this])
                else:
                    receiver = "((%s *)%s)" % (cls, self.value(this, "void *", events, ctx, e))
                name = name.split("::")[-1]
            else:
                params = self.protos.params(name)
        if params is None:
            raise Unsupported("no declaration of %s" % name)
        args, ints, floats = [], 1 if receiver is not None else 0, 0
        for ptype in params:
            if re.match(r"(const )?(float|double)\b", ptype) and "*" not in ptype:
                raw = e["fargs"][floats] if floats < len(e["fargs"]) else None
                floats += 1
            else:
                raw = e["args"][ints] if ints < len(ARG_REGS) else e["stack"].get(16 + 8 * (ints - len(ARG_REGS)))
                ints += 1
            args.append(self.value(raw, ptype, events, ctx, e))
        if receiver is not None:
            return "%s->%s(%s)" % (receiver, name, ", ".join(args))
        return "%s(%s)" % (name, ", ".join(args))

    def value(self, v, ptype, events, ctx, at):
        if v is None:
            raise Unsupported("an argument the tracer lost")
        ptype = ptype or "int"
        ref = ptype.endswith("&")
        if v in ctx["names"]:
            have = ctx["types"].get(v)
            have = "int" if v == ctx["start"] else (have + " *") if have else None
            return self.cast_to(ptype if not ref else None, ctx["names"][v], have)
        if v[0] == "add" and v[1] == ctx["start"]:
            return "start + %d" % v[2]
        if v[0] == "ret":
            call = events[v[1]]
            text = self.call_expr(call, v[1], events, ctx)
            ret = self.returns(call["target"], ctx["cls"])
            if ret is None or ptype.endswith("&") or norm_type(ret) == norm_type(ptype):
                return text
            return "(%s)%s" % (ptype.strip(), text)
        if v[0] == "sp":
            slot = at["frame"].get(v[1])
            if ref and slot is not None:
                return self.value(slot, ptype.rstrip("&").replace("const ", "").strip(), events, ctx, at)
            raise Unsupported("a stack temporary the generator has no template for")
        if v[0] == "f":
            return float_literal(v[1])
        if v[0] == "g":
            owner = self.lib.meta_owner.get(v[1])
            if owner == ctx["cls"]:
                text = "_Meta"
            elif owner and owner in self.members_form:
                text = "%s::getClassMeta()" % (owner if owner == ctx["cls"] else self.qualified(owner))
            else:
                text = self.lib.data_name(v[1])
                if text is None:
                    raise Unsupported("a global 0x%x the generator cannot name" % v[1])
            return "(int)%s" % text if ptype.strip() == "int" else text
        if v[0] == "k":
            n = v[1]
            scalar = "*" not in ptype and not ref and "(" not in ptype
            # a scalar parameter takes a number, unless the constant is a function's address
            if IMAGE_LO <= n < IMAGE_HI and not (scalar and n not in self.lib.by_va):
                if n in self.lib.by_va:
                    text = self.function(n, ctx["cls"])
                    return "(int)%s" % text if ptype.strip() == "int" else text
                s = self.lib.image.string(n)
                if s is not None and ("char" in ptype):
                    return '"%s"' % s.replace("\\", "\\\\").replace('"', '\\"')
                if ref:
                    # a constant bound to a `const T &`: the compiler keeps its literal in .rodata
                    word = self.lib.image.word(n)
                    base = ptype.rstrip("&").replace("const ", "").strip()
                    return self.value(("k", word), base, events, ctx, at)
                name = self.lib.data_name(n)
                if name is None:
                    raise Unsupported("an address 0x%x the generator cannot name" % n)
                return "(int)&%s" % name if ptype.strip() == "int" else "&" + name
            signed = n - (1 << 32) if n & 0x80000000 else n
            if "float" in ptype:
                return float_literal(n)
            return str(signed)
        raise Unsupported("a value %r the generator has no template for" % (v,))

    # --- the other roles

    def instantiate(self, cls):
        return ["%s *%s::_instantiateFromPool(igMemoryPoolView *pool)" % (cls, cls),
                "{",
                "    arkRegister();",
                "    return (%s *)igMetaObject_CreateInstance(_Meta, pool);" % cls,
                "}"]

    def lazy(self, cls):
        return ["igMetaObject *%s::getClassTypeLazy()" % cls,
                "{",
                "    if (_Meta == 0)",
                "        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));",
                "    return _Meta;",
                "}"]

    def safe(self, cls):
        return ["igMetaObject *%s::getClassTypeSafe()" % cls,
                "{",
                "    if ((_Meta == 0) || !_Meta->isValid())",
                "        arkRegister();",
                "    return _Meta;",
                "}"]

    def ark_register(self, cls):
        return ["void %s::arkRegister()" % cls,
                "{",
                "    igMetaObject_RunStaticInit(arkRegisterInternal);",
                "}"]

    def vtable_pointer(self, cls):
        return ["void *%s::retrieveVTablePointer()" % cls,
                "{",
                "    %s temporary;" % cls,
                "    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);",
                "}"]

    def write_class(self, cls):
        """-> (lines, member rows) for one class, or raise Unsupported."""
        if cls not in self.layouts and cls not in self.converted:
            raise Unsupported("no reflected struct holds its members: declare the class in "
                              "config/converted-classes.tsv")
        roles = dict(self.lib.classes[cls])
        roles["sized"] = True
        roles["vtableMember"] = cls in self.converted
        handles = {}
        pieces = {}
        if roles.get("arkRegisterInitialize"):
            pieces["arkRegisterInitialize"] = self.initialize(cls, roles, handles)
        if roles.get("_instantiateFromPool"):
            pieces["_instantiateFromPool"] = self.instantiate(cls)
        if roles.get("getClassTypeLazy"):
            pieces["getClassTypeLazy"] = self.lazy(cls)
        if roles.get("getClassTypeSafe"):
            pieces["getClassTypeSafe"] = self.safe(cls)
        if roles.get("arkRegister"):
            pieces["arkRegister"] = self.ark_register(cls)
        pieces["arkRegisterInternal"] = self.register(cls, roles)
        if roles.get("retrieveVTablePointer"):
            if cls in self.converted:
                pieces["retrieveVTablePointer"] = self.vtable_pointer(cls)
            else:
                # igen's form constructs a temporary of the class: a flat struct keeps the tree's
                # free function until the class is converted
                pieces["retrieveVTablePointer"] = self.sources.definition(
                    self.lib.name_at(roles["retrieveVTablePointer"]))
        self.handles_of[cls] = handles
        lines = ["igMetaObject *%s::_Meta;" % cls]
        for va in sorted(handles):
            lines.append("igMetaField *%s::%s;" % (cls, handles[va]))
        lines.append("")
        for role in sorted(pieces, key=lambda r: roles[r]):
            lines.extend(pieces[role])
            lines.append("")
        macro = "IG_OBJECT_DEFINE" if roles["args"]["vtable"] else "IG_ABSTRACT_OBJECT_DEFINE"
        rows = [(cls, "%s(%s)" % (macro, cls))]
        rows.extend((cls, "static igMetaField *%s;" % handles[va]) for va in sorted(handles))
        return lines, rows


def close(body, block):
    if block is not None:
        body.extend(block)
        body.append("    }")


def globals_in(v):
    """The global loads inside value `v`, outermost first."""
    if isinstance(v, tuple):
        if v[0] == "g":
            yield v
        for part in v[1:]:
            yield from globals_in(part)


def is_global(v, addr):
    """Is `v` the value of the global at `addr` (whichever load read it)?"""
    return bool(v) and v[0] == "g" and v[1] == addr


def field_index(v, start):
    if v == start:
        return 0
    if v and v[0] == "add" and v[1] == start:
        return v[2]
    return None


def values_of(e):
    out = list(e.get("args") or [])
    out.extend((e.get("stack") or {}).values())
    for key in ("val", "base", "target"):
        if isinstance(e.get(key), tuple):
            out.append(e[key])
    return out


def rets_in(v):
    if not isinstance(v, tuple):
        return
    if v[0] == "ret":
        yield v
    for part in v[1:]:
        if isinstance(part, tuple):
            yield from rets_in(part)


def norm_type(t):
    t = re.sub(r"\bstruct\s+", "", t)
    return re.sub(r"\s+", "", t)


def demangle_name(mangled):
    """`Gap::Gui::igRenderer::setVisualContext` for an MWCC name (tools/demangle.py)."""
    try:
        from demangle import demangle
    except ImportError:
        return None
    try:
        return demangle(mangled).qualified
    except Exception:
        return None


# ----------------------------------------------------------------------------- members table

# Members of other classes the generated code calls: the kit's inline igMetaObject::isValid, which
# getClassTypeSafe tests (alchemy-kit_202309 include/igCore/igMetaObject.h; validity bit 4 is the
# finished layout, docs/engine/reflection-registration.md).
SUPPORT_ROWS = (
    ("igMetaObject", "bool isValid() const { return (_validity & 4) ? true : false; }"),
)


def merge_member_rows(path, rows, classes):
    """config/class-members.tsv with each written class's object macro and field handles in front of its
    other rows (an existing macro or handle row of the class is replaced, keeping its access label: a field
    handle is declared in its field's section of the kit header, `protected: static igMetaField *k_x;`)."""
    header, body = [], []
    if os.path.exists(path):
        for line in open(path):
            (header if line.startswith("#") and not body else body).append(line.rstrip("\n"))
    generated = re.compile(r"^((?:public|protected|private)\s*:\s*)?"
                           r"(IG_(ABSTRACT_)?OBJECT_DEFINE\(\w+\)|static igMetaField \*k_\w+;)$")
    labels = {}
    for ln in body:
        cls, _tab, decl = ln.partition("\t")
        m = generated.match(decl)
        if cls in classes and m and m.group(1):
            labels[(cls, m.group(2))] = m.group(1)
    kept = [ln for ln in body if ln.strip() and not (ln.split("\t", 1)[0] in classes
                                                     and generated.match(ln.split("\t", 1)[1]))]

    def labelled(r):
        return "%s\t%s%s" % (r[0], labels.get((r[0], r[1]), ""), r[1])

    out, placed = [], set()
    for ln in kept:
        cls = ln.split("\t", 1)[0]
        if cls in classes and cls not in placed:
            out.extend(labelled(r) for r in rows if r[0] == cls)
            placed.add(cls)
        out.append(ln)
    for cls in classes:
        if cls not in placed:
            out.extend(labelled(r) for r in rows if r[0] == cls)
    present = {tuple(ln.split("\t", 1)) for ln in out if "\t" in ln}
    out.extend("%s\t%s" % row for row in SUPPORT_ROWS if row not in present)
    with open(path, "w") as fh:
        fh.write("\n".join(header + out) + "\n")


def member_form_classes(members_path, converted):
    out = set(converted)
    for row in load_table(members_path, 2):
        if len(row) == 2 and re.match(r"IG_(ABSTRACT_)?OBJECT_DEFINE\(", row[1].strip()):
            out.add(row[0])
    return out


# ----------------------------------------------------------------------------- main

def generate(lib, classes, members_path, converted_path, compiler_names_path, reflected_path, root=ROOT):
    """-> (written [(class, lines)], class-members rows, {class: why not written}, writer).

    A class that cannot be written stays in the tree's form, so the others refer to it by its tree
    names: the classes are written again without it until no further class fails."""
    converted = {row[0]: row[1] for row in load_table(converted_path, 2) if len(row) == 2}
    tabled = member_form_classes(members_path, converted)
    member_rows = {}
    for row in load_table(members_path, 2):
        if len(row) == 2:
            member_rows.setdefault(row[0], []).append(row[1])
    writer = Writer(lib, tabled | set(classes), converted, load_compiler_names(compiler_names_path),
                    Prototypes(root), reflected_layouts(reflected_path), Sources(root), member_rows)
    failed = {}
    while True:
        writer.members_form = tabled | (set(classes) - set(failed))
        written, rows, now = [], [], {}
        for cls in classes:
            if cls in failed:
                continue
            try:
                lines, crow = writer.write_class(cls)
            except Unsupported as exc:
                now[cls] = str(exc)
                continue
            written.append((cls, lines))
            rows.extend(crow)
        if not now:
            return written, rows, failed, writer
        failed.update(now)


def render_fragment(written, converted, library):
    """The fragment: each run of classes of one library namespace in that namespace's block (tools/cxxscope.py, the
    spelling tools/memberize.py writes too)."""
    out = ["/* GENERATED by tools/gen_odl_source.py — do not edit.",
           " * The %s library's reflection boilerplate in igen's form (ODLSource)." % library,
           " */"]
    current = None
    for cls, lines in written:
        ns = "Gap::%s" % converted[cls] if converted.get(cls) else None
        if ns != current:
            if current:
                out.extend(cxxscope.close_lines(current))
            if ns:
                out.extend(cxxscope.open_lines(ns))
            current = ns
        out.append("")
        out.extend(lines[:-1] if lines and lines[-1] == "" else lines)
    if current:
        out.extend(cxxscope.close_lines(current))
    return "\n".join(out) + "\n"


def mangled_member(symbol, classes):
    """(class, member) of an MWCC member name (`getClassTypeSafe__10igRendererFv`,
    `_Meta__Q33Gap3Gui10igRenderer`) whose class is one of `classes`, or None."""
    for m in re.finditer(r"__(?=\d|Q\d)", symbol):
        member, rest = symbol[:m.start()], symbol[m.end():]
        if not member:
            continue
        count = 1
        if rest.startswith("Q"):
            count, rest = int(rest[1]), rest[2:]
        parts = []
        for _ in range(count):
            n = re.match(r"\d+", rest)
            if not n:
                break
            size = int(n.group())
            parts.append(rest[len(n.group()):len(n.group()) + size])
            rest = rest[len(n.group()) + size:]
        if len(parts) == count and parts[-1] in classes and (rest == "" or rest[0] in "CF"):
            return parts[-1], member
    return None


def verify(lib, written, writer, rows, preamble, members_path, converted_path, typed_path, root=ROOT):
    """Compile the written boilerplate under its unit's profile and compare every function with retail.

    The classes get their member rows in a private copy of config/class-members.tsv, reflected.h is
    regenerated from it into a private include folder, and the fragment compiles in place of the
    `.inc` fragments of the library's unit file (or after the header `preamble`). Relocations resolve through symbols.txt, the tree's data names and the
    classes' own `_Meta`/`k_` handles; a function-local table has no retail name, so its address
    halves are the only words left out of the comparison. -> (matched, compared)."""
    sys.path.insert(0, os.path.join(root, "tools"))
    import cc
    import unitprofiles
    import verify as vfy
    work = os.path.join(cc.scratch_dir(), "odl")
    inc = os.path.join(work, "include", "dw4", "support")
    os.makedirs(inc, exist_ok=True)
    members = os.path.join(work, "class-members.tsv")
    if os.path.exists(members_path):
        open(members, "w").write(open(members_path).read())
    merge_member_rows(members, rows, [c for c, _ in written])
    sys.path.insert(0, os.path.join(root, "scripts"))
    import gen_type_headers
    cwd = os.getcwd()
    os.chdir(root)
    try:
        import contextlib
        import io
        with contextlib.redirect_stdout(io.StringIO()):
            gen_type_headers.main(["--out", os.path.join(inc, "reflected.h"), "--members", members,
                                   "--converted", converted_path, "--typed-fields", typed_path])
    finally:
        os.chdir(cwd)
    source = os.path.join(work, "odl.cpp")
    fragment = render_fragment(written, writer.converted, "verify")
    if preamble:
        text = '#include "%s"\n%s' % (preamble, fragment)
    else:
        latch = lib.classes[written[0][0]]["latch"]
        text = writer.sources.unit_with_fragment(lib.name_at(latch), fragment) if latch else None
        if text is None:
            print("verify: no unit file defines the library latch; give --preamble")
            return 0, 0
    with open(source, "w") as fh:
        fh.write(text)
    table = unitprofiles.load(os.path.join(root, unitprofiles.DEFAULT_PATH))
    first = lib.classes[written[0][0]]["arkRegisterInternal"]
    unit = unitprofiles.unit_for(first, table)
    compiler = os.path.join(root, table.compilers[unit.compiler][0])
    flags = unitprofiles.command_flags(unitprofiles.Profile(compiler, unit.flags, unit.exceptions))
    flags = "-I%s %s" % (os.path.join(work, "include"), flags)
    obj = os.path.join(work, "odl.o")
    argv = cc.compile_argv(os.path.join(root, "local", "wibo"), compiler, flags, source, obj)
    import subprocess
    run = subprocess.run(argv, cwd=root, capture_output=True, text=True)
    if run.returncode != 0 or not os.path.exists(obj):
        print(run.stdout + run.stderr)
        return 0, 0
    handles = {}
    for cls, _lines in written:
        handles[(cls, "_Meta")] = lib.classes[cls]["meta"]
        for va, handle in writer.handles_of.get(cls, {}).items():
            handles[(cls, handle)] = va
    lib.data_name(0)
    data = {name: va for va, name in lib._data_names.items()}

    roles = {role: va for va, role in lib.role_at.items()}

    def resolve(name):
        if name in lib.by_name:
            return lib.by_name[name]
        if name in data:
            return data[name]
        hit = mangled_member(name, lib.classes)
        if hit:
            return handles.get(hit, roles.get(hit))
        return None

    syms, _sections = vfy.object_syms(obj)
    headers = vfy.elf_section_headers(obj)
    image = lib.image.data
    gp = lib.image.gp
    matched = compared = 0
    for name, (section, _value, _size) in sorted(syms.items()):
        if not isinstance(section, int) or not headers[section][0].startswith(".text"):
            continue
        target = resolve(name)
        if target is None:
            continue
        raw = vfy.object_section(obj, headers[section][0], section)
        relocs = vfy.object_relocs(obj, target_section=section)
        patched, _need, unresolved = vfy.apply_relocs(raw, relocs, resolve, gp)
        retail = bytearray(vfy.va_bytes(image, target, len(raw)))
        patched = bytearray(patched)
        lost = {name for _off, name in unresolved}
        masked = [(off, rtype) for _s, off, rtype, name, _a in relocs if name in lost]
        for off, rtype in masked:
            mask = 0x03FFFFFF if rtype == vfy.R_26 else 0xFFFF
            for buf in (patched, retail):
                w = struct.unpack_from("<I", buf, off)[0] & ~mask
                struct.pack_into("<I", buf, off, w)
        same = patched == retail
        compared += 1
        matched += same
        print("%s %s %dB at 0x%x%s" % ("MATCH" if same else "DIFFER", name, len(raw), target,
                                       " (%d words address function-local data: not compared)"
                                       % len(masked) if masked else ""))
        if not same:
            for at in range(0, len(raw), 4):
                if patched[at:at + 4] != retail[at:at + 4]:
                    print("   [%d] retail %s ours %s" % (at // 4, retail[at:at + 4][::-1].hex(),
                                                       patched[at:at + 4][::-1].hex()))
    print("verify: %d of %d functions match retail" % (matched, compared))
    return matched, compared


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--library", help="the library whose classes to write (Gui for GuiLibrary_MarkRegistered)")
    ap.add_argument("--class", dest="classes", action="append", default=[], help="a class to write")
    ap.add_argument("--out", help="write the fragment here (default: stdout)")
    ap.add_argument("--list", action="store_true", help="list each class's roles and what cannot be written")
    ap.add_argument("--members", action="store_true", help="print the class-members.tsv rows")
    ap.add_argument("--write-members", action="store_true", help="put the rows into config/class-members.tsv")
    ap.add_argument("--verify", action="store_true",
                    help="compile the fragment under the unit's profile and compare each function with retail")
    ap.add_argument("--preamble", help="--verify: compile the fragment after this header instead of in "
                                       "the library's unit file")
    ap.add_argument("--typed-fields", default=os.path.join(ROOT, "config", "typed-fields.tsv"))
    ap.add_argument("--asm", default=os.path.join(ROOT, "asm"))
    ap.add_argument("--elf", default=os.path.join(ROOT, "orig", GAME, "SLUS_208.36"))
    ap.add_argument("--symbols", default=os.path.join(ROOT, "config", GAME, "symbols.txt"))
    ap.add_argument("--reflection", default=os.path.join(ROOT, "data", "reflection.json"))
    ap.add_argument("--class-members", default=os.path.join(ROOT, "config", "class-members.tsv"))
    ap.add_argument("--converted", default=os.path.join(ROOT, "config", "converted-classes.tsv"))
    ap.add_argument("--compiler-names", default=os.path.join(ROOT, "config", GAME, "compiler-names.tsv"))
    ap.add_argument("--reflected", default=os.path.join(ROOT, "include", "dw4", "support", "reflected.h"))
    a = ap.parse_args(argv)
    if not a.library and not a.classes:
        ap.error("give --library or --class")
    lib = Library(ROOT, a.asm, a.elf, a.reflection, a.symbols)
    classes = list(a.classes)
    if a.library:
        classes += [c for c in lib.library_classes(a.library) if c not in classes]
    for cls in classes:
        if cls not in lib.classes:
            print("%s: %s" % (cls, lib.problems.get(cls, "not a registered class")), file=sys.stderr)
            return 1
    written, rows, failed, writer = generate(lib, classes, a.class_members, a.converted, a.compiler_names,
                                             a.reflected)
    if a.list:
        for cls in classes:
            roles = lib.classes[cls]
            text = " ".join("%s=0x%x" % (r, roles[r]) for r in ROLE_ORDER if roles.get(r))
            print("%-40s %s%s" % (cls, text, ("  CANNOT: " + failed[cls]) if cls in failed else ""))
        print("%d classes, %d written, %d cannot be written" % (len(classes), len(written), len(failed)))
        return 0
    for cls, why in failed.items():
        print("%s: not written: %s" % (cls, why), file=sys.stderr)
    if writer.undeclared:
        print("referenced without a declaration in any header: %s" % " ".join(sorted(writer.undeclared)),
              file=sys.stderr)
    if a.members:
        for row in rows:
            print("%s\t%s" % row)
        return 0
    if a.verify:
        if not written:
            return 1
        matched, compared = verify(lib, written, writer, rows, a.preamble, a.class_members, a.converted,
                                   a.typed_fields)
        return 0 if compared and matched == compared and not failed else 1
    if a.write_members:
        merge_member_rows(a.class_members, rows, [c for c, _ in written])
    text = render_fragment(written, writer.converted, a.library or "selected")
    if a.out:
        with open(a.out, "w") as fh:
            fh.write(text)
        print("wrote %s: %d classes (%d not written)" % (a.out, len(written), len(failed)), file=sys.stderr)
    else:
        sys.stdout.write(text)
    return 0


if __name__ == "__main__":
    sys.exit(main())
