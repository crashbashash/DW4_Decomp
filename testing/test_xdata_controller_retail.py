#!/usr/bin/env python3
"""Complete XDATA controller vs original instructions and ordered record writes.

Widget/input, formatting, lookup/recalculation and pool/list services are leaves.
Spending XDATA and updating UPCNT are original-body effects, not a host purchase.
"""
import ctypes as C
import itertools
import json
from pathlib import Path
import subprocess
import tempfile
from test_window_presentation_retail import PresentationWorld,WINDOW,LIST,VTABLES,TOKENS,POOL,EMPTYLIST,RGB,SCRATCH,ROOT,Api,READ,WRITE,CALL,MASK,STACK
from test_window_tree_retail import CLOSE,INIT,UPDATE,SHOP,REFERENCES,NEW,VIRTUAL
XDATA=0x4270a0
REFS=(0x428610,0x428690,0x428710)
FACTORIES=(0x3b4d90,0x3b4790,0x3b4f50,0x3b6940)
KEYS=(0x51b3f8,0x51b400,0x51b408,0x51b418,0x51b420,0x51b430,0x51b438,0x51b440,0x51b488,0x51b490)
FOLDERS,PROPS,COUNTERPROPS,COUNTERS=0x1f00000,0x1f10000,0x1f20000,0x1f30000

class XdataWorld(PresentationWorld):
    def __init__(self,image):
        super().__init__(image);self.descend={XDATA,INIT,0x3f5920,*REFS};self.initial_s0=KEYS[0]
        self.xmutation=None;self.player_index=0;self.group=0;self.ints=[];self.intern_map={};self.queues=[];self.widget_return=None;self.lua_info=0x1b08000;self.lua_type=1;self.script_calls=[];self.w(0x589208,4,0xfeed)
        self.w(WINDOW+28,4,1);self.w(WINDOW+32,4,1);self.w(WINDOW+36,4,1)
        self.w(WINDOW+40,4,0);self.w(WINDOW+48,4,0);self.w(WINDOW+80,4,1);self.w(WINDOW+84,4,0);self.w(WINDOW+88,4,0)
        self.w(WINDOW+20,4,0);self.w(WINDOW,4,VTABLES);self.w(VTABLES+92,4,XDATA)
        for player in range(4):
            for key in KEYS:self.w(self.prop(player,key)+12,4,50 if key!=0x51b440 else 1000)
            self.w(COUNTERPROPS+player*256+12,4,COUNTERS+player*256)
            p=COUNTERS+player*256;self.w(p+8,4,7);self.w(p+12,4,8);self.w(p+16,4,COUNTERS+0x4000+player*256)
            for i in range(8):self.w(COUNTERS+0x4000+player*256+i*4,4,0)
    def prop(self,player,key):return PROPS+player*0x1000+KEYS.index(key)*32
    def invoke(self,entry,*args):
        cov=self.covered;self.ee_reset();self.covered=cov;self.r[4:4+len(args)]=[v&MASK for v in args]
        self.r[16]=self.initial_s0&MASK;self.r[28]=0x55c870;self.r[29]=STACK;self.r[31]=0xfffffff0
        self.run_until(entry,0xfffffff0);return self.r[2]
    def snapshot(self):
        return (*super().snapshot(),tuple(self.read(WINDOW+i,4) for i in (48,80,84,88)),
                tuple(self.read(self.prop(p,k)+12,4) for p in range(4) for k in KEYS),
                tuple(tuple(self.read(self.read(COUNTERS+p*256+16,4)+i*4,4) for i in range(8)) for p in range(4)),
                tuple((p,self.read(p-4,4)) for p in self.intern_map.values()))
    def call(self,e,args):
        if e==0x236f80 and (args[1]&0xffffffff)!=0xfeed:return super().call(e,args)
        counts={0x236f80:2,0x300cd0:2,0x389ff0:3,0x38e5d0:2,0x38f250:2,0x38f150:2,0x38e060:2,0x38f800:2,0x3a9220:2,0x3a9250:2,
                0x3f5920:3,0x3f5410:5,0x129e60:3,0x2eaf60:2,VIRTUAL:1,**{p:1 for p in FACTORIES}}
        if e not in counts:
            result=super().call(e,args)
            if e==0x1ca620 and self.xmutation=='string_temp':
                self.w(TOKENS[19]-4,4,1);self.w(args[1]&0xffffffff,4,TOKENS[19])
            return result
        raw=list(args[:counts[e]]);v=[x&0xffffffff for x in raw];normalized=list(raw)
        if e==0x129e60:normalized[0]=('frame',v[0]-self.frame)
        if e==0x3f5410 and (STACK-0x2000<=v[3]<STACK or SCRATCH<=v[3]<SCRATCH+0x10000):
            b=[];p=v[3]
            while self.read(p,1):b.append(self.read(p,1));p+=1
            normalized[3]=bytes(b).decode()
        self.events.append((e,tuple(normalized),self.snapshot()))
        if e==0x236f80:return self.lua_info&MASK
        if e==0x300cd0:return self.lua_type&MASK
        if e==0x389ff0:self.script_calls.append((raw[0],raw[1],self.read(0x58a220,4),raw[2]));return 0
        if e==VIRTUAL:
            if self.widget_return is not None:
                self.w(v[0]+24,1,0);self.w(self.read(v[0]+56,4)+48,4,self.widget_return)
            return 0
        if e==0x38e5d0:self.group=v[1];self.ints=[]
        if e==0x38f250:self.ints.append(v[1])
        if self.xmutation=='message' and e in (0x38e5d0,0x38e060,0x38f250):self.w(WINDOW+12,4,0x1b07000)
        if e==0x3f5410 and self.xmutation=='font_null':
            for i in range(7):self.w(self.frame+272+i*4,4,0)
        if e==0x38e060:
            if self.group==0x51b398 and v[1]==0x51b3e8:self.player_index=self.ints[0]
            if self.group==0x51b398 and v[1]==0x51b3a0 and self.xmutation=='recalc':
                player=self.ints[0];self.w(self.prop(player,0x51b430)+12,4,54321);self.w(self.prop(player,0x51b438)+12,4,45678)
        if e==0x38f800:return FOLDERS+self.player_index*256
        if e==0x3a9220:
            player=(v[0]-FOLDERS)//256
            assert v[1] in KEYS,(hex(v[1]),player)
            return self.prop(player,v[1])
        if e==0x3a9250:return COUNTERPROPS+(v[0]-FOLDERS)//256*256
        if e==0x129e60:
            n=v[2]-(1<<32) if v[2]>>31 else v[2]
            for i,b in enumerate(str(n).encode()+b'\0'):self.w(v[0]+i,1,b)
            return len(str(n))
        if e==0x2eaf60:
            if not v[1]:return 0
            if v[1] not in self.intern_map:
                p=0x1e80100+len(self.intern_map)*256;self.intern_map[v[1]]=p;self.w(p-8,4,POOL);self.w(p-4,4,0)
            p=self.intern_map[v[1]];self.w(p-4,4,self.read(p-4,4)+1)
            if self.xmutation=='drop_pool':self.w(0x586f20,4,0)
            return p
        if e in FACTORIES:
            self.last_factory=e
            p=NEW+self.factory_count*256;self.factory_count+=1;self.window(p,p+0x8000,20+self.factory_count);self.w(p+4,4,self.created_refs)
            for i,offset in enumerate((60,64,68,72,76)):
                q=0x1b10000+self.factory_count*0x1000+i*64;data=0x1b90000+self.factory_count*0x1000+i*256
                self.w(q+8,4,0);self.w(q+12,4,32);self.w(q+16,4,data);self.w(p+offset,4,q);self.queues.append(q)
            return p
        return 0


