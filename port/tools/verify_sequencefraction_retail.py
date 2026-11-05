#!/usr/bin/env python3
"""Adjacent-key fractions against complete original 001df040 instructions."""
import ctypes as C
import itertools
import random
import struct
import subprocess
import tempfile
from pathlib import Path
from verify_scriptservices_retail import World, ROOT, BASE
from ee_core import sx

NODE,LIST,KEYS,LOW,HIGH,FRACTION,CACHE=range(BASE+0x280000,BASE+0x280700,0x100)
class Loop(World):
    def call(self,entry,args):
        if entry==KEYS:
            return self.first if args[1]==0 else self.last
        if entry==0x1dd4b0:
            dividend=sx(args[0],64);divisor=sx(args[1],64)
            quotient=dividend//divisor;self.w(args[2],8,dividend-quotient*divisor);return quotient
        if entry==0x1bfc70:return 0 # Selected-key/fraction consumer is independently checked.
        return super().call(entry,args)
    def step(self,pc,delay=False):
        if pc==0x1bfa2c:self.normalized=sx(self.r[19],64)
        return super().step(pc,delay)
    def clock(self,first,last,duration,now):
        self.first=first;self.last=last
        self.w(NODE,4,LIST);self.w(LIST+0xa8,4,KEYS)
        self.w(NODE+16,4,CACHE);self.w(CACHE+8,4,2)
        self.w(NODE+40,8,duration);self.w(NODE+48,4,0);self.w(NODE+52,4,1)
        self.invoke(0x1bf7d0,NODE,LOW,HIGH,FRACTION,CACHE,LOW+4,HIGH+4,now)
        return self.normalized

def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():
        print('sequence fraction: private ELF unavailable, skipped');return
    w=World(elf.read_bytes())
    w.w(NODE+56,4,LIST);w.w(LIST+8,4,2);w.w(LIST+16,4,KEYS)
    cases=[]
    for start,gap in itertools.product((-10**12,-262145,-1,0,1,262143,10**12),
            (1,262143,262144,262145,16666667,83333336,10**9,5*10**9,1<<49,1<<50,(1<<50)+262144)):
        cases.extend((start,start+gap,start+offset) for offset in {0,1,gap//2,gap-1,gap} if offset<=gap)
    rng=random.Random(20836)
    for _ in range(512):
        first=rng.randrange(-10**12,10**12);gap=rng.randrange(1,10**11)
        cases.append((first,first+gap,first+rng.randrange(gap+1)))
    total=0;full_ns_negatives=0;separate_shift_negatives=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'fraction.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra',
            '-I'+str(ROOT/'include'),'-I'+str(ROOT/'recovered/frontend'),
            str(ROOT/'src/sequencefraction.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));fraction=lib.dw4_sequence_fraction
        loop=lib.dw4_sequence_loop_clock;loop.argtypes=[C.c_int64,C.c_int64,C.c_int64];loop.restype=C.c_int64
        fraction.argtypes=[C.c_int64,C.c_int64,C.c_int64];fraction.restype=C.c_uint32
        for first,last,now in cases:
            w.w(KEYS,8,first);w.w(KEYS+8,8,last);w.w(CACHE,4,1)
            w.invoke(0x1df040,NODE,now,LOW,HIGH,FRACTION,CACHE)
            expected=w.read(FRACTION,4)
            assert (w.read(LOW,4),w.read(HIGH,4),w.read(CACHE,4))==(0,1,1)
            actual=fraction(now,first,last)
            assert actual==expected,(first,last,now,hex(actual),hex(expected))
            naive=struct.unpack('<I',struct.pack('<f',(now-first)/(last-first)))[0]
            full_ns_negatives+=naive!=expected
            # Shifting timestamps separately changes the boundary remainder.
            a,b=(now>>18)-(first>>18),(last>>18)-(first>>18)
            separate=struct.unpack('<I',struct.pack('<f',a/b if b else 0))[0]
            separate_shift_negatives+=separate!=expected
            total+=1
        original=Loop(elf.read_bytes());loops=0
        for first,duration in itertools.product((0,262144,10**9),(1,262144,1983333349,3316666603)):
            for elapsed in (0,1,duration-1,duration,duration+1,2*duration,2*duration+1,100*duration+123):
                now=first+elapsed
                assert loop(now,first,duration)==original.clock(first,first+duration,duration,now),(first,duration,now)
                loops+=1
    assert full_ns_negatives and separate_shift_negatives
    print(f'sequence fraction: {total} adjacent-key queries match complete original 001df040; '
          f'full-ns division rejected in {full_ns_negatives}, separate timestamp shifts in {separate_shift_negatives}; '
          'EE FPU model assumed, bracket inputs controlled')
    print(f'compressed ambient clock: {loops} original 1bf7d0 strict-end/loop states match; key and division leaves controlled')

if __name__=='__main__':main()
