#!/usr/bin/env python3
"""m2c_typed_fields.py DRAFT.c [--only VAR,...] - retype raw offset accesses of an m2c draft as struct fields.

m2c drafts spell every field access `*(T *)((char *)(VAR) + N)`.  The compiler treats such an expression as
pointer arithmetic: a load and a store of the same offset share one hoisted address register
(`addiu s3,s6,4 ... sw v0,0(s3)`), which retail does not.  Typed members (`VAR->f4`) are plain `base + offset`
accesses.  This script collects, per variable, every `(offset, type)` pair, builds one struct per variable
(`char padN[..]` between members), declares the variable as a pointer to it and rewrites the accesses, so a
draft can be re-tested quickly.  Chains `*(T *)((char *)(VAR->f16) + 8)` become nested structs.

It is a starting point, not a result: a variable accessed with two types at one offset, overlapping or
misaligned members, or a declaration that is not `void *VAR` / `int *VAR` is left raw.  Use `--only` to retype
a subset when the compiler rejects a comparison between two differently typed pointers.  Output goes to
stdout; run `tools/verify.py` or `tools/dispatcher/regalloc.py` on it.  See archived near-miss note wave8s6.
"""
import collections
import re
import sys

SZ = {'int': 4, 'unsigned int': 4, 'float': 4, 'unsigned char': 1, 'char': 1, 'short': 2, 'unsigned short': 2,
      'long long': 8, 'unsigned long long': 8, 'void *': 4, 'int *': 4, 'signed char': 1}
TY = r'(unsigned long long|long long|unsigned int|unsigned short|unsigned char|signed char|short|char|int|float|void \*|int \*)'
BASE = r'(\w+(?:->f\d+)*)'
PAT = re.compile(r'\*\(' + TY + r' \*\)\(\(char \*\)\(' + BASE + r'\) \+ (0x[0-9a-fA-F]+|\d+)\)')
PAT2 = re.compile(r'\*\(' + TY + r' \*\)\(\(char \*\)' + BASE + r' \+ (0x[0-9a-fA-F]+|\d+)\)')


def sname(path):
    return 'S_' + re.sub(r'\W+', '_', path)


def convert(src, only=None):
    acc = collections.defaultdict(dict)
    bad = set()
    cur = src
    for _ in range(6):
        changed = False

        def rep(m):
            nonlocal changed
            t, b, n = m.group(1), m.group(2), int(m.group(3), 0)
            if only is not None and b.split('->')[0] not in only:
                return m.group(0)
            d = acc[b]
            if n in d and d[n] != t:
                bad.add(b)
            d[n] = t
            changed = True
            return '%s->f%d' % (b, n)
        cur = PAT.sub(rep, cur)
        cur = PAT2.sub(rep, cur)
        if not changed:
            break

    def isbad(p):
        parts = p.split('->')
        return any('->'.join(parts[:i + 1]) in bad for i in range(len(parts)))
    paths = {p for p in acc if not isbad(p)}
    for p in sorted(paths, key=lambda x: x.count('->')):
        d = acc[p]
        end = 0
        for n in sorted(d):
            if n < end or n % SZ[d[n]]:
                paths.discard(p)
                break
            end = n + SZ[d[n]]
    structs = []
    for p in sorted(paths, key=lambda x: -x.count('->')):
        d = acc[p]
        fl = []
        pos = 0
        for n in sorted(d):
            if n > pos:
                fl.append('char pad%d[%d];' % (pos, n - pos))
            child = '%s->f%d' % (p, n)
            fl.append('%s *f%d;' % (sname(child), n) if child in paths else '%s f%d;' % (d[n], n))
            pos = n + SZ[d[n]]
        structs.append('typedef struct %s { %s } %s;' % (sname(p), ' '.join(fl), sname(p)))
    out = cur
    for p in paths:
        if '->' not in p:
            out = re.sub(r'(void \*|int \*)\s*%s\b(?=\s*[,;)])' % p, '%s *%s' % (sname(p), p), out, count=1)
    m = re.search(r'^\w[^\n;]*\([^;]*\)\s*\{', out, re.M)
    if structs and m:
        out = out[:m.start()] + '\n'.join(structs) + '\n' + out[m.start():]
    return out


def main(argv):
    if len(argv) < 2:
        sys.stderr.write(__doc__)
        return 2
    only = None
    if '--only' in argv:
        only = set(argv[argv.index('--only') + 1].split(','))
    sys.stdout.write(convert(open(argv[1]).read(), only))
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
