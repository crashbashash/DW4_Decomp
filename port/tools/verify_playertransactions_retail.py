#!/usr/bin/env python3
"""Equipment/CTRLITEM/CURRENT2BASE against retail instructions.

Allocation, typed property/list lookup, item attribute lookup and message sinks
are controlled leaves. Item identity, flag writes, list order, limits, species
copy loops and signed eligibility execute from the ELF.
"""
from native_shared import build_shared
import argparse
import ctypes as C
import random
import subprocess
import tempfile
from pathlib import Path
from verify_playerrecords_retail import Retail as World
from verify_scriptservices_retail import ROOT, BASE
NODE, FOLDER, LIST, CAND, PROPERTY = [BASE+0x600000+i*0x10000 for i in range(5)]
class Val(C.Structure):
    _fields_=[('type',C.c_int),('number',C.c_double),('string',C.c_char_p),('length',C.c_size_t)]
class Item(C.Structure):
    _fields_=[(k,C.c_int32) for k in ['kind','record','equipped','revision','pocket']]
ATTR=C.CFUNCTYPE(C.c_int,C.c_void_p,C.POINTER(Item),C.c_char_p,C.POINTER(C.c_int32))
FAMILIES=['TSUYOSA','KASHIKOSA','SEISHIN','SUBAYASA','RES_FIRE','RES_ICE','RES_THUNDER','RES_DARK','CHIMEIRITSU','HPDRAIN','MPDRAIN','CHOHATURITSU']
class Retail(World):
    def __init__(self,image):
        super().__init__(image);self.descend={0x4482c0,0x448410,0x448560,0x448660,0x448050};self.props={};self.group='DEVICE';self.next=BASE+0x900000
        self.w(NODE+20,4,BASE);self.w(0x554c14,1,1);self.w(NODE+68,4,BASE+0x690000)
        self.list(BASE+0x690000,[FOLDER]*4)
    def alloc(self):
        p=self.next;self.next+=0x1000;self.w(p+4,4,1000);return p
    def property(self,key,vals):
        p=self.alloc();self.props[key]=p
        if isinstance(vals,list):l=self.alloc();self.list(l,vals);self.w(p+12,4,l)
        else:self.w(p+12,4,vals)
        return p
    def items(self,values):
        result=[]
        for i in values:
            p=self.alloc();result.append(p)
            for off,k in [(8,'kind'),(12,'record'),(16,'equipped'),(20,'revision'),(24,'pocket')]:self.w(p+off,1 if off==16 else 4,getattr(i,k))
        self.itemptrs=result;return result
    def call(self,e,a):
        a=[x&0xffffffff for x in a]
        if e in [0x3a9220,0x3a9250,0x3a92b0,0x3a9340]:return self.props[self.string(a[1])]
        if e==0x407050:return self.read(a[0],4)
        if e in [0x406f10,0x407040]:return self.read(a[0],4)
        if e==0x406f00:return self.read(a[0]+16,4)
        if e==0x3c9c40:return 0
        if e==0x38d4a0:return 17
        if e==0x38f8f0:return self.token([self.group,self.operation,self.kindname][a[1]])
        if e==0x38f320:return self.arguments[a[1]]
        if e==0x407030:return self.read(a[0],4)
        if e==0x3e9260:return self.values(a[0])[a[1]]
        if e==0x406f80:return self.read(a[0],4)
        if e in [0x3e90d0,0x3e9110,0x406f40,0x406f50,0x406f60,0x406f70,0x406fa0]:
            if e in [0x406f40,0x406f50,0x406f60,0x406f70]:self.w(a[0],4,a[1])
            return 0
        if e==0x406f20:
            vals=self.values(a[0]);del vals[a[1]];self.list(a[0],vals);return 0
        if e==0x38f150:self.result=a[1];return 0
        if e in [0x301000,0x3e9370,0x236f80]:return BASE
        if e in [0x3c87f0,0x3c8970,0x3c8b00,0x3c8c90]:return self.alloc()
        if e==0x1ca620:self.list(a[0],self.values(a[0])+[self.read(a[1],4)]);return 0
        if e==0x2b90e0:
            p=self.alloc();self.list(p,[]);return p
        if e==0x2caa70:return self.alloc()
        if e==0x447c10:
            idx=self.itemptrs.index(a[0]);return C.c_int32(self.attributes[idx].get(self.string(a[2]),0)).value
        return super().call(e,a)

