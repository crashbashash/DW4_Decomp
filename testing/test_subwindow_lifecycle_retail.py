#!/usr/bin/env python3
"""SUBWND lifecycle prefix vs original RAM and ordered calls for all11 modes.

Menu preparation/construction/initialization/tree update, messaging, allocator,
record lookups and destruction remain controlled leaves. This is recovery of
the manager, not implementation/acceptance of shop, lab, card or save gameplay.
"""
import ctypes as C
import itertools
import json
from pathlib import Path
import subprocess
import sys
import tempfile
from test_messenger_dispatch_retail import World,ROOT,Api,READ,WRITE,CALL,MASK,STACK

sys.path.insert(0,str(ROOT/'tools'))
import verify
ENTRIES=(0x3d58f0,0x3d5950,0x3d5960,0x3d59b0,0x3d9bd0,0x3d9c50,0x3d9cd0,0x3d9d50,0x3d9dd0)
OWNER,RAM,OLD,WINDOW,ALT,INFO,CONTEXT,ALTCTX,WRAPPER,PROP,FOLDERS,ALLOCATOR,SCRATCH=range(0x1800000,0x180d000,0x1000)
CTOR_STATUS,CTOR_SHOP,CTOR_LABO,CTOR_CARD=0x3bb1d0,0x3b8d90,0x3b7750,0x3b7eb0
CONSTRUCTORS={0:CTOR_STATUS,2:CTOR_LABO,10:CTOR_CARD}


class LifecycleWorld(World):
    def read(self,p,n):
        p&=0xffffffff
        return sum((self.mem[p+i] if p+i in self.mem else super(LifecycleWorld,self).read(p+i,1))<<(8*i) for i in range(n))
    def __init__(self,image):
        super().__init__(image);self.descend=set(ENTRIES);self.events=[]
        self.frame=STACK-80;self.group=0;self.args=[];self.player=0;self.mutation=None
        self.root_active=1;self.card_result=0;self.inject=None;self.changed=False;self.constructor_refs=1
        self.w(OWNER+12,4,0x18f0000);self.w(OWNER+20,4,CONTEXT);self.w(OWNER+24,4,INFO)
        self.w(OWNER+32,4,0);self.w(OWNER+36,4,0);self.w(OWNER+40,4,0);self.w(INFO+8,4,1)
        for off,value in ((20,1),(24,0),(28,7),(32,8),(36,9)):
            self.w(RAM+off,1 if off==20 else 4,value)
        self.w(0x554c14,1,1);self.w(0x587110,4,0x1234);self.w(0x589208,4,0x5678)
        self.w(0x58ac30,4,0x81234567);self.w(0x58b028,4,0x89abcdef)
        for p in (OLD,WINDOW,ALT):self.w(p+4,4,1);self.w(p+24,4,1)
        self.w(WRAPPER,4,OLD)
        for p in range(4):self.w(PROP+p*32+12,4,1)
    def call(self,e,args):
        counts={0x3d8740:2,0x38d820:3,0x38e5d0:2,0x38f830:2,0x38f250:2,
                0x38e060:2,0x38e670:3,0x38d470:2,0x38f800:2,0x3a9280:2,
                0x38f220:2,0x301000:1,0x2f88e0:1,CTOR_STATUS:1,CTOR_SHOP:1,
                CTOR_LABO:1,CTOR_CARD:1,0x3f63c0:5,0x3f6490:1,0x2ff820:1,
                0x100610:1,0x236f80:2,0x389ff0:3}
        assert e in counts,hex(e)
        raw=list(args[:counts[e]]);v=[x&0xffffffff for x in raw]
        snapshot=(self.read(OWNER+32,4),self.read(OWNER+40,4),self.read(RAM+20,1),
                  self.read(RAM+24,4),self.read(OLD+4,4),self.read(WINDOW+4,4),
                  self.read(self.frame+76,4))
        self.events.append((e,tuple(raw),snapshot))
        if e==0x38e5d0:self.group=v[1];self.args=[]
        if e in (0x38f830,0x38f250):self.args.append(raw[1])
        if e==0x38e060 and self.group==0x516848:
            if v[1]==0x516850:self.player=self.args[0]&0xffffffff
            if v[1]==0x516870 and self.mutation=='join_live' and self.player==0:
                self.w(PROP+32+12,4,256);self.w(PROP+64+12,4,257)
        if e==0x38f800:return FOLDERS+self.player*256
        if e==0x3a9280:
            assert v[0]==FOLDERS+self.player*256 and v[1]==0x516860
            return PROP+self.player*32
        if e==0x38f220:return self.card_result
        if e==0x301000:
            if self.inject=='object':self.w(self.frame+76,4,ALT)
            return ALLOCATOR
        if e==0x2f88e0:
            if self.inject=='fallback':self.w(self.frame+76,4,ALT)
            return ALLOCATOR+128
        if e in (CTOR_STATUS,CTOR_SHOP,CTOR_LABO,CTOR_CARD):
            self.w(WINDOW+4,4,self.constructor_refs);return WINDOW
        if e==0x236f80:return 0x18f1000
        if e==0x3f63c0:
            self.w(v[0]+24,4,1)
            if self.mutation=='initialize_mode':self.w(OWNER+40,4,10)
            if self.mutation=='initialize_temp':self.w(self.frame+76,4,ALT)
        if e==0x3f6490:
            self.w(v[0]+24,4,self.root_active)
            if self.mutation=='tick_state':self.w(RAM+24,4,0xffffffff)
            if self.mutation=='tick_replace':self.w(OWNER+32,4,ALT);self.w(ALT+24,4,self.root_active)
            if self.mutation=='tick_clear':self.w(OWNER+32,4,0)
        if e==0x3d8740:
            if self.mutation=='setup_mode':self.w(OWNER+40,4,2)
            if self.mutation=='setup_state':self.w(RAM+24,4,0x7fffffff)
        if e==0x38d820:self.w(v[1]+20,1,255)
        if e==0x2ff820 and self.mutation=='delete_root':self.w(OWNER+32,4,ALT)
        if e==0x38e060 and v[1]==0x5167a8 and self.mutation=='messenger':self.w(OWNER+20,4,ALTCTX)
        return 0


