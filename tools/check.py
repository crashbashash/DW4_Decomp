#!/usr/bin/env python3
"""
check.py — coverage and correctness for the matching-decompilation build.

Two questions, both answered against the retail image rather than by trust:

  * **Is the split honest?** Every `asm/<name>.s` is assembled and its bytes
    compared against `game.elf`. If a split unit does not round-trip
    byte-exactly, the build is lying and this fails loudly.
  * **How much is actually decompiled?** For every symbol that has a C
    implementation (`src/<name>.c`), compile it with the original compiler
    (MWCCPS2 3.0 `011126` via wibo) and diff the instruction words against
    retail. That is the coverage number, and it is the only one worth reporting.

Usage:
  check.py                    # split integrity + coverage
  check.py --split-only       # just verify asm/ round-trips
  check.py --function 0x151090 --cand src/f1.c   # one candidate, through tools/verify.py
  check.py --list-mismatch    # names of functions whose C does not match

The single-function mode is `tools/verify.py` with the unit profile table
(config/SLUS-20836/units.tsv), the per-function override tables and the ownership table
applied: exact length, relocations resolved, jump tables and exception metadata
compared. (It used to compare a raw prefix of the object's words, which called a
candidate with trailing extra code or unapplied relocations a match.)

Every function is compiled under its translation unit's profile first (compiler,
flags and exception mode from config/SLUS-20836/units.tsv; docs/engine/build-profiles.md).
A provisional per-function override (config/SLUS-20836/unit-flags.tsv, unit-compilers.tsv)
is tried only when that fails, and a function that matches only that way is
`foreign-profile` debt. An override the unit profile makes unnecessary is
reported after the categories (`!! stale overrides:`) so its row can be deleted.

Besides the matched count, the coverage report says how much of the retail C++
exception metadata (config/SLUS-20836/exceptions.txt) the decompiled units reproduce:
`exc=ok` units compared their index record and table byte for byte; `missing`
ones are compiled without the metadata retail keeps for them; `extra` ones
emit metadata retail never had; `differ` ones emit a different shape or bytes.

Every verified unit lands in exactly one category (tools/verify.py `category`):

  match          code bytes, exception metadata and symbol rules all pass
  code-only      code bytes identical, exception metadata unproven
                 (exc=missing|extra|differ: build mode or cleanup scope)
  name-defect    code bytes identical, a symbol-rule refusal: a data name on a
                 function start, or a mapped name whose eight-digit suffix is
                 not its address
  inventory-gap  code bytes identical, a reference lands in a symbol-map gap or
                 inside another function's recorded extent
  unapproved      code bytes identical, but the source uses inline `asm` or `volatile` with no row
                  in config/source-approvals.tsv; counted in no matched figure.
  foreign-profile code bytes identical only under a provisional per-function
                 override whose compiler, flags or exception mode differ from
                 the function's unit profile (config/SLUS-20836/units.tsv)
  asm-body       code bytes identical because the source is the retail
                 instructions in an `asm` function: nothing recovered, so it
                 counts as neither decompiled nor matched
  assembly       code bytes identical from an owner-approved hand-written
                 assembly source (config/assembly-sources.tsv): recovered,
                 but not C, so counted apart from the C figures
  mismatch       code bytes, size, jump table or object shape differ (this
                 includes smuggled data and unowned sections)
  compile        the unit does not compile

The `cover :` line counts only `match`, and its decompiled figure leaves out the
asm bodies; the other categories are printed with
a `!! debt:` prefix so they are never read as green. Exit status 1 only for
`mismatch`, `compile` or a split failure. The per-unit list is written to
build/check-categories.tsv (tab-separated: `va` hex, `name`, `category`,
`diagnostic` = the first reason line of the unit's verify report, or `-`)
for tools/progress.py. A unit whose exception metadata the relink cannot place
(exc=extra/differ) has `; orphan N bytes` appended to its diagnostic: the
aligned size of its `.exceptix`/`.exception` sections, which tools/linkcheck.py
sums as the recorded orphan debt its gate allows.

A whole-tree run ends with the section census of the last relink's objects
(`sections: N objects, {name: count, ...}, K unknown`): every section name
must be in tools/verify.py's COMPARED_SECTIONS or DEBT_SECTIONS, and an unknown
name is a failure (tools/test_section_census.py checks the same).

Exit status: 0 no mismatch/compile failure, 1 otherwise or a split failure.
"""
import argparse
import concurrent.futures
import json
import os
import re
import struct
import subprocess
import sys
import threading

