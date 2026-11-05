#!/usr/bin/env python3
"""Memory value lifecycle plus actual Work/list instance construction and teardown."""
import argparse,ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
import test_reflection_registration_retail as reg
from test_list_registration_retail import Registration,ENTRIES as REGISTRATION
from test_object_base_retail import ENTRIES as BASE_ENTRIES,SCRATCH
from test_list_descriptor_copy_retail import ENTRIES as COPY_ENTRIES
from test_metadata_callback_services_retail import ENTRIES as SERVICES
from test_reflection_registration_retail import ROOT,Api,READ,WRITE,CALL,MASK,STACK,SYSTEM
from test_field_factories_retail import ENTRIES as FACTORY
from test_metadata_bootstrap_retail import ENTRIES as META
from test_internal_object_lists_retail import ENTRIES as INTERNAL
from test_object_storage_retail import ENTRIES as STORAGE
from test_object_creation_retail import ENTRIES as CREATION
from test_object_fields_retail import ENTRIES as FIELDS
from test_string_fields_retail import ENTRIES as STRINGS
from test_object_lists_retail import ENTRIES as LISTS
from test_list_services_retail import ENTRIES as GENERIC
ACTUAL_ARRAY=False
ACTUAL_BUFFERS=False
ACTUAL_REGISTRY=False
ACTUAL_BOOTSTRAP=False
ACTUAL_CONTEXT_LIFE=False
CONTEXT_LIFE_ENTRIES={0x2f25d0,0x2f2670,0x2f49e0,0x2f8830,0x2f28d0,0x2f64e0,0x2f6780}
BOOTSTRAP_ENTRIES={0x2fa4d0,0x2fa540,0x2fa5c0,0x2fa610,0x2fa6c0,0x2fa6e0,0x2f2180,0x2f2200,0x2f8680,0x2f88d0,0x2f88e0,0x2f8920,0x2f8960,0x2f89a0,0x2f89e0,0x2f2730,0x2f2830}
CONTEXT_DEFAULT,CONTEXT_NAMED,POOL_CLOSE=0x19a1000,0x19a1010,0x19a1020
REGISTRY_ENTRIES={0x2f04f0,0x2f0620,0x2f0630,0x2f0640,0x2f0650,0x2f0660,0x2f0670,0x2f0700,0x2fa5c0,0x2f00d0,0x2ed1c0,0x2ed200,0x2ed240}
REGISTRY_KIND,REGISTRY_AVAILABLE,REGISTRY_OWNS=0x19d0020,0x19d0030,0x19d0040
BUFFER_ENTRIES={0x2ed460,0x2ed4b0,0x2ed4c0,0x2ed4e0,0x2ed520,0x2ed530,0x2ed5a0,0x2ed5c0,0x2ed5d0}
BUFFER_SIZE=0x19d0000
BUFFER_INDEX=0x19d0010
ALIGNED_ALLOCATE=0x19f0020
MEMORY={0x2fa9d0,0x2fa9e0,0x2faa10,0x2faae0,0x2fab40,0x2fabf0,0x2facc0}
SCALAR={0x2fc580,0x2fc5a0,0x2fc5c0,0x2fd040,0x2fd050,0x2fd060,0x2fd070,0x2fd080,0x2fd230}
TRIM={0x13c180,0x331d60}
GETTERS={0x142b40,0x142a70,0x331660,0x36efa0,0x36f600}
NOOPS={0x2ff0a0,0x2ff0b0,0x2ff0c0,0x2ff0e0,0x2ff0f0,0x2ff140,0x2ff150,0x2ff130,0x2ff1a0}
ENTRIES=MEMORY|SCALAR|TRIM|GETTERS|NOOPS
RETURNS={0x2fa9d0,0x2fd230}|GETTERS
class Values(Registration):
    def __init__(self,image):
        super().__init__(image);self.descend|=ENTRIES|set(FIELDS)|set(STRINGS)|set(LISTS)|set(GENERIC)|set(STORAGE)|{0x2fda40};self.descend.discard(0x2ff820);self.descend.discard(0x2d6680)
        if ACTUAL_ARRAY:
            self.descend.add(0x2fb190);self.w(0x1825000+220,4,ALIGNED_ALLOCATE)
        if ACTUAL_BUFFERS:
            self.descend|=BUFFER_ENTRIES;self.w(0x1825000+336,4,BUFFER_SIZE);self.w(0x1825000+364,4,BUFFER_INDEX)
        if ACTUAL_REGISTRY:
            self.descend|=REGISTRY_ENTRIES
            self.w(0x1822000+4,4,1)
            secondary=self.allocate(12,True);self.w(0x586f60,4,secondary)
            for slot,entry in ((116,REGISTRY_KIND),(132,REGISTRY_AVAILABLE),(340,REGISTRY_OWNS),(364,0x2f0650)):
                self.w(0x1825000+slot,4,entry)
        if ACTUAL_BOOTSTRAP:
            self.descend|=BOOTSTRAP_ENTRIES;self.w(SYSTEM+48,4,0x18f2000)
            self.w(0x587040,4,2)  # Fixture allocator selector, not a pointer-shaped token.
            self.w(0x586fd0,4,0x1e10000);self.w(0x587010,4,0)
            self.w(0x1e10000,4,0x1e20000);self.w(0x1e20000+92,4,0x2f2730);self.w(0x1e20000+96,4,0x2f2830)
            for i in range(46):self.w(0x1e10000+20+i*144,4,0x18f2000)
            self.text(0x1e10000+24+2*144,b'pool')
            self.w(0x1825000+392,4,POOL_CLOSE)
        if ACTUAL_CONTEXT_LIFE:
            self.descend|=CONTEXT_LIFE_ENTRIES
            self.text(0x1e10000+24+2*144,self.string(self.read(0x4c2170+2*4,4)))
        self.actual_lifetime=False;self.named=True;self.element_size=4;self.move_on_destroy=False;self.move_on_free=False
        self.field=self.allocate(80,True);self.object=self.allocate(64,True);self.nodes=[self.allocate(8,True) for _ in range(3)]
        self.buffer=self.allocate(12,True);self.other=self.allocate(12,True);self.default=self.allocate(4,True)
        self.w(self.field,4,0x532a50);self.w(self.field+4,4,1);self.w(self.field+8,4,8);self.w(self.field+20,2,4);self.w(self.field+32,4,self.default)
        self.w(self.field+52,1,1);self.w(self.field+53,1,1);self.w(self.field+56,4,10);self.w(self.field+60,4,self.scalar[1]);self.w(self.field+65,1,1);self.w(self.field+66,1,1)
        self.w(self.object+8,4,self.buffer);self.w(self.object+12,4,self.other)
        for i,node in enumerate(self.nodes):self.w(node+4,4,1);self.w(self.buffer+i*4,4,node);self.w(self.other+i*4,4,0)
    def step(self,pc,delay=False):
        if ACTUAL_BOOTSTRAP and pc in (0x2fa6d8,0x2fa6f8):
            target=self.r[25]&0xffffffff;super().step(pc+4,True);self.call_hook(target);return self.r[31]&0xffffffff
        if ACTUAL_REGISTRY and not ACTUAL_BOOTSTRAP and pc==0x2f00d0:
            super().step(pc+4,True);self.call_hook(0x2f88e0);return self.r[31]&0xffffffff
        if ACTUAL_REGISTRY and pc in (0x2ed1ec,0x2ed254):
            target=self.r[25]&0xffffffff;super().step(pc+4,True);self.call_hook(target);return self.r[31]&0xffffffff
        if ACTUAL_BUFFERS and not ACTUAL_REGISTRY and pc==0x2ed520:
            super().step(pc+4,True);self.call_hook(0x2f04f0);return self.r[31]&0xffffffff
        if pc in (0x2fc590,0x2fc5b0):
            target=(self.read(pc,4)&0x3ffffff)<<2
            super().step(pc+4,True);self.call_hook(target);return self.r[31]&0xffffffff
        return super().step(pc,delay)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==0x12ad58:
            self.events.append((e,*v[:3]));text=self.string(v[1])
            for i in range(v[2]):self.w(v[0]+i,1,text[i] if i<len(text) else 0)
            return v[0]
        if e==CONTEXT_DEFAULT:self.events.append((e,*v[:2]));return 0x18f2000
        if e==CONTEXT_NAMED:self.events.append((e,*v[:2]));return 0x18f2000 if self.named else 0
        if e==POOL_CLOSE:self.events.append((e,v[0],self.read(0x586f58,4),self.read(0x586f60,4)));return 0
        if e==0x300cd0:self.events.append((e,*v[:2]));return int(v[0]==self.scalar[1])
        if e==0x2f04f0:self.events.append((e,v[0]));return 0x18f2000 if ACTUAL_BUFFERS else 0
        if e==REGISTRY_KIND:self.events.append((e,v[0]));return 0
        if e==REGISTRY_AVAILABLE:self.events.append((e,v[0]));return 1
        if e==REGISTRY_OWNS:self.events.append((e,*v[:2]));return int(v[1] in self.allocated or v[1] in self.list_bytes)
        if e==BUFFER_INDEX:self.events.append((e,v[0]));return 0
        if e==BUFFER_SIZE:
            self.events.append((e,*v[:2]));return self.allocated.get(v[1],self.list_bytes.get(v[1],0))
        if e==0x2ed1c0:
            self.events.append((e,*v[:2]));return self.allocate(v[0])
        if ACTUAL_BUFFERS and e==0x1821100 and self.move_on_free:
            self.events.append((e,*v[:2]));self.freed.add(v[1]);self.w(self.field+8,4,12);self.move_on_free=False;return 0
        if e==0x2f0670:self.events.append((e,v[0]));return 0
        if e==0x2f8920:self.events.append((e,v[0]));return 0x18f2000 if self.named else 0
        if e==ALIGNED_ALLOCATE:
            self.events.append((e,*v[:3]));return self.allocate(v[1])
        if e==0x2fb190:
            self.events.append((e,'temp',*v[1:5]));p=self.allocate(v[3]*self.element_size,True)
            self.w(v[2]+self.read(v[1]+8,4),4,p);self.w(v[0],4,p);return v[0]
        if e==0x2ed530:self.events.append((e,v[0]));return v[0]
        if e==0x2ed5d0:self.events.append((e,v[0]));self.freed.add(v[0]);return 0
        if e==0x2ff820 and not self.actual_lifetime:
            self.events.append((e,v[0]))
            if self.move_on_destroy:self.w(self.field+8,4,12);self.move_on_destroy=False
            return 0
        if e==0x2ed460 and self.move_on_free:
            self.events.append((e,v[0]));self.freed.add(v[0]);self.w(self.field+8,4,12);self.move_on_free=False;return 0
        if e==0x2d6680 and not self.actual_lifetime:self.events.append((e,*v[:3]));self.w(v[0]+12,4,v[1]);return 0
        return super().call(e,args)

