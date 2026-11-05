#!/usr/bin/env python3
"""Typed coverage of the port-relevant game layer.

`tools/typed_coverage.py` counts every function in `src/`, most of which is `ig*` middleware, vendor
code and registration boilerplate the port replaces. The port only needs structs for the game logic it
reimplements, so this measures that slice:

  scope = functions named `Gap__Bec__*` or `be<Upper>*` (game classes), minus registration boilerplate
          (`*_GetMetaObject`, `*_Register`, `*_InitFields`, `*_GetVTable`, `*_GetMetaEnum`),
          plus the functions listed in `config/typed-scope-extra.tsv` (combat helpers with FUN_ names).

Each access in scope falls in one bucket:

  typed      member access through a recovered class (reflection) or an authoritative header
  local      member access through a file-local struct (named fields, but private to one file)
  synthetic  member access through automatch's `struct G` (offsets with no recovered meaning)
  raw        `*(T *)(base + N)` offset cast

"typed share" = typed / total. The goal stops at 80 %.

Usage:
  typed_scope.py                    # report
  typed_scope.py --by-class         # per class, worst first
  typed_scope.py --list out.tsv     # write the in-scope function list
  typed_scope.py --update-baseline  # record config/typed-scope-baseline.json (commit it)
"""
import argparse
import collections
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import typed_coverage as tc

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXTRA = os.path.join(ROOT, "config", "typed-scope-extra.tsv")
BASELINE = os.path.join(ROOT, "config", "typed-scope-baseline.json")
BOILERPLATE = re.compile(r"_(GetMetaObject|Register|InitFields|GetVTable|GetMetaEnum)$")
GAME = re.compile(r"^(Gap__Bec__|be[A-Z])")


def load_extra():
    out = {}
    if os.path.exists(EXTRA):
        for line in open(EXTRA):
            if line.strip() and not line.startswith("#"):
                f = line.rstrip("\n").split("\t")
                out[f[0]] = f[1] if len(f) > 1 else ""
    return out


def class_of(name):
    n = name[len("Gap__Bec__"):] if name.startswith("Gap__Bec__") else name
    return n.split("__")[0].split("_")[0]


def scope_of(name, extra):
    if name in extra:
        return "extra"
    if GAME.match(name) and not BOILERPLATE.search(name):
        return "game"
    return None


def measure(src="src"):
    st = tc.measure(src=src)
    extra = load_extra()
    funcs = {}
    for (path, name), c in st["per_function"].items():
        s = scope_of(name, extra)
        if not s:
            continue
        if os.path.relpath(path, src).split(os.sep)[0] == "asmbody":
            continue
        funcs[(path, name)] = (s, c)
    return funcs


def summarize(funcs):
    t = collections.Counter()
    for _, (_, c) in funcs.items():
        t.update(c)
    total = sum(t.values())
    return dict(functions=len(funcs), accesses=total,
                typed=t["recovered"], local=t["other"], synthetic=t["synthetic"], raw=t["raw"],
                typed_pct=round(100.0 * t["recovered"] / max(1, total), 2))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--by-class", action="store_true")
    ap.add_argument("--list")
    ap.add_argument("--file", help="measure only this source file (a scratch copy is fine)")
    ap.add_argument("--update-baseline", action="store_true")
    a = ap.parse_args()
    if a.file:
        import shutil, tempfile
        with tempfile.TemporaryDirectory() as tmp:
            shutil.copy(a.file, os.path.join(tmp, os.path.basename(a.file)))
            funcs = measure(tmp)
    else:
        funcs = measure()
    s = summarize(funcs)
    print("typed coverage, port-relevant game layer")
    print("  functions in scope:        %d" % s["functions"])
    print("  accesses in scope:         %d" % s["accesses"])
    print("    typed (recovered class): %5d (%.1f%%)   <- the goal's number, stop at 80%%" % (s["typed"], s["typed_pct"]))
    print("    local file-private struct:%4d (%.1f%%)" % (s["local"], 100.0 * s["local"] / max(1, s["accesses"])))
    print("    synthetic struct G:      %5d (%.1f%%)" % (s["synthetic"], 100.0 * s["synthetic"] / max(1, s["accesses"])))
    print("    raw offset casts:        %5d (%.1f%%)" % (s["raw"], 100.0 * s["raw"] / max(1, s["accesses"])))
    if a.by_class:
        byc = collections.defaultdict(collections.Counter)
        for (path, name), (_, c) in funcs.items():
            byc[class_of(name)].update(c)
        print("\n  class                               accesses typed local synth raw")
        for cls, c in sorted(byc.items(), key=lambda kv: -(sum(kv[1].values()) - kv[1]["recovered"]))[:40]:
            print("  %-34s %8d %5d %5d %5d %4d" % (cls, sum(c.values()), c["recovered"], c["other"], c["synthetic"], c["raw"]))
    if a.list:
        with open(a.list, "w") as fh:
            fh.write("# function\tclass\tscope\n")
            for (path, name), (sc, _) in sorted(funcs.items(), key=lambda kv: kv[0][1]):
                fh.write("%s\t%s\t%s\n" % (name, class_of(name), sc))
    if a.update_baseline:
        json.dump(dict(note="Baseline for tools/typed_scope.py: the port-relevant game layer. Record deliberately "
                            "with --update-baseline.", **s), open(BASELINE, "w"), indent=1, sort_keys=True)
        print("recorded %s" % os.path.relpath(BASELINE, ROOT))


if __name__ == "__main__":
    main()
