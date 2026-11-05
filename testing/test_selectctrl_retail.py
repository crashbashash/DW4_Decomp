#!/usr/bin/env python3
"""Full SELECTCTRL update/general receiver against original retail instructions.

Registry, allocation/factories, physical pad sampling, messaging, formatting and
interning remain controlled. The pad-manager lookup executes its real body in
201 direct cases and 216 composed manager cases. These tests establish guest control/ownership behavior,
not rendering, timing, physical pad fidelity or native integration.
"""
import ctypes as C
import itertools
import json
from pathlib import Path
import subprocess
import tempfile
from test_subwindow_lifecycle_retail import LifecycleWorld,ROOT,Api,READ,WRITE,CALL,MASK,STACK

UPDATE,HANDLER,PAD_GET=0x39cbf0,0x39d720,0x39b810
SELF,CTX,INFO,DATA,WORK,OLDWORK,REG,NEWREG,NEWWORK,FLAGS,OLDFLAGS,PAD,ALT,ALTFLAGS=range(0x1c00000,0x1c0e000,0x1000)
PAD_MANAGER,PAD_LIST,PAD_DATA=0x1b01000,0x1c10000,0x1c11000
SCRATCH,POOL,TOKEN,ALLOC=0x1d00000,0x1e00000,0x1e10000,0x1e20000

