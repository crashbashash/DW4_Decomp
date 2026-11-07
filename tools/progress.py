#!/usr/bin/env python3
"""
progress.py — the repo's progress numbers, computed from committed files only.

Why a separate tool: `make check` is the oracle, but it needs the retail ELF and the proprietary
compiler, so it cannot run in CI and cannot be run by a reader. This reads what *is* committed —
`config/SLUS-20836/symbols.txt` for the layout, `src/` for what has been decompiled — and writes:

  PROGRESS.md        the detailed page (coverage, size bands, where in the binary, metadata)
  docs/progress.json the same numbers, machine-readable
  README.md          a one-line block between `<!-- progress:start -->` / `<!-- progress:end -->`

A function counts as decompiled when `src/<symbol>.c` or `.cpp` defines it as C/C++. That is the
same set `tools/check.py` reports, and every one of those files was written only after `tools/verify.py`
proved its bytes identical to retail — so the numbers are honest, but they are a *record* of that
verification, not a re-verification. Re-run `make check` to prove it again.

An `asm` body (the retail instructions wrapped in an MWCC `asm` function under `#pragma
optimization_level 0`, see docs/engine/asm-body-matches.md) counts as neither decompiled nor
matched: every figure here is C/C++, and asm bodies are reported on their own line. The test is
the file's content, not its folder, so an asm body anywhere under `src/` is one.

The output is a pure function of the tree: it carries no date, revision or commit count, so a
re-run with no source changes produces no changes (and `--check` is idempotent).

Usage:
  progress.py                 # write PROGRESS.md, docs/progress.json, README.md block
  progress.py --report        # print the summary, write nothing
  progress.py --json          # dump docs/progress.json to stdout
  progress.py --check         # exit 1 if the committed outputs are stale (for CI linting)
  progress.py --debt-check    # exit 1 naming each debt counter above config/debt-baseline.json
  progress.py --debt-baseline [--allow-increase "<reason>"]   # re-record the debt floor
"""
import argparse
import collections
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import regions
import units
from unitprofiles import asm_body_names
import datamap
import re
import statistics
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SYMBOLS = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")
SRC = os.path.join(ROOT, "src")
JUMPTABLES = os.path.join(ROOT, "config", "SLUS-20836", "jumptables.txt")
CATEGORIES_TSV = os.path.join(ROOT, "data", "check-categories.tsv")
PROGRESS_MD = os.path.join(ROOT, "PROGRESS.md")
PROGRESS_JSON = os.path.join(ROOT, "docs", "progress.json")
README = os.path.join(ROOT, "README.md")

# The one file-backed section `make link` rebuilds and `tools/linkcheck.py` compares:
# 0x454B00 = 4,541,184 bytes. The loader also maps a zero-initialised `.bss` tail to
# 0x58d280, but the link never emits those bytes, so "fully linked" is measured over the
# section, not over the mapped image.
SECTION_LO, SECTION_HI = 0x100000, 0x100000 + 0x454B00
SECTION_BYTES = SECTION_HI - SECTION_LO
REGIONS = 16
BANDS = [(1, 32), (33, 64), (65, 128), (129, 256), (257, 512), (513, 1024),
         (1025, 4096), (4097, 10 ** 9)]
BAR = 24


def bar(percent, width=BAR):
    """A unicode progress bar for a percentage (0-100)."""
    filled = int(round(percent / 100.0 * width))
    filled = max(0, min(width, filled))
    return "\u2588" * filled + "\u2591" * (width - filled)


def load_symbols():
    out = []
    for ln in open(SYMBOLS):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        out.append((int(p[0], 16), int(p[1], 16), p[2]))
    return out


def have_src_paths():
    # `src/` holds translation units, so a symbol is resolved by reading the
    # definitions, not by filename (tools/units.py) — `src/lua/api.c` is 47
    # functions and must count as 47, not as one file called `api`.
    return units.scan(SRC)


def have_src():
    return set(have_src_paths())


def is_asm_body(name, path):
    return name in asm_body_names(path)


def named(name):
    """A recovered name, as opposed to an address-derived one (`FUN_<va>`, `thunk_<…>`)."""
    return not name.startswith(("FUN_", "thunk_"))


# Role names are mechanical: the vtable slot number, the class-boilerplate suffixes that the
# reflection records and `tools/apply_names.py` generate for every registered class. They are
# real names, but they say nothing about what the function *does*.
ROLE_NAME_RE = re.compile(
    r"(?:_(?:GetMetaObject|GetVTable|Register|InitFields)|vfunc_\d+)(?:__[0-9a-f]{8})?$")


def semantic_named(name):
    """A recovered name that says what the function does: not an address, not a role name."""
    return named(name) and not ROLE_NAME_RE.search(name)


# ---- verification categories (what `make check` proved about each decompiled unit) ----
# tools/check.py classifies every unit and commits the table as data/check-categories.tsv
# (`va name category diagnostic`). Only `match` is fully verified; the others are code
# bytes identical with a debt still to settle, or not matched at all.
CATEGORY_ORDER = ["match", "code-only", "name-defect", "inventory-gap", "foreign-profile", "asm-body", "mismatch",
                  "compile"]
CATEGORY_EXPLAIN = {
    "match": "code bytes, exception metadata and symbol rules all pass — fully verified",
    "code-only": "code bytes identical; exception metadata not reproduced (compile mode or cleanup scope)",
    "name-defect": "code bytes identical; a symbol name is wrong for its address",
    "inventory-gap": "code bytes identical; a reference lands in a symbol-map gap or inside another extent",
    "foreign-profile": "code bytes identical only under a provisional per-function override whose compiler, flags or "
                       "exception mode differ from the unit's profile (config/SLUS-20836/units.tsv; docs/engine/build-profiles.md)",
    "asm-body": "the retail instructions in an `asm` function: links identically, recovers nothing, counted in no "
                "figure above (docs/engine/asm-body-matches.md)",
    "mismatch": "code bytes, size, tables or object shape differ",
    "compile": "does not compile",
}
EXC_REASONS = ["missing", "extra", "differ", "other"]
EXC_EXPLAIN = {
    "missing": "retail keeps an exception record the unit does not produce",
    "extra": "the unit emits exception metadata retail lacks (compiled with exceptions off, or as C)",
    "differ": "both have exception metadata and it differs",
    "other": "the unit's first diagnostic line does not name the exception reason (a deferred duplicate, "
             "or a table/index line comes first); see its row in data/check-categories.tsv",
}


def exc_reason(diagnostic):
    """Which exception-metadata debt a code-only unit carries, read from its diagnostic."""
    d = diagnostic or ""
    if not d.startswith("exception metadata"):
        return "other"
    if "retail keeps no" in d:
        return "extra"
    if "retail keeps an" in d or "emits 0 .exception" in d or "does not reproduce" in d:
        return "missing"
    return "differ"


def load_categories():
    """{va: (category, diagnostic)} from data/check-categories.tsv, or None when absent."""
    if not os.path.exists(CATEGORIES_TSV):
        return None
    out = {}
    for ln in open(CATEGORIES_TSV, errors="replace"):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.rstrip("\n").split("\t")
        if len(p) < 3:
            continue
        out[int(p[0], 16)] = (p[2], p[3] if len(p) > 3 else "-")
    return out


