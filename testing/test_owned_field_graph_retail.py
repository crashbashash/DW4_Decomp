#!/usr/bin/env python3
"""Real reference-field construction/destruction in a synthetic owned graph.

Actual shared object lifecycle, field passes, reference operations and list
release execute. Metadata is synthetic; allocator, hooks and bytes remain leaves.
"""
import argparse,ctypes as C,subprocess,tempfile
from pathlib import Path
from test_object_creation_retail import Creation,ENTRIES as CREATION,ROOT,Api,READ,WRITE,CALL,MASK,STACK,META,OTHER,FIELDS,BASEFIELDS,FIELD,FVT,VT,VOP,VOTHER,OBJECT,ALLOC,ALLOCATE
from test_object_fields_retail import ENTRIES as FIELDS_ENTRIES
from test_object_lists_retail import ENTRIES as LISTS
CHILD_TABLE,CHILD_VT,CHILD,LIST,DATA=range(0x18a0000,0x18a5000,0x1000)
class Graph(Creation):
    def __init__(self,image,n):
        super().__init__(image);self.descend=set(CREATION)|set(FIELDS_ENTRIES)|set(LISTS)
        self.allocations=0;self.owner=False
        self.w(META+72,4,8+4*n);self.w(OTHER+72,4,8);self.w(OTHER+40,4,CHILD_TABLE)
        self.w(CHILD_TABLE+12,4,0);self.w(FIELDS+12,4,n)
        for meta in (META,OTHER):self.w(meta+44,4,0);self.w(meta+48,4,0)
        self.w(OTHER+92,4,CHILD_VT)
        for table in (VT,CHILD_VT):
            for slot in (8,12,16,36,40,44,48,52,72,80,88):self.w(table+slot,4,VOP+slot)
        for i in range(n):
            f=FIELD+i*0x100;self.w(f+8,4,8+i*4);self.w(f+52,1,1);self.w(f+53,1,1)
            self.w(f+56,4,OTHER);self.w(f+60,1,0);self.w(f+64,4,0)
        for slot,fn in ((100,0x303450),(124,0x303540),(128,0x303620),(132,0x305500),(136,0x303680),(240,0x305cd0)):
            self.w(FVT+slot,4,fn)
        self.w(LIST+8,4,1);self.w(LIST+12,4,1);self.w(LIST+16,4,DATA);self.w(DATA,4,OBJECT)
    def call(self,e,args):
        v=[x&0xffffffff for x in args]
        if e==ALLOCATE:
            self.events.append((e,*v[:2]));p=OBJECT if not self.allocations else CHILD+(self.allocations-1)*0x100
            self.allocations+=1
            for i in range(v[1]):self.w(p+i,1,0xa5)
            return p
        if e==VOP+88:self.events.append((e,v[0]));return OTHER if self.read(v[0],4)==CHILD_VT else META
        if e==VOP+16:self.events.append((e,v[0]));return 0
        if e==0x301000:self.events.append((e,v[0]));return ALLOC
        if e==0x300d30:self.events.append((e,));return v[0]
        if e==0x12724c:
            self.events.append((e,*v[:3]))
            for i in range(v[2]):self.w(v[0]+i,1,v[1])
            return v[0]
        return super().call(e,args)

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT/'orig/SLUS-20836/SLUS_208.36');args=p.parse_args()
    image=args.elf.read_bytes();retail=Graph(image,1);native=Graph(image,1);errors=[];cases=0
    @CALL
    def call(_,e,values):
        try:
            if e in FIELDS_ENTRIES:return fields(C.byref(api),e,values)
            if e in CREATION:return creation(C.byref(api),e,values)
            if e in LISTS:return lists(C.byref(api),e,values)
            return native.call(e,list(values[:8]))&MASK
        except Exception as error:errors.append(error);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-owned-fields-') as td:
        so=Path(td)/'graph.so';subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/name) for name in ('object-fields.c','object-creation.c','object-lists.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));fields=lib.dw4_object_field;creation=lib.dw4_object_creation;lists=lib.dw4_object_list
        for fn in (fields,creation,lists):fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64)];fn.restype=C.c_uint64
        def compare(entry,*values):
            nonlocal cases
            for key,value in retail.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image'):
                    setattr(native,key,value.copy() if isinstance(value,(dict,list,set)) else value)
            retail.events=[];native.events=[];expected=retail.invoke(entry,*values)
            actual=(creation if entry in CREATION else lists)(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in values]))
            assert not errors,errors
            if entry==0x2fda40:assert expected==actual==OBJECT
            def ram(world):return {p:v for p,v in world.mem.items() if not STACK-0x2000<=p<STACK+32 and v}
            er,ar=ram(retail),ram(native)
            assert er==ar,(hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            assert retail.events==native.events,(hex(entry),retail.events,native.events)
            cases+=1
        for n in (0,1,3):
            retail=Graph(image,n);compare(0x2fda40,META,ALLOC)
            assert retail.read(META+44,4)==1 and retail.read(OTHER+44,4)==n
            for i in range(n):assert retail.read(OBJECT+8+i*4,4)==CHILD+i*0x100 and retail.read(CHILD+i*0x100+4,4)==1
            # The factory's owned reference is transferred to the fixture list.
            # Filling that list with null performs the actual final release.
            compare(0x301c90,LIST,0)
            assert retail.read(META+44,4)==retail.read(OTHER+44,4)==0
            assert retail.read(OBJECT+4,4)==0 and retail.read(DATA,4)==0
            frees=[event[1] for event in retail.events if event[0]==0x2ed460]
            assert sorted(frees)==sorted([OBJECT]+[CHILD+i*0x100 for i in range(n)])
            for i in range(n):assert retail.read(OBJECT+8+i*4,4)==retail.read(CHILD+i*0x100+4,4)==0
    print(f'owned fields retail: {cases} persistent creation/final-release checkpoints for 0/1/3 owned children; real concrete reference-field and generic lifecycle bodies; synthetic metadata and allocator/hooks/bytes leaves')
if __name__=='__main__':main()
