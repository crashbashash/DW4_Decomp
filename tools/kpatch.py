#!/usr/bin/env python3
"""kpatch.py — build libkernl's kernel patches from source.

Four libkernl files carry code the kernel runs: each copies a byte array into kernel memory and installs
system calls that point into it (docs/engine/sony-libkernl-sys.md#the-kernel-patches). The array is a
program of its own, linked to run where it is copied, so its bytes are rebuilt from the patch's own
sources under src/sony/libkernl/kpatch/ rather than committed. config/SLUS-20836/kernel-patches.tsv lists
each patch:

    name <TAB> sources <TAB> run address <TAB> owner unit <TAB> compiler <TAB> array <TAB> size

A build compiles every source with the owner unit's flags (config/SLUS-20836/units.tsv, through tools/cc.py
and tools/eegcc_compile.py) and the owner's compiler, or the units.tsv compiler the row names: Sony built each
patch apart from the library that embeds it, so its assembler need not be the owner's. It links the objects
at the run address with config/kernel-patch.ld, keeps .text and .data as raw bytes, checks the size against
the row and writes build/<GAMEID>/kpatch/<name>.inc, a C initializer list. The owner file defines its array
from it:

    static unsigned char tlbsrc[TLB_PATCH_SIZE] = {
    #include "tlbsrc.inc"
    };

so `verify` compares the patch bytes with retail as part of the owner's .data. tools/cc.py builds the
patches a source includes before it compiles that source and adds the include directory, so every compile
site (check, verify, linkgen, objdiff) gets them. A build is skipped while its inputs are unchanged.

The patch sources are not image units: their functions run at the patch's address and nothing in the image
calls them, so tools/units.py leaves this directory out of every definition census, and the progress report
counts the patches on a line of their own.

  python3 tools/kpatch.py            # build every patch (cached), one line each
  python3 tools/kpatch.py tlbsrc     # build one
  python3 tools/kpatch.py --no-cache # rebuild even when the inputs are unchanged
"""
import argparse
import fcntl
import hashlib
import os
import re
import subprocess
import sys
from collections import namedtuple
from functools import lru_cache

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
GAMEID = "SLUS-20836"
TABLE = os.path.join(ROOT, "config", GAMEID, "kernel-patches.tsv")
LINK_SCRIPT = os.path.join(ROOT, "config", "kernel-patch.ld")
PATCH_DIR = os.path.join(ROOT, "src", "sony", "libkernl", "kpatch")
OUT_DIR = os.path.join(ROOT, "build", GAMEID, "kpatch")
LD = "mipsel-linux-gnu-ld"
OBJCOPY = "mipsel-linux-gnu-objcopy"

Patch = namedtuple("Patch", "name sources run owner compiler array size")

_INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]+"(\w+)\.inc"', re.M)


def parse(text, path="kernel-patches.tsv"):
    """The table's rows -> [Patch]. Raises ValueError on a malformed row."""
    out, seen = [], set()
    for number, line in enumerate(text.splitlines(), 1):
        if not line.strip() or line.startswith("#"):
            continue
        fields = line.split("\t")
        where = "%s:%d" % (os.path.basename(path), number)
        if len(fields) != 7:
            raise ValueError("%s: expected name, sources, run address, owner unit, compiler, array, size" % where)
        name, sources, run, owner, compiler, array, size = fields
        if not re.fullmatch(r"\w+", name) or name in seen:
            raise ValueError("%s: bad or repeated patch name %r" % (where, name))
        seen.add(name)
        # `-`: a patch whose bytes are not built from source yet (its owner still names the retail array)
        paths = () if sources.strip() == "-" else tuple(s.strip() for s in sources.split(","))
        for source in paths:
            if os.path.dirname(os.path.join(ROOT, source)) != PATCH_DIR or not source.endswith((".c", ".S")):
                raise ValueError("%s: %s is not a .c or .S file in %s" % (where, source, os.path.relpath(PATCH_DIR, ROOT)))
        out.append(Patch(name, paths, int(run, 16), owner, None if compiler == "-" else compiler, array,
                         int(size, 0)))
    return out


@lru_cache(maxsize=4)
def load(path=TABLE):
    """[Patch] from the table; a missing table is no patches."""
    if not os.path.exists(path):
        return []
    with open(path) as fh:
        return parse(fh.read(), path)


def is_patch_source(path):
    """Whether `path` is under the patch source directory (not an image unit)."""
    real = os.path.realpath(path)
    return real == os.path.realpath(PATCH_DIR) or real.startswith(os.path.realpath(PATCH_DIR) + os.sep)


