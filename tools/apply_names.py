#!/usr/bin/env python3
"""apply_names.py — apply `config/SLUS-20836/names/` to the tree as one verified batch.

Renaming a function is a cross-file refactor: its unit file, the definition inside
it, every caller in `src/`, the `asm/<name>.s` unit and the label every other asm
unit jumps to all carry the name.  Doing that by hand, one function at a time, is
why naming stalled; a whole module's worth can be done at once instead.

For every overlay entry whose name differs from `config/SLUS-20836/symbols.txt`:

  1. rewrite `<old>` -> `<new>` in every source, header and `.inc` fragment under
     `src/` and `include/` (word-boundary, so `FUN_ab` does not match inside
     `FUN_abcd`), which covers the definition, every declaration and every call
     site, and in the function column of `config/source-approvals.tsv`;
  2. move the unit to `src/<module>/` (the overlay's third column);
  3. delete the stale `asm/<old>.s`;
  4. regenerate `config/SLUS-20836/symbols.txt` and `asm/` with `tools/split.py`, which also
     rewrites every asm caller's `jal` for free.

Dry-run by default.  After `--apply`, `make check` must still be green and
`make link` byte-identical — the batch is only done when both are.

  apply_names.py                       # show what would change
  apply_names.py --apply               # do it
  apply_names.py --apply --no-regen    # skip step 4 (e.g. symbols already current)
  apply_names.py --apply --check       # ...and run make check + make link
"""
import argparse
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import asmsources  # noqa: E402
import split  # noqa: E402  (tools/split.py — load_names/sanitize are the name rules)
import srctree  # noqa: E402


def current(symbols):
    """{va: name} from `config/SLUS-20836/symbols.txt`."""
    out = {}
    for ln in open(symbols):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        out[int(p[0], 16)] = p[2]
    return out


