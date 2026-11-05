#!/usr/bin/env python3
"""Alias binding/accounting block vs original instructions, RAM and call order.

Destroy/query/reset callbacks remain controlled leaves; callback-time refcounts,
publication and enabled state are observed. This does not test an allocator backend.
"""
import ctypes as C
import itertools
from pathlib import Path
import subprocess
import tempfile
from test_messenger_dispatch_retail import World,ROOT,Api,READ,WRITE,CALL,MASK,STACK

ENTRIES=(0x2d0560,0x2d0600,0x2d0620,0x2d0640,0x2d0670,
         0x2d0680,0x2d0690,0x2d06a0,0x2d06b0)
SELF,OLD,NEW,VT,QUERY,RESET,OUT=range(0x1800000,0x1807000,0x1000)
SYSTEM,INIT,SET,ALLOCATOR=range(0x1810000,0x1814000,0x1000)


class BindingWorld(World):
    def read(self,p,n):
        p&=0xffffffff
        return sum((self.mem[p+i] if p+i in self.mem else super(BindingWorld,self).read(p+i,1))<<(8*i) for i in range(n))
    def __init__(self,image):
        super().__init__(image)
        self.descend=set(ENTRIES);self.events=[];self.query_result=1;self.mutate=False
        self.w(SELF,4,VT);self.w(OLD,4,VT);self.w(NEW,4,VT)
        self.w(VT+376,4,QUERY);self.w(VT+124,4,RESET)
        self.descend.add(0x2cd170)
        self.w(0x586dc8,4,SYSTEM);self.w(0x5869b0,4,0x12345678)
        self.w(0x4fb418,4,0x76543210)
        self.w(VT+44,4,INIT);self.w(VT+36,4,SET)
        self.change_meta=False
    def call(self,e,args):
        v=[x&0xffffffff for x in args[:8]]
        if e in (0x2cd3f0,0x2fda40,0x2f0040,0x2d1540,INIT,SET):
            count={0x2cd3f0:0,0x2fda40:2,0x2f0040:3,0x2d1540:2,INIT:1,SET:2}[e]
            self.events.append((e,*v[:count]))
            if e==0x2cd3f0 and self.change_meta:self.w(0x5869b0,4,0x23456789)
            return NEW if e==0x2fda40 else OLD if e in (0x2f0040,0x2d1540) else 0
        assert e in (0x2ff820,QUERY,RESET),hex(e)
        self.events.append((e,*v[:2 if e==QUERY else 1],
                            self.read(SELF+180,4),self.read(OLD+4,4),
                            self.read(NEW+4,4),self.read(SELF+112,1)))
        if e==QUERY:return self.query_result
        if self.mutate:
            # Destruction may change the old slot; the captured incoming alias
            # still wins. Reset may write the flag before the final clear.
            self.w(SELF+180,4,0x12345678);self.w(SELF+112,1,0x7e)
        return 0


def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes()
    native=BindingWorld(image);errors=[];cases=0;coverage=set()
    @CALL
    def call(_,e,args):
        try:return native.call(e,args)&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n))
    write=WRITE(lambda _,p,n,v:native.write(p,n,v))
    api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-alias-binding-') as td:
        so=Path(td)/'binding.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',
                        str(ROOT/'recovered/engine/alias-pool-binding.c'),'-o',str(so)],check=True)
        fn=C.CDLL(str(so)).dw4_alias_pool_binding
        fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)]
        fn.restype=C.c_uint64
        def compare(w,entry,*args):
            nonlocal cases
            w.events=[]
            native.mem=w.mem.copy();native.events=[]
            native.query_result=w.query_result;native.mutate=w.mutate
            native.change_meta=w.change_meta
            result=w.invoke(entry,*args)
            actual=fn(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in args[:8]]))
            assert not errors,errors
            if entry in (0x2cd170,0x2d0670,0x2d0680,0x2d06a0,0x2d06b0):assert result==actual,(result,actual)
            def ram(world):return {p:v for p,v in world.mem.items() if v and not STACK-4096<=p<STACK+64}
            assert ram(w)==ram(native),(hex(entry),[(hex(p),ram(w).get(p),ram(native).get(p)) for p in ram(w).keys()|ram(native).keys() if ram(w).get(p)!=ram(native).get(p)][:10])
            assert w.events==native.events,(w.events,native.events)
            cases+=1;coverage.update(w.covered)
        for old,new,refs,result,mutation in itertools.product((0,OLD,NEW),(0,NEW),(1,2,0x800001,0xffffffff),(0,1,0x123),(False,True)):
            w=BindingWorld(image);w.query_result=result;w.mutate=mutation
            w.w(SELF+180,4,old);w.w(OLD+4,4,refs);w.w(NEW+4,4,refs);w.w(SELF+113,1,0x55)
            compare(w,0x2d0560,SELF,new)
            assert w.read(SELF+180,4)==new
            assert w.read(SELF+113,1)==(result&255 if new else 0)
            if old==new==NEW:assert not any(e[0]==0x2ff820 for e in w.events)
        for entry,flag in itertools.product(ENTRIES[1:],(0,1,255)):
            w=BindingWorld(image);w.mutate=True
            for i in range(112,184):w.w(SELF+i,1,0xa5)
            w.w(SELF+112,1,flag)
            compare(w,entry,OUT if entry==0x2d0690 else SELF)
            if entry==0x2d0600:assert w.read(SELF+112,1)==1
            if entry==0x2d0620:assert w.read(SELF+112,1)==flag
            if entry==0x2d0640:assert w.read(SELF+112,1)==0
        # A retained bind, same-object rebind, replacement and detach operate on
        # one world rather than resetting the fixture between transitions.
        w=BindingWorld(image);w.w(OLD+4,4,1);w.w(NEW+4,4,1)
        for value in (OLD,OLD,NEW,0):compare(w,0x2d0560,SELF,value)
        assert w.read(OLD+4,4)==1 and w.read(NEW+4,4)==1
        for active,change in itertools.product((0,1,255),(False,True)):
            w=BindingWorld(image);w.w(SYSTEM,1,active);w.change_meta=change
            compare(w,0x2cd170,ALLOCATOR)
            if active:
                assert w.events==[(0x2cd3f0,), (0x2fda40,0x23456789 if change else 0x12345678,ALLOCATOR)]
            else:
                assert w.events==[(0x2f0040,184,0,ALLOCATOR),(0x2d1540,OLD,1),(INIT,OLD),(SET,OLD,0)]
        sizes=(152,32,24,48,8,8,16,8,8)
        expected={p for entry,size in zip(ENTRIES,sizes) for p in range(entry,entry+size,4)}
        expected.update(range(0x2cd170,0x2cd210,4))
        assert expected<=coverage,sorted(hex(p) for p in expected-coverage)
    print(f'alias factory/binding/accounting: {cases} retail RAM/ordered-call cases, {len(coverage)} instruction addresses; backend remains separate')


if __name__=='__main__':main()
