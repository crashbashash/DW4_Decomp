#!/usr/bin/env python3
"""Original AABox transforms/intersections and3908e0 hit-body projection.
Allocation/list/context lookup are controlled leaves; geometry runs original code.
"""
import ctypes as C
import random,struct,subprocess,tempfile
from pathlib import Path
from verify_scriptservices_retail import World,ROOT,BASE
BOX,MATRIX,CENTRE,BODY,RAM,INFO,HIT,LOOKUP,BOXES,MINUS,PLUS,OUT=range(BASE+0x600000,BASE+0x60c000,0x1000)
def bits(x):return struct.unpack('<I',struct.pack('<f',x))[0]
PROBE,PROBE_RAM,PROBE_INFO,PROBE_MGR,PROBE_CTX,PROBE_NODE,PROBE_WORK=range(BASE+0x610000,BASE+0x617000,0x1000)
class Retail(World):
    probe_active=False
    def call(self,e,a):
        a=[x&0xffffffff for x in a]
        if e==0x301000:return 1
        if e==0x3022c0:return PROBE_CTX if self.probe_active else HIT
        if self.probe_active:
            if e==0x38e5d0:assert a[1]==0x50f430;return 0
            if e==0x38f670:self.probe_box=a[1];return 0
            if e in (0x38f250,0x38f5b0,0x38f830,0x38f0e0):return 0
            if e==0x38e060:assert a[1]==0x50f450;self.probe_result=self.output(self.probe_box+8,6);return 0
            if e==0x38f0f0:return 0
        if e==0x18a660:self.w(OUT+0x100+4,4,1);return OUT+0x100
        if e==0x301e30:
            self.list(a[0],self.values(a[0])+[a[1]]);self.w(a[1]+4,4,self.read(a[1]+4,4)+1);return 0
        if e==0x2ff820:return 0
        raise AssertionError('unexpected hit geometry leaf %#x'%e)
    def put(self,p,values):
        for i,v in enumerate(values):self.w(p+4*i,4,bits(v))
    def output(self,p,n):return struct.pack('<%dI'%n,*[self.read(p+4*i,4) for i in range(n)])
    def body(self,box,matrix):
        self.w(0x554c14,1,1);self.w(BODY+8,1,1);self.w(BODY+16,8,0xffffffffffffffff)
        self.w(BODY+32,4,MINUS);self.w(BODY+36,4,PLUS);self.w(BODY+40,4,OUT)
        for p in (MINUS,PLUS,OUT):self.list(p,[])
        self.w(RAM+12,4,INFO);self.w(INFO+20,4,INFO+0x100);self.w(LOOKUP+20,4,HIT)
        self.w(HIT+20,4,BOXES);self.list(BOXES,[BOX]);self.put(BOX+8,box);self.put(MATRIX,matrix)
        self.descend={0x18ac80,0x18b930,0x18b990,0x192fc0}
        self.invoke(0x3908e0,BODY,RAM,MATRIX,1)
        assert self.values(OUT)==[OUT+0x100]
        return self.output(OUT+0x108,6)
    def probe(self,matrix):
        self.probe_active=True;self.probe_result=None
        self.w(0x554c14,1,1);self.w(PROBE_RAM+8,4,0);self.w(PROBE_RAM+12,4,PROBE_INFO)
        self.w(PROBE_RAM+16,4,PROBE_MGR);self.w(PROBE_RAM+40,4,PROBE_CTX)
        self.w(PROBE_INFO+8,4,self.token('p_dorumon'));self.w(PROBE_MGR+20,4,PROBE_MGR+0x100)
        self.w(PROBE_MGR+40,1,0);self.w(PROBE_CTX+16,4,PROBE_NODE);self.w(PROBE_CTX+20,4,PROBE_WORK)
        self.w(PROBE_WORK+48,4,0);self.w(PROBE_WORK+220,4,0);self.put(PROBE_NODE+32,matrix)
        self.w(PROBE+20,4,60000);self.w(PROBE+24,4,1);self.put(PROBE+32,[0,4,7,3,3,3])
        self.descend={0x18ac80,0x18b930,0x18b990,0x192fc0}
        assert self.invoke(0x3993e0,PROBE,PROBE_RAM)==1
        self.probe_active=False;assert self.probe_result is not None;return self.probe_result
def main():
    w=Retail((ROOT.parent.parent/'local/extracted/SLUS_208.36').read_bytes());rng=random.Random(3993);total=0
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'box.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',
            '-I'+str(ROOT/'include'),'-I'+str(ROOT/'recovered/frontend'),str(ROOT/'src/hitbox.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));array=C.c_float*6;matrix_type=C.c_float*16;vector=C.c_float*3
        for name in ('dw4_hitbox_transform','dw4_hitbox_center','dw4_hitbox_intersects'):getattr(lib,name).argtypes=[C.POINTER(C.c_float),C.POINTER(C.c_float)]
        lib.dw4_hitbox_fixed_world.argtypes=[C.POINTER(C.c_float)]*3
        lib.dw4_hitbox_talk_probe.argtypes=[C.POINTER(C.c_float)]*2
        for case in range(160):
            lo=[rng.uniform(-30,30) for _ in range(3)];hi=[x+rng.uniform(0,30) for x in lo];box=lo+hi
            m=[rng.uniform(-2,2) for _ in range(16)];m[12:15]=[rng.uniform(-600,600) for _ in range(3)]
            m[3]=m[7]=m[11]=0;m[15]=(1,2,-1,0,.00000001)[case%5]
            if case%17==0:box[3]=box[0]-1
            original=array(*box);native=array(*box);matrix=matrix_type(*m);w.put(BOX+8,original);w.put(MATRIX,matrix)
            w.descend={0x192fc0};w.invoke(0x18ac80,BOX,MATRIX);lib.dw4_hitbox_transform(native,matrix)
            assert bytes(native)==w.output(BOX+8,6),('transform',case,list(native),list(struct.unpack('<6f',w.output(BOX+8,6))))
            total+=1
            out=vector();w.descend=set();w.invoke(0x18b990,BOX,CENTRE);lib.dw4_hitbox_center(native,out)
            assert bytes(out)==w.output(CENTRE,3);total+=1
            other=array(*[rng.uniform(-100,100) for _ in range(6)]);w.put(BOX+0x100+8,other)
            expected=w.invoke(0x18b050,BOX,BOX+0x100);assert lib.dw4_hitbox_intersects(native,other)==expected;total+=1
            probe=array();expected=w.probe(matrix);lib.dw4_hitbox_talk_probe(matrix,probe)
            assert bytes(probe)==expected,('talk probe',case,list(probe),struct.unpack('<6f',expected));total+=1
            if case%17:
                native=array();expected=w.body(original,matrix);lib.dw4_hitbox_fixed_world(original,matrix,native)
                assert bytes(native)==expected,('body',case,list(native),struct.unpack('<6f',expected));total+=1
        for axis in range(3):
            a=array(0,0,0,1,1,1)
            for boundary in (1.,1.000001,0.,-.000001):
                b=array(*a);b[axis]=boundary;b[axis+3]=boundary+.25
                w.put(BOX+8,a);w.put(BOX+0x100+8,b);w.descend=set();expected=w.invoke(0x18b050,BOX,BOX+0x100)
                assert lib.dw4_hitbox_intersects(a,b)==expected;total+=1
    print(f'hit boxes: {total} original transform/centre/intersection and complete3908e0/3993e0 results match; object/list/context leaves controlled')
if __name__=='__main__':main()
