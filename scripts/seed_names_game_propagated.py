#!/usr/bin/env python3
"""seed_names_game_propagated.py — name game functions from evidence that propagates mechanically.

Every row carries a confidence (high or medium; nothing lower is written) and its evidence, the layout of
`config/SLUS-20836/names/CoreNames.tsv`, whose conventions it follows (`<Class>_<Method>`).  Routes:

  slot          a virtual is named once per family and that name is carried to every override still called
                `FUN_<addr>` or `<Class>::vfunc_NN`.  The family of slot S of class C is (introducer, S), the
                introducer being the highest ancestor in `data/class-hierarchy.tsv` whose vtable
                (`data/vtables.json`, `data/vtables-getvtable.json`; igObject has 21 slots) already has slot S;
                a class whose record ends early (its trailing pure slots) counts with the classes under it.
                S is the position in the vtable record, never the NN of a `vfunc_NN` name (those follow two
                numbering conventions).  A record shorter than its parent's is a truncated dump and is ignored.
                A family named by reading its callers (`scripts/game_slot_families.tsv`) takes that name for
                every member in every region, and the overrides that spell it otherwise are renamed (one
                name per virtual).  Any other family takes the introducer's own implementation's name
                (high), else the one name every named override agrees on (high with two or more, medium
                with one); disagreeing overrides are never settled by a majority, the family is left for
                review, as is a method decided for two slots of related families.  An address in several
                families is named only when they agree.  The owner is the nearest common ancestor of the
                classes whose vtables hold the function (the class that defines a shared default), or the
                class in its current RTTI name when that ancestor is igObject.
  plumbing      registrar plumbing recognised from its body (matched C, else the retail instructions in
                `asm/`): `<C>_EnsureRegistered` (runs `igMetaObject_RunStaticInit(<C>_Register)`),
                `<C>_GetMetaObject` (the validity-checked accessor of `g_<C>_metaObject`),
                `<C>_GetOrCreateMetaObject`, `<C>_GetPublishedMetaObject`, `<C>_Create`.  The registrar's
                argument-4 stub, which only calls the accessor and held `<C>_GetMetaObject` until now, becomes
                `<C>_GetMetaObjectFunction`.  Each accessor must call nothing but its own `EnsureRegistered`,
                each stub nothing but its accessor.
  emitted       a compiler-emitted `igSmartPointer<T>` destructor (its `unit-objects.json` name) is
                `igSmartPointer_<T>_Destruct`; where two copies are the same instance, each takes its owning
                file's class as a prefix (`<Class>_igSmartPointer_<T>_Destruct`).
  engine        the Alchemy registrar plumbing the game's matched C calls, recognised from the retail
                instructions.
  class-name    the functions of a class registered under a name Alchemy also registers move from the
                handle-suffixed prefix to the class's own (`seed_names_reflection.class_prefixes`).

A name already held by another address, or given to two, is dropped.  The rows other overlays held for the
addresses named here move here (`--write`), so `tools/split.py` sees each address named once.  The
generator is idempotent: the addresses of the overlay it wrote last are candidates again and their names
are not counted as evidence, so it can be re-run after `tools/apply_names.py`.  It reads the generated
`asm/` (`make asm`).

  scripts/seed_names_game_propagated.py                       # summary only
  scripts/seed_names_game_propagated.py --write               # write the overlay, move the rows
  scripts/seed_names_game_propagated.py --todo families.tsv   # the slot families that need a name
"""
import argparse
import bisect
import collections
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
sys.path.insert(0, os.path.join(REPO, "tools"))
sys.path.insert(0, HERE)
os.chdir(REPO)

import progress as P  # noqa: E402
import regions  # noqa: E402
from seed_names_reflection import class_prefixes  # noqa: E402

CONFIG = os.path.join("config", "SLUS-20836")
NAMES = os.path.join(CONFIG, "names")
OVERLAY = os.path.join(NAMES, "GamePropagated.tsv")
FAMILIES = os.path.join("scripts", "game_slot_families.tsv")
GAME = {"bec", "ndmw", "adx-movie", "game-main"}
SYNONYMS = {"GetMetaObject_Virtual": "GetMeta", "RegisterReceivers": "RegisterReceiver"}
IGOBJECT_SLOTS = 21    # igObject's slots 0..19 and GetMeta (20), which every class overrides
INS = re.compile(r"/\* ([0-9a-f]{8}): (\w+)\s*(.*?) \*/")
META = re.compile(r"\bg_(\w+?)_metaObject\b")
SMART_POINTER_DTOR = re.compile(r"__dt__\d+igSmartPointer<\d+(\w+)>Fv")


