#!/usr/bin/env python3
"""Compare custom byte decoding with original 382eb0, allocation/string leaves controlled."""
import ctypes as C
import argparse
import random
import struct
import subprocess
import tempfile
from pathlib import Path
from verify_statusviews_retail import Views,ROOT,BASE

OWNER,OBJ,BUFFER,INPUT,OUTPUT,BUILDER=[BASE+0x280000+i*0x10000 for i in range(6)]
class Retail(Views):
    def call(self,e,a):
        a=[v&0xffffffff for v in a]
        if e==0x12a78c:
            n=0
            while self.read(a[0]+n,1):n+=1
            return n
        if e in (0x301000,0x2f88e0,0x2ff820):return 0
        if e==0x30b420:self.w(a[0]+12,4,0);return 0
        if e==0x30b460:self.w(a[0]+12,4,self.read(a[0]+12,4)+a[3]);return 0
        if e==0x3614f0:self.w(OBJ+4,4,1000);return OBJ
        if e==0x3843c0:self.w(OBJ+12,4,BUFFER);return 0
        raise AssertionError(f'unknown decoder leaf {e:#x}')
    def decode(self,bytes):
        self.w(OWNER+56,4,BUILDER)
        for i,b in enumerate(bytes+b'\0'):self.w(INPUT+i,1,b)
        self.invoke(0x382eb0,OUTPUT,OWNER,INPUT)
        assert self.read(OUTPUT,4)==OBJ
        result=[]
        while self.read(BUFFER+len(result)*2,2):
            result.append(self.read(BUFFER+len(result)*2,2));assert len(result)<=len(bytes)
        return result

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--elf',type=Path,default=ROOT.parent.parent/'local/extracted/SLUS_208.36');a=p.parse_args()
    if not a.elf.exists():print('text codec retail: private ELF unavailable, skipped');return
    image=a.elf.read_bytes()
    pairs=[struct.unpack_from('<HH',image,0x4c8880-0x100000+0x80+i*4) for i in range(424)]
    encoded=[bytes([v]) if v<128 else bytes([v>>8,v&255]) for u,v in pairs]
    cases=[bytes([b]) for b in range(256)]+encoded
    cases+=[b'',b'A\nB',b'AA\nB',b'\r\nAB',b'A\rB',b'AA\n\nB',b'\x81\xbaWeapon',b'\x8a\x71Weapon']
    rng=random.Random(20836)
    for _ in range(128):cases.append(b''.join(rng.choice(encoded+[b'\n',b'\r',b'\x7f',b'\xff\xff']) for _ in range(rng.randrange(1,12))))
    w=Retail(image)
    with tempfile.TemporaryDirectory() as tmp:
        so=Path(tmp)/'codec.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/textcodec.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_textcodec_decode.argtypes=[C.c_char_p,C.c_size_t,C.POINTER(C.c_uint32),C.c_size_t,C.POINTER(C.c_size_t)]
        for value in cases:
            expected=w.decode(value);out=(C.c_uint32*(len(value)+1))();n=C.c_size_t()
            assert not lib.dw4_textcodec_decode(value,len(value),out,len(out),C.byref(n))
            assert list(out)[:n.value]==expected and out[n.value]==0,(value,list(out)[:n.value],expected)
        out=(C.c_uint32*1)(0xdeadbeef);n=C.c_size_t(123)
        assert lib.dw4_textcodec_decode(b'AB',2,out,1,C.byref(n))==-1 and out[0]==0xdeadbeef and n.value==123
    print(f'text codec: {len(cases)} original byte/mapped-pair/icon/CR/LF/mixed-string outputs match 382eb0; allocation and builder leaves controlled; bounded failure preserves output')

if __name__=='__main__':main()
