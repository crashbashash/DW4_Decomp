"""srctree.py — resolve a filename to its path when `src/` is not flat.

The tree started as one flat directory of `FUN_<addr>.c` files.  It is now
organised by module (`src/lua/`, `src/engine/`, `src/game/`) with every not-yet-named
function under `src/unmatched/`, so the old `os.path.join("src", name + ".c")`
lookup no longer finds a file that lives in a subdirectory.

This module answers *which path*, treating the filename as the symbol.  That is the
rule for a one-function file, and it is what `tools/apply_names.py` renames.  It is
NOT true for a translation unit (`src/lua/api.c` defines 47 functions), so anything
that needs to go from a symbol to its definition uses `tools/units.py:scan`
instead: this one is for a path by filename (moving a one-function file), that one
is for a definition by symbol.

`index()` walks once and returns the whole `{filename: path}` map.  Callers that
loop over the 16,857-symbol layout must use it — one tree walk per symbol would
dominate `make check`.
"""
import os

EXTS = (".c", ".cpp")


def index(src_dir="src"):
    """{filename-without-extension: path} for every file under `src_dir`.

    Deterministic (directories sorted); skips the dot-named one-function splits
    `tools/units.py` writes.
    """
    out = {}
    for root, dirs, files in os.walk(src_dir):
        dirs.sort()
        for f in sorted(files):
            if f.endswith(EXTS) and not f.startswith("dw4u_"):
                out[os.path.splitext(f)[0]] = os.path.join(root, f)
    return out


def find(src_dir, name):
    """The path for `name`, or None.  For one-off lookups; loops should use index()."""
    for ext in EXTS:
        p = os.path.join(src_dir, name + ext)
        if os.path.exists(p):
            return p
    return index(src_dir).get(name)