def tsv_rows(path):
    for ln in open(path):
        if ln.strip() and not ln.startswith("#"):
            yield ln.rstrip("\n").split("\t")


# ---------------------------------------------------------------- inputs
sym = {}
for ln in open(os.path.join(CONFIG, "symbols.txt")):
    if ln.strip() and not ln.startswith("#"):
        p = ln.split()
        sym[int(p[0], 16)] = p[2]
by_name = {n: a for a, n in sym.items()}
starts = sorted(sym)
own = {int(r[0], 16) for r in tsv_rows(OVERLAY)} if os.path.exists(OVERLAY) else set()

base = {}
for r in tsv_rows("data/class-hierarchy.tsv"):
    if r[1] != "-":
        base[r[0]] = r[1]
children = collections.defaultdict(set)
for a, b in base.items():
    children[b].add(a)


def short(c):
    return c.split("::")[-1]


slots_of = {}
for a, v in json.load(open("data/vtables.json"))["vtables"].items():
    slots_of[short(v["class"])] = [int(x, 16) if x else None for x in v["vfuncs"]]
for a, v in json.load(open("data/vtables-getvtable.json")).items():
    fl = v["vfuncs"][2:]                  # these lists keep the {rtti, 0} header words
    while fl and fl[-1] is None:
        fl.pop()
    slots_of.setdefault(short(v["class"]), [int(x, 16) if x else None for x in fl])
allcls = set(base) | set(base.values()) | set(slots_of)

refl = json.load(open("data/reflection.json"))["classes"]
prefix_of = class_prefixes(refl)                                   # handle -> class symbol prefix
handle_prefix = {int(h, 16): p for h, p in prefix_of.items()}
class_set = set(prefix_of.values())


def containing(va):
    i = bisect.bisect_right(starts, va) - 1
    return starts[i] if i >= 0 else None


register_prefix = {containing(int(c["register_site"], 16)): prefix_of[h] for h, c in refl.items()}
paths = P.have_src_paths()
categories = P.load_categories() or {}
texts = {}


def body(name):
    """The matched C definition of `name` (comments and strings blanked), or ''."""
    path = paths.get(name)
    va = by_name.get(name)
    if path is None or categories.get(va, ("",))[0] != "match":
        return ""
    if path not in texts:
        texts[path] = P._function_texts(path)
    return texts[path][0].get(name, "")


def flat(text):
    return re.sub(r"\s+", " ", text)


def region(va):
    row = regions.of(va)
    return row.id if row else None


def module_of(va):
    path = paths.get(sym[va])
    if path:
        parts = os.path.relpath(path, "src").split(os.sep)
        if len(parts) > 1 and parts[0] != "unmatched":
            return parts[0]
    return "game" if region(va) in GAME else "engine"


asm_cache = {}


def asm(va):
    """[(op, [args])] of the retail instructions at `va` (asm/<symbol>.s), or []."""
    if va not in asm_cache:
        p = os.path.join("asm", "%s.s" % sym.get(va, ""))
        asm_cache[va] = [(op, [x.strip() for x in args.split(",")])
                         for _a, op, args in INS.findall(open(p).read())] if os.path.exists(p) else []
    return asm_cache[va]


def calls(va):
    return [int(ar[0], 16) for op, ar in asm(va) if op in ("jal", "j") and ar and ar[0].startswith("0x")]


def unnamed(va):
    """Still an address or slot-number name, or a name this overlay gave."""
    n = sym[va]
    return n.startswith("FUN_") or bool(P.SLOT_NAME_RE.search(n)) or va in own


# ---------------------------------------------------------------- class tree
def desc(c):
    out, st, seen = [], [c], set()
    while st:
        x = st.pop()
        if x not in seen:
            seen.add(x)
            out.append(x)
            st.extend(children.get(x, ()))
    return out


def ancestors(c):
    out = [c]
    while c in base and base[c] not in out:
        c = base[c]
        out.append(c)
    return out


bound = {"igObject": IGOBJECT_SLOTS}


