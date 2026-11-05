#!/usr/bin/env python3
"""extract_iso.py -- extract the Digimon World 4 (USA, SLUS-20836) PS2 disc files the port reads.

The port and its tests read a directory of disc files (NDMW.AFS, AREA.AFS, NDMW.IGB, SLUS_208.36, ...), not the ISO.
This tool reads the ISO9660 file system of a disc image, copies every file to a directory, and validates the result.
It needs only Python 3 and never writes to the ISO.

  tools/extract_iso.py ISO --out DIR [--skip OUTER.DAT] [--force] [--strict]   extract, then validate
  tools/extract_iso.py --check DIR                                              validate an existing directory
  tools/extract_iso.py --self-test                                              no game data needed; run by `make check`

Validation (exit 1 on failure):
  * the disc holds SYSTEM.CNF naming SLUS_208.36 (the USA release);
  * the required files exist with the retail sizes: NDMW.AFS, AREA.AFS, NDMW.IGB, SLUS_208.36;
  * with --strict the whole-image MD5 of the pristine disc (3185f04230b1dabd853db750e4b51108) must match.
    Without it a different MD5 is only a warning, so patched or modded discs still extract.

A re-run skips files that already have the right size (use --force to copy again). Files are written to `<name>.part` and renamed
when complete, so an interrupted run never leaves a short file under the real name.
"""
import argparse
import hashlib
import os
import struct
import sys
import tempfile

SECTOR = 2048
PRISTINE_MD5 = '3185f04230b1dabd853db750e4b51108'
BOOT_ELF = 'SLUS_208.36'
# Files the port reads, with their retail sizes (bytes).
REQUIRED = {'NDMW.AFS': 727056384, 'AREA.AFS': 511082496, 'NDMW.IGB': 106350, BOOT_ELF: 4541744}


class IsoError(Exception):
    pass