def categorise(matched):
    """The verified/debt split of the decompiled units, or why it is not recorded.

    `matched` is the list of (va, size, name) symbols that have a definition in src/, asm bodies
    included because they have rows too. The
    table must cover exactly those units: a missing file or a row count that differs
    (a check run older or newer than the tree) makes the figures unreliable, so they are
    marked "(categories not recorded)" rather than published.
    """
    rows = load_categories()
    by = {k: dict(functions=0, bytes=0) for k in CATEGORY_ORDER}
    exc = {k: dict(functions=0, bytes=0) for k in EXC_REASONS}
    result = dict(recorded=False, warning=None, by=by, code_only_by_exc=exc, foreign_orphan_bytes=0,
                  fully_verified=dict(functions=0, bytes=0), source="data/check-categories.tsv")
    if rows is None:
        result["warning"] = ("data/check-categories.tsv is missing: run `make check` to record the "
                             "verification categories")
        return result
    if len(rows) != len(matched):
        result["warning"] = ("data/check-categories.tsv has %d rows but %d units are decompiled: "
                             "the table is from another tree state; run `make check` to regenerate it"
                             % (len(rows), len(matched)))
        return result
    unknown = 0
    for va, size, _name in matched:
        if va not in rows:
            unknown += 1
            continue
        kind, diagnostic = rows[va]
        if kind not in by:
            by[kind] = dict(functions=0, bytes=0)
        by[kind]["functions"] += 1
        by[kind]["bytes"] += size
        if kind == "code-only":
            r = exc_reason(diagnostic)
            exc[r]["functions"] += 1
            exc[r]["bytes"] += size
        elif kind == "foreign-profile" and "; orphan " in (diagnostic or ""):
            # the override compile emits exception metadata retail lacks: orphan bytes like exc=extra
            result["foreign_orphan_bytes"] += size
    if unknown:
        result["warning"] = ("%d decompiled unit(s) have no row in data/check-categories.tsv: "
                             "run `make check` to regenerate it" % unknown)
        return result
    result["recorded"] = True
    result["fully_verified"] = dict(by["match"])
    return result


def pct(part, whole):
    return 100.0 * part / whole if whole else 0.0


def collect():
    syms = load_symbols()
    paths = have_src_paths()
    asm_body = [s for s in syms if s[2] in paths and is_asm_body(s[2], paths[s[2]])]
    asm_body_names_set = {s[2] for s in asm_body}
    have = set(paths) - asm_body_names_set
    matched = [s for s in syms if s[2] in have]
    cats = categorise(matched + asm_body)
    if cats["warning"]:
        sys.stderr.write("progress: warning: %s — figures marked (categories not recorded)\n"
                         % cats["warning"])

    total_b = sum(s[1] for s in syms)
    done_b = sum(s[1] for s in matched)
    sizes_done = [s[1] for s in matched]
    sizes_left = [s[1] for s in syms if s[2] not in have]

    bands = []
    for lo, hi in BANDS:
        b = [s for s in syms if lo <= s[1] <= hi]
        m = [s for s in b if s[2] in have]
        bands.append(dict(lo=lo, hi=hi, total=len(b), matched=len(m),
                          total_bytes=sum(s[1] for s in b),
                          matched_bytes=sum(s[1] for s in m)))

    span = SECTION_HI - SECTION_LO
    regions = []
    for i in range(REGIONS):
        lo = SECTION_LO + span * i // REGIONS
        hi = SECTION_LO + span * (i + 1) // REGIONS
        b = [s for s in syms if lo <= s[0] < hi]
        m = [s for s in b if s[2] in have]
        regions.append(dict(lo=lo, hi=hi, total=len(b), matched=len(m),
                            total_bytes=sum(s[1] for s in b),
                            matched_bytes=sum(s[1] for s in m)))

    biggest = sorted(matched, key=lambda s: -s[1])[:10]

    # ---- recovered metadata, from the committed dumps ----
    meta = {}
    try:
        v = json.load(open(os.path.join(ROOT, "data", "vtables.json")))
        meta["rtti_records"] = len(v.get("rtti", {}))
        meta["vtables"] = len(v.get("vtables", {}))
        meta["vfunc_names"] = len(v.get("names", {}))
    except Exception:
        pass
    try:
        r = json.load(open(os.path.join(ROOT, "data", "reflection.json")))
        c = r.get("counts", {})
        meta["metaobjects"] = c.get("metaobjects")
        meta["classes_with_fields"] = c.get("with_fields")
        meta["fields"] = c.get("fields")
    except Exception:
        pass
    try:
        tabs = {}
        for ln in open(JUMPTABLES):
            if ln.startswith("#") or not ln.strip():
                continue
            p = ln.split()
            tabs.setdefault(int(p[0], 16), []).append(int(p[2], 16))
        meta["table_functions"] = len(tabs)
        meta["tables"] = sum(len(v) for v in tabs.values())
        meta["table_entries"] = sum(sum(v) for v in tabs.values())
    except FileNotFoundError:
        pass
    n_lua = sum(1 for _ in _walk(os.path.join(ROOT, "lua"), ".lua"))
    if n_lua:
        meta["lua_chunks"] = n_lua
    # asm/ is generated from the symbol map and not committed: one unit per symbol
    meta["asm_units"] = len(syms)

    # ---- the data half of the image (`tools/datamap.py`) ----
    # Decomp projects are read on code *and* data. Counting only code left the data
    # regions invisible even where the metadata is fully recovered, so the second
    # number is reported next to the first. `datamap` explains the classification.
    dm = datamap.summarise(datamap.build())

    # ---- "fully linked" (what the link step actually emits from source) ----
    # Two numbers are published: *decompiled* (bytes matched) and *fully linked*
    # (bytes inside units so complete that the build links C instead of the asm stub).
    # They differ for a translation-unit build (TP: 12.07 % / 8.12 %, and "100 %
    # decompiled but not fully linked") because a unit's stub can only be dropped when
    # the *whole* unit is done. Here `tools/layout.py` tiles per function, so
    # `tools/linkgen.py` replaces retail one function at a time and the two coincide.
    # Reported anyway, because it is the number a WIP decomp is read on -- and it is
    # *measured* by the link (`make link` prints this same accounting).
    #
    # Two honesty rules. (1) The denominator is the 4,541,184-byte section the link emits
    # and `tools/linkcheck.py` compares, not the 4,772,480-byte mapped image: the `.bss`
    # tail is never linked from anything. (2) An asm body is linked from `src/`, but it is
    # the retail instructions, not recovered C, so it is reported in its own column and
    # never folded into "from C/C++".
    jtbl_b = 0            # compiler-regenerated jump tables of C/C++ owners
    jtbl_asm_b = 0        # jump tables owned by an asm body (its retail words carry them)
    try:
        for ln in open(os.path.join(ROOT, "config", "SLUS-20836", "layout.txt")):
            if ln.startswith("#") or not ln.strip():
                continue
            p = ln.split()
            if p[2] == "jtbl":
                owner = p[4] if len(p) > 4 else ""
                if owner in asm_body_names_set:
                    jtbl_asm_b += int(p[1], 16)
                elif owner in have:
                    jtbl_b += int(p[1], 16)
    except FileNotFoundError:
        pass
    asm_body_b = sum(s[1] for s in asm_body)
    from_c = done_b + jtbl_b                    # the compiler regenerates the jump tables
    from_asm_body = asm_body_b + jtbl_asm_b
    # Typed coverage: how much of the matched C speaks in recovered structs rather than
    # offset casts.  It is not a measure of the matching build.
    try:
        sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__))))
        from typed_coverage import measure as measure_types
        typed = measure_types()
    except Exception as exc:               # never let this metric break the build metric
        typed = dict(error=str(exc), recovered=0, total=0, recovered_pct=0.0)
    link = dict(section_bytes=SECTION_BYTES,
                from_c_bytes=from_c, from_c_units=len(matched),
                from_asm_body_bytes=from_asm_body, from_asm_body_units=len(asm_body),
                jtbl_bytes=jtbl_b, jtbl_asm_body_bytes=jtbl_asm_b,
                asm_bytes=total_b - done_b - asm_body_b,
                image_bytes=dm["image_bytes"],
                from_c_pct=round(100.0 * from_c / SECTION_BYTES, 2),
                from_asm_body_pct=round(100.0 * from_asm_body / SECTION_BYTES, 2))

    # Deliberately no revision, date or commit count: the outputs must be a function of the CODE
    # state alone, so a push that changes no C produces no diff and the workflow publishes nothing.
    # (A sha in the file would make every push churn one, and leave the operator's next push
    # non-fast-forward.) The workflow puts the revision in its run summary instead.
    # `matched` is a C/C++ definition in src/ whose code bytes are retail's, never an asm body;
    # `fully_verified` is the subset `make check` classifies as `match` — the headline — and is
    # None when the categories are not recorded.
    fv = cats["fully_verified"] if cats["recorded"] else None
    d = dict(
        functions=dict(matched=len(matched), total=len(syms),
                       fully_verified=fv["functions"] if fv else None,
                       named=sum(1 for s in syms if named(s[2])),
                       named_semantic=sum(1 for s in syms if semantic_named(s[2])),
                       named_semantic_matched=sum(1 for s in matched if semantic_named(s[2]))),
        code_bytes=dict(matched=done_b, total=total_b,
                        fully_verified=fv["bytes"] if fv else None,
                        asm_body=asm_body_b,
                        functions_asm_body=len(asm_body)),
        categories=cats,
        data_bytes=dict(identified=dm["identified_data_bytes"],
                        total=dm["data_bytes"],
                        pct=dm["identified_data_pct"], kinds=dm["kinds"]),
        link=link,
        typed=dict(recovered=typed.get("recovered", 0), total=typed.get("total", 0),
                   pct=typed.get("recovered_pct", 0.0),
                   offset_casts=typed.get("offset_casts", 0),
                   synthetic=typed.get("synthetic", 0),
                   typeable=typed.get("typeable", 0),
                   typeable_pct=typed.get("typeable_pct", 0.0),
                   error=typed.get("error")),
        median_size=dict(matched=int(statistics.median(sizes_done)) if sizes_done else 0,
                         unmatched=int(statistics.median(sizes_left)) if sizes_left else 0),
        bands=bands, regions=regions,
        largest=[dict(va="0x%08x" % s[0], size=s[1], name=s[2]) for s in biggest],
        metadata=meta,
    )
    d["debt"] = debt_summary(d, syms, matched, asm_body, paths, typed)
    clear = readable(syms, paths)
    d["readable"] = dict(functions=clear["functions"], bytes=clear["bytes"],
                         matched_functions=clear["matched_functions"], failing=clear["failing"])
    return d


