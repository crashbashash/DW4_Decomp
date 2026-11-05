#!/usr/bin/env python3
"""Generic cleanup/serialization and concrete object-reference fields vs retail."""
import argparse,ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
from test_object_creation_retail import Creation,ROOT,Api,READ,WRITE,CALL,MASK,STACK,META,OTHER,FIELDS,BASEFIELDS,POINTERS,ALTPOINTERS,FIELD,FVT,VT,ALT,VOP,VOTHER,OBJECT,REDIRECT,BASETYPE
ENTRIES=(0x2fdf00,0x2fe470,0x2ffc10,0x2ffcb0,0x2ffd40,0x2ffe10,0x303390,0x303450,0x303540,0x303620,0x303680,0x305500,0x305540,0x305cd0)
RETURNS={0x2fdf00,0x2fe470,0x2ffd40,0x2ffe10,0x303450,0x305cd0}
OLD,NEW,BUFFER,SWAPPER,SVT,SWAP,SIZE,NAME=range(0x1890000,0x1898000,0x1000)
class Fields(Creation):
    def __init__(self,image):
        super().__init__(image);self.descend=set(ENTRIES);self.size=4;self.named=True;self.child=NEW
        self.change_offset=False;self.disable_on_hook=False;self.size_bias=0;self.change_size=False
        self.w(META+25,1,1);self.w(OTHER+25,1,1);self.w(META+64,4,0)
        for table,code in ((VT,VOP),(ALT,VOTHER)):
            for slot in (16,56):self.w(table+slot,4,code+slot)
        for i in range(6):
            p=FIELD+i*0x100;self.w(p+8,4,32+i*8);self.w(p+38,1,1);self.w(p+37,1,0)
        self.w(FIELD+52,1,1);self.w(FIELD+53,1,1);self.w(FIELD+60,1,0);self.w(FIELD+56,4,META);self.w(FIELD+64,4,0)
        for slot in (100,128,136,196):self.w(FVT+slot,4,VOP+slot)
        self.w(SWAPPER,4,SVT);self.w(SVT+208,4,SWAP)
        self.w(OLD+4,4,1);self.w(NEW+4,4,1);self.w(OBJECT+32,4,OLD);self.w(OBJECT+40,4,0xa5a5a5a5)
        self.w(NAME,1,ord('a'))
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==0x2ff820:
            self.events.append((e,v[0]))
            if self.change_offset:self.w(FIELD+8,4,40)
            return 0
        if e==0x301000:self.events.append((e,v[0]));return 0x1880000
        if e==0x2f8920:self.events.append((e,v[0]));return 0x1881000 if self.named else 0
        if e==0x2fda40:self.events.append((e,*v[:2]));return self.child
        if e==0x12724c:
            self.events.append((e,*v[:3]));assert v[2]<=65535
            for i in range(v[2]):self.w(v[0]+i,1,v[1])
            return v[0]
        if e==0x2fe600:self.events.append((e,*v[:2]));return 0x11223344
        if e==0x2c3090:self.events.append((e,));return SWAPPER
        if e==SWAP:
            self.events.append((e,*v[:3]))
            for i in range(v[2]):self.w(v[1]+i*4,4,int.from_bytes(self.read(v[1]+i*4,4).to_bytes(4,'little'),'big'))
            return 0
        if e==0x2fc6f0:
            self.events.append((e,*v[:5]));self.w(v[2],4,0xb000+(v[0]-FIELD)//0x100)
            if self.change_size:self.size_bias+=4
            return 4
        if VOP<=e<VOP+256 or VOTHER<=e<VOTHER+256:
            slot=e-(VOTHER if e>=VOTHER else VOP)
            if slot in (16,56,100,128,136,196):
                self.events.append((e,*v[:2 if slot in (128,136,196) else 1]))
                if slot==16 and self.swap_vtable:self.w(v[0],4,ALT)
                if slot==56 and self.disable_on_hook:self.w(META+25,1,0)
                if slot==100:
                    if self.change_offset:self.w(FIELD+8,4,40)
                    return self.size
                if slot in (128,136):
                    self.w(v[1]+self.read(v[0]+8,4),4,slot)
                    if self.swap_fields:self.w(FIELDS+8,4,ALTPOINTERS);self.w(FIELDS+12,4,0)
                if slot==196:return 4+self.size_bias
                return 0
        return super().call(e,args)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=p.parse_args()
    image=args.elf.read_bytes();retail=Fields(image);native=Fields(image);errors=[];cases=0;hits=set()
    @CALL
    def call(_,e,values):
        try:return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-object-fields-') as td:
        so=Path(td)/'fields.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/object-fields.c'),'-o',str(so)],check=True)
        fn=C.CDLL(str(so)).dw4_object_field;fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];fn.restype=C.c_uint64
        def setup():
            nonlocal retail
            retail=Fields(image)
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            expected=retail.invoke(entry,*values);actual=fn(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in values]))
            assert not errors,errors
            if entry in RETURNS:assert expected==actual,(hex(entry),values,expected,actual)
            def ram(world):return {p:v for p,v in world.mem.items() if not STACK-0x1000<=p<STACK+32 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry);return actual
        for entry,start,count,swap in itertools.product((0x2ffc10,0x2ffcb0),(0,1,3),(0,1,3),(False,True)):
            setup();retail.w(BASEFIELDS+12,4,start);retail.w(FIELDS+12,4,count);retail.swap_fields=swap;retail.swap_vtable=swap;compare(entry,OBJECT)
        for entry,persistent,proxy,swap,context in itertools.product((0x2ffd40,0x2ffe10),(0,1,2),(False,True),(0,1),(0,0x18a0000)):
            setup();retail.w(META+25,1,persistent);retail.w(META+64,4,REDIRECT if proxy else 0)
            compare(entry,*((OBJECT,) if entry==0x2ffd40 else (OBJECT,BUFFER,0x18b0000,context,swap)))
        for persistent,runtime in itertools.product((0,1,2),(0,1,2)):
            setup()
            for i in range(3):retail.w(FIELD+i*0x100+38,1,persistent);retail.w(FIELD+i*0x100+37,1,runtime)
            retail.change_size=True;returned=compare(0x2ffe10,OBJECT,BUFFER,0,0,0)
            if persistent==1 and runtime==0:assert returned!=retail.read(BUFFER+4,4)
        setup();retail.disable_on_hook=True;compare(0x2ffe10,OBJECT,BUFFER,0,0,1)
        setup();retail.w(META+64,4,REDIRECT);retail.w(OTHER+25,1,0);compare(0x2ffd40,OBJECT)
        compare(0x2ffe10,OBJECT,BUFFER,0,0,0)
        for refcounted,destruct,refs,new in itertools.product((0,1),(0,1),(1,2,0x800001),(0,OLD,NEW)):
            setup();retail.w(FIELD+60,1,refcounted);retail.w(FIELD+53,1,destruct);retail.w(OLD+4,4,refs);compare(0x303390,FIELD,OBJECT,new)
        for construct,refcounted,destruct,named,child in itertools.product((0,1),(0,1),(0,1),(0,1,2),(0,NEW)):
            setup();retail.w(FIELD+52,1,construct);retail.w(FIELD+60,1,refcounted);retail.w(FIELD+53,1,destruct)
            retail.w(FIELD+64,4,NAME if named else 0);retail.named=named==1;retail.child=child;compare(0x303540,FIELD,OBJECT)
        for entry,enabled,refs in itertools.product((0x303620,0x303680),(0,1,2),(0,1,2,0x800001)):
            setup();retail.w(FIELD+(53 if entry==0x303620 else 60),1,enabled);retail.w(OLD+4,4,refs);compare(entry,FIELD,OBJECT)
        for entry,size,change in itertools.product((0x305500,0x305540),(0,1,4,17,0x10004),(False,True)):
            setup();retail.size=size;retail.change_offset=change;compare(entry,FIELD,OBJECT)
        for entry in (0x303390,0x303680):setup();retail.change_offset=True;retail.w(FIELD+60,1,1);compare(entry,FIELD,OBJECT,NEW)
        setup();compare(0x303450,FIELD);compare(0x305cd0,FIELD)
        setup();compare(0x2fe470,META);compare(0x2fdf00,META,1)
        assert hits==set(ENTRIES),hits
    print(f'object fields retail: {cases} RAM/defined-return/ordered-call cases; all 14 bodies; concrete creation/destruction/field serialization/allocator/byte services controlled')
if __name__=='__main__':main()
