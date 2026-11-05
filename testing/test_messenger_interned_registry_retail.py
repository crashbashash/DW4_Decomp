#!/usr/bin/env python3
"""Cold messenger registry through real pool/table/chunk interning and results.

Concrete fields/registrars, allocation, bytes and synchronization remain leaves.
All stored fixture names are seeded through the original interning bodies.
"""
import argparse,ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
from test_messenger_registry_retail import Registry,OBJECTS,CREATION,MEMORY,GENERIC,LIFE,DISPATCH,MSG,ROOT,STACK,MASK,Api,READ,WRITE,CALL,REG,NAMES,RECORD,BASE
from test_string_pool_retail import ENTRIES as POOL_ENTRIES
from test_string_chunks_retail import ENTRIES as CHUNKS,TAILS
POOL,TABLE,ALLOC,AVT,MUTEX,MVT,POOL_ALLOC_CALL,INIT,LOCK,UNLOCK=range(0x19b0000,0x19b0a00,0x100)
CHUNK=0x19b1000;ARRAY=0x1d00000;STORAGE=0x1c00000
POOL_PROVIDER,SYNC_PROVIDER=0x19b0e00,0x19b0f00
STRING_RESULTS=(0x38f820,0x38f830,0x38f8f0)
class InternedRegistry(Registry):
    def __init__(self,image):
        super().__init__(image);self.descend|=set(POOL_ENTRIES)|set(CHUNKS)|set(STRING_RESULTS)
        self.chunk_objects=0;self.chunk_buffers=0;self.reallocations=0
        self.w(ALLOC,4,AVT);self.w(AVT+216,4,POOL_ALLOC_CALL)
        self.w(MUTEX,4,MVT);self.w(MUTEX+4,4,1)
        for slot,fn in ((92,INIT),(132,LOCK),(124,UNLOCK)):self.w(MVT+slot,4,fn)
        self.w(0x587048,4,POOL_PROVIDER);self.w(0x587038,4,SYNC_PROVIDER);self.w(0x5871c8,4,0)
        self.w(0x586f20,4,0)
        self.seed_group=self.read(RECORD+8,4);self.w(RECORD+8,4,0)
        self.seed_names=self.values(NAMES)
        for i in range(len(self.seed_names)):self.w(self.read(NAMES+16,4)+i*4,4,0)
    def step(self,pc,delay=False):
        if pc in TAILS:
            word=self.read(pc,4);target=((word&0x3ffffff)<<2) if word>>26==2 else self.r[(word>>21)&31]&0xffffffff
            super().step(pc+4,True);self.call_hook(target);return self.r[31]&0xffffffff
        return super().step(pc,delay)
    def text(self,p,value):
        for i,b in enumerate(value+b'\0'):self.w(p+i,1,b)
    def string(self,p):
        data=[]
        while self.read(p,1):data.append(self.read(p,1));p+=1
        return bytes(data)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==0x2eb010:self.events.append((e,v[0]));return POOL
        if e==0x2f00d0:self.events.append((e,));return ALLOC
        if e==0x2f88e0 and v[0] in (POOL_PROVIDER,SYNC_PROVIDER):self.events.append((e,v[0]));return ALLOC
        if e==0x2f8a20:self.events.append((e,));return ALLOC
        if e==0x2ba650:self.events.append((e,v[0]));return MUTEX
        if e in (INIT,LOCK,UNLOCK):
            n=3 if e==LOCK else 2
            self.events.append((e,*['temp' if STACK-0x7000<=p<STACK else p for p in v[:n]]));self.w(v[0],4,v[1]);return 0
        if e==POOL_ALLOC_CALL:
            self.events.append((e,*v[:2]))
            if v[1]==24:return TABLE
            if v[1]==36:
                result=CHUNK+self.chunk_objects*0x100;self.chunk_objects+=1;return result
            if v[1]==4096:return ARRAY
            result=STORAGE+self.chunk_buffers*0x10000;self.chunk_buffers+=1;return result
        if e==0x2ed330:
            self.events.append((e,*v[:2]));result=ARRAY+(self.reallocations+1)*0x10000;self.reallocations+=1
            for i in range(self.read(TABLE+12,4)*4):self.w(result+i,1,self.read(v[0]+i,1))
            return result
        if e in (0x2ed4b0,0x2eb050):self.events.append((e,v[0]));return 0
        if e==0x12a4a4:
            self.events.append((e,*v[:2]));left,right=self.string(v[0]),self.string(v[1]);return (left>right)-(left<right)
        if e==0x12a78c:self.events.append((e,v[0]));return len(self.string(v[0]))
        return super().call(e,args)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=p.parse_args()
    image=args.elf.read_bytes();retail=InternedRegistry(image);native=InternedRegistry(image);errors=[];cases=0;depth=0
    @CALL
    def call(_,e,values):
        nonlocal depth
        try:
            if e in CHUNKS:return chunk(C.byref(api),e,values)
            depth+=1
            try:
                if e in POOL_ENTRIES:return pool(C.byref(api),e,values,STACK-0x1800-depth*0x100)
                if e in OBJECTS:return objects(C.byref(api),e,values)
                if e in CREATION:return creation(C.byref(api),e,values)
                if e in MEMORY:return memory(C.byref(api),e,values)
                if e in GENERIC:return generic(C.byref(api),e,values,STACK-0x800-depth*0x100)
                if e in LIFE or e in DISPATCH:return (life if e in LIFE else dispatch)(C.byref(api),e,values,STACK-0x1000-depth*0x100)
                if e in STRING_RESULTS:return result(C.byref(api),e,values[0],values[1],values[2],0,STACK-0x1400-depth*0x100)
            finally:depth-=1
            return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-interned-registry-') as td:
        so=Path(td)/'interned.so';sources=('object-lists.c','list-services.c','object-creation.c','messenger-memory.c','messenger-lifecycle.c','messenger-dispatch.c','string-pool.c','string-chunks.c','messenger-results.c')
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/name) for name in sources],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));chunk=lib.dw4_string_chunk;objects=lib.dw4_object_list;creation=lib.dw4_object_creation;memory=lib.dw4_messenger_memory
        for fn in (chunk,objects,creation,memory):fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];fn.restype=C.c_uint64
        pool=lib.dw4_string_pool;generic=lib.dw4_list_service;life=lib.dw4_messenger_lifecycle;dispatch=lib.dw4_messenger_dispatch
        for fn in (pool,generic,life,dispatch):fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        result=lib.dw4_messenger_result;result.argtypes=[C.POINTER(Api),C.c_uint32,C.c_uint64,C.c_uint64,C.c_uint64,C.c_uint32,C.c_uint32];result.restype=C.c_uint64
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[];expected=retail.invoke(entry,*values);v=(C.c_uint64*8)(*[x&MASK for x in values])
            if entry in POOL_ENTRIES:actual=pool(C.byref(api),entry,v,STACK-0x1800)
            elif entry in CHUNKS:actual=chunk(C.byref(api),entry,v)
            elif entry in OBJECTS:actual=objects(C.byref(api),entry,v)
            elif entry in MEMORY:actual=memory(C.byref(api),entry,v)
            elif entry in STRING_RESULTS:actual=result(C.byref(api),entry,v[0],v[1],v[2],0,STACK-0x1400)
            else:actual=(life if entry in LIFE else dispatch)(C.byref(api),entry,v,STACK-0x1000)
            assert not errors,errors
            if entry in (0x2eaf60,0x38f820,0x38f8f0):assert expected==actual,(hex(entry),hex(expected),hex(actual))
            def ram(world):return {p:v for p,v in world.mem.items() if not STACK-0x7000<=p<STACK+32 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:15])
            assert retail.events==native.events,(hex(entry),next(((i,x,y) for i,(x,y) in enumerate(zip(retail.events,native.events)) if x!=y),('length',len(retail.events),len(native.events))))
            assert (retail.chunk_objects,retail.chunk_buffers,retail.reallocations)==(native.chunk_objects,native.chunk_buffers,native.reallocations)
            cases+=1;return actual
        for synchronized,allocator_mode in itertools.product((False,True),(0,1)):
            retail=InternedRegistry(image);retail.w(0x554c14,1,allocator_mode)
            if synchronized:compare(0x30c180,1)
            compare(0x2fecb0,RECORD,retail.seed_group)
            assert retail.read(0x586f20,4)==POOL
            for i,text in enumerate(retail.seed_names):
                token=compare(0x2eaf60,POOL,text) if text else 0
                retail.w(retail.read(NAMES+16,4)+i*4,4,token)
            retail.w(MSG+48,1,0);compare(0x38d050,MSG)
            for key in ('SEARCH','FIND_SPACE','EVENT'):compare(0x38e670,MSG,retail.token('MODELCTRL'),retail.token(key))
            for i,length in enumerate((1,15,16375,16385)):
                text=0x1e00000+i*0x10000;name=bytes([ord('A')+i])*length;retail.text(text,name)
                receiver=BASE+0x5000
                compare(0x38d560,MSG,receiver,text,retail.token('first'),7)
                compare(0x38e5f0,MSG,text,retail.token('first'),7,retail.token('SEARCH'))
                compare(0x38f830,MSG,text);token=compare(0x38f8f0,MSG,0)
                assert retail.string(token)==name and token!=text
                assert token==retail.read(retail.values(REG)[-1]+8,4)
                headers=[retail.read(retail.read(TABLE+16,4)+j*4,4) for j in range(retail.read(TABLE+4,4))]
                assert token-8 in headers and retail.read(token-4,4)>0
                compare(0x38eca0,MSG,text,retail.token('first'),7,retail.token('EVENT'),0)
                compare(0x38d0a0,MSG)
            assert retail.read(REG+8,4)==5 and retail.chunk_objects>=3
            # Actual SetName -> final-token release -> footer coalescing and
            # empty-chunk notification. The first empty notification retains its
            # chunk; the next cycle deletes that non-head chunk via real tails.
            owner,text=0x1af0000,0x1e40000;retail.w(owner+8,4,0);retail.text(text,b'Q'*20000)
            before=retail.read(TABLE+4,4)
            for _ in range(2):compare(0x2fecb0,owner,text);compare(0x2fecb0,owner,0)
            assert retail.read(TABLE+4,4)==before and any(event[0]==0x2ed4b0 for event in retail.events)
            compare(0x38ed70,MSG);compare(0x38ef50,MSG)
            compare(0x38c490,MSG);compare(0x38d050,MSG)
            assert retail.read(REG+8,4)==0
    print(f'interned registry retail: {cases} persistent RAM/defined-return/ordered-call checkpoints through real pool/table/chunk, registry, lists, factories, cold lifecycle and string channels; concrete fields/allocator/byte/sync leaves controlled')
if __name__=='__main__':main()
