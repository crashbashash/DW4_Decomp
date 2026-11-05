#!/usr/bin/env python3
"""HUD meter display/time steps against original 38fa50, unbound HP leaves."""
import ctypes as C
import itertools
import struct
import subprocess
import tempfile
from pathlib import Path
from verify_scriptservices_retail import World,ROOT,BASE
RAM,INFO,LIST,DATA,NODE,TIMES=range(BASE+0x2b0000,BASE+0x2b0600,0x100)
def bits(x):return struct.unpack('<I',struct.pack('<f',x))[0]
class State(C.Structure):
    _fields_=[(n,C.c_uint32) for n in ('maximum','ratio','step','target','display')]+[(n,C.c_int64) for n in ('nonzero','nonmax','time')]+[('notch',C.c_int)]
class Retail(World):
    def call(self,e,a):
        if e==0x357600:return 0
        if e==0x38d4a0:return 4
        if e==0x38f3d0:self.f[0]=bits(self.percent);return 0
        if e==0x230110:
            return int(struct.unpack('<f',struct.pack('<I',self.f[12]))[0])
        return super().call(e,a)
    def tick(self,s):
        self.w(RAM+8,4,0);self.w(RAM+12,4,INFO);self.w(RAM+24,4,1)
        self.w(INFO+28,4,LIST);self.list(LIST,[DATA]);self.w(DATA+12,4,NODE)
        for off,value in ((16,s.maximum),(20,s.ratio),(24,s.step),(28,s.target),(32,s.display)):
            self.w(DATA+off,4,value)
        self.w(DATA+40,8,s.nonzero);self.w(DATA+48,8,s.nonmax)
        self.w(DATA+60,1,1);self.w(DATA+62,1,s.notch);self.w(DATA+64,4,0)
        self.w(NODE+32,1,1);self.w(NODE+36,4,TIMES);self.list(TIMES,[0,0,0,0])
        self.invoke(0x38fa50,BASE,RAM)
        return self.read(DATA+32,4),self.read(self.read(TIMES+16,4),8)
def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('HUD meter: private ELF unavailable, skipped');return
    w=Retail(elf.read_bytes());total=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'meter.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),'-I'+str(ROOT/'recovered/frontend'),str(ROOT/'src/hudmeter.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_hudmeter_init.argtypes=[C.POINTER(State),C.c_float,C.c_int,C.c_int64,C.c_int64];lib.dw4_hudmeter_percent.argtypes=[C.POINTER(State),C.c_float];lib.dw4_hudmeter_tick.argtypes=[C.POINTER(State)]
        for maximum,notch in itertools.product((1,10,100,999),range(2)):
            s=State();assert not lib.dw4_hudmeter_init(C.byref(s),maximum,notch,16666667,1983333373)
            w.w(DATA+16,4,bits(maximum));w.invoke(0x38f9b0,BASE,DATA)
            assert (s.ratio,s.step)==(w.read(DATA+20,4),w.read(DATA+24,4))
            for percent in (100,50,.1,0,1,99,150,-1,100,0):
                lib.dw4_hudmeter_percent(C.byref(s),percent)
                w.tick(s);w.percent=percent;w.invoke(0x38ff40,BASE,RAM,0)
                assert s.target==w.read(DATA+28,4),(maximum,percent,s.target,w.read(DATA+28,4))
                for tick in range(130):
                    expected=w.tick(s);lib.dw4_hudmeter_tick(C.byref(s))
                    assert (s.display,s.time)==expected,(maximum,notch,percent,tick,s.display,s.time,expected)
                    total+=1
    print(f'HUD meter: {total} display/time steps match retail 38fa50 across notch modes, endpoints and target changes')
if __name__=='__main__':main()
