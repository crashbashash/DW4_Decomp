#!/usr/bin/env python3
"""The indirect-transfer frontier of the port-critical closure: what its unresolved register transfers could reach.

`scripts/port_critical_map.py` follows direct calls only and counts every `jalr` and non-`ra` `jr` as an unresolved site (a lower bound).
This script classifies those sites by instruction pattern and resolves what it can without guessing:

  * **switch** - a `jr` in a function that has a recovered jump table (config/SLUS-20836/jumptables.txt): local control flow, not a dependency;
  * **virtual** - `lw vt,0(obj)`; `lw fn,off(vt)`; `jalr fn` with `off = 8 + 4 * slot` (the vtable has an 8-byte header). The callee is one of
    the functions at that slot in the class vtables (data/vtables.json); without the receiver's class the candidate set is every vtable that
    has the slot, so each slot is reported with its candidates and their recovery state;
  * **other** - everything else (a function pointer from a table or argument, or a pattern this scan does not recognize).

The classification is a scan of at most 16 instructions back from the transfer, so the counts are approximate by construction; a site that
matches no pattern is reported as other, never dropped. Needs the private ELF (orig/SLUS-20836/SLUS_208.36). Output: docs/engine/indirect-frontier.md.
Usage: scripts/indirect_frontier.py [--write|--check]
"""
import argparse
import collections
import json
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "scripts"))
import progress          # noqa: E402
import units             # noqa: E402
import verify            # noqa: E402
from lua_engine_dependencies import transfers  # noqa: E402

GAME_LO, GAME_HI = 0x334000, 0x540000
CLASSES = {}
PATHS = {}
TSV = ROOT / "data/port-critical-map.tsv"
DOC = ROOT / "docs/engine/indirect-frontier.md"
WINDOW = 16


def dest_register(word):
    """The general register an instruction writes, or None (enough of MIPS for the backward scan)."""
    op = word >> 26
    if op == 0:
        fn = word & 63
        if fn in (0x08, 0x0c, 0x0d, 0x11, 0x13, 0x18, 0x19, 0x1a, 0x1b):   # jr, syscall, break, mthi, mtlo, mult, multu, div, divu
            return None
        return (word >> 11) & 31
    if op == 3:
        return 31
    if op in (8, 9, 10, 11, 12, 13, 14, 15, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x37, 0x1e):
        return (word >> 16) & 31
    return None


def argument_registers(words, upto):
    """Map register -> parameter index (0..3) for registers that still hold an incoming argument just before instruction `upto`: a0..a3, or an s-register
    copy made before the first call. A linear scan that ignores branches and stops tracking a/t registers at the first call: a heuristic."""
    alias = {4: 0, 5: 1, 6: 2, 7: 3}
    for i in range(0, upto):
        w = words[i]
        op = w >> 26
        if op == 3 or (op == 0 and (w & 63) == 9):   # jal / jalr: a0-a3 and the temporaries are gone, s registers survive
            alias = {r: k for r, k in alias.items() if 16 <= r <= 23}
            continue
        if op == 0 and (w & 63) in (0x2d, 0x21, 0x25) and ((w >> 16) & 31) == 0 and ((w >> 21) & 31) in alias:   # daddu/addu/or rd,rs,zero
            alias[(w >> 11) & 31] = alias[(w >> 21) & 31]
            continue
        rd = dest_register(w)
        if rd in alias:
            del alias[rd]
    return alias


