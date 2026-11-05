#!/usr/bin/env python3
"""Compare the complete node-animation/loading runtime with original EE instructions.

Clock source, traversal callbacks/allocation are leaves. EE float conversion is
executed on the retail side and integer-modeled by recovered eefloat.c.
"""
import argparse, ctypes as C, hashlib, random, subprocess, tempfile
from pathlib import Path
from ee_core import EE, MASK
from verify_systemclock import Api, READ, WRITE, CALL
from verify_action2time import World as Memory, reachable, interpreter_selftest, SOFTFLOAT, Union
ROOT=Path(__file__).resolve().parents[1]
NODE,CTX,VT,RES,LIST,ARR,VALUE,GROUP,GARR,RWRAP,RLIST,RARR,MAP=range(0x1600000,0x1600d00,0x100)
CLOCK,PUSH,POP,CALLBACK=range(0x1610000,0x1610400,0x100)
SIZES={0x39a930:36,0x39a960:124,0x39a9e0:308,0x39ab20:596,0x39ad80:52,
       0x39adc0:36,0x39adf0:12,0x39ae00:16,0x39ae10:52}
RETURNS={0x39a930,0x39a9e0,0x39ab20,0x39adc0,0x39ae00}
LEAVES={CLOCK:1,PUSH:2,POP:1,CALLBACK:2,0x1dca40:2,0x2d6790:3,
        0x1b1490:3,0x1e07a0:2,0x34e870:0,0x34e5d0:0,0x1e06c0:3}
class World(Memory):
    def __init__(self,image,**o):
        self.image=image;self.mem={};self.trace=[];self.options=o
        w=self.w32
        for off,key,d in [(0x20,'start',16666666),(0x28,'loop1',1666666666),
                          (0x30,'loop2',4666666666),(0x38,'stop',0),(0x48,'time',0),
                          (0x58,'bias',0),(0x60,'before',0),(0x68,'play',0),
                          (0x70,'lock',4733333333),(0x78,'limit',1666666666)]:
            self.w64(NODE+off,o.get(key,d))
        self.write(NODE+0x40,1,o.get('first',0));w(NODE+0x50,o.get('scale',0x3f800000))
        for a,v in [(CTX,VT),(VT+0x68,CLOCK),(VT+0x80,PUSH),(VT+0x84,POP),
                    (CTX+0x34,RES),(CTX+0x4c,LIST),(LIST+8,o.get('allocate',0)^1),
                    (LIST+0x14,0),(LIST+0x10,ARR),(ARR,VALUE),(VALUE+8,0),
                    (RES+0x44,MAP),(MAP,0),(RES+0x10,RWRAP),(RWRAP+0x10,RARR),
                    (RARR,GROUP),(GROUP+8,0),(GROUP+0xc,o.get('grow',0)^1),
                    (GROUP+0x10,GARR),(GROUP+0x1c,CALLBACK if o.get('callback',1) else 0),
                    (RES+0x30,0x7007),(0x562640,0x7777)]:w(a,v)
        self.trace=[]
    def call(self,e,a):
        assert e in LEAVES,hex(e)
        a=tuple(x&MASK for x in a[:LEAVES[e]])
        self.trace.append(('call',e,*a))
        if e==CLOCK:return self.options.get('now',1000000000)&MASK
        if e==0x1dca40:self.w32(LIST+8,1)
        if e==0x2d6790:self.w32(GROUP+8,a[1]);self.w32(GROUP+0xc,a[1])
        if e==0x1e07a0:return self.options.get('result',2)&MASK
        if e in (0x34e870,0x34e5d0):return 0x777
        return 0
