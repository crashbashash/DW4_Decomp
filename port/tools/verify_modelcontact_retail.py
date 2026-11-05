#!/usr/bin/env python3
"""Contact Lua helpers vs original bodies, including matrix arithmetic/atan2.
Formatting is the platform leaf; it consumes the original converted doubles.
"""
import ctypes as C
import random
import struct
import subprocess
import tempfile
from pathlib import Path
from verify_scriptservices_retail import World,ROOT,BASE
MATRIX=BASE+0x500000
class Value(C.Structure):
    _fields_=[('type',C.c_int),('number',C.c_double),('string',C.c_char_p),('length',C.c_size_t)]
class Contact(C.Structure):
    _fields_=[('world',C.c_float*16),('bullet_kind',C.c_int32),('bullet_box',C.c_int32),('shoot_ram_no',C.c_int32),('damage_turn',C.c_int),('result',C.c_char*192),('fight',C.c_void_p),('target_row',C.c_int32),('target_max_hp',C.c_int32),('target_slot',C.c_int32),('source_row',C.c_int32),('receiver_status',C.c_void_p),('source_status',C.c_void_p),('cached',C.c_int32*3),('sequence',C.c_char_p),('bullet_name',C.c_char_p)]
def bits(x):return struct.unpack('<I',struct.pack('<f',x))[0]
class Retail(World):
    def read(self,a,n):
        if 0x4e1098<=a and a+n<=0x4e10a4:return sum(self.mem.get(a+i,0)<<(8*i) for i in range(n))
        return super().read(a,n)
    def call(self,e,a):
        if e==0x129e60:
            values=[struct.unpack('<d',struct.pack('<Q',x&((1<<64)-1)))[0] for x in a[2:5]]
            self.formatted='V<%f,%f,%f>'%tuple(values)
            return len(self.formatted)
        raise AssertionError('unexpected contact helper leaf %#x'%e)
    def helper(self,entry,offset):
        self.ee_reset();self.descend={0x190380,0x1908f0,0x190a50,0x190a30,0x192f50,0x123640,0x11ede8,0x122d90,0x123210}|set(range(0x22e000,0x231100,4))
        self.f[12:15]=list(map(bits,offset));self.r[28]=0x55c870;self.r[29]=0x1fff000;self.r[31]=0xfffffff0
        self.formatted=None;self.run_until(entry,0xfffffff0)
        assert self.formatted is not None
        return self.formatted

def main():
    image=ROOT.parent.parent/'local/extracted/SLUS_208.36';w=Retail(image.read_bytes());w.w(0x58a1e8,4,MATRIX)
    # Startup-initialized +Z: raw retail ELF storage is zero, so startup is a controlled precondition.
    for i,b in enumerate(struct.pack('<3f',0,0,1)):w.w(0x4e1098+i,1,b)
    rng=random.Random(41761);total=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'contact.so'
        abi=Path(td)/'abi.c'
        abi.write_text('#include "dw4/modelcontact.h"\n#include <stddef.h>\nsize_t contact_abi(unsigned i){const size_t v[]={sizeof(dw4_model_contact),offsetof(dw4_model_contact,fight),offsetof(dw4_model_contact,sequence)};return v[i];}\n')
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror','-I'+str(ROOT/'include'),'-I'+str(ROOT/'recovered/frontend'),
            *map(str,[ROOT/'src/modelcontact.c',ROOT/'src/modelai.c',ROOT/'src/random.c',ROOT/'recovered/frontend/eefloat.c',abi]),'-lm','-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.contact_abi.argtypes=[C.c_uint];lib.contact_abi.restype=C.c_size_t
        assert [lib.contact_abi(i) for i in range(3)]==[C.sizeof(Contact),Contact.fight.offset,Contact.sequence.offset], 'contact ctypes layout is stale'
        call=lib.dw4_model_contact_call
        call.argtypes=[C.POINTER(Contact),C.c_char_p,C.POINTER(Value),C.c_size_t,C.POINTER(Value),C.c_char_p,C.c_size_t]
        err=C.create_string_buffer(128);out=Value()
        for index in range(160):
            m=[rng.uniform(-3,3) for _ in range(16)];m[12:15]=[rng.uniform(-1000,1000) for _ in range(3)]
            if index==0:m=[1,0,0,0,0,1,0,0,0,0,1,0,10,20,30,1]
            elif index==1:m=[-1,0,0,0,0,1,0,0,0,0,-1,0,-0.,0,0,1]
            c=Contact((C.c_float*16)(*m),60000,index%4,index%4,1)
            for i,x in enumerate(c.world):w.w(MATRIX+4*i,4,bits(x))
            offset=[0,0,0] if index<2 else [rng.uniform(-12,12) for _ in range(3)]
            offset=[C.c_float(x).value for x in offset];args=(Value*3)(*[Value(1,x,None,0) for x in offset])
            for method,entry in [('MDLgetPosStr',0x373b40),('MDLgetRotStr',0x373c10)]:
                wanted=w.helper(entry,offset)
                assert call(C.byref(c),method.encode(),args,3,C.byref(out),err,128)==0,err.value
                actual=C.string_at(out.string,out.length).decode()
                assert actual==wanted,(index,method,actual,wanted,m,offset)
                total+=1
        for kind in (-2147483648,-1,0,1,60000,2147483647):
            c=Contact();c.bullet_kind=c.bullet_box=c.shoot_ram_no=kind
            for method,entry,global_ in [('MDLgetBulletKind',0x373e80,0x58a1fc),('MDLgetBulletBoxNo',0x373ee0,0x58a200),('BLTgetShootRamNo',0x374880,0x58a208)]:
                w.w(global_,4,kind);wanted=w.invoke(entry)&0xffffffff
                assert not call(C.byref(c),method.encode(),None,0,C.byref(out),err,128)
                assert int(out.number)&0xffffffff==wanted;total+=1
        for turn in (-2147483648,-1,0,1,2,255,2147483647):
            c=Contact();c.damage_turn=99;arg=Value(1,turn,None,0)
            w.invoke(0x374160,turn);wanted=w.read(0x58a210,1)
            assert not call(C.byref(c),b'MDLsetDMGTurn',C.byref(arg),1,C.byref(out),err,128)
            assert c.damage_turn==wanted;total+=1
        assert call(None,b'MDLgetPosStr',None,0,C.byref(out),err,128)==1
    print(f'model contact: {total} original helper results match, real matrix/atan2/conversion bodies; formatting is the platform leaf')
if __name__=='__main__':main()
