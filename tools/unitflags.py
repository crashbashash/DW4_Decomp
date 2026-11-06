#!/usr/bin/env python3
"""unitflags.py — per-function compiler-flag overrides (config/SLUS-20836/unit-flags.tsv).

The retail ELF was built with **per-file** optimisation flags. The flag set of a file
is its unit's profile in config/SLUS-20836/units.tsv (tools/unitprofiles.py); this table holds
the per-function **overrides** of that profile. The discriminator is often MWCC's `,p`
peephole sub-flag, which changes how an integral float literal is materialised
: `beAction2JOINTSET_Start` needs `,p` (the IEEE-754 bits are loaded
directly, `lui`/`ori`/`mtc1`), while `FUN_0015e130` needs it *off* (`,p` rewrites its
popcount into a different, longer shape). The flag lives in a table rather than a
source pragma because `,p` has no source-level equivalent: `#pragma peephole`,
`#pragma opt_peephole` and `#pragma optimization_level` are all ignored (measured).

The table is a committed, hand-authored overlay (like `config/SLUS-20836/names/*.tsv`):

    <va>\\t<flags>\\t<status>[\\t<reason>]

`va` is the function's retail virtual address (stable across renames); `flags` is the
**complete** flag string for that function and replaces the unit's (a
`-Cpp_exceptions on|off` token in it also replaces the unit's exception mode). Where a
unit of config/SLUS-20836/units.tsv covers the function, `status` must be `provisional`: the row
says the function has not been reproduced under its unit's profile, the verifier
applies it only after the unit profile failed, and `make check` reports the function
as `foreign-profile` debt rather than a match (AGENTS.md, "One translation unit, one
profile"). A table used without a units table (a fixture) may omit
the status; its rows are then the whole profile, as before units.tsv existed.
"""
import os
from collections import namedtuple

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_PATH = "config/SLUS-20836/unit-flags.tsv"

Row = namedtuple("Row", "flags status reason")

_CACHE = {}


def _resolve(path):
    return path if os.path.isabs(path) else os.path.join(ROOT, path)


def load_rows(path=DEFAULT_PATH, refresh=False):
    """-> {va: Row(flags, status, reason)}. A missing file is not an error (an empty table)."""
    path = _resolve(path)
    if not refresh and path in _CACHE:
        return _CACHE[path]
    table = {}
    if os.path.exists(path):
        for ln in open(path):
            ln = ln.rstrip("\n")
            if not ln.strip() or ln.lstrip().startswith("#"):
                continue
            parts = [p.strip() for p in ln.split("\t")] if "\t" in ln else ln.split(None, 1)
            if len(parts) < 2:
                continue
            try:
                va = int(parts[0], 0)
            except ValueError:
                continue
            status = parts[2] if len(parts) > 2 and parts[2] else "-"
            reason = parts[3] if len(parts) > 3 else ""
            table[va] = Row(parts[1].strip(), status, reason)
    _CACHE[path] = table
    return table


def load(path=DEFAULT_PATH, refresh=False):
    """-> {va: flags} (the historical view of the table; see load_rows for the status)."""
    return {va: row.flags for va, row in load_rows(path, refresh).items()}


def flags_for(va, default, path=DEFAULT_PATH):
    """Effective flags for the function at `va`: its override if listed, else `default`.

    Callers that know the unit profile use tools/unitprofiles.resolve instead; this
    remains for tools that only read the override table.
    """
    row = load_rows(path).get(va)
    return row.flags if row is not None else default
