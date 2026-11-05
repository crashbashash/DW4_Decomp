#!/usr/bin/env python3
"""Retail/C differential for long-timer lifecycle and system-clock pump.

Raw time, external notification/task virtual methods and software-double conversion
leaves are stubbed. Multiplication runs original retail instructions. Compares
ordered calls/stores, final memory, and defined returns. No game bytes embedded.
"""
import argparse
import ctypes as C
import hashlib
from pathlib import Path
import random
import subprocess
import sys
import tempfile
from ee_core import EE, MASK, sx
from verify_action2time import World as Memory, reachable, symbol_sizes, interpreter_selftest

ROOT=Path(__file__).resolve().parents[1]
TIMER,SYS,VT,WRAP,LIST,ARR,OWNER,N1,N2,NVT=range(0x1500000,0x1500a00,0x100)
RAW,NOTIFY,BEGIN,END,GATE,PRESENT,FINISH=range(0x1510000,0x1510700,0x100)
ENTRIES=(0x330a50,0x330af0,0x330b40,0x330be0,0x330c20,0x330c80,0x330cd0,
         0x330cf0,0x330d30,0x330d90,0x330da0,0x330db0,0x330e50,
         0x2371f0,0x237280,0x237730,0x2377c0)
EXTRA=(0x237ec0,0x378bc0,0x3a0540)
RETURNS={0x3a0540,0x330a50,0x330af0,0x330b40,0x330da0,0x330db0,0x330e50}
LEAF={RAW:1,NOTIFY:1,BEGIN:1,END:1,GATE:1,PRESENT:1,FINISH:1,
      0x22eb50:2,0x22fcc8:1,0x230cc8:1,0x230a18:2,0x22e4b8:2,
      0x2306d0:2,0x230790:2,0x22ff70:1}
DISPATCH,DWRAP,DLIST,DARRAY,SNAPSHOT,SARRAY,MGR,MVT,MSYS,GLIST,GARRAY,GROUP,ALIST,AARRAY,ACT1,ACT2=range(0x1520000,0x1521000,0x100)
ACTION=0x1530000
LEAF.update({0x301ee0:2,0x2ff820:1,ACTION:2})
READ=C.CFUNCTYPE(C.c_uint64,C.c_void_p,C.c_uint32,C.c_uint)
WRITE=C.CFUNCTYPE(None,C.c_void_p,C.c_uint32,C.c_uint,C.c_uint64)
CALL=C.CFUNCTYPE(C.c_uint64,C.c_void_p,C.c_uint32,C.POINTER(C.c_uint64))
class Api(C.Structure):
    _fields_=[('user',C.c_void_p),('read',READ),('write',WRITE),('call',CALL)]

