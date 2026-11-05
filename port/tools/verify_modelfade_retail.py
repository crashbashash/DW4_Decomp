#!/usr/bin/env python3
"""Fade arithmetic against original 376680, with frame delta/attributes controlled."""
import ctypes as C
import itertools
import struct
import subprocess
import tempfile
from pathlib import Path
from verify_scriptservices_retail import World, ROOT, BASE
RAM,WORK,CTX,ATTR,VT,HOOK=range(BASE+0x280000,BASE+0x280600,0x100)
def bits(x):return struct.unpack('<I',struct.pack('<f',x))[0]
class State(C.Structure):
    _fields_=[('value',C.c_uint32),('step',C.c_uint32),('limit',C.c_uint32),('direction',C.c_int),('updated',C.c_int),('clock',C.c_int64)]
class Retail(World):
    def call(self,e,a):
        if e==0x3a8140:self.f[0]=self.delta;return self.delta
        if e in (0x193540,0x302000,0x3a8580,HOOK):return 0
        return super().call(e,a)
    def update(self,state,delta):
        self.delta=delta;self.w(RAM+56,4,WORK);self.w(RAM+44,4,CTX);self.w(CTX+136,4,CTX+0x80)
        for off,val in ((52,state.direction),(56,state.limit),(60,state.step),(64,state.value),(80,ATTR),(84,ATTR),(88,ATTR),(92,ATTR)):self.w(WORK+off,4,val)
        self.w(ATTR,4,VT);self.w(ATTR+4,4,1000);self.w(VT+128,4,HOOK)
        self.invoke(0x376680,BASE,RAM)
        return self.read(WORK+64,4),self.read(WORK+52,4)
def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('model fade: private ELF unavailable, skipped');return
    w=Retail(elf.read_bytes());total=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'fade.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),'-I'+str(ROOT/'recovered/frontend'),str(ROOT/'src/modelfade.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-lm','-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_modelfade_start.argtypes=[C.POINTER(State),C.c_int,C.c_uint32,C.c_uint32,C.c_int64];lib.dw4_modelfade_tick.argtypes=[C.POINTER(State),C.c_int64]
        for direction,frames,limit in itertools.product(range(2),(.5,1,15,30,50),(0,.2,.5,1)):
            state=State();lib.dw4_modelfade_start(C.byref(state),direction,bits(frames),bits(limit),0)
            for index,now in enumerate((0,0,16666667,33333334,100000000,100000000,116666667,1000000000,*range(1016666667,3000000000,16666667))):
                delta=1 if not state.updated else min(3,((now>>18)-(state.clock>>18))*262144/16666667)
                # The timer returns a binary32 quotient before fade multiplication.
                delta=bits(delta)
                expected=w.update(state,delta)
                lib.dw4_modelfade_tick(C.byref(state),now)
                assert (state.value,state.direction)==expected,(direction,frames,limit,index,hex(state.value),state.direction,expected)
                total+=1
    print(f'model fade: {total} IN/OUT value/direction steps match original 376680; frame delta and attribute leaves controlled')
if __name__=='__main__':main()
