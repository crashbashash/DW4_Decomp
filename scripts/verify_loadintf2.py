#!/usr/bin/env python3
"""Compare the recovered beNDMWLoadIntf2 reference with retail execution.

No game bytes are embedded.  Loads the user's retail ELF and runs the original
MIPS instructions of

    0x003e4750  beNDMWLoadIntf2::vfunc_31   (per-frame master update)
    0x003e9430  beNDMWLoadIntf2::vfunc_34   (family message handler)
    0x003eba10..0x003ef5d0  the master update's per-screen helpers

through a restricted integer R5900 interpreter.  The recovered C in
recovered/frontend/loadintf2.c and recovered/frontend/selslot.c runs against
the *same* world (peek/poke/call), so the two are compared on the ordered
engine calls (with their meaningful arguments) and on every non-stack byte
written.

For the slot-selection screen the *original helper instructions execute* on the
retail side: the interpreter descends into the real beNDMWLoadIntf2SelSlot
helpers (REAL, recovered/frontend/selslot.c) instead of stubbing them, and the
recovered C calls the matching ss_* implementation.  Their own callees stay
stubbed.  Everything else is stubbed on both sides; this verifies control flow
and call stream, not the callees' own implementations, rendering, timing, or
reference-lifetime side effects.

The one engine call whose argument list contains a temporary buffer (not just
an opaque pointer) is compared more strongly than the rest:

  0x003e3e00  the text-operation send (owner, playerIndex, nameToken,
              opToken, vec3*, flag).  Its fifth argument is a *temporary*
              vec3 the caller filled with 0x003e9220.  The two interpreters
              use different temporary addresses (a retail stack slot vs the
              recovered LI2_TMP slot), so each call's 12-byte payload is read
              at its own pointer and compared by value (see `_event`).

What this comparison does *not* establish, stated so it is not mistaken for a
stronger claim than it is:

  * `snapshot()` compares two *final* memory images, not an ordered write
    trace.  Two implementations that reach the same final bytes through a
    different sequence of stores pass.  Spurious intermediate stores that are
    later overwritten are invisible.  The byte writes are also compared as a
    single final map, so a write the C makes and the retail does not *at the
    same final value* is indistinguishable.
  * Temporary and stack pointers are normalised out of the compared call
    arguments (both sides use different scratch addresses), so the *identity*
    and *alias* relationship of a temporary is not compared directly — only
    the 12-byte payload of the 0x003e3e00 temporaries is, by value.
  * The stubbed callees are called with the same arguments on both sides, so
    their own behaviour, the reference-lifetime side effects their real bodies
    would have, and everything downstream of a stub are out of scope.
  * A stubbed callee's argument count (ARGC) is the number of its argument
    registers the *recovered C* supplies; where a retail call site leaves a
    later register stale (e.g. 0x003de260's second argument) that register is
    not compared.
"""
import argparse
import ctypes as C
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
MASK = (1 << 64) - 1

SELF, FRAME, INFO, WORK = 0x01000000, 0x01001000, 0x01008000, 0x0100a000
SYS, MSG = 0x01002000, 0x01003000
OBJ = 0x01010000
INTF, CTRL, MAKECHR, CM, MESWIN, TEXTORDER, DST = (
    0x01020000, 0x01021000, 0x01022000, 0x01023000, 0x01024000, 0x01025000, 0x01026000)
NODE, GAMERAM, ELEMS, ELEM0 = 0x01030000, 0x01040000, 0x01041000, 0x01042000
PAD, FLAGOBJ = 0x01070000, 0x01071000
RECLIST, RECARR, REC = 0x01080000, 0x01080100, 0x01080200
AUXLIST, AUXARR, AUXREC = 0x01081000, 0x01081100, 0x01081200
AUX2, AUX2ARR = 0x01082000, 0x01082100
MCTRL, MCARRAY, MCTRLARR = 0x01083000, 0x01083100, 0x01083200
SELSLOT, NAMESEL, DATASELINTF, DIFFSELECT = 0x01027000, 0x01028000, 0x01029000, 0x0102a000
MCREC = 0x01083300
# CommMdlCtrl's open/close data lists (recovered/frontend/completion.c reads
# [cm+0x14]/[cm+0x18] as an igObjectList: +8 count, +0x10 data).
CMLIST_O, CMLIST_C = 0x01023040, 0x01023080
CMARR_O, CMARR_C = 0x01023050, 0x01023090
# The three per-player records ds_select arms besides the current player's.
RECALT = 0x0108f000
GP_FLAG = 0x554c14
STACK_LO = 0x01f00000
TMP_LO, TMP_HI = 0x01060000, 0x01070000


def norm_event(args):
    """Stack/temporaries are not part of the compared contract."""
    out = []
    for v in args:
        u = v & 0xffffffff
        out.append(0 if (STACK_LO <= u < 0x02000000 or TMP_LO <= u < TMP_HI) else v)
    return tuple(out)


def sx(n, bits):
    n &= (1 << bits) - 1
    return n - (1 << bits) if n >> (bits - 1) else n


# (address, number of meaningful argument registers) for every stubbed callee.
ARGC = {
    0x3c46a0: 0,
    0x38d4a0: 3, 0x301000: 1, 0x2f88e0: 1, 0x36ae80: 1, 0x2ff820: 1,
    0x301e30: 2, 0x3022c0: 3, 0x236f80: 2,
    0x3c43c0: 1, 0x3c40c0: 1, 0x3c6ea0: 1, 0x3c76c0: 1, 0x3c2e60: 1,
    0x3c27c0: 1, 0x3c6b00: 1, 0x3c3900: 1, 0x3c3e40: 1, 0x3c3560: 1, 0x3c31e0: 1,
    0x3d9de0: 7, 0x38f800: 2, 0x38e5f0: 5, 0x38e5d0: 2, 0x38e060: 2,
    0x38f240: 1, 0x38f250: 2, 0x38f2e0: 3, 0x38f320: 2,
    # --- master update (vfunc_31) callees ---
    0x3e44f0: 1, 0x3ec450: 1, 0x39b810: 2, 0x38d860: 4, 0x3a9280: 2,
    0x3ee6d0: 2, 0x3ecba0: 2, 0x3e9240: 2, 0x3e9260: 2, 0x3e93b0: 1,
    0x3e92a0: 1, 0x3e9280: 3, 0x3e9370: 2, 0x3e9360: 2, 0x3e9330: 2,
    0x3e92b0: 2, 0x33e9c0: 2, 0x3e3e00: 6, 0x3eca70: 1, 0x3e44d0: 1,
    0x3ec050: 2, 0x3ebe00: 3, 0x3e42a0: 5, 0x3ecaa0: 1, 0x3e4030: 5,
    0x3e4210: 4, 0x3e4280: 1, 0x3ecad0: 2, 0x3e9220: 2, 0x1ae1a0: 1,
    0x3e9090: 1, 0x3e90a0: 2, 0x3e90b0: 1, 0x3e90c0: 1, 0x3e90d0: 1,
    0x3e90f0: 2, 0x3e9110: 1, 0x3e9160: 3, 0x3ee320: 2, 0x38f0f0: 1,
    0x38f220: 2, 0x38d860: 4, 0x3a9580: 3, 0x3ebd70: 7, 0x3ebdc0: 4,
    0x3ebd70: 7, 0x3ecdc0: 7, 0x3ed050: 5, 0x3ed2e0: 5, 0x3ed650: 5,
    0x3edf60: 5, 0x3ee250: 3, 0x3ef5d0: 3, 0x3ecb00: 2, 0x3ecae0: 3,
    0x3ecb70: 1, 0x3ecb80: 1, 0x3ecb90: 1, 0x3ecb20: 1, 0x3ecbc0: 1,
    0x3def80: 2, 0x3def70: 1, 0x3ee320: 2, 0x3ddb10: 3, 0x3ddb80: 2,
    0x3de260: 2, 0x3d9e10: 4, 0x3d9e70: 2, 0x3d9e90: 1, 0x3da7c0: 1,
    0x3dafb0: 3, 0x3daff0: 2, 0x3db060: 2, 0x3db780: 2, 0x3dbf90: 2,
    0x2294f0: 1, 0x12a4a4: 2, 0x2d6790: 3, 0x3614f0: 1, 0x3843c0: 2,
    0x38f4b0: 2, 0x38f670: 2, 0x38f830: 2, 0x3a9220: 2, 0x3c6830: 1,
    0x3e3e00: 6,
    0x3e4480: 3, 0x3ee190: 2,
    # --- text-order publishing (0x3ebce0/0x3ebe00/0x3ec050) callees ---
    0x389ff0: 3,
}

# The slot-selection per-screen helpers, the text-order publishing trio and
# the completion/selection group execute their ORIGINAL instructions on the
# retail side (the interpreter descends into them instead of stubbing) and the
# recovered C calls the matching ss_*/to_*/cm_*/ds_* implementation.  Their own
# callees stay stubbed.
# See recovered/frontend/selslot.{c,h}, textorder.{c,h}, completion.{c,h}.
REAL = frozenset((
    0x3e0b80, 0x3e0bb0, 0x3e0c40, 0x3e1760, 0x3e2a80, 0x3e2b10, 0x3e3070,
    0x3eba10, 0x3ebce0, 0x3ebd70, 0x3ebdc0, 0x3ebe00, 0x3ec050,
    0x3e4280, 0x3e44d0, 0x3ee190,
))