class World(Memory):
    def __init__(self,image,**opt):
        self.image=image;self.mem={};self.trace=[];self.options=opt
        self.raw=opt.get('raw',1000000000);self.step_ns=opt.get('step',101)
        w=self.w32
        w(TIMER,VT)
        for off,entry in {0x60:RAW,0x68:0x330af0,0x6c:0x330be0,0x70:0x330c20,
                          0x74:0x330c80,0x78:0x330cd0,0x7c:0x330cf0,
                          0x84:0x330d90,0x8c:0x330da0,0x90:0x330e50,0x94:RAW}.items():w(VT+off,entry)
        for off,key in ((8,'base'),(0x10,'elapsed'),(0x18,'preset')):self.w64(TIMER+off,opt.get(key,0))
        self.write(TIMER+0x20,1,opt.get('paused',0))
        w(SYS+0x30,TIMER);w(SYS+8,WRAP);w(SYS+0x1c,WRAP)
        w(WRAP+8,LIST);w(LIST+8,opt.get('count',2));w(LIST+0x10,ARR)
        w(ARR,N1);w(ARR+4,N2);w(N1,NVT);w(N2,NVT)
        w(NVT+0x5c,NOTIFY);w(NVT+0x64,BEGIN);w(NVT+0x68,END)
        w(SYS+0x20,N1);w(SYS+0xc,N2);w(SYS+0x18,OWNER);w(OWNER,NVT+0x1000)
        w(NVT+0x1000+0x90,GATE);w(NVT+0x1000+0x2b4,PRESENT);w(NVT+0x1000+0x2b8,FINISH)
        self.w64(SYS+0x38,opt.get('sample',0));self.w64(SYS+0x40,opt.get('delta',0))
        self.w64(SYS+0x50,opt.get('clock',0));w(SYS+0x48,opt.get('scale',0x40000))
        w(SYS+0x34,opt.get('frame',0))
        # Actual dispatch chain, with only the final Action2 update stubbed.
        w(DISPATCH,NVT+0x2000);w(NVT+0x2000+0x5c,0x237ec0)
        w(DISPATCH+8,DWRAP);w(DWRAP+8,DLIST);w(DLIST+8,opt.get('managers',1));w(DLIST+16,DARRAY)
        w(DARRAY,MGR);w(DARRAY+4,MGR)
        w(DISPATCH+0xc,SNAPSHOT);w(SNAPSHOT+16,SARRAY)
        w(SARRAY,N1 if opt.get('old_snapshot') else MGR);w(SARRAY+4,MGR);w(MGR+4,opt.get('refs',4))
        w(N1+4,1)
        w(MGR,MVT);w(MVT+0x74,0x378bc0);w(MVT+0x84,ACTION)
        w(MGR+0x10,MSYS);w(MGR+0x18,GLIST)
        self.write(MGR+0x1c,1,opt.get('enabled',1))
        for off,key,default in ((0x2c,'g2c',1),(0x2d,'g2d',0),(0x2e,'g2e',0)):
            self.write(MSYS+off,1,opt.get(key,default))
        w(GLIST+8,opt.get('groups',1));w(GLIST+16,GARRAY);w(GARRAY,GROUP);w(GARRAY+4,GROUP)
        w(GROUP+0x18,ALIST);w(ALIST+8,opt.get('actions',2));w(ALIST+16,AARRAY)
        w(AARRAY,ACT1);w(AARRAY+4,ACT2)
        if opt.get('dispatch'):w(SYS+0xc,DISPATCH)
        self.trace=[]
    def call(self,entry,args):
        assert entry in LEAF,hex(entry)
        a=tuple(v&MASK for v in args[:LEAF[entry]])
        self.trace.append(('call',entry,*a))
        if entry==0x301ee0:
            self.w32(a[0]+8,a[1]);return 0
        if entry==0x2ff820:return 0
        if entry==ACTION:
            self.trace.append(('action-clock',a[1],self.read(SYS+0x50,8)))
            return 0
        if entry==RAW:
            value=self.raw;self.raw=(self.raw+self.step_ns)&MASK
            return value
        if entry==GATE:return self.options.get('gate',0)
        if entry==PRESENT:return self.options.get('present',1)
        if entry in (BEGIN,END,NOTIFY,FINISH):
            if self.options.get('shrink') and entry==BEGIN:self.w32(LIST+8,0)
            # Tests notification order: a callback observes the clock already written.
            self.trace.append(('observed-clock',entry,self.read(SYS+0x50,8)))
            return 0
        # Opaque deterministic software-double leaves: verify forwarding/order only.
        return (entry*0x9e3779b97f4a7c15+sum((i+1)*v for i,v in enumerate(a)))&MASK

