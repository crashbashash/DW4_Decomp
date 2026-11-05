#!/usr/bin/env python3
"""Shared equipment scalar branches against retail; virtual view/record leaves controlled."""
from native_shared import build_shared
import ctypes as C
import itertools
import subprocess
import tempfile
from pathlib import Path
from verify_statusctrl_retail import Retail, State, NODE, CHILDREN, PARENT, OFF
from verify_scriptservices_retail import BASE, ROOT

class Equip(C.Structure):
    _fields_=[('window',State)]+[(n,C.c_int32) for n in ('slot','slots','pocket','mode')]
IO=C.CFUNCTYPE(C.c_int,C.c_void_p,C.POINTER(Equip),C.c_int,C.c_int32)
COUNT,PREPARE,SELECTOR,CURSOR,BLANK,OFFPREVIEW,REFRESH,COLORS,HIDE,FIND,READY,CLOSE,RESTART,SWAP,SWAPPREVIEW,ERROR,SCRIPT,CLOSEMODELS,CLEARTEXT,CLOSECHILDREN,FINISHED,CLEARPOCKETS,PLAYERMODEL=range(23)
SELECT=BASE+0x210000
class Equipment(Retail):
    def call(self,e,a):
        a=[v&0xffffffff for v in a]
        if BASE+0x300000<=e<BASE+0x300100:
            slot=(e-BASE-0x300000)//4
            v=C.c_int32(a[1]).value if slot in (23,30,32,39) else 0
            self.events.append((100+slot,v));return self.query if slot==30 else 0
        if e==0x4115c0:self.events.append((CURSOR,C.c_int32(a[1]).value));return 0
        if e==0x411750:self.events.append((BLANK,0));return 0
        if e==0x411180:self.events.append((SWAPPREVIEW,0));return 0
        if e==0x3b51b0:
            self.events.append((SELECTOR,int(self.sub==3 and self.state==1)));self.w(SELECT+4,4,1000);return SELECT
        if e==0x3b4f50:self.events.append((ERROR,0));return BASE+0x220000
        if e==0x3f5920:self.events.append((SCRIPT,C.c_int32(a[2]).value));return 0
        if e==0x300cd0:return int(a[0]==SELECT)
        if e==0x3a9340:return BASE+0x230000 # record -> list
        if e==0x3a9310:return BASE+0x231000
        if e==0x1c64e0:self.w(a[0],4,self.token('player'));return 0
        if e==0x38f800:self.events.append((PREPARE,0));return BASE+0x232000
        if e==0x38e5f0:
            if self.string(a[4])=='GETPLAYER':self.events.append((PREPARE,0))
            elif self.string(a[1])=='PLAYERARMS':self.events.append((PLAYERMODEL,0))
            return 0
        if e==0x38e060:
            key=self.string(a[1])
            if key=='OFPREVIEW':self.events.append((OFFPREVIEW,0))
            elif key=='RECALCPLAYER':self.events.append((REFRESH,0))
            # UPDATE is part of REFRESH, except the duplicate after socket swap.
            elif key=='UPDATE' and self.sub==3:
                self.updates+=1
                if self.updates==2 or self.selected not in (0,1,2):self.events.append((REFRESH,1))
            return 0
        if e in (0x3f5f80,0x3f5a40,0x3f6350,0x3f6090):
            op={0x3f5f80:CLOSEMODELS,0x3f5a40:CLEARTEXT,0x3f6350:CLOSECHILDREN,0x3f6090:FINISHED}[e]
            self.events.append((op,0));return self.query if op==FINISHED else 0
        if e==0x2cb0d0:
            self.list(BASE+0x240000,[],1);self.w(BASE+0x240004,4,1000);return BASE+0x240000
        if e==0x2d6790:self.w(a[0]+8,4,a[1]);return 0
        return super().call(e,a)
    def tick_equipment(self,s,count,q,ready):
        self.events=[];self.query=q;self.selected=s.window.selection;self.sub=s.window.sub;self.state=s.window.state;self.updates=0
        for off,(key,_) in zip(OFF,State._fields_):self.w(NODE+off,1 if off==24 else 4,getattr(s.window,key))
        for off,v in [(84,s.slot),(88,s.slots),(92,s.pocket),(96,BASE+0x232000),(100,BASE+0x233000)]:self.w(NODE+off,4,v)
        self.w(PARENT+44,4,s.mode);self.w(PARENT+56,4,BASE+0x235000)
        self.w(NODE,4,BASE+0x236000)
        for slot in range(22,40):self.w(BASE+0x236000+(slot+2)*4,4,BASE+0x300000+slot*4)
        self.list(BASE+0x233000,[BASE+0x234000+i*0x100 for i in range(3)])
        for p in self.values(BASE+0x233000):self.w(p+4,4,1000)
        self.w(BASE+0x23000c,4,BASE+0x233000)
        self.list(CHILDREN,[SELECT]+[BASE+0x250000+i*0x100 for i in range(count-1)] if count else [])
        self.w(SELECT+28,4,1);self.w(SELECT+32,4,2 if ready else 1)
        self.invoke(0x40f720,NODE)
        return [C.c_int32(self.read(NODE+off,1 if off==24 else 4)).value for off in OFF[:7]]+[self.read(NODE+off,4) for off in (84,88,92)]

