#!/usr/bin/env python3
"""Complete SUBWND stock/work preparation against original instructions.

Database/list/item factories and item initializers are controlled leaves. The
actual preparation can also compose with the recovered lifecycle. No shop
purchase, price calculation or native UI acceptance is inferred from this test.
"""
import ctypes as C
from pathlib import Path
import itertools
import json
import subprocess
import tempfile
from test_subwindow_lifecycle_retail import LifecycleWorld,ENTRIES,OWNER,RAM,WINDOW,OLD,ROOT,Api,READ,WRITE,CALL,MASK,STACK

PREP=0x3d8740
WORK,ALTWORK=0x1a00000,0x1a01000
LISTS=[0x1a02000+i*0x1000 for i in range(4)];ALTLIST=0x1a06000
FOLDERS,PROPS,ITEMS,DATABASE,COMMON,COUNTER,COUNTERLIST,COUNTERDATA,ALTPROP,SCRATCH=range(0x1b00000,0x1ba0000,0x10000)
FACTORIES={0x3c8c90:0,0x3c8b00:1,0x3c8970:2,0x3c87f0:3}
INITIALIZERS={0x4482e0:4,0x448430:4,0x448580:4,0x448660:2}
KEYS={0x516ad8:0,0x516ac8:1,0x516960:2,0x5169a8:3,0x516860:4}


class PreparationWorld(LifecycleWorld):
    def __init__(self,image):
        super().__init__(image);self.descend={PREP};self.frame=STACK-224
        self.next_item=0;self.db_name=0;self.last_column=0;self.junk_kind=0;self.missing=3
        self.created_refs=1;self.work_refs=1;self.prep_mutation=None;self.lookups={};self.query_result=None
        self.w(WORK+4,4,1);self.w(ALTWORK+4,4,1);self.w(RAM+44,4,WORK)
        self.w(0x587108,4,0x5678)
        for i,offset in enumerate((16,20,24,28)):
            self.w(WORK+offset,4,LISTS[i]);self.w(ALTWORK+offset,4,LISTS[i])
        self.w(WORK+32,4,0x12345678)
        for p in LISTS+[ALTLIST]:self.w(p+8,4,0);self.w(p+12,4,36);self.w(p+16,4,p+0x10000)
        for i in range(4):
            for key,index in KEYS.items():
                p=PROPS+i*256+index*32;self.w(p+12,4,1 if index==4 else 10 if index==2 else 0)
        self.w(COUNTER+12,4,COUNTERLIST);self.w(COUNTERLIST+16,4,COUNTERDATA);self.w(COUNTERDATA+4,4,1000)
    def prop(self,player,key):return PROPS+player*256+KEYS[key]*32
    def text_at(self,p):
        p&=0xffffffff;b=[]
        while self.read(p,1):b.append(self.read(p,1));p+=1
        return bytes(b).decode('ascii')
    def call_hook(self,e):
        previous=self.frame;self.frame=self.r[29]&0xffffffff
        try:self.r[2]=self.call(e,self.r[4:12])&MASK
        finally:self.frame=previous
    def call(self,e,args):
        counts={0x38e5d0:2,0x38f250:2,0x38e060:2,0x38f800:2,0x3a9280:2,0x3a9220:2,
                0x38e670:3,0x3a9250:2,0x38e5f0:5,0x3a9460:3,0x12a1e8:2,
                0x2d6680:3,0x301c90:2,0x301e30:2,0x301000:1,0x2f88e0:1,
                0x3b5ec0:1,0x2ff820:1,**{p:1 for p in FACTORIES},**INITIALIZERS}
        if e not in counts:return super().call(e,args)
        raw=list(args[:counts[e]]);v=[x&0xffffffff for x in raw];normalized=list(raw)
        if e==0x3a9460:normalized[2]=self.text_at(v[2])
        if e==0x12a1e8:normalized[0]='column'
        state=(self.read(RAM+44,4),self.read(WORK+4,4),self.read(WORK+32,4),
               tuple(self.read(p+8,4) for p in LISTS+[ALTLIST]),
               tuple(self.read(self.prop(i,key)+12,4) for i in range(4) for key in (0x516ad8,0x516ac8)))
        self.events.append((e,tuple(normalized),state))
        if e==0x38e5d0:self.group=v[1];self.args=[]
        elif e==0x38f250:self.args.append(raw[1])
        elif e==0x38e060 and v[1]==0x516850:self.player=self.args[0]&0xffffffff
        elif e==0x38e670 and v[2]==0x516b80:self.group=0x516b80
        elif e==0x38e5f0:self.group=0x516980;self.db_name=v[2]
        elif e==0x38f800:
            return DATABASE if self.group==0x516980 else COMMON if self.group==0x516b80 else FOLDERS+self.player*256
        elif e in (0x3a9280,0x3a9220):
            player=(v[0]-FOLDERS)//256;key=v[1];p=self.prop(player,key)
            n=self.lookups.get((player,key),0);self.lookups[(player,key)]=n+1
            if self.prep_mutation=='cap_target' and key in (0x516ad8,0x516ac8) and n%2==1:return ALTPROP
            return p
        elif e==0x3a9250:return COUNTER
        elif e==0x301000:return 0x1c00000
        elif e==0x2f88e0:return 0x1c01000
        elif e==0x3b5ec0:
            self.w(WORK+4,4,self.work_refs)
            if self.prep_mutation=='work_factory':self.w(RAM+44,4,ALTWORK)
            return WORK
        elif e in FACTORIES:
            p=ITEMS+self.next_item*64;self.next_item+=1;self.w(p+4,4,self.created_refs);self.w(p+8,4,FACTORIES[e]);return p
        elif e in INITIALIZERS:
            self.w(v[0]+12,4,v[1])
            if self.prep_mutation=='item_temp':self.replace_item_temp(FACTORIES[{0x4482e0:0x3c8c90,0x448430:0x3c8b00,0x448580:0x3c8970,0x448660:0x3c87f0}[e]])
            return 0
        elif e==0x3a9460:
            text=self.text_at(v[2])
            if text=='kind':return self.junk_kind&MASK
            self.last_column=int(text)
            if self.query_result is not None:return self.query_result&MASK
            return MASK if self.missing and self.last_column%self.missing==0 else 100+self.last_column
        elif e==0x12a1e8:
            self.assert_kind=v[1];text=self.text_at(v[1]).encode()+b'\0'
            for i,b in enumerate(text):self.w(v[0]+i,1,b)
        elif e==0x2d6680:
            self.w(v[0]+8,4,v[1]);self.w(v[0]+12,4,v[1])
            if self.prep_mutation=='list_swap':
                offset={6:16,7:20,8:24,9:28}[self.read(OWNER+40,4)];self.w(WORK+offset,4,ALTLIST)
        elif e==0x301c90:self.w(v[0]+8,4,v[1])
        elif e==0x301e30:
            n=self.read(v[0]+8,4);self.w(self.read(v[0]+16,4)+n*4,4,v[1]);self.w(v[0]+8,4,n+1)
            if v[1]:self.w(v[1]+4,4,self.read(v[1]+4,4)+1)
            if self.prep_mutation=='append_temp' and v[1]:self.replace_item_temp(self.read(v[1]+8,4))
        elif e==0x2ff820 and self.prep_mutation=='work_release' and v[0]==WORK:self.w(RAM+44,4,ALTWORK)
        return 0

    def replace_item_temp(self,kind):
        mode=self.read(OWNER+40,4)
        offset=216 if mode==6 else (212 if kind==1 else 208) if mode==7 else 204 if mode==8 else {0:200,1:196,2:192}[kind]
        replacement=ITEMS+0x8000
        self.w(replacement+4,4,1);self.w(replacement+8,4,kind)
        self.w(self.frame+offset,4,replacement)