def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();native=XdataWorld(image)
    errors=[];cases=0;covered=set();depth=0
    @CALL
    def call(_,e,args):
        try:return invoke(e,args)&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-xdata-controller-') as td:
        so=Path(td)/'xdata.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in ('xdata-controller.c','window-tree.c','window-presentation.c','shop-root-update.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));fn=lib.dw4_xdata_controller;ref=lib.dw4_xdata_reference_cleanup
        tree=lib.dw4_window_tree;present=lib.dw4_window_presentation
        fn.argtypes=[C.POINTER(Api),C.POINTER(C.c_uint64),C.c_uint32,C.c_uint64];fn.restype=C.c_uint64
        ref.argtypes=[C.POINTER(Api),C.POINTER(C.c_uint64)];ref.restype=C.c_uint64
        tree.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];tree.restype=C.c_uint64
        present.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];present.restype=C.c_uint64
        def invoke(e,args):
            nonlocal depth
            if e not in native.descend:return native.call(e,args)&MASK
            depth+=1;old=native.frame;native.frame=SCRATCH+depth*512
            try:
                if e==XDATA:return fn(C.byref(api),args,native.frame,native.initial_s0&MASK)
                if e in REFS:return ref(C.byref(api),args)
                if e in (CLOSE,INIT,UPDATE):return tree(C.byref(api),e,args)
                return present(C.byref(api),e,args,native.frame)
            finally:native.frame=old;depth-=1
        def compare(w,entry=XDATA,*values):
            nonlocal cases
            if not values:values=(WINDOW,)
            w.events=[];errors.clear()
            for key,value in w.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image','frame'):
                    setattr(native,key,value.copy() if isinstance(value,(list,dict,set)) else value)
            size=368 if entry==XDATA else 96
            for i in range(size):native.w(SCRATCH+512+i,1,w.read(STACK-size+i,1))
            if entry==UPDATE:
                for i in range(368):native.w(SCRATCH+1024+i,1,w.read(STACK-96-368+i,1))
            expected=w.invoke(entry,*values);actual=invoke(entry,(C.c_uint64*8)(*[v&MASK for v in values]))
            assert not errors,errors
            if entry in REFS:assert expected==actual
            assert w.script_calls==native.script_calls
            def ram(obj):return {p:v for p,v in obj.mem.items() if v and not STACK-0x10000<=p<STACK+64 and not SCRATCH<=p<SCRATCH+0x10000}
            er,ar=ram(w),ram(native)
            if er!=ar:raise AssertionError(('RAM',[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12]))
            if w.events!=native.events:
                i=next((i for i,(x,y) in enumerate(zip(w.events,native.events)) if x!=y),min(len(w.events),len(native.events)))
                raise AssertionError(('event',i,w.events[i:i+1],native.events[i:i+1]))
            cases+=1;covered.update(w.covered)
        for state,main,sub in itertools.product(range(5),range(4),range(7)):
            w=XdataWorld(image);w.w(WINDOW+28,4,state);w.w(WINDOW+32,4,main);w.w(WINDOW+36,4,sub);compare(w)
        for selected in range(-1,8):
            w=XdataWorld(image);w.w(WINDOW+48,4,selected);compare(w)
        for selected in range(7):
            w=XdataWorld(image);w.w(WINDOW+36,4,3);w.w(WINDOW+88,4,selected);compare(w)
        for main,sub,ret,flag in itertools.product((0,1,2),range(6),(-1,0,1,2,7),(0,1)):
            w=XdataWorld(image);w.w(WINDOW+32,4,main);w.w(WINDOW+36,4,sub);w.w(WINDOW+48,4,ret);w.w(0x554c14,1,flag);compare(w)
        for selected,stat,balance in itertools.product(range(7),(-2147483648,-1,0,35,36,40,44,45,46,50,2044,2045,2046,9998,9999,10000,99998,99999,100000,2147483647),(-1,0,1,399,400,401,10000)):
            w=XdataWorld(image);w.w(WINDOW+48,4,selected);w.w(w.prop(0,KEYS[selected])+12,4,stat);w.w(w.prop(0,0x51b440)+12,4,balance);compare(w)
        for selected,count,player in itertools.product(range(7),(-2147483648,-1,0,1,2,3,4,5,6,7,8),range(4)):
            w=XdataWorld(image);w.w(WINDOW+36,4,3);w.w(WINDOW+88,4,selected);w.w(WINDOW+20,4,player)
            w.w(COUNTERS+player*256+8,4,count);compare(w)
        for mutation in ('message','recalc','font_null','string_temp'):
            for sub in (1,3):
                w=XdataWorld(image);w.xmutation=mutation;w.w(WINDOW+36,4,sub);compare(w)
        for main,sub in ((0,0),(1,0),(1,1),(1,2),(1,3),(1,4),(2,0)):
            w=XdataWorld(image);w.w(WINDOW+32,4,main);w.w(WINDOW+36,4,sub);w.created_refs=0
            if sub==2:w.w(WINDOW+40,4,1)
            compare(w)
        for entry,pointer,target,refs,flags in itertools.product(REFS,(0,WINDOW),(0,TOKENS[19]),(0,1,2,0x800001,0xffffffff),(-1,0,1,0xffff,0x10001,0x8000)):
            w=XdataWorld(image);w.w(WINDOW,4,target);w.w(TOKENS[19]+4,4,refs);compare(w,entry,pointer,flags)
        for allocation in (False,True):
            w=XdataWorld(image);w.xmutation='drop_pool';w.w(0x586f20,4,0);w.allocation=allocation;compare(w)
        for selected,stat,balance in itertools.product(range(7),(-2147483648,-1,0,35,36,40,44,45,46,50,2044,2045,2046,2147483647),(0,1,400)):
            w=XdataWorld(image);w.w(WINDOW+36,4,3);w.w(WINDOW+88,4,selected)
            w.w(w.prop(0,KEYS[selected])+12,4,stat);w.w(w.prop(0,0x51b440)+12,4,balance);compare(w)
        for flag in (0,1):
            w=XdataWorld(image);w.w(WINDOW+36,4,1);w.w(WINDOW+80,4,0);w.w(WINDOW+48,4,3);w.w(0x554c14,1,flag);compare(w)
        for result in (1,256,0x100000000):
            w=XdataWorld(image);w.w(WINDOW+28,4,3);w.close_result=result;compare(w)
        for current,target in ((0,1),(1,0),(-1,0),(7,1)):
            w=XdataWorld(image);w.w(WINDOW+48,4,current);w.w(WINDOW+80,4,0);w.w(WINDOW+40,4,target);compare(w)
        for selected in (-1,7,0xffffffff):
            w=XdataWorld(image);w.w(WINDOW+36,4,3);w.w(WINDOW+88,4,selected);w.initial_s0=KEYS[2];compare(w)
        for flag in (0,1):
            w=XdataWorld(image);w.w(WINDOW+36,4,2);w.w(WINDOW+40,4,1);w.w(0x554c14,1,flag);compare(w)
        for selected,player in itertools.product(range(7),range(4)):
            w=XdataWorld(image);w.w(WINDOW+36,4,3);w.w(WINDOW+88,4,selected);w.w(WINDOW+20,4,player);w.xmutation='recalc';compare(w)
            assert w.read(w.prop(player,0x51b440)+12,4)==999
            index=(2,3,4,5,6,0,1)[selected]
            assert w.read(w.read(COUNTERS+player*256+16,4)+index*4,4)==1
            assert w.read(w.prop(player,0x51b488)+12,4)==54321 and w.read(w.prop(player,0x51b490)+12,4)==45678
            assert all(w.read(w.prop(other,0x51b440)+12,4)==1000 for other in range(4) if other!=player)
        for selected,initial in itertools.product(range(7),(0x7fffffff,0xffffffff)):
            w=XdataWorld(image);w.w(WINDOW+36,4,3);w.w(WINDOW+88,4,selected);index=(2,3,4,5,6,0,1)[selected]
            p=w.read(COUNTERS+16,4)+index*4;w.w(p,4,initial);compare(w);assert w.read(p,4)==(initial+1)&0xffffffff
        # Stateful owned-child progression through quote, confirmation, spend,
        # post-upgrade notice, continue question and real common close helpers.
        for selected,accept in itertools.product(range(7),(False,True)):
            w=XdataWorld(image);w.descend.update((UPDATE,CLOSE,0x3f5a40,0x3f5f80,0x3f6090));w.w(WINDOW+28,4,0);w.widget_return=0
            for _ in range(2):compare(w,UPDATE,WINDOW)
            w.widget_return=selected;compare(w,UPDATE,WINDOW);compare(w,UPDATE,WINDOW)
            assert w.read(w.prop(0,0x51b440)+12,4)==1000 # A quote alone spends nothing.
            w.widget_return=0 if accept else 1
            compare(w,UPDATE,WINDOW);compare(w,UPDATE,WINDOW)
            assert w.read(w.prop(0,0x51b440)+12,4)==(999 if accept else 1000)
            if accept:
                w.widget_return=1;compare(w,UPDATE,WINDOW);compare(w,UPDATE,WINDOW)
            # Request ordinary primary closure; all common routines really run.
            w.w(WINDOW+28,4,2);compare(w,UPDATE,WINDOW);compare(w,UPDATE,WINDOW)
            assert w.read(WINDOW+24,1)==0
        for info,kind,message in itertools.product((0,0x1b08000),(0,1,256),(-1,0,0x482,0xffffffff)):
            w=XdataWorld(image);w.lua_info=info;w.lua_type=kind;compare(w,0x3f5920,WINDOW,0x51b3b0,message)
            assert w.script_calls==[(info if info and kind else 0,0x51b3b0,message&0xffffffff,0)]
        rows=json.loads((ROOT/'data/function-extents.json').read_text())
        row=next(r for r in rows if int(r['address'],0)==XDATA)
        occupied={p for r in row['body_ranges'] for p in range(int(r['start'],0),int(r['end_exclusive'],0),4)}
        expected=set(range(XDATA,0x42860c,4))|set(range(0x428610,0x428790,4))|set(range(0x3f5920,0x3f59b0,4))
        dead={p+d for p in (0x427758,0x4278a0,0x427940,0x4279e0,0x427a80,0x427b20) for d in (0,4)}
        padding=set(range(XDATA,0x42860c,4))-occupied
        assert len(padding)==32
        missing=expected-covered
        padding.add(0x3f5974)
        assert len(expected&covered)==1458
        assert missing==padding|dead,sorted(hex(p) for p in missing-padding-dead)
        assert all(w.read(p,4)==0 for p in padding)
        print(f'XDATA/controller-script: {cases} RAM/ordered-call cases, {len(expected&covered)}/{len(expected)} instruction addresses; widget/recalculation/receiver services remain leaves')


if __name__=='__main__':main()
