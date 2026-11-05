#!/usr/bin/env python3
"""Retail DEVICE row decisions and controller states with controlled service leaves."""
from native_shared import build_shared
import ctypes as C
import itertools
from pathlib import Path
import subprocess
import tempfile
from verify_statusctrl_retail import Retail as RootRetail, State, OFF, NODE, CHILDREN, PARENT
from verify_scriptservices_retail import World, BASE, ROOT

ITEMS, KINDS, FLAGS, RECORD = [BASE+0x260000+i*0x100 for i in range(4)]
SELECTOR = BASE+0x270000
class Item(C.Structure):
    _fields_ = [(name,C.c_int32) for name in ('kind','record','equipped','revision','pocket')]
class Filter(C.Structure):
    _fields_ = [('kinds',C.c_int32*4),('nkinds',C.c_int32),('ab_type',C.c_int32)]+[
        (name,C.c_uint8) for name in ('equip_disable','unknown_enable','unknown_disable')]
class Rows(C.Structure):
    _fields_ = [(name,C.c_int32) for name in ('pages','rows','count')]+[('enabled',C.c_uint8*12)]
ATTRIBUTE = C.CFUNCTYPE(C.c_int,C.c_void_p,C.POINTER(Item),C.c_char_p,C.POINTER(C.c_int32))
class Device(C.Structure):
    _fields_ = [('window',State)]+[(name,C.c_int32) for name in ('page','pages','row','auto_close')]
IO = C.CFUNCTYPE(C.c_int,C.c_void_p,C.POINTER(Device),C.c_int,C.c_int32)
INIT,COUNT,REFRESH,TOP,PREVIOUS,NEXT,REPAGE,INVCOUNT,RESELECT,PUBLISH,CLOSEMODELS,CLEARTEXT,CLOSECHILDREN,COLORS,FINISHED = range(15)

class DecideRetail(World):
    def string(self,p):
        p &= 0xffffffff
        if not p:return None
        out=[]
        while self.read(p,1):out.append(self.read(p,1));p+=1
        return bytes(out).decode('ascii')
    def call(self,e,a):
        if e in (0x38e5d0,0x38f250,0x38e060):return 0
        if e==0x38f800:return RECORD
        if e==0x3a9340:return RECORD+0x40
        if e==0x236f80:return RECORD+0x80
        if e==0x447c60:
            index=(a[0]-BASE-0x280000)//32
            return self.attributes[index][self.string(a[2])]
        return super().call(e,a)
    def decide(self,items,page,f,attributes):
        self.attributes=attributes
        self.w(RECORD+0x4c,4,ITEMS)
        self.list(ITEMS,[BASE+0x280000+i*32 for i in range(len(items))])
        for j,item in enumerate(items):
            for off,value in zip((8,12,16,20,24),item):self.w(BASE+0x280000+j*32+off,4,value)
        for off,value in ((84,page),(96,0),(100,KINDS),(104,f.ab_type),(112,FLAGS)):
            self.w(NODE+off,4,value)
        for off,key in ((108,'equip_disable'),(109,'unknown_enable'),(110,'unknown_disable')):
            self.w(NODE+off,1,getattr(f,key))
        self.list(KINDS,list(f.kinds)[:f.nkinds]);self.list(FLAGS,[],1)
        rows=self.invoke(0x4191f0,NODE);count=self.read(FLAGS+8,4)
        flags=[self.read(self.read(FLAGS+16,4)+i,1) for i in range(count)]
        return self.read(NODE+88,4),rows,count,flags

