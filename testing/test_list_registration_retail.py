#!/usr/bin/env python3
"""Actual inherited list schemas and Work's deferred child registration vs retail."""
import ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
import test_reflection_registration_retail as reg
from test_object_base_retail import ObjectBase,ENTRIES as BASE_ENTRIES,SCRATCH
from test_reflection_registration_retail import ROOT,Api,READ,WRITE,CALL,MASK,STACK,SYSTEM,TYPE,ALLOCATE_DESCRIPTOR,ALLOCATE_STORAGE,FREE_STORAGE,REALLOCATE_LIST
from test_field_factories_retail import ENTRIES as FIELD_ENTRIES
from test_list_descriptor_copy_retail import ENTRIES as COPY_ENTRIES
from test_metadata_callback_services_retail import ENTRIES as SERVICES,SELECTOR
from test_metadata_bootstrap_retail import ENTRIES as META_ENTRIES
from test_internal_object_lists_retail import ENTRIES as LIST_ENTRIES
from test_object_storage_retail import ENTRIES as STORAGE_ENTRIES
from test_object_creation_retail import ENTRIES as CREATION_ENTRIES
HANDLES=(0x586788,0x585b60,0x586880,0x589d20)
ALLOCATE=(0x2c8490,0x2bd6c0,0x2caab0,0x36a0a0)
READY=(0x2c84e0,0x2bd710,0x2cab00,0x36a0f0)
TABLES=(0x2c8530,0x2bd760,0x2cab50,0x36a140)
GUARDS=(0x2c8570,0x2bd7a0,0x2cab90,0x36a180)
REGISTERS=(0x2c8580,0x2bd7b0,0x2caba0,0x36a1a0)
ACCESSORS=(0x2c85f0,0x2bd820,0x2cac10,0x36a210)
INITIALIZERS=(0x2c8600,0x2bd830,0x2cac20)
PROVIDERS=(0x2b7660,0x2bd2e0,0x2c3090)
PROVIDER_SLOTS=(0x585768,0x585b28,0x586100)
PROVIDER_GUARDS=(0x2b7500,0x2bd0c0,0x2c2f30)
ENTRIES=set(ALLOCATE+READY+TABLES+GUARDS+REGISTERS+ACCESSORS+INITIALIZERS+PROVIDERS+(0x143720,0x130c00))
RETURNS=set(ALLOCATE+READY+TABLES+REGISTERS+ACCESSORS+PROVIDERS+(0x143720,0x130c00))
class Registration(ObjectBase):
    def __init__(self,image):
        super().__init__(image);self.descend|=ENTRIES|COPY_ENTRIES|SERVICES|{0x300d70,0x300d30};self.descend.discard(0x2fda40)
        self.heap=0x1a00000;self.allocated={};self.freed=set();self.scalar=[]
        for slot in (0x587198,0x588f88,*HANDLES):self.w(slot,4,0)
        self.w(SYSTEM+52,4,0x18f2000);self.w(0x585cd8,4,SELECTOR);self.w(SELECTOR+8,4,12)
        self.vt_kind={}
        for vt in (0x52e530,0x532670,0x532c80,0x533430,0x533180,0x532a50):
            for slot in (92,100,108):self.vt_kind[self.read(vt+slot,4)]=(slot,vt)
        # Type-system publication remains a boundary: real-shape scalar field selectors.
        for pub,vt,size in zip(PROVIDER_SLOTS,(0x52e530,0x532c80,0x532670),(1,4,4)):
            p=self.allocate(80,True);self.w(p,4,vt);self.w(p+4,4,1);self.w(p+16,2,0xffff);self.w(p+20,2,size)
            self.w(p+32,4,self.allocate(size,True));self.w(p+38,1,1)
            if vt==0x532c80:self.w(p+60,1,1)
            self.scalar.append(p);self.w(pub,4,p)
    def allocate(self,size,zero=False):
        assert size<=65536,size
        p=self.heap;self.heap+=max(0x100,(size+0xff)&~0xff);self.allocated[p]=size;self.list_bytes[p]=size
        for i in range(size):self.w(p+i,1,0 if zero else 0xa5)
        return p
    def fields(self,meta):
        table=self.read(meta+40,4);return [self.read(self.read(table+8,4)+i*4,4) for i in range(self.read(table+12,4))]
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e in self.vt_kind:
            slot,vt=self.vt_kind[e];self.events.append((e,v[0]))
            return TYPE if slot==92 else (1 if vt==0x52e530 else 4)
        if e in PROVIDER_GUARDS:
            self.events.append((e,));i=PROVIDER_GUARDS.index(e);self.w(PROVIDER_SLOTS[i],4,self.scalar[i]);return 0
        if e==0x2b5d50:self.events.append((e,));return 0
        if e==0x36a360:self.events.append((e,v[0]));return 0
        if e==ALLOCATE_DESCRIPTOR:self.events.append((e,*v[:2]));return self.allocate(v[1])
        if e==ALLOCATE_STORAGE:self.events.append((e,*v[:3]));return self.allocate(v[1],bool(v[2]))
        if e in (REALLOCATE_LIST,0x2ed330):
            n=3 if e==REALLOCATE_LIST else 2;self.events.append((e,*v[:n]));old,size=(v[1],v[2]) if n==3 else (v[0],v[1]);p=self.allocate(size)
            if old:
                for i in range(min(self.allocated.get(old,self.list_bytes.get(old,0)),size)):self.w(p+i,1,self.read(old+i,1))
                self.freed.add(old)
            return p
        if e==0x2ed240:self.events.append((e,*v[:2]));return self.allocate(v[0])
        if e in (0x2ed460,0x2ed5c0,FREE_STORAGE):
            self.events.append((e,*v[:2 if e==FREE_STORAGE else 1]));self.freed.add(v[1] if e==FREE_STORAGE else v[0]);return 0
        if e==0x2ed4e0:self.events.append((e,v[0]));return self.allocated.get(v[0],self.list_bytes[v[0]])
        if e==0x2c29c0:
            self.events.append((e,v[0]));p=self.allocate(16,True);self.w(p,4,0x532770);self.w(p+4,4,1);self.w(p+8,4,self.allocate(16));return p
        if e==0x12a4a4:self.events.append((e,*v[:2]));return int(self.string(v[0])!=self.string(v[1]))
        return super().call(e,args)

