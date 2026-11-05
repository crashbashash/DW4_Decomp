#!/usr/bin/env python3
"""Alias-pool method run vs original instructions, RAM, returns and callback order.

Backing allocator, locks, files, ownership services and base constructors are
controlled leaves. Real alias wrappers, counters, lifetime and backend compose.
"""
import ctypes as C
import itertools
from pathlib import Path
import subprocess
import sys
import tempfile
from test_alias_pool_binding_retail import BindingWorld,SELF,OLD,NEW,VT,OUT,SYSTEM,ALLOCATOR
from test_messenger_dispatch_retail import ROOT,Api,READ,WRITE,CALL,MASK,STACK

sys.path.insert(0,str(ROOT/'tools'))
import verify
_,SYMBOLS=verify.load_symbols(str(ROOT/'config/SLUS-20836/symbols.txt'))
ENTRIES={p for p in SYMBOLS if 0x2d0560<=p<0x2d1640}|{0x2cd170}
assert len(ENTRIES)==54 and sum(SYMBOLS[p][1] for p in ENTRIES)==4160, 'review alias method boundaries before testing'
AVT,LOCK,LVT,FILE,FVT,DATA,LABEL,NAME,SCRATCH=range(0x1820000,0x1829000,0x1000)
LEAVES=range(0x1840000,0x1842000,0x10)
(ALLOC,REALLOC,FREE,SIZE,ASSIGN,INDEX,USAGE,TRANSFORM,PURGE1,PURGE2,PURGE3,
 OWNERQUERY,LOCKINIT,LOCKTAKE,LOCKDROP,LOCKCLOSE,RESIZE,STATS,CLOSE,GETNAME,
 FILEOPEN,FILEWRITE,FILECLOSE)=list(LEAVES)[:23]


