"""gdb_nodeflags.py: the qualifier flags of every IR node after chosen optimizer phases (gdb script).

The dump log does not print `nodeflags`; this reads them from the running compiler (retail or dump copy) at each
call of IRO_DumpAfterPhase, which runs after every phase whether or not dumping is on. For the first time each phase
named in IRDUMP_PHASES runs, it writes every node whose flags (ignoring 0x200) are not 0, with its IR index, kind
and node type, to IRDUMP_OUT. Bit 0x0001 marks a pointer-valued node whose target is `const`.

    IRDUMP_OUT=/tmp/irdump/flags.txt MWCIncludes=src gdb -q -batch -x tools/mwcc_irdump/gdb_nodeflags.py \
        --args local/wibo local/mwcps2/3.0b52-030722/mwccps2.exe -c -O4,p -sdatathreshold 2 \
        -inline level=8,bottomup -Iinclude /tmp/irdump/t.cpp -o /tmp/irdump/t.o

IRDUMP_PHASES is a `|`-separated list of phase-name fragments (default
"IRO_RotateLoop|IRO_MoveInvariantsInAddressExpr|Second pass"). Run from the repository root. Index numbers are the
ones the dump log prints, so a node can be found in both.
"""
import os
import sys

import gdb

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import b52  # noqa: E402
import gdb_common as g  # noqa: E402


def cstr(inferior, address):
    data = b""
    while True:
        c = inferior.read_memory(address, 1).tobytes()
        if c == b"\0":
            return data.decode(errors="replace")
        data += c
        address += 1


def main():
    inferior = g.start(b52.DUMP_AFTER_PHASE)
    rd = g.reader(inferior)
    want = os.environ.get("IRDUMP_PHASES", "IRO_RotateLoop|IRO_MoveInvariantsInAddressExpr|Second pass").split("|")
    out = open(os.environ["IRDUMP_OUT"], "w")
    gdb.execute("break *%#x" % b52.DUMP_AFTER_PHASE)
    seen = set()
    while True:
        try:
            gdb.execute("continue", to_string=True)
            pc = g.register("pc")
        except gdb.error:
            break
        if pc != b52.DUMP_AFTER_PHASE:
            break
        name = cstr(inferior, rd(g.esp() + 4, 4))
        if name in seen or not any(w in name for w in want):
            continue
        seen.add(name)
        out.write("== after %s\n" % name)
        node = rd(b52.NODE_LIST, 4)
        while node:
            kind, ntype = rd(node + b52.NODE_KIND, 1), rd(node + b52.NODE_TYPE, 1)
            flags, index = rd(node + b52.NODE_FLAGS, 2), rd(node + b52.NODE_INDEX, 4)
            if kind != 0 and flags & ~b52.FLAG_IGNORED:
                out.write("  node %d kind %d nodetype %d (%s) nodeflags %04x\n"
                          % (index, kind, ntype, b52.NODE_TYPES.get(ntype, "?"), flags))
            node = rd(node + b52.NODE_NEXT, 4)
    g.finish(out)


main()
