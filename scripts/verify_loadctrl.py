#!/usr/bin/env python3
"""Compare the recovered load-controller reference with retail execution.

No game bytes are embedded.  Loads the user's retail ELF and runs the original
MIPS instructions of

    0x003f1a80  beNDMWLoadCtrl2::vfunc_31   (update)
    0x003f2490  beNDMWLoadCtrl2::vfunc_34   (RUN/GAMESTART message handler)

through a restricted integer R5900 interpreter.  The recovered C in
recovered/frontend/loadctrl.c runs against the *same* world (peek/poke/call),
so the two are compared on the ordered engine calls (with their meaningful
arguments) and on every non-stack byte written.

This verifies control flow and the engine call stream, not the engine's own
implementations, rendering, timing, or reference-lifetime side effects; the
callees are stubbed.
"""
import argparse
import ctypes as C
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
MASK = (1 << 64) - 1

SELF, FRAME, INFO, WORK = 0x01000000, 0x01001000, 0x01008000, 0x0100a000
CTRL, INTF, CM = 0x01002000, 0x01003000, 0x0100d000
FLAGWORK, ELEMS, ELEM0 = 0x01004000, 0x01005000, 0x01006000
MCUTIL, GAMERAM = 0x01007000, 0x01010000
NODE, O1, O2, SYS = 0x0100e000, 0x0100f000, 0x0100f800, 0x0100b000
GP_FLAG = 0x554c14
STACK_LO = 0x01f00000


def sx(n, bits):
    n &= (1 << bits) - 1
    return n - (1 << bits) if n >> (bits - 1) else n


# (address, number of meaningful argument registers) for every stubbed callee.
ARGC = {
    0x301000: 1, 0x2f88e0: 1, 0x36ae80: 1, 0x3c7a40: 1, 0x3c4be0: 1,
    0x3c6830: 1, 0x3c56b0: 1, 0x2ff820: 1, 0x3c7d40: 0,
    0x236f80: 2, 0x389ff0: 3, 0x3022c0: 3, 0x38d4a0: 3, 0x38e670: 3,
    0x38f240: 1, 0x38f250: 2, 0x38e060: 2, 0x38e5d0: 2,
    0x38f320: 2, 0x38f220: 2, 0x38f830: 2, 0x3a9220: 2, 0x3a9280: 2, 0x38f800: 2,
    0x38d860: 4, 0x38e5f0: 5,
    0x3f1270: 1, 0x3f12f0: 1, 0x3f1380: 1, 0x3f13d0: 1,
    0x3f0ed0: 3, 0x3ecc60: 1, 0x301e30: 2, 0x38f660: 1, 0x38f670: 2,
}


class Harness:
    """World memory + the one stubbed-engine reply function, shared by the
    retail interpreter and the recovered C."""

    def __init__(self, image):
        self.image = image
        self.mem = {}
        self.events = []
        self.counter = {}
        self.scen = {}

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
        if addr in (0x301000, 0x2f88e0):
            return SYS
        if addr == 0x36ae80:
            return WORK
        if addr == 0x3c7a40:
            return CTRL
        if addr == 0x3c4be0:
            return CM
        if addr == 0x3c6830:
            return self.fresh('o1', O1)
        if addr == 0x3c56b0:
            return self.fresh('o2', O2)
        if addr == 0x236f80:
            return NODE + (0x40 if a[1] == 0x589208 else 0)
        if addr == 0x3a9220:
            return NODE + 0x200 + (a[1] & 7) * 0x20
        if addr == 0x3a9280:
            return NODE + 0x400
        if addr == 0x38f800:
            return GAMERAM
        if addr == 0x38d4a0:
            return s.get('cmd', 0)
        for key, name in ((0x38f240, 'f240'), (0x38f320, 'f320'), (0x38f220, 'f220'),
                          (0x38f660, 'f660'), (0x3f13d0, 'f13d0'), (0x3f12f0, 'f12f0')):
            if addr == key:
                return s.get(name, 0)
        return 0

    def call(self, addr, a):
        n = ARGC.get(addr)
        if n is None:
            raise AssertionError(f'unknown callee {addr:#x}')
        self.events.append((addr, tuple(a[:n]) + (0,) * (5 - n)))
        return self.reply(addr, a)

    def setup(self, r):
        w32 = lambda a, v: self.write(a, 4, v)
        w8 = lambda a, v: self.write(a, 1, v)
        w32(SELF + 0x0c, SYS)
        w32(SELF + 0x14, 0x01020000)
        w32(SELF + 0x24, r['cam'])
        w32(SELF + 0x28, r['light'])
        w32(FRAME + 0x18, r['run'])
        w32(FRAME + 0x28, r['work'])
        w32(INFO + 0x14, 0x01021000)
        w32(CTRL + 0x10, r['isTitle'])
        w32(CTRL + 0x14, r['st0'])
        w32(CTRL + 0x18, r['st1'])
        w32(CTRL + 0x1c, r['st2'])
        w32(CTRL + 0x20, r['st3'])
        w32(INTF + 0x28, FLAGWORK)
        w32(INTF + 0x30, r['intfStat'])
        w32(INTF + 0x34, MCUTIL)
        w32(INTF + 0x3c, r['difficult'])
        w32(FLAGWORK + 0x10, ELEMS)
        for i in range(4):
            w32(ELEMS + i * 4, ELEM0 + i * 0x100)
            w8(ELEM0 + i * 0x100 + 0xd, r['use'][i])
            w8(ELEM0 + i * 0x100 + 0xe, r['done'][i])
        w8(NODE + 0x400 + 0xc, r['isuse'])
        w8(GP_FLAG, 1)
        # globals the controller dereferences (retail `lw` of a named base).
        for a in (0x585be0, 0x587110, 0x587d08, 0x589208):
            w32(a, a)

    def snapshot(self):
        return {a: v for a, v in self.mem.items() if a < STACK_LO}


