#!/usr/bin/env python3
"""seed_names_getvtable_slots.py — name the vtable slots of the classes RTTI never listed.

`data/vtables.json` maps a vtable to its class from the class's `__RTTI__` record, and the
RTTI pass names those slots.  But only **478** classes emit an RTTI record; every class still
has its own `<Class>_GetVTable` function, and that function builds the class's vtable as the
**first rodata-range value stored to a stack slot** (the same rule `seed_names_metafield_slots.py`
uses for the MetaField subclasses, finding #368).  Resolving those gives **958 distinct vtables /
980 classes**, of which **499 are not RTTI records** — and each one's slots are unnamed.

A slot body that (a) is an unmatched `FUN_`, (b) is used by exactly one class's vtable, and
(c) is not inherited from a resolved ancestor's vtable, is that class's own override, so it is
named `<Namespace>::<Class>::vfunc_N`.  Nothing is guessed from the body: the class comes from
the class's own `GetVTable`, the namespace from the nearest RTTI ancestor of the recovered
hierarchy (`class-hierarchy.tsv`), and the role from the slot index.  The generator is
idempotent and skips anything already named.

The names are middleware (`ig*`) classes: the game's own `Gap::Bec::be*` classes all carry RTTI,
so their slots were named by the RTTI pass already.  Naming these is T6 coverage; they are
deliberately **not** fed to the receiver-typing rule, which the port plan scopes to game code
(finding #488).

  scripts/seed_names_getvtable_slots.py                 # print the rows
  scripts/seed_names_getvtable_slots.py --out config/SLUS-20836/names/GetVTableSlots.tsv
"""
import argparse
import json
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
ELF_DEFAULT = os.environ.get("DW4_ELF", os.path.join(REPO, "orig", "SLUS-20836", "SLUS_208.36"))
SYMBOLS = os.path.join(REPO, "config", "SLUS-20836", "symbols.txt")
MODULE = "engine"
VADDR_BASE, FILE_BASE = 0x100000, 0x80
VLO, VHI = 0x500000, 0x580000          # .rodata / .data, where a vtable lives
MAX_SLOT = 62


