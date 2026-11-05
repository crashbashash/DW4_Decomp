#!/usr/bin/env python3
"""Compare each native title/Options tick against original title and queue bodies.
Requires sibling decomp interpreter and user retail ELF. Logo JUMP/WCHECK also
execute as retail instructions, including Action2 and system-clock timing bodies.
Raw source cadence, EE arithmetic model and native non-timing leaves remain boundaries.
"""
import argparse
import ctypes as C
from pathlib import Path
import hashlib
import subprocess
import sys
import tempfile
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT.parent / 'scripts'))
from verify_commdl import Retail, ENTRIES, sx, MASK
from verify_modelwait import ENTRIES as MW_ENTRIES
from verify_loadintf2 import Api, PEEK, POKE, CALL
import action2_retail_oracle as a2oracle

class LogoOracle(Retail):
    def __init__(self,image,api):
        super().__init__(image);self.api=api
    def read(self,a,n):
        if hasattr(self,'api') and (0x1300000<=a<0x1300900 or a==0x586f20):
            return PEEK(self.api.peek)(self.api.user,a,n)&((1<<(8*n))-1)
        return super().read(a,n)
    def write(self,a,n,v):
        if hasattr(self,'api') and 0x1300000<=a<0x1300900:
            POKE(self.api.poke)(self.api.user,a,n,sx(v,32));return
        super().write(a,n,v)
    def call_hook(self,addr):
        self.r[2]=CALL(self.api.call)(self.api.user,addr,(C.c_int32*8)(*[sx(v,32) for v in self.r[4:12]]))&MASK

# Wrap both the compiled helpers and the retail instruction oracle at the actual
# native adapter boundary, retaining calls and writes in one ordered event stream.
LOGO_INVOKE=C.CFUNCTYPE(C.c_int,C.c_int,C.c_int,C.POINTER(Api),C.POINTER(C.c_int32))
def logo_oracle_callback(image,lib,traces,errors,hits):
    counts={0x12a4a4:2,0x2eaf60:2,0x30c940:2,0x38e5f0:5,0x38f220:2,0x395250:4,0x1300600:3}
    def invoke(i,addr,api,args):
        try:
            hits.add((i,addr))
            original=api.contents
            read=PEEK(original.peek);write=POKE(original.poke);call=CALL(original.call)
            def store(u,a,n,v):
                traces[i].append(('write',a,n,v));write(original.user,a,n,v)
            def leaf(u,a,v):
                if a not in counts:errors.append(('unexpected leaf',hex(a)));return 0
                traces[i].append(('call',a,*v[:counts[a]]))
                return call(original.user,a,v)
            peek=PEEK(lambda u,a,n:read(original.user,a,n));poke=POKE(store);callback=CALL(leaf)
            proxy=Api(None,*[C.cast(f,C.c_void_p) for f in (peek,poke,callback)])
            name,n=MW_ENTRIES[addr]
            if i==1:return LogoOracle(image,proxy).invoke(addr,args[:n])
            fn=getattr(lib,name);fn.argtypes=[C.POINTER(Api)]+[C.c_int32]*n
            fn.restype=C.c_int32 if addr!=0x394bf0 else None
            return fn(C.byref(proxy),*args[:n]) or 0
        except Exception as e:
            errors.append(e);return 0
    return LOGO_INVOKE(invoke)

BASE=0x1000000
SELF,INFO,CTRL,OPTION,PAD,WORK=range(0x1020000,0x1020600,0x100)

