#!/usr/bin/env python3
"""permuter_one.py — turn one function into a decomp-permuter project and run it.

The guard-family harness (`tools/permuter/FUN_00130060/`) proved decomp-permuter
works against MWCC-MIPS, but it was hand-built for one function. This generalises
it: given a VA, it assembles the project from the retail bytes and m2c's draft.

    <dir>/base.c    m2c's cleaned C (the permuter mutates this)
    <dir>/target.o  the retail function, assembled symbolically
    <dir>/compile.sh

Two things have to line up or every run scores 0 forever:

* **the target must carry relocations against the same symbol names the C does.**
  `m2c_one.asm_for` already emits `%hi(SYM)`/`%lo(SYM)` and named `jal` targets, so
  assembling its listing (after turning `glabel NAME` into `NAME:`) produces exactly
  the HI16/LO16/26 relocations MWCC emits for the same identifiers;
* **`as` pads every section to 16 bytes**, and the permuter disassembles the whole
  object, so `sh_size` is rewritten down to the real function size (the guard
  harness's trap #3).

The permuter's score is a diff, not proof: anything it reports is re-checked with
`tools/verify.py` before it is written to `src/`.

Usage:
  permuter_one.py 0x100240 --budget 120            # build + search 120 s
  permuter_one.py 0x100240 --build-only            # just the project dir
  permuter_one.py --from-worklist build/m2c_worklist3.tsv --max-diffs 3 --limit 20

Projects default to ../scratch/permuter/ outside the repository. --outdir
selects that project root; each function has its own named subdirectory.
"""
import argparse
import os
import re
import struct
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)

import automatch as am            # noqa: E402
import m2c_one                    # noqa: E402
import m2c_batch as MB            # noqa: E402
import units                      # noqa: E402
import verify as vfy              # noqa: E402

PERMUTER = os.environ.get("DW4_PERMUTER", os.path.join(ROOT, "local", "decomp-permuter"))
VENV_PY = os.environ.get("DW4_PERMUTER_PY",
                         os.path.join(ROOT, "local", "permuter-venv", "bin", "python"))
WIBO = os.environ.get("DW4_WIBO", os.path.join(ROOT, "local", "wibo"))
MWCC = os.environ.get("DW4_MWCC",
                      os.path.join(ROOT, "local", "mwcps2", "3.0-011126", "mwccps2.exe"))
ELF = os.path.join(ROOT, "orig", "SLUS-20836", "SLUS_208.36")
SYMBOLS = os.path.join(ROOT, "config", "SLUS-20836", "symbols.txt")

COMPILE_SH = """#!/bin/bash
# Driven by decomp-permuter as:  bash compile.sh <source.c> -o <out.o>
set -u
WIBO=${DW4_WIBO:-%(wibo)s}
MWCC=${DW4_MWCC:-%(mwcc)s}
export MWCIncludes=${MWCIncludes:-$(dirname "$1")}
tmp=$(mktemp --suffix=.c)
cp "$1" "$tmp"
"$WIBO" "$MWCC" -c -O3 "$tmp" -o "$3"
rc=$?
rm -f "$tmp"
exit $rc
"""

SETTINGS = 'compiler_type = "mwcc"\n'


def as_to_gnu_as(spimdisasm_text, name):
    """m2c's listing -> something GNU `as` accepts."""
    out = [".set arch=r5900", ".set noat", ".set noreorder", ".set nomacro", ".text",
           ".globl %s" % name, "%s:" % name]
    for line in spimdisasm_text.splitlines():
        s = line.strip()
        if not s or s.startswith(".set"):
            continue
        if s.startswith("glabel ") or s.startswith("endlabel "):
            continue
        out.append(line)
    return "\n".join(out) + "\n"


def build(va, outdir, table, names, bysym, quiet=True):
    size, name = bysym[va]
    os.makedirs(outdir, exist_ok=True)
    bounds = m2c_one.load_bounds(ELF)
    text = m2c_one.asm_for(va, name, size, table, names, bounds=bounds, ee_abi=False)
    asm = as_to_gnu_as(text, name)
    open(os.path.join(outdir, "target.s"), "w").write(asm)
    r = subprocess.run(["mipsel-linux-gnu-as", "-march=r5900", "-G0", "-o",
                        os.path.join(outdir, "target.o"), os.path.join(outdir, "target.s")],
                       capture_output=True, text=True)
    if r.returncode:
        return None, "assemble failed: " + (r.stderr or r.stdout).strip()[:200]
    _shrink_text(os.path.join(outdir, "target.o"), size)
    c = MB.run_m2c(m2c_one.asm_for(va, name, size, table, names, bounds=bounds), name,
                   os.path.join(outdir, "m2c.s"))
    if not c.strip() or "Decompilation failure" in c:
        return None, "m2c could not decompile it"
    open(os.path.join(outdir, "base.c"), "w").write(
        "/* base.c — m2c draft for %s (0x%08x), mutated by decomp-permuter. */\n" % (name, va)
        + MB.clean(c, "symbol", bounds))
    open(os.path.join(outdir, "compile.sh"), "w").write(COMPILE_SH % {"wibo": WIBO, "mwcc": MWCC})
    os.chmod(os.path.join(outdir, "compile.sh"), 0o755)
    open(os.path.join(outdir, "permuter_settings.toml"), "w").write(SETTINGS)
    return name, None


