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
for tag, l, h, x, y in sm.get_opcodes():
    for k in range(max(h-l,y-x)):
        a = kr[l+k] if l+k<h else None
        b = ko[x+k] if x+k<y else None
        if a is None and b is None: continue
        if a is not None and not (lo<=a<hi): continue
        if a is None and tag=='insert': pass
        rs = '%x %s %s'%(a,*dr[a]) if a is not None else ''
        os_ = '%s %s'%do[b] if b is not None else ''
        print('%-40s | %-40s %s'%(rs,os_,'' if tag=='equal' and rs.split(' ',1)[1]==os_ else '*'))