class RuntimeWorld(BindingWorld):
    def __init__(self,image):
        super().__init__(image);self.descend=set(ENTRIES)
        for slot in range(0,416,4):self.w(VT+slot,4,self.read(0x5313a0+slot,4))
        for slot,fn in ((92,RESIZE),(200,STATS),(392,CLOSE),(396,GETNAME)):
            self.w(VT+slot,4,fn)
        for p in (OLD,NEW):self.w(p,4,AVT);self.w(p+4,4,2)
        for slot,fn in ((220,ALLOC),(236,REALLOC),(264,FREE),(336,SIZE),(372,ASSIGN),
                        (380,INDEX),(192,USAGE),(260,TRANSFORM),(248,PURGE1),
                        (252,PURGE2),(256,PURGE3),(376,OWNERQUERY)):
            self.w(AVT+slot,4,fn)
        self.w(LOCK,4,LVT);self.w(LOCK+4,4,1)
        for slot,fn in ((92,LOCKINIT),(132,LOCKTAKE),(124,LOCKDROP),(96,LOCKCLOSE)):self.w(LVT+slot,4,fn)
        self.w(FILE,4,FVT);self.w(FILE+4,4,1)
        for slot,fn in ((100,FILEOPEN),(124,FILEWRITE),(104,FILECLOSE)):self.w(FVT+slot,4,fn)
        self.w(SELF+180,4,OLD);self.w(SELF+144,8,4096);self.w(SELF+176,2,16)
        self.w(SELF+120,4,7);self.w(SELF+172,4,24)
        self.text(LABEL,b'label');self.text(NAME,b'pool')
        for i in range(64):self.w(DATA+i,1,0xa5)
        self.result=DATA;self.old_size=24;self.usage=[100,120];self.usage_calls=0
        self.growth=0;self.growth_calls=0;self.grow_to=4096;self.owner=SELF;self.owner_status=0x1234
        self.index=7;self.named=False;self.open=True;self.mutation=None
        self.w(0x4fb410,4,0x1234);self.w(0x4fb418,4,0x5678)
        self.base_init=self.read(0x5313a0+44,4);self.base_set=self.read(0x5313a0+36,4)
        self.base_close=self.read(0x5313a0+392,4)
    def text(self,p,b):
        for i,v in enumerate(b+b'\0'):self.w(p+i,1,v)
    def step(self,pc,delay=False):
        w=self.read(pc,4);op=w>>26;rs=(w>>21)&31
        tail=op==2 or (op==0 and w&63==8 and rs!=31)
        if tail:
            target=((pc+4)&0xf0000000)|((w&0x3ffffff)<<2) if op==2 else self.r[rs]&0xffffffff
            if target not in self.descend:
                self.covered.add(pc);super().step(pc+4,True);self.call_hook(target);return self.r[31]&0xffffffff
        return super().step(pc,delay)
    def call_hook(self,e):
        values=self.r[4:12]
        if e==0x304430:values=values+[self.read(self.r[29]+i*8,8) for i in range(4)]
        self.r[2]=self.call(e,values)&MASK
    def call(self,e,args):
        count={ALLOC:3,REALLOC:4,FREE:2,SIZE:2,ASSIGN:4,INDEX:1,USAGE:1,TRANSFORM:2,
               PURGE1:2,PURGE2:2,PURGE3:1,OWNERQUERY:2,LOCKINIT:2,LOCKTAKE:3,
               LOCKDROP:2,LOCKCLOSE:2,RESIZE:3,STATS:4,CLOSE:1,GETNAME:1,
               FILEOPEN:3,FILEWRITE:2,FILECLOSE:1,0x2ff820:1,0x301000:1,
               0x2ba650:1,0x2f0880:1,0x2f0180:3,0x2f0220:3,0x2f0320:3,
               0x2f89a0:1,0x304680:0,0x2c4ca0:1,0x128528:1,0x12724c:3,
               0x2eff70:1,0x2effb0:1,0x2efff0:1,0x2f0030:1,0x2f0040:3,
               0x2cd3f0:0,0x2fda40:2,self.base_init:1,self.base_set:2,self.base_close:1}
        if e==0x304430:count[e]=12 if args[0]==0x4f90c0 else 2
        assert e in count,hex(e)
        raw=list(args[:count[e]]);v=[x&0xffffffff for x in raw]
        def normalized(x):return 'out' if STACK-0x10000<=x<STACK+64 or SCRATCH<=x<SCRATCH+0x10000 else x
        state=(self.read(SELF+116,4),self.read(SELF+128,8),self.read(SELF+136,4),
               self.read(SELF+140,4),self.read(SELF+180,4))
        self.events.append((e,tuple(normalized(x) for x in raw),state))
        if e in (ALLOC,REALLOC):
            if self.mutation=='allocate-alias':self.w(SELF+180,4,NEW)
            return self.result
        if e==SIZE:return self.old_size
        if e==RESIZE:
            self.growth_calls+=1
            if self.growth_calls<=self.growth:
                if self.growth_calls==self.growth:self.w(SELF+144,8,self.grow_to)
                return 1
            return 0
        if e in (ASSIGN,0x2f0220,0x2f0320):
            self.w(v[0],4,0x9876)
            if self.mutation=='ownership-alias':self.w(SELF+180,4,NEW)
            return 0
        if e==INDEX:
            if self.mutation=='index':self.w(SELF+120,4,8)
            return self.index
        if e==USAGE:
            n=self.usage[min(self.usage_calls,len(self.usage)-1)];self.usage_calls+=1
            if self.mutation=='usage-alias':self.w(SELF+180,4,NEW)
            return n
        if e==TRANSFORM:return self.result
        if e in (PURGE1,PURGE2,LOCKINIT,LOCKTAKE,LOCKDROP,LOCKCLOSE):
            self.w(v[0],4,0x8765)
            if e==LOCKINIT and self.mutation=='lock-init':self.w(SELF+116,4,NEW)
            return 0
        if e==OWNERQUERY:return self.query_result
        if e==GETNAME:return NAME if self.named else 0
        if e==0x2f89a0:return NAME
        if e==0x2f0180:
            self.w(v[0],4,self.owner_status);self.w(v[2],4,self.owner)
            if self.mutation=='owner-status':self.w(0x4fb410,4,self.owner_status)
            return 0
        if e==0x2f0880:self.w(v[0],4,0x11223344);return 0
        if e==0x301000:return ALLOCATOR
        if e==0x2ba650:return LOCK
        if e==0x2c4ca0:return FILE
        if e==FILEOPEN:return int(self.open)
        if e==0x12724c:
            for i in range(min(v[2],64)):self.w(v[0]+i,1,v[1]&255)
            return raw[0]
        if e in (0x2eff70,0x2effb0,0x2efff0):self.w(v[0]+4,4,1);self.w(v[0],4,0x12345678)
        if e==0x2f0040:return SELF
        if e==0x2fda40:return SELF
        if e==self.base_init:
            self.w(v[0]+144,8,4096);self.w(v[0]+176,2,16)
        return 0


