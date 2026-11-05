#!/usr/bin/env python3
"""Retail 4207a0 detail update, with constructors/resources/properties controlled.

Original instructions decide discard/give refusals, all outer update boundaries,
retained DEVICE closure/wait, recipient selection, capacity and command ordering.
Sort helpers and record list operations are independently verified host leaves.
"""
from native_shared import build_shared
import ctypes as C
import itertools
import subprocess
import tempfile
from pathlib import Path
from verify_statusdiskctrl_retail import Retail as DiskRetail, LISTS, ITEMS, FOLDERS, PROPERTY, NEW
from verify_statusctrl_retail import State, NODE, CHILDREN, OFF, BASE, ROOT

DEVICE=BASE+0x260000
class Control(C.Structure):
    _fields_=[('window',State),('recipient',C.c_int32),('retained',C.c_int32)]
IO=C.CFUNCTYPE(C.c_int,C.c_void_p,C.POINTER(Control),C.c_int,C.c_int32)
INIT,COUNT,CLOSE,FINISHED,DEFAULT_COLOR,DISCARD_CHECK,POPUP,CONFIRM,REMOVE,SORT,CHECK,DEVICE_CLOSE,DEVICE_FINISHED,DEVICE_RELEASE,CURSOR_CLOSE,CLEAR_TEXT,GIVE_SETUP,RECIPIENT,RECIPIENT_COUNT,TRANSFER,CURSOR_OPEN=range(21)