def bind(lib):
    lib.dw4_equipment_assign.argtypes=[C.POINTER(Item),C.c_size_t,C.POINTER(C.c_int32),C.c_size_t,C.c_size_t,C.c_int32,ATTR,C.c_void_p]
    lib.dw4_weapon_eligible.argtypes=[C.c_int32,C.POINTER(C.c_int32),C.c_uint32,C.c_int32,C.c_int32]
    lib.dw4_playerrecords_open.restype=C.c_void_p
    lib.dw4_playerrecords_close.argtypes=[C.c_void_p]
    lib.dw4_playerrecords_get.argtypes=[C.c_void_p,C.c_char_p,C.c_int32];lib.dw4_playerrecords_get.restype=C.c_void_p
    lib.dw4_property_set_items.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(Item),C.c_size_t]
    lib.dw4_property_items.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(C.c_size_t)];lib.dw4_property_items.restype=C.POINTER(Item)
    lib.dw4_property_set_array.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(C.c_int32),C.c_size_t]
    lib.dw4_property_array.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(C.c_size_t)];lib.dw4_property_array.restype=C.POINTER(C.c_int32)
    lib.dw4_property_set_number.argtypes=[C.c_void_p,C.c_char_p,C.c_int32]
    lib.dw4_playertransactions_device.argtypes=[C.c_void_p,C.c_int32,C.c_int,C.c_int32,C.c_int32,C.c_int32,C.c_int32,C.POINTER(C.c_int)]
    lib.dw4_playertransactions_current_to_base.argtypes=[C.c_void_p,C.c_int32]
    lib.dw4_playertransactions_folder_call.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(Val),C.c_size_t,C.POINTER(Val),C.c_char_p,C.c_size_t]
    lib.dw4_property_set_bytes.argtypes=[C.c_void_p,C.c_char_p,C.c_char_p,C.c_size_t]
    lib.dw4_property_bytes.argtypes=[C.c_void_p,C.c_char_p,C.POINTER(C.c_size_t)];lib.dw4_property_bytes.restype=C.POINTER(C.c_ubyte)
    lib.dw4_playertransactions_disk_folder.argtypes=[C.c_void_p,C.c_int32,C.c_int,C.c_int32,C.c_int32,C.POINTER(C.c_int)]

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,required=True);args=p.parse_args()
    if not args.elf.exists():print('player transactions retail: private ELF unavailable, skipped');return
    image=args.elf.read_bytes();rng=random.Random(796);equipment=devices=skills=eligibility=0
    with tempfile.TemporaryDirectory(prefix='dw4-transactions-') as td:
        so=Path(td)/'transactions.so'
        build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/playerrecords.c'),str(ROOT/'src/playertransactions.c'),str(ROOT/'src/inventorydetail.c'),str(ROOT/'src/foldercalls.c'),'-lm','-o',str(so)],check=True)
        lib=C.CDLL(str(so));bind(lib)
        for sample in range(800):
            w=Retail(image);count=6;slots=5
            values=[Item(3 if sample%2 else 0,i%3,0,0,0) for i in range(count)]
            refs=rng.sample(range(count),slots)
            refs=[-1 if rng.randrange(3)==0 else x for x in refs]
            for r in refs:
                if r>=0:values[r].equipped=1
            ptrs=w.items(values);w.attributes=[{FAMILIES[i%3]:1,FAMILIES[(i+1)%3]:int(i%2==0)} for i in range(count)]
            w.list(LIST,[ptrs[r] if r>=0 else 0 for r in refs]);w.list(CAND,ptrs);w.w(NODE+120,4,CAND)
            slot=rng.randrange(slots);candidate=rng.randrange(-1,count)
            w.invoke(0x411950,NODE,LIST,slot,candidate)
            native=(Item*count)(*values);links=(C.c_int32*slots)(*refs)
            # Attribute fixture keyed by inventory identity; native callback gets
            # a pointer into the native contiguous item array, not record number.
            @ATTR
            def attr(_,item,key,out):
                idx=(C.addressof(item.contents)-C.addressof(native))//C.sizeof(Item)
                out[0]=w.attributes[idx].get(key.decode(),0);return 0
            assert lib.dw4_equipment_assign(native,count,links,slots,slot,candidate,attr,None)==0
            expected=[ptrs.index(x) if x else -1 for x in w.values(LIST)]
            assert list(links)==expected,(sample,list(links),expected)
            assert [x.equipped for x in native]==[w.read(x+16,1) for x in ptrs],sample
            equipment+=1
        for sample in range(500):
            w=Retail(image);species=rng.randrange(-40,70);skill=rng.randrange(9);threshold=rng.choice([-2147483648,-1,0,1,2500,2147483647])
            levels=[rng.choice([-2147483648,-1,0,1,2500,2147483647]) for _ in range(9)];mask=rng.getrandbits(32)
            w.property('DIGIMONNO',species);w.property('SKILL',levels)
            w.list(CAND,[BASE+0x800000]);w.w(NODE+120,4,CAND);w.w(NODE+96,4,FOLDER)
            w.attributes=[{'SOUBI':mask,'SKILL':skill,'SKILLPOINT':threshold}];w.itemptrs=[BASE+0x800000]
            expected=w.invoke(0x4144a0,NODE,0)
            assert lib.dw4_weapon_eligible(species,(C.c_int32*9)(*levels),mask,skill,threshold)==expected,(species,mask,skill,threshold,levels,expected)
            eligibility+=1
        for sample in range(360):
            w=Retail(image);count=rng.choice([0,1,5,35,36]);kind=rng.randrange(4);record=rng.randrange(3);op=sample%5
            values=[Item(rng.randrange(4),rng.randrange(3),rng.choice([0,1,256,257]),0,0) for _ in range(count)]
            ptrs=w.items(values);prop=w.property('DEVICEFOLDER',ptrs);lst=w.read(prop+12,4)
            w.operation=['SET','CLR','IS','ISMAX','ISEQUIP'][op];w.kindname=['weapon','armor1','armor2','abChip'][kind]
            w.arguments=[sample%4,record,0x1234,0x5678];w.result=None
            assert w.invoke(0x3fca10,NODE,0,BASE)==1
            owner=lib.dw4_playerrecords_open();f=lib.dw4_playerrecords_get(owner,b'GETPLAYER',sample%4)
            try:
                assert lib.dw4_property_set_items(f,b'DEVICEFOLDER',(Item*count)(*values),count)==0
                for key,n in [('POWERSOCKETREF',3),('POWERPOCKETREF',5),('MAINSLOTREF',1),('MAINPOCKETREF',5),('SUBSLOTREF',1)]:
                    assert lib.dw4_property_set_array(f,key.encode(),(C.c_int32*n)(*([-1]*n)),n)==0
                out=C.c_int(-1);assert lib.dw4_playertransactions_device(owner,sample%4,op,kind,record,0x1234,0x5678,C.byref(out))==0
                assert out.value==w.result,(sample,out.value,w.result)
                n=C.c_size_t();native=lib.dw4_property_items(f,b'DEVICEFOLDER',C.byref(n));expected=w.values(lst)
                assert n.value==len(expected)
                for i,pointer in enumerate(expected):
                    for off,key in [(8,'kind'),(12,'record'),(16,'equipped'),(20,'revision'),(24,'pocket')]:
                        assert (getattr(native[i],key)&(255 if off==16 else 0xffffffff))==w.read(pointer+off,1 if off==16 else 4),(sample,i,key,getattr(native[i],key),w.read(pointer+off,4))
            finally:lib.dw4_playerrecords_close(owner)
            devices+=1
        disks=0
        for sample in range(400):
            # CTRLITEM DISK (SYSctlDiskFolder): retail 448050 finds the entry by record, +0x14 holds the count.
            w=Retail(image);player=sample%4;record=rng.randrange(12);op=sample%4;amount=rng.choice([0,1,3,8,9,50])
            values=[Item(4,i,0,rng.randrange(10),0) for i in range(12)]
            ptrs=w.items(values);prop=w.property('DISKFOLDER',ptrs);lst=w.read(prop+12,4)
            w.group='DISK';w.operation=['SET','CLR','IS','ISMAX'][op];w.kindname='';w.arguments=[player,record,0,amount];w.result=None
            assert w.invoke(0x3fca10,NODE,0,BASE)==1
            owner=lib.dw4_playerrecords_open();f=lib.dw4_playerrecords_get(owner,b'GETPLAYER',player)
            try:
                assert lib.dw4_property_set_items(f,b'DISKFOLDER',(Item*12)(*values),12)==0 and lib.dw4_property_set_number(f,b'BIT',0)==0
                out=C.c_int(-1);assert lib.dw4_playertransactions_disk_folder(owner,player,op,record,amount,C.byref(out))==0
                assert w.result is not None and out.value==w.result,(sample,op,out.value,w.result)
                n=C.c_size_t();native=lib.dw4_property_items(f,b'DISKFOLDER',C.byref(n));expected=w.values(lst)
                assert n.value==12 and len(expected)==12
                for i,pointer in enumerate(expected):assert native[i].revision==w.read(pointer+20,4) and native[i].record==w.read(pointer+12,4),(sample,i)
            finally:lib.dw4_playerrecords_close(owner)
            disks+=1
        flags=0
        for sample in range(300):
            # CTRLITEM FLAG (SYSctlFlagFolder): retail reads the session FLAGFOLDER byte, SET from 0 / CLR from set.
            w=Retail(image);op=sample%3;index=rng.randrange(12);name=['SET','CLR','IS'][op]
            data=bytes(rng.choice([0,0,1,7]) for _ in range(12));buf=w.alloc()
            for i,b in enumerate(data):w.w(buf+i,1,b)
            array=w.alloc();w.w(array+8,4,12);w.w(array+16,4,buf);w.property('FLAGFOLDER',array);w.w(NODE+0x40,4,array)
            w.group='FLAG';w.operation=name;w.kindname='';w.arguments=[0,index,0,0];w.result=None
            assert w.invoke(0x3fca10,NODE,0,BASE)==1 and w.result is not None,(sample,name)
            expected=bytes(w.read(buf+i,1) for i in range(12))
            owner=lib.dw4_playerrecords_open();common=lib.dw4_playerrecords_get(owner,b'GETCOMMON',0)
            try:
                assert lib.dw4_property_set_bytes(common,b'FLAGFOLDER',data,12)==0
                args=(Val*2)(Val(2,0,name.encode(),len(name)),Val(1,index,None,0));res=Val();err=C.create_string_buffer(256)
                assert lib.dw4_playertransactions_folder_call(owner,b'SYSctlFlagFolder',args,2,C.byref(res),err,256)==0,err.value
                n=C.c_size_t();got=bytes(lib.dw4_property_bytes(common,b'FLAGFOLDER',C.byref(n))[i] for i in range(12))
                assert int(res.number)==w.result and got==expected,(sample,name,index,data.hex(),got.hex(),expected.hex(),res.number,w.result)
            finally:lib.dw4_playerrecords_close(owner)
            flags+=1
        for op in ['ISEQUIP','GET','ADD']: # operations the DISK group does not implement push no answer
            w=Retail(image);values=[Item(4,i,0,i%10,0) for i in range(12)]
            ptrs=w.items(values);w.property('DISKFOLDER',ptrs);w.group='DISK';w.operation=op;w.kindname='';w.arguments=[0,3,0,5];w.result=None
            assert w.invoke(0x3fca10,NODE,0,BASE)==1 and w.result is None,op
            disks+=1
        for slot in range(4):
            for species in range(16):
                w=Retail(image);owner=lib.dw4_playerrecords_open();f=lib.dw4_playerrecords_get(owner,b'GETPLAYER',slot)
                try:
                    for key,val in [('DIGIMONNO',species),('LEVEL',-1),('EXP',2147483647)]:
                        w.property(key,val);assert lib.dw4_property_set_number(f,key.encode(),val)==0
                    for key,n in [('BASE_LEVEL',16),('BASE_EXP',16),('BASE_SKILL',144),('BASE_UPCNT',176),('SKILL',9),('UPCNT',11)]:
                        vals=[C.c_int32(rng.getrandbits(32)).value for _ in range(n)];w.property(key,vals)
                        assert lib.dw4_property_set_array(f,key.encode(),(C.c_int32*n)(*vals),n)==0
                    w.invoke(0x3f8760,NODE,slot);assert lib.dw4_playertransactions_current_to_base(owner,slot)==0
                    for key in ['BASE_LEVEL','BASE_EXP','BASE_SKILL','BASE_UPCNT']:
                        n=C.c_size_t();native=lib.dw4_property_array(f,key.encode(),C.byref(n));expected=w.values(w.read(w.props[key]+12,4))
                        assert [x&0xffffffff for x in native[:n.value]]==expected,(slot,species,key)
                finally:lib.dw4_playerrecords_close(owner)
                skills+=1
    print(f'player transactions retail: {equipment} assignments, {eligibility} signed eligibility, {devices} CTRLITEM DEVICE and {disks} CTRLITEM DISK and {flags} CTRLITEM FLAG states and {skills} species persistence states match (allocation/property/list/attribute/message leaves controlled)')
if __name__=='__main__':main()
