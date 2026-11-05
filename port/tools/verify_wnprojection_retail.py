#!/usr/bin/env python3
"""WN XY normalization against complete 1fbce0 and original VU instruction words.

The reference pins scalar DIV to the installed capture profile's nearest mode;
other operations use the existing toward-zero EE/VU model. Matrix/camera/Q
inputs and renderer-buffer capacity are controlled. Hardware rounding is not
claimed by this oracle.
"""
import ctypes as C
import itertools
from pathlib import Path
import random
import struct
import subprocess
import sys
import tempfile
from verify_scriptservices_retail import World,ROOT,BASE
from ee_core import sx,M32,f_mul,f_add,f_div,f_trunc_w
import vu1_microcode as vu

DESCRIPTOR=BASE+0x300000
BUFFER=DESCRIPTOR+0x1000
MATRIX=DESCRIPTOR+0x5000

def bits(value):return struct.unpack('<I',struct.pack('<f',value))[0]
def number(value):return struct.unpack('<f',struct.pack('<I',value))[0]

class Renderer(World):
    def step(self,pc,delay=False):
        word=self.read(pc,4);op=word>>26;rs=word>>21&31;rt=word>>16&31;imm=sx(word&65535,16)
        # This routine copies full quadwords. Keep 128 bits for LQ/SQ, unlike
        # the scalar interpreter's deliberate 64-bit GPR subset.
        if op==0x1e:
            if rt:self.r[rt]=self.read((self.r[rs]+imm)&M32,16)
            self.covered.add(pc);return pc+4
        if op==0x1f:
            self.write((self.r[rs]+imm)&M32,16,self.r[rt]);self.covered.add(pc);return pc+4
        return super().step(pc,delay)
    def _cop1(self,w,rs,rt,rd,sh,fn,branch):
        if rs==16 and fn==3:
            self.f[sh]=bits(number(self.f[rd])/number(self.f[rt]));return
        return super()._cop1(w,rs,rt,rd,sh,fn,branch)

def upper(word,vf,acc):
    """Only the upper opcodes present in the scoped, original fragments."""
    fs,ft,fd=word>>11&31,word>>16&31,word>>6&31;op=word&63
    for c,bit in enumerate((24,23,22,21)):
        if not word>>bit&1:continue
        if op==0x3c and fd==10:acc[c]=f_add(vf[fs][c],vf[ft][c]) # ADDA
        elif op in (0x3c,0x3d) and fd==2: # MADDAx/y
            acc[c]=f_add(acc[c],f_mul(vf[fs][c],vf[ft][op-0x3c]))
        elif op in (0x3c,0x3f) and fd==6: # MULAx/w
            acc[c]=f_mul(vf[fs][c],vf[ft][0 if op==0x3c else 3])
        elif op==0x1a:vf[fd][c]=f_mul(vf[fs][c],vf[ft][2]) # MULz
        elif op==0x0a:vf[fd][c]=f_add(acc[c],f_mul(vf[fs][c],vf[ft][2])) # MADDz
        elif op==0x29:vf[fd][c]=f_add(acc[c],f_mul(vf[fs][c],vf[ft][c])) # MADD
        elif op==0x3d and fd==5:vf[ft][c]=f_trunc_w(f_mul(vf[fs][c],bits(16))) # FTOI4
        else:raise AssertionError(hex(word))

