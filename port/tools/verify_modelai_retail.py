#!/usr/bin/env python3
"""Compare WPOS AI zone/choice/duration, direction, turn, timer and CTRL boundaries.

Original instruction slices execute with controlled lookup/allocation/sequence/
movement leaves; RNG uses real MT instructions. Full target acquisition and
complete retail manager/gameplay trajectories remain outside this oracle.
"""
import argparse
import ctypes as C
from pathlib import Path
import subprocess
import tempfile
from verify_random_retail import Random, State, RNG, MANAGER
from verify_scriptservices_retail import ROOT, BASE, World
import struct
from ee_core import sx

MAP, NODE, MGR = BASE+0x90000, BASE+0x91000, BASE+0x92000
LISTS=[BASE+0x93000+i*0x1000 for i in range(4)]
DATA=BASE+0xa0000
class Choice(C.Structure):
    _fields_=[('sequence',C.c_char_p),('direction',C.c_uint32),('frames',C.c_uint32),('limit',C.c_int32)]

class AI(Random):
    def setup(self):
        self.ee_reset();self.r[16]=MAP;self.r[17]=NODE;self.r[23]=MGR
        self.r[29]=0x1fff000;self.r[28]=0x55c870
    def choose(self,distance):
        self.setup();self.f[0]=distance
        self.run_until(0x391238,0x3912e8)
        return self.r[20],self.r[16]
    def duration(self,frames):
        self.setup();self.r[20]=DATA;self.w(DATA+16,4,frames)
        self.run_until(0x39137c,0x3913b0)
        return sx(self.r[2],64)

class Turn(World):
    def call(self,e,a):
        if e==0x3a8140:self.f[0]=self.frames;return 0
        return super().call(e,a)
    def turn(self,current,target,limit,frames):
        self.ee_reset();self.frames=frames
        self.r[22]=NODE;self.r[21]=NODE+4;self.r[17]=0;self.r[19]=MGR
        self.r[16]=NODE+8;self.r[20]=NODE;self.r[29]=0x1fff000
        for p,v in [(NODE,current),(NODE+4,target),(NODE+8,current),(MGR+140,limit),(MGR+152,current),(MGR+128,target)]:self.w(p,4,v)
        self.run_until(0x395750,0x395930)
        return self.read(NODE+8,4)

class Direction(World):
    def direction(self,dx,dz,offset):
        self.ee_reset();self.descend={0x123640,0x11ede8,0x122d90,0x123210}
        self.f[12]=offset
        self.w(0x58a580,4,0);self.w(0x58a588,4,0);self.w(0x58a5e0,4,dx);self.w(0x58a5e8,4,dz)
        self.r[29]=0x1fff000;self.r[31]=0xfffffff0
        self.run_until(0x3a68e0,0xfffffff0);return self.f[0]
class PlayerDirection(World):
    def direction(self,x,y,camera_x,camera_z):
        self.ee_reset();self.descend={0x123640,0x11ede8,0x122d90,0x123210}
        self.r[29]=0x1fff000;self.r[18]=NODE
        self.f[20]=y;self.f[21]=x
        self.w(self.r[29]+232,4,camera_x);self.w(self.r[29]+240,4,camera_z)
        self.run_until(0x3d252c,0x3d2568)
        assert self.read(NODE+112,1)==1
        return self.read(NODE+132,4)

class Control(World):
    def string(self,p):
        p&=0xffffffff
        chars=[]
        while self.read(p,1):chars.append(self.read(p,1));p+=1
        return bytes(chars).decode('ascii')
    def call(self,e,a):
        if e==DATA+0x200:self.selected=self.string(a[2]);return 0
        if e==0x392d20:self.move=self.r[5];return 0
        return super().call(e,a)
    def control(self,control,walking,next,phase):
        self.selected=None;self.move=-1
        self.w(DATA,4,DATA+0x100);self.w(DATA+0x100+0x8c,4,DATA+0x200)
        self.w(NODE+20,4,self.token('SQ_CURRENT'));self.w(NODE+60,4,control)
        self.w(NODE+64,4,phase);self.w(NODE+68,1,0)
        self.w(NODE+112,1,walking);self.w(NODE+116,4,self.token(next))
        self.w(NODE+200,4,MAP);self.list(MAP,[MGR]*4)
        self.w(NODE+72,4,MGR);self.list(MGR,[0]*4)
        self.invoke(0x391cf0,DATA,0,0,NODE)
        return self.selected,self.read(NODE+64,4),self.move

class Clock(World):
    def __init__(self,image):
        super().__init__(image)
        self.descend=set(range(0x22e000,0x231100,4))|{0x3a7fd0}
        self.w(NODE+40,4,MAP);self.w(NODE+16,4,MGR);self.w(MGR+12,4,DATA)
        self.w(LISTS[0]+16,4,0x3f800000)
    def call(self,e,a):
        if e==0x3022c0:return LISTS[0]
        return super().call(e,a)
    def start(self,ns,duration):
        self.w(DATA+80,8,ns)
        self.invoke(0x3a7a20,NODE,self.token('AITIMER'),duration)
        return -sx(self.read(LISTS[0]+24,8),64)
    def expired(self,ns):
        self.w(DATA+80,8,ns)
        return self.invoke(0x3a7e90,NODE,self.token('AITIMER'))

