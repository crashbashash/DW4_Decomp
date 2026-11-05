#!/usr/bin/env python3
"""Original shop-selector owner + real SELECTCTRL handler/update/pad lookup.

Immediate SD delivery, enum decoding, primitive message buffers, factories and
model/physical-pad services are controlled. Responses come from the real handler;
no fixture chosen result or completion flag is substituted for that handler.
"""
import itertools
import ctypes as C
from pathlib import Path
import subprocess
import tempfile
from test_selectctrl_retail import (SelectWorld,ROOT,Api,READ,WRITE,CALL,MASK,STACK,
    SELF,CTX,INFO,DATA,WORK,NEWWORK,FLAGS,ALTFLAGS,PAD,PAD_GET,PAD_MANAGER,UPDATE,HANDLER,SCRATCH)

SELECT,READY=0x4233f0,0x423700
PRESENT={0x3f5f80,0x3f5a40,0x3f6090}
SIZES={SELECT:64,READY:32,UPDATE:240,HANDLER:160,PAD_GET:0,**{e:144 for e in PRESENT}}
WINDOW,PARENT,VTABLE,NAME,DECISIONS,DECISION_DATA,LISTS=range(0x1f80000,0x1f87000,0x1000)
INITIALIZE=0x1f88000
COMMANDS={name:i for i,name in enumerate((b'GENERATE',b'ISEND',b'GETSELECT',b'ISSELECTNOW',b'FO2TOP',b'ISFO2TOP',b'REMOVE'))}
CPU=('r','f','acc','hi','lo','hi1','lo1','fcond')

