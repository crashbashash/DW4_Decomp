#!/usr/bin/env python3
"""ADDHP/MP zero restoration against retail, lookup and output commands controlled."""
from native_shared import build_shared
import ctypes as C
import itertools
import subprocess
import tempfile
from pathlib import Path
from verify_statusctrl_retail import Retail as BaseRetail,ROOT,BASE
OWNER,LIST,FOLDER,PROPS=range(BASE+0x2a0000,BASE+0x2a0400,0x100)
class Health(C.Structure):
    _fields_=[(k,C.c_int32) for k in ('level','hp','mp','max_hp','max_mp','hp_publish')]+[('hp_percent',C.c_float),('mp_percent',C.c_float)]
class Retail(BaseRetail):
    def call(self,e,a):
        if e==0x3a9220:return self.prop[self.string(a[1])]
        if e==0x38f350:self.percent.append(self.f[12]);return 0
        if e in (0x38d860,0x38f250,0x38e060):return 0
        return super().call(e,a)
    def restore(self,hp,mp,mhp,mmp,amount=0,absolute=-1):
        self.percent=[];self.w(OWNER+68,4,LIST);self.list(LIST,[FOLDER]);self.prop={}
        for i,(key,value) in enumerate(zip(('HP','MP','MHP','MMP'),(hp,mp,mhp,mmp))):
            p=PROPS+i*32;self.prop[key]=p;self.w(p+12,4,value)
        result=self.invoke(0x3f9c80,OWNER,0,amount,absolute)
        self.invoke(0x3f9e20,OWNER,0,amount)
        return C.c_int32(self.read(self.prop['HP']+12,4)).value,C.c_int32(self.read(self.prop['MP']+12,4)).value,int(result),self.percent

def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('player health: private ELF unavailable, skipped');return
    w=Retail(elf.read_bytes());total=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'health.so';build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),'-I'+str(ROOT/'recovered/frontend'),str(ROOT/'src/playerhealth.c'),str(ROOT/'src/playerrecords.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-lm','-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_playerrecords_open.restype=C.c_void_p
        lib.dw4_playerrecords_close.argtypes=[C.c_void_p];lib.dw4_playerrecords_get.argtypes=[C.c_void_p,C.c_char_p,C.c_int];lib.dw4_playerrecords_get.restype=C.c_void_p
        lib.dw4_property_set_number.argtypes=[C.c_void_p,C.c_char_p,C.c_int32];lib.dw4_playerhealth_restore.argtypes=[C.c_void_p,C.c_int,C.POINTER(Health),C.c_char_p,C.c_size_t]
        lib.dw4_property_number.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(C.c_int32)]
        lib.dw4_playerhealth_add.argtypes=[C.c_void_p,C.c_int,C.c_int,C.c_int32,C.c_int32,C.c_char_p,C.c_size_t]
        p=lib.dw4_playerrecords_open();f=lib.dw4_playerrecords_get(p,b'GETPLAYER',0)
        try:
            for hp,mp,mhp,mmp in itertools.product((-1,0,1,60,170,999),(-1,0,1,60,170,999),(1,170,999),(1,60,999)):
                for key,value in zip(('ISUSE','LEVEL','HP','MP','MHP','MMP'),(1,1,hp,mp,mhp,mmp)):assert not lib.dw4_property_set_number(f,key.encode(),value)
                out=Health();error=C.create_string_buffer(256);assert not lib.dw4_playerhealth_restore(p,0,C.byref(out),error,256)
                expected=w.restore(hp,mp,mhp,mmp);percent=[]
                if out.hp_publish:percent.append(int.from_bytes(C.c_float(out.hp_percent),'little'))
                percent.append(int.from_bytes(C.c_float(out.mp_percent),'little'))
                assert (out.hp,out.mp,out.hp_publish,percent)==expected,(hp,mp,mhp,mmp,out.hp,out.mp,out.hp_publish,percent,expected)
                total+=1
            additions=0
            for hp,mp,amount,absolute in itertools.product((0,1,60,170,999),(-1,0,1,60,999),(-999,-1,0,1,170,2147483647),(-1,0,170)):
                for key,value in zip(('HP','MP','MHP','MMP'),(hp,mp,170,60)):assert not lib.dw4_property_set_number(f,key.encode(),value)
                error=C.create_string_buffer(256)
                assert not lib.dw4_playerhealth_add(p,0,0,amount,absolute,error,256)
                assert not lib.dw4_playerhealth_add(p,0,1,amount,-1,error,256)
                actual=[]
                for key in (b'HP',b'MP'):
                    value=C.c_int32();assert not lib.dw4_property_number(f,key,C.byref(value));actual.append(value.value)
                expected=w.restore(hp,mp,170,60,amount,absolute)
                assert actual==list(expected[:2]),(hp,mp,amount,absolute,actual,expected)
                additions+=1
        finally:lib.dw4_playerrecords_close(p)
    print(f'player health: {total} clamp/dead-HP/percentage publications match original 3f9c80/3f9e20; property and meter/number sinks controlled')
    print(f'player health additions: {additions} additive/absolute/dead-HP/overflow clamps match retail; heal particle sink remains separate')
if __name__=='__main__':main()
