#!/usr/bin/env python3
"""datamap.py — how much of the binary's *data* is matched from source, and what the rest is.

Decomp projects are read on two numbers, code and data. The data number is the bytes the
source defines and `make check` proved equal to retail (`source` below), the counterpart of
matched code; it moves only when a unit defines its data instead of referring to retail's
address. The other kinds classify the rest from the recovered metadata, which says what a
region is without making it decompiled.

What counts as data here: the image is **one merged section** (`0x100000..0x554b00`,
with a zero-initialised tail to `0x58d280`), so there are no sections to divide —
`tools/layout.py` already tiles the whole section into `code` (function) units and the
data regions between them, and that tiling is the definition used. `datamap` then
classifies each data byte, the first kind that claims it winning:

| kind | source | size |
| --- | --- | --- |
| `code` | `config/SLUS-20836/layout.txt` (`code` units — the functions) | the `symbols.txt` extents |
| `source` | `data/check-data.tsv` (data a fully matched unit defines and `make check` compared with retail, compiled into the section kind retail's region holds) and the `jtbl` units of fully matched owners | the compared sections |
| `jtbl` | `config/SLUS-20836/layout.txt` (`jtbl` units of the other owners) | from `config/SLUS-20836/jumptables.txt` |
| `exc` | `config/SLUS-20836/exceptions.txt` and the static-initializer table | 12-byte index records, the recorded table sizes |
| `literal` | the compiler's float and double pool | `0x554880`–`0x554974` |
| `vtable` | `data/vtables.json` (RTTI), `data/vtables-getvtable.json` (each class's `GetVTable`) and the `vtable` rows of `data/data-layout.tsv` | `8 + 4 × len(vfuncs)`, the header and the run of function starts |
| `str` | `data/strings.json` | `length + 1`, for the strings that are actually in the image |
| `handle` | `data/reflection.json` | 4 bytes per class handle (they live in the `.bss` tail) |
| `table` | `table` rows of `data/data-layout.tsv` | a run of pointers to known starts |
| `region` | the `data` rows of `config/SLUS-20836/regions.tsv` that say what they hold (VU1 microcode, Sony library descriptors, kernel patch arrays) | the row |
| `pad` | alignment after a datum of known size (functions included) | zero bytes before the next 8-aligned start, fewer than 16 |
| `named` | `config/SLUS-20836/data-names.tsv` (the data rows) | to the next start or sized end |
| `ref` | `ref` rows of `data/data-layout.tsv`: an address retail code forms | to the next start or sized end |
| `ptr` | `ptr` rows: an address only a pointer word in the data holds | to the next start or sized end |
| `?` | everything else | |

`source` is the data half of the decompilation: bytes compiled from `src/` and proven equal to retail,
the counterpart of matched code. Fully matched means a unit `make check` classifies `match` or
`assembly`, as for the code headline. The other kinds say what the remaining bytes are, not that
they are decompiled.

`named`, `ref` and `ptr` know where a datum starts, not where it ends. Such a datum, with its padding,
runs to the next start any source records or to the end of a datum of known size, never past its
section, so a datum nothing references that sits inside that span is counted with it. These bytes are
identified as belonging to a known datum or one next to it, and are published apart (`START_ONLY`)
from the data whose extent is recorded. scripts/data_layout.py reads the facts that need the retail
executable (code references, pointer runs, the zero bytes before each start) into
`data/data-layout.tsv`.

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
CHECK_DATA = os.path.join(ROOT, "data", "check-data.tsv")
CATEGORIES = os.path.join(ROOT, "data", "check-categories.tsv")
DATA_LAYOUT = os.path.join(ROOT, "data", "data-layout.tsv")
EXCEPTIONS = os.path.join(ROOT, "config", "SLUS-20836", "exceptions.txt")
REGIONS_TSV = os.path.join(ROOT, "config", "SLUS-20836", "regions.tsv")
FULLY_MATCHED = ("match", "assembly")

# The image: the one file-backed section, plus the zero-initialised tail the loader
# still maps (`tools/m2c_batch.py:load_bounds` reads both from the program headers).
IMG_LO, IMG_HI = 0x100000, 0x58D280
FILE_HI = 0x554B00
# Most specific first: an earlier kind wins a byte two sources claim.
KINDS = ["code", "source", "jtbl", "exc", "literal", "vtable", "str", "handle", "table", "region", "pad",
         "named", "ref", "ptr", "?"]
DATA_NAMES = os.path.join(ROOT, "config", "SLUS-20836", "data-names.tsv")
# kinds known by where a datum starts, not where it ends: their extent runs to the next datum
START_ONLY = ("named", "ref", "ptr")
GETVTABLES = os.path.join(ROOT, "data", "vtables-getvtable.json")
NOT_DATA = ("function-symbol", "published-accessor", "string-literal", "class-name", "class-handle")
# The compiler's float and double literals, reached through gp (tools/verify.py LITERAL_POOL), and the
# static-initializer table `__init_cpp` walks (verify.STATIC_INITIALIZERS).
LITERAL_POOL = (0x554880, 0x554974)
STATIC_INITIALIZERS = (0x522440, 0x522480)
# regions.tsv data rows that only say "data follows" rather than what it is
GENERIC_REGIONS = ("data", "vtables")
# The retail linker's output sections, each from its start: the section kind a compiled datum must have to be
# the one retail placed there. The read-only sequence starts at 0x4d1c10 (config/SLUS-20836/regions.tsv; the
# runtime's RTTI pointer there compiles read-only), the rest as docs/engine/data-regions.md measures them. The
# vtable section also holds the static-initializer table and the exception metadata, placed and counted apart.
REGIONS = ((0x481C00, ".data"), (0x4D1C10, ".rodata"), (0x522440, ".vtables"), (0x554880, ".sdata"),
           (0x554B00, ".sbss"), (0x554F00, ".bss"))


def region_kind(address):
    """The section kind retail's layout gives `address`, or None outside the data regions."""
    kind = None
    for start, name in REGIONS:
        if address >= start:
            kind = name
    return kind if address < IMG_HI else None


