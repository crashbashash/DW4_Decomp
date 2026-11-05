#!/usr/bin/env python3
"""Original igObject bootstrap and its inherited header descriptors vs retail."""
import ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
import test_reflection_registration_retail as reg
from test_reflection_registration_retail import Registration,ROOT,Api,READ,WRITE,CALL,MASK,STACK,META,BASE,FIELDS,BASEFIELDS,FIELD,SYSTEM,TYPE,ALLOCATE_DESCRIPTOR
from test_field_factories_retail import ENTRIES as FIELD_ENTRIES
from test_metadata_bootstrap_retail import ENTRIES as META_ENTRIES
from test_internal_object_lists_retail import ENTRIES as LIST_ENTRIES
from test_object_storage_retail import ENTRIES as STORAGE_ENTRIES
from test_object_creation_retail import ENTRIES as CREATION_ENTRIES
ENTRIES={0x2ff460,0x2ff4a0,0x2ff4b0,0x2ff4e0,0x2ff4f0,0x2ff560,0x135530,0x155b80,0x2ff570,0x2fde60}
RETURNS=ENTRIES-{0x2ff4e0,0x2ff570,0x2fde60}
SCRATCH=STACK-0x3800
class ObjectBase(Registration):
    def __init__(self,image):
        super().__init__(image);self.descend|=ENTRIES|set(FIELD_ENTRIES)|set(CREATION_ENTRIES)
        self.metadata_allocations=0;self.list_calls=0
        self.w(0x587198,4,0);self.w(0x588f88,4,0);self.w(SYSTEM+916,4,0)
        for slot in (92,100,108):self.descriptor_services[self.read(0x533430+slot,4)]=slot
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==ALLOCATE_DESCRIPTOR and v[1]==100:
            self.events.append((e,*v[:2]));p=(BASE,META)[self.metadata_allocations];self.metadata_allocations+=1;return p
        if e==ALLOCATE_DESCRIPTOR and v[1]==16:
            self.events.append((e,*v[:2]));n=self.list_calls;self.list_calls+=1
            return (BASEFIELDS,FIELDS)[n//2] if n%2==0 else self.list_buffer(16)
        if e==0x2d3420:self.events.append((e,*v[:2]));return 0
        return super().call(e,args)

def main():
    reg.STORAGE=reg.FACTORIES=reg.METADATA=reg.INTERNAL=True
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();retail=ObjectBase(image);native=ObjectBase(image);errors=[];cases=0;hits=set();executed=set()
    @CALL
    def call(_,e,values):
        try:return invoke_native(e,values)
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-object-base-') as td:
        so=Path(td)/'base.so'
        sources=('object-base.c','reflection-registration.c','field-factories.c','metadata-bootstrap.c','internal-object-lists.c','object-storage.c','object-creation.c')
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in sources],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));fns={name:getattr(lib,name) for name in ('dw4_object_base','dw4_reflection_registration','dw4_field_factory','dw4_metadata_bootstrap','dw4_internal_object_list','dw4_object_storage','dw4_object_creation')}
        for name,f in fns.items():
            f.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)]+([C.c_uint32] if name in ('dw4_object_base','dw4_reflection_registration') else []);f.restype=C.c_uint64
        def invoke_native(e,values):
            if e in ENTRIES:return fns['dw4_object_base'](C.byref(api),e,values,SCRATCH)
            if e in reg.ENTRIES:return fns['dw4_reflection_registration'](C.byref(api),e,values,SCRATCH+0x100)
            for entries,name in ((LIST_ENTRIES,'dw4_internal_object_list'),(FIELD_ENTRIES,'dw4_field_factory'),(META_ENTRIES,'dw4_metadata_bootstrap'),(STORAGE_ENTRIES,'dw4_object_storage'),(CREATION_ENTRIES,'dw4_object_creation')):
                if e in entries:return fns[name](C.byref(api),e,values)
            return native.call(e,list(values[:8]))&MASK
        def setup():
            nonlocal retail
            retail=ObjectBase(image)
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            native.w(SCRATCH+20,4,retail.read(STACK-4,4))
            expected=retail.invoke(entry,*values);actual=invoke_native(entry,(C.c_uint64*12)(*[x&MASK for x in values]))
            assert not errors,errors
            if entry in RETURNS:assert expected==actual,(hex(entry),expected,actual)
            def ram(w):return {p:v for p,v in w.mem.items() if not STACK-0x5000<=p<STACK+40 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry);executed.update(retail.covered);return actual
        for entry,handle in itertools.product((0x135530,0x155b80,0x2ff560),(0,BASE,META)):
            setup();retail.w(0x587198,4,handle);assert compare(entry)==handle
        setup();assert compare(0x2ff4a0)==0
        for available in (False,True):
            setup();retail.callback_allocation=available;compare(0x2ff460)
        for offset,flags in itertools.product((0,4),(0,0x80800000,0xffffffff)):
            setup();retail.w(SYSTEM+916,4,offset);retail.w(STACK-4,4,flags);compare(0x2ff4b0)
        # Full cold registration, then repeated registration without new fields.
        for entry,available in itertools.product((0x2ff4f0,0x2ff4e0),(False,True)):
            setup();retail.callback_allocation=available;compare(entry);assert retail.read(0x587198,4)==BASE
            assert retail.read(BASEFIELDS+12,4)==2 and retail.read(BASE+36,4)==7
            assert retail.read(BASE+72,4)==8 and retail.read(BASE+92,4)==0x52f0f0
            for i in range(2):
                p=retail.read(retail.read(BASEFIELDS+8,4)+i*4,4)
                assert retail.read(p,4)==0x533430 and retail.read(p+4,4)==1
                assert retail.read(p+8,4)==4 and retail.read(p+36,1)==3 and retail.read(p+38,1)==0
                assert retail.string(retail.read(p+12,4))==retail.string(0x4faf40+i*16)
                assert retail.read(0x5871a0+i*8,4)==p and retail.read(p+24,4)==BASE
            created=retail.created;compare(entry);assert retail.created==created==2
        setup();compare(0x2ff4f0);compare(0x2ff570)
        assert retail.read(BASEFIELDS+12,4)==4
        # The append/finalize helper is independently entered with a real fresh descriptor.
        setup();compare(0x2ff4f0);compare(0x2b6d20,0x18f2000);compare(0x2fde60,BASE,FIELD+0x200)
        assert retail.read(BASEFIELDS+12,4)==3
        # Actual Work registration inherits the two generated header descriptors.
        setup();compare(0x2ff4e0);compare(0x3581f0)
        assert retail.read(META+56,4)==BASE and retail.read(FIELDS+12,4)==8
        assert retail.read(META+12,4)==1 and retail.read(BASE+12,4)==0
        assert retail.read(META+4,4)==retail.read(BASE+4,4)==1
        for i in range(2):
            b=retail.read(retail.read(BASEFIELDS+8,4)+i*4,4)
            assert retail.read(retail.read(FIELDS+8,4)+i*4,4)==b and retail.read(b+4,4)==2
        assert retail.read(META+72,4)==32 and retail.created==8
        for i,offset in enumerate((8,12,16,20,24,28),2):
            p=retail.read(retail.read(FIELDS+8,4)+i*4,4)
            assert retail.read(p+8,4)==offset and retail.read(p+18,2)==i and retail.read(p+4,4)==1
        assert ENTRIES<=hits,(ENTRIES-hits)
        assert {0x2b6d20,0x30e8e0,0x30e920}<=executed
    print(f'object base retail: {cases} RAM/defined-return/ordered-call checkpoints; all10 bootstrap bodies and actual unsigned descriptor chain; original base/Work registration with two inherited header fields; allocator/type/interner/callback-vector leaves controlled')
if __name__=='__main__':main()
