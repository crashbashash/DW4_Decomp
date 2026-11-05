#!/usr/bin/env python3
"""Object storage helpers against retail instructions, RAM and service ordering."""
import ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
from test_reflection_registration_retail import Registration,ROOT,Api,READ,WRITE,CALL,MASK,STACK
ENTRIES=(0x2f0700,0x300d30,0x300d70,0x300db0,0x300e00,0x300e50,0x300ea0,0x300f00,0x300f50,0x300fa0,0x301000)
RETURNS=set(ENTRIES)-{0x300f00,0x300f50}
OBJECT,VT,META,POOL0,POOL1,TABLE0,TABLE1,AVT,NAME,OUTPUT=range(0x1900000,0x190a000,0x1000)
GETMETA=0x1910000
class Storage(Registration):
    def __init__(self,image):
        super().__init__(image);self.descend=set(ENTRIES);self.w(OBJECT,4,VT);self.w(VT+88,4,GETMETA)
        self.w(0x586f58,4,POOL0);self.w(0x586f60,4,POOL1);self.w(POOL0,4,TABLE0);self.w(POOL1,4,TABLE1)
        self.result=OUTPUT;self.mutate=False;self.free_calls=0
        for i in range(-3,130):
            for bank,table in enumerate((TABLE0,TABLE1)):
                alloc=0x1940000+bank*0x10000+(i+3)*0x100
                self.w(table+i*4,4,alloc);self.w(alloc,4,AVT)
        for slot in (216,220,224,232,236,264):self.w(AVT+slot,4,GETMETA+slot)
        self.text(NAME,b'hello');self.w(META+32,4,16)
    def step(self,pc,delay=False):
        if pc==0x301000:
            # Execute the original tail's delay-slot byte load before lookup.
            assert (self.read(pc,4)&0x3ffffff)<<2==0x2f0700
            super().step(pc+4,True)
            self.r[2]=self.invoke_selector(self.r[4]);return self.r[31]&0xffffffff
        return super().step(pc,delay)
    def invoke_selector(self,encoded):
        saved_ra=self.r[31];self.run_until(0x2f0700,saved_ra&0xffffffff);return self.r[2]
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==GETMETA:
            self.events.append((e,v[0]));return META
        if e in (0x12a78c,0x12a5fc):
            self.events.append((e,*v[:1 if e==0x12a78c else 2]))
            if e==0x12a78c:
                if self.mutate:self.w(OBJECT+7,1,255)
                return len(self.string(v[0]))
            self.text(v[0],self.string(v[1]));return v[0]
        slot=e-GETMETA
        assert slot in (216,220,224,232,236,264),hex(e)
        count={216:2,220:3,224:3,232:3,236:4,264:2}[slot]
        self.events.append((e,*v[:count]))
        if slot==264:self.free_calls+=1;return 0
        return self.result

def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();retail=Storage(image);native=Storage(image);errors=[];cases=0;hits=set()
    @CALL
    def call(_,e,values):
        try:return native.call(e,list(values[:8]))&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-storage-') as td:
        so=Path(td)/'storage.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/object-storage.c'),'-o',str(so)],check=True)
        fn=C.CDLL(str(so)).dw4_object_storage;fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];fn.restype=C.c_uint64
        def setup():
            nonlocal retail
            retail=Storage(image)
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            expected=retail.invoke(entry,*values);actual=fn(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in values]))
            assert not errors,errors
            if entry in RETURNS:assert expected==actual,(hex(entry),expected,actual)
            def ram(w):return {p:v for p,v in w.mem.items() if not STACK-0x1000<=p<STACK+32 and v}
            assert ram(retail)==ram(native),hex(entry)
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry);return actual
        for encoded in (*range(256),-1,-2,-3,-4):setup();compare(0x2f0700,encoded)
        for encoded in range(256):setup();retail.w(OBJECT+7,1,encoded);compare(0x301000,OBJECT)
        for prefix in (0,1,16,0x7fffffff,0x80000000,0xffffffff):setup();retail.w(META+32,4,prefix);compare(0x300d30,OBJECT)
        for entry,encoded,count,other in itertools.product((0x300d70,0x300db0,0x300e00,0x300e50,0x300ea0),(0,1,2,255),(0,1,0xffffffff),(0,1,16)):
            setup();retail.w(OBJECT+7,1,encoded);compare(entry,OBJECT,count,other,0xa5a5)
        for entry,encoded,pointer in itertools.product((0x300f00,0x300f50),(0,1,254,255),(0,OUTPUT)):
            setup();retail.w(OBJECT+7,1,encoded);compare(entry,OBJECT,pointer)
            assert retail.free_calls==int(bool(pointer))
        for text,mutate in itertools.product((b'',b'a',b'hello',b'x'*129),(False,True)):
            setup();retail.text(NAME,text);retail.mutate=mutate;compare(0x300fa0,OBJECT,NAME)
            assert retail.string(OUTPUT)==text
        assert hits==set(ENTRIES)
    print(f'object storage retail: {cases} RAM/defined-return/ordered-call cases; all11 bodies; allocator virtual methods and libc byte services controlled')
if __name__=='__main__':main()
