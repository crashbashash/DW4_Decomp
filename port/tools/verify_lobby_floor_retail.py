#!/usr/bin/env python3
"""3926d0 floor/fall admission; collision, movement queries and messenger leaves controlled."""
import ctypes as C
import itertools
from pathlib import Path
import subprocess
import tempfile
from verify_scriptservices_retail import World, ROOT, BASE
OWNER, INFO, NODE, WORK, VT, SELECT=range(BASE+0x290000,BASE+0x290600,0x100)
class Floor(World):
    def string(self,p):
        p&=0xffffffff
        b=[]
        while self.read(p,1):b.append(self.read(p,1));p+=1
        return bytes(b).decode('ascii')
    def call(self,e,a):
        if e==0x392be0:
            if a[3]==3:return self.upward
            if a[3]==4:return self.falling
            if a[3]==5:self.cleared+=1;return 1
            raise AssertionError(a)
        if e==0x38e5f0:
            key=self.string(a[4]);assert key in ('HITFLOORCHECK','HITFLOORADJUST'),key
            if key=='HITFLOORADJUST':self.adjusted+=1
            return 0
        if e==0x38f0f0:return 1
        if e==0x38f820:return 0
        if e==0x38f220:return self.support if a[1]==0 else self.landing
        if e==SELECT:self.selected=self.string(a[2]);return 0
        return super().call(e,a)
    def response(self,floor,fall,upward,falling,support,landing,sleeping):
        self.upward=upward;self.falling=falling;self.support=support;self.landing=landing
        self.adjusted=self.cleared=0;self.selected=None
        self.w(OWNER,4,VT);self.w(VT+0x8c,4,SELECT);self.w(OWNER+20,4,0)
        self.w(INFO+8,4,self.token('p_dorumon'));self.w(NODE+8,4,0)
        self.w(WORK+216,1,0);self.w(WORK+217,1,floor);self.w(WORK+218,1,fall)
        self.w(WORK+20,4,self.token('SQ_SLEP' if sleeping else 'SQ_WALK'))
        self.w(WORK+56,4,0);self.w(WORK+204,4,0)
        self.invoke(0x3926d0,OWNER,INFO,NODE,WORK)
        if self.adjusted:assert self.cleared==1
        if self.selected:assert self.selected=='SQ_FALL'
        return 1 if self.adjusted else 2 if self.selected else 0

def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('lobby floor: private ELF unavailable, skipped');return
    retail=Floor(elf.read_bytes());total=0
    with tempfile.TemporaryDirectory() as tmp:
        so=Path(tmp)/'floor.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),'-I'+str(ROOT/'recovered/frontend'),str(ROOT/'src/modelai.c'),str(ROOT/'src/random.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-lm','-o',str(so)],check=True)
        lib=C.CDLL(str(so));f=lib.dw4_model_floor_response;f.argtypes=[C.c_int]*7;f.restype=C.c_int
        for args in itertools.product((0,1),(0,1),(0,1),(0,1),(0,1,255,256),(0,1,255,256),(0,1)):
            assert f(*args)==retail.response(*args),args
            total+=1
    print(f'lobby floor: {total} original 3926d0 floor/fall/upward/landing/sleep states match; geometry and movement/messenger consumers controlled')
if __name__=='__main__':main()
