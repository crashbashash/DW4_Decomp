#!/usr/bin/env python3
"""All 32 messenger result bodies vs retail RAM, return registers and call order.

List metadata, allocator/delete/byte and synchronization services are controlled
leaves. List, matrix, pool, table and packed chunk bodies execute recovered C.
"""
import argparse,ctypes as C,subprocess,sys,tempfile
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'port/tools'))
from verify_scriptservices_retail import World
from ee_core import MASK
SELF,CONTEXT,SOURCE,OUTPUT,OBJECT,STRING=range(0x1800000,0x1800600,0x100)
STORAGE=0x19a0000
STRING=STORAGE+8
STACK=0x1fff000
VT,META,FIELD,FVT,TAG=range(0x18b1000,0x18b1500,0x100)
CLASS_CALL,UNIT_CALL=0x18b0100,0x18b0200
LIST_ENTRIES={0x2d6680,0x2d6790,0x2d6b20,0x301e30,0x30cdf0,0x1ca620,0x1c64e0}
POOL_ADDR,POOL_TABLE,POOL_ALLOC,POOL_VT,POOL_BUFFER,POOL_CHUNK,POOL_FRESH=range(0x1980000,0x1987000,0x1000)
POOL_ALLOC_CALL=0x1988000
POOL_ENTRIES={0x2eadf0,0x2eaf60,0x30c0c0,0x30c240,0x30c2d0,0x30c390,
              0x30c430,0x30c500,0x30c600,0x30c670,0x30c940}
CHUNK_ENTRIES={0x30c740,0x30c760,0x30c770,0x30c7d0,0x30c830,0x30c9b0,
               0x30ca30,0x30ca40,0x30cb30,0x30cb80,0x30cce0,0x30cd00}
TAILS={0x30c754,0x30c760,0x30ca30,0x30ccf4,0x30cd00}
READ=C.CFUNCTYPE(C.c_uint64,C.c_void_p,C.c_uint32,C.c_uint)
WRITE=C.CFUNCTYPE(None,C.c_void_p,C.c_uint32,C.c_uint,C.c_uint64)
CALL=C.CFUNCTYPE(C.c_uint64,C.c_void_p,C.c_uint32,C.POINTER(C.c_uint64))
class Api(C.Structure):
    _fields_=[('user',C.c_void_p),('read',READ),('write',WRITE),('call',CALL)]
MREAD=C.CFUNCTYPE(C.c_uint32,C.c_void_p,C.c_uint32)
MWRITE=C.CFUNCTYPE(None,C.c_void_p,C.c_uint32,C.c_uint32)
class MatrixApi(C.Structure):
    _fields_=[('user',C.c_void_p),('read',MREAD),('write',MWRITE)]
ENTRIES=(0x38f0e0,0x38f0f0,0x38f100,0x38f150,0x38f1d0,0x38f1e0,0x38f220,
         0x38f240,0x38f250,0x38f2d0,0x38f2e0,0x38f320,0x38f340,0x38f350,
         0x38f3d0,0x38f3f0,0x38f400,0x38f480,0x38f4a0,0x38f4b0,0x38f550,
         0x38f560,0x38f5a0,0x38f5b0,0x38f630,0x38f660,0x38f670,0x38f690,
         0x38f800,0x38f820,0x38f830,0x38f8f0)
GETTERS={0x38f0f0,0x38f220,0x38f240,0x38f320,0x38f340,0x38f3d0,0x38f3f0,
         0x38f480,0x38f4a0,0x38f5a0,0x38f660,0x38f800,0x38f820,0x38f8f0}