def functions(patches=None):
    """{key: (path, definition)} for every function the patch sources define. The key is the definition's
    name, or `<name>_<patch>` when several patches define one name, the way the symbol map tells apart a
    `static` several files define; an approval row names a patch function by its key."""
    import asmsources
    import srctext
    import units
    found = []
    for patch in load() if patches is None else patches:
        for source in patch.sources:
            path = os.path.join(ROOT, source)
            if not os.path.exists(path):
                continue
            if source.endswith(".S"):
                # an assembly source's approval is checked apart (status), so an unapproved one still lists
                with open(path) as fh:
                    names = asmsources.definitions(fh.read())
            else:
                names = [name for name, _s, _e in units.definitions(srctext.read(path))]
            found += [(name, patch.name, path) for name in names]
    counts = {}
    for name, _patch, _path in found:
        counts[name] = counts.get(name, 0) + 1
    return {(name if counts[name] == 1 else "%s_%s" % (name, patch)): (path, name) for name, patch, path in found}


def _profile(patch):
    """(compiler executable, flag string): the owner unit's flags with the row's compiler, or the owner's."""
    import unitprofiles
    table = unitprofiles.load()
    unit = next((u for u in table.units if u.name == patch.owner), None)
    if unit is None:
        raise ValueError("kernel patch %s: owner unit %s is not in units.tsv" % (patch.name, patch.owner))
    ident = patch.compiler or unit.compiler
    if ident not in table.compilers:
        raise ValueError("kernel patch %s: compiler %s is not declared in units.tsv" % (patch.name, ident))
    executable, digest = table.compilers[ident]
    compiler = unitprofiles.checked_executable(executable, digest)
    return compiler, unitprofiles.command_flags(unitprofiles.Profile(compiler, unit.flags, unit.exceptions))


@lru_cache(maxsize=None)
def _tool_version(tool):
    return subprocess.run([tool, "--version"], capture_output=True, text=True, check=True).stdout.split("\n")[0]


def _key(patch, compiler, flags):
    """Digest of everything the patch's bytes depend on."""
    import buildcache
    h = hashlib.sha256()
    parts = [repr(patch), flags, buildcache.tree_sha(os.path.dirname(os.path.dirname(compiler))),
             buildcache.fresh_sha(LINK_SCRIPT), buildcache.fresh_sha(os.path.abspath(__file__)),
             buildcache.fresh_sha(os.path.join(HERE, "eegcc_compile.py")), _tool_version(LD), _tool_version(OBJCOPY)]
    parts += [buildcache.fresh_sha(os.path.join(ROOT, s)) for s in patch.sources]
    # a source's own includes (project headers) shape its code too
    parts += [buildcache.tree_sha(os.path.join(ROOT, "include"))]
    for part in parts:
        data = part.encode()
        h.update(len(data).to_bytes(8, "little") + data)
    return h.hexdigest()


def inc_path(name):
    return os.path.join(OUT_DIR, name + ".inc")


def build(patch, cache=True):
    """Build one patch; returns (path of its .inc, whether it was rebuilt). Raises ValueError when a step fails
    or the bytes are not the row's size."""
    import cc
    if not patch.sources:
        raise ValueError("kernel patch %s has no sources in %s" % (patch.name, os.path.relpath(TABLE, ROOT)))
    compiler, flags = _profile(patch)
    os.makedirs(OUT_DIR, exist_ok=True)
    key = _key(patch, compiler, flags)
    out, stamp = inc_path(patch.name), os.path.join(OUT_DIR, patch.name + ".key")
    with open(os.path.join(OUT_DIR, ".lock"), "w") as lock:
        # parallel compiles of the owner (make check, make link) build it once
        fcntl.flock(lock, fcntl.LOCK_EX)
        if cache and os.path.exists(out) and os.path.exists(stamp) and open(stamp).read() == key:
            return out, False
        work = os.path.join(cc.scratch_dir(), "kpatch_%s_%d" % (patch.name, os.getpid()))
        os.makedirs(work, exist_ok=True)
        objects = []
        for source in patch.sources:
            obj = os.path.join(work, os.path.splitext(os.path.basename(source))[0] + ".o")
            r = subprocess.run(cc.compile_argv(None, compiler, flags, source, obj),
                               cwd=ROOT, capture_output=True, text=True)
            if r.returncode:
                raise ValueError("kernel patch %s: %s does not compile:\n%s" % (patch.name, source, r.stdout + r.stderr))
            objects.append(obj)
        elf, raw = os.path.join(work, patch.name + ".elf"), os.path.join(work, patch.name + ".raw")
        for argv in ([LD, "-T", LINK_SCRIPT, "-Ttext=0x%x" % patch.run, "-o", elf, *objects],
                     [OBJCOPY, "-O", "binary", "-j", ".text", "-j", ".data", elf, raw]):
            r = subprocess.run(argv, cwd=ROOT, capture_output=True, text=True)
            if r.returncode:
                raise ValueError("kernel patch %s: %s failed:\n%s" % (patch.name, argv[0], r.stdout + r.stderr))
        with open(raw, "rb") as fh:
            data = fh.read()
        if len(data) != patch.size:
            raise ValueError("kernel patch %s: %d bytes, the table says %d" % (patch.name, len(data), patch.size))
        text = "".join(" ".join("0x%02x," % b for b in data[at:at + 16]) + "\n" for at in range(0, len(data), 16))
        for path, content in ((out, text), (stamp, key)):
            with open(path + ".tmp", "w") as fh:
                fh.write(content)
            os.replace(path + ".tmp", path)
        return out, True


