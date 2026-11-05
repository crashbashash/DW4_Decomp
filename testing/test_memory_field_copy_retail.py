#!/usr/bin/env python3
"""Memory copy/print/visitor and actual owner-directed buffer services vs retail."""
import ctypes as C
import itertools
import subprocess
import tempfile
from pathlib import Path
import test_reflection_registration_retail as reg
from test_memory_field_values_retail import Values,ENTRIES as VALUES
from test_object_base_retail import SCRATCH
from test_reflection_registration_retail import ROOT,Api,READ,WRITE,CALL,MASK,STACK
COPY={0x2fad50,0x2faf10,0x2fafb0,0x2fb0b0}
VISITOR={0x300b00}
BUFFERS={0x2ed460,0x2ed4b0,0x2ed4c0,0x2ed4e0,0x2ed520,0x2ed530,0x2ed5a0,0x2ed5c0,0x2ed5d0}
RETURNS={0x2ed4e0,0x2ed520,0x2ed530,0x2ed5a0}
OWNER=0x18f2000
SIZE,FREE,SLOT240,CLONE,PREPARE,STRIDE=range(0x19e0000,0x19e0060,0x10)
GETMETA,VISIT,FIELD_VISIT=0x19e0060,0x19e0070,0x19e0080
CLASS_OBJECT,CLASS_MEMORY=0x1e00000,0x1e00100

class CopyWorld(Values):
    def __init__(self,image):
        super().__init__(image);self.descend|=COPY|BUFFERS|VISITOR
        self.source=self.allocate(64,True);self.source_buffer=self.allocate(12,True)
        self.memory_type=self.allocate(80,True);self.w(self.memory_type,4,0x532a50)
        self.w(0x585b20,4,CLASS_OBJECT);self.w(0x585d80,4,CLASS_MEMORY)
        self.w(0x1825000+336,4,SIZE);self.w(0x1825000+264,4,FREE);self.w(0x1825000+240,4,SLOT240)
        self.node_vt=self.allocate(128,True);self.w(self.node_vt+72,4,PREPARE);self.w(self.node_vt+84,4,CLONE);self.w(self.node_vt+88,4,GETMETA)
        self.type_vt=self.allocate(192,True);self.w(self.type_vt+104,4,STRIDE)
        self.print_type=self.allocate(80,True);self.w(self.print_type,4,self.type_vt)
        self.visit_result=1;self.skip_field=-1;self.visit_calls=0;self.allocate_fail=False
        self.meta=self.allocate(80,True);self.meta_fields=self.allocate(16,True);self.field_table=self.allocate(16,True)
        self.base_meta=self.allocate(80,True);self.base_fields=self.allocate(16,True)
        self.w(0x587198,4,self.base_meta);self.w(self.base_meta+40,4,self.base_fields);self.w(self.base_fields+12,4,2)
        self.w(self.meta+40,4,self.meta_fields);self.w(self.meta_fields+8,4,self.field_table);self.w(self.meta_fields+12,4,4)
        self.visitor_fields=[];field_vt=self.allocate(192,True);self.w(field_vt+168,4,FIELD_VISIT)
        for i in range(4):
            p=self.allocate(80,True);self.w(p,4,field_vt);self.w(self.field_table+i*4,4,p);self.visitor_fields.append(p)
        self.kind=1;self.stride=4;self.owner=True;self.mutation='';self.size_calls=0;self.clones=0
        self.w(self.object+8,4,self.buffer);self.w(self.source+8,4,self.source_buffer)
        self.w(self.object+12,4,self.other);self.w(self.source+12,4,self.source_buffer)
        for i,node in enumerate(self.nodes):
            self.w(node,4,self.node_vt);self.w(node+4,4,5)
            self.w(self.source_buffer+i*4,4,0 if i==1 else node)
        self.w(self.field+64,1,1)
    def configure(self,kind):
        self.kind=kind
        self.w(self.field+60,4,(self.scalar[2],self.scalar[1],self.memory_type,0)[kind])
        if kind==2:
            for i in (0,2):
                p=self.allocate(8,True);self.w(p,4,0x12340000+i);self.w(p+4,4,0x56780000+i)
                self.w(self.source_buffer+i*4,4,p)
    def step(self,pc,delay=False):
        # Original owner alias tail-jumps to the deliberately controlled owner search.
        if pc in (0x2ed4d4,0x2ed5b4):
            target=self.r[25]&0xffffffff;super().step(pc+4,True);self.call_hook(target);return self.r[31]&0xffffffff
        if pc==0x2ed520:
            super().step(pc+4,True);self.call_hook(0x2f04f0);return self.r[31]&0xffffffff
        return super().step(pc,delay)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==0x2f04f0:self.events.append((e,v[0]));return OWNER if self.owner else 0
        if e==SIZE:
            self.events.append((e,*v[:2]));self.size_calls+=1
            n=self.allocated.get(v[1],self.list_bytes.get(v[1],0))
            if self.mutation=='size' and self.size_calls>1:n=max(0,n-4)
            return n
        if e==0x2ed1c0:
            self.events.append((e,*v[:2]));p=0 if self.allocate_fail else self.allocate(v[0])
            if self.mutation=='offset':self.w(self.field+8,4,12)
            return p
        if e==FREE:
            self.events.append((e,*v[:2]));self.freed.add(v[1])
            if self.mutation=='free':self.w(self.field+8,4,12)
            return 0
        if e==SLOT240:self.events.append((e,*v[:2]));return v[1]^0x1234
        if e==0x300cd0:
            self.events.append((e,*v[:2]))
            answer=v[0] in (self.scalar[1],self.print_type) if v[1]==CLASS_OBJECT else v[0]==self.memory_type if v[1]==CLASS_MEMORY else False
            if self.mutation=='type' and v[1]==CLASS_OBJECT:self.w(self.field+60,4,self.memory_type)
            return int(answer)
        if e==CLONE:
            self.events.append((e,*v[:2]));p=self.allocate(8,True);self.w(p,4,self.node_vt);self.w(p+4,4,1);self.clones+=1
            if self.mutation=='clone':
                self.w(self.source_buffer+8,4,0);self.w(self.field+8,4,12)
                self.w(self.source+8,4,0);self.w(self.object+8,4,0)
            return p
        if e==PREPARE:
            self.events.append((e,v[0]))
            if self.mutation=='prepare':self.w(self.buffer,4,self.nodes[2]);self.w(self.field+8,4,12)
            return 0
        if e==GETMETA:self.events.append((e,v[0]));return self.meta
        if e==VISIT:
            self.events.append((e,*v[:3]));self.visit_calls+=1
            if self.mutation=='visitor-count' and self.visit_calls==2:self.w(self.meta_fields+12,4,2)
            if self.mutation=='visitor-buffer' and self.visit_calls==2:
                p=self.allocate(16,True)
                for i,f in enumerate(reversed(self.visitor_fields)):self.w(p+i*4,4,f)
                self.w(self.meta_fields+8,4,p)
            return 1 if v[1]==self.skip_field else self.visit_result
        if e==FIELD_VISIT:self.events.append((e,*v[:4]));return 0
        if e==0x300490:self.events.append((e,*v[:3]));return 0
        if e==0x304430:
            self.events.append((e,*v[:4]))
            if self.mutation=='print':self.w(self.object+8,4,0)
            return 0
        if e==0x304680:self.events.append((e,));return 0
        if e in (STRIDE,self.read(0x532670+104,4)):self.events.append((e,v[0]));return self.stride
        return super().call(e,args)

