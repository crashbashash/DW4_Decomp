#!/usr/bin/env python3
"""datamap.py — how much of the binary's *data* the repo has identified.

Decomp projects are usually read on two numbers, code and data: a code bar and a data bar
against 1.50 MB of data. This repo reported **only code**, which made a quarter of the
image invisible — and it is not untouched: the strings, the RTTI vtables, the jump
tables and the class handles have all been recovered, they are just not *code*, so
`tools/progress.py` never counted them. This is the second number.

What counts as data here: the image is **one merged section** (`0x100000..0x554b00`,
with a zero-initialised tail to `0x58d280`), so there are no sections to divide —
`tools/layout.py` already tiles the whole section into `code` (function) units and the
data regions between them, and that tiling is the definition used. `datamap` then
classifies each data byte from the metadata the repo has actually recovered:

| kind | source | size |
| --- | --- | --- |
| `code` | `config/SLUS-20836/layout.txt` (`code` units — the functions) | the `symbols.txt` extents |
| `jtbl` | `config/SLUS-20836/layout.txt` (`jtbl` units) | from `config/SLUS-20836/jumptables.txt` |
| `vtable` | `data/vtables.json` (RTTI) and `data/vtables-getvtable.json` (each class's `GetVTable`) | `8 + 4 × len(vfuncs)`, the GetVTable dumps cut at the next labelled address |
| `str` | `data/strings.json` | `length + 1`, for the strings that are actually in the image |
| `handle` | `data/reflection.json` | 4 bytes per class handle (they live in the `.bss` tail) |
| `named` | `config/SLUS-20836/data-names.tsv` (the data rows) | see below |
| `?` | everything else | alignment padding, unrecovered tables, other `.bss` |

A name gives a datum's start, not its size, so `named` claims only what the evidence bounds: a
reflection table (`field-table`, `ctor-table`, `callback-list`) or a `_vtable` runs to the next
labelled address (at most 1 KB); any other named datum counts one word. Function symbols and the
rows `str`/`handle` already cover are not counted again.

`?` is the honest remainder, not a failure: it holds alignment, the tables whose
extent is not yet pinned, and the rest of `.bss`.

Usage:
  datamap.py                # the breakdown
  datamap.py --json         # machine-readable (used by tools/progress.py)
  datamap.py --list-vtables # every vtable region, for spot checks
"""
import argparse
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LAYOUT = os.path.join(ROOT, "config", "SLUS-20836", "layout.txt")
VTABLES = os.path.join(ROOT, "data", "vtables.json")
STRINGS = os.path.join(ROOT, "data", "strings.json")
REFLECTION = os.path.join(ROOT, "data", "reflection.json")

# The image: the one file-backed section, plus the zero-initialised tail the loader
# still maps (`tools/m2c_batch.py:load_bounds` reads both from the program headers).
IMG_LO, IMG_HI = 0x100000, 0x58D280
KINDS = ["code", "jtbl", "vtable", "str", "handle", "named", "?"]
DATA_NAMES = os.path.join(ROOT, "config", "SLUS-20836", "data-names.tsv")
GETVTABLES = os.path.join(ROOT, "data", "vtables-getvtable.json")
NOT_DATA = ("function-symbol", "published-accessor", "string-literal", "class-name", "class-handle")
TABLE_RULES = ("field-table", "ctor-table", "callback-list")
TABLE_CAP = 1024


def known_intervals():
    """-> [(lo, hi, kind)] from every recovered source, most specific first."""
    out = []
    for ln in open(LAYOUT):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        va, size, kind = int(p[0], 16), int(p[1], 16), p[2]
        if kind in ("code", "jtbl"):
            out.append((va, va + size, kind))
    vt = json.load(open(VTABLES))["vtables"]
    for addr, d in vt.items():
        a = int(addr, 16)
        out.append((a, a + 8 + 4 * len(d["vfuncs"]), "vtable"))
    for s in json.load(open(STRINGS))["strings"]:
        a = int(s["address"], 16)
        if IMG_LO <= a < IMG_HI:              # some entries are at 0 (not in the image)
            out.append((a, a + s["length"] + 1, "str"))
    for c in json.load(open(REFLECTION))["classes"].values():
        a = int(c["handle"], 16)
        if IMG_LO <= a < IMG_HI:
            out.append((a, a + 4, "handle"))
    out += bounded_intervals(out)
    return out


