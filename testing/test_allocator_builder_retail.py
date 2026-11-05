#!/usr/bin/env python3
"""Complete slot204 allocator builder vs original instructions and RAM."""
import ctypes as C
import itertools
import subprocess
import tempfile
from pathlib import Path
from test_context_lifecycle_retail import LifeWorld,LIFE,POOL_QUERY
from test_registry_bootstrap_retail import BOOTSTRAP
from test_reflection_registration_retail import ROOT,Api,READ,WRITE,CALL,MASK,STACK,SYSTEM
from test_object_base_retail import SCRATCH
import test_reflection_registration_retail as reg
BUILD=0x2f5cd0
META={0x2fe460,0x2d3070}
ALIGNMENT,ALLOC_SYSTEM,ENABLE,READY,RESIZE,CONFIGURE,APPLY,PROXY_SET,LOOKUP_ALIAS,LOOKUP_NAME=range(0x19b2000,0x19b20a0,0x10)
ALLOC_BACKING=0x19b20a0
class BuilderWorld(LifeWorld):
    def read(self,p,n):
        p&=0xffffffff
        return sum((self.mem[p+i] if p+i in self.mem else super(BuilderWorld,self).read(p+i,1))<<(8*i) for i in range(n))
    def __init__(self,image):
        super().__init__(image);self.descend.add(BUILD);self.descend.difference_update({0x2f88e0,0x2fda40,0x2fe460,0x2cd170})
        self.index=4;self.row=self.ctx+self.index*144;self.w(self.row+20,4,0);self.w(self.row+152,4,self.descriptor)
        self.primary_pool,self.current_pool,self.nontracked_pool=self.pools
        self.alias=self.allocate(16,True);self.proxy=self.allocate(16,True)
        for p in (self.primary_pool,self.current_pool,self.nontracked_pool,self.alias,self.proxy):
            self.w(p,4,self.pool_vt);self.w(p+4,4,10 if p in self.pools else 1)
        for slot,e in ((132,READY),(120,ENABLE),(172,RESIZE),(96,CONFIGURE),(180,APPLY),(216,ALLOC_BACKING),(400,PROXY_SET)):self.w(self.pool_vt+slot,4,e)
        self.w(self.tracker_vt+84,4,ALIGNMENT);self.w(self.tracker_vt+68,4,ALLOC_SYSTEM)
        vt=self.read(self.ctx,4)
        for slot,e in ((204,BUILD),(100,0x2f28d0),(116,LOOKUP_ALIAS),(96,LOOKUP_NAME)):self.w(vt+slot,4,e)
        self.w(self.ctx+20,4,self.primary_pool);self.w(self.ctx+164,4,self.current_pool);self.w(self.ctx+452,4,self.nontracked_pool)
        self.default_meta=0x18d0000;self.named_meta=0x18d0100;self.alias_meta=0x18d0200
        self.w(0x586a88,4,self.default_meta)
        for g,value in ((0x587018,0),(0x587020,1),(0x587030,3),(0x587040,2)):self.w(g,4,value)
        self.w(0x4fb410,4,0x1234);self.w(0x4fb418,4,0x5678)
        self.alias_name=self.allocate(32,True);self.text(self.alias_name,b'alias')
        self.class_name=self.allocate(32,True);self.text(self.class_name,b'PoolClass')
        self.kind=self.allocate(32,True);self.backing_name=self.allocate(32,True);self.options=self.allocate(128,True)
        for off in (24,28,36,40,44,48,52):self.w(self.descriptor+off,4,0)
        self.alias_index=10;self.alias_lookup=True;self.named_backing=True;self.class_found=True;self.allocator_ready=True
        self.w(self.ctx+10*144+20,4,self.alias)
        self.alignments=[16,16];self.alignment_calls=0;self.default_current=True;self.special_lookup=True
        self.outputs=[];self.actual_meta=False
        self.meta_list=self.allocate(16,True);self.meta_data=self.allocate(8,True);self.meta_selector=self.allocate(16,True)
        self.w(self.meta_list+8,4,self.meta_data);self.w(self.meta_list+12,4,2);self.w(self.meta_selector+8,4,28)
        self.w(SYSTEM+24,4,self.meta_list);self.w(0x585c28,4,self.meta_selector)
        for i,(meta,name) in enumerate(((self.named_meta,b'PoolClass'),(self.alias_meta,b'AliasClass'))):
            text=self.allocate(32,True);self.text(text,name);self.w(meta+28,4,text);self.w(self.meta_data+i*4,4,meta)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==0x2f88e0:
            self.events.append((e,v[0]))
            return self.primary_pool if v[0]==0 else (self.current_pool if self.default_current else 0) if v[0]==1 else self.nontracked_pool if v[0]==3 else self.current_pool if self.special_lookup else 0
        if e==0x2ea780:
            for i in range(self.read(v[0]+12,4)):
                meta=self.read(self.read(v[0]+8,4)+i*4,4);name=self.read(meta+self.read(v[1]+8,4),4)
                if not self.call(0x12a4a4,[name,v[2],0,0,0,0,0,0]):return self.read(self.read(v[0]+8,4)+i*4,4)
            return 0
        if e==LOOKUP_ALIAS:self.events.append((e,*v[:2]));return self.alias_index if self.alias_lookup else MASK
        if e==LOOKUP_NAME:self.events.append((e,*v[:2]));return self.primary_pool if self.named_backing else 0
        if e==0x2fe460:
            self.events.append((e,v[0]))
            if self.string(v[0])==b'AliasClass':return self.alias_meta
            if self.mutation=='meta-fallback':self.w(0x586a88,4,self.named_meta)
            return self.named_meta if self.class_found else 0
        if e==0x2fda40:
            self.events.append((e,*v[:2]));p=self.alias if v[0]==self.alias_meta else self.pool;self.w(p+4,4,1);return p
        if e==0x2cd170:self.events.append((e,v[0]));self.w(self.proxy+4,4,1);return self.proxy
        if e==PROXY_SET:self.events.append((e,*v[:2]));return 0
        if e==ALIGNMENT:
            self.events.append((e,v[0]));i=min(self.alignment_calls,1);self.alignment_calls+=1;return self.alignments[i]
        if e==READY:self.events.append((e,v[0]));return int(self.allocator_ready)
        if e==ENABLE:self.events.append((e,v[0]));return 0
        if e in (RESIZE,CONFIGURE,APPLY):
            n=3 if e in (RESIZE,APPLY) else 5
            self.events.append((e,'temp',v[1],args[2]&MASK) if e==RESIZE else (e,'temp',*v[1:n]));self.w(v[0],4,0xbeef);self.outputs.append((e,*v[1:n]))
            if self.mutation=='status':self.w(0x4fb410,4,0xabcd)
            return 0
        if e in (ALLOC_SYSTEM,ALLOC_BACKING):
            n=3 if e==ALLOC_SYSTEM else 2;self.events.append((e,*v[:n]))
            return self.allocate(v[2] if e==ALLOC_SYSTEM else v[1])
        return super().call(e,args)