def plan(names, cur):
    """-> (renames, errors); renames = [(va, old, new, module)] sorted by va."""
    by_name = {n: v for v, n in cur.items()}
    renaming = {v for v in names if v in cur}
    renames, errors, taken = [], [], {}
    for va in sorted(names):
        nm, mod = names[va]
        if va not in cur:
            errors.append("0x%08x is not in config/SLUS-20836/symbols.txt" % va)
            continue
        new, old = split.sanitize(nm), cur[va]
        if new == old:
            continue
        if new in taken and taken[new] != va:
            errors.append("0x%08x and 0x%08x both want the name %s" % (taken[new], va, new))
            continue
        taken[new] = va
        # A name may be *freed* by another entry in this same batch (a chain of
        # swaps); only a name held by a function staying put is a real collision.
        holder = by_name.get(new)
        if holder is not None and holder != va and holder not in renaming:
            errors.append("0x%08x -> %s collides with 0x%08x" % (va, new, holder))
            continue
        renames.append((va, old, new, mod))
    return renames, errors


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--names", default="config/SLUS-20836/names")
    ap.add_argument("--symbols", default="config/SLUS-20836/symbols.txt")
    ap.add_argument("--src", default="src")
    ap.add_argument("--asm", default="asm")
    ap.add_argument("--apply", action="store_true", help="commit (default: dry run)")
    ap.add_argument("--no-regen", action="store_true",
                    help="do not re-run tools/split.py after the move")
    ap.add_argument("--check", action="store_true",
                    help="after applying, run `make check` and `make link`")
    a = ap.parse_args(argv)

    names = split.load_names(a.names)
    if not names:
        print("apply_names: %s has no entries (nothing to do)" % a.names)
        return 0
    cur = current(a.symbols)
    renames, errors = plan(names, cur)
    for e in errors:
        print("error: " + e, file=sys.stderr)
    if errors:
        return 2
    if not renames:
        print("apply_names: %d overlay entries, all already applied" % len(names))
        return 0

    idx = srctree.index(a.src)
    to_move = [(va, old, new, mod) for va, old, new, mod in renames if old in idx]
    print("apply_names: %d/%d entries rename something (%d units to move, %d new asm labels)"
          % (len(renames), len(names), len(to_move), len(renames)))
    for va, old, new, mod in renames[:40]:
        where = ("-> %s/%s" % (mod, new)) if old in idx else "(no unit yet)"
        print("  0x%08x  %-28s -> %-32s %s" % (va, old, new, where))
    if len(renames) > 40:
        print("  ... and %d more" % (len(renames) - 40))
    if not a.apply:
        print("\n(dry run — re-run with --apply)")
        return 0

    # 1. rewrite src/ references.  Tokenize rather than alternate: a module batch can
    #    be thousands of names, and a regex with thousands of alternatives is far
    #    slower than one identifier regex plus a dict lookup.
    sub = {old: new for _, old, new, _ in renames}
    # A `thunk_<target>` unit is named after its target, so renaming the target renames
    # the thunk too — but the thunk's own definition is one token (`thunk_<target>`), not
    # an occurrence of `<target>`, so the exact-key map misses it and the unit would keep
    # a name `split.py` no longer emits (the symbol becomes `thunk_<new>`).
    # An explicit alias overlay takes precedence over its target-derived name.
    for _, old, new, _ in renames:
        sub.setdefault("thunk_" + old, "thunk_" + new)
    word = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")
    rewritten = 0
    # Filename indexing is for moves. It collapses a same-basename .c/.cpp pair,
    # both of which can contain references (or several merged definitions). Headers and
    # `.inc` fragments in src/ and the shared include/ tree declare and call functions too.
    tree = os.path.dirname(os.path.abspath(a.src))
    include = os.path.join(tree, "include")
    paths = sorted(os.path.join(root, filename)
                   for top in (a.src, include) if os.path.isdir(top)
                   for root, _, files in os.walk(top)
                   for filename in files
                   if filename.endswith(srctree.EXTS + (asmsources.EXT, ".h", ".inc"))
                   and not filename.startswith("dw4u_"))
    for path in paths:
        text = open(path).read()
        new_text = word.sub(lambda m: sub.get(m.group(0), m.group(0)), text)
        if new_text != text:
            open(path, "w").write(new_text)
            rewritten += 1
    # the owner's source approvals name their functions by symbol in the second column
    approvals = os.path.join(tree, "config", "source-approvals.tsv")
    if os.path.exists(approvals):
        text = open(approvals).read()
        lines = []
        for line in text.splitlines(True):
            cols = line.split("\t")
            if not line.startswith("#") and len(cols) > 2 and cols[1] in sub:
                cols[1] = sub[cols[1]]
            lines.append("\t".join(cols))
        if "".join(lines) != text:
            open(approvals, "w").write("".join(lines))
    # the assembly approval table names its functions by symbol (tools/asmsources.py)
    if os.path.exists(asmsources.TABLE):
        text = open(asmsources.TABLE).read()
        new_text = "".join(sub.get(line.split("\t", 1)[0], line.split("\t", 1)[0]) + line[len(line.split("\t", 1)[0]):]
                           if not line.startswith("#") else line for line in text.splitlines(True))
        if new_text != text:
            open(asmsources.TABLE, "w").write(new_text)

    # 2. move each unit to its module folder.
    moved = 0
    for va, old, new, mod in to_move:
        src_path = idx[old]
        ext = src_path[src_path.rfind("."):]
        dest_dir = os.path.join(a.src, mod)
        os.makedirs(dest_dir, exist_ok=True)
        dest = os.path.join(dest_dir, new + ext)
        if os.path.exists(dest):
            print("error: %s already exists" % dest, file=sys.stderr)
            return 2
        shutil.move(src_path, dest)
        moved += 1

    # 3. drop the stale asm units so the regenerated tree has no duplicate label.
    removed = 0
    for va, old, new, mod in renames:
        stale = os.path.join(a.asm, old + ".s")
        if os.path.exists(stale):
            os.remove(stale)
            removed += 1

    print("rewrote %d units, moved %d, removed %d stale asm units"
          % (rewritten, moved, removed))

    # 4. regenerate the layout + asm from the overlay.
    if not a.no_regen:
        cmd = [sys.executable, os.path.join(ROOT, "tools", "split.py"),
               "--symbols", "--names", a.names]
        r = subprocess.run(cmd, cwd=ROOT)
        if r.returncode:
            return r.returncode
        # `split.py` writes the units it knows and never deletes, so a name it no
        # longer uses — an overlay entry removed, or a function whose symbol moved —
        # would leave an orphan asm unit behind.  asm/ is generated from the symbol
        # list, so anything not in it is stale by definition.
        names = {ln.split()[2] for ln in open(a.symbols)
                 if ln.strip() and not ln.startswith("#")}
        pruned = 0
        for f in os.listdir(a.asm):
            if f.endswith(".s") and f[:-2] not in names:
                os.remove(os.path.join(a.asm, f))
                pruned += 1
        if pruned:
            print("pruned %d stale asm units" % pruned)

    if a.check:
        for tgt in (["make", "check"], ["make", "link"]):
            r = subprocess.run(tgt, cwd=ROOT)
            if r.returncode:
                print("apply_names: `%s` failed" % " ".join(tgt), file=sys.stderr)
                return r.returncode
    else:
        print("\nnext: `make check` (must be green) and `make link` (must be byte-identical)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
