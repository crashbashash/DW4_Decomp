"""gdb_pcode.py: the b52 code generator's blocks around its delay-slot filler (gdb script).

The compiler's own PCode dump is compiled out (its dump routine is an empty function), so this reads the blocks
from memory: on entry to the block pass (0x4c6d60), with a line for every change that pass makes, and in the
routine that fills delay slots (0x4c7a30) before the liveness pass, after it (use, def, live-in and live-out per
block) and after the slots are filled. Each block is printed with its predecessor and
successor lists, each instruction with its operands and flags.

    PCODE_OUT=<out>.txt MWCIncludes=src gdb -q -batch -x tools/mwcc_irdump/gdb_pcode.py \
        --args local/wibo local/mwcps2/3.0b52-030722/mwccps2.exe -c <unit flags> <test>.cpp -o <test>.o

Run from the repository root, on a test file with one function. What to read from it:

- A block whose `pred` list is empty although it has predecessors: the block pass changed something (it retargeted
  a branch whose target began with a jump, deleted a jump to the next block, or merged two blocks) and emptied
  every predecessor list. The filler then takes nothing from a branch's fall-through block.
- The filler takes the first instruction of the fall-through block only when that block has exactly one
  predecessor and the instruction's destination is in neither the live-in nor the live-out set of the block that
  ends with the branch.

Immediate operands of kind 3 are printed as `#?`; register, memory-offset and label operands are decoded.
"""
import os
import sys

import gdb

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gdb_common as g  # noqa: E402

BLOCK_LIST = 0x5B639C      # head of the block list
LIVE_INFO = 0x5B67A4       # per register class: array of {use, def, in, out} bit sets, 16 bytes per block
OPCODE_INFO = 0x5A84A0     # 44 bytes per opcode
OPCODE_NAME = -24          # offset of the mnemonic pointer in an opcode's record
BEFORE, LIVE, AFTER = 0x4C7A56, 0x4C7A61, 0x4C7A7B
BLOCK_PASS = 0x4C6D60      # entry of the block pass ("After block optimization" is its phase name)
# The three places where the block pass's per-block routine (0x4c6b80) reports a change; its argument, the block,
# is at 0x1c(%esp) at each of them.
CHANGES = {0x4C6C40: "retargeted the branch that ends it: the target began with an unconditional jump",
           0x4C6CA1: "deleted the jump that ends it: the target is the next block",
           0x4C6D47: "merged its only successor into it: the successor ends with a jump or the return"}
REGISTERS = ['zero', 'at', 'v0', 'v1', 'a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7',
             's0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 't8', 't9', 'k0', 'k1', 'gp', 'sp', 's8', 'ra']


def cstr(inferior, address, limit=40):
    data = b""
    try:
        while len(data) < limit:
            c = inferior.read_memory(address, 1).tobytes()
            if c == b"\0":
                break
            data += c
            address += 1
    except gdb.MemoryError:
        return "?"
    return data.decode(errors="replace")


def main():
    inferior = g.start(BEFORE)
    rd = g.reader(inferior)
    out = open(os.environ["PCODE_OUT"], "w")
    names = {}

    def mnemonic(op):
        if op not in names:
            names[op] = "op%x" % op
            pointer = rd(OPCODE_INFO + op * 44 + OPCODE_NAME, 4)
            if 0x541000 <= pointer < 0x576000:
                text = cstr(inferior, pointer)
                if text and text.isprintable():
                    names[op] = text
        return names[op]

    def operand(a):
        kind, cls, usage, reg = rd(a, 1), rd(a + 1, 1), rd(a + 2, 2), rd(a + 4, 2)
        if kind == 0:
            name = REGISTERS[reg] if cls == 0 and reg < 32 else "c%d:r%d" % (cls, reg)
            return name + {1: "(u)", 2: "(d)", 3: "(ud)"}.get(usage & 3, "")
        if kind == 3:
            return "#?"
        if kind == 4:
            value = rd(a + 2, 4)
            return "#%d" % (value - (1 << 32) if value >> 31 else value)
        if kind == 6:
            label = rd(a + 2, 4)
            block = rd(label + 4, 4) if label else 0
            return "->B%d" % (rd(block + 0x1C, 4) if block else -1)
        return "k%d:%x" % (kind, rd(a + 2, 4))

    def blocks(title):
        out.write("== %s\n" % title)
        block = rd(BLOCK_LIST, 4)
        while block:
            preds, edge = [], rd(block + 0xC, 4)
            while edge:
                preds.append(rd(rd(edge + 0xC, 4) + 0x1C, 4))
                edge = rd(edge + 8, 4)
            succs, edge = [], rd(block + 0x10, 4)
            while edge:
                succs.append(rd(rd(edge + 0x10, 4) + 0x1C, 4))
                edge = rd(edge + 4, 4)
            out.write("B%d flags=%04x n=%d pred=%s succ=%s\n"
                      % (rd(block + 0x1C, 4), rd(block + 0x2E, 2), rd(block + 0x2C, 2), preds, succs))
            code = rd(block + 0x14, 4)
            while code:
                count = min(rd(code + 0x2A, 2), 8)
                out.write("    %-8s %-44s flags=%08x\n" % (mnemonic(rd(code + 0x28, 2)),
                                                          ",".join(operand(code + 0x3C + 22 * i) for i in range(count)),
                                                          rd(code + 0xC, 4)))
                code = rd(code, 4)
            block = rd(block, 4)

    def liveness():
        out.write("== liveness, general registers\n")
        info = rd(LIVE_INFO, 4)
        block = rd(BLOCK_LIST, 4)
        while block:
            index = rd(block + 0x1C, 4)
            sets = []
            for k in range(4):
                pointer = rd(info + index * 16 + 4 * k, 4)
                bits = rd(pointer, 4) if pointer else 0
                sets.append(" ".join(REGISTERS[i] for i in range(32) if bits >> i & 1))
            out.write("B%d use[%s] def[%s] in[%s] out[%s]\n" % (index, sets[0], sets[1], sets[2], sets[3]))
            block = rd(block, 4)

    for address in (BEFORE, LIVE, AFTER, BLOCK_PASS) + tuple(CHANGES):
        gdb.execute("break *%#x" % address)
    function, last = 0, None
    while True:
        try:
            gdb.execute("continue", to_string=True)
            pc = g.register("pc")
        except gdb.error:
            break
        if pc == last and pc != BEFORE:
            continue                      # gdb reports a stop twice after stepping off a breakpoint
        last = pc
        if pc == BLOCK_PASS:
            blocks("function %d before the block pass" % (function + 1))
        elif pc in CHANGES:
            out.write("== block pass: B%d %s\n" % (rd(rd(g.esp() + 0x1C, 4) + 0x1C, 4), CHANGES[pc]))
        elif pc == BEFORE:
            function += 1
            blocks("function %d before the delay slots" % function)
        elif pc == LIVE:
            liveness()
        elif pc == AFTER:
            blocks("function %d after the delay slots" % function)
        else:
            break
    g.finish(out)


main()
