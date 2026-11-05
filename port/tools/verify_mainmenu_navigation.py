#!/usr/bin/env python3
"""Compare admitted naming edit steps with original 3def80 instructions.

Model/font/formatting leaves are controlled; waits are admitted explicitly.
This checks Latin/digit strip wrapping and saved mode/scroll/column restore,
not complete NameSel lifecycle, original symbol repertoire or live pad timing.
"""
import argparse
from pathlib import Path
import subprocess
from verify_scriptservices_retail import World,BASE,ROOT

NODE,PAD=BASE+0x300000,BASE+0x301000
class Retail(World):
    def call(self,e,a):
        a=[v&0xffffffff for v in a]
        if e==0x39b810:return PAD
        if e in (0x129e60,0x3e4030,0x3de480,0x3de7a0,0x3de990):return 0
        raise AssertionError(f'unexpected naming leaf {e:#x}')
    def begin(self):
        self.invoke(0x3de260,NODE,1)
        assert tuple(self.read(NODE+o,4) for o in (40,44,48,68))==(1,4,0,8)
    def edit(self,key):
        self.w(NODE+84,4,1);self.w(NODE+88,4,0) # editing admitted after real model waits
        self.w(PAD+72,4,{'U':16,'R':32,'D':64,'L':128,'C':0x4000,'B':0x2000}[key])
        self.w(PAD+76,4,0)
        self.invoke(0x3def80,NODE,1)
        return tuple(self.read(NODE+o,4) for o in (52,56,60,72))

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--elf',type=Path,default=ROOT.parent.parent/'local/extracted/SLUS_208.36')
    p.add_argument('--roms',default=str(ROOT.parent.parent/'local/extracted'))
    p.add_argument('--tool',default=str(ROOT/'build/test_mainmenu_cursor'))
    a=p.parse_args();image=a.elf.read_bytes()
    cases=['L'+'R'*31+'L'*33,'D'+'R'*30+'L'*31,'DD'+'R'*14+'L'*16,
           'CRRRCB','CDCRRUB','LCRRDUB','RRRRRRCRRRB','DD'+'R'*8+'CUB']
    total=0
    for sequence in cases:
        r=Retail(image);r.begin();expected=[r.edit(key) for key in sequence]
        result=subprocess.run([a.tool,a.roms,'--navigation',sequence],capture_output=True,text=True,check=True)
        got=[tuple(map(int,line.split()[2:])) for line in result.stdout.splitlines() if line.startswith('NAV ')]
        assert got==expected,(sequence,got,expected)
        total+=len(got)
    print(f'Naming navigation: {total} admitted edit states match original wrap and history restoration; model/font/formatting leaves controlled')

if __name__=='__main__':main()