def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('WN projection: private ELF unavailable, skipped');return
    world=Renderer(elf.read_bytes())
    raw,offset=vu.va_to_file(str(elf),vu.BLOB_VA)
    words=lambda start,locations:[struct.unpack_from('<I',raw,offset+start+o+4)[0] for o in locations]
    transform=words(7264,[88,96,104,112]) # TRANS_MVPS_TEXTURE translation/X/Y/Z
    viewport=words(63264,[144,160,176,216]) # viewport ACC, scale*Q, MADD, FTOI4
    assert transform==[0x01e5eabc,0x01ea10bc,0x01ea18bd,0x01ea238a]
    assert viewport==[0x01c029bf,0x01c6235a,0x01d368e9,0x01c3197d]
    rng=random.Random(20836);matrix_cases=[]
    for _ in range(128):matrix_cases.append([bits(rng.uniform(-1000,1000)) for _ in range(16)])
    matrix_cases.extend([[bits(1 if i%5==0 else 0) for i in range(16)],
                         [bits(x) for x in (.003125,0,0,0,0,1/224,0,0,0,0,-.0002002002,0,0,0,-1.002002,1)]])
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'projection.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra',
            '-I'+str(ROOT/'include'),'-I'+str(ROOT/'recovered/frontend'),
            str(ROOT/'src/wnprojection.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));arr=C.c_float*16;vec=C.c_float*4;xy=C.c_float*2
        lib.dw4_wn_projection_normalize.argtypes=[C.POINTER(C.c_float),C.POINTER(C.c_float)]
        lib.dw4_wn_projection_xy.argtypes=[C.POINTER(C.c_float),C.POINTER(C.c_float),C.POINTER(C.c_float)]
        lib.dw4_wn_viewport.argtypes=[C.c_float]*4;lib.dw4_wn_viewport.restype=C.c_float
        normalizations=transforms=viewports=0;late_normalization_negatives=0
        for values,misaligned in itertools.product(matrix_cases,(0,4)):
            world.w(0x568f04,4,DESCRIPTOR);world.w(DESCRIPTOR+48,4,BUFFER+misaligned)
            world.w(DESCRIPTOR+40,4,BUFFER+0x2000);world.w(0x56c2d8,4,bits(6))
            for i,b in enumerate(values):world.w(MATRIX+misaligned+4*i,4,b)
            world.invoke(0x1fbce0,3,MATRIX+misaligned)
            source=[world.read(BUFFER+misaligned+32+4*i,4) for i in range(16)]
            native=arr();lib.dw4_wn_projection_normalize(arr(*map(number,values)),native)
            assert list(struct.unpack('<16I',bytes(native)))==source
            assert world.read(DESCRIPTOR+48,4)==BUFFER+misaligned+96
            normalizations+=1
            camera=[bits(rng.uniform(-500,500)) for _ in range(3)]+[bits(1)]
            vf=[[0]*4 for _ in range(32)];vf[0][3]=bits(1)
            for i in range(4):vf[2+i]=source[i*4:i*4+4]
            vf[10]=camera;acc=[0]*4
            for word in transform:upper(word,vf,acc)
            actual=xy();lib.dw4_wn_projection_xy(vec(*map(number,camera)),native,actual)
            assert [bits(v) for v in actual]==vf[14][:2]
            transforms+=1
            # Late normalization is mathematically equivalent, not bit-equivalent.
            for column in range(2):
                late=f_mul(values[12+column],camera[3])
                for row in range(3):late=f_add(late,f_mul(values[row*4+column],camera[row]))
                late_normalization_negatives+=f_mul(late,bits(1/6))!=vf[14][column]
        for coordinate,w,dimension,origin in itertools.product(
                (-.9375,-.7232143,-.328125,-.00001,0,.00001,.328125,.7232143,.9375),
                (1.,2.,6.,300.,1000.),(640.,-448.),(2048.,1888.)):
            vf=[[0]*4 for _ in range(32)];vf[0][3]=bits(1)
            vf[4]=[bits(dimension*3)]*3+[bits(6)]
            vf[5]=[bits(origin)]*3+[0];vf[6][2]=f_div(bits(1),bits(w))
            vf[19]=[bits(coordinate)]*3+[bits(w)];acc=[0]*4
            for word in viewport:upper(word,vf,acc)
            expected=sx(vf[3][0],32)/16
            actual=lib.dw4_wn_viewport(coordinate,w,dimension,origin)
            assert actual==expected,(coordinate,w,dimension,origin,actual,expected)
            viewports+=1
        assert late_normalization_negatives
    print(f'WN projection: {normalizations} complete original matrix uploads, {transforms} VU transforms and '
          f'{viewports} VU viewport conversions pass; late normalization rejected in {late_normalization_negatives} columns; '
          'nearest scalar DIV and toward-zero EE/VU model pinned to capture profile, inputs/capacity controlled')

if __name__=='__main__':main()