def below(c, floor):
    """The fewest slots a class under c has, at least `floor`: each child counts with its own record or,
    when that is shorter, the classes under it (a record ends at its last non-null word, so a class's
    trailing pure slots show only in its subclasses; a record shorter than `floor` is a truncated dump)."""
    counts = []
    for ch in children.get(c, ()):
        own_n = len(slots_of.get(ch, []))
        n = max(own_n, below(ch, max(floor, own_n)))
        if n >= floor and n:
            counts.append(n)
    return min(counts) if counts else 0


def getbound(c):
    """The slots class c has: its own record, or the fewest any class under it has."""
    if c not in bound:
        pb = getbound(base[c]) if c in base else 0
        own_n = len(slots_of[c]) if c in slots_of and len(slots_of[c]) >= pb else 0
        bound[c] = max(own_n, below(c, max(pb, own_n)), pb)
    return bound[c]


def introducer(c, s):
    intro = c
    for a in ancestors(c):
        if getbound(a) > s:
            intro = a
        else:
            break
    return intro


def split_name(n):
    """(class, method) of a symbol; method None for `vfunc_NN`, (None, None) for `FUN_`."""
    if n.startswith(("FUN_", "thunk_")):
        return None, None
    rest = re.sub(r"^Gap__(?:[A-Za-z]+__)?", "", n)
    best = None
    for c in allcls:
        for sep in ("__", "_"):
            if rest.startswith(c + sep) and (best is None or len(c) > len(best[0])):
                best = (c, rest[len(c) + len(sep):])
    if not best:
        return None, None
    if P.SLOT_NAME_RE.fullmatch(best[1]):
        return best[0], None
    return best


def nca(classes):
    chains = [ancestors(c) for c in classes]
    common = [x for x in chains[0] if all(x in ch for ch in chains)]
    return common[0] if common else None


rows = {}                                    # va -> [name, module, confidence, evidence, route]
unresolved = collections.defaultdict(list)


def add(va, name, conf, ev, route, module=None):
    if P.carries_address(name):              # a class still named by an address needs its own name first
        unresolved["address-class"].append((va, name))
        return
    rows[va] = [name, module or module_of(va), conf, ev, route]


# ---------------------------------------------------------------- route: slots
occ = collections.defaultdict(list)
fam = collections.defaultdict(list)
for c, sl in slots_of.items():
    for s, a in enumerate(sl):
        if a:
            occ[a].append((c, s))
            fam[(introducer(c, s), s)].append((c, a))


def method_at(a):
    if a in own or a not in sym:             # this overlay's own names are not evidence for it
        return None, None
    return split_name(sym[a])


def decide(k):
    """(method, confidence, evidence) of family k, or (None, 'conflict'|'unnamed', detail)."""
    intro, s = k
    for c, a in fam[k]:
        oc, m = method_at(a)
        if oc == intro and m:
            m = SYNONYMS.get(m, m)
            return m, "high", "slot %d is %s::%s, the introducing class's own implementation (0x%x %s)" % (
                s, intro, m, a, sym[a])
    ms = collections.defaultdict(set)
    for c, a in fam[k]:
        oc, m = method_at(a)
        if m:
            ms[SYNONYMS.get(m, m)].add(a)
    if len(ms) == 1:
        m, v = next(iter(ms.items()))
        ex = ", ".join("%s 0x%x" % (sym[x], x) for x in sorted(v)[:3])
        return m, "high" if len(v) >= 2 else "medium", \
            "slot %d introduced by %s; all %d named overrides are %s (%s)" % (s, intro, len(v), m, ex)
    if ms:
        return None, "conflict", "; ".join("%s x%d" % (m, len(v)) for m, v in
                                           sorted(ms.items(), key=lambda x: (-len(x[1]), x[0])))
    return None, "unnamed", ""


decided = {k: decide(k) for k in fam}
by_method = collections.defaultdict(list)
for k, (m, _c, _e) in decided.items():
    if m:
        by_method[m].append(k)
for m, ks in by_method.items():              # one virtual has one slot
    for k1 in ks:
        for k2 in ks:
            if k1[1] != k2[1] and (k1[0] in ancestors(k2[0]) or k2[0] in ancestors(k1[0])):
                decided[k1] = (None, "conflict", "%s also decided for slot %d of %s" % (m, k2[1], k2[0]))
                break