class Frame(Clock):
    def delta(self,previous,now):
        before=self.start(previous,0)
        self.w(LISTS[0]+24,8,0)
        self.w(LISTS[0]+40,8,~now);self.w(LISTS[0]+48,8,before)
        self.w(DATA+80,8,now)
        self.invoke(0x3a8140,NODE,self.token('Frame'))
        return self.f[0]

class Muteki(World):
    def call(self,e,a):
        if e==0x3a8140:
            assert a[0]==NODE
            self.f[0]=self.frames;self.calls+=1;return 0
        return super().call(e,a)
    def tick(self,count,frames):
        self.frames=frames;self.calls=0;self.w(MGR+124,4,count)
        self.invoke(0x3951e0,0,NODE,MGR)
        return self.read(MGR+124,4),self.calls

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--elf',type=Path,default=ROOT.parent.parent / 'local/extracted/SLUS_208.36')
    w=AI(parser.parse_args().elf.read_bytes())
    # Follow the retail floating-point conversion helpers, including tail calls.
    w.descend.update(range(0x22e000,0x231100,4))
    w.invoke(0x1e6b80,RNG)
    bounds=(0x41c80000,0x461c4000,0x471c4000)
    limits=((12,14,16),(8,12,16),(16,),(16,))
    w.w(MGR+16,4,MANAGER)
    choices=[]
    for z,ls in enumerate(limits):
        w.w(MAP+28+4*z,4,LISTS[z]);rows=[]
        choices.append((Choice*len(ls))(*(Choice(None,0,0,x) for x in ls)))
        for i,limit in enumerate(ls):
            p=DATA+0x100+z*0x100+i*32;rows.append(p);w.w(p+20,4,limit)
        w.list(LISTS[z],rows)
    for i,b in enumerate(bounds):w.w(MAP+12+4*i,4,b)
    with tempfile.TemporaryDirectory() as tmp:
        so=Path(tmp)/'ai.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),
            '-I'+str(ROOT/'recovered/frontend'),str(ROOT/'src/modelai.c'),
            str(ROOT/'src/random.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_random_init.argtypes=[C.POINTER(State)]
        lib.dw4_model_ai_zone.argtypes=[C.c_uint32,C.POINTER(C.c_uint32)]
        lib.dw4_model_ai_choose.argtypes=[C.POINTER(State),C.POINTER(Choice),C.c_uint]
        lib.dw4_model_ai_duration.argtypes=[C.c_uint32];lib.dw4_model_ai_duration.restype=C.c_int64
        s=State();lib.dw4_random_init(C.byref(s));bs=(C.c_uint32*3)(*bounds)
        samples=(0,0x41c7ffff,0x41c80000,0x41c80001,0x461c3fff,0x461c4000,
                 0x461c4001,0x471c3fff,0x471c4000,0x471c4001,0x47800000)
        for i in range(512):
            distance=samples[i%len(samples)];z=lib.dw4_model_ai_zone(distance,bs)
            ptr,lst=w.choose(distance)
            got=lib.dw4_model_ai_choose(C.byref(s),choices[z],len(choices[z]))
            assert lst==LISTS[z] and ptr==DATA+0x100+z*0x100+got*32,(i,z,got,hex(ptr))
            assert (s.index,tuple(s.words))==w.state(),i
        frames=(0,0x3f800000,0x41200000,0x42700000,0x42f00000,0x43340000,
                0x43b40000,0xbf800000,0x3dcccccd,0x4b800001)
        for f in frames:assert lib.dw4_model_ai_duration(f)==w.duration(f),hex(f)
        direction=Direction(parser.parse_args().elf.read_bytes())
        lib.dw4_model_ai_direction.argtypes=[C.c_uint32]*3;lib.dw4_model_ai_direction.restype=C.c_uint32
        values=[0,0x80000000,0x3f000000,0x3f800000,0x40000000,0x41400000,0xbf000000,0xbf800000,0xc0000000,0xc1400000,0x3dcccccd]
        total=0
        for dx in values:
            for dz in values:
                for offset in (0,0x3e32b8c3,0xbf800000):
                    got=lib.dw4_model_ai_direction(dx,dz,offset);want=direction.direction(dx,dz,offset)
                    assert got==want,(hex(dx),hex(dz),hex(offset),hex(got),hex(want));total+=1
        print(f'Model AI direction retail: {total} exact polynomial/quadrant/offset samples passed')
        player_direction=PlayerDirection(parser.parse_args().elf.read_bytes())
        lib.dw4_model_player_direction.argtypes=[C.c_uint32]*4;lib.dw4_model_player_direction.restype=C.c_uint32
        total=0
        for x in values[:9]:
            for y in values[:9]:
                for camera_x,camera_z in ((0,0x3f800000),(0x3e32b8c3,0x3f7c1c5c),(0xbf000000,0x3f000000),(0x3f000000,0xbf000000)):
                    got=lib.dw4_model_player_direction(x,y,camera_x,camera_z)
                    want=player_direction.direction(x,y,camera_x,camera_z)
                    assert got==want,(hex(x),hex(y),hex(camera_x),hex(camera_z),hex(got),hex(want));total+=1
        print(f'Player direction retail: {total} exact 3d252c..2558 camera/stick yaw states; matrix/pad admission leaves controlled')
        control=Control(parser.parse_args().elf.read_bytes())
        lib.dw4_model_ai_control.argtypes=[C.c_int,C.c_int,C.c_char_p,C.POINTER(C.c_int),C.POINTER(C.c_int)]
        lib.dw4_model_ai_control.restype=C.c_char_p
        total=0
        for mode in range(5):
            for walking in (0,1):
                for next in ('SQ_NONE','SQ_WAIT','SQ_WALK','SQ_CURRENT'):
                    for phase in range(3):
                        ph=C.c_int(phase);mv=C.c_int(-1)
                        got=lib.dw4_model_ai_control(mode,walking,next.encode(),C.byref(ph),C.byref(mv)).decode()
                        want=control.control(mode,walking,next,phase)
                        selected=got if got not in ('SQ_NONE','SQ_CURRENT') else None
                        assert (selected,ph.value,mv.value)==want,(mode,walking,next,phase,selected,ph.value,mv.value,want)
                        total+=1
        print(f'Model CTRL retail: {total} fallback/sequence/movement phase states passed')
        clock=Clock(parser.parse_args().elf.read_bytes())
        lib.dw4_model_ai_clock.argtypes=[C.c_int64];lib.dw4_model_ai_clock.restype=C.c_int64
        for ns in (0,1,262143,262144,1_000_000_000,9_000_000_000,1<<50,-1):
            got=lib.dw4_model_ai_clock(ns);assert got==clock.start(ns,1_000_000_000),(ns,got)
            for delta in (999_737_856,1_000_000_000,1_000_262_144):
                elapsed=C.c_int64(lib.dw4_model_ai_clock(C.c_int64(ns+delta).value)-got).value
                assert clock.expired(C.c_int64(ns+delta).value)==(1_000_000_000<elapsed),(ns,delta,elapsed)
        print('Model AI timer retail: 8 quantized/wrapped starts and 24 strict expiry samples passed')
        frame=Frame(parser.parse_args().elf.read_bytes())
        lib.dw4_model_frame_delta.argtypes=[C.c_int64,C.c_int64];lib.dw4_model_frame_delta.restype=C.c_uint32
        total=0
        for previous in (0,1,262143,1_000_000_000,9_000_000_000,(1<<49)-1,(1<<50)-1,-1):
            for offset in (0,1,262143,262144,16666666,16666667,33333333,49999999,50000000,50000001,1000000000,-16666667):
                now=C.c_int64(previous+offset).value
                got=lib.dw4_model_frame_delta(previous,now);want=frame.delta(previous,now)
                assert got==want,('frame',previous,now,hex(got),hex(want));total+=1
        print(f'Model Frame retail: {total} full3a8140 scale-one delta results; property/context leaves controlled')
        muteki=Muteki(parser.parse_args().elf.read_bytes())
        lib.dw4_model_muteki_tick.argtypes=[C.c_uint32,C.c_uint32];lib.dw4_model_muteki_tick.restype=C.c_uint32
        total=0
        for count in (0,0x80000000,0xbf800000,0xc2f00000,1,0x3f000000,0x3f800000,0x42f00000,0x4b800001):
            for frames in (0,0x80000000,0x3f000000,0x3f800000,0x40400000,0x42f00000,0xbf800000):
                got=lib.dw4_model_muteki_tick(count,frames);want,calls=muteki.tick(count,frames)
                assert got==want,('muteki',hex(count),hex(frames),hex(got),hex(want));total+=1
                assert calls==int(count in (0x3f000000,0x3f800000,0x42f00000,0x4b800001))
        print(f'Model MUTEKI retail: {total} full3951e0 countdown/clamp/permanent states; Frame leaf controlled')
        turn=Turn(parser.parse_args().elf.read_bytes())
        lib.dw4_model_ai_turn.argtypes=[C.c_uint32]*4;lib.dw4_model_ai_turn.restype=C.c_uint32
        angles=[0,0x3f800000,0x40490fdb,0x40c90fdb,0x41000000,0xbf800000,0xc1000000]
        total=0
        for current in angles:
            for target in angles:
                for limit in [0,0x3c23d70a,0x3e32b8c3]:
                    for frames in [0,0x3f800000,0x40000000]:
                        got=lib.dw4_model_ai_turn(current,target,limit,frames)
                        want=turn.turn(current,target,limit,frames)
                        assert got==want,(hex(current),hex(target),hex(limit),hex(frames),hex(got),hex(want))
                        total+=1
        print(f'Model AI retail: {total} shortest-arc/zero-limit/wrapped-angle states passed')
        print('Model AI retail: 512 strict-boundary/absolute-threshold choices, full RNG states and 10 durations passed')
if __name__=='__main__':main()