def matched_owners():
    """Names of the functions `make check` classified fully matched (data/check-categories.tsv)."""
    out = set()
    if os.path.exists(CATEGORIES):
        for ln in open(CATEGORIES):
            p = ln.rstrip("\n").split("\t")
            if not ln.startswith("#") and len(p) > 2 and p[2] in FULLY_MATCHED:
                out.add(p[1])
    return out


def source_rows():
    """(consistent, mismatched): [(lo, hi)] of the data rows of data/check-data.tsv whose unit is fully
    matched, split by whether the compiled section is of the kind retail's region holds. A literal
    compiled into `.data` at a read-only address, or a zero global in `.bss` at a `.data` address, has
    retail's bytes but not retail's section: the source still differs from the original, so it is not
    counted as matched."""
    consistent, mismatched = [], []
    if os.path.exists(CHECK_DATA):
        for ln in open(CHECK_DATA):
            p = ln.rstrip("\n").split("\t")
            if not ln.startswith("#") and len(p) > 4 and p[4] in FULLY_MATCHED:
                lo = int(p[0], 16)
                kind = ".rodata" if p[2] == "jump-table" else p[2]
                (consistent if region_kind(lo) == kind else mismatched).append((lo, lo + int(p[1])))
    return consistent, mismatched


def fixed_intervals():
    """[(lo, hi, kind)] whose extent the repository records outright: the exception index records and
    tables (config/SLUS-20836/exceptions.txt), the static-initializer table, the literal pool, and the
    data rows of config/SLUS-20836/regions.tsv that say what they hold (the VU1 microcode, the Sony
    library descriptors, the kernel patch arrays)."""
    out = [(STATIC_INITIALIZERS[0], STATIC_INITIALIZERS[1], "exc"), (LITERAL_POOL[0], LITERAL_POOL[1], "literal")]
    for ln in open(EXCEPTIONS):
        p = ln.split()
        if ln.startswith("#") or len(p) < 4:
            continue
        index = int(p[1], 16)
        out.append((index, index + 12, "exc"))
        if p[2] != "-":
            table = int(p[2], 16)
            out.append((table, table + int(p[3], 16), "exc"))
    for ln in open(REGIONS_TSV):
        p = ln.rstrip("\n").split("\t")
        if not ln.startswith("#") and len(p) > 5 and p[5] == "data" and p[2] not in GENERIC_REGIONS:
            out.append((int(p[0], 16), int(p[1], 16), "region"))
    return out


def layout_rows():
    """[(va, size, kind)] of data/data-layout.tsv (scripts/data_layout.py), or [] before it is generated."""
    if not os.path.exists(DATA_LAYOUT):
        return []
    out = []
    for ln in open(DATA_LAYOUT):
        p = ln.split()
        if not ln.startswith("#") and len(p) == 3:
            out.append((int(p[0], 16), int(p[1]), p[2]))
    return out


def known_intervals():
    """-> [(lo, hi, kind)] from every recovered source."""
    out = []
    matched = matched_owners()
    for ln in open(LAYOUT):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        va, size, kind = int(p[0], 16), int(p[1], 16), p[2]
        if kind == "jtbl" and len(p) > 4 and p[4] in matched:
            out.append((va, va + size, "source"))
        elif kind in ("code", "jtbl"):
            out.append((va, va + size, kind))
    out += [(lo, hi, "source") for lo, hi in source_rows()[0]]
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
    out += fixed_intervals()
    rows = layout_rows()
    out += [(va, va + size, kind) for va, size, kind in rows if size and kind != "zeros"]
    out += bounded_intervals(out, [va for va, _s, kind in rows if kind == "ref"],
                             [va for va, _s, kind in rows if kind == "ptr"],
                             {va + size: va for va, size, kind in rows if kind == "zeros"})
    return out


