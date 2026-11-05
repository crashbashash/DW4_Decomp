#!/usr/bin/env python3
"""Common SELECTCTRL loop, shop initializers and stat display vs retail code.

Receiver/input/render, formatting, strings/lists, Lua execution and player lookup
are leaves. Real selector/initializers/window tree/presentation can compose.
"""
import ctypes as C
import itertools
import json
import struct
from pathlib import Path
import subprocess
import tempfile
from test_xdata_controller_retail import FACTORIES as WIDGETS,XdataWorld,XDATA,KEYS,FOLDERS,COUNTERS,WINDOW,LIST,VTABLES,TOKENS,POOL,ROOT,Api,READ,WRITE,CALL,MASK,STACK,SCRATCH,INIT,UPDATE,CLOSE
from test_window_tree_retail import PARENT,OLD

SELECT,TOP_READY,ONE,CHOICES,STATS,REFRESH=0x4233f0,0x423700,0x43d1d0,0x43d450,0x43ecc0,0x43fb70
ENTRIES=(SELECT,TOP_READY,ONE,CHOICES,STATS,REFRESH)
SIZES={SELECT:64,TOP_READY:32,ONE:64,CHOICES:96,STATS:128,REFRESH:288,UPDATE:96}
DECIDE,ALTDECIDE=0x1f60000,0x1f70000
CUSTOM_INIT=0x1e50000

class SelectorWorld(XdataWorld):
    def __init__(self,image):
        super().__init__(image);self.descend={*ENTRIES,0x3f5f00,0x3f5c90};self.frame=STACK-64
        self.selected=-1;self.ended=0;self.fo2top_busy=0;self.selector_mutation=None;self.commands={};self.flag_calls=0
        self.w(WINDOW+28,4,0);self.w(WINDOW+56,4,PARENT);self.w(PARENT+48,4,0x12345678)
        self.w(WINDOW+80,4,0);self.w(WINDOW+84,4,3);self.w(WINDOW+100,4,2);self.w(WINDOW+104,1,0);self.w(WINDOW+108,4,0);self.w(WINDOW+112,4,0)
        self.w(VTABLES+92,4,SELECT);self.w(VTABLES+96,4,ONE)
        for p in (DECIDE,ALTDECIDE):
            self.w(p+8,4,3);self.w(p+12,4,8);self.w(p+16,4,p+0x4000)
            for i,b in enumerate((1,0,255,2,1,0,1,1)):self.w(p+0x4000+i,1,b)
    def text(self,p):
        p&=0xffffffff;out=[]
        while self.read(p,1):out.append(self.read(p,1));p+=1
        return bytes(out).decode('latin1')
    def snapshot(self):
        return (*super().snapshot(),tuple(self.read(WINDOW+i,4) for i in (80,84,88,92,96,100,104,108,112)),self.read(PARENT+48,4),self.read(OLD+48,4))
    def call(self,e,args):
        raw=list(args[:8]);v=[x&0xffffffff for x in raw]
        if e==CUSTOM_INIT:
            self.events.append((e,(raw[0],),self.snapshot()))
            if self.selector_mutation=='init_state':self.w(WINDOW+28,4,0x7fffffff)
            return 0
        if e==0x3a9220 and v[1] not in KEYS:
            key=next(k for k in KEYS if self.text(k)==self.text(v[1]));player=(v[0]-FOLDERS)//256
            self.events.append((e,tuple(raw[:2]),self.snapshot()));return self.prop(player,key)
        if e in (0x38e5f0,0x38f320,0x38f220,0x38f150,0x38f830,0x129e60):
            counts={0x38e5f0:5,0x38f320:2,0x38f220:2,0x38f150:2,0x38f830:2,0x129e60:3};norm=list(raw[:counts[e]])
            if e==0x129e60:norm[0]=('frame',v[0]-self.frame)
            if e==0x38f830 and (STACK-0x4000<=v[1]<STACK or SCRATCH<=v[1]<SCRATCH+0x20000):norm[1]=('text',self.text(v[1]))
            self.events.append((e,tuple(norm),self.snapshot()))
            if e==0x38e5f0:self.commands[v[0]]=v[4] if v[1]==0x51a918 else 0
            if e==0x38f320:
                if self.selector_mutation=='parent':self.w(WINDOW+56,4,OLD)
                return self.selected&MASK
            if e==0x38f220:
                command=self.commands.get(v[0],0)
                return (self.ended if command==0x51a958 else self.fo2top_busy if command==0x51a968 else self.running)&MASK
            if e==0x38f150:
                self.flag_calls+=1
                if self.selector_mutation=='grow' and self.flag_calls==1:self.w(DECIDE+8,4,4)
                if self.selector_mutation=='shrink' and self.flag_calls==1:self.w(DECIDE+8,4,1)
                if self.selector_mutation=='flags':self.w(WINDOW+108,4,ALTDECIDE)
            if e==0x129e60:
                value=v[2]-(1<<32) if v[2]>>31 else v[2]
                text=self.text(v[1]);text=text.replace('%d',str(value))
                for i,b in enumerate(text.encode()+b'\0'):self.w(v[0]+i,1,b)
                return len(text)
            if self.selector_mutation=='message' and e==0x38e5f0:self.w(WINDOW+12,4,0x1b0a000)
            return 0
        result=super().call(e,args)
        if e==0x38e060 and self.group==0x51c500 and v[1]==0x51c508:self.player_index=self.ints[0]
        if e in WIDGETS[:3]:
            table={WIDGETS[0]:0x540220,WIDGETS[1]:0x5400d0,WIDGETS[2]:0x540290}[e]
            self.w(result,4,table);self.w(result+80,4,0);self.w(result+84,4,0);self.w(result+108,4,0);self.w(result+112,4,0)
        if e==0x1ca620 and self.selector_mutation=='temp':self.w(TOKENS[18]-4,4,1);self.w(v[1],4,TOKENS[18])
        if e==0x2eaf60 and self.selector_mutation=='old_name':self.w(WINDOW+80,4,TOKENS[19])
        if e==0x1ca620 and self.selector_mutation=='drop_pool':self.w(0x586f20,4,0)
        return result


