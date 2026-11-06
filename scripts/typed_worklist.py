#!/usr/bin/env python3
"""typed_worklist.py — which *callee signatures* would unlock the most raw casts (P1.2's queue).

Typed coverage is stuck at the same place P1.2 found: of the raw `*(T *)((char *)x + N)` accesses in
the matched C, almost none apply the offset to the receiver.  They apply it to a temporary holding the
result of a **call**, so what is missing is the callee's return type — and `config/SLUS-20836/signatures.tsv`
holds the ones that have been recovered.  This tool says which callees to recover *next*, by counting
how many raw casts sit on each one's result:

    temp_s2 = igMetaObject_GetFieldAt(meta, i);
    ...
    *(int *)((char *)temp_s2 + 52) = ...;      <- 1 cast unlocked by that signature

Two buckets, because they need different work:

  * **callee has C in `src/`** — its own body is in the tree, so its `return` shape is inspectable:
    a signature can be *recovered* rather than guessed (look at what it returns and how the callers
    use it).  These are the cheap rows.
  * **callee has no C** — matched only as `asm/`, so recovering its type means reading the assembly.
    These are the archaeology rows.

and the rest are bucketed by where their base *does* come from, because each bucket needs a
different mechanism (P1.1's receiver rule, P1.2's signatures, or naming at all):

  * the receiver (`arg0`..)          -> a class for the function (naming, P1.3)
  * a declaration with a type        -> a stronger declared type, or a conversion
  * an undeclared `temp_sN`          -> the value's producer is not a plain call: inspect the body
  * a global (`DAT_...`, `0x...`)    -> the global's own class

  scripts/typed_worklist.py [--top 25] [--src src] [--json out.json]
"""
import argparse
import json
import os
import re
import sys
from collections import Counter, defaultdict

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "tools"))
import typed_coverage as TC      # noqa: E402
import module_map as MM          # noqa: E402  (region labels; see docs/engine/module-map.md)

GAME_REGIONS = tuple(r.label for r in MM.regions.load() if r.group == "Game")

ASSIGN_RE = "\\b%s\\s*=\\s*([^;]+);"
CALL_RE = re.compile(r"\b([A-Za-z_]\w*)\s*\(")