class Retail(World,EE):
    def __init__(self,image,**opt):
        self.ee_reset();World.__init__(self,image,**opt)
        self.descend=set(ENTRIES+EXTRA)|{0x22e440}
    def call_hook(self,entry):self.r[2]=self.call(entry,self.r[4:12])
    def invoke(self,entry,a,b=0):
        cov=self.covered;self.ee_reset();self.covered=cov
        self.r[4:6]=[a&MASK,b&MASK]
        self.r[28],self.r[29],self.r[31]=0x55c870,0x1fff000,0xfffffff0
        self.run_until(entry,0xfffffff0)
        return self.r[2]

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--elf',type=Path,required=True)
    ap.add_argument('--source',type=Path,default=ROOT/'recovered/frontend/systemclock.c')
    ap.add_argument('--mutations',action='store_true',help='also reject four deliberately broken C variants')
    args=ap.parse_args();image=args.elf.read_bytes()
    assert hashlib.sha1(image[0x80:0x80+0x454b00]).hexdigest()=='ffad4dab663cb290190bdfa34a8016d616a1652a'
    interpreter_selftest()
    with tempfile.TemporaryDirectory(prefix='dw4-clock-') as d:
        lib=Path(d)/'clock.so'
        subprocess.run(['cc','-std=c99','-O2','-Wall','-Wextra','-Werror','-fPIC','-shared',str(args.source),
                        '-I',str(ROOT/'recovered/frontend'),'-o',str(lib)],check=True)
        fn=C.CDLL(str(lib)).dw4_clock_call
        fn.argtypes=[C.POINTER(Api),C.c_uint32,C.c_uint64,C.c_uint64];fn.restype=C.c_uint64
        current=[None];errors=[]
        def read(_,a,n):return current[0].read(a,n)
        def write(_,a,n,v):current[0].write(a,n,v)
        def call(_,e,a):
            try:return current[0].call(e,[a[i] for i in range(8)])
            except Exception as exc:errors.append(exc);return 0
        api=Api(None,READ(read),WRITE(write),CALL(call))
        covered=set();calls=0
        def invoke(pair,entry,a=TIMER,b=0):
            nonlocal calls
            r,c=pair;r.trace=[];c.trace=[]
            expected=r.invoke(entry,a,b);current[0]=c
            got=fn(C.byref(api),entry,a,b&MASK)
            if errors:raise errors[0]
            assert r.trace==c.trace,(hex(entry),'trace',r.trace,c.trace)
            assert r.snapshot()==c.snapshot(),(hex(entry),'memory')
            assert r.raw==c.raw,(hex(entry),'raw calls')
            if entry in RETURNS:assert expected==got,(hex(entry),'return',expected,got)
            covered.update(r.covered);calls+=1
            return got
        def pair(**o):return Retail(image,**o),World(image,**o)
        rng=random.Random(772)
        # Every timer branch, including noncanonical true bytes and 64-bit wrap.
        for paused in (0,1,2,255):
            for k in range(75):
                o=dict(paused=paused,base=rng.getrandbits(64),elapsed=rng.getrandbits(64),
                       preset=rng.getrandbits(64),raw=rng.getrandbits(64))
                for entry in ENTRIES[:13]:invoke(pair(**o),entry,b=rng.getrandbits(64))
        # System start/stop and task-loop branch/callback-length behavior.
        for count in (0,1,2):
            for paused in (0,1):
                for gate in (0,1):
                    for present in (0,1):
                        for shrink in (False,True):
                            o=dict(count=count,paused=paused,gate=gate,present=present,shrink=shrink,
                                   clock=987654321,elapsed=12345,frame=0xffffffff)
                            for entry in ENTRIES[13:]:invoke(pair(**o),entry,SYS)
        # Exact low-64 multiply followed by signed shift, including overflow,
        # backwards time, stalled time and negative fractional deltas.
        for scale in (0,1,0x3ffff,0x40000,0x80000,0xffffffff,0x80000000,0x7fffffff):
            for delta in (0,1,-1,262143,262144,-262145,16683333,1<<46,1<<63,MASK):
                p=pair(raw=delta&MASK,scale=scale,clock=1000)
                invoke(p,0x237730,SYS)
                expected=(1000+(sx((delta*sx(scale,32))&MASK,64)>>18))&MASK
                assert p[0].read(SYS+0x50,8)==expected
        # Evolving timer lifecycle with independent elapsed-time expectations.
        p=pair(paused=1,raw=1000,step=0,preset=9)
        invoke(p,0x330cf0)
        for w in p:w.raw=1100
        assert invoke(p,0x330af0)==109
        invoke(p,0x330c20)
        for w in p:w.raw=999999
        assert invoke(p,0x330af0)==109
        invoke(p,0x330c20) # idempotent pause
        invoke(p,0x330be0)
        for w in p:w.raw+=20
        assert invoke(p,0x330af0)==129
        invoke(p,0x330be0) # idempotent resume must not discard those 20 ns
        assert invoke(p,0x330af0)==129
        invoke(p,0x330c80);assert invoke(p,0x330af0)==9
        invoke(p,0x330cd0)
        for w in p:w.raw+=700
        assert invoke(p,0x330af0)==9
        # Repeated system start clears sample/delta, not accumulated clock.
        p=pair(paused=1,raw=1000,step=0,count=0)
        invoke(p,0x2371f0,SYS)
        for w in p:w.raw=1100
        invoke(p,0x237730,SYS);assert p[0].read(SYS+0x50,8)==100
        invoke(p,0x237280,SYS)
        for w in p:w.raw=8000
        invoke(p,0x2371f0,SYS)
        invoke(p,0x237730,SYS);assert p[0].read(SYS+0x50,8)==200
        # Repeated task passes read raw source for profiling, never advance sys+50.
        p=pair(clock=123456789,raw=1000,step=100)
        for _ in range(8):
            invoke(p,0x2377c0,SYS)
            assert p[0].read(SYS+0x50,8)==123456789
            assert p[0].read(SYS+0x58,8)==100 and p[0].read(SYS+0x60,8)==100
        # Mixed lifecycle sequences exercise state retention, rebasing and updates.
        for _ in range(80):
            p=pair(paused=rng.randrange(2),raw=rng.getrandbits(50),count=2)
            for _ in range(60):
                for w in p:w.raw=(w.raw+16683300)&MASK
                entry=rng.choice((0x330af0,0x330be0,0x330c20,0x330c80,0x330cd0,
                                  0x330cf0,0x330d90,0x237730,0x2377c0))
                invoke(p,entry,SYS if entry<0x300000 else TIMER,b=rng.getrandbits(50))
        # Clock -> manager snapshot -> Action2 driver: the new clock reaches
        # each action in list order. No later render/task read changes that clock.
        for managers in (0,1,2):
            for groups in (0,1,2):
                for actions in (0,1,2):
                    for g2c in (0,1,2,255):
                        for g2d,g2e,enabled in ((0,0,1),(1,0,1),(0,1,1),(0,0,0)):
                            p=pair(dispatch=True,managers=managers,groups=groups,actions=actions,
                                   g2c=g2c,g2d=g2d,g2e=g2e,enabled=enabled,raw=16683300)
                            invoke(p,0x237730,SYS)
                            events=[x for x in p[0].trace if x[0]=='action-clock']
                            n=managers*groups*actions if g2c&1 and not g2d and not g2e and enabled else 0
                            assert len(events)==n
                            assert events==[('action-clock',a,16683300)
                                for _ in range(managers*groups if n else 0)
                                for a in (ACT1,ACT2)[:actions]]
        invoke(pair(dispatch=True,old_snapshot=True),0x237730,SYS)
        sizes=symbol_sizes();sizes[0x237ec0]=0x150;required=set()
        for entry in ENTRIES+EXTRA:
            needed=reachable(image,entry,sizes[entry]);required|=needed
            assert needed<=covered,(hex(entry),'uncovered',sorted(hex(x) for x in needed-covered))
        print(f'systemclock: {calls} retail/C calls; {len(required & covered)} body instruction addresses covered; '
              'ordered calls/stores, final memory and defined returns agree')
        print('Independent lifecycle, pause/resume/reset/restart, scaled-overflow, start/stop and held-clock task-pass assertions pass')
        print('Boundaries: raw time, external task/notification methods, Action2 leaf update and software-double leaves are shared stubs')
    if args.mutations:
        source=args.source.read_text()
        mutations={
            'logical-shift':('return (v >> 18) | ((v >> 63) ? (UINT64_MAX << 46) : 0);',
                             'return v >> 18;'),
            'drop-frozen-elapsed':('W(self+0x20,1,0);\n            now=virt',
                                  'W(self+0x20,1,0);\n            W(self+0x10,8,0);\n            now=virt'),
            'reset-world-time':('W(self+0x40,8,0);','W(self+0x50,8,0);\n        W(self+0x40,8,0);'),
            'stale-clock-callback':('W(self+0x50,8,R(self+0x50,8)+sar18(value));\n        virt(api,(uint32_t)R(self+0x20,4),0x5c,0);',
                                    'virt(api,(uint32_t)R(self+0x20,4),0x5c,0);\n        W(self+0x50,8,R(self+0x50,8)+sar18(value));')}
        with tempfile.TemporaryDirectory(prefix='dw4-clock-mutations-') as directory:
            for name,(old,new) in mutations.items():
                assert old in source
                path=Path(directory)/'systemclock.c';path.write_text(source.replace(old,new,1))
                result=subprocess.run([sys.executable,__file__,'--elf',str(args.elf),'--source',str(path)],
                                      stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
                assert result.returncode and 'AssertionError' in result.stdout,(name,result.stdout)
                print('mutation rejected:',name)
if __name__=='__main__':main()
