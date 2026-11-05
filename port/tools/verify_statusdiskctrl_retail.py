#!/usr/bin/env python3
"""Execute every retail DISK outer state with controlled resource/record leaves.

The original 41acf0 instructions decide all update/fallthrough boundaries and
write scalar state, selected rows, limits and disk quantities. Constructors,
property lookup, strings, fonts and model programs are controlled leaves.
"""
from native_shared import build_shared
import ctypes as C
import itertools
import subprocess
import tempfile
from pathlib import Path
from verify_statusviews_retail import Views
from verify_statusctrl_retail import State, NODE, CHILDREN, OFF, BASE, ROOT

class Control(C.Structure):
    _fields_=[('window',State)]+[(n,C.c_int32) for n in ('selected','recipient','limit')]
IO=C.CFUNCTYPE(C.c_int,C.c_void_p,C.POINTER(Control),C.c_int,C.c_int32)
INIT,MAIN,REFRESH,ACTION,ACTION_TEXT,REORDER,SWAP,CURSOR_CLOSE,CHECK,POPUP,RETIRE_MAIN,GIVE_SETUP,RECIPIENT,RECIPIENT_QUANTITY,CURSOR_OPEN,QUANTITY,QUANTITY_TEXT,TRANSFER,ACK_CLEAR,RETIRE_GIVE,CLOSE,FINISHED,COUNT=range(23)
LISTS=BASE+0x190000
ITEMS=BASE+0x1a0000
FOLDERS=BASE+0x1b0000
PROPERTY=BASE+0x1c0000
NEW=BASE+0x250000

