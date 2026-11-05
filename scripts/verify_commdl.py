#!/usr/bin/env python3
"""Execute retail common-model helpers against C; compare ordered engine calls,
ordered non-stack stores and final bytes. Allocation/list/string/messenger leaves
are explicit test boundaries. This does not validate animation or rendering."""
import argparse
import ctypes as C
import hashlib
from pathlib import Path
import random
import subprocess
import tempfile
from verify_loadintf2 import Retail as Cpu, Harness, Api, PEEK, POKE, CALL, sx, MASK

ROOT=Path(__file__).resolve().parents[1]
CM,MSG,OPEN,CLOSE,OA,CA,VEC,REF=range(0x1000000,0x1000800,0x100)
SCRATCH=0x106f000
ENTRIES={0x3e3b80:('cm_start',5),0x3e3d80:('cm_ref_destroy',2),
         0x3e3e00:('cm_start_at',6),0x3e4030:('cm_play',5),
         0x3e4210:('cm_is_sequence',4),0x3e4280:('cm_open_empty',1),
         0x3e42a0:('cm_close',5),0x3e4480:('cm_is_running',3),
         0x3e44d0:('cm_close_empty',1),0x3e44f0:('cm_poll',1)}
ARGC={0x38e5f0:5,0x38d860:4,0x38f830:2,0x38e060:2,0x38f220:2,
      0x38f4b0:2,0x301000:1,0x2f88e0:1,0x3c7450:1,0x301e30:2,
      0x2d6cf0:2,0x2ff820:1,0x2eb010:1,0x2eadf0:1,0x2eaf60:2,
      0x30c940:2,0x100610:1}
RETURNS={0x3e3d80,0x3e4210,0x3e4280,0x3e4480,0x3e44d0}

class World(Harness):
    def __init__(self,image,**options):
        super().__init__(image)
        self.options=options; self.trace=[]; self.target=0; self.seq=0; self.result=0
        self.answers={}; self.next_item=0x1010000
        for a,v in ((CM+16,MSG),(CM+20,OPEN),(CM+24,CLOSE),(OPEN+16,OA),
                    (CLOSE+16,CA),(0x554c14,options.get('allocator',1)),
                    (0x587110,0x1110000),(0x586f20,options.get('pool',0x1120000)),
                    (VEC,0x3f800000),(VEC+4,0xc0000000),(VEC+8,0x7fc01234)):
            self.write(a,4,v)
        self.trace=[]
    def write(self,a,n,v):
        super().write(a,n,v)
        if not (0x1f00000<=a<0x2000000 or SCRATCH<=a<SCRATCH+12):
            self.trace.append(('write',a,n,v&((1<<(n*8))-1)))
    def call(self,addr,a):
        assert addr in ARGC,hex(addr)
        a=tuple(a[:ARGC[addr]])
        event=a
        if addr==0x38f4b0: event=(a[0],*(self.read(a[1]+i,4) for i in (0,4,8)))
        self.trace.append(('call',addr,*event))
        if addr==0x301000: return 0x1130000
        if addr==0x2f88e0: return 0x1140000
        if addr==0x3c7450:
            p=self.next_item;self.next_item+=32
            self.write(p+4,4,self.options.get('refs',1))
            for off in (12,16):
                old=0x1150000+off if self.options.get('old',0) else 0
                self.write(p+off,4,old)
                if old:
                    self.write(old-8,4,0x1160000)
                    self.write(old-4,4,self.options['old'])
            return p
        if addr==0x2eb010: return 0 if self.options.get('null_pool') else 0x1120000
        if addr==0x2eadf0: return a[0]
        if addr==0x2eaf60: return a[1] # identity token; engine string interning remains a boundary
        if addr==0x301e30:
            count=self.read(a[0]+8,4);data=self.read(a[0]+16,4)
            self.write(data+count*4,4,a[1]); self.write(a[0]+8,4,count+1)
            self.write(a[1]+4,4,self.read(a[1]+4,4)+self.options.get('retain',1))
        elif addr==0x2d6cf0:
            count=self.read(a[0]+8,4);data=self.read(a[0]+16,4)
            for i in range(a[1],count-1):self.write(data+i*4,4,self.read(data+(i+1)*4,4))
            self.write(a[0]+8,4,count-1)
        elif addr==0x38d860:self.target=a[2];self.slot=a[3]
        elif addr==0x38f830:self.seq=a[1]
        elif addr==0x38e060:
            self.result=self.answers.get((self.slot,self.target,self.seq),0)
        elif addr==0x38e5f0 and a[4]==0x517228:
            self.result=self.answers.get((a[3],a[2],None),0)
        elif addr==0x38f220:return self.result
        return 0
    def snapshot(self):
        return {a:v for a,v in self.mem.items() if not (0x1f00000<=a<0x2000000 or SCRATCH<=a<SCRATCH+12)}