def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();native=SelectorWorld(image)
    errors=[];cases=0;covered=set();depth=0
    @CALL
    def call(_,e,args):
        try:return invoke(e,args)&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-shop-selectors-') as td:
        so=Path(td)/'selector.so'
        files=('window-selector.c','shop-selectors.c','window-tree.c','window-presentation.c','xdata-controller.c')
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in files],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));selector=lib.dw4_window_selector;initial=lib.dw4_shop_selectors;tree=lib.dw4_window_tree;present=lib.dw4_window_presentation;xdata=lib.dw4_xdata_controller
        for fn in (selector,initial,present):fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        xdata.argtypes=[C.POINTER(Api),C.POINTER(C.c_uint64),C.c_uint32,C.c_uint64];xdata.restype=C.c_uint64
        tree.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];tree.restype=C.c_uint64
        def invoke(e,args):
            nonlocal depth
            if e not in native.descend:return native.call(e,args)&MASK
            depth+=1;old=native.frame;native.frame=SCRATCH+depth*512
            try:
                if e==XDATA:return xdata(C.byref(api),args,native.frame,native.initial_s0&MASK)
                if e in (SELECT,TOP_READY):return selector(C.byref(api),e,args,native.frame)
                if e in (ONE,CHOICES,STATS,REFRESH):return initial(C.byref(api),e,args,native.frame)
                if e in (CLOSE,INIT,UPDATE):return tree(C.byref(api),e,args)
                return present(C.byref(api),e,args,native.frame)
            finally:native.frame=old;depth-=1
        def compare(w,entry):
            nonlocal cases
            w.events=[];errors.clear()
            for key,value in w.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image','frame'):
                    setattr(native,key,value.copy() if isinstance(value,(list,dict,set)) else value)
            size=SIZES[entry]
            for i in range(size):native.w(SCRATCH+512+i,1,w.read(STACK-size+i,1))
            if entry==UPDATE:
                for i in range(368):native.w(SCRATCH+1024+i,1,w.read(STACK-96-368+i,1))
            expected=w.invoke(entry,WINDOW);actual=invoke(entry,(C.c_uint64*8)(WINDOW))
            assert not errors,errors
            if entry==TOP_READY:assert expected==actual
            def ram(obj):return {p:v for p,v in obj.mem.items() if v and not STACK-0x10000<=p<STACK+64 and not SCRATCH<=p<SCRATCH+0x10000}
            er,ar=ram(w),ram(native)
            if er!=ar:raise AssertionError(('RAM',hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12]))
            if w.events!=native.events:
                i=next((i for i,(x,y) in enumerate(zip(w.events,native.events)) if x!=y),min(len(w.events),len(native.events)))
                raise AssertionError((hex(entry),'event',i,w.events[i:i+1],native.events[i:i+1]))
            cases+=1;covered.update(w.covered)
        for entry in ENTRIES:
            w=SelectorWorld(image);w.w(WINDOW+44,4,1150);compare(w,entry)
        for state,end,busy in itertools.product(range(6),(0,1,2,255,256,257),(0,1,256)):
            w=SelectorWorld(image);w.w(WINDOW+28,4,state);w.ended=end;w.fo2top_busy=busy;compare(w,SELECT)
        for entry,code in itertools.product((ONE,CHOICES),(-1,0,1,1150,1163,1166,0x79e,0x7aa,0x1234)):
            w=SelectorWorld(image);w.w(WINDOW+44,4,code);compare(w,entry)
        triples=(0x79e,0x73a,0x6d6,0x672,0x60e,0x546,0x47e)
        pairs=(0x7aa,0x5ad,0x61a,0x740,0x6dc,0x678,0x614,0x54b,0x4f8,0x4ea,0x4e7,0x493,0x48e,0x48b)
        for code,pool,allocation in itertools.product(triples+pairs+(0,0x1234),(0,POOL),(False,True)):
            w=SelectorWorld(image);w.w(WINDOW+44,4,code);w.w(0x586f20,4,pool);w.allocation=allocation;compare(w,CHOICES)
            assert w.read(WINDOW+84,4)==(3 if code in triples else 2 if code in pairs else 3)
            assert w.read(WINDOW+100,4)==2 # Caller-owned start point is retained.
        for entry,pool,allocation,old,text in itertools.product((ONE,STATS),(0,POOL),(False,True),(0,TOKENS[18]),(0,TOKENS[19])):
            w=SelectorWorld(image);w.w(0x586f20,4,pool);w.allocation=allocation;w.w(WINDOW+80,4,old);w.w(WINDOW+112,4,text);w.w(WINDOW+44,4,1150);compare(w,entry)
        for state,pointer,count,cancel in itertools.product((0,4),(0,DECIDE),(-1,0,1,3),(0,1,255)):
            w=SelectorWorld(image);w.w(WINDOW+28,4,state);w.w(WINDOW+108,4,pointer);w.w(DECIDE+8,4,count);w.w(WINDOW+104,1,cancel);compare(w,SELECT)
        for mutation,state in itertools.product(('grow','shrink','flags','parent','message'),(0,1,4)):
            w=SelectorWorld(image);w.selector_mutation=mutation;w.w(WINDOW+28,4,state);w.w(WINDOW+108,4,DECIDE);w.w(DECIDE+8,4,2);compare(w,SELECT)
        for mutation,entry in itertools.product(('temp','old_name','drop_pool'),(ONE,CHOICES,STATS)):
            w=SelectorWorld(image);w.selector_mutation=mutation;w.w(WINDOW+44,4,1150);w.w(WINDOW+112,4,TOKENS[17]);compare(w,entry)
        for player,stat in itertools.product(range(4),(-2147483648,-1,0,35,36,44,45,46,2045,2046,9998,9999,10000,99998,99999,100000,2147483647)):
            w=SelectorWorld(image);w.w(WINDOW+20,4,player)
            for key in KEYS[:7]:w.w(w.prop(player,key)+12,4,stat)
            compare(w,REFRESH)
        for selected in (-1,0,1,2,6,0x80000000,0xffffffff,0x100000001):
            w=SelectorWorld(image);w.w(WINDOW+28,4,1);w.selected=selected;compare(w,SELECT);assert w.read(PARENT+48,4)==selected&0xffffffff
        for cancel in (0,1,255):
            w=SelectorWorld(image);w.w(VTABLES+96,4,CUSTOM_INIT);w.w(WINDOW+104,1,cancel);w.w(WINDOW+108,4,DECIDE);compare(w,SELECT)
        for entry,text,code,mutation in itertools.product((ONE,CHOICES,STATS),(0,TOKENS[17]),(1150,1163),('temp','drop_pool')):
            w=SelectorWorld(image);w.selector_mutation=mutation;w.w(WINDOW+44,4,code);w.w(WINDOW+112,4,text);compare(w,entry)
        for state,result in itertools.product((0,1,2,3),(1,256,0x100000000)):
            w=SelectorWorld(image);w.w(WINDOW+28,4,state);w.close_result=result;w.ended=1;compare(w,SELECT)
        w=SelectorWorld(image);w.w(VTABLES+96,4,CUSTOM_INIT);w.selector_mutation='init_state';compare(w,SELECT)
        for value in (0,1,256,0x100000000,-1):
            w=SelectorWorld(image);w.fo2top_busy=value;compare(w,TOP_READY)
        # The XDATA owner receives actual selector results and child removal;
        # only SELECTCTRL input/receiver responses and recalculation remain leaves.
        for parameter,accept in itertools.product(range(7),(False,True)):
            w=SelectorWorld(image);w.descend.update((XDATA,INIT,UPDATE,CLOSE,0x3f5920,0x3f59b0,0x3f5f40,0x3f5f80,0x3f5a40,0x3f6090))
            w.w(VTABLES+92,4,XDATA);w.w(WINDOW+28,4,0);w.w(WINDOW+80,4,0);w.w(WINDOW+84,4,0);w.w(WINDOW+88,4,0);w.ended=1;w.selected=0
            for _ in range(2):compare(w,UPDATE)
            w.selected=parameter;compare(w,UPDATE);w.selected=0;compare(w,UPDATE)
            assert w.read(w.prop(0,0x51b440)+12,4)==1000
            w.selected=0 if accept else 1;compare(w,UPDATE);compare(w,UPDATE)
            assert w.read(w.prop(0,0x51b440)+12,4)==(999 if accept else 1000)
            index=(2,3,4,5,6,0,1)[parameter]
            assert [w.read(w.read(COUNTERS+16,4)+i*4,4) for i in range(7)]==[int(accept and i==index) for i in range(7)]
            if accept:w.selected=1;compare(w,UPDATE);compare(w,UPDATE)
            w.w(WINDOW+28,4,2);compare(w,UPDATE);compare(w,UPDATE);assert w.read(WINDOW+24,1)==0
        w=SelectorWorld(image);w.w(VTABLES+96,4,CUSTOM_INIT)
        for offset,bits in ((88,0x80000000),(92,0x7fc00001),(96,0x3f800000)):w.w(WINDOW+offset,4,bits)
        compare(w,SELECT)
        rows=[r for r in json.loads((ROOT/'data/function-extents.json').read_text()) if int(r['address'],0) in ENTRIES]
        expected={p for r in rows for p in range(int(r['address'],0),int(r['end_exclusive'],0),4)}
        occupied={p for r in rows for span in r['body_ranges'] for p in range(int(span['start'],0),int(span['end_exclusive'],0),4)}
        padding=expected-occupied;dead=set();blocks=0
        for p in sorted(expected):
            code=[w.read(p+i*4,4) for i in range(6)]
            if code[0]==0x3c020052 and code[1]>>16==0x2442 and code[2]>>16==0x1440 and code[4]>>26==4:
                blocks+=1;dead.update((p+16,p+20))
        assert blocks==32 and len(dead)==64 and len(padding)==6
        assert expected-covered==padding|dead,sorted(hex(p) for p in expected-covered-padding-dead)
        assert len(expected&covered)==1909 and all(w.read(p,4)==0 for p in padding)
        print(f'Shop selectors: {cases} RAM/ordered-call cases, 1909/1979 instruction addresses (six padding, 64 literal-null words); receiver/string/record services remain leaves')


if __name__=='__main__':main()
