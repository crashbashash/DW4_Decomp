#!/usr/bin/env python3
"""Compare STATUS view initialization with private retail instructions."""
from native_shared import build_shared
import argparse
import ctypes as C
from pathlib import Path
import subprocess
import tempfile
from verify_statusctrl_retail import Retail, NODE, BASE, ROOT

class Command(C.Structure):
    _fields_=[('op',C.c_int),('group',C.c_char_p),('name',C.c_char_p),('key',C.c_char_p),('value',C.c_char_p),('slot',C.c_int32)]
IO=C.CFUNCTYPE(C.c_int,C.c_void_p,C.POINTER(Command))
MODEL,TRACK,TEXT,SCRIPT,SWITCH,REFRESH=range(6)
class Views(Retail):
    def step(self,pc,delay=False):
        # The shared scalar EE core truncates LQ to 64 bits. These initializers
        # copy authored 16-byte tables with LQ/SQ, so retain all four lanes here.
        w=self.read(pc,4)
        if w>>26==0x1e:
            rs,rt=(w>>21)&31,(w>>16)&31
            imm=C.c_int16(w&0xffff).value
            self.r[rt]=self.read((self.r[rs]+imm)&0xffffffff,16)
            self.r[0]=0;self.covered.add(pc);return pc+4
        return super().step(pc,delay)
    def call(self,e,a):
        a=[v&0xffffffff for v in a]
        if e==0x2eaf60:return a[1]
        if e==0x1ca620:
            p=self.read(a[1],4);self.list(a[0],self.values(a[0])+[p])
            if a[0]==BASE+0x181100:
                group=self.string(self.values(BASE+0x181000)[-1]);font=self.string(p)
                self.events.append((TRACK,group,font,None,None,0))
            return 0
        if e==0x3f5410:
            self.events.append((TEXT,self.string(a[1]),self.string(a[2]),self.string(a[4]),self.string(a[3]),0));return 0
        if e in (0x3f5f00,0x3f5c90):
            opening=self.string(a[3])
            if e==0x3f5c90:
                assert [self.read(a[5]+i*4,4) for i in range(3)]==[0xc3cd0000,0x43700000,0]
                opening+='/V<-410,240,0>'
            self.events.append((MODEL,None,self.string(a[1]),opening,self.string(a[4]),C.c_int32(a[2]).value));return 0
        if e==0x3f5920:self.events.append((SCRIPT,None,self.string(a[1]),None,None,C.c_int32(a[2]).value));return 0
        if e==0x38e5d0:self.category=self.string(a[1]);self.strings=[];return 0
        if e==0x38f830:self.strings.append(self.string(a[1]));return 0
        if e==0x129e60:
            data=(self.string(a[1])%C.c_int32(a[2]).value).encode()+b'\0'
            for i,b in enumerate(data):self.w(a[0]+i,1,b)
            return len(data)-1
        if e==0x38f250:return 0
        if e==0x38e060:
            key=self.string(a[1])
            if self.category=='TEXTCTL':self.events.append((8 if key=='ALIGN' else SWITCH,self.strings[0],self.strings[1],None,self.strings[2],0))
            if self.category=='SUBWND':self.events.append((REFRESH,None,None,None,None,self.player))
            return 0
        if e==0x38f800:return BASE+0x182000
        if e==0x3a9220:
            assert self.string(a[1])=='DIGIMONNO';self.w(BASE+0x182100+12,4,self.digimon);return BASE+0x182100
        if e==0x3f5f80:return 0
        return super().call(e,a)
    def setup(self,entry,player,variant,digimon,callno):
        self.events=[];self.player=player;self.digimon=digimon;self.w(NODE+80,4,0)
        for off,val in [(20,player),(44,callno if entry in (0x4265c0,0x423bf0,0x423f00,0x424070) else variant),(60,BASE+0x181000),(64,BASE+0x181100),(68,BASE+0x181200),(72,BASE+0x181300),(76,BASE+0x181400)]:self.w(NODE+off,4,val)
        for p in range(BASE+0x181000,BASE+0x181500,0x100):self.list(p,[])
        self.descend={0x425e60,0x425fb0,0x425430}
        self.invoke(entry,NODE);return self.events
    def folder_fonts(self,start,stop):
        # Original inline initialization only: preserve literal pointers and
        # font-table iteration, control the TEXT service at its call boundary.
        self.ee_reset();self.events=[];self.r[20]=NODE
        self.run_until(start,stop)
        return self.events

