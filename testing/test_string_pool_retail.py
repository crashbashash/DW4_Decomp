#!/usr/bin/env python3
"""Whole public pool + ordered table lifecycle against original EE instructions.

Allocator/chunk/byte comparison-copy-length/synchronization leaves are controlled.
Fifteen engine bodies, header refs, ordered slots and global publication are real.
"""
import argparse,ctypes as C,subprocess,sys,tempfile
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'port/tools'))
from verify_scriptservices_retail import World
from ee_core import MASK
sys.path.insert(0,str(ROOT/'testing'))
from test_messenger_results_retail import Api,READ,WRITE,CALL
from test_string_chunks_retail import ENTRIES as CHUNK_ENTRIES,TAILS
POOL,TABLE,ALLOC,AVT,MUTEX,MVT,CHUNK,CHUNK2,INPUT,OUT,BUFFER,REBUFFER,FRESH=range(0x1800000,0x180d000,0x1000)
STACK=0x1fff000
ALLOC_CALL,INIT_CALL,LOCK_CALL,UNLOCK_CALL=range(0x1810000,0x1810400,0x100)
ENTRIES=(0x2eadf0,0x2eaec0,0x2eaf20,0x2eaf60,0x30c0c0,0x30c120,0x30c180,
         0x30c240,0x30c2d0,0x30c390,0x30c430,0x30c500,0x30c600,0x30c670,0x30c940)
RETURNS={0x2eadf0,0x2eaec0,0x2eaf60,0x30c0c0,0x30c120,0x30c240,0x30c2d0,0x30c500}
class Pool(World):
    def __init__(self,image):
        super().__init__(image);self.descend=set(ENTRIES);self.events=[];self.fail_table=False;self.fail_chunk=False;self.fallback=ALLOC
        self.real_chunks=False;self.chunk_objects=0;self.chunk_buffers=0
    def step(self,pc,delay=False):
        if self.real_chunks and pc in TAILS:
            word=self.read(pc,4);target=((word&0x3ffffff)<<2) if word>>26==2 else self.r[(word>>21)&31]&0xffffffff
            super().step(pc+4,True);self.call_hook(target);return self.r[31]&0xffffffff
        return super().step(pc,delay)
    def string(self,p):
        data=[]
        while self.read(p,1):data.append(self.read(p,1));p+=1
        return bytes(data)
    def text(self,p,value):
        for i,b in enumerate(value+b'\0'):self.w(p+i,1,b)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if self.real_chunks and e in CHUNK_ENTRIES:
            return self.chunk_function(C.byref(self.chunk_api),e,(C.c_uint64*8)(*args))
        n={0x2f88e0:1,0x2f00d0:0,0x30c740:2,0x30cce0:2,ALLOC_CALL:2,
           0x30c770:4,0x30c7d0:2,0x2eb050:1,0x2ed460:1,0x30c760:1,
           0x2f8a20:0,0x2ba650:1,0x2ff820:1,INIT_CALL:2,LOCK_CALL:3,UNLOCK_CALL:2,
           0x12a4a4:2,0x12a78c:1,0x30c830:4,0x127098:3,0x127148:3,
           0x2ed330:2,0x30cb80:3,0x2ed4b0:1}[e]
        self.events.append((e,*['temp' if STACK-0x1000<=x<STACK else x for x in v[:n]]))
        if e==0x2f88e0:return self.fallback
        if e in (0x2f00d0,0x2f8a20):return ALLOC
        if e==0x30c740:return 0 if self.fail_table else TABLE
        if e==0x30cce0:return 0 if self.fail_chunk else CHUNK
        if e==ALLOC_CALL:
            if self.real_chunks:
                if v[1]==24:return TABLE
                if v[1]==36:
                    value=CHUNK+self.chunk_objects*0x100;self.chunk_objects+=1;return value
                if v[1]==4096:return BUFFER
                value=0x1830000+self.chunk_buffers*0x10000;self.chunk_buffers+=1;return value
            return BUFFER
        if e==0x30c770:
            self.w(v[0],4,v[2]);self.w(v[0]+4,4,0);self.w(v[0]+8,4,v[1]);return v[0]
        if e==0x30c7d0:self.w(v[0]+32,1,0xde);return v[0]
        if e in (0x2eb050,0x2ed460,0x2ed4b0,0x30c760,0x2ff820,0x30cb80):return 0
        if e==0x2ba650:return MUTEX
        if e in (INIT_CALL,LOCK_CALL,UNLOCK_CALL):self.w(v[0],4,v[1]);return 0
        if e==0x12a4a4:
            left=self.string(v[0]);right=self.string(v[1]);return (left>right)-(left<right)
        if e==0x12a78c:return len(self.string(v[0]))
        if e==0x30c830:
            self.w(v[2],4,CHUNK);self.w(v[3],4,FRESH);return FRESH+8
        if e in (0x127098,0x127148):
            assert v[2]<10000,'invalid pool fixture movement'
            data=bytes(self.read(v[1]+i,1) for i in range(v[2]))
            for i,b in enumerate(data):self.w(v[0]+i,1,b)
            return v[0]
        if e==0x2ed330:
            for i in range(self.read(TABLE+12,4)*4):self.w(REBUFFER+i,1,self.read(v[0]+i,1))
            return REBUFFER
        raise AssertionError(e)
    def setup(self,words=(),capacity=8,mutex=0):
        self.mem={};self.events=[];self.fail_table=self.fail_chunk=False;self.fallback=ALLOC
        self.chunk_objects=self.chunk_buffers=0
        self.w(POOL,4,TABLE);self.w(POOL+4,4,CHUNK);self.w(POOL+8,4,16384);self.w(POOL+12,4,ALLOC)
        self.w(ALLOC,4,AVT);self.w(AVT+216,4,ALLOC_CALL)
        self.w(TABLE,4,POOL);self.w(TABLE+4,4,len(words));self.w(TABLE+12,4,capacity);self.w(TABLE+16,4,BUFFER)
        step=0
        if words:step=1<<(len(words).bit_length()-1)
        self.w(TABLE+8,4,step);self.w(TABLE+20,4,0)
        self.w(CHUNK,4,TABLE);self.w(CHUNK+4,4,CHUNK2);self.w(CHUNK+8,4,0);self.w(CHUNK2,4,TABLE);self.w(CHUNK2+4,4,0);self.w(CHUNK2+8,4,CHUNK)
        self.w(MUTEX,4,MVT);self.w(MUTEX+4,4,1)
        for off,fn in ((92,INIT_CALL),(132,LOCK_CALL),(124,UNLOCK_CALL)):self.w(MVT+off,4,fn)
        self.w(0x5871c8,4,mutex);self.w(0x554c14,1,0)
        for i,word in enumerate(words):
            header=0x1820000+i*0x100;self.w(header,4,CHUNK);self.w(header+4,4,2);self.text(header+8,word);self.w(BUFFER+i*4,4,header)
        self.w(OUT,4,0xabcdef);self.w(OUT+4,4,0x987654)
        self.w(FRESH,4,0);self.w(FRESH+4,4,0);self.text(FRESH+8,b'new')
