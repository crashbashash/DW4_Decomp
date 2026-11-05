#!/usr/bin/env python3
"""Allocator registries/indices/wrappers with actual buffer duplication vs retail."""
import ctypes as C
import itertools
import subprocess
import tempfile
from pathlib import Path
from test_memory_field_copy_retail import CopyWorld,BUFFERS,OWNER
from test_memory_field_values_retail import Values
import test_reflection_registration_retail as reg
from test_reflection_registration_retail import ROOT,Api,READ,WRITE,CALL,MASK,STACK,SYSTEM
REGISTRY={0x2f04f0,0x2f0620,0x2f0630,0x2f0640,0x2f0650,0x2f0660,0x2f0670,0x2f0700,0x2fa5c0,0x2f00d0,0x2ed1c0,0x2ed200,0x2ed240}
RETURNS=REGISTRY-{0x2f0620,0x2f0660}
KIND,AVAILABLE,OWNS,OWNS_REPLACED,ALLOCATE=range(0x19c0000,0x19c0050,0x10)

class RegistryWorld(CopyWorld):
    def __init__(self,image):
        super().__init__(image);self.descend|=REGISTRY
        self.pools=[OWNER,OWNER+0x100,OWNER+0x200]
        for p in self.pools:self.w(p,4,0x1825000)
        for slot,entry in ((116,KIND),(132,AVAILABLE),(340,OWNS),(216,ALLOCATE)):self.w(0x1825000+slot,4,entry)
        self.replacement_vt=self.allocate(384,True)
        for slot,entry in ((116,KIND),(132,AVAILABLE),(340,OWNS_REPLACED),(216,ALLOCATE)):self.w(self.replacement_vt+slot,4,entry)
        self.primary=self.vector_registry([self.pools[0],self.pools[2]])
        self.secondary=self.vector_registry([self.pools[1],0,self.pools[0]])
        self.replacement=self.vector_registry([self.pools[1],self.pools[2],0])
        self.w(0x586f58,4,self.primary);self.w(0x586f60,4,self.secondary)
        self.available={p:True for p in self.pools};self.claims={p:p==OWNER for p in self.pools}
        self.kinds={p:int(i==1) for i,p in enumerate(self.pools)};self.avail_calls=0;self.w(SYSTEM,1,1)
        self.out=self.allocate(4,True);self.w(self.out,4,0xa5a5a5a5)
    def vector_registry(self,values):
        p=self.allocate(12,True);data=self.allocate(32,True)
        self.w(p,4,data+4);self.w(p+4,4,len(values));self.w(p+8,4,len(values))
        for i,v in enumerate(values):self.w(data+4+i*4,4,v)
        return p
    def step(self,pc,delay=False):
        if pc==0x2ed520:return Values.step(self,pc,delay)
        if pc==0x2f00d0:
            Values.step(self,pc+4,True);self.call_hook(0x2f88e0);return self.r[31]&0xffffffff
        if pc in (0x2ed1ec,0x2ed254):
            target=self.r[25]&0xffffffff;Values.step(self,pc+4,True);self.call_hook(target);return self.r[31]&0xffffffff
        return super().step(pc,delay)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==AVAILABLE:
            self.events.append((e,v[0]));self.avail_calls+=1
            if self.avail_calls==1:
                if self.mutation=='vtable':self.w(v[0],4,self.replacement_vt)
                if self.mutation=='registry':self.w(0x586f60,4,self.replacement);self.w(self.replacement+4,4,0)
                if self.mutation=='buffer':self.w(self.secondary,4,self.read(self.replacement,4))
                if self.mutation=='primary':self.w(0x586f58,4,self.replacement)
            return int(self.available[v[0]])
        if e in (OWNS,OWNS_REPLACED):self.events.append((e,*v[:2]));return int(self.claims[v[0]])
        if e==KIND:
            self.events.append((e,v[0]))
            if self.mutation=='mode':self.w(SYSTEM,1,0)
            if self.mutation=='kind-list':self.w(0x586f58,4,self.replacement)
            return self.kinds[v[0]]
        if e==0x2f88e0:self.events.append((e,v[0]));return OWNER
        if e==ALLOCATE:self.events.append((e,*v[:2]));return self.allocate(v[1])
        return super().call(e,args)

