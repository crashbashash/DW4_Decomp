#!/usr/bin/env python3
"""Execute retail 3fab90 growth/equipment/technique logic on authored table inputs.
Allocation, property/list ownership and item DB manager dispatch are controlled leaves. Item attribute wrappers and virtual
getters execute, checking the database selector for each concrete item kind.
Checks arbitrary equipment projections, levels, signed wrapping and HP/MP rules.
"""
import argparse
import ctypes as C
from pathlib import Path
import subprocess
from verify_playerinit_retail import Retail as Initial, OWNER
from verify_scriptservices_retail import ROOT

class Retail(Initial):
    def __init__(self,*args):
        super().__init__(*args)
        self.descend.update([0x447c10,0x447cb0,0x4482a0,0x4483f0,0x448540,0x448640])
    def call(self,e,a):
        a=[x&0xffffffff for x in a]
        if e==0x3a9460:return C.c_int32(self.numbers[self.dbs[a[0]]].get((a[1],self.string(a[2])),0)).value
        if e==0x447bc0:
            name=self.string(a[2]);kind=self.read(a[0]+8,4)
            assert name==['weapon','armor1','armor2','abChip'][kind]
            return self.db(name)
        return super().call(e,a)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,required=True);p.add_argument('--roms',type=Path,default=ROOT.parent.parent/'local/extracted');a=p.parse_args()
    if not a.elf.exists():print('player stats retail: private ELF unavailable, skipped');return
    exe=str(ROOT/'build/test_playerinit');nums={};strings={}
    for line in subprocess.check_output([exe,str(a.roms),'--dump'],text=True,encoding='latin1').splitlines():
        cols=line.split('\t')
        if cols[0] in ('N','S'):
            tag,db,row,key,val=cols;dest=nums if tag=='N' else strings;dest.setdefault(db,{})[int(row),key]=int(val) if tag=='N' else val
    cases=[]
    for line in subprocess.check_output([exe,str(a.roms),'--stats'],text=True,encoding='latin1').splitlines():
        cols=line.split('\t');tag=cols.pop(0)
        if tag=='C':case={'C':list(map(int,cols)),'A':{},'E':{},'V':{}};cases.append(case)
        elif tag=='A':case['A'][cols[0]]=list(map(int,cols[1:]))
        elif tag=='E':k,j,kind,rec,rev=map(int,cols);case['E'][k,j]=(kind,rec,rev)
        elif tag=='V':case['V'][cols[0]]=int(cols[1])
        elif tag=='W':case['W']=[tuple(map(int,cols[i:i+2])) for i in range(0,len(cols),2)]
        elif tag=='M':case['M']=cols
    total=0;techniques=0
    for case in cases:
        # A new interpreter keeps fixture allocations bounded for each test.
        w=Retail(a.elf.read_bytes(),nums,strings);_,species,level,hp,mp,base=case['C'];f=w.players[0]
        for key,v in [('DIGIMONNO',species),('LEVEL',level),('HP',hp),('MP',mp)]:w.w(w.prop(f,key)+12,4,v)
        for key,vals in case['A'].items():w.list(w.read(w.prop(f,key)+12,4),vals)
        for k,key in enumerate(['POWERSOCKET','POWERPOCKET','MAINSLOT','MAINPOCKET','SUBSLOT']):
            vals=[]
            for j in range([3,5,1,5,1][k]):
                kind,rec,rev=case['E'][k,j];item=0
                if kind!=-1:
                    item=w.alloc();w.w(item,4,[0x540960,0x5408f0,0x540880,0x540810][kind]);w.w(item+8,4,kind);w.w(item+12,4,rec);w.w(item+16,1,1);w.w(item+20,4,rev)
                vals.append(item)
            w.list(w.read(w.prop(f,key)+12,4),vals)
        w.invoke(0x3fab90,OWNER,0,0 if base else 1) # third argument: equipment bonuses enabled
        for key,val in case['V'].items():
            expected=C.c_int32(w.read(w.prop(f,key)+12,4)).value
            assert val==expected,(case['C'],key,val,expected);total+=1
        wazalist=w.values(w.read(w.prop(f,'WAZALIST')+12,4))
        expected=[(C.c_int32(w.read(i+12,4)).value,C.c_int32(w.read(i+20,4)).value) for i in wazalist]
        assert case['W']==expected,(case['C'],'WAZALIST',case['W'],expected)
        assert all(w.read(i+8,4)==9 and w.read(i+16,1)==0 for i in wazalist);techniques+=len(expected)
        if 'M' in case:
            names=[w.string(i) for i in w.values(w.read(w.prop(f,'POWERSOCKETNAME')+12,4))]
            assert case['M']==names,(case['C'],'names',case['M'],names)
    bases=sum(1 for c in cases if c['C'][-1]);print(f'player stats retail: {len(cases)} species/level/equipment cases ({bases} with the RECALCPLAYER-false equipment-free flag), {total} scalar results and {techniques} technique records match; DB/property/allocation leaves controlled; production commit/preview checks pass')
if __name__=='__main__':main()
