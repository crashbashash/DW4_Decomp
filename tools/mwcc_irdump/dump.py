#!/usr/bin/env python3
"""dump.py DUMP_EXE SOURCE OUTDIR [--function VA_OR_NAME | --flags "..."]: compile SOURCE with the IR dump copy.

The dump copy (make_dump_compiler.py) writes `<source>.log` beside the source it compiles, so this copies SOURCE
into OUTDIR (outside the repository) and compiles the copy there, from the repository root as the build does
(`-Iinclude` and `#include "src/..."` resolve as in tools/check.py; SOURCE's own folder is added as an include
path for its sibling files). It prints the path of the log; the object goes beside it.

Flags: --function takes the unit profile the build uses for that function (config/SLUS-20836/units.tsv; the unit
must be a b52 one), --flags a flag string; the default is the game's b52 profile
"-O4,p -sdatathreshold 2 -inline level=8,bottomup -Iinclude".

    python3 tools/mwcc_irdump/dump.py /tmp/irdump/mwdump.exe /tmp/irdump/t.cpp /tmp/irdump/out
    python3 tools/mwcc_irdump/ph.py /tmp/irdump/out/t.log "after IRO_CommonSubs"

The whole file is compiled, so the log holds every function in it: a few hundred kilobytes per function, a few hundred
megabytes for a large whole-file unit. A small test file with one function keeps it short.
"""
import argparse
import os
import shutil
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.dirname(HERE))
import b52  # noqa: E402

WIBO = os.environ.get("DW4_WIBO", os.path.join(b52.ROOT, "local", "wibo"))


def unit_flags(spec):
    """The flag string of the unit profile `spec` (a symbol or a VA) builds under."""
    import project
    import unitprofiles
    import verify
    cfg = project.read_config(project.DEFAULT_VERSION)
    symbols = os.path.join(b52.ROOT, cfg["symbols"])
    by_name = verify.load_symbols(symbols)[0]
    va = by_name[spec][0] if spec in by_name else int(spec, 16)
    res = unitprofiles.resolve(va, project.DEFAULT_FLAGS, project.DEFAULT_COMPILER,
                               units=os.path.join(b52.ROOT, cfg["splits"]) if "splits" in cfg else None,
                               unit_flags=os.path.join(b52.ROOT, cfg["unit_flags"]),
                               unit_compilers=os.path.join(b52.ROOT, cfg["unit_compilers"]), symbols=symbols)
    profile = res.override or res.profile
    compiler = profile.compiler if os.path.isabs(profile.compiler) else os.path.join(b52.ROOT, profile.compiler)
    if b52.sha256(compiler) != b52.SHA256:
        raise SystemExit("%s builds under %s, not 3.0b52-030722; the dump copy is b52 only" % (spec, profile.compiler))
    return unitprofiles.command_flags(profile)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("compiler", help="the dump copy written by make_dump_compiler.py")
    ap.add_argument("source")
    ap.add_argument("outdir", help="where the copy, the log and the object go (outside the repository)")
    group = ap.add_mutually_exclusive_group()
    group.add_argument("--function", help="use this function's unit profile")
    group.add_argument("--flags", help="compile with these flags")
    a = ap.parse_args()
    if b52.inside_repository(a.outdir):
        raise SystemExit("%s: the log is written beside the compiled file; use a folder outside the repository" % a.outdir)
    if b52.known_builds().get(b52.sha256(a.compiler)) != "dump":
        raise SystemExit("%s: not a dump copy made by make_dump_compiler.py" % a.compiler)
    flags = a.flags if a.flags else unit_flags(a.function) if a.function else b52.GAME_FLAGS
    os.makedirs(a.outdir, exist_ok=True)
    outdir = os.path.abspath(a.outdir)
    source = os.path.abspath(a.source)
    copy = os.path.join(outdir, os.path.basename(source))
    if copy != source:
        shutil.copyfile(source, copy)
    stem = os.path.splitext(copy)[0]
    log = stem + ".log"
    if os.path.exists(log):
        os.remove(log)
    argv = [WIBO, os.path.abspath(a.compiler), "-c", *flags.split(), "-I" + os.path.dirname(source), copy,
            "-o", stem + ".o"]
    r = subprocess.run(argv, cwd=b52.ROOT, env=dict(os.environ, MWCIncludes=os.path.join(b52.ROOT, "src")))
    if r.returncode != 0 or not os.path.exists(log):
        raise SystemExit("compile failed or wrote no log (exit %d)" % r.returncode)
    print(log)


if __name__ == "__main__":
    main()
