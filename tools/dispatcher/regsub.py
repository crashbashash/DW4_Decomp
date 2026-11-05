#!/usr/bin/env python3
"""regsub.py PREFIX LO HI : tally register substitutions (retail->ours) in shape-aligned words of region [LO,HI), from regdiff.py DUMP files."""
import re,sys,difflib,collections
pre,lo,hi=sys.argv[1],int(sys.argv[2],16),int(sys.argv[3],16)
RG=r'\b(?:[sv][0-8]|a[0-3]|t[0-9]|at)\b'
def load(f): return [(int(l.split(' ',1)[0],16),l.rstrip('\n').split(' ',1)[1]) for l in open(f)]
R=load(pre+'.ret');O=load(pre+'.ours')
def nm(s):
    m,_,o=s.partition(' ')
    if re.match(r'^(b|j|bal)',m): o=re.sub(r'0x[0-9a-f]+','T',o)
    o=re.sub(RG,'R',o); o=re.sub(r'-?\d+\(sp\)','SLOT(sp)',o); o=re.sub(r'sp,-?\d+','sp,N',o)
    return m+' '+o
sm=difflib.SequenceMatcher(None,[nm(s) for _,s in R],[nm(s) for _,s in O],autojunk=False)
sub=collections.Counter(); where=collections.defaultdict(list)
for tag,l,h,x,y in sm.get_opcodes():
    if tag!='equal': continue
    for k in range(h-l):
        a,s1=R[l+k]; _,s2=O[x+k]
        if not(lo<=a<hi) or s1==s2: continue
        ra=re.findall(RG,s1); rb=re.findall(RG,s2)
        for p,q in zip(ra,rb):
            if p!=q: sub[(p,q)]+=1; where[(p,q)].append(a)
print(sum(sub.values()))
for (p,q),c in sub.most_common(30): print(p,'->',q,c,[hex(a) for a in where[(p,q)][:4]])
