#!/usr/bin/env python3
"""Complete SUBWND command receiver vs original instructions.

Formatting, enumeration, messages, records, list resize and menu preparation are
controlled leaves. This does not accept actual transactions, prices or native UI.
"""
import ctypes as C
import itertools
import json
from pathlib import Path
import subprocess
import tempfile
from test_subwindow_preparation_retail import PreparationWorld,PREP,WORK,ALTWORK,LISTS,PROPS,FOLDERS,SCRATCH
from test_subwindow_lifecycle_retail import ENTRIES,OWNER,RAM,WINDOW,OLD,ROOT,Api,READ,WRITE,CALL,MASK,STACK

COMMAND=0x3d60e0
MESSAGE,TABLE,MODES,PARAMETERS,ALT_PARAMETERS,NAMEPROP,NAMELIST,NAMEDATA,NAME,OTHERNAME,SPECIESNAME=range(0x1bc0000,0x1c70000,0x10000)
STAT_KEYS=(0x5169e8,0x5169f8,0x516a08,0x516a18,0x516a28,0x516a40,0x516a50,0x516a68,0x516a80,0x516a98,0x516ab0)
ALL_KEYS=list(dict.fromkeys((0x516ad8,0x516ac8,0x516960,0x5169a8,0x516860,0x5169c8,0x5169e0,*STAT_KEYS,0x516ae8,0x516af0)))

class CommandWorld(PreparationWorld):
    def __init__(self,image):
        super().__init__(image);self.descend={COMMAND};self.frame=STACK-400
        self.command=2;self.input_int=0;self.input_string=0x510a58;self.input_mode=0
        self.command_mutation=None;self.command_calls={};self.rename_slot=None;self.out_objects=[];self.out_strings=[];self.out_vectors=[];self.out_bools=[]
        self.w(MESSAGE+20,4,0x511a10);self.w(WORK+8,4,PARAMETERS);self.w(ALTWORK+8,4,ALT_PARAMETERS)
        for p,data,base in ((PARAMETERS,0x1d00000,100),(ALT_PARAMETERS,0x1d01000,300)):
            self.w(p+8,4,13);self.w(p+12,4,32);self.w(p+16,4,data)
            for i in range(13):self.w(data+i*4,4,base+i)
        self.w(NAMEPROP+12,4,NAMELIST);self.w(NAMELIST+16,4,NAMEDATA);self.w(NAMEDATA,4,NAME)
        self.w(NAME+4,4,1);self.w(OTHERNAME+4,4,1)
        for p,text in ((SPECIESNAME,'Agumon'),):
            for i,b in enumerate(text.encode()+b'\0'):self.w(p+i,1,b)
        for player in range(4):
            for i,key in enumerate(ALL_KEYS):self.w(self.prop(player,key)+12,4,100+player*100+i)
            self.w(self.prop(player,0x516960)+12,4,50);self.w(self.prop(player,0x516860)+12,4,1)
    def prop(self,player,key):return PROPS+player*0x1000+ALL_KEYS.index(key)*32
    def snapshot(self):
        return (self.read(OWNER+20,4),self.read(OWNER+32,4),self.read(OWNER+36,4),self.read(OWNER+40,4),
                self.read(RAM+20,1),tuple(self.read(RAM+p,4) for p in (24,28,32,36,44)),
                self.read(NAME+4,4),self.read(OTHERNAME+4,4),tuple(self.values(PARAMETERS)),tuple(self.values(ALT_PARAMETERS)))
    def call(self,e,args):
        counts={0x3bb730:0,0x3b1d70:0,0x38d4a0:3,0x38f320:2,0x38f8f0:2,0x3d8740:2,
                0x3a9340:2,0x3a9580:3,0x129e60:3,0x38f830:2,0x38f670:2,0x38f4b0:2,
                0x38ecf0:4,0x38f150:2,0x2d6790:3}
        if e not in counts:
            result=super().call(e,args)
            if e==0x3a9220 and self.command_mutation=='property_swap':self.w(WORK+8,4,ALT_PARAMETERS)
            return result
        raw=list(args[:counts[e]]);v=[x&0xffffffff for x in raw];normalized=list(raw)
        if e==0x129e60:normalized[0]=('frame',v[0]-self.frame)
        if e==0x38f830:normalized[1]=self.text_at(v[1])
        if e==0x38f4b0:normalized[1]=tuple(self.read(v[1]+i*4,4) for i in range(3))
        self.events.append((e,tuple(normalized),self.snapshot()))
        self.command_calls[e]=self.command_calls.get(e,0)+1
        if e==0x3bb730:return TABLE
        if e==0x3b1d70:return MODES
        if e==0x38d4a0:return self.command&MASK if v[1]==TABLE else self.input_mode&MASK
        if e==0x38f320:
            if self.command_mutation=='work_swap':self.w(RAM+44,4,ALTWORK)
            return self.input_int&MASK
        if e==0x38f8f0:return self.input_string&MASK
        if e==0x3d8740:self.w(RAM+44,4,WORK);return 0
        if e==0x3a9340:return NAMEPROP
        if e==0x3a9580:return SPECIESNAME
        if e==0x129e60:
            value=v[2]-(1<<32) if v[2]>>31 else v[2];text=str(value).encode()+b'\0'
            for i,b in enumerate(text):self.w(v[0]+i,1,b)
            return len(text)-1
        if e==0x38f830:
            self.out_strings.append(self.text_at(v[1]))
            if self.command_mutation=='name_temp':self.w(self.frame+396,4,OTHERNAME)
            if self.command_mutation=='messenger':self.w(OWNER+20,4,0x1c80000)
        if e==0x38f670:
            self.out_objects.append(raw[1])
            if self.command_mutation=='junk_gift':self.w(WORK+32,4,0x87654321)
        if e==0x38f4b0:self.out_vectors.append(tuple(self.read(v[1]+i*4,4) for i in range(3)))
        if e==0x38f150:self.out_bools.append(raw[1])
        if e==0x2d6790:
            if self.command_mutation=='resize_relocate':
                p=self.read(v[0]+16,4);new=p^0x300000
                for i in range(self.read(v[0]+8,4)*4):self.w(new+i,1,self.read(p+i,1))
                self.w(v[0]+16,4,new)
            self.w(v[0]+8,4,v[1]);self.w(v[0]+12,4,v[1])
        return 0


