#!/usr/bin/env python3
"""make_dump_compiler.py RETAIL_MWCCPS2 OUT_EXE: a copy of MWCC 3.0b52-030722 that dumps its optimizer's IR.

The b52 compiler still holds its IR dump code (IRO_DumpAfterPhase); the optimizer's setup stores 0 in the two
switches that turn it on. The copy stores 1 instead (one immediate byte each, see b52.py), so every compile writes
the IR of every function after every optimizer phase to `<source>.log`, beside the source file. The object it
writes is byte-identical to the retail compiler's.

OUT_EXE must lie outside the repository and outside local/: the copy is a modified compiler and never part of the
toolchain the build uses.

    python3 tools/mwcc_irdump/make_dump_compiler.py local/mwcps2/3.0b52-030722/mwccps2.exe /tmp/irdump/mwdump.exe

Then compile with tools/mwcc_irdump/dump.py and read the log with tools/mwcc_irdump/ph.py.
"""
import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import b52  # noqa: E402


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("compiler", help="the retail local/mwcps2/3.0b52-030722/mwccps2.exe")
    ap.add_argument("out", help="where to write the dump copy (outside the repository)")
    a = ap.parse_args()
    if b52.inside_repository(a.out):
        raise SystemExit("%s: write the dump copy outside the repository and local/" % a.out)
    if b52.sha256(a.compiler) != b52.SHA256:
        raise SystemExit("%s: not the 3.0b52-030722 build (SHA-256 %s)" % (a.compiler, b52.SHA256))
    data = b52.dump_copy(open(a.compiler, "rb").read())
    os.makedirs(os.path.dirname(os.path.abspath(a.out)), exist_ok=True)
    with open(a.out, "wb") as fh:
        fh.write(data)
    print(a.out)


if __name__ == "__main__":
    main()
