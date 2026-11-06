#!/usr/bin/env python3
"""gsdump.py — read a PCSX2 `.gs` (or `.gs.zst`) GS dump: its header, the freeze state, the GIF
stream, and the texture the GS actually sampled out of VRAM.

The .gs format (PCSX2 `GS/GSDump.cpp`, `GSDumpBase::AddHeader`):

    u32 0xFFFFFFFF, u32 header_size, GSDumpHeader {state_version, state_size, serial_offset,
    serial_size, crc, screenshot_w, screenshot_h, screenshot_offset, screenshot_size}, serial
    (serial_offset bytes from the end of the two leading u32), screenshot (w*h*4), the freeze data
    (state_size bytes), a GSPrivRegSet, then a record stream:

        transfer : u8 0, u8 index, u32 size, size bytes of GIF data
        readfifo : u8 2, u32 size                       (size in qwords, 16 bytes each)
        vsync    : u8 3, GSPrivRegSet, u8 1, u8 field

    NOTE the header field order: PCSX2 2.8.x (which wrote this dump) has `serial_offset` third and
    `crc` fifth; master reordered `crc` third.  We read the 2.8.x order and print the serial, which
    is self-checking (it lands on a `SLUS-`/`SCUS-` string either way or not).

The freeze data is the whole drawing environment in `GSState::GetSaveStateSize` order.  Its last
84 bytes are `4 * (GIFPath.tag + GIFPath.reg)` (80) plus `m_q` (4), so the 4 MB of GS VRAM is the
`state_size - 84` bytes before them:

    u32 STATE_VERSION, then the GIFReg fields (m_env.PRIM, PRMODECONT, TEXCLUT, SCANMSK, TEXA,
    FOGCOL, DIMX, DTHE, COLCLAMP, PABE, BITBLTBUF, TRXDIR, TRXPOS, TRXREG twice), then for context
    i=0,1 {XYOFFSET, TEX0, TEX1, CLAMP, MIPTBP1, MIPTBP2, SCISSOR, ALPHA, TEST, FBA, FRAME, ZBUF},
    then m_v.{RGBAQ, ST, UV, FOG, XYZ} and one obsolete GIFReg, then m_tr, then the VRAM, then the
    four GIFPath {tag, reg} pairs, then m_q.

`--state` prints the header and the fields this frame's draws use.  `--draws` tracks the PACKED
register cycle (the A_D state writes) and the vertex packets, so every draw's TEX0/PRIM/ALPHA/TEST
and its per-vertex RGBA/ST/XYZ come out (the vertex format here is the PACKED
`NREG=3` STQRGBAXYZF2 complex type — STQ, RGBA, XYZF2 — not STQ+UV+XYZF2, so there *is* a
per-vertex colour).  `--tex TEX0 --tex-out F.png` decodes a texture out of the dump's VRAM with the
GS swizzle and CLUT, which is how the world's P11G00n binding was settled.
"""
import argparse
import ctypes
import ctypes.util
import struct
import sys
from collections import Counter

VM_SIZE = 1024 * 1024 * 4

STATE_NAMES = {0: "PRIM", 1: "RGBAQ", 2: "ST", 3: "UV", 4: "XYZF2", 5: "XYZ2", 6: "TEX0_1",
               7: "TEX0_2", 8: "CLAMP_1", 9: "CLAMP_2", 10: "FOG", 14: "A_D", 15: "NOP"}


# ---------------------------------------------------------------------------------------------------
# reading
# ---------------------------------------------------------------------------------------------------

