"""gdb_cse_compare.py: the IR node pairs IRO_CommonSubs rejects as different, and why (gdb script).

Common-subexpression elimination decides that two expressions are the same with a node comparison that needs equal
node kinds, equal `nodeflags` (bit 0x200 ignored) and equal types, then recurses into the operands. This stops in
that comparison during one call of IRO_CommonSubs and writes to IRDUMP_OUT each distinct pair of nodes that fails on
the flags or on the type, with both values:

    node 384 vs 321 (nodetype 15): nodeflags 0000 vs 0001 -> NOT EQUAL

    IRDUMP_OUT=/tmp/irdump/cse.txt MWCIncludes=src gdb -q -batch -x tools/mwcc_irdump/gdb_cse_compare.py \
        --args local/wibo local/mwcps2/3.0b52-030722/mwccps2.exe -c -O4,p -sdatathreshold 2 \
        -inline level=8,bottomup -Iinclude /tmp/irdump/t.cpp -o /tmp/irdump/t.o

IRDUMP_CALL picks the call (default 0, the first: IRO_CommonSubs runs once per optimised function, in the order the
dump log lists them). Node numbers are the dump log's. Run from the repository root.
"""
import os
import sys

import gdb

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import b52  # noqa: E402
import gdb_common as g  # noqa: E402


def main():
    inferior = g.start(b52.COMMON_SUBS)
    rd = g.reader(inferior)
    out = open(os.environ["IRDUMP_OUT"], "w")
    gdb.execute("break *%#x" % b52.COMMON_SUBS)
    for _ in range(int(os.environ.get("IRDUMP_CALL", "0")) + 1):
        gdb.execute("continue")
    gdb.execute("delete")
    ret = rd(g.esp(), 4)
    for address in (b52.NODE_EQUAL_FLAGS, b52.NODE_EQUAL_TYPES, ret):
        gdb.execute("break *%#x" % address)
    seen = set()
    while True:
        gdb.execute("continue", to_string=True)
        pc = g.register("pc")
        if pc == ret:
            break
        a, b = g.register("edi"), g.register("esi")
        ia, ib = rd(a + b52.NODE_INDEX, 4), rd(b + b52.NODE_INDEX, 4)
        ntype = rd(a + b52.NODE_TYPE, 1)
        if pc == b52.NODE_EQUAL_FLAGS:
            fa, fb = rd(a + b52.NODE_FLAGS, 2), rd(b + b52.NODE_FLAGS, 2)
            if (fa ^ fb) & ~b52.FLAG_IGNORED and (ia, ib, "f") not in seen:
                seen.add((ia, ib, "f"))
                out.write("node %d vs %d (nodetype %d): nodeflags %04x vs %04x -> NOT EQUAL\n" % (ia, ib, ntype, fa, fb))
        elif g.register("eax") & 0xFF == 0 and (ia, ib, "t") not in seen:
            seen.add((ia, ib, "t"))
            ta, tb = rd(a + b52.NODE_RTYPE, 4), rd(b + b52.NODE_RTYPE, 4)
            out.write("node %d vs %d (nodetype %d): rtype %x vs %x [type kind %d vs %d, size %d vs %d] -> TYPES NOT EQUAL\n"
                      % (ia, ib, ntype, ta, tb, rd(ta, 1), rd(tb, 1), rd(ta + 2, 4), rd(tb + 2, 4)))
    g.finish(out)


main()
