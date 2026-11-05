#!/usr/bin/env python3
"""Compare the complete beSeCtl runtime group with retail MIPS, including ordered SETSOUND calls."""
import argparse
import ctypes as C
from pathlib import Path
import struct
import subprocess
import tempfile
from verify_loadintf2 import Harness, Retail as Cpu, Api, PEEK, POKE, CALL, sx, MASK
ROOT=Path(__file__).resolve().parents[1]
ENTRIES={0x39c900:('se_attach',1),0x39c940:('se_register',2),
         0x39c970:('se_meta',0),0x39c980:('se_tick',0),
         0x39c990:('se_action',3),0x39cb60:('se_data_meta',0)}
RETURNS={0x39c970,0x39c990,0x39cb60}
ARGC={0x236f80:2,0x38d560:5,0x12a4a4:2,0x38d860:4,0x38f830:2,
      0x22fd70:1,0x38f350:2,0x38e060:2}
SELF,CTX,MSG,INFO,LIST,ROWS,MODELS,ACTS,DATA,STR=range(0x1000000,0x1000a00,0x100)
class World(Harness):
    def __init__(self,image):
        super().__init__(image);self.trace=[]
    def write(self,a,n,v):
        super().write(a,n,v)
        if a<0x1f00000:self.trace.append(('write',a,n,v&((1<<(n*8))-1)))
    def text(self,p):
        out=[]
        for i in range(128):
            b=self.read(p+i,1)
            if not b:return bytes(out)
            out.append(b)
        raise AssertionError('unterminated string')
    def call(self,addr,a):
        assert addr in ARGC,hex(addr)
        a=tuple(a[:ARGC[addr]]);self.trace.append(('call',addr,*a))
        if addr==0x12a4a4:return (self.text(a[0])>self.text(a[1]))-(self.text(a[0])<self.text(a[1]))
        if addr==0x236f80:return 0x1120000
        if addr==0x22fd70:return struct.unpack('<I',struct.pack('<f',a[0]))[0]
        return 0
    def snapshot(self):return {a:v for a,v in self.mem.items() if a<0x1f00000}
class Retail(World,Cpu):
    def __init__(self,image):
        World.__init__(self,image);self.r=[0]*32;self.f=[0]*32;self.executed=set();self.real_hits=set()
    def step(self,pc,delay=False):
        word=self.read(pc,4)
        if word>>26==0x21:  # lh: signed sound delay
            self.executed.add(pc)
            rs=(word>>21)&31;rt=(word>>16)&31
            self.r[rt]=sx(self.read((self.r[rs]+sx(word,16))&MASK,2),16)&MASK
            self.r[0]=0
            return pc+4
        return Cpu.step(self,pc,delay)
    def call_hook(self,addr):
        a=[sx(v,32) for v in self.r[4:12]]
        if addr==0x38f350:a[1]=sx(self.f[12],32)
        result=self.call(addr,a)
        if addr==0x22fd70:self.f[0]=result
        else:self.r[2]=result&MASK
    def invoke(self,addr,args):
        self.r=[0]*32;self.r[4:4+len(args)]=[v&MASK for v in args]
        self.r[28]=0x55c870;self.r[29]=0x1fff000;self.r[31]=0xfffffff0
        pc=addr
        for _ in range(10000):
            if pc==0xfffffff0:return sx(self.r[2],32)
            pc=self.step(pc)
        raise AssertionError('did not return')
class Native:
    def __init__(self,lib,w):
        self.lib=lib;self.errors=[]
        def safe(fn):
            def wrapped(*a):
                try:return fn(*a)
                except Exception as e:self.errors.append(e);return 0
            return wrapped
        self.peek=PEEK(safe(lambda u,a,n:sx(w.read(a,n),n*8)))
        self.poke=POKE(safe(lambda u,a,n,v:w.write(a,n,v)))
        self.call=CALL(safe(lambda u,a,v:sx(w.call(a,list(v[:8])),32)))
        self.api=Api(None,*[C.cast(f,C.c_void_p) for f in (self.peek,self.poke,self.call)])
    def invoke(self,addr,args):
        name,n=ENTRIES[addr];f=getattr(self.lib,name)
        f.argtypes=[C.POINTER(Api)]+[C.c_int32]*n;f.restype=C.c_int32 if addr in RETURNS else None
        out=f(C.byref(self.api),*args);assert not self.errors,self.errors;return out

def setup(w,count=1,actions=1,delay=0,null=False,duplicate=False,match=True):
    for a,v in [(SELF+12,CTX),(SELF+20,0x1100000),(CTX+12,INFO),(INFO+20,LIST),
                (LIST+8,count),(LIST+16,ROWS),(MSG+12,STR),(MSG+16,-1),(MSG+20,STR+32),
                (0x587ea8,0x1110000),(0x587fb0,123),(0x587fe8,456)]:w.write(a,4,v)
    for p,text in [(STR,b'menu\0'),(STR+32,b'MOVE\0'),(STR+64,b'other\0')]:
        for i,b in enumerate(text):w.write(p+i,1,b)
    if null:w.write(MSG+12,4,0x4e0858);w.write(MSG+20,4,0x4e0858)
    for i in range(max(0,count)):
        row=MODELS+i*24;lst=ACTS+i*24;data=DATA+i*64
        for a,v in [(ROWS+i*4,row),(row+8,0 if null else STR),(row+16,lst),
                    (lst+8,actions),(lst+16,data)]:w.write(a,4,v)
        if not match:w.write(row+8,4,STR+64)
        for j in range(max(0,actions)):
            item=0x1010000+i*0x400+j*32
            for a,v in [(data+j*4,item),(item+8,0 if null else (STR+32 if duplicate or j==0 else STR+64)),
                        (item+12,0x1020000+i*0x100+j*16)]:w.write(a,4,v)
            w.write(item+16,2,delay)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,required=True);a=p.parse_args()
    image=a.elf.read_bytes();total=0;coverage=set()
    with tempfile.TemporaryDirectory() as temp:
        libpath=Path(temp)/'sectl.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-O2',str(ROOT/'recovered/frontend/sectl.c'),'-o',str(libpath)],check=True)
        lib=C.CDLL(str(libpath))
        def check(addr,args,opts={},cached=0):
            nonlocal total
            r=Retail(image);w=World(image)
            for x in (r,w):setup(x,**opts);x.write(SELF+32,4,cached);x.trace=[]
            n=Native(lib,w);rx=r.invoke(addr,args);nx=n.invoke(addr,args)
            assert r.trace==w.trace,(hex(addr),opts,r.trace,w.trace)
            assert r.snapshot()==w.snapshot(),(hex(addr),'memory')
            if addr in RETURNS:assert rx==nx,(hex(addr),rx,nx)
            coverage.update(r.executed);total+=1
        for cached in (0,0x1112222):check(0x39c900,[SELF],cached=cached)
        for addr in (0x39c970,0x39c980,0x39cb60):check(addr,[])
        for value in (0,-1,0x123456):check(0x39c940,[SELF,value])
        for count in (-1,0,1,3):
            for actions in (-1,0,1,3):
                for delay in (-32768,-1,0,1,20,32767):
                    for null,duplicate,match in ((False,False,True),(False,True,True),(True,True,True),(False,False,False)):
                        check(0x39c990,[SELF,CTX,MSG],dict(count=count,actions=actions,delay=delay,null=null,duplicate=duplicate,match=match))
    print(f'beSeCtl: {total} retail/C comparisons; {len(coverage)} instruction addresses; ordered SETSOUND, signed delays, duplicate/absent/null names and initialization OK')
if __name__=='__main__':main()
