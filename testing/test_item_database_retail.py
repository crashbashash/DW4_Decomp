#!/usr/bin/env python3
"""Complete item/database getters against original instructions and live records.

Database request delivery, strcmp and exceptional virtual/lookup results are
controlled. Normal chains execute actual chip selection, item wrappers, database
lookups and the previously recovered property-name search.
"""
import ctypes as C
import itertools
from pathlib import Path
import subprocess
import tempfile
from test_subwindow_lifecycle_retail import LifecycleWorld,ROOT,Api,READ,WRITE,CALL,MASK,STACK
REQUEST,GETINT,GETBOOL,GETSTRING,CHIP=0x447bc0,0x447c10,0x447c60,0x447cb0,0x448640
FIND,DBINT,DBBOOL,DBSTRING,COUNT,PROPERTY=0x3a93a0,0x3a9460,0x3a9540,0x3a9580,0x3a95e0,0x3022c0
SIZES={REQUEST:72,GETINT:72,GETBOOL:72,GETSTRING:72,CHIP:32,FIND:192,DBINT:216,DBBOOL:56,DBSTRING:88,COUNT:296}
SELF,STATUS,DB,VTABLE,DESC,COLUMNS,VALUES,NAMES,KEYS,STRINGS,SCRATCH=0x1a00000,0x1a10000,0x1a20000,0x1a30000,0x1a40000,0x1a50000,0x1b00000,0x1c00000,0x1c10000,0x1c20000,0x1d00000
VIRTUAL=0x1234000
OFFSETS=(8,16,24,32,40,48)

def word(n):return C.c_int32(n&0xffffffff).value&MASK

class DatabaseWorld(LifecycleWorld):
    def __init__(self,image):
        super().__init__(image);self.descend=set(SIZES)|{PROPERTY};self.frame=STACK-80
        self.mutation=None;self.find_result=None;self.lookup_results=[];self.leaf_return=0;self.object_result=DB;self.virtual_result=DB;self.compares=0
        self.w(SELF,4,VTABLE);self.w(VTABLE+92,4,CHIP);self.w(SELF+12,4,1);self.w(STATUS+20,4,0x1a41000)
        self.w(0x585be0,4,DESC);self.w(DESC+8,4,8)
        for k in range(3):self.text(KEYS+k*64,('key%d'%k).encode())
        self.text(KEYS+0x400,b'missing')
        for family,offset in enumerate(OFFSETS):
            names=COLUMNS+family*0x1000;values=VALUES+family*0x1000
            self.w(DB+offset,4,names);self.w(DB+offset+4,4,values)
            self.make_columns(names,[NAMES+family*0x1000+k*64 for k in range(3)])
            for k in range(3):self.w(NAMES+family*0x1000+k*64+8,4,KEYS+k*64)
            self.w(values+8,4,27);self.w(values+16,4,values+0x400)
            for i in range(27):
                size=1 if family in (0,4) else 2 if family==1 else 4
                if family==5:
                    p=STRINGS+i*64;self.w(p+8,4,KEYS+(i%3)*64);self.w(values+0x400+i*4,4,p)
                else:self.w(values+0x400+i*size,size,10+family*100+i)
    def text(self,p,data):
        for i,b in enumerate(data+b'\0'):self.w(p+i,1,b)
    def string(self,p):
        p&=0xffffffff;out=[]
        while self.read(p,1):out.append(self.read(p,1));p+=1
        return bytes(out)
    def make_columns(self,p,values):
        self.w(p+8,4,len(values));self.w(p+16,4,p+0x400)
        for i,v in enumerate(values):self.w(p+0x400+i*4,4,v)
    def invoke(self,e,*args):
        covered=self.covered;self.ee_reset();self.covered=covered
        self.r[4:4+len(args)]=[x&MASK for x in args];self.r[28]=0x55c870;self.r[29]=STACK;self.r[31]=0xfffffff0
        self.run_until(e,0xfffffff0);return self.r[2]
    def snapshot(self):
        return (self.read(SELF+12,4),self.read(STATUS+20,4),tuple((self.read(self.read(DB+o,4)+8,4),self.read(self.read(DB+o,4)+16,4)) for o in OFFSETS))
    def call(self,e,args):
        counts={0x38e5f0:5,0x38f800:2,PROPERTY:3,FIND:4,VIRTUAL:2,DBINT:3,DBBOOL:3,DBSTRING:3,0x12a4a4:2}
        assert e in counts,hex(e)
        raw=tuple(args[:counts[e]]);v=[x&0xffffffff for x in raw];self.events.append((e,raw,self.snapshot()))
        if e==0x38e5f0:
            assert v[1]==0x51d550 and v[3:]==[0,0x51d560]
            if self.mutation=='messenger':self.w(STATUS+20,4,0x1a42000)
            return 0
        if e==0x38f800:return self.object_result&MASK
        if e==VIRTUAL:
            if self.mutation=='record':self.w(SELF+12,4,0x80000003)
            return self.virtual_result&MASK
        if e in (DBINT,DBBOOL,DBSTRING):return self.leaf_return&MASK
        if e==FIND:
            if self.mutation=='value_list':self.w(DB+12,4,VALUES+0x1000)
            return self.lookup_results.pop(0)&MASK
        if e==PROPERTY:
            if self.mutation=='columns_zero':self.w(v[0]+8,4,0)
            if self.mutation=='columns_negative':self.w(v[0]+8,4,-1)
            if self.mutation=='columns_relocate':
                self.w(v[0]+8,4,2);self.w(v[0]+16,4,v[0]+0x800);self.w(v[0]+0x800,4,0);self.w(v[0]+0x804,4,NAMES)
            return (self.find_result if self.find_result is not None else NAMES)&MASK
        if e==0x12a4a4:
            self.compares+=1;result=int(self.string(v[0])!=self.string(v[1]))
            if self.mutation=='compare_relocate' and self.compares==1:
                p=COLUMNS;self.w(p+8,4,2);self.w(p+16,4,p+0x800)
                for i in range(3):self.w(p+0x800+i*4,4,NAMES+i*64)
            return result
        return 0