NAME_BY_TOKEN = {
    0x5172a0: INTF, 0x5172b0: CTRL, 0x5172b8: MAKECHR, 0x5172c0: CM,
    0x5172d0: MESWIN, 0x5172e8: TEXTORDER, 0x5172f8: DST,
    0x5172d8: 0x01027000, 0x5172e0: 0x01028000, 0x517308: 0x01029000,
    0x517318: 0x0102a000,
}


class Harness:
    def __init__(self, image):
        self.image = image
        self.mem = {}
        self.events = []
        self.counter = {}
        self.scen = {}
        self.rv = {}

    def read(self, address, size):
        address &= 0xffffffff
        if 0x100000 <= address and address + size <= 0x554b00:
            o = address - 0x100000 + 0x80
            return int.from_bytes(self.image[o:o + size], 'little')
        return sum(self.mem.get(address + i, 0) << (i * 8) for i in range(size))

    def write(self, address, size, value):
        address &= 0xffffffff
        for i in range(size):
            self.mem[address + i] = (value >> (8 * i)) & 255

    def fresh(self, key, addr):
        v = self.counter.get(key, addr)
        self.counter[key] = v + 0x100
        return v

    def reply(self, addr, a):
        s = self.scen
        if getattr(self, 'rebind_text', False) and addr in (0x38d860, 0x38f830, 0x38e060):
            self.write(TEXTORDER + 0x10, 4, self.read(TEXTORDER + 0x10, 4) + 4)
        if addr in self.rv:
            return self.rv[addr]
        if addr == 0x3c46a0:
            return 0
        if addr == 0x38d4a0:
            return s.get('cmd', 0)
        if addr in (0x301000, 0x2f88e0):
            return SYS
        if addr == 0x36ae80:
            return self.fresh('work', WORK)
        if addr in (0x3022c0, 0x3e9280):
            return NAME_BY_TOKEN.get(a[2], 0)
        if addr in (0x3e93b0, 0x3e92a0):
            return self.read(a[0], 4)
        if addr in (0x3e9240, 0x3e9260):
            base = self.read(a[0] + 0x10, 4)
            return self.read(base + (a[1] & 0xffff) * 4, 4)
        if addr == 0x3e9090:
            return self.read(a[0] + 0x10, 4)
        if addr == 0x3e90c0:
            return self.read(a[0] + 0x0c, 1)
        if addr == 0x3e90b0:
            return self.read(a[0] + 0x0d, 1)
        if addr == 0x3e90f0:
            return self.read(a[0] + (a[1] & 0xffff) * 4, 4)
        if addr == 0x3e9370:
            return a[1]
        if addr == 0x3e9220:
            # The vec3 copy helper (retail 0x3e9220 copies 3 words from a1 to
            # a0: lwc1/swc1 at +0/+4/+8).  Modelled so the 0x3e3e00 temporary
            # carries a real payload on both sides.
            for o in range(0, 12, 4):
                self.write(a[0] + o, 4, self.read(a[1] + o, 4))
            return 0
        if addr == 0x39b810:
            return PAD
        if addr == 0x236f80:
            return self.fresh('node', OBJ + 0x8000)
        if addr in (0x3c43c0, 0x3c40c0, 0x3c6ea0, 0x3c76c0, 0x3c2e60, 0x3c27c0,
                    0x3c6b00, 0x3c3900, 0x3c3e40, 0x3c3560, 0x3c31e0, 0x3c6830):
            return self.fresh('obj', OBJ)
        if addr == 0x38f800:
            return GAMERAM
        if addr == 0x3a9280:
            return FLAGOBJ
        if addr == 0x3a9220:
            return self.fresh('slot', OBJ + 0x4000)
        if addr == 0x3a9580:
            return a[0]
        if addr == 0x38f240:
            return s.get('f240', 0)
        if addr == 0x38f320:
            return s.get('f320', 0)
        if addr == 0x2294f0:
            return s.get('count', 0)
        if addr == 0x12a4a4:
            return s.get('cmp', 0)
        return 0

    def _event(self, addr, a, n):
        """One ordered engine call: normalised args plus, for the text-operation
        send, the 12-byte payload of the caller's vec3 temporary read at that
        call's own pointer (the two sides use different scratch addresses)."""
        args = norm_event(tuple(a[:n]) + (0,) * (8 - n))
        payload = None
        if addr == 0x3e3e00 and n >= 5:
            vp = a[4] & 0xffffffff
            payload = tuple(self.read(vp + o, 4) for o in range(0, 12, 4))
        return (addr, args, payload)

    def call(self, addr, a):
        n = ARGC.get(addr)
        if n is None:
            raise AssertionError(f'unknown callee {addr:#x}')
        self.events.append(self._event(addr, a, n))
        return self.reply(addr, a)

    def set_pad(self, r):
        """The controller input memory changed for this tick.  Only the pad
        block (and the CommMdlCtrl model-queue counts, which drive the recovered
        completion accessors) is written: the controller/record state (CTRL, the
        per-player record, the sub-controller records) is *game state* and must
        evolve on its own across a multi-tick flow, so it is set once by
        setup()."""
        self.write(PAD + 0x1c, 4, r.get('pad1c', 0))
        self.write(PAD + 0x20, 4, r.get('pad20', 0))
        self.write(PAD + 0x48, 4, r.get('pad48', 0))
        self.write(PAD + 0x4c, 4, r.get('pad4c', 0))
        if 'cmon' in r:
            self.write(CMLIST_O + 8, 4, r['cmon'])
        if 'cmcn' in r:
            self.write(CMLIST_C + 8, 4, r['cmcn'])

    def setup(self, r, up=False):
        w32 = lambda a, v: self.write(a, 4, v)
        w8 = lambda a, v: self.write(a, 1, v)
        w32(SELF + 0x0c, SYS)
        w32(SELF + 0x14, MSG)
        w32(SELF + 0x20, 0)
        w32(SELF + 0x2c, 0)
        w32(FRAME + 8, r.get('kind', 0))
        w32(FRAME + 0x28, r.get('work', 0))
        w32(INFO + 0x14, 0x01050000)
        w32(MSG + 0x14, MSG)
        for tok, base in NAME_BY_TOKEN.items():
            w32(base + 4, 1)
        if up:
            self.setup_up(w32, w8, r)
        else:
            w32(CTRL + 0x10, r.get('b10', 0))
            w32(CTRL + 0x11, r.get('b11', 0))
            w32(CTRL + 0x12, r.get('b12', 0))
            w32(CTRL + 0x13, r.get('b13', 0))
            w32(INTF + 0x28, ELEMS)
            w32(ELEMS + 0x10, ELEM0)
            for i in range(2):
                w32(ELEM0 + i * 4, 0x01051000 + i * 0x40)
                w8(0x01051000 + i * 0x40 + 0x0d, r.get('elem_d', (0, 0))[i])
        w8(GP_FLAG, 1)
        for a in (0x585be0, 0x587110, 0x587d08, 0x588518, 0x589208, 0x587108, 0x589678):
            w32(a, a)

    def setup_up(self, w32, w8, r):
        p = r.get('p', 0)
        w32(FRAME + 0x28, 0x01009000)
        w32(FRAME + 8, p)
        w32(INTF + 0x14, MSG)
        w32(INTF + 0x20, AUXLIST)
        w32(INTF + 0x24, AUX2)
        w32(INTF + 0x28, RECLIST)
        w32(INTF + 0x34, MCTRL)
        w32(INTF + 0x38, r.get('lang', 0))
        w32(INTF + 0x3c, 0)
        w32(INTF + 0x40, 0)
        w32(RECLIST + 0x10, RECARR)
        for i in range(4):
            w32(RECARR + i * 4, REC if i == p else RECALT + i * 0x40)
        w32(REC + 8, p)
        w8(REC + 0x0c, r.get('r0c', 0))
        w8(REC + 0x0d, r.get('r0d', 0))
        w8(REC + 0x0e, r.get('r0e', 0))
        w8(REC + 0x0f, r.get('r0f', 0))
        w8(REC + 0x10, r.get('r10', 0))
        w32(REC + 0x14, r.get('r14', 0))
        w32(REC + 0x24, r.get('ost', 0))
        w32(REC + 0x28, r.get('os28', 0))
        w32(REC + 0x2c, r.get('os2c', 0))
        w32(REC + 0x30, r.get('os30', 0))
        w8(CTRL + 0x10, r.get('c10', 0))
        w8(CTRL + 0x11, r.get('c11', 0))
        w8(CTRL + 0x12, r.get('c12', 0))
        w8(CTRL + 0x13, r.get('c13', 0))
        w8(CTRL + 0x14, r.get('c14', 0))
        w8(CTRL + 0x15, r.get('c15', 0))
        w8(CTRL + 0x16, r.get('issys', 0))
        w8(CTRL + 0x17, r.get('c17', 0))
        w8(CTRL + 0x1c, r.get('c1c', 0))
        w8(CTRL + 0x1d, r.get('c1d', 0))
        w8(CTRL + 0x1e, r.get('c1e', 0))
        w32(CTRL + 0x18, r.get('c18', 0))
        w32(CTRL + 0x24, r.get('st0', 0))
        w32(CTRL + 0x28, r.get('st1', 0))
        w32(CTRL + 0x2c, r.get('st2', 0))
        w32(CTRL + 0x30, r.get('st3', 0))
        w8(MAKECHR + 0x30, r.get('mk30', 0))
        w32(MAKECHR + 0x30, r.get('mki', 0))
        w8(SELSLOT + 0x36, r.get('sel36', 0))
        w8(SELSLOT + 0x37, r.get('sel37', 0))
        w32(SELSLOT + 0x40, r.get('sel40', 0))
        w32(SELSLOT + 0x4c, r.get('sel4c', 0))
        w32(SELSLOT + 0x50, r.get('sel50', 0))
        w32(SELSLOT + 0x54, r.get('sel54', 0))
        w32(SELSLOT + 0x58, r.get('sel58', 0))
        # Slot-selection screen wiring (recovered/frontend/selslot.c): the pad
        # manager, the CommMdlCtrl, the TextOrder and the manager object, plus
        # the inherited per-player sub-state and the mode/kind/cursor/mark
        # fields the ss_* helpers read.
        w32(SELSLOT + 0x14, PAD)
        w32(SELSLOT + 0x18, CM)
        w32(SELSLOT + 0x1c, TEXTORDER)
        w32(SELSLOT + 0x20, INTF)
        w32(SELSLOT + 0x30, p)
        w32(SELSLOT + 0x24, r.get('ss24', 0))
        w32(SELSLOT + 0x2c, r.get('ss2c', 0))
        w8(SELSLOT + 0x34, r.get('ss34', 0))
        w8(SELSLOT + 0x35, r.get('ss35', 0))
        w8(SELSLOT + 0x38, r.get('ss38', 0))
        w32(SELSLOT + 0x3c, r.get('ss3c', 0))
        w32(SELSLOT + 0x44, r.get('ss44', 0))
        w32(SELSLOT + 0x48, r.get('ss48', 0))
        w8(DATASELINTF + 0x49, r.get('ds49', 0))
        w8(DIFFSELECT + 0x25, r.get('df25', 0))
        w32(DIFFSELECT + 0x10, r.get('df10', 0))
        w8(NAMESEL + 0x4d, r.get('ns4d', 0))
        w8(NAMESEL + 0x4e, r.get('ns4e', 0))
        w32(PAD + 0x08, 0)
        self.set_pad(r)
        w32(CM + 0x1c, r.get('cm1c', 0))
        w32(CM + 0x20, r.get('cm20', 0))
        w32(CM + 0x24, r.get('cm24', 0))
        # The CommMdlCtrl's model queues (completion.c reads these).
        w32(CM + 0x14, CMLIST_O)
        w32(CM + 0x18, CMLIST_C)
        w32(CMLIST_O + 8, r.get('cmon', 0))
        w32(CMLIST_O + 0x10, CMARR_O)
        w32(CMLIST_C + 8, r.get('cmcn', 0))
        w32(CMLIST_C + 0x10, CMARR_C)
        w8(FLAGOBJ + 0x0c, r.get('flagc', 0))
        w32(MCTRL + 0x0c, r.get('mc0c', 0))
        w32(MCTRL + 0x10, r.get('mc10', 0))
        w32(MCTRL + 0x20, r.get('mc20', 0))
        w32(MCTRL + 0x2c, MCARRAY)
        w32(MCARRAY + 0x10, MCTRLARR)
        for i in range(6):
            w32(MCTRLARR + i * 4, MCREC + i * 0x40)
            w8(MCREC + i * 0x40 + 8, r.get('mr8', 0))
        w32(AUX2 + 0x10, MCTRLARR)
        w32(AUXLIST + 8, r.get('auxn', 0))
        w32(AUXLIST + 0x10, AUXARR)
        for i in range(4):
            w32(AUXARR + i * 4, AUXREC + i * 0x40)
            w8(AUXREC + i * 0x40 + 0x0f, r.get('auxf', 0))

    def snapshot(self):
        # Final-value map of the *persistent* world only.  Stack and the
        # LI2_TMP scratch slots are excluded: they are caller temporaries, not
        # game state, and the two sides do not share addresses (retail's live
        # on the interpreter stack).  The temp payload actually handed to
        # 0x3e3e00 is compared by value in _event instead.
        return {a: v for a, v in self.mem.items()
                if a < STACK_LO and not (TMP_LO <= a < TMP_HI)}


