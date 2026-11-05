#!/usr/bin/env python3
"""Compare boot seed, full MT state and draws with original retail EE instructions."""
import argparse
import ctypes as C
from pathlib import Path
import subprocess
import tempfile
from verify_scriptservices_retail import World, ROOT, BASE

RNG, MANAGER, VTABLE = BASE+0x80000, BASE+0x81000, BASE+0x82000

class State(C.Structure):
    _fields_=[('index',C.c_uint32),('words',C.c_uint32*624)]

class Random(World):
    def __init__(self,image):
        super().__init__(image)
        self.descend={0x1e6b20,0x1e6b80,0x1e6bc0,0x371f10}
        self.w(RNG,4,VTABLE)
        self.w(VTABLE+92,4,0x1e6b20)
        self.w(VTABLE+96,4,0x1e6bc0)
        self.w(0x58a1b8,4,MANAGER)
        self.w(MANAGER+48,4,RNG)
    def call(self,e,a):
        if e==0x2ff130:return 0 # base Reset has no generator state
        raise AssertionError(hex(e))
    def state(self):
        return (self.read(RNG+8,4),tuple(self.read(RNG+12+4*i,4) for i in range(624)))

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--elf',type=Path,default=ROOT.parent.parent / 'local/extracted/SLUS_208.36')
    w=Random(p.parse_args().elf.read_bytes())
    with tempfile.TemporaryDirectory() as tmp:
        so=Path(tmp)/'random.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),
                        str(ROOT/'src/random.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so))
        lib.dw4_random_init.argtypes=[C.POINTER(State)]
        lib.dw4_random_next.argtypes=[C.POINTER(State)]
        lib.dw4_random_next.restype=C.c_uint32
        lib.dw4_random_mod.argtypes=[C.POINTER(State),C.c_int32]
        lib.dw4_random_mod.restype=C.c_int32
        s=State();lib.dw4_random_init(C.byref(s));w.invoke(0x1e6b80,RNG)
        assert (s.index,tuple(s.words))==w.state()
        moduli=(1,2,3,6,19,99,121,179,239,299,419,10000,0,-1,-2,-2147483648,2147483647)
        for i in range(2500):
            if i%2:
                modulus=moduli[(i//2)%len(moduli)]
                expected=C.c_int32(w.invoke(0x371f10,modulus)).value
                got=lib.dw4_random_mod(C.byref(s),modulus)
            else:
                expected=w.invoke(0x1e6bc0,RNG)&0xffffffff
                got=lib.dw4_random_next(C.byref(s))
            assert got==expected,(i,got,expected)
            assert s.index==w.read(RNG+8,4)
            if i%624 in (0,226,227,622,623):
                assert (s.index,tuple(s.words))==w.state(),i
        assert (s.index,tuple(s.words))==w.state()
        print('RNG retail: boot seed/full state and 2500 interleaved raw/SYSgetRandom draws passed (5 twists)')

if __name__=='__main__':main()