import asmsources
import sourceapprovals
import buildcache
import cc
import srctree
import unitobjects
import unitprofiles
import units


def TMP_TAG():
    """A scratch-file tag unique to this *call's* thread.

    Must be a function, not a module constant: a constant freezes the importing
    thread's id, so a `--jobs` pool would have every worker write the same path.
    `getpid` separates processes, `get_ident` the threads within one (the same
    reasoning as `verify.TMP_TAG`, which parallel tooling already relies on).
    """
    return "%d_%d" % (os.getpid(), threading.get_ident())

VADDR_BASE, FILE_BASE = 0x100000, 0x80
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ELF_DEFAULT = os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36")
MWCC_DEFAULT = os.path.join(ROOT, "local", "mwcps2", "3.0-011126", "mwccps2.exe")
WIBO_DEFAULT = os.path.join(ROOT, "local", "wibo")
FLAGS_DEFAULT = "-O3 -Iinclude"     # the Makefile's FLAGS; a unit row in config/SLUS-20836/unit-flags.tsv overrides it


def read_elf(path):
    with open(path, "rb") as fh:
        return fh.read()


def va_bytes(img, va, n):
    off = va - VADDR_BASE + FILE_BASE
    return img[off:off + n]


def load_symbols(path):
    out = []
    for ln in open(path):
        ln = ln.strip()
        if not ln or ln.startswith("#"):
            continue
        parts = ln.split()
        va, sz, nm = parts[0], parts[1], parts[2]   # optional 4th = original name
        out.append((int(va, 16), int(sz, 16), nm))
    return out