def _zstd_decompress(raw):
    """Decompress a .gs.zst with libzstd (ctypes, so no Python package is needed)."""
    lib = ctypes.CDLL(ctypes.util.find_library("zstd") or "libzstd.so.1")
    lib.ZSTD_createDStream.restype = ctypes.c_void_p
    lib.ZSTD_initDStream.argtypes = [ctypes.c_void_p]
    lib.ZSTD_decompressStream.restype = ctypes.c_size_t
    lib.ZSTD_decompressStream.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p]
    lib.ZSTD_isError.argtypes = [ctypes.c_size_t]

    class In(ctypes.Structure):
        _fields_ = [("src", ctypes.c_void_p), ("size", ctypes.c_size_t), ("pos", ctypes.c_size_t)]

    class Out(ctypes.Structure):
        _fields_ = [("dst", ctypes.c_void_p), ("size", ctypes.c_size_t), ("pos", ctypes.c_size_t)]

    src = ctypes.create_string_buffer(raw, len(raw))
    ib = In(ctypes.cast(src, ctypes.c_void_p), len(raw), 0)
    out = bytearray()
    ds = lib.ZSTD_createDStream()
    lib.ZSTD_initDStream(ds)
    chunk = ctypes.create_string_buffer(1 << 20)
    while ib.pos < ib.size:
        ob = Out(ctypes.cast(chunk, ctypes.c_void_p), len(chunk), 0)
        r = lib.ZSTD_decompressStream(ds, ctypes.byref(ob), ctypes.byref(ib))
        if lib.ZSTD_isError(r):
            raise SystemExit("gsdump: zstd error %d" % r)
        out += chunk.raw[:ob.pos]
        if r == 0:
            break
    return bytes(out)


def read_dump(path):
    raw = open(path, "rb").read()
    if path.endswith(".zst") or raw[:4] != b"\xff\xff\xff\xff":
        raw = _zstd_decompress(raw)
    if raw[:4] != b"\xff\xff\xff\xff":
        raise SystemExit("%s: not a PCSX2 .gs dump (no 0xFFFFFFFF header marker)" % path)
    fake_crc, header_size = struct.unpack_from("<II", raw, 0)
    (state_version, state_size, serial_off, serial_size, crc, sw, sh, shot_off, shot_size) = \
        struct.unpack_from("<9I", raw, 8)
    serial = raw[8 + serial_off:8 + serial_off + serial_size].decode("latin-1")
    body = 8 + header_size
    return {"raw": raw, "crc": crc, "serial": serial, "state_version": state_version,
            "state_size": state_size, "state": body, "size": len(raw), "resolution": (sw, sh)}


def records(d):
    """Walk the record stream; yields (offset, kind, index, payload).  The GSPrivRegSet that follows
    the freeze data has no size in the header, so the stream start is found by looking for the first
    offset whose transfer chain walks to the end of the file."""
    raw, base, N = d["raw"], d["state"] + d["state_size"], d["size"]

    def walk(start, regs_size):
        off, n = start, 0
        while off + 6 <= N:
            m = raw[off]
            if m == 0:
                size = struct.unpack_from("<I", raw, off + 2)[0]
                if size < 16 or size > 0x400000 or off + 6 + size > N:
                    return None
                off += 6 + size
            elif m == 2:
                size = struct.unpack_from("<I", raw, off + 1)[0]
                if size > 0x100000:
                    return None
                off += 5 + size * 16
            elif m == 3:
                off += 1 + regs_size + 2
            else:
                return None
            n += 1
        return n if abs(off - N) <= 64 else None

    start = None
    for regs_size in range(0x200, 0x4000):
        cand = base + regs_size
        if cand + 6 > N or raw[cand] != 0:
            continue
        size = struct.unpack_from("<I", raw, cand + 2)[0]
        if size < 16 or size > 0x100000:
            continue
        if walk(cand, regs_size):
            start = cand
            break
    if start is None:
        raise SystemExit("could not find the record stream (GSPrivRegSet size unknown)")
    d["regs_size"] = regs_size
    off = start
    while off + 6 <= N:
        m = raw[off]
        if m == 0:
            idx = raw[off + 1]
            size = struct.unpack_from("<I", raw, off + 2)[0]
            yield off, "transfer", idx, raw[off + 6:off + 6 + size]
            off += 6 + size
        elif m == 2:
            size = struct.unpack_from("<I", raw, off + 1)[0]
            yield off, "readfifo", None, b""
            off += 5 + size * 16
        elif m == 3:
            yield off, "vsync", None, raw[off + 1:off + 1 + regs_size]
            off += 1 + regs_size + 2
        else:
            off += 1


