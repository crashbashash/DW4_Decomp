#!/usr/bin/env python3
"""module_map.py — which region of game.elf belongs to which library (evidence, not guesswork).

P1 was aiming at the 2,097 raw casts applied to a function's receiver, on the theory that naming the
owning function makes them typeable.  Before spending months on that, ask *whose* functions they are.
`config/SLUS-20836/symbols.txt` has addresses but still names 738 of the receivers `FUN_*`; the strings each
function references say what it is, because vendor code is loud about itself:

    0x20d040  'Intrinsic Alchemy  v3.2 -0810 (Static/Release) ... Built by terada on Tue Aug 10 ...'
    0x1f7530  'p2readGSPrivRegister(%d)'           <- the PS2 renderer backend
    0x24c990  'last token read: `%.30s'\'' at line %d in %.80s'   <- Lua 4.0
    0x28b0d0  'CRI M2V/PS2EE Ver.1.945 Build:Oct  6 2004 ...'    <- CRIWARE
    0x23d...  'Unsupported metafield type %s'      <- Alchemy's type system

So the map is mechanical: contiguous runs of symbols (a run is the original translation unit -- MWCC
emits in source order), each labelled by the strings its functions reference.  The `LABELS` table
below is the human judgement about those strings, printed next to the evidence so it can be checked
and corrected; everything else is derived.

    scripts/module_map.py                      # print
    scripts/module_map.py --out docs/engine/module-map.md
"""
import argparse
import bisect
import json
import os
import re
import sys
from collections import defaultdict

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.join(HERE, "..")

# Judgement calls about the evidence strings, ordered by address.  Each is checked by reading the
# strings printed beside it; a wrong one shows up as a run whose evidence contradicts its label.
LABELS = [
    (0x100000, 0x130000, "Sony SDK + C runtime",
     "libdma / libmpeg / libipu / libcdvd / libsd / sio2+padman+mtapman, and libc: malloc's "
     "`max system bytes`, vfprintf's `bug in vfprintf: bad base`"),
    (0x130000, 0x1F0000, "Intrinsic Alchemy core (graphics, math, shaders, GS/VU1)",
     "`IG_GFX_*` capability constants, shader attribute names, the VU1 ucode symbol table; "
     "`ig*` class functions from 0x130060"),
    (0x1F0000, 0x20D000, "Alchemy `p2` -- the PS2/EE renderer backend",
     "`p2LoadTexture`, `p2lighting`, `p2readGSPrivRegister`, `swapbuffersPredicate`"),
    (0x20D000, 0x221870, "libpng",
     "`Incompatible libpng version`, chunk errors; stock 1.0.8 from 0x20e750"),
    (0x221870, 0x2252D8, "zlib", "`incorrect data check`, `invalid stored block lengths`; stock 1.1.3"),
    (0x2252D8, 0x226000, "Sony libmtap and small units", "`sceMtap`"),
    (0x226000, 0x246D30, "Alchemy insight / registry / serialisation",
     "`Unsupported metafield type %s`, `Possible options are :`, `showRegistryQueries`"),
    (0x246D30, 0x2590C0, "Lua 4.0",
     "`_ERRORMESSAGE`, `last token read`, `too many %.50s (limit=%d)`; stock 4.0.1, `luaA_index` first"),
    (0x2590C0, 0x25D000, "Alchemy core (igb file, frame rate)",
     "`ndmw.igb`, `average frame rate over %d frames`; `alchemy.ini`'s pool table"),
    (0x25D000, 0x2B0000, "CRIWARE (ADX, Sofdec/SFD, MPS, SUD, PS2RNA)",
     "`E9040801:partition ID is range outside.(adxf_ChkPrmPt)`, `CRI M2V/PS2EE Ver.1.945`, "
     "`PS2RNA Ver.1.30`"),
    (0x2B0000, 0x2B5DA0, "CRI audio (SNDF / SUD / MWSFD)",
     "`SNDF Ver.2.09c`, `sfxcnv_MakeTable`, `MWSFD/PS2EE Ver.3.33s281`"),
    (0x2B5DA0, 0x2D1000, "Alchemy metafields and reflection",
     "`ig*MetaField` class functions from `igVirtualCFuncMetaField` at 0x2b5da0"),
    (0x2D1000, 0x310000, "Alchemy core (registry, ini, memory pools)",
     "`Intrinsic Alchemy  v3.2 -0810`, `drivers.ini`, `alchemy.ini`, `igContextExt`"),
    (0x310000, 0x338C00, "Alchemy memory pools + IOP module loader",
     "`igArenaMemoryPool::checkHeap(E71)`, `Pool igStackMemoryPool`, `\\MODULES\\%s`"),
    (0x338C00, 0x44B860, "GAME (be* objects, MODELCTRL, STAGECTL, menus)",
     "`MODELCTRL`, `GETMATRIX`, `GAMERAM`, `STAGECTL`, `font000`, the menu `SQ_*` states; "
     "the start is a run boundary in the unnamed gap before the first `be*` at 0x33e880"),
    (0x44B860, 0x540000, "Alchemy scene, GUI, overlay and actor managers",
     "`Actor manager`, `Scenes done`, `Overlays done`, `current view matrix`"),
]


