"""gdb_schedtrace.py: what the b52 instruction scheduler decides, block by block (gdb script).

The compiler schedules every basic block twice, before and after register allocation. For each block this writes
the dependence nodes the scheduler built (in the order of its list) and then every pick it makes, to IRDUMP_OUT:

    BLOCK <n> index=<block index> count=<instructions>
      node <id> op=<opcode> <operands>  order=<x12> ready=<x14> latest=<x16> path=<x18> preds=<x1a> -> <id>+<latency> ...
      t=<cycle> slot=<slot in the cycle> pick <id> op=<opcode> <operands>

An operand is `D:` (written) and/or `U:` (read), then `c<class>r<number>`; numbers under 32 in class 0 are the MIPS
registers, larger ones the allocator's nodes. `ready` is the first cycle the node may be issued in (it rises as its
predecessors are issued, by the latency on the edge), `latest` is the cycle at which the node becomes critical
(longest path of the block less the node's own path to the end), `path` that path.

    IRDUMP_OUT=/tmp/irdump/sched.txt MWCIncludes=src gdb -q -batch -x tools/mwcc_irdump/gdb_schedtrace.py \
        --args local/wibo local/mwcps2/3.0b52-030722/mwccps2.exe -c -O4,s -sdatathreshold 2 \
        -inline level=8,bottomup -Iinclude /tmp/irdump/t.cpp -o /tmp/irdump/t.o

Run from the repository root, on a file with one function: the blocks of every function are written in sequence,
first pass then second pass for each.
"""
import os
import sys

import gdb

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gdb_common as g  # noqa: E402

SCHEDULE_BLOCK = 0x4C42F0      # scheduleblock(PCodeBlock *)
NODES_BUILT = 0x4C4361         # in it: the node list is complete and every node's latest cycle is set
PICKED = 0x4C43C5              # in it: the chosen node is in esi, the slot in ebx, the cycle at 4(%esp)
NODE_LIST = 0x59D24A           # head of the node list
MACHINE = 0x59D1E4             # the processor model; its first word is the issue width

# node: next, ?, successors, instruction, ..., 0x12 order, 0x14 ready, 0x16 latest, 0x18 path, 0x1a predecessors
# successor: next, node, latency (16 bits)
# instruction: 0x2a operand count, operands of 0x16 bytes from 0x3c: kind, class, flags (1 read, 2 written), number


def main():
    inferior = g.start(SCHEDULE_BLOCK)
    rd = g.reader(inferior)
    out = open(os.environ["IRDUMP_OUT"], "w")
    for address in (SCHEDULE_BLOCK, NODES_BUILT, PICKED):
        gdb.execute("break *%#x" % address)
    ids = {}
    count = 0

    def operands(instr):
        text = []
        for i in range(rd(instr + 0x2A, 2)):
            op = instr + 0x3C + 0x16 * i
            kind, cls, flags, number = rd(op, 1), rd(op + 1, 1), rd(op + 2, 2), rd(op + 4, 2)
            if kind == 0:
                text.append("%s%sc%dr%d" % ("D:" if flags & 2 else "", "U:" if flags & 1 else "", cls, number))
            elif kind == 1:
                text.append("#%d" % (rd(op + 4, 4) - (1 << 32) if rd(op + 4, 4) >> 31 else rd(op + 4, 4)))
            else:
                text.append("k%d" % kind)
        return "op=%04x %s" % (rd(instr + 0x28, 2), " ".join(text))

    while True:
        try:
            gdb.execute("continue", to_string=True)
            pc = g.register("pc")
        except gdb.error:
            break
        if pc == SCHEDULE_BLOCK:
            block = rd(g.esp() + 4, 4)
            out.write("BLOCK %d index=%d count=%d width=%d\n" % (count, rd(block + 0x1C, 4), rd(block + 0x2C, 2),
                                                           rd(rd(MACHINE, 4), 4)))
            count += 1
        elif pc == NODES_BUILT:
            ids = {}
            nodes = []
            node = rd(NODE_LIST, 4)
            while node:
                ids[node] = len(nodes)
                nodes.append(node)
                node = rd(node, 4)
            for node in nodes:
                successors = []
                link = rd(node + 8, 4)
                while link:
                    successors.append("%d+%d" % (ids.get(rd(link + 4, 4), -1), rd(link + 8, 2)))
                    link = rd(link, 4)
                out.write("  node %d %s  order=%d ready=%d latest=%d path=%d preds=%d -> %s\n" % (
                    ids[node], operands(rd(node + 0xC, 4)), rd(node + 0x12, 2), rd(node + 0x14, 2),
                    rd(node + 0x16, 2), rd(node + 0x18, 2), rd(node + 0x1A, 2), " ".join(successors)))
        elif pc == PICKED:
            node = g.register("esi")
            out.write("  t=%d slot=%d pick %d %s\n" % (rd(g.esp() + 4, 4), g.register("ebx") & 0xFFFF,
                                                    ids.get(node, -1), operands(rd(node + 0xC, 4))))
        else:
            break
    g.finish(out)


main()
