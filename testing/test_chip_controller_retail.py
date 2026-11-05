#!/usr/bin/env python3
"""Chip transaction controller vs original EE instructions.

Synthetic memory and controlled engine services; no native/gameplay acceptance.
Compare persistent RAM and ordered calls, including preview and wallet writes.
"""
import ctypes as C
import itertools
from pathlib import Path
import subprocess
import tempfile
from test_xdata_controller_retail import XdataWorld,WINDOW,LIST,VTABLES,NEW,SCRATCH,ROOT,Api,READ,WRITE,CALL,MASK,STACK,FOLDERS
CHIP=0x43aae0
COUNT,BIND=0x43c720,0x3f63c0
ITEM_LIST,INVENTORY,DEVICE,ITEMS,CLONE,STRINGS,INTS,STATUS=range(0x2000000,0x2080000,0x10000)
ARROWS,PREV,NEXT=0x1230010,0x1230020,0x1230030
STAT_KEYS=(0x51b3f8,0x51b408,0x51b418,0x51b420,0x51be40,0x51be50,0x51be58,0x51be68,0x51be78,0x51be88,0x51be90,0x51be98)

class ChipWorld(XdataWorld):
    def __init__(self,image):
        super().__init__(image);self.descend={CHIP};self.frame=STACK-288
        self.chip_mutation=None;self.old_text=0;self.copy_refs=None;self.lookup_count=0;self.property_count=0
        self.cost=100;self.stat=0;self.delta=5;self.rows=12;self.can_page=1;self.prev=0;self.next=0
        self.w(WINDOW+32,4,2);self.w(WINDOW+36,4,0);self.w(WINDOW+96,4,ITEM_LIST)
        self.w(WINDOW+40,4,0);self.w(WINDOW+84,4,0);self.w(WINDOW+92,4,0)
        self.w(VTABLES+96,4,ARROWS);self.w(VTABLES+100,4,PREV);self.w(VTABLES+104,4,NEXT)
        self.make_list(ITEM_LIST,[ITEMS+i*64 for i in range(25)])
        self.make_list(INVENTORY,[ITEMS+i*64 for i in range(25)])
        self.make_list(LIST,[NEW+0x7000]);self.window(NEW+0x7000,NEW+0xf000,90)
        self.w(DEVICE+12,4,INVENTORY)
        for i in range(25):
            self.w(ITEMS+i*64+4,4,2);self.w(ITEMS+i*64+8,4,3);self.w(ITEMS+i*64+12,4,10+i);self.w(ITEMS+i*64+16,1,0)
    def snapshot(self):
        return (*super().snapshot(),tuple(self.read(ITEMS+i*64+12,4) for i in range(25)),tuple(self.values(ITEM_LIST)))
    def call(self,e,args):
        result=self.service(e,args)
        if e==0x3b4f50 and self.old_text:self.w(result+112,4,self.old_text)
        if e==0x1c64e0 and self.copy_refs is not None:
            token=self.read(args[0]&0xffffffff,4)
            if token:self.w(token-4,4,self.copy_refs)
        if e==0x236f80 and (args[1]&0xffffffff)==self.read(0x58b028,4):
            self.lookup_count+=1;result+=self.lookup_count*256
            if self.chip_mutation=='lookup':
                self.w(WINDOW+84,4,1);self.w(WINDOW+92,4,3)
                self.w(ITEM_LIST+0x4000,4,ITEMS+64)
        if e==0x38e060:
            if args[1]==0x51bdf0 and self.chip_mutation=='preview':self.w(ITEMS+12,4,99)
            if args[1]==0x51be00 and self.chip_mutation=='decline':self.w(WINDOW+48,4,1)
            if self.chip_mutation=='message':self.w(WINDOW+12,4,0x1b07000)
        if e==0x3a9220:
            self.property_count+=1
            if self.chip_mutation=='wallet' and self.property_count==2:
                self.w(DEVICE+0x100+12,4,9999);return DEVICE+0x100
        if e==0x301000 and self.chip_mutation=='entry':self.w(WINDOW+40,4,0x12345678)
        return result
    def service(self,e,args):
        counts={0x3f63c0:5,0x236f80:2,0x3a9340:2,0x43c720:1,0x43c7f0:3,ARROWS:3,PREV:1,NEXT:1,0x423700:1,
                0x3b51b0:1,0x3c87f0:1,0x448660:2,0x447cb0:3,0x447c10:3,0x2b90e0:1,0x2caa70:1,0x3f5f00:5,0x38d860:4}
        if e not in counts:return super().call(e,args)
        raw=list(args[:counts[e]]);v=[n&0xffffffff for n in raw];norm=list(raw)
        if e==ARROWS:
            norm[1:]=[tuple(self.read(p+i*4,4) for i in range(3)) for p in v[1:]]
        self.events.append((e,tuple(norm),self.snapshot()))
        if e==0x236f80:return STATUS if v[1]==self.read(0x58b028,4) else (0x1b00000 if v[1]==0x1234 else 0x1b01000)
        if e==0x3a9340:assert v[1]==0x51b528;return DEVICE
        if e==0x43c720:return self.rows
        if e==PREV:return self.prev
        if e==NEXT:return self.next
        if e==0x423700:return self.can_page
        if e==0x38d860:self.group=v[1];self.ints=[]
        if e==0x3b51b0:
            p=NEW+self.factory_count*256;self.factory_count+=1;self.window(p,p+0x8000,20+self.factory_count);self.w(p+4,4,self.created_refs);return p
        if e==0x3c87f0:self.w(CLONE+4,4,self.created_refs);return CLONE
        if e==0x448660:self.w(v[0]+12,4,v[1])
        if e==0x447cb0:return 0x51b590
        if e==0x447c10:
            if v[2]==0x51be38:return self.cost&MASK
            key=next((k for k,p in self.intern_map.items() if p==v[2]),v[2])
            assert key in STAT_KEYS,hex(key)
            return (self.delta if STAT_KEYS.index(key)==self.stat else 0)&MASK
        if e in (0x2b90e0,0x2caa70):
            p=STRINGS if e==0x2b90e0 else INTS;self.make_list(p,[]);self.w(p+4,4,self.created_refs);return p
        return 0


