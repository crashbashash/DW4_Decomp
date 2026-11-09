#!/usr/bin/env python3
"""
linkgen.py — build the relink inputs from config/SLUS-20836/layout.txt.

Emits one assembly unit per layout entry and a linker script that places every
unit at an EXPLICIT address. Two things fall out of that:

  * alignment cannot corrupt the layout — the location counter is pinned before
    each input, so no `.align` inside a unit can shift anything;
  * a wrong size is not silently absorbed — if a unit does not occupy exactly the
    bytes the layout says it does, the next `. = addr` would move backwards and
    `ld` fails, loudly.

Units come from the layout, not from `asm/`, because the layout is disjoint (33
function pairs overlap in the Ghidra dump) and its units are the exact sizes to
place. `asm/` stays the human-readable per-function view.

A compiled C++ unit also carries its exception index record (`.exceptix`) and,
with cleanup actions, its exception table (`.exception`). Retail keeps those in
the raw data region (config/SLUS-20836/exceptions.txt, tools/exceptions.py), so the data
unit holding them is carved into raw fragments around the retail slots and the
compiled sections are pinned there: the relink then reproduces them from the
source instead of orphaning them, and linkcheck's byte compare covers them.

Usage:
  linkgen.py --all          # regenerate everything into build/link/ (slow: ~28k files)
  linkgen.py --verify-only  # just re-emit the linker script (units already exist)
"""
import argparse
import bisect
import concurrent.futures
import os
import re
import shutil
import struct
import subprocess
import sys
import threading

import asmsources
import buildcache
import exceptions as exception_records
import srctree
import units as unitfiles
import unitobjects
import unitprofiles
import cc
import verify

VADDR_BASE, FILE_BASE = 0x100000, 0x80
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ELF_DEFAULT = os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36")
# The tree's global compiler flags, used outside every unit of config/SLUS-20836/units.tsv; a unit's
# own profile (compiler, flags, exception mode) replaces them — the retail
# ELF was built with per-file flags; docs/engine/build-profiles.md).
FLAGS_DEFAULT = "-O3 -Iinclude"


def TMP_TAG():
    """A scratch-file tag unique to this *call's* thread (see verify.TMP_TAG).

    The raw-bytes path derives its objcopy symbol names from the temp path, so a
    module-constant tag would make every `--jobs` worker collide on one file and
    one symbol set.
    """
    return "%d_%d" % (os.getpid(), threading.get_ident())


def load_layout(path):
    """-> [(va, size, kind, name, extra)]; `extra` is the jtbl owner or 'truncated'."""
    out = []
    for ln in open(path):
        if ln.startswith("#") or not ln.strip():
            continue
        p = ln.split()
        out.append((int(p[0], 16), int(p[1], 16), p[2], p[3],
                    p[4] if len(p) > 4 else None))
    return out


