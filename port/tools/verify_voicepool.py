#!/usr/bin/env python3
"""Compare the native resident-effect handle allocator with the original instructions of FUN_0037c130.

Builds the retail object graph (beCri -> _hdSEs list -> beCriHandle -> beCriAudio) in the EE interpreter's memory, executes
0x0037c130 for randomized pool states and compares the chosen index and whether the stop routine (0x0037caf0) was called on
that handle with dw4_voicepool_pick (src/voicepool.c). When no handle qualifies retail returns an uninitialised local, so
that case is checked only for dependence on caller state. The stop routine itself and the rest of the sound runtime are not
executed; this establishes the allocation rule only.

    python3 tools/verify_voicepool.py --elf ../../local/extracted/SLUS_208.36
"""
import argparse
import ctypes as C
import random
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT.parent / 'scripts'))
from verify_loadintf2 import Harness, Retail as Cpu, MASK, sx

SELF, LIST, ARRAY, HANDLES, AUDIOS, STACK, SENTINEL = 0x1000000, 0x1001000, 0x1002000, 0x1010000, 0x1020000, 0x1030000, 0x1fffff00
ENTRY, STOP = 0x37c130, 0x37caf0


class Retail(Cpu):
    def __init__(self, image):
        Harness.__init__(self, image)
        self.r = [0] * 32
        self.f = [0] * 32
        self.executed = set()
        self.real_hits = set()
        self.stopped = []

    def read(self, address, size):
        address &= 0xffffffff
        if any(address + i in self.mem for i in range(size)):
            return sum(self.mem.get(address + i, 0) << (8 * i) for i in range(size))
        return Harness.read(self, address, size)

    def step(self, pc, delay=False):
        word = self.read(pc, 4)
        if word >> 26 == 0x21:   # lh: the interpreter has lhu but not the signed halfword load the priority compare uses
            rs, rt = (word >> 21) & 31, (word >> 16) & 31
            self.executed.add(pc)
            self.r[rt] = sx(self.read((self.r[rs] + sx(word, 16)) & 0xffffffff, 2), 16) & MASK
            self.r[0] = 0
            return pc + 4
        return Cpu.step(self, pc, delay)

    def call_hook(self, address):
        assert address == STOP, hex(address)
        self.stopped.append(self.r[5] & 0xffffffff)   # a1 = the handle being stopped
        self.r[2] = 0

    def pick(self, slots, kind, priority, request, fill=0):
        for reg in range(1, 26):
            self.r[reg] = fill   # caller state the allocator never initialises
        self.write(SELF + 24, 8, request & MASK)
        self.write(SELF + 40, 4, LIST)
        self.write(LIST + 8, 4, len(slots))
        self.write(LIST + 16, 4, ARRAY)
        for i, (adx, bank, play_id, prio) in enumerate(slots):
            h, a = HANDLES + 0x40 * i, AUDIOS + 0x20 * i
            self.write(ARRAY + 4 * i, 4, h)
            self.write(h + 12, 4, a)
            self.write(h + 24, 8, play_id & MASK)
            self.write(h + 34, 2, prio & 0xffff)
            self.write(a + 8, 4, 0x1100000 if adx else 0)    # _adxt object reference
            self.write(a + 12, 4, 0x1100000 if bank else 0)  # _sndf object reference
        self.r[4], self.r[5], self.r[6] = SELF, kind, priority & MASK
        self.r[29], self.r[31] = STACK, SENTINEL
        pc = ENTRY
        for _ in range(20000):
            if pc == SENTINEL:
                break
            pc = self.step(pc)
        else:
            raise AssertionError('allocator did not return')
        victim = None
        if self.stopped:
            assert len(self.stopped) == 1, self.stopped
            victim = (self.stopped[0] - HANDLES) // 0x40
        return sx(self.r[2] & 0xffffffff, 32), victim


