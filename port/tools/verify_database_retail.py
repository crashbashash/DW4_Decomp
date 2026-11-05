#!/usr/bin/env python3
"""String-column lookup and DATABASE GETDATABASE against original instructions.

Executes 3a93a0, igProperty_FindByName 3022c0, 3a9580 and 3a9780.
Only strcmp, command decoding, enum construction and object-result publication
are controlled leaves. Fixtures supply native lists; private game bytes are
read solely from the user-supplied ELF.
"""
import argparse
import ctypes as C
from pathlib import Path
import random
import subprocess
import tempfile
from verify_scriptservices_retail import World, ROOT, BASE

DB, COLUMNS, DATA, FIELD, MANAGER, RAM, INFO = range(BASE+0x180000, BASE+0x180700, 0x100)
class Numbers(C.Structure):
    _fields_=[("columns",C.POINTER(C.c_char_p)),("ncolumns",C.c_uint32),("count",C.c_uint32),("values",C.POINTER(C.c_int32))]
class ObjectValue(C.Structure):
    _fields_=[("kind",C.c_int),("pointer",C.c_void_p),("owner",C.c_void_p)]
class Database(C.Structure):
    _fields_=[('name',C.c_char_p),('columns',C.POINTER(C.c_char_p)),
              ('strings',C.POINTER(C.c_char_p)),('ncolumns',C.c_uint32),('nstrings',C.c_uint32),('numeric',Numbers*4),('view',ObjectValue),('token',C.c_uint64)]
class Databases(C.Structure):
    _fields_=[('items',C.POINTER(Database)),('count',C.c_size_t),('sd',C.c_void_p)]
