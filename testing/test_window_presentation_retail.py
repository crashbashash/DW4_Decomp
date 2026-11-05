#!/usr/bin/env python3
"""Full text/model presentation run and shared title vs original instructions.

String pool/list/receiver services and title-specific initialization are leaves;
window/tree/title/root bodies can compose without copied retail output.
"""
import ctypes as C
import itertools
import json
from pathlib import Path
import subprocess
import tempfile
from test_window_tree_retail import WindowWorld,CLOSE,INIT,UPDATE,SHOP,REFERENCES,WINDOW,LIST,VTABLES,FACTORIES,SCRATCH,ROOT,Api,READ,WRITE,CALL,MASK,STACK

ENTRIES=(0x3f59b0,0x3f5a40,0x3f5c90,0x3f5f00,0x3f5f40,0x3f5f80,0x3f6090,0x424160)
SIZES={0x3f59b0:64,0x3f5a40:144,0x3f5c90:144,0x3f5f00:32,0x3f5f40:16,0x3f5f80:144,0x3f6090:144,0x424160:32,SHOP:80,INIT:96,UPDATE:96,CLOSE:0}
TYPES,NAMES,MODELS,IDS,SEQUENCES,ALTLIST=range(0x1c00000,0x1c60000,0x10000)
TOKENS=[0x1d00100+i*0x1000 for i in range(20)]
POOL,RGB,EMPTYLIST,TITLE_INIT=0x1e00000,0x1e10000,0x1e30000,0x1e40000

class PresentationWorld(WindowWorld):
    def __init__(self,image):
        super().__init__(image);self.descend.update(ENTRIES)
        self.running=0;self.result_count=1;self.allocation=True;self.empty_token=0;self.present_mutation=None;self.pool_calls=0;self.count_results=[];self.boolean_results=[]
        self.w(0x586f20,4,POOL);self.w(VTABLES+96,4,TITLE_INIT)
        for i,p in enumerate(TOKENS):
            self.w(p-8,4,POOL);self.w(p-4,4,1)
            for j,b in enumerate(('token%02d'%i).encode()+b'\0'):self.w(p+j,1,b)
        for i,bits in enumerate((0x3f800000,0x80000000,0x7fc00001)):self.w(RGB+i*4,4,bits)
        for offset,p in zip((60,64,68,72,76),(TYPES,NAMES,MODELS,IDS,SEQUENCES)):
            self.w(WINDOW+offset,4,p);self.make_list(p,[])
        self.make_list(ALTLIST,[]);self.make_list(EMPTYLIST,[])
    def snapshot(self):
        base=super().snapshot()
        return (*base,tuple((self.read(p+8,4),tuple(self.values(p))) for p in (TYPES,NAMES,MODELS,IDS,SEQUENCES,ALTLIST)),tuple(self.read(p-4,4) for p in TOKENS),self.read(0x586f20,4))
    def call(self,e,args):
        counts={0x1c64e0:3,0x1ca620:2,0x30c940:2,0x2eb010:1,0x2eadf0:1,0x2eaf60:2,0x2d6790:3,
                0x38f4b0:2,0x38f0f0:1,0x38f220:2,TITLE_INIT:1}
        if e not in counts:
            result=super().call(e,args)
            if e in FACTORIES:
                for off in (60,64,68,72,76):self.w(result+off,4,EMPTYLIST)
                self.w(result,4,VTABLES+0x2000);self.w(VTABLES+0x2000+92,4,0x424160);self.w(VTABLES+0x2000+96,4,TITLE_INIT)
            if self.present_mutation=='message' and e in (0x38d860,0x38f830,0x38e060,0x38e5f0):self.w(WINDOW+12,4,0x1b05000)
            return result
        raw=list(args[:counts[e]]);v=[x&0xffffffff for x in raw];normalized=list(raw)
        if e==0x1c64e0:normalized[0]=('cell',v[0]-self.frame)
        if e==0x1ca620:normalized[1]=('cell',v[1]-self.frame,self.read(v[1],4))
        if e==0x38f4b0:normalized[1]=tuple(self.read(v[1]+i*4,4) for i in range(3))
        self.events.append((e,tuple(normalized),self.snapshot()))
        if e==0x1c64e0:
            token=self.read(self.read(v[1]+16,4)+v[2]*4,4);self.w(v[0],4,token)
            if token:self.w(token-4,4,self.read(token-4,4)+1)
        if e==0x1ca620:
            token=self.read(v[1],4);n=self.read(v[0]+8,4);self.w(self.read(v[0]+16,4)+n*4,4,token);self.w(v[0]+8,4,n+1)
            if token:self.w(token-4,4,self.read(token-4,4)+1)
            if self.present_mutation=='temp':self.w(v[1],4,TOKENS[18] if v[1]-self.frame==140 else TOKENS[19])
        if e==0x30c940:
            if self.present_mutation=='free_message':self.w(WINDOW+12,4,0x1b06000)
            if self.present_mutation=='free_list':self.w(WINDOW+60,4,ALTLIST)
        if e==0x2eb010:return POOL+128 if self.allocation else 0
        if e==0x2eadf0:return POOL
        if e==0x2eaf60:
            token=v[1] if v[1] else self.empty_token
            if token:self.w(token-4,4,self.read(token-4,4)+1)
            self.pool_calls+=1
            if self.present_mutation=='drop_pool':self.w(0x586f20,4,0)
            return token
        if e==0x2d6790:
            if self.present_mutation=='relocate':
                data=self.read(v[0]+16,4);new=data+0x1000
                for i in range(self.read(v[0]+8,4)):self.w(new+i*4,4,self.read(data+i*4,4))
                self.w(v[0]+16,4,new)
            self.w(v[0]+8,4,v[1]);self.w(v[0]+12,4,v[1]);return 0
        if e==0x38f0f0:return (self.count_results.pop(0) if self.count_results else self.result_count)&MASK
        if e==0x38f220:return (self.boolean_results.pop(0) if self.boolean_results else self.running)&MASK
        if e==TITLE_INIT:
            if self.present_mutation=='init_state':self.w(v[0]+28,4,0x7fffffff)
            return 0
        return 0