class Slot(C.Structure):
    _fields_ = [('adx', C.c_ubyte), ('bank', C.c_ubyte), ('play_id', C.c_int64), ('priority', C.c_int16)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--elf', type=Path, required=True)
    p.add_argument('--cases', type=int, default=4000)
    opts = p.parse_args()
    image = opts.elf.read_bytes()
    with tempfile.TemporaryDirectory(prefix='dw4-voicepool-') as temp:
        so = Path(temp) / 'pool.so'
        subprocess.run(['cc', '-shared', '-fPIC', '-std=c99', '-O2', '-I' + str(ROOT / 'include'),
                        str(ROOT / 'src' / 'voicepool.c'), '-o', str(so)], check=True)
        lib = C.CDLL(str(so))
        lib.dw4_voicepool_pick.argtypes = [C.POINTER(Slot), C.c_uint, C.c_int, C.c_int16, C.c_int64, C.POINTER(C.c_int)]
        lib.dw4_voicepool_pick.restype = C.c_int
        rng = random.Random(0x37c130)
        counts = {'idle': 0, 'steal': 0, 'none': 0, 'none_varies': 0}

        def run(slots, kind, priority, request):
            arr = (Slot * max(len(slots), 1))(*[Slot(a, b, i, pr) for a, b, i, pr in slots])
            steal = C.c_int(-1)
            got = lib.dw4_voicepool_pick(arr, len(slots), kind, priority, request, C.byref(steal))
            if got == -1:
                # No handle qualifies: retail returns its uninitialised `best`, i.e. whatever the caller left in a register
                # (and then stops that handle). That is undefined, so the native function fails the play; check that the
                # retail result really depends on the caller state, and never compare it for equality.
                assert not steal.value
                seen = set()
                for fill in (0, 1, 2, 0x55):
                    seen.add(Retail(image).pick(slots, kind, priority, request, fill))
                counts['none'] += 1
                counts['none_varies'] += len(seen) > 1
                return
            want, victim = Retail(image).pick(slots, kind, priority, request)
            assert got == want, (slots, kind, priority, request, got, want)
            assert (victim is not None) == bool(steal.value), (slots, kind, priority, request, victim, steal.value)
            if victim is not None:
                assert victim == got
            counts['steal' if victim is not None else 'idle'] += 1
            # the defined result must not depend on the caller state either
            assert Retail(image).pick(slots, kind, priority, request, 0x55) == (want, victim)

        # the real pool shape: 4 ADX handles then 48 sound-bank handles, in many fill states
        for _ in range(opts.cases):
            n_adx = 4 if rng.random() < 0.7 else rng.randint(0, 6)
            n_bank = 48 if rng.random() < 0.5 else rng.randint(0, 12)
            request = rng.randint(1, 500)
            busy = rng.random()
            slots = []
            for i in range(n_adx + n_bank):
                adx = 1 if i < n_adx else 0
                both = rng.random() < 0.05
                playing = rng.random() < busy
                slots.append((adx or int(both), int(not adx) or int(both), rng.randint(1, request) if playing else 0,
                              rng.choice((0, 0, 0, 1, 1, 2, -1))))
            run(slots, rng.choice((0, 1)), rng.choice((0, 0, 1, 2, -1)), request)
        # ties, equal ids, ids equal to the request counter and an ADX-less pool
        for request in (1, 2, 7):
            for ids in ([request] * 3, [request, 1, 1], [3, 3, 3], [0, 0, 0]):
                for prios in ([0, 0, 0], [1, 0, 1], [1, 1, 1], [0, 1, 2]):
                    slots = [(1, 1, i, pr) for i, pr in zip(ids, prios)]
                    for kind in (0, 1):
                        for priority in (-1, 0, 1, 2):
                            run(slots, kind, priority, request)
        run([], 1, 0, 1)
        run([(0, 1, 5, 0)], 1, 0, 9)
        total = sum(counts.values())
        print(f'Voice pool: {total} retail/native comparisons ({counts["idle"]} idle handle, {counts["steal"]} reuse after stop, '
              f'{counts["none"]} no qualifying handle: native fails the play, retail returns caller register state in '
              f'{counts["none_varies"]} of them); chosen index and stop call match FUN_0037c130 wherever it is defined')


if __name__ == '__main__':
    main()
