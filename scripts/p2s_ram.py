#!/usr/bin/env python3
"""p2s_ram.py -- read a PCSX2 2.x savestate (.p2s) without the emulator.

A PCSX2 2.x savestate is a **zip archive** whose entries are individually
compressed with **zstd** (zip method 93).  Info-ZIP's `unzip` and Python's
`zipfile` both refuse that method, so the usual "just unzip it" fails with
`rc=81 (unsupported compression method)` -- while still extracting the two
STORED entries (the version id and the screenshot), which makes it look like a
broken archive.  This script parses the zip by hand and calls libzstd's
one-shot `ZSTD_decompress` through ctypes, which needs no Python package.

Entries (PCSX2 2.8.x):
  PCSX2 Savestate Version.id     stored
  PCSX2 Internal Structures.dat  zstd   (CPU state, breakpoints, disc info)
  eeMemory.bin                   zstd   32 MiB  <-- the useful one
  iopMemory.bin                  zstd    2 MiB
  eeHwRegs.bin / iopHwRegs.bin   zstd   64 KiB each
  Scratchpad.bin                 zstd   16 KiB
  vu0Memory.bin / vu1Memory.bin  zstd    4 KiB / 16 KiB
  vu0MicroMem.bin / vu1MicroMem.bin
  SPU2.bin / USB.bin / PAD.bin / GS.bin
  Screenshot.png                 stored (already a PNG)

EE RAM addresses are identical to the pine/live addresses (both are the
32 MiB main RAM from physical 0), so a byte offset into `eeMemory.bin` is the
same number as `pine read <addr>`.

Usage:
  p2s_ram.py state.p2s --list
  p2s_ram.py state.p2s --extract eeMemory.bin --out /tmp/ram.bin
  p2s_ram.py state.p2s --extract Screenshot.png --out /tmp/shot.png
  p2s_ram.py state.p2s                     # list, then extract eeMemory.bin to a temp file

As a module:
  import p2s_ram; ram = p2s_ram.read_entry("state.p2s", "eeMemory.bin")
"""
import argparse
import ctypes
import ctypes.util
import os
import struct
import sys
import tempfile

ZSTD_METHOD = 93
STORE_METHOD = 0
DEFLATE_METHOD = 8

_libzstd = None


def _zstd():
    global _libzstd
    if _libzstd is None:
        path = ctypes.util.find_library("zstd") or "libzstd.so.1"
        lib = ctypes.CDLL(path)
        lib.ZSTD_getFrameContentSize.restype = ctypes.c_ulonglong
        lib.ZSTD_getFrameContentSize.argtypes = [ctypes.c_void_p, ctypes.c_size_t]
        lib.ZSTD_decompress.restype = ctypes.c_size_t
        lib.ZSTD_decompress.argtypes = [ctypes.c_void_p, ctypes.c_size_t,
                                        ctypes.c_void_p, ctypes.c_size_t]
        lib.ZSTD_isError.restype = ctypes.c_uint
        lib.ZSTD_isError.argtypes = [ctypes.c_size_t]
        lib.ZSTD_getErrorName.restype = ctypes.c_char_p
        lib.ZSTD_getErrorName.argtypes = [ctypes.c_size_t]
        _libzstd = lib
    return _libzstd


def _zstd_decompress(src, expected_size=0):
    lib = _zstd()
    srcbuf = ctypes.create_string_buffer(src, len(src))
    size = lib.ZSTD_getFrameContentSize(srcbuf, len(src))
    if size in (0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFE):   # error / unknown
        size = expected_size
    if not size:
        raise RuntimeError("zstd frame size unknown and no expected size given")
    dst = ctypes.create_string_buffer(size)
    got = lib.ZSTD_decompress(dst, size, srcbuf, len(src))
    if lib.ZSTD_isError(got):
        raise RuntimeError("zstd: %s" % lib.ZSTD_getErrorName(got).decode())
    return dst.raw[:got]


def entries(path):
    """Yield (name, method, usize, data_offset, csize) for every local entry."""
    raw = open(path, "rb").read()
    off = 0
    while True:
        i = raw.find(b"PK\x03\x04", off)
        if i < 0:
            return
        (_sig, _ver, flags, method, _t, _d, _crc, csize, usize,
         nlen, xlen) = struct.unpack_from("<IHHHHHIIIHH", raw, i)
        name = raw[i + 30:i + 30 + nlen].decode("utf-8", "replace")
        start = i + 30 + nlen + xlen
        if flags & 0x08:            # sizes only in the trailing data descriptor
            _s2, _c2, csize, usize = struct.unpack_from("<IIII", raw, start + csize)
        yield name, method, usize, start, csize
        off = start + csize


def read_entry(path, name):
    for ename, method, usize, off, csize in entries(path):
        if ename != name:
            continue
        raw = open(path, "rb").read()
        blob = raw[off:off + csize]
        if method == STORE_METHOD:
            return blob
        if method == ZSTD_METHOD:
            return _zstd_decompress(blob, usize)
        if method == DEFLATE_METHOD:
            import zlib
            return zlib.decompress(blob, -15)
        raise RuntimeError("entry %s uses unsupported zip method %d" % (name, method))
    raise KeyError(name)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[1],
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("state")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--extract", metavar="ENTRY", default="eeMemory.bin")
    ap.add_argument("--out")
    a = ap.parse_args()

    print("%s  (%d bytes)" % (a.state, os.path.getsize(a.state)))
    for name, method, usize, off, csize in entries(a.state):
        m = {0: "store", 8: "deflate", 93: "zstd"}.get(method, str(method))
        print("  %-32s %-8s %10d  -> %10d" % (name, m, csize, usize))
    if a.list:
        return 0

    data = read_entry(a.state, a.extract)
    out = a.out or os.path.join(tempfile.gettempdir(),
                                os.path.basename(a.state) + "." + a.extract)
    with open(out, "wb") as f:
        f.write(data)
    print("wrote %s (%d bytes)" % (out, len(data)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
