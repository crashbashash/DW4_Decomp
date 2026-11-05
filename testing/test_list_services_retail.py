#!/usr/bin/env python3
"""List growth/mutation/search and reference bridges vs whole retail instructions.

Metadata/allocator/buffer-free, byte-copy/move/fill, comparator and string pool
are controlled leaves. Composed list logic and reference updates are real bodies.
"""
import argparse,ctypes as C,subprocess,sys,tempfile
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'port/tools'))
from verify_scriptservices_retail import World
from ee_core import MASK
sys.path.insert(0,str(ROOT/'testing'))
from test_messenger_results_retail import Api,READ,WRITE,CALL
LIST,OLD,SOURCE,KEY,VT,META,FIELD,FVT,TAG,NEW,TOKEN,OTHER=range(0x1800000,0x180c000,0x1000)
OLD,SOURCE,NEW=0x1880000,0x1840000,0x18c0000
STACK=0x1fff000
ENTRIES=(0x2d6670,0x2d6680,0x2d6790,0x2d6810,0x2d6900,0x2d69a0,
         0x2d6a20,0x2d6b20,0x2d6b80,0x2d6c60,0x2d6cf0,0x2d6d70,
         0x1c64e0,0x1ca620,0x301e30,0x30cdf0)
CLASS_CALL,UNIT_CALL,COMPARE=0x180d000,0x180d100,0x180d200
class Lists(World):
    def __init__(self,image):
        super().__init__(image);self.descend=set(ENTRIES);self.events=[];self.unit=4;self.allocate=True
    def setup(self,count,capacity,stride=4):
        self.mem={};self.events=[];self.unit=4 if stride%4==0 else 1
        self.w(LIST,4,VT);self.w(VT+88,4,CLASS_CALL);self.w(FIELD,4,FVT);self.w(FVT+100,4,UNIT_CALL)
        self.w(META+60,4,FIELD);self.w(0x5867a0,4,TAG);self.w(TAG+18,2,17)
        self.w(LIST+8,4,count);self.w(LIST+12,4,capacity);self.w(LIST+16,4,OLD)
        for i in range(capacity*stride):self.w(OLD+i,1,(i*23+7)&255)
        for i in range(128):self.w(SOURCE+i,1,(i*13+31)&255)
        self.w(TOKEN-8,4,0x180e000);self.w(TOKEN-4,4,2);self.w(TOKEN+4,4,2)
        self.w(OTHER-8,4,0x180e000);self.w(OTHER-4,4,1)
        self.w(0x586f20,4,0)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        n={CLASS_CALL:1,UNIT_CALL:1,0x2fdf00:2,0x301000:1,0x2fb190:5,
           0x127098:3,0x127148:3,0x12724c:3,0x300f50:2,COMPARE:2,
           0x2eb010:1,0x2eadf0:1,0x2eaf60:2,0x30c940:2}[e]
        self.events.append((e,*['temp' if STACK-0x1000<=x<STACK else x for x in v[:n]]))
        if e==CLASS_CALL:return META
        if e==UNIT_CALL:return self.unit
        if e==0x2fdf00:return META
        if e==0x301000:return 0x180f000
        if e==0x2fb190:
            self.w(v[2]+16,4,NEW);self.w(v[0],4,NEW);return 0
        if e in (0x127098,0x127148):
            assert v[2]<200000,'unbounded fixture copy'
            # Caller contract is checked separately from this byte-service leaf.
            data=bytes(self.read(v[1]+i,1) for i in range(v[2]))
            for i,b in enumerate(data):self.w(v[0]+i,1,b)
            return v[0]
        if e==0x12724c:
            assert v[2]<200000,'unbounded fixture fill'
            for i in range(v[2]):self.w(v[0]+i,1,v[1])
            return v[0]
        if e==COMPARE:
            left=self.read(v[0],4);right=self.read(v[1],4)
            return (left>right)-(left<right)
        if e==0x2eb010:return 0x1810000 if self.allocate else 0
        if e==0x2eadf0:return 0x1811000
        if e==0x2eaf60:return 0 if not v[1] else TOKEN
        if e in (0x300f50,0x30c940):return 0
        raise AssertionError(e)