def classify(code, start, site, has_table):
    """Return (kind, slot or None, receiver) for the transfer at `site`; receiver is the incoming parameter index (0 = this) the object still holds, else None."""
    words = [struct.unpack_from("<I", code, i)[0] for i in range(0, len(code), 4)]
    index = (site - start) // 4
    word = words[index]
    reg = (word >> 21) & 31
    if (word & 63) == 8 and has_table:
        return "switch", None, None
    # nearest earlier writer of the transfer register
    for back in range(1, WINDOW + 1):
        i = index - back
        if i < 0:
            break
        w = words[i]
        if dest_register(w) != reg:
            continue
        if w >> 26 == 0x23:                       # lw fn, off(vt)
            vt, off = (w >> 21) & 31, w & 0xffff
            off = off - 0x10000 if off >= 0x8000 else off
            for back2 in range(1, WINDOW + 1):
                j = i - back2
                if j < 0:
                    break
                w2 = words[j]
                if dest_register(w2) != vt:
                    continue
                if w2 >> 26 == 0x23 and (w2 & 0xffff) == 0 and off >= 8 and (off - 8) % 4 == 0:
                    obj = (w2 >> 21) & 31
                    arg = argument_registers(words, j).get(obj)
                    return "virtual", (off - 8) // 4, arg
                break
        break
    return "other", None, None


def collect():
    syms = {va: (name, size) for va, size, name in progress.load_symbols()}
    paths = units.scan(str(ROOT / "src"))
    PATHS.update(paths)
    image = verify.read_elf(str(ROOT / "orig/SLUS-20836/SLUS_208.36"))
    tables = {int(line.split()[0], 16) for line in (ROOT / "config/SLUS-20836/jumptables.txt").read_text().splitlines()
              if line.strip() and not line.startswith("#")}
    vt = json.loads((ROOT / "data/vtables.json").read_text())["vtables"]
    candidates = collections.defaultdict(set)
    by_class = {}
    for entry in vt.values():
        by_class[entry["class"]] = [int(t, 16) for t in entry["vfuncs"]]
        for slot, target in enumerate(entry["vfuncs"]):
            candidates[slot].add(int(target, 16))
    base_of = {r["name"]: r["base_name"] for r in json.loads((ROOT / "data/vtables.json").read_text())["rtti"].values()}
    CLASSES.update(by_class=by_class, base_of=base_of)

    def state(va):
        if va not in syms:
            return "unknown"
        name = syms[va][0]
        if name not in paths:
            return "unmatched"
        return "asm body" if progress.is_asm_body(name, paths[name]) else "matched C"

    rows = []
    for line in TSV.read_text().splitlines():
        if line.startswith("#") or not line.strip():
            continue
        f = line.split("\t")
        va, name, size, indirect = int(f[0], 16), f[1], int(f[2]), int(f[10])
        if indirect:
            rows.append((va, name, size, indirect))
    sites = []
    for va, name, size, indirect in rows:
        _direct, ind = transfers(verify.va_bytes(image, va, size), va)
        for s in ind:
            kind, slot, recv = classify(verify.va_bytes(image, va, size), va, s["site"], va in tables)
            sites.append((va, name, s["site"], s["kind"], kind, slot, recv))
    return syms, state, candidates, sites