def functions_of(text):
    """[(name, body)] using the coverage tool's own splitter, so the counts agree."""
    return [(name, text[start:end]) for name, _args, start, end in TC.split_functions(text)]


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--src", default=os.path.join(HERE, "..", "src"))
    ap.add_argument("--reflection", default=os.path.join(HERE, "..", "data",
                                                         "reflection.json"))
    ap.add_argument("--top", type=int, default=25)
    ap.add_argument("--json")
    ap.add_argument("--by-region", action="store_true",
                    help="bucket the receiver casts by library (docs/engine/module-map.md)")
    ap.add_argument("--game-only", action="store_true",
                    help="count/list only game+engine code -- the P1.3 queue")
    args = ap.parse_args()
    classes = TC.load_classes(args.reflection)
    known = set(classes) if not isinstance(classes, dict) else set(classes.keys())

    region = Counter()            # library -> receiver casts
    region_funcs = defaultdict(set)
    receiver = Counter()          # function -> receiver casts (game code when --game-only)
    unlocked = Counter()          # callee -> raw casts whose base it produces
    funcs = defaultdict(set)      # callee -> functions affected
    examples = {}
    buckets = Counter()
    total_raw = 0
    have_c = set()
    asm_only = set()

    for root, _dirs, files in os.walk(args.src):
        for fn in sorted(files):
            if not fn.endswith((".c", ".cpp")):
                continue
            path = os.path.join(root, fn)
            text = open(path, errors="replace").read()
            have_c.add(fn.rsplit(".", 1)[0])
            for fname, body in functions_of(text):
                if not body:
                    continue
                for a in TC.accesses(body):
                    if a[0] != "cast":
                        continue
                    if a[1] in known:
                        continue                  # the cast already names a recovered class
                    if a[2] is None or not a[3]:
                        continue                  # no offset or no base: not this pass's business
                    total_raw += 1
                    base, span = a[3], a[4]
                    if re.fullmatch(r"arg\d+", base):
                        buckets["the receiver (needs the function's class -- naming)"] += 1
                        reg = MM.label_of(int(fname[4:], 16)) if fname.startswith("FUN_") else \
                            "named already"
                        region[reg] += 1
                        region_funcs[reg].add(fname)
                        if args.game_only and not reg.startswith(GAME_REGIONS):
                            continue
                        receiver[fname] += 1
                        continue
                    if re.search(r"\bDAT_|\b0x[0-9A-Fa-f]{6,}", base):
                        buckets["a global (needs the global's class)"] += 1
                        continue
                    if TC.DECL_RE.search(body[:span[0]]) and re.search(
                            r"\b(?:struct\s+)?[A-Za-z_]\w*\s*\*+\s*" + re.escape(base) + r"\b",
                            body[:span[0]]):
                        buckets["a declared pointer local (needs its declared type to be recovered)"] += 1
                        # ...and if that local was filled from a call, its *signature* is one way to
                        # supply the type: record the callee too (the table below is that subset)
                        ms = list(re.finditer(ASSIGN_RE % re.escape(base), body[:span[0]]))
                        if ms:
                            c = CALL_RE.search(ms[-1].group(1))
                            if c:
                                unlocked[c.group(1)] += 1
                                funcs[c.group(1)].add(fname)
                                examples.setdefault(c.group(1), (fname, fname,
                                                                 ms[-1].group(1).strip()[:70]))
                        continue
                    # the value the base held when the cast ran: the last assignment before it
                    before = body[:span[0]]
                    ms = list(re.finditer(ASSIGN_RE % re.escape(base), before))
                    if not ms:
                        buckets["undeclared local with no assignment before the cast"] += 1
                        continue
                    rhs = ms[-1].group(1)
                    call = CALL_RE.search(rhs)
                    if not call:
                        buckets["assigned from an expression, not a call"] += 1
                        continue
                    callee = call.group(1)
                    unlocked[callee] += 1
                    funcs[callee].add(fname)
                    examples.setdefault(callee, (fname, fname, rhs.strip()[:70]))

    for root, _dirs, files in os.walk(os.path.join(HERE, "..", "asm")):
        for fn in files:
            if fn.endswith(".s"):
                asm_only.add(fn.rsplit(".", 1)[0])

    rows = []
    for callee, n in unlocked.most_common():
        rows.append({
            "callee": callee,
            "casts": n,
            "functions": len(funcs[callee]),
            "has_c": callee in have_c,
            "example": examples[callee][2],
        })
    print("raw casts in matched C: %d" % total_raw)
    print("  (a `temp = call(...)` whose target is a declared pointer local is counted in the")
    print("   declared-local bucket: what is missing there is a *type*, which a signature or a")
    print("   declaration can supply -- the per-callee table below is that subset.)")
    for k, n in buckets.most_common():
        print("  %-58s %5d (%.1f%%)" % (k, n, 100.0 * n / total_raw if total_raw else 0))
    print()
    if args.by_region:
        print()
        print("%-58s %6s %6s" % ("library (docs/engine/module-map.md)", "funcs", "casts"))
        for reg, n in region.most_common():
            print("%-58s %6d %6d" % (reg, len(region_funcs[reg]), n))
        g = sum(n for r, n in region.items() if r.startswith(GAME_REGIONS))
        print("%-58s %6s %6d   <- the P1.3 queue (%.1f%% of all)"
              % ("GAME + engine, total", "", g, 100.0 * g / sum(region.values())))
    if args.game_only:
        print()
        print("%-16s %6s  %s" % ("function (game code)", "casts", "region"))
        for f, n in receiver.most_common(args.top):
            print("%-16s %6d  %s" % (f, n, MM.label_of(int(f[4:], 16))))
    print()
    print("%-34s %6s %6s %-8s %s" % ("callee (recover this signature)", "casts", "funcs",
                                     "source", "example use"))
    for r in rows[:args.top]:
        print("%-34s %6d %6d %-8s %s" % (r["callee"], r["casts"], r["functions"],
                                         "src/" if r["has_c"] else "asm/", r["example"]))
    if args.json:
        json.dump(rows, open(args.json, "w"), indent=1)
        print("\nwrote %s (%d callees)" % (args.json, len(rows)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
