#!/usr/bin/env python3
"""place_named.py — move named units out of `src/` root into their module folder.

Named-but-unplaced units (the RTTI/vtable `Gap::Bec::Foo::vfunc_N` set) sat flat in
`src/` root because their names carried no folder.  Their name does carry one: the
namespace and class.  This groups them by class and folds each group into one file
with `tools/merge_units.py`:

  Gap__Bec__beCameraMode__vfunc_03.c \
  Gap__Bec__beCameraMode__vfunc_07.c  ->  src/game/beCameraMode.c

A class whose methods need C++ mode and C mode both keeps two files
(`Foo.c` and `Foo.cpp`): a C-mode method does **not** match when compiled as C++
(measured: 0 of 25 mixed classes), so the split is real, not cosmetic.

Folder by namespace:

  Gap::Bec::*                  -> src/game/
  Gap::Core::*                 -> src/engine/
  Gap::igAdx*                  -> src/audio/
  Gap::igMovie* / igCriMovie*  -> src/movie/
  Gap::Gui::*                  -> src/menu/
  anything else                -> src/engine/

Dry-run by default.

  place_named.py                 # what would move where
  place_named.py --apply
"""
import argparse
import collections
import os
import shutil
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import merge_units  # noqa: E402


def classify(stem):
    """`Gap__Bec__beCamera__vfunc_03` -> ('game', 'beCamera').

    The namespace depth varies: `Gap::Bec::Foo::vfunc_N` and
    `Gap::igMovieRenderer::vfunc_N` are both real.  So take everything between
    `Gap` and the `vfunc_N` segment, and folder by its head: `Bec` is the game,
    `Core` the engine, `igAdx*` audio, `igMovie*`/`igCriMovie*` movie, `Gui` the
    menus.  Deeper class paths keep their extra segments in the filename so two
    classes with the same leaf name cannot collide.
    """
    parts = stem.split("__")
    i = next((k for k, p in enumerate(parts) if p.startswith("vfunc")), len(parts))
    path = parts[1:i] or [parts[-1]]
    head, leaf = path[0], path[-1]
    if head == "Bec":
        d = "game"
    elif head == "Core":
        d = "engine"
    elif head.startswith("igAdx"):
        d = "audio"
    elif head.startswith(("igMovie", "igCriMovie")):
        d = "movie"
    elif head == "Gui":
        d = "menu"
    else:
        d = "engine"
    name = leaf if d == "engine" and len(path) == 1 else "__".join(path[1:] or [leaf])
    return d, name


def groups(src="src"):
    """{target path: [source files]} for every file directly in `src`."""
    out = collections.defaultdict(list)
    for f in sorted(os.listdir(src)):
        path = os.path.join(src, f)
        if not os.path.isfile(path) or not f.endswith((".c", ".cpp")):
            continue
        stem, ext = os.path.splitext(f)
        d, cls = classify(stem)
        out[os.path.join(src, d, cls + ext)].append(path)
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--src", default="src")
    ap.add_argument("--apply", action="store_true")
    a = ap.parse_args(argv)

    gs = groups(a.src)
    if not gs:
        print("place_named: no files in %s root" % a.src)
        return 0
    by_dir = collections.Counter(os.path.dirname(k) for k in gs)
    print("place_named: %d files -> %d unit files" % (sum(len(v) for v in gs.values()), len(gs)))
    for d, n in sorted(by_dir.items()):
        print("  %-14s %d units" % (d, n))
    folded = [k for k, v in gs.items() if len(v) > 1]
    print("  folded (>1 function): %d" % len(folded))
    for k in sorted(folded, key=lambda k: -len(gs[k]))[:8]:
        print("    %-40s <- %d" % (k, len(gs[k])))
    if not a.apply:
        print("\n(dry run — re-run with --apply)")
        return 0

    folded_n = 0
    for out, files in sorted(gs.items()):
        os.makedirs(os.path.dirname(out), exist_ok=True)
        cls = os.path.splitext(os.path.basename(out))[0]
        merge_units.main(["--out", out, "--title", "the %s methods" % cls,
                          "--remove"] + files)
        folded_n += len(files)
    print("place_named: %d units written, %d source files folded away" % (len(gs), folded_n))
    return 0


if __name__ == "__main__":
    sys.exit(main())
