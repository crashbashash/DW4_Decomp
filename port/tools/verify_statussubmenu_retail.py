#!/usr/bin/env python3
"""Retail equipment/folder/skill orchestration with explicit controlled view leaves."""
from native_shared import build_shared
import argparse
import ctypes as C
import itertools
from pathlib import Path
import subprocess
import tempfile
from verify_statusctrl_retail import Retail as RootRetail, State, NODE, CHILDREN, OFF, verify_factory_classes
from verify_scriptservices_retail import BASE, ROOT

class Submenu(C.Structure):
    _fields_=[('window',State)]+[(n,C.c_int32) for n in ('mode','page','pages','offset')]
IO=C.CFUNCTYPE(C.c_int,C.c_void_p,C.POINTER(Submenu),C.c_int,C.c_char_p,C.c_char_p,C.c_int32)
CREATE,COUNT,MODEL,SCRIPT,CLEAR_MESSAGE,CLOSE_MODELS,CLEAR_TEXT,CLOSE_CHILDREN,FINISHED,FIND,READY,SELECT_CLOSE,RESTART,RESET,SKILL_LIST,SETUP,REFRESH,TOP,NEXT,PREVIOUS,REPAGE,COLORS=range(22)
CTORS={0x3b3900:'BAND',0x3b3530:'TITLE',0x3b5530:'MENU',0x3ba900:'POWER',0x3ba760:'MAIN',0x3ba260:'SUB',0x3baf10:'DEVICE',0x3b8f50:'DEVICE_DETAIL',0x3b9db0:'FLAG',0x3b9a50:'DISK',0x3b97d0:'BANK'}
SELECTOR=BASE+0x220000
class Retail(RootRetail):
    def call(self,e,a):
        a=[v&0xffffffff for v in a]
        if e in CTORS:
            p=BASE+0x200000+len(self.values(CHILDREN))*0x100
            self.w(p+4,4,1000);self.pending=(CTORS[e],p);return p
        if e==0x3f63c0:
            kind,p=self.pending;value=a[4]
            key=None
            if kind=='TITLE':key='FOLDER_TITLE' if self.entry==0x4196c0 else 'EQUIP_TITLE'
            elif kind!='MENU':key=kind
            if kind=='POWER':value=3
            self.events.append((CREATE,None,key,C.c_int32(value).value));return 0
        if e==0x3f5920:self.events.append((SCRIPT,'txt_status.lua',None,a[2]));return 0
        if e==0x3f5410:return 0 # initial blank message owned by the created selector
        if e in (0x3f5f80,0x3f5a40,0x3f6350):
            op={0x3f5f80:CLOSE_MODELS,0x3f5a40:CLEAR_TEXT,0x3f6350:CLOSE_CHILDREN}[e]
            self.events.append((op,None,None,0));return 0
        if e==0x3f6090:self.events.append((FINISHED,None,None,0));return self.query
        if e==0x300cd0:return int(self.has_selector and (a[0]==SELECTOR or (getattr(self,'pending',(None,None))[0]=='DEVICE' and a[0]==self.pending[1])))
        if e==0x38e060:
            key=self.string(a[1])
            if self.category=='MODELCTRL':self.events.append((MODEL,self.name,key+'/'+self.value,0))
            elif self.category=='TEXTCTL':self.events.append((CLEAR_MESSAGE,self.parts[0],self.parts[1],0))
            return 0
        if e==0x38e5d0:self.category=self.string(a[1]);self.name=None;self.value=None;self.parts=[];return 0
        if e==0x38f830:
            val=self.string(a[1]);self.parts.append(val)
            if self.name is None:self.name=val
            else:self.value=val
            return 0
        if e==0x3f5f00:self.events.append((MODEL,self.string(a[1]),'GENERATE/'+self.string(a[3]),0));return 0
        if e==0x3f5f40:self.events.append((MODEL,self.string(a[1]),self.string(a[3]),0));return 0
        if e==0x443110:self.events.append((SKILL_LIST,None,None,0));return 0
        if e==0x420230:self.events.append((REFRESH,None,None,a[1]));return 0
        return super().call(e,a)
    def tick_sub(self,entry,s,count,q,has_selector,ready):
        self.entry=entry;self.events=[];self.query=q;self.has_selector=has_selector;self.selected=s.window.selection
        self.category=self.name=self.value=None;self.parts=[]
        for off,(key,_) in zip(OFF,State._fields_):self.w(NODE+off,1 if off==24 else 4,getattr(s.window,key))
        self.w(NODE+44,4,s.mode if entry!=0x41f190 else 0)
        if entry==0x41f190:
            for off,v in zip((84,88,92,96),(s.page,s.pages,s.offset,s.mode)):self.w(NODE+off,4,v)
            self.w(NODE+100,4,BASE+0x230000);self.w(BASE+0x23001c,4,BASE+0x230100);self.list(BASE+0x230100,list(range(10)))
        self.list(CHILDREN,[SELECTOR]+[BASE+0x210000+i*0x100 for i in range(count-1)] if count else [])
        self.w(SELECTOR+28,4,1);self.w(SELECTOR+32,4,2 if ready else 0);self.w(SELECTOR+36,4,7);self.w(SELECTOR+40,4,8)
        for off in (60,64,68,72,76):self.w(NODE+off,4,BASE+0x240000+off*0x100);self.list(BASE+0x240000+off*0x100,[])
        self.invoke(entry,NODE)
        return [C.c_int32(self.read(NODE+off,1 if off==24 else 4)).value for off in OFF]

