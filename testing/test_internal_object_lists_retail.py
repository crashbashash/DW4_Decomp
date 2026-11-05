#!/usr/bin/env python3
"""Complete internal pointer-list group vs retail RAM, returns and ordered calls."""
import ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
from test_metadata_bootstrap_retail import Metadata,ENTRIES as META_ENTRIES,OBJECT,ALLOC,SOURCE,ROOT,Api,READ,WRITE,CALL,MASK,STACK,SYSTEM
from test_field_factories_retail import ENTRIES as FIELD_ENTRIES,ALLOCATE
from test_reflection_registration_retail import World
ENTRIES={0x2c2670,0x2ea4f0,0x2ea550,0x2ea590,0x2ea630,0x2ea690,0x2ea780,0x2ea820,0x2ea870,0x2ea8e0,0x2ea9a0,0x2eaa00,0x2eaa60,0x2eaaf0,0x2eab70,0x2eabb0,0x2eabf0,0x2eac30,0x2eac60,0x2eac80,0x2ead30,0x2ead50}
STORAGE={0x2f0700,0x301000,0x300e50}
RETURNS={0x2c2670,0x2ea4f0,0x2ea550,0x2ea590,0x2ea780,0x2ea820,0x2eaa00,0x2eab70,0x2eabb0,0x2eabf0}
BUFFER,ALT,SRCDATA,OWNER,NAMES,QUERY,NODE=0x1a00000,0x1a10000,0x1a20000,0x1990000,0x1991000,0x1992000,0x1993000
FREE,REALLOC=0x1960200,0x1960300
class Lists(Metadata):
    def __init__(self,image):
        super().__init__(image);self.descend=ENTRIES|FIELD_ENTRIES|META_ENTRIES|STORAGE
        self.blocks={};self.allocations=0;self.factory_allocation=False;self.freed=set()
        self.move_capacity=False;self.move_after_zero=False;self.move_after_release=False;self.move_after_compare=False
        self.w(OBJECT+8,4,BUFFER);self.w(OBJECT+12,4,3);self.w(SOURCE+8,4,SRCDATA);self.w(SOURCE+12,4,3)
        self.w(ALLOC,4,0x1952000);self.w(0x1952000+216,4,ALLOCATE);self.w(0x1952000+232,4,REALLOC);self.w(0x1952000+264,4,FREE)
        for bank in range(2):
            node=0x1980000+bank*0x1000;table=node+0x100
            self.w(0x586f58+bank*8,4,node);self.w(node,4,table)
            for i in range(128):self.w(table+i*4,4,ALLOC)
        for p,capacity in ((BUFFER,4),(ALT,8),(SRCDATA,4)):self.buffer(p,capacity)
        for i in range(8):self.w(NODE+i*0x100+4,4,1)
        for i in range(4):self.w(BUFFER+i*4,4,NODE+i*0x100);self.w(ALT+i*4,4,NODE+(3-i)*0x100);self.w(SRCDATA+i*4,4,NODE+i*0x100)
        self.w(OWNER+8,4,12)
        for i,text in enumerate((b'a',b'b',b'c')):self.text(QUERY+i*0x100,text);self.w(NODE+i*0x100+12,4,QUERY+i*0x100)
        self.w(0x5860d0,4,0x1984000)
    def step(self,pc,delay=False):return World.step(self,pc,delay)
    def buffer(self,p,capacity):
        self.blocks[p]=capacity*4
        for i in range(-16,capacity*4+16):self.w(p+i,1,0xa5)
    def allocate(self,size):
        p=0x1c00000+self.allocations*0x10000;self.allocations+=1;self.buffer(p,(size+3)//4);self.blocks[p]=size;return p
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==0x2ed4e0:
            self.events.append((e,v[0]));size=self.blocks[v[0]]
            if self.move_capacity:self.w(OBJECT+8,4,ALT);self.move_capacity=False
            return size
        if e==ALLOCATE:
            self.events.append((e,*v[:2]))
            if self.factory_allocation:self.factory_allocation=False;return OBJECT
            return self.allocate(v[1])
        if e==FREE:self.events.append((e,*v[:2]));self.freed.add(v[1]);return 0
        if e==REALLOC:
            self.events.append((e,*v[:3]));p=self.allocate(v[2])
            if v[1]:
                for i in range(min(self.blocks[v[1]],v[2])):self.w(p+i,1,self.read(v[1]+i,1))
                self.freed.add(v[1])
            return p
        if e in (0x127098,0x12724c):
            self.events.append((e,*v[:3]));assert v[2]<=65536,(hex(e),v)
            data=bytes(self.read(v[1]+i,1) for i in range(v[2])) if e==0x127098 else bytes([v[1]&255])*v[2]
            for i,b in enumerate(data):self.w(v[0]+i,1,b)
            if e==0x12724c and self.move_after_zero:self.w(OBJECT+12,4,2);self.move_after_zero=False
            return v[0]
        if e==0x12a4a4:
            self.events.append((e,*v[:2]));result=int(self.string(v[0])!=self.string(v[1]))
            if self.move_after_compare:self.w(OBJECT+8,4,ALT);self.move_after_compare=False
            return result
        if e==0x2ff820:
            self.events.append((e,v[0]))
            if self.move_after_release:self.w(OBJECT+8,4,ALT);self.w(OBJECT+12,4,7);self.move_after_release=False
            return 0
        if e==0x2c2860:self.events.append((e,));self.w(0x5860d0,4,0x1984100);return 0
        if e==0x2ff0a0:self.events.append((e,v[0]));return 0
        return super().call(e,args)

def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();retail=Lists(image);native=Lists(image);errors=[];cases=0;hits=set()
    @CALL
    def call(_,e,values):
        try:
            if e in ENTRIES:return fn(C.byref(api),e,values)
            if e in FIELD_ENTRIES:return field_fn(C.byref(api),e,values)
            if e in META_ENTRIES:return meta_fn(C.byref(api),e,values)
            if e in STORAGE:return storage_fn(C.byref(api),e,values)
            return native.call(e,list(values[:8]))&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-internal-lists-') as td:
        so=Path(td)/'lists.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in ('internal-object-lists.c','field-factories.c','metadata-bootstrap.c','object-storage.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));fn=lib.dw4_internal_object_list;field_fn=lib.dw4_field_factory;meta_fn=lib.dw4_metadata_bootstrap;storage_fn=lib.dw4_object_storage
        for f in (fn,field_fn,meta_fn,storage_fn):f.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];f.restype=C.c_uint64
        def setup():
            nonlocal retail
            retail=Lists(image)
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            expected=retail.invoke(entry,*values);actual=fn(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in values]))
            assert not errors,errors
            if entry in RETURNS:assert expected==actual,(hex(entry),expected,actual)
            def ram(w):return {p:v for p,v in w.mem.items() if not STACK-0x3000<=p<STACK+32 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry);return actual
        for active,allocator in itertools.product((0,1),(0,ALLOC)):
            setup();retail.w(SYSTEM,1,active);retail.factory_allocation=True;compare(0x2c2670,allocator)
        for entry,active,present,alias in itertools.product((0x2ea4f0,0x2ea550,0x2ea590,0x2eab70,0x2eabb0,0x2eabf0),(0,1),(False,True),(False,True)):
            setup();retail.w(SYSTEM,1,active)
            if not present:retail.w(SOURCE+8,4,0)
            compare(entry,OBJECT,OBJECT if alias else SOURCE)
        for capacity in (0,1,4,511,512,1024):
            for index in (capacity-1,capacity,capacity+1,capacity+512):
                setup();retail.buffer(BUFFER,capacity);retail.w(OBJECT+8,4,BUFFER if capacity else 0);compare(0x2ea690,OBJECT,index)
        for entry,capacity,count in itertools.product((0x2ea8e0,0x2eaa60,0x2eaaf0,0x2ea9a0),(0,4),(0,3,4)):
            for index in (0,count,count+1):
                setup();retail.buffer(BUFFER,capacity);retail.w(OBJECT+8,4,BUFFER if capacity else 0);retail.w(OBJECT+12,4,count)
                compare(entry,OBJECT,index,NODE) if entry in (0x2ea8e0,0x2eaaf0) else compare(entry,OBJECT,NODE if entry==0x2eaa60 else index)
        for count,index in itertools.product((0,1,4),(-1,0,1,3,4,5)):
            setup();retail.w(OBJECT+12,4,count);compare(0x2eaa00,OBJECT,index)
        for capacity,count in itertools.product((0,1,4,8),(-1,0,1,4,9)):
            setup();retail.buffer(BUFFER,capacity);retail.w(OBJECT+8,4,BUFFER if capacity else 0);retail.w(OBJECT+12,4,count)
            compare(0x2ea870,OBJECT)
        for entry,count,value,index in itertools.product((0x2eac60,0x2ead30),(0,3,4),(0,NODE,NODE+0x100),(0,1,3)):
            setup();retail.w(OBJECT+12,4,count)
            compare(entry,OBJECT,index,value) if entry==0x2eac60 else compare(entry,OBJECT,value)
        for count,target,refs in itertools.product((0,1,3,4),(0,1,3,4,5),(1,2,0x800001)):
            setup();retail.w(OBJECT+12,4,count)
            for i in range(4):retail.w(NODE+i*0x100+4,4,refs)
            compare(0x2eac80,OBJECT,target)
        for entry,count,present in itertools.product((0x2ea630,0x2eac30),(0,3),(False,True)):
            if count and not present:continue
            setup();retail.w(OBJECT+12,4,count);retail.w(OBJECT+8,4,BUFFER if present else 0);compare(entry,OBJECT)
        for count,query,mutate in itertools.product((0,3),(0,1,2),(False,True)):
            setup();retail.w(OBJECT+12,4,count)
            for i in range(3):retail.w(BUFFER+i*4,4,NODE+i*0x100);retail.w(ALT+i*4,4,NODE+((i+1)%3)*0x100)
            retail.move_after_compare=mutate;compare(0x2ea780,OBJECT,OWNER,QUERY+query*0x100)
        for count,value in itertools.product((-1,0,3),(0,NODE,NODE+0x100,0x1234)):
            setup();retail.w(OBJECT+12,4,count);compare(0x2ea820,OBJECT,value)
        setup();retail.move_capacity=True;compare(0x2ea690,OBJECT,4)
        setup();retail.w(OBJECT+12,4,4);retail.move_after_zero=True;compare(0x2eaa60,OBJECT,NODE)
        assert retail.read(OBJECT+12,4)==3
        setup();retail.w(OBJECT+12,4,4);retail.move_after_release=True;compare(0x2eac80,OBJECT,1)
        assert retail.read(OBJECT+8,4)==ALT and retail.read(OBJECT+12,4)==1
        for old,value,refs,index in itertools.product((0,NODE),(0,NODE,NODE+0x100),(1,2,0x800001),(0,3)):
            setup();retail.w(BUFFER+index*4,4,old);retail.w(NODE+4,4,refs);compare(0x2ead50,OBJECT,index,value)
        setup();retail.move_after_release=True;compare(0x2ead50,OBJECT,0,NODE+0x100)
        assert retail.read(ALT,4)==NODE+0x100 and retail.read(OBJECT+12,4)==7
        # Persistent original factory -> retaining append/growth -> shrink/destruct.
        setup();retail.factory_allocation=True;compare(0x2c2670,ALLOC)
        first_buffer=retail.read(OBJECT+8,4)
        assert retail.read(OBJECT,4)==0x5327d0 and retail.read(OBJECT+12,4)==0
        for i in range(6):compare(0x2ead30,OBJECT,NODE+i*0x100)
        assert retail.read(OBJECT+12,4)==6 and all(retail.read(NODE+i*0x100+4,4)==2 for i in range(6))
        last_buffer=retail.read(OBJECT+8,4);assert last_buffer!=first_buffer
        compare(0x2eac80,OBJECT,3);compare(0x2eac30,OBJECT)
        assert retail.read(OBJECT+12,4)==0 and all(retail.read(NODE+i*0x100+4,4)==1 for i in range(6))
        assert {first_buffer,last_buffer}<=retail.freed
        assert hits==ENTRIES,hits
    print(f'internal object lists retail: {cases} RAM/defined-return/ordered-call cases; all22 bodies; real header/raw allocation/storage helpers, allocator/byte/destruction/type services controlled')
if __name__=='__main__':main()