def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();native=PresentationWorld(image)
    errors=[];cases=0;covered=set();depth=0
    @CALL
    def call(_,e,args):
        try:return invoke(e,args)&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-window-presentation-') as td:
        so=Path(td)/'presentation.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in ('window-presentation.c','window-tree.c','shop-root-update.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));present=lib.dw4_window_presentation;tree=lib.dw4_window_tree;shop=lib.dw4_shop_root_update
        present.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];present.restype=C.c_uint64
        tree.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];tree.restype=C.c_uint64
        shop.argtypes=[C.POINTER(Api),C.POINTER(C.c_uint64),C.c_uint32];shop.restype=C.c_uint64
        def invoke(e,args):
            nonlocal depth
            if e not in native.descend:return native.call(e,args)&MASK
            depth+=1;old=native.frame;native.frame=SCRATCH+depth*512
            try:
                if e in ENTRIES:return present(C.byref(api),e,args,native.frame)
                if e==SHOP:return shop(C.byref(api),args,native.frame)
                return tree(C.byref(api),e,args)
            finally:native.frame=old;depth-=1
        def compare(w,entry,*args):
            nonlocal cases
            w.events=[];errors.clear()
            for key,value in w.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image','frame'):
                    setattr(native,key,value.copy() if isinstance(value,(list,dict,set)) else value)
            for i in range(SIZES[entry]):native.w(SCRATCH+512+i,1,w.read(STACK-SIZES[entry]+i,1))
            expected=w.invoke(entry,*args);actual=invoke(entry,(C.c_uint64*8)(*[x&MASK for x in args]))
            assert not errors,errors
            if entry==0x3f6090:assert expected==actual,(hex(expected),hex(actual))
            def ram(obj):return {p:v for p,v in obj.mem.items() if v and not STACK-0x10000<=p<STACK+64 and not SCRATCH<=p<SCRATCH+0x10000}
            er,ar=ram(w),ram(native)
            assert er==ar,[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12]
            if w.events!=native.events:
                i=next((i for i,(x,y) in enumerate(zip(w.events,native.events)) if x!=y),min(len(w.events),len(native.events)))
                raise AssertionError((hex(entry),'event',i,w.events[i:i+1],native.events[i:i+1]))
            cases+=1;covered.update(w.covered)
        for entry in (0x3f59b0,0x3f5f40):compare(PresentationWorld(image),entry,WINDOW,TOKENS[0],TOKENS[1],TOKENS[2])
        for entry,running,track,name in itertools.product((0x3f5c90,0x3f5f00),(0,1,2,256),(0,TOKENS[2]),(0,TOKENS[0])):
            w=PresentationWorld(image);w.running=running;compare(w,entry,WINDOW,name,7,TOKENS[1],track,RGB)
        for entry,count in itertools.product((0x3f5a40,0x3f5f80,0x3f6090),range(4)):
            w=PresentationWorld(image)
            for p,vals in ((TYPES,TOKENS[:count]),(NAMES,TOKENS[4:4+count]),(MODELS,TOKENS[8:8+count]),(IDS,list(range(count))),(SEQUENCES,TOKENS[12:12+count])):w.make_list(p,vals)
            compare(w,entry,WINDOW)
        for state in (-1,0,1,2,3,4):
            w=PresentationWorld(image);w.w(WINDOW,4,VTABLES);w.w(WINDOW+28,4,state);compare(w,0x424160,WINDOW)
        for entry,refs,pool,allocation in itertools.product((0x3f5a40,0x3f5f80,0x3f6090),(0,1,2),(0,POOL),(False,True)):
            w=PresentationWorld(image);w.w(0x586f20,4,pool);w.allocation=allocation
            for p,values in ((TYPES,TOKENS[:2]),(NAMES,TOKENS[4:6]),(MODELS,TOKENS[8:10]),(IDS,[1,2]),(SEQUENCES,TOKENS[12:14])):w.make_list(p,values)
            for token in TOKENS:w.w(token-4,4,refs)
            compare(w,entry,WINDOW)
        for pool,allocation,capacity,refs in itertools.product((0,POOL),(False,True),(0,32),(0,1)):
            w=PresentationWorld(image);w.w(0x586f20,4,pool);w.allocation=allocation;w.w(IDS+12,4,capacity)
            for token in TOKENS:w.w(token-4,4,refs)
            compare(w,0x3f5c90,WINDOW,TOKENS[0],0xffffffff,TOKENS[1],TOKENS[2],RGB)
        for count,running,children in itertools.product((-1,0,1,2,0x100000000),(0,1,256),(0,1)):
            w=PresentationWorld(image);w.result_count=count;w.running=running;w.w(LIST+8,4,children)
            w.make_list(MODELS,TOKENS[:2]);w.make_list(IDS,[3,4]);w.make_list(SEQUENCES,TOKENS[4:6]);compare(w,0x3f6090,WINDOW)
        for mutation,entry in itertools.product(('message','free_message','temp','relocate','drop_pool'),(0x3f5a40,0x3f5c90,0x3f6090)):
            w=PresentationWorld(image);w.present_mutation=mutation;w.w(IDS+12,4,0)
            for p,values in ((TYPES,TOKENS[:2]),(NAMES,TOKENS[4:6]),(MODELS,TOKENS[8:10]),(IDS,[1,2]),(SEQUENCES,TOKENS[12:14])):w.make_list(p,values)
            compare(w,entry,WINDOW,TOKENS[0],7,TOKENS[1],TOKENS[2],RGB)
        for entry in (0x3f5a40,0x3f6090):
            w=PresentationWorld(image);w.empty_token=TOKENS[19]
            for p,values in ((TYPES,TOKENS[:2]),(NAMES,TOKENS[4:6]),(MODELS,TOKENS[8:10]),(IDS,[1,2]),(SEQUENCES,TOKENS[12:14])):w.make_list(p,values)
            compare(w,entry,WINDOW)
        for entry in (0x3f5a40,0x3f5f80,0x3f6090):
            w=PresentationWorld(image)
            for p in (TYPES,NAMES,MODELS,SEQUENCES):w.w(p+8,4,0xffffffff)
            compare(w,entry,WINDOW)
        w=PresentationWorld(image);w.present_mutation='init_state';w.w(WINDOW,4,VTABLES);compare(w,0x424160,WINDOW)
        # Poll the second model as pending, then finish with the same retained queues.
        w=PresentationWorld(image);w.make_list(MODELS,TOKENS[:2]);w.make_list(IDS,[0,1]);w.make_list(SEQUENCES,TOKENS[4:6])
        w.count_results=[0,1];w.boolean_results=[1];compare(w,0x3f6090,WINDOW);compare(w,0x3f6090,WINDOW)
        # Actual root -> actual tree -> actual title -> actual presentation close.
        for mode in range(11):
            w=PresentationWorld(image);w.w(WINDOW+44,4,mode)
            compare(w,UPDATE,WINDOW);compare(w,UPDATE,WINDOW)
            w.w(WINDOW+28,4,2)
            for _ in range(4):compare(w,UPDATE,WINDOW)
        expected={p for r in json.loads((ROOT/'data/function-extents.json').read_text()) if int(r['address'],0) in ENTRIES for p in range(int(r['address'],0),int(r['end_exclusive'],0),4)}
        rows=[r for r in json.loads((ROOT/'data/function-extents.json').read_text()) if int(r['address'],0) in ENTRIES]
        occupied={p for r in rows for span in r['body_ranges'] for p in range(int(span['start'],0),int(span['end_exclusive'],0),4)}
        padding=expected-occupied;unreachable={0x3f5e54,0x3f5e58}
        assert len(padding)==4 and expected-covered==padding|unreachable,sorted(hex(p) for p in expected-covered-padding-unreachable)
        assert all(w.read(p,4)==0 for p in padding)
        assert len(expected&covered)==651
        print(f'Window presentation: {cases} RAM/return/ordered-call cases, 651/657 instruction addresses (four padding NOPs, two ABI-unreachable words); pool/list/model/text/init services remain leaves')


if __name__=='__main__':main()