class Oracle(Retail):
    def __init__(self,image,lib):
        super().__init__(image);self.lib=lib;self.active=False
    def read(self,a,n):
        if getattr(self,'active',False) and BASE<=a<BASE+0x3000:
            return self.lib.bridge_peek(1,a,n)&((1<<(n*8))-1)
        return super().read(a,n)
    def write(self,a,n,v):
        if getattr(self,'active',False) and BASE<=a<BASE+0x3000:
            self.lib.bridge_poke(1,a,n,sx(v,32));return
        super().write(a,n,v)
    def step(self,pc,delay=False):
        word=self.read(pc,4)
        target=(word&0x3ffffff)<<2
        if word>>26==3 and target in (0x3ebe00,0x3ec050):
            assert not delay
            self.r[31]=pc+8;self.step(pc+4,True);self.call_hook(target)
            return pc+8
        return super().step(pc,delay)
    def call(self,addr,a):
        if addr==0x3022c0:return {0x518348:CTRL,0x518350:BASE,0x518360:WORK,0x5184a0:OPTION}[a[2]]
        if addr==0x39b810:return PAD
        if addr==0x301000:return 1
        if addr==0x2eaf60:return a[1]
        assert addr not in ENTRIES,hex(addr)
        return self.lib.bridge_call(1,addr,(C.c_int*8)(*a))
    def call_hook(self,addr):
        if addr==0x3e44f0:self.lib.bridge_advance(1)
        super().call_hook(addr)
    def tick(self,dir,pressed):
        self.active=True
        ctrl=(C.c_int*6)();opt=(C.c_int*9)();self.lib.bridge_state(1,ctrl,opt)
        for a,v in ((SELF+20,WORK),(SELF+32,BASE+0x200),(INFO+40,WORK),(INFO+24,1)):
            self.write(a,4,v)
        for i,v in enumerate(ctrl):self.write(CTRL+24+i*4,4,v)
        for i,v in enumerate(opt):self.write(OPTION+20+i*4,4,v)
        for off,v in ((28,dir),(32,0),(72,pressed),(76,0)):self.write(PAD+off,4,v)
        self.invoke(0x3f2ef0,(SELF,INFO))
        for i in range(6):ctrl[i]=sx(self.read(CTRL+24+i*4,4),32)
        for i in range(9):opt[i]=sx(self.read(OPTION+20+i*4,4),32)
        self.lib.bridge_set_state(1,ctrl,opt)
        # Native tick mirrors committed option fields into presentation values.
        return list(ctrl),list(opt)