def render(syms, state, candidates, sites):
    kinds = collections.Counter(x[4] for x in sites)
    by_function = collections.defaultdict(collections.Counter)
    for va, name, _site, _transfer, kind, slot, _recv in sites:
        by_function[(va, name)][kind] += 1
    slot_sites = collections.defaultdict(list)
    for va, name, _site, _transfer, kind, slot, _recv in sites:
        if kind == "virtual":
            slot_sites[slot].append(name)
    out = ["# Indirect-transfer frontier of the port-critical closure", "",
           "Generated by `scripts/indirect_frontier.py --write`; do not edit by hand. It needs the private ELF.", "",
           "[`port-critical-map`](../../port/docs/project/critical-dependency-map.md) follows direct calls only, so every register transfer in its",
           "closure is an unresolved site. This page classifies those sites by instruction pattern and, for virtual calls, lists what the called",
           "slot can reach. The scan looks at most 16 instructions back from each transfer; the classification is approximate and an unrecognized",
           "site is reported as *other*, never dropped. **The receiver's class is not known**, so the candidates of a slot are every vtable entry",
           "at that slot (data/vtables.json) - a superset of what one call can reach.", "", "## Sites", "",
           "| kind | sites | meaning |", "| --- | ---: | --- |",
           "| switch | %d | `jr` of a recovered jump table (`config/SLUS-20836/jumptables.txt`): local control flow, not a dependency |" % kinds["switch"],
           "| virtual | %d | `lw vt,0(obj); lw fn,8+4*slot(vt); jalr fn`: reaches one of the slot's candidates below |" % kinds["virtual"],
           "| other | %d | a function pointer from a table or argument, or a pattern the scan does not recognize |" % kinds["other"],
           "| **total** | **%d** | the closure's `indirect` count |" % len(sites), ""]
    novt = sum(len(slot_sites[sl]) for sl in slot_sites if not candidates[sl])
    out += ["%d of the virtual sites use a slot that no vtable in data/vtables.json has (the highest slot there is %d): they load through an "
            "object whose first word is not a class vtable we know, or the pattern matched something else, and they have no candidate list. A hand check of four sites "
            "(two ordinary, two above the table) found real `lw vt,0(obj); lw fn,off(vt); jalr fn` calls with the slot computed correctly; the two high-slot ones "
            "call through a field of an Alchemy memory-pool object (`igAliasMemoryPool`, `MemoryContext`), whose vtables data/vtables.json does not list." %
            (novt, max(sl for sl in list(candidates) if candidates[sl])), "",
            "## Functions with the most unresolved (virtual or other) sites", "",
            "| function | bytes | virtual | other | switch |", "| --- | ---: | ---: | ---: | ---: |"]
    ranked = sorted(by_function.items(), key=lambda kv: -(kv[1]["virtual"] + kv[1]["other"]))
    for (va, name), c in ranked[:20]:
        if c["virtual"] + c["other"] == 0:
            break
        out.append("| `%s` | %d | %d | %d | %d |" % (name, syms[va][1], c["virtual"], c["other"], c["switch"]))
    out += ["", "## Virtual slots used by the closure", "",
            "Candidates are the distinct functions at the slot across all vtables; the last columns count them by recovery state "
            "(*unmatched* = no source in `src/`, so a hidden dependency if a call can reach it).", "",
            "| slot | sites | functions | candidates | in game region | matched C | asm body | unmatched |",
            "| ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |"]
    hidden = []
    for slot in sorted(slot_sites, key=lambda s: -len(slot_sites[s])):
        cand = candidates[slot]
        game = [c for c in cand if GAME_LO <= c < GAME_HI]
        states = collections.Counter(state(c) for c in game)
        out.append("| %d | %d | %d | %d | %d | %d | %d | %d |" % (
            slot, len(slot_sites[slot]), len(set(slot_sites[slot])), len(cand), len(game), states["matched C"], states["asm body"],
            states["unmatched"] + states["unknown"]))
        hidden += [(slot, c) for c in game if state(c) in ("unmatched", "unknown")]
    # calls on the function's own `this`: the receiver class is the method's class, so the candidates are that class and its descendants
    by_class, base_of = CLASSES["by_class"], CLASSES["base_of"]

    def descendants(root):
        found = set()
        for name in by_class:
            c = name
            while c:
                if c == root:
                    found.add(name)
                    break
                c = base_of.get(c)
        return found

    sig_cache = {}

    def declared_types(name):
        """Parameter class names from the function's signature in the matched source (the last definition-like line), or []."""
        if name in sig_cache:
            return sig_cache[name]
        types = []
        path = PATHS.get(name)
        if path:
            text = Path(path).read_text(errors="replace")
            for m in re.finditer(r"\b%s\s*\(([^;{)]*)\)\s*\{" % re.escape(name), text):
                params = [x.strip() for x in m.group(1).split(",")]
                types = []
                for x in params:
                    t = re.match(r"^(?:const\s+)?(?:struct\s+)?(\w+)\s*\*", x)
                    types.append(t.group(1) if t else None)
        sig_cache[name] = types
        return types

    def class_of(type_name):
        if not type_name:
            return None
        for c in by_class:
            if c.split("::")[-1] == type_name:
                return c
        return None

    selfsites = [(va, name, site, slot, recv) for va, name, site, _t, kind, slot, recv in sites if kind == "virtual" and recv is not None]
    narrowed = []
    reach = {}
    for va, name, site, slot, recv in selfsites:
        cls = None
        types = declared_types(name)
        if recv < len(types):
            cls = class_of(types[recv])
        if cls is None and recv == 0 and "__vfunc_" in name:
            c = name.split("__vfunc_")[0].replace("__", "::")
            cls = c if c in by_class else None
        if cls is None:
            continue
        cand = {by_class[c][slot] for c in descendants(cls) if slot < len(by_class[c])}
        narrowed.append((name, cls, slot, cand, recv))
        for c in cand:
            reach.setdefault(c, set()).add((cls, slot))
    out += ["", "## Calls on an incoming argument of known class", "",
            "Where the object of a virtual call is still an incoming argument (a0..a3, or an s-register copy made before the first call; a linear scan that ignores "
            "branches, so approximate) and its class is known - `this` of a `Gap::...::Class::vfunc_N` method, or a parameter whose class the matched source declares - "
            "the candidates are that class and its descendants at the slot, not every vtable. %d virtual sites are on an incoming argument; %d of them have a known class." % (len(selfsites), len(narrowed)), ""]
    if narrowed:
        out += ["| method | param | class | slot | candidates | in game region | unmatched |", "| --- | ---: | --- | ---: | ---: | ---: | ---: |"]
        for name, cls, slot, cand, recv in sorted(narrowed, key=lambda t: -len(t[3]))[:25]:
            game = [c for c in cand if GAME_LO <= c < GAME_HI]
            out.append("| `%s` | %d | `%s` | %d | %d | %d | %d |" % (name, recv, cls, slot, len(cand), len(game), sum(1 for c in game if state(c) in ("unmatched", "unknown"))))
        missing = sorted({c for c in reach if GAME_LO <= c < GAME_HI and state(c) in ("unmatched", "unknown")})
        out += ["", "Unsourced game-region functions that a narrowed call can reach (%d): %s" % (
            len(missing), ", ".join("`%s`" % syms[c][0] for c in missing) if missing else "none"), ""]
    out += ["", "## Game-region candidates with no source yet", "",
            "Distinct functions that a virtual slot used by the closure can reach and that have no definition in `src/` (%d). Each is a place where "
            "a hidden dependency could sit; whether any call actually reaches one needs the receiver's class at that site." % len({c for _s, c in hidden}), ""]
    seen = set()
    rows = []
    for slot, c in sorted(hidden, key=lambda t: (t[1], t[0])):
        if c in seen:
            continue
        seen.add(c)
        name, size = syms.get(c, ("?", 0))
        rows.append((name, size, sorted({s for s, cc in hidden if cc == c})))
    out += ["| function | bytes | slots |", "| --- | ---: | --- |"]
    for name, size, slots in sorted(rows, key=lambda r: -r[1])[:40]:
        out.append("| `%s` | %d | %s |" % (name, size, ", ".join(map(str, slots[:8])) + (" ..." if len(slots) > 8 else "")))
    if len(rows) > 40:
        out.append("| _%d more_ | | |" % (len(rows) - 40))
    out.append("")
    return "\n".join(out)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    text = render(*collect())
    if args.write:
        DOC.write_text(text)
        print("wrote", DOC.relative_to(ROOT))
    elif args.check:
        if not DOC.exists() or DOC.read_text() != text:
            print("indirect-frontier.md is stale: run scripts/indirect_frontier.py --write")
            return 1
        print("indirect-frontier.md is up to date")
    else:
        print(text)
    return 0


if __name__ == "__main__":
    sys.exit(main())
