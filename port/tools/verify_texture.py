#!/usr/bin/env python3
"""verify_texture.py — pixel-exact test of `dw4asset texture` against a reference.

The decode half of P3.4 is testable without a pack: build a synthetic indexed image and
palette, decode them with the C tool, read the PNG back, and compare every pixel with
what the format says it should be.  Two formats are covered (8-bit indices with RGBA8888
entries, 4-bit indices with PS2 CSM1 entries) plus the failure path (inputs too small
must be refused rather than read out of bounds).

Usage: tools/verify_texture.py [path/to/dw4asset]
"""
import os
import struct
import subprocess
import sys
import tempfile
import zlib

HERE = os.path.dirname(os.path.abspath(__file__))


def png_pixels(path):
    """(w, h, rgba bytes) from a PNG this project wrote (8-bit RGBA, filter 0)."""
    d = open(path, 'rb').read()
    assert d[:8] == b'\x89PNG\r\n\x1a\n', 'not a PNG'
    i, idat, w, h = 8, b'', 0, 0
    while i < len(d):
        ln = struct.unpack_from('>I', d, i)[0]
        typ = d[i + 4:i + 8]
        data = d[i + 8:i + 8 + ln]
        if typ == b'IHDR':
            w, h, depth, ctype = struct.unpack_from('>IIBB', data, 0)
            assert (depth, ctype) == (8, 6), 'expected 8-bit RGBA'
        elif typ == b'IDAT':
            idat += data
        i += 12 + ln
    raw = zlib.decompress(idat)
    stride = w * 4
    assert len(raw) == (stride + 1) * h, 'raw size %d != %d' % (len(raw), (stride + 1) * h)
    out = bytearray()
    for y in range(h):
        off = y * (stride + 1)
        assert raw[off] == 0, 'unexpected filter %d' % raw[off]
        out += raw[off + 1:off + 1 + stride]
    return w, h, bytes(out)


def pal_rgba8888(n):
    b = bytearray()
    for i in range(n):
        b += bytes(((i * 7) & 0xff, (i * 13) & 0xff, (i * 29) & 0xff, (i * 3) & 0xff))
    return bytes(b)


def pal_csm1(n):
    out = bytearray()
    for i in range(n):
        v = (i & 0x1f) | (((i * 3) & 0x1f) << 5) | (((i * 5) & 0x1f) << 10) | (0x8000 if i % 2 else 0)
        out += struct.pack('<H', v)
    return bytes(out)


def csm1_expand(v):
    return (((v >> 0) & 0x1f) * 255 // 31,
            ((v >> 5) & 0x1f) * 255 // 31,
            ((v >> 10) & 0x1f) * 255 // 31,
            255 if v & 0x8000 else 0)


def case8(tool, tmp):
    w, h = 9, 5
    idx = bytes(((x * 31 + y * 17) & 0xff) for y in range(h) for x in range(w))
    pal = pal_rgba8888(256)
    ip, pp, op = os.path.join(tmp, 'i8.raw'), os.path.join(tmp, 'p8.raw'), os.path.join(tmp, 'o8.png')
    open(ip, 'wb').write(idx)
    open(pp, 'wb').write(pal)
    r = subprocess.run([tool, 'texture', ip, op, '--w', str(w), '--h', str(h),
                        '--bits', '8', '--pal', pp], capture_output=True, text=True)
    assert r.returncode == 0, r.stderr
    gw, gh, got = png_pixels(op)
    assert (gw, gh) == (w, h)
    for y in range(h):
        for x in range(w):
            e = pal[idx[y * w + x] * 4:idx[y * w + x] * 4 + 4]
            g = got[(y * w + x) * 4:(y * w + x) * 4 + 4]
            assert g == e, 'pixel (%d,%d): %s != %s' % (x, y, list(g), list(e))
    return '8-bit RGBA8888 %dx%d: %d pixels exact' % (w, h, w * h)


def case4(tool, tmp):
    w, h, bits = 6, 4, 4
    packed = (w * bits + 7) // 8
    idx = bytearray()
    for y in range(h):
        row = bytes(((x * 5 + y * 3) & 0x0f) for x in range(w))
        for x in range(0, w, 2):
            idx.append((row[x] << 4) | (row[x + 1] if x + 1 < w else 0))
    pal = pal_csm1(16)
    ip, pp, op = os.path.join(tmp, 'i4.raw'), os.path.join(tmp, 'p4.raw'), os.path.join(tmp, 'o4.png')
    open(ip, 'wb').write(idx)
    open(pp, 'wb').write(pal)
    r = subprocess.run([tool, 'texture', ip, op, '--w', str(w), '--h', str(h), '--bits', '4',
                        '--bpr', str(packed), '--pal', pp, '--pal-entries', '16',
                        '--pal-mode', 'ps2csm1'], capture_output=True, text=True)
    assert r.returncode == 0, r.stderr
    gw, gh, got = png_pixels(op)
    assert (gw, gh) == (w, h)
    for y in range(h):
        for x in range(w):
            row = idx[y * packed:y * packed + packed]
            b = row[x >> 1]
            i = (b & 0x0f) if (x & 1) else (b >> 4)
            v = struct.unpack_from('<H', pal, i * 2)[0]
            e = bytes(csm1_expand(v))
            g = got[(y * w + x) * 4:(y * w + x) * 4 + 4]
            assert g == e, 'pixel (%d,%d): %s != %s' % (x, y, list(g), list(e))
    return '4-bit PS2 CSM1 %dx%d: %d pixels exact' % (w, h, w * h)


def case_short(tool, tmp):
    ip = os.path.join(tmp, 'short.raw')
    pp = os.path.join(tmp, 'short_pal.raw')
    open(ip, 'wb').write(b'\x00' * 16)          # only 16 bytes for 32x32x8bpp
    open(pp, 'wb').write(pal_rgba8888(4))
    r = subprocess.run([tool, 'texture', ip, os.path.join(tmp, 'nope.png'), '--w', '32',
                        '--h', '32', '--bits', '8', '--pal', pp], capture_output=True, text=True)
    assert r.returncode == 1, 'expected refusal, got %d' % r.returncode
    assert not os.path.exists(os.path.join(tmp, 'nope.png')), 'wrote an output anyway'
    return 'short inputs refused, no output written'


def main():
    tool = sys.argv[1] if len(sys.argv) > 1 else os.path.join(HERE, '..', 'build', 'dw4asset')
    if not os.path.exists(tool):
        raise SystemExit('no %s — build first (make)' % tool)
    with tempfile.TemporaryDirectory() as tmp:
        for fn in (case8, case4, case_short):
            print('  ' + fn(tool, tmp))
    print('verify_texture: all cases pass')


if __name__ == '__main__':
    main()
