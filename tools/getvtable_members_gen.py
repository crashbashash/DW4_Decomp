#!/usr/bin/env python3
"""getvtable_members_gen.py OUTDIR NAME... — two-member (object-ref / string-chunk) stack-object *_GetVTable accessors as C++ (verify with the alternate compiler, -O3,p mostly)."""
import re,sys,os
ROOT=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
def sx(v): return v-0x10000 if v>=0x8000 else v
def words(n):
    return [int(x,16) for x in re.findall(r"\.word (0x[0-9a-f]+)",open(f'{ROOT}/asm/{n}.s').read())]
syms={}
for l in open(f'{ROOT}/config/symbols.txt'):
    p=l.split()
    if len(p)>=3 and not l.startswith('#'):
        try: syms[int(p[0],16)]=p[2]
        except: pass
def gen(name):
    w=words(name)
    F=-sx(w[0]&0xFFFF)
    reg={}
    ev=[]       # events
    N=None
    members={}  # reg -> offset
    calls=[]
    i=0
    inited=False
    while i<len(w):
        x=w[i]; op=x>>26; rs=(x>>21)&31; rt=(x>>16)&31; imm=sx(x&0xFFFF)
        if op==3:
            tgt=syms.get((x&0x3FFFFFF)<<2)
            if not inited:
                inited=True; N=reg[4][1]; init=tgt
            else:
                ev.append(('call',tgt))
            # delay slot
            d=w[i+1]; 
            if (d>>26)==0x2B and ((d>>21)&31)==29:  # sw in delay slot
                rtd=(d>>16)&31
                ev.append(('vt',reg[rtd][1]))
            i+=2; continue
        if op==9 and rs==29: reg[rt]=('a',imm)
        elif op==9 and rs==0: reg[rt]=('c',imm)
        elif op==0xF: reg[rt]=('hi',(x&0xFFFF)<<16)
        elif op==9 and rs==rt and rt in reg and reg[rt][0]=='hi': reg[rt]=('c',reg[rt][1]+imm)
        elif op==0x2B:
            if rs==29 and rt!=0:
                if rt in reg and reg[rt][0]=='c' and reg[rt][1]>0x100000 and imm==N: ev.append(('vt',reg[rt][1]))
            elif rt==0 and rs in reg and reg[rs][0]=='a': ev.append(('zero',reg[rs][1]-N)); 
        elif op==0x23 and rs==2 and 16<=rt<=23 and imm==N: ev.append(('t',))
        elif op in (4,5) and rs in reg and reg[rs][0]=='a':
            d=w[i+1]
            if (d>>26)==0x2B and ((d>>21)&31)==29 and ((d>>16)&31)!=0:
                rtd=(d>>16)&31
                if rtd in reg and reg[rtd][0]=='c': ev.append(('vt',reg[rtd][1]))
            kind=None
            for j in range(i+1,min(i+10,len(w))):
                y=w[j]
                if (y>>26)==0x23 and sx(y&0xFFFF) in (4,-4):
                    kind='ref' if sx(y&0xFFFF)==4 else 'str'; break
            ev.append(('rel',reg[rs][1]-N,kind))
            i+=2; continue
        elif op==0x23 and rt in reg and not (rs==2 and imm==N):
            del reg[rt]
        i+=1
    return F,N,init,ev
def emit(name):
    F,N,init,ev=gen(name)
    size=F-N
    # first rel for each member only
    rels=[]
    seen=set()
    out=[]
    vts=[e[1] for e in ev if e[0]=='vt']
    mem={}
    for e in ev:
        if e[0]=='rel' and len(e)==3 and e[1] not in mem: mem[e[1]]=e[2]
    if len(mem)!=2: raise ValueError('members %s'%mem)
    offs=sorted(mem)
    ext=''.join('extern int DAT_%08x[4];\n'%v for v in sorted(set(vts)))
    # struct
    fields='int *vt; '
    pos=4
    for o in offs:
        if o>pos: fields+='char p%d[%d]; '%(pos,o-pos)
        fields+=('T *m%d; '%o) if mem[o]=='ref' else ('char *m%d; '%o)
        pos=o+4
    if size>pos: fields+='char tail[%d]; '%(size-pos)
    meths=''
    for o in offs:
        if mem[o]=='ref':
            meths+='''    inline void rel%d() {
        T **self = &m%d;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
'''%(o,o)
        else:
            meths+='''    inline void rel%d() {
        char **self = &m%d;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
'''%(o,o)
    body=''
    for e in ev:
        if e[0]=='zero': body+='    obj.m%d = 0;\n'%e[1]
        elif e[0]=='vt': body+='    obj.vt = &DAT_%08x[0];\n'%e[1]
        elif e[0]=='t': body+='    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));\n'
        elif e[0]=='rel' and len(e)==3: body+='    obj.rel%d();\n'%e[1]
    s='''extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int StringChunk_ReleaseHeader(...);
%sextern void * DAT_00586dc8[4];
}
struct Obj {
    %s
%s};
extern "C" int %s(Obj *);
extern "C" int %s(void) {
    Obj obj;
    int r;

    %s(&obj);
%s    return r;
}
'''%(ext,fields,meths,init,name,init,body)
    return s
if __name__=='__main__':
    out=sys.argv[1]
    for n in sys.argv[2:]:
        try:
            open(f'{out}/{n}.cpp','w').write(emit(n)); print('wrote',n)
        except Exception as e:
            print('skip',n,repr(e))