# ---- the debt ratchet: every debt counter may only go down -------------------------------
# Each counter is read from committed files alone (no compiler, no game), so the gate can run
# anywhere. The recorded floor lives in config/debt-baseline.json; `--debt-check` fails when
# a counter rises above it, `--debt-baseline` re-records it and refuses an increase unless
# `--allow-increase "<reason>"` is given, in which case the reason is stored next to the
# value. docs/engine/debt-ratchet.md explains each counter.
DEBT_BASELINE = os.path.join(ROOT, "config", "debt-baseline.json")
M2C_IDIOM_RE = re.compile(r"\b(?:temp_\w+|var_\w+|arg[0-9])\b")
FUN_DAT_RE = re.compile(r"\b(?:FUN|DAT)_[0-9a-fA-F]{6,8}\b")

# (counter, explanation) in report order; the value of every counter is an int or None when
# its source is unavailable (which `--debt-check` treats as a failure, never as zero).
DEBT_COUNTERS = [
    ("code_only.functions", "units whose code bytes match but exception metadata is unproven (data/check-categories.tsv)"),
    ("code_only.bytes", "code bytes of those units"),
    ("code_only.missing.functions", "code-only: retail keeps an exception record the unit does not produce"),
    ("code_only.missing.bytes", "bytes of those"),
    ("code_only.extra.functions", "code-only: the unit emits exception metadata retail lacks"),
    ("code_only.extra.bytes", "bytes of those"),
    ("code_only.differ.functions", "code-only: both have exception metadata and it differs"),
    ("code_only.differ.bytes", "bytes of those"),
    ("code_only.other.functions", "code-only: the diagnostic line does not name the exception reason"),
    ("code_only.other.bytes", "bytes of those"),
    ("name_defect.functions", "code bytes match, a symbol name is wrong for its address"),
    ("name_defect.bytes", "bytes of those"),
    ("inventory_gap.functions", "code bytes match, a reference lands in a symbol-map gap or inside another extent"),
    ("inventory_gap.bytes", "bytes of those"),
    ("mismatch.functions", "decompiled units whose bytes differ from retail"),
    ("mismatch.bytes", "bytes of those"),
    ("compile.functions", "decompiled units that do not compile"),
    ("compile.bytes", "bytes of those"),
    ("asm_body.functions", "functions kept as an `asm` body (content classification)"),
    ("asm_body.bytes", "bytes of those"),
    ("unmatched.functions", "functions in the layout with no definition in src/"),
    ("unmatched.bytes", "bytes of those"),
    ("struct.a", "struct-report groups: same view name, clashing layouts across units (scripts/check_struct_conflicts.py)"),
    ("struct.b", "struct-report groups: receiver view disagrees with the reflected class"),
    ("struct.c", "struct-report groups: offset-named member whose number is not its offset"),
    ("m2c_idiom.units", "source files (asm bodies excluded) still carrying m2c idioms: `temp_*`, `var_*` or `argN`"),
    ("raw_casts.reflected", "raw offset casts on a named receiver where reflection names the field (tools/typed_coverage.py `typeable`)"),
    ("fun_dat_refs", "FUN_/DAT_-named references in matched units' code (comments and strings excluded, definitions subtracted)"),
    ("foreign_profile.functions", "code bytes match only under a provisional per-function override that differs from the unit's profile in config/SLUS-20836/units.tsv (data/check-categories.tsv)"),
    ("foreign_profile.bytes", "bytes of those"),
    ("orphan.bytes", "exception-metadata orphan bytes: code-only `extra` + `differ` bytes, plus foreign-profile units whose override emits metadata retail lacks"),
    ("inventory.unsymbolised_bytes", "instruction-shaped bytes in layout `data` units that no symbol owns (data/inventory-scan.tsv, scripts/inventory_scan.py)"),
]


# Readability is a separate job from matching, so these are tracked and never refuse a change.
READABILITY_COUNTERS = {"m2c_idiom.units", "raw_casts.reflected", "fun_dat_refs"}


def _unit_files(paths, asm_body_names):
    """The distinct source files of the matched units, minus files that are asm bodies only."""
    files = {}
    for name, path in paths.items():
        files.setdefault(path, set()).add(name)
    return {p: names for p, names in files.items() if not names <= asm_body_names}


