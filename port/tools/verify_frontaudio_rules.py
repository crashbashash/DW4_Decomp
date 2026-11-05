#!/usr/bin/env python3
"""Compare native SE repeat admission and stream levels with retail instructions.

Executes 0x0039eef0..0x0039ef78 (admission) and 0x0039efe4..0x0039effc
(deadline store), not the entire beSound dispatcher. Playback, allocation and
messaging leaves are boundaries. Stream comparisons also execute the original
CRI packet writer (0x00279984..0x002799c4) and clamp (0x0027ae18..0x0027ae50).
The title/lobby integration test is test_audio.
"""
import argparse
import ctypes as C
from pathlib import Path
import subprocess
import sys
import tempfile
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT.parent / 'scripts'))
from verify_loadintf2 import Harness, Retail as Cpu, MASK, sx
SELF, CTX, LIST, ARRAY, ROW, STACK = [0x1000000 + i*0x100 for i in range(6)]

class Retail(Cpu):
    def __init__(self, image):
        Harness.__init__(self, image)
        self.r = [0]*32
        self.f = [0]*32
        self.executed = set()
        self.real_hits = set()
    def read(self, address, size):
        address &= 0xffffffff
        if any(address+i in self.mem for i in range(size)):
            return sum(self.mem.get(address+i, 0) << (8*i) for i in range(size))
        return Harness.read(self, address, size)
    def step(self, pc, delay=False):
        word = self.read(pc, 4)
        if word >> 26 == 0 and word & 63 == 0x0b:  # movn in CRI level clamp
            self.executed.add(pc)
            rs = (word >> 21) & 31; rt = (word >> 16) & 31; rd = (word >> 11) & 31
            if self.r[rt]: self.r[rd] = self.r[rs]
            self.r[0] = 0
            return pc+4
        return Cpu.step(self, pc, delay)
    def call_hook(self, address):
        assert address in (0x38f250, 0x38f400), hex(address)
    def until(self, start, stops):
        pc = start
        for _ in range(1000):
            if pc in stops:
                return pc
            pc = self.step(pc)
        raise AssertionError('region did not exit')
    def admission(self, now, sound, rows):
        self.write(SELF+12, 4, CTX)
        self.write(SELF+40, 4, LIST)
        self.write(CTX+80, 8, now)
        self.write(LIST+8, 4, len(rows))
        self.write(LIST+16, 4, ARRAY)
        for i, (idx, expiry) in enumerate(rows):
            self.write(ARRAY+4*i, 4, ROW+32*i)
            self.write(ROW+32*i+8, 4, idx)
            self.write(ROW+32*i+16, 8, expiry)
        self.r[23] = SELF  # s7, sound manager
        self.r[19] = sound # s3, resolved sound row index
        return self.until(0x39eef0, {0x39ef78, 0x39faa8}) == 0x39ef78
    def deadline(self, now):
        self.r[17] = now & MASK  # s1, sampled context clock
        self.r[29] = STACK
        self.write(STACK+0xec, 4, ROW)
        self.until(0x39efe4, {0x39effc})
        return self.read(ROW+16, 8)

class Gate(C.Structure):
    _fields_ = [('until', C.c_uint64), ('valid', C.c_int)]

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--elf', type=Path, required=True)
    opts = p.parse_args()
    image = opts.elf.read_bytes()
    with tempfile.TemporaryDirectory(prefix='dw4-repeat-') as temp:
        source = Path(temp)/'gate.c'
        source.write_text('#include "audio_repeat.h"\n'
                          'int allow(const dw4_audio_repeat *r, uint64_t n) { return dw4_audio_repeat_allowed(r,n); }\n'
                          'void start(dw4_audio_repeat *r, uint64_t n) { dw4_audio_repeat_started(r,n); }\n'
                          '#include "audio_level.h"\n'
                          'unsigned level(int v) { return dw4_audio_stream_level(v); }\n')
        path = Path(temp)/'gate.so'
        subprocess.run(['cc', '-shared', '-fPIC', '-std=c99', '-O2', '-I'+str(ROOT/'src'), str(source), '-o', str(path), '-lm'], check=True)
        lib = C.CDLL(str(path))
        lib.allow.argtypes = [C.POINTER(Gate), C.c_uint64]
        lib.start.argtypes = [C.POINTER(Gate), C.c_uint64]
        lib.allow.restype = C.c_int
        lib.level.argtypes = [C.c_int]
        lib.level.restype = C.c_uint
        total = 0
        for now in (0, 1, 16666666, 49999997, 49999998, 49999999, 10**12,
                    (1<<63)-1, 1<<63, MASK-49999998, MASK):
            r = Retail(image)
            g = Gate()
            lib.start(C.byref(g), now)
            assert g.until == r.deadline(now), (now, g.until, r.deadline(now))
            total += 1
            for offset in (-1, 0, 1, 49999997, 49999998, 49999999, 100000000):
                sample = (now+offset)&MASK
                for valid in (0, 1):
                    g.valid = valid
                    for other in ([], [(99, MASK)], [(99, 0), (99, MASK)]):
                        rows = other + ([(7, g.until)] if valid else [])
                        expected = Retail(image).admission(sample, 7, rows)
                        assert lib.allow(C.byref(g), sample) == expected, (sample, rows)
                        total += 1
        # Execute the original packet writer which indexes the CRI volume table.
        for volume in range(-999, 1):
            r = Retail(image)
            r.r[7] = ROW; r.r[6] = ARRAY; r.r[18] = 0x4b0e20
            r.write(ROW+0x38, 4, volume)
            r.write(ROW+0x3c, 4, volume-1)
            r.until(0x279984, {0x2799c4})
            expected = r.read(ARRAY+12, 4)
            assert lib.level(volume) == expected, (volume, expected, lib.level(volume))
        for volume in (-65536, -1000, -999, -998, -50, -40, -30, -1, 0, 1, 65534):
            r = Retail(image)
            r.r[4] = ROW; r.r[5] = sx(volume, 32) & MASK
            r.write(0x4b1dc8, 4, 0)  # enabled normal CRI driver mode
            r.until(0x27ae18, {0x27ae50})
            clamped = sx(r.read(ROW+0x38, 4), 32)
            word = r.read(0x4b0e20 - clamped*4, 4)
            assert lib.level(volume) == word, (volume, clamped, word)
        print('Stream levels: all 1,000 CRI table entries match original packet writes; upper/lower clamps OK')
        print(f'SE repeat: {total} retail/native comparisons; exact deadline, signed clock boundaries, unrelated sounds and held-clock admission OK')

if __name__ == '__main__':
    main()