class Actions(C.Structure):
    _fields_=[('callno',C.c_int32),('rows',C.c_int32),('enabled',C.c_uint8*3)]
class Item(C.Structure):
    _fields_=[(n,C.c_int32) for n in ('kind','record','equipped','revision','pocket')]
class ActionRetail(Equipment):
    def call(self,e,a):
        if e==0x3b5370:
            self.w(BASE+0x220004,4,1000);self.w(BASE+0x22006c,4,0);return BASE+0x220000
        if e==0x38e060:return 0
        return super().call(e,a)
    def actions(self,kind,mode,slot,latch,present,pockets):
        self.events=[];self.w(NODE+84,4,slot);self.w(NODE+40,4,latch);self.w(PARENT+44,4,mode)
        length=3 if kind==0 else 1
        values=[]
        for i in range(length):
            p=BASE+0x234000+i*0x100 if present&(1<<i) else 0
            if p:self.w(p+24,4,pockets);self.w(p+4,4,1000)
            values.append(p)
        for off in (100,104,108):self.w(NODE+off,4,BASE+0x233000)
        self.list(BASE+0x233000,values);self.list(CHILDREN,[])
        self.invoke((0x413c20,0x415de0,0x417880)[kind],NODE)
        p=BASE+0x220000;flags=self.read(p+108,4)
        return self.read(p+44,4),self.read(p+84,4),[self.read(self.read(flags+16,4)+i,1) for i in range(self.read(flags+8,4))]

class ArmorRetail(Equipment):
    def call(self,e,a):
        if e==0x236f80:return 0
        if e==0x3a9220:
            assert self.string(a[1])=='LEVEL'
            return BASE+0x231000
        if e==0x447c10:
            assert self.string(a[2])=='LVPOINT'
            return self.threshold # signed int return ABI (LW sign-extends)
        return super().call(e,a)
    def eligible(self,kind,level,threshold):
        self.threshold=threshold;self.w(BASE+0x23100c,4,level)
        self.w(NODE+120,4,BASE+0x233000);self.list(BASE+0x233000,[BASE+0x234000]);self.w(NODE+96,4,BASE+0x232000)
        return self.invoke(0x4164d0 if kind==1 else 0x417f40,NODE,0)

def armor_checks(elf,tmp):
    stub=Path(tmp)/'armorstubs.c';so=Path(tmp)/'armor.so'
    stub.write_text('''#include "dw4/statusequip.h"
#include <string.h>
#include <stdlib.h>
int dw4_playerstats_item_attribute(void *u,const dw4_item_record *i,const char *key,int32_t *out){
 (void)i;if(strcmp(key,"LVPOINT"))return -1;*out=*(int32_t *)u;return 0;}
int dw4_weapon_eligible(int32_t s,const int32_t k[9],uint32_t m,int32_t a,int32_t b){(void)s;(void)k;(void)m;(void)a;(void)b;abort();}
int dw4_playertransactions_equip_database(dw4_playerrecords *p,int32_t a,const char *k,size_t b,int32_t c,const dw4_databases *d){(void)p;(void)a;(void)k;(void)b;(void)c;(void)d;abort();}
int dw4_playerstats_recalculate(void *u,dw4_property_folder *f){(void)u;(void)f;abort();}
''')
    build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/statusequiprecords.c'),str(ROOT/'src/playerrecords.c'),str(stub),'-lm','-o',str(so)],check=True)
    lib=C.CDLL(str(so));lib.dw4_playerrecords_open.restype=C.c_void_p;lib.dw4_playerrecords_close.argtypes=[C.c_void_p]
    lib.dw4_playerrecords_get.argtypes=[C.c_void_p,C.c_char_p,C.c_int32];lib.dw4_playerrecords_get.restype=C.c_void_p
    lib.dw4_property_set_number.argtypes=[C.c_void_p,C.c_char_p,C.c_int32]
    lib.dw4_property_set_items.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(Item),C.c_size_t]
    lib.dw4_statusequip_eligible.argtypes=[C.c_void_p,C.c_int32,C.c_int32,C.c_void_p,C.POINTER(C.c_int)]
    players=lib.dw4_playerrecords_open();f=lib.dw4_playerrecords_get(players,b'GETPLAYER',0);w=ArmorRetail(elf.read_bytes());total=0
    try:
        for kind,level,threshold in itertools.product((1,2),(-2147483648,-1,0,1,27,999,2147483647),(-2147483648,-1,0,1,27,999,2147483647)):
            expected=w.eligible(kind,level,threshold);requirement=C.c_int32(threshold);out=C.c_int()
            assert not lib.dw4_property_set_number(f,b'LEVEL',level)
            assert not lib.dw4_property_set_items(f,b'DEVICEFOLDER',(Item*1)(Item(kind,0,0,0,0)),1)
            assert not lib.dw4_statusequip_eligible(players,0,0,C.byref(requirement),C.byref(out)) and out.value==expected,(kind,level,threshold,out.value,expected)
            total+=1
    finally:lib.dw4_playerrecords_close(players)
    print(f'equipment armor: {total} signed LEVEL/LVPOINT eligibility cases match retail Main/Sub methods')

