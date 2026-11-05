#!/usr/bin/env python3
"""Differential of port NPC channels against retail R5900 start/expire/update.
Runs the contiguous 0x00392d20..0x00392f98 group, comparing all channel bytes
and returned EE float bits. No game binary is generated or committed.
"""
import argparse, ctypes as C, random, struct, subprocess, tempfile
from pathlib import Path
from ee_core import EE, MASK
ROOT = Path(__file__).resolve().parents[1]
OBJ = 0x1400000
class Retail(EE):
    descend = {0x392d20, 0x392d90, 0x392e10}
    def __init__(self, image):
        self.image=image; self.mem={}; self.ee_reset()
    def read(self,a,n):
        if 0x100000 <= a < 0x554b00:
            return int.from_bytes(self.image[a-0x100000+0x80:a-0x100000+0x80+n],'little')
        return sum(self.mem.get(a+i,0) << (8*i) for i in range(n))
    def write(self,a,n,v):
        for i in range(n): self.mem[a+i]=(v>>(8*i))&255
    def call_hook(self,a): raise AssertionError(hex(a))
    def invoke(self,a,mode=0,fp=()):
        self.ee_reset(); self.r[4]=OBJ; self.r[5]=mode
        self.r[29]=0x1fff000; self.r[31]=0xfffffff0
        self.f[12:12+len(fp)]=fp
        self.run_until(a,0xfffffff0)
        return self.f[0]
def bits(f): return struct.unpack('<I',struct.pack('<f',f))[0]
def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--elf',type=Path,default=ROOT.parent/'local/extracted/SLUS_208.36')
    args=ap.parse_args(); rng=random.Random(20836)
    image=args.elf.read_bytes()
    # Retail reflection defaults for the delivered NPC collision probe.
    for address, instruction in [(0x35e8c4,0x3c024040),(0x35e8e4,0x3c024080),(0x35e904,0x3c024080)]:
        assert struct.unpack_from('<I',image,address-0x100000+0x80)[0]==instruction

    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'npc.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'port/include'),
            '-I'+str(ROOT/'port/recovered/frontend'),str(ROOT/'port/src/npcmotion.c'),
            str(ROOT/'port/recovered/frontend/eefloat.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so)); lib.dw4_npc_motion_tick.restype=C.c_uint32
        lib.dw4_npc_motion_start.argtypes=[C.c_void_p,C.c_uint32,C.c_uint32,C.c_uint32,C.c_int]
        lib.dw4_npc_motion_tick.argtypes=[C.c_void_p,C.c_uint32]
        checks=0
        for case in range(180):
            r=Retail(image); buf=(C.c_ubyte*44)()
            value=bits(rng.choice([.14,1.,3.5,7.,.5])); frame=bits(rng.choice([0.,1.,4.,6.,6.3]))
            time=bits(rng.choice([0.,18.,25.,2.5])); mode=case%6
            speed=bits(rng.uniform(-1,1)) if case>12 else 0
            initial=bytearray(44)
            struct.pack_into('<III',initial,28,speed,1,bits(1.))
            struct.pack_into('<I',initial,40,bits(1.))
            for i,b in enumerate(initial): r.write(OBJ+i,1,b);buf[i]=b
            r.invoke(0x392d20,mode,(value,frame,time))
            lib.dw4_npc_motion_start(buf,value,frame,time,mode)
            for tick in range(100):
                assert bytes(buf)==bytes(r.read(OBJ+i,1) for i in range(44)),(case,tick,'state')
                dt=bits(rng.choice([0.,1.,.9999999,2.,3.,4.,.25]))
                got=r.invoke(0x392e10,fp=(dt,))
                native=lib.dw4_npc_motion_tick(buf,dt)
                assert got==native,(case,tick,hex(got),hex(native))
                checks+=1
            assert bytes(buf)==bytes(r.read(OBJ+i,1) for i in range(44))
        print(f'NPC movement: {checks} retail instruction/state comparisons passed')
if __name__=='__main__': main()
