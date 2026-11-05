#!/usr/bin/env python3
"""Memory-descriptor copy chain and original list-specialization callbacks."""
import ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
from test_metadata_callback_services_retail import Services,ENTRIES as SERVICES,SELECTOR,QUERY
import test_reflection_registration_retail as reg
from test_reflection_registration_retail import ROOT,Api,READ,WRITE,CALL,MASK,STACK,BASE,SYSTEM,ALLOCATE_DESCRIPTOR
from test_object_base_retail import ENTRIES as BASE_ENTRIES,SCRATCH
from test_field_factories_retail import ENTRIES as FIELD_ENTRIES
from test_metadata_bootstrap_retail import ENTRIES as META_ENTRIES
from test_internal_object_lists_retail import ENTRIES as LIST_ENTRIES
from test_object_storage_retail import ENTRIES as STORAGE_ENTRIES
from test_object_creation_retail import ENTRIES as CREATION_ENTRIES
ENTRIES={0x2bf2e0,0x2fb8e0,0x2fb930,0x2fc0e0,0x305c70,0x2fb9a0,0x2ff800,0x2bf380,0x300c60,0x2bd830,0x2cac20}
VOID={0x2bd830,0x2cac20}
SOURCE,DEST,TOKEN,DEFAULT,ALTDEFAULT,METAINFO,CHILD,LIST,DATA,ELEMENT1,ELEMENT2,PUBOLD,ALTVT,ALTGET=range(0x19b0000,0x19be000,0x1000)
class Copies(Services):
    def __init__(self,image):
        super().__init__(image);self.descend|=ENTRIES|{0x300d70,0x300d30};self.descend.discard(0x2fda40)
        self.copy_objects=0;self.fail_clone=False;self.mutate_default=False;self.switch_getter=False;self.change_handle=False
        self.w(0x587198,4,BASE);self.w(BASE+32,4,0)
        self.w(0x585b60,4,CHILD);self.w(0x586880,4,CHILD);self.w(CHILD+40,4,LIST)
        self.vector(LIST,[SOURCE]);self.w(LIST,4,0x5327d0)
        for p in range(SOURCE,SOURCE+80):self.w(p,1,0xa5)
        for p in range(DEST,DEST+80):self.w(p,1,0x5a)
        self.w(SOURCE,4,0x532a50);self.w(SOURCE+4,4,2);self.w(SOURCE+8,4,16);self.w(SOURCE+12,4,TOKEN)
        self.w(SOURCE+16,2,0xfffe);self.w(SOURCE+18,2,7);self.w(SOURCE+20,2,4);self.w(SOURCE+24,4,BASE)
        self.w(SOURCE+28,4,PUBOLD);self.w(PUBOLD,4,SOURCE);self.w(SOURCE+32,4,DEFAULT)
        for offset,value in ((36,3),(37,0),(38,1),(39,2),(40,1),(41,0),(42,0),(43,1),(44,2),(52,1),(53,1),(64,1),(65,1),(66,1)):self.w(SOURCE+offset,1,value)
        self.w(SOURCE+48,4,0x19bf000);self.w(SOURCE+56,4,31);self.w(SOURCE+60,4,ELEMENT1)
        self.w(SOURCE+68,4,0xffffffff);self.w(SOURCE+72,4,0x19bf100);self.w(SOURCE+76,4,0x19bf200)
        self.text(TOKEN,b'_data');self.w(TOKEN-4,4,1);self.w(TOKEN-8,4,0x19bf300)
        self.w(DEFAULT,4,0x11223344);self.w(ALTDEFAULT,4,0xaabbccdd)
        self.list_bytes[DEFAULT]=4;self.list_bytes[ALTDEFAULT]=4
        self.get_meta=self.read(0x532a50+88,4)
        for slot in (92,100,108):self.descriptor_services[self.read(0x532a50+slot,4)]=slot
        self.w(ALTVT+88,4,ALTGET)
    def new_descriptor(self):
        p=0x1e00000+self.copy_objects*0x100;self.copy_objects+=1
        for i in range(80):self.w(p+i,1,0xa5)
        return p
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==ALLOCATE_DESCRIPTOR and v[1]==80:
            self.events.append((e,*v[:2]));return 0 if self.fail_clone else self.new_descriptor()
        if e==ALLOCATE_DESCRIPTOR and self.mutate_default:
            self.mutate_default=False;self.events.append((e,*v[:2]));p=self.list_buffer(max(v[1],8))
            self.w(DEST+20,2,2);self.w(SOURCE+32,4,ALTDEFAULT);return p
        if e in (0x2bd2e0,0x2c3090):
            self.events.append((e,))
            if self.change_handle:self.w(0x585b60 if e==0x2bd2e0 else 0x586880,4,CHILD+0x100)
            return ELEMENT1 if e==0x2bd2e0 else ELEMENT2
        if e==0x2bf680:
            self.events.append((e,))
            if self.switch_getter:self.w(SOURCE,4,ALTVT)
            return 0
        if e in (self.get_meta,ALTGET):self.events.append((e,v[0]));return METAINFO if e==self.get_meta else METAINFO+0x100
        if e==0x2f04f0:self.events.append((e,v[0]));return 0
        if e==0x2f0670:self.events.append((e,v[0]));return 0
        if e==0x2fda40:
            self.events.append((e,*v[:2]));p=self.new_descriptor();self.w(p,4,0x532a50);self.w(p+4,4,1);return p
        if e==0x300c00:self.events.append((e,*v[:3]));self.w(v[0]+56,4,v[2]);return 0
        return super().call(e,args)

