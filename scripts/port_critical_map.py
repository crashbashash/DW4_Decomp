#!/usr/bin/env python3
"""The port-critical dependency map: which retail functions the native port needs, and how far each is recovered.

Seeds, with the evidence that makes each one port-critical:
  * the 116 Lua API implementations (the original scripts call them), the Lua dispatch infrastructure and the reviewed
    producer/receiver roots of config/SLUS-20836/lua-dependency-roots.tsv;
  * every game-region function that the port's own sources (`port/src`, `port/include`) cite by address or by retail name;
  * every function that the port's subsystem documentation (`port/docs/*.md`) cites the same way.
From the seeds the map follows direct calls (branch-and-link, tail jumps) inside the game/engine region, breadth first, and records the
depth. Middleware (Sony SDK, Alchemy core, CRI, Lua, libpng) is a platform boundary the port replaces; it is counted, not traversed.
Virtual and register transfers are frontiers, not inferred edges, so every figure is a lower bound.

Per function it reports the recovery state (matched C / matched asm body / not yet in src), whether it is named, and, for matched C,
the recovered-access counters of tools/typed_coverage.py. It writes docs/ page and a TSV; --check fails when they are stale.
Needs the private ELF (orig/SLUS-20836/SLUS_208.36), like scripts/lua_engine_dependencies.py. Usage: scripts/port_critical_map.py [--write|--check]
"""
import argparse
import bisect
import collections
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "scripts"))
import progress          # noqa: E402
import typed_coverage    # noqa: E402
import units             # noqa: E402
import verify            # noqa: E402
from lua_engine_dependencies import transfers  # noqa: E402

GAME_LO, GAME_HI = 0x334000, 0x540000     # docs/engine/module-map.md: GAME + engine, scene / overlay / actor managers
DOC = ROOT / "port/docs/project/critical-dependency-map.md"
TSV = ROOT / "data/port-critical-map.tsv"
SKIP_DOCS = {"arena-migration-backlog.md", "critical-dependency-map.md"}
HEX = re.compile(r"(?<![\w.])(?:0x)?([0-9a-fA-F]{6})(?!\w)")
WORD = re.compile(r"\b[A-Za-z_][A-Za-z0-9_]{7,}\b")


def load():
    syms = {va: (name, size) for va, size, name in progress.load_symbols()}
    starts = sorted(syms)
    paths = units.scan(str(ROOT / "src"))
    return syms, starts, paths


def owner(starts, syms, va):
    i = bisect.bisect_right(starts, va) - 1
    if i >= 0 and va < starts[i] + syms[starts[i]][1]:
        return starts[i]
    return None


def citations(text, syms, starts, names):
    """Game-region functions a text cites: by address (0x-prefixed or a hex word with a letter) or by retail name."""
    found = set()
    for m in HEX.finditer(text):
        tok = m.group(0)
        if not (tok.lower().startswith("0x") or re.search(r"[a-fA-F]", m.group(1))):
            continue
        va = int(m.group(1), 16)
        if GAME_LO <= va < GAME_HI:
            o = owner(starts, syms, va)
            if o is not None:
                found.add(o)
    for w in WORD.findall(text):
        va = names.get(w)
        if va is not None:
            found.add(va)
    return found


