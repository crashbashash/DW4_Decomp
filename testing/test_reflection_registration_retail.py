#!/usr/bin/env python3
"""Metadata registration/field builders vs original EE RAM and service order.

Original Work registrar/field tables execute; object/field factories, allocator,
interner, callback-vector and system services remain controlled primitives.
"""
import argparse,ctypes as C,itertools,json,subprocess,tempfile
from pathlib import Path
from test_messenger_dispatch_retail import World,ROOT,Api,READ,WRITE,CALL,MASK,STACK
ENTRIES=(0x2ead30,0x2fde50,0x2fdc50,0x2fdf40,0x2fc490,0x2fc2c0,0x2fc3b0,0x2fc440,0x2fc630,0x2fe000,0x2fe0d0,0x2fe9c0,0x358290,0x3581f0)
PURE={0x2fe470,0x2fdf00};TAILS={0x2ead44}
META,BASE,FIELDS,BASEFIELDS,FIELD,FVT,SYSTEM,NAME,HANDLE,CBLIST,DEPS,NAMES,SLOTS,OFFSETS,CTORS,TYPE=range(0x1800000,0x1810000,0x1000)
ALIGN,GETTYPE,SIZE,SETDEFAULT=0x1810000,0x1810100,0x1810200,0x2fc440
BASEREG,BASEGET,GETVT,POST,SETUP,CTOR=0x1811000,0x1811100,0x1811200,0x1811300,0x1811400,0x1811500
CALLBACK2=0x1811600;CHILDREN=0x1812000
STORAGE=False
FACTORIES=False
METADATA=False
INTERNAL=False
INTERNAL_ENTRIES={0x2c2670,0x2ea4f0,0x2ea550,0x2ea590,0x2ea630,0x2ea690,0x2ea780,0x2ea820,0x2ea870,0x2ea8e0,0x2ea9a0,0x2eaa00,0x2eaa60,0x2eaaf0,0x2eab70,0x2eabb0,0x2eabf0,0x2eac30,0x2eac60,0x2eac80,0x2ead30,0x2ead50}
REALLOCATE_LIST=0x1821300
METADATA_ENTRIES={0x2be4f0,0x2fd7c0,0x2fd820,0x2fef70,0x2fd940,0x2fd980,0x2fddb0,0x2fe7a0,0x2ea820,0x2d3060}
METADATA_REGISTRY=0x1826000
FACTORY_ENTRIES={0x2b9750,0x2c2cf0,0x2bce90,0x2fef20,0x2ff010,0x2ff790,0x2fbf90,0x2fbfe0,0x305bf0,0x305c30,0x30b230,0x30b270,0x2ea3e0,0x2ea420,0x303bc0,0x303c10,0x30a820,0x303350}
ALLOCATE_DESCRIPTOR=0x1821200
STORAGE_ENTRIES={0x2f0700,0x301000,0x300e00,0x300f00}
ALLOCATE_STORAGE,FREE_STORAGE=0x1821000,0x1821100
WORK_CTORS={0x2b9750:0,0x2c2cf0:1,0x2bce90:2}
class Registration(World):
    def __init__(self,image):
        super().__init__(image);self.descend=set(ENTRIES)|PURE;self.events=[];self.created=0;self.memories=0;self.tokens_by_text={};self.list_bytes={};self.list_allocations=0;self.list_factory_allocated=False;self.list_freed=set()
        self.base_callbacks=CBLIST;self.callback_allocation=True;self.old_size=4;self.null_type=False;self.reenter=False;self.reentered=False
        self.w(0x587040,4,0x18f0000);self.w(0x586dc8,4,SYSTEM);self.w(0x586f20,4,0x18f1000)
        self.w(HANDLE,4,META);self.w(0x588f88,4,META)
        self.vector(FIELDS,[]);self.vector(BASEFIELDS,[])
        self.w(META+4,4,2);self.w(META+40,4,FIELDS);self.w(META+36,4,0);self.w(META+72,4,32)
        self.w(BASE+40,4,BASEFIELDS);self.w(BASE+52,4,0);self.w(BASE+92,4,0x52f010);self.w(BASE+88,2,4)
        self.w(BASE+32,4,0);self.w(BASE+72,4,8);self.w(TYPE+18,2,5)
        for slot,fn in ((92,GETTYPE),(100,SIZE),(108,ALIGN),(140,SETDEFAULT)):self.w(FVT+slot,4,fn)
        for i in range(8):
            p=FIELD+i*0x100;self.initialize_field(p)
            self.w(CTORS+i*4,4,CTOR);self.text(NAME+i*0x100,b'name'+str(i).encode())
            self.w(NAMES+i*4,4,NAME+i*0x100);self.w(SLOTS+i*4,4,0x18e0000+i*4);self.w(OFFSETS+i*4,4,8+i*4)
        self.w(DEPS,4,CALLBACK2);self.w(DEPS+4,4,SETUP);self.w(DEPS+8,4,0)
        if STORAGE:
            self.descend|=STORAGE_ENTRIES
            self.w(0x586f58,4,0x1822000);self.w(0x1822000,4,0x1823000);self.w(0x1823000,4,0x1824000)
            self.w(0x1824000,4,0x1825000);self.w(0x1825000+224,4,ALLOCATE_STORAGE);self.w(0x1825000+264,4,FREE_STORAGE)
        self.descriptor_services={}
        if FACTORIES:
            self.descend|=FACTORY_ENTRIES
            self.w(0x18f2000,4,0x1825000);self.w(0x1825000+216,4,ALLOCATE_DESCRIPTOR)
            for vt in (0x533180,0x532670,0x532c80):
                for slot in (92,100,108):self.descriptor_services[self.read(vt+slot,4)]=slot
        if METADATA:
            self.descend|=METADATA_ENTRIES
            self.w(SYSTEM+24,4,METADATA_REGISTRY);self.vector(METADATA_REGISTRY,[])
        if INTERNAL:
            self.descend|=INTERNAL_ENTRIES|{0x300e50};self.w(0x1825000+232,4,REALLOCATE_LIST)
        self.current_args=(0,HANDLE,BASEREG,BASEGET,0x1811700,NAME,32,GETVT,POST,0,0)
    def initialize_field(self,p):
        self.w(p,4,FVT);self.w(p+4,4,1);self.w(p+8,4,0);self.w(p+12,4,0);self.w(p+20,2,4)
        self.w(p+32,4,0);self.w(p+37,1,0);self.w(p+38,1,1)
    def list_buffer(self,size):
        p=0x1b00000+self.list_allocations*0x1000;self.list_allocations+=1;self.list_bytes[p]=size
        for i in range(size):self.w(p+i,1,0xa5)
        return p
    def vector(self,p,values):
        if INTERNAL:self.list_bytes[p+0x40000]=max(16,len(values)*4)
        self.w(p+8,4,p+0x40000);self.w(p+12,4,len(values))
        for i,value in enumerate(values):self.w(p+0x40000+i*4,4,value)
    def invoke(self,entry,*args):
        cov=self.covered;self.ee_reset();self.covered=cov
        self.r[4:12]=[v&MASK for v in args[:8]]+[0]*(8-len(args[:8]))
        self.r[28],self.r[29],self.r[31]=0x55c870,getattr(self,'stack',STACK),0xfffffff0
        for i,value in enumerate(args[8:]):self.w(self.r[29]+i*8,8,value)
        self.run_until(entry,0xfffffff0);return self.r[2]
    def step(self,pc,delay=False):
        if INTERNAL:return World.step(self,pc,delay)
        if pc in TAILS:
            target=(self.read(pc,4)&0x3ffffff)<<2;super().step(pc+4,True);self.call_hook(target);return self.r[31]&0xffffffff
        return super().step(pc,delay)
    def text(self,p,value):
        for i,b in enumerate(value+b'\0'):self.w(p+i,1,b)
    def string(self,p):
        data=[]
        while self.read(p,1):data.append(self.read(p,1));p+=1
        return bytes(data)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if FACTORIES and e in self.descriptor_services:
            self.events.append((e,v[0]));return TYPE if self.descriptor_services[e]==92 else 4
        if INTERNAL and e==REALLOCATE_LIST:
            self.events.append((e,*v[:3]));p=self.list_buffer(v[2])
            if v[1]:
                for i in range(min(self.list_bytes[v[1]],v[2])):self.w(p+i,1,self.read(v[1]+i,1))
                self.list_freed.add(v[1])
            return p
        if INTERNAL and e==0x12724c:
            self.events.append((e,*v[:3]))
            for i in range(v[2]):self.w(v[0]+i,1,v[1]&255)
            return v[0]
        if e==ALLOCATE_DESCRIPTOR:
            self.events.append((e,*v[:2]));
            if METADATA and v[1]==100:return META
            if INTERNAL and v[1]==16 and not self.list_factory_allocated:self.list_factory_allocated=True;return FIELDS
            if INTERNAL and v[1] not in (52,60,68):return self.list_buffer(v[1])
            p=FIELD+self.created*0x100;self.created+=1;return p
        if FACTORIES and e in (0x2ff0e0,0x2ff140):
            self.events.append((e,*v[:2 if e==0x2ff0e0 else 1]));return 0
        counts={0x2c2670:1,ALLOCATE_STORAGE:3,FREE_STORAGE:2,0x2f88e0:1,0x2be4f0:1,0x12a1e8:2,0x2ff820:1,0x2c29c0:1,0x2eaa60:2,
                0x2eb010:1,0x2eadf0:1,0x2eaf60:2,0x30c940:2,0x300e00:3,0x300f00:2,0x2ed4e0:1,
                0x127098:3,0x2fddb0:2,0x2fe7a0:1,0x30d350:2,0x2fe810:3,0x2ed240:2,
                0x2d3400:1,0x2d3480:2,0x2d3150:2,ALIGN:1,GETTYPE:1,SIZE:1,BASEREG:0,BASEGET:0,
                GETVT:0,POST:0,SETUP:1,CTOR:1,0x2caab0:0,0x36a0a0:0,0x33c8e0:0,
                0x2ff4f0:0,0x135530:0,0x358100:0}
        if e in WORK_CTORS:counts[e]=1
        assert e in counts,hex(e)
        self.events.append((e,*['temp' if STACK-0x5000<=p<STACK else p for p in v[:counts[e]]]))
        if e==0x2c2670:self.vector(FIELDS,[]);return FIELDS
        if e==0x2f88e0:return 0x18f2000
        if e==0x2be4f0:return META
        if e==0x12a1e8:self.text(v[0],self.string(v[0])+self.string(v[1]));return v[0]
        if e in (0x2ff820,0x30c940,0x300f00,FREE_STORAGE,0x2d3150,0x33c8e0):return 0
        if e==0x2c29c0:self.vector(CHILDREN,[]);return CHILDREN
        if e==0x2eaa60:
            n=self.read(v[0]+12,4);self.w(self.read(v[0]+8,4)+n*4,4,v[1]);self.w(v[0]+12,4,n+1);return 0
        if e in (CTOR,*WORK_CTORS):
            p=FIELD+self.created*0x100;self.created+=1;self.initialize_field(p);return p
        if e==ALIGN:return self.read(v[0]+0x80,4) or 4
        if e==GETTYPE:return 0 if self.null_type else TYPE
        if e==SIZE:return self.read(v[0]+0x84,4) or 4
        if e in (0x300e00,ALLOCATE_STORAGE):
            p=0x1a00000+self.memories*0x100;self.memories+=1
            for i in range(v[1]):self.w(p+i,1,0)
            return p
        if e==0x2ed4e0:return self.list_bytes[v[0]] if INTERNAL and v[0] in self.list_bytes else self.old_size
        if e==0x127098:
            data=bytes(self.read(v[1]+i,1) for i in range(v[2]))
            for i,b in enumerate(data):self.w(v[0]+i,1,b)
            return v[0]
        if e==0x2eb010:return 0x18f1000
        if e==0x2eadf0:return v[0]
        if e==0x2eaf60:
            if not v[1]:return 0
            text=self.string(v[1]);p=self.tokens_by_text.get(text)
            if p is None:
                p=0x1c00000+len(self.tokens_by_text)*0x100;self.tokens_by_text[text]=p;self.text(p,text);self.w(p-4,4,0);self.w(p-8,4,0x18f3000)
            self.w(p-4,4,self.read(p-4,4)+1);return p
        if e==0x2fddb0:self.w(v[0]+28,4,v[1]);return 0
        if e==0x2fe7a0:self.w(v[0]+18,2,7);return 0
        if e==0x30d350:return -1 if not getattr(self,'diagnostic_found',False) else 0
        if e==0x2fe810:self.w(v[0],4,1);return 0
        if e==0x2ed240:return CBLIST if self.callback_allocation else 0
        if e==0x2d3400:return v[0]
        if e==0x2d3480:return 0
        if e in (BASEREG,0x2ff4f0):return self.base_callbacks
        if e in (BASEGET,0x135530):return BASE
        if e in (GETVT,0x358100):return 0x536f10
        if e==POST:
            if self.reenter and not self.reentered:self.reentered=True;self.nested()
            return 0
        if e==SETUP:return 0
        if e==0x2caab0:return 0x18d0000
        if e==0x36a0a0:return 0x18d1000
        raise AssertionError(e)
    def nested(self):
        names=('r','f','acc','hi','lo','hi1','lo1','fcond');saved={k:getattr(self,k) for k in names};self.stack=STACK-0x2000
        try:assert self.invoke(0x2fe9c0,*self.current_args)==0
        finally:
            for k,value in saved.items():setattr(self,k,value)
            del self.stack