class Retail(World,Cpu):
    def __init__(self,image,**kw):
        World.__init__(self,image,**kw)
        self.r=[0]*32;self.f=[0]*32;self.real_hits=set();self.covered=set()
    def step(self,pc,delay=False):
        self.covered.add(pc)
        return Cpu.step(self,pc,delay)
    def call_hook(self,addr):
        if addr in ENTRIES:
            self.real_hits.add(addr)
            end=self.r[31];pc=addr
            for _ in range(10000):
                if pc==end:return
                pc=self.step(pc)
            raise AssertionError('nested call did not return')
        self.r[2]=self.call(addr,[sx(v,32) for v in self.r[4:12]])&MASK
    def invoke(self,addr,args):
        self.r=[0]*32;self.r[4:4+len(args)]=[v&MASK for v in args]
        self.r[28]=0x55c870;self.r[29]=0x1fff000;self.r[31]=0xfffffff0
        pc=addr;self.real_hits.add(addr)
        for _ in range(10000):
            if pc==0xfffffff0:return sx(self.r[2],32)
            pc=self.step(pc)
        raise AssertionError('did not return')

class Native:
    def __init__(self,lib,world):
        self.world=world;self.errors=[]
        def safe(fn,default=0):
            def wrapped(*args):
                try:return fn(*args)
                except Exception as e:self.errors.append(e);return default
            return wrapped
        self.peek=PEEK(safe(lambda u,a,n:sx(world.read(a,n),n*8)))
        self.poke=POKE(safe(lambda u,a,n,v:world.write(a,n,v)))
        self.call=CALL(safe(lambda u,a,v:world.call(a,list(v[:8]))))
        self.api=Api(None,*[C.cast(f,C.c_void_p) for f in (self.peek,self.poke,self.call)])
        self.lib=lib
    def invoke(self,addr,args):
        name,n=ENTRIES[addr];fn=getattr(self.lib,name)
        fn.argtypes=[C.POINTER(Api)]+[C.c_int32]*n
        fn.restype=C.c_int32 if addr in RETURNS else None
        result=fn(C.byref(self.api),*args)
        assert not self.errors,self.errors
        return result