# the families named by reading their callers: the name holds for every member, whatever it is called now
named_families, named_addresses = set(), []
for r in tsv_rows(FAMILIES):
    if r[0] == "-":
        named_addresses.append((int(r[1], 16), r[2], r[3], r[4]))
        continue
    k = (r[0], int(r[1]))
    if k not in fam:
        unresolved["families:no-such-family"].append((None, k))
        continue
    decided[k] = (r[2], r[3], "%s/%d = %s: %s" % (r[0], k[1], r[2], r[4]))
    named_families.add(k)
for va in sorted(occ):
    if va not in sym:
        continue
    keys = sorted({(introducer(c, s), s) for c, s in occ[va]})
    by_reading = all(k in named_families for k in keys)
    if not by_reading and (region(va) not in GAME or not unnamed(va)):
        continue
    methods = {decided[k][0] for k in keys}
    if len(keys) != 1 and (len(methods) != 1 or None in methods):
        unresolved["slot:multi-family"].append((va, keys))
        continue
    k = keys[0]
    method, conf, ev = decided[k]
    if method is None:
        unresolved["slot:" + conf].append((va, k))
        continue
    if len(keys) > 1:
        conf = "medium" if any(decided[x][1] == "medium" for x in keys) else conf
        ev += "; the same name in %s" % ", ".join("%s/%d" % x for x in keys[1:])
    classes = sorted({c for c, s in occ[va]})
    oc = split_name(sym[va])[0]
    owner = nca(classes)                     # the class that defines a shared default
    if owner in (None, "igObject"):
        owner = oc
    if owner is None:
        unresolved["slot:no-owner"].append((va, k))
        continue
    name = "%s_%s" % (owner, method)
    if name == sym[va] and va not in own:
        continue                             # already this name, from another overlay or the dump
    add(va, name, conf,
        ev + "; held by %d vtable(s)%s" % (len(classes), " (owner = nearest common ancestor)" if owner != oc else ""),
        "slot")
for va, name, conf, ev in named_addresses:
    add(va, name, conf, ev, "slot")


# ---------------------------------------------------------------- route: registrar plumbing
def register_class(ident):
    """The class whose registrar `ident` names (by address, so a renamed registrar still counts)."""
    va = by_name.get(ident)
    if va in register_prefix:
        return register_prefix[va]
    return ident[:-len("_Register")] if ident.endswith("_Register") else None


handle_classes = {}                          # class prefix -> handle


def classify_body(va):
    """(role, class, evidence) of a matched game function's C, or None."""
    b = body(sym[va])
    if not b:
        return None
    f = flat(b)
    m = re.search(r"igMetaObject_RunStaticInit\(\s*(\w+_Register)\s*\)", f)
    if m and f.count(";") == 1:
        c = register_class(m.group(1))
        if c in class_set:
            return "EnsureRegistered", c, "runs igMetaObject_RunStaticInit(%s_Register)" % c
    metas = set(META.findall(f)) & class_set
    if len(metas) == 1:
        c = next(iter(metas))
        if re.search(r"_validity\b|\+ 0x?\d+\) & 4|& 4\)|!\s*isValid\(\s*g_%s_metaObject\s*\)" % c, f) and \
                re.search(r"\b(?:FUN_[0-9a-f]{8}|%s_EnsureRegistered)\s*\(\s*\)" % c, f):
            return "GetMetaObject", c, ("validity-checked accessor of g_%s_metaObject that runs %s registration when "
                                        "the class is not valid" % (c, c))
        if re.search(r"==\s*0\s*\)\s*\{?\s*g_%s_metaObject\s*=\s*igMetaObject_Create\(" % c, f):
            return "GetOrCreateMetaObject", c, "creates g_%s_metaObject on first use and returns it" % c
        if re.fullmatch(r"\s*\w[\w\s\*]*\(\s*void\s*\)\s*\{\s*return\s+g_%s_metaObject(?:\[0\])?\s*;\s*\}\s*" % c, b):
            return "GetPublishedMetaObject", c, "12-byte leaf returning g_%s_metaObject" % c
        if re.search(r"igMetaObject_CreateInstance\(\s*(?:\*\s*\(\s*\w+\s*\*\)\s*&?)?g_%s_metaObject" % c, f) \
                and f.count(";") <= 3:
            return "Create", c, "ensures %s is registered, then igMetaObject_CreateInstance(g_%s_metaObject, allocator)" % (c, c)
    m = re.search(r"igMetaObject_CreateInstance\(\s*\*\s*\(\s*int\s*\*\s*\)\s*(0x[0-9a-fA-F]+|\d+)\s*,", f)
    if m and int(m.group(1), 0) in handle_prefix and f.count(";") <= 3:
        c = handle_prefix[int(m.group(1), 0)]
        return "Create", c, ("ensures %s is registered, then igMetaObject_CreateInstance(*%s, the %s handle, allocator)"
                             % (c, m.group(1), c))
    return None