def bounded_intervals(known):
    """GetVTable vtables and named data, each cut at the next labelled address."""
    import bisect
    named = []
    for ln in open(DATA_NAMES):
        p = ln.rstrip("\n").split("\t")
        if ln.startswith("#") or len(p) < 3 or p[2] in NOT_DATA:
            continue
        a = int(p[0], 16)
        if IMG_LO <= a < IMG_HI:
            named.append((a, p[1], p[2]))
    getv = [(int(k, 16), d) for k, d in json.load(open(GETVTABLES)).items()]
    starts = sorted({lo for lo, _hi, _k in known} | {a for a, _n, _r in named} | {a for a, _d in getv}
                    | {IMG_HI})

    def next_start(a):
        return starts[bisect.bisect_right(starts, a)]
    out = [(a, min(next_start(a), a + 8 + 4 * len(d["vfuncs"])), "vtable") for a, d in getv]
    for a, name, rule in named:
        if rule in TABLE_RULES or name.endswith("_vtable"):
            out.append((a, min(next_start(a), a + TABLE_CAP), "named"))
        else:
            out.append((a, min(next_start(a), a + 4), "named"))
    return out


def build():
    """A kind per image byte. `code`/`jtbl` win over a string that overlaps them."""
    rank = {k: i for i, k in enumerate(KINDS)}
    kinds = bytearray(len(KINDS)) * 0                       # placeholder, replaced below
    kinds = bytearray(IMG_HI - IMG_LO)
    unknown = KINDS.index("?")
    for i in range(len(kinds)):
        kinds[i] = unknown
    # rare-first so the more specific kind wins an overlap; `?` is never written
    for lo, hi, kind in sorted(known_intervals(), key=lambda t: -rank[t[2]]):
        lo = max(lo, IMG_LO)
        hi = min(hi, IMG_HI)
        if hi > lo:
            kinds[lo - IMG_LO:hi - IMG_LO] = bytes([rank[kind]]) * (hi - lo)
    return kinds


def summarise(kinds):
    counts = {k: 0 for k in KINDS}
    for b in kinds:
        counts[KINDS[b]] += 1
    code = counts["code"]
    data = sum(v for k, v in counts.items() if k != "code")
    identified = data - counts["?"]
    return {
        "image_bytes": len(kinds),
        "code_bytes": code,
        "data_bytes": data,
        "identified_data_bytes": identified,
        "unidentified_data_bytes": counts["?"],
        "kinds": counts,
        "identified_data_pct": round(100.0 * identified / data, 2) if data else 0.0,
    }


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--list-vtables", action="store_true")
    a = ap.parse_args(argv)
    if a.list_vtables:
        for addr, d in sorted(json.load(open(VTABLES))["vtables"].items(),
                              key=lambda kv: int(kv[0], 16)):
            print("%s %5d bytes  %s" % (addr, 8 + 4 * len(d["vfuncs"]), d["class"]))
        return 0
    s = summarise(build())
    if a.json:
        print(json.dumps(s, indent=2, sort_keys=True))
        return 0
    print("image  %10d bytes" % s["image_bytes"])
    print("code   %10d bytes  %5.1f %% of the image"
          % (s["code_bytes"], 100.0 * s["code_bytes"] / s["image_bytes"]))
    print("data   %10d bytes  %5.1f %% of the image  (%5.1f %% of it identified)"
          % (s["data_bytes"], 100.0 * s["data_bytes"] / s["image_bytes"],
             s["identified_data_pct"]))
    for k in ("jtbl", "vtable", "str", "handle", "named", "?"):
        v = s["kinds"][k]
        print("   %-7s %9d bytes  %5.1f %% of the data"
              % (k, v, 100.0 * v / s["data_bytes"]))
    return 0


if __name__ == "__main__":
    sys.exit(main())