def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();native=ChipWorld(image);errors=[];cases=0;covered=set()
    @CALL
    def call(_,e,args):
        try:
            if e==COUNT and e in native.descend:return view(C.byref(api),e,args,native.frame)
            if e==BIND and e in native.descend:return tree(C.byref(api),e,args)
            return native.call(e,args)&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-chip-controller-') as td:
        so=Path(td)/'chip.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in ('chip-controller.c','chip-list-view.c','window-tree.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));view=lib.dw4_chip_list_view;tree=lib.dw4_window_tree
        view.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];view.restype=C.c_uint64
        tree.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];tree.restype=C.c_uint64
        fn=lib.dw4_chip_controller;fn.argtypes=[C.POINTER(Api),C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        def compare(w):
            nonlocal cases
            w.events=[];errors.clear()
            for k,value in w.__dict__.items():
                if k not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image','frame'):
                    setattr(native,k,value.copy() if isinstance(value,(list,dict,set)) else value)
            w.frame=STACK-288;native.frame=SCRATCH+512
            for i in range(288):native.w(native.frame+i,1,w.read(w.frame+i,1))
            w.invoke(CHIP,WINDOW);fn(C.byref(api),(C.c_uint64*8)(WINDOW),native.frame)
            assert not errors,errors
            def ram(obj):return {p:v for p,v in obj.mem.items() if v and not STACK-0x10000<=p<STACK+64 and not SCRATCH<=p<SCRATCH+0x10000}
            er,ar=ram(w),ram(native)
            assert er==ar,('RAM',cases,[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            if w.events!=native.events:
                i=next((i for i,(x,y) in enumerate(zip(w.events,native.events)) if x!=y),min(len(w.events),len(native.events)))
                raise AssertionError(('event',cases,i,w.events[i:i+1],native.events[i:i+1]))
            cases+=1;covered.update(w.covered)
        for primary,phase,sub in itertools.product(range(5),range(13),range(4)):
            w=ChipWorld(image);w.w(WINDOW+28,4,primary);w.w(WINDOW+32,4,phase);w.w(WINDOW+36,4,sub);compare(w)
        for phase,ret,changed in itertools.product((1,2),(-1,0,1,11),(False,True)):
            w=ChipWorld(image);w.w(WINDOW+32,4,phase);w.w(WINDOW+48,4,ret);w.w(WINDOW+80,4,0 if changed else 1);compare(w)
        for cost,balance,player in itertools.product((-1,0,1,100,1001,-2,0x100000064),(0,99,100,1000,0xffffffff),range(4)):
            w=ChipWorld(image);w.cost=cost;w.w(WINDOW+32,4,3);w.w(WINDOW+20,4,player);w.w(w.prop(player,0x51b440)+12,4,balance);compare(w)
        for stat,delta,equipped,flag in itertools.product(range(-1,12),(0,5,0x100000000,-1),(0,1),(0,1)):
            w=ChipWorld(image);w.stat=stat;w.delta=delta;w.w(WINDOW+32,4,4);w.w(ITEMS+16,1,equipped);w.w(0x554c14,1,flag);compare(w)
        for ret,player,cost in itertools.product((-1,0,1),range(4),(0,100,1001,-1)):
            w=ChipWorld(image);w.cost=cost;w.w(WINDOW+32,4,4);w.w(WINDOW+36,4,2);w.w(WINDOW+80,4,0);w.w(WINDOW+48,4,ret);w.w(WINDOW+20,4,player);compare(w)
            assert w.read(ITEMS+12,4)==(11 if ret==0 else 10)
            assert w.read(w.prop(player,0x51b440)+12,4)==((1000-cost)&0xffffffff if ret==0 else 1000)
        for n in (0,1,7,8,9,25):
            w=ChipWorld(image);w.w(WINDOW+32,4,0);w.w(INVENTORY+8,4,n)
            for i in range(25):w.w(ITEMS+i*64+8,4,3 if i%2 else 2)
            compare(w)
        for phase,sub,ret,flag in itertools.product((4,10,11),(0,1,2),(-1,0,1),(0,1)):
            w=ChipWorld(image);w.w(WINDOW+32,4,phase);w.w(WINDOW+36,4,sub);w.w(WINDOW+80,4,0);w.w(WINDOW+48,4,ret);w.w(0x554c14,1,flag);compare(w)
        for prev,nxt,can,typ,box in itertools.product((0,1),(0,1),(0,1),(0,1),(0,1)):
            w=ChipWorld(image);w.prev=prev;w.next=nxt;w.can_page=can;w.lua_type=typ
            if not box:w.w(w.read(LIST+16,4),4,0)
            compare(w)
        for result in (0,1,256,0x100000000):
            w=ChipWorld(image);w.w(WINDOW+28,4,3);w.close_result=result;compare(w)
        for phase,pool,allocation,refs,mutation in itertools.product((0,4,10,11),(False,True),(False,True),(0,1,0x800001),('string_temp',None)):
            w=ChipWorld(image);w.w(WINDOW+28,4,0 if phase==0 else 1);w.w(WINDOW+32,4,phase);w.w(WINDOW+36,4,0);w.w(0x586f20,4,0 if not pool else 0x1e00000);w.allocation=allocation;w.created_refs=refs;w.xmutation=mutation
            for i in range(25):w.w(ITEMS+i*64+4,4,refs)
            compare(w)
        # Persistent controller calls: quote, notice completion, confirmation,
        # then a fresh wallet and price at commit, followed by selection rebuild.
        for equipped,accept,player in itertools.product((0,1),(False,True),range(4)):
            w=ChipWorld(image);w.w(WINDOW+32,4,3);w.w(WINDOW+20,4,player);w.w(ITEMS+16,1,equipped)
            compare(w);assert w.read(WINDOW+32,4)==4
            compare(w);assert w.read(ITEMS+12,4)==10 and w.read(w.prop(player,0x51b440)+12,4)==1000
            w.w(LIST+8,4,w.read(LIST+8,4)-1);compare(w);assert w.read(WINDOW+36,4)==2
            w.w(LIST+8,4,w.read(LIST+8,4)-1);w.w(WINDOW+48,4,0 if accept else 1)
            w.cost=37;w.w(w.prop(player,0x51b440)+12,4,500);compare(w)
            assert w.read(ITEMS+12,4)==(11 if accept else 10)
            assert w.read(w.prop(player,0x51b440)+12,4)==(463 if accept else 500)
            compare(w);assert w.read(WINDOW+32,4)==1
        for phase,sub,mutation in itertools.product((0,3,4,10,11),(0,2),('lookup','preview','decline','wallet','message','entry')):
            w=ChipWorld(image);w.chip_mutation=mutation;w.w(WINDOW+32,4,phase);w.w(WINDOW+36,4,sub);w.w(WINDOW+80,4,0);w.w(ITEMS+16,1,1);compare(w)
        for n,flag,refs in itertools.product((0,1,7,8,9,25),(0,1),(0,1,0x800001)):
            w=ChipWorld(image);w.w(WINDOW+32,4,0);w.w(ITEM_LIST+8,4,n);w.w(0x554c14,1,flag);w.created_refs=refs;compare(w)
        for phase,sub,refs in itertools.product((4,10),(0,1),(0,1,2)):
            w=ChipWorld(image);w.w(WINDOW+32,4,phase);w.w(WINDOW+36,4,sub);w.w(WINDOW+80,4,0);w.created_refs=refs
            w.old_text=0x1d13100;w.w(w.old_text-8,4,0x1e00000);w.w(w.old_text-4,4,refs);w.copy_refs=refs;compare(w)
        for n,page in itertools.product((1,11,12,13,24,25),(0,1,2)):
            w=ChipWorld(image);w.descend.update((COUNT,BIND));w.w(WINDOW+32,4,0);w.w(INVENTORY+8,4,n);w.w(WINDOW+84,4,page);compare(w)
            child=w.values(LIST)[-1]
            assert w.read(child+84,4)==max(1,min(12,(n-page*12)&0xffffffff if n-page*12>=0 else n-page*12))
        for phase in (0,4):
            w=ChipWorld(image);w.w(WINDOW+28,4,0 if phase==0 else 1);w.w(WINDOW+32,4,phase);w.xmutation='drop_pool';w.w(0x586f20,4,0);compare(w)
        for rec,sub in itertools.product((0x7fffffff,0xffffffff),(0,2)):
            w=ChipWorld(image);w.w(WINDOW+32,4,4);w.w(WINDOW+36,4,sub);w.w(WINDOW+80,4,0);w.w(ITEMS+12,4,rec);w.w(ITEMS+16,1,1);compare(w)
            assert w.read(ITEMS+12,4)==(((rec+1)&0xffffffff) if sub==2 else rec)
        expected=set(range(CHIP,CHIP+7232,4))
        literal_null=(0x43ab48,0x43abe0,0x43ac78,0x43ad10,0x43b7e4,0x43b880,0x43b918,0x43b9b0,0x43ba48,0x43bae0,0x43bb78,0x43bc10,0x43bca8,0x43bd40,0x43bdd8,0x43be70)
        dead={p+d for p in literal_null for d in (0,4)}
        padding={0x43ab34,0x43b26c,0x43b2ec,0x43b31c,0x43b364,0x43b3f4,0x43b414,0x43b4d4,0x43b4fc,0x43b7ec,0x43c024,0x43c2ec,0x43c434,0x43c6dc,0x43c71c}
        for p in literal_null:
            # LUI v0 + ADDIU v0 gives a non-null literal. BNE takes its
            # target before the delay slot clears v0; fallthrough is dead.
            hi,lo,branch=(w.read(p+d,4) for d in (-16,-12,-8))
            assert hi>>16==0x3c02 and lo>>16==0x2442 and branch>>16==0x1440
            literal=((hi&0xffff)<<16)+((lo&0xffff)-0x10000 if lo&0x8000 else lo&0xffff)
            assert literal&0xffffffff and w.read(p,4)>>16==0x1000
        assert all(w.read(p,4)==0 for p in padding)
        assert expected-covered==padding|dead,sorted(hex(p) for p in expected-covered-padding-dead)
        assert len(expected&covered)==1761
        print(f'Chip controller: {cases} RAM/ordered-call cases; 1761/1808 controller words executed, 15 padding and 32 statically dead words checked; services remain controlled')

if __name__=='__main__':main()
