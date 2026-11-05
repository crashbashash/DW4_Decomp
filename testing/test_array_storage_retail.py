#!/usr/bin/env python3
"""Aligned array storage and retained named-alignment selection vs retail MIPS."""
import ctypes as C
import itertools
import subprocess
import tempfile
from pathlib import Path
import test_reflection_registration_retail as reg
from test_memory_field_values_retail import Values
from test_reflection_registration_retail import ROOT, Api, READ, WRITE, CALL, MASK, STACK
from test_object_base_retail import SCRATCH
ENTRIES={0x2fb190,0x2fb280}
SIZE,ALIGN,ALLOCATE=0x19f0000,0x19f0010,0x19f0020

class Storage(Values):
    def read(self,p,n):
        p&=0xffffffff
        return sum((self.mem[p+i] if p+i in self.mem else super(Storage,self).read(p+i,1))<<(8*i) for i in range(n))
    def __init__(self,image):
        super().__init__(image)
        self.descend|=ENTRIES
        self.size=4;self.alignment=16;self.fail=False;self.mutate='';self.comparisons=0
        self.element=self.allocate(80,True);self.element2=self.allocate(80,True)
        vt=self.allocate(256,True)
        for p in (self.element,self.element2):self.w(p,4,vt)
        self.w(vt+100,4,SIZE);self.w(vt+108,4,ALIGN)
        self.w(self.field+60,4,self.element)
        self.w(0x1825000+220,4,ALLOCATE)
        self.reference=True;self.out=self.allocate(4,True)
        self.w(0x4fb410,4,0x1234);self.w(0x4fb418,4,0x5678)
        self.registry=self.allocate(20,True);self.registry_data=self.allocate(12,True)
        self.registry_data2=self.allocate(12,True);manager=self.allocate(48,True)
        self.w(0x586dd0,4,manager);self.w(manager+44,4,self.registry)
        self.w(self.registry+4,4,1);self.w(self.registry+8,4,3);self.w(self.registry+16,4,self.registry_data)
        self.names=[]
        for i,text in enumerate((b'first',b'middle',b'last')):
            name=self.allocate(16,True);self.text(name,text);self.names.append(name)
            row=self.allocate(12,True);self.w(row+8,4,name)
            self.w(self.registry_data+i*4,4,row);self.w(self.registry_data2+i*4,4,row)
        self.w(0x4c22f0,4,self.names[1]);self.w(self.field+68,4,77)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e in (SIZE,ALIGN):
            self.events.append((e,v[0]))
            if e==SIZE and self.mutate=='element':self.w(self.field+60,4,self.element2)
            return self.size if e==SIZE else self.alignment
        if e==ALLOCATE:
            self.events.append((e,*v[:3]))
            if self.mutate=='publish':self.w(self.field+8,4,12);self.w(0x4fb410,4,0xabcd);self.w(0x4fb418,4,0xef01)
            return 0 if self.fail else self.allocate(v[1])
        if e==0x300cd0:
            self.events.append((e,*v[:2]));return int(self.reference)
        if e==0x12a4a4:
            self.events.append((e,*v[:2]));self.comparisons+=1
            if self.comparisons==1:
                if self.mutate=='count':self.w(self.registry+8,4,0)
                if self.mutate=='buffer':
                    self.w(self.registry+16,4,self.registry_data2)
                    self.w(self.registry_data2+4,4,self.read(self.registry_data+8,4))
                if self.mutate=='owner':
                    self.w(self.registry+4,4,self.read(self.registry+4,4)-1)
                    self.w(self.read(0x586dd0,4)+44,4,0)
            return int(self.string(v[0])!=self.string(v[1]))
        return super().call(e,args)

def main():
    reg.STORAGE=reg.FACTORIES=reg.METADATA=reg.INTERNAL=True
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();retail=Storage(image);native=Storage(image)
    errors=[];cases=0;coverage=set()
    @CALL
    def call(_,e,args):
        try:return native.call(e,list(args[:8]))&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-array-storage-') as td:
        so=Path(td)/'storage.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/array-storage.c'),'-o',str(so)],check=True)
        fn=C.CDLL(str(so)).dw4_array_storage;fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        def setup():
            nonlocal retail
            retail=Storage(image)
        def compare(entry,*args):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            retail.invoke(entry,*args);fn(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in args]),SCRATCH)
            assert not errors,errors
            def ram(w):return {p:v for p,v in w.mem.items() if not STACK-0x5000<=p<STACK+40 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;coverage.update(retail.covered)
        for reference,fail,size,alignment,count in itertools.product((False,True),(False,True),(1,4,0x10004),(1,16,0x10010),(0,3,0x40000000)):
            setup();retail.reference=reference;retail.fail=fail;retail.size=size;retail.alignment=alignment
            # Keep successful allocations bounded while exercising 32-bit multiplication wrap.
            if not fail and count==0x40000000 and size==1:continue
            compare(0x2fb190,retail.out,retail.field,retail.object,count,0x18f2000)
            assert retail.read(retail.out,4)==(0x5678 if fail else 0x1234),(reference,fail,size,alignment,count,hex(retail.read(retail.out,4)),retail.events)
            if fail:assert retail.read(retail.object+8,4)==retail.buffer
            else:
                p=retail.read(retail.object+8,4);n=(count*(size&65535))&0xffffffff
                assert all(retail.read(p+i,1)==(0 if reference else 0xa5) for i in range(n))
        for mutation,fail in itertools.product(('element','publish'),(False,True)):
            setup();retail.mutate=mutation;retail.fail=fail
            compare(0x2fb190,retail.out,retail.field,retail.object,3,0x18f2000)
            if mutation=='element':assert (ALIGN,retail.element2) in retail.events
            else:assert retail.read(retail.out,4)==(0xef01 if fail else 0xabcd)
        for which,mutation,refs in itertools.product((None,0,1,2,3),('','count','buffer','owner'),(1,0x800001)):
            setup();retail.mutate=mutation;retail.w(retail.registry+4,4,refs)
            missing=retail.allocate(16,True);retail.text(missing,b'missing')
            name=0 if which is None else missing if which==3 else retail.names[which]
            compare(0x2fb280,retail.field,name)
            if which is None:assert retail.read(retail.field+68,4)==0xffffffff
            if which==3:assert retail.read(retail.field+68,4)==77
            if mutation=='owner' and which is not None:assert (0x2ff820,retail.registry) in retail.events
        setup();row=retail.read(retail.registry_data,4);retail.w(row+8,4,0)
        compare(0x2fb280,retail.field,retail.names[1]);assert retail.read(retail.field+68,4)==0
        setup();retail.w(retail.read(0x586dd0,4)+44,4,0)
        compare(0x2fb280,retail.field,retail.names[0]);assert retail.read(retail.field+68,4)==77
        for count in (0,0xffffffff):
            setup();retail.w(retail.registry+8,4,count)
            compare(0x2fb280,retail.field,retail.names[0]);assert retail.read(retail.field+68,4)==77
        setup();retail.out=retail.object+8
        compare(0x2fb190,retail.out,retail.field,retail.object,3,0x18f2000)
        assert retail.read(retail.object+8,4)==0x1234
        assert ENTRIES<=coverage,ENTRIES-coverage
    print(f'array storage retail: {cases} RAM/ordered-call checkpoints; allocation/status/zeroing and retained alignment selection')
if __name__=='__main__':main()
