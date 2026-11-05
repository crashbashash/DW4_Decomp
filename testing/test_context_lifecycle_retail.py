#!/usr/bin/env python3
"""Context lifetime, retained slots and special tracker delegation vs retail."""
import ctypes as C
import itertools
import subprocess
import tempfile
from pathlib import Path
from test_registry_bootstrap_retail import BootstrapWorld,BOOTSTRAP
from test_reflection_registration_retail import ROOT,Api,READ,WRITE,CALL,MASK,STACK,SYSTEM
from test_object_base_retail import SCRATCH
from test_allocator_registry_retail import OWNER
import test_reflection_registration_retail as reg
LIFE={0x2f25d0,0x2f2670,0x2f49e0,0x2f8830,0x2f28d0,0x2f64e0,0x2f6780}
RETURNS={0x2f25d0,0x2f2670}
BUILD,POOL_QUERY,TRACKER_INIT,ATTACH,PREDICATE,PREPARE,CLOSE,BUFFER,DETACH,SIZE,RELEASE_BACKING,MAP=range(0x19b1000,0x19b10c0,0x10)

class LifeWorld(BootstrapWorld):
    def __init__(self,image):
        super().__init__(image);self.descend|=LIFE
        for e in (0x2fef20,0x2ff810,0x2ff820,0x2f04f0,0x2ed460):self.descend.discard(e)
        self.ctx=self.contexts[0];self.pool=self.allocate(16,True);self.tracker=self.allocate(96,True);self.parent=self.allocate(16,True)
        self.pool_vt=self.allocate(400,True);self.tracker_vt=self.allocate(128,True)
        self.w(self.pool,4,self.pool_vt);self.w(self.pool+4,4,1);self.w(self.tracker,4,self.tracker_vt);self.w(self.tracker+4,4,1)
        self.w(self.parent+4,4,1);self.w(OWNER+4,4,1)
        for slot,e in ((360,ATTACH),(356,MAP),(188,PREDICATE),(348,PREPARE),(128,CLOSE),(104,BUFFER),(96,DETACH),(144,SIZE)):self.w(self.pool_vt+slot,4,e)
        self.w(self.tracker_vt+92,4,TRACKER_INIT);self.w(self.tracker_vt+72,4,RELEASE_BACKING);self.w(0x587218,4,self.tracker)
        self.descriptor=self.allocate(96,True);self.text_name=self.allocate(128,True)
        self.w(self.descriptor+60,4,self.text_name);self.w(self.descriptor+80,4,0);self.w(SYSTEM+124,4,99)
        self.index=2;self.row=self.ctx+self.index*144;self.w(self.row+20,4,self.pool);self.w(self.row+152,4,self.descriptor)
        self.buffer=self.allocate(16,True);self.out=self.allocate(4,True)
        self.build_status=0x1234;self.pool_buffer=True;self.owner_found=True;self.predicate=True;self.map_present=True;self.tracker_refs=1
        vt=self.read(self.ctx,4)
        for slot,e in ((92,POOL_QUERY),(204,BUILD),(208,0x2f64e0),(212,0x2f6780)):self.w(vt+slot,4,e)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==0x2fef20:self.events.append((e,v[0]));self.w(v[0],4,0x52f0f0);self.w(v[0]+4,4,0);return v[0]
        if e in (0x2ff810,0x126360,0x2ff820,0x2ed460):
            self.events.append((e,v[0]));self.freed.add(v[0]);return 0
        if e==0x12ad58:
            self.events.append((e,*v[:3]));text=self.string(v[1])
            for i in range(v[2]):self.w(v[0]+i,1,text[i] if i<len(text) else 0)
            return v[0]
        if e==0x12aff0:
            self.events.append((e,*v[:2]));return v[0] if self.string(v[1]) in self.string(v[0]) else 0
        if e==BUILD:
            self.events.append((e,'temp',*v[1:4]));self.w(v[0],4,self.build_status)
            self.w(v[1]+v[2]*144+20,4,self.pool)
            if self.mutation=='build-flags':self.w(self.ctx+12,4,0)
            return 0
        if e==POOL_QUERY:self.events.append((e,*v[:2]));return self.pool
        if e==0x2c5780:
            self.events.append((e,v[0]));self.w(self.tracker+4,4,self.tracker_refs);return self.tracker
        if e==0x2dcc40:self.events.append((e,*v[:2]));return 0
        if e==TRACKER_INIT:self.events.append((e,v[0]));return 0
        if e==ATTACH:
            self.events.append((e,*v[:2]))
            if self.mutation=='retain-tracker':self.w(v[1]+4,4,self.read(v[1]+4,4)+1)
            return 0
        if e==PREDICATE:self.events.append((e,v[0]));return int(self.predicate)
        if e==PREPARE:self.events.append((e,*v[:2]));return 0
        if e==CLOSE:
            self.events.append((e,v[0]))
            if self.mutation=='storage-flags':self.w(self.row+156,4,2)
            return 0
        if e==BUFFER:self.events.append((e,v[0]));return self.buffer if self.pool_buffer else 0
        if e==MAP:self.events.append((e,v[0]));return self.tracker if self.map_present else 0
        if e==DETACH:self.events.append((e,'temp',*v[1:5]));self.w(v[0],4,0xfeed);return 0
        if e==SIZE:self.events.append((e,v[0]));return 0x80000010
        if e==RELEASE_BACKING:self.events.append((e,'temp',v[1],v[2],args[3]&MASK));self.w(v[0],4,0);return 0
        if e==0x2f04f0:self.events.append((e,v[0]));return OWNER if self.owner_found else 0
        return super().call(e,args)

