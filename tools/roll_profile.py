#!/usr/bin/env python3
"""roll_profile.py — move whole units onto a profile, when every member still verifies there.

config/SLUS-20836/units.tsv is maintained, not regenerated: the sweeps tools/gen_unit_profiles.py
drew its first version from are not in the repository. This is how a unit changes profile. A unit
moves only when each function with source keeps its category or verifies there, and a unit holding the retail copy of a `duplicates` entry stays, since check.py compares
every emitted copy under that unit's profile. Overrides of the moved functions go with it.

  python3 tools/roll_profile.py --regions bec,ndmw --flags "-O4,p -sdatathreshold 2 -Iinclude"
  python3 tools/roll_profile.py --regions bec,ndmw --flags "..." --apply
"""
import argparse
import bisect
import collections
import json
import multiprocessing
import os
import re
import shutil
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import regions  # noqa: E402
import units as unitfiles  # noqa: E402
import verify  # noqa: E402

CONFIG = "config/SLUS-20836/"
UNITS = CONFIG + "units.tsv"
OVERRIDES = (CONFIG + "unit-flags.tsv", CONFIG + "unit-compilers.tsv")


def rows():
    out = []
    with open(UNITS) as fh:
        for line in fh:
            f = line.rstrip("\n").split("\t")
            if line[0] not in "#@" and len(f) > 6 and f[0].startswith("0x"):
                out.append((int(f[0], 16), int(f[1], 16), f[2], f[3], f[4], f[5]))
    return sorted(out)


def duplicate_holders():
    found = set()

    def walk(node, inside=False):
        if isinstance(node, dict):
            for key, value in node.items():
                walk(value, inside or key == "duplicates")
        elif isinstance(node, list):
            for value in node:
                walk(value, inside)
        elif inside and isinstance(node, str) and re.fullmatch(r"0x[0-9a-fA-F]+", node):
            found.add(int(node, 16))

    with open(CONFIG + "unit-objects.json") as fh:
        walk(json.load(fh))
    return found


def check(task):
    source, temporary = unitfiles.standalone(task["path"], task["name"], symbols=CONFIG + "symbols.txt",
                                             unit_objects=None)
    tables = task["tables"]
    try:
        # every candidate unit already moved, so a compiler-emitted copy is compared under the
        # profile its retail unit would have
        ok, report = verify.verify_one(task["va"], source, units=tables[0], unit_flags=tables[1],
                                       unit_compilers=tables[2])
    finally:
        if temporary:
            os.remove(temporary)
    found = re.search(r"\bcat=([\w-]+)", (report or "").partition("\n")[0])
    kind = found[1] if found else None
    return dict(task, passed=kind == task["category"] or bool(ok))


def main():
    parser = argparse.ArgumentParser(description=__doc__.partition("\n")[0])
    parser.add_argument("--regions", required=True, help="comma-separated ids of config/SLUS-20836/regions.tsv")
    parser.add_argument("--flags", required=True)
    parser.add_argument("--compiler", default="b52", help="an @compiler id of units.tsv")
    parser.add_argument("--jobs", type=int, default=os.cpu_count())
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()
    wanted = set(args.regions.split(","))
    units = rows()
    starts = [unit[0] for unit in units]
    holders = duplicate_holders()
    targets = {}
    for index, (start, end, _label, unit_compiler, flags, _exceptions) in enumerate(units):
        region = regions.of(start)
        if (region.id in wanted and regions.of(end - 1) is region and unit_compiler != "ee-gcc"
                and (unit_compiler, flags) != (args.compiler, args.flags)
                and "-lang" not in flags and not any(start <= held < end for held in holders)):
            targets[index] = units[index]
    paths = unitfiles.scan("src")
    scratch = tempfile.mkdtemp(prefix="roll_profile_")
    keys = {units[index][0] for index in targets}
    tables = [os.path.join(scratch, os.path.basename(path)) for path in (UNITS,) + OVERRIDES]
    with open(UNITS) as fh:
        lines = fh.readlines()
    for number, line in enumerate(lines):
        f = line.rstrip("\n").split("\t")
        if line[0] not in "#@" and len(f) > 6 and f[0].startswith("0x") and int(f[0], 16) in keys:
            f[3], f[4] = args.compiler, args.flags
            lines[number] = "\t".join(f) + "\n"
    with open(tables[0], "w") as fh:
        fh.writelines(lines)
    inside = [(units[index][0], units[index][1]) for index in targets]
    for path, copy in zip(OVERRIDES, tables[1:]):
        with open(path) as fh, open(copy, "w") as out:
            out.writelines(line for line in fh if not (line.startswith("0x") and any(
                lo <= int(line.split("\t")[0], 16) < hi for lo, hi in inside)))
    tasks = []
    with open("data/check-categories.tsv") as fh:
        for line in fh:
            if line[0] == "#":
                continue
            address, name, category = line.rstrip("\n").split("\t")[:3]
            va = int(address, 16)
            index = bisect.bisect_right(starts, va) - 1
            if index in targets and va < units[index][1] and name in paths:
                tasks.append(dict(va=va, name=name, path=paths[name], category=category, unit=index,
                                  tables=tables))
    with multiprocessing.Pool(args.jobs) as pool:
        results = pool.map(check, tasks, chunksize=4)
    shutil.rmtree(scratch)
    members = collections.defaultdict(list)
    for result in results:
        members[result["unit"]].append(result)
    moving = [index for index in targets if all(member["passed"] for member in members[index])]
    print("units %d, can move %d, functions blocking the rest %d"
          % (len(targets), len(moving), sum(not result["passed"] for result in results)))
    for result in results:
        if not result["passed"]:
            print("  0x%06x %s" % (result["va"], result["name"]))
    if not args.apply:
        return 0
    keys = {units[index][0] for index in moving}
    moved = {member["va"] for index in moving for member in members[index]}
    with open(UNITS) as fh:
        lines = fh.readlines()
    for number, line in enumerate(lines):
        f = line.rstrip("\n").split("\t")
        if line[0] not in "#@" and len(f) > 6 and f[0].startswith("0x") and int(f[0], 16) in keys:
            f[3], f[4], f[6] = args.compiler, args.flags, "-"
            lines[number] = "\t".join(f) + "\n"
    with open(UNITS, "w") as fh:
        fh.writelines(lines)
    for path in OVERRIDES:
        with open(path) as fh:
            kept = [line for line in fh if not (line.startswith("0x") and int(line.split("\t")[0], 16) in moved)]
        with open(path, "w") as fh:
            fh.writelines(kept)
    print("moved %d units" % len(moving))
    return 0


if __name__ == "__main__":
    sys.exit(main())
