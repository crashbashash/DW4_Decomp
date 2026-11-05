#!/usr/bin/env python3
"""Window parent binding, recursive update and concrete shop root vs retail.

Factories, shared object/message/list/UI services and synthetic child virtual
methods are controlled leaves. Real shop-root and window-tree bodies can compose.
"""
import ctypes as C
import itertools
import json
from pathlib import Path
import subprocess
import tempfile
from test_subwindow_lifecycle_retail import LifecycleWorld,ROOT,Api,READ,WRITE,CALL,MASK,STACK

CLOSE,INIT,UPDATE,SHOP=0x3f6350,0x3f63c0,0x3f6490,0x4267b0
REFERENCES=(0x426fa0,0x427020)
WINDOW,PARENT,OLD,INSIGHT,LIST,ALTLIST,CHILDREN,ALTCHILD,VTABLES,VIRTUAL,NEW,REPLACEMENT,SCRATCH=range(0x1a00000,0x1ad0000,0x10000)
FACTORIES=(0x3b3370,0x3b3ac0,0x3b3900,0x3b36f0,0x3b31b0,0x3b8b60,0x3b8630,0x3b8400,0x3b81d0,0x3b6650,0x3b6310)

class WindowWorld(LifecycleWorld):
    def __init__(self,image):
        super().__init__(image);self.descend={CLOSE,INIT,UPDATE,SHOP,*REFERENCES};self.frame=STACK-80
        self.phase_gate=0;self.close_result=0;self.created_refs=1;self.mutate=None
        self.inject_temp=None;self.factory_count=0;self.virtual_calls=[];self.remove=[];self.virtual_actions={}
        self.w(0x588f38,4,0x1234);self.w(0x588518,4,0x5678)
        for i,p in enumerate((WINDOW,PARENT,OLD,ALTCHILD,REPLACEMENT,*[CHILDREN+j*256 for j in range(4)])):
            self.window(p,LIST if p==WINDOW else p+0x8000,i)
        self.w(WINDOW,4,0x53feb0);self.w(WINDOW+56,4,OLD);self.w(WINDOW+44,4,6)
        self.make_list(ALTLIST,[]);self.make_list(LIST,[])
    def values(self,p):
        count=self.read(p+8,4);count=count-(1<<32) if count>>31 else count
        return [self.read(self.read(p+16,4)+i*4,4) for i in range(max(0,count))]
    def make_list(self,p,items):
        self.w(p+8,4,len(items));self.w(p+12,4,32);self.w(p+16,4,p+0x4000)
        for i,value in enumerate(items):self.w(p+0x4000+i*4,4,value)
    def window(self,p,listp,index):
        self.w(p,4,VTABLES+index*128);self.w(VTABLES+index*128+92,4,VIRTUAL)
        self.w(p+4,4,1);self.w(p+8,4,INSIGHT);self.w(p+12,4,0x1b00000);self.w(p+20,4,2)
        self.w(p+24,1,1);self.w(p+28,4,0);self.w(p+32,4,0);self.w(p+36,4,5);self.w(p+40,4,7)
        self.w(p+52,4,listp);self.make_list(listp,[])
    def snapshot(self):
        return (tuple(self.read(WINDOW+i,4) for i in (4,8,12,16,20,24,28,32,36,40,44,52,56,80)),
                tuple(self.values(LIST)),tuple(self.values(ALTLIST)),self.read(PARENT+4,4),self.read(OLD+4,4))
    def call_hook(self,e):
        old=self.frame;self.frame=self.r[29]&0xffffffff
        try:self.r[2]=self.call(e,self.r[4:12])&MASK
        finally:self.frame=old
    def call(self,e,args):
        counts={0x100610:1,0x2ff820:1,0x236f80:2,0x301e30:2,0x2d6cf0:2,VIRTUAL:1,
                0x301000:1,0x2f88e0:1,0x38d860:4,0x38f830:2,0x38e060:2,0x38f220:2,
                0x38e5f0:5,0x3f5f80:1,0x3f5a40:1,0x3f6350:1,0x3f6090:1,**{p:1 for p in FACTORIES}}
        assert e in counts,hex(e)
        raw=list(args[:counts[e]]);v=[x&0xffffffff for x in raw]
        self.events.append((e,tuple(raw),self.snapshot()))
        if e==0x236f80:
            if self.mutate=='lookup':self.w(WINDOW+20,4,99);self.w(WINDOW+44,4,99)
            return 0x1b00000 if v[1]==0x1234 else 0x1b01000
        if e==0x2ff820:
            if self.mutate=='delete_parent':self.w(WINDOW+56,4,REPLACEMENT)
            if self.mutate=='delete_list':self.w(WINDOW+52,4,ALTLIST)
            return 0
        if e==VIRTUAL:
            self.virtual_calls.append(v[0]);action=self.virtual_actions.get(v[0])
            if action=='close':self.w(v[0]+24,1,0)
            if action=='parent_close':self.w(WINDOW+24,1,0)
            if action=='swap':self.w(WINDOW+52,4,ALTLIST)
            if action=='grow':
                p=self.read(WINDOW+52,4);n=self.read(p+8,4);self.w(self.read(p+16,4)+n*4,4,ALTCHILD);self.w(p+8,4,n+1)
            return 0
        if e==0x301e30:
            p,n=v[0],self.read(v[0]+8,4);self.w(self.read(p+16,4)+n*4,4,v[1]);self.w(p+8,4,n+1)
            if v[1]:self.w(v[1]+4,4,self.read(v[1]+4,4)+1)
            if self.mutate=='append_temp':self.w(self.frame+56,4,REPLACEMENT)
            if self.mutate=='append_swap':self.w(WINDOW+52,4,ALTLIST)
            if self.mutate=='append_close':self.w(v[1]+24,1,0)
            return 0
        if e==0x2d6cf0:
            self.remove.append((v[0],v[1]));items=self.values(v[0]);items.pop(v[1]);data=self.read(v[0]+16,4)
            if self.mutate=='remove_relocate':data+=0x1000;self.w(v[0]+16,4,data)
            for i,item in enumerate(items):self.w(data+i*4,4,item)
            self.w(v[0]+8,4,len(items));return 0
        if e==0x301000:
            if self.inject_temp is not None:self.w(self.frame+56,4,self.inject_temp)
            return 0x1b02000
        if e==0x2f88e0:return 0x1b03000
        if e in FACTORIES:
            p=NEW+self.factory_count*256;self.factory_count+=1;self.window(p,p+0x8000,20+self.factory_count)
            self.w(p+4,4,self.created_refs);return p
        if e==0x38f220:return self.phase_gate&MASK
        if e==0x3f6090:return self.close_result&MASK
        if self.mutate=='message' and e in (0x38d860,0x38f830,0x38e060):self.w(WINDOW+12,4,0x1b04000)
        if self.mutate=='helper_state' and e==0x3f5a40:self.w(WINDOW+28,4,0x7fffffff)
        return 0