def main():
    reg.STORAGE=reg.FACTORIES=reg.METADATA=reg.INTERNAL=True
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();retail=Copies(image);native=Copies(image);errors=[];cases=0;hits=set();coverage=set()
    @CALL
    def call(_,e,values):
        try:return invoke_native(e,values)
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-list-copy-') as td:
        so=Path(td)/'copy.so'
        sources=('list-descriptor-copy.c','metadata-callback-services.c','object-base.c','reflection-registration.c','field-factories.c','metadata-bootstrap.c','internal-object-lists.c','object-storage.c','object-creation.c')
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in sources],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));names=('dw4_list_descriptor_copy','dw4_metadata_callback_service','dw4_object_base','dw4_reflection_registration','dw4_field_factory','dw4_metadata_bootstrap','dw4_internal_object_list','dw4_object_storage','dw4_object_creation')
        fns={name:getattr(lib,name) for name in names}
        for name,f in fns.items():f.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)]+([C.c_uint32] if name in ('dw4_object_base','dw4_reflection_registration') else []);f.restype=C.c_uint64
        def invoke_native(e,values):
            if e in ENTRIES:return fns['dw4_list_descriptor_copy'](C.byref(api),e,values)
            if e==0x2fda40:return native.call(e,list(values[:8]))&MASK
            if e in SERVICES:return fns['dw4_metadata_callback_service'](C.byref(api),e,values)
            if e in BASE_ENTRIES:return fns['dw4_object_base'](C.byref(api),e,values,SCRATCH)
            if e in reg.ENTRIES:return fns['dw4_reflection_registration'](C.byref(api),e,values,SCRATCH+0x100)
            for entries,name in ((LIST_ENTRIES,'dw4_internal_object_list'),(FIELD_ENTRIES,'dw4_field_factory'),(META_ENTRIES,'dw4_metadata_bootstrap'),(STORAGE_ENTRIES,'dw4_object_storage'),(CREATION_ENTRIES,'dw4_object_creation')):
                if e in entries:return fns[name](C.byref(api),e,values)
            return native.call(e,list(values[:8]))&MASK
        def setup():
            nonlocal retail
            retail=Copies(image)
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            expected=retail.invoke(entry,*values);actual=invoke_native(entry,(C.c_uint64*12)(*[x&MASK for x in values]))
            assert not errors,errors
            if entry not in VOID:assert expected==actual,(hex(entry),expected,actual)
            def ram(w):return {p:v for p,v in w.mem.items() if not STACK-0x5000<=p<STACK+40 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry);coverage.update(retail.covered);return actual
        for entry,active,size,alias,token in itertools.product((0x2fc0e0,0x305c70,0x2fb9a0),(0,1),(0,4,8),(False,True),(0,TOKEN)):
            setup();retail.w(SYSTEM,1,active);retail.w(SOURCE+20,2,size);retail.list_bytes[DEFAULT]=max(4,size);retail.w(DEFAULT+4,4,0x55667788);retail.w(SOURCE+12,4,token)
            compare(entry,SOURCE if alias else DEST,SOURCE)
            if not alias and token:assert retail.read(TOKEN-4,4)==2
        for entry in (0x2fb8e0,0x2fb930):setup();compare(entry,DEST,1)
        setup();compare(0x2bf2e0,0x18f2000)
        for active,flag,change in itertools.product((0,1),(0,1,3),(False,True)):
            setup();retail.w(SYSTEM,1,active);retail.switch_getter=change;result=compare(0x2bf380,SOURCE,flag)
            if active:assert retail.read(result+56,4)==flag
            else:
                assert retail.read(result+4,4)==1 and retail.read(result+12,4)==TOKEN and retail.read(TOKEN-4,4)==2
                assert retail.read(result+32,4)!=DEFAULT and retail.read(retail.read(result+32,4),4)==0x11223344
                assert retail.read(result+72,4)==retail.read(result+76,4)==0
        setup();retail.fail_clone=True;assert compare(0x2bf380,SOURCE,1)==0
        setup();compare(0x2ff800,80,0)
        setup();compare(0x300c60,SOURCE,2)
        setup();retail.mutate_default=True;compare(0x2fc0e0,DEST,SOURCE)
        assert retail.read(DEST+20,2)==2 and retail.read(retail.read(DEST+32,4),2)==0xccdd
        for (entry,target,pub),change in itertools.product(((0x2bd830,ELEMENT1,0x585b68),(0x2cac20,ELEMENT2,0x586888)),(False,True)):
            setup();retail.change_handle=change;compare(entry)
            field=retail.read(retail.read(LIST+8,4),4)
            assert field!=SOURCE and retail.read(field,4)==0x532a50
            assert retail.read(SOURCE+4,4)==retail.read(field+4,4)==1
            assert retail.read(TOKEN-4,4)==2 and retail.read(field+12,4)==TOKEN
            assert retail.read(field+60,4)==target and retail.read(field+56,4)==0
            assert retail.read(field+28,4)==pub and retail.read(pub,4)==field and retail.read(PUBOLD,4)==SOURCE
            assert retail.read(field+32,4)!=DEFAULT and retail.read(retail.read(field+32,4),4)==0x11223344
        assert ENTRIES<=hits,ENTRIES-hits
    print(f'list descriptor copy retail: {cases} RAM/defined-return/ordered-call cases; all11 bodies; original copy chain, lookup, retaining replacement and publication; scalar providers and runtime clone contents controlled')
if __name__=='__main__':main()
