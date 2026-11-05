#!/usr/bin/env python3
"""Original NUMBERCTRL 3a4b20 digit/UV projection; vertex lock leaves controlled."""
import ctypes as C
import itertools
import struct
import subprocess
import tempfile
from pathlib import Path
from verify_scriptservices_retail import World,ROOT,BASE
RAM,GEOM,ATTRS,ATTR,VA,VT,DIGITS=range(BASE+0x2c0000,BASE+0x2c0700,0x100)
UV=BASE+0x2d0000;LOCK,UNLOCK=BASE+0x2e0000,BASE+0x2e0004
def bits(x):return struct.unpack('<I',struct.pack('<f',x))[0]
class Retail(World):
    def call(self,e,a):
        if e==0x15db90:return 0
        if e==LOCK:self.w(a[1]+16,4,UV);self.w(a[1]+20,4,8);return 0
        if e==UNLOCK:return 0
        return super().call(e,a)
    def project(self,value,mode,offset):
        self.w(RAM+44,4,GEOM);self.w(GEOM+32,4,ATTRS);self.list(ATTRS,[ATTR]);self.w(ATTR+12,4,VA)
        self.w(VA,4,VT);self.w(VA+12,4,36);self.w(VT+108,4,LOCK);self.w(VT+112,4,UNLOCK)
        self.w(RAM+48,4,bits(offset));self.w(RAM+56,4,mode);self.w(RAM+60,4,DIGITS)
        digits=[];kinds=(0,1,2,1,3,2)
        for d in range(6):
            data=BASE+0x300000+d*0x1000;vl=data+0x100;digits.append(data);self.w(data+12,4,vl)
            refs=[]
            for v,kind in enumerate(kinds):
                vr=data+0x200+v*32;refs.append(vr);self.w(vr+8,4,d*6+v);self.w(vr+12,4,kind)
            self.list(vl,refs)
        self.list(DIGITS,digits);self.invoke(0x3a4b20,BASE,RAM,value)
        return [C.c_int32(self.read(d+8,4)).value for d in digits],[(self.read(UV+i*8,4),self.read(UV+i*8+4,4)) for i in range(36)]
def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('HUD number: private ELF unavailable, skipped');return
    w=Retail(elf.read_bytes());total=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'number.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),'-I'+str(ROOT/'recovered/frontend'),str(ROOT/'src/hudnumber.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_hudnumber_digit.argtypes=[C.c_int32,C.c_int,C.c_uint];lib.dw4_hudnumber_uv.argtypes=[C.c_int32,C.c_uint,C.c_float,C.POINTER(C.c_float)]
        for value,mode,offset in itertools.product((-1,0,1,9,10,100,170,999,99999,999999),range(2),(.0938,.1)):
            expected_digits,expected_uv=w.project(value,mode,offset)
            digits=[lib.dw4_hudnumber_digit(value,mode,d) for d in range(6)];assert digits==expected_digits
            actual=[]
            for digit in digits:
                for kind in (0,1,2,1,3,2):
                    uv=(C.c_float*2)();lib.dw4_hudnumber_uv(digit,kind,offset,uv)
                    actual.append(tuple(int.from_bytes(C.c_float(v),'little') for v in uv))
            assert actual==expected_uv,(value,mode,offset,actual,expected_uv);total+=1
    print(f'HUD number: {total} original 3a4b20 digit arrays / {total*36} UV pairs match; vertex lock/unlock leaves controlled')
if __name__=='__main__':main()
