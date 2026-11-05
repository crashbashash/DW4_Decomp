#!/usr/bin/env python3
"""Retail SendBit digit edits, with selector/number/sound leaves controlled."""
from native_shared import build_shared
import ctypes as C
import itertools
import subprocess
import tempfile
from pathlib import Path
from verify_statusctrl_retail import Retail as BaseRetail, State, NODE, CHILDREN, BASE, ROOT
from verify_statuspage_retail import Input, PAD

class Retail(BaseRetail):
    def call(self,e,a):
        if e==0x129e60:
            text=self.string(a[1])%a[2]
            for i,b in enumerate(text.encode()+b'\0'):self.w(a[0]+i,1,b)
            return len(text)
        if e==0x39b810:return PAD
        if e==0x4402e0:self.effects.append(('number',a[1]&0xffffffff,a[2]&0xffffffff));return 0
        if e==0x38e060 and self.category=='SOUND':self.effects.append(('sound',self.name,self.string(a[1])));return 0
        return super().call(e,a)
    def edit(self,amount,limit,selected,pad,ready,previous=None):
        self.events=[];self.effects=[];self.query=ready;self.category=self.name=self.value=None
        for off,val in ((28,1),(32,0),(36,2),(40,selected if previous is None else previous),(48,selected),(80,1),(84,amount),(88,limit)):
            self.w(NODE+off,4,val)
        self.list(CHILDREN,[BASE+0x200000])
        for off,val in ((28,pad.horizontal),(32,0),(72,pad.digital),(76,0)):self.w(PAD+off,4,val)
        self.invoke(0x41de40,NODE)
        return self.read(NODE+84,4),self.read(NODE+40,4),self.effects

def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('STATUS currency: private ELF unavailable, skipped');return
    w=Retail(elf.read_bytes());total=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'bit.so';build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/statusbit.c'),'-o',str(so)],check=True)
        names=[line.split()[-1] for line in subprocess.check_output(['nm','-D','-u',str(so)],text=True).splitlines() if line.split()[-1].startswith('dw4_')]
        stub=Path(td)/'stubs.c';stub.write_text('#include <stdlib.h>\n'+''.join('void '+name+'(void){abort();}\n' for name in names))
        stubso=Path(td)/'stubs.so';subprocess.run(['cc','-shared','-fPIC',str(stub),'-o',str(stubso)],check=True)
        stubs=C.CDLL(str(stubso),mode=C.RTLD_GLOBAL);lib=C.CDLL(str(so))
        lib.dw4_statusbit_adjust.argtypes=[C.POINTER(C.c_int32),C.c_int32,C.c_int,C.POINTER(Input)]
        for limit in (0,1,9,99,9999999):
            for amount,selected,horizontal,digital,ready in itertools.product(sorted({0,limit,max(limit-1,0)}),range(7),(0,1,4,5),(0,0x10,0x40,0x50),range(2)):
                pad=Input(horizontal,0,digital);expected,_,_=w.edit(amount,limit,selected,pad,ready);current=C.c_int32(amount)
                if ready:assert lib.dw4_statusbit_adjust(C.byref(current),limit,selected,C.byref(pad))>=0
                assert current.value==expected,(amount,limit,selected,horizontal,digital,ready,current.value,expected)
                total+=1
        lib.dw4_statusbit_edit.argtypes=[C.POINTER(C.c_int32),C.c_int32,C.c_int,C.POINTER(C.c_int32),C.c_int,C.POINTER(Input)]
        trace_total=0
        for limit,selected,previous,horizontal,digital,ready in itertools.product((0,1,99,9999999),range(7),(-1,0,6),(0,1,4,5),(0,0x10,0x40,0x50),range(2)):
            amount=limit;pad=Input(horizontal,0,digital);expected_amount,expected_previous,expected_effects=w.edit(amount,limit,selected,pad,ready,previous)
            current=C.c_int32(amount);last=C.c_int32(previous);effects=lib.dw4_statusbit_edit(C.byref(current),limit,selected,C.byref(last),ready,C.byref(pad));assert effects>=0
            actual=[]
            if effects&1:actual.append(('number',current.value,7-selected))
            if effects&2:actual.append(('sound','CURSOR_MOVE','PLAY'))
            assert (current.value,last.value&0xffffffff,actual)==(expected_amount,expected_previous,expected_effects),(limit,selected,previous,horizontal,digital,ready,actual,expected_effects)
            trace_total+=1
            lib.dw4_statusbit_close_step.argtypes=[C.POINTER(State),C.c_int]
        close_total=0
        for active,state,sub,delay,latch,finished in itertools.product(range(2),(2,3),(0,1,7),(0,2,4),(-1,0,6),range(2)):
            s=State(active,state,sub,delay,latch,2,1,3);w.events=[];w.query=finished;w.category=w.name=w.value=None
            for offset,val in zip((24,28,32,36,40,48,80,84),(active,state,sub,delay,latch,2,1,3)):w.w(NODE+offset,1 if offset==24 else 4,val)
            w.invoke(0x41de40,NODE)
            expected=[C.c_int32(w.read(NODE+offset,1 if offset==24 else 4)).value for offset in (24,28,32,36,40)]
            assert not lib.dw4_statusbit_close_step(C.byref(s),finished)
            assert [s.active,s.state,s.sub,s.delay,s.latch]==expected,(active,state,sub,delay,latch,finished,expected)
            close_total+=1
        print(f'STATUS currency: {close_total} close/wait metadata states match original41de40; model/font/child-close and completion leaves controlled')
    print(f'STATUS currency: {trace_total} edit redraw/sound/place-width traces match original41de40; effects drive the production owner')
    print(f'STATUS currency: {total} amount/digit/input/cap/readiness edits match original 41de40; number/sound/selector leaves controlled')
if __name__=='__main__':main()
