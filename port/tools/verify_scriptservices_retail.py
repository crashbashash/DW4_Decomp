#!/usr/bin/env python3
"""Compare native SD selectors and timed messages with private retail MIPS.

Executes 38d860/38e060 receiver selection/dispatch and 38e8f0/38d0a0
enqueue/expiry. Allocation, string interning, list operations and receiver
handlers are controlled host leaves. No game code or data is embedded.
"""
import argparse
import ctypes as C
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT.parent / 'scripts'))
from ee_core import EE, MASK, sx

BASE=0x1900000
MSG,SYS,CTX,CACHE,QUEUE,REG,RECORD,NAMES,IDS,RECEIVERS=range(BASE,BASE+0xa00,0x100)
BYTE,INTS,CIDS,CRECV=range(BASE+0xa00,BASE+0xe00,0x100)
STRINGS=BASE+0x10000
CHECK,HANDLE=BASE+0x20000,BASE+0x20100

class World(EE):
    def __init__(self,image):
        self.image=image;self.mem={};self.tokens={None:0};self.trace=[]
        self.ee_reset();self.descend={0x38d860,0x38e060,0x38e8f0,0x38d0a0}
        self.w(MSG+0x30,1,1);self.w(MSG+12,4,SYS);self.w(MSG+16,4,CTX)
        self.w(MSG+24,4,CACHE);self.w(MSG+28,4,QUEUE);self.w(MSG+20,4,REG)
        self.list(CACHE,[BASE+0x1000]);self.list(QUEUE,[])
        self.list(BYTE,[],1);self.list(INTS,[])
        self.w(CTX+16,4,BYTE);self.w(CTX+20,4,INTS)
        self.list(CIDS,[]);self.list(CRECV,[])
        self.w(BASE+0x1000+24,4,CIDS);self.w(BASE+0x1000+28,4,CRECV)
        self.w(0x586f20,4,BASE+0x3000)
        self.w(RECORD+12,4,NAMES);self.w(RECORD+16,4,IDS);self.w(RECORD+20,4,RECEIVERS)
        self.selected=None
    def read(self,a,n):
        a&=0xffffffff
        if 0x100000<=a and a+n<=0x554b00:
            p=a-0x100000+0x80;return int.from_bytes(self.image[p:p+n],'little')
        return sum(self.mem.get(a+i,0)<<(8*i) for i in range(n))
    def write(self,a,n,v):
        a&=0xffffffff
        for i in range(n):self.mem[a+i]=(v>>(8*i))&255
    w=write
    def token(self,s):
        if s not in self.tokens:
            p=STRINGS+len(self.tokens)*256;self.tokens[s]=p
            for i,b in enumerate(s.encode()+b'\0'):self.w(p+i,1,b)
            self.w(p-4,4,1000)
        return self.tokens[s]
    def string(self,p):
        return next((s for s,t in self.tokens.items() if p&0xffffffff==t),None)
    def list(self,p,values,stride=4):
        self.w(p+8,4,len(values));self.w(p+12,4,128);self.w(p+16,4,p+0x40000)
        for i,v in enumerate(values):self.w(p+0x40000+i*stride,stride,v)
    def values(self,p):
        return [self.read(self.read(p+16,4)+i*4,4) for i in range(self.read(p+8,4))]
    def invoke(self,entry,*args):
        cov=self.covered;self.ee_reset();self.covered=cov
        self.r[4:4+len(args)]=[v&MASK for v in args]
        self.r[28],self.r[29],self.r[31]=0x55c870,getattr(self,'stack',0x1fff000),0xfffffff0
        self.run_until(entry,0xfffffff0)
        return self.r[2]
    def call_hook(self,entry):self.r[2]=self.call(entry,self.r[4:12])&MASK
    def call(self,e,a):
        a=[x&0xffffffff for x in a]
        if e==0x38ca40:
            self.w(a[0]+8,1,0)
            self.w(self.read(a[0]+16,4)+8,4,0);self.w(self.read(a[0]+20,4)+8,4,0)
            return 0
        if e==0x12a4a4:return int(self.string(a[0])!=self.string(a[1]))
        if e==0x2eaf60:return a[1] # interned string
        if e in (0x2ff820,0x30c940):return 0
        if e==0x2d6680:return 0 # existing fixture capacity covers the request
        if e==0x3022c0:return RECORD if self.string(a[2])=='MODELCTRL' else 0
        if e==0x1c64e0:
            self.w(a[0],4,self.values(a[1])[a[2]]);return 0
        if e==0x2d6790:self.w(a[0]+8,4,a[1]);return 0
        if e==0x301e30:
            self.list(a[0],self.values(a[0])+[a[1]]);return 0
        if e==0x2d6cf0:
            rows=self.values(a[0]);rows.pop(a[1]);self.list(a[0],rows);return 0
        if e==0x2d6b80:
            rows=self.values(a[0]);rows[a[1]:a[1]]=[self.read(a[3],4)]
            self.list(a[0],rows);return 0
        raise AssertionError(f'unknown leaf {e:#x}')