def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();native=PreparationWorld(image)
    errors=[];cases=0;coverage=set();depth=0
    @CALL
    def call(_,e,args):
        try:return invoke(e,args)&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-subwindow-preparation-') as td:
        so=Path(td)/'preparation.so'
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',
                        *[str(ROOT/'recovered/engine'/p) for p in ('subwindow-preparation.c','subwindow-lifecycle.c')],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));prep=lib.dw4_subwindow_preparation;life=lib.dw4_subwindow_lifecycle
        prep.argtypes=[C.POINTER(Api),C.POINTER(C.c_uint64),C.c_uint32];prep.restype=C.c_uint64
        life.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];life.restype=C.c_uint64
        def invoke(e,args):
            nonlocal depth
            if e!=PREP and e not in native.descend:return native.call(e,args)&MASK
            depth+=1;previous=native.frame;native.frame=SCRATCH+depth*512
            try:return prep(C.byref(api),args,native.frame) if e==PREP else life(C.byref(api),e,args,native.frame)
            finally:native.frame=previous;depth-=1
        def compare(w,entry=PREP):
            nonlocal cases
            w.events=[];errors.clear()
            for key,value in w.__dict__.items():
                if key not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image','frame'):
                    setattr(native,key,value.copy() if isinstance(value,(list,dict,set)) else value)
            # Translate only incoming private storage, before retail executes.
            size=224 if entry==PREP else 80
            for i in range(size):native.w(SCRATCH+512+i,1,w.read(STACK-size+i,1))
            if entry!=PREP:
                for i in range(224):native.w(SCRATCH+1024+i,1,w.read(STACK-80-224+i,1))
            w.invoke(entry,OWNER,RAM);invoke(entry,(C.c_uint64*8)(OWNER,RAM))
            assert not errors,errors
            def ram(obj):return {p:v for p,v in obj.mem.items() if v and not STACK-0x10000<=p<STACK+64 and not SCRATCH<=p<SCRATCH+0x10000}
            er,ar=ram(w),ram(native)
            assert er==ar,[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12]
            if w.events!=native.events:
                i=next((i for i,(x,y) in enumerate(zip(w.events,native.events)) if x!=y),min(len(w.events),len(native.events)))
                raise AssertionError(('event',i,w.events[i:i+1],native.events[i:i+1]))
            cases+=1;coverage.update(w.covered)
        for mode,existing,flag,mask in itertools.product(range(11),(False,True),(0,1),(0,1,3,15)):
            w=PreparationWorld(image);w.w(OWNER+40,4,mode);w.w(0x554c14,1,flag)
            if not existing:w.w(RAM+44,4,0)
            for i in range(4):
                w.w(w.prop(i,0x516860)+12,4,257 if mask>>i&1 else 256)
                w.w(w.prop(i,0x516ad8)+12,4,10000000+i);w.w(w.prop(i,0x516ac8)+12,4,10000+i)
            compare(w)
        cuts=[10,17,22,27,32,37,42,47,52,61,68,73,78,83,88,93,98,103,108,113,118,128,138,148,158,168,178,188,198]
        for mode,level in itertools.product((6,7,8),[-2147483648,-1,0,2147483647]+sorted({v+d for v in cuts for d in (-1,0,1)})):
            w=PreparationWorld(image);w.w(OWNER+40,4,mode);w.w(w.prop(0,0x516960)+12,4,level);compare(w)
        for species in range(17):
            w=PreparationWorld(image);w.w(OWNER+40,4,6)
            for i in range(1,4):w.w(w.prop(i,0x516860)+12,4,0)
            w.w(w.prop(0,0x5169a8)+12,4,species);compare(w)
        for invested,kind in itertools.product([-1,0,999]+[v+d for v in (1000,6000,26000,86000,206000,456000,956000,1956000,3956000) for d in (-1,0,1)],(0,1,2,9)):
            w=PreparationWorld(image);w.w(OWNER+40,4,9);w.w(COUNTERDATA+4,4,invested);w.junk_kind=kind;compare(w)
        for mode in (6,7,8,9):
            w=PreparationWorld(image);w.w(OWNER+40,4,mode);w.w(LISTS[mode-6]+8,4,1);compare(w)
            w=PreparationWorld(image);w.w(OWNER+40,4,mode);w.prep_mutation='list_swap';compare(w)
        w=PreparationWorld(image);w.prep_mutation='cap_target'
        for i in range(4):w.w(w.prop(i,0x516ad8)+12,4,10000000);w.w(w.prop(i,0x516ac8)+12,4,10000)
        compare(w)
        for mutation in ('work_factory','work_release'):
            w=PreparationWorld(image);w.w(RAM+44,4,0);w.prep_mutation=mutation;w.work_refs=0 if mutation=='work_release' else 1;compare(w)
        for mode in (6,7,8,9):
            w=PreparationWorld(image);w.w(OWNER+40,4,mode);w.created_refs=0;w.missing=0;compare(w)
        for kind,flag,refs in itertools.product((0,1,2),(0,1),(0,1)):
            w=PreparationWorld(image);w.w(OWNER+40,4,9);w.w(0x554c14,1,flag)
            w.junk_kind=kind;w.created_refs=refs;compare(w)
        for mode,value in itertools.product(range(11),(-2147483648,-1,9999,10000,9999999,10000000)):
            w=PreparationWorld(image);w.w(OWNER+40,4,mode)
            for i in range(4):
                w.w(w.prop(i,0x516ad8)+12,4,value);w.w(w.prop(i,0x516ac8)+12,4,value)
            compare(w)
        for mode,result in itertools.product((6,7,8,9),(0xffffffff,0x100000064,-1)):
            w=PreparationWorld(image);w.w(OWNER+40,4,mode);w.query_result=result;compare(w)
        for mode,mutation in itertools.product((6,7,8,9),('item_temp','append_temp')):
            for kind in ((0,1,2) if mode==9 else (0,)):
                w=PreparationWorld(image);w.w(OWNER+40,4,mode);w.junk_kind=kind;w.prep_mutation=mutation;compare(w)
        # Compose the actual preparation with original and recovered lifecycle.
        for mode,mask in itertools.product(range(11),(0,1,3,15)):
            w=PreparationWorld(image);w.descend.update(ENTRIES);w.frame=STACK-80
            w.w(OWNER+40,4,mode);w.w(RAM+44,4,0)
            for i in range(4):w.w(w.prop(i,0x516860)+12,4,(mask>>i)&1)
            compare(w,0x3d59b0);compare(w,0x3d59b0)
            w.root_active=0;compare(w,0x3d59b0)
        # Warm work/list state persists; stock is not silently rebuilt on reopen.
        for mode in (6,7,8,9):
            w=PreparationWorld(image);w.w(OWNER+40,4,mode);compare(w);compare(w)
        expected=set(range(PREP,0x3d9bd0,4));missing=expected-coverage
        extent=next(r for r in json.loads((ROOT/'data/function-extents.json').read_text()) if int(r['address'],0)==PREP)
        occupied={p for r in extent['body_ranges'] for p in range(int(r['start'],0),int(r['end_exclusive'],0),4)}
        padding=expected-occupied
        assert len(padding)==94 and missing==padding,sorted(hex(p) for p in missing-padding)
        assert all(w.read(p,4)==0 for p in padding)
        assert len(expected&coverage)==1222
        print(f'SUBWND preparation: {cases} RAM/ordered-call cases, 1222/1316 preparation instruction addresses (94 padding NOPs); database/item/list services remain leaves')


if __name__=='__main__':main()