def main():
    reg.STORAGE=reg.FACTORIES=reg.METADATA=reg.INTERNAL=True
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();retail=Registration(image);native=Registration(image);errors=[];cases=0;hits=set();coverage=set()
    @CALL
    def call(_,e,values):
        try:return invoke_native(e,values)
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-list-reg-') as td:
        so=Path(td)/'registration.so';sources=('list-registration.c','list-descriptor-copy.c','metadata-callback-services.c','object-base.c','reflection-registration.c','field-factories.c','metadata-bootstrap.c','internal-object-lists.c','object-storage.c','object-creation.c')
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in sources],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));names=('dw4_list_registration','dw4_list_descriptor_copy','dw4_metadata_callback_service','dw4_object_base','dw4_reflection_registration','dw4_field_factory','dw4_metadata_bootstrap','dw4_internal_object_list','dw4_object_storage','dw4_object_creation')
        fns={name:getattr(lib,name) for name in names}
        for name,f in fns.items():f.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)]+([C.c_uint32] if name in ('dw4_list_registration','dw4_object_base','dw4_reflection_registration') else []);f.restype=C.c_uint64
        def invoke_native(e,values):
            if e in ENTRIES:return fns['dw4_list_registration'](C.byref(api),e,values,SCRATCH-0x400)
            if e in COPY_ENTRIES:return fns['dw4_list_descriptor_copy'](C.byref(api),e,values)
            if e in SERVICES:return fns['dw4_metadata_callback_service'](C.byref(api),e,values)
            if e in BASE_ENTRIES:return fns['dw4_object_base'](C.byref(api),e,values,SCRATCH)
            if e in reg.ENTRIES:return fns['dw4_reflection_registration'](C.byref(api),e,values,SCRATCH+0x100)
            for entries,name in ((LIST_ENTRIES,'dw4_internal_object_list'),(FIELD_ENTRIES,'dw4_field_factory'),(META_ENTRIES,'dw4_metadata_bootstrap'),(STORAGE_ENTRIES,'dw4_object_storage'),(CREATION_ENTRIES,'dw4_object_creation')):
                if e in entries:return fns[name](C.byref(api),e,values)
            return native.call(e,list(values[:8]))&MASK
        def setup():
            nonlocal retail
            retail=Registration(image)
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
            cases+=1;hits.add(entry);coverage.update(retail.covered);return actual
        for i in range(4):
            setup();meta=compare(ALLOCATE[i]);assert retail.read(HANDLES[i],4)==meta and retail.read(meta+36,4)==0
            before=retail.heap;compare(ALLOCATE[i]);assert retail.heap==before
            setup();meta=compare(READY[i]);assert retail.read(meta+36,4)==7
            before=retail.heap;compare(READY[i]);assert retail.heap==before
            setup();compare(GUARDS[i]);compare(REGISTERS[i]);compare(ACCESSORS[i])
            for offset in (0,4):setup();retail.w(SYSTEM+916,4,offset);compare(TABLES[i])
        for e,slot,expected in ((0x143720,0x586788,0),(0x130c00,0x585b60,0)):
            setup();assert compare(e)==expected;retail.w(slot,4,0x19f0000);assert compare(e)==0x19f0000
        for e,pub,pointer in zip(PROVIDERS,PROVIDER_SLOTS,range(3)):
            for present in (False,True):
                setup();retail.w(pub,4,retail.scalar[pointer] if present else 0);assert compare(e)==retail.scalar[pointer]
        # Full original Work callback dispatch builds all four list metadata schemas.
        setup();compare(0x3581d0)
        root=retail.read(0x587198,4);work=retail.read(0x588f88,4);data,obj,integer,ram=(retail.read(h,4) for h in HANDLES)
        assert all(retail.read(p+36,4)==7 for p in (root,work,data,obj,integer,ram))
        assert len(retail.fields(root))==2 and len(retail.fields(work))==8
        assert all(len(retail.fields(p))==5 and retail.read(p+72,4)==20 for p in (data,obj,integer,ram))
        expected=('_count','_capacity','_data')
        for meta in (data,obj,integer,ram):
            fields=retail.fields(meta)
            assert tuple(retail.string(retail.read(p+12,4)).decode() for p in fields[2:])==expected
            assert tuple(retail.read(p+8,4) for p in fields[2:])==(8,12,16)
        raw,object_data,int_data,ram_data=(retail.fields(p)[4] for p in (data,obj,integer,ram))
        assert len({raw,object_data,int_data})==3 and ram_data==object_data
        assert [retail.read(p+60,4) for p in (raw,object_data,int_data)]==[retail.scalar[0],retail.scalar[1],retail.scalar[2]]
        assert [retail.read(p+4,4) for p in (raw,object_data,int_data)]==[1,2,1]
        assert len({retail.read(p+32,4) for p in (raw,object_data,int_data)})==3
        assert retail.read(retail.read(raw+12,4)-4,4)==3
        assert retail.read(0x585b68,4)==object_data and retail.read(0x586888,4)==int_data
        assert retail.read(retail.fields(work)[6]+56,4)==integer and retail.read(retail.fields(work)[7]+56,4)==ram
        before=retail.heap;compare(0x3581d0);assert retail.heap==before
        assert ENTRIES<=hits|coverage,ENTRIES-(hits|coverage)
    print(f'list registration retail: {cases} RAM/defined-return/ordered-call checkpoints; all32 bodies; actual Work deferred registrations, inherited schemas and cloned data descriptors; scalar publication/type/system services controlled')
if __name__=='__main__':main()
