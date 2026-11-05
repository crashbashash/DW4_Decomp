#!/usr/bin/env python3
"""Compare SELECTCTRL update state and model/sound commands with 39cbf0.

Input sampling and MODELCTRL completion are controlled leaves. Execute the real
retail state machine, including its one-tick terminal state and 16-update lock.
"""
import argparse
import ctypes as C
import itertools
from pathlib import Path
import subprocess
import tempfile
from verify_scriptservices_retail import World, ROOT, BASE

OWNER, RAM, INFO, ONE, WORK, PAD, FLAGS = [BASE+0x190000+i*0x100 for i in range(7)]
class Select(C.Structure):
    _fields_=[(k,C.c_int) for k in ('active','state','sub','delay','latch','selected','count','vertical','cancel')]+[
        ('position',C.c_float*3),('enabled',C.POINTER(C.c_uint8)),('sequence',C.c_char*32)]
IO=C.CFUNCTYPE(C.c_int,C.c_void_p,C.c_int,C.c_char_p,C.c_char_p)
class Retail(World):
    def __init__(self,image):
        super().__init__(image);self.descend=set()
        self.w(OWNER+20,4,BASE+0x180000);self.w(RAM+12,4,INFO);self.w(INFO+8,4,self.token('cursor'))
        self.w(RAM+40,4,BASE+0x180100);self.w(RAM+8,4,2);self.w(ONE+28,4,WORK)
        self.w(WORK+4,4,1000)
    def string(self,p):
        p&=0xffffffff
        if not p:return None
        chars=[]
        while self.read(p,1):chars.append(self.read(p,1));p+=1
        return bytes(chars).decode('ascii')
    def call(self,e,a):
        a=[v&0xffffffff for v in a]
        if e==0x3022c0:return ONE
        if e==0x39b810:return PAD
        if e==0x38d860:return 0
        if e==0x38f830:self.value=self.string(a[1]);return 0
        if e==0x38f4b0:return 0
        if e==0x38f220:return self.query
        if e==0x38e060:
            key=self.string(a[1]);
            if key=='ISSEQNAME':return 0
            self.events.append(('SOUND','ERROR') if key=='PLAY' else (key,self.value));return 0
        if e==0x38e5f0:
            seq=self.string(a[4]);self.events.append((seq,seq));return 0
        if e==0x38e5d0:return 0
        if e==0x129e60:
            text=(self.string(a[1])%(C.c_int32(a[2]).value)).encode()+b'\0'
            for i,b in enumerate(text):self.w(a[0]+i,1,b)
            return len(text)-1
        return super().call(e,a)
    def tick(self,s,analog,held,pressed,query):
        self.query=query;self.events=[]
        for off,k in [(20,'active'),(24,'state'),(28,'sub'),(32,'delay'),(36,'latch')]:self.w(RAM+off,1 if k=='active' else 4,getattr(s,k))
        for off,k in [(16,'vertical'),(20,'count'),(24,'selected')]:self.w(ONE+off,1 if k=='vertical' else 4,getattr(s,k))
        self.w(ONE+28,4,WORK);self.w(WORK+20,4,s.count);self.w(WORK+24,1,s.cancel)
        self.w(WORK+28,4,self.token(s.sequence.decode()))
        self.w(WORK+32,4,FLAGS if s.enabled else 0)
        if s.enabled:self.list(FLAGS,[s.enabled[i] for i in range(s.count)],1)
        for off,v in [(36,analog),(68,held),(72,pressed)]:self.w(PAD+off,4,v)
        self.invoke(0x39cbf0,OWNER,RAM)
        values=[C.c_int32(self.read(p+off,size)).value for p,off,size in [(RAM,20,1),(RAM,24,4),(RAM,28,4),(RAM,32,4),(RAM,36,4),(ONE,24,4)]]
        return values,self.events
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT.parent.parent / 'local/extracted/SLUS_208.36')
    w=Retail(p.parse_args().elf.read_bytes())
    with tempfile.TemporaryDirectory() as tmp:
        so=Path(tmp)/'select.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/selectctrl.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_selectctrl_tick.argtypes=[C.POINTER(Select),C.c_uint32,C.c_uint32,C.c_uint32,IO,C.c_void_p]
        total=0
        flags=(C.c_uint8*3)(1,0,1)
        cases=itertools.product([(0,0),(0,1),(1,0),(1,1),(1,2),(2,0),(2,1),(3,0),(10,0),(10,1)],
            [0,1],[0,1,2],[0,1],[0,1],[0,16],[0,1],[0,1,4,8,2],[0,0x2000,0x4000,0x6000])
        for (state,sub),vertical,selected,cancel,latch,delay,query,analog,pressed in cases:
            s=Select(1,state,sub,delay,latch,selected,3,vertical,cancel,(C.c_float*3)(0,0,0),flags,b'SQ_LINESL00')
            expected,events=w.tick(s,analog,0,pressed,query);got_events=[]
            @IO
            def io(user,q,key,value):
                if q:return query
                got_events.append((key.decode(),value.decode()));return 0
            assert lib.dw4_selectctrl_tick(C.byref(s),analog,0,pressed,io,None)==0
            got=[s.active,s.state,s.sub,s.delay,s.latch,s.selected]
            assert got==expected,(state,sub,vertical,selected,cancel,latch,delay,query,analog,pressed,got,expected)
            assert got_events==events,(got_events,events)
            total+=1
        print(f'SELECTCTRL retail: {total} input/disabled-row/cancel/open/close/FO2TOP/terminal states and command traces passed')
if __name__=='__main__':main()
