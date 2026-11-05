#!/usr/bin/env python3
"""seed_receiver_classes.py — receiver classes for unnamed `FUN_` functions, without naming them.

`retype_receiver_class.py` takes a function's receiver class from its *name*.  Many matched
`FUN_` functions cannot be named (their role is unknown) yet their receiver class is determined
by evidence.  This generator emits `config/SLUS-20836/receiver-classes.tsv` (`<va> <class> <rule>`), which the
retyper reads in addition to names.  Only a receiver *type* is recorded here, never a method name.

Rules (each is recovered from the binary, none from decompiler output):

  vtable-slot   The function is a slot of the vtables of one or more classes
                (`data/vtables.json`, `data/vtables-getvtable.json`).  The owner is the nearest
                common ancestor of those classes (`data/class-hierarchy.tsv`); the rule fires only
                when the owner is not bare `igObject` (a shared stub/default) and **every** offset
                the matched C applies to the receiver is a reflected field of the owner or an
                ancestor (`data/reflection.json`).
  vtable-stamp  The function stores exactly one known vtable at `+0` of its own receiver (a
                constructor shape).  A function stamping several vtables is an inlined base-chain
                constructor and is left out.

  scripts/seed_receiver_classes.py                      # print the rows
  scripts/seed_receiver_classes.py --out config/SLUS-20836/receiver-classes.tsv
  scripts/seed_receiver_classes.py --out config/SLUS-20836/receiver-classes.tsv --check
"""
import argparse
import collections
import glob
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
sys.path.insert(0, os.path.join(REPO, "tools"))
from typed_coverage import split_functions  # noqa: E402

INS_RE = re.compile(r"/\* ([0-9a-f]{8}): (\S+)\s*(.*?) \*/")
CAST_RE = re.compile(r"\*\(\s*(?:unsigned )?[\w ]+\s*\*\s*\)\s*\(\s*\(\s*char\s*\*\s*\)\s*\(?\s*arg0\s*\)?"
                     r"\s*\+\s*(\d+)\s*\)")
FUN_DEF = re.compile(r"\bFUN_([0-9a-f]{8})\s*\(")


def short(c):
    return c.split("::")[-1]


def load():
    vt = json.load(open(os.path.join(REPO, "data", "vtables.json")))
    gv = json.load(open(os.path.join(REPO, "data", "vtables-getvtable.json")))
    refl = json.load(open(os.path.join(REPO, "data", "reflection.json")))
    hier = {}
    for ln in open(os.path.join(REPO, "data", "class-hierarchy.tsv")):
        if ln.startswith("#") or not ln.strip():
            continue
        a, b = ln.split()[:2]
        hier[a] = b
    fields = {short(c["class"]): {f["offset"] for f in c["fields"]} for c in refl["classes"].values()}
    return vt, gv, hier, fields


def chain(hier, c):
    out = [c]
    while out[-1] in hier and len(out) < 30:
        out.append(hier[out[-1]])
    return out


def receiver_offsets():
    """{va: sorted offsets applied to arg0} for every FUN_ definition in src/."""
    out = {}
    for path in glob.glob(os.path.join(REPO, "src", "**", "*.c*"), recursive=True):
        text = open(path, errors="replace").read()
        for name, _sig, start, end in split_functions(text):
            m = re.fullmatch(r"FUN_([0-9a-f]{8})", name)
            if not m:
                continue
            offs = sorted({int(c.group(1)) for c in CAST_RE.finditer(text[start:end])})
            if offs:
                out[int(m.group(1), 16)] = offs
    return out