class Retail(Harness):
    def __init__(self, image):
        super().__init__(image)
        self.r = [0] * 32
        self.f = [0] * 32
        self.real_hits = set()     # recovered helpers we descended into (jal)
        self.executed = set()

    def call_hook(self, address):
        a = [sx(self.r[4 + i], 32) for i in range(8)]
        self.r[2] = self.call(address, a) & MASK

    def step(self, pc, delay=False):
        self.executed.add(pc)
        w = self.read(pc, 4)
        op, rs, rt, rd = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31
        sh, fn = (w >> 6) & 31, w & 63
        imm = sx(w, 16)
        r = self.r
        dest = None
        call = False
        if op == 0:
            if fn == 0:
                r[rd] = sx((r[rt] & 0xffffffff) << sh, 32) & MASK
            elif fn == 2:
                r[rd] = (r[rt] & 0xffffffff) >> sh
            elif fn == 3:
                r[rd] = (sx(r[rt] & 0xffffffff, 32) >> sh) & MASK
            elif fn in (8, 9):
                dest = r[rs] & 0xffffffff
                if fn == 9:
                    r[31] = pc + 8
                    call = dest not in REAL   # descend into recovered helpers
                    if not call:
                        self.real_hits.add(dest)
            elif fn in (0x21, 0x2d):
                r[rd] = (sx(r[rs] + r[rt], 32) if fn == 0x21 else r[rs] + r[rt]) & MASK
            elif fn == 0x23:
                r[rd] = (r[rs] - r[rt]) & MASK
            elif fn in (0x24, 0x25, 0x26):
                r[rd] = {0x24: r[rs] & r[rt], 0x25: r[rs] | r[rt], 0x26: r[rs] ^ r[rt]}[fn] & MASK
            elif fn in (0x2a, 0x2b):
                r[rd] = int(sx(r[rs], 64) < sx(r[rt], 64)) if fn == 0x2a else int((r[rs] & MASK) < (r[rt] & MASK))
            elif fn == 0x3c:
                r[rd] = (r[rt] << (sh + 32)) & MASK
            elif fn == 0x3e:
                r[rd] = r[rt] >> (sh + 32)
            elif fn == 0x3f:
                r[rd] = (sx(r[rt], 64) >> (sh + 32)) & MASK
            else:
                raise AssertionError(f'R opcode {w:#x} at {pc:#x}')
        elif op in (2, 3):
            dest = ((pc + 4) & 0xf0000000) | ((w & 0x3ffffff) << 2)
            if op == 3:
                r[31] = pc + 8
                call = dest not in REAL       # descend into recovered helpers
                if not call:
                    self.real_hits.add(dest)
        elif op in (1, 4, 5, 6, 7):
            if op == 1:
                assert rt in (0, 1), f'unsupported REGIMM {w:#x} at {pc:#x}'
            take = {1: (lambda: sx(r[rs], 64) >= 0 if rt == 1 else sx(r[rs], 64) < 0),
                    4: (lambda: r[rs] == r[rt]), 5: (lambda: r[rs] != r[rt]),
                    6: (lambda: sx(r[rs], 64) <= 0), 7: (lambda: sx(r[rs], 64) > 0)}[op]()
            dest = pc + 4 + (imm << 2) if take else pc + 8
        elif op == 9:
            r[rt] = sx(r[rs] + imm, 32) & MASK
        elif op == 0x19:
            r[rt] = (r[rs] + imm) & MASK
        elif op == 0xf:
            r[rt] = sx((w & 0xffff) << 16, 32) & MASK
        elif op == 0xc:
            r[rt] = r[rs] & (w & 0xffff)
        elif op == 0xd:
            r[rt] = r[rs] | (w & 0xffff)
        elif op == 0xe:
            r[rt] = r[rs] ^ (w & 0xffff)
        elif op == 0xa:
            r[rt] = int(sx(r[rs], 64) < imm)
        elif op == 0xb:
            r[rt] = int((r[rs] & MASK) < (imm & MASK))
        elif op in (0x23, 0x24, 0x25, 0x20, 0x37, 0x1e):
            size = {0x23: 4, 0x24: 1, 0x25: 2, 0x20: 1, 0x37: 8, 0x1e: 16}[op]
            v = self.read((r[rs] + imm) & 0xffffffff, size)
            # lw (0x23) sign-extends 32 bits; lb (0x20) sign-extends the byte
            # (8 bits), not 32 — 0xff is -1, not 255.  lbu/lhu are zero-extended.
            r[rt] = (sx(v, 32 if op == 0x23 else 8) if op in (0x23, 0x20) else v) & MASK
        elif op in (0x2b, 0x28, 0x29, 0x3f, 0x1f):
            self.write((r[rs] + imm) & 0xffffffff, {0x2b: 4, 0x28: 1, 0x29: 2, 0x3f: 8, 0x1f: 16}[op], r[rt])
        elif op == 0x31:                              # lwc1: raw 4-byte move into an f-register
            self.f[rt] = self.read((r[rs] + imm) & 0xffffffff, 4)
        elif op == 0x39:                              # swc1: raw 4-byte move out of an f-register
            self.write((r[rs] + imm) & 0xffffffff, 4, self.f[rt])
        elif op == 0x11:                              # COP1 moves (no FP arithmetic in this code)
            if rs == 0x04:                            # mtc1
                self.f[rd] = r[rt] & MASK
            elif rs == 0x00:                          # mfc1
                r[rt] = self.f[rd] & MASK
            elif rs == 0x02:                          # cfc1: FP control register, opaque here
                r[rt] = 0
            elif rs == 0x06:                          # ctc1
                pass
            elif rs == 0x10 and fn == 6:              # mov.s
                self.f[sh] = self.f[rd]
            else:
                raise AssertionError(f'COP1 rs={rs:#x} fn={fn:#x} at {pc:#x}')
        else:
            raise AssertionError(f'opcode {w:#x} at {pc:#x}')
        r[0] = 0
        if dest is not None:
            assert not delay, f'branch in delay slot at {pc:#x}'
            self.step(pc + 4, True)
            if call:
                self.call_hook(dest)
                return pc + 8
            return dest
        return pc + 4

    def run(self, pc, a0, a1, a2, *extra):
        self.r = [0] * 32
        self.r[4], self.r[5], self.r[6] = a0, a1, a2
        assert len(extra) <= 5
        self.r[7:7 + len(extra)] = [v & MASK for v in extra]
        self.r[28] = 0x55c870
        self.r[29] = 0x01fff000
        self.r[31] = 0xfffffff0
        for _ in range(4000000):
            if pc == 0xfffffff0:
                break
            pc = self.step(pc)
        else:
            raise AssertionError('retail function did not return')