def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=parser.parse_args()
    image=args.elf.read_bytes();retail=Lists(image);native=Lists(image);errors=[];cases=0;hits=set()
    @CALL
    def call(_,e,values):
        try:return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-lists-') as td:
        so=Path(td)/'lists.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/list-services.c'),'-o',str(so)],check=True)
        fn=C.CDLL(str(so)).dw4_list_service;fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        def compare(entry,*values):
            nonlocal cases
            native.mem=retail.mem.copy();native.events=[];retail.events=[];native.unit=retail.unit;native.allocate=retail.allocate
            wanted=retail.invoke(entry,*values)
            got=fn(C.byref(api),entry,(C.c_uint64*8)(*[v&MASK for v in values]),STACK-4)
            assert not errors,errors
            if entry in (0x2d6670,0x2d6a20,0x2d6d70):assert wanted==got,(hex(entry),wanted,got)
            expected={p:v for p,v in retail.mem.items() if not STACK-0x1000<=p<STACK+32}
            actual={p:v for p,v in native.mem.items() if not STACK-0x1000<=p<STACK+32}
            assert actual==expected,(hex(entry),values,[(hex(p),expected.get(p),actual.get(p)) for p in expected.keys()|actual.keys() if expected.get(p)!=actual.get(p)][:8])
            assert native.events==retail.events,(hex(entry),native.events,retail.events)
            cases+=1;hits.add(entry)
        for capacity in (0,1,4,5,8,1023,1024,1025):
            for target in (0,1,4,5,9,1024,1025,2049):
                for stride in (1,4,12,64):
                    retail.setup(min(capacity,2),capacity,stride);compare(0x2d6680,LIST,target,stride)
                    retail.setup(min(capacity,2),capacity,stride);compare(0x2d6790,LIST,target,stride)
        for count,capacity in ((0,0),(0,4),(2,4),(4,4),(9,9)):
            for index in (-1,0,count,count+1):
                for number in (-1,0,1,3):
                    for stride in (1,4,12):
                        for entry in (0x2d6810,0x2d6b80):
                            retail.setup(count,capacity,stride if entry==0x2d6810 else 4);compare(entry,LIST,index,number,SOURCE,stride)
                    for entry in (0x2d69a0,0x2d6cf0):
                        retail.setup(count,capacity);compare(entry,LIST,index,4)
            for number in (-1,0,1,3):
                for entry in (0x2d6900,0x2d6c60):
                    retail.setup(count,capacity);compare(entry,LIST,number,SOURCE,4)
            retail.setup(count,capacity);compare(0x2d6b20,LIST,0x80000001)
            retail.setup(count,capacity);compare(0x301e30,LIST,TOKEN)
        for count in (0,1,2,3,8,9,17):
            for target in (0,1,2,7,17,31):
                for entry in (0x2d6a20,0x2d6d70):
                    retail.setup(count,count,4)
                    for i in range(count):retail.w(OLD+i*4,4,i*2)
                    retail.w(KEY,4,target);compare(entry,LIST,KEY,COMPARE,4)
        for unit in (1,2,4,8,0x10004):
            retail.setup(2,4,8);retail.unit=unit;compare(0x2d6680,LIST,9,8)
        for target in (0,1,9):
            retail.setup(0,0);retail.w(LIST+16,4,0);compare(0x2d6680,LIST,target,4)
        for entry in (0x2d6a20,0x2d6d70):
            for target in (0,2,4,6):
                retail.setup(8,8)
                for i in range(8):retail.w(OLD+i*4,4,(i//2)*2)
                retail.w(KEY,4,target);compare(entry,LIST,KEY,COMPARE,4)
        for count in (0,1,2,8,9):
            for target in (0,1,2,9,17):
                retail.setup(count,max(count,4))
                for i in range(max(count,4)):retail.w(OLD+i*4,4,TOKEN if i%2==0 else OTHER)
                compare(0x30cdf0,LIST,target)
            for value in (0,TOKEN):
                retail.setup(count,max(count,4));retail.w(SOURCE,4,value);compare(0x1ca620,LIST,SOURCE)
            for index in (0,count):
                retail.setup(count,max(count,4));retail.w(OLD+index*4,4,TOKEN);compare(0x1c64e0,SOURCE,LIST,index)
        retail.setup(0,0);compare(0x2d6670,LIST)
        retail.setup(0,4);retail.w(OLD,4,TOKEN);compare(0x1ca620,LIST,OLD)
        retail.setup(2,4);retail.w(OLD,4,TOKEN);retail.w(OLD+4,4,OTHER)
        compare(0x1c64e0,OLD,LIST,1)
        assert hits==set(ENTRIES),hits
    print(f'list services retail: {cases} full RAM/call/return cases cover all 16 bodies; metadata/allocation/byte/string/comparator leaves controlled')
if __name__=='__main__':main()
