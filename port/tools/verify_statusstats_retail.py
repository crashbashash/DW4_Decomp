#!/usr/bin/env python3
"""STATUS UPDATE/preview traces and snapshots against original 3d60e0."""
from native_shared import build_shared
import argparse
import ctypes as C
from pathlib import Path
import random
import subprocess
import tempfile
from verify_statusctrl_retail import Retail, ROOT, BASE, NODE
FIELDS=['MHP','MMP','TSUYOSA','MAMORI','KASHIKOSA','SEISHIN','SUBAYASA','HONOOTEIKO','KOORITEIKO','KAMINARITEIKO','YAMITEIKO','HP','MP']
EXTRA=['LEVEL','DIGIMONNO','XDATA','BIT','EXP','NEXTEXP']
RAM,WORK,LIST,PROP=BASE+0x181000,BASE+0x181100,BASE+0x181200,BASE+0x182000
class Unicode(C.Structure):
    _fields_=[('codes',C.POINTER(C.c_uint16)),('count',C.c_size_t),('present',C.c_int)]
class Command(C.Structure):
    _fields_=[('op',C.c_int),('group',C.c_char_p),('font',C.c_char_p),('text',C.c_char_p),('unicode',Unicode),('color',C.c_float*3)]
class Snapshot(C.Structure):
    _fields_=[('valid',C.c_int),('player',C.c_int32),('value',C.c_int32*13)]
IO=C.CFUNCTYPE(C.c_int,C.c_void_p,C.POINTER(Command))
NAME=C.CFUNCTYPE(C.c_void_p,C.c_void_p,C.c_int32)
def bits(v):return int.from_bytes(C.c_float(v),'little')
class Stats(Retail):
    def call(self,e,a):
        a=[x&0xffffffff for x in a]
        if e==0x3bb730:return 0
        if e==0x38d4a0:return self.command
        if e==0x38f320:return self.player
        if e==0x38f800:return PROP
        if e==0x3a9580:
            assert a[1]==self.data['DIGIMONNO']&0xffffffff and self.string(a[2])=='NAME'
            return self.token('Species')
        if e==0x3a9220:return self.properties[self.string(a[1])]
        if e==0x3a9340:
            assert self.string(a[1])=='PLAYERNAME'
            return BASE+0x183000
        if e==0x129e60:
            assert self.string(a[1])=='%d'
            b=str(C.c_int32(a[2]).value).encode()+b'\0'
            for i,x in enumerate(b):self.w(a[0]+i,1,x)
            return len(b)-1
        if e==0x38e5d0:self.category=self.string(a[1]);self.args=[];return 0
        if e==0x38e5f0:
            assert self.string(a[1])=='DATABASE' and self.string(a[2])=='shinka' and self.string(a[4])=='GETDATABASE';return 0
        if e==0x38f830:self.args.append(self.string(a[1]));return 0
        if e==0x38f670:self.args.append(tuple(self.codes));return 0
        if e==0x38f4b0:self.args.append(tuple(self.read(a[1]+i*4,4) for i in range(3)));return 0
        if e==0x38f250:return 0
        if e==0x38e060:
            if self.category=='TEXTCTL':
                key=self.string(a[1]);op={'TEXTSET':0,'COLOR':2,'DEFAULTCOLOR':3}[key]
                payload=self.args[2] if len(self.args)>2 else None
                if isinstance(payload,tuple) and key=='TEXTSET':op=1
                self.events.append((op,*self.args[:2],payload))
            return 0
        return super().call(e,a)
    def run(self,command,player,data,codes,baseline=None):
        self.command=command;self.player=player;self.data=data;self.codes=codes;self.events=[];self.descend=set()
        self.w(NODE+20,4,BASE);self.w(RAM+44,4,WORK);self.w(WORK+8,4,LIST);self.list(LIST,baseline or [])
        self.properties={}
        for i,(key,val) in enumerate(data.items()):
            p=PROP+0x100+i*32;self.properties[key]=p;self.w(p+12,4,val)
        self.w(BASE+0x183000+12,4,BASE+0x183100);self.w(BASE+0x183100+16,4,BASE+0x183200)
        self.w(BASE+0x183200,4,BASE+0x183300);self.w(BASE+0x183300+4,4,1000)
        assert self.invoke(0x3d60e0,NODE,RAM,BASE+0x184000)==1
        return self.events,self.values(LIST)
