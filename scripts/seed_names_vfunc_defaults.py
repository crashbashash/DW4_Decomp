#!/usr/bin/env python3
r"""seed_names_vfunc_defaults.py — name the shared default vfunc bodies that the
vtable pass had to leave anonymous.

MWCC emits one default stub per virtual slot and points every class that does not
override it at that one body, so 11,714 vtable slots collapse to 1,333 functions
(#283).  When a body is referenced by the classes of exactly one family, its owner
is the family's base class; when two *different* bodies resolve to the same
owner + slot, the base is an unnamed intermediate and both bodies had to be left
as `FUN_` — 47 of them (data/vtables.json `ambiguous`).

#360 tested whether the recovered class hierarchy lifts that ambiguity, using the
*lowest common ancestor* of the referrers, and concluded it does not: the LCA is
always `igObject`.  That test is too weak.  The right question is not "what is the
common ancestor" but "is there a class whose **descendant set** is exactly the set
of referrers".  A body referenced by every descendant of `C` (and by `C`'s
descendants only) is `C`'s default for that slot, whether or not `C` emits a vtable
of its own — and the owners here are precisely classes that declare the virtual but
never emit a vtable (abstract bases), which is why they are absent from the 478
emitted vtables and were missed.

Acceptance rule, per ambiguous body with referrer set R:

    candidate C  <=>  R ⊆ D(C) ∪ {C}   and   (D(C) ∪ {C}) \ R ⊆ {C}

i.e. every referrer is a descendant of C, and the only member of C's closure that
does not reference the body is C itself (C emits no vtable, so it cannot).  The
candidate must be **unique**; if two classes satisfy it the body stays anonymous.

This is a derived label (`<Class>::vfunc_<slot>`, the convention #283 used for the
other 1,286), not a semantic name, and the evidence is structural.  The bodies the
rule cannot place are genuinely ownerless in the available data: their base is a
template instantiation (`igTObjectList<…>`, `igTDataList<…>`) that has no MetaObject
and therefore no entry in the hierarchy at all.

Reads data/vtables.json (the referrer sets) and data/class-hierarchy.tsv (the
hierarchy); writes the curated overlay config/SLUS-20836/names/Vtables.tsv.

  python3 scripts/seed_names_vfunc_defaults.py            # write config/SLUS-20836/names/Vtables.tsv
  python3 scripts/seed_names_vfunc_defaults.py --report   # print the census only
"""
import argparse
import collections
import json
import os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
VTABLES = os.path.join(ROOT, "data", "vtables.json")
HIER = os.path.join(ROOT, "data", "class-hierarchy.tsv")
OUT = os.path.join(ROOT, "config", "SLUS-20836", "names", "Vtables.tsv")


def short(fqn):
    return fqn.split("::")[-1]


def load_hierarchy(path):
    """{short class: short base} — the recovered MetaObject hierarchy."""
    hier = {}
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.rstrip("\n").split("\t")
        if len(p) >= 2:
            hier[p[0]] = p[1] or None
    return hier


def descendants(hier):
    children = collections.defaultdict(list)
    for c, b in hier.items():
        children[b].append(c)
    cache = {}

    def closure(c):
        if c in cache:
            return cache[c]
        out = set()
        for ch in children.get(c, []):
            out.add(ch)
            out |= closure(ch)
        cache[c] = out
        return out

    return closure


def resolve(ambiguous, hier, closure, fqn_of):
    """-> (named, unresolved); named = [(va, slot, class_short, fqn)]."""
    named, unresolved = [], []
    for a in ambiguous:
        refs = {short(r) for r, _ in a["refs"]}
        cands = []
        for c in hier:
            s = closure(c) | {c}
            if refs <= s and (s - refs) <= {c}:
                cands.append(c)
        if len(cands) != 1:
            unresolved.append((a, cands))
            continue
        c = cands[0]
        named.append((a["addr"], a["slot"], c, fqn_of.get(c)))
    return named, unresolved


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--report", action="store_true",
                    help="print the census, write nothing")
    args = ap.parse_args()

    data = json.load(open(VTABLES))
    ambiguous = data["ambiguous"]

    # short name -> FQN, from the RTTI records (the hierarchy stores short names).
    fqn_of = {}
    for rec in data["rtti"].values():
        fqn_of.setdefault(short(rec["name"]), rec["name"])

    hier = load_hierarchy(HIER)
    closure = descendants(hier)
    named, unresolved = resolve(ambiguous, hier, closure, fqn_of)

    named.sort(key=lambda t: int(t[0], 16))
    print("ambiguous bodies: %d; resolved: %d; unresolved: %d"
          % (len(ambiguous), len(named), len(unresolved)))

    missing_fqn = [t for t in named if not t[3]]
    if missing_fqn:
        raise SystemExit("no RTTI record for: %r" % (missing_fqn,))

    lines = [
        "# Shared default vfunc bodies named from their referrer family.",
        "#",
        "# GENERATED by scripts/seed_names_vfunc_defaults.py; do not hand-edit.",
        "#",
        "# Each body in data/vtables.json's `ambiguous` list is referenced by the",
        "# full descendant set of exactly one class, so it is that class's virtual",
        "# slot.  This is the `<Class>::vfunc_<slot>` convention of #283, with the",
        "# owner recovered from data/class-hierarchy.tsv (#360's LCA test was too",
        "# weak; descendant-set equality is the right test).  Bodies whose owner is a",
        "# template base with no MetaObject stay anonymous -- see finding #410.",
        "#",
        "# <va>\t<name>\t<module>",
    ]
    for va, slot, c, fqn in named:
        mod = "game" if fqn.startswith("Gap::Bec::") else "engine"
        lines.append("0x%08x\t%s::vfunc_%d\t%s" % (int(va, 16), fqn, slot, mod))

    print()
    for va, slot, c, fqn in named:
        print("  %s slot%-3d -> %s::vfunc_%d" % (va, slot, fqn, slot))
    print()
    for a, cands in unresolved:
        refs = sorted(short(r) for r, _ in a["refs"])
        print("  anonymous %s slot%-3d nrefs=%d %s"
              % (a["addr"], a["slot"], len(refs), refs[:6] + (["..."] if len(refs) > 6 else [])))

    if args.report:
        return
    with open(OUT, "w") as f:
        f.write("\n".join(lines) + "\n")
    print("\nwrote %s (%d entries)" % (os.path.relpath(OUT, ROOT), len(named)))


if __name__ == "__main__":
    main()