def debt_struct_counts():
    """(a)/(b)/(c) group counts from scripts/check_struct_conflicts.py, or None if it cannot run."""
    try:
        sys.path.insert(0, os.path.join(ROOT, "scripts"))
        import check_struct_conflicts as csc
        import glob
        reflected = csc.parse_reflected(os.path.join(ROOT, "include", "dw4", "reflected.h"))
        src, inc = os.path.join(ROOT, "src"), os.path.join(ROOT, "include", "dw4")
        files = sorted(glob.glob(os.path.join(src, "**", "*.c"), recursive=True)
                       + glob.glob(os.path.join(src, "**", "*.cpp"), recursive=True)
                       + [f for f in glob.glob(os.path.join(inc, "**", "*"), recursive=True) if os.path.isfile(f)])
        files = [f for f in files if "/asmbody/" not in f and not os.path.basename(f).startswith("dw4u_")
                 and os.path.abspath(f) != os.path.abspath(os.path.join(inc, "reflected.h"))]
        views = csc.collect(files, reflected)
        sink = []
        return dict(a=csc.report_a(views, sink), b=csc.report_b(views, reflected, sink), c=csc.report_c(views, sink))
    except Exception as exc:               # the report is optional input; say so, do not fake zeros
        sys.stderr.write("progress: warning: struct report unavailable (%s)\n" % exc)
        return None


def debt_summary(d, syms, matched, asm_body, paths, typed):
    """{counter: int|None} for every DEBT_COUNTERS entry, plus the recorded baseline."""
    from typed_coverage import strip_comments_and_strings
    cats = d["categories"]
    by, exc = cats["by"], cats["code_only_by_exc"]
    rec = cats["recorded"]
    c = {}

    def cat(kind, what):
        return by.get(kind, {}).get(what, 0) if rec else None
    for kind, key in (("code-only", "code_only"), ("name-defect", "name_defect"),
                      ("inventory-gap", "inventory_gap"), ("foreign-profile", "foreign_profile"),
                      ("mismatch", "mismatch"), ("compile", "compile")):
        c[key + ".functions"] = cat(kind, "functions")
        c[key + ".bytes"] = cat(kind, "bytes")
    for r in EXC_REASONS:
        c["code_only.%s.functions" % r] = exc[r]["functions"] if rec else None
        c["code_only.%s.bytes" % r] = exc[r]["bytes"] if rec else None
    c["asm_body.functions"] = len(asm_body)
    c["asm_body.bytes"] = sum(s[1] for s in asm_body)
    left = [s for s in syms if s[2] not in paths]
    c["unmatched.functions"] = len(left)
    c["unmatched.bytes"] = sum(s[1] for s in left)
    st = debt_struct_counts()
    for k in ("a", "b", "c"):
        c["struct." + k] = st[k] if st else None
    # m2c idioms and FUN_/DAT_ references: over the matched units' source, asm bodies excluded,
    # comments and string literals blanked so prose never counts.
    asm_names = {s[2] for s in asm_body}
    idiom_units, refs = 0, 0
    for path, names in _unit_files(paths, asm_names).items():
        try:
            text = strip_comments_and_strings(open(path, errors="replace").read())
        except FileNotFoundError:
            continue
        if M2C_IDIOM_RE.search(text):
            idiom_units += 1
        n = sum(1 for _ in FUN_DAT_RE.finditer(text))
        # A FUN_ function the file defines is not an unnamed *reference*: subtract every
        # occurrence of its own name (the definition and, in a C++ unit, the `extern "C"`
        # prototype that gives it C linkage).
        own = sum(len(re.findall(r"\b%s\b" % re.escape(nm), text))
                  for nm in names if nm.startswith("FUN_"))
        refs += max(0, n - own)
    c["m2c_idiom.units"] = idiom_units
    c["raw_casts.reflected"] = None if typed.get("error") else typed.get("typeable", 0)
    c["fun_dat_refs"] = refs
    c["orphan.bytes"] = (exc["extra"]["bytes"] + exc["differ"]["bytes"] + cats["foreign_orphan_bytes"]) if rec else None
    # The function inventory's own debt: code the symbol map does not own, read from the
    # committed scan (`scripts/inventory_scan.py --write`; `make inventory-check` keeps it fresh).
    try:
        sys.path.insert(0, os.path.join(ROOT, "scripts"))
        import inventory_scan
        c["inventory.unsymbolised_bytes"] = inventory_scan.unsymbolised_bytes()
    except Exception as exc_:                # the scan table is optional input; say so, never fake a zero
        sys.stderr.write("progress: warning: inventory scan unavailable (%s)\n" % exc_)
        c["inventory.unsymbolised_bytes"] = None
    return dict(counters={k: c.get(k) for k, _ in DEBT_COUNTERS},
                baseline=load_debt_baseline())


def load_debt_baseline():
    """{counter: {"value": int, "reason": str|None}} from config/debt-baseline.json, or None."""
    if not os.path.exists(DEBT_BASELINE):
        return None
    raw = json.load(open(DEBT_BASELINE))
    out = {}
    for k, v in raw.get("counters", {}).items():
        if isinstance(v, dict):
            out[k] = dict(value=v.get("value"), reason=v.get("reason"))
        else:
            out[k] = dict(value=v, reason=None)
    return out


def debt_check(d):
    """Exit status and the few lines the pre-push hook prints."""
    cur, base = d["debt"]["counters"], d["debt"]["baseline"]
    if base is None:
        print("debt: no baseline at config/debt-baseline.json — run `tools/progress.py --debt-baseline`")
        return 1
    rose, unavailable, new = [], [], []
    for k, _ in DEBT_COUNTERS:
        v = cur.get(k)
        if v is None:
            unavailable.append(k)
            continue
        if k not in base:
            new.append(k)
            continue
        if v > base[k]["value"] and k not in READABILITY_COUNTERS:
            rose.append((k, base[k]["value"], v))
    for k in unavailable:
        print("debt: %s unavailable (its source is missing or stale; see the warning above)" % k)
    for k in new:
        print("debt: %s has no baseline value yet — re-record with --debt-baseline" % k)
    for k, old, v in rose:
        print("debt: %s rose %s → %s" % (k, format(old, ","), format(v, ",")))
    n = len(rose) + len(unavailable) + len(new)
    if n:
        print("debt: %d counter(s) rose" % n if not (unavailable or new) else
              "debt: %d counter(s) rose or could not be checked" % n)
        return 1
    print("debt: OK — %d counters at or below config/debt-baseline.json" % len(DEBT_COUNTERS))
    return 0


