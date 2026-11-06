#!/usr/bin/env python3
"""Retail messenger harness: executes the original MIPS for receiver selection, dispatch and timed
messages (38d860/38e060, 38e8f0/38d0a0) with allocation, string interning, list operations and
receiver handlers as controlled host leaves. No game code or data is embedded.
"""
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