class Retail(World,EE):
    def __init__(self,image,**o):
        self.ee_reset();World.__init__(self,image,**o)
        self.descend=Union(set(SIZES),SOFTFLOAT)
    def call_hook(self,e):self.r[2]=self.call(e,self.r[4:12])
    def invoke(self,e,a,b=0,c=0):
        coverage=self.covered;self.ee_reset();self.covered=coverage
        self.r[4:7]=[a&MASK,b&MASK,c&MASK]
        self.r[28],self.r[29],self.r[31]=0x55c870,0x1fff000,0xfffffff0
        self.run_until(e,0xfffffff0)
        return self.r[2]
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,required=True)
    args=p.parse_args();image=args.elf.read_bytes()
    assert hashlib.sha1(image[0x80:0x454b80]).hexdigest()=='ffad4dab663cb290190bdfa34a8016d616a1652a'
    interpreter_selftest()
    with tempfile.TemporaryDirectory(prefix='dw4-loading-node-') as d:
        out=Path(d)/'node.so'
        subprocess.run(['cc','-std=c99','-O2','-Wall','-Wextra','-Werror','-shared','-fPIC',
                        str(ROOT/'recovered/frontend/loadingnode.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-o',str(out)],check=True)
        fn=C.CDLL(str(out)).dw4_loadingnode_call
        fn.argtypes=[C.POINTER(Api),C.c_uint32,C.c_uint64,C.c_uint64,C.c_uint64];fn.restype=C.c_uint64
        current=[None];errors=[]
        def call(_,e,a):
            try:return current[0].call(e,[a[i] for i in range(8)])
            except Exception as exc:errors.append(exc);return 0
        api=Api(None,READ(lambda _,a,n:current[0].read(a,n)),WRITE(lambda _,a,n,v:current[0].write(a,n,v)),CALL(call))
        covered=set();total=0
        def pair(**o):return Retail(image,**o),World(image,**o)
        def step(pair,e,a=NODE,b=0,c=0):
            nonlocal total
            r,w=pair;r.trace=[];w.trace=[]
            expected=r.invoke(e,a,b,c);current[0]=w;actual=fn(C.byref(api),e,a,b&MASK,c&MASK)
            assert not errors,errors
            assert r.trace==w.trace,(hex(e),'trace',r.trace,w.trace)
            assert r.snapshot()==w.snapshot(),(hex(e),'memory')
            if e in RETURNS:assert expected==actual,(hex(e),expected,actual)
            covered.update(r.covered);total+=1
            return actual
        rng=random.Random(779)
        for k in range(400):
            now=rng.randrange(0,30000000000)
            o=dict(now=now,before=now-rng.choice([0,1,16666666,33333333,33333334,1000000000]),
                   play=rng.getrandbits(64),bias=rng.randrange(-1000000000,1000000000),
                   stop=rng.choice([0,0,4733333333]),scale=rng.choice([0,0x3f000000,0x3f800000,0x40000000]))
            step(pair(**o),0x39a960,b=rng.getrandbits(64),c=now)
            step(pair(**o),0x39a9e0,b=now)
            step(pair(**o),0x39adf0)
            step(pair(**o),0x39ae00)
        for now in (0x80000000<<18,0xffffffff<<18,(1<<32)<<18,-1,-(1<<63)):
            o=dict(before=now,loop2=1<<62,scale=0x3f800000)
            step(pair(**o),0x39a960,b=123,c=now)
            step(pair(**o),0x39a9e0,b=now)
        for first in (0,1,255):
            for allocate in (0,1):
                for grow in (0,1):
                    for callback in (0,1):
                        for result in (0,1,2,3,-1):
                            for e in (0x39ab20,0x39a930,0x39adc0):
                                o=dict(first=first,allocate=allocate,grow=grow,callback=callback,result=result)
                                step(pair(**o),e,a=NODE if e==0x39ab20 else CTX,b=CTX if e==0x39ab20 else NODE)
        for e in (0x39ad80,0x39ae10):step(pair(),e)
        for t in (0,4666666665,4666666666,4666666667,9333333332):
            step(pair(before=t),0x39a9e0,b=t)
        # Strict ready threshold and the stop-time freeze, including accumulation
        # during host stalls: local animation caps stalls, total play time does not.
        for play in (1666666665,1666666666,1666666667):
            assert step(pair(play=play),0x39ae00)==int(play>1666666666)
        flow=pair(first=1)
        for tick in range(650):
            for w in flow:w.options['now']=tick*16666666;w.w32(LIST+0x14,0)
            step(flow,0x39ab20,b=CTX)
            if tick==600:step(flow,0x39adf0)
        for e,size in SIZES.items():
            required=reachable(image,e,size)
            missing=required-covered
            assert not missing,(hex(e),'uncovered',[hex(x) for x in sorted(missing)])
        print(f'loadingnode: {total} retail/C comparisons, all nine consecutive bodies and reachable instructions; calls, stores, memory and defined returns agree')
if __name__=='__main__':main()
