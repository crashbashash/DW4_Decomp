#!/usr/bin/env python3
"""Pad sector branches against39b110; atan2 and vector-length leaves controlled."""
import ctypes as C
import itertools
import math
import struct
import subprocess
import tempfile
from pathlib import Path
from verify_scriptservices_retail import World,ROOT,BASE
PAD,OUT,VECTOR=BASE+0x2f0000,BASE+0x2f0200,BASE+0x2f0400
def bits(x):return struct.unpack('<I',struct.pack('<f',x))[0]
def value(b):return struct.unpack('<f',struct.pack('<I',b))[0]
class Retail(World):
    def step(self,pc,delay=False):
        if pc==0x39b13c:self.f[20]=self.length;return 0x39b148
        return super().step(pc,delay)
    def call(self,e,a):
        if e==0x123640:self.f[0]=self.angle;return 0
        return super().call(e,a)
    def classify(self,length,angle,threshold,spread):
        self.length=bits(length);self.angle=bits(angle);self.w(PAD+88,4,bits(threshold));self.w(PAD+92,4,bits(spread));
        self.invoke(0x39b110,PAD,OUT,VECTOR);return self.read(OUT,4)
def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('pad direction: private ELF unavailable, skipped');return
    w=Retail(elf.read_bytes());total=0
    angles=[0]
    for degrees in (-180,-157.5,-135,-112.5,-90,-67.5,-45,-22.5,22.5,45,67.5,90,112.5,135,157.5,180):
        b=bits(math.radians(degrees));angles.extend(value(b+d) for d in (-1,0,1))
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'direction.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),'-I'+str(ROOT/'recovered/frontend'),str(ROOT/'src/padrepeat.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-lm','-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_pad_directions_polar.argtypes=[C.c_float]*4;lib.dw4_pad_directions_polar.restype=C.c_uint32
        lib.dw4_pad_directions.argtypes=[C.c_float,C.c_float];lib.dw4_pad_directions.restype=C.c_uint32
        for length,angle,threshold,spread in itertools.product((0,.1,.39999997,.4,.5,1),angles,(0,value(0x3ecccccc),.5),(0,value(0x3f490fdb))):
            got=lib.dw4_pad_directions_polar(length,angle,threshold,spread);expected=w.classify(length,angle,threshold,spread)
            assert got==expected,(length,angle,threshold,spread,got,expected);total+=1
        for x,y,expected in ((0,0,0),(.39,0,0),(.4,0,2),(.45,0,2),(0,.45,1),(-.45,0,8),(0,-.45,4),(.3,.3,3),(-.3,.3,9),(.3,-.3,6),(-.3,-.3,12)):
            assert lib.dw4_pad_directions(x,y)==expected,(x,y,expected)
    print(f'pad direction: {total} radial/sector branch cases match39b110; atan2/length leaves controlled; native Cartesian cardinal/diagonal/dead-zone probes pass')
if __name__=='__main__':main()