class Retail(DiskRetail):
    def call(self,e,a):
        a=[v&0xffffffff for v in a]
        if e in (0x3b51b0,0x3b4f50,0x3b5370):
            p=NEW+self.created*0x1000;self.created+=1;self.w(p+4,4,1000)
            for off in (60,64,68,72,76):
                target=NEW+0x100000+(p-NEW)+off*32
                self.w(p+off,4,target);self.list(target,[])
            return p
        if e==0x3c90f0:
            p=NEW+0x80000+self.allocated*0x100;self.allocated+=1;self.list(p,[]);self.w(p+4,4,1000);return p
        if e==0x3a9340:
            key=self.string(a[1]);player=(a[0]-FOLDERS)//0x100
            if key=='DEVICEFOLDER':target=LISTS+player*0x100
            elif key=='PLAYERNAME':target=LISTS+0x1500
            else:
                assert key in ('POWERSOCKET','MAINSLOT','SUBSLOT','POWERPOCKET','MAINPOCKET'),key
                target=LISTS+0x1600
            p=PROPERTY+0x1000;self.w(p+12,4,target);return p
        if e==0x447c60:return self.allowed
        if e==0x447cb0:return self.token('device name')
        if e==0x447d00:
            for i in range(3):self.w(a[0]+4*i,4,0x3f666666)
            return 0
        if e==0x3f6090:
            self.effects.append(('finished','device' if a[0]==DEVICE else 'self'))
            return self.finished
        if e in (0x3f5f80,0x3f5a40,0x3f6350):
            self.effects.append(({0x3f5f80:'models',0x3f5a40:'text',0x3f6350:'children'}[e],));return 0
        if e==0x3f5f40:self.effects.append(('cursor','SQ_CLOSE'));return 0
        if e==0x3e9260:
            rows=self.values(a[0]);self.effects.append(('remove',)) if self.sub==1 else None
            return rows[a[1]]
        if e==0x406f20:
            rows=self.values(a[0]);rows.pop(a[1]);self.list(a[0],rows);return 0
        if e in (0x423000,0x422c00):
            if not self.sorted:self.effects.append(('sort',));self.sorted=True
            return 0
        if e==0x38e060:
            if self.category=='TEXTCTL' and self.string(a[1])=='DEFAULTCOLOR':self.effects.append(('color',))
            return 0
        return super().call(e,a)
    def tick_detail(self,c,count,joined,kind,equipped,allowed,capacity,finished):
        self.created=self.allocated=0;self.effects=[];self.joined=joined;self.finished=finished
        self.player=0;self.category=None;self.strings=[];self.allowed=allowed;self.sub=c.window.sub;self.sorted=False
        for off,(key,_) in zip(OFF,State._fields_):self.w(NODE+off,1 if off==24 else 4,getattr(c.window,key))
        for off,value in ((20,0),(44,1),(84,1),(88,DEVICE if c.retained else 0),(92,c.recipient)):
            self.w(NODE+off,4,value)
        self.w(DEVICE+4,4,1000)
        for off in (28,32,36,40):self.w(DEVICE+off,4,7)
        self.list(CHILDREN,[NEW+0x10000+i*0x100 for i in range(count)])
        for off in (60,64,68,72,76):self.w(NODE+off,4,BASE+0x240000+off*0x100);self.list(BASE+0x240000+off*0x100,[])
        for player in range(4):
            rows=[ITEMS+player*0x1000+i*32 for i in range(3 if player==0 else capacity)]
            self.list(LISTS+player*0x100,rows)
            for i,p in enumerate(rows):
                self.w(p+4,4,1000);self.w(p+8,4,kind);self.w(p+12,4,i);self.w(p+16,4,equipped if i==1 and player==0 else 0)
        self.list(LISTS+0x1500,[]);self.list(LISTS+0x1600,[])
        recipients=[] if c.window.state in (0,1) and c.window.sub==3 and c.window.delay==0 else list(range(1,joined+1))
        self.w(NODE+96,4,LISTS+0x800);self.list(LISTS+0x800,recipients)
        self.w(NODE+100,4,LISTS+0x900);self.list(LISTS+0x900,[capacity]*joined if c.window.delay!=1 else [])
        self.invoke(0x4207a0,NODE)
        values=[C.c_int32(self.read(NODE+off,1 if off==24 else 4)).value for off in OFF[:-1]]
        values += [C.c_int32(self.read(NODE+92,4)).value,int(bool(self.read(NODE+88,4)))]
        device=[self.read(DEVICE+off,4) for off in (28,32,36,40)]
        orders=[[(p-ITEMS)//32 for p in self.values(LISTS+player*0x100)] for player in range(4)]
        return values,device,orders

def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('STATUS detail: private ELF unavailable, skipped');return
    w=Retail(elf.read_bytes());total=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'detail.so'
        build_shared(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-I'+str(ROOT/'include'),str(ROOT/'src/statusdetailctrl.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_statusdetailctrl_tick.argtypes=[C.POINTER(Control),IO,C.c_void_p]
        cases=[(*row,1,0,1,3,3) for row in itertools.product(range(5),range(5),range(12),(-1,0,1,2),(0,1),(0,1),(0,1))]
        cases += [(1,1,0,0,0,0,1,kind,equipped,allowed,3,3) for kind,equipped,allowed in itertools.product((0,1,2,3),(0,1,256),(0,1,256))]
        cases += [(1,3,0,0,0,0,retained,1,equipped,allowed,capacity,joined) for equipped,allowed,capacity,joined,retained in itertools.product((0,1,256),(0,1,256),(0,35,36),range(4),range(2))]
        cases += [(1,3,3,selection,0,0,0,1,0,1,capacity,3) for selection,capacity in itertools.product(range(3),(0,35,36))]
        for state,sub,delay,selection,count,finished,retained,kind,equipped,allowed,capacity,joined in cases:
            c=Control(State(1,state,sub,delay,2,selection,1,0),0,retained)
            expected,device,orders=w.tick_detail(c,count,joined,kind,equipped,allowed,capacity,finished)
            native_count=count;native_device=[7]*4;native_orders=[[i for i in range(3)]]+[[128*player+i for i in range(capacity)] for player in range(1,4)];effects=[]
            @IO
            def io(user,p,op,value):
                nonlocal native_count
                current=p.contents
                if op==COUNT:return native_count
                if op==FINISHED:effects.append(('finished','self'));return finished
                if op==DEVICE_FINISHED:effects.append(('finished','device' if current.retained else 'self'));return finished
                if op in (INIT,POPUP,CONFIRM,RECIPIENT):native_count+=1
                if op==INIT:effects.append(('script',67))
                if op==CLOSE:effects.extend([('models',),('text',),('children',)])
                if op==DEFAULT_COLOR:effects.append(('color',))
                if op==DISCARD_CHECK:return 144 if equipped&255 else 145 if kind==0 and not allowed&255 else 78
                if op==POPUP:effects.append(('script',value))
                if op==REMOVE:effects.append(('remove',));native_orders[0].pop(1)
                if op==SORT:effects.append(('sort',))
                if op==CHECK:return 146 if equipped&255 else 147 if not allowed&255 else 148 if not joined else 0
                if op==DEVICE_CLOSE:native_device[:]=[2,0,0,0]
                if op==CURSOR_CLOSE:effects.append(('cursor','SQ_CLOSE'))
                if op==CLEAR_TEXT:effects.append(('text',))
                if op==GIVE_SETUP:effects.append(('script',73))
                if op==RECIPIENT_COUNT:return capacity
                if op==TRANSFER:native_orders[current.recipient+1].append(native_orders[0].pop(1))
                return 0
            assert not lib.dw4_statusdetailctrl_tick(C.byref(c),io,None)
            actual=[getattr(c.window,n) for n,_ in State._fields_[:-1]]+[c.recipient,c.retained]
            assert actual==expected,(state,sub,delay,selection,count,finished,retained,actual,expected)
            assert native_device==device,(state,sub,delay,selection,retained,native_device,device)
            assert native_orders==orders,(state,sub,delay,selection,native_orders,orders)
            assert effects==w.effects,(state,sub,delay,selection,count,finished,effects,w.effects)
            total+=1
    print(f'STATUS detail: {total} outer states, refusal/capacity effects, retained DEVICE waits and record transfers match original 4207a0; property/resource/selector/sort leaves controlled')
if __name__=='__main__':main()