RUN_STATIC_INIT, META_CREATE = by_name["igMetaObject_RunStaticInit"], by_name["igMetaObject_Create"]


def classify_asm(va):
    """(role, class, evidence) from the retail instructions, or None."""
    ins = asm(va)
    hi, handles, jals, addr_args, andi4 = {}, set(), [], set(), False
    for op, ar in ins:
        if op == "lui":
            hi[ar[0]] = int(ar[1], 16) << 16
        elif op in ("lw", "sw") and len(ar) >= 2:
            m = re.match(r"(-?\d+)\((\w+)\)", ar[-1])
            if m and m.group(2) in hi and (hi[m.group(2)] + int(m.group(1))) & 0xffffffff in handle_prefix:
                handles.add((hi[m.group(2)] + int(m.group(1))) & 0xffffffff)
        elif op == "addiu" and len(ar) == 3 and ar[1] in hi:
            addr_args.add((hi[ar[1]] + int(ar[2])) & 0xffffffff)
        elif op in ("jal", "j"):
            jals.append(int(ar[0], 16))
        elif op == "andi" and ar[-1] in ("0x4", "4"):
            andi4 = True
    if RUN_STATIC_INIT in jals:
        regs = [x for x in addr_args if x in register_prefix]
        if len(regs) == 1:
            c = register_prefix[regs[0]]
            return "EnsureRegistered", c, "j igMetaObject_RunStaticInit with &%s_Register" % c
    if len(handles) == 1:
        h = next(iter(handles))
        c = handle_prefix[h]
        if META_CREATE in jals:
            return "GetOrCreateMetaObject", c, "creates the class handle 0x%x with igMetaObject_Create on first use" % h
        if andi4 and len(jals) == 1:
            return "GetMetaObject", c, "validity test (andi 4) of the class handle 0x%x, one registration call" % h
        if len(ins) == 3 and ins[1][0] == "jr":
            return "GetPublishedMetaObject", c, "lui; jr ra; lw v0 of the class handle 0x%x" % h
    return None


accessor_of = {}                             # va of a validity accessor -> class
for va in sorted(sym):
    if va in rows or region(va) not in GAME or not unnamed(va):
        continue
    k = classify_body(va) if body(sym[va]) else classify_asm(va)
    if k:
        role, c, ev = k
        add(va, "%s_%s" % (c, role), "high", "%s; Core convention <C>_%s (CoreNames.tsv)" % (ev, role), "plumbing")
        if role == "GetMetaObject":
            accessor_of[va] = c

# the Alchemy plumbing the game's sources call (a game file read whole, as the compiler sees it)
called = set()
for path in sorted({p for n, p in paths.items() if region(by_name.get(n, 0)) in GAME}):
    if path not in texts:
        texts[path] = P._function_texts(path)
    called.update(int(t[4:], 16) for t in re.findall(r"\bFUN_[0-9a-f]{8}\b", texts[path][1]))
called |= {va for va in own if va in sym and region(va) not in GAME}
for a in sorted(called):
    if a in rows or a not in sym or region(a) in GAME or not unnamed(a):
        continue
    k = classify_asm(a)
    if k:
        add(a, "%s_%s" % (k[1], k[0]), "high", "retail instructions: %s; Core convention <C>_%s" % (k[2], k[0]),
            "engine", "engine")
        if k[0] == "GetMetaObject":
            accessor_of[a] = k[1]

# the registrar's argument-4 stub: a function that only calls its class's accessor
for va, n in sym.items():
    if not n.endswith(("_GetMetaObject", "_GetMetaObjectFunction")) or va in accessor_of:
        continue
    cs = calls(va)
    if len(cs) == 1 and cs[0] in accessor_of and len(asm(va)) <= 8:
        c = accessor_of[cs[0]]
        add(va, "%s_GetMetaObjectFunction" % c, "high",
            "registrar argument 4 (t0) stub that only calls %s_GetMetaObject (0x%x); Core convention "
            "<C>_GetMetaObjectFunction" % (c, cs[0]), "plumbing")


