#!/usr/bin/env python3
"""Metadata name selectors, field replacement and actual initializer arrays."""
import ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
import test_reflection_registration_retail as reg
from test_object_base_retail import ObjectBase,ENTRIES as BASE_ENTRIES,SCRATCH
from test_reflection_registration_retail import ROOT,Api,READ,WRITE,CALL,MASK,STACK,BASE,META,FIELD,CBLIST,SYSTEM
from test_field_factories_retail import ENTRIES as FIELD_ENTRIES
from test_metadata_bootstrap_retail import ENTRIES as META_ENTRIES
from test_internal_object_lists_retail import ENTRIES as LIST_ENTRIES
from test_object_storage_retail import ENTRIES as STORAGE_ENTRIES
from test_object_creation_retail import ENTRIES as CREATION_ENTRIES
ENTRIES={0x2d3400,0x2d3420,0x2d3480,0x2ea780,0x2fdf20,0x2fdea0}
RETURNS={0x2d3400,0x2d3420,0x2ea780,0x2fdf20}
BUFFER,ALT,SELECTOR,QUERY,REGISTRAR,CALLBACK,CALLBACK2=0x1d00000,0x1d10000,0x19a0000,0x19a1000,0x19a2000,0x19a2100,0x19a2200
DEPS={0x2cab90,0x36a180}
class Services(ObjectBase):
    def __init__(self,image):
        super().__init__(image);self.descend|=ENTRIES
        self.callback_buffers=0;self.freed=set();self.mutate_count=False;self.mutate_iteration=False
        self.w(SYSTEM+52,4,0x18f2000);self.w(0x585cd8,4,SELECTOR);self.w(SELECTOR+8,4,12)
        self.w(CBLIST,4,BUFFER);self.w(CBLIST+4,4,0);self.w(CBLIST+8,4,4)
        self.text(QUERY,b'_refCount');self.array_buffer(BUFFER,256)
    def array_buffer(self,p,n):
        for i in range(-16,n+16):self.w(p+i,1,0xa5)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==0x2ed240:
            self.events.append((e,*v[:2]))
            if v[0]==12:
                self.freed.discard(CBLIST);return CBLIST if self.callback_allocation else 0
            assert v[0]<=65536,v
            p=BUFFER+self.callback_buffers*0x1000;self.callback_buffers+=1;self.array_buffer(p,v[0])
            if self.mutate_count:self.w(CBLIST+4,4,2);self.mutate_count=False
            return p
        if e==0x2ed330:
            self.events.append((e,*v[:2]));assert v[1]<=65536,v
            p=BUFFER+(self.callback_buffers+1)*0x1000;self.callback_buffers+=1;self.array_buffer(p,v[1])
            for i in range(min(64,v[1])):self.w(p+i,1,self.read(v[0]+i,1))
            self.freed.add(v[0])
            if self.mutate_count:self.w(CBLIST+4,4,2);self.mutate_count=False
            return p
        if e in (0x2ed460,0x2ed5c0):self.events.append((e,v[0]));self.freed.add(v[0]);return 0
        if e==0x12a4a4:self.events.append((e,*v[:2]));return int(self.string(v[0])!=self.string(v[1]))
        if e==REGISTRAR:self.events.append((e,));return CBLIST
        if e in (CALLBACK,CALLBACK2):
            self.events.append((e,v[0]))
            if self.mutate_iteration:
                self.w(CBLIST,4,ALT);self.w(CBLIST+4,4,0);self.mutate_iteration=False
            return 0
        if e in DEPS:self.events.append((e,v[0]));return 0
        return super().call(e,args)