def packets(payload):
    """(offset_in_payload, tag_info, data) for each GIF packet; the generator stops when malformed.

    tag_info = (nloop, eop, pre, prim, flg, nreg, tag_u64)."""
    off, n = 0, len(payload)
    while off + 16 <= n:
        t = struct.unpack_from("<Q", payload, off)[0]
        nloop = t & 0x7fff
        eop = (t >> 15) & 1
        pre = (t >> 46) & 1
        prim = (t >> 47) & 0x7ff
        flg = (t >> 58) & 3
        nreg = (t >> 60) & 0xf or 16
        if not (1 <= nloop <= 0x7fff):
            return
        if flg == 0:
            length = 16 + nloop * nreg * 16
        elif flg == 1:
            length = 16 + nreg * 8 + nloop * nreg * 8
        else:                                    # IMAGE: continues to an EOP tag
            length = 16 + nloop * 16
            e = eop
            guard = 0
            while not e and off + length + 16 <= n:
                t2 = struct.unpack_from("<Q", payload, off + length)[0]
                length += 16 + (t2 & 0x7fff) * 16
                e = (t2 >> 15) & 1
                guard += 1
                if guard > 64:
                    return
        if off + length > n:
            return
        yield off, (nloop, eop, pre, prim, flg, nreg, t), payload[off + 16:off + length]
        off += length


# ---------------------------------------------------------------------------------------------------
# the freeze state
# ---------------------------------------------------------------------------------------------------

# the first GIFReg field is at +4 (STATE_VERSION is +0) and each is 8 bytes; the two contexts are at
# +124 and +220, and m_v follows them at +316.  These offsets are read straight off the Freeze order
# above, and the tail (VRAM + GIFPath + m_q) fixes the whole block's size (state_size - 84 - 4 MB).
_ENV_FIELDS = ["PRIM", "PRMODECONT", "TEXCLUT", "SCANMSK", "TEXA", "FOGCOL", "DIMX", "DTHE",
               "COLCLAMP", "PABE", "BITBLTBUF", "TRXDIR", "TRXPOS", "TRXREG"]
_CTX_FIELDS = ["XYOFFSET", "TEX0", "TEX1", "CLAMP", "MIPTBP1", "MIPTBP2", "SCISSOR", "ALPHA",
               "TEST", "FBA", "FRAME", "ZBUF"]
_MV_FIELDS = ["RGBAQ", "ST", "UV", "FOG", "XYZ"]
CTX_OFF = 124
CTX_STRIDE = 96
MV_OFF = CTX_OFF + 2 * CTX_STRIDE


def read_state(d):
    """The freeze data as {name: u64} plus `VRAM` (bytes) and `GIFPath` (list of (tag_u64, reg))."""
    raw, fz, ss = d["raw"], d["state"], d["state_size"]
    u64 = lambda o: struct.unpack_from("<Q", raw, fz + o)[0]
    out = {"STATE_VERSION": struct.unpack_from("<I", raw, fz)[0]}
    for i, nm in enumerate(_ENV_FIELDS):
        out[nm] = u64(4 + 8 * i)
    for c, ctx in enumerate(("CTXT0", "CTXT1")):
        for i, nm in enumerate(_CTX_FIELDS):
            out["%s.%s" % (ctx, nm)] = u64(CTX_OFF + c * CTX_STRIDE + 8 * i)
    for i, nm in enumerate(_MV_FIELDS):
        out["m_v.%s" % nm] = u64(MV_OFF + 8 * i)
    pre_vram = ss - VM_SIZE - 4 * (16 + 4) - 4      # GIFPath tag+reg per path (4) and m_q
    out["VRAM"] = raw[fz + pre_vram:fz + pre_vram + VM_SIZE]
    paths = []
    for p in range(4):
        base = fz + pre_vram + VM_SIZE + p * 20
        tag = struct.unpack_from("<Q", raw, base)[0]
        reg = struct.unpack_from("<I", raw, base + 16)[0]
        paths.append((tag, reg))
    out["GIFPath"] = paths
    return out


