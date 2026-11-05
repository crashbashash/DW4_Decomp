#!/usr/bin/env python3
"""Model FREEZE command admission against original 396a80 dispatch."""
from pathlib import Path
import subprocess
from verify_statusctrl_retail import Retail as BaseRetail, BASE, ROOT
OWNER,RAM,CELL,WORK,INFO,VT=range(BASE+0x260000,BASE+0x260600,0x100)
HOOK=BASE+0x261000
class Retail(BaseRetail):
    def call(self,e,a):
        if e==0x3022c0:return CELL
        if e==HOOK:return 0
        if e==0x356ab0:return 0
        if e==0x38d4a0:return self.command
        if e==0x3a84a0:self.rates.append(self.f[12]);return 0
        if e==0x38e5f0:return 0
        return super().call(e,a)
    def freeze(self,active,initial,on):
        self.events=[];self.rates=[];self.command=20 if on else 21
        self.w(OWNER,4,VT);self.w(VT+0xc4,4,HOOK);self.w(VT+0xac,4,HOOK)
        self.w(RAM+40,4,CELL);self.w(CELL+20,4,WORK);self.w(RAM+12,4,INFO)
        self.w(RAM+20,1,active);self.w(WORK+69,1,initial)
        self.w(INFO+8,4,self.token('i_messwn'))
        self.invoke(0x396a80,OWNER,RAM,self.token('ONFREEZE' if on else 'OFFREEZE'))
        return bool(active and self.read(WORK+69,1)),self.rates

def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('model freeze: private ELF unavailable, skipped');return
    w=Retail(elf.read_bytes());total=0
    for index,key in ((20,'ONFREEZE'),(21,'OFFREEZE')):
        assert w.string(w.read(0x4c58f0+4*index,4))==key and w.read(0x4c5980+4*index,4)==index
    output=subprocess.check_output([str(ROOT/'build/test_controllers'),str(elf.parent),'--freeze'],text=True)
    for line in output.splitlines():
        if not line.startswith('FREEZE '):continue
        active,initial,on,frozen=map(int,line.split()[1:]);expected,rates=w.freeze(active,initial,on)
        assert frozen==expected,(active,initial,on,frozen,expected)
        assert rates==([0 if on else 0x3f800000] if active else []),(active,initial,on,rates)
        total+=1
    assert total==8
    print('model freeze: eight active/inactive ON/OFF admissions match original 396a80, including rate 0/1 publication; lookup/parser/animation hooks controlled')
if __name__=='__main__':main()
