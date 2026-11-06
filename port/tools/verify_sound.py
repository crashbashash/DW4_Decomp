#!/usr/bin/env python3
"""verify_sound.py — exact test of the C sound reader against ffmpeg.

Two decoders read the same bytes: the port's `dw4asset sfp` builds a bank's VAG ADPCM
into a WAV, and ffmpeg's `adpcm_psx` reads the same ADPCM wrapped in a `VAGp` header.
They must agree sample-for-sample — that is what pins the three details a plain VAG
decoder gets wrong (byte 1 is a control byte, the samples start at byte 2, and the
predictor feeds back the unclamped sample).  The reference is ffmpeg, not a second copy
of our own reading.

Also checked: the bank table the C reader prints (offset, pcm/vag sizes, rate, entry
count) against a straight Python scan of the pack, and that the entry ranges tile the
VAGD chunk exactly.

Usage: tools/verify_sound.py [path/to/dw4asset] [path/to/sound-pack.bin]
"""
import os
import struct
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
COEF_RATE = 24000


def banks_of(pack):
    """[(off, pcm_size, vag_size, header_size, vag_data, rate, [(start, end)])]"""
    out = []
    i = 0
    while True:
        off = pack.find(b'ps2_DTPK', i)
        if off < 0:
            break
        i = off + 8
        pcm = struct.unpack_from('<I', pack, off + 0x0c)[0]
        vag_size = struct.unpack_from('<I', pack, off + 0x18)[0]
        header = struct.unpack_from('<I', pack, off + 0x1c)[0]
        assert pack[off + 0x60:off + 0x68] == b'ps2_TBLD'
        assert pack[off + header:off + header + 8] == b'ps2_VAGD'
        assert struct.unpack_from('<I', pack, off + header + 0x0c)[0] == vag_size
        # the entry-record table: 16-byte records, rate (u16 LE) at record+2; the table
        # is not aligned to the TBLD, so find the longest run carrying the same rate
        tbl, vag = off + 0x60, off + header
        best, bestn, pos = 0, 0, tbl
        while True:
            q = pack.find(b'\xc0\x5d', pos, vag)
            if q < 0 or q < 2:
                break
            s, n = q - 2, 0
            while s + 16 * (n + 1) <= vag and pack[s + 16 * n + 2:s + 16 * n + 4] == b'\xc0\x5d':
                n += 1
            if n > bestn:
                best, bestn = s, n
            pos = q + 2
        recs = [best + 16 * k for k in range(bestn)]
        assert recs, 'no entry records in bank @0x%x' % off
        rate = struct.unpack_from('<H', pack, recs[0] + 2)[0]
        entries, prev = [], header
        for r in recs:
            end = struct.unpack_from('<I', pack, r + 8)[0] or (header + vag_size)
            entries.append((prev, end))
            prev = end
        assert prev == header + vag_size, 'entry ranges do not tile the chunk'
        out.append((off, pcm, vag_size, header, off + header + 0x20, rate, entries))
    return out