class Retail(Harness):
    def __init__(self, image):
        super().__init__(image)
        self.r = [0] * 32

    def call_hook(self, address):
        a = [sx(self.r[4 + i], 32) for i in range(5)]
        self.r[2] = self.call(address, a) & MASK

    def step(self, pc, delay=False):
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
                    call = True
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
                call = True
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

    def run(self, pc, a0, a1, a2):
        self.r = [0] * 32
        self.r[4], self.r[5], self.r[6] = a0, a1, a2
        self.r[28] = 0x55c870
        self.r[29] = 0x01fff000
        self.r[31] = 0xfffffff0
        for _ in range(400000):
            if pc == 0xfffffff0:
                break
            pc = self.step(pc)
        else:
            raise AssertionError('retail function did not return')


class LoadApi(C.Structure):
    _fields_ = [('user', C.c_void_p), ('peek', C.c_void_p),
                ('poke', C.c_void_p), ('call', C.c_void_p)]


PEEK = C.CFUNCTYPE(C.c_int32, C.c_void_p, C.c_int32, C.c_int)
POKE = C.CFUNCTYPE(None, C.c_void_p, C.c_int32, C.c_int, C.c_int32)
CALL = C.CFUNCTYPE(C.c_int32, C.c_void_p, C.c_int32, C.POINTER(C.c_int32))


