#!/usr/bin/env python3
"""Execute retail STATUS root/title/selection updates with controlled service leaves."""
from native_shared import build_shared
import argparse
import ctypes as C
import itertools
from pathlib import Path
import subprocess
import tempfile
from verify_scriptservices_retail import World, ROOT, BASE

NODE,CHILDREN,PARENT=BASE+0x180000,BASE+0x180200,BASE+0x180400
class State(C.Structure):
    _fields_=[(n,C.c_int32) for n in ('active','state','sub','delay','latch','selection','previous_count','last_selection')]
IO=C.CFUNCTYPE(C.c_int,C.c_void_p,C.c_int,C.c_char_p,C.c_char_p,C.c_int32)
CREATE,MODEL,LAYER,COUNT,CLOSE_CHILDREN,CLOSE_MODELS,CLEAR_TEXT,FINISHED,TEXT,INIT,GET,END,TOP,IS_TOP=range(14)
# Factory identity follows the registered metadata global used by 2fda40,
# not the preceding GetMetaObject symbol in address order.
CTORS={0x3b3c80:0,0x3b3ac0:1,0x3b3900:2,0x3b36f0:3,0x3b56f0:5,0x3bace0:6,0x3ba030:7,0x3b92b0:8}
OFF=[24,28,32,36,40,48,80,84]
def verify_factory_classes(image,specs=None):
    class Metadata(Retail):
        def call(self,e,a):
            a=[v&0xffffffff for v in a]
            if e in parents:return 0 # parent registration already available
            if e==0x2fe9c0:
                self.w(a[1],4,a[5]);return 0 # metadata token retains original class string
            if e in getters:return 0 # registration ran explicitly below
            if e==0x2fda40:
                self.allocated=self.string(a[0]);return NODE
            return super().call(e,a)
    if specs is None:specs=[(0x3b3c80,0x3b3db0,0x3b3d90,'Title00'),
           (0x3b3ac0,0x3b3bf0,0x3b3bd0,'Title01'),
           (0x3b3900,0x3b3a30,0x3b3a10,'Title02'),
           (0x3b36f0,0x3b3870,0x3b3850,'Title03'),
           (0x3b56f0,0x3b5820,0x3b5800,'Select00'),
           (0x3bace0,0x3bae10,0x3badf0,'CtrlEquip'),
           (0x3ba030,0x3ba160,0x3ba140,'CtrlFolder'),
           (0x3b92b0,0x3b9400,0x3b93e0,'CtrlSkill')]
    getters={s[2] for s in specs};w=Metadata(image)
    parents={(w.read(s[1]+8,4)&0x3ffffff)<<2 for s in specs}
    for factory,register,getter,name in specs:
        w.invoke(register);w.allocated=None;w.invoke(factory,0)
        assert w.allocated=='beNDMWStatus'+name,(hex(factory),w.allocated,name)
    print(f'STATUS factories: {len(specs)} original registration/factory class identities pass; metadata allocation leaves controlled')