def main():
    reg.STORAGE=reg.FACTORIES=reg.METADATA=reg.INTERNAL=True
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();retail=CopyWorld(image);native=CopyWorld(image)
    cases=0;coverage=set();hits=set();errors=[]
    @CALL
    def call(_,e,args):
        try:return invoke_native(e,args)
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-memory-copy-') as td:
        so=Path(td)/'copy.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in ('memory-field-copy.c','memory-buffer-services.c','memory-field-values.c','object-fields.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));fcopy=lib.dw4_memory_field_copy;fbuffer=lib.dw4_memory_buffer_service;fvalue=lib.dw4_memory_field_value;fvisitor=lib.dw4_object_field
        for f in (fcopy,fbuffer,fvalue,fvisitor):f.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)]+([C.c_uint32] if f==fvalue else []);f.restype=C.c_uint64
        def invoke_native(e,args):
            if e in VISITOR:return fvisitor(C.byref(api),e,args)
            if e in COPY:return fcopy(C.byref(api),e,args)
            if e in BUFFERS:return fbuffer(C.byref(api),e,args)
            if e in VALUES:return fvalue(C.byref(api),e,args,SCRATCH)
            return native.call(e,list(args[:8]))&MASK
        def setup():
            nonlocal retail
            retail=CopyWorld(image)
        def compare(entry,*args):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[]
            expected=retail.invoke(entry,*args);actual=invoke_native(entry,(C.c_uint64*8)(*[x&MASK for x in args]))
            assert not errors,errors
            if entry in RETURNS:assert expected==actual,(hex(entry),expected,actual)
            def ram(w):return {p:v for p,v in w.mem.items() if not STACK-0x5000<=p<STACK+40 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1;hits.add(entry);coverage.update(retail.covered);return actual
        for entry,kind,release,refcounted,source in itertools.product((0x2fad50,0x2faf10),range(4),(0,1),(0,1),(False,True)):
            setup();retail.configure(kind);retail.w(retail.field+64,1,release);retail.w(retail.field+66,1,refcounted)
            if not source:retail.w(retail.source+8,4,0)
            compare(entry,retail.field,retail.object,retail.source)
            dst=retail.read(retail.object+8,4)
            if source:
                assert dst and dst!=retail.source_buffer
                if entry==0x2faf10:assert [retail.read(dst+i*4,4) for i in range(3)]==[retail.read(retail.source_buffer+i*4,4) for i in range(3)]
                if entry==0x2fad50 and kind==1:assert retail.clones==2
                if entry==0x2fad50 and kind==2:
                    for i in (0,2):
                        old=retail.read(retail.source_buffer+i*4,4);new=retail.read(dst+i*4,4)
                        assert old!=new and retail.read(old,8)==retail.read(new,8)
            else:assert not dst
            assert (retail.buffer in retail.freed)==bool(release)
        for entry in (0x2fad50,0x2faf10):
            setup();retail.w(retail.field+64,1,0)
            compare(entry,retail.field,retail.object,retail.object)
            assert retail.read(retail.object+8,4)!=retail.buffer
        for entry,mutation in itertools.product((0x2fad50,0x2faf10),('offset','free','size','clone')):
            setup();retail.mutation=mutation;compare(entry,retail.field,retail.object,retail.source)
        setup();retail.configure(2);retail.w(retail.field+60,4,retail.scalar[2]);retail.mutation='type'
        compare(0x2fad50,retail.field,retail.object,retail.source)
        for mode,buffer,kind,stride in itertools.product((0,1),(False,True),(0,1),(0,4,8,0x10004)):
            setup();retail.w(retail.field+60,4,retail.print_type if kind else retail.scalar[2]);retail.stride=stride
            if not buffer:retail.w(retail.object+8,4,0)
            compare(0x2fafb0,retail.field,retail.object,mode,0x1234)
        setup();retail.w(retail.field+60,4,retail.print_type);retail.mutation='print';compare(0x2fafb0,retail.field,retail.object,1,7)
        for kind,buffer,mutation in itertools.product((0,1),(False,True),('','prepare')):
            setup();retail.configure(kind);retail.mutation=mutation
            if not buffer:retail.w(retail.object+8,4,0)
            compare(0x2fb0b0,retail.field,retail.object,VISIT,0x789)
        for entry in BUFFERS:
            setup();compare(entry,retail.buffer,OWNER)
        for entry,buffer,owner in itertools.product((0x2ed460,0x2ed4b0,0x2ed5c0),(False,True),(False,True)):
            setup();retail.owner=owner;compare(entry,retail.buffer if buffer else 0)
        setup();retail.mutation='size';p=compare(0x2ed530,retail.buffer)
        assert retail.allocated[p]==12 and retail.read(p+8,4)==0xa5a5a5a5
        for result,skip,mutation in itertools.product((0,1,2),(-1,2,3),('','visitor-count','visitor-buffer')):
            setup();retail.visit_result=result;retail.skip_field=retail.visitor_fields[skip] if skip>=0 else -1;retail.mutation=mutation
            compare(0x300b00,retail.nodes[0],VISIT,0x789)
            walked=[e for e in retail.events if e[0]==FIELD_VISIT]
            if result==1:assert not walked
            if result==2 and skip<0 and not mutation:assert len(walked)==2
        setup();retail.visit_result=0
        compare(0x2fb0b0,retail.field,retail.object,VISIT,0x789)
        assert sum(e[0]==FIELD_VISIT for e in retail.events)==6
        setup();retail.allocate_fail=True;compare(0x2ed530,retail.buffer)
        assert any(e[0]==0x127098 and e[1]==0 for e in retail.events)
        assert COPY|BUFFERS|VISITOR<=hits|coverage,(COPY|BUFFERS|VISITOR)-(hits|coverage)
    print(f'memory copy retail: {cases} RAM/defined-return/ordered-call checkpoints; four field bodies, nine actual buffer services and original object visitor')
if __name__=='__main__':main()
