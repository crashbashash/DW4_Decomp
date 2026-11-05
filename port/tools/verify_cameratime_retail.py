#!/usr/bin/env python3
"""Compare camera time state with retail 0x37a900; matrix/path leaves controlled."""
import ctypes as C
import argparse
from pathlib import Path
import subprocess
import tempfile
from verify_scriptservices_retail import World, ROOT, BASE

MODE=BASE+0x80000
CLOCK=MODE+0x100

class State(C.Structure):
    _fields_=[('last',C.c_uint64),('time',C.c_uint64),('end',C.c_uint64),
              ('loaded',C.c_int),('finished',C.c_int),('frozen',C.c_int)]

class Camera(World):
    def __init__(self,image):
        super().__init__(image)
        self.descend={0x37a900}
        self.samples=[]
    def call(self,e,a):
        if e==0x1c5b30:self.samples.append(a[2])
        elif e not in (0x190380,0x191230,0x190a30,0x190ed0,0x190a10,0x191e30,0x4578c0):
            raise AssertionError(hex(e))
        return 0

class Query(World):
    def __init__(self,image,demo):
        super().__init__(image);self.descend={0x379ce0};self.demo=demo;self.result=None
    def call(self,e,a):
        if e==0x3697c0:return 1
        if e==0x38d4a0:return 8 # original command table: ISDEMOCAMERA
        if e==0x38f0f0:return 0 # no explicit optional query-mode argument
        if e==0x38f100:return 0
        if e==0x38f1e0:self.result=a[2];return 0
        if e==0x378e80:return self.demo # demo-data type predicate is a controlled leaf
        raise AssertionError(hex(e))

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--elf',type=Path,default=ROOT.parent.parent / 'local/extracted/SLUS_208.36')
    image=parser.parse_args().elf.read_bytes()
    table=World(image)
    name=table.read(0x4c79d0+8*4,4)
    assert bytes(table.read(name+i,1) for i in range(13))==b'ISDEMOCAMERA\0'
    assert table.read(0x50e250+8*4,4)==0x379f18
    with tempfile.TemporaryDirectory() as tmp:
        so=Path(tmp)/'camera.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),
                        str(ROOT/'src/cameratime.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so))
        lib.dw4_camera_time_tick.argtypes=[C.POINTER(State),C.c_uint64]
        total=0
        # Includes last==0 sentinel, inclusive finish, capped jumps, backwards
        # samples, signed wrap, frozen finished state and missing source.
        cases=[(0,0,1000000000,1,0,0),(100,0,50000000,1,0,0),
               (100,49999999,50000000,1,0,0),(100,0,0,1,0,0),
               (100,9,1000000000,1,0,1),(100,9,10,1,1,0),
               (100,9,10,1,1,1),(100,9,10,0,0,0),
               ((1<<64)-20,(1<<64)-5,10,1,0,0),
               ((1<<63)-20,(1<<63)-5,(1<<63)+10,1,0,0)]
        for fields in cases:
            for now in (0,1,99,100,101,50000100,50000101,1000000000,(1<<63),(1<<64)-1):
                c=State(*fields);w=Camera(image)
                w.w(MODE+0x50,4,1 if c.loaded else 0)
                w.w(MODE+0x54,4,CLOCK)
                for off,val in ((0x58,c.last),(0x60,c.time),(0x68,c.end)):w.w(MODE+off,8,val)
                w.w(MODE+0x70,1,c.finished);w.w(MODE+0x71,1,c.frozen)
                w.w(CLOCK+0x50,8,now)
                w.invoke(0x37a900,MODE)
                lib.dw4_camera_time_tick(C.byref(c),now)
                got=(c.last,c.time,c.end,c.finished,c.frozen)
                expected=tuple(w.read(MODE+off,size) for off,size in
                               ((0x58,8),(0x60,8),(0x68,8),(0x70,1),(0x71,1)))
                assert got==expected,(fields,now,got,expected)
                if c.loaded and not c.frozen:assert w.samples==[c.time]
                else:assert not w.samples
                total+=1
        print(f'Camera retail clock: {total} state/path-time comparisons passed; matrix leaves controlled')
        for demo in (0,1):
            for finished in (0,1):
                w=Query(image,demo)
                w.w(MODE+0x28,4,CLOCK);w.w(CLOCK+0x70,1,finished)
                ram=MODE+0x200;w.w(ram+0x14,1,1);w.w(ram+0x18,4,1)
                w.invoke(0x379ce0,MODE,ram,0)
                assert w.result==int(demo and not finished),(demo,finished,w.result)
        print('Camera retail ISDEMOCAMERA: 4 default-query states passed; demo-data type leaf controlled')

if __name__=='__main__':main()