class NavigationRetail(Retail):
    def call(self,e,a):
        if e==0x423700:return self.query # recovered ready helper, not raw ISFO2TOP
        if e in (0x40dbf0,0x40dd30):
            op=PREVIOUS if e==0x40dbf0 else NEXT
            self.events.append((op,None,None,0))
            page=self.read(NODE+84,4)
            change=self.left and page>0 if op==PREVIOUS else self.right and page<1
            if change:self.w(NODE+84,4,page+(-1 if op==PREVIOUS else 1))
            return int(change)
        return super().call(e,a)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT.parent.parent/'local/extracted/SLUS_208.36');args=p.parse_args()
    if not args.elf.exists():print('STATUS submenus: private ELF unavailable, skipped');return
    image=args.elf.read_bytes();w=Retail(image);total=0
    names=['Title02','Title04','Select01','PowerSocket','MainSlot','SubSlot','CtrlD0','SubMenu','CtrlFlag','CtrlDisk','CtrlBit']
    specs=[]
    for factory,name in zip(CTORS,names):
        jump=w.read(factory+12,4);assert jump>>26==3;getter=(jump&0x3ffffff)<<2
        hi,lo=w.read(getter+4,4),w.read(getter+16,4)
        assert hi>>26==15 and lo>>26==9
        register=((hi&0xffff)<<16)+C.c_int16(lo&0xffff).value
        specs.append((factory,register,getter,name))
    verify_factory_classes(image,specs)
    with tempfile.TemporaryDirectory() as tmp:
        so=Path(tmp)/'submenu.so';build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/statussubmenu.c'),str(ROOT/'src/menuwindow.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_statussubmenu_tick.argtypes=[C.POINTER(Submenu),C.c_int,IO,C.c_void_p]
        for kind,entry in ((6,0x40ee60),(7,0x4196c0),(8,0x41f190)):
            for state,sub,delay,count,q,selected,mode in itertools.product(range(4),range(6),range(5),[0,1,3,4],[0,1,256],[-1,0,1,2,3],[0,1]):
                # Skill page setup/data projection/navigation have separately controlled
                # owners. Exercise scalar page refresh/return without the setup leaf.
                if kind==8 and sub==3 and (delay==0 or (selected!=-1 and count==4)):continue
                s=Submenu(State(1,state,sub,delay,2,selected,4,1),mode,0,1,0)
                expected=w.tick_sub(entry,s,count,q,True,True);events=[];native_count=count;found=count>0;ready=count>0
                @IO
                def io(user,ptr,op,name,key,value):
                    nonlocal native_count,found,ready
                    name=name.decode() if name else None;key=key.decode() if key else None
                    if op==COUNT:return native_count
                    if op==FIND:return int(found)
                    if op==READY:return int(ready)
                    if op in (SELECT_CLOSE,RESTART,RESET):return 0
                    if op==COLORS:
                        events.extend((CLEAR_MESSAGE,'STWINFONT14',f'font{i:03}',0) for i in range(value));return 0
                    events.append((op,name,key,value))
                    if op==CREATE:
                        native_count+=1
                        if key=='DEVICE' and not found:found=True;ready=False
                    if op==SKILL_LIST:return 10
                    return q if op in (MODEL,FINISHED) else 0
                rc=lib.dw4_statussubmenu_tick(C.byref(s),kind,io,None)
                got=[getattr(s.window,n) for n,_ in State._fields_]
                if kind==8:got[-1]=s.page
                assert rc==0 and got==expected,(kind,state,sub,delay,count,q,selected,mode,got,expected)
                assert events==w.events,(kind,state,sub,delay,count,q,selected,mode,events,w.events)
                total+=1
        nav=NavigationRetail(args.elf.read_bytes());navigation=0
        nav.w(NODE,4,0x53ec80) # original skill vtable pointer, including RTTI header
        for page,selected,ready,left,right in itertools.product(range(2),range(2),range(2),range(2),range(2)):
            s=Submenu(State(1,1,3,2,selected,selected,1,0),0,page,2,0)
            nav.left=left;nav.right=right
            expected=nav.tick_sub(0x41f190,s,1,ready,True,False);events=[];repage=False
            @IO
            def io(user,ptr,op,name,key,value):
                nonlocal repage
                c=ptr.contents
                if op==COUNT:return 1
                if op==FIND:return 1
                if op==TOP:return ready
                if op in (PREVIOUS,NEXT):
                    events.append((op,None,None,0))
                    change=left and c.page>0 if op==PREVIOUS else right and c.page<1
                    if change:c.page+=-1 if op==PREVIOUS else 1
                    return int(change)
                if op==REPAGE:repage=True;return 0
                if op==REFRESH:events.append((op,None,None,value));return 0
                raise AssertionError(op)
            assert lib.dw4_statussubmenu_tick(C.byref(s),8,io,None)==0
            got=[getattr(s.window,n) for n,_ in State._fields_];got[-1]=s.page
            assert got==expected and events==nav.events,(page,selected,ready,left,right,got,expected,events,nav.events)
            assert repage==(nav.read(SELECTOR+28,4)==4)
            if repage:assert nav.read(SELECTOR+84,4)==(2 if s.page else 8)
            navigation+=1
        print(f'STATUS submenus: {total} equipment/folder/skill scalar states/traces and {navigation} skill paging/restart states match retail instructions; virtual input leaves controlled')
if __name__=='__main__':main()
