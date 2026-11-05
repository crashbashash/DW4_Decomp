#!/usr/bin/env python3
"""Typed native MAT callback projection versus all seven original helpers.
No controlled callee leaves: the original helpers only read/write fixture RAM.
"""
import argparse
import ctypes as C
from pathlib import Path
import subprocess
import tempfile
from verify_scriptservices_retail import World,ROOT,BASE
OWNER,NOW,OLD=BASE+0x400000,BASE+0x401000,BASE+0x402000
class Value(C.Structure):
    _fields_=[('type',C.c_int),('number',C.c_double),('string',C.c_char_p),('length',C.c_size_t)]
class Contact(C.Structure):
    _fields_=[('active',C.c_int),('exists',C.c_uint8*4),('current',C.c_uint32),('previous',C.c_uint32),
              ('index',C.c_uint32),('request_index',C.c_uint32),('request_value',C.c_uint8)]
class Retail(World):
    def call(self,entry,a):raise AssertionError(f'unexpected MAT helper leaf {entry:x}')
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--roms',default=str(ROOT.parent.parent/'local/extracted'));ap.add_argument('--elf');a=ap.parse_args()
    elf=Path(a.elf) if a.elf else Path(a.roms)/'SLUS_208.36'
    w=Retail(elf.read_bytes());w.descend=set()
    w.w(OWNER+40,4,0);w.w(OWNER+56,4,NOW);w.w(OWNER+60,4,OLD);w.list(NOW,[0]);w.list(OLD,[0])
    entries=[('MATisPlayer',0x38aca0),('MATisAllPlayer',0x38acd0),('MATgetPlayerNo',0x38ad40),
             ('MATisRidePlayer',0x38add0),('MATisRideOffPlayer',0x38ae30),('MATgetPlayerMatStat',0x38aea0)]
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'contact.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',
            '-I'+str(ROOT/'include'),str(ROOT/'src/materialcontact.c'),'-lm','-o',str(so)],check=True)
        lib=C.CDLL(str(so));call=lib.dw4_material_contact_call
        call.argtypes=[C.POINTER(Contact),C.c_char_p,C.POINTER(Value),C.c_size_t,C.POINTER(Value),C.c_char_p,C.c_size_t]
        error=C.create_string_buffer(128);result=Value();arg=Value(1,0,None,0);total=0
        def compare(current,previous,exists):
            nonlocal total
            c=Contact(1,(C.c_uint8*4)(*exists),current,previous,0,0xffffffff,1)
            w.w(NOW+0x40000,4,current);w.w(OLD+0x40000,4,previous)
            for i,v in enumerate(exists):w.w(OWNER+32+i,1,v)
            for j,(name,entry) in enumerate(entries):
                for player in (range(4) if j>=3 else (None,)):
                    arg.number=0 if player is None else player
                    expected=w.invoke(entry,OWNER,*(() if player is None else (player,)))
                    assert not call(C.byref(c),name.encode(),C.byref(arg),0 if player is None else 1,C.byref(result),error,128),error.value
                    assert result.type==1 and result.number==expected,(name,current,previous,exists,player,result.number,expected)
                    assert c.request_index==0xffffffff and c.request_value==1
                    total+=1
        for current in range(16):
            for previous in range(16):
                for roster in range(16):compare(current,previous,[(1,2,128,255)[i] if roster&(1<<i) else 0 for i in range(4)])
        for current,previous in ((0x80000000,0),(0,0x80000000),(0xffffffff,0xffffffff),(16,0)):
            compare(current,previous,[1,2,128,255])
            c=Contact(1,(C.c_uint8*4)(1,2,128,255),current,previous,0,0xffffffff,1)
            for player in (-33,-1,4,31,32,33,63):
                for name,entry in entries[3:]:
                    arg.number=player;expected=w.invoke(entry,OWNER,player)
                    assert not call(C.byref(c),name.encode(),C.byref(arg),1,C.byref(result),error,128)
                    assert result.number==expected;total+=1
        for index in (0,2,0xffffffff):
            for value in (0,1,255,256,-1,257):
                c=Contact(1,(C.c_uint8*4)(),0,0,index,0xffffffff,1);w.w(OWNER+40,4,index)
                w.invoke(0x38ae90,OWNER,value);arg.number=value
                assert not call(C.byref(c),b'MATsetRun',C.byref(arg),1,C.byref(result),error,128)
                assert result.type==0 and (c.request_index,c.request_value)==(w.read(OWNER+48,4),w.read(OWNER+52,1));total+=1
        c.active=0;assert call(C.byref(c),b'MATisAllPlayer',None,0,C.byref(result),error,128)==-1
        assert call(C.byref(c),b'unrelated',None,0,C.byref(result),error,128)==1
    print(f'native MAT contacts: {total} original-helper return/deferred-request comparisons pass; all four-player masks/rosters, noncanonical existence bytes and wrapped shifts; geometry/callback scheduling remain separate')
if __name__=='__main__':main()
