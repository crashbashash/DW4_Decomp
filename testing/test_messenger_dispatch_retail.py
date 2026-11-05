#!/usr/bin/env python3
"""Complete messenger selector/dispatcher block vs original RAM and call order.

Registry, list, intern, allocation and virtual receiver callbacks are controlled
leaves. This tests guest semantics, not native gameplay or hardware concurrency.
"""
import argparse,ctypes as C,itertools,subprocess,sys,tempfile
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'port/tools'))
from verify_scriptservices_retail import World,Selector,BASE,MSG,SYS,CTX,CACHE,QUEUE,REG,RECORD,NAMES,IDS,RECEIVERS,BYTE,INTS,CIDS,CRECV,CHECK,HANDLE
from ee_core import MASK
from test_messenger_results_retail import Api,READ,WRITE,CALL
ENTRIES=(0x38d470,0x38d4a0,0x38d560,0x38d7a0,0x38d820,0x38d860,
         0x38e060,0x38e530,0x38e5b0,0x38e5d0,0x38e5f0,0x38e630,0x38e670,0x38e6b0)
STACK=0x1fff000
OBJECTS=0x1800000
NEW_RECORD,NEW_QUEUE,ENUM_TYPE,ALLOC=BASE+0x9000,BASE+0xa000,BASE+0xb000,BASE+0xc000
class Dispatch(Selector):
    def __init__(self,image,rows=()):
        super().__init__(image,rows);self.descend=set(ENTRIES);self.events=[]
        self.handled=0;self.change_filter=None;self.change_state=None;self.destroy_count=False
        self.relocate=False;self.registry_exists=True;self.enum_valid=True;self.enum_value=17;self.allocation=True
        self.w(CTX+40,4,OBJECTS);self.list(OBJECTS,[])
        self.w(RECORD+4,4,10);self.w(0x585be0,4,0x1800400)
        self.w(0x554c14,1,1)
        for p in self.values(RECEIVERS):self.w(p+4,4,10)
        self.w(BASE+0x1000+4,4,10)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        counts={0x38bee0:1,0x38ca40:1,0x12a4a4:2,0x2eaf60:2,0x2ff820:1,
                0x30c940:2,0x2d6680:3,0x3022c0:3,0x1c64e0:3,0x2d6790:3,
                0x301e30:2,0x2d6cf0:2,0x2d6b80:4,CHECK:3,HANDLE:3,
                0x2eb010:1,0x2eadf0:1,0x2fba30:4,0x12a5fc:2,0x301000:1,
                0x2f88e0:1,0x3584e0:1,0x358950:1,0x2fecb0:2,0x1ca620:2,0x100610:1}
        assert e in counts,hex(e)
        normalized=[('temp' if STACK-0x2000<=x<STACK else x) for x in v[:counts[e]]]
        self.events.append((e,*normalized))
        if e==0x38bee0:
            self.w(MSG+48,1,1);self.w(CTX+8,1,0);self.w(BYTE+8,4,0);self.w(INTS+8,4,0);return 0
        if e==0x12a4a4:
            def text(p):
                if not p:return None
                data=[]
                while self.read(p,1):data.append(self.read(p,1));p+=1
                return bytes(data)
            return int(text(v[0])!=text(v[1]))
        if e==0x2eaf60:
            if v[1]:self.w(v[1]-4,4,self.read(v[1]-4,4)+1)
            return v[1]
        if e==0x3022c0:return RECORD if self.registry_exists and v[2]==self.token('MODELCTRL') else 0
        if e==0x1c64e0:
            value=self.values(v[1])[v[2]];self.w(v[0],4,value)
            if value:self.w(value-4,4,self.read(value-4,4)+1)
            return 0
        if e==0x301e30:
            if v[1]:self.w(v[1]+4,4,self.read(v[1]+4,4)+1)
            self.list(v[0],self.values(v[0])+[v[1]]);return 0
        if e==0x1ca620:
            value=self.read(v[1],4)
            if value:self.w(value-4,4,self.read(value-4,4)+1)
            self.list(v[0],self.values(v[0])+[value]);return 0
        if e==CHECK:
            if self.change_state is not None:self.w(CTX+8,1,self.change_state)
            return self.handled
        if e==HANDLE:
            if self.change_filter is not None:self.w(BASE+0x1000+16,4,self.change_filter)
            return 0
        if e==0x2ff820:
            if self.destroy_count:self.w(CRECV+8,4,0)
            return 0
        if e==0x2d6790:
            if self.relocate:
                old=self.read(v[0]+16,4);new=old+0x80000
                for i in range(self.read(v[0]+8,4)*v[2]):self.w(new+i,1,self.read(old+i,1))
                self.w(v[0]+16,4,new)
            self.w(v[0]+8,4,v[1]);self.w(v[0]+12,4,v[1]+4);return 0
        if e==0x2eb010:return ALLOC if self.allocation else 0
        if e==0x2eadf0:return v[0]
        if e==0x301000:return ALLOC
        if e==0x2f88e0:return ALLOC+0x100
        if e==0x2fba30:
            self.w(v[0],4,self.read(0x4fb410,4) if self.enum_valid else self.read(0x4fb410,4)^4);self.w(v[3],4,self.enum_value);return 0
        if e==0x12a5fc:
            i=0
            while True:
                byte=self.read(v[1]+i,1);self.w(v[0]+i,1,byte);i+=1
                if not byte:break
            return 0
        if e==0x3584e0:
            self.w(NEW_RECORD+4,4,1)
            for offset,listp in ((12,NAMES),(16,IDS),(20,RECEIVERS)):
                self.w(NEW_RECORD+offset,4,listp);self.list(listp,[])
            return NEW_RECORD
        if e==0x358950:self.w(NEW_QUEUE+4,4,1);return NEW_QUEUE
        if e in (0x2fecb0,0x100610):return 0
        return World.call(self,e,args)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=p.parse_args()
    image=args.elf.read_bytes();retail=Dispatch(image);native=Dispatch(image);errors=[];cases=0;hits=set()
    @CALL
    def call(_,e,values):
        try:return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    def setup(rows=()):
        nonlocal retail
        retail=Dispatch(image,rows)
    with tempfile.TemporaryDirectory(prefix='dw4-messenger-dispatch-') as td:
        so=Path(td)/'dispatch.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/messenger-dispatch.c'),'-o',str(so)],check=True)
        fn=C.CDLL(str(so)).dw4_messenger_dispatch;fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            expected=retail.invoke(entry,*values);actual=fn(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in values]),STACK-0x1000)
            assert not errors,errors
            if entry in (0x38d4a0,0x38d7a0,0x38e530):assert expected==actual,(hex(entry),expected,actual)
            def ram(world):return {p:v for p,v in world.mem.items() if not STACK-0x2000<=p<STACK+32 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),values,[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry)
        rows=[('first',7,0),('other',8,1),(None,-1,0),('first',7,1)]
        for name,id,ready in itertools.product((None,'first','other','missing'),(-2,-1,7,8,99),(0,1)):
            setup(rows);retail.w(MSG+48,1,ready)
            compare(0x38d860,MSG,retail.token('MODELCTRL'),retail.token(name),id)
            # Persistent cache hit, name miss, category miss and restored hit.
            compare(0x38d860,MSG,retail.token('MODELCTRL'),retail.token(name),id+1)
            compare(0x38e060,MSG,retail.token('EVENT'))
        for count in (0,1,2,4,9,17):
            varied=[(None if i%3==0 else 'first',(-1,7,8)[i%3],i%2) for i in range(count)]
            for id,key,state,handled in itertools.product((-2,-1,7,99),('SEARCH','FIND_SPACE','EVENT'),(0,1,2),(0,1,256)):
                setup(varied)
                compare(0x38d860,MSG,retail.token('MODELCTRL'),0,id)
                retail.w(CTX+8,1,state);retail.handled=handled
                compare(0x38e060,MSG,retail.token(key))
        # Actual special query strings come from the retail image, not a guess.
        for key in (0x50ee10,0x50ee18):
            for id in (-2,-1,7,99):
                setup(rows);compare(0x38d860,MSG,retail.token('MODELCTRL'),0,id);compare(0x38e060,MSG,key)
        # Cache hit at every position, promotion, empty cached receivers refill,
        # old strings/receiver destruction, and >8-cell clear re-read.
        for position in (0,1,2):
            setup(rows);cache_rows=[]
            for i in range(3):
                row=BASE+0x1000+i*0x100
                retail.w(row+4,4,10);retail.w(row+8,4,retail.token('MODELCTRL' if i==position else 'OTHER'))
                retail.w(row+12,4,retail.token('first'));retail.w(row+24,4,CIDS+i*0x1000);retail.w(row+28,4,CRECV+i*0x1000)
                retail.list(CIDS+i*0x1000,[]);retail.list(CRECV+i*0x1000,[]);cache_rows.append(row)
            retail.list(CACHE,cache_rows);compare(0x38d860,MSG,retail.token('MODELCTRL'),retail.token('first'),7)
        for count,destroy in itertools.product((1,8,9,17),(False,True)):
            setup(rows);old=BASE+0x1000;retail.w(old+8,4,retail.token('OTHER'))
            retail.w(old+12,4,retail.token('old'));retail.w(retail.token('OTHER')-4,4,1);retail.w(retail.token('old')-4,4,1)
            retail.list(CRECV,[BASE+0xd000+i*16 for i in range(count)])
            for row in retail.values(CRECV):retail.w(row+4,4,1)
            retail.destroy_count=destroy;compare(0x38d860,MSG,retail.token('MODELCTRL'),0,-1)
        for registry,pool,allocation in itertools.product((False,True),(0,BASE+0x3000),(False,True)):
            setup(rows);retail.registry_exists=registry;retail.w(0x586f20,4,pool);retail.allocation=allocation
            compare(0x38d860,MSG,retail.token('MODELCTRL'),0,-1)
            compare(0x38e060,MSG,0x50ee10)
        for key in (0x50ee10,0x50ee18):
            setup(rows);retail.relocate=True
            for listp in (CIDS,CRECV,BYTE,INTS,OBJECTS):retail.w(listp+12,4,0)
            compare(0x38d860,MSG,retail.token('MODELCTRL'),0,7)
            compare(0x38e060,MSG,key)
        for state in (0,1,2):
            setup(rows);compare(0x38d860,MSG,retail.token('MODELCTRL'),0,-1)
            retail.change_state=state;compare(0x38e060,MSG,retail.token('EVENT'))
        for entry in (0x38e5b0,0x38e5d0,0x38e5f0,0x38e630,0x38e670):
            setup(rows);cat=retail.token('MODELCTRL');key=retail.token('EVENT')
            values={0x38e5b0:(MSG,cat,7),0x38e5d0:(MSG,cat),0x38e5f0:(MSG,cat,0,7,key),0x38e630:(MSG,cat,7,key),0x38e670:(MSG,cat,key)}[entry]
            compare(entry,*values)
        for handled in (0,1,256):
            setup(rows);compare(0x38d860,MSG,retail.token('MODELCTRL'),0,-1)
            retail.change_filter=-2;retail.handled=handled;compare(0x38e060,MSG,retail.token('EVENT'))
        for entry in (0x38d7a0,0x38e530):
            for self,flag,refs in itertools.product((0,BASE+0xe000),(0,1,0x8000,0x10001),(1,2,0x800001)):
                setup();retail.w(BASE+0xe000,4,RECORD);retail.w(RECORD+4,4,refs);compare(entry,self,flag)
        for enabled in (0,1,0x100000000):
            setup();retail.w(SYS+80,8,0xfedcba9876543210);compare(0x38d470,MSG,enabled)
        for valid,cached,value in itertools.product((False,True),(False,True),(0,17,0xffffffff)):
            setup();text=retail.token('field');retail.enum_valid=valid;retail.enum_value=value
            if cached:retail.w(0x58a4e0,4,ENUM_TYPE);retail.call(0x12a5fc,[0x58a4f0,text,0,0,0,0,0,0]);retail.w(0x58a530,4,value)
            compare(0x38d4a0,MSG,ENUM_TYPE,text)
        for exists,name,allocator in itertools.product((False,True),(None,'first'),(0,1)):
            setup();retail.registry_exists=exists;retail.w(0x554c14,1,allocator)
            compare(0x38d560,MSG,BASE+0xf000,retail.token('MODELCTRL'),retail.token(name),7)
        for name in (0,BASE+0x11000):
            setup();receiver=BASE+0x12000;description=BASE+0x12100
            retail.w(receiver+12,4,description);retail.w(description+8,4,name);retail.w(receiver+8,4,99)
            compare(0x38d820,MSG,receiver,retail.token('MODELCTRL'))
        for busy,allocator,ready in itertools.product((0,1),(0,1),(0,1)):
            setup();row=BASE+0x13000;retail.list(QUEUE,[row]);retail.w(row+4,4,10);retail.w(row+8,1,busy)
            retail.w(0x554c14,1,allocator);retail.w(MSG+48,1,ready)
            compare(0x38e6b0,MSG,retail.token('MODELCTRL'),retail.token('first'),7)
        assert hits==set(ENTRIES),hits
    print(f'messenger dispatch retail: {cases} RAM/return/ordered-call cases; all 14 bodies; external services controlled')
if __name__=='__main__':main()