def stamps(vtable_class):
    """{va: [vtable addresses stored at +0 of the receiver, in order]} from asm/."""
    res = {}
    for path in glob.glob(os.path.join(REPO, "asm", "FUN_*.s")):
        text = open(path, errors="replace").read()
        m = re.search(r"— 0x([0-9a-f]{8}),", text)
        if not m:
            continue
        regs = {"a0": "ARG0"}
        found = []
        after_call = False        # a call's delay slot still sees (and may set) its argument registers
        for _a, op, args in INS_RE.findall(text):
            p = [x.strip() for x in args.split(",")] if args else []
            if after_call:
                after_call = False
                if op == "move" and len(p) == 2:
                    regs[p[0]] = regs.get(p[1])
                regs = {k: v for k, v in regs.items() if k.startswith("s")}
                continue
            if op == "move" and len(p) == 2:
                regs[p[0]] = regs.get(p[1])
            elif op == "lui" and len(p) == 2:
                regs[p[0]] = ("hi", int(p[1], 0) << 16)
            elif op in ("addiu", "ori") and len(p) == 3:
                b = regs.get(p[1])
                if isinstance(b, tuple):
                    regs[p[0]] = ("c", b[1] + int(p[2], 0))
                else:
                    regs[p[0]] = "ARG0" if (b == "ARG0" and int(p[2], 0) == 0) else None
            elif op == "sw" and len(p) == 2:
                mm = re.match(r"(-?\d+)\((\w+)\)", p[1])
                if mm and int(mm.group(1)) == 0 and regs.get(mm.group(2)) == "ARG0":
                    v = regs.get(p[0])
                    if isinstance(v, tuple) and 0x480000 <= v[1] < 0x554000:   # any rodata address, known or not
                        found.append(v[1])
            elif op.startswith("j") or op.startswith("b"):
                if op == "jal":
                    after_call = True
            elif p and not op.startswith("s"):
                regs[p[0]] = None
        if found:
            res[int(m.group(1), 16)] = found
    return res


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out")
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args()
    vt, gv, hier, fields = load()
    vtable_class = {int(k, 16): short(v["class"]) for k, v in vt["vtables"].items()}
    for k, v in gv.items():
        vtable_class.setdefault(int(k, 16), short(v["class"]))

    def avail(c):
        o = {0}          # the vtable pointer is not a reflected field
        for k in chain(hier, c):
            o |= fields.get(k, set())
        return o

    slot_classes = collections.defaultdict(set)
    for tbl in (vt["vtables"], gv):
        for x in tbl.values():
            for f in x["vfuncs"]:
                if f:
                    slot_classes[int(f, 16)].add(short(x["class"]))
    offs = receiver_offsets()
    rows = {}
    for va, o in offs.items():
        cs = slot_classes.get(va)
        if not cs:
            continue
        chains = [chain(hier, c) for c in cs]
        common = [c for c in chains[0] if all(c in ch for ch in chains)]
        owner = common[0] if common else None
        if owner and owner != "igObject" and all(x in avail(owner) for x in o):
            rows[va] = (owner, "vtable-slot")
    for va, found in stamps(vtable_class).items():
        if va in rows or va not in offs or len(set(found)) != 1 or found[0] not in vtable_class:
            continue
        c = vtable_class[found[0]]
        if all(x in avail(c) for x in offs[va]):
            rows[va] = (c, "vtable-stamp")
    lines = ["# Receiver classes for unnamed functions (type only, never a method name).",
             "# GENERATED by scripts/seed_receiver_classes.py; do not hand-edit.",
             "# va\tclass\trule"]
    lines += ["0x%08x\t%s\t%s" % (va, c, r) for va, (c, r) in sorted(rows.items())]
    text = "\n".join(lines) + "\n"
    if a.check:
        cur = open(a.out).read() if a.out and os.path.exists(a.out) else ""
        print("seed_receiver_classes: %s" % ("current (%d row(s))" % len(rows) if cur == text else "stale"))
        return 0 if cur == text else 1
    if a.out:
        open(a.out, "w").write(text)
        print("seed_receiver_classes: wrote %s (%d row(s))" % (a.out, len(rows)))
    else:
        sys.stdout.write(text)
    return 0


if __name__ == "__main__":
    sys.exit(main())