def tex0_fields(v):
    """Decode a GIFRegTEX0 (GSRegs.h): the 8 and 4-bit sizes are 2**TW x 2**TH."""
    low = v & 0xffffffff
    return {"TBP0": (low & 0x3fff) * 256, "TBW": (low >> 14) & 0x3f, "PSM": (low >> 20) & 0x3f,
            "TW": 1 << ((low >> 26) & 0xf), "TH": 1 << ((v >> 30) & 0xf),
            "TCC": (v >> 34) & 1, "TFX": (v >> 35) & 3, "CBP": ((v >> 37) & 0x3fff) * 256,
            "CPSM": (v >> 51) & 0xf, "CSM": (v >> 55) & 1, "CSA": (v >> 56) & 0x1f}


def prim_fields(v):
    return {"PRIM": v & 7, "IIP": (v >> 3) & 1, "TME": (v >> 4) & 1, "FGE": (v >> 5) & 1,
            "ABE": (v >> 6) & 1, "AA1": (v >> 7) & 1, "FST": (v >> 8) & 1, "CTXT": (v >> 9) & 1,
            "FIX": (v >> 10) & 1}


def alpha_fields(v):
    return {"A": v & 3, "B": (v >> 2) & 3, "C": (v >> 4) & 3, "D": (v >> 6) & 3,
            "FIX": (v >> 32) & 0xff}


def tex1_fields(v):
    return {"LCM": v & 1, "MXL": (v >> 2) & 7, "MMAG": (v >> 5) & 1, "MMIN": (v >> 6) & 7,
            "MTBA": (v >> 9) & 1, "L": (v >> 19) & 3, "K": (v >> 32) & 0xfff}


# ---------------------------------------------------------------------------------------------------
# the GIF stream: A_D state + the vertex packets
# ---------------------------------------------------------------------------------------------------

def _unpack_regs(regs, nreg):
    """PCSX2 `GIFPath::SetTag`: regs = unpacklo_epi8(REGS, REGS >> 4) & 0x0f(nreg).  The nibble for
    register j comes out at byte j, which is what decides the complex packet type."""
    b = [(regs >> (8 * i)) & 0xff for i in range(8)]
    s = []
    for lane in (regs & 0xffffffff, (regs >> 32) & 0xffffffff):
        t = lane >> 4
        s += [t & 0xff, (t >> 8) & 0xff, (t >> 16) & 0xff, (t >> 24) & 0xff]
    out = []
    for i in range(4):
        out += [b[2 * i], s[2 * i], b[2 * i + 1], s[2 * i + 1]]
    return tuple(x & 0xf for x in out[:nreg])