class Retail(Views):
    def call(self,e,a):
        a=[v&0xffffffff for v in a]
        if e in (0x3b51b0,0x3b4f50,0x3b4410):
            p=NEW+self.created*0x200;self.created+=1;self.w(p+4,4,1000)
            for off in (60,64,68,72,76):self.w(p+off,4,p+0x100+off)
            for off in (60,64,68,72,76):self.list(p+0x100+off,[])
            return p
        if e==0x3f63c0:return 0
        if e==0x2cb0d0:
            p=NEW+0x80000;self.list(p,[],1);self.w(p+4,4,1000);return p
        if e==0x1ca620:
            self.list(a[0],self.values(a[0])+[self.read(a[1],4)]);return 0
        if e==0x38f250:self.player=C.c_int32(a[1]).value;return 0
        if e==0x38f800:return FOLDERS+max(self.player,0)*0x100
        if e==0x3a9340:
            assert self.string(a[1]) in ('DISKFOLDER','PLAYERNAME')
            p=PROPERTY+(a[0]-FOLDERS)
            self.w(p+12,4,LISTS+(a[0]-FOLDERS));return p
        if e==0x3a9280:
            assert self.string(a[1])=='ISUSE'
            self.w(PROPERTY+0x800+12,1,int(self.player==0 or self.player<=self.joined));return PROPERTY+0x800
        if e==0x236f80:return 0
        if e==0x447cb0:return self.token('disk name')
        if e in (0x41d2c0,0x41d3b0,0x41d3f0,0x41d490,0x3e90d0,0x3e9110):return 0
        if e==0x3e9160:
            rows=self.values(a[0]);rows[a[1]]=a[2];self.list(a[0],rows);return 0
        if e==0x41d510:self.effects.append(('refresh',a[1]));return 0
        if e in (0x3f5f80,0x3f5a40,0x3f6350):return 0
        if e==0x3f6090:return self.finished
        if e==0x38e5f0:
            self.effects.append(('cursor',self.string(a[4])));return 0
        if e in (0x3f5f00,0x3f5c90):return 0
        if e in (0x3f5410,0x3f56d0):return 0
        if e==0x3f5920:self.effects.append(('script',a[2]));return 0
        if e==0x38e5d0:self.category=self.string(a[1]);self.strings=[];return 0
        if e==0x38f830:self.strings.append(self.string(a[1]));return 0
        if e==0x38e060:
            if self.category=='TEXTCTL' and self.string(a[1])=='TEXTSET' and self.strings[:2]==['STWINFONT38','font001']:
                self.effects.append(('quantity',int(self.strings[-1])))
            return 0
        return super().call(e,a)
    def tick_disk(self,c,count,joined,source,target,finished):
        self.created=0;self.effects=[];self.joined=joined;self.finished=finished;self.player=0;self.category=None;self.strings=[]
        for off,(key,_) in zip(OFF,State._fields_):self.w(NODE+off,1 if off==24 else 4,getattr(c.window,key))
        for off,value in ((20,0),(84,c.selected),(92,c.recipient),(100,ITEMS+32*c.selected),(104,c.limit)):
            self.w(NODE+off,4,value)
        self.list(CHILDREN,[NEW+0x10000+i*0x100 for i in range(count)])
        for off in (60,64,68,72,76):self.w(NODE+off,4,BASE+0x240000+off*0x100);self.list(BASE+0x240000+off*0x100,[])
        for player in range(4):
            rows=[ITEMS+player*0x1000+i*32 for i in range(12)]
            self.list(LISTS+player*0x100,rows)
            for i,p in enumerate(rows):
                self.w(p+4,4,1000);self.w(p+12,4,i);self.w(p+20,4,source if player==0 else target)
        self.w(NODE+88,4,LISTS+0x800);self.list(LISTS+0x800,list(range(1,joined+1)))
        self.w(NODE+96,4,LISTS+0x900);self.list(LISTS+0x900,[ITEMS+i*0x1000+c.selected*32 for i in range(1,joined+1)])
        self.invoke(0x41acf0,NODE)
        values=[C.c_int32(self.read(NODE+off,1 if off==24 else 4)).value for off in OFF[:-1]]
        values += [C.c_int32(self.read(NODE+off,4)).value for off in (84,92,104)]
        quantities=[self.read(ITEMS+c.selected*32+20,4),self.read(ITEMS+(c.recipient+1)*0x1000+c.selected*32+20,4)]
        order=[(p-ITEMS)//32 for p in self.values(LISTS)]
        return values,quantities,order

def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('STATUS DISK: private ELF unavailable, skipped');return
    w=Retail(elf.read_bytes());total=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'disk.so'
        build_shared(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-I'+str(ROOT/'include'),str(ROOT/'src/statusdiskctrl.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_statusdiskctrl_tick.argtypes=[C.POINTER(Control),IO,C.c_void_p]
        cases=[(*row,5,6,3,1,3) for row in itertools.product(range(5),range(8),range(13),(-1,0,1,2),(0,1),(0,1))]
        cases += [(1,5,0,0,0,0,source,0,joined,0,1) for source,joined in itertools.product((0,1,9),range(4))]
        cases += [(1,6,4,0,0,0,source,target,1,0,1) for source,target in itertools.product((1,5,9),(0,8,9))]
        for source,target in itertools.product(range(1,10),range(9)):
            limit=min(source,9-target)
            cases += [(1,6,delay,selection,count,0,source,target,1,0,limit)
                      for delay,selection,count in itertools.product((5,6,7),range(limit),(0,1))]
        for state,sub,delay,selection,count,finished,source,target,joined,recipient,limit in cases:
            c=Control(State(1,state,sub,delay,2,selection,1,0),1,recipient,limit)
            expected,quantities,order=w.tick_disk(c,count,joined,source,target,finished)
            native_count=count;native_quantities=[source,target];native_order=list(range(12));effects=[]
            @IO
            def io(user,p,op,value):
                nonlocal native_count
                current=p.contents
                if op==COUNT:return native_count
                if op==FINISHED:return finished
                if op in (MAIN,ACTION,REORDER,RECIPIENT,QUANTITY,POPUP):native_count+=1
                if op==CHECK:return 141 if source<1 else 142 if not joined else 0
                if op==RECIPIENT_QUANTITY:return target
                if op==QUANTITY:return min(source,9-target)
                if op==REFRESH:effects.append(('refresh',value))
                if op==ACTION_TEXT:effects.append(('script',value))
                if op in (CURSOR_CLOSE,RETIRE_MAIN):effects.append(('cursor','SQ_CLOSE'))
                if op==POPUP:effects.append(('script',value))
                if op==INIT:effects.append(('script',72))
                if op==MAIN:effects.append(('script',43))
                if op==GIVE_SETUP:effects.append(('script',74))
                if op==QUANTITY_TEXT:effects.append(('quantity',value))
                if op==TRANSFER:
                    amount=current.limit-current.window.selection;native_quantities[0]-=amount;native_quantities[1]+=amount
                if op==SWAP:
                    a,b=current.selected,current.window.selection;native_order[a],native_order[b]=native_order[b],native_order[a]
                return 0
            assert not lib.dw4_statusdiskctrl_tick(C.byref(c),io,None)
            actual=[getattr(c.window,n) for n,_ in State._fields_[:-1]]+[c.selected,c.recipient,c.limit]
            assert actual==expected,(state,sub,delay,selection,count,finished,actual,expected)
            assert native_quantities==quantities,(state,sub,delay,selection,count,finished,native_quantities,quantities)
            assert native_order==order,(state,sub,delay,selection,count,finished,native_order,order)
            # Main row text/model/setup operations have independent asset tests;
            # compare outer script, cursor-close, quantity and refresh effects.
            assert effects==w.effects,(state,sub,delay,selection,count,finished,effects,w.effects)
            total+=1
    print(f'STATUS DISK: {total} outer states, effect traces, identity orders and quantity writes match original 41acf0; resource/property/selector leaves controlled')
if __name__=='__main__':main()
