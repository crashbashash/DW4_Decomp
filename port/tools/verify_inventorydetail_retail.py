#!/usr/bin/env python3
"""Execute retail identity-preserving revision/record sort helpers."""
from native_shared import build_shared
import ctypes as C
import random
import subprocess
import tempfile
from pathlib import Path
from verify_scriptservices_retail import World, ROOT, BASE
LIST,TEMP,REF,ITEMS=BASE+0x180000,BASE+0x181000,BASE+0x182000,BASE+0x183000
class Item(C.Structure):
    _fields_=[(k,C.c_int32) for k in ('kind','record','equipped','revision','pocket')]
class Retail(World):
    def call(self,e,a):
        a=[x&0xffffffff for x in a]
        if e in (0x301000,0x2f88e0):return 0
        if e==0x3c90f0:return TEMP
        if e==0x302000:
            rows=self.values(a[1]);rows.remove(a[2]);self.list(a[1],rows);return 0
        return super().call(e,a)
    def sort(self,items,chips):
        ptrs=[ITEMS+i*32 for i in range(len(items))]
        for p,item in zip(ptrs,items):
            self.w(p+4,4,1000)
            for off,v in zip((8,12,16,20,24),item):self.w(p+off,4,v)
        self.list(LIST,ptrs);self.list(TEMP,[]);self.w(TEMP+4,4,1000);self.w(REF,4,LIST)
        self.invoke(0x423000 if chips else 0x422c00,BASE,REF)
        return [ptrs.index(p) for p in self.values(LIST)]
def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('inventory sort: private ELF unavailable, skipped');return
    w=Retail(elf.read_bytes());rng=random.Random(20836);total=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'sort.so'
        build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/inventorydetail.c'),str(ROOT/'src/playerrecords.c'),'-lm','-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_inventory_sort_part.argtypes=[C.POINTER(Item),C.c_size_t,C.c_int,C.POINTER(C.c_int32)]
        for chips in (0,1):
            for n in (0,1,2,3,12,35,36):
                for case in range(32):
                    kind=3 if chips else case%3
                    items=[(kind,(276,31,44)[kind] if not chips and i%5==0 else rng.choice((-1,0,1,2,27,2147483647)),0,
                            rng.choice((-2147483648,-1,0,1,31,1000,2147483647)),0) for i in range(n)]
                    expected=w.sort(items,chips);out=(C.c_int32*max(n,1))()
                    assert lib.dw4_inventory_sort_part((Item*n)(*[Item(*x) for x in items]),n,chips,out)==0
                    assert list(out)[:n]==expected,(chips,n,case,list(out)[:n],expected)
                    total+=1
    print(f'inventory sort: {total} signed/tied/special-record identity permutations match retail 422c00/423000; allocation/list leaves controlled')
if __name__=='__main__':main()