def include_dir_for(source):
    """The include directory a compile of `source` needs once the patches it includes are built, or None
    when it includes none. Raises ValueError when a patch fails to build."""
    try:
        with open(source, errors="replace") as fh:
            text = fh.read()
    except OSError:
        return None
    if ".inc" not in text:
        return None
    wanted = set(_INCLUDE.findall(text))
    patches = [p for p in load() if p.name in wanted]
    if not patches:
        return None
    for patch in patches:
        build(patch)
    return OUT_DIR


def _data_addresses(names):
    """{name: retail address} of the arrays among config/SLUS-20836/data-names.tsv's rows."""
    out = {}
    with open(os.path.join(ROOT, "config", GAMEID, "data-names.tsv")) as fh:
        for line in fh:
            fields = line.rstrip("\n").split("\t")
            if len(fields) >= 2 and fields[1] in names and not line.startswith("#"):
                out[fields[1]] = int(fields[0], 16)
    return out


def status(check_data=os.path.join(ROOT, "data", "check-data.tsv")):
    """[(patch, matched, waiting)] for every row. `matched`: the patch builds from its sources and its
    array lies inside data `make check` compared equal to retail (data/check-data.tsv, as the data
    figures read it). `waiting`: the reasons a matched patch still awaits the owner's approval, a
    function's `asm` or `volatile` without its row (tools/sourceapprovals.py) or an assembly source
    without its row in config/assembly-sources.tsv."""
    import asmsources
    import sourceapprovals
    patches = load()
    addresses = _data_addresses({p.array for p in patches})
    spans = []
    if os.path.exists(check_data):
        for line in open(check_data):
            fields = line.rstrip("\n").split("\t")
            if line.startswith("#") or len(fields) < 5 or fields[4] in ("mismatch", "compile", "asm-body"):
                continue
            spans.append((int(fields[0], 16), int(fields[0], 16) + int(fields[1])))
    rows, assembly = sourceapprovals.load(), asmsources.load()
    problems = {}
    for key, path, why in sourceapprovals.patch_problems(rows):
        problems.setdefault(path, []).append("%s: %s" % (key, why))
    out = []
    for patch in patches:
        at = addresses.get(patch.array)
        matched = bool(patch.sources) and at is not None and any(
            lo <= at and at + patch.size <= hi for lo, hi in spans)
        waiting = []
        for source in patch.sources:
            if source in problems:
                waiting += problems[source]
            elif source.endswith(".S"):
                text = open(os.path.join(ROOT, source)).read()
                missing = [n for n in asmsources.definitions(text)
                           if os.path.normpath(assembly.get(n, ("",))[0]) != os.path.normpath(source)]
                if missing:
                    waiting.append("%s: assembly %s without a row" % (source, ", ".join(missing)))
        out.append((patch, matched, waiting))
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("names", nargs="*", help="patches to build (default: all)")
    ap.add_argument("--no-cache", action="store_true", help="rebuild even when the inputs are unchanged")
    a = ap.parse_args(argv)
    patches = load()
    unknown = set(a.names) - {p.name for p in patches}
    if unknown:
        ap.error("no such patch: " + ", ".join(sorted(unknown)))
    failed = 0
    for patch in patches:
        if a.names and patch.name not in a.names:
            continue
        if not patch.sources and not a.names:
            print("kpatch: %s not built from source (the owner names the retail array)" % patch.name)
            continue
        try:
            path, rebuilt = build(patch, cache=not a.no_cache)
        except ValueError as error:
            print("kpatch: %s" % error, file=sys.stderr)
            failed += 1
            continue
        print("kpatch: %s %d bytes at 0x%08x -> %s (%s)" % (patch.name, patch.size, patch.run,
                                                           os.path.relpath(path, ROOT), "built" if rebuilt else "cached"))
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