def bounded_intervals(known, refs, pointed, zero_gaps):
    """GetVTable vtables, the padding, and the data known only by where it starts.

    A name (config/SLUS-20836/data-names.tsv), a code reference (`ref`) or a data pointer (`ptr`, rows of
    data/data-layout.tsv) gives a datum's start; the datum, with any alignment padding after it, runs to
    the next start any source records or the end of a datum of known size, never past the end of its
    section (REGIONS) or of the image. A GetVTable dump is cut the same way.

    Padding follows a datum whose size is known: zero bytes up to the next start, fewer than 16 of them,
    and that start 8-aligned (4 in `.sbss`), the retail linker's placement rule (docs/engine/emitted-
    functions.md, "A unit's own data"). In the zero-initialised tail every byte is zero; in the file
    image `zero_gaps` ({start: first zero byte before it}, the `zeros` rows) says which bytes are.
    """
    import bisect
    named = []
    for ln in open(DATA_NAMES):
        p = ln.rstrip("\n").split("\t")
        if ln.startswith("#") or len(p) < 3 or p[2] in NOT_DATA:
            continue
        a = int(p[0], 16)
        if IMG_LO <= a < IMG_HI:
            named.append(a)
    getv = [(int(k, 16), d) for k, d in json.load(open(GETVTABLES)).items()]
    starts = sorted({lo for lo, _hi, _k in known} | set(named) | set(refs) | set(pointed)
                    | {a for a, _d in getv} | {s for s, _n in REGIONS} | {FILE_HI, IMG_HI})
    # where a datum known only by its start can end: the next start, or the end of a sized datum (what
    # follows that is a different datum or padding)
    bounds = sorted(set(starts) | {hi for _lo, hi, _k in known})

    def next_bound(a):
        return bounds[bisect.bisect_right(bounds, a)]
    out = [(a, min(next_bound(a), a + 8 + 4 * len(d["vfuncs"])), "vtable") for a, d in getv]
    out += [(a, next_bound(a), "named") for a in named]
    out += [(a, next_bound(a), "ref") for a in refs if IMG_LO <= a < IMG_HI]
    out += [(a, next_bound(a), "ptr") for a in pointed if IMG_LO <= a < IMG_HI]
    gap_starts = sorted(zero_gaps)
    for _lo, end, _kind in known:
        # a function is a datum of known size too: the zeros up to the next one are its alignment
        if not IMG_LO <= end < IMG_HI:
            continue
        following = starts[bisect.bisect_left(starts, end)]
        if end < FILE_HI:
            # the first datum start the zero-gap facts know after `end`, if no recorded start comes first
            i = bisect.bisect_right(gap_starts, end)
            if i == len(gap_starts) or zero_gaps[gap_starts[i]] > end or gap_starts[i] > following:
                continue
            following = gap_starts[i]
        align = 4 if region_kind(end) == ".sbss" else 8
        if 0 < following - end < 16 and following % align == 0:
            out.append((end, following, "pad"))
    return out


def build():
    """A kind per image byte. `code`, then `source`, win over a string that overlaps them."""
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
    start_only = sum(counts[k] for k in START_ONLY)
    mismatched, reach = 0, 0
    for lo, hi in sorted(source_rows()[1]):
        lo = max(lo, reach)
        if hi > lo:
            mismatched, reach = mismatched + hi - lo, hi
    return {
        "image_bytes": len(kinds),
        "code_bytes": code,
        "data_bytes": data,
        "matched_data_bytes": counts["source"],
        "kind_mismatch_bytes": mismatched,
        "identified_data_bytes": identified,
        "start_only_data_bytes": start_only,
        "unidentified_data_bytes": counts["?"],
        "kinds": counts,
        "matched_data_pct": round(100.0 * counts["source"] / data, 2) if data else 0.0,
        "identified_data_pct": round(100.0 * identified / data, 2) if data else 0.0,
        "start_only_data_pct": round(100.0 * start_only / data, 2) if data else 0.0,
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
    print("data   %10d bytes  %5.1f %% of the image  (%5.1f %% of it matched from source, %5.1f %% identified, "
          "%5.1f %% known only by where a datum starts)"
          % (s["data_bytes"], 100.0 * s["data_bytes"] / s["image_bytes"],
             s["matched_data_pct"], s["identified_data_pct"], s["start_only_data_pct"]))
    for k in KINDS[1:]:
        v = s["kinds"][k]
        print("   %-7s %9d bytes  %5.1f %% of the data"
              % (k, v, 100.0 * v / s["data_bytes"]))
    print("compared equal but compiled into another section kind than retail's region (not matched): %d bytes"
          % s["kind_mismatch_bytes"])
    return 0


if __name__ == "__main__":
    sys.exit(main())
