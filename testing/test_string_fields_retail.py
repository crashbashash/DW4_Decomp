#!/usr/bin/env python3
"""Scalar string-field value run against original EE RAM and service order."""
import argparse,ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
from test_messenger_dispatch_retail import World,ROOT,Api,READ,WRITE,CALL,MASK,STACK
ENTRIES=(0x2fc500,0x2fc6f0,0x1c8c00,0x30a910,0x30a9d0,0x30aa00,0x30aa10,0x30aab0,0x30ab20,0x30add0,0x30ae90,0x30aea0,0x30aeb0,0x30af80,0x30aff0,0x30b060,0x30b0b0,0x30b0c0,0x30b110,0x30b170,0x30b1d0)
RETURNS={0x2fc6f0,0x30aa00,0x30aab0,0x30ab20,0x30add0,0x30b060,0x30b110,0x30b170,0x30b1d0}
FIELD,DEST,SOURCE,CELL,DEFAULT,OLD,NEW,ALT,INPUT,OUTPUT,ALLOC,AVT,BUFFER,SWAPPER,SVT=range(0x1800000,0x180f000,0x1000)
ALLOCATE,FREE,SWAP=0x1810000,0x1810100,0x1810200
FIELDVT=0x1810300;RESET0,RESET2,RESET3=0x1810400,0x1810500,0x1810600
ALTALLOC,ALTAVT=0x1810700,0x1810800
class Strings(World):
    def __init__(self,image):
        super().__init__(image);self.descend=set(ENTRIES);self.events=[];self.mutate_source=False;self.change_allocator=False
        self.w(FIELD,4,FIELDVT);self.w(FIELDVT+112,4,RESET0);self.w(FIELDVT+120,4,RESET2);self.w(FIELDVT+116,4,RESET3);self.w(FIELDVT+200,4,0x30add0)
        self.w(FIELD+8,4,16);self.w(FIELD+32,4,DEFAULT);self.w(FIELD+38,1,1);self.w(FIELD+53,1,1)
        self.w(DEST+16,4,OLD);self.w(SOURCE+16,4,NEW);self.w(CELL,4,NEW);self.w(DEFAULT,4,NEW)
        for p,text in ((OLD,b'old'),(NEW,b'new'),(ALT,b'new')):
            self.text(p,text);self.w(p-8,4,0x18f0000);self.w(p-4,4,1)
        self.w(ALLOC,4,AVT);self.w(AVT+216,4,ALLOCATE);self.w(AVT+264,4,FREE)
        self.w(ALTALLOC,4,ALTAVT);self.w(ALTAVT+264,4,FREE)
        self.w(SWAPPER,4,SVT);self.w(SVT+208,4,SWAP);self.w(0x586f20,4,0x18f1000)
        self.w(0x587060,4,0x18f2000);self.w(0x554c14,1,1)
        for i in range(128):self.w(OUTPUT+i,1,0xa5)
    def text(self,p,value):
        for i,b in enumerate(value+b'\0'):self.w(p+i,1,b)
    def string(self,p):
        out=[]
        while self.read(p,1):out.append(self.read(p,1));p+=1
        return bytes(out)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e in (RESET0,RESET2,RESET3):
            self.events.append((e,*v[:2]));self.w(v[1]+16,4,e);return 0
        n={0x2eb010:1,0x2eadf0:1,0x2eaf60:2,0x30c940:2,0x12a78c:1,0x12a4a4:2,
           0x12a5fc:2,0x127098:3,0x301000:1,0x2f88e0:1,0x2c3090:0,ALLOCATE:2,FREE:2,SWAP:3}[e]
        self.events.append((e,*['temp' if STACK-0x2000<=p<STACK else p for p in v[:n]]))
        if e==0x2eb010:return 0x18f1000
        if e==0x2eadf0:return v[0]
        if e==0x2eaf60:
            if self.change_allocator:self.w(0x554c14,1,0)
            if not v[1]:return 0
            result=OLD if self.string(v[1])==b'old' else NEW
            self.w(result-4,4,self.read(result-4,4)+1);return result
        if e==0x30c940:
            if self.mutate_source:self.w(CELL,4,ALT);self.w(FIELD+8,4,24)
            return 0
        if e==0x12a78c:return len(self.string(v[0]))
        if e==0x12a4a4:
            a,b=self.string(v[0]),self.string(v[1]);return (a>b)-(a<b)
        if e in (0x12a5fc,0x127098):
            data=self.string(v[1])+b'\0' if e==0x12a5fc else bytes(self.read(v[1]+i,1) for i in range(v[2]))
            for i,b in enumerate(data):self.w(v[0]+i,1,b)
            return v[0]
        if e==0x301000:return ALLOC
        if e==0x2f88e0:return ALTALLOC if self.change_allocator else ALLOC
        if e==ALLOCATE:return BUFFER
        if e==FREE:return 0
        if e==0x2c3090:return SWAPPER
        if e==SWAP:
            for i in range(v[2]):self.w(v[1]+i*4,4,int.from_bytes(self.read(v[1]+i*4,4).to_bytes(4,'little'),'big'))
            return 0
        raise AssertionError(e)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=p.parse_args()
    image=args.elf.read_bytes();retail=Strings(image);native=Strings(image);errors=[];cases=0;hits=set()
    @CALL
    def call(_,e,values):
        try:
            if e in ENTRIES:return fn(C.byref(api),e,values,STACK-0x1000)
            return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-string-fields-') as td:
        so=Path(td)/'fields.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/string-fields.c'),'-o',str(so)],check=True)
        fn=C.CDLL(str(so)).dw4_string_field;fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        def setup():
            nonlocal retail
            retail=Strings(image)
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[];wanted=retail.invoke(entry,*values)
            actual=fn(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in values]),STACK-0x800)
            assert not errors,errors
            if entry in RETURNS:assert wanted==actual,(hex(entry),wanted,actual)
            def ram(world):return {p:v for p,v in world.mem.items() if not STACK-0x2000<=p<STACK+32 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry);return actual
        for method in (-1,0,1,2,3):
            setup();retail.w(FIELD+36,1,method);compare(0x2fc500,FIELD,DEST)
        for persistent,value,swapped in itertools.product((0,1,2),(0,OLD),(0,1)):
            setup();retail.w(FIELD+38,1,persistent);retail.w(DEST+16,4,value);compare(0x2fc6f0,FIELD,DEST,OUTPUT,0,swapped)
        for entry,old,new,refs in itertools.product((0x1c8c00,0x30a910,0x30aeb0,0x30aa10),(0,OLD),(0,OLD,NEW),(0,1,2)):
            setup();retail.w(DEST+16,4,old);retail.w(DEFAULT,4,new);retail.w(CELL,4,new);retail.w(OLD-4,4,refs)
            if entry==0x30aa10:compare(entry,FIELD,new)
            else:compare(entry,FIELD,DEST,CELL)
        for entry,source,dest in itertools.product((0x30af80,0x30aff0,0x30b060,0x30b110,0x30b170,0x30b1d0),(0,OLD,NEW,ALT),(0,OLD,NEW)):
            setup();retail.w(SOURCE+16,4,source);retail.w(DEST+16,4,dest);compare(entry,FIELD,DEST,SOURCE)
        for enabled,old in itertools.product((0,1,2),(0,OLD)):
            setup();retail.w(FIELD+53,1,enabled);retail.w(DEST+16,4,old);compare(0x30b0c0,FIELD,DEST)
        for persistent,value in itertools.product((0,1,2),(0,OLD,NEW)):
            setup();retail.w(FIELD+38,1,persistent);retail.w(DEST+16,4,value);compare(0x30aab0,FIELD,DEST)
        for length,terminated,swapped,mode in itertools.product((-1,0,1,3,4,7,15),(False,True),(0,1),(0,1)):
            setup();retail.w(0x554c14,1,mode);retail.w(INPUT,4,length)
            if swapped:retail.w(INPUT,4,int.from_bytes((length&0xffffffff).to_bytes(4,'little'),'big'))
            for i in range(max(1,length)):retail.w(INPUT+4+i,1,ord('x'))
            if terminated and length>0:retail.w(INPUT+4+length-1,1,0)
            compare(0x30ab20,FIELD,CELL,INPUT,0,swapped)
        for value,swapped,text in itertools.product((0,NEW),(0,1),(b'',b'a',b'abcd',b'abcdefg')):
            setup();retail.text(NEW,text);retail.w(CELL,4,value);compare(0x30add0,FIELD,CELL,OUTPUT,0,swapped)
        setup();retail.mutate_source=True;compare(0x1c8c00,FIELD,DEST,CELL)
        setup();retail.change_allocator=True;retail.w(INPUT,4,3);retail.text(INPUT+4,b'xyz');compare(0x30ab20,FIELD,CELL,INPUT,0,0)
        assert (FREE,ALTALLOC,BUFFER) in retail.events
        setup();compare(0x30a9d0,OUTPUT,FIELD,CELL);compare(0x30aa00,FIELD)
        for entry in (0x30ae90,0x30aea0,0x30b0b0):setup();compare(entry,FIELD,DEST)
        assert hits==set(ENTRIES),hits
    print(f'string fields retail: {cases} RAM/defined-return/ordered-call cases; all 21 bodies; pool/allocator/byte/endian services controlled')
if __name__=='__main__':main()
