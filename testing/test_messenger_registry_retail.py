#!/usr/bin/env python3
"""Compose actual property lookup/name and object/generic lists in cold messaging.

Concrete metadata/fields, allocator, byte and interner services remain leaves.
"""
import argparse,ctypes as C,subprocess,tempfile
from pathlib import Path
from test_messenger_factories_retail import Factories,CREATION,MEMORY,LIFE,DISPATCH,MSG,ROOT,STACK,MASK,Api,READ,WRITE,CALL,VOP
from test_object_lists_retail import ENTRIES as OBJECTS
from test_list_services_retail import ENTRIES as GENERIC
from test_messenger_lifecycle_retail import CONTEXTS
from test_messenger_dispatch_retail import REG,CACHE,QUEUE,NAMES,IDS,RECEIVERS,CIDS,CRECV,RECORD,BASE
PUSH=0x1730000
LISTVT,LISTMETA,FIELD,FVT,TAG,DESC=range(0x18f0000,0x18f6000,0x1000)
CLASS_CALL,UNIT_CALL=0x18f0800,0x18f0900
class Registry(Factories):
    def __init__(self,image):
        super().__init__(image);self.descend|=set(OBJECTS)|set(GENERIC);self.buffers=0
        self.w(LISTVT+88,4,CLASS_CALL);self.w(LISTMETA+60,4,FIELD);self.w(FIELD,4,FVT);self.w(FVT+100,4,UNIT_CALL)
        self.w(0x5867a0,4,TAG);self.w(TAG+18,2,17);self.w(0x585be0,4,DESC);self.w(DESC+8,4,8)
        self.list(REG,[RECORD]);self.w(RECORD+8,4,self.token('MODELCTRL'))
        for p in (REG,CACHE,QUEUE,PUSH,NAMES,IDS,RECEIVERS,CIDS,CRECV):self.attach(p)
        for ctx in CONTEXTS:self.attach_context(ctx)
    def attach(self,p):self.w(p,4,LISTVT)
    def attach_context(self,p):
        for offset in range(16,48,4):self.attach(self.read(p+offset,4))
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==VOP+124:
            result=super().call(e,args);kind,_=self.pending[v[1]]
            if kind==0:
                for offset in (24,28):self.attach(self.read(v[1]+offset,4))
            elif kind==1:
                for offset in (12,16,20):self.attach(self.read(v[1]+offset,4))
            elif kind==2:self.attach_context(self.read(v[1]+40,4))
            else:self.attach_context(v[1])
            return result
        if e in (CLASS_CALL,UNIT_CALL,0x2fdf00,0x2fb190,0x300f50,0x127098,0x127148,0x12724c):
            n={CLASS_CALL:1,UNIT_CALL:1,0x2fdf00:2,0x2fb190:5,0x300f50:2,0x127098:3,0x127148:3,0x12724c:3}[e]
            self.events.append((e,*['temp' if STACK-0x4000<=p<STACK else p for p in v[:n]]))
            if e in (CLASS_CALL,0x2fdf00):return LISTMETA
            if e==UNIT_CALL:return 4
            if e==0x2fb190:
                p=0x1b00000+self.buffers*0x1000;self.buffers+=1;self.w(v[2]+16,4,p);self.w(v[0],4,p);return 0
            if e in (0x127098,0x127148):
                assert v[2]<0x10000
                data=bytes(self.read(v[1]+i,1) for i in range(v[2]))
                for i,byte in enumerate(data):self.w(v[0]+i,1,byte)
                return v[0]
            if e==0x12724c:
                assert v[2]<0x10000
                for i in range(v[2]):self.w(v[0]+i,1,v[1])
                return v[0]
            return 0
        return super().call(e,args)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=p.parse_args()
    image=args.elf.read_bytes();retail=Registry(image);native=Registry(image);errors=[];cases=0;depth=0
    @CALL
    def call(_,e,values):
        nonlocal depth
        try:
            if e in OBJECTS:return objects(C.byref(api),e,values)
            if e in CREATION:return creation(C.byref(api),e,values)
            if e in MEMORY:return memory(C.byref(api),e,values)
            depth+=1
            try:
                if e in GENERIC:return generic(C.byref(api),e,values,STACK-0x800-depth*0x100)
                if e in LIFE or e in DISPATCH:return (life if e in LIFE else dispatch)(C.byref(api),e,values,STACK-0x1000-depth*0x100)
            finally:depth-=1
            return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-messenger-registry-') as td:
        so=Path(td)/'registry.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/name) for name in ('object-lists.c','list-services.c','object-creation.c','messenger-memory.c','messenger-lifecycle.c','messenger-dispatch.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));objects=lib.dw4_object_list;creation=lib.dw4_object_creation;memory=lib.dw4_messenger_memory
        for fn in (objects,creation,memory):fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];fn.restype=C.c_uint64
        generic=lib.dw4_list_service;life=lib.dw4_messenger_lifecycle;dispatch=lib.dw4_messenger_dispatch
        for fn in (generic,life,dispatch):fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[];retail.invoke(entry,*values);v=(C.c_uint64*8)(*[x&MASK for x in values])
            if entry in OBJECTS:objects(C.byref(api),entry,v)
            elif entry in MEMORY:memory(C.byref(api),entry,v)
            else:(life if entry in LIFE else dispatch)(C.byref(api),entry,v,STACK-0x1000)
            assert not errors,errors
            def ram(world):return {p:v for p,v in world.mem.items() if not STACK-0x4000<=p<STACK+32 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events[:40],native.events[:40])
            cases+=1
        retail.w(MSG+48,1,0);compare(0x38d050,MSG)
        for key in ('SEARCH','FIND_SPACE','EVENT'):compare(0x38e670,MSG,retail.token('MODELCTRL'),retail.token(key))
        receiver=BASE+0x5000
        compare(0x38d560,MSG,receiver,retail.token('NEWGROUP'),retail.token('first'),7)
        assert retail.read(REG+8,4)==2
        compare(0x38e5f0,MSG,retail.token('NEWGROUP'),retail.token('first'),7,retail.token('SEARCH'))
        compare(0x38eca0,MSG,retail.token('NEWGROUP'),retail.token('first'),7,retail.token('EVENT'),0)
        compare(0x38d0a0,MSG);compare(0x38ed70,MSG);compare(0x38ef50,MSG)
        compare(0x38c490,MSG);compare(0x38d050,MSG)
        assert retail.read(REG+8,4)==0
    print(f'messenger registry retail: {cases} persistent RAM/ordered-call checkpoints with real registry/name/object/generic lists and cold lifecycle; concrete fields/interner/allocator/byte services controlled')
if __name__=='__main__':main()