def main():
    global ACTUAL_ARRAY,ACTUAL_BUFFERS,ACTUAL_REGISTRY,ACTUAL_BOOTSTRAP,ACTUAL_CONTEXT_LIFE
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--array-storage',action='store_true');parser.add_argument('--buffer-services',action='store_true');parser.add_argument('--allocator-registry',action='store_true');parser.add_argument('--registry-bootstrap',action='store_true');parser.add_argument('--context-lifecycle',action='store_true');args=parser.parse_args();ACTUAL_CONTEXT_LIFE=args.context_lifecycle;ACTUAL_BOOTSTRAP=args.registry_bootstrap or ACTUAL_CONTEXT_LIFE;ACTUAL_REGISTRY=args.allocator_registry or ACTUAL_BOOTSTRAP;ACTUAL_BUFFERS=args.buffer_services or ACTUAL_REGISTRY;ACTUAL_ARRAY=args.array_storage or ACTUAL_BUFFERS
    reg.STORAGE=reg.FACTORIES=reg.METADATA=reg.INTERNAL=True
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();retail=Values(image);native=Values(image);errors=[];cases=0;hits=set();coverage=set()
    @CALL
    def call(_,e,values):
        try:return invoke_native(e,values)
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-memory-values-') as td:
        so=Path(td)/'values.so';sources=('context-lifecycle.c','registry-bootstrap.c','allocator-registry.c','memory-buffer-services.c','array-storage.c','memory-field-values.c','list-registration.c','list-descriptor-copy.c','metadata-callback-services.c','object-base.c','reflection-registration.c','field-factories.c','metadata-bootstrap.c','internal-object-lists.c','object-storage.c','object-creation.c','object-fields.c','string-fields.c','object-lists.c','list-services.c')
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in sources],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));names=('dw4_context_lifecycle','dw4_registry_bootstrap','dw4_allocator_registry','dw4_memory_buffer_service','dw4_array_storage','dw4_memory_field_value','dw4_list_registration','dw4_list_descriptor_copy','dw4_metadata_callback_service','dw4_object_base','dw4_reflection_registration','dw4_field_factory','dw4_metadata_bootstrap','dw4_internal_object_list','dw4_object_storage','dw4_object_creation','dw4_object_field','dw4_string_field','dw4_object_list','dw4_list_service')
        fns={name:getattr(lib,name) for name in names};scratch_names={'dw4_context_lifecycle','dw4_registry_bootstrap','dw4_array_storage','dw4_memory_field_value','dw4_list_registration','dw4_object_base','dw4_reflection_registration','dw4_string_field','dw4_list_service'}
        for name,f in fns.items():f.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)]+([C.c_uint32] if name in scratch_names else []);f.restype=C.c_uint64
        def invoke_native(e,values):
            if ACTUAL_CONTEXT_LIFE and e in CONTEXT_LIFE_ENTRIES:return fns['dw4_context_lifecycle'](C.byref(api),e,values,SCRATCH+0x800)
            if ACTUAL_BOOTSTRAP and e in BOOTSTRAP_ENTRIES:return fns['dw4_registry_bootstrap'](C.byref(api),e,values,SCRATCH+0x600)
            if ACTUAL_REGISTRY and e in REGISTRY_ENTRIES:return fns['dw4_allocator_registry'](C.byref(api),e,values)
            if ACTUAL_BUFFERS and e in BUFFER_ENTRIES:return fns['dw4_memory_buffer_service'](C.byref(api),e,values)
            if ACTUAL_ARRAY and e==0x2fb190:return fns['dw4_array_storage'](C.byref(api),e,values,SCRATCH+0x400)
            if e==0x2d6680 and not native.actual_lifetime:return native.call(e,list(values[:8]))&MASK
            if e==0x2ff820 and not native.actual_lifetime:return native.call(e,list(values[:8]))&MASK
            for entries,name in ((ENTRIES,'dw4_memory_field_value'),(REGISTRATION,'dw4_list_registration'),(COPY_ENTRIES,'dw4_list_descriptor_copy'),(SERVICES,'dw4_metadata_callback_service'),(BASE_ENTRIES,'dw4_object_base'),(reg.ENTRIES,'dw4_reflection_registration'),(INTERNAL,'dw4_internal_object_list'),(FACTORY,'dw4_field_factory'),(META,'dw4_metadata_bootstrap'),(STORAGE,'dw4_object_storage'),(FIELDS,'dw4_object_field'),(STRINGS,'dw4_string_field'),(LISTS,'dw4_object_list'),(GENERIC,'dw4_list_service'),(CREATION,'dw4_object_creation')):
                if e in entries:return fns[name](C.byref(api),e,values,*([SCRATCH+0x200 if name in ('dw4_memory_field_value','dw4_string_field','dw4_list_service') else SCRATCH] if name in scratch_names else []))
            return native.call(e,list(values[:8]))&MASK
        def setup():
            nonlocal retail
            retail=Values(image)
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            try:expected=retail.invoke(entry,*values)
            except Exception as ex:raise AssertionError((hex(entry),hex(retail.r[31]),[hex(x) for x in retail.r[4:8]],retail.events[-15:])) from ex
            actual=invoke_native(entry,(C.c_uint64*12)(*[x&MASK for x in values]))
            assert not errors,errors
            if entry in RETURNS:assert expected==actual,(hex(entry),expected,actual)
            def ram(w):return {p:v for p,v in w.mem.items() if not STACK-0x5000<=p<STACK+40 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry);coverage.update(retail.covered);return actual
        for entry,flag,kind,buffer in itertools.product((0x2fab40,0x2fabf0),(0,1,2),(0,1,2),(False,True)):
            setup();retail.w(retail.field+66,1,flag);retail.w(retail.field+60,4,0 if kind==0 else retail.scalar[kind]);retail.w(retail.object+8,4,retail.buffer if buffer else 0);compare(entry,retail.field,retail.object)
        for enabled,buffer,change in itertools.product((0,1),(False,True),(False,True)):
            setup();retail.w(retail.field+53,1,enabled);retail.w(retail.object+8,4,retail.buffer if buffer else 0);retail.move_on_destroy=change;retail.move_on_free=change;compare(0x2faae0,retail.field,retail.object)
        for release,default in itertools.product((0,1),(False,True)):
            setup();retail.w(retail.field+65,1,release);retail.w(retail.default,4,retail.other if default else 0);compare(0x2facc0,retail.field,retail.object)
        for enabled,named,found,size in itertools.product((0,1),(False,True),(False,True),(0,1,10)):
            setup();retail.w(retail.field+52,1,enabled);retail.named=found
            if ACTUAL_BOOTSTRAP:retail.w(0x1e10000+20+2*144,4,0x18f2000 if found else 0)
            name=retail.allocate(8,True);retail.text(name,retail.string(retail.read(0x4c2170+2*4,4)) if ACTUAL_CONTEXT_LIFE else b'pool');retail.w(retail.field+76,4,name if named else 0)
            retail.w(retail.field+56,4,size);compare(0x2faa10,retail.field,retail.object)
        for entry in (0x2fc580,0x2fc5a0):
            setup();retail.w(retail.default,4,0x12345678);compare(entry,retail.field,retail.object);assert retail.read(retail.object+8,4)==0x12345678
        setup();compare(0x2fa9e0,retail.field,0x1234);compare(0x2fa9d0,retail.field)
        for entry in SCALAR|NOOPS|TRIM|GETTERS:
            setup();compare(entry,retail.field,retail.object)
        # Original metadata -> three actual instances -> final owner release.
        setup()
        if ACTUAL_CONTEXT_LIFE:
            compare(0x2f25d0,0x1e10000)
            retail.w(0x18f2000+4,4,1)  # External allocator ownership survives context bindings.
            for i in range(46):compare(0x2f28d0,0x1e10000,i,0x18f2000)
            assert retail.read(0x18f2000+4,4)==47
            assert retail.read(0x1e10000+8,4)==46
            for i in range(46):assert retail.string(0x1e10000+24+i*144)==retail.string(retail.read(0x4c2170+i*4,4))
        if ACTUAL_BOOTSTRAP:
            compare(0x2f2180,0x1824000)
            primary=retail.read(0x586f58,4);secondary=retail.read(0x586f60,4)
            assert retail.read(primary+4,4)==1 and retail.read(secondary+4,4)==0
            assert retail.read(primary+8,4)==retail.read(secondary+8,4)==64
            assert retail.read(retail.read(primary,4),4)==0x1824000
            registry_allocations={primary,secondary,retail.read(primary,4),retail.read(secondary,4)}
        compare(0x3581d0);retail.w(SYSTEM,1,1);retail.actual_lifetime=True;retail.descend|={0x2ff820,0x2d6680}
        work_meta=retail.read(0x588f88,4);int_meta=retail.read(0x586880,4);ram_meta=retail.read(0x589d20,4)
        compare(0x2fda40,work_meta,0x18f2000)
        created=[p for p,size in retail.allocated.items() if size==32 and retail.read(p,4)==0x536f10]
        assert len(created)==1,created
        work=created[0];integer=retail.read(work+24,4);ram=retail.read(work+28,4)
        assert retail.read(work+4,4)==retail.read(integer+4,4)==retail.read(ram+4,4)==1
        assert all(retail.read(work+o,4)==0 for o in (8,12,16,20))
        for p in (integer,ram):assert all(retail.read(p+o,4)==0 for o in (8,12,16))
        assert all(retail.read(p+44,4)==1 for p in (work_meta,int_meta,ram_meta))
        if ACTUAL_REGISTRY:
            header=retail.allocate(8)
            saved_flags=retail.read(work+6,1);retail.w(work+6,1,saved_flags|128)
            compare(0x2fef70,header,work)
            assert retail.read(header,4)==0x52f0f0
            assert retail.read(header+6,1)&128 and retail.read(header+7,1)==0
            retail.w(work+6,1,saved_flags)
        # Populate strings, integers and retained references through original methods.
        fields=retail.fields(work_meta)
        text=retail.allocate(32,True);retail.text(text,b'owned-value');cell_source=retail.allocate(4,True);retail.w(cell_source,4,text)
        compare(0x30a910,fields[2],work,cell_source)
        token=retail.read(work+8,4);assert token and retail.read(token-4,4)==1
        compare(0x2d6b20,integer,7);compare(0x2d6b20,integer,9)
        assert retail.read(integer+8,4)==2
        root_meta=retail.read(0x587198,4);root_objects=[]
        for _ in range(2):
            before=set(retail.allocated);compare(0x2fda40,root_meta,0x18f2000)
            created_root=[p for p in set(retail.allocated)-before if retail.read(p,4)==0x52f0f0 and retail.allocated[p]==8]
            assert len(created_root)==1;root_objects.append(created_root[0])
            compare(0x301e30,ram,created_root[0])
            temporary=retail.allocate(20,True);slot=retail.allocate(4,True)
            retail.w(temporary+8,4,1);retail.w(temporary+12,4,1);retail.w(temporary+16,4,slot);retail.w(slot,4,created_root[0])
            compare(0x301c90,temporary,0)
            assert retail.read(created_root[0]+4,4)==1
        assert retail.read(root_meta+44,4)==2 and retail.read(ram+8,4)==2
        int_buffer=retail.read(integer+16,4);ram_buffer=retail.read(ram+16,4)
        holder=retail.allocate(20,True);cell=retail.allocate(4,True);retail.w(holder+8,4,1);retail.w(holder+12,4,1);retail.w(holder+16,4,cell);retail.w(cell,4,work)
        before_teardown=set(retail.allocated)
        compare(0x301c90,holder,0)
        assert retail.read(cell,4)==0 and all(retail.read(p+44,4)==0 for p in (work_meta,int_meta,ram_meta))
        assert {work,integer,ram,int_buffer,ram_buffer,*root_objects}<=retail.freed
        trimmed_buffers=set(retail.allocated)-before_teardown
        assert len(trimmed_buffers)==2 and all(retail.allocated[p]==8 for p in trimmed_buffers)
        assert trimmed_buffers<=retail.freed
        assert retail.read(root_meta+44,4)==0 and retail.read(token-4,4)==0
        if ACTUAL_BOOTSTRAP:
            compare(0x2f2200,0x1824000)
            assert registry_allocations<=retail.freed
            assert retail.read(0x586f58,4)==retail.read(0x586f60,4)==0
            assert retail.events[-1]==(POOL_CLOSE,0x1824000,0,0)
            assert {0x2f2180,0x2f2200,0x2fa4d0,0x2fa610,0x2fa540,0x2f8680,0x2f8920,0x2f2730,0x2f2830}<=coverage
        if ACTUAL_CONTEXT_LIFE:
            for i in range(46):compare(0x2f28d0,0x1e10000,i,0)
            assert retail.read(0x18f2000+4,4)==1
            assert all(retail.read(0x1e10000+20+i*144,4)==0 for i in range(46))
            compare(0x2f2670,0x1e10000,0)
            assert retail.read(0x1e10000+4,4)==0
            assert {0x2f25d0,0x2f2670,0x2f49e0,0x2f28d0,0x2f6780}<=coverage
        assert ENTRIES<=hits|coverage,ENTRIES-(hits|coverage)
        if ACTUAL_ARRAY:assert 0x2fb190 in coverage
        if ACTUAL_BUFFERS:assert {0x2ed460,0x2ed4e0,0x2ed530,0x2ed5d0}<=coverage
        if ACTUAL_REGISTRY:assert {0x2f04f0,0x2f0670,0x2fa5c0,0x2ed1c0}<=coverage
    boundary='type/allocator leaves controlled; actual array storage' if ACTUAL_ARRAY else 'type/allocator/array allocation leaves controlled'
    if ACTUAL_BUFFERS:boundary='actual array/buffer services; owner search, allocator and type leaves controlled'
    if ACTUAL_REGISTRY:boundary='actual array/buffer/owner/selector/wrapper services; allocator virtual methods and type leaves controlled'
    if ACTUAL_BOOTSTRAP:boundary='actual registry bootstrap, context dispatch and allocation services; allocator/context virtual implementations and types controlled'
    if ACTUAL_CONTEXT_LIFE:boundary='actual context constructor/names/retained slots and teardown; concrete allocator internals and slot204 builder controlled'
    print(f'memory field values retail: {cases} RAM/defined-return/ordered-call checkpoints; all32 bodies plus real registered Work/two-child instance creation and final release; {boundary}')
if __name__=='__main__':main()