def main():
    reg.STORAGE=reg.FACTORIES=reg.METADATA=reg.INTERNAL=True
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();retail=BuilderWorld(image);native=BuilderWorld(image)
    cases=0;coverage=set();errors=[];depth=0
    @CALL
    def call(_,e,args):
        try:return invoke_native(e,args)
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-allocator-builder-') as td:
        so=Path(td)/'builder.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in ('allocator-builder.c','context-lifecycle.c','registry-bootstrap.c','allocator-registry.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));functions=(lib.dw4_allocator_builder,lib.dw4_context_lifecycle,lib.dw4_registry_bootstrap)
        for f in functions:f.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];f.restype=C.c_uint64
        def invoke_native(e,args):
            nonlocal depth
            if e==0x2f88e0 or (e in META and not native.actual_meta):return native.call(e,list(args[:8]))&MASK
            fn=functions[0] if e==BUILD or e in META else functions[1] if e in LIFE else functions[2] if e in BOOTSTRAP else None
            if fn:
                depth+=1
                try:return fn(C.byref(api),e,args,SCRATCH+0xa00+depth*0x100)
                finally:depth-=1
            return native.call(e,list(args[:8]))&MASK
        def setup():
            nonlocal retail
            retail=BuilderWorld(image)
        def compare(entry,*args):
            nonlocal cases
            for k,value in retail.__dict__.items():
                if k not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):setattr(native,k,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            retail.invoke(entry,*args);invoke_native(entry,(C.c_uint64*8)(*[x&MASK for x in args]))
            assert not errors,errors
            def ram(w):return {p:v for p,v in w.mem.items() if not STACK-0x5000<=p<STACK+40 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,([(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(retail.events,native.events)
            cases+=1;coverage.update(retail.covered)
        def build(mode=1,index=None):
            index=retail.index if index is None else index
            compare(BUILD,retail.out,retail.ctx,index,mode)
        for index in (0,2,29,30,45):
            setup();retail.w(retail.ctx+index*144+152,4,0);build(index=index)
            assert retail.read(retail.out,4)==(0x1234 if index>=30 else 0x5678)
        for primary,current,nontracked,found in itertools.product((False,True),repeat=4):
            setup();retail.default_current=found
            if not primary:retail.w(retail.ctx+20,4,0)
            if not current:retail.w(retail.ctx+164,4,0)
            if not nontracked:retail.w(retail.ctx+452,4,0)
            build()
        option_values=(b'',b'Level',b'Frame',b'LongTerm Level Frame',b'Level Create',b'Frame Reset',b'Level OnDemand',b'LongTerm OnDemand',b'Level Frame Create Reset OnDemand')
        for option,mode in itertools.product(option_values,(0,1)):
            setup();retail.text(retail.options,option);retail.w(retail.descriptor+52,4,retail.options);build(mode)
            assert retail.read(retail.out,4)==0x1234
        for length,kind,ready in itertools.product((0,32),(None,b'Dynamic',b'Fixed',b'Other'),(False,True)):
            setup();retail.allocator_ready=ready;retail.w(retail.row+20,4,retail.pool);retail.w(retail.descriptor+28,4,length)
            if kind is not None:retail.text(retail.kind,kind);retail.w(retail.descriptor+44,4,retail.kind)
            build()
        setup();retail.w(retail.row+20,4,retail.pool);retail.w(retail.descriptor+28,4,0x80000010)
        build();assert any(e[0]==RESIZE and e[3]==0xffffffff80000010 for e in retail.events)
        for wrap,present,lookup,mode,on_demand,index in itertools.product((False,True),(False,True),(False,True),(0,1),(False,True),(4,5)):
            setup();retail.index=index;retail.row=retail.ctx+index*144;retail.w(retail.row+152,4,retail.descriptor)
            retail.w(retail.ctx+12,4,4 if wrap else 0);retail.w(retail.descriptor+24,4,retail.alias_name);retail.alias_lookup=lookup
            if not present:retail.w(retail.ctx+10*144+20,4,0)
            if on_demand:retail.text(retail.options,b'OnDemand');retail.w(retail.descriptor+52,4,retail.options)
            build(mode,index)
        for kind,backing,length,named in itertools.product((None,b'Dynamic',b'Fixed',b'Other'),(None,b'SystemMemory',b'Low',b'High',b'Virtual',b'HighSpeed',b'Raw',b'Custom',b'Named'),(0,33),(False,True)):
            setup();retail.named_backing=named;retail.w(retail.descriptor+28,4,length)
            if kind is not None:retail.text(retail.kind,kind);retail.w(retail.descriptor+44,4,retail.kind)
            if backing is not None:retail.text(retail.backing_name,backing);retail.w(retail.descriptor+48,4,retail.backing_name)
            build();assert retail.read(retail.out,4)==0x1234
        for found,mutation in itertools.product((False,True),('','meta-fallback','status')):
            setup();retail.class_found=found;retail.mutation=mutation;retail.w(retail.descriptor+40,4,retail.class_name)
            build()
        setup();retail.w(retail.descriptor+24,4,retail.alias_name);retail.w(retail.ctx+10*144+20,4,0)
        cfg=retail.allocate(96,True);cls=retail.allocate(32,True);retail.text(cls,b'AliasClass');retail.w(cfg+40,4,cls)
        retail.w(retail.ctx+10*144+152,4,cfg);build()
        assert retail.read(retail.row+20,4)==retail.alias
        setup();retail.alignments=[16,32];retail.w(retail.descriptor+28,4,33);retail.text(retail.kind,b'Fixed');retail.w(retail.descriptor+44,4,retail.kind)
        retail.text(retail.backing_name,b'SystemMemory');retail.w(retail.descriptor+48,4,retail.backing_name);build()
        assert any(e[0]==ALLOC_SYSTEM and e[2:]==(0,32) for e in retail.events)
        for active in (0,1):
            setup();retail.actual_meta=True;retail.descend|=META;retail.w(SYSTEM,1,active);retail.w(retail.descriptor+40,4,retail.class_name)
            build()
            assert any(e[0]==0x2fda40 and e[1]==(retail.named_meta if active else retail.default_meta) for e in retail.events)
        for entry in (0x2f2730,0x2f2830,0x2f8920):
            setup();vt=retail.read(retail.ctx,4);retail.w(vt+92,4,0x2f2730);retail.w(vt+96,4,0x2f2830)
            compare(0x2f49e0,retail.ctx)
            retail.w(retail.row+20,4,0);retail.w(retail.row+160,4,0x04000000)
            retail.w(retail.descriptor+28,4,33)
            name=retail.allocate(32,True);retail.text(name,retail.string(retail.read(0x4c2170+retail.index*4,4)))
            args=(retail.ctx,retail.index) if entry==0x2f2730 else (retail.ctx,name) if entry==0x2f2830 else (name,)
            compare(entry,*args);assert retail.read(retail.row+20,4)==retail.pool
            assert any(e[0]==RESIZE for e in retail.events)
        assert BUILD in coverage
    print(f'allocator builder retail: {cases} RAM/ordered-call checkpoints; complete2064-byte body, recursive aliases and backing policies; concrete allocator factories/virtuals controlled')
if __name__=='__main__':main()
