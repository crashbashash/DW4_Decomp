#!/usr/bin/env python3
"""Compare original-Lua/native DM traces to execution of retail scheduler MIPS.

The receiver, string interner and engine timer services are stubbed on both sides.
This verifies DM list order, while-condition polarity, retry, pc retention,
delayed-action forwarding and completion. It does not prove rendered/gameplay parity.
"""
import argparse
from pathlib import Path
import re
import subprocess
import sys
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT.parent / 'scripts'))
from verify_loadintf2 import Retail
SELF, GROUPLIST, GROUPARRAY, GROUP, CMDLIST, CMDARRAY = range(0x1800000, 0x1800600, 0x100)
CMD, STRINGS, MSG = 0x1801000, 0x1810000, 0x1820000

class World(Retail):
    def __init__(self, image, area, rows=None):
        super().__init__(image)
        self.tick = 0
        self.trace = []
        self.tokens = {}
        self.names = {0: 'nil'}
        self.selected = None
        self.key = None
        # These commands are independently read from the original title Lua
        # instruction stream; C runs that chunk, not a committed decompilation.
        title_rows = [
            (0,'SOUND',None,-1,'BGMSTOP',None,0),
            (0,'SOUND',None,-1,'ENVSTOP',None,0),
            (0,'MODELCTRL','i_fadewn01',0,'GENERATE','SQ_BLIN30',0),
            (0,'CAMERA',None,-1,'SETDEMOCAMERA','entry',0),
            (2,'CAMERA',None,-1,'ISDEMOCAMERA',None,0),
            (0,'CAMERA',None,-1,'SETBOXCAMERA',None,0),
            (0,'SOUND',None,-1,'PLAYatPAUSE','ST_CHARA',0),
            (0,'SOUND',None,-1,'PAUSEOFF','ST_CHARA',240),
            (0,'SOUND',None,-1,'PLAY','AM_TITLE' if area == 0 else 'AM_TITLE2',0),
            (0,'MODELCTRL','j_startback',0,'GENERATE','SQ_OPEN',0),
            (1,'MODELCTRL','j_startback',0,'ISSEQNAME','SQ_OPEN',0),
            (2,'MODELCTRL','j_startback',0,'ISSEQNAME','SQ_OPEN',0),
        ]
        if area == 0:
            title_rows.append((0,'MODELCTRL','i_fadewn01',0,'GENERATE','SQ_WTIN60',0))
        title_rows.append((0,'TITLE2',None,0,'RUN',None,0))
        if rows is None:
            rows = title_rows
        for a,v in ((SELF+16,MSG),(SELF+28,GROUPLIST),(GROUPLIST+8,1),
                    (GROUPLIST+16,GROUPARRAY),(GROUPARRAY,GROUP),
                    (GROUP+4,2),(GROUP+8,0),(GROUP+12,CMDLIST),
                    (CMDLIST+8,len(rows)),(CMDLIST+16,CMDARRAY)):
            self.write(a,4,v)
        for i,(kind,cat,name,ram,key,val,delay) in enumerate(rows):
            p = CMD+i*64
            self.write(CMDARRAY+i*4,4,p)
            for off,v in ((8,kind),(24,self.token(cat)),(28,self.token(name)),
                          (32,ram),(36,self.token(key)),(40,self.token(val))):
                self.write(p+off,4,v)
            self.write(p+16,8,delay)

    def token(self, name):
        if name is None:
            return 0
        if name not in self.tokens:
            token = STRINGS+len(self.tokens)*64
            self.tokens[name] = token
            self.names[token] = name
        return self.tokens[name]

    def call(self, addr, a):
        if addr in (0x38d860,0x38e6b0):
            self.selected = a[1:4]
            return 0
        if addr == 0x372cf0: # optional value decoding
            return a[0]
        if addr in (0x38e060,0x38e8f0):
            cat,_,_ = self.selected
            self.key = self.names[a[1]]
            if not self.key.startswith('IS'):
                self.trace.append(f'{self.names[cat]}:{self.key}@{self.tick};')
            if addr == 0x38e8f0:
                assert a[2] == 240
            return 0
        if addr == 0x38f0f0:
            return 1 # receiver exists
        if addr == 0x38f220:
            if self.key == 'ISDEMOCAMERA':
                return int(self.tick < 2)
            if self.key == 'ISSEQNAME':
                return int(self.tick < 5)
            raise AssertionError(self.key)
        if addr == 0x2d6cf0:
            assert a[0] == GROUPLIST and a[1] == 0
            self.write(GROUPLIST+8,4,0)
            return 0
        if addr == 0x2ff820:
            return 0
        raise AssertionError(f'unknown retail service {addr:#x}')

