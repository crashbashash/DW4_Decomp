#!/usr/bin/env python3
"""regdiff.py SOURCE.cpp LO HI : print shape opcodes (retail vs ours) for retail region [LO,HI)."""
import sys, re, difflib
sys.path.insert(0,'tools'); sys.path.insert(0,'tools/dispatcher')
import verify, m2c_loop
exec(open('tools/dispatcher/score.py').read().split('def main')[0])
_n=norm
def norm(m,o):
    return re.sub(r'(R,)sp,-?\d+', r'\1sp,N', _n(m,o)) if m=='addiu' else _n(m,o)
src, lo, hi = sys.argv[1], int(sys.argv[2],16), int(sys.argv[3],16)
import tempfile
tf=tempfile.NamedTemporaryFile('w',suffix='.txt',delete=False)
tf.write(open('config/SLUS-20836/symbols.txt').read().rstrip('\n')+'\n0033e9c0 000080 __dt__17RecoveryCopiedRefFv\n');tf.close()
ok,rep=verify.verify_one(BASE,src,symbols=tf.name,mwcc='local/mwcps2/combat/mwccps2.exe',flags='-O3,p -Iinclude',verbose=True)
ours,retail=m2c_loop.parse_verbose(rep)
wo=[ours[i] for i in sorted(ours)]; wr=[retail[i] for i in sorted(retail)]
do=m2c_loop.disasm_words(wo,BASE); dr=m2c_loop.disasm_words(wr,BASE)
ko,kr=sorted(do),sorted(dr)
no=[norm(*do[k]) for k in ko]; nr=[norm(*dr[k]) for k in kr]
sm=difflib.SequenceMatcher(None,nr,no,autojunk=False)
for tag,l,h,x,y in sm.get_opcodes():
    if tag=='equal': continue
    if not (lo<=kr[min(l,len(kr)-1)]<hi) : continue
    print('%s retail %x..%x ours idx %d..%d'%(tag,kr[l],kr[min(h,len(kr)-1)],x,y))
    for a in range(l,h): print('   R %x %s'%(kr[a],dr[kr[a]][0]+' '+dr[kr[a]][1]))
    for b in range(x,y): print('   O %x %s'%(ko[b],do[ko[b]][0]+' '+do[ko[b]][1]))

n=0
for tag,l,h,x,y in sm.get_opcodes():
    if tag!='equal' and lo<=kr[min(l,len(kr)-1)]<hi: n+=max(h-l,0)
print('SHAPE-WORDS-DIFF(no sp imm):',n)
import os
if os.environ.get('DUMP'):
    open(os.environ['DUMP']+'.ours','w').write('\n'.join('%x %s %s'%(k,do[k][0],do[k][1]) for k in ko))
    open(os.environ['DUMP']+'.ret','w').write('\n'.join('%x %s %s'%(k,dr[k][0],dr[k][1]) for k in kr))