def main():
    reg.STORAGE=reg.FACTORIES=reg.METADATA=reg.INTERNAL=True
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();retail=RegistryWorld(image);native=RegistryWorld(image)
    cases=0;coverage=set();hits=set();errors=[]
    @CALL
    def call(_,e,args):
        try:return invoke_native(e,args)
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-allocator-registry-') as td:
        so=Path(td)/'registry.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in ('allocator-registry.c','memory-buffer-services.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));fn=lib.dw4_allocator_registry;fb=lib.dw4_memory_buffer_service
        for f in (fn,fb):f.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];f.restype=C.c_uint64
        def invoke_native(e,args):
            if e in REGISTRY:return fn(C.byref(api),e,args)
            if e in BUFFERS:return fb(C.byref(api),e,args)
            return native.call(e,list(args[:8]))&MASK
        def setup():
            nonlocal retail
            retail=RegistryWorld(image)
        def compare(entry,*args):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            expected=retail.invoke(entry,*args);actual=invoke_native(entry,(C.c_uint64*8)(*[x&MASK for x in args]))
            assert not errors,errors
            if entry in RETURNS:assert expected==actual,(hex(entry),expected,actual)
            def ram(w):return {p:v for p,v in w.mem.items() if not STACK-0x5000<=p<STACK+40 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry);coverage.update(retail.covered);return actual
        for avail,claims,buffer in itertools.product(range(8),range(8),(0,0x123456)):
            setup();retail.available={p:bool(avail&(1<<i)) for i,p in enumerate(retail.pools)};retail.claims={p:bool(claims&(1<<i)) for i,p in enumerate(retail.pools)}
            result=compare(0x2f04f0,buffer)
            order=[retail.pools[0],retail.pools[1],retail.pools[2],retail.pools[0]]
            expected=next((p for p in order if retail.available[p] and retail.claims[p]),0)
            assert result==expected
        for count in (0,0xffffffff):
            setup();retail.w(retail.secondary+4,4,count);retail.w(retail.primary+4,4,count);assert compare(0x2f04f0,0x123456)==0
        for mutation in ('vtable','registry','buffer','primary'):
            setup();retail.mutation=mutation
            if mutation!='vtable':retail.claims={p:p==retail.pools[2] for p in retail.pools}
            compare(0x2f04f0,0x123456)
            if mutation=='vtable':assert any(e[0]==OWNS_REPLACED for e in retail.events)
        for active,kind,present,mutation in itertools.product((0,1),(0,1),(False,True),('','mode','kind-list')):
            setup();retail.w(SYSTEM,1,active);retail.kinds[OWNER]=kind;retail.mutation=mutation
            if not present:
                for p in (retail.primary,retail.secondary):
                    data=retail.read(p,4)
                    for i in range(retail.read(p+4,4)):
                        if retail.read(data+i*4,4)==OWNER:retail.w(data+i*4,4,0)
            compare(0x2f0670,OWNER)
        for p in (0,OWNER,OWNER+0x100,0x123456):
            setup();compare(0x2fa5c0,retail.primary,p)
        for encoded in (0,1,2,3,4,0xffffffff,0xfffffffe):
            setup();compare(0x2f0700,encoded)
        for entry in (0x2f0620,0x2f0630,0x2f0640,0x2f0650,0x2f0660,0x2f00d0):
            setup();compare(entry,retail.out if entry==0x2f0620 else OWNER)
        for entry,size in itertools.product((0x2ed1c0,0x2ed200,0x2ed240),(0,4,12)):
            setup();p=compare(entry,size,OWNER);assert retail.allocated[p]==size
        setup();p=compare(0x2ed530,retail.buffer)
        assert p!=retail.buffer and retail.read(p,12)==retail.read(retail.buffer,12)
        compare(0x2ed460,p);assert p in retail.freed
        assert REGISTRY<=hits|coverage,REGISTRY-(hits|coverage)
    print(f'allocator registry retail: {cases} RAM/defined-return/ordered-call checkpoints; all13 bodies and actual owner/wrapper/buffer composition')
if __name__=='__main__':main()
