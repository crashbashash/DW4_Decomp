#!/usr/bin/env python3
"""Packed chunk allocation/free/coalescing vs original instructions.

Only allocator/delete remain controlled; tail service jumps are mediated after
their real delay slots. Full chunk and cross-chunk bodies execute retail code.
"""
import argparse,ctypes as C,subprocess,sys,tempfile
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'port/tools'))
from verify_scriptservices_retail import World
from ee_core import MASK
sys.path.insert(0,str(ROOT/'testing'))
from test_messenger_results_retail import Api,READ,WRITE,CALL
CHUNK,TABLE,POOL,ALLOC,VT,OUT=range(0x1800000,0x1800600,0x100)
BUFFER=0x1820000;ALLOC_CALL=0x1810000
ENTRIES=(0x30c740,0x30c760,0x30c770,0x30c7d0,0x30c830,0x30c9b0,
         0x30ca30,0x30ca40,0x30cb30,0x30cb80,0x30cce0,0x30cd00)
RETURNS={0x30c740,0x30c770,0x30c7d0,0x30c830,0x30ca40,0x30cb30,0x30cce0}
TAILS={0x30c754,0x30c760,0x30ca30,0x30ccf4,0x30cd00}
class Chunks(World):
    def __init__(self,image):super().__init__(image);self.descend=set(ENTRIES);self.events=[];self.allocations=0
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        assert e in (ALLOC_CALL,0x2ed460,0x2ed4b0),hex(e)
        self.events.append((e,*v[:2 if e==ALLOC_CALL else 1]))
        if e==ALLOC_CALL:
            result=0x1840000+self.allocations*0x10000;self.allocations+=1;return result
        return 0
    def step(self,pc,delay=False):
        if pc in TAILS:
            word=self.read(pc,4);target=((word&0x3ffffff)<<2) if word>>26==2 else self.r[(word>>21)&31]&0xffffffff
            super().step(pc+4,True);self.call_hook(target);return self.r[31]&0xffffffff
        return super().step(pc,delay)
    def setup(self,size=64,blocks=None,largest=-1):
        self.mem={};self.events=[];self.allocations=0
        self.w(CHUNK,4,TABLE);self.w(TABLE,4,POOL);self.w(POOL+12,4,ALLOC)
        self.w(ALLOC,4,VT);self.w(VT+216,4,ALLOC_CALL)
        self.w(CHUNK+12,4,size);self.w(CHUNK+16,4,BUFFER);self.w(CHUNK+20,4,BUFFER+size)
        self.w(CHUNK+28,4,largest);self.w(CHUNK+32,1,0)
        if blocks is None:blocks=[(0,size)]
        self.w(CHUNK+24,4,BUFFER+sum(blocks[0]) if blocks else 0)
        for i,(start,length) in enumerate(blocks):
            end=BUFFER+start+length
            following=BUFFER+sum(blocks[i+1]) if i+1<len(blocks) else 0
            self.w(end-2,2,length//4);self.w(end-4,2,(following-end)//4 if following else 0)
        self.w(OUT,4,0xa5a5a5a5);self.w(OUT+4,4,0x5a5a5a5a)
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=p.parse_args()
    image=args.elf.read_bytes();retail=Chunks(image);native=Chunks(image);errors=[];cases=0;hits=set()
    @CALL
    def call(_,e,values):
        try:return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-string-chunks-') as td:
        so=Path(td)/'chunks.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/string-chunks.c'),'-o',str(so)],check=True)
        fn=C.CDLL(str(so)).dw4_string_chunk;fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];fn.restype=C.c_uint64
        def compare(entry,*values):
            nonlocal cases
            native.mem=retail.mem.copy();native.allocations=retail.allocations;native.events=[];retail.events=[]
            expected=retail.invoke(entry,*values);actual=fn(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in values]))
            assert not errors,errors
            if entry in RETURNS:assert expected==actual,(hex(entry),values,expected,actual)
            expected_ram={p:v for p,v in retail.mem.items() if not 0x1ffe000<=p<0x1fff020}
            actual_ram={p:v for p,v in native.mem.items() if not 0x1ffe000<=p<0x1fff020}
            assert expected_ram==actual_ram,(hex(entry),values,[(hex(p),expected_ram.get(p),actual_ram.get(p)) for p in expected_ram.keys()|actual_ram.keys() if expected_ram.get(p)!=actual_ram.get(p)][:10])
            assert native.events==retail.events,(hex(entry),native.events,retail.events)
            cases+=1;hits.add(entry);return actual
        for size in (16,64,128,1024):
            for blocks in ([],[(0,size)],[(0,8),(16,8)],[(0,8),(16,size-16)]):
                for request in (4,8,12,16,32,64,128,size,size+4):
                    retail.setup(size,blocks);compare(0x30ca40,CHUNK,request)
        # Arbitrary release orders across a completely allocated chunk exercise
        # left, right and two-sided merging as well as head/non-head linkage.
        import itertools
        for order in itertools.permutations(range(4)):
            retail.setup(64,[],0)
            for index in order:compare(0x30cb80,CHUNK,BUFFER+index*16,16)
        for largest in (-1,0,8,64):
            retail.setup(64,[],largest);compare(0x30cb80,CHUNK,BUFFER,15)
        for flag in (0,1,0x8000,0x10001):
            for self in (0,CHUNK):retail.setup();compare(0x30c7d0,self,flag)
        for size in (16,64,16384):
            retail.setup(size);compare(0x30c770,CHUNK,0,TABLE,size)
            retail.setup(size);compare(0x30c9b0,CHUNK)
        for entry in (0x30c740,0x30cce0):retail.setup();compare(entry,36,ALLOC)
        for entry in (0x30c760,0x30ca30,0x30cd00):retail.setup();compare(entry,CHUNK)
        # Merge endpoint footers directly.
        retail.setup(64,[(0,16),(16,16)]);compare(0x30cb30,CHUNK,0,BUFFER+16,BUFFER+32)
        for size in (16,64,128):
            for request in (0,1,3,4,8,16,32,64,128):
                retail.setup(size);compare(0x30c830,CHUNK,request,OUT,OUT+4)
        assert hits==set(ENTRIES),hits
    print(f'string chunks retail: {cases} full RAM/return/call cases, all 12 bodies; splitting/exact fit/misses/coalescing/growth; allocator/delete leaves controlled')
if __name__=='__main__':main()