class Retail(World):
    def __init__(self,image):
        super().__init__(image);self.descend=set();self.w(NODE+52,4,CHILDREN);self.w(NODE+56,4,PARENT)
    def string(self,p):
        p &= 0xffffffff
        if not p:return None
        chars=[]
        while self.read(p,1):chars.append(self.read(p,1));p+=1
        return bytes(chars).decode('ascii')
    def call(self,e,a):
        a=[v&0xffffffff for v in a]
        if e in (0x301000,0x2f88e0):return 0
        if e in CTORS:
            kind=CTORS[e];self.events.append((CREATE,None,None,kind))
            p=BASE+0x200000+len(self.values(CHILDREN))*0x100;self.w(p+4,4,1000);return p
        if e==0x3f63c0:return 0
        if e==0x38d860:self.category,self.name=self.string(a[1]),self.string(a[2]);self.value=None;return 0
        if e==0x38e5d0:self.category=self.string(a[1]);self.name=None;self.value=None;return 0
        if e==0x38f830:
            v=self.string(a[1]);
            if self.name is None:self.name=v
            else:self.value=v
            return 0
        if e==0x38e060:
            key=self.string(a[1])
            if self.category=='LAYERCTL':self.events.append((LAYER,self.name,self.value,0))
            elif self.category=='MODELCTRL':self.events.append((MODEL,self.name,key+'/'+self.value,0))
            return 0
        if e==0x38e5f0:
            self.category,self.name=self.string(a[1]),self.string(a[2]);key=self.string(a[4]);self.value=None
            if self.category=='MODELCTRL':self.events.append((MODEL,self.name,key,0))
            else:self.query_key=key
            return 0
        if e==0x38f220:return self.query
        if e==0x38f320:return self.selected & 0xffffffff
        if e==0x3f5410:self.events.append((TEXT,self.string(a[1]),self.string(a[3]),self.last));return 0
        if e in (0x3f5f80,0x3f5a40,0x3f6350):
            op={0x3f5f80:CLOSE_MODELS,0x3f5a40:CLEAR_TEXT,0x3f6350:CLOSE_CHILDREN}[e]
            self.events.append((op,None,None,0));return 0
        if e==0x3f6090:self.events.append((FINISHED,None,None,0));return self.query
        if e==0x3f5f00:
            self.events.append((MODEL,self.string(a[1]),'GENERATE/'+self.string(a[3]),0));return 0
        if e==BASE+0x300000:self.events.append((INIT,'i_stcursor02','GENERATE',self.last));return 0
        if e==0x423700:self.events.append((IS_TOP,'i_stcursor02','ISFO2TOP',0));return self.query
        if e in (0x38f250,0x38f4b0):return 0
        return super().call(e,a)
    def tick(self,entry,s,count,q,selected):
        self.events=[];self.query=q;self.selected=selected;self.last=s.last_selection
        self.category=self.name=self.value=None
        for off,(key,_) in zip(OFF,State._fields_):self.w(NODE+off,1 if off==24 else 4,getattr(s,key))
        self.list(CHILDREN,[BASE+0x200000+i*0x100 for i in range(count)])
        for p in self.values(CHILDREN):
            for off,v in [(24,1),(28,0),(32,7),(36,8),(40,9)]:self.w(p+off,4,v)
        self.w(PARENT+48,4,0)
        self.w(NODE,4,BASE+0x180600);self.w(BASE+0x180600+96,4,0x424230 if entry==0x424160 else BASE+0x300000)
        # WindowSelect's initialized string/list fields and selector context.
        self.w(NODE+80,4,self.token('i_stcursor02') if entry==0x4233f0 else s.previous_count)
        if entry==0x4233f0:self.w(NODE+100,4,s.last_selection)
        self.invoke(entry,NODE)
        result=[C.c_int32(self.read(NODE+off,1 if off==24 else 4)).value for off in OFF]
        return result

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT.parent.parent / 'local/extracted/SLUS_208.36');args=p.parse_args()
    if not args.elf.exists():print('STATUS retail: private ELF unavailable, skipped');return
    image=args.elf.read_bytes();verify_factory_classes(image);w=Retail(image);total=0
    with tempfile.TemporaryDirectory() as tmp:
        so=Path(tmp)/'status.so';build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/statusctrl.c'),str(ROOT/'src/menuwindow.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_statusctrl_tick.argtypes=[C.POINTER(State),IO,C.c_void_p]
        lib.dw4_statustitle_tick.argtypes=[C.POINTER(State),IO,C.c_void_p]
        lib.dw4_statusselect_tick.argtypes=[C.POINTER(State),C.POINTER(State),IO,C.c_void_p]
        for state,sub,delay,count,q,selection in itertools.product(range(5),range(6),range(4),[0,1,5,6],[0,1,2,256],[-1,0,1,2,3]):
            s=State(1,state,sub,delay,9,selection,6,2)
            expected=w.tick(0x40de80,s,count,q,selection);events=[];native_count=count
            @IO
            def io(user,op,name,key,value):
                nonlocal native_count
                name=name.decode() if name else None;key=key.decode() if key else None
                if op==COUNT:return native_count
                if op==CLOSE_CHILDREN and value==1:return 0 # direct inline close loop
                events.append((op,name,key,value))
                if op==CREATE:native_count+=1
                return q if op in (MODEL,FINISHED) else 0
            assert lib.dw4_statusctrl_tick(C.byref(s),io,None)==0
            got=[getattr(s,n) for n,_ in State._fields_]
            expected_events=w.events
            assert got==expected,(state,sub,delay,count,q,selection,got,expected)
            assert events==expected_events,(state,sub,delay,count,q,selection,events,expected_events)
            total+=1
        titles=0
        for state,q in itertools.product(range(5),[0,1,256]):
            s=State(1,state,7,8,9,-1,0,2);events=[]
            # Descend into concrete StatusTitle00 initializer.
            w.events=[];w.descend={0x424230};expected=w.tick(0x424160,s,0,q,0);w.descend=set()
            @IO
            def io(user,op,name,key,value):
                events.append((op,name.decode() if name else None,key.decode() if key else None,value));return q if op==FINISHED else 0
            assert lib.dw4_statustitle_tick(C.byref(s),io,None)==0
            assert [getattr(s,n) for n,_ in State._fields_]==expected
            assert events==w.events,(events,w.events)
            titles+=1
        # Selector base scalar update. Its initialization leaf is controlled;
        # SELECTCTRL itself has a separate 19,200-state retail comparison.
        selects=0
        for state,q,selected in itertools.product(range(6),[0,1,256],[-1,0,1,2]):
            s=State(1,state,7,8,9,-1,0,2);parent=State();expected=w.tick(0x4233f0,s,0,q,selected)
            @IO
            def io(user,op,name,key,value):return selected if op==GET else q if op in (END,IS_TOP,FINISHED) else 0
            assert lib.dw4_statusselect_tick(C.byref(s),C.byref(parent),io,None)==0
            assert [s.active,s.state,s.sub,s.delay,s.latch]==expected[:5],(state,q,selected,s.state,expected)
            assert parent.selection==C.c_int32(w.read(PARENT+48,4)).value
            selects+=1
        print(f'STATUS retail: {total} root states/traces, {titles} Title00 states/traces and {selects} selection states match retail instructions')
if __name__=='__main__':main()
