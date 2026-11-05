#!/usr/bin/env python3
"""Retail CtrlBit/SendBit outer states and effects, with explicit host leaves."""
from native_shared import build_shared
import ctypes as C
import itertools
import subprocess
import tempfile
from pathlib import Path
from verify_statusviews_retail import Views
from verify_statusctrl_retail import State, NODE, CHILDREN, OFF, ROOT, BASE
from verify_statuspage_retail import Input, PAD

class Wrapper(C.Structure):
    _fields_=[('window',State),('recipients',C.c_int32)]
class Send(C.Structure):
    _fields_=[('window',State)]+[(n,C.c_int32) for n in ('amount','limit','recipient')]
WIO=C.CFUNCTYPE(C.c_int,C.c_void_p,C.POINTER(Wrapper),C.c_int,C.c_int32)
SIO=C.CFUNCTYPE(C.c_int,C.c_void_p,C.POINTER(Send),C.c_int,C.c_int32)
COLLECT,SEND_CHILD,WPOPUP,WCOUNT,WCLOSE,WFINISHED=range(6)
INIT,HIDE,RESET,COUNT,CURSOR_OPEN,NUMBER_SELECTOR,NUMBER,LIMIT,EDIT,CURSOR_CLOSE,HIDE_PROMPT,TRANSFER,POPUP,ACK_HIDE,REFRESH,CLOSE,FINISHED=range(17)
LIST=BASE+0x190000
PROPS=BASE+0x1a0000
FOLDERS=BASE+0x1b0000
NEW=BASE+0x250000
class Retail(Views):
    def call(self,e,a):
        a=[v&0xffffffff for v in a]
        if e in (0x3b9560,0x3b4f50,0x3b51b0,0x3b45d0):
            p=NEW+self.created*0x1000;self.created+=1;self.w(p+4,4,1000)
            for off in (60,64,68,72,76):
                target=NEW+0x100000+(p-NEW)+off*32;self.w(p+off,4,target);self.list(target,[])
            return p
        if e==0x3f63c0:return 0
        if e==0x1ca620:self.list(a[0],self.values(a[0])+[self.read(a[1],4)]);return 0
        if e==0x38e670:self.category=self.string(a[1]);return 0
        if e==0x38f250:
            if self.category=='GAMERAM':self.player=C.c_int32(a[1]).value
            return 0
        if e==0x38f800:return FOLDERS+self.player*0x100
        if e==0x3a9220:
            key=self.string(a[1]);assert key in ('BIT','NINZU');return PROPS+(a[0]-FOLDERS) if key=='BIT' else PROPS+0x800
        if e==0x3a9280:
            self.w(PROPS+0x900+12,1,(self.mask>>self.player)&1);return PROPS+0x900
        if e==0x3a9340:
            assert self.string(a[1])=='PLAYERNAME';self.w(PROPS+0xa00+12,4,LIST+0x1000);return PROPS+0xa00
        if e==0x3f6090:self.effects.append(('finished',));return self.finished
        if e in (0x3f5f80,0x3f5a40,0x3f6350):self.effects.append(({0x3f5f80:'models',0x3f5a40:'text',0x3f6350:'children'}[e],));return 0
        if e==0x3f5920:self.effects.append(('script',a[2]));return 0
        if e==0x3f5f00:self.effects.append(('panel',self.string(a[3])));return 0
        if e==0x3f5c90:self.effects.append(('open',self.string(a[3])));return 0
        if e in (0x3f5410,0x38f670):return 0
        if e==0x129e60:
            text=self.string(a[1])%C.c_int32(a[2]).value
            for i,b in enumerate(text.encode()+b'\0'):self.w(a[0]+i,1,b)
            return len(text)
        if e==0x4402e0:self.effects.append(('number',a[1],a[2]));return 0
        if e==0x39b810:return PAD
        if e==0x38e5d0:self.category=self.string(a[1]);self.strings=[];return 0
        if e==0x38f830:self.strings.append(self.string(a[1]));return 0
        if e==0x38e5f0:
            if self.string(a[1])=='MODELCTRL':self.effects.append(('cursor',self.string(a[4])))
            return 0
        if e==0x38f220:return self.ready
        if e==0x38e060:
            key=self.string(a[1])
            if self.category=='TEXTCTL':
                if self.strings[0]=='STWINFONT28' or self.strings[:2] in (['STWINFONT29','font000'],['STWINFONT29','font100']):
                    self.effects.append(('font',*self.strings,key))
            if self.category=='SUBWND':self.effects.append(('update',))
            if self.category=='SOUND':self.effects.append(('sound','CURSOR_MOVE',key))
            return 0
        return super().call(e,a)
    def tick(self,entry,c,count,mask,finished,ready,pad,sender,receiver,owner=0):
        self.created=0;self.effects=[];self.mask=mask;self.finished=finished;self.ready=ready;self.player=0;self.category=None;self.strings=[]
        for off,(key,_) in zip(OFF,State._fields_):self.w(NODE+off,1 if off==24 else 4,getattr(c.window,key))
        recipients=[i for i in range(1,4) if mask>>i&1]
        for i in range(4):self.w(PROPS+i*0x100+12,4,sender if i==0 else receiver)
        self.list(LIST+0x1000,[0]);self.w(NODE+20,4,owner)
        if entry==0x41d810:
            self.w(NODE+84,4,LIST);self.list(LIST,[] if c.window.state==0 else list(range(1,c.recipients+1)))
        else:
            for off,v in ((84,c.amount),(88,c.limit),(92,LIST),(96,c.recipient)):self.w(NODE+off,4,v)
            self.list(LIST,recipients)
        self.list(CHILDREN,[NEW+0x10000+i*0x100 for i in range(count)])
        for off in (60,64,68,72,76):self.w(NODE+off,4,BASE+0x240000+off*0x100);self.list(BASE+0x240000+off*0x100,[])
        for off,v in ((28,pad.horizontal),(32,0),(72,pad.digital),(76,0)):self.w(PAD+off,4,v)
        self.invoke(entry,NODE)
        values=[C.c_int32(self.read(NODE+off,1 if off==24 else 4)).value for off in OFF[:-1]]
        if entry==0x41d810:values.append(self.read(LIST+8,4))
        else:values += [C.c_int32(self.read(NODE+off,4)).value for off in (84,88,96)]
        balances=[self.read(PROPS+i*0x100+12,4) for i in range(4)]
        return values,balances

