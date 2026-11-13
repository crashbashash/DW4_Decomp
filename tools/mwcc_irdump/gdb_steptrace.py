"""gdb_steptrace.py: an instruction trace of one compiler routine (gdb script).

Single-steps one call of the routine at IRDUMP_START (default IRO_CommonSubs) and writes the address of every
instruction it executes, callees included, to IRDUMP_OUT, one per line. Calls that leave the compiler image (into
the loader's own code) are run to their return and written as `host->ADDR`. Use it to see which branch of a
decision the compiler takes for one spelling and not for another: trace both and diff the files. It is slow
(a few thousand instructions a second); IRDUMP_MAX caps the count (default 3000000).

    IRDUMP_OUT=/tmp/irdump/trace.txt MWCIncludes=src gdb -q -batch -x tools/mwcc_irdump/gdb_steptrace.py \
        --args local/wibo local/mwcps2/3.0b52-030722/mwccps2.exe -c -O4,p -sdatathreshold 2 \
        -inline level=8,bottomup -Iinclude /tmp/irdump/t.cpp -o /tmp/irdump/t.o

Run from the repository root.
"""
import os
import sys

import gdb

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import b52  # noqa: E402
import gdb_common as g  # noqa: E402

IMAGE_END = 0x5D1000


def main():
    start = int(os.environ.get("IRDUMP_START", "%#x" % b52.COMMON_SUBS), 16)
    limit = int(os.environ.get("IRDUMP_MAX", "3000000"))
    inferior = g.start(start)
    rd = g.reader(inferior)
    gdb.execute("break *%#x" % start)
    gdb.execute("continue")
    gdb.execute("delete")
    out = open(os.environ["IRDUMP_OUT"], "w")
    sp = g.esp()
    ret = rd(sp, 4)
    out.write("ret %x\n" % ret)
    n = 0
    while n < limit:
        gdb.execute("stepi", to_string=True)
        pc = g.register("pc")
        if pc == ret and g.esp() > sp:
            break
        if 0x400000 <= pc < IMAGE_END:
            out.write("%x\n" % pc)
        else:
            back = rd(g.esp(), 4)
            out.write("host->%x\n" % back)
            gdb.execute("tbreak *%#x" % back, to_string=True)
            gdb.execute("continue", to_string=True)
            out.write("%x\n" % g.register("pc"))
        n += 1
    out.write("END %d\n" % n)
    g.finish(out)


main()