import clock_retail_oracle as clockoracle
from native_shared import build_shared

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--elf',type=Path,default=ROOT.parent.parent / 'local/extracted/SLUS_208.36');args=ap.parse_args()
    image=args.elf.read_bytes()
    assert hashlib.sha1(image[0x80:0x454b80]).hexdigest()=='ffad4dab663cb290190bdfa34a8016d616a1652a'
    with tempfile.TemporaryDirectory() as tmp:
        so=Path(tmp)/'bridge.so'
        build_shared(['cc','-std=c99','-Wall','-Wextra','-Werror','-shared','-fPIC','-O2',
            '-I'+str(ROOT/'include'),'-I'+str(ROOT/'recovered/frontend'),
            *[str(ROOT/p) for p in ('tools/title_retail_bridge.c','src/clockhost.c','recovered/frontend/systemclock.c','src/commdlhost.c','recovered/frontend/title-menu.c',
                                   'recovered/frontend/commdl.c','recovered/frontend/completion.c','src/logoseq.c','recovered/frontend/modelwait.c','src/action2host.c','src/random.c','recovered/frontend/action2time.c','recovered/frontend/eefloat.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));total=0
        traces=[[],[]];errors=[];hits=set()
        callback=logo_oracle_callback(image,lib,traces,errors,hits)
        lib.bridge_logo_oracle.argtypes=[LOGO_INVOKE];lib.bridge_logo_oracle(callback)
        a2hits=set()
        a2callback=a2oracle.install(image,lib,traces,errors,a2hits)
        clockhits=set()
        clockcallback=clockoracle.install(image,lib,traces,errors,clockhits)
        lib.bridge_world.restype=C.c_int64
        def state():
            a=(C.c_int*6)();b=(C.c_int*9)();lib.bridge_state(0,a,b);return list(a),list(b)
        def reset():
            lib.bridge_init(0);lib.bridge_init(1);return Oracle(image,lib)
        oracle=reset()
        def compare():
            assert not errors,errors
            assert not lib.bridge_error(0) and not lib.bridge_error(1)
            assert traces[0]==traces[1],('ordered logo/Action2 events',total,traces)
            a=(C.c_ubyte*40000)();b=(C.c_ubyte*40000)()
            n=lib.bridge_snapshot(0,a);m=lib.bridge_snapshot(1,b)
            assert n==m and bytes(a[:n])==bytes(b[:m]),('snapshot',total,[(i,a[i],b[i]) for i in range(n) if a[i]!=b[i]][:30])
        def tick(d=0,p=0):
            nonlocal total
            traces[0].clear();traces[1].clear()
            lib.bridge_tick(0,d,p);expected=oracle.tick(d,p)
            assert state()==expected,(total,state(),expected)
            compare();total+=1
        def ready(s):
            c,_=state()
            return c[2]==s and ((c[3:]==[2,1,0]) if s==1 else (c[3:5]==[1,1]) if s==2 else c[3:5]==[1,0])
        def wait(s):
            for _ in range(500):
                if ready(s):return
                tick()
            raise AssertionError(('stalled',s,state()))
        # Interrupt OPEN with CLOSE, then replace it with OPEN before completion.
        # Token values come from the imported title reference.
        tokens=(ROOT/'recovered/frontend/title-menu.h').read_text()
        import re
        def token(name):return int(re.search(r'\b'+name+r'\s*=\s*(0x[0-9a-fA-F]+)',tokens).group(1),16)
        for seq in ('T_SQ_OPEN','T_SQ_CLOSE','T_SQ_OPEN'):
            traces[0].clear();traces[1].clear()
            for i in (0,1):lib.bridge_logo_play(i,token(seq))
            assert not errors,errors[:3]
            assert traces[0]==traces[1],("clock trace",traces[0][:8],traces[1][:8])
            for _ in range(4):tick()
        # Explicit absolute clock, held ticks, large jumps and precision loss.
        for c0 in (0,123456789,((1<<25)+1)<<18,(1<<31)<<18,((1<<31)+255)<<18):
            for seq in ('T_SQ_OPEN','T_SQ_CLOSE'):
                oracle=reset()
                for i in (0,1):lib.bridge_clock(i,c0);lib.bridge_model_tick(i)
                world0=lib.bridge_world(0)
                traces[0].clear();traces[1].clear()
                for i in (0,1):lib.bridge_logo_play(i,token(seq))
                compare()
                for frame in range(46):
                    # Repeat the start clock ten times to reject age-based completion.
                    now=c0+max(0,frame-10)*16666667
                    traces[0].clear();traces[1].clear()
                    for i in (0,1):lib.bridge_clock(i,now);lib.bridge_model_tick(i)
                    compare();total+=1
                    elapsed=a2oracle.py_node_time(lib.bridge_world(0),0x3f800000,0)-a2oracle.py_node_time(world0,0x3f800000,0)
                    assert lib.bridge_logo_done(0)==int(elapsed>499999968),(c0,seq,frame,elapsed)
                assert lib.bridge_logo_done(0),('never completed',c0,seq)
        # Pause after 200 ms, hold raw time for 100 ticks, then resume at half speed.
        oracle=reset()
        for i in (0,1):lib.bridge_clock(i,0);lib.bridge_logo_play(i,token('T_SQ_OPEN'))
        for op,value in [('clock',200000000),('model_tick',None),('pause',None),
                         ('clock',9200000000)]+[('model_tick',None)]*100+[
                         ('resume',None),('scale',0x20000),('clock',9600000000),
                         ('model_tick',None),('clock',9900000000),('model_tick',None)]:
            traces[0].clear();traces[1].clear()
            for i in (0,1):getattr(lib,'bridge_'+op)(i,*([] if value is None else [value]))
            compare()
            if op=='model_tick':total+=1
        assert lib.bridge_world(0)==550000000 and lib.bridge_logo_done(0)
        assert clockhits=={(i,a) for i in (0,1) for a in (0x237730,0x330be0,0x330c20)},clockhits
        oracle=reset()
        wait(1);tick(0,0x4000);assert ready(1);tick(0,8);wait(2)
        tick(4);tick(0,0x4000);wait(2);tick(0,0x4000);wait(4)
        tick(2);wait(4);tick(4);wait(4);tick(8);wait(4)
        tick(4);wait(4);tick(0,0x2000);wait(2)
        tick(0,0x2000);wait(1);tick(0,8);wait(2)
        tick(4);wait(2);tick(0,0x4000);wait(4)
        tick(4);wait(4);tick(4);wait(4);tick(0,0x4000);wait(2)
        tick(0,0x4000)
        for _ in range(180):tick()
        oracle=reset()
        for _ in range(2200):tick()
        assert hits=={(i,a) for i in (0,1) for a in (0x394ae0,0x394b30,0x394bf0)},hits
        assert {(1,a) for a in (0x376340,0x3764c0,0x376de0,0x376f40,0x3a7a20,0x3a7e90,0x3a7fd0,0x398e80,0x230110)} <= a2hits,a2hits
        print(f'title integration: {total} retail/native ticks agree, including queues, model state, Options, cancel/re-entry, handoff and attract')
if __name__=='__main__':main()