def main():
    p=argparse.ArgumentParser();p.add_argument('--elf',type=Path,required=True);a=p.parse_args()
    if not a.elf.exists():print('STATUS stats retail: private ELF unavailable, skipped');return
    w=Stats(a.elf.read_bytes());rng=random.Random(20836);total=0
    with tempfile.TemporaryDirectory() as td:
        td=Path(td);stub=td/'stub.c'
        stub.write_text('#include <stdlib.h>\n'+''.join('void '+n+'(void){abort();}\n' for n in ['dw4_dialogue_set_unicode','dw4_scriptservices_call']))
        so=td/'stats.so';build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/statusstats.c'),str(ROOT/'src/playerrecords.c'),str(stub),'-lm','-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_playerrecords_open.restype=C.c_void_p
        lib.dw4_playerrecords_get.argtypes=[C.c_void_p,C.c_char_p,C.c_int32];lib.dw4_playerrecords_get.restype=C.c_void_p
        lib.dw4_property_set_number.argtypes=[C.c_void_p,C.c_char_p,C.c_int32]
        lib.dw4_property_set_unicode_objects.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(Unicode),C.c_size_t]
        lib.dw4_playerrecords_close.argtypes=[C.c_void_p]
        lib.dw4_statusstats_update.argtypes=[C.POINTER(Snapshot),C.c_void_p,C.c_int32,NAME,C.c_void_p,IO,C.c_void_p,C.c_char_p,C.c_size_t]
        lib.dw4_statusstats_preview.argtypes=[C.POINTER(Snapshot),C.c_void_p,C.c_int32,C.c_int,IO,C.c_void_p,C.c_char_p,C.c_size_t]
        species=C.create_string_buffer(b'Species')
        @NAME
        def lookup(u,id):return C.addressof(species)
        for player in range(4):
            for level in [-1,0,998,999,1000,2147483647]:
                for exp,next_exp in [(0,100),(100,0),(-2147483648,2147483647),(2147483647,-2147483648)]:
                    data={key:rng.randint(-2147483648,2147483647) for key in FIELDS+EXTRA}
                    data.update(LEVEL=level,EXP=exp,NEXTEXP=next_exp)
                    codes=[65,0x2192,0xfffe];array=(C.c_uint16*len(codes))(*codes)
                    obj=Unicode(array,len(codes),1);players=lib.dw4_playerrecords_open();f=lib.dw4_playerrecords_get(players,b'GETPLAYER',player)
                    for key,v in data.items():assert not lib.dw4_property_set_number(f,key.encode(),v)
                    assert not lib.dw4_property_set_unicode_objects(f,b'PLAYERNAME',C.byref(obj),1)
                    snap=Snapshot();error=C.create_string_buffer(256);events=[]
                    @IO
                    def io(u,ptr):
                        c=ptr.contents;payload=None
                        if c.op==0:payload=c.text.decode()
                        elif c.op==1:payload=tuple(c.unicode.codes[i] for i in range(c.unicode.count))
                        elif c.op==2:payload=tuple(bits(v) for v in c.color)
                        events.append((c.op,c.group.decode(),c.font.decode(),payload));return 0
                    expected,baseline=w.run(2,player,data,codes)
                    assert not lib.dw4_statusstats_update(C.byref(snap),players,player,lookup,None,io,None,error,256),error.value
                    assert events==expected,(events,expected)
                    assert list(snap.value)==[C.c_int32(v).value for v in baseline]
                    for i,key in enumerate(FIELDS[:11]):
                        data[key]=C.c_int32(data[key]+[-1,0,1][i%3]).value
                        assert not lib.dw4_property_set_number(f,key.encode(),data[key])
                    for key in ['HP','MP']:
                        data[key]=C.c_int32(data[key]+123).value
                        assert not lib.dw4_property_set_number(f,key.encode(),data[key])
                    for on in [1,0]:
                        events.clear();expected,_=w.run(4 if on else 5,player,data,codes,baseline)
                        assert not lib.dw4_statusstats_preview(C.byref(snap),players,player,on,io,None,error,256)
                        assert events==expected,(on,events,expected)
                        if not on:
                            lib.dw4_property_number.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(C.c_int32)]
                            for key,index in [('HP',11),('MP',12)]:
                                v=C.c_int32();assert not lib.dw4_property_number(f,key.encode(),C.byref(v))
                                retail=w.read(w.properties[key]+12,4)
                                assert v.value==C.c_int32(retail).value==snap.value[index]
                    lib.dw4_playerrecords_close(players);total+=1
    print(f'STATUS stats retail: {total} UPDATE snapshots and {total*2} preview traces/restorations match')
if __name__=='__main__':main()