class Retail(World):
    def __init__(self,image):
        super().__init__(image)
        self.descend={0x3a93a0,0x3022c0}
        self.w(0x585be0,4,FIELD);self.w(FIELD+8,4,8)
    def call(self,e,a):
        a=[x&0xffffffff for x in a]
        if e==0x366070:return BASE+0x190000
        if e==0x38d4a0:return self.command
        if e==0x38f670:self.published=a[1];return 0
        return super().call(e,a)
    def setup(self,columns,strings):
        ids=[]
        for i,name in enumerate(columns):
            p=BASE+0x181000+i*16;self.w(p+8,4,self.token(name));ids.append(p)
        self.list(COLUMNS,ids)
        ids=[]
        for i,name in enumerate(strings):
            p=BASE+0x182000+i*16;self.w(p+8,4,self.token(name));ids.append(p)
        self.list(DATA,ids);self.w(DB+48,4,COLUMNS);self.w(DB+52,4,DATA)
    def text(self,p):
        if p&0xffffffff==0x4e0858:return ''
        return self.string(p)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,required=True);args=p.parse_args()
    if not args.elf.exists():print('database retail: private ELF unavailable, skipped');return
    w=Retail(args.elf.read_bytes());rng=random.Random(20836);offsets=strings=numeric=booleans=0
    with tempfile.TemporaryDirectory() as tmp:
        tmp=Path(tmp);stub=tmp/'stub.c'
        stub.write_text('#include <stdlib.h>\n'+''.join('void '+name+'(void){abort();}\n' for name in
            ['dw4_stageobjects_count','dw4_stageobjects_at','dw4_igb_ref','dw4_igb_decode','dw4_igb_record_free',
             'dw4_igb_block','dw4_object_get_ref','dw4_object_from_record','dw4_object_free']))
        so=tmp/'db.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/database.c'),str(ROOT/'src/scriptservices.c'),str(stub),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.dw4_database_string_offset.argtypes=[C.POINTER(C.c_char_p),C.c_uint32,C.c_int32,C.c_char_p]
        lib.dw4_database_string_offset.restype=C.c_int32
        lib.dw4_database_string.argtypes=[C.POINTER(Database),C.c_int32,C.c_char_p];lib.dw4_database_string.restype=C.c_char_p
        lib.dw4_database_number.argtypes=[C.POINTER(Database),C.c_int32,C.c_char_p,C.POINTER(C.c_int32)]
        lib.dw4_database_bool.argtypes=[C.POINTER(Database),C.c_int32,C.c_char_p,C.POINTER(C.c_int32)]
        lib.dw4_databases_get.argtypes=[C.POINTER(Databases),C.c_char_p];lib.dw4_databases_get.restype=C.POINTER(Database)
        for count in [0,1,2,3,7,16]:
            columns=[None if i==1 else 'COL'+str(i) for i in range(count)]
            if count>=3:columns[-1]=columns[0] # first equal name/object wins
            data=[None if i%5==0 else '' if i%5==1 else 'cell'+str(i) for i in range(count*8)]
            w.setup(columns,data)
            cols=(C.c_char_p*count)(*[s.encode() if s is not None else None for s in columns])
            values=(C.c_char_p*len(data))(*[s.encode() if s is not None else None for s in data])
            d=Database(b'shinka',cols,values,count,len(data))
            for key in columns+['absent',None]:
                for row in [-2147483648,-1,0,1,7,2147483647]+[rng.randint(-2147483648,2147483647) for _ in range(10)]:
                    name=key.encode() if key is not None else None
                    expected=C.c_int32(w.invoke(0x3a93a0,DB,row,w.token(key),COLUMNS)&0xffffffff).value
                    got=lib.dw4_database_string_offset(cols,count,row,name)
                    assert got==expected,(columns,row,key,got,expected);offsets+=1
                if key is None or key not in columns or not count:continue
                for row in range(8):
                    expected=w.text(w.invoke(0x3a9580,DB,row,w.token(key)))
                    got=lib.dw4_database_string(C.byref(d),row,key.encode())
                    assert got is not None and got.decode()==expected,(columns,row,key,got,expected);strings+=1
            assert lib.dw4_database_string(C.byref(d),-1,b'COL0') is None
            assert lib.dw4_database_string(C.byref(d),8,b'COL0') is None
            assert lib.dw4_database_string(C.byref(d),0,b'absent') is None
        # Signed char/short/int selection, first type/name precedence and zero fallback.
        w.descend={0x3a93a0,0x3022c0}
        for types in [[],[0],[1],[2],[0,1,2]]:
            d=Database();keep=[]
            for k in range(3):
                names=['DUP','C'+str(k)] if k in types else []
                vals=[-128 if k==0 else -32768 if k==1 else -2147483648,127 if k==0 else 32767 if k==1 else 2147483647]*4 if names else []
                cols=(C.c_char_p*len(names))(*[x.encode() for x in names]);data=(C.c_int32*len(vals))(*vals)
                keep.extend([cols,data]);d.numeric[k]=Numbers(cols,len(names),len(vals),data)
                cl=BASE+0x190000+k*0x100;dl=cl+0x80;entries=[]
                for i,key in enumerate(names):
                    p=BASE+0x191000+k*0x100+i*16;w.w(p+8,4,w.token(key));entries.append(p)
                w.list(cl,entries);w.list(dl,vals,1<<k);w.w(DB+8+k*8,4,cl);w.w(DB+12+k*8,4,dl)
            for row in range(4):
                for key in ['DUP','C0','C1','C2','missing']:
                    expected=C.c_int32(w.invoke(0x3a9460,DB,row,w.token(key))&0xffffffff).value
                    got=C.c_int32();rc=lib.dw4_database_number(C.byref(d),row,key.encode(),C.byref(got))
                    assert rc in [0,1] and got.value==expected,(types,row,key,got.value,expected);numeric+=1
            got=C.c_int32();assert lib.dw4_database_number(C.byref(d),-1,b'DUP',C.byref(got))==-1
            if types:assert lib.dw4_database_number(C.byref(d),4,b'DUP',C.byref(got))==-1
        # 3a9540's own byte table is unsigned and separate from numeric columns.
        for columns in [['WU'],['WU','BLUEAB'],['DUP',None,'DUP']]:
            values=[0,1,127,128,255,1]*len(columns)
            cols=(C.c_char_p*len(columns))(*[key.encode() if key else None for key in columns])
            data=(C.c_int32*len(values))(*values);d=Database();d.numeric[3]=Numbers(cols,len(columns),len(values),data)
            ids=[]
            for i,key in enumerate(columns):
                p=BASE+0x194000+i*16;w.w(p+8,4,w.token(key));ids.append(p)
            w.list(COLUMNS,ids);w.list(DATA,values,1);w.w(DB+40,4,COLUMNS);w.w(DB+44,4,DATA)
            for row in range(len(values)//len(columns)):
                for key in columns:
                    if key is None:continue
                    expected=w.invoke(0x3a9540,DB,row,w.token(key));out=C.c_int32()
                    assert lib.dw4_database_bool(C.byref(d),row,key.encode(),C.byref(out))==0 and out.value==expected
                    booleans+=1
            out=C.c_int32();assert lib.dw4_database_bool(C.byref(d),-1,b'WU',C.byref(out))==-1
            assert lib.dw4_database_bool(C.byref(d),999,b'DUP' if 'DUP' in columns else b'WU',C.byref(out))==-1
            assert lib.dw4_database_bool(C.byref(d),0,b'missing',C.byref(out))==1 and out.value==0
        # Receiver dispatch publishes the authored typed database only on command 0.
        published=0;w.w(MANAGER+20,4,BASE+0x183000);w.w(RAM+12,4,INFO);w.w(INFO+28,4,DB)
        for command in [0,1,2,-1,2147483647]:
            w.command=command;w.published=None
            result=w.invoke(0x3a9780,MANAGER,RAM,BASE+0x184000)&0xffffffff
            assert result==int(command==0) and w.published==(DB if command==0 else None);published+=1
        items=(Database*3)(Database(b'shinka',None,None,0,0),Database(b'shinka',None,None,0,0),Database(b'other',None,None,0,0))
        owner=Databases(items,3)
        assert C.addressof(lib.dw4_databases_get(C.byref(owner),b'shinka').contents)==C.addressof(items[0])
        assert not lib.dw4_databases_get(C.byref(owner),b'SHINKA')
    for start,end in [(0x3a93a0,0x3a9460),(0x3022c0,0x30237c),(0x3a9540,0x3a9578),(0x3a9580,0x3a95d8),(0x3a9780,0x3a97f8)]:
        # Trailing compiler padding is not required, but each body must execute.
        assert start in w.covered and end-4 in w.covered,(hex(start),hex(end))
    print(f'database retail: {offsets} column offsets, {strings} strings, {numeric} signed numbers, {booleans} unsigned booleans and {published} GETDATABASE cases match; strcmp/command/publication leaves controlled')
if __name__=='__main__':main()