def interpreter_selftest():
    """Focused checks for the interpreter semantics this verifier relies on.

    lb (op 0x20) sign-extends the loaded byte, so a byte 0xff must read as -1;
    lbu (0x24) zero-extends it; lw (0x23) sign-extends 32 bits.  The update
    reads record/state bytes through lb, so a wrong sign extension changes
    control flow indirectly.
    """
    def enc(op, rs, rt, imm):
        return ((op & 0x3f) << 26) | (rs << 21) | (rt << 16) | (imm & 0xffff)

    def load(op, word):
        w = Retail(b'')
        base = 0x01000000
        w.write(base + 4, 4, word)
        pc = base + 0x20
        w.write(pc, 4, enc(op, 8, 9, 4))
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
    args = ap.parse_args()
    interpreter_selftest()
    image = args.elf.read_bytes()
    if image[:4] != b'\x7fELF':
        raise SystemExit('not an ELF')

    H = {'w': None}

    def _peek(_u, addr, width):
        return sx(H['w'].read(addr, width), width * 8) if width in (1, 2, 4) else H['w'].read(addr, width)

    def _poke(_u, addr, width, v):
        H['w'].write(addr, width, v)

    def _call(_u, addr, p):
        a = [p[0], p[1], p[2], p[3], p[4]]
        n = ARGC.get(addr, 5)
        H['w'].events.append((addr, tuple(a[:n]) + (0,) * (5 - n)))
        return H['w'].reply(addr, a)

    api = LoadApi(None, C.cast(PEEK(_peek), C.c_void_p), C.cast(POKE(_poke), C.c_void_p),
                  C.cast(CALL(_call), C.c_void_p))

    with tempfile.TemporaryDirectory(prefix='dw4-lc-') as tmp:
        lib = Path(tmp) / 'loadctrl.so'
        subprocess.run(['cc', '-std=c99', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', '-O2',
                        str(ROOT / 'recovered/frontend/loadctrl.c'),
                        '-I' + str(ROOT / 'recovered/frontend'), '-o', str(lib)], check=True)
        cdll = C.CDLL(str(lib))
        update = cdll.dw4_loadctrl_update
        update.argtypes = [C.c_int32, C.c_int32, C.POINTER(LoadApi)]
        message = cdll.dw4_loadctrl_message
        message.argtypes = [C.c_int32, C.c_int32, C.c_int32, C.POINTER(LoadApi)]
        message.restype = C.c_int32

        def c_run(fn, extra, scen, replies):
            w = Harness(image)
            H['w'] = w
            w.scen = scen
            w.setup(replies)
            fn(SELF, FRAME, *extra, C.byref(api))
            return list(w.events), w.snapshot()

        def retail_run(pc, extra, scen, replies):
            w = Retail(image)
            H['w'] = w
            w.scen = scen
            w.setup(replies)
            w.run(pc, SELF, FRAME, INFO if extra else 0)
            return list(w.events), w.snapshot()

        cases = 0
        for st0 in (0, 1, 2, 3):
            for st1 in (0, 1, 2, 3, 4):
                for st2 in (0, 1, 2, 3, 4):
                    for is_title in (0, 1):
                        for f12f0, f13d0, f220 in ((0, 0, 0), (1, 1, 1), (0, 1, 0), (1, 0, 1)):
                            scen = {'f12f0': f12f0, 'f13d0': f13d0, 'f220': f220}
                            replies = dict(cam=1, light=1, run=1, work=WORK, isTitle=is_title,
                                           st0=st0, st1=st1, st2=st2, st3=0, intfStat=0,
                                           difficult=1, use=(0, 0, 0, 0), done=(0, 0, 0, 0), isuse=0)
                            exp_ev, exp_mem = retail_run(0x3f1a80, (), scen, replies)
                            got_ev, got_mem = c_run(update, (), scen, replies)
                            where = ('update', st0, st1, st2, is_title)
                            assert got_ev == exp_ev, (where, exp_ev, got_ev)
                            assert got_mem == exp_mem, (where, 'memory')
                            cases += 1

        for cmd in (0, 1, 2, 3):
            for work in (0, WORK):
                for f240, f320, f660, isuse in ((0, 0, 0, 0), (2, 1, 0, 1), (-1, 1, 1, 0)):
                    scen = {'cmd': cmd, 'f240': f240, 'f320': f320, 'f660': f660}
                    replies = dict(cam=1, light=1, run=1, work=work, isTitle=1,
                                   st0=0, st1=0, st2=0, st3=0, intfStat=0, difficult=2,
                                   use=(0, 0, 0, 0), done=(0, 0, 0, 0), isuse=isuse)
                    exp_ev, exp_mem = retail_run(0x3f2490, (INFO,), scen, replies)
                    got_ev, got_mem = c_run(message, (INFO,), scen, replies)
                    where = ('message', cmd, work)
                    assert got_ev == exp_ev, (where, exp_ev, got_ev)
                    assert got_mem == exp_mem, (where, 'memory')
                    cases += 1

        # --- randomized update/message sweep ---------------------------------
        import random
        rng = random.Random(0x3f1a80)
        for _ in range(400):
            n = 4
            replies = dict(cam=rng.randrange(4), light=rng.randrange(4), run=rng.randrange(2),
                           work=rng.choice((0, WORK)) if False else WORK,
                           isTitle=rng.randrange(2), st0=rng.randrange(5), st1=rng.randrange(5),
                           st2=rng.randrange(5), st3=rng.randrange(5),
                           intfStat=rng.choice((0, 1, 2, 3)),
                           difficult=rng.randrange(3),
                           use=tuple(rng.randrange(2) for _ in range(n)),
                           done=tuple(rng.randrange(2) for _ in range(n)),
                           isuse=rng.randrange(2))
            scen = {'f12f0': rng.randrange(2), 'f13d0': rng.randrange(2), 'f220': rng.randrange(2),
                    'f240': rng.choice((-1, 0, 2)), 'f320': rng.randrange(3),
                    'f660': rng.randrange(2), 'cmd': rng.randrange(4)}
            exp_ev, exp_mem = retail_run(0x3f1a80, (), scen, replies)
            got_ev, got_mem = c_run(update, (), scen, replies)
            assert got_ev == exp_ev, ('update rand', exp_ev, got_ev)
            assert got_mem == exp_mem, ('update rand memory',)
            exp_ev, exp_mem = retail_run(0x3f2490, (INFO,), scen, replies)
            got_ev, got_mem = c_run(message, (INFO,), scen, replies)
            assert got_ev == exp_ev, ('message rand', exp_ev, got_ev)
            assert got_mem == exp_mem, ('message rand memory',)
            cases += 2

        print(f'{cases} retail-vs-C load-controller cases agree: ordered engine calls '
              f'and every non-stack byte write')


if __name__ == '__main__':
    main()
