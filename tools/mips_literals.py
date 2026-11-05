#!/usr/bin/env python3
"""Resolve the addresses MIPS code forms, from the `lui` that starts them.

Both the platform-boundary map and the SDK string miner need the same thing: given a
`lui rt, hi`, find the address the code builds out of `rt`, a few instructions later.
They were written separately and each got the same two things wrong, so the logic now
lives here once.

The two things:

  * **The address is usually completed in the delay slot of a call.** `lui a0, 0x4e` /
    `jal f` / `addiu a0, a0, ...` puts the low half *after* the call, because the delay
    slot always executes.  A scan that stops at the call sees the `lui` and none of its
    uses; every SDK error string is materialised this way.
  * **The page is not the address.** MWCC reaches 0x1000F180 as `lui 0x1001` plus a
    negative offset, and 0x10010000 is not a register, so the resolved address must be
    classified, never the page it was started from.

`writes_rt` is what keeps the search honest: an unrelated `nop`, `sll` or second `lui`
does not end the value, but any instruction that writes `rt` does.
"""

VADDR_BASE, FILE_BASE = 0x100000, 0x80

# Every memory opcode the EE has: the MMI 128-bit pair, the classic 32-bit set, the
# unaligned pair, and the 64-bit `ld`/`sd`.
LOADSTORE = {0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
             0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x37, 0x3F}


def signed16(imm):
    return imm - 0x10000 if imm & 0x8000 else imm


def writes_rt(ins, rt):
    """Does `ins` write general-purpose register `rt`?"""
    op = ins >> 26
    if op == 0x00:  # SPECIAL: the destination is rd; jr/jalr write nothing
        if (ins & 0x3F) in (0x08, 0x09):
            return False
        rd = (ins >> 11) & 0x1F
        return rd == rt and rd != 0
    if op == 0x0F or op in (0x09, 0x0D, 0x0C, 0x0A, 0x0B, 0x0E) or op in LOADSTORE:
        return ((ins >> 16) & 0x1F) == rt
    if op in (0x10, 0x12):  # COP0/COP2 moves: mfc writes a GPR, mtc does not
        return ((ins >> 16) & 0x1F) == rt
    return False


def exact_addr(ins, hi, rt):
    """The address `ins` forms from a base in `rt` (`lui rt, hi`), or None.

    Covers the register form (`addiu`/`ori rt2, rt, lo`) and the direct access form
    (`lw`/`sw`/`lq`/`sq ... (rt)`).
    """
    op = ins >> 26
    rs = (ins >> 21) & 0x1F
    if rs != rt:
        return None
    if op in (0x09, 0x0D):  # addiu / ori
        return (hi << 16) + signed16(ins & 0xFFFF)
    if op in LOADSTORE:
        return (hi << 16) + signed16(ins & 0xFFFF)
    return None


def dynamic_base(ins, rt):
    """True when `ins` adds a second register to `rt` (`addu`/`or`), losing the low half."""
    if (ins >> 26) != 0x00 or (ins & 0x3F) not in (0x21, 0x25):
        return False
    return ((ins >> 21) & 0x1F) == rt or ((ins >> 16) & 0x1F) == rt


def is_control_flow(ins):
    """True for a jump or a call: its delay slot still executes, then control leaves."""
    op = ins >> 26
    return op == 0x03 or (op == 0x00 and (ins & 0x3F) in (0x08, 0x09))


def scan_from_lui(word, va, hi, rt, window=9):
    """Yield ('exact', addr) / ('range', page) for a `lui` at `va`.

    `word` is a callable address -> instruction word or None.  Stops at the first
    instruction that writes `rt`; looks one instruction past a jump, because the delay
    slot of a call is where the low half usually lands.
    """
    for k in range(1, window):
        ins = word(va + 4 * k)
        if ins is None:
            return
        a = exact_addr(ins, hi, rt)
        if a is not None:
            yield ("exact", a)
            return
        if dynamic_base(ins, rt):
            yield ("range", hi << 16)
            return
        if is_control_flow(ins):
            # the delay slot executes even though control then leaves
            nxt = word(va + 4 * (k + 1))
            if nxt is not None:
                a = exact_addr(nxt, hi, rt)
                if a is not None:
                    yield ("exact", a)
                elif dynamic_base(nxt, rt):
                    yield ("range", hi << 16)
            return
        if writes_rt(ins, rt):
            return


def make_word(img):
    def word(va):
        import struct
        o = va - VADDR_BASE + FILE_BASE
        if 0 <= o <= len(img) - 4:
            return struct.unpack_from("<I", img, o)[0]
        return None
    return word
