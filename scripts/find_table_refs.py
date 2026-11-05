# find_table_refs.py — find code instructions that reference a VA range.
#
# Scans all instructions for lui/addiu (and similar) sequences whose combined
# value lands in [lo, hi], plus any data references the reference manager has
# recorded into that range. Prints the containing function and address.
#
#   pyghidra-run <elf> -postScript find_table_refs.py --lo 0x004cd000 --hi 0x004ce500
#
# @category PS2
# @runtime PyGhidra

import typing

if typing.TYPE_CHECKING:
    from typing import Any
    currentProgram: Any = None
    getScriptArgs: Any = None
    toAddr: Any = None


def parse_args(argv):
    lo = hi = None
    i = 0
    while i < len(argv):
        a = argv[i]
        if a == "--lo" and i + 1 < len(argv):
            lo = int(argv[i + 1], 0); i += 2
        elif a == "--hi" and i + 1 < len(argv):
            hi = int(argv[i + 1], 0); i += 2
        else:
            i += 1
    if lo is None or hi is None:
        raise SystemExit("need --lo and --hi")
    return lo, hi


def main():
    lo, hi = parse_args(list(getScriptArgs()))
    listing = currentProgram.getListing()
    fm = currentProgram.getFunctionManager()
    refs = set()

    ins_iter = listing.getInstructions(True)
    while ins_iter.hasNext():
        ins = ins_iter.next()
        addr = ins.getAddress().getOffset()
        # Skip data (Ghidra marks undefined data as instructions sometimes)
        if not (0x100000 <= addr < 0x4c0000):
            continue
        # look at operand scalar values
        for op in range(ins.getNumOperands()):
            refs_from = ins.getOperandReferences(op)
            for r in refs_from:
                t = r.getToAddress().getOffset()
                if lo <= t < hi:
                    refs.add((addr, t, ins.getMnemonicString()))

    # also scan raw lui/addiu pairs by walking instructions in order
    ins_iter = listing.getInstructions(True)
    prev_lui = {}  # reg -> value
    out = set()
    while ins_iter.hasNext():
        ins = ins_iter.next()
        addr = ins.getAddress().getOffset()
        if not (0x100000 <= addr < 0x4c0000):
            continue
        mn = ins.getMnemonicString()
        if mn == "lui":
            # operand 0 = reg, operand 1 = imm
            if ins.getNumOperands() >= 2:
                reg = ins.getRegister(0)
                val = ins.getScalar(1)
                if reg is not None and val is not None:
                    prev_lui[reg.getName()] = (val.getUnsignedValue() << 16) & 0xFFFFFFFF
        elif mn in ("addiu", "ori", "addi", "daddiu") and ins.getNumOperands() >= 3:
            reg = ins.getRegister(1)  # target reg (2nd operand for addiu rt, rs)
            base = ins.getRegister(1)
            reg = ins.getRegister(0) if False else reg
            # For addiu rt, rs, imm: operands[0]=rt, [1]=rs, [2]=imm
            try:
                rt = ins.getRegister(0)
                rs = ins.getRegister(1)
                imm = ins.getScalar(2)
            except Exception:
                continue
            if rt is None or rs is None or imm is None:
                continue
            base_val = prev_lui.get(rs.getName())
            if base_val is not None:
                full = (base_val + imm.getSignedValue()) & 0xFFFFFFFF
                if lo <= full < hi:
                    out.add((addr, full, mn))
    for a, t, m in sorted(refs):
        fn = fm.getFunctionContaining(toAddr(a))
        fnname = fn.getName() if fn else "-"
        print(f"REF  0x{a:08x} -> 0x{t:08x} [{m}]  in {fnname} (0x{fn.getEntryPoint().getOffset():08x})")
    for a, t, m in sorted(out):
        fn = fm.getFunctionContaining(toAddr(a))
        fnname = fn.getName() if fn else "-"
        print(f"LIMM 0x{a:08x} -> 0x{t:08x} [{m}]  in {fnname} (0x{fn.getEntryPoint().getOffset():08x})")


if __name__ == "__main__":
    main()