def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();native=WindowWorld(image)
    cases=0;coverage=set();errors=[];depth=0
    @CALL
    def call(_,e,args):
        try:return invoke(e,args)&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-window-tree-') as td:
        so=Path(td)/'window.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in ('window-tree.c','shop-root-update.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));tree=lib.dw4_window_tree;shop=lib.dw4_shop_root_update;reference=lib.dw4_shop_root_reference_cleanup
        tree.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];tree.restype=C.c_uint64
        shop.argtypes=[C.POINTER(Api),C.POINTER(C.c_uint64),C.c_uint32];shop.restype=C.c_uint64
        reference.argtypes=[C.POINTER(Api),C.POINTER(C.c_uint64)];reference.restype=C.c_uint64
        def invoke(e,args):
            nonlocal depth
            if e not in native.descend:return native.call(e,args)&MASK
            depth+=1;old=native.frame;native.frame=SCRATCH+depth*512
            try:
                if e in REFERENCES:return reference(C.byref(api),args)
                return shop(C.byref(api),args,native.frame) if e==SHOP else tree(C.byref(api),e,args)
            finally:native.frame=old;depth-=1
        def compare(w,entry,*values):
            nonlocal cases
            w.events=[];errors.clear()
            for key,value in w.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image','frame'):
                    setattr(native,key,value.copy() if isinstance(value,(list,dict,set)) else value)
            # Frame references used by SHOP are mapped from input, never output.
            size=80 if entry==SHOP else 96
            for i in range(size):native.w(SCRATCH+512+i,1,w.read(STACK-size+i,1))
            if entry==UPDATE:
                for i in range(80):native.w(SCRATCH+1024+i,1,w.read(STACK-96-80+i,1))
            result=w.invoke(entry,*values);actual=invoke(entry,(C.c_uint64*8)(*[x&MASK for x in values]))
            if entry in REFERENCES:assert result==actual,(hex(entry),hex(result),hex(actual))
            assert not errors,errors
            def ram(obj):return {p:v for p,v in obj.mem.items() if v and not STACK-0x10000<=p<STACK+64 and not SCRATCH<=p<SCRATCH+0x10000}
            er,ar=ram(w),ram(native)
            assert er==ar,[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12]
            if w.events!=native.events:
                i=next((i for i,(x,y) in enumerate(zip(w.events,native.events)) if x!=y),min(len(w.events),len(native.events)))
                raise AssertionError((hex(entry),'event',i,w.events[i:i+1],native.events[i:i+1]))
            assert w.virtual_calls==native.virtual_calls and w.remove==native.remove
            cases+=1;coverage.update(w.covered)
        for parent,old,refs in itertools.product((0,PARENT),(0,OLD,PARENT),(0,1,2,0x800001,0xffffffff)):
            w=WindowWorld(image);w.w(WINDOW+56,4,old);w.w(OLD+4,4,refs);w.w(PARENT+4,4,refs);compare(w,INIT,WINDOW,parent,INSIGHT,3,6)
        for state,phase,mode,flag in itertools.product(range(5),range(3),range(11),(0,1)):
            w=WindowWorld(image);w.w(WINDOW+28,4,state);w.w(WINDOW+32,4,phase);w.w(WINDOW+44,4,mode);w.w(0x554c14,1,flag);compare(w,SHOP,WINDOW)
        for active,state,mask in itertools.product((0,1,255),(-1,0,1,2,3),range(16)):
            w=WindowWorld(image);w.w(WINDOW,4,VTABLES);w.w(WINDOW+24,1,active);w.w(WINDOW+28,4,state)
            w.make_list(LIST,[CHILDREN+i*256 for i in range(4)])
            for i in range(4):w.virtual_actions[CHILDREN+i*256]='close' if mask>>i&1 else None
            compare(w,UPDATE,WINDOW)
        for gate in (0,1,2,255,256,257,-1):
            w=WindowWorld(image);w.w(WINDOW+28,4,1);w.phase_gate=gate;compare(w,SHOP,WINDOW)
        for result in (0,1,256,0x100000000):
            w=WindowWorld(image);w.w(WINDOW+28,4,3);w.close_result=result;compare(w,SHOP,WINDOW)
        for mode,flag,refs in itertools.product((0,1,3,4,5,6,9),(0,1),(0,1,2,0x800001)):
            w=WindowWorld(image);w.w(WINDOW+28,4,1);w.w(WINDOW+44,4,mode)
            w.w(0x554c14,1,flag);w.inject_temp=OLD;w.w(OLD+4,4,refs);compare(w,SHOP,WINDOW)
        for state in (0,1):
            w=WindowWorld(image);w.w(WINDOW+28,4,state);w.created_refs=0;compare(w,SHOP,WINDOW)
        for count in (0,1,2):
            w=WindowWorld(image);w.w(WINDOW+28,4,1);w.w(WINDOW+32,4,1);w.w(WINDOW+80,4,count);compare(w,SHOP,WINDOW)
        for mutation in ('delete_parent','lookup'):
            w=WindowWorld(image);w.mutate=mutation;compare(w,INIT,WINDOW,PARENT,INSIGHT,1,9)
        for state,mutation in itertools.product(range(4),('append_temp','append_swap','message','helper_state')):
            w=WindowWorld(image);w.w(WINDOW+28,4,state);w.mutate=mutation;compare(w,SHOP,WINDOW)
        for action in ('close','parent_close','swap','grow'):
            w=WindowWorld(image);w.w(WINDOW,4,VTABLES);w.make_list(LIST,[CHILDREN,CHILDREN+256])
            w.make_list(ALTLIST,[ALTCHILD,CHILDREN+256]);w.virtual_actions[CHILDREN]=action
            w.virtual_actions[ALTCHILD]='close';compare(w,UPDATE,WINDOW)
        for mutation in ('delete_list','remove_relocate'):
            w=WindowWorld(image);w.w(WINDOW,4,VTABLES);w.mutate=mutation
            w.make_list(LIST,[CHILDREN,CHILDREN+256]);w.make_list(ALTLIST,[CHILDREN+256]);w.virtual_actions[CHILDREN]='close';w.virtual_actions[CHILDREN+256]='close'
            compare(w,UPDATE,WINDOW)
        for mode in range(11):
            w=WindowWorld(image);w.w(WINDOW+44,4,mode)
            compare(w,UPDATE,WINDOW);compare(w,UPDATE,WINDOW)
            # The real child operations are separate dependencies. Controlled
            # children close; root observes changed count on the following tick.
            for child in w.values(LIST):w.virtual_actions[child]='close'
            compare(w,UPDATE,WINDOW);compare(w,UPDATE,WINDOW);compare(w,UPDATE,WINDOW)
            w.close_result=1;compare(w,UPDATE,WINDOW)
        w=WindowWorld(image);w.w(WINDOW+28,4,1);w.w(WINDOW+32,4,1);w.make_list(LIST,[CHILDREN]);compare(w,SHOP,WINDOW)
        for state in (-1,0x7fffffff,0x80000000):
            w=WindowWorld(image);w.w(WINDOW+28,4,state);compare(w,SHOP,WINDOW)
        for player,code in itertools.product((-1,0,3,0x80000000),(0,6,0xffffffff)):
            w=WindowWorld(image);compare(w,INIT,WINDOW,PARENT,INSIGHT,player,code)
        for entry,pointer,target,refs,flags in itertools.product(REFERENCES,(0,WINDOW),(0,OLD),(0,1,2,0x800001,0xffffffff),(-1,0,1,0xffff,0x10001,0x8000)):
            w=WindowWorld(image);w.w(WINDOW,4,target);w.w(OLD+4,4,refs);compare(w,entry,pointer,flags)
        for count,state in itertools.product(range(5),(-2147483648,-1,0,1,2,3,2147483647)):
            w=WindowWorld(image);w.make_list(LIST,[CHILDREN+i*256 for i in range(count)])
            for i in range(count):w.w(CHILDREN+i*256+28,4,state)
            compare(w,CLOSE,WINDOW)
        for count,entry in itertools.product((-2147483648,-1),(CLOSE,UPDATE)):
            w=WindowWorld(image);w.w(WINDOW,4,VTABLES);w.w(LIST+8,4,count);compare(w,entry,WINDOW)
        expected=set(range(CLOSE,0x3f63b8,4))|set(range(INIT,0x3f6618,4))|set(range(SHOP,0x426f94,4))|set(range(0x426fa0,0x4270a0,4))
        row=next(r for r in json.loads((ROOT/'data/function-extents.json').read_text()) if int(r['address'],0)==SHOP)
        occupied={p for r in row['body_ranges'] for p in range(int(r['start'],0),int(r['end_exclusive'],0),4)}
        padding=set(range(SHOP,0x426f94,4))-occupied
        assert padding=={0x4267f4,0x426ae4,0x426b04,0x426b8c}
        assert expected-coverage==padding and len(expected&coverage)==741
        assert all(w.read(p,4)==0 for p in padding)
        print(f'Window/shop-root runtime: {cases} RAM/ordered-call cases, 741/745 instruction addresses (four padding NOPs); factories/UI/shared services remain leaves')


if __name__=='__main__':main()