def draws(d):
    """Yield one dict per draw packet with the state at the time it was issued.

    A_D packets (all registers 0x0e) update the register map; the two vertex formats are the PACKED
    STQRGBAXYZF2 (regs 2,1,4: 3 x 16 bytes per vertex) and RGBA+XYZF2 (regs 1,4: 2 x 16 bytes).

    The *effective* PRIM follows PCSX2's `ApplyPRIM`/`GIFRegHandlerPRMODE`: while `PRMODECONT.AC`
    is 0 (the state here) the non-class bits come from the last PRMODE write, and a PACKED tag with
    `PRE=1` replaces only the 3-bit primitive class (`tag.PRIM & 7`)."""
    st = {}
    fs = read_state(d)
    prim = fs["PRIM"]
    ac = fs["PRMODECONT"] & 1

    def apply_prim(v):
        """PCSX2's ApplyPRIM: the full 11-bit PRIM when PRMODECONT.AC=1, otherwise only the class."""
        nonlocal prim
        prim = v if ac else (prim & ~7) | (v & 7)

    def set_prmode(v):
        """PCSX2's GIFRegHandlerPRMODE: the value supplies every bit but the class."""
        nonlocal prim
        prim = (v & ~7) | (prim & 7)

    vsync = 0
    for _off, kind, _idx, payload in records(d):
        if kind == "vsync":
            vsync += 1
        if kind != "transfer":
            continue
        for po, tag, data in packets(payload):
            nloop, eop, pre, tag_prim, flg, nreg, t = tag
            if flg != 0:
                continue
            regs = struct.unpack_from("<Q", payload, po + 8)[0]
            rl = _unpack_regs(regs, nreg)
            if all(r == 0x0e for r in rl):
                for k in range(nloop * nreg):
                    ch = data[k * 16:(k + 1) * 16]
                    addr = ch[8]
                    val = struct.unpack_from("<Q", ch, 0)[0]
                    st[addr] = val
                    if addr == 0x1a:            # PRMODECONT
                        ac = val & 1
                    elif addr == 0x1b:          # PRMODE
                        set_prmode(val)
                    elif addr == 0x00:          # PRIM
                        apply_prim(val)
                continue
            if pre:
                apply_prim(tag_prim)
            snap = dict(st)
            snap["PRIM_EFF"] = prim
            if nreg == 3 and rl[:3] == (2, 1, 4):
                verts = []
                for v in range(nloop):
                    b = data[v * 48:v * 48 + 48]
                    verts.append({"ST": struct.unpack_from("<3f", b, 0),
                                  "RGBA": (b[16], b[20], b[24], b[28]),
                                  "FOG": (struct.unpack_from("<I", b, 44)[0] >> 4) & 0xff,
                                  "XYZ": struct.unpack_from("<3I", b, 32),
                                  "Z": (struct.unpack_from("<I",b,40)[0]>>4)&0xffffff,
                                  "ADC": bool(struct.unpack_from("<I",b,44)[0]&0x8000)})
                yield {"kind": "STQRGBAXYZF2", "n": nloop, "verts": verts, "state": snap,
                       "vsync": vsync, "record_offset": _off, "packet_offset": po}
            elif nreg == 2 and rl[:2] == (1, 4):
                verts = []
                for v in range(nloop):
                    b = data[v * 32:v * 32 + 32]
                    verts.append({"RGBA": (b[0], b[4], b[8], b[12]),
                                  "XYZ": struct.unpack_from("<3I", b, 16),
                                  "Z": (struct.unpack_from("<I",b,24)[0]>>4)&0xffffff,
                                  "ADC": bool(struct.unpack_from("<I",b,28)[0]&0x8000)})
                yield {"kind": "RGBAXYZF2", "n": nloop, "verts": verts, "state": snap,
                       "vsync": vsync, "record_offset": _off, "packet_offset": po}


# ---------------------------------------------------------------------------------------------------
# decoding a texture out of the dump's VRAM (PSMT8 + CT32 CLUT)
# ---------------------------------------------------------------------------------------------------

# GSTables.cpp / GSOffset for swizzle8: page 128x64, blocks 16x16, 8 blocks wide x 4 high.
_BLOCK8 = [[0, 1, 4, 5, 16, 17, 20, 21], [2, 3, 6, 7, 18, 19, 22, 23],
           [8, 9, 12, 13, 24, 25, 28, 29], [10, 11, 14, 15, 26, 27, 30, 31]]
