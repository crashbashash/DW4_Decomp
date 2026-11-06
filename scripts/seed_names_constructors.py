#!/usr/bin/env python3
"""seed_names_constructors.py — name unmatched constructors from the vtable they stamp.

The engine's object constructor shape is fixed: call `igObject_InitHeader`
(`0x2fef20`), stamp the class's vtable at `+0`, then zero the reflected fields.  So the vtable a
function writes into its `this` IS its class, and `data/vtables.json` maps that address to the class
name.  This generator finds every **unmatched** function with that shape and emits
`<Class>_Construct` for it.

  python3 scripts/seed_names_constructors.py                 # print the rows
  python3 scripts/seed_names_constructors.py --out config/SLUS-20836/names/Constructors.tsv

The result is not a guess: the vtable address is the class's own RTTI-backed vtable, so the class
half of the name is recovered; the `_Construct` role is recovered from the `igObject_InitHeader`
call plus the `+0` vtable stamp plus the field zeroing.
"""
import argparse
import json
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
LINE_RE = re.compile(r"^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)\s*(.*)$")


def disassemble(elf, lo, hi):
    out = subprocess.run(["mipsel-linux-gnu-objdump", "-d", "--start-address=%#x" % lo,
                          "--stop-address=%#x" % hi, elf], capture_output=True, text=True).stdout
    ins = []
    for line in out.splitlines():
        m = LINE_RE.match(line)
        if m:
            ins.append((int(m.group(1), 16), m.group(3), m.group(4)))
    return ins


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--elf", default=os.environ.get("DW4_ELF",
                    os.path.join(REPO, "orig", "SLUS-20836", "SLUS_208.36")))
    ap.add_argument("--out", default=None)
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args()
    vts = json.load(open(os.path.join(REPO, "data", "vtables.json")))["vtables"]
    vtable_class = {int(k, 16): v["class"].split("::")[-1] for k, v in vts.items()}
    fns = json.load(open(os.path.join(REPO, "data", "functions.json")))["functions"]

    # unmatched functions, in address order
    todo = []
    for f in fns:
        if not f["name"].startswith("FUN_") and not f["name"].startswith("thunk_FUN_"):
            continue
        todo.append((int(f["address"], 16), f["size"]))
    todo.sort()
    lo = min(a for a, _ in todo)
    hi = max(a + s for a, s in todo)
    ins = disassemble(a.elf, lo, hi)
    by_addr = {a: (mn, ops) for a, mn, ops in ins}
    # function membership
    import bisect
    starts = [a for a, _ in todo]

    rows = []
    for start, size in todo:
        stamps = []
        called_init = False
        for k in range(start, start + size, 4):
            if k not in by_addr:
                continue
            mn, ops = by_addr[k]
            if mn == "jal" and ops.strip() == "0x2fef20":
                called_init = True
            elif mn == "sw":
                mm = re.match(r"(\S+),(-?0x[0-9a-f]+|-?\d+)\((\S+)\)", ops)
                if mm and int(mm.group(2), 0) == 0 and mm.group(3) in ("s0", "a0", "v0", "s1", "s2"):
                    # the source register must hold a known vtable address: look back for lui/addiu
                    src = mm.group(1)
                    val = None
                    ctx = {}
                    for j in range(start, k, 4):
                        if j not in by_addr:
                            continue
                        mn2, ops2 = by_addr[j]
                        mm2 = re.match(r"(\S+),(0x[0-9a-f]+)", ops2) if mn2 == "lui" else None
                        if mm2:
                            ctx[mm2.group(1)] = int(mm2.group(2), 16) << 16
                        elif mn2 in ("addiu", "ori"):
                            mm3 = re.match(r"(\S+),(\S+),(0x[0-9a-f]+|-?\d+)", ops2)
                            if mm3 and mm3.group(2) in ctx:
                                v = int(mm3.group(3), 0)
                                if v > 32767:
                                    v -= 65536
                                ctx[mm3.group(1)] = (ctx[mm3.group(2)] + v) & 0xFFFFFFFF
                        elif mn2 in ("move", "addu"):
                            mm3 = re.match(r"(\S+),(\S+)$", ops2)
                            if mm3 and mm3.group(2) in ctx:
                                ctx[mm3.group(1)] = ctx[mm3.group(2)]
                    if src in ctx and ctx[src] in vtable_class:
                        val = ctx[src]
                    if val is not None:
                        stamps.append(val)
        if not called_init or not stamps:
            continue
        # the most-derived class is the last vtable stamped
        cls = vtable_class[stamps[-1]]
        if not cls.startswith("be"):
            continue          # game classes only, not the middleware (Alchemy `ig*`)
        rows.append((start, cls))

    # one `<Class>_Construct` per class, then `_Construct2`, ... by address
    seen = {}
    out = []
    for start, cls in sorted(rows):
        n = seen.get(cls, 0)
        seen[cls] = n + 1
        name = "%s_Construct" % cls if n == 0 else "%s_Construct%d" % (cls, n + 1)
        out.append((start, name, cls, len(rows)))
    lines = ["# Constructors recovered from the `igObject_InitHeader` + `+0` vtable stamp shape",
             "#.  GENERATED by scripts/seed_names_constructors.py.",
             "# The class comes from the stamped vtable in data/vtables.json, the role from the body."]
    for start, name, cls, _n in out:
        lines.append("0x%08x\t%s\tgame" % (start, name))
    text = "\n".join(lines) + "\n"
    if a.check:
        cur = open(a.out).read() if a.out and os.path.exists(a.out) else ""
        if cur != text:
            print("seed_names_constructors: %s is stale" % (a.out or "-"))
            return 1
        print("seed_names_constructors: current (%d name(s))" % len(out))
        return 0
    if a.out:
        open(a.out, "w").write(text)
        print("seed_names_constructors: wrote %s (%d name(s))" % (a.out, len(out)))
    else:
        sys.stdout.write(text)
    return 0


if __name__ == "__main__":
    sys.exit(main())