# ---------------------------------------------------------------- route: emitted smart-pointer destructors
def view_class(t):
    """The class an ABI view stands for: `<Class>DispatchView`, or a `<Class>View` whose header is in
    include/dw4, is the class itself; any other T is returned unchanged."""
    if t.endswith("DispatchView"):
        return t[:-len("DispatchView")]
    if t.endswith("View") and os.path.exists(os.path.join("include", "dw4", t + ".h")):
        return t[:-len("View")]
    return t


def instances(names):
    return {view_class(m.group(1)) for m in map(SMART_POINTER_DTOR.fullmatch, names) if m}


own_names, dup_names = collections.defaultdict(set), collections.defaultdict(set)
for start, row in json.load(open(os.path.join(CONFIG, "unit-objects.json"))).items():
    for key, table in (("emitted", own_names), ("duplicates", dup_names)):
        for n, a in (row.get(key) or {}).items():
            if isinstance(a, str):
                table[int(a, 16)].add(n)
instance, emitted = {}, {}                   # va -> T of its igSmartPointer<T> destructor, and that name
for a in set(own_names) | set(dup_names):
    # the emitting unit's own compiler name decides; a copy its unit defines under its symbol is named by
    # the units that list it, when they agree
    mangled = own_names[a] - {sym.get(a)}
    ts = instances(mangled or dup_names[a])
    if len(ts) == 1:
        instance[a] = next(iter(ts))
        emitted[a] = next(n for n in sorted(mangled or dup_names[a]) if SMART_POINTER_DTOR.fullmatch(n))
copies = collections.defaultdict(list)       # instance -> every address emitted as it
for a, t in instance.items():
    copies[t].append(a)


def preceding_class(va):
    """The class of the nearest function before `va` that names one: MWCC emits an inline's copy right
    after the first function of the file that uses it."""
    i = starts.index(va)
    for a in reversed(starts[max(0, i - 6):i]):
        c = split_name(rows[a][0] if a in rows else sym[a])[0]
        if c and paths.get(sym[a]) == paths.get(sym[va]):
            return c
    return None


for t, vas in sorted(copies.items()):
    files = collections.Counter(paths.get(sym.get(a)) for a in vas)
    for va in vas:
        if va not in sym or va in rows or region(va) not in GAME or \
                not (unnamed(va) or P.carries_address(sym[va])):
            continue
        name = "igSmartPointer_%s_Destruct" % t
        ev = "compiler-emitted %s (unit-objects.json); Core convention igSmartPointer_<T>_Destruct" % emitted[va]
        if len(vas) > 1:
            path = paths.get(sym[va])
            owner = os.path.splitext(os.path.basename(path or ""))[0]
            why = "the owning file's class"
            if files[path] > 1 or owner.endswith("Library"):
                # a library file, or one holding two copies: the class whose function first uses it
                owner, why = preceding_class(va), "the class of the function it follows"
            if not owner:
                unresolved["emitted:no-owner"].append((va, name))
                continue
            name = "%s_%s" % (owner, name)
            ev += "; %d copies of this instance, so %s, %s, is added" % (len(vas), why, owner)
        add(va, name, "high", ev, "emitted")


# ---------------------------------------------------------------- route: class registered twice
for h, c in refl.items():
    old, new = "%s_%s" % (c["class"], h[2:].lower()), prefix_of[h]
    if new == old:
        continue
    for va, n in sym.items():
        for head in ("", "thunk_"):
            if va not in rows and (n.startswith(head + old + "_") or (va in own and n.startswith(head + new + "_"))):
                add(va, head + new + n[len(head + (old if n.startswith(head + old + "_") else new)):], "high",
                    "%s is registered twice (handles %s); this copy's registrar is in the %s library and its RTTI "
                    "vtable names it there, so it takes the prefix %s" % (
                        c["class"], ", ".join(x for x, y in refl.items() if y["class"] == c["class"]),
                        region(int(c["register_site"], 16)), new), "class-name")


# ---------------------------------------------------------------- collisions and self-checks
others = {}                                  # va -> (name, overlay file) of every other overlay
for f in sorted(os.listdir(NAMES)):
    if f.endswith(".tsv") and os.path.join(NAMES, f) != OVERLAY:
        for r in tsv_rows(os.path.join(NAMES, f)):
            others[int(r[0], 0)] = (r[1].replace("::", "__"), f)


