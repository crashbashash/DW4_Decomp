#!/usr/bin/env python3
"""regmap.py SOURCE.cpp LO HI : for retail addresses LO..HI (hex), tabulate retail-register -> our-register pairings over shape-aligned words,
so a pure renaming (global colouring offset) shows up as a consistent bijection and real structural/liveness differences as conflicts."""
import sys, difflib, re, collections
sys.path.insert(0, 'tools')
import verify, m2c_loop, tempfile
spec_src = open('tools/dispatcher/score.py').read().replace('\nmain()\n', '\n'); sc = {}
exec(compile(spec_src, 'score', 'exec'), sc)
a = sys.argv[1]; lo = int(sys.argv[2], 16); hi = int(sys.argv[3], 16)
tf = tempfile.NamedTemporaryFile('w', suffix='.txt', delete=False)
tf.write(open('config/SLUS-20836/symbols.txt').read().rstrip('\n') + '\n0033e9c0 000080 __dt__17RecoveryCopiedRefFv\n'); tf.close()
ok, report = verify.verify_one(sc['BASE'], a, symbols=tf.name, mwcc='local/mwcps2/combat/mwccps2.exe', flags='-O3,p -Iinclude', verbose=True)
ours, retail = m2c_loop.parse_verbose(report)
wo = [ours[i] for i in sorted(ours)]; wr = [retail[i] for i in sorted(retail)]
do = m2c_loop.disasm_words(wo, sc['BASE']); dr = m2c_loop.disasm_words(wr, sc['BASE'])
ko, kr = sorted(do), sorted(dr)
no = [sc['norm'](*do[k]) for k in ko]; nr = [sc['norm'](*dr[k]) for k in kr]
sm = difflib.SequenceMatcher(None, nr, no, autojunk=False)
REG = re.compile(r'\b(?:[sv][0-8]|a[0-3]|t[0-9]|at)\b')
pairs = collections.Counter(); where = collections.defaultdict(list)
for tag, l, h, x, y in sm.get_opcodes():
    if tag != 'equal': continue
    for k in range(h-l):
        ad = kr[l+k]
        if not (lo <= ad < hi): continue
        r = REG.findall(' '.join(map(str, dr[ad]))); o = REG.findall(' '.join(map(str, do[ko[x+k]])))
        if len(r) != len(o): continue
        for p, q in zip(r, o):
            pairs[(p, q)] += 1; where[(p, q)].append(ad)
byr = collections.defaultdict(list)
for (p, q), n in pairs.items(): byr[p].append((n, q))
for p in sorted(byr, key=lambda r: (r[0], int(r[1:]) if r[1:].isdigit() else 0)):
    print(p, '->', ', '.join('%s x%d' % (q, n) for n, q in sorted(byr[p], reverse=True)))