def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=parser.parse_args()
    image=args.elf.read_bytes();retail=Pool(image);native=Pool(image);errors=[];cases=0;hits=set()
    @CALL
    def call(_,e,values):
        try:return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-string-pool-') as td:
        so=Path(td)/'pool.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/string-pool.c'),str(ROOT/'recovered/engine/string-chunks.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));fn=lib.dw4_string_pool;fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        native.chunk_api=api;native.chunk_function=lib.dw4_string_chunk
        native.chunk_function.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];native.chunk_function.restype=C.c_uint64
        def compare(entry,*values):
            nonlocal cases
            native.mem=retail.mem.copy();native.events=[];retail.events=[]
            for name in ('fail_table','fail_chunk','fallback','real_chunks','chunk_objects','chunk_buffers'):setattr(native,name,getattr(retail,name))
            wanted=retail.invoke(entry,*values);got=fn(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in values]),STACK-0x800)
            assert not errors,errors
            if entry in RETURNS:assert wanted==got,(hex(entry),wanted,got)
            expected={p:v for p,v in retail.mem.items() if not STACK-0x1000<=p<STACK+32}
            actual={p:v for p,v in native.mem.items() if not STACK-0x1000<=p<STACK+32}
            assert expected==actual,(hex(entry),values,[(hex(p),expected.get(p),actual.get(p)) for p in expected.keys()|actual.keys() if expected.get(p)!=actual.get(p)][:8])
            assert native.events==retail.events,(hex(entry),native.events,retail.events)
            cases+=1;hits.add(entry)
            return got
        for count in (0,1,2,3,4,7,8,9,16,17):
            words=[f'{i*2:03}'.encode() for i in range(count)]
            for query in (b'',b'000',b'001',b'006',b'015',b'032',b'zzz'):
                for mutex in (0,MUTEX):
                    for entry in (0x30c500,0x30c240,0x2eaf60):
                        retail.setup(words,max(1,count),mutex);retail.text(INPUT,query)
                        if entry==0x30c500:compare(entry,TABLE,INPUT,OUT,OUT+4)
                        elif entry==0x30c240:compare(entry,TABLE,INPUT)
                        else:compare(entry,POOL,INPUT)
        for count in (0,1,2,3,4,7,8):
            for index in range(count+1):
                retail.setup([b'aaa']*count,max(1,count));compare(0x30c670,TABLE,FRESH,index)
            for index in range(count):
                retail.setup([b'aaa']*count,max(1,count));compare(0x30c600,TABLE,index)
        for mutex in (0,MUTEX):
            retail.setup([b'aaa',b'new',b'zzz'],8,mutex);compare(0x30c390,TABLE,0x1820100)
            retail.setup([b'aaa',b'zzz'],8,mutex);compare(0x30c2d0,TABLE,FRESH,CHUNK,FRESH+8)
            for counter in (0,1):
                for chunk in (CHUNK,CHUNK2):
                    retail.setup([],8,mutex);retail.w(TABLE+20,4,counter);compare(0x30c430,TABLE,chunk)
            retail.setup([b'aaa'],8,mutex);compare(0x30c940,CHUNK,0x1820000)
        for flag in (0,1):
            for fallback in (0,ALLOC):
                for failure in ('none','table','chunk'):
                    retail.setup();retail.w(0x554c14,1,flag);retail.fallback=fallback
                    retail.fail_table=failure=='table';retail.fail_chunk=failure=='chunk';compare(0x2eadf0,POOL)
        for flag in (0,1):
            for existing in (0,MUTEX):
                for request in (0,1,2):
                    retail.setup(mutex=existing);retail.w(0x554c14,1,flag);compare(0x30c180,request)
        for deletion in (0,1,0x8000,0x10001):
            for self in (0,POOL):
                retail.setup();compare(0x2eaec0,self,deletion)
            retail.setup();compare(0x30c120,TABLE,deletion)
        retail.setup();compare(0x2eaf20,POOL)
        retail.setup();compare(0x2eaf60,POOL,0)
        retail.setup();compare(0x30c0c0,TABLE,POOL,8)
        for mutex in (0,MUTEX):
            # Persistent miss -> cache hit -> final removal, with real header
            # reference changes and ordered slots across successive invocations.
            retail.setup([],8,mutex);retail.text(INPUT,b'again')
            compare(0x2eaf60,POOL,INPUT);compare(0x2eaf60,POOL,INPUT)
            retail.w(FRESH+4,4,0);compare(0x30c940,CHUNK,FRESH)
            retail.setup([b'aaa',b'new',b'zzz'],8,mutex)
            # Registration ignores search's found flag: equal text still adds
            # another header, and the existing header receives the search retain.
            compare(0x30c2d0,TABLE,FRESH,CHUNK,FRESH+8)
        # Additional valid lifecycle runs compose actual chunk construction,
        # allocation and coalescing. Earlier failure tests retain their declared
        # chunk-constructor boundary; allocator failure policy remains separate.
        retail.real_chunks=True;retail.descend.update(CHUNK_ENTRIES)
        for mutex in (0,MUTEX):
            retail.setup([],8,mutex);compare(0x2eadf0,POOL)
            retail.text(INPUT,b'live');token=compare(0x2eaf60,POOL,INPUT)
            compare(0x2eaf60,POOL,INPUT);retail.w(token-4,4,0)
            compare(0x30c940,CHUNK,token-8);compare(0x2eaec0,POOL,1)
        assert hits==set(ENTRIES),hits
    print(f'string pool retail: {cases} whole RAM/return/call cases, all 15 bodies, 10 real-chunk lifecycle calls; allocator/byte/sync leaves controlled on those routes')
if __name__=='__main__':main()