def check():
    """Drop the rows that collide or whose partner row is gone; -> True when something was dropped."""
    held = collections.Counter(n for va, n in sym.items() if va not in rows)
    held.update(n for va, (n, _f) in others.items() if va not in rows and n != sym.get(va))
    given = collections.Counter(r[0] for r in rows.values())
    drop = [va for va, r in rows.items() if given[r[0]] > 1 or held[r[0]]]
    for va in drop:
        unresolved["collision:" + rows[va][4]].append((va, rows[va][0]))
    names = {r[0]: va for va, r in rows.items()}
    for va, r in rows.items():
        if va in drop:
            continue
        if r[0].endswith("_GetMetaObjectFunction"):
            acc = names.get(r[0][:-len("Function")])
            if acc is None or calls(va) != [acc]:
                unresolved["check:stub"].append((va, r[0]))
                drop.append(va)
        elif r[0].endswith("_GetMetaObject") and r[4] == "plumbing" and body(sym[va]):
            c = r[0][:-len("_GetMetaObject")]
            for x in re.findall(r"\b(\w+)\s*\(\s*\)", body(sym[va])):
                tgt = by_name.get(x)
                if tgt is not None and tgt != va and (rows[tgt][0] if tgt in rows else x) != "%s_EnsureRegistered" % c:
                    unresolved["check:accessor"].append((va, r[0]))
                    drop.append(va)
                    break
    for va in set(drop):
        del rows[va]
    return bool(drop)


while check():
    pass


# ---------------------------------------------------------------- output
def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--write", action="store_true",
                    help="write %s and drop the rows other overlays hold for its addresses" % OVERLAY)
    ap.add_argument("--todo", help="write the slot families that need a name to this file")
    a = ap.parse_args()
    routes = collections.Counter("%s/%s" % (r[4], r[2]) for r in rows.values())
    print("%d rows: %s" % (len(rows), ", ".join("%s %d" % kv for kv in sorted(routes.items()))))
    print("left: %s" % ", ".join("%s %d" % (k, len(v)) for k, v in sorted(unresolved.items())))
    if a.write:
        with open(OVERLAY, "w") as f:
            f.write("# Game function names that propagate mechanically: vtable slot families, registrar plumbing,\n"
                    "# compiler-emitted smart-pointer destructors. GENERATED by scripts/seed_names_game_propagated.py;\n"
                    "# do not hand-edit.\n"
                    "# Columns: <va>  <name>  <module>  <confidence>  <evidence>. tools/split.py reads the first three.\n")
            for va in sorted(rows):
                n, mod, conf, ev, _route = rows[va]
                f.write("0x%08x\t%s\t%s\t%s\t%s\n" % (va, n, mod, conf, ev))
        moved = collections.Counter()
        for fn in sorted(os.listdir(NAMES)):
            path = os.path.join(NAMES, fn)
            if not fn.endswith(".tsv") or path == OVERLAY:
                continue
            lines = open(path).readlines()
            keep = [ln for ln in lines if not ln.strip() or ln.startswith("#") or int(ln.split("\t")[0], 0) not in rows]
            if len(keep) != len(lines):
                moved[fn] = len(lines) - len(keep)
                open(path, "w").writelines(keep)
        print("wrote %s; rows moved here from %s" % (OVERLAY, ", ".join("%s %d" % kv for kv in sorted(moved.items()))
                                                     or "no other overlay"))
    if a.todo:
        with open(a.todo, "w") as f:
            f.write("# <introducer>\t<slot>\t<status>\t<named overrides>\t<unnamed members (va name)>\n")
            todo = collections.defaultdict(list)
            for key in ("slot:conflict", "slot:unnamed"):
                for va, k in unresolved.get(key, []):
                    todo[(k, key[5:])].append(va)
            for (k, status), vas in sorted(todo.items(), key=lambda kv: (-len(kv[1]), kv[0])):
                f.write("%s\t%d\t%s\t%s\t%s\n" % (k[0], k[1], status, decided[k][2] or "-",
                                                 ", ".join("0x%x %s" % (x, sym[x]) for x in sorted(vas))))
            for va, keys in unresolved.get("slot:multi-family", []):
                f.write("-\t-\tmulti-family\t%s\t0x%x %s\n" % ("; ".join("%s/%d" % k for k in keys), va, sym[va]))
    return 0


if __name__ == "__main__":
    sys.exit(main())