def main():
    reg.STORAGE=reg.FACTORIES=reg.METADATA=reg.INTERNAL=True
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();retail=LifeWorld(image);native=LifeWorld(image)
    errors=[];cases=0;coverage=set();hits=set()
    @CALL
    def call(_,e,args):
        try:return invoke_native(e,args)
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-context-life-') as td:
        so=Path(td)/'life.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in ('context-lifecycle.c','registry-bootstrap.c','allocator-registry.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));fl=lib.dw4_context_lifecycle;fb=lib.dw4_registry_bootstrap
        for f in (fl,fb):f.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];f.restype=C.c_uint64
        def invoke_native(e,args):
            if e in LIFE:return fl(C.byref(api),e,args,SCRATCH+0x800)
            if e in BOOTSTRAP:return fb(C.byref(api),e,args,SCRATCH+0x600)
            return native.call(e,list(args[:8]))&MASK
        def setup():
            nonlocal retail
            retail=LifeWorld(image)
        def compare(entry,*args):
            nonlocal cases
            for k,value in retail.__dict__.items():
                if k not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):setattr(native,k,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            expected=retail.invoke(entry,*args);actual=invoke_native(entry,(C.c_uint64*8)(*[x&MASK for x in args]))
            assert not errors,errors
            if entry in RETURNS:assert expected==actual,(hex(entry),expected,actual)
            def ram(w):return {p:v for p,v in w.mem.items() if not STACK-0x5000<=p<STACK+40 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry);coverage.update(retail.covered);return actual
        setup();compare(0x2f25d0,retail.ctx)
        assert retail.read(retail.ctx+4,4)==1 and retail.read(retail.ctx+8,4)==30
        for i in range(46):assert retail.string(retail.ctx+i*144+24)==retail.string(retail.read(0x4c2170+i*4,4))
        for flag,parent,refs in itertools.product((0,1,0xffff,0x10001),(False,True),(1,2,0x800001)):
            setup();retail.w(retail.ctx+16,4,retail.parent if parent else 0);retail.w(retail.parent+4,4,refs)
            compare(0x2f2670,retail.ctx,flag);assert retail.read(retail.ctx+4,4)==0
        setup();compare(0x2f2670,0,1)
        for active in (0,1):
            setup();retail.w(SYSTEM,1,active);compare(0x2f8830,retail.ctx)
        for index,old,new in itertools.product((-1,2,45,46),(False,True),(0,1,2)):
            setup();retail.w(retail.ctx+8,4,30);retail.w(retail.ctx+index*144+20,4,retail.pool if old else 0)
            value=0 if new==0 else retail.pool if new==1 else retail.tracker
            compare(0x2f28d0,retail.ctx,index,value)
        for flags,index,name,limit,map_present in itertools.product((0,1,2,3),(1,2),(b'',b'UseEventTracker',b'InhibitEventTracker',b'Other'),(0,77),(False,True)):
            setup();retail.index=index;retail.row=retail.ctx+index*144;retail.w(retail.row+152,4,retail.descriptor)
            retail.w(retail.ctx+12,4,flags);retail.text(retail.text_name,name);retail.w(retail.descriptor+80,4,limit);retail.map_present=map_present
            compare(0x2f64e0,retail.out,retail.ctx,index);assert retail.read(retail.out,4)==retail.build_status
        for flags,refs,buffer,owner in itertools.product((0,1,2,3),(1,2,0x800001),(False,True),(False,True)):
            setup();retail.w(retail.pool+4,4,refs);retail.w(retail.row+156,4,flags);retail.pool_buffer=buffer;retail.owner_found=owner
            compare(0x2f6780,retail.ctx,retail.index);assert retail.read(retail.row+20,4)==0
        for mutation in ('build-flags','retain-tracker','storage-flags'):
            setup();retail.mutation=mutation;retail.w(retail.ctx+12,4,3)
            compare(0x2f64e0 if mutation!='storage-flags' else 0x2f6780,*((retail.out,retail.ctx,2) if mutation!='storage-flags' else (retail.ctx,2)))
        for entry in (0x2f2730,0x2f2830,0x2f8920):
            setup();vt=retail.read(retail.ctx,4);retail.w(vt+92,4,0x2f2730);retail.w(vt+96,4,0x2f2830)
            compare(0x2f49e0,retail.ctx)
            retail.w(retail.row+20,4,0);retail.w(retail.row+160,4,0x04000000)
            name=retail.allocate(16,True);retail.text(name,b'Current')
            args=(retail.ctx,2) if entry==0x2f2730 else (retail.ctx,name) if entry==0x2f2830 else (name,)
            compare(entry,*args);assert retail.read(retail.row+20,4)==retail.pool
            assert any(e[0]==BUILD for e in retail.events)
        for index in (-1,46):
            setup();compare(0x2f6780,retail.ctx,index)
        setup();retail.w(retail.ctx+8,4,1);compare(0x2f6780,retail.ctx,2);assert retail.read(retail.ctx+8,4)==2
        setup();retail.predicate=False;retail.w(retail.row+156,4,0);compare(0x2f6780,retail.ctx,2)
        setup();retail.w(retail.ctx+12,4,3);retail.w(retail.row+152,4,0);compare(0x2f64e0,retail.out,retail.ctx,2)
        setup();retail.text(retail.text_name,b'prefixUseEventTrackerSuffix');retail.w(retail.ctx+12,4,0)
        compare(0x2f64e0,retail.out,retail.ctx,2)
        setup();compare(0x2f49e0,retail.ctx)
        assert LIFE<=hits|coverage,LIFE-(hits|coverage)
    print(f'context lifecycle retail: {cases} RAM/defined-return/ordered-call checkpoints; all7 bodies; builder and allocator/tracker virtuals controlled')
if __name__=='__main__':main()