class Selector(World):
    def __init__(self,image,rows):
        super().__init__(image);self.rows=rows
        self.list(NAMES,[self.token(name) for name,_,_ in rows])
        self.list(IDS,[id&0xffffffff for _,id,_ in rows])
        recs=[]
        for i,(_,_,active) in enumerate(rows):
            p=BASE+0x5000+i*0x400;obj=p+0x40;vt=p+0x80;recs.append(p)
            self.w(p+16,4,obj);self.w(p+20,1,active);self.w(obj,4,vt)
            self.w(vt+0x90,4,CHECK);self.w(vt+0x8c,4,HANDLE)
        self.list(RECEIVERS,recs)
    def call(self,e,a):
        if e==CHECK:return 0 # native handler takes the general method path
        if e==HANDLE:
            i=(a[1]-BASE-0x5000)//0x400;self.trace.append(i)
            return 0
        return super().call(e,a)
    def select(self,name,id):
        self.invoke(0x38d860,MSG,self.token('MODELCTRL'),self.token(name),id)
        self.invoke(0x38e060,MSG,self.token('EVENT'))
        return self.trace

class Timers(World):
    def __init__(self,image):
        super().__init__(image)
        self.descend={0x38e8f0,0x38d0a0}
        slots=[]
        for i in range(32):
            p=BASE+0x8000+i*0x100;slots.append(p)
            self.w(p+4,4,10);self.w(p+40,4,CTX) # controlled argument context
        self.list(QUEUE,slots)
        self.on_event=None
    def schedule(self,key,delay,now):
        self.w(SYS+0x50,8,now)
        p=self.values(QUEUE)[-1]
        self.w(p+24,4,self.token('MODELCTRL'));self.w(p+28,4,self.token('first'))
        self.w(p+32,4,7)
        self.invoke(0x38e8f0,MSG,self.token(key),delay)
        return self.read(p+16,8)
    def tick(self,now):
        self.w(SYS+0x50,8,now);self.invoke(0x38d0a0,MSG)
    def call(self,e,a):
        if e==0x38d860:
            self.selected=(self.string(a[1]),self.string(a[2]),sx(a[3],32));return 0
        if e==0x38e060:
            key=self.string(a[1])
            self.trace.append((*self.selected,key,self.read(SYS+0x50,8)))
            if self.on_event:
                # Preserve the suspended interpreter and its stack while the
                # controlled receiver executes the original enqueue body.
                fields=('r','f','acc','hi','lo','hi1','lo1','fcond')
                saved={name:getattr(self,name) for name in fields}
                self.stack=0x1ffe000
                try:self.on_event(key)
                finally:
                    for name,v in saved.items():setattr(self,name,v)
                    del self.stack
            return 0
        if e==0x38ce70:self.w(a[0]+8,1,0);return 0 # recycle record leaf
        return super().call(e,a)