def font(group,name,value,key):return ('font',group,name,value,key)
def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('STATUS currency outer: private ELF unavailable, skipped');return
    w=Retail(elf.read_bytes());wrappers=sends=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'bit.so';build_shared(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-I'+str(ROOT/'include'),str(ROOT/'src/statusbitctrl.c'),str(ROOT/'src/statusbit.c'),'-o',str(so)],check=True)
        names=[line.split()[-1] for line in subprocess.check_output(['nm','-D','-u',str(so)],text=True).splitlines() if line.split()[-1].startswith('dw4_')]
        stub=Path(td)/'stubs.c';stub.write_text('#include <stdlib.h>\n'+''.join('void '+name+'(void){abort();}\n' for name in names))
        stubso=Path(td)/'stubs.so';subprocess.run(['cc','-shared','-fPIC',str(stub),'-o',str(stubso)],check=True)
        stubs=C.CDLL(str(stubso),mode=C.RTLD_GLOBAL);lib=C.CDLL(str(so))
        lib.dw4_statusbitctrl_tick.argtypes=[C.POINTER(Wrapper),WIO,C.c_void_p]
        lib.dw4_statussendbitctrl_tick.argtypes=[C.POINTER(Send),SIO,C.c_void_p]
        lib.dw4_statusbit_edit.argtypes=[C.POINTER(C.c_int32),C.c_int32,C.c_int,C.POINTER(C.c_int32),C.c_int,C.POINTER(Input)]
        for state,sub,delay,count,finished,mask,owner in itertools.product(range(5),range(3),range(3),(0,1),(0,1),range(16),range(4)):
            c=Wrapper(State(1,state,sub,delay,2,0,1,0),2);expected,_=w.tick(0x41d810,c,count,mask,finished,0,Input(),100,10,owner);effects=[];n=count
            @WIO
            def io(u,p,op,value):
                nonlocal n
                if op==COLLECT:return sum((mask>>i)&1 for i in range(4) if i!=owner)
                if op in (SEND_CHILD,WPOPUP):n+=1
                if op==WPOPUP:effects.append(('script',value))
                if op==WCOUNT:return n
                if op==WCLOSE:effects.extend([('models',),('text',),('children',)])
                if op==WFINISHED:effects.append(('finished',));return finished
                return 0
            assert not lib.dw4_statusbitctrl_tick(C.byref(c),io,None)
            actual=[getattr(c.window,n) for n,_ in State._fields_[:-1]]+[c.recipients]
            assert actual==expected and effects==w.effects,(state,sub,delay,count,finished,mask,actual,expected,effects,w.effects)
            wrappers+=1
        for state,delay,selection,count,finished,ready,amount in itertools.product(range(5),range(7),(-1,0,1,2,3,4,5,6),(0,1),(0,1),(0,1,256),(0,1,99)):
            if state==1 and delay==1 and selection>2:continue
            c=Send(State(1,state,0,delay,selection,selection,1,0),amount,99,1);pad=Input(1,0,0)
            expected,balances=w.tick(0x41de40,c,count,15,finished,ready,pad,1000,9999900);effects=[];n=count;actual_balances=[1000]+[9999900]*3
            @SIO
            def io(u,p,op,value):
                nonlocal n
                current=p.contents;s=current.window
                if op==COUNT:return n
                if op==FINISHED:effects.append(('finished',));return finished
                if op in (RESET,NUMBER_SELECTOR,POPUP):n+=1
                if op==INIT:effects.extend([('panel','SQ_3BITOPEN'),('script',76)])
                if op==HIDE:effects.extend(font('STWINFONT28',f'font{i:03}','DISPOFF','SWITCH') for i in range(7))
                if op==RESET:effects.extend([font('STWINFONT28','font000','CENTER','ALIGN'),font('STWINFONT28','font000','0','TEXTSET'),font('STWINFONT28','font000','DISPON','SWITCH')])
                if op==CURSOR_OPEN:effects.append(('open',f'SQ_OPEN{current.recipient:02}'))
                if op==NUMBER:effects.append(('number',current.amount,value))
                if op==LIMIT:return min(1000,9999999-9999900)
                if op==EDIT:
                    a=C.c_int32(current.amount);last=C.c_int32(s.latch)
                    flags=lib.dw4_statusbit_edit(C.byref(a),current.limit,s.selection,C.byref(last),ready&255,C.byref(pad));assert flags>=0
                    p.contents.amount=a.value;p.contents.window.latch=last.value
                    if flags&1:effects.append(('number',a.value,7-s.selection))
                    if flags&2:effects.append(('sound','CURSOR_MOVE','PLAY'))
                if op==CURSOR_CLOSE:effects.append(('cursor','SQ_CLOSE'))
                if op==HIDE_PROMPT:effects.append(font('STWINFONT29','font100','DISPOFF','SWITCH'))
                if op==TRANSFER:actual_balances[0]-=current.amount;actual_balances[current.recipient+1]+=current.amount
                if op==POPUP:effects.append(('script',value))
                if op==ACK_HIDE:effects.append(font('STWINFONT29','font000','DISPOFF','SWITCH'))
                if op==REFRESH:effects.append(('update',))
                if op==CLOSE:effects.extend([('models',),('text',),('children',)])
                return 0
            assert not lib.dw4_statussendbitctrl_tick(C.byref(c),io,None)
            actual=[getattr(c.window,n) for n,_ in State._fields_[:-1]]+[c.amount,c.limit,c.recipient]
            assert actual==expected,(state,delay,selection,count,finished,ready,amount,actual,expected)
            assert actual_balances==balances,(state,delay,selection,amount,actual_balances,balances)
            assert effects==w.effects,(state,delay,selection,count,ready,amount,effects,w.effects)
            sends+=1
    print(f'STATUS currency outer: {wrappers} CtrlBit and {sends} SendBit states/effect traces/balance writes match original 41d810/41de40; constructors/property/resource/selector leaves controlled')
if __name__=='__main__':main()