def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();native=DatabaseWorld(image);errors=[];cases=0;coverage=set();depth=0
    @CALL
    def call(_,e,args):
        nonlocal depth
        try:
            if e in native.descend:
                if e==PROPERTY:return objects(C.byref(api),e,args)
                depth+=1
                try:return fn(C.byref(api),e,args,SCRATCH+depth*256)
                finally:depth-=1
            return native.call(e,args)&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-item-database-') as td:
        so=Path(td)/'db.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in ('item-database.c','object-lists.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));fn=lib.dw4_item_database;objects=lib.dw4_object_list
        fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        objects.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];objects.restype=C.c_uint64
        def compare(w,e,*values):
            nonlocal cases,depth
            w.events=[];errors.clear();depth=1
            for k,v in w.__dict__.items():
                if k not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image','frame'):
                    setattr(native,k,v.copy() if isinstance(v,(list,dict,set)) else v)
            expected=w.invoke(e,*values);actual=fn(C.byref(api),e,(C.c_uint64*8)(*[v&MASK for v in values]),SCRATCH+256)
            assert not errors,errors
            assert expected==actual,('return',cases,hex(e),hex(expected),hex(actual))
            def ram(o):return {p:v for p,v in o.mem.items() if v and not STACK-0x10000<=p<STACK+64 and not SCRATCH<=p<SCRATCH+0x10000}
            er,ar=ram(w),ram(native)
            assert er==ar,('RAM',cases,[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert w.events==native.events,('events',cases,hex(e),w.events[:3],native.events[:3])
            cases+=1;coverage.update(w.covered);return expected
        for e,record,key in itertools.product((GETINT,GETBOOL,GETSTRING,DBINT,DBBOOL,DBSTRING),(-1,0,1,2,7),(0,KEYS,KEYS+64,KEYS+128,KEYS+0x400)):
            w=DatabaseWorld(image);w.w(SELF+12,4,record)
            compare(w,e,*((SELF,STATUS,key) if e in (GETINT,GETBOOL,GETSTRING) else (DB,record,key)))
        for family,value in itertools.product(range(3),(0,1,-1,127,128,255,32767,32768,65535,0x7fffffff,0x80000000,0xffffffff)):
            w=DatabaseWorld(image)
            for k in range(family):w.w(COLUMNS+k*0x1000+8,4,0)
            size=(1,2,4)[family];w.w(VALUES+family*0x1000+0x400+3*size,size,value)
            assert compare(w,GETINT,SELF,STATUS,KEYS)==(C.c_int8(value).value if family==0 else C.c_int16(value).value if family==1 else C.c_int32(value).value)&MASK
        for value in (0,1,2,128,255):
            w=DatabaseWorld(image);w.w(VALUES+0x4000+0x403,1,value);assert compare(w,GETBOOL,SELF,STATUS,KEYS)==value
        for pointer in (0,KEYS,0x80001000,0xffffffff):
            w=DatabaseWorld(image);w.w(STRINGS+3*64+8,4,pointer);assert compare(w,GETSTRING,SELF,STATUS,KEYS)==word(pointer or 0x4e0858)
        for chosen,columns,rows in itertools.product(range(6),(1,3,-1,-3),(0,1,27,-27,0x7fffffff,0x80000000)):
            w=DatabaseWorld(image);order=(5,0,1,2,3,4)
            for f in order[:chosen]:w.w(COLUMNS+f*0x1000+8,4,0)
            family=order[chosen];w.w(COLUMNS+family*0x1000+8,4,columns);w.w(VALUES+family*0x1000+8,4,rows);compare(w,COUNT,DB)
        w=DatabaseWorld(image)
        for f in range(6):w.w(COLUMNS+f*0x1000+8,4,0)
        assert compare(w,COUNT,DB)==0
        for mutation,found,record in itertools.product((None,'columns_zero','columns_negative','columns_relocate'),(0,NAMES,NAMES+0x400,0x100000000),(-1,0,1,0x7fffffff,0x80000000)):
            w=DatabaseWorld(image);w.descend.remove(PROPERTY);w.mutation=mutation;w.find_result=found;compare(w,FIND,DB,record,KEYS,COLUMNS)
        for e,value in itertools.product((GETINT,GETBOOL,GETSTRING),(-1,0,1,0x100000000,0x1234567887654321)):
            w=DatabaseWorld(image);w.w(VTABLE+92,4,VIRTUAL);w.mutation='record';w.descend.difference_update((DBINT,DBBOOL,DBSTRING));w.leaf_return=value
            assert compare(w,e,SELF,STATUS,0x1234567800000001)==value&MASK
        for mutation in ('messenger','compare_relocate'):
            w=DatabaseWorld(image);w.mutation=mutation;compare(w,GETINT,SELF,STATUS,KEYS+128)
        for value in (-1,0,1,0x100000000,0x1234567887654321):
            for e in (REQUEST,CHIP):
                w=DatabaseWorld(image);w.object_result=value;assert compare(w,e,SELF,STATUS,0x51d598)==value&MASK
        for e,result in itertools.product((DBINT,DBBOOL,DBSTRING),(-1,0,2,0xffffffff,0x100000000)):
            w=DatabaseWorld(image);w.descend.remove(FIND);w.lookup_results=[result,-1,-1]
            w.w(VALUES+0x3ff,1,0x80);w.w(VALUES+0x4000+0x3ff,1,0xfe)
            w.w(VALUES+0x5000+0x3fc,4,STRINGS);w.w(STRINGS+8,4,KEYS+64)
            compare(w,e,DB,1,KEYS)
        for initial,record in itertools.product((-1,0x80000000,0x7fffffff),(-1,0,1,0x80000000)):
            w=DatabaseWorld(image);w.descend.remove(PROPERTY);w.find_result=NAMES;w.w(COLUMNS+8,4,initial);compare(w,FIND,DB,record,KEYS,COLUMNS)
        print(f'Item/database: {cases} full-return/RAM/ordered-call cases; {len(coverage)} total addresses')
        expected={p for e,n in SIZES.items() for p in range(e,e+n,4)}
        padding={0x3a93cc,0x3a9424}
        assert expected-coverage==padding,sorted(hex(p) for p in expected-coverage-padding)
        assert len(expected)==292 and len(expected&coverage)==290
        assert all(w.read(p,4)==0 for p in padding)
        print('All290 non-padding module words executed;2 zero padding words checked')

if __name__=='__main__':main()