def verify(image,lib):
    total=0;covered=set();hits=set()
    def pair(**kw):
        r=Retail(image,**kw);w=World(image,**kw);return r,w,Native(lib,w)
    def step(p,addr,*args):
        nonlocal total
        r,w,c=p;r.trace=[];w.trace=[]
        x=r.invoke(addr,args);y=c.invoke(addr,args)
        assert r.trace==w.trace,(hex(addr),'trace',r.trace,w.trace)
        assert r.snapshot()==w.snapshot(),(hex(addr),'memory')
        if addr in RETURNS:assert x==y,(hex(addr),x,y)
        covered.update(r.covered);hits.update(r.real_hits);total+=1
    for entry in (0x3e3b80,0x3e3e00,0x3e4030,0x3e42a0):
        for wait in (0,1,2,255,257,-1):
            for allocator in (0,1):
                for pool,old,refs,retain in ((0,0,1,1),(0x1120000,1,1,1),(0x1120000,2,2,1),(0,0,0x800001,0)):
                    p=pair(allocator=allocator,pool=pool,old=old,refs=refs,retain=retain)
                    args=[CM,-1,0x518388,0x518380]
                    if entry==0x3e3e00:args.append(VEC)
                    step(p,entry,*args,wait)
                    assert p[0].read((CLOSE if entry==0x3e42a0 else OPEN)+8,4)==int(wait&255==1)
        # Retail still passes null to string helper if pool creation fails.
        p=pair(pool=0,null_pool=True)
        step(p,entry,CM,0,0x518388,0x518380,*([VEC] if entry==0x3e3e00 else []),1)
    for ref in (0,REF):
        for ptr in (0,0x1010000):
            for refs in (1,2,0x800001):
                for flag in (-1,0,1,0x8000,0x10001):
                    p=pair()
                    for w in p[:2]:w.write(REF,4,ptr);w.write(ptr+4,4,refs)
                    step(p,0x3e3d80,ref,flag)
    for count in (-2147483648,-1,0,1,3):
        p=pair()
        for w in p[:2]:w.write(OPEN+8,4,count);w.write(CLOSE+8,4,count)
        step(p,0x3e4280,CM);step(p,0x3e44d0,CM)
        if count<=0:step(p,0x3e44f0,CM)
    # Multi-tick: newest open blocks older completed; close drains independently;
    # duplicate/replaced sequences retain separate records; nonboolean low bytes.
    rng=random.Random(0x3e44f0)
    for trial in range(80):
        p=pair()
        records=[]
        for i in range(6):
            addr=0x3e4030 if i<3 else 0x3e42a0
            slot=i%2;name=0x518388+(i%2)*8;seq=0x518380+(i%3)*8
            records.append((slot,name,seq))
            step(p,addr,CM,slot,name,seq,1)
        for tick in range(8):
            answers={}
            for slot,name,seq in records:
                answers[slot,name,seq]=rng.choice((0,1,2,255,257)) if tick<7 else 0
                answers[slot,name,None]=rng.choice((0,1,2,255,257)) if tick<7 else 0
            for w in p[:2]:w.answers=answers
            step(p,0x3e44f0,CM);step(p,0x3e4280,CM);step(p,0x3e44d0,CM)
        assert p[0].read(OPEN+8,4)==p[0].read(CLOSE+8,4)==0
    p=pair()
    step(p,0x3e4030,CM,0,100,10,1);step(p,0x3e4030,CM,0,200,20,1)
    step(p,0x3e42a0,CM,0,300,30,1)
    for w in p[:2]:w.answers={(0,200,20):1}
    step(p,0x3e44f0,CM)
    assert p[0].read(OPEN+8,4)==2 and p[0].read(CLOSE+8,4)==0
    queries=[e for e in p[0].trace if e[:2]==('call',0x38d860)]
    assert len(queries)==1 and queries[0][4]==200
    for w in p[:2]:w.answers={}
    step(p,0x3e44f0,CM)
    step(p,0x3e4030,CM,0,100,10,1);step(p,0x3e44f0,CM)
    assert p[0].read(OPEN+8,4)==0
    assert hits==set(ENTRIES),(hits,set(ENTRIES))
    print(f'commdl: {total} retail/C calls agree; all 10 bodies; {len(covered)} instructions; ordered stores and engine arguments')

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36')
    args=ap.parse_args();image=args.elf.read_bytes()
    assert hashlib.sha1(image[0x80:0x454b80]).hexdigest()=='ffad4dab663cb290190bdfa34a8016d616a1652a'
    with tempfile.TemporaryDirectory() as tmp:
        out=Path(tmp)/'cm.so'
        subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Werror','-shared','-fPIC','-O2',
                        str(ROOT/'recovered/frontend/commdl.c'),str(ROOT/'recovered/frontend/completion.c'),'-o',str(out)],check=True)
        verify(image,C.CDLL(str(out)))
if __name__=='__main__':main()
