#!/usr/bin/env python3
"""Retained object-list and property lookup group vs original RAM/call order.

Generic list operations run recovered C. Metadata, allocation, bytes, string
comparison/interning and object destruction remain controlled leaves.
"""
import argparse,ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
from test_list_services_retail import Lists,ENTRIES as GENERIC,LIST,OLD,SOURCE,NEW,TOKEN,OTHER,ROOT,STACK,MASK,Api,READ,WRITE,CALL
ENTRIES=(0x301c90,0x301d80,0x301e30,0x301e90,0x301ee0,0x302000,0x302100,0x302240,0x3022c0,0x302380,0x3023f0,0x302480,0x2fecb0)
RECORD=0x1900000;DESC=0x1940000;SECOND=0x1950000;OUT=0x1960000;TEXT=0x1a00000
RETURNS={0x302100,0x302240,0x3022c0,0x302380,0x3023f0,0x302480}
class Objects(Lists):
    def __init__(self,image):super().__init__(image);self.descend=set(ENTRIES)|set(GENERIC);self.clear_count=False;self.relocate_lookup=False
    def setup_objects(self,count,capacity,refs=2):
        self.setup(count,capacity,4);self.clear_count=False;self.relocate_lookup=False
        self.w(DESC+8,4,8)
        for i in range(max(count,capacity)+1):
            p=RECORD+i*0x100;self.w(p+4,4,refs);self.w(p+8,4,TEXT+i*0x100);self.w(p+16,4,i*2)
            self.text(TEXT+i*0x100,('key'+str(i)).encode());self.w(OLD+i*4,4,p if i<count else 0)
        self.w(SECOND+8,4,count);self.w(SECOND+12,4,capacity);self.w(SECOND+16,4,SECOND+0x1000)
        for i in range(count):self.w(SECOND+0x1000+i*4,4,RECORD+i*0x100)
    def text(self,p,value):
        for i,b in enumerate(value+b'\0'):self.w(p+i,1,b)
    def string(self,p):
        out=[]
        while self.read(p,1):out.append(self.read(p,1));p+=1
        return bytes(out)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==0x2ff820:
            self.events.append((e,v[0]))
            if self.clear_count:self.w(LIST+8,4,0)
            return 0
        if e==0x12a4a4:
            self.events.append((e,*v[:2]))
            if self.relocate_lookup:
                for i in range(self.read(LIST+8,4)):self.w(NEW+i*4,4,self.read(OLD+i*4,4))
                self.w(LIST+16,4,NEW);self.w(LIST+8,4,0);self.relocate_lookup=False
            return int(self.string(v[0])!=self.string(v[1]))
        if e==0x2eaf60:
            self.events.append((e,*v[:2]))
            if v[1]:self.w(v[1]-4,4,self.read(v[1]-4,4)+1)
            return v[1]
        return super().call(e,args)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=p.parse_args()
    image=args.elf.read_bytes();retail=Objects(image);native=Objects(image);errors=[];cases=0;hits=set();depth=0
    @CALL
    def call(_,e,values):
        nonlocal depth
        try:
            if e in ENTRIES:return objects(C.byref(api),e,values)
            if e in GENERIC:
                depth+=1
                try:return generic(C.byref(api),e,values,STACK-0x800-depth*0x100)
                finally:depth-=1
            return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-object-lists-') as td:
        so=Path(td)/'objects.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/object-lists.c'),str(ROOT/'recovered/engine/list-services.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));objects=lib.dw4_object_list;generic=lib.dw4_list_service
        objects.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];objects.restype=C.c_uint64
        generic.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];generic.restype=C.c_uint64
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            expected=retail.invoke(entry,*values);actual=objects(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in values]))
            assert not errors,errors
            if entry in RETURNS:assert expected==actual,(hex(entry),values,expected,actual)
            def ram(world):return {p:v for p,v in world.mem.items() if not STACK-0x2000<=p<STACK+32 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),values,[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry)
        for count,capacity,refs,value in itertools.product((0,1,4,8,9,17),(4,32),(1,2,0x800001),(0,RECORD)):
            for entry in (0x301c90,0x301d80,0x301e30,0x302240):
                retail.setup_objects(count,max(count,capacity),refs);compare(entry,LIST,value)
        for count,new,refs in itertools.product((0,1,4,9,17),(-1,0,1,4,8,20),(1,2)):
            retail.setup_objects(count,max(count,4),refs);compare(0x301ee0,LIST,new)
        for count,alias in itertools.product((0,1,4,9),(False,True)):
            retail.setup_objects(count,max(count,4));compare(0x301e90,LIST,LIST if alias else SECOND)
        for count,start,target in itertools.product((0,1,4,9),(-1,0,1,8),(0,RECORD,RECORD+0x100,RECORD+0x10000)):
            for entry in (0x302000,0x302100):
                retail.setup_objects(count,max(count,4),1)
                for i in range(count):retail.w(OLD+i*4,4,RECORD if i%2 else 0)
                retail.w(RECORD+4,4,count+1)
                compare(entry,*((OUT,LIST,target,start) if entry==0x302000 else (LIST,target,start)))
        for entry in (0x301c90,0x301d80,0x301ee0):
            retail.setup_objects(9,17,1);retail.clear_count=True;compare(entry,LIST,0)
        for count,descriptor,key in itertools.product((0,1,4,9,17),(0,DESC),(0,TEXT,TEXT+0x100,TEXT+0x10000)):
            retail.setup_objects(count,max(count,4));retail.text(TEXT+0x10000,b'missing');compare(0x3022c0,LIST,descriptor,key)
            retail.setup_objects(count,max(count,4));compare(0x302380,LIST,descriptor,key)
        retail.setup_objects(4,4);retail.relocate_lookup=True;compare(0x3022c0,LIST,DESC,TEXT+0x300)
        for count,key in itertools.product((0,1,2,3,4,9,17),(0,1,2,7,31,0x7fffffff,0x80000000,0xffffffff)):
            for entry in (0x302480,0x3023f0):
                retail.setup_objects(count,max(count,4));retail.w(DESC+8,4,16)
                keys=sorted([0,1,1,2,7,0x7fffffff,0x80000000,0xffffffff][i%8] for i in range(count))
                for i,value in enumerate(keys):retail.w(RECORD+i*0x100+16,4,value)
                compare(entry,LIST,DESC,C.c_int32(key).value)
        for entry in (0x302480,0x3023f0):retail.setup_objects(1,4);compare(entry,LIST,0,7)
        for pool,old,new,refs in itertools.product((0,0x1811000),(0,TEXT),(0,TEXT,TEXT+0x100),(0,1,2)):
            retail.setup_objects(1,4);retail.w(0x586f20,4,pool);retail.w(RECORD+8,4,old)
            retail.w(TEXT-4,4,refs);retail.w(TEXT+0x100-4,4,1);compare(0x2fecb0,RECORD,new)
        assert hits==set(ENTRIES),hits
    print(f'object lists retail: {cases} RAM/defined-return/ordered-call cases; all 13 bodies with real generic list operations; destruction/string/allocator/metadata/byte leaves controlled')
if __name__=='__main__':main()
