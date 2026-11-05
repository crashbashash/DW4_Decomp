#!/usr/bin/env python3
"""Compare the native stream-request decision (src/streamplayer.c) with the original instructions of FUN_0037c2c0.

Builds the retail objects (beCri player, its two stream slots and handles, the file-name table and the beSoundData request) in the
interpreter's memory and executes 0x0037c130-style entry 0x0037c2c0 for every combination of request type, memory index, slot state
(playing / finished / error), ramp running, start success, one-shot pause flag, volume, base and request counter. The leaf operations
(voice query, fade arm, pause, level, start, name) are recorded in call order with their arguments; their own bodies are not executed.

    python3 tools/verify_streamplayer.py --elf ../../local/extracted/SLUS_208.36
"""
import argparse
import ctypes as C
import itertools
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT.parent / 'scripts'))
from ee_core import EE, MASK, M32, sx

SELF, TABLE, ITEMS, ENTRY0, ENTRY1, EV, SLOT1, SLOT2, H1, H2, VOICE1, VOICE2, NAME_EV, NAME_E = [0x1000000 + 0x1000 * i for i in range(14)]
STACK, SENTINEL = 0x1ff0000, 0xfffffff0
ENTRY = 0x37c2c0
CHECK, FADE, PAUSE_OR_UNPAUSE, LEVEL, START, SETNAME = 0x3a70c0, 0x3a7590, 0x3a7260, 0x3a6f70, 0x3a6c00, 0x2fecb0
CODES = {'check': 1, 'fade': 2, 'pause': 3, 'level': 4, 'start': 5, 'unpause': 6, 'name': 7}


class Retail(EE):
    def __init__(self, image, state, start_ok):
        self.image = image
        self.mem = {}
        self.state, self.start_ok = state, start_ok
        self.ee_reset()
        self.ops = []
        self.args = {}

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
        r = self.r
        if addr == CHECK:
            self.ops.append('check'); r[2] = self.state & MASK
        elif addr == FADE:
            self.ops.append('fade'); self.args['fade'] = (r[4] & M32, sx(r[5] & M32, 32), self.f[12], self.f[13], self.f[14]); r[2] = 0
        elif addr == PAUSE_OR_UNPAUSE:
            self.ops.append('pause' if (r[5] & 255) == 1 else 'unpause'); r[2] = 0
        elif addr == LEVEL:
            self.ops.append('level'); self.args['level'] = sx(r[5] & M32, 32); r[2] = 0
        elif addr == START:
            self.ops.append('start'); r[2] = 1 if self.start_ok else 0
        elif addr == SETNAME:
            self.ops.append('name'); r[2] = 0
        else:
            raise AssertionError(f'unexpected call {addr:#x}')

    def request(self, typ, memory_idx, volume, base, counter, skip, fade_running, slot_index):
        self.write(SELF + 24, 8, counter & MASK)
        self.write(SELF + 32, 4, SLOT1)
        self.write(SELF + 36, 4, SLOT2)
        self.write(SELF + 52, 4, base & M32)
        self.write(SELF + 60, 1, skip)
        self.write(TABLE + 16, 4, ITEMS)
        self.write(ITEMS, 4, ENTRY0)
        self.write(ITEMS + 4, 4, ENTRY1)
        self.write(ENTRY0 + 8, 4, NAME_E)
        self.write(ENTRY1 + 8, 4, NAME_E)
        self.write(EV + 8, 4, NAME_EV)
        self.write(EV + 16, 2, typ & 0xffff)
        self.write(EV + 18, 2, slot_index)
        self.write(EV + 20, 4, memory_idx & M32)
        self.write(EV + 26, 2, volume & 0xffff)
        for slot, handle, voice in ((SLOT1, H1, VOICE1), (SLOT2, H2, VOICE2)):
            self.write(slot + 12, 4, voice)
            self.write(slot + 16, 4, handle)
            self.write(handle + 8, 4, 1 if fade_running else 0)
        self.r[4], self.r[5], self.r[6] = SELF, TABLE, EV
        self.r[28], self.r[29], self.r[31] = 0x55c870, STACK, SENTINEL
        self.run_until(ENTRY, SENTINEL)
        slot = SLOT1 if typ == 1 else SLOT2
        return sx(self.r[2], 64), slot


class Decision(C.Structure):
    _fields_ = [('seq', C.c_int64), ('ops', C.c_int * 8), ('level', C.c_int), ('clear_skip', C.c_int)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--elf', type=Path, required=True)
    opts = p.parse_args()
    image = opts.elf.read_bytes()
    with tempfile.TemporaryDirectory(prefix='dw4-stream-') as temp:
        so = Path(temp) / 'stream.so'
        subprocess.run(['cc', '-shared', '-fPIC', '-std=c99', '-O2', '-I' + str(ROOT / 'include'), str(ROOT / 'src' / 'streamplayer.c'), '-o', str(so)],
                       check=True)
        lib = C.CDLL(str(so))
        lib.dw4_stream_decide.argtypes = [C.c_int, C.c_int, C.c_int, C.c_int, C.c_int, C.c_int, C.c_int, C.c_int, C.c_int64, C.POINTER(Decision)]
        total = {'ignored': 0, 'fade': 0, 'wait': 0, 'started': 0, 'failed': 0}
        for typ, mem, state, fading, ok, skip, vol, base, counter in itertools.product(
                (1, 2, 3, 4), (-1, 0, 7), (1, 0, -1), (0, 1), (0, 1), (0, 1), (-130, -20, 0, 7), (-30, 0, 15), (0, 41, 2**40)):
            r = Retail(image, state, ok)
            ret, slot = r.request(typ, mem, vol, base, counter, skip, fading, 0)
            d = Decision()
            lib.dw4_stream_decide(typ, mem, state, fading, ok, skip, vol, base, counter, C.byref(d))
            ops = []
            for code in d.ops:
                if code == 0:
                    break
                ops.append(code)
            want_ops = [CODES[o] for o in r.ops]
            assert ops == want_ops and d.seq == ret, ((typ, mem, state, fading, ok, skip, vol, base, counter), ops, want_ops, d.seq, ret)
            if 'level' in r.args:
                assert d.level == r.args['level'], (d.level, r.args)
            if 'fade' in r.args:
                handle, add, f1, f2, f3 = r.args['fade']
                assert handle == (H1 if typ == 1 else H2) and add == base and (f1, f2, f3) == (0x3f800000, 0, 0x41200000), r.args
            # the pause flag is consumed exactly when retail clears it, the slot's id/type are stored on success
            assert r.read(SELF + 60, 1) == (0 if d.clear_skip else skip) if ok and d.seq else True
            if d.seq:
                assert r.read(SELF + 24, 8) == d.seq and sx(r.read(slot + 32, 2), 16) == typ and r.read(slot + 24, 8) == d.seq
            assert (r.read((H1 if typ == 1 else H2) + 12, 2) == vol & 0xffff) if 'level' in r.args else True
            key = ('ignored' if not ops else 'fade' if 'fade' in r.args else 'wait' if ops == [1] else 'started' if d.seq else 'failed')
            total[key] += 1
        print('Stream player: %d requests match FUN_0037c2c0 (%s)' % (sum(total.values()),
              ', '.join(f'{v} {k}' for k, v in total.items())))


if __name__ == '__main__':
    main()