class Composed(SelectWorld):
    def __init__(self,image):
        super().__init__(image);self.descend.update((SELECT,READY,PAD_GET,*PRESENT))
        self.channel=b'';self.handler_depth=0;self.reply_ints=[];self.reply_bools=[];self.list_factories=0
        self.bridge_commands=[];self.runner=self.enter_retail
        self.w(CTX+20,1,0);self.w(NEWWORK+28,4,0)
        self.w(INFO+8,4,NAME);self.text(NAME,b'i_stmesscr')
        self.w(WINDOW,4,VTABLE);self.w(VTABLE+96,4,INITIALIZE)
        for off,value in ((12,self.read(SELF+20,4)),(20,2),(24,1),(28,0),(32,0),(36,0),(40,0),(56,PARENT),(80,NAME),(84,3),(88,0x80000000),(92,0x7fc00001),(96,0),(100,1),(104,0),(108,0)):
            self.w(WINDOW+off,1 if off in (24,104) else 4,value)
        self.w(PARENT+48,4,0x12345678)
        for i,off in enumerate((52,60,64,68,72,76)):
            p=LISTS+i*64;self.w(p+8,4,0);self.w(p+12,4,8);self.w(p+16,4,p+0x4000);self.w(WINDOW+off,4,p)
        self.w(DECISIONS+8,4,3);self.w(DECISIONS+12,4,3);self.w(DECISIONS+16,4,DECISION_DATA)
        for i,n in enumerate((1,0,1)):self.w(DECISION_DATA+i,1,n)
    def snapshot(self):
        return (*super().snapshot(),tuple(self.read(WINDOW+i,4) for i in (20,24,28,32,36,40,80,84,100,104,108)),self.read(PARENT+48,4),
                self.channel,tuple(self.int_args),tuple(self.bool_args),tuple(self.reply_ints),tuple(self.reply_bools))
    def enter_retail(self,entry,values):
        # Re-enter the original code with a separate guest frame and preserve the
        # calling CPU state. RAM, ordered events and coverage are shared naturally.
        old={k:getattr(self,k) for k in CPU};old_frame=self.frame;coverage=self.covered
        sp=(self.r[29]&0xffffffff)-256
        try:
            self.ee_reset();self.covered=coverage
            self.r[4:4+len(values)]=[v&MASK for v in values]
            self.r[28],self.r[29],self.r[31]=0x55c870,sp,0xfffffff0
            self.frame=sp-SIZES[entry];self.run_until(entry,0xfffffff0);return self.r[2]
        finally:
            for k,v in old.items():setattr(self,k,v)
            self.frame=old_frame
    def request(self,group):
        self.channel=group;self.int_args=[];self.bool_args=[];self.vector_count=0;self.string_count=0
        self.reply_ints=[];self.reply_bools=[]
    def dispatch(self,command):
        self.command=COMMANDS[command];self.bridge_commands.append((command,tuple(self.int_args),tuple(self.bool_args)))
        self.reply_ints=[];self.reply_bools=[];self.handler_depth+=1
        try:return self.runner(HANDLER,(SELF,CTX,0x1b03000))
        finally:self.handler_depth-=1
    def target(self,values):
        assert self.string(values[1])==b'SELECTCTRL'
        assert values[2]==self.read(INFO+8,4)
        assert values[3]==self.read(CTX+8,4)
    def call(self,e,args):
        raw=list(args[:8]);v=[x&0xffffffff for x in raw]
        if e==INITIALIZE:
            self.events.append((e,(raw[0],),self.snapshot()));return 0
        if e==0x38d860:
            result=super().call(e,raw)
            group=self.string(v[1])
            if group==b'SELECTCTRL':self.target(v)
            self.request(group);return result
        if e==0x38e5d0:
            result=super().call(e,raw);self.request(self.string(v[1]));return result
        if e==0x38e5f0:
            result=super().call(e,raw);group=self.string(v[1])
            if group==b'SELECTCTRL':
                self.target(v);self.request(group);return self.dispatch(self.string(v[4]))
            self.request(group);return result
        if e==0x38e060:
            result=super().call(e,raw)
            if self.channel==b'SELECTCTRL' and not self.handler_depth:return self.dispatch(self.string(v[1]))
            return result
        if e in (0x38f250,0x38f150):
            result=super().call(e,raw)
            if self.channel==b'SELECTCTRL':
                if self.handler_depth:(self.reply_ints if e==0x38f250 else self.reply_bools).append(raw[1])
                else:(self.int_args if e==0x38f250 else self.bool_args).append(raw[1])
            return result
        if e==0x38f830:
            result=super().call(e,raw)
            if self.channel==b'SELECTCTRL' and not self.handler_depth:self.string_count=1;self.string_arg=v[1]
            return result
        if e==0x38f4b0:
            result=super().call(e,raw)
            if self.channel==b'SELECTCTRL' and not self.handler_depth:self.vector_count=1;self.vector=tuple(self.read(v[1]+i*4,4) for i in range(3))
            return result
        if e in (0x38f320,0x38f220) and self.channel==b'SELECTCTRL' and not self.handler_depth:
            # Record the same service boundary, but take its result from the
            # real handler's append operation, not SelectWorld's input fixture.
            super().call(e,raw)
            return (self.reply_ints if e==0x38f320 else self.reply_bools)[v[1]]&MASK
        result=super().call(e,raw)
        if e==0x2cb0d0:
            fresh=FLAGS if not self.list_factories else ALTFLAGS;self.list_factories+=1
            self.w(fresh+4,4,1);self.w(fresh+8,4,0);return fresh
        return result