def action_checks(elf,tmp):
    so=Path(tmp)/'actions.so';stub=Path(tmp)/'actionstubs.c'
    stub.write_text('#include <stdlib.h>\n'+''.join('void '+name+'(void){abort();}\n' for name in ('dw4_playerstats_item_attribute','dw4_weapon_eligible','dw4_playertransactions_equip_database','dw4_playerstats_recalculate')))
    build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/statusequiprecords.c'),str(ROOT/'src/playerrecords.c'),str(stub),'-lm','-o',str(so)],check=True)
    lib=C.CDLL(str(so));lib.dw4_playerrecords_open.restype=C.c_void_p;lib.dw4_playerrecords_close.argtypes=[C.c_void_p]
    lib.dw4_playerrecords_get.argtypes=[C.c_void_p,C.c_char_p,C.c_int32];lib.dw4_playerrecords_get.restype=C.c_void_p
    lib.dw4_property_set_items.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(Item),C.c_size_t]
    lib.dw4_statusequip_action_rows.argtypes=[C.c_void_p,C.c_int32,C.c_int,C.c_int,C.c_int32,C.c_int32,C.POINTER(Actions)]
    w=ActionRetail(elf.read_bytes());players=lib.dw4_playerrecords_open();assert players
    f=lib.dw4_playerrecords_get(players,b'GETPLAYER',0);total=0
    try:
        for kind in range(3):
            for mode,slot,latch,present,pockets in itertools.product(range(2),range(3 if kind==0 else 1),range(2),range(8 if kind==0 else 2),range(6)):
                n=3 if kind==0 else 1;items=(Item*n)(*[Item(kind if present&(1<<i) else -1,i,1,0,pockets) for i in range(n)])
                assert lib.dw4_property_set_items(f,(b'POWERSOCKET',b'MAINSLOT',b'SUBSLOT')[kind],items,n)==0
                out=Actions();assert lib.dw4_statusequip_action_rows(players,0,kind,mode,slot,latch,C.byref(out))==0
                got=out.callno,out.rows,list(out.enabled)[:out.rows]
                expected=w.actions(kind,mode,slot,latch,present,pockets)
                assert got==expected,(kind,mode,slot,latch,present,pockets,got,expected)
                total+=1
    finally:lib.dw4_playerrecords_close(players)
    print(f'equipment actions: {total} authored row counts/text calls/disabled flags match retail Power/Main/Sub virtual methods')

def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('equipment base: private ELF unavailable, skipped');return
    w=Equipment(elf.read_bytes());total=0
    with tempfile.TemporaryDirectory() as tmp:
        so=Path(tmp)/'equipment.so'
        build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/statusequip.c'),str(ROOT/'src/menuwindow.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_statusequip_tick.argtypes=[C.POINTER(Equip),IO,C.c_void_p]
        for st,sub,d,count,q,sel,ready in itertools.product(range(4),range(5),range(14),(1,3,4),(0,1,256),(-1,0,1,2),(False,True)):
            s=Equip(State(1,st,sub,d,2,sel,3,0),1,3,2,0)
            try:expected=w.tick_equipment(s,count,q,ready)
            except Exception as e:raise AssertionError((st,sub,d,count,q,sel,ready,w.events)) from e
            events=[];nc=count
            @IO
            def io(user,p,op,v):
                nonlocal nc
                if op==COUNT:return nc
                if op==FIND:return 1
                if op==READY:return int(ready)
                # The trace compares virtual calls and service helpers. Inline
                # socket writes/font loops/selector close have separate owners.
                if op not in (COLORS,HIDE,CLOSE,RESTART,SWAP):events.append((op,v))
                if op in (SELECTOR,ERROR):nc+=1
                return q if op in (FINISHED,130) else 0
            rc=lib.dw4_statusequip_tick(C.byref(s),io,None)
            got=[getattr(s.window,n) for n,_ in State._fields_[:7]]+[s.slot,s.slots,s.pocket]
            assert rc==0 and got==expected,(st,sub,d,count,q,sel,ready,got,expected)
            assert events==w.events,(st,sub,d,count,q,sel,ready,events,w.events)
            total+=1
        action_checks(elf,tmp)
        armor_checks(elf,tmp)
    print(f'equipment base: {total} scalar states and virtual/service helper traces match retail; concrete views/records separately tested')
if __name__=='__main__':main()