def reginfo_gp(path):
    """gp from the ELF's .reginfo (gprmask, cprmask[4], gp_value)."""
    img = open(path, "rb").read()
    e_shoff, = struct.unpack_from("<I", img, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", img, 0x2e)
    shstr_off = struct.unpack_from("<I", img, e_shoff + e_shstrndx * e_shentsize + 16)[0]
    for i in range(e_shnum):
        sh = struct.unpack_from("<IIIIIIIIII", img, e_shoff + i * e_shentsize)
        nm = img[shstr_off + sh[0]:img.find(b"\0", shstr_off + sh[0])].decode("latin1")
        if nm == ".reginfo":
            return struct.unpack_from("<I", img, sh[4] + 20)[0]
    return None


def _elf_sections(d):
    """[(name, size, offset)] from an ELF32 image, or None if it is not ELF."""
    if d[:4] != b"\x7fELF":
        return None
    e_shoff, = struct.unpack_from("<I", d, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", d, 0x2e)
    if not e_shoff or not e_shnum:
        return []
    shstr_off = struct.unpack_from("<I", d, e_shoff + e_shstrndx * e_shentsize + 16)[0]
    out = []
    for i in range(e_shnum):
        base = e_shoff + i * e_shentsize
        n, = struct.unpack_from("<I", d, base)
        size, = struct.unpack_from("<I", d, base + 20)
        off, = struct.unpack_from("<I", d, base + 16)
        nm = d[shstr_off + n:d.find(b"\0", shstr_off + n)].decode("latin1")
        out.append((nm, size, off))
    return out


def _section_size_objdump(obj, name):
    """Fallback for a non-ELF or unparsable object."""
    out = subprocess.run(["mipsel-linux-gnu-objdump", "-h", obj],
                         capture_output=True, text=True).stdout
    for ln in out.splitlines():
        # "  1 .text         00000008  00000000  00000000  00000040  2**0"
        m = __import__("re").match(r"\s*\d+\s+(\S+)\s+([0-9a-f]+)\s", ln)
        if m and m.group(1) == name:
            return int(m.group(2), 16)
    return 0


def section_size(obj, name=".text"):
    """Size of a named section in an object, in bytes (0 if absent).

    Parsed in Python rather than shelling out to `objdump -h`: linkgen calls this
    once per layout unit (~34k times per run) and those forks dominated the run.
    """
    try:
        with open(obj, "rb") as fh:
            secs = _elf_sections(fh.read())
    except OSError:
        secs = None
    if secs is None:
        return _section_size_objdump(obj, name)
    for nm, size, off in secs:
        if nm == name:
            return size
    return 0


def binutils_versions():
    """The binutils the raw-unit objects and object readers come from (part of every cached answer)."""
    out = []
    for tool in ("objcopy", "readelf", "objdump"):
        r = subprocess.run(["mipsel-linux-gnu-" + tool, "--version"], capture_output=True, text=True)
        out.append((r.stdout or r.stderr).splitlines()[0] if (r.stdout or r.stderr) else "?")
    return "|".join(out)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--layout", default="config/SLUS-20836/layout.txt")
    ap.add_argument("--symbols", default="config/SLUS-20836/symbols.txt")
    ap.add_argument("--unit-objects", default=None)
    ap.add_argument("--unit-flags", default=None)
    ap.add_argument("--unit-compilers", default=None)
    ap.add_argument("--units", default=None,
                    help="unit profile table (default config/SLUS-20836/units.tsv, or units.tsv beside --symbols)")
    ap.add_argument("--src", default="src", help="source inventory root")
    ap.add_argument("--mwcc", default=os.environ.get("DW4_MWCC", verify.MWCC_DEFAULT))
    ap.add_argument("--flags", default=FLAGS_DEFAULT)
    ap.add_argument("--section-start", type=lambda s: int(s, 0), default=VADDR_BASE)
    ap.add_argument("--section-size", type=lambda s: int(s, 0), default=None,
                    help="require the layout to cover exactly this many bytes")
    ap.add_argument("--elf", default=os.environ.get("DW4_ELF", ELF_DEFAULT))
    ap.add_argument("--out", default="build/link")
    ap.add_argument("--ld", dest="ld_out", default="build/link.ld")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--verify-only", action="store_true")
    ap.add_argument("--no-c", action="store_true",
                    help="use retail bytes for every code unit (ignore src/)")
    ap.add_argument("--jobs", type=int, default=os.cpu_count() or 1,
                    help="worker threads for object building (default: all cores)")
    ap.add_argument("--no-cache", action="store_true",
                    help="rebuild every object and write no cache (also DW4_NOCACHE=1). Objects are otherwise reused when their "
                         "inputs are unchanged (build/cache/, tools/buildcache.py)")
    ap.add_argument("--unit-range", default="",
                    help="LO:HI addresses; build only the layout units in that range and stop before the link script "
                         "(for testing the cache; not a link)")
    a = ap.parse_args(argv)
    use_cache = buildcache.enabled(a.no_cache)

    img = open(a.elf, "rb").read()
    units = load_layout(a.layout)
    if a.section_start < VADDR_BASE or (a.section_size is not None and
                               (a.section_size <= 0 or a.section_start + a.section_size > 0x100000000)):
        ap.error("invalid section bounds")
    if a.section_size is not None:
        cursor = a.section_start
        for address, size, _kind, _name, _extra in units:
            if address != cursor or size <= 0:
                ap.error("layout does not tile the selected section")
            cursor += size
        if cursor != a.section_start + a.section_size:
            ap.error("layout does not cover the selected section size")
    os.makedirs(a.out, exist_ok=True)
    os.makedirs(os.path.dirname(a.ld_out), exist_ok=True)

    # A `switch` compiles its jump table into `.rodata`, and `.rodata` has to be
    # placed at the retail table address rather than dropped: the layout gave every
    # table its own 'jtbl' unit (tools/layout.py), and the code unit that owns it is
    # compiled from src/. `u_<fnva>.o` is therefore both the `.text` and the table.
    code_obj = {}
    owner_tables = {}
    # tools/layout.py gives a function with several tables ONE span (the compiler's padding
    # between them stays inside it), so a compiled owner's individual tables come from
    # config/SLUS-20836/jumptables.txt, restricted to the span; a span with no listed table falls back
    # to the unit itself.
    function_address = {name: va for va, _size, kind, name, _extra in units if kind == "code"}
    recorded = verify.load_jumptables(verify.jumptables_path(a.symbols))
    for va, size, kind, _name, owner in units:
        if kind == "jtbl":
            inside = sorted((t, c) for t, c in recorded.get(function_address.get(owner), [])
                            if va <= t < va + size)
            owner_tables.setdefault(owner, []).extend(inside if len(inside) > 1 else [(va, size // 4)])
    # `src/` is a module tree of translation units: resolve a symbol by reading the
    # definitions, not by its filename (tools/units.py), so one file may define
    # several functions without any tool assuming `src/<name>.c`.
    src_index = unitfiles.scan(a.src, symbols=a.symbols, unit_objects=a.unit_objects)
    # a whole-file unit's tables are data rows, compared with retail and left as retail's bytes
    whole_file = {va for g in unitobjects.load(a.unit_objects) if g.whole_file for va in g.addresses}
    for u in units:
        if u[2] == "code" and not a.no_c:
            if u[3] in src_index and u[0] not in whole_file:
                code_obj[u[3]] = os.path.join(a.out, "u_%08x.o" % u[0])

    # ---- build every object, in parallel ------------------------------------
    # The link script must be emitted in layout order because a jump-table unit
    # reads its owner's `.rodata` size — so the work is split: build the objects
    # here (expensive, order-independent, one output path per unit), emit the
    # script below.  Every scratch path is thread-tagged, so `--jobs` is safe.
    built = {}
    store = buildcache.Store("linkgen", use_cache)
    profile_files = verify.profile_input_files(a.unit_flags, a.unit_compilers, a.units)
    link_fp = buildcache.sha("link", buildcache.build_inputs_sha(
                                a.elf, a.symbols, a.unit_objects,
                                extra_files=(a.layout, verify.jumptables_path(a.symbols),
                                             exception_records.config_path(a.symbols)) + profile_files),
                             repr(profile_files), a.section_start, a.section_size, os.path.abspath(a.src),
                             buildcache.tree_sha(a.src, skip_ext=buildcache.NOT_HEADERS),
                             buildcache.tools_sha("linkgen.py"), a.flags, buildcache.file_sha(a.mwcc), buildcache.file_sha(
                                 os.environ.get("DW4_WIBO", os.path.join(ROOT, "local", "wibo"))),
                             a.mwcc, "a.no_c=%s" % a.no_c, binutils_versions())

    records = exception_records.load(exception_records.config_path(a.symbols))
    # C++ exception metadata accounting: how many compiled records/tables are
    # placed at their retail slots, and which units `make check` flags instead.
    exception_stats = {"placed": 0, "tables": 0, "bytes": 0, "extra": 0, "missing": 0, "differ": 0}
    stats_lock = threading.Lock()

    def count(what):
        with stats_lock:
            exception_stats[what] += 1

    def build_raw(va, sz, kind, name, obj):
        """Retail bytes -> `obj`, an object of exactly `sz` bytes (the asm side of the link)."""
        off = va - VADDR_BASE + FILE_BASE
        raw = img[off:off + sz]
        if len(raw) != sz:
            return {"fatal": f"0x{va:x} size {sz} runs past the image"}
        key = None
        if use_cache:
            key = buildcache.sha(link_fp, "raw", kind, name, va, sz, raw)
            hit = store.get(key)
            if hit and buildcache.fresh_sha(obj) == hit["digest"]:
                return {"obj": obj, "undef": [], "use_c": False, "tables": {}}
        # raw bytes -> object. `as` rounds every section up to 16 bytes, so an
        # 8-byte unit becomes 16 and shifts the whole layout; objcopy -I binary
        # gives the exact size with alignment 1.
        tmp = os.path.join(cc.scratch_dir(), "%s_unit.bin" % TMP_TAG())
        with open(tmp, "wb") as fh:
            fh.write(raw)
        # objcopy -I binary names its symbols after the *path* (`/tmp/unit.bin` ->
        # `_binary__tmp_unit_bin_start`), so a temp path that varies per process
        # silently renames every symbol and linkgen's own --localize-sym/
        # --redefine-sym arguments stop matching. Derive the prefix from the path
        # we actually used instead of hard-coding it.
        symbase = "_binary_" + re.sub(r"[^A-Za-z0-9]", "_", tmp)
        # every objcopy -I binary object defines the same three symbol names,
        # so they must be localised (or renamed) or 28k units collide.
        cmd = ["mipsel-linux-gnu-objcopy", "-I", "binary", "-O", "elf32-tradlittlemips",
               "-B", "mips",
               # NB: `contents` is required. Without it the renamed section keeps its
               # size but is treated as having no data, and every unit links as
               # zeros — which looked exactly like a placement bug.
               "--rename-section", ".data=.text,alloc,load,readonly,code,contents",
               "--localize-symbol", symbase + "_end",
               "--localize-symbol", symbase + "_size"]
        if kind == "code":
            cmd += ["--redefine-sym", "%s_start=%s" % (symbase, name)]
        else:
            cmd += ["--localize-symbol", symbase + "_start"]
        cmd += [tmp, obj]
        try:
            subprocess.run(cmd, check=True, capture_output=True, text=True)
        except subprocess.CalledProcessError as e:
            return {"fatal": "objcopy failed for 0x%x: %s" % (va, (e.stderr or "").strip())}
        got = section_size(obj, ".text")
        if got != sz:
            return {"fatal": f"unit 0x{va:x} object is {got} bytes, layout says {sz}"}
        if key:
            store.put(key, {"digest": buildcache.fresh_sha(obj), "undef": [], "tables": {}})
        return {"obj": obj, "undef": [], "use_c": False, "tables": {}}

    def group_placement(records_, va):
        """A group member's reproduced record/table, as `isolate_emitted_body` kept them.

        `verify_emitted_unit` returns, per placed member whose metadata equals retail,
        (index section, index va, table section, table va, table size); the sections were
        renamed `.exceptix.dw4_<index va>` / `.exception.dw4_<table va>` for placement.
        """
        member = next((name for name, (address, _s, _z) in records_.items() if address == va), None)
        kept = getattr(records_, "exception_placements", {}).get(member)
        if not kept:
            return {}
        _idx, index_at, table_section, table_at, table_size = kept
        placement = {"index": [index_at, 12, ".exceptix.dw4_%08x" % index_at]}
        if table_section is not None:
            placement["table"] = [table_at, table_size, ".exception.dw4_%08x" % table_at]
        return placement

    def exception_placement(obj, va, group):
        """(placement, status) for a compiled unit's `.exceptix`/`.exception` sections.

        The placement maps "index"/"table" to [retail address, slot size, section]
        and is non-empty only when the object's shape fits the retail record as
        tools/verify.py requires (one 12-byte record; one table of the retail size
        less at most three padding bytes). The status names why nothing is placed:
        "extra" (retail keeps no record), "missing" (the object emits none) or
        "differ" (the shape does not fit); `make check` reports the same units. A group
        member's placement comes from the verifier instead (`group_placement`).
        """

        headers = verify.elf_section_headers(obj)
        record = records.get(va)
        if group:
            return {}, ""           # see group_placement in build_one
        index = [h[5] for n, h in headers if n == ".exceptix" and h[5]]
        table = [h[5] for n, h in headers if n == ".exception" and h[5]]
        if record is None and not index and not table:
            return {}, ""
        if record is None:
            return {}, "extra"
        if not index and not table:
            return {}, "missing"
        index_at, table_at, table_size = record
        fits = index == [12] and ((table_at is None and not table)
                                  or (table_at is not None and len(table) == 1
                                      and 0 <= table_size - table[0] <= 3))
        if not fits:
            return {}, "differ"
        placement = {"index": [index_at, 12, ".exceptix"]}
        if table_at is not None:
            placement["table"] = [table_at, table_size, ".exception"]
        return placement, ""

    retail_image, retail_gp = verify.read_elf(a.elf), reginfo_gp(a.elf)

    def build_one(u):
        va, sz, kind, name, extra = u
        key = None
        if kind == "jtbl" and extra in code_obj:
            return va, {"skip": True}
        obj = os.path.join(a.out, "u_%08x.o" % va)
        csrc = src_index.get(name) if (kind == "code" and not a.no_c) else None
        if csrc is None:
            return va, build_raw(va, sz, kind, name, obj)
        undef = []
        table_names = {}
        placement = {}
        from_group = None
        # A multi-function unit is split to a dot-named sibling so MWCC sees one
        # function; a single-function unit is compiled where it lies.
        csrc_path, tmp = unitfiles.standalone(csrc, name, symbols=a.symbols,
                                            unit_objects=a.unit_objects)
        env = dict(os.environ, MWCIncludes=os.path.abspath(a.src))
        # Compile into /tmp, not straight into build/link: wibo/MWCC writes its
        # output through a freshly-named temp file in the destination directory,
        # and build/link/ holds ~34k objects, so creating a new name there costs
        # ~160 ms against ~5 ms here (measured).  The copy back is a plain write.
        stage = os.path.join(cc.scratch_dir(), "%s_%08x.o" % (TMP_TAG(), va))
        group = unitobjects.group_for(va, a.unit_objects)
        owner = group.owner if group else va
        # The unit profile (config/SLUS-20836/units.tsv), or the function's provisional override when it has
        # one: `make check` proved the override is what reproduces the bytes (or reported the row
        # as stale), so the link builds with it and the function stays foreign-profile debt.
        try:
            resolution = unitprofiles.resolve(owner, a.flags, a.mwcc, units=a.units, unit_flags=a.unit_flags,
                                              unit_compilers=a.unit_compilers, symbols=a.symbols)
        except ValueError as error:
            return va, {"fatal": f"{name}: {error}"}
        profile = unitprofiles.for_source(resolution.override or resolution.profile, csrc_path, a.flags, a.mwcc)
        compiler, cflags = profile.compiler, unitprofiles.command_flags(profile)
        if use_cache:
            with open(csrc_path) as fh:
                body = fh.read()
            key = buildcache.sha(link_fp, "c", name, va, sz, cflags, compiler, buildcache.file_sha(compiler),
                                 buildcache.tools_sha("eegcc_compile.py") if cc.is_eegcc(compiler) else "", body,
                                 repr(owner_tables.get(name, [])), repr(records.get(va)),
                                 buildcache.unit_profile_sha(va, a.flags, a.mwcc, a.unit_objects, units=a.units,
                                                             unit_flags=a.unit_flags, unit_compilers=a.unit_compilers,
                                                             symbols=a.symbols))
            hit = store.get(key)
            if hit and buildcache.fresh_sha(obj) == hit["digest"]:
                if tmp:
                    os.remove(tmp)
                if hit.get("exc_status"):
                    count(hit["exc_status"])
                return va, {"obj": obj, "undef": hit["undef"], "use_c": True,
                            "tables": {int(k): v for k, v in hit["tables"].items()},
                            "exceptions": hit.get("exceptions", {})}
        subprocess.run(cc.compile_argv(os.environ.get("DW4_WIBO",
                                                      os.path.join(ROOT, "local", "wibo")),
                                       compiler, cflags, csrc_path, stage),
                       capture_output=True, text=True, env=env, check=False)
        if tmp and not group:
            os.remove(tmp)
        if not os.path.exists(stage):
            if tmp:
                os.remove(tmp)
            return va, {"fatal": f"compile failed for {name}"}
        if group:
            def recompile(twin_compiler, twin_flags, out):
                subprocess.run(cc.compile_argv(os.environ.get("DW4_WIBO",
                                                              os.path.join(ROOT, "local", "wibo")),
                                               twin_compiler, twin_flags, csrc_path, out),
                               capture_output=True, text=True, env=env)
                return os.path.exists(out)

            try:
                # The split sibling source is still needed to build the
                # profile-deferred duplicates; remove it once they are checked.
                good, report, records_ = verify.verify_emitted_unit(
                    stage, group, a.elf, a.symbols, profile, recompile,
                    unit_flags=a.unit_flags, unit_compilers=a.unit_compilers, units=a.units)
            finally:
                if tmp:
                    os.remove(tmp)
            head = report.partition("\n")[0]
            if records_ is None:
                # bodies, jump tables or a declared row differ: the unit cannot be linked honestly
                os.remove(stage)
                return va, {"fatal": report}
            found = re.search(r"\bexc=(missing|extra|differ)\b", head)
            if found:
                # bodies and tables exact, some retail exception metadata not reproduced:
                # link the code, place the reproduced records, keep retail's bytes for the
                # rest (`make check` reports the unit as exc=... / code-only)
                count(found.group(1))
            try:
                verify.isolate_emitted_body(stage, va, records_, group, a.symbols)
            except (ValueError, subprocess.CalledProcessError) as error:
                os.remove(stage)
                return va, {"fatal": f"{name}: {error}"}
            from_group = group_placement(records_, va)
        if not group:
            _folded, literal_errors = verify.fold_literals(stage, {name: va}, retail_image, retail_gp)
            if literal_errors:
                os.remove(stage)
                return va, {"fatal": f"{name}: {literal_errors[0]}"}
        shutil.copyfile(stage, obj)
        # MWCC's .text is exact-size; only its alignment (16) needs overriding,
        # which the linker script's SUBALIGN(1) does.
        # a group's stripped destructor bodies were removed by isolate_emitted_body and
        # nothing references them: their leftover undefined symbols need no address
        undef = [symbol for symbol, (section, _, _) in verify.object_syms(stage)[0].items()
                 if section == "UND" and not (group and symbol in group.stripped)]
        got = section_size(stage, ".text")
        os.remove(stage)
        if got != sz:
            return va, {"fatal": f"{name} compiles to {got} bytes, layout says {sz}"}
        try:
            tables = verify.jump_table_sections(obj, [] if va in whole_file else owner_tables.get(name, []))
        except ValueError as error:
            return va, {"fatal": f"{name}: {error}"}
        renames = {}
        for section, address, _size in tables:
            section_name = ".rodata.dw4_%08x" % address if len(tables) > 1 else ".rodata"
            table_names[address] = section_name
            if len(tables) > 1:
                renames[section] = section_name
        if renames:
            verify.rename_object_sections(obj, renames)
        placement, exc_status = (from_group, "") if group else exception_placement(obj, va, group)
        if exc_status:
            count(exc_status)
        if key:
            store.put(key, {"digest": buildcache.fresh_sha(obj), "undef": undef,
                            "tables": {str(k): v for k, v in table_names.items()},
                            "exceptions": placement, "exc_status": exc_status})
        return va, {"obj": obj, "undef": undef, "use_c": True,
                    "tables": table_names, "exceptions": placement}

    to_build = units
    if a.unit_range:
        lo, hi = (int(x, 16) for x in a.unit_range.split(":"))
        to_build = [u for u in units if lo <= u[0] < hi]
    # Two passes: the C units first, because where their exception metadata lands
    # decides how the raw data units are carved; then everything else.
    c_units = [u for u in to_build if u[2] == "code" and not a.no_c and u[3] in src_index]
    with concurrent.futures.ThreadPoolExecutor(max_workers=max(1, a.jobs)) as ex:
        for va, info in ex.map(build_one, c_units):
            built[va] = info

    # ---- carve the raw data units around the compiled exception metadata -----
    data_units = sorted((va, sz) for va, sz, kind, _n, _e in units if kind == "data")
    data_starts = [va for va, _ in data_units]
    carve = {}
    for va, info in built.items():
        for address, size, section in info.get("exceptions", {}).values():
            i = bisect.bisect_right(data_starts, address) - 1
            if i < 0 or address + size > data_starts[i] + data_units[i][1]:
                print(f"linkgen: exception metadata of 0x{va:x} at 0x{address:x} is not inside one "
                      "raw data unit", file=sys.stderr)
                return 2
            carve.setdefault(data_starts[i], []).append((address, size, info["obj"], section))
            exception_stats["placed" if section.startswith(".exceptix") else "tables"] += 1
            exception_stats["bytes"] += size
    pieces = {}      # data unit va -> [(start, size)] raw fragments between the carved slots
    for unit_va, slots in carve.items():
        slots.sort()
        unit_size = dict(data_units)[unit_va]
        cursor, fragments = unit_va, []
        for address, size, _obj, _section in slots:
            if address < cursor:
                print(f"linkgen: exception metadata slots overlap at 0x{address:x}", file=sys.stderr)
                return 2
            if address > cursor:
                fragments.append((cursor, address - cursor))
            cursor = address + size
        if cursor < unit_va + unit_size:
            fragments.append((cursor, unit_va + unit_size - cursor))
        pieces[unit_va] = fragments

    def build_rest(item):
        va, sz, kind, name, extra = item
        if va in pieces:
            fragments = {}
            for start, size in pieces[va]:
                info = build_raw(start, size, kind, name, os.path.join(a.out, "u_%08x.o" % start))
                if info.get("fatal"):
                    return va, info
                fragments[start] = info["obj"]
            return va, {"obj": None, "undef": [], "use_c": False, "tables": {}, "fragments": fragments}
        return build_one(item)

    with concurrent.futures.ThreadPoolExecutor(max_workers=max(1, a.jobs)) as ex:
        for va, info in ex.map(build_rest, [u for u in to_build if u[0] not in built]):
            built[va] = info
    # only a complete run over the repository's own tree may prune: the build-option tests
    # drive this tool on their own tree against the same cache directory
    whole_tree = (os.path.abspath(a.src) == os.path.join(ROOT, "src")
                  and os.path.abspath(a.symbols) == os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt"))
    store.save(prune=whole_tree and not a.unit_range)
    print("linkgen: " + store.summary("objects built"))
    if a.unit_range:
        print("linkgen: --unit-range: built %d of %d units, no link script written" % (len(to_build), len(units)))
        return 0
    # report the first failure in layout order (as the serial loop did)
    for va, sz, kind, name, extra in units:
        if built[va].get("fatal"):
            print("linkgen: " + built[va]["fatal"], file=sys.stderr)
            return 2
    table_names = {(name, address): section for va, _sz, _kind, name, _extra in units
                   for address, section in built[va].get("tables", {}).items()}

    undefined = set()
    script = ["/* GENERATED by tools/linkgen.py — do not edit. */",
              "ENTRY(entry)",
              "SECTIONS {",
              f"  .text 0x{a.section_start:08x} : SUBALIGN(1) {{",
              "    _section_start = .;"]

    made = 0
    c_units = c_bytes = body_units = body_bytes = asm_units = asm_bytes = jtbl_bytes = 0
    hand_units = hand_bytes = 0
    for va, sz, kind, name, extra in units:
        off = va - VADDR_BASE + FILE_BASE
        raw = img[off:off + sz]
        if len(raw) != sz:
            print(f"linkgen: 0x{va:x} size {sz} runs past the image", file=sys.stderr)
            return 2

        obj = os.path.join(a.out, "u_%08x.o" % va)
        # .c normally, .cpp for the templates that need C++ mode (MWCC picks the
        # language from the extension). Both are still one unit.
        csrc = None
        if kind == "code" and not a.no_c:
            csrc = src_index.get(name)
        use_c = csrc is not None
        # The "fully linked" accounting: a translation-unit project can only drop a
        # unit's asm stub when the *whole* translation unit is decompiled, so its
        # matched and fully-linked percentages differ. Here the units are functions
        # (`tools/layout.py` tiles per function), so C replaces retail one function at
        # a time and the two numbers coincide — measure it rather than assume it.
        if kind == "code":
            if use_c and name in unitprofiles.asm_body_names(csrc):
                body_units += 1
                body_bytes += sz
            elif use_c and asmsources.is_assembly(csrc):
                hand_units += 1
                hand_bytes += sz
            elif use_c:
                c_units += 1
                c_bytes += sz
            else:
                asm_units += 1
                asm_bytes += sz
        elif kind == "jtbl":
            jtbl_bytes += sz

        if kind == "jtbl" and extra in code_obj:
            # The compiler generated this table: place its `.rodata` here instead of
            # the retail bytes, and require the sizes to agree — a table that is the
            # wrong length would silently shift everything after it.
            owner_obj = code_obj[extra]
            inside = sorted((t, c) for t, c in recorded.get(function_address.get(extra), [])
                            if va <= t < va + sz)
            # several tables in one span: place each at its own address (the bytes between
            # them are the compiler's zero padding, which the linker's fill reproduces)
            parts = [(t, c * 4) for t, c in inside] if len(inside) > 1 else [(va, sz)]
            for table_va, table_size in parts:
                section = table_names.get((extra, table_va))
                if section is None:
                    print(f"linkgen: {extra} has no compiled table section for 0x{table_va:x}", file=sys.stderr)
                    return 2
                got = section_size(owner_obj, section)
                # a literal pool may end inside its last recorded word (a 2-byte string): the
                # linker's zero fill gives the rest, and linkcheck compares it with retail
                if not table_size - 4 < got <= table_size:
                    print(f"linkgen: {extra} jump table at 0x{table_va:x}: object .rodata is "
                          f"{got} bytes, layout says {table_size}", file=sys.stderr)
                    return 2
                script.append("    . = 0x%x;" % (table_va - a.section_start))
                script.append("    %s(%s)" % (owner_obj, section))
            continue

        # The object for this unit was built in parallel above; all that is left
        # here is to consume it, in layout order (the jump-table `.rodata` check
        # above needs its owner object to exist, which the build pass guarantees).
        info = built[va]
        if not use_c:
            made += 1
        undefined.update(info.get("undef", ()))
        if "fragments" in info:
            # A raw data unit carved around compiled exception metadata: its raw
            # fragments and the owning C objects' sections, each pinned at its
            # retail address; the linker's zero fill reproduces a table's padding.
            parts = [(start, f"{obj}(.text)") for start, obj in info["fragments"].items()]
            parts += [(address, f"{owner_obj}({section})") for address, _size, owner_obj, section in carve[va]]
            for address, what in sorted(parts):
                script.append("    . = 0x%x;" % (address - a.section_start))
                script.append("    " + what)
            continue

        # Pin the unit to its retail offset, then let the next unit's pin absorb any
        # slack the unit left. Inside an output section ld treats `.` as an offset from
        # the section start, so this is `va - VADDR_BASE` -- setting it to the absolute
        # VA silently prefixes 1 MB of zeros (measured; a bare `. = 0x100000;` produced
        # exactly that).
        #
        # For a matched build this emits nothing: every unit is already exactly `sz`
        # bytes, so each pin is a no-op and the byte-for-byte comparison still holds
        # (which is how the change was validated). It earns its keep when a unit is
        # *modified*: a mod's function may then compile smaller or larger than its
        # retail slot without shifting any other unit, so every absolute address baked
        # into the committed disassembly stays valid. A unit that grows past the next
        # pin is a loud ld error rather than a silent misplacement.
        script.append("    . = 0x%x;" % (va - a.section_start))
        script.append("    %s(.text)" % obj)

    script += ["    _section_end = .;",
               "  }",
               "  /DISCARD/ : { *(.comment) *(.reginfo) *(.mwcats) *(.debug) *(.lit4) *(.lit8) }"]
    # gp must be defined: __start does `move gp, a0`, i.e. the loader passes it in,
    # and the value is in the ELF's .reginfo. Without it every R_MIPS_GPREL16
    # reloc in the C objects fails with "small-data section too large".
    script.append("  _gp = 0x%08x;" % reginfo_gp(a.elf))
    # A symbol a C unit referenced but no unit defines: resolved by the one rule
    # tools/verify.py applies (`verify.sym_address`): the symbol map, the compiler
    # runtime table, data-names.tsv, or an honest address-bearing name. A name that fails the
    # naming rules (a `DAT_` name for a function's address, a `FUN_` name for
    # unlisted code) is still provided at the address it spells, so the relink
    # stays byte-identical, but it is counted and named here: `make check` fails
    # the unit that uses it. A name with no address stays undefined and ld reports it.
    by_name, _ = verify.load_symbols(a.symbols)
    dishonest = []
    for sym in sorted(undefined):
        try:
            address = verify.sym_address(sym, by_name, a.symbols)
        except verify.SymbolError as error:
            dishonest.append(str(error))
            address = verify.spelled_address(sym, a.symbols)
        if address is not None and sym not in by_name:
            script.append("  PROVIDE(%s = 0x%08x);" % (sym, address))
    script.append("}")
    for why in dishonest[:5]:
        print("linkgen: naming rule: " + why, file=sys.stderr)
    if dishonest:
        print(f"linkgen: {len(dishonest)} undefined symbols fail the naming rules (provided at the address "
              "they spell; make check fails their units)")
    open(a.ld_out, "w").write("\n".join(script) + "\n")
    print(f"linkgen: {len(units)} units, {made} asm units written, "
          f"{len(undefined)} undefined C symbols -> {a.ld_out}")
    total = c_bytes + body_bytes + hand_bytes + asm_bytes + jtbl_bytes
    print("linkgen: linked from C      %6d units  %9d bytes  %5.1f %% of the section"
          % (c_units, c_bytes, 100.0 * c_bytes / total))
    print("linkgen: asm bodies         %6d units  %9d bytes  %5.1f %%  (not counted)"
          % (body_units, body_bytes, 100.0 * body_bytes / total))
    if hand_units:
        print("linkgen: hand-written .S    %6d units  %9d bytes  %5.1f %%  (approved assembly sources)"
              % (hand_units, hand_bytes, 100.0 * hand_bytes / total))
    print("linkgen: linked from asm    %6d units  %9d bytes  %5.1f %%"
          % (asm_units, asm_bytes, 100.0 * asm_bytes / total))
    print("linkgen: compiler tables    %6s        %9d bytes  %5.1f %%"
          % ("", jtbl_bytes, 100.0 * jtbl_bytes / total))
    print("linkgen: exception metadata %6d records placed from C (%d tables, %d bytes); retail bytes kept for "
          "%d units that emit metadata retail lacks, %d whose retail record they do not produce, "
          "%d whose shape differs (see make check)"
          % (exception_stats["placed"], exception_stats["tables"], exception_stats["bytes"],
             exception_stats["extra"], exception_stats["missing"], exception_stats["differ"]))
    return 0


if __name__ == "__main__":
    sys.exit(main())