def seeds(syms, starts):
    names = {n: va for va, (n, _s) in syms.items() if GAME_LO <= va < GAME_HI and progress.named(n)}
    out = collections.OrderedDict()   # va -> (group, label)

    def add(va, group, label):
        if va not in out:
            out[va] = (group, label)

    apis = json.loads((ROOT / "data/script_api.json").read_text())
    for row in apis:
        add(row["real"], "lua", "Lua API " + row["name"])
    for va in (0x370780, 0x3719d0):
        add(va, "lua", "Lua dispatch")
    for line in (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines():
        if line.strip() and not line.startswith("#"):
            add(int(line.split("\t", 1)[0], 0), "lua", "Lua root")
    for sub, group, pattern in (("port/src", "port", "*.c"), ("port/include", "port", "*.h")):
        for p in sorted((ROOT / sub).rglob(pattern)):
            for va in sorted(citations(p.read_text(errors="replace"), syms, starts, names)):
                add(va, group, p.name)
    for p in sorted((ROOT / "port/docs").rglob("*.md")):
        if p.name in SKIP_DOCS:
            continue
        for va in sorted(citations(p.read_text(errors="replace"), syms, starts, names)):
            add(va, "doc", p.name)
    return out


def closure(elf, syms, starts, seed):
    image = verify.read_elf(str(elf))
    depth, why, indirect = {}, {}, {}
    frontier = collections.deque()
    for va, (_g, label) in seed.items():
        if va in syms and va not in depth:
            depth[va], why[va] = 0, label
            frontier.append(va)
    while frontier:
        va = frontier.popleft()
        name, size = syms[va]
        direct, ind = transfers(verify.va_bytes(image, va, size), va)
        indirect[va] = len(ind)
        for e in direct:
            o = owner(starts, syms, e["target"])
            if o is None or o in depth or not GAME_LO <= o < GAME_HI:
                continue
            depth[o], why[o] = depth[va] + 1, why[va]
            frontier.append(o)
    return depth, why, indirect


def typed_per_function(paths):
    stats = typed_coverage.measure(src=str(ROOT / "src"))
    by_name = {}
    for (path, name), c in stats["per_function"].items():
        by_name[name] = c
    return by_name


def state(name, paths):
    p = paths.get(name)
    if not p:
        return "none"
    return "asm" if progress.is_asm_body(name, p) else "c"


def build(elf):
    syms, starts, paths = load()
    seed = seeds(syms, starts)
    depth, why, indirect = closure(elf, syms, starts, seed)
    typed = typed_per_function(paths)
    rows = []
    for va in sorted(depth):
        name, size = syms[va]
        st = state(name, paths)
        c = typed.get(name) if st == "c" else None
        group = seed[va][0] if va in seed else None
        rows.append(dict(va=va, name=name, size=size, state=st, named=progress.named(name), depth=depth[va],
                         why=why[va], seed=group, indirect=indirect[va],
                         rec=c["recovered"] if c else 0, syn=c["synthetic"] if c else 0,
                         oth=c["other"] if c else 0, raw=c["raw"] if c else 0))
    region = [(va, s) for va, (n, s) in syms.items() if GAME_LO <= va < GAME_HI]
    return rows, dict(nseeds=len(seed), by_group=collections.Counter(g for g, _l in seed.values()),
                      region_functions=len(region), region_bytes=sum(s for _v, s in region),
                      region_matched=sum(s for v, s in region if syms[v][0] in paths))


def agg(rows):
    d = dict(n=len(rows), bytes=sum(r["size"] for r in rows))
    for st in ("c", "asm", "none"):
        sel = [r for r in rows if r["state"] == st]
        d[st], d[st + "_bytes"] = len(sel), sum(r["size"] for r in sel)
    d["named"] = sum(r["named"] for r in rows)
    d["rec"] = sum(r["rec"] for r in rows)
    d["acc"] = sum(r["rec"] + r["syn"] + r["oth"] + r["raw"] for r in rows)
    d["indirect"] = sum(r["indirect"] for r in rows)
    return d


def pct(a, b):
    return "%.1f%%" % (100.0 * a / b) if b else "n/a"


def row(label, d):
    return "| %s | %s | %s | %s | %s | %s | %s |" % (
        label, format(d["n"], ","), format(d["bytes"], ","), pct(d["c_bytes"], d["bytes"]), pct(d["asm_bytes"], d["bytes"]),
        format(d["none_bytes"], ","), pct(d["rec"], d["acc"]))


HEAD = "| scope | functions | bytes | matched C | matched asm | not in src (bytes) | typed accesses |\n| --- | ---: | ---: | ---: | ---: | ---: | ---: |"


def render(rows, meta):
    total = agg(rows)
    out = ["# Port-critical dependency map", "",
           "Generated by `scripts/port_critical_map.py --write`; do not edit by hand. It answers: *which retail functions does the native port",
           "need, and how far is each recovered?* It needs the private ELF to regenerate.", "",
           "## Method", "",
           "- **Seeds** (%d functions): the 116 Lua API implementations plus Lua dispatch and reviewed roots (%d), every game-region function"
           % (meta["nseeds"], meta["by_group"]["lua"]),
           "  that `port/src` or `port/include` cites by address or retail name (%d), and the same from `port/docs` (%d more)."
           % (meta["by_group"]["port"], meta["by_group"]["doc"]),
           "- **Closure**: direct calls and tail jumps inside the game/engine region (`0x334000`-`0x540000`), breadth first; *depth* is the number of",
           "  calls from the nearest seed. Middleware (Sony SDK, Alchemy core, CRI, Lua, libpng) is a platform boundary the port replaces and is not",
           "  traversed.",
           "- **Lower bound**: virtual dispatch, register jumps and Lua callbacks are frontiers, not inferred edges (%s unresolved sites in the set)."
           % format(total["indirect"], ","),
           "- *Matched C* / *matched asm* mean a definition in `src/` that `make check` verifies byte for byte (*matched asm* is an `asm` body; none are kept in the repository). *Typed accesses*",
           "  is the share of member accesses in matched C that use a recovered struct field (`tools/typed_coverage.py`).", "",
           "## The whole set", "", HEAD, row("port-critical closure", total)]
    region_b, region_m = meta["region_bytes"], meta["region_matched"]
    out += ["", "For scale, the game/engine region holds %s functions / %s bytes, of which %s bytes (%s) have a definition in `src/`; the closure is %s of"
            % (format(meta["region_functions"], ","), format(region_b, ","), format(region_m, ","), pct(region_m, region_b),
               pct(total["bytes"], region_b)),
            "the region's bytes.", "", "## By depth from a seed", "", HEAD]
    for lo, hi, label in ((0, 0, "depth 0 (seeds)"), (1, 1, "depth 1"), (2, 2, "depth 2"), (3, 99, "depth 3+")):
        out.append(row(label, agg([r for r in rows if lo <= r["depth"] <= hi])))
    out += ["", "Depth 0 is what the port already reproduces or names; depth 1 is what it needs to read to be faithful to it; the deeper tiers are",
            "transitive helpers that matter only where the port runs the retail path rather than replacing it.", "",
            "## By origin (the seed that first reaches each function)", "", HEAD]
    for grp, label in (("lua", "Lua API / script bindings"), ("port", "port sources"), ("doc", "port documentation only")):
        sel = [r for r in rows if _first_group(r) == grp]
        out.append(row(label, agg(sel)))
    out += ["", "## By port module (functions its source cites, plus everything they reach)", "",
            "Each function is counted once, under the first seed that reaches it (Lua bindings first, then port sources, then documentation).", "",
            HEAD]
    by = collections.defaultdict(list)
    for r in rows:
        by[r["why"]].append(r)
    mods = sorted(by.items(), key=lambda kv: -agg(kv[1])["none_bytes"])
    for label, sel in mods[:60]:
        out.append(row("`%s`" % label, agg(sel)))
    if len(mods) > 60:
        out.append(row("_%d smaller origins_" % (len(mods) - 60), agg([r for _l, s in mods[60:] for r in s])))
    todo = sorted((r for r in rows if r["state"] == "none"), key=lambda r: (r["depth"], -r["size"]))
    big = [r for r in todo if r["size"] >= 4096]
    out[out.index("## By depth from a seed"):out.index("## By depth from a seed")] = [
        "## Reading", "",
        "- Matching has not followed the port's needs: the closure is %s matched against %s for the region as a whole."
        % (pct(total["c_bytes"] + total["asm_bytes"], total["bytes"]), pct(region_m, region_b)),
        "- What remains is concentrated: %s of the %s unmatched port-critical functions are 4 KB or larger and hold %s of the %s bytes."
        % (format(len(big), ","), format(len(todo), ","), format(sum(r["size"] for r in big), ","), format(sum(r["size"] for r in todo), ",")),
        "  They are mostly large virtual methods (`vfunc_21`/`31`/`34`) of save/load, status, shop and model controllers.",
        "- The port already runs without them: it was written from the analysed behavior, so these are the places where its faithfulness is",
        "  checked by retail comparison rather than by a byte-matched oracle.", ""]
    out += ["", "## What is left to byte-match, nearest first", "",
            "Port-critical functions with no definition in `src/` yet: **%s functions / %s bytes**. The list is ordered by depth, then size;"
            % (format(len(todo), ","), format(sum(r["size"] for r in todo), ",")), "the first 80:", "",
            "| address | name | bytes | depth | reached from |", "| --- | --- | ---: | ---: | --- |"]
    for r in todo[:80]:
        out.append("| `0x%08x` | `%s` | %d | %d | %s |" % (r["va"], r["name"], r["size"], r["depth"], r["why"]))
    raw = sorted((r for r in rows if r["state"] == "c" and r["raw"] + r["oth"] + r["syn"] > r["rec"]),
                 key=lambda r: -(r["raw"] + r["oth"] + r["syn"]))
    out += ["", "## What is left to type, biggest first", "",
            "Matched-C functions in the closure whose untyped accesses (raw offset casts, synthetic structs, unrecovered members) outnumber the",
            "recovered ones: **%s functions**. The first 60:" % format(len(raw), ","), "",
            "| name | bytes | recovered | untyped | depth | reached from |", "| --- | ---: | ---: | ---: | ---: | --- |"]
    for r in raw[:60]:
        out.append("| `%s` | %d | %d | %d | %d | %s |" % (r["name"], r["size"], r["rec"], r["raw"] + r["oth"] + r["syn"], r["depth"], r["why"]))
    unnamed = [r for r in rows if not r["named"]]
    out += ["", "## What is left to understand", "",
            "%s of the closure's %s functions are still unnamed (%s bytes); %s of those already have matching source, so naming them is a rename,"
            % (format(len(unnamed), ","), format(len(rows), ","), format(sum(r["size"] for r in unnamed), ","),
               format(sum(r["state"] != "none" for r in unnamed), ",")),
            "not a recovery. The rest of the evidence is in `data/port-critical-map.tsv` (one row per function).", ""]
    return "\n".join(out)


def _first_group(r):
    return "lua" if r["why"].startswith("Lua") else ("doc" if r["why"].endswith(".md") else "port")


def tsv(rows):
    lines = ["# address\tname\tbytes\tstate\tnamed\tdepth\tseed\treached_from\trecovered\tuntyped\tindirect",
             "# GENERATED by scripts/port_critical_map.py; do not hand-edit."]
    for r in rows:
        lines.append("0x%08x\t%s\t%d\t%s\t%d\t%d\t%s\t%s\t%d\t%d\t%d" % (
            r["va"], r["name"], r["size"], r["state"], r["named"], r["depth"], r["seed"] or "-", r["why"],
            r["rec"], r["raw"] + r["oth"] + r["syn"], r["indirect"]))
    return "\n".join(lines) + "\n"


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--elf", type=Path, default=ROOT / "orig/SLUS-20836/SLUS_208.36")
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    rows, meta = build(args.elf)
    outputs = {DOC: render(rows, meta), TSV: tsv(rows)}
    for path, text in outputs.items():
        if args.write:
            path.write_text(text)
        if args.check and (not path.exists() or path.read_text() != text):
            raise SystemExit("stale generated output: %s" % path.relative_to(ROOT))
    total = agg(rows)
    print("closure: %s functions / %s bytes; matched C %s, asm %s, not in src %s bytes (%d seeds)" % (
        format(total["n"], ","), format(total["bytes"], ","), pct(total["c_bytes"], total["bytes"]),
        pct(total["asm_bytes"], total["bytes"]), format(total["none_bytes"], ","), meta["nseeds"]))


if __name__ == "__main__":
    main()