def _shrink_text(path, want):
    d = bytearray(open(path, "rb").read())
    shoff, = struct.unpack_from("<I", d, 0x20)
    entsize, shnum, shstrndx = struct.unpack_from("<HHH", d, 0x2E)
    strtab = shoff + shstrndx * entsize
    strbase, = struct.unpack_from("<I", d, strtab + 16)
    for i in range(shnum):
        o = shoff + i * entsize
        nameoff, = struct.unpack_from("<I", d, o)
        end = d.find(b"\0", strbase + nameoff)
        if d[strbase + nameoff:end].decode() == ".text":
            struct.pack_into("<I", d, o + 20, want)
            break
    open(path, "wb").write(d)


def run(dirpath, budget, stop_on_zero=True, jobs=1):
    """-> (score, source). score 0 means the permuter thinks it matched."""
    cmd = [VENV_PY, os.path.join(PERMUTER, "permuter.py"), dirpath,
           "-j", str(jobs)] + (["--stop-on-zero"] if stop_on_zero else [])
    with open(os.path.join(dirpath, "permuter.log"), "w") as log:
        p = subprocess.Popen(cmd, stdout=log, stderr=subprocess.STDOUT,
                             stdin=subprocess.DEVNULL)
        try:
            p.wait(timeout=budget)
        except subprocess.TimeoutExpired:
            p.terminate()
            try:
                p.wait(timeout=10)
            except subprocess.TimeoutExpired:
                p.kill()
    best, src = None, None
    for d in sorted(os.listdir(dirpath)):
        m = re.match(r"output-(\d+)-\d+$", d)
        if not m:
            continue
        s = int(m.group(1))
        if best is None or s < best:
            sp = os.path.join(dirpath, d, "source.c")
            if os.path.exists(sp):
                best, src = s, open(sp).read()
    return best, src


def pilot(targets, table, names, bysym, budget=100, parallel=4, outdir=None):
    """Run a stratified sample and report the closure rate by size band.

    Build serially (m2c is driven in-process and mutates global state, so it cannot
    run in threads), run the permuter subprocesses in parallel, then **verify
    serially** — `verify.py` writes fixed temp paths, so calling it concurrently
    produces false negatives (this bug made a real match look like a failure the
    first time this pilot was run).
    """
    import collections
    from concurrent.futures import ThreadPoolExecutor
    base = project_root(outdir)
    os.makedirs(base, exist_ok=True)
    built = []
    for va, sz, band in targets:
        d = os.path.join(base, names[va])
        _n, err = build(va, d, table, names, bysym)
        built.append((va, sz, band, d, err))

    def work(x):
        va, sz, band, d, err = x
        if err:
            return (va, names[va], sz, band, err[:40], None)
        score, src = run(d, budget, jobs=3)
        return (va, names[va], sz, band, score, src)

    with ThreadPoolExecutor(max_workers=parallel) as ex:
        out = list(ex.map(work, built))

    agg, ver, byt = collections.Counter(), collections.Counter(), collections.Counter()
    for va, n, sz, band, score, src in out:
        agg[band] += 1
        byt[band] += sz
        ok = False
        if src:
            tmp = "/tmp/permuter_pilot.c"
            open(tmp, "w").write(src)
            ok, _rep = vfy.verify_one(va, tmp, symbols=SYMBOLS, elf=ELF)
        if ok:
            ver[band] += 1
        print("  %-44s %5dB %-10s score=%-8s verified=%s" % (n, sz, band, score, ok), flush=True)
    print("band            closed / n   bytes in band")
    for b in sorted(agg):
        print("  %-12s  %d / %d        %d B" % (b, ver[b], agg[b], byt[b]))
    print("closures: %d/%d functions; %d of %d bytes"
          % (sum(ver.values()), len(out), sum(byt[b] for b in agg if ver[b]), sum(byt.values())))
    return out


target_by_name = {}