def load_symbols(path):
    rows = []
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        rows.append((int(p[0], 16), int(p[1], 16), p[2]))
    return rows


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", default=ELF_DEFAULT)
    ap.add_argument("--out", default=None)
    ap.add_argument("--json", default=None,
                    help="also write the vtable -> {class, slots} map for the RTTI-less "
                         "vtables (the port's method-dispatch table, P2.6)")
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args()

    image = open(a.elf, "rb").read()

    def word(va):
        off = va - VADDR_BASE + FILE_BASE
        if not 0 <= off <= len(image) - 4:
            return None
        return struct.unpack_from("<I", image, off)[0]

    rows = load_symbols(SYMBOLS)
    syms = {v: n for v, _, n in rows}
    named = lambda n: bool(n) and not n.startswith(("FUN_", "thunk_"))

    vt = json.load(open(os.path.join(REPO, "data", "vtables.json")))
    rtti_by_addr = vt["rtti"]
    rtti_vtables = vt["vtables"]
    rtti_slot_names = vt["names"]
    ambiguous = {int(x["addr"], 16) for x in vt["ambiguous"]}

    def class_vtable(va, size):
        """The first rodata-range value stored to a stack slot (finding #368)."""
        reg = {}
        for k in range(size // 4):
            ins = word(va + 4 * k)
            if ins is None:
                break
            op, rs, rt, imm = ins >> 26, (ins >> 21) & 0x1F, (ins >> 16) & 0x1F, ins & 0xFFFF
            if op == 0x0F:                                        # lui
                reg[rt] = imm << 16
            elif op in (0x09, 0x0D) and rs in reg:                # addiu / ori
                reg[rt] = reg[rs] + (imm - 0x10000 if imm & 0x8000 else imm)
            elif op == 0x2B and rs == 29:                         # sw rt,imm(sp)
                v = reg.pop(rt, None)
                if v is not None and VLO <= v < VHI:
                    return v
            else:
                reg.pop(rt, None)
        return None

    # every class's own vtable, from its <Class>_GetVTable function
    vtable_of = {}
    for addr, size, n in rows:
        if not n.endswith("_GetVTable"):
            continue
        v = class_vtable(addr, size)
        if v:
            vtable_of.setdefault(v, []).append(n[:-len("_GetVTable")])

    # namespace from the nearest RTTI ancestor (the RTTI record carries `Gap::Core::` etc.)
    ns_of = {}
    for _k, o in rtti_by_addr.items():
        nm = o["name"]
        if "::" in nm:
            ns_of.setdefault(nm.split("::")[-1], "::".join(nm.split("::")[:-1]))
    parent = {}
    for ln in open(os.path.join(REPO, "data", "class-hierarchy.tsv")):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.rstrip("\n").split("\t")
        if len(p) >= 2:
            parent[p[0]] = p[1]

    def namespace(cls):
        seen = set()
        while cls and cls not in seen:
            if cls in ns_of:
                return ns_of[cls]
            seen.add(cls)
            cls = parent.get(cls)
        return None

    # the vtables the RTTI pass already covered are named; the rest are the queue
    rtti_addrs = {int(k, 16) for k in rtti_vtables}
    unique = {v: cs[0] for v, cs in vtable_of.items() if len(cs) == 1}
    slots_of = {c: [word(v + 4 * s) for s in range(MAX_SLOT)] for v, c in unique.items()}

    # a body used by more than one class is a shared default, not this class's override (T7)
    users = {}
    for c, slots in slots_of.items():
        for s, body in enumerate(slots):
            if body:
                users.setdefault(body, set()).add(c)

    def ancestors(c):
        out, seen = [], set()
        while c in parent and parent[c] not in seen:
            c = parent[c]
            seen.add(c)
            out.append(c)
        return out

    out, skipped_ns = [], 0
    for v, cls in sorted(unique.items(), key=lambda kv: (kv[1], kv[0])):
        if v in rtti_addrs:
            continue                                  # the RTTI pass owns this vtable
        ns = namespace(cls)
        if not ns:
            skipped_ns += 1
            continue
        for s in range(2, MAX_SLOT):
            body = slots_of[cls][s]
            if not body:
                continue
            gen = "%s::%s::vfunc_%02d" % (ns, cls, s)
            n = syms.get(body, "")
            # `FUN_` before the batch; after `apply_names.py` the symbol carries the generated
            # name, so emit it either way or a re-run would write an empty overlay.
            if body in ambiguous or (n.startswith("FUN_") is False
                                     and n != gen.replace("::", "__")):
                continue
            if len(users.get(body, set())) != 1:
                continue                              # shared body (inherited default)
            if any(c in slots_of and slots_of[c][s] == body for c in ancestors(cls)):
                continue                              # inherited from a resolved ancestor
            out.append((body, gen))

    seen = set()
    lines = ["# Vtable slots of the classes that emit no __RTTI__ record, named from the class's",
             "# own <Class>_GetVTable vtable (finding #368's rule) and the slot index.",
             "# GENERATED by scripts/seed_names_getvtable_slots.py."]
    for addr, name in sorted(out):
        if addr in seen:
            continue
        seen.add(addr)
        lines.append("0x%08x\t%s\t%s" % (addr, name, MODULE))
    text = "\n".join(lines) + "\n"

    if a.json and not a.check:
        m = {}
        for v, cls in sorted(unique.items(), key=lambda kv: kv[1]):
            if v in rtti_addrs:
                continue
            ns = namespace(cls)
            if not ns:
                continue
            slots = slots_of[cls]
            m["0x%06x" % v] = {
                "class": "%s::%s" % (ns, cls),
                "vfuncs": [("0x%08x" % b) if b else None for b in slots],
            }
        with open(a.json, "w") as fh:
            json.dump(m, fh, indent=1, sort_keys=True)
            fh.write("\n")
        print("seed_names_getvtable_slots: wrote %s (%d vtable(s))" % (a.json, len(m)))

    if a.check:
        cur = open(a.out).read() if a.out and os.path.exists(a.out) else ""
        if cur != text:
            print("seed_names_getvtable_slots: %s is stale" % (a.out or "-"))
            return 1
        print("seed_names_getvtable_slots: current (%d name(s))" % (len(seen)))
        return 0
    if a.out:
        open(a.out, "w").write(text)
        print("seed_names_getvtable_slots: wrote %s (%d name(s); %d vtable(s) with no namespace "
              "skipped)" % (a.out, len(seen), skipped_ns))
    else:
        sys.stdout.write(text)
    print("%d name(s) over %d RTTI-less vtable(s)" % (len(seen), len(unique)),
          file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
