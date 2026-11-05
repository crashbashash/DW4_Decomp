#!/usr/bin/env python3
"""getvtable_union_conv.py DRAFT NAME SIZE

Turns the m2c draft of a stack-object `*_GetVTable` accessor into the union form used by the banked siblings (see
archived near-miss note wave6s11): zero stores in order, object/string member releases, member destructor calls
through `&u.w[i]`.  Run from the repository root; SIZE is the byte size of the stack object (scan frame-objoff-28..+12).
Environment: DECLREV=1 reverses the declaration order of the member pointers, ALIAS=1 writes the later vtable stores through
a second symbol plus offset (defeats the constant CSE across a call).  The result is only a candidate: verify it with
tools/verify.py (with the alternate compiler if needed, see unit-compilers.md).
"""
import re,sys
draft,name,sz=sys.argv[1],sys.argv[2],int(sys.argv[3])
src=open(draft).read().split('\n')
# keep extern/prototype lines
protos=[l for l in src if re.match(r'^(extern |int \w+\(\);|void \w+\(\);|void \*\w+\(\);)',l)]
# body
start=[i for i,l in enumerate(src) if l.startswith('int %s_GetVTable(void)'%name)][0]
body=src[start+1:]
# remove trailing }
while body and body[-1].strip()=='' : body.pop()
body=body[:-1]
# main obj offset: variable declared "int *spXX;"
objoff=None
for l in body:
    m=re.match(r'\s*int \*sp([0-9A-F]+);',l)
    if m: objoff=int(m.group(1),16)
assert objoff is not None
def idx(hexs): return (int(hexs,16)-objoff)//4
out=[]
members={}   # hex -> kind
# first pass: find release blocks
i=0
stm=[]
while i<len(body):
    l=body[i]
    if re.match(r'\s*(int|void) .*;$',l) and not '=' in l and not '(' in l:
        i+=1; continue
    m=re.match(r'\s*if \(&sp([0-9A-F]+) != 0\) \{',l)
    if m:
        depth=l.count('{')-l.count('}'); blk=[l]; j=i+1
        while depth>0:
            blk.append(body[j]); depth+=body[j].count('{')-body[j].count('}'); j+=1
        txt='\n'.join(blk)
        kind='obj' if 'igObject_Destroy' in txt else 'str'
        stm.append(('rel',m.group(1),kind)); members[m.group(1)]=kind
        i=j; continue
    stm.append(('s',l.strip())); i+=1
res=[]
decl=[]
n=0
qn={}
for s in stm:
    if s[0]=='rel':
        h,kind=s[1],s[2]
        n+=1
        q='q%d'%n if False else qn[h]
        if kind=='obj':
            res.append("    if (%s != 0) {\n        %s = *(S_ref **)%s;\n        if (%s != 0) {\n            %s->f4 = (int)((int) (%s->f4 - 1));\n            if (((unsigned long long) ((long long) %s->f4 << 0x29) >> 0x29) == 0) {\n                igObject_Destroy(%s);\n            }\n        }\n    }"%(q,q,q,q,q,q,q,q))
        else:
            t=q[1:]
            res.append("    if (%s != 0) {\n        tv%s = *(int **)%s;\n        if (tv%s != 0) {\n            ta%s = tv%s - 2;\n            tc%s = tv%s[-1] - 1;\n            tv%s[-1] = tc%s;\n            if (tc%s == 0) {\n                StringChunk_ReleaseHeader(*ta%s, ta%s);\n            }\n        }\n    }"%(q,t,q,t,t,t,t,t,t,t,t,t,t))
        continue
    l=s[1]
    m=re.match(r'sp([0-9A-F]+) = \(int \*\)\((&DAT_\w+\[0\])\);',l)
    if m:
        res.append("    u.w[%d] = (int)(%s);"%(idx(m.group(1)),m.group(2))); continue
    m=re.match(r'sp([0-9A-F]+) = (\(void \*\)\()?0\)?;',l)
    if m:
        h=m.group(1)
        if h in members:
            k=members[h]; n+=1; q='q%d'%n; qn[h]=q
            off=int(h,16)-objoff
            if k=='obj':
                decl.append("    S_ref *%s;"%q); res.append("    %s = (S_ref *)&u.b[%d];\n    *(int *)%s = 0;"%(q,off,q))
            else:
                decl.append("    char *%s;\n    int *tv%s, *ta%s;\n    int tc%s;"%(q,q[1:],q[1:],q[1:])); res.append("    %s = &u.b[%d];\n    *(int *)%s = 0;"%(q,off,q))
        else:
            res.append("    u.w[%d] = 0;"%idx(h))
        continue
    m=re.match(r'(temp_\w+) = \*\(int \*\)\(\(char \*\)\(\(\*\(int \*\)\(\(char \*\)\(DAT_00586dc8\[0\]\) \+ 916\) \+ sp\)\) \+ (\d+)\);',l)
    if m:
        res.append("    %s = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];"%m.group(1)); retv=m.group(1); continue
    # calls with &spXX
    def rep(mm):
        h=mm.group(1)
        return "&u.w[%d]"%idx(h)
    l2=re.sub(r'&sp([0-9A-F]+)',rep,l)
    l2=l2.replace('&u.w[0]','u.b') if re.match(r'(igObject_InitHeader|\w+_Construct)\(&u.w\[0\]\);',l2) else l2
    res.append("    "+l2)
    # note: leave return
import os
if os.environ.get("ALIAS"):
    seen={}
    for k,r in enumerate(res):
        m=re.match(r'    u\.w\[0\] = \(int\)\(&DAT_(\w+)\[0\]\);',r)
        if m:
            a=m.group(1)
            if a in seen:
                alt='%08x'%(int(a,16)-16)
                res[k]="    u.w[0] = (int)(&DAT_%s[4]);"%alt
                protos.append("extern int DAT_%s[8];"%alt)
            seen[a]=1
print("typedef struct S_ref { char pad4[4]; int f4; } S_ref;")
print("\n".join(protos))
print("union U { int vt; int w[%d]; char b[%d]; };"%(sz//4,sz))
print("int %s_GetVTable(void) {\n    union U u;\n    int %s;"%(name,retv))
import os
print("\n".join(decl[::-1] if os.environ.get("DECLREV") else decl))
print("\n".join(res))
print("}")