def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();native=LifecycleWorld(image)
    cases=0;errors=[];coverage=set();tested=set();depth=0
    @CALL
    def call(_,e,args):
        try:return invoke(e,args)&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-subwindow-lifecycle-') as td:
        so=Path(td)/'lifecycle.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/subwindow-lifecycle.c'),'-o',str(so)],check=True)
        fn=C.CDLL(str(so)).dw4_subwindow_lifecycle
        fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        def invoke(e,args):
            nonlocal depth
            if e not in ENTRIES:return native.call(e,args)&MASK
            depth+=1;previous=native.frame;native.frame=SCRATCH+depth*256
            try:return fn(C.byref(api),e,args,native.frame)
            finally:native.frame=previous;depth-=1
        def compare(w,entry,*args,result=False):
            nonlocal cases
            w.events=[];errors.clear()
            for key,value in w.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image','frame'):
                    setattr(native,key,value.copy() if isinstance(value,(list,dict,set)) else value)
            # Match the incoming private frame word, including stale storage on
            # later ticks. This is copied from input state, not retail output.
            native.w(SCRATCH+256+76,4,w.read(w.frame+76,4))
            expected=w.invoke(entry,*args)
            actual=invoke(entry,(C.c_uint64*8)(*[x&MASK for x in args]))
            assert not errors,errors
            if result:assert expected==actual,(hex(entry),hex(expected),hex(actual))
            def ram(obj):return {p:v for p,v in obj.mem.items() if v and not STACK-0x10000<=p<STACK+64 and not SCRATCH<=p<SCRATCH+0x10000}
            er,ar=ram(w),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            if w.events!=native.events:
                index=next((i for i,(x,y) in enumerate(zip(w.events,native.events)) if x!=y),min(len(w.events),len(native.events)))
                raise AssertionError((hex(entry),'event',index,w.events[index:index+1],native.events[index:index+1]))
            tested.add(entry);coverage.update(w.covered);cases+=1
        for entry in (0x3d5950,0x3d9dd0):compare(LifecycleWorld(image),entry,result=True)
        for count in (0,1,2,0xffffffff):
            w=LifecycleWorld(image);w.w(INFO+8,4,count);compare(w,0x3d5960,OWNER,RAM)
            assert w.read(RAM+20,1)==(0 if count==1 else 1)
        for root,refs in itertools.product((0,OLD),(0,1,2,0x800001,0xffffffff)):
            w=LifecycleWorld(image);w.w(OWNER+32,4,root);w.w(OLD+4,4,refs);compare(w,0x3d58f0,OWNER)
            assert w.read(OWNER+32,4)==0
        for mode,player,allocator,active in itertools.product(range(11),range(4),(0,1),(0,1)):
            w=LifecycleWorld(image);w.w(OWNER+36,4,player);w.w(OWNER+40,4,mode);w.w(0x554c14,1,allocator);w.root_active=active
            compare(w,0x3d59b0,OWNER,RAM)
            constructors=[e for e in w.events if e[0] in (CTOR_STATUS,CTOR_SHOP,CTOR_LABO,CTOR_CARD)]
            assert len(constructors)==1 and constructors[0][0]==CONSTRUCTORS.get(mode,CTOR_SHOP)
            assert constructors[0][1]==(ALLOCATOR if allocator else ALLOCATOR+128,)
            assert w.read(WINDOW+44,4)==mode
            assert w.read(RAM+20,1)==active
        for state,mode,mask,card in itertools.product((1,2,0xffffffff),(0,2,10),range(16),(0,1,256,257)):
            w=LifecycleWorld(image);w.w(RAM+24,4,state);w.w(OWNER+32,4,WINDOW);w.w(OWNER+40,4,mode);w.root_active=0;w.card_result=card
            for p in range(4):w.w(PROP+p*32+12,4,257 if mask>>p&1 else 256)
            compare(w,0x3d59b0,OWNER,RAM)
            assert not w.read(RAM+20,1) and not w.read(OWNER+32,4)
        for mode,inject,fallback in itertools.product(range(11),('object','fallback'),(0,1)):
            w=LifecycleWorld(image);w.w(OWNER+40,4,mode);w.inject=inject;w.w(0x554c14,1,fallback)
            compare(w,0x3d59b0,OWNER,RAM)
        for mode in range(11):
            w=LifecycleWorld(image);w.w(OWNER+40,4,mode);w.constructor_refs=0
            compare(w,0x3d59b0,OWNER,RAM)
        for mutation in ('setup_mode','setup_state','initialize_mode','initialize_temp','tick_state','tick_replace','tick_clear','messenger','join_live','delete_root'):
            for mode in (0,3,10):
                w=LifecycleWorld(image);w.mutation=mutation;w.w(OWNER+40,4,mode);w.w(OWNER+32,4,OLD);w.root_active=0
                compare(w,0x3d59b0,OWNER,RAM)
        for entry,ptr,refs,flags in itertools.product(ENTRIES[4:8],(0,WRAPPER),(1,2,0x800001,0xffffffff),(0,1,0xffff,0x10001,0x8000)):
            w=LifecycleWorld(image);w.w(OLD+4,4,refs);compare(w,entry,ptr,flags,result=True)
        w=LifecycleWorld(image);w.w(RAM+20,1,0);compare(w,0x3d59b0,OWNER,RAM);assert not w.events
        for padding in (1,0xabcdef):
            w=LifecycleWorld(image);w.w(RAM+20,4,padding<<8)
            compare(w,0x3d59b0,OWNER,RAM);assert not w.events
        for mode,active in itertools.product((0,3,10),(256,257,255,0x80000000)):
            w=LifecycleWorld(image);w.w(RAM+24,4,1);w.w(OWNER+32,4,WINDOW);w.w(OWNER+40,4,mode);w.root_active=active
            compare(w,0x3d59b0,OWNER,RAM)
            assert w.read(RAM+20,1)==int(bool(active&255))
        # One persistent open/update/complete/clear sequence for every service mode.
        for mode in range(11):
            w=LifecycleWorld(image);w.w(OWNER+40,4,mode)
            compare(w,0x3d5960,OWNER,RAM);w.w(RAM+20,1,1)
            compare(w,0x3d59b0,OWNER,RAM);w.root_active=0
            compare(w,0x3d59b0,OWNER,RAM);compare(w,0x3d58f0,OWNER)
        assert tested==set(ENTRIES),sorted(hex(p) for p in set(ENTRIES)-tested)
        _,symbols=verify.load_symbols(str(ROOT/'config/SLUS-20836/symbols.txt'))
        assert symbols[0x3d59b0][1]==1832
        expected={p for entry in ENTRIES for p in range(entry,entry+symbols[entry][1],4)}
        missing=expected-coverage
        row=next(r for r in json.loads((ROOT/'data/function-extents.json').read_text()) if int(r['address'],0)==0x3d59b0)
        occupied={p for r in row['body_ranges'] for p in range(int(r['start'],0),int(r['end_exclusive'],0),4)}
        padding=set(range(0x3d59b0,0x3d60d8,4))-occupied
        assert padding=={0x3d59f4,0x3d5a5c,0x3d600c}
        assert all(verify.va_bytes(verify.read_elf(str(ROOT/'orig/SLUS-20836/SLUS_208.36')),p,4)==bytes(4) for p in padding)
        assert missing==padding,sorted(hex(p) for p in missing-padding)
        if '--show-gaps' in sys.argv:print('unexecuted:', ' '.join(hex(p) for p in sorted(missing)))
        print(f'SUBWND lifecycle: {cases} RAM/return/ordered-call cases across11 modes, {len(coverage)}/{len(expected)} instruction addresses; constructors/menu prep/tree/records remain leaves')


if __name__=='__main__':main()
