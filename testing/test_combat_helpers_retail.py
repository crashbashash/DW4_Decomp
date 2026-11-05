#!/usr/bin/env python3
"""Compare both complete combat helpers with original instructions.

Property lookup, allocator/factory, list growth and messenger services are
controlled boundaries. Matrix translation executes original versus recovered
code. Compare all runtime RAM and meaningful ordered call arguments, excluding
compiler stack storage. Float checks share the documented EE arithmetic model.
"""
import argparse
import ctypes as C
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from ee_core import EE, MASK, sx

READ = C.CFUNCTYPE(C.c_uint64, C.c_void_p, C.c_uint32, C.c_uint)
WRITE = C.CFUNCTYPE(None, C.c_void_p, C.c_uint32, C.c_uint, C.c_uint64)
CALL = C.CFUNCTYPE(C.c_uint64, C.c_void_p, C.c_uint32, C.POINTER(C.c_uint64))


class Api(C.Structure):
    _fields_ = [("user", C.c_void_p), ("read", READ), ("write", WRITE), ("call", CALL)]


SELF, PLAYER, PROPERTY, ITEMS, BUFFER, OUTPUT, LIST, OLD, NEW, CENTER, GROUP = range(0x1800000, 0x180B000, 0x1000)
STACK, FRAME = 0x1FFF000, 0x1FFEF00
SIZES = {0x3A9340: 2, 0x301000: 1, 0x2F88E0: 1, 0x2CAA70: 1, 0x38E670: 3,
         0x38F240: 1, 0x38F320: 2, 0x38F630: 3, 0x38ED70: 1, 0x38D860: 4,
         0x38F0E0: 2, 0x38E060: 2, 0x38EF50: 1, 0x2D6790: 3, 0x2FF820: 1}


def bits(value):
    return struct.unpack("<I", struct.pack("<f", value))[0]


class Combat(EE):
    def __init__(self, image):
        self.image, self.mem, self.events = image, {}, []
        self.descend = {0x3FC6F0, 0x3FC780, 0x190A30}
        self.ee_reset()
        self.ids, self.positions, self.hp = [], [], {}
        self.query, self.selected = False, None
        self.factory, self.relocate, self.change_messenger = LIST, False, False
        self.count_override = None

    def read(self, address, size):
        address &= 0xFFFFFFFF
        if 0x100000 <= address and address + size <= 0x554B00:
            offset = address - 0x100000 + 0x80
            return int.from_bytes(self.image[offset:offset + size], "little")
        return sum(self.mem.get(address + i, 0) << (8 * i) for i in range(size))

    def write(self, address, size, value):
        address &= 0xFFFFFFFF
        for i in range(size): self.mem[address + i] = (value >> (i * 8)) & 255

    w = write

    def invoke(self, entry, *args):
        covered = self.covered
        self.ee_reset()
        self.covered = covered
        saved = {i: (i << 96) | (0x1234 << 64) | (0xA000 + i) for i in range(16, 24)}
        saved[30] = 0xFEDCBA98765432100123456789ABCDEF
        for i, value in saved.items(): self.r[i] = value
        self.r[4:4 + len(args)] = [value & MASK for value in args]
        self.r[28], self.r[29], self.r[31] = 0x55C870, STACK, 0xFFFFFFF0
        self.run_until(entry, 0xFFFFFFF0)
        assert self.r[29] == STACK
        assert all(self.r[i] == value for i, value in saved.items())
        return self.r[2]

    def call_hook(self, entry):
        self.r[2] = self.call(entry, self.r[4:12]) & MASK

    def call(self, entry, arguments):
        values = [value & 0xFFFFFFFF for value in arguments]
        self.events.append((entry, *values[:SIZES[entry]]))
        if entry == 0x3A9340:
            assert values[:2] == [PLAYER, 0x518928]
            return PROPERTY
        if entry == 0x301000: return 0x1810000
        if entry == 0x2F88E0: return 0x1811000
        if entry == 0x2CAA70: return self.factory
        if entry == 0x38E670:
            assert values[1:3] == [GROUP, 0x519030]
            return 0
        if entry == 0x38F240:
            return len(self.ids) if self.count_override is None else self.count_override
        if entry == 0x38F320:
            value = self.hp[self.selected] if self.query else self.ids[values[1]]
            return sx(value, 32)
        if entry == 0x38F630:
            for i in range(16): self.w(values[0] + i * 4, 4, 0x3F800000 if i % 5 == 0 else 0)
            for i, value in enumerate(self.positions[values[2]]): self.w(values[0] + 48 + i * 4, 4, value)
            return 0
        if entry == 0x38ED70:
            if self.change_messenger: self.w(SELF + 20, 4, self.read(SELF + 20, 4) + 4)
            return 0
        if entry == 0x38D860:
            assert values[1:3] == [GROUP, 0]
            self.selected = sx(values[3], 32)
            return 0
        if entry == 0x38F0E0:
            assert values[1] == 1
            return 0
        if entry == 0x38E060:
            assert values[1] == 0x519040
            self.query = True
            return 0
        if entry == 0x38EF50:
            self.query = False
            return 0
        if entry == 0x2D6790:
            address, count, stride = values[:3]
            assert address == LIST and stride == 4
            if self.relocate:
                previous = self.read(LIST + 16, 4)
                for i in range(self.read(LIST + 8, 4) * 4): self.w(NEW + i, 1, self.read(previous + i, 1))
                self.w(LIST + 16, 4, NEW)
            self.w(LIST + 8, 4, count)
            self.w(LIST + 12, 4, count + 8)
            return 0
        if entry == 0x2FF820: return 0
        raise AssertionError(f"unexpected helper boundary {entry:#x}")