def debt_record(d, reason):
    """Re-record the baseline; refuse a counter that went up unless a reason is given."""
    cur, base = d["debt"]["counters"], d["debt"]["baseline"] or {}
    rose = [(k, base[k]["value"], v) for k, _ in DEBT_COUNTERS
            for v in [cur.get(k)] if v is not None and k in base and v > base[k]["value"]
            and k not in READABILITY_COUNTERS]
    if rose and not reason:
        for k, old, v in rose:
            print("debt: %s would rise %s → %s" % (k, format(old, ","), format(v, ",")))
        print("debt: refusing to record an increase; pass --allow-increase \"<reason>\" to record it with the reason")
        return 1
    out = {}
    for k, _ in DEBT_COUNTERS:
        v = cur.get(k)
        if v is None:                       # keep the old value rather than record nothing
            if k in base:
                out[k] = base[k]["value"] if base[k]["reason"] is None else dict(base[k])
            continue
        old = base.get(k)
        if old is not None and v > old["value"]:
            out[k] = dict(value=v, reason=reason)
        elif old is not None and old["reason"] and v == old["value"]:
            out[k] = dict(value=v, reason=old["reason"])
        else:
            out[k] = v
        marker = "  (+%s, reason recorded)" % format(v - old["value"], ",") if old is not None and v > old["value"] else ""
        print("debt: %-30s %12s -> %12s%s" % (k, format(old["value"], ",") if old is not None else "-", format(v, ","), marker))
    json.dump({"note": "Debt ratchet baseline for tools/progress.py --debt-check: every counter may only go "
                       "down. Re-record with --debt-baseline; an increase needs --allow-increase \"<reason>\" "
                       "and the reason is kept next to the value. See docs/engine/debt-ratchet.md.",
               "counters": out}, open(DEBT_BASELINE, "w"), indent=1, sort_keys=True)
    open(DEBT_BASELINE, "a").write("\n")
    print("debt: recorded %s" % os.path.relpath(DEBT_BASELINE, ROOT))
    return 0


def _walk(top, ext):
    for dirpath, _dirs, files in os.walk(top):
        for f in files:
            if f.endswith(ext):
                yield os.path.join(dirpath, f)

# The README's breakdown by code region, from config/SLUS-20836/regions.tsv.
REGION_LABELS = collections.OrderedDict([
    ("Game", "Game"), ("Alchemy", "Alchemy engine"), ("Lua", "Lua 4.0.1 interpreter"),
    ("CRI ADX", "CRI ADX"), ("CRI Sofdec", "CRI Sofdec"), ("PNG", "libpng and zlib"),
    ("Sony", "Sony SDK"), ("newlib", "newlib"), ("libgcc", "libgcc"), ("Metrowerks", "Metrowerks runtime"),
    ("Static", "Static initialisers")])
REGION_ORDER = list(REGION_LABELS.values())


def region_of(va):
    row = regions.of(va)
    if row is None or row.group not in REGION_LABELS:
        raise ValueError("0x%x is outside every code region" % va)
    return REGION_LABELS[row.group]


# ---- readable: the second half of the work -------------------------------------------
# A matched function proves the bytes. It is *readable* when a person can also follow it without the
# disassembly open: every condition below is a mechanical test on the function's own source text
# (comments and string literals blanked), so the figure is a floor, not a judgement of quality.
SLOT_NAME_RE = re.compile(r"vfunc_\d+(?:__[0-9a-f]{8})?$")
# A virtual call that is still a slot number: `Class__vfunc_23(...)`, `->vfunc_23(`, `->slot_4(`, `->vf7(`,
# or a call through a cast to a function-pointer table.
SLOT_REF_RE = re.compile(r"vfunc_\d+\b|(?:->|\.)\s*(?:slot_?\d+|vf\d+|v\d+|vX)\s*\(|\(\s*\*+\s*\(\s*[\w\s\*]+\(\s*\*+\s*\)")
OFFSET_MEMBER_RE = re.compile(r"(?:->|\.)\s*(?:f\d+|unk_?[0-9A-Fa-f]+|field_?[0-9A-Fa-fx]+)\b")
OFFSET_CAST_RE = re.compile(r"\(\s*(?:unsigned\s+|signed\s+)?(?:char|u8|s8|int|u32|s32|void)\s*\*\s*\)\s*\(?\s*\w+\s*\)?"
                            r"\s*\+\s*(?:0x[0-9a-fA-F]+|\d+)")
# Leftovers beyond M2C_IDIOM_RE, which the debt ratchet shares: stack-offset locals (`sp5C`, upper-case
# hex so `spec` stays a word) and the other generated spellings of a local.
LOCAL_IDIOM_RE = re.compile(r"\b(?:sp[0-9A-F]{1,4}|phi_\w+|saved_reg_\w+|local_[0-9a-f]+|[a-z]{1,2}Var\d+|"
                            r"a?[a-z]Stack\w+|param_\d+)\b")
# A type defined in a source file, and the shapes that name nothing: one or two letters with any digits
# (`S`, `VC`, `V3`), a word with a size or offset on the end (`Info176`, `Obj0060`), `Obj`, `DW4VC_232_2`.
TYPE_DEFINITION_RE = re.compile(r"\b(?:struct|class|union|enum)\s+([A-Za-z_]\w*)\s*(?::[^{;]*)?\{|\}\s*([A-Za-z_]\w*)\s*;")
PLACEHOLDER_TYPE_RE = re.compile(r"[A-Za-z]{1,2}\d*|[A-Za-z]{3}\d+|\w*[A-Za-z_]\d{3,}|Obj|DW4\w*")
IDENTIFIER_RE = re.compile(r"\b[A-Za-z_]\w*\b")
HEX_PART_RE = re.compile(r"(?:0x)?[0-9a-fA-F]{6,8}$")
IMAGE_LO, IMAGE_HI = 0x100000, 0x600000


def carries_address(identifier):
    """True when a `_`-separated part of `identifier` is an address in the image. An address says
    where something is, not what it is, so a name holding one is not recovered, whatever surrounds
    it: `thunk_FUN_002ed330`, `Memory_FreeBufferAlias_002ed4b0`, `GAMERAM_004f1234`."""
    return any(HEX_PART_RE.fullmatch(part) and IMAGE_LO <= int(part, 16) < IMAGE_HI
               for part in identifier.split("_"))


READABLE_CHECKS = [
    ("name", "the function has a recovered name, not `FUN_<address>` or a numbered virtual slot"),
    ("addresses", "no name holds an address: not the function's own, nor any function, variable or type it uses"),
    ("types", "the types it uses have real names, not a placeholder such as `S`, `Obj`, `Info176` or `DW4VC_232_2`"),
    ("placed", "it sits in its class or module file, not `src/unmatched/`"),
    ("references", "what it calls and reads is named: no `FUN_`/`DAT_` references"),
    ("idioms", "no decompiler leftovers: `temp_*`, `var_*`, `argN`, stack-offset locals such as `sp5C`"),
    ("fields", "fields are reached through named struct members: no `fNN`/`unkNN` members, no cast of a pointer plus an offset"),
    ("virtuals", "virtual calls go through a named method, not a slot number such as `v216` or a cast function pointer"),
]
_READABLE = {}


def _function_texts(path):
    """{name: source text of that definition} for one file, comments and strings blanked."""
    from typed_coverage import strip_comments_and_strings
    try:
        raw = open(path, errors="replace").read()
    except OSError:
        return {}, ""
    out = {}
    try:
        for name, start, end in units.definitions(raw):
            out[name] = strip_comments_and_strings(raw[start:end])
    except Exception:                       # an unparsable file is judged whole, which is the stricter reading
        pass
    return out, strip_comments_and_strings(raw)