class ControllerRetail(RootRetail):
    def call(self,e,a):
        a=[x&0xffffffff for x in a]
        if e==0x3b51b0:
            self.w(SELECTOR+4,4,1000)
            if self.initial:self.events.append((INIT,0))
            else:self.events.append((RESELECT,0))
            return SELECTOR
        if e==0x3f63c0:return 0
        if e==0x4191f0:return 12 # controlled row/decision helper (separate oracle)
        if e==0x423700:return self.ready
        if e in (0x40dbf0,0x40dd30):
            op=PREVIOUS if e==0x40dbf0 else NEXT
            self.events.append((op,0));page=self.read(NODE+84,4)
            change=self.left and page>0 if op==PREVIOUS else self.right and page<1
            if change:self.w(NODE+84,4,page+(-1 if op==PREVIOUS else 1))
            return int(change)
        if e==0x418ac0:self.events.append((REFRESH,a[1]+2*a[2]));return 0
        if e in (0x3f5f80,0x3f5a40,0x3f6350,0x3f6090):
            op={0x3f5f80:CLOSEMODELS,0x3f5a40:CLEARTEXT,0x3f6350:CLOSECHILDREN,0x3f6090:FINISHED}[e]
            self.events.append((op,0));return self.query if op==FINISHED else 0
        if e in (0x1ca620,0x3f5920,0x3f5410,0x3f5f00,0x38e5f0,0x38e5d0,0x38f830,0x38f250,0x38e060,0x40dae0):return 0
        if e==0x38f800:return RECORD
        if e==0x3a9340:return RECORD+0x40
        return super().call(e,a)
    def tick(self,s,count,inventory,ready,left,right,finished):
        self.events=[];self.ready=ready;self.left=left;self.right=right;self.query=finished;self.initial=s.window.state==0
        for off,(key,_) in zip(OFF,State._fields_):self.w(NODE+off,1 if off==24 else 4,getattr(s.window,key))
        for off,value in ((84,s.page),(88,s.pages),(92,s.row),(96,0),(100,KINDS),(112,FLAGS)):
            self.w(NODE+off,4,value)
        self.w(NODE+111,1,s.auto_close);self.w(NODE,4,BASE+0x290000)
        for off,entry in ((96,0x40dae0),(100,0x40dbf0),(104,0x40dd30)):self.w(BASE+0x290000+off,4,entry)
        for off in (60,64,68,72,76):self.w(NODE+off,4,BASE+0x2a0000+off*0x100)
        self.w(KINDS+4,4,1000);self.list(KINDS,[])
        self.list(CHILDREN,[SELECTOR]+[BASE+0x2b0000+i*0x100 for i in range(count-1)] if count else [])
        self.w(SELECTOR+108,4,0);self.w(SELECTOR+28,4,1)
        self.w(PARENT+48,4,0x12345678);self.w(RECORD+0x4c,4,ITEMS);self.list(ITEMS,list(range(inventory)))
        self.invoke(0x418090,NODE)
        fields=[C.c_int32(self.read(NODE+off,1 if off==24 else 4)).value for off in OFF[:7]]
        fields += [C.c_int32(self.read(NODE+off,4)).value for off in (84,88,92)]
        return fields,C.c_int32(self.read(PARENT+48,4)).value

class HoverRetail(RootRetail):
    def call(self,e,a):
        if e==0x300cd0:return 1
        if e==0x236f80:return 0
        if e==BASE+0x310000:return 1 # controlled equipment eligibility
        if e==0x3c90f0:return BASE+0x2c0000
        if e==0x411950:self.assigned=True;return 0 # controlled staged assignment
        if e in (0x38d860,0x38e5d0,0x38f250):return 0
        if e==0x38e060:
            key=self.string(a[1])
            if key=='OFPREVIEW':self.off=True
            return 0
        return super().call(e,a)
    def hover(self,s,latch,enabled):
        self.descend={0x419680};self.assigned=self.off=False
        self.w(NODE+48,4,0);self.w(NODE+40,4,latch);self.w(NODE,4,BASE+0x320000)
        self.w(BASE+0x320080,4,BASE+0x310000)
        self.list(CHILDREN,[SELECTOR]);self.w(NODE+120,4,BASE+0x2d0000)
        self.list(BASE+0x2d0000,[BASE+0x330000+i*32 for i in range(36)])
        for i in range(36):
            self.w(BASE+0x330000+i*32+4,4,1000);self.w(BASE+0x330000+i*32+8,4,0)
        self.list(ITEMS,[BASE+0x330000]);self.list(BASE+0x2c0000,[]);self.w(BASE+0x2c0004,4,1000)
        for off,value in ((28,s.window.state),(32,s.window.sub),(48,s.window.selection),(84,s.page),(112,FLAGS)):
            self.w(SELECTOR+off,4,value)
        self.list(FLAGS,[enabled]*12,1)
        self.invoke(0x412600,NODE,ITEMS,0,0)
        return C.c_int32(self.read(NODE+40,4)).value,self.assigned,self.off