class Value(C.Structure):
    _fields_=[('type',C.c_int),('number',C.c_double),('string',C.c_char_p),('length',C.c_size_t)]
CALL=C.CFUNCTYPE(C.c_int,C.c_void_p,C.c_char_p,C.POINTER(Value),C.c_size_t,
                C.POINTER(Value),C.c_void_p,C.c_size_t)
def value(v):
    if v is None:return Value()
    if isinstance(v,str):
        b=v.encode();return Value(2,0,b,len(b))
    return Value(1,v,None,0)
class Native:
    def __init__(self,lib,rows):
        self.lib=lib;self.owner=lib.dw4_scriptservices_open();assert self.owner
        self.trace=[];self.now=0;self.callbacks=[];self.errors=[]
        self.on_event=None
        for i,(name,id,active) in enumerate(rows):
            def handler(u,method,args,n,result,error,cap,index=i):
                try:
                    self.trace.append((index,args[3].string.decode(),self.now))
                    if self.on_event:self.on_event(args[3].string.decode())
                    return 0
                except Exception as exc:self.errors.append(exc);return -1
            cb=CALL(handler);self.callbacks.append(cb)
            assert lib.dw4_scriptservices_register(self.owner,1,b'MODELCTRL',
                name.encode() if name is not None else None,id,active,cb,None)
    def send(self,name,id,key,delay=None):
        rows=['MODELCTRL',name,id,key]+([] if delay is None else [delay])
        args=(Value*len(rows))(*(value(v) for v in rows));r=Value();error=C.create_string_buffer(512)
        assert not self.lib.dw4_scriptservices_call(self.owner,b'sd',args,len(rows),C.byref(r),error,512),error.value
    def tick(self,now):
        self.now=now;assert not self.lib.dw4_scriptservices_tick(self.owner,now)
    def close(self):
        self.lib.dw4_scriptservices_close(self.owner);assert not self.errors,self.errors