class SelectWorld(LifecycleWorld):
    def __init__(self,image):
        super().__init__(image);self.descend={UPDATE,HANDLER};self.frame=STACK-240
        self.command=0;self.int_args=[];self.bool_args=[];self.vector_count=0;self.vector=(0x80000000,0x7fc01234,0x3f800000);self.string_count=0;self.string_arg=0x50f8d0
        self.wait=0;self.interned={};self.allocation=True;self.create_registry=NEWREG;self.create_work=NEWWORK;self.create_list=FLAGS
        self.mod=None;self.bool_calls=0;self.results=[];self.count_calls=0;self.int_counts=[];self.ref_events=[]
        self.w(SELF+12,4,0x1c0f000);self.w(SELF+20,4,0x1b00000);self.w(SELF+32,4,0x1b01000)
        self.w(CTX+8,4,2);self.w(CTX+12,4,INFO);self.w(CTX+20,1,1)
        self.w(CTX+24,4,1);self.w(CTX+28,4,0);self.w(CTX+32,4,5);self.w(CTX+36,4,0);self.w(CTX+40,4,REG)
        self.w(INFO+8,4,0x50f800);self.w(DATA+16,1,1);self.w(DATA+20,4,3);self.w(DATA+24,4,1);self.w(DATA+28,4,WORK)
        for p in (WORK,OLDWORK,NEWWORK,REG,NEWREG,FLAGS,OLDFLAGS,ALT,ALTFLAGS):self.w(p+4,4,1)
        for p in (WORK,OLDWORK,NEWWORK):
            for i,x in enumerate((0x80000000,0,0x7fc00001)):self.w(p+8+i*4,4,x)
            self.w(p+20,4,3);self.w(p+24,1,1);self.w(p+28,4,TOKEN);self.w(p+32,4,0)
        self.w(TOKEN-8,4,POOL);self.w(TOKEN-4,4,1);self.text(TOKEN,b'old_sequence')
        for p in (FLAGS,OLDFLAGS,ALTFLAGS):
            self.w(p+8,4,0);self.w(p+12,4,8);self.w(p+16,4,p+0x20000)
            for i,b in enumerate((1,0,255,2,0,1,1,1)):self.w(p+0x20000+i,1,b)
        self.w(0x586f20,4,POOL);self.w(0x585be0,4,0x1234)
        self.w(PAD_MANAGER+20,4,PAD_LIST);self.w(PAD_MANAGER+29,1,0);self.w(PAD_LIST+16,4,PAD_DATA)
        for i in range(-1,5):self.w(PAD_DATA+i*4,4,PAD+(i+1)*256)
    def text(self,p,value):
        for i,b in enumerate(value+b'\0'):self.w(p+i,1,b)
    def string(self,p):
        p&=0xffffffff;out=[]
        while self.read(p,1):out.append(self.read(p,1));p+=1
        return bytes(out)
    def snapshot(self):
        return (tuple(self.read(CTX+i,4) for i in (8,12,20,24,28,32,36,40)),self.read(SELF+20,4),
                tuple(self.read(DATA+i,4) for i in (16,20,24,28)),
                tuple(tuple(self.read(p+i,4) for i in (4,8,12,16,20,24,28,32)) for p in (WORK,NEWWORK,FLAGS,OLDFLAGS)),
                tuple(self.results))
    def call(self,e,args):
        counts={0x301000:1,0x2f88e0:1,0x36ae80:1,0x345680:1,0x2cb0d0:1,0x3022c0:3,0x2ff820:1,
                0x3459a0:0,0x38d4a0:3,0x38f240:1,0x38f320:2,0x38f4a0:1,0x38f560:3,
                0x38f820:1,0x38f8f0:2,0x12a4a4:2,0x38f0f0:1,0x38f220:2,0x38f150:2,0x38f250:2,
                0x2d6790:3,0x39b810:2,0x38d860:4,0x38e5f0:5,0x38f4b0:2,0x38f830:2,0x38e060:2,
                0x129e60:3,0x2eb010:1,0x2eadf0:1,0x2eaf60:2,0x30c940:2,0x38e5d0:2}
        assert e in counts,hex(e)
        raw=list(args[:counts[e]]);v=[x&0xffffffff for x in raw];norm=list(raw)
        if e in (0x129e60,0x38f560):norm[0]=('frame',v[0]-self.frame)
        if e==0x38f4b0:norm[1]=('vector',tuple(self.read(v[1]+i*4,4) for i in range(3)))
        for i in ({0x38e5f0:(4,),0x2eaf60:(1,)}.get(e,())):
            if STACK-0x2000<=v[i]<STACK or SCRATCH<=v[i]<SCRATCH+0x10000:norm[i]=('text',self.string(v[i]))
        self.events.append((e,tuple(norm),self.snapshot()))
        if self.mod=='messenger' and e in (0x38d860,0x38e5f0,0x38f830,0x38f320,0x38f240):self.w(SELF+20,4,ALT)
        if e==0x38d860 and self.mod=='select_sequence':
            token=TOKEN+0x800;self.w(token-8,4,POOL);self.w(token-4,4,2);self.text(token,b'callback_sequence')
            for work in (WORK,NEWWORK):self.w(work+28,4,token)
        if e==0x301000:
            if self.mod=='allocator_list':self.w(self.read(DATA+28,4)+32,4,OLDFLAGS)
            return ALLOC
        if e==0x2f88e0:return ALLOC+256
        if e==0x36ae80:
            if self.mod=='registry_old':self.w(CTX+40,4,ALT)
            return self.create_registry
        if e==0x345680:
            if self.mod=='work_old':self.w(DATA+28,4,OLDWORK)
            return self.create_work
        if e==0x2cb0d0:return self.create_list
        if e==0x2ff820:
            self.ref_events.append(v[0])
            if self.mod=='delete_temp':self.w(self.frame+156,4,ALT)
            if self.mod=='registry_temp':self.w(self.frame+(144 if self.entry==HANDLER else 236),4,ALT)
            return 0
        if e==0x3022c0:return DATA
        if e==0x3459a0:return 0x1b02000
        if e==0x38d4a0:return self.command&MASK
        if e==0x38f240:
            self.count_calls+=1
            return (self.int_counts.pop(0) if self.int_counts else len(self.int_args))&MASK
        if e==0x38f320:return self.int_args[v[1]]&MASK if v[1]<len(self.int_args) else 0
        if e==0x38f4a0:return self.vector_count
        if e==0x38f560:
            for i,n in enumerate(self.vector):self.w(v[0]+i*4,4,n)
            return 0
        if e==0x38f820:return self.string_count
        if e==0x38f8f0:return self.string_arg
        if e==0x12a4a4:return int(self.string(v[0])!=self.string(v[1]))
        if e==0x38f0f0:return len(self.bool_args)&MASK
        if e==0x38f220:
            if self.mod=='wait_state':self.w(CTX+24,4,0x7fffffff);self.w(CTX+28,4,99)
            self.bool_calls+=1
            if self.mod=='flag_temp':self.w(self.frame+152,4,ALTFLAGS);self.w(self.frame+148,4,ALTFLAGS)
            return (self.bool_args[v[1]] if v[1]<len(self.bool_args) else self.wait)&MASK
        if e in (0x38f150,0x38f250):self.results.append((e,raw[1]));return 0
        if e==0x2d6790:
            if self.mod=='relocate':self.w(v[0]+16,4,self.read(v[0]+16,4)+0x1000)
            self.w(v[0]+8,4,v[1]);self.w(v[0]+12,4,v[1]+4);return 0
        if e==0x39b810:
            if self.mod=='pad_context':self.w(CTX+24,4,2);self.w(DATA+28,4,OLDWORK)
            if self.mod=='pad_info':self.w(CTX+12,4,ALT);self.w(ALT+8,4,0)
            return PAD
        if e==0x129e60:
            n=v[2]-(1<<32) if v[2]>>31 else v[2]
            text=self.string(v[1]).replace(b'%02d',f'{n:02d}'.encode()).replace(b'%d',str(n).encode());self.text(v[0],text);return len(text)
        if e==0x2eb010:return POOL if self.allocation else 0
        if e==0x2eadf0:return v[0]
        if e==0x2eaf60:
            if self.mod=='intern_name':self.w(INFO+8,4,0);self.w(CTX+8,4,3)
            if self.mod=='intern_old':self.w(self.read(DATA+28,4)+28,4,0)
            text=self.string(v[1])
            if text not in self.interned:
                p=TOKEN+0x100+len(self.interned)*256;self.interned[text]=p;self.w(p-8,4,POOL);self.w(p-4,4,0);self.text(p,text)
            p=self.interned[text];self.w(p-4,4,self.read(p-4,4)+1);return p
        return 0


