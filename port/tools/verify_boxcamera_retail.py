#!/usr/bin/env python3
"""Run retail 378ed0 and quaternion primitives against the native box camera.

Player/region lookup, allocations, list operations and timer service are controlled
leaves. The transition branches and original matrix/quaternion math execute as EE
instructions. Private ELF is read locally; no game binary is embedded.
"""
import argparse
import ctypes as C
import math
from pathlib import Path
import struct
import subprocess
import tempfile
from verify_scriptservices_retail import World, ROOT, BASE
from ee_core import f_div, f_from_i32

Float16=C.c_float*16
class Camera(C.Structure):
    _fields_=[(n,Float16) for n in ('eye','interest','start_eye','start_interest')]+[
        ('position',C.c_float*3),('frame',C.c_float),('current',C.c_uint),
        ('previous',C.c_uint),('initialized',C.c_int),('timer',C.c_int)]

CTRL,WORK,INFO,BOX,MODE,VIEWER=range(BASE+0x100000,BASE+0x106000,0x1000)
LISTS=[BASE+0x110000+i*0x1000 for i in range(4)]
EYES=[BASE+0x120000+i*0x100 for i in range(8)]
INTS=[BASE+0x130000+i*0x100 for i in range(8)]
GEOMS=[BASE+0x140000+i*0x100 for i in range(8)]

def bits(f):return struct.unpack('<I',struct.pack('<f',f))[0]
def floats(v):return struct.unpack('<%df'%len(v),struct.pack('<%dI'%len(v),*v))
def matrix(axis,angle,x,y,z):
    m=[0.0]*16;m[0]=m[5]=m[10]=m[15]=1
    j,k=(axis+1)%3,(axis+2)%3
    m[j*4+j]=m[k*4+k]=math.cos(angle)
    m[j*4+k]=-math.sin(angle);m[k*4+j]=math.sin(angle)
    m[12:15]=[x,y,z];return list((Float16)(*m))

class Retail(World):
    def __init__(self,image,eyes,interests):
        super().__init__(image)
        self.descend={0x1925f0,0x192cc0,0x191770,0x192f00}
        self.eyes=eyes;self.interests=interests;self.timer=False;self.delta=0
        self.w(WORK+12,4,INFO);self.w(WORK+24,4,1)
        self.w(INFO+28,4,BOX);self.w(CTRL+32,4,VIEWER)
        self.w(CTRL+36,4,VIEWER);self.w(CTRL+40,4,MODE)
        for off,lst,rows in [(12,LISTS[0],GEOMS),(16,LISTS[1],[BASE+0x150000]),
            (20,LISTS[2],EYES),(24,LISTS[3],INTS)]:
            self.w(BOX+off,4,lst);self.list(lst,rows)
        for i,m in enumerate(eyes):self.store(EYES[i]+32,m)
        for i,m in enumerate(interests):self.store(INTS[i]+32,m)
        for i,g in enumerate(GEOMS):self.w(g+12,4,i)
        self.position=(0,0,0);self.selected_region=1
        self.w(CTRL+44,4,bits(-1));self.w(CTRL+48,4,bits(-1));self.w(CTRL+52,4,bits(-1))
    def store(self,p,m):
        for i,f in enumerate(m):self.w(p+4*i,4,bits(f))
    def array(self,p,n=16):return [self.read(p+4*i,4) for i in range(n)]
    def call(self,e,a):
        a=[v&0xffffffff for v in a]
        if e==0x38f5a0:return 1
        if e==0x38f630:
            self.store(a[0],matrix(0,0,*self.position));return 0
        if e==0x190a30:
            for i in range(3):self.w(a[1]+4*i,4,self.read(a[0]+48+4*i,4))
            return 0
        if e==0x190a10:
            for i in range(3):self.w(a[0]+48+4*i,4,self.read(a[1]+4*i,4))
            return 0
        if e==0x1908f0:
            b=self.read(a[1],64);self.w(a[0],64,b);return 0
        if e==0x18ab70:
            # Selected volume contains the player; all others are far away.
            lo=-10000 if a[0]==self.selected_region else 10000
            self.store(a[2],[lo+20000 if a[1]==0 else lo]*3);return 0
        if e in (0x38e670,0x37a690,0x463fd0):return 0
        if e==0x3a7d80:return int(self.timer)
        if e==0x3a7a20:self.timer=True;self.delta=0;return 0
        if e==0x3a8580:self.timer=False;return 0
        if e==0x3a8140:self.f[0]=self.delta;return 0
        return super().call(e,a)
    def tick(self,region,p,delta):
        self.position=p;self.selected_region=region;self.delta=delta
        self.invoke(0x378ed0,CTRL,WORK)
        return self.array(EYES[0]+32),self.array(INTS[0]+32)

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--elf',type=Path,required=True);args=ap.parse_args()
    eyes=[matrix(i%3,i*.43,2*i,50-i,80+i) for i in range(8)]
    interests=[matrix(i%3,i*.9,0,0,0) for i in range(8)]
    interests[5]=matrix(2,3.4,0,0,0) # negative-trace largest-Z branch
    count=0;maximum=0
    with tempfile.TemporaryDirectory() as tmp:
        libpath=Path(tmp)/'camera.so'
        subprocess.run(['cc','-std=c99','-shared','-fPIC','-O2','-I'+str(ROOT/'include'),
            '-I'+str(ROOT/'recovered/frontend'),str(ROOT/'src/boxcamera.c'),
            str(ROOT/'recovered/frontend/eefloat.c'),'-lm','-o',str(libpath)],check=True)
        lib=C.CDLL(str(libpath));lib.dw4_boxcamera_tick.argtypes=[C.POINTER(Camera),C.c_uint,
            C.POINTER(C.c_float),C.POINTER(C.c_float),C.POINTER(C.c_float),C.c_float]
        for seed in range(6):
            r=Retail(args.elf.read_bytes(),eyes,interests);c=Camera();p=[0.,10.,-30.]
            for tick in range(700):
                # Initial acquisition, long transitions, interruption, no-hit,
                # stationary completion, zero delta and capped timer delta.
                region=1 if tick<20 else 2 if tick<90 else 3 if tick<170 else 0 if tick<200 else 4+seed%4
                if tick<230 and tick%7:p[0]+=1
                dt=f_div(f_from_i32([16666600,16666700,50000000,0][(tick+seed)%4]),bits(16666667))
                e,i=r.tick(region,p,dt)
                selected=region or c.current
                lib.dw4_boxcamera_tick(C.byref(c),selected,Float16(*eyes[selected]),
                    Float16(*interests[selected]),(C.c_float*3)(*p),floats([dt])[0])
                assert (c.current,c.previous,bits(c.frame),bool(c.timer))==(
                    r.read(CTRL+76,4),r.read(CTRL+80,4),r.read(CTRL+72,4),r.timer),('state',seed,tick,c.frame,floats([r.read(CTRL+72,4)]))
                for native,original in [(c.eye,e),(c.interest,i)]:
                    error=max(abs(a-b) for a,b in zip(native,floats(original)))
                    maximum=max(maximum,error)
                    assert error<3e-5,('matrix',seed,tick,error,list(native),floats(original))
                count+=1
    print(f'box camera: {count} retail controller states/matrix pairs pass; maximum float error {maximum:.9g}')
if __name__=='__main__':main()