class Api(C.Structure):
    _fields_ = [('user', C.c_void_p), ('peek', C.c_void_p),
                ('poke', C.c_void_p), ('call', C.c_void_p)]


PEEK = C.CFUNCTYPE(C.c_int32, C.c_void_p, C.c_int32, C.c_int)
POKE = C.CFUNCTYPE(None, C.c_void_p, C.c_int32, C.c_int, C.c_int32)
CALL = C.CFUNCTYPE(C.c_int32, C.c_void_p, C.c_int32, C.POINTER(C.c_int32))


def interpreter_selftest():
    """Focused checks for the interpreter semantics this verifier relies on.

    lb (op 0x20) sign-extends the loaded byte, so a byte 0xff must read as -1;
    lbu (0x24) zero-extends it (0xff stays 255); lw (0x23) sign-extends 32 bits.
    These are the load semantics used to sample controller/pad bytes and to
    inspect record flags, so a wrong sign extension silently changes branches.
    """
    def enc(op, rs, rt, imm):
        return ((op & 0x3f) << 26) | (rs << 21) | (rt << 16) | (imm & 0xffff)

    def load(op, word):
        w = Retail(b'')
        base = 0x01000000
        w.write(base + 4, 4, word)          # little-endian data at base+4
        pc = base + 0x20
        w.write(pc, 4, enc(op, 8, 9, 4))    # <op> $t1, 4($t0)
        w.r[8] = base
        w.step(pc)
        return sx(w.r[9], 32)

    assert load(0x20, 0xffffffff) == -1, 'lb(0xff) must sign-extend to -1'
    assert load(0x20, 0x00000080) == -128, 'lb(0x80) must sign-extend to -128'
    assert load(0x24, 0xffffffff) == 0xff, 'lbu(0xff) must zero-extend to 255'
    assert load(0x23, 0xffffffff) == -1, 'lw(0xffffffff) must sign-extend to -1'
    assert load(0x25, 0x00008000) == 0x8000, 'lhu(0x8000) must zero-extend'


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--elf', type=Path, default=ROOT / 'orig/SLUS-20836/SLUS_208.36')
    ap.add_argument('--up-only', action='store_true')
    ap.add_argument('--up-n', type=int, default=600)
    ap.add_argument('--msg-only', action='store_true')
    ap.add_argument('--regression-only', action='store_true',
                    help='run only the deterministic pad-mask regression')
    args = ap.parse_args()
    only_reg = args.regression_only
    interpreter_selftest()
    image = args.elf.read_bytes()
    if image[:4] != b'\x7fELF':
        raise SystemExit('not an ELF')

    H = {'w': None}
    real_hits = set()

    def _peek(_u, addr, width):
        return sx(H['w'].read(addr, width), width * 8) if width in (1, 2, 4) else H['w'].read(addr, width)

    def _poke(_u, addr, width, v):
        H['w'].write(addr, width, v)

    def _call(_u, addr, p):
        a = [p[i] for i in range(8)]
        w = H['w']
        n = ARGC.get(addr, 8)
        w.events.append(w._event(addr, a, n))
        return w.reply(addr, a)

    api = Api(None, C.cast(PEEK(_peek), C.c_void_p), C.cast(POKE(_poke), C.c_void_p),
              C.cast(CALL(_call), C.c_void_p))

    with tempfile.TemporaryDirectory(prefix='dw4-li2-') as tmp:
        lib = Path(tmp) / 'loadintf2.so'
        subprocess.run(['cc', '-std=c99', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', '-O2',
                        str(ROOT / 'recovered/frontend/loadintf2.c'),
                        str(ROOT / 'recovered/frontend/selslot.c'),
                        str(ROOT / 'recovered/frontend/textorder.c'),
                        str(ROOT / 'recovered/frontend/completion.c'),
                        '-I' + str(ROOT / 'recovered/frontend'), '-o', str(lib)], check=True)
        cdll = C.CDLL(str(lib))
        update = cdll.dw4_loadintf2_update
        update.argtypes = [C.c_int32, C.c_int32, C.POINTER(Api)]
        message = cdll.dw4_loadintf2_message
        message.argtypes = [C.c_int32, C.c_int32, C.c_int32, C.POINTER(Api)]
        message.restype = C.c_int32

        def c_run(fn, extra, scen, replies):
            w = Harness(image)
            H['w'] = w
            w.scen = scen
            w.rv = replies.get('rv', {})
            w.setup(replies)
            ret = fn(0x01000000, 0x01001000, 0x01008000 if extra else 0, C.byref(api))
            return list(w.events), w.snapshot(), ret

        def retail_run(pc, extra, scen, replies):
            w = Retail(image)
            H['w'] = w
            w.scen = scen
            w.rv = replies.get('rv', {})
            w.setup(replies)
            w.run(pc, 0x01000000, 0x01001000, 0x01008000 if extra else 0)
            real_hits.update(w.real_hits)
            return list(w.events), w.snapshot(), sx(w.r[2], 32)

        def c_run_up(scen, replies):
            w = Harness(image)
            H['w'] = w
            w.scen = scen
            w.rv = replies.get('rv', {})
            w.setup(replies, up=True)
            update(0x01000000, 0x01001000, C.byref(api))
            return list(w.events), w.snapshot()

        def retail_run_up(scen, replies):
            w = Retail(image)
            H['w'] = w
            w.scen = scen
            w.rv = replies.get('rv', {})
            w.setup(replies, up=True)
            w.run(0x3e4750, 0x01000000, 0x01001000, 0)
            real_hits.update(w.real_hits)
            return list(w.events), w.snapshot()

        cases = 0
        for cmd in (() if (args.up_only or only_reg) else (0, 1, 2, 3, 4, 5, 6, 7, 8)):
            for work in (0, WORK):
                for kind in (0, 1):
                    for b11 in (0, 1):
                        for b12 in (0, 1):
                            for f240, f320, ed in ((0, 0, (0, 0)), (1, 2, (1, 0)), (-1, 0, (0, 1))):
                                scen = {'cmd': cmd, 'f240': f240, 'f320': f320}
                                replies = dict(work=work, kind=kind, b10=1, b11=b11, b12=b12,
                                               b13=1, elem_d=ed)
                                exp_ev, exp_mem, exp_ret = retail_run(0x3e9430, (1,), scen, replies)
                                got_ev, got_mem, got_ret = c_run(message, (1,), scen, replies)
                                where = ('msg', cmd, work, kind, b11, b12, f240)
                                assert got_ev == exp_ev, (where, exp_ev, got_ev)
                                assert got_mem == exp_mem, (where, 'memory')
                                assert got_ret == exp_ret, (where, 'ret', exp_ret, got_ret)
                                cases += 1

        import random
        rng = random.Random(0x3e4750)

        def gen(rng, issys=None, p=None):
            replies = dict(
                p=rng.randrange(4) if p is None else p,
                r0f=rng.randrange(2), r0c=rng.randrange(2), r0d=rng.randrange(2),
                r0e=rng.randrange(2), r10=rng.randrange(2), r14=rng.randrange(4),
                ost=rng.choice((0, 1, 2, 3, 4, 5, 6, 7, 8)),
                os28=rng.randrange(5), os2c=rng.randrange(5), os30=rng.randrange(3),
                c10=rng.randrange(2), c11=rng.randrange(2), c12=rng.randrange(2),
                c13=rng.randrange(2), c14=rng.randrange(2), c15=rng.randrange(2),
                c17=rng.randrange(2), c1c=rng.randrange(2), c1d=rng.randrange(2),
                c1e=rng.randrange(2), c18=rng.randrange(3),
                issys=rng.randrange(2) if issys is None else issys,
                st0=rng.choice((0, 1, 2, 3, 4, 5, 6, 7, 8)),
                st1=rng.randrange(6), st2=rng.randrange(6), st3=rng.randrange(3),
                mk30=rng.randrange(2), mki=rng.randrange(4),
                sel36=rng.randrange(2), sel37=rng.randrange(2), sel40=rng.randrange(3),
                sel4c=rng.randrange(3), sel50=0, sel54=0, sel58=0,
                ss24=rng.choice((0, 1, 2)), ss2c=rng.randrange(6),
                ss34=rng.randrange(2), ss35=rng.randrange(2), ss38=rng.randrange(3),
                ss3c=rng.randrange(5), ss44=rng.randrange(2), ss48=rng.randrange(2),
                mr8=rng.randrange(2),
                ds49=rng.randrange(2), df25=rng.randrange(2), df10=rng.randrange(3),
                ns4d=rng.randrange(2), ns4e=rng.randrange(2),
                pad1c=rng.randrange(16), pad20=rng.randrange(16),
                pad48=rng.choice((0, 0x10, 0x20, 0x40, 0x80, 0x2000, 0x4000)),
                pad4c=rng.choice((0, 0x10, 0x20, 0x40, 0x80, 0x2000, 0x4000)),
                padf=rng.randrange(2), flagc=rng.randrange(2), lang=rng.randrange(3),
                mc0c=rng.randrange(2), mc10=rng.randrange(4),
                mc20=rng.choice((0, 4, 7, 9, 10, 12, 3)),
                auxn=rng.randrange(4), auxf=rng.randrange(2),
                cm1c=rng.randrange(0x10000), cm20=rng.randrange(0x10000),
                cm24=rng.randrange(0x10000),
            )
            scen = {'f240': rng.randrange(2), 'f320': rng.randrange(3),
                    'count': rng.randrange(3), 'cmp': rng.randrange(2)}
            rv = {}
            # 0x3e4280/0x3e44d0 are recovered (REAL) so their return value is no
            # longer stubbed; only the still-stubbed helpers get an rv entry.
            for h in (0x3e4210, 0x3e0c40, 0x3e1760, 0x3e2b10,
                      0x3da7c0, 0x3db060, 0x3db780, 0x3dbf90, 0x3def80, 0x3ecb70,
                      0x3e0bb0, 0x3ecb80):
                rv[h] = rng.randrange(3)
            rv[0x3ddb80] = rng.randrange(2)
            rv[0x38f0f0] = rng.randrange(2)
            rv[0x38f220] = rng.randrange(2)
            rv[0x3e4480] = rng.randrange(2)
            for h in (0x3ed050, 0x3ed2e0, 0x3ed650, 0x3edf60, 0x3ecdc0):
                rv[h] = rng.randrange(3)
            replies['rv'] = rv
            return scen, replies

        up_cases = 0
        for _ in range(0 if (args.msg_only or only_reg) else args.up_n):
            scen, replies = gen(rng)
            exp_ev, exp_mem = retail_run_up(scen, replies)
            got_ev, got_mem = c_run_up(scen, replies)
            assert got_ev == exp_ev, ('update', exp_ev, got_ev)
            assert got_mem == exp_mem, ('update memory',)
            up_cases += 1

        # --- edge rows: system gate, pad absent, player 1 ---
        for issys, r0f, pp, ost, st0 in (() if only_reg else (
                (1, 1, 0, 0, 0), (1, 0, 1, 5, 8),
                (0, 0, 0, 8, 0), (0, 1, 1, 2, 1))):
            scen, replies = gen(rng, issys=issys)
            replies['r0f'] = r0f
            replies['p'] = pp
            replies['ost'] = ost
            replies['st0'] = st0
            exp_ev, exp_mem = retail_run_up(scen, replies)
            got_ev, got_mem = c_run_up(scen, replies)
            assert got_ev == exp_ev, ('edge', issys, r0f, pp, ost, st0, exp_ev, got_ev)
            assert got_mem == exp_mem, ('edge memory',)
            up_cases += 1

        # --- multi-step flows: consecutive ticks on one evolving world ------
        # Each tick writes that tick's controller input (the pad block, plus the
        # recorded COMMDLCTRL vec3 the text-operation temporary copies) to the
        # shared world before stepping, while the controller/record state is
        # left to evolve from tick 0.  The comparison runs after every tick, so
        # the first divergent tick and engine call are reported, not just a
        # final mismatch.
        def first_diff(er, ec):
            for k in range(max(len(er), len(ec))):
                a = er[k] if k < len(er) else None
                b = ec[k] if k < len(ec) else None
                if a != b:
                    return k, a, b
            return None

        seen_p = set()
        seen_calls = set()
        flow_events = []
        flow_end = {}
        flow_prog = []

        def run_flow(seq, label):
            flow_events.clear()
            flow_prog.clear()
            seen_p.add(seq[0][1].get('p', 0))
            wr = Retail(image)
            H['w'] = wr
            wr.setup(seq[0][1], up=True)
            wc = Harness(image)
            wc.setup(seq[0][1], up=True)
            for ti, (scen, rep) in enumerate(seq):
                wr.set_pad(rep)
                wc.set_pad(rep)
                wr.scen = scen
                wr.rv = rep['rv']
                wr.run(0x3e4750, 0x01000000, 0x01001000, 0)
                H['w'] = wc
                wc.scen = scen
                wc.rv = rep['rv']
                update(0x01000000, 0x01001000, C.byref(api))
                H['w'] = wr
                er, ec = list(wr.events), list(wc.events)
                assert ec == er, ('multi-step calls', label, ti, first_diff(er, ec))
                assert wc.snapshot() == wr.snapshot(), ('multi-step memory', label, ti)
                seen_calls.update(a for a, _, _ in er)
                flow_events.extend(er)
                flow_prog.append((wr.read(SELSLOT + 0x34, 1),
                                  wr.read(SELSLOT + 0x35, 1),
                                  wr.read(SELSLOT + 0x4c, 4)))
            real_hits.update(wr.real_hits)
            flow_end.clear()
            flow_end.update(wr.snapshot())
            return len(seq)

        for _ in range(0 if (args.msg_only or only_reg) else 40):
            up_cases += run_flow([gen(rng) for _ in range(8)], 'random')

        # --- deliberate, reachable interaction flows ------------------------
        # A tick-0 state that reaches the direction/confirm/cancel handling
        # (outer per-record state 3, list cursor) or the character-select
        # confirm window (outer state 1 -> CTRL state 2), then a scripted pad
        # sequence.  The markers are the pad bits the controller tests in
        # 0x3e4750: 0x10 up, 0x40 down, 0x20/0x80 the cross directions.
        # The face buttons follow the retail handling: 0x4000 (Cross) is
        # confirm/advance and 0x2000 (Circle) is cancel/back -- see the
        # st0==3 block (0x4000 gates the advance, 0x2000 fires SQ_CANCEL) and
        # the st0==2 block (0x4000 confirms the line window).  The flows keep
        # their original pad sequences; the two that were mislabelled confirm/
        # cancel are renamed to the button they actually drive.
        def build_seq(state, pads, p, rv=None):
            seq = []
            for i, pad in enumerate(pads):
                scen, rep = gen(rng, p=p)
                rep = dict(rep)
                if i == 0:
                    rep.update(state)
                rep.update(pad)
                if rv is not None:
                    rep['rv'] = dict(rv[i] if isinstance(rv, list) else rv)
                seq.append((scen, rep))
            return seq

        list_state = dict(ost=3, os28=0, os2c=0, os30=0, r0f=1, st0=3, st1=2, st2=0, st3=0)
        conf_state = dict(ost=1, os28=0, st0=2, st1=0, r0f=1)
        deliberate = [
            # directions on the list cursor: up, down, cross-left, cross-right
            ('directions', list_state, 1,
             [dict(pad48=0x10), dict(pad48=0x40), dict(pad48=0x20), dict(pad48=0x80),
              dict(pad48=0x10), dict(pad48=0x40), dict(pad48=0), dict(pad48=0x20)]),
            # Cross confirm/advance (player index non-zero), held then released
            ('cross-confirm', list_state, 2,
             [dict(pad48=0x4000), dict(pad48=0x4000), dict(pad48=0), dict(pad48=0x4000),
              dict(pad48=0), dict(pad48=0x4000), dict(pad48=0), dict(pad48=0)]),
            # confirm is gated on P32(frame+8) != 0, so player 0 must not advance
            ('cross-confirm-p0', list_state, 0, [dict(pad48=0x4000)] * 8),
            # Circle cancel / back
            ('circle-cancel', list_state, 3,
             [dict(pad48=0x2000), dict(pad48=0), dict(pad48=0x2000), dict(pad48=0),
              dict(pad48=0x2000), dict(pad48=0), dict(pad48=0x2000), dict(pad48=0)]),
            # delayed completion: the pad held across the ticks the stub
            # reports the model flow still running, then released
            ('delayed', conf_state, 1,
             [dict(pad48=0x2000), dict(pad48=0x2000), dict(pad48=0x2000), dict(pad48=0),
              dict(pad48=0x2000), dict(pad48=0), dict(pad48=0), dict(pad48=0x2000)]),
            # backtracking: the two face buttons alternating, twice
            ('backtrack', conf_state, 2,
             [dict(pad48=0x2000), dict(pad48=0x4000), dict(pad48=0x2000), dict(pad48=0x4000),
              dict(pad48=0), dict(pad48=0x2000), dict(pad48=0x4000), dict(pad48=0)]),
        ]
        # --- deliberate slot-selection interaction flows ---------------------
        # CTRL state 6 runs the recovered beNDMWLoadIntf2SelSlot helpers
        # (recovered/frontend/selslot.c).  The state below is the entry into the
        # slot grid (outer per-record state 0, CTRL st0 6); the pad markers are
        # the bits ss_update reads (0x10 up, 0x40 down, 0x20/0x80 cross,
        # 0x4000 confirm/select, 0x2000 cancel/back).  Completion is NOT forced:
        # 0x3e4280/0x3e44d0 (the CommMdlCtrl model-queue emptiness) are recovered
        # and read the queue counts wired by setup_up/set_pad, so the flows drive
        # the open through the `cmon`/`cmcn` counts the accessors actually read.
        slot_rv = {}
        for h in (0x3e4210, 0x3e0c40, 0x3e1760, 0x3e2b10,
                  0x3da7c0, 0x3db060, 0x3db780, 0x3dbf90, 0x3def80, 0x3ecb70,
                  0x3e0bb0, 0x3ecb80, 0x3ddb80, 0x38f0f0, 0x38f220, 0x3ecb90):
            slot_rv[h] = 0
        slot_rv[0x3e4480] = 1          # mark state (still a stub)
        slot_rv[0x3e4210] = 1
        slot_rv[0x3da7c0] = 1
        # A complete, fixed tick-0 record so the slot flows behave identically
        # in every --mode (no dependence on the rng draw order).
        slot_base = dict(
            p=1, r0f=1, r0c=0, r0d=0, r0e=0, r10=0, r14=0,
            ost=0, os28=0, os2c=0, os30=0,
            c10=0, c11=0, c12=0, c13=0, c14=0, c15=0, c17=0, c1c=0, c1d=0, c1e=0, c18=0,
            issys=0, st0=6, st1=0, st2=0, st3=0,
            mk30=0, mki=0, sel36=0, sel37=0, sel40=1, sel4c=0, sel50=0, sel54=0, sel58=0,
            ds49=0, df25=0, df10=0, ns4d=0, ns4e=0,
            pad1c=0, pad20=0, pad48=0, pad4c=0, padf=0,
            flagc=0, lang=0, mc0c=0, mc10=0, mc20=0, auxn=0, auxf=0,
            cm1c=0, cm20=0, cm24=0,
            ss24=0, ss2c=2, ss34=0, ss35=0, ss38=0, ss3c=0, ss44=0, ss48=0, mr8=1,
        )
        slot_fresh = dict(slot_base)
        slot_open = dict(slot_base, ss34=1, sel4c=1, st1=1, st2=0, sel50=0)
        # CTRL state 6, sub-state 1/1 with the character mode (REC+0x14) set
        # reaches ss_pub_cursor (0x3e2a80): the "publish the slot cursor line"
        # step the update runs while the slot grid is settling.
        slot_cursor = dict(slot_base, ss34=1, sel4c=1, st1=1, st2=1, st3=1, r14=1)

        def build_slot_seq(state, pads, p, rv):
            seq = []
            for i, pad in enumerate(pads):
                rep = dict(state if i == 0 else slot_base)
                rep['p'] = p
                rep.update(pad)
                rep['rv'] = dict(rv[i] if isinstance(rv, list) else rv)
                seq.append((dict(f240=0, f320=0, count=0, cmp=0), rep))
            return seq

        slot_deliberate = [
            ('slot-entry', slot_fresh, 1, [dict(pad48=0)] * 8, slot_rv),
            ('slot-move', slot_open, 1,
             [dict(pad48=0x40), dict(pad48=0x10), dict(pad48=0x40), dict(pad48=0x40),
              dict(pad48=0x10), dict(pad48=0x40), dict(pad48=0), dict(pad48=0x40)],
             slot_rv),
            ('slot-confirm', slot_open, 2,
             [dict(pad48=0x4000), dict(pad48=0x4000), dict(pad48=0), dict(pad48=0x4000),
              dict(pad48=0), dict(pad48=0x4000), dict(pad48=0), dict(pad48=0)],
             slot_rv),
            ('slot-cancel', slot_open, 3,
             [dict(pad48=0x2000), dict(pad48=0), dict(pad48=0x2000), dict(pad48=0),
              dict(pad48=0x2000), dict(pad48=0), dict(pad48=0x2000), dict(pad48=0)],
             slot_rv),
            ('slot-backtrack', slot_open, 1,
             [dict(pad48=0x4000), dict(pad48=0x2000), dict(pad48=0x4000), dict(pad48=0x2000),
              dict(pad48=0), dict(pad48=0x4000), dict(pad48=0x2000), dict(pad48=0)],
             slot_rv),
            ('slot-delayed', slot_fresh, 1,
             [dict(pad48=0, cmon=1)] * 4 + [dict(pad48=0, cmon=0)] * 4, slot_rv),
            ('slot-cursor', slot_cursor, 1, [dict(pad48=0)] * 8, slot_rv),
            # waiting: the open queue never drains, so the screen never opens
            ('slot-stall', slot_fresh, 1, [dict(pad48=0, cmon=1)] * 8, slot_rv),
            # completion: the settle path (sel50==2) drains after three ticks
            ('slot-complete', dict(slot_open, sel50=2), 1,
             [dict(pad48=0, cmon=1)] * 3 + [dict(pad48=0, cmon=0)] * 5, slot_rv),
        ]
        for label, state, p, pads in (() if only_reg else deliberate):
            up_cases += run_flow(build_seq(state, pads, p), label)
        slot_seen = {}
        slot_end = {}
        slot_prog = {}
        for label, state, p, pads, rv in (() if only_reg else slot_deliberate):
            up_cases += run_flow(build_slot_seq(state, pads, p, rv), label)
            if not only_reg:
                slot_seen[label] = list(flow_events)
                slot_end[label] = dict(flow_end)
                slot_prog[label] = list(flow_prog)
        def bmap(mem, addr, size=4):
            return sum(mem.get(addr + i, 0) << (8 * i) for i in range(size))

        if not only_reg:
            assert seen_p == {0, 1, 2, 3}, ('player-index coverage', sorted(seen_p))
            # 0x3e4480 (mark publish/close) is only ever reached *inside* the
            # recovered helpers, so seeing it proves the real helper
            # instructions ran on both sides; the per-flow argument checks below
            # pin the entry / movement / confirm / cancel / backtracking /
            # delayed-completion paths (SQ_MOVE and SQ_CANCEL are 0x516e48 and
            # 0x516d50).
            assert 0x3e4480 in seen_calls, ('slot helpers not exercised',
                                            sorted(hex(a) for a in seen_calls))

            def slot_has(label, addr, sub=None):
                for a, args, _ in slot_seen.get(label, ()):
                    if a == addr and (sub is None or args[3] == sub):
                        return True
                return False

            assert slot_has('slot-entry', 0x3e3e00), 'slot entry must open the grid'
            assert slot_has('slot-move', 0x3e4030, 0x516e48), 'slot move must emit SQ_MOVE'
            assert slot_has('slot-cancel', 0x3e4030, 0x516d50), 'slot cancel must emit SQ_CANCEL'
            for label, token in (('slot-move', 0x516e48), ('slot-cancel', 0x516d50)):
                operations = [a for pc, a, _ in slot_seen[label]
                              if pc == 0x3e4030 and a[3] == token]
                assert operations and all(a[4] == 1 for a in operations), \
                    (label, 'movement/cancel must request tracked completion', operations)
            # 0x3ee190 is recovered (REAL), so the selection is no longer a call
            # event: it shows up as the SS_T_ON cursor publish it accompanies and
            # as the armed per-player records (below), not a 0x3ee190 event.
            assert slot_has('slot-confirm', 0x3e4030, 0x5171f0), 'slot confirm must publish the selection'
            assert slot_has('slot-backtrack', 0x3e4030, 0x5171f0), 'slot backtrack must select'
            assert slot_has('slot-delayed', 0x3e3e00), 'slot delayed must still open'

            endval = lambda label, addr, size=4: bmap(slot_end.get(label, {}), addr, size)

            # Completion is driven by the recovered CommMdlCtrl queue accessors
            # (0x3e4280/0x3e44d0), not a forced return.  The open path
            # (SELSLOT+0x34 isOpen) advances exactly when the open queue drains:
            # slot-entry opens on tick 3, slot-delayed two ticks later (the queue
            # holds until tick 4), and slot-stall never opens because the queue
            # never drains.  `prog` is the per-tick (isOpen, isSelect, st0) trace,
            # read from the *retail* side.
            def col(label, i):
                return [p[i] for p in slot_prog[label]]

            assert col('slot-entry', 0)[:3] == [0, 0, 0] and col('slot-entry', 0)[3] == 1, \
                'slot entry must open on tick 3'
            assert col('slot-delayed', 0)[:5] == [0, 0, 0, 0, 0] and col('slot-delayed', 0)[5] == 1, \
                'slot delayed-open must wait for the queue to drain'
            assert col('slot-stall', 0) == [0] * 8, 'slot stall must never open'
            assert col('slot-stall', 2) == [0] * 8, 'slot stall must not advance st0'
            # The settle path (sel50==2, SELSLOT+0x35 isSelect) likewise follows
            # the queue: it settles on the tick the queue empties.
            assert col('slot-complete', 1)[:3] == [0, 0, 0] and col('slot-complete', 1)[3] == 1, \
                'slot completion must settle when the queue drains'
            assert endval('slot-complete', SELSLOT + 0x4c) == 2, 'slot completion must advance st0'
            assert endval('slot-cancel', SELSLOT + 0x36, 1) == 1, 'slot cancel must flag the cancel'
            # ds_select (0x3ee190) arms every per-player record and clears the
            # selected one; the extra records (players != p) must show it ran.
            assert endval('slot-confirm', RECALT + 0x24) == 1, 'ds_select must arm the records'
            # The text-order publish trio (0x3ebce0/0x3ebe00/0x3ec050) runs as
            # real instructions on the retail side and as recovered C on the C
            # side; its leaf callees must therefore show up in the slot flows.
            assert slot_has('slot-entry', 0x38d860), 'text-order line must publish (0x38d860)'
            assert slot_has('slot-entry', 0x38e060), 'text-order line must publish (0x38e060)'
            assert slot_has('slot-entry', 0x389ff0), 'text-order open must fire its anim token'
            assert sum(slot_has(l, 0x389ff0) for l in slot_seen) >= 2, \
                'text-order anim token must fire across several flows'
            # Every recovered body was entered on the retail side, i.e. the
            # interpreter executed its ORIGINAL instructions rather than a stub.
            # (Only the full matrix walks every helper; --msg-only runs neither
            # the random nor the edge update flows.)
            if not args.msg_only:
                assert REAL <= real_hits, ('recovered bodies not run on retail',
                                           sorted(hex(a) for a in REAL - real_hits))

        # --- deterministic minimized regression -----------------------------
        # Frozen reduction of the flow the wider pad masks exposed: during
        # outer per-record state 1, os28==0, CTRL st0==2, retail executes
        # 0x3e4e90-0x3e4eac which resets the *per-player record* (v0 from
        # 0x3e9240) and leaves CTRL at state 2, so the case-0 dispatch falls
        # through to state 2 and emits the j_linewin01 open
        # (0x3e3e00(JLINEWIN01)).  The pre-fix C wrote CTRL via SET_ST(0) and
        # emitted 0x3e3e00(JCHRSELBASE) instead.  One tick is the minimum that
        # diverges.  It also pins the 0x3e9220->0x3e3e00 temporary contract:
        # the 12-byte payload is COMMDLCTRL's +0x1c vec3, read at each side's
        # own scratch pointer.
        reg_rep = dict(
            p=0, r0f=1, r0c=0, r0d=0, r0e=0, r10=0, r14=1,
            ost=1, os28=0, os2c=1, os30=2,
            c10=0, c11=1, c12=0, c13=0, c14=1, c15=0, c17=0, c1c=1, c1d=1, c1e=1, c18=2,
            issys=0, st0=2, st1=0, st2=3, st3=2,
            mk30=0, mki=1, sel36=1, sel37=0, sel40=1, sel4c=2, sel50=0, sel54=0, sel58=0,
            ds49=1, df25=1, df10=2, ns4d=1, ns4e=1,
            pad1c=0, pad20=0, pad48=0x40, pad4c=0x80, padf=0,
            flagc=1, lang=2, mc0c=0, mc10=1, mc20=0, auxn=3, auxf=0,
            cm1c=0x11, cm20=0x22, cm24=0x33,
        )
        reg_scen = {'f240': 1, 'f320': 0, 'count': 1, 'cmp': 0}
        reg_rep['rv'] = {h: 0 for h in (
            0x3e4210, 0x3e0c40, 0x3e1760, 0x3e2b10,
            0x3da7c0, 0x3db060, 0x3db780, 0x3dbf90, 0x3def80, 0x3ecb70,
            0x3e0bb0, 0x3ecb80, 0x3ddb80, 0x38f0f0, 0x38f220,
            0x3ed050, 0x3ed2e0, 0x3ed650, 0x3edf60, 0x3ecdc0)}
        reg_exp_ev, reg_exp_mem = retail_run_up(reg_scen, reg_rep)
        reg_got_ev, reg_got_mem = c_run_up(reg_scen, reg_rep)
        assert reg_got_ev == reg_exp_ev, ('regression', first_diff(reg_exp_ev, reg_got_ev))
        assert reg_got_mem == reg_exp_mem, ('regression memory',)
        line = [ev for ev in reg_got_ev if ev[0] == 0x3e3e00 and ev[1][2] == 0x517370]
        assert line, 'regression must emit the j_linewin01 text-operation call'
        assert all(ev[1][2] != 0x517328 for ev in reg_got_ev
                   if ev[0] == 0x3e3e00), 'regression must not take the j_chrselbase path'
        assert line[0][2] == (0x11, 0x22, 0x33), ('temp payload', line[0][2])
        up_cases += 1

        # --- focused direct cases -------------------------------------------
        # The screen flows reach the text-order and completion functions only
        # through their callers; these drive them directly to cover the branches
        # the flows never take -- a missing id, the flag-controlled next-entry
        # publish, the close variant, and both queue states -- comparing the
        # recovered bodies' calls, side effects and return values against retail.
        def bind(fn, argc, res=False):
            fn.argtypes = [C.POINTER(Api)] + [C.c_int32] * argc
            fn.restype = C.c_int32 if res else None
            return fn

        c_to_configure = bind(cdll.to_configure, 6)
        c_to_configure_font = bind(cdll.to_configure_font, 7)
        c_to_clear_font = bind(cdll.to_clear_font, 4)
        c_to_set = bind(cdll.to_set, 3)
        c_to_pub = bind(cdll.to_pub, 2)
        c_cm_open = bind(cdll.cm_open_empty, 1, True)
        c_cm_close = bind(cdll.cm_close_empty, 1, True)
        c_ds_sel = bind(cdll.ds_select, 2)

        def dsetup(w, cmon=0, cmcn=0, state=None):
            w.scen = {}
            w.rebind_text = (state or {}).get('rebind_text', False)
            w.rv = {}
            w.setup(dict({'p': 0, 'cmon': cmon, 'cmcn': cmcn}, **(state or {})), up=True)
            w.write(TEXTORDER + 0x10, 4, MSG)         # messenger
            w.write(TEXTORDER + 0x14, 4, 0x01050000)  # lua node
            return w

        direct_cases = 0
        text_executed = set()

        def direct(name, pc, args, cfn, ret=False, cmon=0, cmcn=0, state=None):
            nonlocal direct_cases
            wr = Retail(image)
            H['w'] = wr
            dsetup(wr, cmon, cmcn, state)
            wr.run(pc, args[0], args[1] if len(args) > 1 else 0,
                   args[2] if len(args) > 2 else 0, *args[3:])
            text_executed.update(wr.executed)
            exp_ev, exp_mem, exp_ret = list(wr.events), wr.snapshot(), sx(wr.r[2], 32)
            wc = Harness(image)
            H['w'] = wc
            dsetup(wc, cmon, cmcn, state)
            got_ret = cfn(C.byref(api), *args)
            got_ev, got_mem = list(wc.events), wc.snapshot()
            assert got_ev == exp_ev, ('direct calls', name, first_diff(exp_ev, got_ev))
            assert got_mem == exp_mem, ('direct memory', name)
            if ret:
                assert int(got_ret) == exp_ret, ('direct ret', name, exp_ret, int(got_ret))
            direct_cases += 1
            return exp_ev, exp_mem, exp_ret

        def ncall(ev, addr):
            return sum(1 for a, _, _ in ev if a == addr)

        mval = bmap

        # All alignment/colour branches, including preserve/unknown modes;
        # wrappers execute the same body with an indexed font and shifted ABI.
        for align in (-1, 0, 1, 2, 3):
            for colour in (-1, 0, 1, 2, 3):
                for font_set in range(4):
                    for font_index in (0, 1, 19):
                        font = Harness(image).read(0x4ceb30 + font_set*0x50 + font_index*4, 4)
                        argv = [TEXTORDER, 0x5173c8, font, 0x517a00, align, colour]
                        ev, _, _ = direct('text-configure', 0x3eba10, argv, c_to_configure)
                        wrapper = [TEXTORDER, argv[1], font_set, font_index, argv[3], align, colour]
                        wrapped, _, _ = direct('text-font-configure', 0x3ebd70, wrapper, c_to_configure_font)
                        assert ev == wrapped, 'indexed wrapper must preserve text command stream'
                        commands = [a[1] for pc, a, _ in ev if pc == 0x38e060]
                        expected = ([0x5179c0] if align in (0, 1, 2) else [])
                        expected += ([0x5179d8 + colour*0x10] if colour in (0, 1) else [])
                        expected += [0x5179f8, 0x517a08]
                        assert commands == expected, (align, colour, commands)
        for font_set in range(4):
            for font_index in (0, 1, 19):
                ev, _, _ = direct('text-font-clear', 0x3ebdc0,
                    [TEXTORDER, 0x5173c8, font_set, font_index], c_to_clear_font)
                assert [a[1] for pc, a, _ in ev if pc == 0x38e060] == [0x517a08]
                assert [a[1] for pc, a, _ in ev if pc == 0x38f830][-1] == 0x517a10

        # Messenger callbacks may rebind owner+0x10; each call reloads it.
        for pc, argv, fn in (
            (0x3eba10, [TEXTORDER, 0x5173c8, 0x517a00, 0x517a00, 1, 0], c_to_configure),
            (0x3ebd70, [TEXTORDER, 0x5173c8, 0, 0, 0x517a00, 1, 0], c_to_configure_font),
            (0x3ebdc0, [TEXTORDER, 0x5173c8, 0, 0], c_to_clear_font),
        ):
            ev, _, _ = direct('text-messenger-rebind', pc, argv, fn,
                              state={'rebind_text': True})
            assert [a[0] for _, a, _ in ev] == [MSG + 4*i for i in range(len(ev))]
        text_body = (set(range(0x3eba10, 0x3ebcd4, 4)) |
                     set(range(0x3ebd70, 0x3ebdb8, 4)) |
                     set(range(0x3ebdc0, 0x3ebdfc, 4)))
        # Unconditional branches skip these padding nops on all paths.
        unreachable = {0x3eba64, 0x3ebb8c}
        assert text_body - unreachable <= text_executed, sorted(text_body - unreachable - text_executed)
        print(f'{len(text_body - unreachable)} new text-body instructions covered; '
              f'{len(unreachable)} unreachable padding instructions excluded')

        # 1. a present id, flag 0: publishes its whole line list (table entry
        #    0x100c, 2 lines), latches the global text pointer, and fires the
        #    on-token (id & 0xf000 == 0x1000).
        ev, mem, _ = direct('order-present', 0x3ebe00, [TEXTORDER, 0x100c, 0], c_to_set)
        assert ncall(ev, 0x38d860) == 2, 'present id must publish its whole line list'
        assert ncall(ev, 0x389ff0) == 1 and \
            [x[1] for a, x, _ in ev if a == 0x389ff0] == [0x517a28], \
            'id & 0xf000 == 0x1000 must fire the on-token'
        assert mval(mem, 0x58a220) != 0, 'present id must latch the global text pointer'

        # 2. flag-controlled next-entry handling: table entry 0x100503 carries
        #    bit 20, so flag 1 latches the FOLLOWING entry's text pointer and
        #    repeats the animation dispatch.  Retail does *not* publish that
        #    entry's line list, so the 0x38d860 count is unchanged.
        ev0, mem0, _ = direct('order-id0', 0x3ebe00, [TEXTORDER, 0x503, 0], c_to_set)
        ev1, mem1, _ = direct('order-id1', 0x3ebe00, [TEXTORDER, 0x503, 1], c_to_set)

        def limg(addr, size=4):
            o = addr - 0x100000 + 0x80
            return int.from_bytes(image[o:o + size], 'little')

        assert ncall(ev0, 0x38d860) == 6, 'entry 0x100503 has a 6-line list'
        assert ncall(ev0, 0x389ff0) == 1 and ncall(ev1, 0x389ff0) == 2, \
            'flag=1 must repeat the animation dispatch for the next entry'
        assert [x[1] for a, x, _ in ev0 if a == 0x389ff0] == [0x517a18], \
            'id & 0xf000 == 0 must fire the off-token'
        assert ncall(ev1, 0x38d860) == ncall(ev0, 0x38d860), \
            'flag=1 must not publish the next entry line list'
        assert mval(mem0, 0x58a220) == limg(0x4cda44 + 26 * 0xc), \
            'flag=0 must latch the entry text pointer'
        assert mval(mem1, 0x58a220) == limg(0x4cda44 + 27 * 0xc), \
            'flag=1 must latch the next entry text pointer'

        # 3. a missing id: the sentinel scan (0xffffffff) returns with no calls
        #    and no writes at all.
        ev, mem, _ = direct('order-missing', 0x3ebe00, [TEXTORDER, 0x7ffff, 0], c_to_set)
        assert ev == [], ('missing id must publish nothing', ev)
        assert mval(mem, 0x58a220) == 0 and mval(mem, 0x58a1e0) == 0, \
            'missing id must not touch the global text pointers'

        # 4. the close variant (0x3ec050): line list only -- no global latch and
        #    no animation token.
        ev, mem, _ = direct('order-close', 0x3ec050, [TEXTORDER, 0x100c], c_to_pub)
        assert ncall(ev, 0x38d860) >= 1, 'close must publish the line list'
        assert not any(a == 0x389ff0 for a, _, _ in ev), 'close must not fire the anim token'
        assert mval(mem, 0x58a220) == 0, 'close must not latch the global text pointer'

        # 5. the completion accessors compute the boolean from the queue count
        #    the harness sets ([cm+0x14]/[cm+0x18] -> +8), not a forced return.
        for cnt, want in ((0, 1), (3, 0)):
            _, _, r = direct(f'open-empty-{cnt}', 0x3e4280, [CM], c_cm_open, ret=True, cmon=cnt)
            assert r == want, ('cm_open_empty', cnt, r)
            _, _, r = direct(f'close-empty-{cnt}', 0x3e44d0, [CM], c_cm_close, ret=True, cmcn=cnt)
            assert r == want, ('cm_close_empty', cnt, r)

        # 6. the selection (0x3ee190) arms all four per-player records and clears
        #    the selected one (player 0's record is REC, player 2's is RECALT+0x80).
        _, mem, _ = direct('ds-select', 0x3ee190, [INTF, 2], c_ds_sel)
        assert mem.get(REC + 0x24, 0) == 1, 'ds_select must arm record 0'
        assert mem.get(REC + 0x0f, 1) == 0, 'ds_select must clear record 0 run byte'
        assert mem.get(RECALT + 2 * 0x40 + 0x24, 0) == 0, 'ds_select must clear the selectee'
        assert mem.get(RECALT + 2 * 0x40 + 0x0f, 1) == 1, 'ds_select must set the selectee run byte'

        # Signature regression: the first close reused t0=1 from the phase
        # comparison; omitting its fifth argument silently disabled tracking.
        c_ss_marks = bind(cdll.ss_marks, 1, True)
        ev, _, _ = direct('slot-tracked-close', 0x3e2b10, [SELSLOT], c_ss_marks,
                          ret=True, state=dict(sel4c=2, sel50=0, ss24=0, ss44=0, ss38=0))
        closes = [a for pc, a, _ in ev if pc == 0x3e42a0][:3]
        assert len(closes) == 3 and all(a[4] == 1 for a in closes), closes

        print(f'{direct_cases} focused direct cases agree: text configuration/font/rebinding, present/missing/'
              f'next-entry/close branches, completion/selection and tracked slot close')
        print(f'{cases} retail-vs-C load-interface message cases agree: ordered engine '
              f'calls, every non-stack byte write, and the return value')
        print(f'{up_cases} retail-vs-C load-interface update cases agree: ordered engine '
              f'calls, every non-stack byte write, and the 0x3e3e00 temporary payload '
              f'(40 random + {len(deliberate) + len(slot_deliberate)} deliberate 8-tick flows + 1 regression; '
              f'player indices {sorted(seen_p)})')
        print(f'{len(REAL)} recovered helpers executed their original instructions on the '
              f'retail side: {", ".join(hex(a) for a in sorted(REAL))}')


if __name__ == '__main__':
    main()