class Iso:
    """A minimal read-only ISO9660 reader (2048-byte sectors, primary volume descriptor, no Joliet/Rock Ridge)."""

    def __init__(self, path):
        self.f = open(path, 'rb')
        self.f.seek(0, os.SEEK_END)
        self.size = self.f.tell()
        pvd = self.read(16, 1)
        if pvd[0] != 1 or pvd[1:6] != b'CD001':
            raise IsoError('not an ISO9660 image (no primary volume descriptor at sector 16)')
        self.volume_blocks = struct.unpack('<I', pvd[80:84])[0]
        if self.volume_blocks * SECTOR > self.size:
            raise IsoError('image is shorter than its volume size (truncated download?)')
        self.root = self.record(pvd[156:190])

    def read(self, lba, count):
        self.f.seek(lba * SECTOR)
        data = self.f.read(count * SECTOR)
        if len(data) != count * SECTOR:
            raise IsoError('read past the end of the image at sector %d' % lba)
        return data

    @staticmethod
    def record(raw):
        lba, length = struct.unpack('<I', raw[2:6])[0], struct.unpack('<I', raw[10:14])[0]
        flags = raw[25]
        n = raw[32]
        name = raw[33:33 + n]
        if name == b'\x00':
            text = '.'
        elif name == b'\x01':
            text = '..'
        else:
            text = name.decode('ascii', 'replace').split(';')[0].rstrip('.')
        return {'lba': lba, 'size': length, 'dir': bool(flags & 2), 'name': text}

    def listdir(self, rec):
        data = self.read(rec['lba'], (rec['size'] + SECTOR - 1) // SECTOR)[:rec['size']]
        out, pos = [], 0
        while pos < len(data):
            n = data[pos]
            if n == 0:                      # records never span a sector: skip the padding
                pos = (pos // SECTOR + 1) * SECTOR
                continue
            r = self.record(data[pos:pos + n])
            pos += n
            if r['name'] not in ('.', '..'):
                out.append(r)
        return out

    def walk(self, rec=None, prefix=''):
        for r in self.listdir(rec or self.root):
            path = prefix + r['name']
            if r['dir']:
                yield from self.walk(r, path + '/')
            else:
                yield path, r

    def copy(self, rec, dest, force=False, progress=None):
        """Write one file; returns 'copied' or 'kept'."""
        if not force and os.path.isfile(dest) and os.path.getsize(dest) == rec['size']:
            return 'kept'
        os.makedirs(os.path.dirname(dest) or '.', exist_ok=True)
        part = dest + '.part'
        remaining, lba = rec['size'], rec['lba']
        self.f.seek(lba * SECTOR)
        with open(part, 'wb') as out:
            while remaining:
                chunk = self.f.read(min(remaining, 4 << 20))
                if not chunk:
                    raise IsoError('image ended inside %s' % dest)
                out.write(chunk)
                remaining -= len(chunk)
                if progress:
                    progress(len(chunk))
        if os.path.exists(dest):
            os.chmod(dest, 0o644)
        os.replace(part, dest)
        return 'copied'


def file_md5(path, chunk=8 << 20):
    h = hashlib.md5()
    with open(path, 'rb') as f:
        while True:
            b = f.read(chunk)
            if not b:
                break
            h.update(b)
    return h.hexdigest()


def validate_dir(root):
    """Problems found in an extracted directory (empty list = good)."""
    problems = []
    for name, size in REQUIRED.items():
        p = os.path.join(root, name)
        if not os.path.isfile(p):
            problems.append('missing %s' % name)
        elif os.path.getsize(p) != size:
            problems.append('%s is %d bytes, expected %d' % (name, os.path.getsize(p), size))
    p = os.path.join(root, 'SYSTEM.CNF')
    if os.path.isfile(p) and BOOT_ELF.encode() not in open(p, 'rb').read():
        problems.append('SYSTEM.CNF does not name %s (not the USA disc)' % BOOT_ELF)
    return problems


def extract(iso_path, out, skip=(), force=False, strict=False, quiet=False):
    say = (lambda *a: None) if quiet else (lambda *a: print(*a, flush=True))
    iso = Iso(iso_path)
    files = list(iso.walk())
    names = {n for n, _ in files}
    if BOOT_ELF not in names or 'SYSTEM.CNF' not in names:
        raise IsoError('this disc has no %s / SYSTEM.CNF: not Digimon World 4 (USA)' % BOOT_ELF)
    cnf = dict(files)['SYSTEM.CNF']
    if BOOT_ELF.encode() not in iso.read(cnf['lba'], 1)[:cnf['size']]:
        raise IsoError('SYSTEM.CNF does not boot %s: not the USA release' % BOOT_ELF)
    sizes = {n: r['size'] for n, r in files}
    for name, size in REQUIRED.items():
        if name not in sizes:
            raise IsoError('disc is missing %s' % name)
    if strict:
        say('hashing the image (MD5) ...')
        md5 = file_md5(iso_path)
        if md5 != PRISTINE_MD5:
            raise IsoError('image MD5 %s is not the pristine USA disc (%s)' % (md5, PRISTINE_MD5))
    todo = [(n, r) for n, r in files if n not in skip]
    total = sum(r['size'] for _, r in todo)
    done = [0]
    last = [-1]

    def progress(n):
        done[0] += n
        pct = done[0] * 100 // max(total, 1)
        if pct != last[0] and pct % 5 == 0:
            last[0] = pct
            say('  %3d%%' % pct)
    say('extracting %d files (%.0f MB) to %s' % (len(todo), total / 1e6, out))
    copied = kept = 0
    for n, r in todo:
        res = iso.copy(r, os.path.join(out, n), force, progress if res_big(r) else None)
        copied += res == 'copied'
        kept += res == 'kept'
        say('  %-7s %s' % (res, n))
    problems = validate_dir(out)
    if problems:
        raise IsoError('extracted files failed validation:\n  ' + '\n  '.join(problems))
    say('ok: %d copied, %d already present; required files verified' % (copied, kept))
    return 0


def res_big(r):
    return r['size'] > 50 << 20


# --------------------------------------------------------------------------------------------------------------------
def build_test_iso(path, files):
    """A tiny ISO9660 image with a root directory, one subdirectory and the given {name: bytes} files (sectors 17.. onward)."""
    def rec(name, lba, size, is_dir):
        nm = name if isinstance(name, bytes) else name.encode()
        n = 33 + len(nm)
        n += n & 1
        r = bytearray(n)
        r[0] = n
        r[2:6] = struct.pack('<I', lba)
        r[6:10] = struct.pack('>I', lba)
        r[10:14] = struct.pack('<I', size)
        r[14:18] = struct.pack('>I', size)
        r[25] = 2 if is_dir else 0
        r[32] = len(nm)
        r[33:33 + len(nm)] = nm
        return bytes(r)
    dot, dotdot = b'\x00', b'\x01'
    layout, lba = [], 20
    sub = [(n, d) for n, d in files.items() if '/' in n]
    top = [(n, d) for n, d in files.items() if '/' not in n]
    dirs = {'': top, 'SUB': [(n.split('/', 1)[1], d) for n, d in sub]}
    placed = {}
    for dname, entries in dirs.items():
        for n, d in entries:
            placed[(dname, n)] = (lba, len(d))
            lba += max(1, (len(d) + SECTOR - 1) // SECTOR)
    root_lba, sub_lba = 18, 19

    def dir_sector(me, parent, entries, dname):
        body = rec(dot, me, SECTOR, True) + rec(dotdot, parent, SECTOR, True)
        if dname == '' and sub:
            body += rec('SUB', sub_lba, SECTOR, True)
        for n, d in entries:
            body += rec(n + ';1', *placed[(dname, n)], False)
        return body.ljust(SECTOR, b'\x00')
    img = bytearray(lba * SECTOR)
    pvd = bytearray(SECTOR)
    pvd[0] = 1
    pvd[1:6] = b'CD001'
    pvd[6] = 1
    pvd[80:84] = struct.pack('<I', lba)
    pvd[84:88] = struct.pack('>I', lba)
    pvd[156:190] = rec(dot, root_lba, SECTOR, True)[:34].ljust(34, b'\x00')
    img[16 * SECTOR:17 * SECTOR] = pvd
    img[root_lba * SECTOR:(root_lba + 1) * SECTOR] = dir_sector(root_lba, root_lba, dirs[''], '')
    if sub:
        img[sub_lba * SECTOR:(sub_lba + 1) * SECTOR] = dir_sector(sub_lba, root_lba, dirs['SUB'], 'SUB')
    for (dname, n), (l, size) in placed.items():
        data = files[n if dname == '' else dname + '/' + n]
        img[l * SECTOR:l * SECTOR + size] = data
    open(path, 'wb').write(bytes(img))


def self_test():
    with tempfile.TemporaryDirectory() as tmp:
        iso, out = os.path.join(tmp, 'a.iso'), os.path.join(tmp, 'out')
        files = {'SYSTEM.CNF': b'BOOT2 = cdrom0:\\SLUS_208.36;1\nVER = 1.00\n', 'SLUS_208.36': b'E' * 5000,
                 'SUB/INNER.BIN': b'xyz' * 1000}
        build_test_iso(iso, files)
        got = {n: r['size'] for n, r in Iso(iso).walk()}
        assert got == {n: len(d) for n, d in files.items()}, got
        # a disc missing the USA boot file or the required archives is refused with a clear message
        try:
            extract(iso, out, quiet=True)
            raise SystemExit('self-test: an image without the required archives was accepted')
        except IsoError as e:
            assert 'missing' in str(e), e
        # extraction of a copy that has the sizes we expect (the retail sizes are large, so shrink REQUIRED for the test)
        saved = dict(REQUIRED)
        REQUIRED.clear()
        REQUIRED.update({BOOT_ELF: 5000})
        try:
            assert extract(iso, out, quiet=True) == 0
            assert open(os.path.join(out, 'SUB', 'INNER.BIN'), 'rb').read() == files['SUB/INNER.BIN']
            assert open(os.path.join(out, BOOT_ELF), 'rb').read() == files[BOOT_ELF]
            assert not [f for f in os.listdir(out) if f.endswith('.part')]
            first = os.path.getmtime(os.path.join(out, BOOT_ELF))
            extract(iso, out, quiet=True)                       # re-run keeps what is complete
            assert os.path.getmtime(os.path.join(out, BOOT_ELF)) == first
            open(os.path.join(out, BOOT_ELF), 'wb').write(b'short')   # a truncated file is replaced
            extract(iso, out, quiet=True)
            assert os.path.getsize(os.path.join(out, BOOT_ELF)) == 5000
            try:
                extract(iso, out, strict=True, quiet=True)
                raise SystemExit('self-test: --strict accepted a non-pristine image')
            except IsoError as e:
                assert 'pristine' in str(e), e
        finally:
            REQUIRED.clear()
            REQUIRED.update(saved)
        bad = os.path.join(tmp, 'bad.iso')
        open(bad, 'wb').write(b'\0' * (20 * SECTOR))
        try:
            Iso(bad)
            raise SystemExit('self-test: a non-ISO file was accepted')
        except IsoError:
            pass
    print('extract_iso: ISO9660 parsing, safe re-runs, truncated-file replacement and refusal of non-USA/non-ISO images pass')


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('iso', nargs='?')
    ap.add_argument('--out', help='destination directory (created if needed)')
    ap.add_argument('--skip', action='append', default=[], help='file name to leave out (repeatable), e.g. OUTER.DAT')
    ap.add_argument('--force', action='store_true', help='copy files even when the right size already exists')
    ap.add_argument('--strict', action='store_true', help='require the pristine disc MD5')
    ap.add_argument('--check', metavar='DIR', help='validate an existing extracted directory')
    ap.add_argument('--self-test', action='store_true')
    a = ap.parse_args()
    if a.self_test:
        return self_test()
    try:
        if a.check:
            problems = validate_dir(a.check)
            for p in problems:
                print('problem:', p)
            if not problems:
                print('ok: %s holds the required files' % a.check)
            return 1 if problems else 0
        if not a.iso or not a.out:
            ap.error('give an ISO and --out DIR (or --check DIR / --self-test)')
        return extract(a.iso, a.out, set(a.skip), a.force, a.strict)
    except IsoError as e:
        print('error:', e, file=sys.stderr)
        return 1


if __name__ == '__main__':
    sys.exit(main())
