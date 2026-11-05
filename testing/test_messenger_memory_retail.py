#!/usr/bin/env python3
"""Messenger memory initialization/reset vs retail RAM and service order.

Real recovered memory/lifecycle/dispatch bodies compose through initialization,
message delivery and reset. Object factories and lower services are controlled.
"""
import argparse,ctypes as C,itertools,subprocess,tempfile
from pathlib import Path
from test_messenger_lifecycle_retail import Lifecycle,ENTRIES as LIFE,DISPATCH,ROOT,MSG,SYS,CACHE,QUEUE,REG,PUSH,BASE,STACK,MASK,Api,READ,WRITE,CALL,CONTEXT
ENTRIES=(0x38bee0,0x38c390,0x38c410,0x38c490,0x38d080)
FACTORIES=(0x358d80,0x358070,0x358950)
class Memory(Lifecycle):
    def __init__(self,image):
        super().__init__(image);self.descend|=set(ENTRIES)
        self.factory_counts={e:0 for e in FACTORIES};self.fail_factory=0;self.fail_index=-1;self.factory_refs=1
        self.toggle_allocator=False;self.mutate_list=0;self.mutation=False
    def arg_object(self,index):
        p=0x1000000+index*0x1000;self.context(p,0,4,self.factory_refs)
        for i in range(8):self.w(self.read(p+16+i*4,4)+16,4,0x1100000+index*0x1000+i*0x100)
        return p
    def work_object(self,index):
        p=0x1300000+index*0x400;self.w(p+4,4,self.factory_refs)
        for offset in (8,12,16,20):self.w(p+offset,4,0)
        for offset,delta in ((24,0x100),(28,0x200)):
            self.w(p+offset,4,p+delta);self.list(p+delta,[]);self.w(p+delta+12,4,4)
        return p
    def delay_object(self,index):
        p=0x1400000+index*0x100;self.w(p+4,4,self.factory_refs);self.w(p+8,1,0);self.w(p+16,8,0)
        for offset in (24,28,32,36):self.w(p+offset,4,0)
        self.w(p+40,4,self.arg_object(index+128));return p
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e in FACTORIES:
            self.events.append((e,v[0]));index=self.factory_counts[e];self.factory_counts[e]+=1
            if self.toggle_allocator:self.w(0x554c14,1,1-self.read(0x554c14,1))
            if e==self.fail_factory and (self.fail_index<0 or index==self.fail_index):return 0
            return {0x358d80:self.arg_object,0x358070:self.work_object,0x358950:self.delay_object}[e](index)
        if e==0x301ee0:
            self.events.append((e,*v[:2]));old=self.read(v[0]+8,4)
            data=self.read(v[0]+16,4)
            for i in range(v[1],old):
                obj=self.read(data+i*4,4)
                if obj:self.w(obj+4,4,self.read(obj+4,4)-1)
                self.w(data+i*4,4,0)
            for i in range(old,v[1]):self.w(data+i*4,4,0)
            self.w(v[0]+8,4,v[1]);return 0
        if e==0x2ff820 and self.mutate_list and not self.mutation:
            self.w(self.mutate_list+8,4,0);self.mutation=True
        return super().call(e,args)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=p.parse_args()
    image=args.elf.read_bytes();retail=Memory(image);native=Memory(image);errors=[];cases=0;hits=set();depth=0
    @CALL
    def call(_,e,values):
        nonlocal depth
        try:
            if e in ENTRIES:return memory(C.byref(api),e,values)
            if e in LIFE or e in DISPATCH:
                depth+=1
                try:return (life if e in LIFE else dispatch)(C.byref(api),e,values,STACK-0x1000-depth*0x100)
                finally:depth-=1
            return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-messenger-memory-') as td:
        so=Path(td)/'memory.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/name) for name in ('messenger-memory.c','messenger-lifecycle.c','messenger-dispatch.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));memory=lib.dw4_messenger_memory;memory.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];memory.restype=C.c_uint64
        life=lib.dw4_messenger_lifecycle;dispatch=lib.dw4_messenger_dispatch
        for fn in (life,dispatch):fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        def setup():
            nonlocal retail
            retail=Memory(image)
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            expected=retail.invoke(entry,*values);v=(C.c_uint64*8)(*[x&MASK for x in values])
            if entry in ENTRIES:actual=memory(C.byref(api),entry,v)
            else:actual=(life if entry in LIFE else dispatch)(C.byref(api),entry,v,STACK-0x1000)
            assert not errors,errors
            if entry in (0x38c390,0x38c410):assert expected==actual,(hex(entry),expected,actual)
            def ram(world):return {p:v for p,v in world.mem.items() if not STACK-0x4000<=p<STACK+32 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),values,[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:16])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            assert retail.factory_counts==native.factory_counts
            cases+=1;hits.add(entry)
        for work,delay,spare,allocator in itertools.product((0,64,65),(0,32,33),(0,4,5),(0,1)):
            setup()
            for lst,n in ((CACHE,work),(QUEUE,delay),(PUSH,spare)):
                retail.list(lst,[0]*n);retail.w(lst+12,4,max(n,128))
            retail.w(MSG+48,1,0);retail.w(0x554c14,1,allocator);retail.w(MSG+40,8,1234)
            compare(0x38bee0,MSG)
            assert retail.read(CACHE+8,4)==64 and retail.read(QUEUE+8,4)==32 and retail.read(PUSH+8,4)==4
            assert retail.read(MSG+40,8)==1234
        for factory,index,refs in itertools.product(FACTORIES,(-1,0,2),(0,1)):
            setup();retail.fail_factory=factory;retail.fail_index=index;retail.factory_refs=refs
            compare(0x38bee0,MSG)
        setup();retail.toggle_allocator=True;compare(0x38bee0,MSG)
        setup();retail.list(CACHE,[0x1500000]+[0]*63);retail.w(0x1500000+4,4,1);retail.mutate_list=CACHE
        compare(0x38bee0,MSG)
        assert retail.read(CACHE+8,4)==0 and retail.values(CACHE)==[]
        setup();compare(0x38bee0,MSG);compare(0x38bee0,MSG)
        # Reset captures release counts, then re-reads count for zeroing, and
        # reserves four units even when capacity is already <=4.
        for count,capacity,refs,mutate in itertools.product((0,1,4,8,9,17),(4,32),(1,2,0x800001),(False,True)):
            setup();retail.w(CONTEXT+4,4,refs)
            for j,lst in enumerate((REG,CACHE,QUEUE,PUSH)):
                rows=[]
                for i in range(count):
                    p=0x1500000+j*0x10000+i*0x100;rows.append(p);retail.w(p+4,4,refs)
                retail.list(lst,rows);retail.w(lst+12,4,capacity)
            if mutate:retail.mutate_list=CACHE
            compare(0x38c490,MSG)
            assert retail.read(MSG+48,1)==0 and retail.read(MSG+16,4)==0
        for entry in (0x38c390,0x38c410):
            for owner,object,flag,refs in itertools.product((0,0x1600000),(0,CONTEXT),(0,1,0x8000,0x10001),(1,2,0x800001)):
                setup();retail.w(0x1600000,4,object);retail.w(CONTEXT+4,4,refs);compare(entry,owner,flag)
        setup();compare(0x38d080,MSG)
        # Actual cold initialization, cache selection, immediate and delayed
        # sends, expiry, nesting, reset and initialization again.
        setup();retail.w(MSG+48,1,0)
        compare(0x38d050,MSG)
        assert retail.factory_counts=={0x358d80:5,0x358070:64,0x358950:32}
        compare(0x38e670,MSG,retail.token('MODELCTRL'),retail.token('SEARCH'))
        compare(0x38ecf0,MSG,retail.token('MODELCTRL'),retail.token('EVENT'),0)
        compare(0x38d0a0,MSG)
        compare(0x38ed70,MSG);compare(0x38ef50,MSG)
        compare(0x38c490,MSG);compare(0x38d050,MSG)
        # Receiver selection can itself trigger the original initialization.
        setup();retail.w(MSG+48,1,0);compare(0x38e670,MSG,retail.token('MODELCTRL'),retail.token('FIND_SPACE'))
        assert set(ENTRIES)<=hits,hits
    print(f'messenger memory retail: {cases} RAM/defined-return/ordered-call cases; all 5 bodies and cold init/dispatch/queue/nesting/reset integration; factories and lower services controlled')
if __name__=='__main__':main()