def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();native=CommandWorld(image)
    cases=0;coverage=set();errors=[];depth=0
    @CALL
    def call(_,e,args):
        try:return invoke(e,args)&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-subwindow-command-') as td:
        so=Path(td)/'command.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',
                        *[str(ROOT/'recovered/engine'/p) for p in ('subwindow-command.c','subwindow-preparation.c','subwindow-lifecycle.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));command=lib.dw4_subwindow_command;prep=lib.dw4_subwindow_preparation;life=lib.dw4_subwindow_lifecycle
        for fn in (command,prep):fn.argtypes=[C.POINTER(Api),C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        life.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];life.restype=C.c_uint64
        def invoke(e,args):
            nonlocal depth
            if e not in native.descend:return native.call(e,args)&MASK
            depth+=1;previous=native.frame;native.frame=SCRATCH+depth*512
            try:
                if e==COMMAND:return command(C.byref(api),args,native.frame)
                if e==PREP:return prep(C.byref(api),args,native.frame)
                return life(C.byref(api),e,args,native.frame)
            finally:native.frame=previous;depth-=1
        def compare(w,entry=COMMAND):
            nonlocal cases
            w.events=[];errors.clear()
            for key,value in w.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image','frame'):
                    setattr(native,key,value.copy() if isinstance(value,(list,dict,set)) else value)
            size=400 if entry==COMMAND else 80
            for i in range(size):native.w(SCRATCH+512+i,1,w.read(STACK-size+i,1))
            if PREP in w.descend:
                for i in range(224):native.w(SCRATCH+1024+i,1,w.read(STACK-size-224+i,1))
            result=w.invoke(entry,OWNER,RAM,MESSAGE);actual=invoke(entry,(C.c_uint64*8)(OWNER,RAM,MESSAGE))
            assert not errors,errors
            if entry==COMMAND:assert result==actual,(hex(result),hex(actual))
            def ram(obj):return {p:v for p,v in obj.mem.items() if v and not STACK-0x10000<=p<STACK+64 and not SCRATCH<=p<SCRATCH+0x10000}
            er,ar=ram(w),ram(native)
            assert er==ar,[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12]
            if w.events!=native.events:
                i=next((i for i,(x,y) in enumerate(zip(w.events,native.events)) if x!=y),min(len(w.events),len(native.events)))
                raise AssertionError(('command',w.command,'event',i,w.events[i:i+1],native.events[i:i+1]))
            assert w.out_vectors==native.out_vectors and w.out_strings==native.out_strings and w.out_objects==native.out_objects and w.out_bools==native.out_bools
            cases+=1;coverage.update(w.covered)
        for cmd in (-1,0,1,2,3,4,5,6,7,0x100000000):
            w=CommandWorld(image);w.command=cmd;compare(w)
        for active,root in itertools.product((0,1,2,255),(0,WINDOW)):
            for cmd in (0,1,6):
                w=CommandWorld(image);w.command=cmd;w.w(RAM+20,1,active);w.w(OWNER+32,4,root);compare(w)
        for mode in range(11):
            w=CommandWorld(image);w.command=0;w.w(RAM+20,1,0);w.input_mode=mode;w.input_int=3;compare(w)
        for mode in (-1,0,5,6,7,8,9,10,0x100000006):
            w=CommandWorld(image);w.command=3;w.input_int=mode;compare(w)
        for slot in range(4):
            for cmd in (2,4,5):
                w=CommandWorld(image);w.command=cmd;w.input_int=slot;compare(w)
        for capacity in range(14):
            w=CommandWorld(image);w.w(PARAMETERS+12,4,capacity);compare(w)
        for level,(exp,next_exp) in itertools.product((-2147483648,-1,998,999,1000,2147483647),((0,0),(10,20),(20,10),(0x7fffffff,0x80000000),(0x80000000,0x7fffffff))):
            w=CommandWorld(image);w.w(w.prop(0,0x516960)+12,4,level)
            w.w(w.prop(0,0x516ae8)+12,4,exp);w.w(w.prop(0,0x516af0)+12,4,next_exp);compare(w)
        for value,baseline in itertools.product((-2147483648,-1,0,1,2147483647),repeat=2):
            w=CommandWorld(image);w.command=4
            for i,key in enumerate(STAT_KEYS):w.w(w.prop(0,key)+12,4,value);w.w(w.read(PARAMETERS+16,4)+i*4,4,baseline)
            compare(w)
        for name,refs in itertools.product((0,NAME),(0,1,2,0x800001,0xffffffff)):
            w=CommandWorld(image);w.w(NAMEDATA,4,name);w.w(NAME+4,4,refs);compare(w)
        for mutation in ('work_swap','property_swap','resize_relocate','name_temp','messenger'):
            for cmd in (2,4,5):
                w=CommandWorld(image);w.command=cmd;w.command_mutation=mutation;w.w(PARAMETERS+12,4,0);compare(w)
        w=CommandWorld(image);w.command=3;w.input_int=9;w.command_mutation='junk_gift';compare(w)
        w=CommandWorld(image);w.w(RAM+44,4,0);compare(w)
        # Preparation is really executed on both sides, not a fake prepared result.
        for mode in range(11):
            w=CommandWorld(image);w.descend.add(PREP);w.w(OWNER+40,4,mode);w.w(RAM+44,4,0);compare(w)
        # Persistent menu generation -> stock opening -> stats -> preview ->
        # restoration -> requested removal -> finalization for every service mode.
        for mode in range(11):
            w=CommandWorld(image);w.descend.update(ENTRIES);w.descend.add(PREP)
            w.command=0;w.w(RAM+20,1,0);w.w(RAM+44,4,0);w.input_mode=mode;compare(w)
            w.frame=STACK-80;compare(w,0x3d59b0);w.frame=STACK-400
            for cmd in (2,4,5,3,6,1):w.command=cmd;w.input_int=mode if cmd==3 else 0;compare(w)
            w.root_active=0;w.frame=STACK-80;compare(w,0x3d59b0);w.frame=STACK-400
        expected=set(range(COMMAND,0x3d873c,4));missing=expected-coverage
        extent=next(r for r in json.loads((ROOT/'data/function-extents.json').read_text()) if int(r['address'],0)==COMMAND)
        occupied={p for r in extent['body_ranges'] for p in range(int(r['start'],0),int(r['end_exclusive'],0),4)}
        padding=expected-occupied
        assert len(padding)==21 and missing==padding,sorted(hex(p) for p in missing-padding)
        assert all(w.read(p,4)==0 for p in padding|{0x3d873c})
        assert 0x3d873c not in coverage and len(expected&coverage)==2434
        print(f'SUBWND command: {cases} RAM/return/ordered-call cases, 2434/2455 instruction addresses (21 internal padding NOPs); record/message/format services remain leaves')


if __name__=='__main__':main()