def runtime(memory):
    return {p: value for p, value in memory.items() if not STACK - 0x1000 <= p < STACK + 0x100}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--elf", type=Path, default=ROOT / "orig/SLUS-20836/SLUS_208.36")
    args = parser.parse_args()
    image = args.elf.read_bytes()
    retail, native = Combat(image), Combat(image)
    failures, cases = [], {0x3FC6F0: 0, 0x3FC780: 0}

    @CALL
    def call(_user, entry, values):
        try: return native.call(entry, values[:8]) & MASK
        except Exception as error: failures.append(error); return 0

    read = READ(lambda _u, p, n: native.read(p, n))
    write = WRITE(lambda _u, p, n, value: native.w(p, n, value))
    api = Api(None, read, write, call)
    with tempfile.TemporaryDirectory(prefix="dw4-combat-helpers-") as directory:
        shared = Path(directory) / "helpers.so"
        subprocess.run(["cc", "-shared", "-fPIC", "-std=c99", "-Wall", "-Wextra", "-Werror",
                        str(ROOT / "recovered/game/combat-helpers.c"),
                        str(ROOT / "recovered/engine/matrix-primitives.c"),
                        str(ROOT / "recovered/frontend/eefloat.c"), "-o", str(shared)], check=True)
        lib = C.CDLL(str(shared))
        row = lib.dw4_combat_find_technique_row
        row.argtypes = [C.POINTER(Api), C.c_uint32, C.c_int32, C.c_uint32]
        nearby = lib.dw4_combat_collect_nearby
        # output,self,group,excluded,center,frame: six guest words after the API.
        nearby.argtypes = [C.POINTER(Api), C.c_uint32, C.c_uint32, C.c_uint32,
                           C.c_int32, C.c_uint32, C.c_uint32]
        nearby.restype = C.c_uint32

        def compare(entry, parameters, output):
            native.mem = retail.mem.copy()
            for field in ("ids", "positions", "hp", "factory", "relocate", "change_messenger", "count_override"):
                setattr(native, field, getattr(retail, field))
            retail.events, native.events = [], []
            retail.query = native.query = False
            result = retail.invoke(entry, *parameters)
            if entry == 0x3FC6F0:
                row(C.byref(api), parameters[1], parameters[2], parameters[3])
            else:
                actual = nearby(C.byref(api), *parameters, FRAME)
                assert actual == result == 0
            assert not failures, failures
            assert native.events == retail.events, (entry, native.events, retail.events)
            assert runtime(native.mem) == runtime(retail.mem), (entry, parameters,
                [(hex(p), retail.mem.get(p), native.mem.get(p)) for p in native.mem.keys() | retail.mem.keys()
                 if not STACK-0x1000 <= p < STACK+0x100 and retail.mem.get(p) != native.mem.get(p)][:12])
            cases[entry] += 1
            return native.read(output, 4)

        for count in (-1, 0, 1, 3, 9, 17):
            for key in (-1, 0, 1, 8, 16, 99):
                for alias in (OUTPUT, ITEMS + 8, PROPERTY + 12, BUFFER, BUFFER + 0x104):
                    retail.mem = {}
                    retail.w(PROPERTY + 12, 4, ITEMS)
                    retail.w(ITEMS + 8, 4, count)
                    retail.w(ITEMS + 16, 4, BUFFER)
                    for i in range(max(0, count)):
                        item = BUFFER + 0x100 + i * 0x40
                        retail.w(BUFFER + i * 4, 4, item)
                        retail.w(item + 20, 4, i if i != 2 else 1)
                        retail.w(item + 12, 4, 100 + i)
                    if alias == OUTPUT: retail.w(alias, 4, 0xDEADBEEF)
                    value = compare(0x3FC6F0, (SELF, PLAYER, key, alias), alias)
                    if alias == OUTPUT:
                        matches = [i for i in range(max(0, count)) if (i if i != 2 else 1) == key]
                        assert value == (100 + matches[0] if matches else 0xDEADBEEF)

        shapes = [[], [(5, (0, 0, 0), 1)],
                  [(5, (0, 0, 0), 1), (6, (29, 0, 0), 0), (7, (30, 0, 0), 1), (8, (31, 0, 0), 1)],
                  [(5, (10, 20, 20), 1), (6, (10, 20, 19), -1), (6, (0, 0, 0), -1)]]
        for shape in shapes:
            for excluded in (-1, 5, 6):
                for capacity in (0, 1, 8):
                    for allocator in (0, 1, 255):
                        for refs in (0, 1, 0x800001, 0xFFFFFFFF):
                            retail.mem = {}
                            retail.ids = [item[0] for item in shape]
                            retail.positions = [tuple(bits(value) for value in item[1]) for item in shape]
                            retail.hp = {item[0]: item[2] for item in shape}
                            retail.relocate = capacity != 8
                            retail.change_messenger = allocator == 255
                            retail.w(SELF + 20, 4, 0x1812000)
                            retail.w(0x554C14, 1, allocator)
                            retail.w(0x587110, 4, 0x1813000)
                            retail.w(LIST + 4, 4, refs)
                            retail.w(LIST + 8, 4, 0)
                            retail.w(LIST + 12, 4, capacity)
                            retail.w(LIST + 16, 4, OLD)
                            for i in range(3): retail.w(CENTER + i * 4, 4, 0)
                            assert compare(0x3FC780, (OUTPUT, SELF, GROUP, excluded, CENTER), OUTPUT) == LIST
                            expected = [item[0] for item in shape if item[0] != excluded
                                        and sum(v * v for v in item[1]) < 900 and retail.hp[item[0]] != 0]
                            buffer = native.read(LIST + 16, 4)
                            assert native.read(LIST + 8, 4) == len(expected)
                            assert [sx(native.read(buffer + i * 4, 4), 32) for i in range(len(expected))] == expected
        raw_positions = [(0x41EFFFFF, 0, 0), (0x41F00000, 0, 0), (0x41F00001, 0, 0),
                         (0x80000000, 1, 0x80000001), (0x7F800000, 0, 0),
                         (bits(10), bits(20), bits(20)), (bits(-29), 0, 0)]
        for position in raw_positions:
            retail.mem = {}
            retail.ids, retail.positions, retail.hp = [5], [position], {5: 1}
            retail.w(SELF + 20, 4, 0x1812000)
            retail.w(0x554C14, 1, 1)
            retail.w(LIST + 4, 4, 1)
            retail.w(LIST + 12, 4, 1)
            retail.w(LIST + 16, 4, OLD)
            compare(0x3FC780, (OUTPUT, SELF, GROUP, -1, CENTER), OUTPUT)
        for output in (LIST + 4, LIST + 8, SELF + 20):
            retail.mem = {}
            retail.ids, retail.positions, retail.hp = [5], [(0, 0, 0)], {5: 1}
            retail.w(SELF + 20, 4, 0x1812000)
            retail.w(0x554C14, 1, 1)
            retail.w(LIST + 4, 4, 1)
            retail.w(LIST + 12, 4, 1)
            retail.w(LIST + 16, 4, OLD)
            compare(0x3FC780, (output, SELF, GROUP, -1, CENTER), output)
        for count in (0, -1):
            retail.mem = {}
            retail.factory, retail.count_override = 0, count
            retail.ids, retail.positions, retail.hp = [], [], {}
            retail.w(SELF + 20, 4, 0x1812000)
            assert compare(0x3FC780, (OUTPUT, SELF, GROUP, -1, CENTER), OUTPUT) == 0
        assert cases[0x3FC6F0] and cases[0x3FC780]
        words = set(range(0x3FC6F0, 0x3FC774, 4)) | set(range(0x3FC780, 0x3FCA0C, 4))
        missed = words - retail.covered
        assert missed == {0x3FC74C}, [hex(pc) for pc in sorted(missed)]
        assert retail.read(0x3FC74C, 4) == 0  # unreachable alignment word after unconditional jump
    print(f"combat helpers retail: {cases[0x3FC6F0]} row-search and {cases[0x3FC780]} nearby-query cases; "
          "exact runtime RAM/call order, 195 executable words plus one reviewed padding word")


if __name__ == "__main__":
    main()