def main():
    p=argparse.ArgumentParser();p.add_argument('--elf',type=Path,required=True);a=p.parse_args()
    if not a.elf.exists():print('STATUS views retail: private ELF unavailable, skipped');return
    w=Views(a.elf.read_bytes());total=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'views.so'
        # Unused native owners still link against host implementations; this
        # comparator calls only the pure setup boundary.
        build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/statusview.c'),'-o',str(so)],check=True)
        # Resolve unused native owner symbols with a separate stub library.
        stub=Path(td)/'stubs.c';stub.write_text('#include <stdlib.h>\n'+''.join('void '+n+'(void){abort();}\n' for n in ('dw4_xdata_price','dw4_xdata_stat','dw4_scriptservices_call','dw4_scriptengine_text_event','dw4_scriptengine_error','dw4_statusselect_tick','dw4_property_number','dw4_playerrecords_get','dw4_menu_window_close','dw4_menu_window_open','dw4_menu_window_open_class','dw4_menu_window_data','dw4_menu_window_count','dw4_statusctrl_load','dw4_statusctrl_store','dw4_statusui_positioned')))
        stubso=Path(td)/'stubs.so';subprocess.run(['cc','-shared','-fPIC',str(stub),'-o',str(stubso)],check=True)
        stubs=C.CDLL(str(stubso),mode=C.RTLD_GLOBAL);lib=C.CDLL(str(so));lib.dw4_statusview_setup.argtypes=[C.c_int,C.c_int,C.c_int32,C.c_int32,C.c_int32,IO,C.c_void_p]
        for kind,entry in [(0,0x424230),(1,0x4242a0),(2,0x426100),(3,0x426140),(4,0x4265c0),(5,0x423760),(9,0x423bf0),(10,0x423f00),(11,0x424070),(14,0x43fe30),(15,0x4405c0)]:
            for player in range(4):
                for variant in ([0,1] if kind==1 else range(4) if kind==14 else range(1,10) if kind==15 else [0]):
                    for digimon in ([-1,*range(16),16] if kind==1 else [0]):
                        for callno in ([30,60,90] if kind==4 else [31,61,91] if kind==9 else [0,124,130] if kind==10 else [0]):
                            expected=w.setup(entry,player,variant,digimon,callno);events=[]
                            @IO
                            def io(u,ptr):
                                c=ptr.contents;events.append((c.op,*[(getattr(c,n).decode() if getattr(c,n) else None) for n in ('group','name','key','value')],c.slot));return 0
                            assert lib.dw4_statusview_setup(kind,variant,player,digimon,callno,io,None)==0
                            assert events==expected,(kind,player,variant,digimon,callno,next(((i,x,y) for i,(x,y) in enumerate(zip(events,expected)) if x!=y),None),len(events),len(expected))
                            total+=1
        # Original TXTgetCallNo reads the globally published signed call number.
        for callno in [-2147483648,-1,0,15,30,2147483647]:
            w.w(0x58a220,4,callno);assert C.c_int32(w.invoke(0x3747f0)&0xffffffff).value==callno
        names=[(TEXT,'STWINFONT14',f'font{i:03}', 'LEFT',' ',0) for i in range(12)]
        desc=[(TEXT,'STWINFONT29','font000','LEFT',' ',0)]
        key=names+[(TEXT,'STWINFONT23',f'font{i:03}','RIGHT',' ',0) for i in range(2)]+desc
        disk=names+[(TEXT,'STWINFONT15',f'font{i:03}','RIGHT',' ',0) for i in range(12)]+desc
        assert w.folder_fonts(0x41a64c,0x41a704)==key
        assert w.folder_fonts(0x41af04,0x41afac)==disk
        w.events=[];w.invoke(0x411750,NODE)
        prompt=(TEXT,'STWINFONT29','font100','LEFT',' ',0)
        equipment=[prompt]+[(TEXT,'STWINFONT10',f'font{i:03}','LEFT',' ',0) for i in range(2)]
        equipment += [(TEXT,'STWINFONT11',f'font{i if i<3 else 100+i-3:03}','LEFT',' ',0) for i in range(8)]+[prompt]
        assert w.events==equipment
        print(f'STATUS views retail: {total} title/selection initializations match service/resource traces; 6 TXTgetCallNo states, 40 inline Key/DISK and 12 equipment blank font service calls pass')
if __name__=='__main__':main()
