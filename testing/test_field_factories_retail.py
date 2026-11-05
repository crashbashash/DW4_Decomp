#!/usr/bin/env python3
"""Concrete descriptor constructor/factory chain vs retail instructions."""
import ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
from test_reflection_registration_retail import Registration,ROOT,Api,READ,WRITE,CALL,MASK,STACK,SYSTEM
ENTRIES={0x2b9750,0x2c2cf0,0x2bce90,0x2fef20,0x2ff010,0x2ff790,0x2fbf90,0x2fbfe0,0x305bf0,0x305c30,0x30b230,0x30b270,0x2ea3e0,0x2ea420,0x303bc0,0x303c10,0x30a820,0x303350,0x2b6d20,0x30e8e0,0x30e920,0x2bf2e0,0x2fb8e0,0x2fb930}
OBJECT,ALLOC,AVT,TOKEN,OLD,META=range(0x1950000,0x1956000,0x1000)
ALLOCATE,CODE=0x1960000,0x1960100
GUARDS={0x2b9940:0x585908,0x2c2f30:0x5860f8,0x2bd0c0:0x585b20,0x2b6f10:0x585738,0x2bf680:0x585d80}
class Factories(Registration):
    def __init__(self,image):
        super().__init__(image);self.descend=set(ENTRIES);self.default_allocator=ALLOC;self.owner=ALLOC;self.code=0x1ab
        self.result=OBJECT;self.null_token=0;self.mutate_name=False;self.pool_allocation=True
        self.w(0x587018,4,0x1959000);self.w(ALLOC,4,AVT);self.w(AVT+216,4,ALLOCATE);self.w(AVT+364,4,CODE)
        for p in range(OBJECT,OBJECT+80):self.w(p,1,0xa5)
        self.w(OLD-4,4,2);self.w(OLD-8,4,0x1958000)
        self.w(SYSTEM,1,0)
        for handle in GUARDS.values():self.w(handle,4,0x1957000)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        counts={0x2f88e0:1,0x126308:1,ALLOCATE:2,CODE:1,0x300d30:1,0x2f04f0:1,
                0x2fda40:2,0x2eb010:1,0x2eadf0:1,0x2eaf60:2,0x30c940:2,
                0x2ff0e0:2,0x2ff140:1,0x2fc440:2,**{g:0 for g in GUARDS}}
        assert e in counts,hex(e)
        self.events.append((e,*v[:counts[e]]))
        if e==0x2f88e0:return self.default_allocator
        if e in (0x126308,ALLOCATE):return self.result
        if e==0x300d30:return OBJECT-32
        if e==0x2f04f0:return self.owner
        if e==CODE:return self.code
        if e in GUARDS:self.w(GUARDS[e],4,0x1957100);return 0
        if e==0x2fda40:return self.result
        if e==0x2eb010:return 0x195a000 if self.pool_allocation else 0
        if e==0x2eadf0:return v[0]
        if e==0x2eaf60:
            if self.mutate_name:self.w(OBJECT+12,4,OLD)
            return self.null_token
        return 0

def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();retail=Factories(image);native=Factories(image);errors=[];cases=0;hits=set()
    @CALL
    def call(_,e,values):
        try:
            if e in ENTRIES:return fn(C.byref(api),e,values)
            return native.call(e,list(values[:8]))&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-field-factories-') as td:
        so=Path(td)/'factories.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/field-factories.c'),'-o',str(so)],check=True)
        fn=C.CDLL(str(so)).dw4_field_factory;fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];fn.restype=C.c_uint64
        def setup():
            nonlocal retail
            retail=Factories(image)
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            expected=retail.invoke(entry,*values);actual=fn(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in values]))
            assert not errors,errors
            if entry not in (0x30a820,0x303350):assert expected==actual,(hex(entry),expected,actual)
            def ram(w):return {p:v for p,v in w.mem.items() if not STACK-0x2000<=p<STACK+32 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry);return actual
        constructors=ENTRIES-{0x2b9750,0x2c2cf0,0x2bce90,0x2b6d20,0x2bf2e0,0x2ff790,0x30a820,0x303350}
        for entry,active,owner,refs in itertools.product(sorted(constructors),(0,1),(0,ALLOC),(0,0x80800001,0xffffffff)):
            setup();retail.w(SYSTEM,1,active);retail.owner=owner;retail.w(OBJECT+4,4,refs);compare(entry,OBJECT,1)
            assert retail.read(OBJECT+4,4)&0x7fffff==1
        for entry,active,allocator in itertools.product((0x2b9750,0x2c2cf0,0x2bce90,0x2b6d20,0x2bf2e0),(0,1,2),(0,ALLOC)):
            setup();retail.w(SYSTEM,1,active);assert compare(entry,allocator)==OBJECT
            if active:assert retail.events[-1][1]==0x1957100
        for size,prefix,allocator,default,result in itertools.product((0,4,0x7fffffff,0xffffffff),(0,16,0x80000000),(0,ALLOC),(0,ALLOC),(0,OBJECT)):
            setup();retail.default_allocator=default;retail.result=result
            compare(0x2ff790,size,prefix,allocator)
        for refs,pool,allocation,returned in itertools.product((1,2),(0,0x18f1000),(False,True),(0,TOKEN)):
            setup();retail.mutate_name=True;retail.w(OLD-4,4,refs);retail.w(0x586f20,4,pool);retail.pool_allocation=allocation;retail.null_token=returned
            compare(0x2fbfe0,OBJECT)
            assert retail.read(OLD-4,4)==refs-1 and retail.read(OBJECT+12,4)==returned
        for entry in (0x30a820,0x303350):
            setup();retail.w(OBJECT,4,0x533180 if entry==0x30a820 else 0x532c80);compare(entry,OBJECT)
        assert hits==ENTRIES,hits
    print(f'field factories retail: {cases} RAM/defined-return/ordered-call cases; all24 bodies; registration/instance creation, ownership lookup, allocator, interner and virtual defaults controlled')
if __name__=='__main__':main()
