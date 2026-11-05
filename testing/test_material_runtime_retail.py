#!/usr/bin/env python3
"""Whole material update/message comparisons against the private retail ELF.

Controlled leaves: allocator/list append/resize, messenger selection and matrices,
box-membership queries, formatting and Lua callbacks. Production controller logic,
reference counts, activation writes and buffer swaps execute original instructions.
"""
import argparse
import ctypes as C
from pathlib import Path
import subprocess
import sys
import tempfile
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'port/tools'))
from verify_scriptservices_retail import World
SELF,RAM,INFO,WORK,RUN,PAIR,FIRST,SECOND,MATERIALS=range(0x1800000,0x1800900,0x100)
NEW_WORK,NEW_RUN,NEW_PAIR,NEW_FIRST,NEW_SECOND=range(0x1810000,0x1810500,0x100)
STACK=0x1fff000
READ=C.CFUNCTYPE(C.c_uint32,C.c_void_p,C.c_uint32,C.c_uint)
WRITE=C.CFUNCTYPE(None,C.c_void_p,C.c_uint32,C.c_uint,C.c_uint32)
CALL=C.CFUNCTYPE(C.c_uint32,C.c_void_p,C.c_uint32,C.POINTER(C.c_uint32))
class Api(C.Structure):
    _fields_=[('user',C.c_void_p),('read',READ),('write',WRITE),('call',CALL)]
NARGS={0x301000:1,0x2f88e0:1,0x359480:1,0x2caa70:1,0x2d6790:3,0x301e30:2,
       0x2ff820:1,0x38e670:3,0x38f5a0:1,0x38f320:2,0x38f630:3,0x190a30:2,
       0x38b080:6,0x389ff0:3,0x35a6b0:0,0x38d4a0:3,0x1dc870:1,0x1dc8d0:1,
       0x236f80:2,0x38d560:5,0x18b630:2}