_COL8 = [
    [0, 4, 16, 20, 32, 36, 48, 52, 2, 6, 18, 22, 34, 38, 50, 54],
    [8, 12, 24, 28, 40, 44, 56, 60, 10, 14, 26, 30, 42, 46, 58, 62],
    [33, 37, 49, 53, 1, 5, 17, 21, 35, 39, 51, 55, 3, 7, 19, 23],
    [41, 45, 57, 61, 9, 13, 25, 29, 43, 47, 59, 63, 11, 15, 27, 31],
    [96, 100, 112, 116, 64, 68, 80, 84, 98, 102, 114, 118, 66, 70, 82, 86],
    [104, 108, 120, 124, 72, 76, 88, 92, 106, 110, 122, 126, 74, 78, 90, 94],
    [65, 69, 81, 85, 97, 101, 113, 117, 67, 71, 83, 87, 99, 103, 115, 119],
    [73, 77, 89, 93, 105, 109, 121, 125, 75, 79, 91, 95, 107, 111, 123, 127],
    [128, 132, 144, 148, 160, 164, 176, 180, 130, 134, 146, 150, 162, 166, 178, 182],
    [136, 140, 152, 156, 168, 172, 184, 188, 138, 142, 154, 158, 170, 174, 186, 190],
    [161, 165, 177, 181, 129, 133, 145, 149, 163, 167, 179, 183, 131, 135, 147, 151],
    [169, 173, 185, 189, 137, 141, 153, 157, 171, 175, 187, 191, 139, 143, 155, 159],
    [224, 228, 240, 244, 192, 196, 208, 212, 226, 230, 242, 246, 194, 198, 210, 214],
    [232, 236, 248, 252, 200, 204, 216, 220, 234, 238, 250, 254, 202, 206, 218, 222],
    [193, 197, 209, 213, 225, 229, 241, 245, 195, 199, 211, 215, 227, 231, 243, 247],
    [201, 205, 217, 221, 233, 237, 249, 253, 203, 207, 219, 223, 235, 239, 251, 255]]
_CLUT_T32_I8 = [
    0, 1, 4, 5, 8, 9, 12, 13, 2, 3, 6, 7, 10, 11, 14, 15,
    64, 65, 68, 69, 72, 73, 76, 77, 66, 67, 70, 71, 74, 75, 78, 79,
    16, 17, 20, 21, 24, 25, 28, 29, 18, 19, 22, 23, 26, 27, 30, 31,
    80, 81, 84, 85, 88, 89, 92, 93, 82, 83, 86, 87, 90, 91, 94, 95,
    32, 33, 36, 37, 40, 41, 44, 45, 34, 35, 38, 39, 42, 43, 46, 47,
    96, 97, 100, 101, 104, 105, 108, 109, 98, 99, 102, 103, 106, 107, 110, 111,
    48, 49, 52, 53, 56, 57, 60, 61, 50, 51, 54, 55, 58, 59, 62, 63,
    112, 113, 116, 117, 120, 121, 124, 125, 114, 115, 118, 119, 122, 123, 126, 127]