def configure(lib):
    ptr=C.c_void_p;u64=C.c_uint64
    specs={
        'open':([],ptr),'close':([ptr],None),
        'register':([ptr,u64,C.c_char_p,C.c_char_p,C.c_int32,C.c_int,CALL,ptr],u64),
        'call':([ptr,C.c_char_p,C.POINTER(Value),C.c_size_t,C.POINTER(Value),ptr,C.c_size_t],C.c_int),
        'tick':([ptr,u64],C.c_int),
    }
    for name,(args,result) in specs.items():
        f=getattr(lib,'dw4_scriptservices_'+name);f.argtypes=args;f.restype=result

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--elf',type=Path,default=ROOT.parent.parent / 'local/extracted/SLUS_208.36')
    a=p.parse_args();image=a.elf.read_bytes()
    with tempfile.TemporaryDirectory(prefix='dw4-sd-') as d:
        out=Path(d)/'sd.so'
        subprocess.run(['cc','-O2','-std=c99','-Wall','-Wextra','-Werror','-shared','-fPIC',
            '-I',str(ROOT/'include'),str(ROOT/'src/scriptservices.c'),'-o',str(out),'-lm'],check=True)
        lib=C.CDLL(str(out));configure(lib)
        rows=[('first',7,1),('first',8,0),('second',8,1),(None,-1,1),('',9,0)]
        cases=0
        for name in (None,'first','second','','missing'):
            for id in (-2,-1,0,7,8,9,-7):
                r=Selector(image,rows);expected=r.select(name,id)
                n=Native(lib,rows);n.send(name,id,'EVENT')
                actual=[index for index,_,_ in n.trace];n.close()
                assert actual==expected,(name,id,actual,expected);cases+=1
        # Original shift/add multiplication, signed wrapping deadlines and
        # publication order for equal deadlines. Expiry boundary is inclusive.
        checks=0
        for delay in (-240,-1,0,1,30,240,2147483647,-2147483648):
            now=5_000_000_000
            r=Timers(image);due=r.schedule('EVENT',delay,now)
            n=Native(lib,[('first',7,1)]);n.tick(now);n.send('first',7,'EVENT',delay)
            for clock in sorted(set((now,due-1,due,due+1))):
                if clock<now:continue
                r.tick(clock);n.tick(clock)
                expected=[(key,clock) for _,_,_,key,clock in r.trace]
                actual=[(key,clock) for _,key,clock in n.trace]
                assert actual==expected,(delay,due,clock,actual,expected);checks+=1
            n.close()
        r=Timers(image);n=Native(lib,[('first',7,1)]);n.tick(100)
        for key,delay in (('LATE',240),('ONE',30),('TWO',30),('EARLY',1)):
            r.schedule(key,delay,100);n.send('first',7,key,delay)
        for clock in (100,16666765,16666766,499999080,500000080,4000000000):
            r.tick(clock);n.tick(clock)
            assert [(key,t) for _,key,t in n.trace]==[(key,t) for _,_,_,key,t in r.trace]
        assert [key for _,key,_ in n.trace]==['EARLY','ONE','TWO','LATE']
        n.close()
        reentrant=0
        for delay in (0,1,30):
            r=Timers(image);n=Native(lib,[('first',7,1)]);n.tick(100)
            r.on_event=lambda key: r.schedule('CHILD',delay,100) if key=='PARENT' else None
            n.on_event=lambda key: n.send('first',7,'CHILD',delay) if key=='PARENT' else None
            r.schedule('PARENT',0,100);n.send('first',7,'PARENT',0)
            r.schedule('PEER',0,100);n.send('first',7,'PEER',0)
            for clock in (100,100+16666666,100+30*16666666):
                r.tick(clock);n.tick(clock)
                assert [(key,t) for _,key,t in n.trace]==[(key,t) for _,_,_,key,t in r.trace],(delay,r.trace,n.trace)
                reentrant+=1
            n.close()
        # The original pass budget includes reusable idle records, not merely
        # pending messages. A zero-delay callback chain exhausts 32 slots/pass.
        r=Timers(image);n=Native(lib,[('first',7,1)]);n.tick(100)
        r.on_event=lambda key: r.schedule('CHAIN',0,100)
        n.on_event=lambda key: n.send('first',7,'CHAIN',0)
        r.schedule('CHAIN',0,100);n.send('first',7,'CHAIN',0)
        for expected_count in (32,64):
            r.tick(100);n.tick(100)
            assert len(r.trace)==len(n.trace)==expected_count
            assert [(key,t) for _,key,t in n.trace]==[(key,t) for _,_,_,key,t in r.trace]
            reentrant+=1
        n.close()
        # Preserve an observed discrepancy as a regression of the recovery,
        # not a parity claim: retail leaves the executing record at the head.
        # Inserting an earlier child moves that head, and post-callback recycling
        # removes the child instead, leaving an idle record ahead of PEER.
        r=Timers(image);n=Native(lib,[('first',7,1)]);n.tick(100)
        r.on_event=lambda key: r.schedule('CHILD',-1,100) if key=='PARENT' else None
        n.on_event=lambda key: n.send('first',7,'CHILD',-1) if key=='PARENT' else None
        for key in ('PARENT','PEER'):
            r.schedule(key,0,100);n.send('first',7,key,0)
        r.tick(100);n.tick(100)
        assert [key for _,_,_,key,_ in r.trace]==['PARENT']
        assert [key for _,key,_ in n.trace]==['PARENT','CHILD','PEER']
        n.close()
        print(f'SD retail: {cases} receiver selectors, {checks} expiry samples and {reentrant} reentrant samples match original instructions; equal-deadline ordering passed')
        print('SD boundary: negative-delay callback insertion differs (retail stalls PEER; native detaches executing record)')
if __name__=='__main__':main()