def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('STATUS DEVICE: private ELF unavailable, skipped');return
    with tempfile.TemporaryDirectory() as td:
        so=Path(td)/'device.so'
        build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/statusdevice.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so))
        lib.dw4_statusdevice_decide.argtypes=[C.POINTER(Item),C.c_size_t,C.c_int,C.POINTER(Filter),ATTRIBUTE,C.c_void_p,C.POINTER(Rows)]
        lib.dw4_statusdevice_tick.argtypes=[C.POINTER(Device),IO,C.c_void_p]
        lib.dw4_statusdevice_hover.argtypes=[C.POINTER(Device),C.POINTER(C.c_int32),C.POINTER(C.c_uint8),C.POINTER(C.c_int32)]
        w=DecideRetail(elf.read_bytes());decisions=0
        for count in (0,1,11,12,13,23,24,25,36):
            items=[(j%4,(276,31,44,0)[j%4] if j%3==0 else j%10,(0,1,256,257)[j%4],0,0) for j in range(count)]
            attributes=[{'WU':(0,1,257)[items[j][1]%3],'BLUEAB':(1,256,257)[items[j][1]%3]} for j in range(count)]
            @ATTRIBUTE
            def attribute(user,item,key,out):
                record=item.contents.record
                out[0]=((0,1,257) if key==b'WU' else (1,256,257))[record%3]
                return 0
            for page,kinds,ab_type,equip,enable,disable in itertools.product(range(max(1,(count+11)//12)),
                    ((),(0,),(1,),(2,),(3,),(0,3),(3,0),(0,1,2,3)),(-1,0,1,2),range(2),range(2),range(2)):
                f=Filter((C.c_int32*4)(*kinds),len(kinds),ab_type,equip,enable,disable);out=Rows()
                expected=w.decide(items,page,f,attributes)
                result=lib.dw4_statusdevice_decide((Item*count)(*[Item(*i) for i in items]),count,page,C.byref(f),attribute,None,C.byref(out))
                got=out.pages,out.rows,out.count,list(out.enabled)[:out.count]
                assert result==0 and got==expected,(count,page,kinds,ab_type,equip,enable,disable,result,got,expected)
                decisions+=1
        w=ControllerRetail(elf.read_bytes());states=0
        for state,sub,delay,selected,count,page,auto_close,ready,direction in itertools.product(
                range(4),range(3),range(2),(-1,0,1,11),(0,1),(0,1),range(2),range(2),range(4)):
            # Restart creates a new selector only after its old child was pruned.
            if state==1 and sub==2 and delay==1 and count:continue
            s=Device(State(1,state,sub,delay,0,selected,1,0),page,2,0,auto_close)
            expected,published=w.tick(s,count,12,ready,direction&1,direction&2,1)
            events=[];nc=count;result_selection=0x12345678;repage=False
            @IO
            def io(user,ptr,op,value):
                nonlocal nc,result_selection,repage
                c=ptr.contents
                if op==COUNT:return nc
                if op==TOP:return ready
                if op==INVCOUNT:return 12
                if op==PUBLISH:result_selection=value;return 0
                if op==COLORS:return 0 # controlled native text sink
                if op==REPAGE:repage=True;return 0
                events.append((op,value))
                if op in (INIT,RESELECT):nc+=1
                if op in (PREVIOUS,NEXT):
                    change=(direction&1 and c.page>0) if op==PREVIOUS else (direction&2 and c.page<1)
                    if change:c.page+=-1 if op==PREVIOUS else 1
                    return int(bool(change))
                return 1 if op==FINISHED else 0
            rc=lib.dw4_statusdevice_tick(C.byref(s),io,None)
            got=[getattr(s.window,n) for n,_ in State._fields_[:7]]+[s.page,s.pages,s.row]
            assert rc==0 and got==expected and result_selection==published,(state,sub,delay,selected,count,page,auto_close,ready,direction,got,expected,result_selection,published)
            assert events==w.events,(state,sub,delay,selected,count,page,events,w.events)
            if repage:assert w.read(SELECTOR+28,4)==4
            states+=1
        w=HoverRetail(elf.read_bytes());hovers=0
        for state,sub,selected,page,enabled,last in itertools.product(range(3),range(3),(-1,0,11),range(3),range(2),range(3)):
            s=Device(State(1,state,sub,0,0,selected,0,0),page,3,0,0)
            latch=(-1,page*12+selected,999)[last]
            expected=w.hover(s,latch,enabled);native_latch=C.c_int32(latch);index=C.c_int32(-1234)
            rc=lib.dw4_statusdevice_hover(C.byref(s),C.byref(native_latch),(C.c_uint8*12)(*[enabled]*12),C.byref(index))
            assert (native_latch.value,rc==0,rc==2)==expected,(state,sub,selected,page,enabled,latch,rc,index.value,expected)
            if rc in (0,2):assert index.value==page*12+selected
            hovers+=1
        print(f'STATUS DEVICE: {decisions} page/decision rows, {states} scalar publication/restart states and {hovers} inventory-preview gates match retail instructions; property/attribute/selector/resource/recalculation leaves controlled')
if __name__=='__main__':main()