def readable_failures(name, path, cache):
    """The READABLE_CHECKS keys `name` fails; an empty list means the function is readable.
    Stock library source under src/third_party/ is its authors' own text (never edited here), so it
    is readable as it stands: its identifiers (`arg1`, `var_or_func`) are not decompiler leftovers."""
    if "/third_party/" in path.replace(os.sep, "/"):
        return []
    if path not in cache:
        cache[path] = _function_texts(path)
    texts, whole = cache[path]
    text = texts.get(name, whole)
    body = re.sub(r"\b%s\b" % re.escape(name), " ", text)            # its own name is not a reference
    failed = []
    if not named(name) or SLOT_NAME_RE.search(name):
        failed.append("name")
    if "/unmatched/" in path.replace(os.sep, "/"):
        failed.append("placed")
    if carries_address(name) or any(carries_address(i) for i in IDENTIFIER_RE.findall(body)):
        failed.append("addresses")
    used = set(IDENTIFIER_RE.findall(body))
    defined = {a or b for a, b in TYPE_DEFINITION_RE.findall(whole)}
    if any(PLACEHOLDER_TYPE_RE.fullmatch(t) for t in defined & used):
        failed.append("types")
    if FUN_DAT_RE.search(body):
        failed.append("references")
    if M2C_IDIOM_RE.search(body) or LOCAL_IDIOM_RE.search(body):
        failed.append("idioms")
    if OFFSET_MEMBER_RE.search(body) or OFFSET_CAST_RE.search(body):
        failed.append("fields")
    if SLOT_REF_RE.search(body):
        failed.append("virtuals")
    return failed


def readable(syms=None, paths=None, cats=None):
    """{"names": set of readable matched functions, "functions", "bytes", "matched_functions",
    "failing": {check: {"functions", "bytes"}}} over the functions make check classifies as `match`."""
    if _READABLE:
        return _READABLE
    syms = syms or load_symbols()
    paths = paths or have_src_paths()
    cats = cats if cats is not None else (load_categories() or {})
    cache, names = {}, set()
    failing = {key: {"functions": 0, "bytes": 0} for key, _ in READABLE_CHECKS}
    functions = size_total = matched = 0
    for va, size, name in syms:
        if name not in paths or cats.get(va, ("",))[0] != "match":
            continue
        matched += 1
        failed = readable_failures(name, paths[name], cache)
        for key in failed:
            failing[key]["functions"] += 1
            failing[key]["bytes"] += size
        if not failed:
            names.add(name)
            functions += 1
            size_total += size
    _READABLE.update(names=names, functions=functions, bytes=size_total, matched_functions=matched, failing=failing)
    return _READABLE


def region_table():
    """Markdown rows: per region the code size, the share matched (C/C++ that make check classifies as
    `match`: bytes, exception metadata and symbol rules all pass) and the share readable (matched and
    passing every READABLE_CHECKS condition)."""
    syms = load_symbols()
    paths = have_src_paths()
    cats = load_categories() or {}
    clear = readable(syms, paths, cats)["names"]
    rows = {r: [0, 0, 0] for r in REGION_ORDER}      # total, matched, readable
    for va, size, name in syms:
        row = rows[region_of(va)]
        row[0] += size
        if name in paths and cats.get(va, ("",))[0] == "match":
            row[1] += size
            if name in clear:
                row[2] += size
    out = ["| Region | Size | Matched | Readable |",
           "| --- | ---: | ---: | ---: |"]
    tot = [0, 0, 0]
    for r in REGION_ORDER:
        t, m, c = rows[r]
        tot = [x + y for x, y in zip(tot, rows[r])]
        out.append("| %s | %d KB | %.1f %% | %.1f %% |" % (r, round(t / 1024), pct(m, t), pct(c, t)))
    t, m, c = tot
    out.append("| **Total** | **%d KB** | **%.1f %%** | **%.1f %%** |" % (round(t / 1024), pct(m, t), pct(c, t)))
    return "\n".join(out)



def readme_block(d):
    """The README progress block: the per-region table and a link to PROGRESS.md.

    Generated on every `make progress`, so the README holds no hand-written figure that can go
    stale; `progress --check` fails when it drifts. "Matched" is make check's `match` on C/C++
    source; "Readable" is the matched code that also passes READABLE_CHECKS. `d` is unused: the
    table reads the symbol map, src/ and data/check-categories.tsv directly.
    """
    return ("<!-- progress:start -->\n%s\n\nThe full figures and the verification debt are in "
            "[PROGRESS.md](PROGRESS.md).\n<!-- progress:end -->" % region_table())


def f_(d):
    return d["functions"]["matched"]


def b_fv(d):
    return d["functions"]["fully_verified"]


