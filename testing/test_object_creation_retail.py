#!/usr/bin/env python3
"""Reflection creation, field passes, lifetime and messenger factories vs retail.

Metadata/field/allocator/virtual services are explicit controlled boundaries.
"""
import argparse,ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
from test_messenger_dispatch_retail import World,ROOT,Api,READ,WRITE,CALL,MASK,STACK
FACTORIES=(0x358070,0x3584e0,0x358950,0x358d80)
GUARDS=(0x3581d0,0x358620,0x358a90,0x358fa0)
REGISTRARS=(0x3581f0,0x358640,0x358ab0,0x358fc0)
HANDLES=(0x588f88,0x588fc8,0x588ff0,0x589038)
CORE=(0x2fda10,0x2fda40,0x2fdb40,0x2fe940,0x2ff1d0,0x2ff2f0,0x2ff3a0,0x2ff820,0x2ff930,0x2ffa00,0x2ffab0,0x2ffb50)
ENTRIES=FACTORIES+GUARDS+CORE
META,OTHER,ALLOC,SYSTEM,BASETYPE,OWNER,OVT,TRACK=range(0x1800000,0x1800800,0x100)
FIELDS,BASEFIELDS,POINTERS,ALTPOINTERS=range(0x1801000,0x1801400,0x100)
FIELD=0x1802000;FVT=0x1803000;VT=0x1804000;ALT=0x1805000
ALVT=0x1806000;VOP=0x1810000;VOTHER=0x1811000
ALLOCATE,GETTAG,REDIRECT,CALLBACK,CALLBACK2=range(0x1820000,0x1820500,0x100)
OBJECT=0x1840000;TEXT=0x1850000;CBLIST=0x1860000;CBVECTOR=0x1860100
RETURNS=set(FACTORIES)|{0x2fda10,0x2fda40,0x2fdb40}
class Creation(World):
    def __init__(self,image):super().__init__(image);self.descend=set(ENTRIES);self.setup_core()
    def setup_core(self):
        self.events=[];self.named=True;self.allocation=OBJECT;self.owner=True;self.tag=0xa5
        self.meta_result=META;self.swap_vtable=False;self.swap_fields=False;self.callback_count=0
        self.w(0x586dc8,4,SYSTEM);self.w(SYSTEM,1,1);self.w(SYSTEM+20,1,0);self.w(SYSTEM+916,4,0)
        self.w(0x587198,4,BASETYPE);self.w(BASETYPE+40,4,BASEFIELDS);self.w(BASEFIELDS+12,4,0)
        for meta in (META,OTHER):
            self.w(meta+26,1,0);self.w(meta+32,4,0);self.w(meta+36,4,4);self.w(meta+40,4,FIELDS)
            self.w(meta+44,4,7);self.w(meta+48,4,TRACK);self.w(meta+60,4,0);self.w(meta+72,4,64)
            self.w(meta+92,4,VT);self.w(meta+96,4,0)
        self.w(FIELDS+8,4,POINTERS);self.w(FIELDS+12,4,3)
        for i in range(6):
            field=FIELD+i*0x100;self.w(field,4,FVT);self.w(POINTERS+i*4,4,field);self.w(ALTPOINTERS+i*4,4,field+0x100)
        for slot in (124,132,240):self.w(FVT+slot,4,VOP+slot)
        for table,code in ((VT,VOP),(ALT,VOTHER)):
            for slot in (8,12,36,40,44,48,52,72,80,88):self.w(table+slot,4,code+slot)
        self.w(ALLOC,4,ALVT);self.w(ALVT+216,4,ALLOCATE)
        self.w(OWNER,4,OVT);self.w(OVT+364,4,GETTAG)
        self.w(OBJECT,4,VT);self.w(OBJECT+4,4,0xa5ffffff)
        self.w(CBLIST,4,CBVECTOR);self.w(CBLIST+4,4,0)
        for i in range(4):self.w(CBVECTOR+i*4,4,CALLBACK if i%2==0 else CALLBACK2)
        for handle in HANDLES:self.w(handle,4,META)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e in REGISTRARS:
            self.events.append((e,));self.w(HANDLES[REGISTRARS.index(e)],4,META);return CBLIST if self.callback_count else 0
        if e in (CALLBACK,CALLBACK2):
            self.events.append((e,v[0]));self.w(CBLIST+4,4,0);return 0
        if e==0x2d3420:self.events.append((e,*v[:2]));return 0
        if e==REDIRECT:self.events.append((e,));return OTHER
        if e in (0x2f00d0,0x300d30):self.events.append((e,));return ALLOC if e==0x2f00d0 else OBJECT-32
        if e==0x2f8920:self.events.append((e,v[0]));return ALLOC if self.named else 0
        if e==ALLOCATE:self.events.append((e,*v[:2]));return self.allocation
        if e==0x2f04f0:self.events.append((e,v[0]));return OWNER if self.owner else 0
        if e==GETTAG:self.events.append((e,v[0]));return self.tag
        if e==0x2fc500:
            self.events.append((e,*v[:2]));self.w(v[1]+64+(v[0]-FIELD)//0x100*4,4,0x500);return 0
        if e in (0x2eaa60,0x2ea820,0x2eaa00):
            self.events.append((e,*v[:2]));return 11 if e==0x2ea820 else 0
        if e in (0x2ffc10,0x2ffcb0,0x2ed460):self.events.append((e,v[0]));return 0
        if VOP<=e<VOP+256 or VOTHER<=e<VOTHER+256:
            slot=e-(VOTHER if e>=VOTHER else VOP)
            self.events.append((e,*v[:2 if slot in (12,36,52,80,124,132) else 1]))
            if slot==88:return self.meta_result
            if slot==240:return ((v[0]-FIELD)//0x100)&1
            if slot==124:self.w(v[1]+32+(v[0]-FIELD)//0x100*4,4,0x124)
            if slot==132:self.w(v[1]+48+(v[0]-FIELD)//0x100*4,4,0x132)
            if self.swap_vtable and slot==12:self.w(v[0],4,ALT)
            if self.swap_fields and slot in (124,132):self.w(FIELDS+8,4,ALTPOINTERS);self.w(FIELDS+12,4,0)
            return 0
        raise AssertionError(f'unknown creation leaf {e:#x}')

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=p.parse_args()
    image=args.elf.read_bytes();retail=Creation(image);native=Creation(image);errors=[];cases=0;hits=set()
    @CALL
    def call(_,e,values):
        try:return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-object-creation-') as td:
        so=Path(td)/'creation.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/object-creation.c'),'-o',str(so)],check=True)
        fn=C.CDLL(str(so)).dw4_object_creation;fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];fn.restype=C.c_uint64
        def setup():
            nonlocal retail
            retail=Creation(image)
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            expected=retail.invoke(entry,*values);actual=fn(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in values]))
            assert not errors,errors
            if entry in RETURNS:assert expected==actual,(hex(entry),values,hex(expected),hex(actual))
            def ram(world):return {p:v for p,v in world.mem.items() if not STACK-0x1000<=p<STACK+32 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),values,[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry)
        for entry,allocator,name,named,abstract,bias in itertools.product((0x2fda40,0x2fdb40),(0,ALLOC),(0,TEXT),(False,True),(0,1,2),(0,16)):
            setup();retail.w(TEXT,1,ord('A'));retail.w(META+96,4,name);retail.named=named
            retail.w(META+26,1,abstract);retail.w(META+32,4,bias)
            compare(entry,META,allocator)
        for entry,flags,allocation in itertools.product((0x2fda40,0x2fdb40),(0,4),(0,OBJECT)):
            setup();retail.w(META+36,4,flags);retail.allocation=allocation;compare(entry,META,ALLOC)
        for entry in (0x2fda40,0x2fdb40):
            setup();retail.w(META+60,4,REDIRECT);compare(entry,META,ALLOC)
        setup();compare(0x2fda10,META)
        for entry,tag,owner,swap in itertools.product((0x2ff1d0,0x2ff2f0),(0,255,0x123),(False,True),(False,True)):
            setup();retail.tag=tag;retail.owner=owner;retail.swap_vtable=swap;compare(entry,OBJECT,META)
        for entry,start,count,swap in itertools.product((0x2ff930,0x2ffa00,0x2ffab0,0x2ffb50),(0,1,3),(0,1,3),(False,True)):
            setup();retail.w(BASEFIELDS+12,4,start);retail.w(FIELDS+12,4,count);retail.swap_fields=swap;compare(entry,OBJECT)
        for flags,system,enabled in itertools.product((0,4),(0,1),(0,1)):
            setup();retail.w(META+36,4,flags);retail.w(SYSTEM,1,system);retail.w(SYSTEM+20,1,enabled);compare(0x2ff930,OBJECT)
        for meta,redirect,tracked in itertools.product((0,META),(False,True),(False,True)):
            setup();retail.w(META+60,4,REDIRECT if redirect else 0);retail.w(META+48,4,TRACK if tracked else 0);compare(0x2ff3a0,OBJECT,meta)
        for system,tracked in itertools.product((0,SYSTEM),(False,True)):
            setup();retail.w(0x586dc8,4,system);retail.w(META+48,4,TRACK if tracked else 0);compare(0x2ff820,OBJECT)
        setup();retail.w(SYSTEM,1,0);compare(0x2ff820,OBJECT)
        for entry,count in itertools.product(FACTORIES+GUARDS,(0,1,3)):
            setup();retail.callback_count=count;retail.w(CBLIST+4,4,count)
            compare(entry,*((ALLOC,) if entry in FACTORIES else ()))
        setup();retail.callback_count=3;retail.w(CBLIST+4,4,3);compare(0x2fe940,REGISTRARS[0])
        assert hits==set(ENTRIES),hits
    print(f'object creation retail: {cases} RAM/defined-return/ordered-call cases; all 20 bodies; allocator/registrar/field/virtual leaves controlled')
if __name__=='__main__':main()