def main():
    reg.STORAGE=reg.FACTORIES=reg.METADATA=reg.INTERNAL=True
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();retail=Services(image);native=Services(image);errors=[];cases=0;hits=set();executed=set()
    @CALL
    def call(_,e,values):
        try:return invoke_native(e,values)
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-metadata-callback-') as td:
        so=Path(td)/'services.so'
        sources=('metadata-callback-services.c','object-base.c','reflection-registration.c','field-factories.c','metadata-bootstrap.c','internal-object-lists.c','object-storage.c','object-creation.c')
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in sources],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));names=('dw4_metadata_callback_service','dw4_object_base','dw4_reflection_registration','dw4_field_factory','dw4_metadata_bootstrap','dw4_internal_object_list','dw4_object_storage','dw4_object_creation')
        fns={name:getattr(lib,name) for name in names}
        for name,f in fns.items():
            f.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)]+([C.c_uint32] if name in ('dw4_object_base','dw4_reflection_registration') else []);f.restype=C.c_uint64
        def invoke_native(e,values):
            if e in ENTRIES:return fns['dw4_metadata_callback_service'](C.byref(api),e,values)
            if e in BASE_ENTRIES:return fns['dw4_object_base'](C.byref(api),e,values,SCRATCH)
            if e in reg.ENTRIES:return fns['dw4_reflection_registration'](C.byref(api),e,values,SCRATCH+0x100)
            for entries,name in ((LIST_ENTRIES,'dw4_internal_object_list'),(FIELD_ENTRIES,'dw4_field_factory'),(META_ENTRIES,'dw4_metadata_bootstrap'),(STORAGE_ENTRIES,'dw4_object_storage'),(CREATION_ENTRIES,'dw4_object_creation')):
                if e in entries:return fns[name](C.byref(api),e,values)
            return native.call(e,list(values[:8]))&MASK
        def setup():
            nonlocal retail
            retail=Services(image)
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            expected=retail.invoke(entry,*values);actual=invoke_native(entry,(C.c_uint64*12)(*[x&MASK for x in values]))
            assert not errors,errors
            if entry in RETURNS:assert expected==actual,(hex(entry),expected,actual)
            def ram(w):return {p:v for p,v in w.mem.items() if not STACK-0x5000<=p<STACK+40 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry);executed.update(retail.covered);return actual
        for data,count,capacity in itertools.product((0,BUFFER),(0,3),(0,4)):
            setup();retail.w(CBLIST,4,data);retail.w(CBLIST+4,4,count);retail.w(CBLIST+8,4,capacity);compare(0x2d3400,CBLIST)
            assert all(retail.read(CBLIST+i,4)==0 for i in (0,4,8))
        for pointer,data,flag in itertools.product((0,CBLIST),(0,BUFFER),(0,1,0xffff,0x8000,0x10001,0x7fff)):
            setup();retail.w(CBLIST,4,data);compare(0x2d3420,pointer,flag)
            assert (BUFFER in retail.freed)==bool(pointer and data)
            assert (CBLIST in retail.freed)==bool(pointer and 0<(flag&0xffff)<0x8000)
        for capacity in (0,1,2,3,4,24):
            for count in sorted({0,max(0,capacity-1),capacity,capacity+1}):
                setup();retail.w(CBLIST+4,4,count);retail.w(CBLIST+8,4,capacity)
                if not capacity and not count:retail.w(CBLIST,4,0)
                compare(0x2d3480,CBLIST,CALLBACK)
                assert retail.read(CBLIST+4,4)==count+1
                assert retail.read(retail.read(CBLIST,4)+count*4,4)==CALLBACK
                if count==capacity:assert retail.read(CBLIST+8,4)==(4 if not capacity else capacity*(3*capacity//2))
        for capacity in (0x40000000,0x80000000):
            setup();retail.w(CBLIST+4,4,capacity);retail.w(CBLIST+8,4,capacity);compare(0x2d3480,CBLIST,CALLBACK)
            assert retail.read(CBLIST+8,4)==0
        setup();retail.w(CBLIST+4,4,4);retail.mutate_count=True;compare(0x2d3480,CBLIST,CALLBACK)
        assert retail.read(CBLIST+4,4)==3
        # Original dispatcher captures count while re-reading the current buffer.
        for mutate in (False,True):
            setup();compare(0x2d3400,CBLIST)
            for p in (CALLBACK,CALLBACK2,CALLBACK):compare(0x2d3480,CBLIST,p)
            for i in range(3):retail.w(ALT+i*4,4,CALLBACK2)
            retail.mutate_iteration=mutate;compare(0x2fe940,REGISTRAR)
            called=[event[0] for event in retail.events if event[0] in (CALLBACK,CALLBACK2)]
            assert called==([CALLBACK,CALLBACK2,CALLBACK2] if mutate else [CALLBACK,CALLBACK2,CALLBACK])
            assert CBLIST in retail.freed
        # Real root metadata supplies real object pointers and string fields.
        setup();compare(0x2ff4e0)
        for name,found in ((0x4faf40,True),(0x4faf50,True),(QUERY+0x100,False)):
            if not found:retail.text(name,b'not-a-field')
            result=compare(0x2fdf20,BASE,name);assert bool(result)==found
            compare(0x2ea780,retail.read(BASE+40,4),SELECTOR,name)
        # Replace an inherited descriptor while its parent retains the original.
        compare(0x3581f0);compare(0x2b6d20,0x18f2000)
        field=FIELD+8*0x100;old=retail.read(retail.read(retail.read(META+40,4)+8,4),4)
        assert retail.read(old+4,4)==2
        compare(0x2fdea0,META,0,field)
        assert retail.read(old+4,4)==1 and retail.read(field+4,4)==2
        assert retail.read(retail.read(retail.read(META+40,4)+8,4),4)==field
        # Work's actual dependency addresses are dispatched; their class bodies stay leaves here.
        setup();compare(0x2ff4e0);compare(0x3581d0)
        invoked=[event for event in retail.events if event[0] in DEPS]
        assert [event[0] for event in invoked]==[0x2cab90,0x36a180]
        assert len(invoked)==2 and CBLIST in retail.freed
        assert ENTRIES<=hits,ENTRIES-hits
    print(f'metadata callback services retail: {cases} RAM/defined-return/ordered-call checkpoints; all6 bodies, actual root metadata lookup/replacement and dispatcher/Work dependency array; child callback bodies and allocation/type/interner leaves controlled')
if __name__=='__main__':main()