def syms():
    out = []
    for line in open(os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")):
        m = re.match(r"([0-9a-f]{8}) ([0-9a-f]{6}) (\S+)", line)
        if m:
            out.append((int(m.group(1), 16), int(m.group(2), 16), m.group(3)))
    out.sort()
    return out


def unnamed(name):
    return name.startswith(("FUN_", "thunk_", "Gap__"))


def strings_by_function():
    """{function address: [string, ...]} from every string's xrefs."""
    path = os.path.join(ROOT, "data", "strings.json")
    data = json.load(open(path))["strings"]
    out = defaultdict(list)
    for s in data:
        v = s["value"].strip()
        if len(v) < 7 or v.startswith("."):
            continue
        for x in s["xrefs"]:
            out[int(x["from"], 16)].append(v)
    return out


def runs_of(table):
    """Maximal runs of consecutive symbols inside one region -- a run is the original translation
    unit. The region edge matters as well as the gap: the symbols now tile most of the image, so
    the gap alone would join whole regions into one run."""
    out, cur = [], []
    for a, size, name in table:
        if cur and (a - (cur[-1][0] + cur[-1][1]) > 16 or label_of(a) != label_of(cur[0][0])):
            out.append(cur)
            cur = []
        cur.append((a, size, name))
    if cur:
        out.append(cur)
    return out


def label_of(addr):
    for lo, hi, name, _ev in LABELS:
        if lo <= addr < hi:
            return name
    return "other"


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--out")
    ap.add_argument("--min", type=int, default=0x800, help="smallest run to list (default 0x800)")
    ap.add_argument("--check", action="store_true",
                    help="fail if docs/engine/module-map.md is stale (for `make rules`)")
    ap.add_argument("--default-out", default="docs/engine/module-map.md")
    args = ap.parse_args()

    table = syms()
    starts = [a for a, _s, _n in table]
    strs = strings_by_function()
    rows = []
    for run in runs_of(table):
        lo = run[0][0]
        hi = run[-1][0] + run[-1][1]
        if hi - lo < args.min:
            continue
        n_unnamed = sum(1 for _a, _s, n in run if unnamed(n))
        seen = []
        for a, _s, _n in run:
            for v in strs.get(a, ()):
                if v not in seen:
                    seen.append(v)
        rows.append((lo, hi, hi - lo, len(run), n_unnamed, label_of(lo), seen))

    # per-region totals
    tot = defaultdict(lambda: [0, 0, 0])          # label -> [runs, funcs, unnamed funcs]
    for lo, hi, size, n, nu, lab, _s in rows:
        tot[lab][0] += 1
        tot[lab][1] += n
        tot[lab][2] += nu

    out = []
    w = out.append
    w("# game.elf's module map\n")
    w("_Generated by `scripts/module_map.py` -- do not hand-edit._\n")
    w("`config/SLUS-20836/symbols.txt` carries an address for every function but only names some; the rest are "
      "`FUN_*`. The strings a function references identify it, and vendor code is loud about itself, "
      "so contiguous runs of symbols (a run is the original translation unit -- MWCC emits a unit's "
      "functions in source order) can be attributed to a library. The label table lives in "
      "`scripts/module_map.py` and is printed next to its evidence so it can be checked.\n")
    w("**Why it matters:** of the 2,097 raw casts applied to a function's receiver (finding #486), "
      "**1,676 (85%) are in third-party middleware**, not game code. Naming vendor internals buys "
      "nothing for either goal -- a port replaces the middleware wholesale -- so P1.3's queue is the "
      "game-code remainder.\n")
    w("## Regions\n")
    w("| range | size | funcs | unnamed | region |")
    w("| --- | --- | --- | --- | --- |")
    for lo, hi, name, _ev in LABELS:
        t = tot.get(name, [0, 0, 0])
        w("| `0x%06x`-`0x%06x` | %d | %d | %d | %s |" % (lo, hi, hi - lo, t[1], t[2], name))
    w("")
    w("## Runs, with the strings that identify them\n")
    w("| start | end | bytes | funcs | unnamed | region | evidence |")
    w("| --- | --- | --- | --- | --- | --- | --- |")
    cur_lab = None
    for lo, hi, size, n, nu, lab, seen in rows:
        if lab != cur_lab:
            w("| | | | | | **%s** | |" % lab)
            cur_lab = lab
        ev = "; ".join("`%s`" % s.replace("|", "\\|")[:60] for s in seen[:3])
        w("| `0x%06x` | `0x%06x` | %d | %d | %d | %s | %s |"
          % (lo, hi, size, n, nu, lab.split(" (")[0], ev))
    w("")

    text = "\n".join(out)
    if args.check:
        cur = open(os.path.join(ROOT, args.default_out)).read()
        if cur != text:
            print("module_map: %s is STALE -- regenerate: scripts/module_map.py --out %s"
                  % (args.default_out, args.default_out))
            return 1
        print("module_map: %s is current (%d runs)" % (args.default_out, len(rows)))
        return 0
    if args.out:
        open(os.path.join(ROOT, args.out), "w").write(text)
        print("wrote %s (%d runs)" % (args.out, len(rows)))
    else:
        print(text)
    return 0


if __name__ == "__main__":
    sys.exit(main())