def main():
    global STORAGE,FACTORIES,METADATA,INTERNAL
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--object-storage',action='store_true');p.add_argument('--field-factories',action='store_true');p.add_argument('--metadata',action='store_true');p.add_argument('--internal-lists',action='store_true');p.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=p.parse_args();INTERNAL=args.internal_lists;METADATA=args.metadata or INTERNAL;FACTORIES=args.field_factories or METADATA;STORAGE=args.object_storage or FACTORIES
    image=args.elf.read_bytes();retail=Registration(image);native=Registration(image);errors=[];cases=0;hits=set();storage_hits=set();factory_hits=set();metadata_hits=set();internal_hits=set();depth=0
    @CALL
    def call(_,e,values):
        nonlocal depth
        try:
            if INTERNAL and e in INTERNAL_ENTRIES:return internal_fn(C.byref(api),e,values)
            if METADATA and e in METADATA_ENTRIES:return metadata_fn(C.byref(api),e,values)
            if FACTORIES and e in FACTORY_ENTRIES:return factory_fn(C.byref(api),e,values)
            if STORAGE and (e in STORAGE_ENTRIES or INTERNAL and e==0x300e50):return storage_fn(C.byref(api),e,values)
            if e in ENTRIES:
                depth+=1
                try:return fn(C.byref(api),e,values,STACK-0x1400-depth*0x200)
                finally:depth-=1
            return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-registration-') as td:
        so=Path(td)/'registration.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/reflection-registration.c'),str(ROOT/'recovered/engine/object-storage.c'),str(ROOT/'recovered/engine/field-factories.c'),str(ROOT/'recovered/engine/metadata-bootstrap.c'),str(ROOT/'recovered/engine/internal-object-lists.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));storage_fn=lib.dw4_object_storage;storage_fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];storage_fn.restype=C.c_uint64
        factory_fn=lib.dw4_field_factory;factory_fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];factory_fn.restype=C.c_uint64
        metadata_fn=lib.dw4_metadata_bootstrap;metadata_fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];metadata_fn.restype=C.c_uint64
        internal_fn=lib.dw4_internal_object_list;internal_fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];internal_fn.restype=C.c_uint64
        fn=lib.dw4_reflection_registration;fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        def nested_native():
            value=fn(C.byref(api),0x2fe9c0,(C.c_uint64*12)(*native.current_args),STACK-0x3000);assert value==0
        native.nested=nested_native
        def setup():
            nonlocal retail
            retail=Registration(image)
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image','nested'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[];expected=retail.invoke(entry,*values);storage_hits.update(retail.covered & STORAGE_ENTRIES);factory_hits.update(retail.covered & FACTORY_ENTRIES);metadata_hits.update(retail.covered & METADATA_ENTRIES);internal_hits.update(retail.covered & (INTERNAL_ENTRIES|{0x300e50}))
            actual=fn(C.byref(api),entry,(C.c_uint64*12)(*[x&MASK for x in values]),STACK-0x1400)
            assert not errors,errors
            if entry in (0x2fe9c0,0x3581f0):assert expected==actual,(hex(entry),expected,actual)
            def ram(world):return {p:v for p,v in world.mem.items() if not STACK-0x5000<=p<STACK+40 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:15])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry);return actual
        for count in (-1,0,1,3,6):setup();compare(0x2fdf40,META,CTORS,count)
        for flags,missing,abstract,base_owner,optional,deps,diagnostic in itertools.product((0,1,2,3,4,7,8),(False,True),(0,1),(0,CBLIST),(0,CALLBACK2),(0,DEPS),(False,True)):
            setup();retail.w(META+36,4,flags);retail.w(HANDLE,4,0 if missing else META);retail.base_callbacks=base_owner;retail.diagnostic_found=diagnostic
            if diagnostic:
                for offset in (96,100,104):retail.w(SYSTEM+offset,4,0x18c0000+offset)
            values=(abstract,HANDLE,BASEREG,BASEGET,0x1811700,NAME,32,GETVT,POST,optional,deps);retail.current_args=values
            compare(0x2fe9c0,*values)
        for inherited,runtime in itertools.product((0,1,2),(False,True)):
            setup();rows=[FIELD+i*0x100 for i in range(4)];retail.vector(FIELDS,rows);retail.vector(BASEFIELDS,rows[:inherited]);retail.w(META+56,4,BASE if inherited else 0)
            for i,field in enumerate(rows):
                retail.w(field+8,4,8+i*4);retail.w(field+0x80,4,(4,8,16,4)[i]);retail.w(field+37,1,runtime and i%2==1)
                retail.w(field+24,4,BASE if i<inherited else 0);retail.w(field+18,2,55+i)
            compare(0x2fe0d0,META)
        setup();retail.vector(FIELDS,[FIELD]);retail.w(FIELD+37,1,1);retail.w(META+72,4,0xffffffff);retail.w(META+32,4,77)
        compare(0x2fe0d0,META);assert retail.read(META+32,4)==77
        for null in (False,True):
            setup();retail.null_type=null;retail.w(FIELD+0x84,4,0x10004);compare(0x2fc630,FIELD)
            assert retail.read(FIELD+16,2)==(65535 if null else 5) and retail.read(FIELD+20,2)==4
        for flags in (0,2):
            setup();retail.callback_allocation=False;retail.base_callbacks=0;retail.w(META+36,4,flags)
            assert compare(0x2fe9c0,*retail.current_args)==0
        for oldsize,existing in itertools.product((-1,0,2,4,8),(0,0x1a10000)):
            setup();retail.old_size=oldsize;retail.w(FIELD+32,4,existing);compare(0x2fc3b0,FIELD)
        setup();compare(0x2fc2c0,FIELD,NAME,0x18e0000,12,META);compare(0x2fc630,FIELD)
        compare(0x2fc440,FIELD,NAME);compare(0x2fc490,FIELD,FIELD+12)
        for parent in (0,BASE):setup();compare(0x2fdc50,META,parent)
        setup();compare(0x2ead30,FIELDS,FIELD);compare(0x2fde50,META,FIELD+0x100)
        setup();retail.vector(FIELDS,[FIELD,FIELD+0x100]);compare(0x2fe000,META,NAMES,SLOTS,OFFSETS,0)
        setup();retail.reenter=True;retail.current_args=(0,HANDLE,BASEREG,BASEGET,0x1811700,NAME,32,GETVT,POST,0,0)
        compare(0x2fe9c0,*retail.current_args);assert retail.reentered and native.reentered
        # Actual Work registrar and field tables, not reconstructed table rows.
        setup();retail.w(0x588f88,4,0);compare(0x3581f0)
        expected=json.loads((ROOT/'data/reflection.json').read_text());classes=expected.get('classes',expected)
        work=next(row for row in classes.values() if row.get('class')=='beMessengerWork')
        assert retail.read(FIELDS+12,4)==len(work['fields'])==6
        for i,row in enumerate(work['fields']):
            field=retail.read(retail.read(FIELDS+8,4)+i*4,4)
            assert retail.string(retail.read(field+12,4)).decode()==row['name']
            assert retail.read(field+8,4)==row['offset'] and retail.read(int(row['desc']),4)==field
            assert retail.read(field+4,4)==1 and retail.read(retail.read(field+12,4)-4,4)==1
        for i,meta in ((4,0x18d0000),(5,0x18d1000)):
            field=retail.read(retail.read(FIELDS+8,4)+i*4,4);assert retail.read(field+52,1)==1 and retail.read(field+56,4)==meta
        assert retail.read(META+36,4)==7 and retail.read(META+72,4)==32
        if FACTORIES:
            assert retail.memories==6
            for i,vt in enumerate((0x533180,0x533180,0x532670,0x533180,0x532c80,0x532c80)):
                field=retail.read(retail.read(FIELDS+8,4)+i*4,4)
                assert retail.read(field,4)==vt
                assert retail.read(field+32,4)!=0 and retail.read(field+20,2)==4
                assert retail.read(field+38,1)==1 and retail.read(field+7,1)==0
                if i in (0,1,3):assert retail.read(field+56,1)==1 and retail.read(field+53,1)==1 and retail.read(field+39,1)==2
                if i>=4:assert retail.read(field+60,1)==1
        if METADATA:
            assert retail.read(META+4,4)==1 and retail.read(META+12,4)==0
            assert retail.string(retail.read(META+28,4))==b'beMessengerWork'
            assert retail.read(META+16,4)==1 and retail.read(META+25,1)==1
            assert retail.read(METADATA_REGISTRY+12,4)==1
            assert retail.read(retail.read(METADATA_REGISTRY+8,4),4)==META
        if INTERNAL:
            assert retail.read(FIELDS,4)==0x5327d0
            assert retail.list_bytes[retail.read(FIELDS+8,4)]==32
            assert len(retail.list_freed)==1
        compare(0x3581f0);setup();compare(0x358290)
        assert hits==set(ENTRIES),hits
        if STORAGE:assert storage_hits==STORAGE_ENTRIES,storage_hits
        if FACTORIES:assert FACTORY_ENTRIES<=factory_hits,factory_hits
        if INTERNAL:assert {0x2c2670,0x2ea4f0,0x2ea550,0x2eab70,0x2eaa60,0x2ea690,0x2ead30,0x2ea820,0x300e50}<=internal_hits,internal_hits
        if METADATA:assert METADATA_ENTRIES-{0x2fef70,0x2fd940,0x2fd980}<=metadata_hits,metadata_hits
    print(f'reflection registration retail: {cases} RAM/defined-return/ordered-call cases; all14 bodies, reentrant guard and actual Work tables; factories/allocator/interner/system/vector primitives controlled')
    if STORAGE:print('storage composition: original object-code lookup, allocator selection, allocation/free wrappers execute; allocator virtual leaves remain controlled')
    if FACTORIES:print('factory composition: actual Work string/int/reference factories, full initializer chain and virtual post-construction hooks; type queries and allocator leaves controlled')
    if METADATA:print('metadata composition: original metadata factory/initialization, pooled names and registry search/retaining insertion; internal field-list factory and allocator/interner/vector leaves controlled')
    if INTERNAL:print('internal list composition: actual factory/constructor, buffer allocation, retaining append, growth/reallocation/zeroing and registry search; allocator virtual leaves controlled')
if __name__=='__main__':main()