def render_md(d):
    f, b, m = d["functions"], d["code_bytes"], d["metadata"]
    cats = d.get("categories") or {}
    L = []
    A = L.append
    A("# Progress")
    A("")
    A("A snapshot of how much of `game.elf` has been rebuilt as matching C. "
      "Regenerated by `tools/progress.py`; do not edit by hand.")
    A("")
    A("```")
    if cats.get("recorded"):
        A("fully verified C/C++")
        A("  functions  %s %5.1f %%   %s / %s" % (bar(pct(f["fully_verified"], f["total"])),
                                                  pct(f["fully_verified"], f["total"]),
                                                  format(f["fully_verified"], ","), format(f["total"], ",")))
        A("  code bytes %s %5.1f %%   %s / %s   (make check `match`: code bytes, exception metadata and symbol rules)"
          % (bar(pct(b["fully_verified"], b["total"])), pct(b["fully_verified"], b["total"]),
             format(b["fully_verified"], ","), format(b["total"], ",")))
        A("decompiled as C/C++ (code bytes identical, verification debt included — see below)")
    else:
        A("fully verified: (categories not recorded — data/check-categories.tsv missing or stale; run make check)")
        A("decompiled as C/C++ (code bytes identical)")
    A("  functions  %s %5.1f %%   %s / %s" % (bar(pct(f["matched"], f["total"])),
                                              pct(f["matched"], f["total"]),
                                              format(f["matched"], ","), format(f["total"], ",")))
    A("  code bytes %s %5.1f %%   %s / %s" % (bar(pct(b["matched"], b["total"])),
                                              pct(b["matched"], b["total"]),
                                              format(b["matched"], ","), format(b["total"], ",")))
    lk = d["link"]
    A("fully linked %s %5.1f %%   %s / %s bytes of the section linked from C/C++"
      % (bar(lk["from_c_pct"]), lk["from_c_pct"],
         format(lk["from_c_bytes"], ","), format(lk["section_bytes"], ",")))
    dd = d["data_bytes"]
    A("data bytes %s %5.1f %%   %s / %s identified"
      % (bar(dd["pct"]), dd["pct"], format(dd["identified"], ","),
         format(dd["total"], ",")))
    A("not counted: %s asm bodies, %s code bytes (%.1f %%): retail instructions kept as source, "
      "in no figure above" % (format(b["functions_asm_body"], ","), format(b["asm_body"], ","),
                              pct(b["asm_body"], b["total"])))
    A("```")
    A("")
    A("The function count is flattered by small functions: the ones done have a median size of "
      "**%d bytes** against **%d** for the rest, so byte coverage is the honest headline."
      % (d["median_size"]["matched"], d["median_size"]["unmatched"]))
    A("")

    A("## Verified and debt")
    A("")
    if cats.get("recorded"):
        A("`make check` classifies every decompiled unit (`tools/check.py`, committed as "
          "`data/check-categories.tsv`). Only **match** is fully verified; the other rows are code "
          "bytes identical to retail with something still unproven, and they are the headline's debt, "
          "not part of it. An **asm-body** row recovers nothing, so it is outside the decompiled "
          "figure as well.")
        A("")
        A("| category | functions | code bytes | % of code bytes | meaning |")
        A("| --- | ---: | ---: | ---: | --- |")
        for k in CATEGORY_ORDER:
            row = cats["by"].get(k, dict(functions=0, bytes=0))
            if k != "match" and not row["functions"]:
                continue
            A("| %s`%s`%s | %s | %s | %.1f | %s |"
              % ("**" if k == "match" else "", k, "**" if k == "match" else "",
                 format(row["functions"], ","), format(row["bytes"], ","),
                 pct(row["bytes"], b["total"]), CATEGORY_EXPLAIN.get(k, "")))
        co = cats["code_only_by_exc"]
        if any(v["functions"] for v in co.values()):
            A("")
            A("The `code-only` debt by exception-metadata reason (from each unit's diagnostic):")
            A("")
            A("| reason | functions | code bytes | meaning |")
            A("| --- | ---: | ---: | --- |")
            for k in EXC_REASONS:
                if co[k]["functions"]:
                    A("| `%s` | %s | %s | %s |" % (k, format(co[k]["functions"], ","),
                                                  format(co[k]["bytes"], ","), EXC_EXPLAIN[k]))
    else:
        A("**(categories not recorded)** — %s. The headline above is therefore the decompiled "
          "(code-bytes-identical) figure, not the fully verified one." % cats.get("warning", "no table"))
    A("")
    A("**Fully linked** is the sibling number a WIP decomp is read on, and the bar above measures "
      "bytes built from recovered C/C++ over the **%s-byte "
      "section** that `make link` emits and `tools/linkcheck.py` compares (`0x100000..0x554b00`, "
      "code + data). The loader also maps a zero-initialised `.bss` tail to `0x58d280`, but the "
      "link never emits it, so it is not in the denominator. The **asm bodies** are not "
      "counted: they link from `src/`, but an `asm` body is the retail instructions wrapped in "
      "a function (docs/engine/asm-body-matches.md), not recovered C, so counting it would "
      "overstate the decompilation. Elsewhere the two "
      "headlines differ (Twilight Princess: 12.07 %% decompiled, 8.12 %% fully linked) since "
      "a translation-unit build can only drop a unit's asm stub once the *whole* unit is "
      "decompiled. Counting **code alone**, this repo's two numbers are identical — "
      "**%.1f %%** C/C++ — and that is a property of the pipeline, not a coincidence: "
      "`tools/layout.py` tiles the section per function, so `tools/linkgen.py` replaces "
      "retail one function at a time and a match is linked from source immediately. "
      "`make link` prints the accounting from the link itself — **%s units / %s bytes from "
      "C/C++ (%s of them compiler-generated jump tables), %s units / %s bytes of asm "
      "bodies, %s bytes from `asm/`** — and the section then compares byte-identical, so "
      "nothing decompiled is waiting to be linked."
      % (format(lk["section_bytes"], ","), pct(b["matched"], b["total"]),
         format(lk["from_c_units"], ","), format(lk["from_c_bytes"], ","),
         format(lk["jtbl_bytes"], ","), format(lk["from_asm_body_units"], ","),
         format(lk["from_asm_body_bytes"], ","), format(lk["asm_bytes"], ",")))
    A("")

    A("## Readable")
    A("")
    rd = d["readable"]
    A("Matching proves the bytes; it does not make the source readable. A matched function counts as "
      "**readable** when it also passes every test below. The tests are mechanical, so this is a floor: "
      "a function can pass them all and still be hard to follow.")
    A("")
    A("**%s** of the %s matched functions are readable: **%s** code bytes, **%.1f %%** of the code."
      % (format(rd["functions"], ","), format(rd["matched_functions"], ","), format(rd["bytes"], ","),
         pct(rd["bytes"], d["code_bytes"]["total"])))
    A("")
    A("| A matched function is readable when | matched functions failing it | code bytes |")
    A("| --- | ---: | ---: |")
    for key, text in READABLE_CHECKS:
        fail = rd["failing"][key]
        A("| %s | %s | %s |" % (text, format(fail["functions"], ","), format(fail["bytes"], ",")))
    A("")

    A("## Debt")
    A("")
    A("The debt ratchet ([`docs/engine/debt-ratchet.md`](docs/engine/debt-ratchet.md)): every "
      "counter below is read from committed files and may only go down. `tools/progress.py "
      "--debt-check` fails when one rises above `config/debt-baseline.json`; `--debt-baseline` "
      "re-records it, and an increase is recorded only with `--allow-increase \"<reason>\"`, the "
      "reason kept next to the value.")
    A("")
    debt = d.get("debt") or {}
    cur, base = debt.get("counters") or {}, debt.get("baseline")
    A("| counter | baseline | current | Δ | measures |")
    A("| --- | ---: | ---: | ---: | --- |")
    for k, what in DEBT_COUNTERS:
        v = cur.get(k)
        bv = base.get(k, {}).get("value") if base else None
        reason = base.get(k, {}).get("reason") if base else None
        cur_s = format(v, ",") if v is not None else "n/a"
        base_s = format(bv, ",") if bv is not None else "—"
        if v is None or bv is None:
            delta = "—"
        else:
            delta = ("%+d" % (v - bv)) if v != bv else "0"
            if v > bv:
                delta = "**" + delta + "**"
        A("| `%s` | %s | %s | %s | %s%s |"
          % (k, base_s, cur_s, delta, what,
             (" — increase recorded: " + reason) if reason else ""))
    A("")
    if base is None:
        A("No baseline recorded yet (`tools/progress.py --debt-baseline`).")
        A("")

    A("## The data half")
    A("")
    A("A decompilation is read on two numbers, code and data: code bytes and data bytes, ")
    A("each with its own bar. The image here is a single ")
    A("merged section, so \"data\" is what `tools/layout.py` tiles *between* the functions; ")
    A("`tools/datamap.py` then classifies those bytes from the metadata the repo has recovered. ")
    A("Bytes in `?` are not a failure — they are alignment, tables whose extent is not pinned ")
    A("yet, and the rest of `.bss`.")
    A("")
    A("| kind | bytes | % of data |")
    A("| --- | ---: | ---: |")
    for k in ("jtbl", "vtable", "str", "handle", "?"):
        A("| `%s` | %s | %.1f |" % (k, format(dd["kinds"][k], ","),
                                     100.0 * dd["kinds"][k] / dd["total"]))
    A("")


    A("## By size")
    A("")
    A("| size (bytes) | functions | matched | code bytes | matched | % |")
    A("| --- | ---: | ---: | ---: | ---: | ---: |")
    for band in d["bands"]:
        hi = "∞" if band["hi"] >= 10 ** 9 else format(band["hi"], ",")
        A("| %s–%s | %s | %s | %s | %s | %.1f |"
          % (format(band["lo"], ","), hi, format(band["total"], ","),
             format(band["matched"], ","), format(band["total_bytes"], ","),
             format(band["matched_bytes"], ","), pct(band["matched"], band["total"])))
    A("")

    A("## Where in the binary")
    A("")
    A("The section in %d equal parts. `0x00100000` is the start of everything." % REGIONS)
    A("")
    A("| address range | matched | % |")
    A("| --- | --- | --: |")
    for r in d["regions"]:
        A("| `0x%06x`–`0x%06x` | `%s` | %.1f |"
          % (r["lo"], r["hi"], bar(pct(r["matched_bytes"], r["total_bytes"])),
             pct(r["matched_bytes"], r["total_bytes"])))
    A("")

    A("## Largest functions matched so far")
    A("")
    A("| address | size | function |")
    A("| --- | ---: | --- |")
    for s in d["largest"]:
        A("| `%s` | %s | `%s` |" % (s["va"], format(s["size"], ","), s["name"]))
    A("")

    if m:
        A("## Recovered metadata")
        A("")
        A("| | |")
        A("| --- | --- |")
        A("| functions with a recovered name (any: role names included) | %s of %s |"
          % (format(f["named"], ","), format(f["total"], ",")))
        A("| functions with a **semantic** name (not `FUN_`/`thunk_`, not `::vfunc_NN`, "
          "not `*_GetMetaObject`/`_GetVTable`/`_Register`/`_InitFields`) | %s of %s "
          "(%s of them matched) |"
          % (format(f["named_semantic"], ","), format(f["total"], ","),
             format(f["named_semantic_matched"], ",")))
        if "rtti_records" in m:
            A("| RTTI records / vtables / vfunc names | %s / %s / %s |"
              % (m["rtti_records"], m["vtables"], format(m["vfunc_names"], ",")))
        if "metaobjects" in m:
            A("| reflection MetaObjects (with fields) | %s (%s) |"
              % (format(m["metaobjects"], ","), format(m["classes_with_fields"], ",")))
        if "fields" in m:
            A("| reflection fields with offset and type | %s |" % format(m["fields"], ","))
        if "table_functions" in m:
            A("| switch jump tables recovered | %s tables, %s entries, in %s functions |"
              % (format(m["tables"], ","), format(m["table_entries"], ","), m["table_functions"]))
        if "lua_chunks" in m:
            A("| Lua chunks decompiled | %s |" % format(m["lua_chunks"], ","))
        if d.get("typed") and d["typed"].get("total"):
            t = d["typed"]
            A("| field accesses using a **recovered** type (not an offset cast) | %s of %s (%.2f %%) |"
              % (format(t["recovered"], ","), format(t["total"], ","), t["pct"]))
        if "asm_units" in m:
            A("| functions in the retail split (`asm/`, generated) | %s |" % format(m["asm_units"], ","))
        A("")

    A("## How these numbers are produced")
    A("")
    A("A function counts as decompiled when `src/<symbol>.c` or `src/<symbol>.cpp` defines it as C/C++. Every")
    A("file there was written only after `tools/verify.py` had proved its compiled bytes identical")
    A("to retail, so this is a *record* of verification rather than a re-verification: the numbers")
    A("can be computed from the repository alone, which is what lets them be published on every")
    A("push. To prove the tree again, `make check` (needs the retail ELF and the original")
    A("compiler); `make link` then rebuilds the whole section and compares it byte-for-byte.")
    A("")
    A("**Fully verified** is narrower: `make check` also compares each unit's exception metadata")
    A("and symbol rules, and writes the per-unit category to `data/check-categories.tsv` (committed,")
    A("generated). This tool reads that table; when it is missing, or its row count is not the")
    A("number of decompiled units (a check run from another tree state), the figures are marked")
    A("*(categories not recorded)* and the headline falls back to the decompiled figure.")
    A("")
    A("Sizes and addresses come from `config/SLUS-20836/symbols.txt`, which is committed and regenerated by")
    A("`tools/split.py`.")
    A("")
    A("A function is an **asm body**, and is counted in no figure, when its definition is an MWCC `asm` function under")
    A("`#pragma optimization_level 0` — decided from the file's content, wherever the file sits")
    A("(asm bodies are not kept in the repository). A C function that contains an inline")
    A("`asm { sync }` statement is C. A **semantic name** is a recovered name that says what the")
    A("function does; the per-class boilerplate names (`*_GetMetaObject`, `*_GetVTable`,")
    A("`*_Register`, `*_InitFields`) and the vtable-slot names (`Class::vfunc_NN`) are real names")
    A("but mechanical, so they are counted in the first row and excluded from the second.")
    A("")
    return "\n".join(L)