def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();native=RuntimeWorld(image)
    errors=[];cases=0;coverage=set();tested=set();depth=0
    @CALL
    def call(_,e,args):
        try:return invoke(e,args)&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-alias-runtime-') as td:
        so=Path(td)/'runtime.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',
                        *[str(ROOT/'recovered/engine'/p) for p in ('alias-pool-runtime.c','alias-pool-binding.c')],'-o',str(so)],check=True)
        fn=C.CDLL(str(so)).dw4_alias_pool_runtime
        fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        def invoke(e,args):
            nonlocal depth
            if e not in ENTRIES:return native.call(e,args)&MASK
            depth+=1
            try:return fn(C.byref(api),e,args,SCRATCH+depth*256)
            finally:depth-=1
        def compare(w,entry,*args,result=False):
            nonlocal cases
            w.events=[];errors.clear()
            for key,value in w.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(list,dict,set)) else value)
            expected=w.invoke(entry,*args)
            actual=invoke(entry,(C.c_uint64*8)(*[v&MASK for v in args]))
            assert not errors,errors
            if result:assert expected==actual,(hex(entry),hex(expected),hex(actual))
            def ram(obj):return {p:v for p,v in obj.mem.items() if v and not STACK-0x10000<=p<STACK+64 and not SCRATCH<=p<SCRATCH+0x10000}
            er,ar=ram(w),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:10])
            assert w.events==native.events,(hex(entry),w.events,native.events)
            cases+=1;tested.add(entry);coverage.update(w.covered)
        # All non-allocation interface entries, including output-first methods.
        output_entries={0x2d0690,0x2d06c0,0x2d08b0,0x2d08d0,0x2d0900,0x2d0930,0x2d0960,0x2d0cd0,0x2d0d10}
        void_entries={0x2d0560,0x2d0600,0x2d0620,0x2d0640,0x2d0690,0x2d06c0,0x2d08b0,0x2d08d0,0x2d0900,0x2d0930,0x2d0960,0x2d0a10,0x2d0a50,0x2d0cd0,0x2d0d10,0x2d0d50,0x2d0e50,0x2d1030,0x2d10b0,0x2d1200,0x2d15d0}
        for entry in sorted(ENTRIES-{0x2d06c0,0x2d1210,0x2cd170}):
            w=RuntimeWorld(image)
            args=(OUT,SELF,0x100000001) if entry in output_entries else (SELF,0,4,32,0)
            compare(w,entry,*args,result=entry not in void_entries)
        for entry in (0x2d0cd0,0x2d0d10):
            w=RuntimeWorld(image);w.w(SELF+180,4,0);compare(w,entry,OUT,SELF)
        for entry,args in ((0x2d0560,(SELF,0)),(0x2d1030,(SELF,NEW)),(0x2d15d0,(SELF,))):
            w=RuntimeWorld(image);w.w(OLD+4,4,1);w.w(SELF+152,4,OLD)
            compare(w,entry,*args)
        for mode,present,mutation in ((0,True,None),(1,False,None),(1,False,'lock-init')):
            w=RuntimeWorld(image);w.w(LOCK+4,4,0);w.w(NEW+4,4,1);w.mutation=mutation
            w.w(SELF+116,4,LOCK if present else 0);compare(w,0x2d06c0,OUT,SELF,mode)
        for mode,present,refs,mutation in itertools.product((0,1,2,255,256),(False,True),(1,2,0x800001),(None,'lock-init')):
            w=RuntimeWorld(image);w.mutation=mutation;w.w(LOCK+4,4,refs);w.w(SELF+116,4,LOCK if present else 0)
            compare(w,0x2d06c0,OUT,SELF,mode)
        # Alloc/realloc/free, null alias, failure, both ownership paths, locks,
        # full64 limits and the deliberate reallocation failure accounting.
        for old,freed,delegated,locked,success,alias in itertools.product((0,DATA),(False,True),(0,1),(False,True),(False,True),(0,OLD)):
            if freed and not alias and old:continue # retail unconditionally dereferences the free backing pool
            w=RuntimeWorld(image);w.result=DATA+64 if success else 0
            w.w(SELF+128,8,100);w.w(SELF+136,4,7);w.w(SELF+140,4,3)
            w.w(SELF+180,4,alias);w.w(SELF+113,1,delegated);w.w(SELF+116,4,LOCK if locked else 0)
            compare(w,0x2d1210,SELF,old,MASK if freed else 40,0x10020,result=True)
        for current,size,limit,growth in ((100,40,120,0),(100,40,120,1),(100,40,120,2),(1<<40,32,(1<<40)+64,0),(MASK,2,100,0),(100,0x100000010,4096,0),(100,0xfffffffe,4096,0),(100,0x100000000,4096,0)):
            w=RuntimeWorld(image);w.w(SELF+128,8,current);w.w(SELF+144,8,limit);w.growth=growth
            compare(w,0x2d1210,SELF,0,size,4,result=True)
        for mutation in ('ownership-alias','allocate-alias'):
            w=RuntimeWorld(image);w.mutation=mutation
            compare(w,0x2d1210,SELF,DATA,48,4,result=True)
        for allocs,frees,high in ((0x7fffffff,0,0),(0xffffffff,0,0),(4,7,0xffffffff)):
            w=RuntimeWorld(image);w.w(SELF+136,4,allocs);w.w(SELF+140,4,frees);w.w(SELF+168,4,high)
            compare(w,0x2d1210,SELF,0,32,4,result=True)
        for entry,count,size in itertools.product((0x2d0b00,0x2d0b70),(0,2,0x80000000),(0,4,0x10000)):
            w=RuntimeWorld(image);compare(w,entry,SELF,count,size,32,result=True)
        for delegated,owner,status,index,mutation in itertools.product((0,1),(SELF,NEW),(0x1234,0x7777),(7,8),(None,'index','owner-status')):
            w=RuntimeWorld(image);w.owner=owner;w.owner_status=status;w.index=index;w.mutation=mutation;w.w(SELF+113,1,delegated)
            compare(w,0x2d0da0,SELF,DATA,result=True)
        for stats,alias,mutation in itertools.product((0,1),(0,OLD),(None,'usage-alias')):
            w=RuntimeWorld(image);w.w(SELF+104,1,stats);w.w(SELF+180,4,alias);w.mutation=mutation
            w.usage=[1<<40,(1<<40)+0x80000010]
            compare(w,0x2d0c10,SELF,DATA,result=True)
        for name,label in itertools.product((False,True),(0,LABEL)):
            w=RuntimeWorld(image);w.named=name;w.w(SELF+128,8,1<<40);w.w(SELF+136,4,0xffffffff)
            compare(w,0x2d0e50,SELF,label)
        for file,success,locked in itertools.product((0,LABEL),(False,True),(False,True)):
            w=RuntimeWorld(image);w.open=success;w.w(SELF+116,4,LOCK if locked else 0)
            compare(w,0x2d10b0,SELF,0,0,0,file)
        for active in (0,1,255):
            w=RuntimeWorld(image);w.w(SYSTEM,1,active)
            compare(w,0x2cd170,ALLOCATOR,result=True)
        # Persistent construction -> lock -> allocate/reallocate/free -> detach
        # lock -> destruction: actual wrapper/backend/alias controller bodies.
        w=RuntimeWorld(image)
        for entry,args,result in ((0x2d1540,(SELF,),True),(0x2d0560,(SELF,OLD),False),
                                  (0x2d06c0,(OUT,SELF,1),False),(0x2d0600,(SELF,),False),
                                  (0x2d0ac0,(SELF,32),True),(0x2d0be0,(SELF,DATA,48),True),
                                  (0x2d0d80,(SELF,DATA),True),(0x2d06c0,(OUT,SELF,0),False),
                                  (0x2d15d0,(SELF,),False)):
            compare(w,entry,*args,result=result)
        assert tested==ENTRIES,sorted(hex(p) for p in ENTRIES-tested)
        total=sum(SYMBOLS[p][1] for p in ENTRIES)
        expected={q for p in ENTRIES for q in range(p,p+SYMBOLS[p][1],4)}
        assert expected<=coverage,sorted(hex(p) for p in expected-coverage)
        if '--show-gaps' in sys.argv:
            print('missing instructions:', ' '.join(hex(q) for p in sorted(ENTRIES) for q in range(p,p+SYMBOLS[p][1],4) if q not in coverage))
        print(f'alias runtime: {cases} retail RAM/return/ordered-call cases; {len(tested)} bodies/{total} bytes, {len(coverage)} instruction addresses; backing services remain leaves')


if __name__=='__main__':main()
