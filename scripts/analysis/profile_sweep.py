#!/usr/bin/env python3
"""profile_sweep.py — every matched MWCC function under each candidate profile, by library.

Compiles with the unit tables disabled, so a function gets exactly the candidate, and writes
nothing under config/ or data/. Stock libraries and GCC rows are left out. A function counts as
discriminating when some candidates reproduce it and others do not; the rest say nothing about
the build. Results and their reading: docs/engine/build-profiles.md.

  python3 scripts/analysis/profile_sweep.py results.jsonl --jobs 16
"""
import argparse
import bisect
import collections
import json
import multiprocessing
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import regions  # noqa: E402
import units as unitfiles  # noqa: E402
import verify as vfy  # noqa: E402

COMPILERS = {"3.0": "local/mwcps2/3.0-011126/mwccps2.exe",
             "3.0.3": "local/mwcps2/3.0.3-020716/mwccps2.exe",
             "b38": "local/mwcps2/3.0b38-030307/mwccps2.exe"}
CANDIDATES = [(c, o) for o in ("-O3", "-O3,p") for c in COMPILERS]
SYMBOLS = "config/SLUS-20836/symbols.txt"
PLAIN_FLAGS = {"-O3 -Iinclude", "-O3,p -Iinclude", "-O4 -Iinclude", "-O4,p -Iinclude"}


def tasks():
    rows = []
    for line in open("config/SLUS-20836/units.tsv"):
        p = line.rstrip("\n").split("\t")
        if line[0] not in "#@" and len(p) > 6:
            rows.append((int(p[0], 16), int(p[1], 16), p[4], p[5]))
    rows.sort()
    starts = [r[0] for r in rows]
    paths = unitfiles.scan("src")
    out = []
    for line in open("data/check-categories.tsv"):
        if line[0] == "#":
            continue
        va, name, cat = line.split("\t")[:3]
        va = int(va, 16)
        region = regions.of(va)
        unit = rows[bisect.bisect_right(starts, va) - 1]
        if (region.build == "mwcc" and region.id not in ("libpng", "zlib", "lua") and name in paths
                and unit[0] <= va < unit[1] and unit[2] in PLAIN_FLAGS):
            out.append(dict(va=va, name=name, path=paths[name], exceptions=unit[3], category=cat,
                            region=region.id))
    return out


def sweep(task):
    source, temporary = unitfiles.standalone(task["path"], task["name"], symbols=SYMBOLS, unit_objects=None)
    results = {}
    try:
        for compiler, level in CANDIDATES:
            flags = level + " -Iinclude" + (" -Cpp_exceptions off" if task["exceptions"] == "off" else "")
            ok, _report = vfy.verify_one(task["va"], source, flags=flags, mwcc=COMPILERS[compiler],
                                         unit_flags="/dev/null", unit_compilers="/dev/null",
                                         units="/dev/null", unit_objects=None)
            results["%s %s" % (compiler, level)] = bool(ok)
    finally:
        if temporary:
            os.remove(temporary)
    return dict(task, results=results)


def kind(name):
    m = re.search(r"_(GetVTable|GetMetaObject|InitFields)$", name)
    return m.group(1) if m else "method"


def report(rows):
    names = ["%s %s" % c for c in CANDIDATES]
    print("%-24s %6s  %s" % ("discriminating", "n", " ".join("%12s" % n for n in names)))
    for label, key in (("by library", lambda r: r["region"]), ("by kind", lambda r: kind(r["name"]))):
        print(label)
        groups = collections.defaultdict(list)
        for r in rows:
            values = list(r["results"].values())
            if any(values) and not all(values):
                groups[key(r)].append(r)
        for group, members in sorted(groups.items()):
            print("%-24s %6d  %s" % (group, len(members), " ".join(
                "%11.1f%%" % (100.0 * sum(m["results"][n] for m in members) / len(members)) for n in names)))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("out")
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--limit", type=int, default=0, help="only the first N functions")
    a = ap.parse_args()
    work = tasks()[:a.limit or None]
    with multiprocessing.Pool(a.jobs) as pool, open(a.out, "w") as fh:
        rows = []
        for row in pool.imap_unordered(sweep, work, chunksize=8):
            rows.append(row)
            fh.write(json.dumps(row) + "\n")
    report(rows)
    return 0


if __name__ == "__main__":
    sys.exit(main())
