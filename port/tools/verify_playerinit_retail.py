#!/usr/bin/env python3
"""Fresh GAMERAM creation against retail code, with controlled allocation and DB leaves.

Uses native test output solely for authored DB inputs and native result comparison.
Executes initialization loops, species selection, equipment creation/selection,
stat helpers and name copy/padding from the private ELF. Generic property/template,
list/allocation, DB lookups and scratch byte buffers are controlled leaves. The
US converter and its table are executed, including all name-grid characters.
"""
import argparse
from pathlib import Path
import subprocess
from verify_playerrecords_retail import Retail as World
from verify_scriptservices_retail import ROOT, BASE, sx
import ctypes as C

OWNER=BASE+0x800000
class Retail(World):
    def ee_reset(self):
        super().ee_reset();self.qhi=[0]*32
    def step(self,pc,delay=False):
        # The shared scalar interpreter masks GPRs to 64 bits. This routine also
        # copies its conversion table with LQ/SQ: retain their upper 64-bit lane.
        word=self.read(pc,4);op=word>>26;rs=(word>>21)&31;rt=(word>>16)&31
        address=(self.r[rs]+sx(word,16))&0xffffffff
        if op==0x1e:self.qhi[rt]=self.read(address+8,8)
        nxt=super().step(pc,delay)
        if op==0x1f:self.w(address+8,8,self.qhi[rt])
        return nxt
    def __init__(self,image,numbers,strings):
        super().__init__(image);self.numbers=numbers;self.strings=strings;self.next=BASE+0x900000;self.props={};self.dbs={}
        self.descend={0x3f82a0,0x3f80e0,0x3f8990,0x3f8c90,0x3f9570,0x3fab90,
            0x3fa3b0,0x3fa850,0x3f9f80,0x3fa040,0x3fa120,0x3fa1e0,0x3fa2c0,0x4482c0,0x448710,0x448f30,0x382eb0}
        self.w(0x554c14,1,1);self.w(0x554c2c,1,1) # allocation branch leaves handled either way
        for i,key in enumerate(numbers):self.dbs[BASE+0x810000+i*0x100]=key
        self.w(OWNER+20,4,BASE+0x820000);self.w(OWNER+32,4,self.db('shinka'));self.w(OWNER+36,4,self.db('pcTech'))
        self.common=self.alloc();self.players=[self.alloc() for i in range(4)];self.plist=self.alloc();self.list(self.plist,self.players)
        self.w(OWNER+64,4,self.common);self.w(OWNER+68,4,self.plist)
        self.template(self.common,0x4ced40)
        for p in self.players:self.template(p,0x4cedf0)
    def db(self,name):return next(p for p,n in self.dbs.items() if n==name)
    def alloc(self):
        p=self.next;self.next+=0x1000;self.w(p+4,4,1000);return p
    def list(self,p,values,stride=4):
        if not hasattr(self,'next'):return super().list(p,values,stride)
        data=self.alloc();self.w(p+8,4,len(values));self.w(p+12,4,1024);self.w(p+16,4,data)
        for i,v in enumerate(values):self.w(data+i*stride,stride,v)
    def template(self,p,table):
        self.props[p]={}
        while True:
            kind=self.read(table,4);n=self.read(table+4,4);key=self.string(self.read(table+8,4));table+=12
            if kind==0xffffffff:break
            prop=self.alloc();self.props[p][key]=(prop,kind)
            if kind in [1,3,5,6,7]:
                l=self.alloc();self.list(l,[0]*n,1 if kind==3 else 4);self.w(prop+12,4,l)
    def prop(self,p,key):return self.props[p][key][0]
    def call(self,e,a):
        a=[x&0xffffffff for x in a]
        if e in [0x3a9220,0x3a9250,0x3a9280,0x3a92b0,0x3a92e0,0x3a9310,0x3a9340]:return self.prop(a[0],self.string(a[1]))
        if e==0x3f6620:self.template(a[1],a[2]);return 0
        if e==0x364050:
            p=self.alloc();self.props[p]={};return p
        if e==0x301000:return BASE
        if e==0x2f88e0:return BASE
        if e in [0x3c85b0,0x3c8c90,0x3c8040]:return self.alloc()
        if e==0x3a9460:return self.numbers[self.dbs[a[0]]].get((a[1],self.string(a[2])),0)&0xffffffff
        if e==0x3a9580:return self.token(self.strings[self.dbs[a[0]]][(a[1],self.string(a[2]))])
        if e==0x447c10:return self.numbers['weapon'].get((self.read(a[0]+12,4),self.string(a[2])),0)&0xffffffff
        if e==0x447cb0:return self.token(self.strings['weapon'].get((self.read(a[0]+12,4),self.string(a[2])),''))
        if e==0x1ca620:self.list(a[0],self.values(a[0])+[self.read(a[1],4)]);return 0
        if e==0x3614f0:return self.alloc()
        if e==0x3843c0:
            data=self.alloc();self.w(a[0]+8,4,a[1]);self.w(a[0]+12,4,data);return 0
        if e==0x236f80:return BASE
        if e==0x12a78c:return len(self.string(a[0]))
        if e in [0x30b420,0x30b460]:return 0 # scratch byte-buffer maintenance, unused by conversion pass
        if e==0x382eb0:
            p=self.alloc();data=self.alloc();self.w(p+12,4,data)
            for i,c in enumerate(self.string(a[2])):self.w(data+2*i,2,ord(c))
            self.w(a[0],4,p);return 0
        if e==0x301ee0:self.w(a[0]+8,4,a[1]);return 0
        return super().call(e,a)
    def create(self,slot,model,name):
        self.invoke(0x3f7310,OWNER,slot)
        f=self.values(self.plist)[slot]
        arg=self.alloc();self.w(arg,4,self.token(name))
        self.invoke(0x3f96e0,OWNER,slot,self.token(model),arg)
        return f

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,required=True);p.add_argument('--roms',type=Path,default=ROOT.parent.parent/'local/extracted');a=p.parse_args()
    if not a.elf.exists():print('character init retail: private ELF unavailable, skipped');return
    output=subprocess.check_output([str(ROOT/'build/test_playerinit'),str(a.roms),'--dump'],text=True,encoding='latin1')
    nums={};strings={};cases={}
    for line in output.splitlines():
        cols=line.split('\t');tag=cols.pop(0)
        if tag in ['N','S']:
            db,row,key,val=cols;dest=nums if tag=='N' else strings;dest.setdefault(db,{})[int(row),key]=int(val) if tag=='N' else val
        elif tag in ['P','U','I','B','D']:
            slot,model,name,*rest=cols;case=cases.setdefault((int(slot),model,name),{'P':{},'I':{},'B':{},'D':{},'U':None})
            if tag=='P':case[tag][rest[0]]=int(rest[1])
            elif tag=='I':case[tag][int(rest[0])]=int(rest[1])
            elif tag=='B':case[tag][rest[0]]=list(map(int,rest[1:]))
            elif tag=='D':case[tag][int(rest[0])]=list(map(int,rest[1:]))
            else:case[tag]=list(map(int,rest))
    w=Retail(a.elf.read_bytes(),nums,strings);count=0
    for (slot,model,name),case in cases.items():
        f=w.create(slot,model,name)
        for key,val in case['P'].items():
            prop=w.prop(f,key);kind=w.props[f][key][1];expected=w.read(prop+12,1 if kind==2 else 4)
            assert val==C.c_int32(expected).value,(slot,model,key,val,C.c_int32(expected).value);count+=1
        for key,ones in [('BASE_LEVEL',1),('BASE_SKILL',1),('SKILL',1),('BASE_EXP',0),('BASE_UPCNT',0),('UPCNT',0)]:
            prop=w.prop(f,key);vals=w.values(w.read(prop+12,4));assert all(v==ones for v in vals),(key,vals)
        base_use=w.read(w.prop(f,'BASE_ISUSE')+12,4);data_use=w.read(base_use+16,4)
        species=case['P']['DIGIMONNO']
        assert [w.read(data_use+i,1) for i in range(16)]==[int(i==species) for i in range(16)]
        prop=w.prop(f,'PLAYERNAME');obj=w.values(w.read(prop+12,4))[0];data=w.read(obj+12,4)
        assert [w.read(data+i*2,2) for i in range(8)]==case['U'],(slot,model,name,[w.read(data+i*2,2) for i in range(8)],case['U'])
        folder=w.read(w.prop(f,'DEVICEFOLDER')+12,4);socket=w.read(w.prop(f,'POWERSOCKET')+12,4)
        assert w.values(folder)==w.values(socket)
        for i,item in enumerate(w.values(socket)):
            assert w.read(item+12,4)==case['I'][i] and w.read(item+16,1)==1
        for key,want in [('DIGIMONNAME',model)]:assert w.string(w.read(w.prop(f,key)+12,4))==want
        for key,values in case['B'].items():
            p=w.read(w.prop(f,key)+12,4);data=w.read(p+16,4)
            assert w.read(p+8,4)==len(values) and [w.read(data+i,1) for i in range(len(values))]==values,(slot,model,key)
        disks=w.values(w.read(w.prop(f,'DISKFOLDER')+12,4));assert len(disks)==12
        for i,p in enumerate(disks):
            assert [w.read(p+8,4),w.read(p+12,4),w.read(p+16,1),w.read(p+20,4)]==case['D'][i],(slot,model,i)
        assert not w.values(w.read(w.prop(f,'BANKDEVICE')+12,4))
    # Every creation-grid character passes the actual US converter table.
    grid='abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789&!?+-*/=.,:;()[]_ '
    for char in grid:
        out=w.alloc();w.invoke(0x382eb0,out,BASE,w.token(char));obj=w.read(out,4);data=w.read(obj+12,4)
        supported=char not in '*/=;[]'
        assert w.read(obj+8,4)==int(supported) and w.read(data,2)==(ord(char) if supported else 0) and w.read(data+2,2)==0,(char,w.read(data,2))
    for entry in [0x3f7310,0x3f80e0,0x3f82a0,0x3f8990,0x3f8c90,0x3f9570,0x3f96e0,0x3fab90,0x3fa3b0,0x3fa850,0x382eb0]:assert entry in w.covered
    print(f'character init retail: {len(cases)} paths, {count} scalars, names/base arrays/starter sockets, all flag/card bytes, twelve disk records and empty BANKDEVICE match; allocation/property/DB leaves controlled')
if __name__=='__main__':main()
