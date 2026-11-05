#!/usr/bin/env python3
"""Trigger/repeat counters against original bePadData digital helper 39af10."""
import ctypes as C
import itertools
import struct
import subprocess
import tempfile
from pathlib import Path
from verify_scriptservices_retail import World,ROOT,BASE
PAD=BASE+0x2f0000
class State(C.Structure):
    _fields_=[(n,C.c_uint32) for n in ('held','trigger','repeat')]+[(n,C.c_int32) for n in ('countdown','first','next')]
def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('pad repeat: private ELF unavailable, skipped');return
    w=World(elf.read_bytes());total=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'pad.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),'-I'+str(ROOT/'recovered/frontend'),str(ROOT/'src/padrepeat.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-lm','-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_padrepeat_tick.argtypes=[C.POINTER(State),C.c_uint32]
        for previous,held,countdown,first,nxt in itertools.product((0,1,2,8,0x20,0x2000),(0,1,2,8,0x20,0x2000),(-2147483648,-1,0,1,2,10),(0,1,10),(0,1,6)):
            s=State(previous,0,0,countdown,first,nxt)
            for off,v in ((68,s.held),(84,s.countdown),(96,s.first),(100,s.next)):w.w(PAD+off,4,v)
            w.invoke(0x39af10,PAD,held);expected=tuple(w.read(PAD+off,4) for off in (68,72,76,84))
            lib.dw4_padrepeat_tick(C.byref(s),held)
            assert (s.held,s.trigger,s.repeat,s.countdown&0xffffffff)==expected
            total+=1
    print(f'pad repeat: {total} held/trigger/repeat/countdown states match retail 39af10; default first10/next6 verified in39ae50')
if __name__=='__main__':main()
