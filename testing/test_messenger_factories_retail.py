#!/usr/bin/env python3
"""Compose real factory/reflection construction through cold messenger lifecycle.

Synthetic metadata has one controlled payload-construction field per class.
Concrete field constructors/registrars and allocator services remain leaves.
"""
import argparse,ctypes as C,subprocess,tempfile
from pathlib import Path
from test_messenger_memory_retail import Memory,ENTRIES as MEMORY,LIFE,DISPATCH,MSG,STACK,MASK,Api,READ,WRITE,CALL,ROOT
from test_object_creation_retail import Creation,ENTRIES as CREATION,FACTORIES,REGISTRARS,HANDLES,ALLOCATE,ALLOC,SYSTEM,VT,FVT,VOP,VOTHER,META,OWNER
TYPES=[0x1870000+i*0x100 for i in range(4)]
TABLES=[0x1880000+i*0x1000 for i in range(4)]
FIELDS=[0x1890000+i*0x1000 for i in range(4)]
class Factories(Memory):
    def __init__(self,image):
        super().__init__(image);Creation.setup_core(self);self.descend|=set(CREATION)
        self.owner=False;self.current_kind=0;self.pending={}
        for i,(meta,table,fields) in enumerate(zip(TYPES,TABLES,FIELDS)):
            self.w(HANDLES[i],4,meta);self.w(meta+26,1,0);self.w(meta+32,4,0);self.w(meta+36,4,4)
            self.w(meta+40,4,fields);self.w(meta+44,4,0);self.w(meta+48,4,0);self.w(meta+60,4,0)
            self.w(meta+72,4,(32,24,48,48)[i]);self.w(meta+92,4,table);self.w(meta+96,4,0)
            for slot in (8,12,36,40,44,48,52,72,80,88):self.w(table+slot,4,VOP+slot)
            self.w(fields+8,4,fields+0x80);self.w(fields+12,4,1);self.w(fields+0x80,4,fields+0x100);self.w(fields+0x100,4,FVT)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e in REGISTRARS:
            self.events.append((e,));self.current_kind=REGISTRARS.index(e);self.w(HANDLES[self.current_kind],4,TYPES[self.current_kind]);return 0
        if e in (0x301000,0x2f88e0):self.events.append((e,v[0]));return ALLOC
        if e==ALLOCATE:
            self.events.append((e,*v[:2]));kind=self.current_kind;factory=FACTORIES[kind]
            index=self.factory_counts.get(factory,0);self.factory_counts[factory]=index+1
            obj=(0x1300000+index*0x400,0x1500000+index*0x400,0x1400000+index*0x100,0x1000000+index*0x1000)[kind]
            self.pending[obj]=(kind,index);return obj
        if e==0x300d30:self.events.append((e,));return v[0]
        if e==VOP+88:
            self.events.append((e,v[0]));return TYPES[TABLES.index(self.read(v[0],4))]
        if e in (VOP+124,VOP+132,VOP+240):
            self.events.append((e,*v[:1 if e==VOP+240 else 2]))
            if e==VOP+124:
                kind,index=self.pending[v[1]];header=self.read(v[1]+4,4)
                if kind==0:self.work_object(index)
                elif kind==2:self.delay_object(index)
                elif kind==3:self.arg_object(index)
                else:
                    for offset,delta in ((12,0x100),(16,0x200),(20,0x300)):
                        self.w(v[1]+offset,4,v[1]+delta);self.list(v[1]+delta,[])
                self.w(v[1]+4,4,header)
            return 1 if e==VOP+240 else 0
        if e in (0x2f04f0,0x2ffc10,0x2ffcb0,0x2ed460) or VOP<=e<VOP+256 or VOTHER<=e<VOTHER+256:
            return Creation.call(self,e,args)
        return Memory.call(self,e,args)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=p.parse_args()
    image=args.elf.read_bytes();retail=Factories(image);native=Factories(image);errors=[];cases=0;depth=0
    @CALL
    def call(_,e,values):
        nonlocal depth
        try:
            if e in CREATION:return creation(C.byref(api),e,values)
            if e in MEMORY:return memory(C.byref(api),e,values)
            if e in LIFE or e in DISPATCH:
                depth+=1
                try:return (life if e in LIFE else dispatch)(C.byref(api),e,values,STACK-0x1000-depth*0x100)
                finally:depth-=1
            return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-messenger-factories-') as td:
        so=Path(td)/'factories.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/name) for name in ('object-creation.c','messenger-memory.c','messenger-lifecycle.c','messenger-dispatch.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));creation=lib.dw4_object_creation;memory=lib.dw4_messenger_memory
        for fn in (creation,memory):fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];fn.restype=C.c_uint64
        life=lib.dw4_messenger_lifecycle;dispatch=lib.dw4_messenger_dispatch
        for fn in (life,dispatch):fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[];retail.invoke(entry,*values);v=(C.c_uint64*8)(*[x&MASK for x in values])
            if entry in CREATION:creation(C.byref(api),entry,v)
            elif entry in MEMORY:memory(C.byref(api),entry,v)
            else:(life if entry in LIFE else dispatch)(C.byref(api),entry,v,STACK-0x1000)
            assert not errors,errors
            def ram(world):return {p:v for p,v in world.mem.items() if not STACK-0x4000<=p<STACK+32 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events[:30],native.events[:30])
            assert retail.factory_counts==native.factory_counts;cases+=1
        for factory in FACTORIES:compare(factory,ALLOC)
        # Fresh upper-engine state, with actual factory/create/field-pass bodies.
        retail=Factories(image);retail.w(MSG+48,1,0)
        compare(0x38d050,MSG)
        assert retail.factory_counts=={0x358d80:5,0x358070:64,0x358950:32}
        compare(0x38e670,MSG,retail.token('MODELCTRL'),retail.token('SEARCH'))
        compare(0x38ecf0,MSG,retail.token('MODELCTRL'),retail.token('EVENT'),0)
        compare(0x38d0a0,MSG);compare(0x38ed70,MSG);compare(0x38ef50,MSG)
        compare(0x38c490,MSG);compare(0x38d050,MSG)
        # This fixture also exercises group construction through the registry-miss
        # registration route while keeping actual registry behavior controlled.
        retail.registry_exists=False
        compare(0x38d560,MSG,0x1905000,retail.token('MODELCTRL'),0,7)
    print(f'messenger factories retail: {cases} persistent RAM/ordered-call cases through real factories/create/construct/field passes and cold lifecycle; concrete field/registrar/allocation services controlled')
if __name__=='__main__':main()
