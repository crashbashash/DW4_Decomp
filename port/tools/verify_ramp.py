#!/usr/bin/env python3
"""Compare the native volume ramp (src/ramp.c) with the original instructions of FUN_003a7590 / FUN_003a7890 / FUN_003a7810.

The ramp object is built in the interpreter's memory (mode +8, base +12, position +16, from +20, to +24, step +28); FUN_003a7590 arms it and
FUN_003a7890 steps it once per frame (descending into FUN_003a7810), over the executable's own ease tables. Every armed state and every
frame's level, table position and mode are compared for many fades, using the Emotion Engine FPU model of scripts/ee_core.py (assumed
rounding, as for the other float oracles). The CRI level table that turns a level into a gain is covered by verify_frontaudio_rules.py.

    python3 tools/verify_ramp.py --elf ../../local/extracted/SLUS_208.36
"""
import argparse
import ctypes as C
import itertools
import random
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT.parent / 'scripts'))
from ee_core import EE, MASK, M32, sx

RAMP, STACK, SENTINEL = 0x1000000, 0x1ff0000, 0xfffffff0
START, STEP, EASE = 0x3a7590, 0x3a7890, 0x3a7810


def bits(x):
    return struct.unpack('<I', struct.pack('<f', x))[0]


class Retail(EE):
    descend = frozenset({EASE})

    def __init__(self, image):
        self.image = image
        self.mem = {}
        self.ee_reset()

    def read(self, a, n):
        a &= M32
        if any(a + i in self.mem for i in range(n)):
            return sum(self.mem.get(a + i, 0) << (8 * i) for i in range(n))
        if 0x100000 <= a and a + n <= 0x554b00:
            o = a - 0x100000 + 0x80
            return int.from_bytes(self.image[o:o + n], 'little')
        return 0

    def write(self, a, n, v):
        for i in range(n):
            self.mem[(a & M32) + i] = (v >> (8 * i)) & 255

    def call_hook(self, addr):
        raise AssertionError(f'unexpected call {addr:#x}')

    def run(self, entry, add, floats=()):
        cov = self.covered
        self.ee_reset()
        self.covered = cov
        self.r[4], self.r[5] = RAMP, add & MASK
        for i, b in enumerate(floats):
            self.f[12 + i] = b
        self.r[28], self.r[29], self.r[31] = 0x55c870, STACK, SENTINEL
        self.run_until(entry, SENTINEL)
        return sx(self.r[2] & M32, 32)

    def state(self):
        return tuple(self.read(RAMP + o, 4) for o in (8, 12, 16, 20, 24, 28))


class Ramp(C.Structure):
    _fields_ = [('mode', C.c_int), ('base', C.c_int), ('cur', C.c_uint32), ('from_', C.c_uint32), ('to', C.c_uint32), ('step', C.c_uint32)]

    def state(self):
        return (self.mode & M32, self.base & M32, self.cur, self.from_, self.to, self.step)


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--elf', type=Path, required=True)
    p.add_argument('--src', type=Path, default=ROOT / 'src' / 'ramp.c')
    p.add_argument('--cases', type=int, default=1500)
    opts = p.parse_args()
    image = opts.elf.read_bytes()
    with tempfile.TemporaryDirectory(prefix='dw4-ramp-') as temp:
        so = Path(temp) / 'ramp.so'
        subprocess.run(['cc', '-shared', '-fPIC', '-std=c99', '-O2', '-I' + str(ROOT / 'include'), '-I' + str(ROOT / 'recovered' / 'frontend'),
                        str(opts.src), str(ROOT / 'recovered' / 'frontend' / 'eefloat.c'), '-o', str(so)], check=True)
        lib = C.CDLL(str(so))
        lib.dw4_ramp_start.argtypes = [C.POINTER(Ramp), C.c_int, C.c_uint32, C.c_uint32, C.c_uint32]
        lib.dw4_ramp_start.restype = C.c_int
        lib.dw4_ramp_step.argtypes = [C.POINTER(Ramp), C.c_int]
        lib.dw4_ramp_step.restype = C.c_int
        lib.dw4_ramp_table.argtypes = [C.c_int]
        lib.dw4_ramp_table.restype = C.POINTER(C.c_uint32)
        # the tables are the executable's own
        for rising, addr in ((1, 0x4c8fc0), (0, 0x4c90b0)):
            t = lib.dw4_ramp_table(rising)
            for i in range(60):
                assert t[i] == int.from_bytes(image[addr - 0x100000 + 0x80 + 4 * i:][:4], 'little'), (rising, i)
        rng = random.Random(0x3a7590)
        fades = [(1.0, 0.0), (0.0, 1.0), (0.5, 1.0), (1.0, 0.5), (0.25, 0.75), (0.75, 0.25), (0.96, 0.0), (0.04, 1.0), (0.3, 0.3), (1.0, 1.0), (0.0, 0.0)]
        fades += [(round(rng.random(), 2), round(rng.random(), 2)) for _ in range(40)]
        divs = [1.0, 2.0, 3.0, 5.0, 10.0, 11.0, 15.0, 30.0, 60.0, 120.0]
        adds = [-30, 0, 20, -100]
        bases = [-30, 0, -20, -130, 50]
        combos = list(itertools.product(fades, divs, adds, bases))
        rng.shuffle(combos)
        total = steps = ended = silent = oob = 0
        for (frm, to), div, add, base in combos[:opts.cases]:
            ret = Retail(image)
            ret.write(RAMP + 12, 4, base & M32)
            ret.write(RAMP + 8, 4, 0)
            got = ret.run(START, add, [bits(frm), bits(to), bits(div)])
            r = Ramp(0, base, 0, 0, 0, 0)
            mine = lib.dw4_ramp_start(C.byref(r), add, bits(frm), bits(to), bits(div))
            assert mine == got and ret.state() == r.state(), ((frm, to, div, add, base), mine, got, ret.state(), r.state())
            total += 1
            for _ in range(130):
                want = ret.run(STEP, add)
                have = lib.dw4_ramp_step(C.byref(r), add)
                position = int(struct.unpack('<f', struct.pack('<I', r.cur))[0])
                if position < 0 or position > (119 if frm < to else 59):
                    oob += 1   # past the table pair: retail reads unrelated memory, so nothing to compare
                    break
                assert have == want and ret.state() == r.state(), ((frm, to, div, add, base), have, want, ret.state(), r.state())
                steps += 1
                if r.mode == 0:
                    ended += 1
                    silent += have == -999
                    break
        print(f'Ramp: {total} armed states and {steps} frames match FUN_003a7590/FUN_003a7890/FUN_003a7810 '
              f'({ended} fades reached their target, {silent} of them at silence, {oob} stopped where retail would read past the tables); both ease tables equal the executable\'s')


if __name__ == '__main__':
    main()
