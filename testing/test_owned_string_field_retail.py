#!/usr/bin/env python3
"""Owned string fields through actual construction, codec, cleanup and pool.

One-field class metadata is synthetic. Concrete string/reference operations and
pool storage are real; allocation/hooks/byte/endian primitives remain leaves.
"""
import argparse,ctypes as C,subprocess,tempfile
from pathlib import Path
from test_messenger_interned_registry_retail import InternedRegistry,POOL_ENTRIES,CHUNKS,TAILS,OBJECTS,CREATION,MEMORY,GENERIC,LIFE,DISPATCH,ROOT,STACK,MASK,Api,READ,WRITE,CALL,POOL,TABLE
from test_object_fields_retail import ENTRIES as OBJECT_FIELDS
from test_string_fields_retail import ENTRIES as STRING_FIELDS
META,VT,FIELD,FTABLE,DEFAULT,OWNER,LIST=range(0x19a0000,0x19a7000,0x1000)
RAWALLOC,RAWVT,RAWALLOCATE,RAWFREE,SWAPPER,SWVT,SWAP,GETMETA,OWNALLOC,OWNVT,OWNALLOCATE=range(0x19a7000,0x19a7b00,0x100)
SOURCE,ENCODED,INPUT=0x1e10000,0x1e20000,0x1e30000
class OwnedString(InternedRegistry):
    def __init__(self,image):
        super().__init__(image);self.descend|=set(OBJECT_FIELDS)|set(STRING_FIELDS)
        self.raw_allocations=0
        self.w(META+25,1,1);self.w(META+26,1,0);self.w(META+32,4,0);self.w(META+36,4,4)
        self.w(META+40,4,FTABLE);self.w(META+44,4,0);self.w(META+48,4,0);self.w(META+60,4,0);self.w(META+64,4,0)
        self.w(META+72,4,12);self.w(META+92,4,VT);self.w(META+96,4,0)
        self.w(FTABLE+8,4,FTABLE+0x100);self.w(FTABLE+12,4,1);self.w(FTABLE+0x100,4,FIELD)
        for slot in (8,12,16,36,40,44,48,52,56,72,80):self.w(VT+slot,4,0x1810000+slot)
        self.w(VT+88,4,GETMETA)
        self.w(FIELD,4,0x533180);self.w(FIELD+8,4,8);self.w(FIELD+32,4,DEFAULT);self.w(DEFAULT,4,0)
        for offset,value in ((36,0),(37,0),(38,1),(52,0),(53,1),(56,1)):self.w(FIELD+offset,1,value)
        self.w(RAWALLOC,4,RAWVT);self.w(RAWVT+216,4,RAWALLOCATE);self.w(RAWVT+264,4,RAWFREE)
        self.w(OWNALLOC,4,OWNVT);self.w(OWNVT+216,4,OWNALLOCATE)
        self.w(SWAPPER,4,SWVT);self.w(SWVT+208,4,SWAP)
        self.w(LIST+8,4,1);self.w(LIST+12,4,1);self.w(LIST+16,4,LIST+0x100);self.w(LIST+0x100,4,OWNER)
        for i in range(17000):self.w(ENCODED+i,1,0xa5)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==GETMETA:self.events.append((e,v[0]));return META
        if e==0x301000 and v[0]==FIELD:self.events.append((e,v[0]));return RAWALLOC
        if e==OWNALLOCATE:
            self.events.append((e,*v[:2]))
            for i in range(v[1]):self.w(OWNER+i,1,0xa5)
            return OWNER
        if e==RAWALLOCATE:
            self.events.append((e,*v[:2]));p=0x1a80000+self.raw_allocations*0x1000;self.raw_allocations+=1;return p
        if e==RAWFREE:self.events.append((e,*v[:2]));return 0
        if e==0x12a5fc:
            self.events.append((e,*v[:2]));self.text(v[0],self.string(v[1]));return v[0]
        if e==0x2c3090:self.events.append((e,));return SWAPPER
        if e==SWAP:
            self.events.append((e,*['temp' if STACK-0x7000<=p<STACK else p for p in v[:3]]))
            for i in range(v[2]):self.w(v[1]+i*4,4,int.from_bytes(self.read(v[1]+i*4,4).to_bytes(4,'little'),'big'))
            return 0
        return super().call(e,args)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=p.parse_args()
    image=args.elf.read_bytes();retail=OwnedString(image);native=OwnedString(image);errors=[];cases=0;depth=0
    @CALL
    def call(_,e,values):
        nonlocal depth
        try:
            if e in CHUNKS:return chunk(C.byref(api),e,values)
            if e in OBJECT_FIELDS:return fields(C.byref(api),e,values)
            depth+=1
            try:
                if e in STRING_FIELDS:return strings(C.byref(api),e,values,STACK-0x1800-depth*0x100)
                if e in POOL_ENTRIES:return pool(C.byref(api),e,values,STACK-0x2800-depth*0x100)
                if e in OBJECTS:return objects(C.byref(api),e,values)
                if e in CREATION:return creation(C.byref(api),e,values)
            finally:depth-=1
            return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-owned-string-') as td:
        so=Path(td)/'owned.so';names=('string-fields.c','object-fields.c','object-lists.c','object-creation.c','string-pool.c','string-chunks.c')
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/name) for name in names],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));chunk=lib.dw4_string_chunk;fields=lib.dw4_object_field;objects=lib.dw4_object_list;creation=lib.dw4_object_creation
        for fn in (chunk,fields,objects,creation):fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];fn.restype=C.c_uint64
        pool=lib.dw4_string_pool;strings=lib.dw4_string_field
        for fn in (pool,strings):fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[];expected=retail.invoke(entry,*values);v=(C.c_uint64*8)(*[x&MASK for x in values])
            if entry in STRING_FIELDS:actual=strings(C.byref(api),entry,v,STACK-0x1800)
            elif entry in OBJECT_FIELDS:actual=fields(C.byref(api),entry,v)
            elif entry in CREATION:actual=creation(C.byref(api),entry,v)
            else:actual=objects(C.byref(api),entry,v)
            assert not errors,errors
            if entry in (0x2fda40,0x2ffe10,0x30ab20):assert expected==actual,(hex(entry),expected,actual)
            def ram(world):return {p:v for p,v in world.mem.items() if not STACK-0x7000<=p<STACK+32 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),next(((x,y) for x,y in zip(retail.events,native.events) if x!=y),(len(retail.events),len(native.events))))
            cases+=1;return actual
        for length in (0,7,16385):
            for swapped in (0,1):
                retail=OwnedString(image);retail.text(SOURCE,b'x'*length)
                compare(0x30aa10,FIELD,SOURCE);token=retail.read(DEFAULT,4)
                compare(0x2fda40,META,OWNALLOC)
                assert retail.read(OWNER+8,4)==token and retail.read(token-4,4)==2
                size=compare(0x2ffe10,OWNER,ENCODED,0,0,swapped)
                encoded=retail.read(ENCODED+8,4)
                if swapped:encoded=int.from_bytes(encoded.to_bytes(4,'little'),'big')
                assert size==8+4+((length+4)&~3) and encoded==((length+4)&~3)
                compare(0x30ab20,FIELD,OWNER+8,ENCODED+8,0,swapped)
                assert retail.read(OWNER+8,4)==token and retail.read(token-4,4)==2
                retail.w(INPUT,4,0x03000000 if swapped else 3);retail.text(INPUT+4,b'abc')
                assert compare(0x30ab20,FIELD,OWNER+8,INPUT,0,swapped)==7
                other=retail.read(OWNER+8,4);assert retail.string(other)==b'abc' and other!=token
                assert retail.raw_allocations==1 and any(e[0]==RAWFREE for e in retail.events)
                compare(0x301c90,LIST,0)
                assert retail.read(META+44,4)==0 and retail.read(OWNER+8,4)==0
                assert retail.read(token-4,4)==1 and retail.read(TABLE+4,4)==1
                assert len([e for e in retail.events if e==(0x2ed460,OWNER)])==1
                compare(0x30aa10,FIELD,0)
                assert retail.read(DEFAULT,4)==0 and retail.read(TABLE+4,4)==0
    print(f'owned string retail: {cases} persistent default/create/serialize/read/final-release checkpoints; real concrete string fields and pool/table/chunks; metadata synthetic, allocation/hooks/byte/endian leaves controlled')
if __name__=='__main__':main()