def write(path, text):
    old = open(path).read() if os.path.exists(path) else None
    if old == text:
        return False
    open(path, "w").write(text)
    return True


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--report", action="store_true", help="print the summary, write nothing")
    ap.add_argument("--json", action="store_true", help="dump the JSON to stdout")
    ap.add_argument("--check", action="store_true",
                    help="write nothing; exit 1 if the committed outputs are stale")
    ap.add_argument("--debt-check", action="store_true",
                    help="exit 1 naming every debt counter above config/debt-baseline.json")
    ap.add_argument("--debt-baseline", action="store_true",
                    help="re-record config/debt-baseline.json (refuses an increase without --allow-increase)")
    ap.add_argument("--allow-increase", metavar="REASON", default=None,
                    help="with --debt-baseline: record a counter that went up, keeping this reason next to it")
    a = ap.parse_args(argv)

    d = collect()
    f, b = d["functions"], d["code_bytes"]
    if a.debt_check:
        return debt_check(d)
    if a.debt_baseline:
        return debt_record(d, a.allow_increase)
    if a.json:
        print(json.dumps(d, indent=1, sort_keys=True))
        return 0
    if a.report:
        lk = d["link"]
        cats = d["categories"]
        if cats["recorded"]:
            head = ("%.1f %% of the code bytes fully verified as C/C++ (%d/%d functions), %.1f %% decompiled"
                    % (pct(b["fully_verified"], b["total"]), f["fully_verified"], f["total"],
                       pct(b["matched"], b["total"])))
        else:
            head = ("%.1f %% of the code bytes decompiled (categories not recorded)"
                    % pct(b["matched"], b["total"]))
        print("%s — %d/%d functions (%.1f %%); fully linked %.1f %% of the section from C/C++; "
              "%d asm bodies (%.1f %% of the code bytes) not counted"
              % (head, f["matched"], f["total"], pct(f["matched"], f["total"]), lk["from_c_pct"],
                 b["functions_asm_body"], pct(b["asm_body"], b["total"])))
        return 0

    changed = []
    if a.check:
        # Turn "are the committed numbers current?" into an exit code instead of a diff to
        # inspect. Nothing is written on this path.
        stale = [os.path.relpath(p, ROOT) for p, t in
                 ((PROGRESS_MD, render_md(d)),
                  (PROGRESS_JSON, json.dumps(d, indent=1, sort_keys=True) + "\n"))
                 if (open(p).read() if os.path.exists(p) else None) != t]
        if os.path.exists(README):
            rd = open(README).read()
            new = re.sub(r"<!-- progress:start -->.*?<!-- progress:end -->",
                         readme_block(d), rd, count=1, flags=re.S)
            if new != rd:
                stale.append(os.path.relpath(README, ROOT))
        if stale:
            print("progress --check: stale: %s — run `make progress`" % ", ".join(stale))
            return 1
        print("progress --check: up to date")
        return 0
    changed = [p for p, t in ((PROGRESS_MD, render_md(d)),
                             (PROGRESS_JSON, json.dumps(d, indent=1, sort_keys=True) + "\n"))
               if write(p, t)]
    if os.path.exists(README):
        rd = open(README).read()
        blk = readme_block(d)
        new = re.sub(r"<!-- progress:start -->.*?<!-- progress:end -->", blk, rd, count=1, flags=re.S)
        if new != rd:
            open(README, "w").write(new)
            changed.append(README)
    print("progress: %.1f %% of %s code bytes, %.1f %% of %s functions%s"
          % (pct(b["matched"], b["total"]), format(b["total"], ","),
             pct(f["matched"], f["total"]), format(f["total"], ","),
             "  (updated %s)" % ", ".join(os.path.basename(c) for c in changed)
             if changed else "  (no change)"))
    return 0


if __name__ == "__main__":
    sys.exit(main())
