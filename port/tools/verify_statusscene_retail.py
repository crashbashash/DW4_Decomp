#!/usr/bin/env python3
"""Retail STATUS freeze, manager entry/exit order and joined-player refresh."""
from native_shared import build_shared
import argparse
import ctypes as C
from pathlib import Path
import subprocess
import tempfile
from verify_subwindow_retail import Retail as Commands, State, OWNER, RAM, WINDOW
from verify_scriptservices_retail import BASE, ROOT

class Command(C.Structure):
    _fields_=[('op',C.c_int)]+[(n,C.c_char_p) for n in ('category','name','key','value')]+[(n,C.c_int32) for n in ('player','hp','mp','max_hp','max_mp')]
IO=C.CFUNCTYPE(C.c_int,C.c_void_p,C.POINTER(Command),C.c_void_p,C.c_size_t)
class Scene(C.Structure):
    _fields_=[('players',C.c_void_p),('io',IO),('user',C.c_void_p),('phase',C.c_int),('failed',C.c_int)]
class Retail(Commands):
    def string(self,p):
        p &= 0xffffffff
        if not p:return None
        chars=[]
        while self.read(p,1):chars.append(self.read(p,1));p+=1
        return bytes(chars).decode('ascii')
    def call(self,e,a):
        a=[v&0xffffffff for v in a]
        if e==0x38e670:self.events.append((0,self.string(a[1]),None,self.string(a[2]),None));return 0
        if e==0x38d470:self.events.append((1,None,None,None,str(a[1])));return 0
        if e==0x38e5d0:self.cat=self.string(a[1]);self.parts=[];return 0
        if e==0x38f830:self.parts.append(self.string(a[1]));return 0
        if e==0x38f250:self.parts.append(a[1]);return 0
        if e==0x38e060:
            key=self.string(a[1])
            if self.cat=='GAMERAM':
                self.player=self.parts[0]
                if key!='GETPLAYER':self.events.append((0,self.cat,None,key,(self.player,0)))
            elif self.cat=='LAYERCTL':self.events.append((0,self.cat,self.parts[0],key,self.parts[1]))
            else:self.events.append((0,self.cat,None,key,self.parts[0]));return 0
            return 0
        if e==0x38f800:return BASE+0x300000+self.player*0x100
        if e==0x3a9220:
            key=self.string(a[1]);return self.props[(self.player,key)]
        if e==0x3a9280:
            p=BASE+0x301000;self.w(p+12,1,self.join[self.player]);return p
        if e==0x3f6490:self.w(WINDOW+24,1,self.root_active);return 0
        if e in (0x3d8740,0x3f63c0,0x301000,0x2f88e0):return 0
        if e==0x3bb1d0:return WINDOW
        return super().call(e,a)
    def manager(self,state,join,active):
        self.events=[];self.join=join;self.root_active=active;self.descend={0x3d60e0}
        self.w(OWNER+32,4,WINDOW);self.w(OWNER+40,4,0);self.w(WINDOW+4,4,1000)
        for off,v in [(20,1),(24,state),(28,0),(32,0),(36,0)]:self.w(RAM+off,4,v)
        self.invoke(0x3d59b0,OWNER,RAM);return self.events

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--elf',type=Path,default=ROOT.parent.parent/'local/extracted/SLUS_208.36');args=ap.parse_args()
    if not args.elf.exists():print('STATUS scene retail: private ELF unavailable, skipped');return
    w=Retail(args.elf.read_bytes());total=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'scene.so';build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/statusscene.c'),str(ROOT/'src/playerrecords.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_playerrecords_open.restype=C.c_void_p;lib.dw4_playerrecords_get.argtypes=[C.c_void_p,C.c_char_p,C.c_int32];lib.dw4_playerrecords_get.restype=C.c_void_p
        lib.dw4_property_set_number.argtypes=[C.c_void_p,C.c_char_p,C.c_int32];lib.dw4_property_number.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(C.c_int32)];lib.dw4_playerrecords_close.argtypes=[C.c_void_p]
        for name in ('freeze','enter','restore'):getattr(lib,'dw4_statusscene_'+name).argtypes=[C.POINTER(Scene),C.c_void_p,C.c_size_t]
        for case in range(80):
            mask=case%16;boundary=case//16
            bit=[-2147483648,9999999,10000000,2147483647,-1][boundary]
            xdata=[-2147483648,9999,10000,2147483647,-1][boundary]
            p=lib.dw4_playerrecords_open();events=[]
            @IO
            def io(u,ptr,e,n):
                c=ptr.contents;vals=tuple(getattr(c,k).decode() if getattr(c,k) else None for k in ('category','name','key','value'))
                if c.op==2:
                    events.extend([(0,'GAMERAM',None,'ADDHP',(c.player,0)),(0,'GAMERAM',None,'ADDMP',(c.player,0))])
                else:events.append((c.op,*vals))
                return 0
            for i in range(4):
                f=lib.dw4_playerrecords_get(p,b'GETPLAYER',i)
                for k,v in [('ISUSE',257 if mask>>i&1 else 256),('BIT',bit),('XDATA',xdata),('HP',30),('MP',40),('MHP',50),('MMP',60)]:assert lib.dw4_property_set_number(f,k.encode(),v)==0
            s=Scene(p,io,None,0,0);error=C.create_string_buffer(256)
            original=State(0,0,0,0,0,0,0);w.command(0,original,None);expected=w.events
            assert lib.dw4_statusscene_freeze(C.byref(s),error,256)==0
            assert events==expected,(events,expected)
            events.clear();w.props={}
            for i in range(4):
                for j,(key,value) in enumerate((('BIT',bit),('XDATA',xdata),('LEVEL',1))):
                    ptr=BASE+0x310000+i*0x100+j*0x20;w.props[(i,key)]=ptr;w.w(ptr+12,4,value)
            w.w(RAM+44,4,BASE+0x320000);w.w(OWNER+40,4,0);w.join=[mask>>i&1 for i in range(4)]
            w.invoke(0x3d8740,OWNER,RAM)
            expected=w.manager(0,[mask>>i&1 for i in range(4)],1)
            assert lib.dw4_statusscene_enter(C.byref(s),error,256)==0
            assert events==expected,(events,expected)
            for i in range(4):
                folder=lib.dw4_playerrecords_get(p,b'GETPLAYER',i)
                for key in ('BIT','XDATA'):
                    value=C.c_int32();assert lib.dw4_property_number(folder,key.encode(),C.byref(value))==0
                    original=C.c_int32(w.read(w.props[(i,key)]+12,4)).value
                    assert value.value==original,(mask,boundary,i,key,value.value,original)
            events.clear();expected=w.manager(1,[mask>>i&1 for i in range(4)],0)
            assert lib.dw4_statusscene_restore(C.byref(s),error,256)==0
            assert events==expected,(events,expected)
            lib.dw4_playerrecords_close(p);total+=1
        print(f'STATUS scene: {total} boundary cases across 16 joined-player masks match retail caps, GENERATE freeze and manager entry/restoration traces')
if __name__=='__main__':main()
