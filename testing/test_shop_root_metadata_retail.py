#!/usr/bin/env python3
"""ShopCtrl00 metadata block and WindowCtrl parent callback vs original code.

Shared metadata registration, allocation, header initialization and temporary
cleanup are controlled leaves. This does not accept shop UI or transactions.
"""
import ctypes as C
import itertools
from pathlib import Path
import subprocess
import tempfile
from test_subwindow_lifecycle_retail import LifecycleWorld,ROOT,Api,READ,WRITE,CALL,MASK,STACK

ENTRIES=(0x3b65b0,0x3b8d90,0x3b8dd0,0x3b8e20,0x3b8ea0,0x3b8ec0,0x3b8f30)
META,ALT,SYSTEM,INSTANCE,SCRATCH=range(0x1c00000,0x1c50000,0x10000)
SIZES={0x3b65b0:0,0x3b8d90:32,0x3b8dd0:16,0x3b8e20:128,0x3b8ea0:16,0x3b8ec0:48,0x3b8f30:16}

class MetadataWorld(LifecycleWorld):
    def __init__(self,image):
        super().__init__(image);self.descend=set(ENTRIES);self.frame=STACK-128
        self.ready=False;self.mutation=None;self.result=0;self.allocate_result=INSTANCE;self.init_offset=None
        self.w(0x58ae30,4,META);self.w(0x58b010,4,ALT);self.w(META+36,4,4);self.w(ALT+36,4,4)
        self.w(0x586dc8,4,SYSTEM);self.w(SYSTEM+916,4,0)
    def call_hook(self,e):
        old=self.frame;self.frame=self.r[29]&0xffffffff
        try:
            args=self.r[4:12]
            if e==0x2fe9c0:args=args+[self.read(self.frame+i,8) for i in (0,8,16)]
            self.r[2]=self.call(e,args)&MASK
        finally:self.frame=old
    def call(self,e,args):
        counts={0x2fda40:2,0x2fe940:1,0x2fef20:1,0x3b6430:2,0x3b0a10:0,0x2fe9c0:11}
        assert e in counts,hex(e)
        raw=list(args[:counts[e]]);v=[x&0xffffffff for x in raw];normalized=list(raw)
        if e in (0x2fef20,0x3b6430):normalized[0]='temporary'
        temp=tuple(self.read(v[0]+i,4) for i in range(0,84,4)) if e in (0x2fef20,0x3b6430) else ()
        self.events.append((e,tuple(normalized),(self.read(0x58ae30,4),self.read(META+36,4),self.read(ALT+36,4),temp)))
        if e==0x2fe940:
            assert v[0]==0x3b8ec0
            if self.ready:
                self.w(0x58ae30,4,ALT);self.w(ALT+36,4,self.read(ALT+36,4)|4)
        if e==0x2fda40:return self.allocate_result&MASK
        if e==0x2fef20:
            self.w(v[0],4,0x52f0f0);self.w(v[0]+4,4,0x101)
            if self.init_offset is not None:self.w(SYSTEM+916,4,self.init_offset)
            return v[0]
        if e==0x3b6430:
            self.w(v[0],4,0x53daa0)
            if self.mutation=='cleanup':self.w(v[0]+self.read(SYSTEM+916,4),4,0xdeadbeef)
        if e==0x2fe9c0:
            assert v==[0,0x58ae30,0x3bb630,0x3b65b0,0x3b8f30,0x5115a0,84,0x3b8e20,0,0,0],v
            return self.result&MASK
        return 0


def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();native=MetadataWorld(image)
    cases=0;covered=set();errors=[];depth=0
    @CALL
    def call(_,e,args):
        try:return invoke(e,args)&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-shop-root-metadata-') as td:
        so=Path(td)/'metadata.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/shop-root-metadata.c'),'-o',str(so)],check=True)
        fn=C.CDLL(str(so)).dw4_shop_root_metadata
        fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        def invoke(e,args):
            nonlocal depth
            if e not in ENTRIES:return native.call(e,args)&MASK
            depth+=1;old=native.frame;native.frame=SCRATCH+depth*256
            try:return fn(C.byref(api),e,args,native.frame)
            finally:native.frame=old;depth-=1
        def compare(w,entry,*args,result=True):
            nonlocal cases
            errors.clear();w.events=[]
            for key,value in w.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image','frame'):
                    setattr(native,key,value.copy() if isinstance(value,(list,dict,set)) else value)
            for i in range(SIZES[entry]):native.w(SCRATCH+256+i,1,w.read(STACK-SIZES[entry]+i,1))
            expected=w.invoke(entry,*args);actual=invoke(entry,(C.c_uint64*8)(*[x&MASK for x in args]))
            assert not errors,errors
            if result:assert expected==actual,(hex(entry),hex(expected),hex(actual))
            def ram(obj):return {p:v for p,v in obj.mem.items() if v and not STACK-0x10000<=p<STACK+64 and not SCRATCH<=p<SCRATCH+0x10000}
            assert ram(w)==ram(native),(hex(entry),'RAM')
            assert w.events==native.events,(hex(entry),'events',w.events,native.events)
            cases+=1;covered.update(w.covered)
        for handle in (0,META,ALT,0x81234567):
            w=MetadataWorld(image);w.w(0x58b010,4,handle);compare(w,0x3b65b0)
        for handle,flags,ready in itertools.product((0,META),(0,1,2,3,4,7,8,0xffffffff),(False,True)):
            for entry in (0x3b8dd0,0x3b8f30):
                w=MetadataWorld(image);w.w(0x58ae30,4,handle);w.w(META+36,4,flags);w.ready=ready;compare(w,entry)
        for allocator,result,ready in itertools.product((0,0x1d00000,0xffffffff),(0,INSTANCE,0xffffffff),(False,True)):
            w=MetadataWorld(image);w.allocate_result=result;w.ready=ready;compare(w,0x3b8d90,allocator)
        for result in (0,0x12345678,0x80000000,0x100000001):
            w=MetadataWorld(image);w.result=result;compare(w,0x3b8ec0)
        for ready in (False,True):
            w=MetadataWorld(image);w.ready=ready;compare(w,0x3b8ea0,result=False)
        for offset,cleanup in itertools.product((0,4,8,48,52,56,60,64,68,72,76,80),('none','cleanup')):
            w=MetadataWorld(image);w.w(SYSTEM+916,4,offset);w.mutation=cleanup
            for i in range(84):w.w(STACK-128+32+i,1,(i*13+7)&255)
            compare(w,0x3b8e20)
        w=MetadataWorld(image);w.init_offset=4;compare(w,0x3b8e20)
        expected={p for entry in ENTRIES for p in range(entry,entry+{0x3b65b0:12,0x3b8d90:52,0x3b8dd0:76,0x3b8e20:116,0x3b8ea0:32,0x3b8ec0:100,0x3b8f30:28}[entry],4)}
        missing=expected-covered
        assert not missing,sorted(hex(p) for p in missing)
        assert w.read(0x3b8dfc,4)==0
        print(f'Shop root metadata: {cases} RAM/return/ordered-call cases, 104/104 instruction addresses; registration/header/cleanup remain leaves')


if __name__=='__main__':main()
