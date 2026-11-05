#!/usr/bin/env python3
"""Registry list publication/lifetime and current-context dispatch vs retail."""
import ctypes as C
import itertools
import subprocess
import tempfile
from pathlib import Path
from test_object_base_retail import SCRATCH
from test_allocator_registry_retail import RegistryWorld,REGISTRY,OWNER,ALLOCATE
import test_reflection_registration_retail as reg
from test_reflection_registration_retail import ROOT,Api,READ,WRITE,CALL,MASK,STACK,SYSTEM
BOOTSTRAP={0x2fa4d0,0x2fa540,0x2fa5c0,0x2fa610,0x2fa6c0,0x2fa6e0,0x2f2180,0x2f2200,0x2f8680,0x2f88d0,0x2f88e0,0x2f8920,0x2f8960,0x2f89a0,0x2f89e0,0x2f2730,0x2f2830}
RETURNS={0x2fa4d0,0x2fa540,0x2fa5c0,0x2fa6c0,0x2f8680,0x2f88d0,0x2f88e0,0x2f8920,0x2f8960,0x2f89a0,0x2f89e0,0x2f2730,0x2f2830}
REALLOCATE,FREE,CLOSE=0x19b0000,0x19b0010,0x19b0020
REALIZE,SELECTOR_REPLACED=0x19b0200,0x19b0210
CONTEXT_SLOTS={92:0x19b0100,96:0x19b0110,104:0x19b0120,108:0x19b0130,116:0x19b0140}

class BootstrapWorld(RegistryWorld):
    def __init__(self,image):
        super().__init__(image);self.descend|=BOOTSTRAP
        self.w(SYSTEM+48,4,OWNER);self.w(0x1825000+232,4,REALLOCATE);self.w(0x1825000+264,4,FREE);self.w(0x1825000+392,4,CLOSE)
        self.alloc_calls=0;self.fail_at=0;self.closed=False;self.replacement_pool=self.pools[2]
        self.contexts=[]
        for _ in range(4):
            p=self.allocate(6644,True);vt=self.allocate(256,True);self.w(p,4,vt)
            for slot,entry in CONTEXT_SLOTS.items():self.w(vt+slot,4,entry)
            self.contexts.append(p)
        self.create_success=True;self.name_calls=0
        for p in self.contexts:self.w(self.read(p,4)+208,4,REALIZE)
        self.w(0x586fd0,4,self.contexts[0]);self.w(0x587010,4,0)
        for i,p in enumerate(self.contexts[1:],1):self.w(0x586ffc+i*4,4,p)
    def step(self,pc,delay=False):
        if pc in (0x2fa6d8,0x2fa6f8):
            target=self.r[25]&0xffffffff;super().step(pc+4,True);self.call_hook(target);return self.r[31]&0xffffffff
        return super().step(pc,delay)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==ALLOCATE:
            self.events.append((e,*v[:2]));self.alloc_calls+=1
            p=0 if self.alloc_calls==self.fail_at else self.allocate(v[1])
            if self.mutation=='init-capacity' and v[1]==256:self.w(self.primary+8,4,4)
            return p
        if e==REALLOCATE:
            self.events.append((e,*v[:3]));p=self.allocate(v[2])
            if v[1]:
                for i in range(min(self.allocated.get(v[1],0),v[2])):self.w(p+i,1,self.read(v[1]+i,1))
                self.freed.add(v[1])
            if self.mutation=='append-state':self.w(self.primary+4,4,1);self.w(self.primary+8,4,8)
            return p
        if e==FREE:
            self.events.append((e,*v[:2]));self.freed.add(v[1])
            if self.mutation=='free-pool':self.w(SYSTEM+48,4,self.replacement_pool)
            if self.mutation=='free-publication':self.w(0x586f60,4,0)
            return 0
        if e==REALIZE:
            self.events.append((e,'temp' if STACK-0x5000<=v[0]<STACK else v[0],v[1],v[2],v[3]))
            self.w(v[0],4,0xfeed)
            if self.create_success:self.w(v[1]+20+v[2]*144,4,self.pools[2])
            return 0
        if e==SELECTOR_REPLACED:self.events.append((e,*v[:2]));return self.pools[1]
        if e==0x12a4a4:
            self.events.append((e,*v[:2]));self.name_calls+=1
            if self.mutation=='name-rows' and self.name_calls==1:self.text(self.contexts[0]+24+3*144,b'target')
            result=int(self.string(v[0])!=self.string(v[1]))
            if self.mutation=='name-vtable' and not result:
                self.w(self.contexts[0],4,self.replacement_vt);self.w(self.replacement_vt+92,4,SELECTOR_REPLACED)
            return result
        if e==CLOSE:
            self.events.append((e,v[0],self.read(0x586f58,4),self.read(0x586f60,4)));self.closed=True;return 0
        if e in CONTEXT_SLOTS.values():
            self.events.append((e,*v[:2]))
            if e==CONTEXT_SLOTS[92]:return OWNER if v[1]==2 else self.pools[1]
            if e==CONTEXT_SLOTS[96]:return self.pools[2] if v[1] else 0
            return v[0]^v[1]^e
        return super().call(e,args)