class Results(World):
    def __init__(self,image):
        super().__init__(image);self.descend=set(ENTRIES)|{0x1908f0}|LIST_ENTRIES|POOL_ENTRIES;self.events=[];self.allocation=True;self.clear_on_destroy=False
        self.real_chunks=True;self.chunk_objects=1;self.chunk_buffers=1
    def step(self,pc,delay=False):
        if self.real_chunks and pc in TAILS:
            word=self.read(pc,4);target=((word&0x3ffffff)<<2) if word>>26==2 else self.r[(word>>21)&31]&0xffffffff
            super().step(pc+4,True);self.call_hook(target);return self.r[31]&0xffffffff
        return super().step(pc,delay)
    def text(self,p,value):
        for i,b in enumerate(value+b'\0'):self.w(p+i,1,b)
    def string(self,p):
        data=[]
        while self.read(p,1):data.append(self.read(p,1));p+=1
        return bytes(data)
    def invoke(self,entry,*args,f12=0):
        covered=self.covered;self.ee_reset();self.covered=covered
        self.r[4:4+len(args)]=[v&MASK for v in args];self.f[12]=f12
        self.r[28],self.r[29],self.r[31]=0x55c870,STACK,0xfffffff0
        self.run_until(entry,0xfffffff0)
        return self.f[0] if entry==0x38f3d0 else self.r[2]
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==0x1908f0:
            self.matrix_copy(C.byref(self.matrix_api),v[0],v[1]);return 0
        if e in LIST_ENTRIES:
            # Nested list allocation must not overwrite the outer string token
            # temporary at sp-4. Retail has separate frames for these owners.
            return self.list_function(C.byref(self.list_api),e,(C.c_uint64*8)(*args),STACK-0x800)
        if e in POOL_ENTRIES:
            return self.pool_function(C.byref(self.list_api),e,(C.c_uint64*8)(*args),STACK-0xc00)
        if self.real_chunks and e in CHUNK_ENTRIES:
            return self.chunk_function(C.byref(self.list_api),e,(C.c_uint64*8)(*args))
        n={0x2ff820:1,0x2eb010:1,0x2eadf0:1,0x2eaf60:2,0x30c940:2,
           CLASS_CALL:1,UNIT_CALL:1,0x2fdf00:2,0x301000:1,0x2fb190:5,
           0x127098:3,0x12724c:3,0x300f50:2,0x2f88e0:1,0x2f00d0:0,
           0x30c740:2,0x30cce0:2,POOL_ALLOC_CALL:2,0x30c770:4,
           0x12a4a4:2,0x12a78c:1,0x30c830:4,0x127148:3,0x2ed330:2,
           0x30cb80:3,0x30c7d0:2,0x2ed460:1,0x2ed4b0:1}[e]
        # Reference-copy helpers receive stack addresses for their temporary.
        normalized=[('temp' if STACK-0x1000<=x<STACK else x) for x in v[:n]]
        self.events.append((e,*normalized))
        if e==CLASS_CALL:return META
        if e==UNIT_CALL:return 1
        if e==0x2fdf00:return META
        if e==0x301000:return 0x18b1500
        if e==0x2fb190:
            slot=(v[2]-0x1810000)//0x100
            new=0x18d0000+(slot-16)*0x1000
            self.w(v[2]+16,4,new);self.w(v[0],4,new);return 0
        if e==0x127098:
            data=bytes(self.read(v[1]+i,1) for i in range(v[2]))
            for i,b in enumerate(data):self.w(v[0]+i,1,b)
            return v[0]
        if e==0x12724c:
            for i in range(v[2]):self.w(v[0]+i,1,v[1])
            return v[0]
        if e==0x300f50:return 0
        if e==0x2eb010:return 0x181f000 if self.allocation else 0
        if e in (0x2f88e0,0x2f00d0):return POOL_ALLOC
        if e==0x30c740:return POOL_TABLE
        if e==0x30cce0:return POOL_CHUNK
        if e==POOL_ALLOC_CALL:
            if self.real_chunks:
                if v[1]==24:return POOL_TABLE
                if v[1]==36:
                    value=POOL_CHUNK+self.chunk_objects*0x100;self.chunk_objects+=1;return value
                if v[1]==4096:return POOL_BUFFER
                value=STORAGE+self.chunk_buffers*0x10000;self.chunk_buffers+=1;return value
            return POOL_BUFFER
        if e==0x30c770:self.w(v[0],4,v[2]);self.w(v[0]+4,4,0);self.w(v[0]+8,4,v[1]);return v[0]
        if e==0x12a78c:return len(self.string(v[0]))
        if e==0x12a4a4:
            left=self.string(v[0]);right=self.string(v[1]);return (left>right)-(left<right)
        if e==0x30c830:
            self.w(v[2],4,POOL_CHUNK);self.w(v[3],4,POOL_FRESH);return POOL_FRESH+8
        if e==0x127148:
            assert v[2]<10000,('invalid fixture movement',hex(e),v[:3])
            data=bytes(self.read(v[1]+i,1) for i in range(v[2]))
            for i,b in enumerate(data):self.w(v[0]+i,1,b)
            return v[0]
        if e==0x2ed330:
            new=POOL_BUFFER+0x400
            for i in range(self.read(POOL_TABLE+12,4)*4):self.w(new+i,1,self.read(v[0]+i,1))
            return new
        if e==0x30cb80:self.w(v[0]+32,1,1);return 0
        if e==0x30c7d0:self.w(v[0]+32,1,0xde);return 0
        if e in (0x2ed460,0x2ed4b0):return 0
        if e==0x2ff820 and self.clear_on_destroy:
            self.w(self.read(CONTEXT+40,4)+8,4,0)
        if e in (0x2ff820,0x30c940):return 0
        raise AssertionError(e)
    def setup(self,count,capacity,refs=2):
        self.mem={};self.events=[];self.w(SELF+16,4,CONTEXT)
        self.chunk_objects=self.chunk_buffers=1
        self.w(VT+88,4,CLASS_CALL);self.w(META+60,4,FIELD);self.w(FIELD,4,FVT)
        self.w(FVT+100,4,UNIT_CALL);self.w(0x5867a0,4,TAG);self.w(TAG+18,2,17)
        for slot,width in zip(range(16,48,4),(1,4,4,8,12,64,4,4)):
            items=0x1810000+slot*0x100
            buffer=0x1850000+(slot-16)*0x1000
            self.w(CONTEXT+slot,4,items);self.list(items,[]);self.w(items+8,4,count);self.w(items+12,4,capacity)
            self.w(items,4,VT);self.w(items+16,4,buffer)
            for i in range(max(20,count+2)*width):self.w(buffer+i,1,(i*37+slot)&255)
            if slot in (40,44):
                for i in range(max(20,count+2)):self.w(buffer+i*4,4,(OBJECT if slot==40 else STRING) if i%2==0 else 0)
        self.w(OBJECT+4,4,refs);self.w(STRING-4,4,refs);self.w(STRING-8,4,0x181f200)
        self.text(STRING,b'known');self.w(STRING-8,4,POOL_CHUNK)
        self.w(POOL_ADDR,4,POOL_TABLE);self.w(POOL_ADDR+4,4,POOL_CHUNK);self.w(POOL_ADDR+8,4,16384);self.w(POOL_ADDR+12,4,POOL_ALLOC)
        self.w(POOL_ALLOC,4,POOL_VT);self.w(POOL_VT+216,4,POOL_ALLOC_CALL)
        self.w(POOL_TABLE,4,POOL_ADDR);self.w(POOL_TABLE+4,4,1);self.w(POOL_TABLE+8,4,1);self.w(POOL_TABLE+12,4,4);self.w(POOL_TABLE+16,4,POOL_BUFFER)
        self.w(POOL_BUFFER,4,STRING-8);self.w(POOL_CHUNK,4,POOL_TABLE);self.w(POOL_CHUNK+4,4,0)
        self.w(POOL_CHUNK+8,4,0);self.w(POOL_CHUNK+12,4,16384)
        self.w(POOL_CHUNK+16,4,STORAGE);self.w(POOL_CHUNK+20,4,STORAGE+16384)
        self.w(POOL_CHUNK+24,4,STORAGE+16384);self.w(POOL_CHUNK+28,4,0xffffffff)
        self.w(STORAGE+16384-4,2,0);self.w(STORAGE+16384-2,2,(16384-16)//4)
        self.w(0x5871c8,4,0)
        for i in range(16):self.w(SOURCE+i*4,4,0x80000000+i*0x10203)
        self.w(0x586f20,4,POOL_ADDR)

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=parser.parse_args()
    image=args.elf.read_bytes();retail=Results(image);native=Results(image);errors=[];cases=0;hits=set()
    @CALL
    def call(_,e,values):
        try:return native.call(e,list(values[:8]))
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-results-') as td:
        so=Path(td)/'results.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/messenger-results.c'),str(ROOT/'recovered/engine/list-services.c'),str(ROOT/'recovered/engine/string-pool.c'),str(ROOT/'recovered/engine/string-chunks.c'),str(ROOT/'recovered/engine/matrix-primitives.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));fn=lib.dw4_messenger_result;fn.argtypes=[C.POINTER(Api),C.c_uint32]+[C.c_uint64]*3+[C.c_uint32]*2;fn.restype=C.c_uint64
        native.list_api=api;native.list_function=lib.dw4_list_service
        native.list_function.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];native.list_function.restype=C.c_uint64
        native.pool_function=lib.dw4_string_pool
        native.pool_function.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];native.pool_function.restype=C.c_uint64
        native.chunk_function=lib.dw4_string_chunk
        native.chunk_function.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];native.chunk_function.restype=C.c_uint64
        mread=MREAD(lambda _,p:native.read(p,4));mwrite=MWRITE(lambda _,p,v:native.write(p,4,v))
        native.matrix_api=MatrixApi(None,mread,mwrite);native.matrix_copy=lib.dw4_matrix_copy
        native.matrix_copy.argtypes=[C.POINTER(MatrixApi),C.c_uint32,C.c_uint32];native.matrix_copy.restype=None
        def compare(entry,a0=SELF,a1=0,a2=0,f12=0):
            nonlocal cases
            native.mem=retail.mem.copy();native.events=[];retail.events=[];native.allocation=retail.allocation
            native.clear_on_destroy=retail.clear_on_destroy
            native.real_chunks=retail.real_chunks;native.chunk_objects=retail.chunk_objects;native.chunk_buffers=retail.chunk_buffers
            if retail.real_chunks:retail.descend.update(CHUNK_ENTRIES)
            else:retail.descend.difference_update(CHUNK_ENTRIES)
            # String temporary is sp-4 in both append and borrowed getter.
            wanted=retail.invoke(entry,a0,a1,a2,f12=f12)
            got=fn(C.byref(api),entry,a0&MASK,a1&MASK,a2&MASK,f12,STACK-4)
            assert not errors,errors
            if entry in GETTERS:assert wanted==got,(hex(entry),wanted,got)
            expected={p:v for p,v in retail.mem.items() if not STACK-0x1000<=p<STACK+32}
            actual={p:v for p,v in native.mem.items() if not STACK-0x1000<=p<STACK+32}
            assert actual==expected,(hex(entry),[(hex(p),expected.get(p),actual.get(p)) for p in actual.keys()|expected.keys() if actual.get(p)!=expected.get(p)][:10])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            hits.add(entry);cases+=1
        for count,capacity in ((0,0),(0,3),(2,3),(3,3),(8,8),(9,17),(17,17)):
            for value in (0,1,255,0xffffffff,0x8000000080000001):
                for entry in ENTRIES:
                    retail.setup(count,capacity)
                    arg=value;index=(value&3)-1
                    if entry==0x38f100:compare(entry,a1=C.c_int32(value&0xffffffff).value)
                    elif entry==0x38f670:compare(entry,a1=OBJECT if value else 0)
                    elif entry==0x38f830:compare(entry,a1=STRING if value else 0)
                    elif entry in (0x38f1e0,0x38f2e0):compare(entry,a1=index,a2=value)
                    elif entry in (0x38f560,0x38f630):compare(entry,a0=OUTPUT,a1=SELF,a2=index)
                    elif entry in (0x38f4b0,0x38f5b0):compare(entry,a1=SOURCE)
                    elif entry in (0x38f8f0,0x38f320,0x38f220,0x38f3d0,0x38f480,0x38f800):compare(entry,a1=index)
                    else:compare(entry,a1=arg,f12=value&0xffffffff)
        for refs in (0,1,2,0x800001,0x800002,0xffffffff):
            for count in (0,1,2,8,9,17):
                retail.setup(count,count,refs);compare(0x38f690)
        for pool in (0,POOL_ADDR):
            for allocation in (True,False):
                for value in (0,STRING):
                    retail.setup(0,4);retail.w(0x586f20,4,pool);retail.allocation=allocation
                    # Preserve the previously declared upper-layer null-pool
                    # failure case without inventing an allocator failure policy.
                    retail.real_chunks=bool(pool or allocation or not value)
                    compare(0x38f830,a1=value)
        retail.real_chunks=True
        for refs in (0,1,0x800001,0xfffffffe,0xffffffff):
            retail.setup(0,4,refs);compare(0x38f830,a1=STRING)
            retail.setup(1,4,refs);compare(0x38f8f0,a1=0)
        retail.clear_on_destroy=True
        for count in (1,8,9,17):
            retail.setup(count,count,1);compare(0x38f690)
        retail.clear_on_destroy=False
        # Persistent fresh allocation -> cached append -> retained getter,
        # including requests that exhaust and grow the initial packed chunk.
        text_pointer=0x1830000
        for length in (0,1,7,63,16375,16385):
            retail.setup(0,4);retail.text(text_pointer,b'x'*length)
            compare(0x38f830,a1=text_pointer)
            compare(0x38f830,a1=text_pointer)
            compare(0x38f8f0,a1=0)
        assert hits==set(ENTRIES),hits
    print(f'messenger results retail: {cases} return/RAM/ordered-call cases cover all 32 bodies with real list/matrix/pool/table/chunk services; one upper-layer null-pool failure retains its controlled chunk boundary')
if __name__=='__main__':main()