def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();native=Composed(image);errors=[];checks=0;coverage=set();depth=0
    @CALL
    def call(_,entry,args):
        try:return invoke(entry,list(args[:8]))&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-selector-manager-') as td:
        so=Path(td)/'composition.so';files=('window-selector.c','selectctrl.c','pad-manager-selection.c','window-presentation.c')
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in files],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));selector=lib.dw4_window_selector;manager=lib.dw4_selectctrl_manager;present=lib.dw4_window_presentation;get_pad=lib.dw4_pad_manager_selection
        for fn in (selector,manager,present):fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        get_pad.argtypes=[C.POINTER(Api),C.c_uint64,C.c_uint64];get_pad.restype=C.c_uint64
        def invoke(entry,values):
            nonlocal depth
            if entry not in native.descend:return native.call(entry,values)&MASK
            depth+=1;previous=native.frame;native.frame=SCRATCH+depth*512
            try:
                if entry==PAD_GET:return get_pad(C.byref(api),values[0],values[1])
                fn=selector if entry in (SELECT,READY) else present if entry in PRESENT else manager
                return fn(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in values]),native.frame)
            finally:native.frame=previous;depth-=1
        native.runner=invoke
        def compare(w,entry):
            nonlocal checks
            w.events=[];errors.clear();values=(SELF,CTX,0x1b03000) if entry==UPDATE else (WINDOW,)
            for k,value in w.__dict__.items():
                if k not in (*CPU,'covered','image','frame','runner'):
                    setattr(native,k,value.copy() if isinstance(value,(list,dict,set)) else value)
            expected=w.invoke(entry,*values);actual=invoke(entry,values)
            assert not errors,errors
            if entry==READY:assert expected==actual,('return',expected,actual)
            def ram(obj):return {p:v for p,v in obj.mem.items() if v and not STACK-0x10000<=p<STACK+64 and not SCRATCH<=p<SCRATCH+0x10000}
            er,ar=ram(w),ram(native)
            assert er==ar,('RAM',hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            if w.events!=native.events:
                i=next((i for i,(x,y) in enumerate(zip(w.events,native.events)) if x!=y),min(len(w.events),len(native.events)))
                raise AssertionError(('event',hex(entry),i,w.events[i:i+1],native.events[i:i+1]))
            assert w.bridge_commands==native.bridge_commands
            coverage.update(w.covered);seen_commands.update(cmd for cmd,_,_ in w.bridge_commands);checks+=1
        scenarios=0;seen_commands=set()
        def step(w,entry=UPDATE):compare(w,entry)
        def pad(w):
            index=4 if w.read(PAD_MANAGER+29,1) else w.read(CTX+8,4)
            return PAD+(index+1)*256
        def begin(w):
            w.w(DATA+24,4,0x13579bdf)
            maximum=w.read(WINDOW+84,4)
            w.text(NAME,b'i_stmessky' if maximum==1 else b'i_stcursor01' if maximum==7 else b'i_stmesscr')
            start=w.read(WINDOW+100,4);step(w,SELECT)
            assert w.read(PARENT+48,4)==start and w.read(WINDOW+24,1)
            assert w.read(NEWWORK+24,1)==(0 if w.read(WINDOW+104,1) else 1)
            assert w.read(NEWWORK+20,4)==maximum
            assert tuple(w.read(NEWWORK+8+i*4,4) for i in range(3))==tuple(w.read(WINDOW+88+i*4,4) for i in range(3))
            if w.read(WINDOW+108,4):
                flags=w.read(NEWWORK+32,4);assert flags and w.read(flags+8,4)==maximum
                assert tuple(w.read(w.read(flags+16,4)+i,1) for i in range(maximum))==(1,0,1)
            step(w);w.wait=1;step(w);step(w,SELECT)
            assert w.read(CTX+24,4)==0 and w.read(CTX+28,4)==1
            w.wait=0;step(w);assert w.read(CTX+24,4)==1
        def direction(w,increase):
            vertical=w.read(DATA+16,1)
            w.w(pad(w)+36,4,(4 if increase else 1) if vertical else (2 if increase else 8))
            step(w);step(w);w.w(pad(w)+36,4,0);step(w,SELECT)
        def press(w,buttons):w.w(pad(w)+72,4,buttons);step(w);w.w(pad(w)+72,4,0);step(w,SELECT)
        def finish(w,selected):
            assert w.read(PARENT+48,4)==selected&0xffffffff
            assert w.read(WINDOW+24,1) and w.read(CTX+20,1)
            if w.read(CTX+24,4)==1:
                assert w.read(CTX+28,4)==1
                w.wait=1;step(w);step(w,SELECT)
                assert w.read(WINDOW+24,1) and w.read(CTX+24,4)==1
                w.wait=0;step(w)
            assert w.read(CTX+24,4)==2
            step(w);step(w,SELECT);assert w.read(WINDOW+24,1)
            step(w);assert w.read(CTX+24,4)==3
            step(w);assert not w.read(CTX+20,1) and not w.read(DATA+28,4)
            step(w,SELECT)
            assert not w.read(WINDOW+24,1) and w.read(PARENT+48,4)==selected&0xffffffff
            assert all(w.read(w.read(WINDOW+off,4)+8,4)==0 for off in (60,64,68,72,76))
        for player,disabled,vertical,decisions,mode in itertools.product(range(4),(0,255),(0,1),(0,1),('accept','cancel','reject','top')):
            if mode=='reject' and not decisions:continue
            w=Composed(image);w.w(CTX+8,4,player);w.w(WINDOW+20,4,player);w.w(DATA+16,1,vertical);w.w(PAD_MANAGER+29,1,disabled)
            w.w(WINDOW+108,4,DECISIONS if decisions else 0);begin(w)
            if mode=='cancel':press(w,0x6000);finish(w,-1)
            elif mode=='top':
                w.w(WINDOW+28,4,4);step(w,SELECT)
                assert w.read(CTX+24,4)==10 and not w.read(PARENT+48,4)
                assert w.list_factories==(2 if decisions else 0)
                step(w);w.wait=1;step(w)
                w.w(PARENT+48,4,0x12345555);w.w(WINDOW+28,4,4);step(w,SELECT)
                assert w.read(CTX+24,4)==10 and w.read(PARENT+48,4)==0x12345555
                w.wait=0;step(w);step(w,SELECT)
                assert w.read(CTX+24,4)==1 and not w.read(PARENT+48,4)
                press(w,0x4000);finish(w,0)
            elif mode=='reject':
                press(w,0x4000);assert w.read(CTX+28,4)==2 and w.read(PARENT+48,4)==1
                for _ in range(17):step(w)
                assert not w.read(CTX+28,4)
                direction(w,False);assert not w.read(PARENT+48,4)
                press(w,0x4000);finish(w,0)
            else:
                direction(w,True);assert w.read(PARENT+48,4)==2
                press(w,0x4000);finish(w,2)
            scenarios+=1
        for player,disabled,decisions in itertools.product(range(4),(0,1),(0,1)):
            w=Composed(image);w.w(CTX+8,4,player);w.w(WINDOW+20,4,player);w.w(PAD_MANAGER+29,1,disabled)
            w.w(WINDOW+104,1,1);w.w(WINDOW+108,4,DECISIONS if decisions else 0);begin(w)
            press(w,0x2000);assert w.read(CTX+28,4)==2 and w.read(PARENT+48,4)==1
            for _ in range(17):step(w)
            direction(w,False);press(w,0x4000);finish(w,0);scenarios+=1
        for maximum,start in itertools.product((1,2,3,7),(0,1)):
            if start>=maximum:continue
            w=Composed(image);w.w(WINDOW+84,4,maximum);w.w(WINDOW+100,4,start);begin(w)
            direction(w,True);selected=min(start+1,maximum-1)
            assert w.read(PARENT+48,4)==selected
            press(w,0x4000);finish(w,selected);scenarios+=1
        for selected in range(7):
            w=Composed(image);w.w(WINDOW+84,4,7);w.w(WINDOW+100,4,0);begin(w)
            for index in range(selected):
                direction(w,True);assert w.read(PARENT+48,4)==index+1
            press(w,0x4000);finish(w,selected);scenarios+=1
        for allocator in (0,1):
            w=Composed(image);w.w(CTX+40,4,0);w.w(0x554c14,1,allocator);begin(w)
            direction(w,True);press(w,0x4000);finish(w,2);scenarios+=1
        assert {b'GENERATE',b'GETSELECT',b'ISEND',b'FO2TOP',b'ISFO2TOP'}<=seen_commands
        assert set(SIZES)<=coverage
        spans={}
        for line in (ROOT/'config/SLUS-20836/symbols.txt').read_text().splitlines():
            if not line.strip() or line.startswith('#'):continue
            address,size,*_=line.split();address=int(address,16)
            if address in SIZES:spans[address]=int(size,16)
        assert set(spans)==set(SIZES)
        words={p for address,size in spans.items() for p in range(address,address+size,4)}
        print(f'Selector/manager composition: {scenarios} full lifecycles, {checks} persistent RAM/ordered-call checkpoints; real handler replies, pad lookup and empty close queues; SD delivery/render/device services controlled; {len(coverage&words)}/{len(words)} instruction addresses across {len(spans)} existing bodies')

if __name__=='__main__':main()
