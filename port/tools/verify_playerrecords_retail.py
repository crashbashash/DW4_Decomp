#!/usr/bin/env python3
"""Execute retail SYS player queries with controlled folder/list lookup leaves."""
from native_shared import build_shared
import argparse
import ctypes as C
from pathlib import Path
import subprocess
import tempfile
from verify_scriptservices_retail import World, ROOT, BASE

FOLDER, RECORD, LIST=BASE+0x180000,BASE+0x180100,BASE+0x180200
class Value(C.Structure):
    _fields_=[('type',C.c_int),('number',C.c_double),('string',C.c_char_p),('length',C.c_size_t)]
class Retail(World):
    def string(self,p):
        p &= 0xffffffff
        if not p:return None
        out=[]
        while self.read(p,1):out.append(self.read(p,1));p+=1
        return bytes(out).decode('ascii')
    def call(self,e,a):
        a=[x&0xffffffff for x in a]
        if e==0x371c10:
            assert a[0]==self.player+1;return FOLDER
        if e==0x38e670:return 0
        if e==0x38f800:return FOLDER
        if e in (0x3a9220,0x3a9280,0x3a92e0,0x3a9310,0x3a92b0):
            assert a[0]==FOLDER and self.string(a[1])==self.key
            return RECORD
        return super().call(e,a)

def main():
    p=argparse.ArgumentParser();p.add_argument('--elf',type=Path,required=True);args=p.parse_args()
    if not args.elf.exists():print('player records retail: private ELF unavailable, skipped');return
    w=Retail(args.elf.read_bytes());total=0
    with tempfile.TemporaryDirectory(prefix='dw4-playerrecords-') as td:
        so=Path(td)/'records.so'
        build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/playerrecords.c'),'-lm','-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_playerrecords_open.restype=C.c_void_p
        lib.dw4_playerrecords_close.argtypes=[C.c_void_p]
        lib.dw4_playerrecords_get.argtypes=[C.c_void_p,C.c_char_p,C.c_int32];lib.dw4_playerrecords_get.restype=C.c_void_p
        lib.dw4_property_set_number.argtypes=[C.c_void_p,C.c_char_p,C.c_int32]
        lib.dw4_property_set_string.argtypes=[C.c_void_p,C.c_char_p,C.c_char_p]
        lib.dw4_property_set_strings.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(C.c_char_p),C.c_size_t]
        lib.dw4_playerrecords_call.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(Value),C.c_size_t,C.POINTER(Value),C.c_char_p,C.c_size_t]
        lib.dw4_property_set_array.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(C.c_int32),C.c_size_t]
        lib.dw4_property_set_bytes.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(C.c_ubyte),C.c_size_t]
        o=lib.dw4_playerrecords_open();assert o
        try:
            for player in range(4):
                w.player=player;folder=lib.dw4_playerrecords_get(o,b'GETPLAYER',player)
                for method,key,entry in [('SYSisJoinPlayer','ISUSE',0x371c70),('SYSgetPlayerLevel','LEVEL',0x372590),('SYSgetPlayerDigimon','DIGIMONNO',0x3725c0)]:
                    for v in [0,1,-1,256,257,2147483647,-2147483648]:
                        w.key=key;w.w(RECORD+12,4,v);expected=w.invoke(entry,player)&0xffffffff
                        assert lib.dw4_property_set_number(folder,key.encode(),v)==0
                        a=(Value*2)(Value(1,player,None,0),Value(1,0,None,0));r=Value();err=C.create_string_buffer(160)
                        assert lib.dw4_playerrecords_call(o,method.encode(),a,1,C.byref(r),err,160)==0,err.value
                        assert int(r.number)&0xffffffff==expected,(method,player,v,r.number,expected);total+=1
                w.key='DIGIMONNAME';w.w(RECORD+12,4,w.token('m_agumon'))
                expected=w.string(w.invoke(0x371ca0,player))
                assert lib.dw4_property_set_string(folder,b'DIGIMONNAME',b'm_agumon')==0
                assert lib.dw4_playerrecords_call(o,b'SYSgetPlayerName',a,1,C.byref(r),err,160)==0
                assert r.string.decode()==expected;total+=1
                strings=(C.c_char_p*3)(b'm_wp00',None,b'm_wp02')
                assert lib.dw4_property_set_strings(folder,b'POWERSOCKETNAME',strings,3)==0
                w.key='POWERSOCKETNAME';w.w(RECORD+12,4,LIST);w.list(LIST,[w.token('m_wp00'),0,w.token('m_wp02')])
                for socket in range(6):
                    a[1]=Value(1,socket,None,0);expected=w.string(w.invoke(0x371cd0,player,socket))
                    assert lib.dw4_playerrecords_call(o,b'SYSgetWeaponName',a,2,C.byref(r),err,160)==0
                    assert (r.string.decode() if r.string else None)==expected;total+=1
            common=lib.dw4_playerrecords_get(o,b'GETCOMMON',0);w.player=-1;w.key='NINZU'
            for value in (0,1,4,-1,2147483647):
                w.w(RECORD+12,4,value);want=w.invoke(0x371d70)&0xffffffff
                assert lib.dw4_property_set_number(common,b'NINZU',value)==0
                assert lib.dw4_playerrecords_call(o,b'SYSgetPlayerNinzu',a,0,C.byref(r),err,160)==0,err.value
                assert int(r.number)&0xffffffff==want;total+=1
            w.key='GATESTAGENAME'
            for name in (None,'GateOff','stagML12'):
                w.w(RECORD+12,4,w.token(name));want=w.string(w.invoke(0x3720f0))
                assert lib.dw4_property_set_string(common,b'GATESTAGENAME',name.encode() if name else None)==0
                assert lib.dw4_playerrecords_call(o,b'SYSgetGateStageName',a,0,C.byref(r),err,160)==0,err.value
                assert (r.string.decode() if r.string else None)==want;total+=1
            for player in range(4):
                w.player=player;w.key='BASE_ISUSE';folder=lib.dw4_playerrecords_get(o,b'GETPLAYER',player)
                words=(C.c_int32*16)(*(i*17 for i in range(16)))
                assert lib.dw4_property_set_array(folder,b'BASE_ISUSE',words,16)==0
                w.w(RECORD+12,4,LIST);w.list(LIST,list(words),1)
                for index in range(16):
                    want=w.invoke(0x3725f0,player,index)&255
                    a[0]=Value(1,player,None,0);a[1]=Value(1,index,None,0)
                    assert lib.dw4_playerrecords_call(o,b'SYSisGetShinkaDigimon',a,2,C.byref(r),err,160)==0,err.value
                    assert int(r.number)==want;total+=1
            w.player=0;w.key='CARDLIST';folder=lib.dw4_playerrecords_get(o,b'GETPLAYER',0)
            for count in (0,1,16,50):
                cards=[(i%4) for i in range(count)];raw=(C.c_ubyte*count)(*cards)
                assert lib.dw4_property_set_bytes(folder,b'CARDLIST',raw,count)==0
                w.w(RECORD+12,4,LIST);w.list(LIST,cards,1)
                want=w.invoke(0x372640,w.token('KAZU'),0)&0xffffffff
                a[0]=Value(2,0,b'KAZU',4);a[1]=Value(1,0,None,0)
                assert lib.dw4_playerrecords_call(o,b'SYSctlCardFolder',a,2,C.byref(r),err,160)==0,err.value
                assert int(r.number)==want;total+=1
        finally:lib.dw4_playerrecords_close(o)
    print(f'player records retail: {total} SYS query results match retail instructions (lookup/list leaves controlled)')
if __name__=='__main__':main()
