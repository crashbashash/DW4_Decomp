#!/usr/bin/env python3
"""Retail JUMP/WCHECK comparison; engine and dispatcher callees remain leaves."""
import argparse
import ctypes as C
import hashlib
from pathlib import Path
import subprocess
import tempfile
from verify_commdl import World as BaseWorld, Retail as BaseRetail, Native as BaseNative
from verify_loadintf2 import Api, sx, MASK
ROOT=Path(__file__).resolve().parents[1]
OWNER,INFO,NODE,WORK,CMD,VT,STR,POOL=range(0x1200000,0x1200800,0x100)
JUMP,FALLBACK=0x1210000,0x1210010
ENTRIES={0x394ae0:('mw_jump',3),0x394b30:('mw_start',3),0x394bf0:('mw_update',4),0x394f90:('mw_noop',0)}
ARGC={JUMP:3,FALLBACK:2,0x12a4a4:2,0x38e5f0:5,0x38f220:2,0x392be0:4,0x395250:4,0x2eb010:1,0x2eadf0:1,0x2eaf60:2,0x30c940:2}
class World(BaseWorld):
    def __init__(self,image,**kw):
        super().__init__(image,**kw)
        for a,v in ((OWNER,VT),(VT+0x8c,JUMP),(VT+0xa4,FALLBACK),(OWNER+20,POOL),(INFO+8,kw.get('name',STR)),(NODE+8,-1),(CMD+8,kw.get('command',STR)),(WORK+0x4c,kw.get('old',STR)),(STR-4,kw.get('refs',1)),(STR-8,POOL)):
            self.write(a,4,v)
        self.trace=[]
    def call(self,addr,a):
        assert addr in ARGC,hex(addr)
        a=tuple(a[:ARGC[addr]]);self.trace.append(('call',addr,*a))
        if addr==0x12a4a4:
            def name(p):
                if p==STR:return self.options.get('wait','Action')
                b=bytearray()
                while self.read(p,1):b.append(self.read(p,1));p+=1
                return b.decode()
            assert a[0], 'null strcmp outside caller contract'
            return int(name(a[0])!=name(a[1]))
        if addr in (0x38f220,0x392be0):return self.options.get('result',0)
        if addr==0x2eb010:return 0 if self.options.get('null_pool') else POOL
        if addr==0x2eadf0:return a[0]
        if addr==0x2eaf60:return a[1]
        if addr==0x395250:
            assert self.read(WORK+0x4c,4)==0
            if self.options.get('reenter'):self.write(WORK+0x4c,4,STR)
        if addr==JUMP:self.write(WORK+0x1c,4,17)
        return 0
class Retail(World,BaseRetail):
    def __init__(self,image,**kw):
        World.__init__(self,image,**kw)
        self.r=[0]*32;self.f=[0]*32;self.real_hits=set();self.covered=set()
    def call_hook(self,addr):
        self.r[2]=self.call(addr,[sx(v,32) for v in self.r[4:12]])&MASK
class Native(BaseNative):
    def invoke(self,addr,args):
        name,n=ENTRIES[addr];fn=getattr(self.lib,name)
        fn.argtypes=[C.POINTER(Api)]+[C.c_int32]*n
        fn.restype=C.c_int32 if addr in (0x394ae0,0x394b30) else None
        result=fn(C.byref(self.api),*args)
        assert not self.errors,self.errors
        return result

def verify(image,lib):
    total=0;covered=set()
    def pair(**kw):
        r=Retail(image,**kw);w=World(image,**kw);return r,w,Native(lib,w)
    def step(p,addr,*args):
        nonlocal total
        r,w,c=p;r.trace=[];w.trace=[]
        x=r.invoke(addr,args);y=c.invoke(addr,args)
        assert r.trace==w.trace,(hex(addr),r.options,r.trace,w.trace)
        assert r.snapshot()==w.snapshot(),(hex(addr),'memory')
        if addr in (0x394ae0,0x394b30):assert x==y
        covered.update(r.covered);total+=1
    for cmd in (0,STR):
        p=pair(command=cmd);step(p,0x394ae0,OWNER,WORK,CMD)
        assert p[0].read(WORK+0x1c,4)==17
        for pool in (0,POOL):
            for old in (0,STR):
                for refs in (0,1,2,0x800001,-1):
                    for null in (False,True):
                        p=pair(command=cmd,pool=pool,old=old,refs=refs,null_pool=null)
                        step(p,0x394b30,OWNER,WORK,CMD)
    for wait in ('TurnY','Landing','Action','Moving','Rotation','unknown',''):
        for result in (0,1,2,255,256,257,-1,-256):
            for pool in (0,POOL):
                for refs in (0,1,2,0x800001):
                    for reenter in (False,True):
                        p=pair(wait=wait,result=result,pool=pool,refs=refs,reenter=reenter)
                        step(p,0x394bf0,OWNER,INFO,NODE,WORK)
                        resumed=any(e[:2]==('call',0x395250) for e in p[0].trace)
                        expected=(result!=0 if wait=='Action' else result&255==0) if wait in ('TurnY','Landing','Action','Moving','Rotation') else False
                        assert resumed==expected
    for name in (0,STR):
        p=pair(name=name,pool=0,null_pool=True,result=256)
        step(p,0x394bf0,OWNER,INFO,NODE,WORK)
    p=pair()
    for result in (0,0,2):
        for w in p[:2]:w.options['result']=result
        step(p,0x394bf0,OWNER,INFO,NODE,WORK)
    for w in p[:2]:w.write(STR-4,4,2)
    step(p,0x394b30,OWNER,WORK,CMD)
    for w in p[:2]:w.options['result']=0
    step(p,0x394bf0,OWNER,INFO,NODE,WORK)
    step(p,0x394b30,OWNER,WORK,CMD)
    for w in p[:2]:w.options['result']=-1
    step(p,0x394bf0,OWNER,INFO,NODE,WORK)
    step(p,0x394f90)
    assert covered=={a for start,size in ((0x394ae0,68),(0x394b30,180),(0x394bf0,920),(0x394f90,8)) for a in range(start,start+size,4)}
    print(f'modelwait: {total} retail/C calls; all four bodies; {len(covered)} instruction addresses; ordered calls/stores and final memory agree')

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=ap.parse_args()
    image=args.elf.read_bytes()
    assert hashlib.sha1(image[0x80:0x454b80]).hexdigest()=='ffad4dab663cb290190bdfa34a8016d616a1652a'
    with tempfile.TemporaryDirectory() as tmp:
        out=Path(tmp)/'mw.so'
        subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Werror','-shared','-fPIC','-O2',str(ROOT/'recovered/frontend/modelwait.c'),'-o',str(out)],check=True)
        verify(image,C.CDLL(str(out)))
if __name__=='__main__':main()