def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();native=SelectWorld(image);errors=[];cases=0;coverage=set()
    @CALL
    def call(_,e,args):
        try:
            if e==PAD_GET and e in native.descend:return get_pad(C.byref(api),args[0],args[1])
            return native.call(e,args)&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-selectctrl-') as td:
        so=Path(td)/'selectctrl.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',str(ROOT/'recovered/engine/selectctrl.c'),str(ROOT/'recovered/engine/pad-manager-selection.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));get_pad=lib.dw4_pad_manager_selection;get_pad.argtypes=[C.POINTER(Api),C.c_uint64,C.c_uint64];get_pad.restype=C.c_uint64
        fn=lib.dw4_selectctrl_manager;fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        def compare(w,entry=UPDATE,values=None):
            nonlocal cases
            w.entry=entry;w.frame=STACK-(160 if entry==HANDLER else 240);w.events=[];errors.clear()
            for k,value in w.__dict__.items():
                if k not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image','frame'):
                    setattr(native,k,value.copy() if isinstance(value,(list,dict,set)) else value)
            native.frame=SCRATCH+512
            size=160 if entry==HANDLER else 240
            for i in range(size):native.w(native.frame+i,1,w.read(w.frame+i,1))
            if values is None:values=(SELF,CTX,0x1b03000)
            values=tuple(x&MASK for x in values)
            expected=w.invoke(entry,*values)
            actual=get_pad(C.byref(api),values[0],values[1]) if entry==PAD_GET else fn(C.byref(api),entry,(C.c_uint64*8)(*values),native.frame)
            assert not errors,errors
            if entry in (HANDLER,PAD_GET):assert expected==actual,('return',hex(expected),hex(actual))
            def ram(obj):return {p:v for p,v in obj.mem.items() if v and not STACK-0x10000<=p<STACK+64 and not SCRATCH<=p<SCRATCH+0x10000}
            er,ar=ram(w),ram(native)
            assert er==ar,('RAM',hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:15])
            if w.events!=native.events:
                i=next((i for i,(x,y) in enumerate(zip(w.events,native.events)) if x!=y),min(len(w.events),len(native.events)))
                raise AssertionError(('event',hex(entry),i,w.events[i:i+1],native.events[i:i+1]))
            coverage.update(w.covered);cases+=1
        for command,active,state,sub in itertools.product(range(9),(0,1,255),(0,1,2,3,10,0xffffffff),(0,1,2)):
            w=SelectWorld(image);w.command=command;w.w(CTX+20,1,active);w.w(CTX+24,4,state);w.w(CTX+28,4,sub);compare(w,HANDLER)
        for ints,flags,vec,string,reg in itertools.product(([],[3],[3,2],[0],[-1]),([], [1,0,255]),(0,1),(0,1),(0,REG)):
            w=SelectWorld(image);w.int_args=list(ints);w.bool_args=list(flags);w.vector_count=vec;w.string_count=string;w.w(CTX+40,4,reg);compare(w,HANDLER)
        for state,sub,active,wait in itertools.product((0,1,2,3,10,4,0xffffffff),range(4),(0,1,255),(0,1,2,256,257,0x100000000)):
            w=SelectWorld(image);w.w(CTX+24,4,state);w.w(CTX+28,4,sub);w.w(CTX+20,1,active);w.wait=wait;compare(w)
        for orientation,selected,repeat,direction in itertools.product((0,1,255),(0,1,2),range(16),range(0,256,16)):
            w=SelectWorld(image);w.w(DATA+16,1,orientation);w.w(DATA+24,4,selected);w.w(PAD+36,4,repeat);w.w(PAD+68,4,direction);compare(w)
        for selected,buttons,cancel,flags in itertools.product((0,1,2),(0x2000,0x4000,0x6000),(0,1,255),(0,FLAGS)):
            w=SelectWorld(image);w.w(DATA+24,4,selected);w.w(PAD+72,4,buttons);w.w(WORK+24,1,cancel);w.w(WORK+32,4,flags);compare(w)
        # Both typed factory paths, old owners, fallback allocators, retained
        # temporaries and byte-list growth use original call-stream comparison.
        for command,reg,allocator,refs,capacity in itertools.product((0,4),(0,REG),(0,1),(0,1,2,0x800001,0xffffffff),(0,8)):
            w=SelectWorld(image);w.command=command;w.int_args=[3,2];w.bool_args=[1,0,255]
            w.w(CTX+40,4,reg);w.w(0x554c14,1,allocator);w.w(FLAGS+12,4,capacity)
            w.w(WORK+32,4,OLDFLAGS);w.w(NEWWORK+32,4,OLDFLAGS)
            for p in (REG,NEWREG,WORK,NEWWORK,FLAGS,OLDFLAGS):w.w(p+4,4,refs)
            compare(w,HANDLER)
        for entry,mod,refs in itertools.product((UPDATE,HANDLER),('registry_old','work_old','delete_temp','registry_temp','messenger','relocate','flag_temp'),(0,1,2,0x800001)):
            w=SelectWorld(image);w.mod=mod;w.int_args=[3,2];w.bool_args=[1,0,255]
            w.w(CTX+40,4,0);w.w(FLAGS+12,4,0);w.w(NEWWORK+32,4,OLDFLAGS)
            for p in (ALT,OLDWORK,NEWREG,NEWWORK,OLDFLAGS):w.w(p+4,4,refs)
            compare(w,entry)
        for state,sub,missing_name,reg,allocator in itertools.product((0,1,2,3,10),(0,1),(0,1),(0,REG),(0,1)):
            w=SelectWorld(image);w.w(CTX+24,4,state);w.w(CTX+28,4,sub);w.w(INFO+8,4,0 if missing_name else 0x50f800)
            w.w(CTX+40,4,reg);w.w(0x554c14,1,allocator);w.w(PAD+36,4,1);compare(w)
        for state,sub,selected,pool,allocation,refs in itertools.product((1,2),(0,1),(-1,0,1),(0,POOL),(False,True),(0,1,2)):
            w=SelectWorld(image);w.w(CTX+24,4,state);w.w(CTX+28,4,sub);w.w(DATA+24,4,selected)
            w.w(0x586f20,4,pool);w.allocation=allocation;w.w(TOKEN-4,4,refs);w.w(PAD+36,4,1);w.w(PAD+72,4,0x4000)
            compare(w)
        for state,sub,count in itertools.product((1,),(0,2),(-2147483648,-1,0,15,16,17,0x7fffffff)):
            w=SelectWorld(image);w.w(CTX+24,4,state);w.w(CTX+28,4,sub);w.w(CTX+32,4,count);w.w(CTX+36,4,1);w.w(PAD+36,4,1);compare(w)
        for command,ints,flags in itertools.product((0,4),([0],[-1],[3],[3,2],[3,1,2]),([],[1],[1,0,255])):
            w=SelectWorld(image);w.command=command;w.int_args=list(ints);w.bool_args=list(flags);w.string_count=1;w.string_arg=TOKEN;compare(w,HANDLER)
        for entry in (UPDATE,HANDLER):
            w=SelectWorld(image);w.w(CTX+40,4,0);w.create_registry=0;compare(w,entry)
        for repeat,buttons,allocation in itertools.product((0,1,4),(0,0x4000),(False,True)):
            w=SelectWorld(image);w.w(INFO+8,4,0);w.w(PAD+36,4,repeat);w.w(PAD+72,4,buttons);w.w(0x586f20,4,0);w.allocation=allocation;compare(w)
        for wait in (0,1,256,257,0x100000000):
            w=SelectWorld(image);w.w(INFO+8,4,0);w.w(CTX+36,4,1);w.w(PAD+36,4,1);w.wait=wait;compare(w)
        for entry,refs in itertools.product((UPDATE,HANDLER),(0,1,2,0x800001,0xffffffff)):
            w=SelectWorld(image);w.w(CTX+40,4,0);w.w(NEWREG+4,4,refs);w.mod='registry_old';w.w(ALT+4,4,refs);compare(w,entry)
        for selected in (-2147483648,-1,0,1,0x7fffffff):
            for maximum in (-2147483648,-1,0,1,0x7fffffff):
                for repeat in (1,4):
                    w=SelectWorld(image);w.w(DATA+24,4,selected);w.w(WORK+20,4,maximum);w.w(PAD+36,4,repeat);compare(w)
        for command,kind in itertools.product((0,4),('create_work','create_list')):
            w=SelectWorld(image);w.command=command;w.int_args=[3,2];w.bool_args=[1,0,255];setattr(w,kind,0);compare(w,HANDLER)
        for entry in (UPDATE,HANDLER):
            w=SelectWorld(image);w.mod='registry_temp';w.w(CTX+40,4,0);w.w(NEWREG+4,4,0);compare(w,entry)
        for mode in ('accept','cancel','remove','top','reject'):
            w=SelectWorld(image);w.int_args=[3,1];w.bool_args=[1,0,255];compare(w,HANDLER)
            assert w.read(CTX+24,4)==0 and w.read(DATA+28,4)==NEWWORK
            w.bool_args=[];compare(w);compare(w)
            assert w.read(CTX+24,4)==1
            if mode=='top':
                w.command=4;w.int_args=[3];compare(w,HANDLER)
                assert w.read(CTX+24,4)==10 and w.read(DATA+24,4)==0
                compare(w);compare(w)
                assert w.read(CTX+24,4)==1
                w.command=5;compare(w,HANDLER);assert w.results[-1]==(0x38f150,0)
            if mode=='reject':
                w.w(PAD+72,4,0x4000);compare(w);w.w(PAD+72,4,0)
                assert w.read(CTX+28,4)==2
                for _ in range(17):compare(w)
                assert w.read(CTX+24,4)==1 and w.read(CTX+28,4)==0
            if mode=='remove':w.command=6;compare(w,HANDLER)
            elif mode=='cancel':w.w(PAD+72,4,0x6000);compare(w)
            else:
                w.w(PAD+36,4,4);compare(w);w.w(PAD+36,4,0)
                assert w.read(DATA+24,4)==(1 if mode=='top' else 2)
                if mode=='top':w.w(DATA+24,4,2)
                w.w(PAD+72,4,0x4000);compare(w);w.w(PAD+72,4,0);compare(w)
            w.w(PAD+72,4,0);compare(w);compare(w);compare(w)
            assert not w.read(CTX+20,1) and not w.read(DATA+28,4)
            assert w.read(DATA+24,4)==(0xffffffff if mode in ('cancel','remove') else 2)
            assert (b'SQ_CANCEL' if mode in ('cancel','remove') else b'SQ_CLOSE') in w.interned
            w.command=1;compare(w,HANDLER);assert w.results[-1]==(0x38f150,1)
        for command in (-1,0x100000000,0x100000001,0x7fffffffffffffff):
            w=SelectWorld(image);w.command=command;compare(w,HANDLER)
        for count,capacity in itertools.product((-2147483648,-1,0,0x7fffffff),(-2147483648,-1,0,0x7fffffff)):
            w=SelectWorld(image);w.int_args=[3];w.bool_args=[0x100,0x101,0x100000000]
            w.w(FLAGS+8,4,count);w.w(FLAGS+12,4,capacity);compare(w,HANDLER)
        for state,sub,mod in itertools.product((0,1,2,10),(0,1),('pad_context','pad_info','wait_state','intern_name','intern_old','messenger')):
            w=SelectWorld(image);w.mod=mod;w.w(CTX+24,4,state);w.w(CTX+28,4,sub)
            w.w(PAD+36,4,4);w.w(PAD+72,4,0x4000);compare(w)
        for command in (0,4):
            w=SelectWorld(image);w.command=command;w.mod='allocator_list';w.int_args=[3];w.bool_args=[1,2,3];compare(w,HANDLER)
        for cancel,string_count,string_arg in itertools.product((0,1,255),(0,1),(0x50f8d0,TOKEN)):
            w=SelectWorld(image);w.w(NEWWORK+24,1,cancel);w.string_count=string_count;w.string_arg=string_arg;compare(w,HANDLER)
            assert w.read(NEWWORK+24,1)==(0 if string_count and string_arg==0x50f8d0 else cancel)
        for counts in ([0],[1,2],[1,0],[2,3],[-1,2],[0x100000000,2]):
            w=SelectWorld(image);w.int_args=[3,2];w.int_counts=list(counts);compare(w,HANDLER)
        for state,sub,wait in itertools.product((0,1,2,10),(0,1),(0,1)):
            w=SelectWorld(image);w.mod='select_sequence';w.w(CTX+24,4,state);w.w(CTX+28,4,sub);w.w(PAD+36,4,1);w.w(CTX+36,4,1);w.wait=wait;compare(w)
        manager_cases=cases
        for disabled,all_devices,index,count in itertools.product((0,1,255),(0,1,255),(-2147483648,-1,0,1,2,3,4,5,2147483647,0xffffffff,0x100000001),(0,5)):
            w=SelectWorld(image);w.descend.add(PAD_GET);w.w(PAD_MANAGER+29,1,disabled);w.w(PAD_MANAGER+28,1,all_devices);w.w(PAD_LIST+8,4,count)
            compare(w,PAD_GET,(PAD_MANAGER,index))
            chosen=4 if disabled or index>=4 else index
            address=PAD_DATA+((chosen&0xffffffff)*4&0xffffffff)
            value=w.read(address,4);expected=value-(1<<32) if value>>31 else value
            assert w.invoke(PAD_GET,PAD_MANAGER,index)==expected&MASK
        for pointer in (0,0x81234567,0xffffffff):
            w=SelectWorld(image);w.descend.add(PAD_GET);w.w(PAD_DATA+8,4,pointer);compare(w,PAD_GET,(PAD_MANAGER,2))
        direct_cases=cases-manager_cases
        for player,disabled,orientation,repeat,buttons in itertools.product(range(4),(0,1,255),(0,1),(0,1,4),(0,0x4000,0x6000)):
            w=SelectWorld(image);w.descend.add(PAD_GET);w.w(CTX+8,4,player);w.w(PAD_MANAGER+29,1,disabled);w.w(DATA+16,1,orientation)
            selected=4 if disabled else player;pad=PAD+(selected+1)*256
            w.w(pad+36,4,repeat);w.w(pad+72,4,buttons);compare(w)
            if buttons&0x2000:assert w.read(DATA+24,4)==0xffffffff
        composition_cases=cases-manager_cases-direct_cases
        rows=json.loads((ROOT/'data/function-extents.json').read_text());wanted=set();padding=set()
        for r in rows:
            entry=int(r['address'],0)
            if entry not in (UPDATE,HANDLER):continue
            span=set(range(entry,int(r['end_exclusive'],0),4));occupied={p for b in r['body_ranges'] for p in range(int(b['start'],0),int(b['end_exclusive'],0),4)}
            wanted|=span;padding|=span-occupied
        wanted.update(range(PAD_GET,PAD_GET+88,4));padding.add(PAD_GET+28)
        missing=wanted-coverage

        groups=[]
        for p in sorted(missing-padding):
            if groups and p==groups[-1][-1]+4:groups[-1].append(p)
            else:groups.append([p])
        if groups:print('missing',[(hex(g[0]),hex(g[-1]),len(g)) for g in groups])
        for p in padding:assert w.read(p,4)==0,hex(p)
        assert not (missing-padding),len(missing-padding)
        print(f'SELECTCTRL: {manager_cases} manager, {direct_cases} direct pad selection, {composition_cases} manager/pad composition ({cases} total) RAM/ordered-call cases, {len(coverage&wanted)}/{len(wanted)} instruction addresses ({len(padding)} reviewed padding words); engine/renderer and physical pad sampling remain controlled')

if __name__=='__main__':main()