def project_root(outdir=None):
    """Keep target objects/private search artifacts outside Git by default."""
    return os.path.abspath(outdir or os.path.join(ROOT, "..", "scratch", "permuter"))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("address", nargs="?")
    ap.add_argument("--outdir", default=None, help="project root (default: ../scratch/permuter)")
    ap.add_argument("--budget", type=int, default=120, help="seconds per function")
    ap.add_argument("--jobs", type=int, default=4, help="permuter worker threads")
    ap.add_argument("--build-only", action="store_true")
    ap.add_argument("--from-worklist", default=None)
    ap.add_argument("--max-diffs", type=int, default=3)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--write", action="store_true", help="write verified matches to src/")
    ap.add_argument("--pilot", type=int, default=0,
                    help="stratified sample of N near-misses per size band, run in parallel")
    a = ap.parse_args(argv)

    with open(ELF, "rb") as image_file:
        img = image_file.read()
    syms = am.load_symbols(SYMBOLS)
    names = {v: n for v, s, n in syms}
    bysym = {v: (s, n) for v, s, n in syms}
    lo = min(v for v, _, _ in syms)
    hi = max(v + s for v, s, _ in syms)
    table = am.disassemble(img, lo, hi)

    targets = []
    if a.address:
        targets = [int(a.address, 0)]
    elif a.from_worklist:
        rows = [l.rstrip("\n").split("\t") for l in open(a.from_worklist)][1:]
        for r in rows:
            if r[3] == "mismatch" and int(r[4]) <= a.max_diffs:
                targets.append(int(r[1], 0))
        targets.sort(key=lambda v: bysym[v][0])          # cheapest first
        if a.limit:
            targets = targets[:a.limit]
    if not targets:
        print("no targets", file=sys.stderr)
        return 2

    base = project_root(a.outdir)
    os.makedirs(base, exist_ok=True)
    if a.pilot:
        near = []
        rows = [l.rstrip("\n").split("\t") for l in open(a.from_worklist)][1:]
        for r in rows:
            if r[3] == "mismatch" and int(r[4]) <= a.max_diffs:
                near.append((int(r[1], 0), int(r[2]), None))
        picks = []
        for band, lo, hi in (("tiny<=32", 0, 32), ("mid 33-256", 33, 256),
                             ("large>256", 257, 10 ** 9)):
            sel = sorted([x for x in near if lo <= x[1] <= hi], key=lambda x: x[1])
            step = max(1, len(sel) // max(1, a.pilot))
            picks += [(v, s, band) for v, s, _ in sel[::step][:a.pilot]]
        print("pilot sample: %d" % len(picks))
        pilot(picks, table, names, bysym, budget=a.budget, parallel=a.jobs, outdir=a.outdir)
        return 0
    done, matched, errors = 0, [], []
    t0 = time.time()
    for i, va in enumerate(targets):
        name, err = build(va, os.path.join(base, names[va]), table, names, bysym)
        if err:
            errors.append((names[va], err))
            continue
        if a.build_only:
            done += 1
            continue
        score, src = run(os.path.join(base, name), a.budget, jobs=a.jobs)
        done += 1
        if score is None or src is None:
            continue
        # The permuter's score is a diff, not proof: re-verify with the real oracle.
        # Verify the way `make check` does — a multi-definition result is split to
        # its one function first, so a candidate that only matches by smuggling in a
        # helper definition (which the split drops) is correctly rejected.
        tmp = "/tmp/permuter_cand_%d.c" % os.getpid()
        open(tmp, "w").write(src)
        cand, extra = tmp, None
        if len(units.definitions(src)) > 1:
            cand, extra = units.standalone(tmp, name)
        try:
            ok, rep = vfy.verify_one(va, cand, symbols=SYMBOLS, elf=ELF)
        finally:
            if extra and os.path.exists(extra):
                os.remove(extra)
        if ok:
            matched.append(name)
            if a.write:
                dest = os.path.join(ROOT, "src", "unmatched", name + ".c")
                if not os.path.exists(dest):
                    open(dest, "w").write(
                        "/* 0x%08x — %s. m2c draft + decomp-permuter search, verified\n"
                        " * byte-identical to retail by tools/verify.py. */\n" % (va, name) + src)
            print("  MATCH  %s (permuter score %d)" % (name, score), flush=True)
        elif score == 0:
            print("  score 0 but verify says otherwise: %s" % name, flush=True)
        if (i + 1) % 10 == 0:
            print("  %d/%d searched, %d verified, %.0fs"
                  % (i + 1, len(targets), len(matched), time.time() - t0), flush=True)
    print("permuter_one: %d searched, %d verified matches, %d build errors  [%.0fs]"
          % (done, len(matched), len(errors), time.time() - t0))
    for n, e in errors[:5]:
        print("   !! %s: %s" % (n, e))
    return 0


if __name__ == "__main__":
    sys.exit(main())
