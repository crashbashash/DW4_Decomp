#!/usr/bin/env python3
"""Argument clearing, delayed delivery and context nesting vs retail instructions.

Selection/dispatch and lifecycle bodies execute real recovered C. Allocation,
list/string services, initialization and concrete receiver handlers are leaves.
"""
import argparse,ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
from test_messenger_dispatch_retail import Dispatch,ENTRIES as DISPATCH,ROOT,MSG,SYS,CACHE,QUEUE,REG,CIDS,CRECV,BASE,HANDLE,STACK,MASK,NAMES,IDS,RECEIVERS,Api,READ,WRITE,CALL
ENTRIES=(0x38ca40,0x38ce70,0x38d050,0x38d0a0,0x38e8f0,0x38eca0,0x38ecf0,0x38ed50,0x38ed70,0x38ef50)
CONTEXT=0x1700000;ROWS=0x1720000;PUSH=0x1730000;CONTEXTS=[CONTEXT+i*0x1000 for i in range(12)]
WIDTHS=(1,4,4,8,12,64,4,4)
class Lifecycle(Dispatch):
    def __init__(self,image):
        super().__init__(image,[('first',7,0),('other',8,1),(None,-1,0)])
        self.descend=set(ENTRIES)|set(DISPATCH);self.reenter=False;self.reentered=False
        self.reentry_limit=1;self.reentry_count=0;self.advance_clock=False
        self.clear_count=False;self.shrink_relocate=False;self.null_token=0
        for ctx in CONTEXTS:self.context(ctx)
        self.w(MSG+16,4,CONTEXT);self.w(MSG+32,4,PUSH);self.w(MSG+36,4,0)
        self.list(PUSH,CONTEXTS[8:11]);self.queue([None]*4)
        self.w(SYS+80,8,100)
    def context(self,p,count=0,capacity=4,refs=10):
        self.w(p+4,4,refs);self.w(p+8,1,1);self.w(p+12,4,0)
        for i,width in enumerate(WIDTHS):
            lst=p+0x100+i*0x100;self.w(p+16+i*4,4,lst)
            values=[]
            for j in range(count):
                if i==6:
                    value=0x17f0000+j*16;self.w(value+4,4,refs)
                elif i==7:value=self.token('arg'+str(j))
                else:value=(i+1)*101+j
                values.append(value)
            self.list(lst,values,width);self.w(lst+12,4,capacity)
    def queue(self,times):
        pointers=[]
        for i,time in enumerate(times):
            row=ROWS+i*0x100;pointers.append(row);self.w(row+4,4,10)
            self.w(row+8,1,time is not None);self.w(row+16,8,time or 0)
            self.w(row+24,4,self.token('MODELCTRL'));self.w(row+28,4,self.token('first'))
            self.w(row+32,4,7);self.w(row+36,4,self.token('EVENT'));self.w(row+40,4,CONTEXTS[i+1])
        self.list(QUEUE,pointers)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==HANDLE and self.reenter and self.reentry_count<self.reentry_limit:
            self.reentered=True;self.reentry_count+=1
            if self.advance_clock:self.w(SYS+80,8,self.read(SYS+80,8)+1)
            # The concrete receiver queues one new zero-delay message using
            # its current argument object; both paths execute the real bodies.
            result=super().call(e,args)
            self.nested((0x38ecf0,MSG,self.token('MODELCTRL'),self.token('EVENT'),0))
            return result
        if e==0x2d6680:
            self.events.append((e,*v[:3]))
            if self.shrink_relocate:
                old=self.read(v[0]+16,4);new=old+0x80000
                for i in range(v[1]*v[2]):self.w(new+i,1,self.read(old+i,1))
                self.w(v[0]+16,4,new)
            self.w(v[0]+12,4,v[1]);return 0
        if e==0x2ff820 and self.clear_count:
            self.w(self.read(CONTEXT+40,4)+8,4,0)
        if e==0x2eaf60 and not v[1] and self.null_token:
            self.events.append((e,*v[:2]));self.w(self.null_token-4,4,self.read(self.null_token-4,4)+1);return self.null_token
        result=super().call(e,args)
        self.events=[tuple('temp' if isinstance(x,int) and STACK-0x4000<=x<STACK else x for x in event) for event in self.events]
        return result
    def nested(self,spec):
        fields=('r','f','acc','hi','lo','hi1','lo1','fcond')
        saved={name:getattr(self,name) for name in fields}
        self.stack=STACK-0x2000
        try:self.invoke(spec[0],*spec[1:])
        finally:
            for name,value in saved.items():setattr(self,name,value)
            del self.stack

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=p.parse_args()
    image=args.elf.read_bytes();retail=Lifecycle(image);native=Lifecycle(image);errors=[];cases=0;hits=set();depth=0
    @CALL
    def call(_,e,values):
        nonlocal depth
        try:
            if e in ENTRIES or e in DISPATCH:
                depth+=1
                try:return (life if e in ENTRIES else dispatch)(C.byref(api),e,values,STACK-0x1000-depth*0x100)
                finally:depth-=1
            return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    def nested_native(spec):
        values=(C.c_uint64*8)(*[x&MASK for x in spec[1:]])
        return life(C.byref(api),spec[0],values,STACK-0x1800)
    native.nested=nested_native
    with tempfile.TemporaryDirectory(prefix='dw4-messenger-lifecycle-') as td:
        so=Path(td)/'lifecycle.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/messenger-lifecycle.c'),str(ROOT/'recovered/engine/messenger-dispatch.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));life=lib.dw4_messenger_lifecycle;dispatch=lib.dw4_messenger_dispatch
        for fn in (life,dispatch):fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        def setup():
            nonlocal retail
            retail=Lifecycle(image)
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image','nested'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            expected=retail.invoke(entry,*values)
            actual=life(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in values]),STACK-0x1000)
            assert not errors,errors
            if entry==0x38d050:assert expected==actual==0
            def ram(world):return {p:v for p,v in world.mem.items() if not STACK-0x4000<=p<STACK+32 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),values,[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:15])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry)
        for count,capacity,refs,pool in itertools.product((0,1,4,8,9,17),(4,32),(1,2,0x800001),(0,BASE+0x3000)):
            setup();retail.context(CONTEXT,count,capacity,refs);retail.w(0x586f20,4,pool)
            retail.w(CONTEXT+12,4,retail.token('context'));retail.w(retail.token('context')-4,4,1)
            retail.shrink_relocate=True;compare(0x38ca40,CONTEXT)
        for refs,mutate,null_result in itertools.product((1,2,0x800001),(False,True),(False,True)):
            setup();retail.context(CONTEXT,9,32,refs);retail.clear_count=mutate
            if null_result:retail.null_token=retail.token('null-result')
            compare(0x38ca40,CONTEXT)
        for count in (0,1,9):
            setup();row=ROWS;retail.w(row+40,4,CONTEXT);retail.context(CONTEXT,count,32,1)
            for offset in (24,28,36):retail.w(retail.read(row+offset,4)-4,4,1)
            compare(0x38ce70,row)
        for ready in (0,1):setup();retail.w(MSG+48,1,ready);compare(0x38d050,MSG)
        # Signed 64-bit deadlines, full-width delay arithmetic, stable equal
        # deadlines and inactive records terminating the sorted active prefix.
        for times,delay,now in itertools.product(([None]*4,[10,20,None,None],[100,100,None,None],[200,None,None,None],[-10,0,None,None]),(-2,-1,0,1,7,0x100000001),(0,100,0x7ffffffffffffff0)):
            setup();retail.queue(times);retail.w(SYS+80,8,now)
            compare(0x38e8f0,MSG,retail.token('NEW_EVENT'),delay)
        for times,now,frozen,ready in itertools.product(([],[None]*4,[10,20,None,None],[100,100,None,None],[200,300,None,None],[-10,0,None,None]),(0,10,20,100,101,400,0x8000000000000000),(0,5,150),(0,1)):
            setup();retail.queue(times);retail.w(MSG+48,1,ready);retail.w(SYS+80,8,now);retail.w(MSG+40,8,frozen)
            compare(0x38d0a0,MSG)
        for entry in (0x38eca0,0x38ecf0,0x38ed50):
            for delay in (-1,0,1,0x100000001):
                setup();cat,key=retail.token('MODELCTRL'),retail.token('NEW_EVENT')
                values={0x38eca0:(MSG,cat,retail.token('first'),7,key,delay),0x38ecf0:(MSG,cat,key,delay),0x38ed50:(MSG,cat)}[entry]
                compare(entry,*values)
        for pool_size in (1,2,3):
            setup();retail.list(PUSH,CONTEXTS[8:8+pool_size]);retail.context(CONTEXT,4,32)
            for i in range(pool_size):compare(0x38ed70,MSG)
            for i in range(pool_size):compare(0x38ef50,MSG)
        # Persistent sorted enqueue/deliver and a real receiver re-entering
        # deferred preparation/enqueue while expiry is suspended.
        setup()
        for delay in (3,1,1):compare(0x38ecf0,MSG,retail.token('MODELCTRL'),retail.token('EVENT'),delay)
        for now in (100,16666766,50000100):retail.w(SYS+80,8,now);compare(0x38d0a0,MSG)
        setup();retail.queue([10,None,None,None]);retail.w(CONTEXTS[1]+8,1,0);retail.reenter=True;compare(0x38d0a0,MSG)
        assert retail.reentered and native.reentered, 'receiver re-entry was not exercised'
        for advance in (False,True):
            setup();retail.queue([10,None,None,None]);retail.w(CONTEXTS[1]+8,1,0)
            for listp in (NAMES,IDS,RECEIVERS):retail.list(listp,retail.values(listp)[:1])
            retail.reenter=True;retail.reentry_limit=6;retail.advance_clock=advance
            compare(0x38d0a0,MSG)
            assert retail.reentry_count==native.reentry_count==(1 if advance else 4)
            assert retail.read(retail.values(QUEUE)[0]+8,1)==1
        assert hits==set(ENTRIES),hits
    print(f'messenger lifecycle retail: {cases} RAM/defined-return/ordered-call cases; all 10 bodies and real selector/dispatch integration; lower services controlled')
if __name__=='__main__':main()
