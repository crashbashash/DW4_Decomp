#!/usr/bin/env python3
"""Metadata construction/ownership/indexing vs retail RAM and callback order."""
import ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
from test_field_factories_retail import Factories,ENTRIES as FIELD_ENTRIES,OBJECT,ALLOC,TOKEN,OLD,ROOT,Api,READ,WRITE,CALL,MASK,STACK,SYSTEM
ENTRIES={0x2be4f0,0x2fd7c0,0x2fd820,0x2fef70,0x2fd940,0x2fd980,0x2fddb0,0x2fe7a0,0x2ea820,0x2d3060}
FIELDS,CHILD,OTHER,SOURCE,SYSTEM2,LIST,LIST2,NAME=range(0x1970000,0x1978000,0x1000)
class Metadata(Factories):
    def __init__(self,image):
        super().__init__(image);self.descend=ENTRIES|FIELD_ENTRIES|{0x2ead30};self.member=None;self.searches=[3];self.change_registry=False;self.change_child=False
        for p in range(OBJECT+80,OBJECT+104):self.w(p,1,0xa5)
        self.w(OBJECT+28,4,OLD);self.w(OBJECT+96,4,OLD);self.w(OBJECT+40,4,FIELDS);self.w(OBJECT+52,4,CHILD)
        for p in (FIELDS,CHILD,OTHER):self.w(p+4,4,1)
        self.w(SOURCE+6,1,128);self.text(NAME,b'new');self.w(SYSTEM+24,4,LIST);self.w(SYSTEM2+24,4,LIST2)
        self.w(0x585be8,4,0x1978000);self.vector(LIST,[OBJECT+0x100,OBJECT+0x200,OBJECT+0x300,OBJECT]);self.vector(LIST2,[OTHER,OBJECT]);self.skip_append=False
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==0x2c2670:self.events.append((e,v[0]));return FIELDS
        if e==0x2eaf60:
            self.events.append((e,*v[:2]))
            if self.member is not None:self.w(OBJECT+self.member,4,OLD)
            token=self.null_token if not v[1] else TOKEN
            if token:self.w(token-4,4,self.read(token-4,4)+1)
            return token
        if e==0x2f0670:self.events.append((e,v[0]));return self.code
        if e==0x2be760:self.events.append((e,));self.w(0x585be8,4,0x1978100);return 0
        if e==0x2ff820:
            self.events.append((e,v[0]))
            if self.change_child:self.w(OBJECT+52,4,OTHER)
            return 0
        if e==0x2eaa60:
            self.events.append((e,*v[:2]));n=self.read(v[0]+12,4)
            if not self.skip_append:self.w(self.read(v[0]+8,4)+n*4,4,v[1]);self.w(v[0]+12,4,n+1)
            if self.change_registry:self.w(0x586dc8,4,SYSTEM2)
            return 0
        return super().call(e,args)

def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();retail=Metadata(image);native=Metadata(image);errors=[];cases=0;hits=set()
    @CALL
    def call(_,e,values):
        try:
            if e==0x2ead30:return reg_fn(C.byref(api),e,values,STACK-0x1800)
            if e in FIELD_ENTRIES:return field_fn(C.byref(api),e,values)
            if e in ENTRIES:return fn(C.byref(api),e,values)
            return native.call(e,list(values[:8]))&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-metadata-') as td:
        so=Path(td)/'metadata.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/metadata-bootstrap.c'),str(ROOT/'recovered/engine/field-factories.c'),str(ROOT/'recovered/engine/reflection-registration.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));fn=lib.dw4_metadata_bootstrap;field_fn=lib.dw4_field_factory
        reg_fn=lib.dw4_reflection_registration;reg_fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];reg_fn.restype=C.c_uint64
        for f in (fn,field_fn):f.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];f.restype=C.c_uint64
        def setup():
            nonlocal retail
            retail=Metadata(image)
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            expected=retail.invoke(entry,*values);actual=fn(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in values]))
            assert not errors,errors
            if entry not in (0x2fd980,0x2fddb0,0x2fe7a0,0x2d3060):assert expected==actual,(hex(entry),expected,actual)
            def ram(w):return {p:v for p,v in w.mem.items() if not STACK-0x2000<=p<STACK+32 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry);return actual
        for active,allocator in itertools.product((0,1,2),(0,ALLOC)):
            setup();retail.w(SYSTEM,1,active);compare(0x2be4f0,allocator)
            if active:assert retail.events[-1][1]==0x1978100
            else:assert retail.read(OBJECT+40,4)==FIELDS and retail.read(OBJECT,4)==0x532bb0
        for entry,active,refs,source_flag,owner in itertools.product((0x2fd7c0,0x2fd820,0x2fd940,0x2fef70),(0,1),(0,0x80800001,0xffffffff),(0,128),(0,ALLOC)):
            setup();retail.w(SYSTEM,1,active);retail.w(OBJECT+4,4,refs);retail.w(SOURCE+6,1,source_flag);retail.owner=owner
            compare(entry,OBJECT,SOURCE)
        for entry,active,flag in itertools.product((0x2fd940,0x2fef70),(0,1),(0,128)):
            setup();retail.w(SYSTEM,1,active);retail.w(OBJECT+6,1,flag);compare(entry,OBJECT,OBJECT)
            assert retail.read(OBJECT+6,1)&128==0
        setup();retail.w(OBJECT+28,4,TOKEN);retail.w(TOKEN-4,4,2);compare(0x2fddb0,OBJECT,NAME)
        assert retail.read(TOKEN-4,4)==2 and retail.read(OBJECT+28,4)==TOKEN
        for pool,allocation,returned,refs in itertools.product((0,0x18f1000),(False,True),(0,TOKEN),(1,2)):
            setup();retail.w(0x586f20,4,pool);retail.pool_allocation=allocation;retail.null_token=returned;retail.member=96;retail.w(OLD-4,4,refs)
            compare(0x2fd820,OBJECT);assert retail.read(OLD-4,4)==refs-1
        for pool,name,member,refs in itertools.product((0,0x18f1000),(0,NAME),(None,28),(1,2)):
            setup();retail.w(0x586f20,4,pool);retail.member=member;retail.w(OLD-4,4,refs);compare(0x2fddb0,OBJECT,name)
        for first,second,refs,mutate in itertools.product((0,FIELDS),(0,CHILD,FIELDS),(0,1,2,0x800001),(False,True)):
            setup();retail.w(OBJECT+40,4,first);retail.w(OBJECT+52,4,second);retail.w(FIELDS+4,4,refs);retail.w(CHILD+4,4,refs);retail.change_child=mutate
            compare(0x2fd980,OBJECT)
        for present,mutate,skip in itertools.product((False,True),(False,True),(False,True)):
            setup();retail.vector(LIST,[OTHER,OBJECT] if present else []);retail.change_registry=mutate;retail.skip_append=skip
            compare(0x2fe7a0,OBJECT)
            expected=1 if present or mutate else (-1 if skip else 0)
            assert retail.read(OBJECT+12,4)==expected&0xffffffff
        for count,target in itertools.product((-1,0,1,3),(0,OBJECT,OTHER)):
            setup();retail.vector(LIST,[OTHER,OBJECT,OTHER]);retail.w(LIST+12,4,count);compare(0x2ea820,LIST,target)
        for target in (0,OBJECT,OTHER):setup();compare(0x2d3060,SYSTEM,target)
        assert hits==ENTRIES,hits
    print(f'metadata bootstrap retail: {cases} RAM/defined-return/ordered-call cases; all10 bodies, composed object header/raw allocation; metadata field-list factory, allocator/interner/vector append services controlled')
if __name__=='__main__':main()