class Material(World):
    def __init__(self,image):
        super().__init__(image)
        self.descend={0x38b1f0,0x38bdf0,0x38b080}; self.events=[]; self.allocated=0
        self.players=[]; self.hits={}; self.request=None; self.command=0
        self.real_box=False
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==0x18b630 and self.real_box:
            return self.box_function(C.byref(self.box_api),v[0],v[1])
        n=NARGS.get(e)
        if e==0x129e60:n=3 if v[1]==0x50ed78 else 2
        assert n is not None,f'unknown material leaf {e:#x}'
        self.events.append((e,*v[:n]))
        if e==0x301000:return 0x1818000
        if e==0x2f88e0:return 0x1819000
        if e==0x359480:
            self.w(NEW_WORK+4,4,1); self.w(NEW_WORK+8,4,NEW_RUN);self.w(NEW_WORK+12,4,NEW_PAIR)
            self.list(NEW_RUN,[]);self.list(NEW_PAIR,[]);return NEW_WORK
        if e==0x2caa70:
            p=(NEW_FIRST,NEW_SECOND)[self.allocated];self.allocated+=1
            self.list(p,[]);self.w(p+4,4,1);self.w(p+12,4,2);return p
        if e==0x2d6790:self.w(v[0]+8,4,v[1]);self.w(v[0]+12,4,v[1]);return 0
        if e==0x301e30:
            self.list(v[0],self.values(v[0])+[v[1]])
            self.w(v[1]+4,4,self.read(v[1]+4,4)+1);return 0
        if e==0x2ff820:return 0
        if e==0x38e670:return 0
        if e==0x38f5a0:return len(self.players)
        if e==0x38f320:return self.players[v[1]]
        if e==0x38f630:
            self.current_player=self.players[v[2]]
            for i in range(16):self.w(v[0]+i*4,4,0x3f800000 if i%5==0 else 0)
            return 0
        if e==0x190a30:
            for i in range(3):self.w(v[1]+i*4,4,self.read(v[0]+48+i*4,4))
            return 0
        if e==0x38b080:
            for i in self.hits.get(v[3],[]):
                p=self.read(v[1]+16,4)+i*4;self.w(p,4,self.read(p,4)|(1<<(v[3]&31)))
            return 0
        if e==0x129e60:
            self.w(v[0],4,0x41414141) # controlled formatting output
            return 0
        if e==0x389ff0:
            if self.request is not None:
                index,value=self.request;self.w(SELF+48,4,index);self.w(SELF+52,1,value)
            return 0
        if e==0x35a6b0:return 0x181a000
        if e==0x38d4a0:return self.command
        if e in (0x1dc870,0x1dc8d0):return 0
        if e==0x236f80:return 0x1835000
        if e==0x38d560:return 0
        if e==0x18b630:
            if self.geometry_by_hits:
                index=(v[0]-0x1849000)//0x100
                return 2 if index in self.hits.get(self.current_player,[]) else 1
            return self.geometry_result
        raise AssertionError(e)
    def setup(self,count=3,state=1,run=1,old=None,enabled=None):
        self.geometry_by_hits=True
        self.events=[];self.allocated=0;self.w(RAM+20,1,run);self.w(RAM+24,4,state)
        self.w(RAM+12,4,INFO);self.w(RAM+44,4,WORK)
        self.w(SELF+20,4,0x181b000);self.w(SELF+36,4,0x181c000)
        self.w(INFO+32,4,MATERIALS);self.w(INFO+36,4,0x181d000);self.w(INFO+28,4,0x181e000)
        self.w(WORK+4,4,1);self.w(WORK+8,4,RUN);self.w(WORK+12,4,PAIR)
        self.list(MATERIALS,[0x1820000+i*0x100 for i in range(max(0,count))]);self.w(MATERIALS+8,4,count)
        tree=0x181d000
        self.list(tree,[0x1850000+i*0x100 for i in range(max(0,count))])
        for i in range(max(0,count)):
            self.w(0x1820000+i*0x100+8,4,0 if i==0 else 0x50ed60)
            self.w(0x1820000+i*0x100+12,4,0x1849000+i*0x100)
            node=0x1850000+i*0x100
            self.w(node+8,4,0);self.w(node+12,4,0x3f800000);self.w(node+16,4,i)
            self.w(node+24,4,node+0x40);self.list(node+0x40,[])
        self.list(RUN,enabled if enabled is not None else [1]*max(0,count),1)
        self.list(PAIR,[FIRST,SECOND]);self.list(FIRST,[0xdeadbeef]*max(0,count))
        self.list(SECOND,old if old is not None else [0]*max(0,count))
        self.w(FIRST+4,4,2);self.w(SECOND+4,4,2)
        self.w(SELF+56,4,FIRST);self.w(SELF+60,4,SECOND)
        for i in range(4):self.w(SELF+32+i,1,0xff)
        self.w(SELF+40,4,0xfeed);self.w(SELF+48,4,0xabcd);self.w(SELF+52,1,0x7f)
        self.w(0x58a1e0,4,0x182f000)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=p.parse_args()
    image=args.elf.read_bytes();retail=Material(image);native=Material(image);errors=[]
    @CALL
    def call(_,e,values):
        try:return native.call(e,list(values[:8]))
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    count=0
    with tempfile.TemporaryDirectory(prefix='dw4-material-runtime-') as td:
        so=Path(td)/'runtime.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/material-runtime.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_material_update.argtypes=[C.POINTER(Api),C.c_uint32,C.c_uint32,C.c_uint32]
        lib.dw4_material_update.restype=None
        lib.dw4_material_message.argtypes=[C.POINTER(Api),C.c_uint32,C.c_uint32,C.c_uint32];lib.dw4_material_message.restype=C.c_int
        lib.dw4_material_initialize.argtypes=[C.POINTER(Api),C.c_uint32];lib.dw4_material_initialize.restype=None
        lib.dw4_material_register.argtypes=[C.POINTER(Api),C.c_uint32,C.c_uint32];lib.dw4_material_register.restype=None
        lib.dw4_material_accumulate.argtypes=[C.POINTER(Api)]+[C.c_uint32]*6;lib.dw4_material_accumulate.restype=None
        lib.dw4_material_box_contains.argtypes=[C.POINTER(Api),C.c_uint32,C.c_uint32]
        lib.dw4_material_box_contains.restype=C.c_int
        native.box_function=lib.dw4_material_box_contains;native.box_api=api
        def compare(message=False,entry=None,values=()):
            nonlocal count
            native.mem=retail.mem.copy();native.events=[];retail.events=[];native.allocated=retail.allocated=0
            for name in ('players','hits','request','command','geometry_by_hits'):setattr(native,name,getattr(retail,name))
            if entry is not None:
                retail.descend.add(entry);retail.invoke(entry,SELF,*values)
                if entry==0x38af70:lib.dw4_material_initialize(C.byref(api),SELF)
                elif entry==0x38b050:lib.dw4_material_register(C.byref(api),SELF,*values)
                elif entry==0x38b080:
                    native.geometry_result=retail.geometry_result
                    lib.dw4_material_accumulate(C.byref(api),SELF,*values)
            elif message:
                expected=retail.invoke(0x38bdf0,SELF,RAM,0x1830000)
                actual=lib.dw4_material_message(C.byref(api),SELF,RAM,0x1830000)
                assert actual==expected,(actual,expected)
            else:
                retail.invoke(0x38b1f0,SELF,RAM)
                lib.dw4_material_update(C.byref(api),SELF,RAM,STACK-320)
            assert not errors,errors
            # Only compiler stack/scratch storage is excluded. Every runtime
            # byte and meaningful service-call argument/order is compared.
            wanted={p:v for p,v in retail.mem.items() if p<STACK-0x1000}
            got={p:v for p,v in native.mem.items() if p<STACK-0x1000}
            assert wanted==got,[(hex(p),wanted.get(p),got.get(p)) for p in wanted.keys()|got.keys() if wanted.get(p)!=got.get(p)][:12]
            assert native.events==retail.events,(native.events,retail.events)
            count+=1
        for state in (0,2,0xffffffff):
            for size in (-1,0,1,2,8,9,17):
                retail.setup(size,state);compare()
        for run in (0,2,255):
            retail.setup(run=run);retail.players=[];retail.hits={};compare()
        for current in range(16):
            for previous in range(16):
                for debug in (0,1,2):
                    retail.setup(old=[previous,previous^15,previous]);retail.w(SELF+64,1,debug)
                    retail.players=[i for i in range(4) if current&(1<<i)]
                    retail.hits={i:[0,2] for i in retail.players};retail.request=(1,0) if current&1 else None
                    compare()
        for request in ((-1,0),(0,255),(2,2),(3,0),(-2,0),(1,256)):
            retail.setup(old=[15,15,15]);retail.players=[];retail.hits={};retail.request=request;compare()
        # Persistent state across real buffer swaps, including out-of-order and
        # duplicate selector results. Extra old publisher references are released.
        for seed in range(16):
            retail.setup();retail.request=None
            for tick in range(4):
                mask=(seed+tick*3)&15
                retail.players=[i for i in reversed(range(4)) if mask&(1<<i)]
                if retail.players:retail.players.append(retail.players[0])
                retail.hits={i:[0,1,2] for i in retail.players};compare()
        for flag in (0,1,2):
            retail.setup(9,0);retail.w(0x554c14,1,flag);compare()
        retail.w(0x554c14,1,0)
        for size in (0,1,8,9,17):
            retail.setup(size);retail.players=[0,3];retail.hits={0:list(range(size)),3:list(range(size))};retail.request=None
            compare();retail.players=[];compare()
        for cmd in (0,1,2,3,4,5,6,0xffffffff):
            retail.setup();retail.command=cmd;retail.w(0x1830000+20,4,0x1831000);compare(True)
        for refs in (1,2,0x800001,0x800002,0):
            for published in (0,1,2,3):
                retail.setup();retail.w(FIRST+4,4,refs);retail.w(SECOND+4,4,refs)
                retail.w(SELF+56,4,FIRST if published&1 else 0);retail.w(SELF+60,4,SECOND if published&2 else 0)
                compare(entry=0x38af70)
        for selector in (0,1,3,0xffffffff):
            retail.setup();compare(entry=0x38b050,values=(selector,))
        # Parent/child X gates are inclusive. Child membership is independent of
        # parent's shape hit; negative/overflow mask indices still call geometry.
        tree,node,children,child,point=range(0x1840000,0x1840500,0x100)
        for x in (0xbf800000,0,0x80000000,1,0x3f800000,0x40000000,0x7f800000):
            for index in (-1,0,1,3,-2):
                for result in (0,1,2,3):
                    retail.setup();retail.geometry_result=result;retail.geometry_by_hits=False
                    retail.list(tree,[node]);retail.list(children,[child]);retail.list(child+0x40,[])
                    for p in (node,child):
                        retail.w(p+8,4,0);retail.w(p+12,4,0x3f800000)
                    retail.w(node+16,4,index);retail.w(node+24,4,children)
                    retail.w(child+16,4,1);retail.w(child+24,4,child+0x40)
                    for i in range(3):retail.w(0x1820000+i*0x100+12,4,0x1849000+i*0x100)
                    retail.w(point,4,x)
                    # Out-of-range material access itself is not guarded in retail.
                    compare(entry=0x38b080,values=(FIRST,tree,31,point,MATERIALS))
        # Original box leaf: no callee leaves, every combination of three-axis
        # boundary values, signed zeros, denormals and exponent-255 encodings.
        import itertools
        box,point=0x1860000,0x1860100
        retail.descend.add(0x18b630)
        samples=(0xc0000000,0xbf800000,0xbf7fffff,0x80000000,0,1,0x3f7fffff,0x3f800000,0x40000000,0x7f800000)
        for inverted in (False,True):
            for axis in range(3):
                retail.w(box+8+axis*4,4,0x3f800000 if inverted else 0xbf800000)
                retail.w(box+20+axis*4,4,0xbf800000 if inverted else 0x3f800000)
            for values in itertools.product(samples,repeat=3):
                for axis,value in enumerate(values):retail.w(point+axis*4,4,value)
                native.mem=retail.mem.copy();before=retail.mem.copy()
                expected=retail.invoke(0x18b630,box,point)
                actual=lib.dw4_material_box_contains(C.byref(api),box,point)
                assert actual==expected,(values,inverted,actual,expected)
                assert before==retail.mem and before==native.mem
                count+=1
        # Compose the recovered box leaf with full update/search execution.
        # The retail interpreter descends into 18b630; the native API delegates
        # to actual recovered C, rather than returning a controlled box result.
        native.real_box=True
        for previous in (0,1,7,15):
            retail.setup(old=[previous]*3);retail.players=[0,2];retail.request=None
            for i in range(3):
                box=0x1849000+i*0x100
                for axis in range(3):
                    retail.w(box+8+axis*4,4,0xbf800000)
                    retail.w(box+20+axis*4,4,0x3f800000)
            compare();retail.players=[];compare()
    print(f'material runtime retail: {count} whole-function return, RAM and ordered-call cases; 2000 direct box cases and 8 integrated real-box updates; remaining service leaves controlled')
if __name__=='__main__':main()
