#!/usr/bin/env python3
"""Compare the complete seven-helper recovery with original EE instructions.

No controlled callee leaves: these helpers only read/write fixture RAM.
Compares returned values and all RAM writes. Private retail ELF is read-only.
"""
import argparse
import ctypes as C
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "port/tools"))
from verify_scriptservices_retail import World

SELF, NOW, OLD, DATA = 0x1800000, 0x1810000, 0x1820000, 0x1830000
READ = C.CFUNCTYPE(C.c_uint32, C.c_void_p, C.c_uint32, C.c_uint)
WRITE = C.CFUNCTYPE(None, C.c_void_p, C.c_uint32, C.c_uint, C.c_uint32)


class Api(C.Structure):
    _fields_ = [("user", C.c_void_p), ("read", READ), ("write", WRITE)]


class Material(World):
    def __init__(self, image):
        super().__init__(image)
        self.descend.update({0x38aca0, 0x38acd0, 0x38ad40, 0x38add0, 0x38ae30, 0x38ae90, 0x38aea0})

    def call(self, entry, args):
        raise AssertionError(f"unexpected material leaf {entry:#x}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--elf", type=Path, default=ROOT / "orig/SLUS-20836/SLUS_208.36")
    args = parser.parse_args()
    retail = Material(args.elf.read_bytes())
    native = Material(args.elf.read_bytes())
    read = READ(lambda _, address, width: native.read(address, width))
    write = WRITE(lambda _, address, width, value: native.write(address, width, value))
    api = Api(None, read, write)
    entries = {
        "is_player": 0x38aca0, "is_all_player": 0x38acd0, "get_player_no": 0x38ad40,
        "is_ride_player": 0x38add0, "is_ride_off_player": 0x38ae30,
        "set_run": 0x38ae90, "get_player_status": 0x38aea0,
    }
    count = 0
    with tempfile.TemporaryDirectory(prefix="dw4-material-contact-") as td:
        so = Path(td) / "material.so"
        subprocess.run(["cc", "-shared", "-fPIC", "-std=c99", "-Wall", "-Wextra", "-Werror",
                        str(ROOT / "recovered/engine/material-contact.c"), "-o", str(so)], check=True)
        lib = C.CDLL(str(so))
        functions = {}
        for name in entries:
            fn = getattr(lib, "dw4_mat_" + name)
            fn.argtypes = [C.POINTER(Api), C.c_uint32]
            if name in ("is_ride_player", "is_ride_off_player", "get_player_status", "set_run"):
                fn.argtypes += [C.c_int32 if name != "set_run" else C.c_uint32]
            fn.restype = None if name == "set_run" else C.c_int
            functions[name] = fn

        def compare(name, *values):
            nonlocal count
            native.mem = retail.mem.copy()
            expected = retail.invoke(entries[name], SELF, *values)
            actual = functions[name](C.byref(api), SELF, *values)
            if name != "set_run":
                assert actual == expected, (name, values, actual, expected)
            assert native.mem == retail.mem, (name, "RAM writes differ")
            count += 1

        # Every four-player contact transition and existence roster. Nonzero
        # existence bytes deliberately include 2 and 255, not just booleans.
        for current in range(16):
            for previous in range(16):
                for existence in range(16):
                    index = (current + previous + existence) % 3
                    retail.w(SELF + 40, 4, index)
                    retail.w(SELF + 56, 4, NOW)
                    retail.w(SELF + 60, 4, OLD)
                    retail.w(NOW + 16, 4, DATA)
                    retail.w(OLD + 16, 4, DATA + 0x100)
                    for i in range(3):
                        retail.w(DATA + i * 4, 4, current if i == index else 0xffffffff)
                        retail.w(DATA + 0x100 + i * 4, 4, previous if i == index else 0xffffffff)
                    for i in range(4):
                        retail.w(SELF + 32 + i, 1, (1, 2, 128, 255)[i] if existence & (1 << i) else 0)
                    for name in ("is_player", "is_all_player", "get_player_no"):
                        compare(name)
                    for player in range(4):
                        for name in ("is_ride_player", "is_ride_off_player", "get_player_status"):
                            compare(name, player)
        # High and wrapped SLLV indices, high contact bits, deferred activation
        # byte truncation and preservation of neighboring storage.
        for current, previous in ((0x80000000, 0), (0, 0x80000000), (0xffffffff, 0xffffffff), (16, 0)):
            retail.w(DATA + index * 4, 4, current)
            retail.w(DATA + 0x100 + index * 4, 4, previous)
            compare("is_player")
            for player in (-33, -1, 4, 31, 32, 33, 63):
                for name in ("is_ride_player", "is_ride_off_player", "get_player_status"):
                    compare(name, player)
        for index in (0, 2, 0xffffffff):
            retail.w(SELF + 40, 4, index)
            for value in (0, 1, 2, 255, 256, 257, 0xffffffff):
                retail.w(SELF + 48, 4, 0xa5a5a5a5)
                retail.w(SELF + 52, 4, 0xb6b6b6b6)
                compare("set_run", value)
    print(f"material contact retail: {count:,} exact return/RAM cases; seven engine helpers, no callee leaves")


if __name__ == "__main__":
    main()