class SwitchWorld(World):
    def __init__(self, image, selected, missing=False):
        rows=[(3,'STAGECTL',None,0,'VALUE',None,0)]
        for value,event in ((-7,1),(0,2),(2,3),(2,4)):
            rows.extend(((4,None,None,value,None,None,0),
                         (0,'STAGECTL',None,event,'EVENT',None,0)))
        rows.extend(((5,None,None,0,None,None,0),
                     (6,None,None,42,None,'truth',0),
                     (0,'STAGECTL',None,9,'EVENT',None,0)))
        super().__init__(image,0,rows)
        self.selected_value=selected
        self.missing=missing
        self.events=[]
    def call(self, addr, a):
        if addr==0x38f240:
            return int(not self.missing) # integer result count
        if addr==0x38f320:
            return self.selected_value
        if addr==0x38e060 and self.names[a[1]]=='EVENT':
            self.events.append(self.selected[2])
            return 0
        return super().call(addr,a)

class CountWorld(World):
    def __init__(self,image,count,window,exists=True):
        super().__init__(image,0)
        self.write(0x58a1d0,4,SELF)
        self.write(0x58a1c0,4,MSG)
        self.write(GROUPLIST+8,4,count)
        self.window=window
        self.exists=exists
        self.queries=0
    def call(self,addr,a):
        if addr==0x38e5f0:
            assert a[:5]==[MSG,0x50dae8,0,0,0x50daf0]
            self.queries+=1
            return 0
        if addr==0x38f0f0:
            return int(self.exists)
        if addr==0x38f220:
            return self.window
        return super().call(addr,a)

class DelayWorld(World):
    def __init__(self,image,delay):
        super().__init__(image,0,[(0,'STAGECTL',None,0,'EVENT',None,delay)])
        self.delayed=False
    def call(self,addr,a):
        if addr==0x38e8f0:
            self.delayed=True
            return 0
        return super().call(addr,a)

p = argparse.ArgumentParser(description=__doc__)
p.add_argument('--elf',type=Path,default=ROOT.parent.parent / 'local/extracted/SLUS_208.36')
p.add_argument('--roms',type=Path,default=ROOT.parent.parent / 'local/extracted')
p.add_argument('--tool',type=Path,default=ROOT/'build/test_script')
a=p.parse_args()
image=a.elf.read_bytes()
output=subprocess.check_output([str(a.tool),str(a.roms)],text=True)
for area in (0,1):
    world=World(image,area)
    for world.tick in range(6):
        world.run(0x37ed70,SELF,0,0)
        if world.tick<5:
            assert world.read(GROUPLIST+8,4)==1
    assert world.read(GROUPLIST+8,4)==0
    trace=re.search(rf'Lua title trace area {area}: (.*)',output)[1]
    assert trace==''.join(world.trace),(area,trace,world.trace)
print('Lua integration: both title branches match retail DM scheduler instructions over six ticks')
for i,selected in enumerate((-7,0,2,99,2)):
    world=SwitchWorld(image,selected,i==4)
    world.run(0x37ed70,SELF,0,0)
    native=[int(x) for x in re.search(rf'Lua switch {i}:(.*)',output)[1].split()]
    assert native==world.events,(i,native,world.events)
    assert world.read(GROUPLIST+8,4)==0
for count in (0,1,3):
    for exists in (False,True):
        for window in (0,1,2,256):
            world=CountWorld(image,count,window,exists)
            world.run(0x373710,0,0,0)
            result=world.r[2]&0xffffffff
            expected=count if count else (-1 if exists and (window&255) else 0)
            assert result==expected&0xffffffff,(count,exists,window,result)
            native=int(re.search(rf'Lua count {count} {int(exists)} {window}: (-?\d+)',output)[1])
            assert native==expected
            assert world.queries==int(count==0)
print('Lua DM: signed/duplicate/missing switch cases, kind-6 skip and subwindow-aware count match retail instructions')
for delay in (-10,0,1):
    world=DelayWorld(image,delay);world.run(0x37ed70,SELF,0,0)
    native=re.search(rf'Lua DM delay {delay}: (\w+)',output)[1]
    assert native==('queued' if world.delayed else 'immediate')
print('Lua DM: zero/negative delays dispatch immediately; positive delays queue, matching retail instructions')
