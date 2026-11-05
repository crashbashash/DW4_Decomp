#!/usr/bin/env python3
"""Sound freeze eligibility/level publication from original 37d570."""
import itertools
from pathlib import Path
from verify_scriptservices_retail import World,ROOT,BASE
OWNER,LIST,RECORD,SOURCE=range(BASE+0x290000,BASE+0x290400,0x100)
class Retail(World):
    def call(self,e,a):
        if e==0x3a70c0:return self.playing
        if e==0x3a6f70:self.levels.append(a[1]&0xffffffff);return 0
        return super().call(e,a)
    def freeze(self,kind,handle,playing,backend,on):
        self.playing=playing;self.levels=[];self.w(OWNER+40,4,LIST);self.list(LIST,[RECORD]);self.w(RECORD+24,8,handle)
        self.w(RECORD+32,2,kind);self.w(RECORD+12,4,SOURCE);self.w(SOURCE+16,4,backend)
        self.invoke(0x37d570,OWNER,on);return self.levels
def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('sound freeze: private ELF unavailable, skipped');return
    w=Retail(elf.read_bytes());total=0
    for kind,handle,playing,backend,on in itertools.product((1,2,3,4,5),range(2),range(2),(0,3,4),range(2)):
        expected=[]
        if kind==4 and handle and playing:expected=[(127 if on else 0) if backend==3 else (0 if on else (-999&0xffffffff))]
        assert w.freeze(kind,handle,playing,backend,on)==expected,(kind,handle,playing,backend,on,w.levels,expected)
        total+=1
    print(f'sound freeze: {total} original 37d570 eligibility/level states confirm only live type-four sounds are ducked; playback query/level setter controlled')
if __name__=='__main__':main()