def px_offset8(x, y):
    page_x = x // 128
    sub_x = x % 128
    block = _BLOCK8[(y // 16) % 4][(sub_x // 16) % 8]
    return page_x * 8192 + block * 256 + _COL8[y % 16][sub_x % 16]


def texel8(vram, t, x, y):
    """The byte the GS's PSM=19 addressing gives for texel (x, y), from GIFRegTEX0 fields."""
    bw_pg = t["TBW"] >> 1
    base = t["TBP0"] + (((y & ~63) * bw_pg) << 7)
    return vram[base + px_offset8(x, y)]


def _u16(v):
    return [v[0] & 0xffff, (v[0] >> 16) & 0xffff, v[1] & 0xffff, (v[1] >> 16) & 0xffff,
            v[2] & 0xffff, (v[2] >> 16) & 0xffff, v[3] & 0xffff, (v[3] >> 16) & 0xffff]


def _u32(u):
    return [u[0] | (u[1] << 16), u[2] | (u[3] << 16), u[4] | (u[5] << 16), u[6] | (u[7] << 16)]


def _upl16(a, b):
    a, b = _u16(a), _u16(b)
    return _u32([a[0], b[0], a[1], b[1], a[2], b[2], a[3], b[3]])


def _uph16(a, b):
    a, b = _u16(a), _u16(b)
    return _u32([a[4], b[4], a[5], b[5], a[6], b[6], a[7], b[7]])


def _upl32(a, b):
    return [a[0], b[0], a[1], b[1]]


def _uph32(a, b):
    return [a[2], b[2], a[3], b[3]]


def _sw16(a, b, c, d):
    e, f = list(a), list(c)
    return _upl16(e, b), _upl16(f, d), _uph16(e, b), _uph16(f, d)


def _sw32(a, b, c, d):
    e, f = list(a), list(c)
    return _upl32(e, b), _upl32(f, d), _uph32(e, b), _uph32(f, d)


def _write_clut_t32_i4(vram_u32, s):
    v = [list(vram_u32[s + k:s + k + 4]) for k in (0, 4, 8, 12)]
    v0, v1, v2, v3 = _sw16(v[0], v[1], v[2], v[3])
    v0, v1, v2, v3 = _sw32(v0, v1, v2, v3)
    v0, v2, v1, v3 = _sw16(v0, v2, v1, v3)
    return v0, v2, v1, v3       # d[0], d[1], d[32], d[33]


def clut32_i8(vram, cbp, csa=0):
    """The 256-entry PSMT8 palette, in *logical index* order (GSClut::WriteCLUT32_I8_CSM1 /
    ReadCLUT_T32_I8).  Returns a list of 256 ABGR words as the GS stores them."""
    vram_u32 = struct.unpack_from("<%dI" % (len(vram) // 4), vram, 0)
    base = cbp // 4
    m = [0] * 512
    for i in range(csa, 16):
        off = i << 4
        s = _CLUT_T32_I8[off & 0x70] | (off & 0x80)
        d0, d1, d32, d33 = _write_clut_t32_i4(vram_u32, base + s)
        m[i * 8:i * 8 + 4] = d0
        m[i * 8 + 4:i * 8 + 8] = d1
        m[i * 8 + 128:i * 8 + 132] = d32
        m[i * 8 + 132:i * 8 + 136] = d33
    dst = [0] * 256
    for i in range(0, 256, 16):
        base = min(i + csa, 240) // 2
        # s = (GSVector4i*)&clut[min(i,240)]: s[k] is 4 u32 at base + 4k (16 bytes per vector)
        v = [list(m[base + k:base + k + 4]) for k in (0, 4, 128, 132)]
        v0, v2, v1, v3 = _sw16(v[0], v[2], v[1], v[3])
        dst[i:i + 4] = v0
        dst[i + 4:i + 8] = v1
        dst[i + 8:i + 12] = v2
        dst[i + 12:i + 16] = v3
    return dst


def texture_rgba(d, tex0):
    """(rgba_bytes, w, h, fields) for a PSM=19 (PSMT8) texture with a CT32 CLUT."""
    t = tex0_fields(tex0)
    if t["PSM"] != 19:
        raise SystemExit("gsdump: only PSM=19 (PSMT8) textures are decoded (this one is PSM=%d)"
                         % t["PSM"])
    vram = read_state(d)["VRAM"]
    pal = clut32_i8(vram, t["CBP"], t["CSA"])
    w, h = t["TW"], t["TH"]
    out = bytearray(w * h * 4)
    for y in range(h):
        for x in range(w):
            c = pal[texel8(vram, t, x, y)]
            o = 4 * (y * w + x)
            out[o] = c & 0xff
            out[o + 1] = (c >> 8) & 0xff
            out[o + 2] = (c >> 16) & 0xff
            out[o + 3] = (c >> 24) & 0xff
    return bytes(out), w, h, t


# ---------------------------------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------------------------------

def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("dump")
    ap.add_argument("--head", action="store_true", help="dump header + record census")
    ap.add_argument("--state", action="store_true", help="print the freeze state's draw fields")
    ap.add_argument("--draws", action="store_true", help="per-draw TEX0/PRIM/RGBA census")
    ap.add_argument("--rgbaq", action="store_true",
                    help="single-register RGBAQ-shaped writes and what follows them")
    ap.add_argument("--tex", type=lambda s: int(s, 0), default=None,
                    help="decode this TEX0 value out of VRAM (PSMT8)")
    ap.add_argument("--tex-out", default=None, help="PNG for --tex")
    ap.add_argument("--limit", type=int, default=40)
    a = ap.parse_args()

    d = read_dump(a.dump)
    if a.head or not (a.state or a.draws or a.rgbaq or a.tex):
        print("%s: serial %r crc %#x state_version %d state_size %d resolution %dx%d" % (
            a.dump, d["serial"], d["crc"], d["state_version"], d["state_size"], *d["resolution"]))
    kinds, idxs = Counter(), Counter()
    n = 0
    for _off, kind, idx, _payload in records(d):
        kinds[kind] += 1
        idxs[idx] += 1
        n += 1
    if a.head or not (a.state or a.draws or a.rgbaq or a.tex):
        print("records: %d  %s  indices %s" % (n, dict(kinds), dict(idxs)))

    if a.state:
        s = read_state(d)
        print("STATE_VERSION %d  PRIM %#018x  RGBAQ %#018x" % (
            s["STATE_VERSION"], s["PRIM"], s["m_v.RGBAQ"]))
        pf = prim_fields(s["PRIM"])
        print("  PRIM: prim %d iip %d tme %d fge %d abe %d ctxt %d" % (
            pf["PRIM"], pf["IIP"], pf["TME"], pf["FGE"], pf["ABE"], pf["CTXT"]))
        for ctx in ("CTXT0", "CTXT1"):
            t0 = s["%s.TEX0" % ctx]
            tf = tex0_fields(t0)
            af = alpha_fields(s["%s.ALPHA" % ctx])
            e1 = tex1_fields(s["%s.TEX1" % ctx])
            print("  %s TEX0 %#018x -> TBP %#x %dx%d PSM %d CBP %#x CPSM %d" % (
                ctx, t0, tf["TBP0"], tf["TW"], tf["TH"], tf["PSM"], tf["CBP"], tf["CPSM"]))
            print("       TEX1 MMAG %d MMIN %d MXL %d | ALPHA A%d B%d C%d D%d FIX %d" % (
                e1["MMAG"], e1["MMIN"], e1["MXL"], af["A"], af["B"], af["C"], af["D"], af["FIX"]))
        print("  GIFPath: " + " ".join("nloop %d nreg %d reg %d" % (t & 0x7fff, (t >> 60) & 0xf, r)
                                       for t, r in s["GIFPath"]))

    if a.draws:
        by = Counter()
        nv = 0
        for dr in draws(d):
            st = dr["state"]
            key = (st.get(6), st.get("PRIM_EFF"))
            by[key] += dr["n"]
            nv += dr["n"]
        print("draws: %d vertices" % nv)
        for (t0, prim), n in by.most_common(20):
            if t0 is None:
                continue
            tf = tex0_fields(t0)
            pf = prim_fields(prim) if prim is not None else {"PRIM": "?", "TME": 0}
            print("  TEX0 %#018x TBP %#x %dx%d PSM %d CBP %#x | PRIM %#x prim %s TME %d ABE %d IIP %d | %d vert(s)" % (
                t0, tf["TBP0"], tf["TW"], tf["TH"], tf["PSM"], tf["CBP"], prim,
                pf["PRIM"], pf["TME"], pf["ABE"], pf["IIP"], n))

    if a.tex is not None:
        data, w, h, t = texture_rgba(d, a.tex)
        print("TEX0 %#x -> TBP %#x TBW %d PSM %d %dx%d CBP %#x CPSM %d" % (
            a.tex, t["TBP0"], t["TBW"], t["PSM"], w, h, t["CBP"], t["CPSM"]))
        if a.tex_out:
            try:
                from PIL import Image
            except ImportError:
                raise SystemExit("gsdump: --tex-out needs Pillow")
            Image.frombytes("RGBA", (w, h), data).save(a.tex_out)
            print("wrote %s" % a.tex_out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