def object_func_words(obj, symbol=None):
    """Instruction words of a relocatable object, read from its SYMBOL TABLE.

    Do NOT parse `objdump -d` for this: objdump elides runs of 0x00000000 as
    `...`, so every `nop` pair silently disappears and a correct split looks
    wrong. Instead take the symbol's offset (st_value) and size from readelf and
    slice the raw .text bytes.

    Returns (words, size_in_bytes) or (None, None) if the symbol is absent.
    """
    binpath = os.path.join(cc.scratch_dir(), "text_%s.bin" % TMP_TAG())
    if os.path.exists(binpath):
        os.remove(binpath)
    r = subprocess.run(["mipsel-linux-gnu-objcopy", "-j", ".text", "-O", "binary",
                        obj, binpath], capture_output=True, text=True)
    if not os.path.exists(binpath):
        return None, None
    text = open(binpath, "rb").read()
    if symbol is None:
        return [struct.unpack_from("<I", text, 4 * i)[0] for i in range(len(text) // 4)], len(text)
    syms = subprocess.run(["mipsel-linux-gnu-readelf", "-sW", obj],
                          capture_output=True, text=True).stdout
    for ln in syms.splitlines():
        f = ln.split()
        # Num: Value Size Type Bind Vis Ndx Name
        if len(f) >= 8 and f[7] == symbol and f[3] in ("FUNC", "OBJECT", "NOTYPE"):
            off, size = int(f[1], 16), int(f[2], 16)
            if size:
                chunk = text[off:off + size]
                return [struct.unpack_from("<I", chunk, 4 * i)[0]
                        for i in range(len(chunk) // 4)], size
    return None, None


def assemble_s(src, out=None):
    out = out or os.path.join(cc.scratch_dir(), "s_%s.o" % TMP_TAG())
    if os.path.exists(out):
        os.remove(out)
    r = subprocess.run(["mipsel-linux-gnu-as", "-o", out, src],
                       capture_output=True, text=True)
    if not os.path.exists(out):
        return None, (r.stdout + r.stderr)[:600]
    words, _ = object_func_words(out)
    if words is None:
        return None, "no .text"
    return words, None


def tool_versions():
    """The binutils the split and object readers shell out to (their output is part of every cached answer)."""
    out = []
    for tool in ("as", "objcopy", "readelf"):
        r = subprocess.run(["mipsel-linux-gnu-" + tool, "--version"], capture_output=True, text=True)
        out.append((r.stdout or r.stderr).splitlines()[0] if (r.stdout or r.stderr) else "?")
    return "|".join(out)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", default=os.environ.get("DW4_ELF", ELF_DEFAULT))
    ap.add_argument("--symbols", default="config/SLUS-20836/symbols.txt")
    ap.add_argument("--unit-objects", default=None)
    ap.add_argument("--unit-flags", default=None)
    ap.add_argument("--unit-compilers", default=None)
    ap.add_argument("--units", default=None,
                    help="unit profile table (default config/SLUS-20836/units.tsv, or units.tsv beside --symbols)")
    ap.add_argument("--asm", default="asm")
    ap.add_argument("--src", dest="src_dir", default="src")
    ap.add_argument("--mwcc", default=os.environ.get("DW4_MWCC", MWCC_DEFAULT))
    ap.add_argument("--wibo", default=os.environ.get("DW4_WIBO", WIBO_DEFAULT))
    ap.add_argument("--flags", default=FLAGS_DEFAULT)
    ap.add_argument("--split-only", action="store_true")
    ap.add_argument("--split-limit", type=int, default=0)
    ap.add_argument("--jobs", type=int, default=os.cpu_count() or 1,
                    help="worker threads for the split and coverage sweeps "
                         "(default: all cores; 1 = serial)")
    ap.add_argument("--function", help="single VA to check against --cand")
    ap.add_argument("--cand", help="C file for --function")
    ap.add_argument("--list-mismatch", action="store_true")
    ap.add_argument("--no-cache", action="store_true",
                    help="recompute everything and write no cache (also DW4_NOCACHE=1); run this once before publishing a "
                         "milestone. Results are otherwise cached by content in build/cache/ (tools/buildcache.py)")
    ap.add_argument("--cover-limit", type=int, default=0,
                    help="check only the first N decompiled functions (for testing the tool; not a gate)")
    a = ap.parse_args(argv)
    use_cache = buildcache.enabled(a.no_cache)

    img = read_elf(a.elf)
    syms = load_symbols(a.symbols)
    total = len(syms)
    code_bytes = sum(s for _, s, _ in syms)
    rc = 0

    # ---- single-function mode -------------------------------------------------
    if a.function:
        va = int(a.function, 0)
        nm = next((n for v, _, n in syms if v == va), None)
        if nm is None:
            print("check: 0x%x not in %s" % (va, a.symbols), file=sys.stderr)
            return 2
        if not a.cand:
            print("check: --function needs --cand <file.c>", file=sys.stderr)
            return 2
        import verify as vfy
        src, tmp = units.standalone(a.cand, nm, symbols=a.symbols, unit_objects=a.unit_objects)
        try:
            ok, report = vfy.verify_one(va, src, flags=a.flags, elf=a.elf, symbols=a.symbols,
                                        mwcc=a.mwcc, wibo=a.wibo, unit_flags=a.unit_flags,
                                        unit_compilers=a.unit_compilers, unit_objects=a.unit_objects,
                                        units=a.units)
        finally:
            if tmp:
                os.remove(tmp)
        print(report)
        if not ok and report.startswith("compile failed"):
            return 2
        return 0 if ok else 1

    # ---- split integrity -----------------------------------------------------
    todo = syms[:a.split_limit] if a.split_limit else syms
    bad_split, missing = [], []

    # a run over the repository's own tree may prune the caches; a partial or synthetic one only merges
    whole_tree_run = (os.path.abspath(a.src_dir) == os.path.join(ROOT, "src")
                      and os.path.abspath(a.symbols) == os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt"))
    split_store = buildcache.Store("check-split", use_cache)
    split_fp = buildcache.sha("split", buildcache.file_sha(a.elf), buildcache.tools_sha("check.py"), tool_versions())

    def split_one(item):
        va, sz, nm = item
        path = os.path.join(a.asm, nm + ".s")
        if not os.path.exists(path):
            return (nm, "missing")
        key = None
        if use_cache:
            with open(path, "rb") as fh:
                key = buildcache.sha(split_fp, nm, va, sz, fh.read())
            if split_store.get(key):
                return None
        got, err = assemble_s(path)
        if got is None:
            return (nm, "assemble failed: " + err)
        if got[:sz // 4] != [struct.unpack_from("<I", va_bytes(img, va, sz), 4 * i)[0]
                             for i in range(sz // 4)]:
            return (nm, "bytes differ")
        if key:
            split_store.put(key, "ok")
        return None

    # `ex.map` yields in input order, so the report stays byte-for-byte identical
    # to the serial one whatever order the workers finish in.
    with concurrent.futures.ThreadPoolExecutor(max_workers=max(1, a.jobs)) as ex:
        for res in ex.map(split_one, todo):
            if res is None:
                continue
            nm, why = res
            (missing if why == "missing" else bad_split).append(
                nm if why == "missing" else res)
    split_store.save(prune=whole_tree_run)
    print(split_store.summary("split units"))
    print("split : %d/%d units round-trip byte-exactly%s%s"
          % (len(todo) - len(missing) - len(bad_split), len(todo),
             ", %d missing" % len(missing) if missing else "",
             ", %d WRONG" % len(bad_split) if bad_split else ""))
    if bad_split:
        rc = 1
        for nm, why in bad_split[:10]:
            print("   !! %s: %s" % (nm, why))
    if missing and a.split_limit == 0:
        # a partially generated asm/ tree is expected early on; report, do not fail
        print("   (%d symbols have no asm unit yet — run tools/split.py)" % len(missing))
    if a.split_only:
        return rc

    # ---- coverage ------------------------------------------------------------
    # Relocation-aware: a raw object compare only works for self-contained leaf
    # functions, because an object stores relocations rather than addresses. See
    # tools/verify.py.
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import verify as vfy

    import exceptions as exception_records
    retail_records = exception_records.load(exception_records.config_path(a.symbols))
    decompiled, matched, mismatched, failed = [], [], [], []
    exc_status = {}        # name -> ok | missing | extra | differ (units whose report carried exc=)
    categories = {}        # name -> (category, diagnostic)
    exc_token = re.compile(r"\bexc=(\w+)")
    cat_token = re.compile(r"\bcat=([\w-]+)")
    orphan_token = re.compile(r"\borphan=(\d+)")
    override_token = re.compile(r"\boverride=(\w+)")
    CATEGORIES = ("match", "code-only", "name-defect", "inventory-gap", "foreign-profile", "unapproved", "asm-body",
                  "assembly", "mismatch", "compile")

    def classify(ok, report):
        """(category, exc, diagnostic, override) from a verify report; see the docstring.

        `override` is verify's `override=` token: `foreign` (the function matched only
        under its provisional row), `unused` or `redundant` (the row is not needed)."""
        head, _, rest = report.partition("\n")
        if not ok and "compile failed" in head:
            return "compile", None, head, None
        found = cat_token.search(head)
        kind = found.group(1) if found else ("match" if ok else "mismatch")
        exc = exc_token.search(head)
        diagnostic = next((ln.strip() for ln in rest.splitlines()
                           if ln.strip() and not ln.strip().startswith("MATCH")
                           and not re.match(r"\[\s*\d+\]", ln.strip())), head if kind != "match" else "-")
        orphan = orphan_token.search(head)
        if orphan:
            diagnostic += "; orphan %s bytes" % orphan.group(1)
        override = override_token.search(head)
        return kind, exc.group(1) if exc else None, diagnostic, override.group(1) if override else None
    # `src/` is a module tree of translation units, so a symbol is resolved by
    # reading the definitions, not by its filename (tools/units.py).  Scanning
    # once costs ~0.4 s against 16,857 os.path probes.
    src_index = units.scan(a.src_dir, symbols=a.symbols, unit_objects=a.unit_objects)
    cands = [(va, sz, nm, src_index[nm]) for va, sz, nm in syms if nm in src_index]
    by_name = {nm: va for va, _, nm in syms}
    asm_bodies = {nm for _, _, nm, path in cands if nm in unitprofiles.asm_body_names(path)}
    approvals = sourceapprovals.load()
    # an MWCC `asm` function the owner approved (an `asm-function` row) was written in assembly in the
    # original source: it is counted with the hand-written assembly sources, not as an asm body
    asm_functions = {nm for _, _, nm, path in cands
                     if nm in asm_bodies and sourceapprovals.approved_asm_function(path, nm, approvals)}
    asm_bodies -= asm_functions
    assembly = asmsources.approved_names({nm: path for _, _, nm, path in cands}) | asm_functions
    decompiled = [nm for _, _, nm, _ in cands if nm not in asm_bodies and nm not in assembly]
    if a.cover_limit:
        cands = cands[:a.cover_limit]
    cover_store = buildcache.Store("check-cover", use_cache)
    profile_files = vfy.profile_input_files(a.unit_flags, a.unit_compilers, a.units)
    stale_overrides = {}   # name -> unused | redundant
    cover_fp = buildcache.sha("cover", buildcache.build_inputs_sha(
                                 a.elf, a.symbols, a.unit_objects,
                                 extra_files=profile_files + (vfy.jumptables_path(a.symbols),)),
                              repr(profile_files), os.path.abspath(a.src_dir),
                              buildcache.tree_sha(a.src_dir, skip_ext=buildcache.NOT_HEADERS),
                              buildcache.tools_sha("check.py"), buildcache.tools_sha("eegcc_compile.py"), a.flags, a.mwcc, a.wibo,
                              buildcache.file_sha(a.mwcc), buildcache.file_sha(a.wibo), tool_versions())

    def cover_one(item):
        va, sz, nm, path = item
        key = None
        if use_cache:
            # the text the compiler will see: the file itself, or the one function extracted from it
            text = open(path).read()
            owner = unitobjects.source_owner(nm, a.symbols, a.unit_objects)
            # an owner the file spells as a special member (`Class::Class`) is not a definition name
            # extract can isolate: key on the whole file, which is at least what the compiler sees
            defined = {d[0] for d in units.definitions(text)}
            body = text if len(defined) <= 1 or owner not in defined else units.extract(text, owner)
            key = buildcache.sha(cover_fp, nm, va, sz, body,
                                 buildcache.unit_profile_sha(va, a.flags, a.mwcc, a.unit_objects, units=a.units,
                                                             unit_flags=a.unit_flags, unit_compilers=a.unit_compilers,
                                                             symbols=a.symbols))
            hit = cover_store.get(key)
            if isinstance(hit, dict):
                return (nm, hit["category"], hit.get("exc"), hit.get("diagnostic", "-"), hit.get("override"))
        src, tmp = units.standalone(path, nm, symbols=a.symbols, unit_objects=a.unit_objects)
        try:
            ok, report = vfy.verify_one(va, src, flags=a.flags, elf=a.elf,
                                        symbols=a.symbols, mwcc=a.mwcc, wibo=a.wibo,
                                        unit_flags=a.unit_flags, unit_compilers=a.unit_compilers,
                                        unit_objects=a.unit_objects, units=a.units)
        finally:
            if tmp:
                os.remove(tmp)
        kind, exc, diagnostic, override = classify(ok, report)
        if key and kind != "compile":
            # the category is the cached answer, so a hit reproduces the same lines
            cover_store.put(key, {"category": kind, "exc": exc, "diagnostic": diagnostic, "override": override})
        return (nm, kind, exc, diagnostic, override)

    with concurrent.futures.ThreadPoolExecutor(max_workers=max(1, a.jobs)) as ex:
        for nm, kind, exc, diagnostic, override in ex.map(cover_one, cands):
            if nm in asm_bodies and kind not in ("mismatch", "compile"):
                kind = "asm-body"
            elif nm in assembly and kind == "match":
                kind = "assembly"
            elif kind == "match":
                # read after the cache: approving a row changes the category, not the compile
                src_path, row = src_index[nm], None
                owner = unitobjects.source_owner(nm, a.symbols, a.unit_objects)
                if sourceapprovals.defines(src_path, nm):
                    # a whole-file member is its own definition: it answers for its own uses
                    owner = nm
                else:
                    # a static the symbol map names apart (`Copy_tlbfunc` for the source's `Copy`): its
                    # uses are counted under the source's name, and its row names the symbol
                    member = unitobjects.source_name(nm, a.symbols, a.unit_objects)
                    if member != nm and sourceapprovals.defines(src_path, member):
                        owner, row = member, nm
                why = sourceapprovals.problem(src_path, owner, approvals, row=row)
                if why:
                    kind, diagnostic = "unapproved", "unapproved: " + why
            categories[nm] = (kind, diagnostic)
            if override in ("unused", "redundant"):
                stale_overrides[nm] = override
            if kind == "match":
                matched.append(nm)
            elif kind in ("asm-body", "assembly"):
                pass
            elif kind == "compile":
                failed.append((nm, diagnostic))
                continue
            else:
                mismatched.append(nm)
            if exc:
                exc_status[nm] = exc

    cover_store.save(prune=whole_tree_run and not a.cover_limit)
    print(cover_store.summary("functions compiled and compared"))
    print("code  : %d functions, %d bytes laid out in %s" % (total, code_bytes, a.symbols))
    print("cover : %d/%d decompiled in %s/ (%.1f%%), %d match byte-for-byte, %d asm bodies not counted%s"
          % (len(decompiled), total, a.src_dir,
             100.0 * len(decompiled) / total if total else 0.0, len(matched), len(asm_bodies),
             ", %d hand-written assembly sources counted apart" % len(assembly) if assembly else ""))
    counts = {kind: sum(1 for k, _ in categories.values() if k == kind) for kind in CATEGORIES}
    explain = {"match": "code bytes, exception metadata and symbol rules all pass",
               "code-only": "code bytes identical, exception metadata unproven (exc=missing/extra/differ)",
               "name-defect": "code bytes identical, a symbol name is wrong for its address",
               "inventory-gap": "code bytes identical, a reference lands outside the symbol map or inside another extent",
               "foreign-profile": "code bytes identical only under a provisional override of the unit profile (config/SLUS-20836/units.tsv)",
               "unapproved": "code bytes identical, but `asm` or `volatile` without an owner approval (config/source-approvals.tsv)",
               "asm-body": "retail instructions in an `asm` function: links identically, recovers nothing, not counted",
               "assembly": "owner-approved hand-written assembly source, byte-identical; not C, counted apart",
               "mismatch": "code bytes, size, tables or object shape differ",
               "compile": "does not compile"}
    for kind in CATEGORIES:
        if kind == "match" or counts[kind]:
            print("%s%-15s %6d  %s" % ("   " if kind in ("match", "assembly") else "!! debt: ", kind, counts[kind],
                                       explain[kind]))
    if stale_overrides:
        print("!! stale overrides: %d per-function row(s) the unit profile makes unnecessary (delete them): %s%s"
              % (len(stale_overrides), ", ".join(sorted(stale_overrides)[:8]),
                 ", ..." if len(stale_overrides) > 8 else ""))
    by_va_name = {nm: va for va, _, nm in syms}
    os.makedirs(os.path.join(ROOT, "build"), exist_ok=True)
    # Only a run over the repository's own tree describes the repository: a test
    # pointing `--src`/`--symbols` elsewhere must not overwrite the tables.
    whole_tree = (os.path.abspath(a.src_dir) == os.path.join(ROOT, "src")
                  and os.path.abspath(a.symbols) == os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt"))
    category_lines =["%08x\t%s\t%s\t%s\n" % (by_va_name[nm], nm, kind, (diagnostic or "-").replace("\t", " "))
                      for nm in sorted(categories, key=lambda n: by_va_name[n])
                      for kind, diagnostic in [categories[nm]]]
    if whole_tree:
        with open(os.path.join(ROOT, "build", "check-categories.tsv"), "w") as fh:
            fh.write("# va\tname\tcategory\tdiagnostic — GENERATED by tools/check.py; do not edit.\n")
            fh.writelines(category_lines)
    # The same table is committed as data/check-categories.tsv so tools/progress.py (which runs
    # without the compiler) can report the verified/debt split. Written only by a complete run:
    # a compile failure means the classification is partial, and the committed copy stays as it was.
    if whole_tree and not failed and not a.cover_limit:
        with open(os.path.join(ROOT, "data", "check-categories.tsv"), "w") as fh:
            fh.write("# va\tname\tcategory\tdiagnostic — GENERATED by tools/check.py (make check) and committed; "
                     "do not edit. Read by tools/progress.py.\n")
            fh.writelines(category_lines)
    with_record = [nm for _, _, nm, _ in cands if nm in by_name and by_name[nm] in retail_records]
    exc_counts = {status: sum(1 for nm in with_record if exc_status.get(nm) == status)
                  for status in ("ok", "missing", "differ")}
    print("excepts: %d of %d functions with a retail exception record are decompiled: %d reproduce it byte-for-byte, "
          "%d do not produce it (exc=missing), %d produce different metadata (exc=differ), %d fail otherwise; "
          "%d units emit metadata retail lacks (exc=extra)"
          % (len(with_record), sum(1 for v, _, _ in syms if v in retail_records),
             exc_counts["ok"], exc_counts["missing"], exc_counts["differ"],
             len(with_record) - sum(exc_counts.values()),
             sum(1 for status in exc_status.values() if status == "extra")))
    for nm in (mismatched if a.list_mismatch else mismatched[:10]):
        print("   !! %s: %s%s" % (nm, categories[nm][0], " (exc=%s)" % exc_status[nm] if nm in exc_status else ""))
    if mismatched:
        print("   (%d not matched: %d mismatch, %d debt)" % (len(mismatched), counts["mismatch"],
                                                          len(mismatched) - counts["mismatch"]))
    for nm, why in failed[:10]:
        print("   !! %s: %s" % (nm, why))
    if counts["mismatch"] or failed:
        rc = 1
    if whole_tree:
        rc = max(rc, section_census_line(a))
    return rc


def section_census_line(a):
    """Print `sections: ...` for the last relink's objects; 1 if a section name is unknown."""
    import glob
    import verify as vfy
    objects = sorted(glob.glob(os.path.join(ROOT, "build", "link", "u_*.o")))
    if not objects:
        print("sections: build/link/ has no objects (run make link for the census)")
        return 0
    counts, unknown, filled = vfy.section_census(objects)
    summary = ", ".join("%s: %d" % (name or "(null)", n)
                        for name, n in sorted(counts.items(), key=lambda kv: (-kv[1], kv[0])))
    print("sections: %d objects, {%s}, %d unknown" % (len(objects), summary, len(unknown)))
    for path, name in unknown[:10]:
        print("   !! %s: section %r is in neither COMPARED_SECTIONS nor DEBT_SECTIONS (tools/verify.py)"
              % (os.path.relpath(path, ROOT), name))
    for path, name, size in filled[:10]:
        print("   !! %s: %s has %d bytes but must be empty" % (os.path.relpath(path, ROOT), name, size))
    return 1 if unknown or filled else 0


if __name__ == "__main__":
    sys.exit(main())