def main():
    reg.STORAGE=reg.FACTORIES=reg.METADATA=reg.INTERNAL=True
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();retail=BootstrapWorld(image);native=BootstrapWorld(image)
    cases=0;coverage=set();hits=set();errors=[]
    @CALL
    def call(_,e,args):
        try:return invoke_native(e,args)
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-registry-bootstrap-') as td:
        so=Path(td)/'bootstrap.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in ('registry-bootstrap.c','allocator-registry.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));fn=lib.dw4_registry_bootstrap;fr=lib.dw4_allocator_registry
        fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        fr.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];fr.restype=C.c_uint64
        def invoke_native(e,args):
            if e in BOOTSTRAP:return fn(C.byref(api),e,args,SCRATCH+0x600)
            if e in REGISTRY:return fr(C.byref(api),e,args)
            return native.call(e,list(args[:8]))&MASK
        def setup():
            nonlocal retail
            retail=BootstrapWorld(image)
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
        for mutation,fail in itertools.product(('','init-capacity'),(False,True)):
            setup();retail.mutation=mutation;retail.fail_at=1 if fail else 0
            compare(0x2fa4d0,retail.primary)
            assert retail.read(retail.primary+4,4)==0
            assert retail.read(retail.primary+8,4)==(4 if mutation else 64)
        for flag,buffer,receiver in itertools.product((0,1,0xffff,0x10001,0x8000),(False,True),(False,True)):
            setup();retail.w(retail.primary,4,retail.buffer if buffer else 0)
            compare(0x2fa540,retail.primary if receiver else 0,flag)
            assert (retail.primary in retail.freed)==(receiver and (flag&0xffff) in (1,))
        for capacity,count in ((0,0),(4,0),(4,3),(4,4),(64,63),(64,64),(64,65)):
            setup();data=retail.allocate(max(4,capacity)*4)
            retail.w(retail.primary,4,data);retail.w(retail.primary+4,4,count);retail.w(retail.primary+8,4,capacity)
            compare(0x2fa610,retail.primary,retail.pools[1]);p=retail.read(retail.primary,4)
            assert retail.read(retail.primary+4,4)==count+1 and retail.read(p+count*4,4)==retail.pools[1]
            if count>=capacity:
                assert retail.read(retail.primary+8,4)==capacity+4
                for i in range(capacity,capacity+4):
                    if i!=count:assert retail.read(p+i*4,4)==0
        setup();retail.mutation='append-state';retail.w(retail.primary+4,4,2);retail.w(retail.primary+8,4,2)
        compare(0x2fa610,retail.primary,retail.pools[1]);assert retail.read(retail.primary+4,4)==2
        setup();retail.mutation='free-pool';compare(0x2fa540,retail.primary,1)
        assert (FREE,retail.replacement_pool,retail.primary) in retail.events
        for fail_at in range(5):
            setup();retail.fail_at=fail_at;compare(0x2f2180,OWNER)
            assert retail.read(OWNER+7,1)==0
            if not fail_at:
                primary=retail.read(0x586f58,4);secondary=retail.read(0x586f60,4)
                assert retail.read(primary+4,4)==1 and retail.read(retail.read(primary,4),4)==OWNER
                assert retail.read(secondary+4,4)==0
                assert retail.read(primary+8,4)==retail.read(secondary+8,4)==64
                lists={primary,secondary,retail.read(primary,4),retail.read(secondary,4)}
                compare(0x2f2200,OWNER);assert lists<=retail.freed and retail.closed
                assert retail.read(0x586f58,4)==retail.read(0x586f60,4)==0
        setup();retail.mutation='free-publication';compare(0x2f2200,OWNER)
        assert retail.closed
        for mode,fallback,slot in itertools.product((-1,0,1,2,3,4),(False,True),(False,True)):
            setup();retail.w(0x587010,4,mode)
            if not fallback:retail.w(0x586fd0,4,0)
            if not slot and 1<=mode<=3:retail.w(0x586ffc+mode*4,4,0)
            result=compare(0x2f8680)
            expected=retail.contexts[mode] if 1<=mode<=3 and slot else retail.contexts[0] if mode==0 and fallback else 0
            assert result==expected
        setup();compare(0x2f88d0)
        for entry,mode,value in itertools.product((0x2f88e0,0x2f8920,0x2f8960,0x2f89a0,0x2f89e0),range(4),(0,2,0x1234)):
            setup();retail.w(0x587010,4,mode);compare(entry,value)
            assert retail.events[-1][1]==retail.contexts[mode]
        for entry in (0x2fa6c0,0x2fa6e0,0x2fa5c0):
            setup();compare(entry,12 if entry==0x2fa6c0 else retail.primary,OWNER)
        def records():
            for p in retail.contexts:
                vt=retail.read(p,4);retail.w(vt+92,4,0x2f2730);retail.w(vt+96,4,0x2f2830)
        for selector,present,request,success in itertools.product((-1,0,2,45,46),(False,True),(False,True),(False,True)):
            setup();records();ctx=retail.contexts[0];retail.create_success=success
            if 0<=selector<46:
                retail.w(ctx+20+selector*144,4,OWNER if present else 0)
                retail.w(ctx+160+selector*144,4,0x04000000 if request else 0)
            result=compare(0x2f2730,ctx,selector)
            expected=0 if not 0<=selector<46 else OWNER if present else retail.pools[2] if request and success else 0
            assert result==expected
        for depth in (0,1,2,3):
            setup();records();retail.w(0x587010,4,depth)
            retail.w(retail.contexts[1]+20+7*144,4,retail.pools[1])
            result=compare(0x2f2730,retail.contexts[3],7)
            assert result==(retail.pools[1] if depth==3 else 0)
        setup();records();retail.w(0x587010,4,3);retail.w(0x587004,4,retail.contexts[3])
        assert compare(0x2f2730,retail.contexts[3],7)==0
        setup();records();retail.w(0x587010,4,3)
        assert compare(0x2f2730,retail.contexts[0],7)==0
        for name_case,mutation in itertools.product(('null','empty','first','last','missing'),('','name-rows','name-vtable')):
            setup();records();ctx=retail.contexts[0]
            retail.text(ctx+24,b'first');retail.w(ctx+20,4,OWNER)
            retail.text(ctx+24+45*144,b'last');retail.w(ctx+20+45*144,4,retail.pools[2])
            name=retail.allocate(16,True)
            retail.text(name,{'empty':b'','first':b'first','last':b'last','missing':b'target','null':b''}[name_case])
            retail.mutation=mutation
            compare(0x2f2830,ctx,0 if name_case=='null' else name)
        setup();records();ctx=retail.contexts[0];retail.text(ctx+24+2*144,b'pool');retail.w(ctx+20+2*144,4,OWNER)
        name=retail.allocate(8,True);retail.text(name,b'pool')
        assert compare(0x2f8920,name)==OWNER
        assert compare(0x2f88e0,2)==OWNER
        assert BOOTSTRAP<=hits|coverage,BOOTSTRAP-(hits|coverage)
    print(f'registry bootstrap retail: {cases} RAM/defined-return/ordered-call checkpoints; all17 bodies and real registry publication/teardown')
if __name__=='__main__':main()