def read_wav(path):
    d = open(path, 'rb').read()
    assert d[:4] == b'RIFF' and d[8:12] == b'WAVE', 'not a WAV'
    i, fmt, rate, data = 12, None, None, None
    while i + 8 <= len(d):
        cid = d[i:i + 4]
        n = struct.unpack_from('<I', d, i + 4)[0]
        body = d[i + 8:i + 8 + n]
        if cid == b'fmt ':
            fmt = struct.unpack_from('<HHIIHH', body, 0)
            rate = fmt[2]
        elif cid == b'data':
            data = body
        i += 8 + n + (n & 1)
    assert fmt and data is not None, 'WAV missing fmt/data'
    assert fmt[0] == 1 and fmt[1] == 1 and fmt[5] == 16, 'expected 16-bit mono PCM'
    return rate, list(struct.unpack('<%dh' % (len(data) // 2), data))


def ffmpeg_ref(pack, bank, path):
    _off, _pcm, vag_size, header, data, rate, _e = bank
    adpcm = pack[data:data + vag_size]
    hdr = (b'VAGp' + struct.pack('>III', 0x20, 0, vag_size) +
           struct.pack('>I', rate) + b'\x00' * 12 + b'x'.ljust(16, b'\x00'))
    vag, raw = path + '.vag', path + '.raw'
    open(vag, 'wb').write(hdr + adpcm)
    subprocess.run(['ffmpeg', '-hide_banner', '-loglevel', 'error', '-i', vag,
                    '-f', 's16le', raw, '-y'], check=True)
    b = open(raw, 'rb').read()
    return list(struct.unpack('<%dh' % (len(b) // 2), b))


def main():
    tool = sys.argv[1] if len(sys.argv) > 1 else os.path.join(HERE, '..', 'build', 'dw4asset')
    pack_path = sys.argv[2] if len(sys.argv) > 2 else os.environ.get('DW4_SOUND_PACK')
    if not os.path.exists(tool):
        raise SystemExit('no %s — build first (make)' % tool)
    with tempfile.TemporaryDirectory() as tmp:
        if not pack_path:
            # The stage's sound pack is a stage manifest's `[0.620]` reference; the
            # crosscheck passes it explicitly, so this is only a convenience fallback.
            raise SystemExit('usage: verify_sound.py <tool> <sound-pack.bin>')
        pack = open(pack_path, 'rb').read()
        py = banks_of(pack)

        listing = subprocess.run([tool, 'sfp', pack_path], capture_output=True, text=True)
        assert listing.returncode == 0, listing.stderr
        c_banks = [l for l in listing.stdout.splitlines() if l.strip().startswith('bank ')]
        assert len(c_banks) == len(py), 'C found %d banks, python %d' % (len(c_banks), len(py))
        for k, (line, b) in enumerate(zip(c_banks, py)):
            f = dict(zip(('off', 'pcm', 'vag', 'rate', 'entries'),
                         (line.split(x)[1].split()[0] for x in
                          ('@', 'pcm ', 'vag ', 'rate ', 'entries '))))
            assert int(f['off'], 16) == b[0], '%s: off' % line
            assert int(f['pcm']) == b[1], '%s: pcm' % line
            assert int(f['vag']) == b[2], '%s: vag' % line
            assert int(f['rate']) == b[5], '%s: rate' % line
            assert int(f['entries']) == len(b[6]), '%s: entries' % line

        # The bank names and per-sound mapping come from the pack's beCriSfpData and
        # beSoundData records.  These are the measured facts for
        # NDMW.AFS entry 620, cross-checked against the live beSoundInfo._fnameList:
        # _fnameIdx 9/8/1/7/6/10 name e_goburi/e_ogre/common_blst/scannon/stag0102/e_blosso.
        expect = ['e_goburi.sfp', 'e_ogre.sfp', 'common_blst.sfp', 'scannon.sfp',
                  'stag0102.sfp', 'e_blosso.sfp']
        got_names = [l.split()[3] for l in c_banks]
        assert got_names == expect, 'bank names %s != %s' % (got_names, expect)
        entries = [l.split() for l in listing.stdout.splitlines() if l.strip().startswith('entry ')]
        named = [e[2] for e in entries if e[2] != '<unnamed>']
        assert len(entries) == sum(len(b[6]) for b in py), 'entry lines != total entries'
        assert len(named) == len(entries), 'unnamed entries remain: %d of %d' % (
            len(entries) - len(named), len(entries))

        total = 0
        for k, b in enumerate(py):
            wav = os.path.join(tmp, 'b%d.wav' % k)
            r = subprocess.run([tool, 'sfp', pack_path, '--bank', str(k), '--wav', wav],
                               capture_output=True, text=True)
            assert r.returncode == 0, r.stderr
            rate, got = read_wav(wav)
            ref = ffmpeg_ref(pack, b, os.path.join(tmp, 'b%d' % k))
            assert rate == b[5], 'bank %d: WAV rate %d != %d' % (k, rate, b[5])
            assert len(got) == len(ref), 'bank %d: %d samples != ffmpeg %d' % (k, len(got), len(ref))
            bad = [i for i in range(len(got)) if got[i] != ref[i]]
            assert not bad, 'bank %d: %d/%d samples differ (first at %d)' % (
                k, len(bad), len(got), bad[0])
            total += len(got)
            print('  bank %d @0x%06x: %6d samples, %d entries, %d Hz — exact' % (
                k, b[0], len(got), len(b[6]), rate))
        print('verify_sound: %d banks, %d samples all match ffmpeg' % (len(py), total))
    return 0


if __name__ == '__main__':
    sys.exit(main())
