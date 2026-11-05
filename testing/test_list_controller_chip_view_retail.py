#!/usr/bin/env python3
"""Full ListCtrl paging and chip count/text helpers vs original instructions.

Pad-record lookup can execute its real body. Model generation, packet delivery,
item NAME/NEXTX/TXT lookup and formatting are controlled services. Text state is
an observation model; this does not accept chip purchases or native rendering.
"""
import ctypes as C
import itertools
import json
from pathlib import Path
import subprocess
import tempfile
from test_subwindow_lifecycle_retail import LifecycleWorld,ROOT,Api,READ,WRITE,CALL,MASK,STACK
INIT,PREV,NEXT,COUNT,TEXT,PAD_GET=0x40dae0,0x40dbf0,0x40dd30,0x43c720,0x43c7f0,0x39b810
ENTRIES=(INIT,PREV,NEXT,COUNT,TEXT)
SELF,LEFT,RIGHT,SCRATCH=0x1a00000,0x1b10000,0x1b11000,0x1c00000
PAD_MANAGER,PAD_LIST,PAD_DATA,PADS,ITEM_LIST,ITEM_DATA,ALT_LIST,ALT_DATA,STATUS,ITEMS,NAMES,DESCS=range(0x1d00000,0x1dc0000,0x10000)
SIZES={INIT:96,PREV:48,NEXT:48,COUNT:0,TEXT:160,PAD_GET:0}

def signed(n):return n-(1<<32) if n&0x80000000 else n

def word(n):return signed(n&0xffffffff)&MASK

class ViewWorld(LifecycleWorld):
    def __init__(self,image):
        super().__init__(image);self.descend={*ENTRIES,PAD_GET};self.frame=STACK-96
        self.mutation=None;self.calls=0;self.model_calls=0;self.context=STATUS;self.font_states={};self.buffers={};self.prices={};self.mutated=False
        self.w(SELF+8,4,0x1b01000);self.w(SELF+12,4,0x1b02000);self.w(SELF+16,4,PAD_MANAGER);self.w(SELF+20,4,0)
        self.w(SELF+48,4,0);self.w(SELF+84,4,0);self.w(SELF+88,4,3);self.w(SELF+92,4,0x13579bdf);self.w(SELF+96,4,ITEM_LIST)
        self.w(PAD_MANAGER+20,4,PAD_LIST);self.w(PAD_MANAGER+29,1,0);self.w(PAD_LIST+16,4,PAD_DATA)
        for i in range(5):self.w(PAD_DATA+i*4,4,PADS+i*256)
        for p,data in ((ITEM_LIST,ITEM_DATA),(ALT_LIST,ALT_DATA)):
            self.w(p+8,4,25);self.w(p+12,4,48);self.w(p+16,4,data)
            for i in range(-24,48):self.w(data+i*4,4,ITEMS+i*64 if i>=0 else 0)
        for i in range(48):
            self.put(NAMES+i*256,('name%d'%i).encode());self.put(DESCS+i*256,('description%d'%i).encode());self.prices[ITEMS+i*64]=100+i
        for p,values in ((LEFT,(0xc3120000,0x41c80000,0)),(RIGHT,(0x436c0000,0x41c80000,0))):
            for i,v in enumerate(values):self.w(p+i*4,4,v)
        self.w(0x58b028,4,0x12345678)
        for group in (b'STWINFONT14',b'STWINFONT17',b'STWINFONT29',b'STWINFONT30'):
            for i in range(12):self.font_states[(group,self.string(self.read(0x4cf8a0+i*4,4)))]=(b'old',True)
    def put(self,p,text):
        for i,b in enumerate(text+b'\0'):self.w(p+i,1,b)
    def string(self,p):
        p&=0xffffffff;out=[]
        while self.read(p,1):out.append(self.read(p,1));p+=1
        return bytes(out)
    def snapshot(self):
        return (tuple(self.read(SELF+i,4) for i in (8,12,16,20,48,84,88,92,96)),self.read(ITEM_LIST+8,4),self.read(ALT_LIST+8,4),tuple(sorted(self.font_states.items())))
    def call(self,e,args):
        counts={0x3f5c90:6,0x38e5f0:5,0x236f80:2,0x447cb0:3,0x447c10:3,0x38e5d0:2,0x38f830:2,0x38e060:2,0x129e60:3}
        assert e in counts,hex(e)
        raw=list(args[:counts[e]]);v=[x&0xffffffff for x in raw];norm=list(raw)
        if e==0x3f5c90:norm[5]=('vector',v[5]-self.frame,tuple(self.read(v[5]+i*4,4) for i in range(3)))
        if e==0x129e60:norm[0]=('frame',v[0]-self.frame)
        if e==0x38f830 and (STACK-0x8000<=v[1]<STACK or SCRATCH<=v[1]<SCRATCH+0x10000):norm[1]=('text',self.string(v[1]))
        self.events.append((e,tuple(norm),self.snapshot()));self.calls+=1
        if e==0x3f5c90:
            self.model_calls+=1
            if self.model_calls==1 and self.mutation in ('init_multi','init_single'):
                self.w(SELF+88,4,2 if self.mutation=='init_multi' else 1)
                for i,vv in enumerate((0x80000000,0x7fc01234,0x7f800000)):self.w(RIGHT+i*4,4,vv)
            return 0
        if e==0x38e5f0 and self.mutation=='send' and not self.mutated:
            self.mutated=True;self.w(SELF+12,4,0x1b03000);self.w(SELF+84,4,0x80000000);return 0
        if e==0x236f80:
            if self.mutation=='lookup':self.w(SELF+84,4,1);self.w(SELF+12,4,0x1b03000)
            return self.context&MASK
        if e==0x447cb0:
            index=(v[0]-ITEMS)//64
            assert 0<=index<48,(hex(v[0]),index)
            result=NAMES+index*256 if v[2]==0x51b678 else DESCS+index*256
            if not self.mutated and self.mutation in ('font','list'):
                self.mutated=True
                if self.mutation=='font':self.put(NAMES+0x4000,b'changed_font');self.w(0x4cf8a0,4,NAMES+0x4000)
                else:self.w(SELF+96,4,ALT_LIST);self.w(ALT_LIST+8,4,13);self.w(ALT_DATA,4,ITEMS+64*5)
            return result
        if e==0x447c10:return self.prices[v[0]]&MASK
        if e==0x129e60:
            text=self.string(v[1]).replace(b'%d',str(signed(v[2])).encode());self.put(v[0],text);return len(text)
        if e==0x38e5d0:self.buffers[v[0]]=[]
        if e==0x38f830:self.buffers.setdefault(v[0],[]).append(self.string(v[1]))
        if e==0x38e060:
            fields=self.buffers.get(v[0],[])
            assert len(fields)==3,(hex(v[0]),fields)
            key=tuple(fields[:2]);old=self.font_states.get(key,(b'',True))
            if v[1]==0x51b6b0:self.font_states[key]=(fields[2],old[1])
            elif v[1]==0x51b558:self.font_states[key]=(old[0],fields[2]==b'DISPON')
            else:raise AssertionError(hex(v[1]))
            if self.mutation=='page' and not self.mutated:self.mutated=True;self.w(SELF+84,4,1);self.w(SELF+48,4,2)
        return 0


def main():
    image=(ROOT/'orig/SLUS-20836/SLUS_208.36').read_bytes();native=ViewWorld(image);errors=[];cases=0;coverage=set()
    @CALL
    def call(_,entry,args):
        try:
            if entry==PAD_GET:return get_pad(C.byref(api),args[0],args[1])
            return native.call(entry,args)&MASK
        except Exception as ex:errors.append(ex);return 0
    read=READ(lambda _,p,n:native.read(p,n));write=WRITE(lambda _,p,n,v:native.write(p,n,v));api=Api(None,read,write,call)
    with tempfile.TemporaryDirectory(prefix='dw4-list-chip-view-') as td:
        so=Path(td)/'view.so';files=('list-controller.c','chip-list-view.c','pad-manager-selection.c')
        subprocess.run(['cc','-shared','-fPIC','-std=c99','-Wall','-Wextra','-Werror',*[str(ROOT/'recovered/engine'/p) for p in files],'-o',str(so)],check=True)
        lib=C.CDLL(str(so));base=lib.dw4_list_controller;chip=lib.dw4_chip_list_view;get_pad=lib.dw4_pad_manager_selection
        for fn in (base,chip):fn.argtypes=[C.POINTER(Api),C.c_uint32,C.POINTER(C.c_uint64),C.c_uint32];fn.restype=C.c_uint64
        get_pad.argtypes=[C.POINTER(Api),C.c_uint64,C.c_uint64];get_pad.restype=C.c_uint64
        def compare(w,entry,*extra):
            nonlocal cases
            w.events=[];w.frame=STACK-SIZES[entry];errors.clear();values=(SELF,*extra)
            for k,value in w.__dict__.items():
                if k not in ('r','f','acc','hi','lo','hi1','lo1','fcond','covered','image','frame'):
                    setattr(native,k,value.copy() if isinstance(value,(list,dict,set)) else value)
            native.frame=SCRATCH+512
            for i in range(SIZES[entry]):native.w(native.frame+i,1,w.read(w.frame+i,1))
            result=w.invoke(entry,*values)
            fn=base if entry in (INIT,PREV,NEXT) else chip
            actual=fn(C.byref(api),entry,(C.c_uint64*8)(*[x&MASK for x in values]),native.frame)
            assert not errors,errors
            if entry in (PREV,NEXT,COUNT):assert result==actual,('return',hex(entry),result,actual)
            def ram(obj):return {p:v for p,v in obj.mem.items() if v and not STACK-0x10000<=p<STACK+64 and not SCRATCH<=p<SCRATCH+0x10000}
            er,ar=ram(w),ram(native)
            assert er==ar,('RAM',hex(entry),[(hex(p),er.get(p,0),ar.get(p,0)) for p in er.keys()|ar.keys() if er.get(p,0)!=ar.get(p,0)][:12])
            if w.events!=native.events:
                i=next((i for i,(x,y) in enumerate(zip(w.events,native.events)) if x!=y),min(len(w.events),len(native.events)))
                raise AssertionError(('event',hex(entry),i,w.events[i:i+1],native.events[i:i+1]))
            assert w.font_states==native.font_states
            coverage.update(w.covered);cases+=1
            return result
        for maximum,mutation in itertools.product((-2147483648,-1,0,1,2,3,2147483647),(None,'init_multi','init_single')):
            w=ViewWorld(image);w.w(SELF+88,4,maximum);w.mutation=mutation;compare(w,INIT,LEFT,RIGHT)
        for entry,page,maximum,mask,vertical in itertools.product((PREV,NEXT),(-2,0,1,2,3),(0,1,2,3),range(16),(0,1,4,5)):
            w=ViewWorld(image);w.w(SELF+84,4,page);w.w(SELF+88,4,maximum)
            if mask&1:w.w(PADS+28,4,8 if entry==PREV else 2)
            if mask&2:w.w(PADS+32,4,8 if entry==PREV else 2)
            if mask&4:w.w(PADS+72,4,128 if entry==PREV else 32)
            if mask&8:w.w(PADS+76,4,128 if entry==PREV else 32)
            w.w(PADS+36,4,vertical);compare(w,entry)
        for count,page in itertools.product((-2147483648,-25,-13,-12,-1,0,1,11,12,13,23,24,25,2147483647),(-2147483648,-2,-1,0,1,2,3,2147483647)):
            w=ViewWorld(image);w.w(ITEM_LIST+8,4,count);w.w(SELF+84,4,page);compare(w,COUNT)
        for count,page,selected,rows,detail in itertools.product((-1,0,1,11,12,13,24,25),(-1,0,1,2),(-1,0,11),(0,1),(0,1)):
            w=ViewWorld(image);w.w(ITEM_LIST+8,4,count);w.w(SELF+84,4,page);w.w(SELF+48,4,selected);compare(w,TEXT,rows,detail)
        for price in (-2147483648,-1,0,1,12345,0x80000000,0x100000000,0x7fffffffffffffff):
            w=ViewWorld(image);w.prices[ITEMS]=price;compare(w,TEXT,1,1)
        for mutation in ('lookup','font','list','page'):
            w=ViewWorld(image);w.mutation=mutation;compare(w,TEXT,1,1)
        for entry,player,disabled in itertools.product((PREV,NEXT),range(4),(0,1,255)):
            w=ViewWorld(image);w.w(SELF+20,4,player);w.w(PAD_MANAGER+29,1,disabled);w.w(SELF+84,4,1)
            pad=PADS+(4 if disabled else player)*256
            w.w(pad+28,4,8 if entry==PREV else 2);assert compare(w,entry)==1
        for entry,page in ((PREV,1),(PREV,2),(NEXT,0),(NEXT,1)):
            w=ViewWorld(image);w.w(SELF+84,4,page);w.mutation='send';w.w(PADS+28,4,8 if entry==PREV else 2)
            assert compare(w,entry)==1;assert w.read(SELF+84,4)==0x80000000
        for count in (0,1,12,13,100):
            w=ViewWorld(image);w.w(SELF+96,4,SELF+80);w.w(SELF+88,4,count)
            compare(w,COUNT)
        for rows,detail,context in itertools.product((0,1,0x100000000),(0,1,0x100000000),(0,STATUS)):
            w=ViewWorld(image);w.context=context;compare(w,TEXT,rows,detail)
        w=ViewWorld(image);w.w(ITEM_DATA,4,0);compare(w,TEXT,1,1)
        for group in (b'STWINFONT14',b'STWINFONT17',b'STWINFONT29'):
            assert w.font_states[(group,w.string(w.read(0x4cf8a0,4))) ]==(b'old',True)
        for page in (0,8,9,16,207):
            w=ViewWorld(image);w.w(SELF+84,4,page);w.w(SELF+88,4,page+1);compare(w,TEXT,1,0)
            key=(b'STWINFONT30',w.string(w.read(0x4cf8a0,4)))
            byte=(page+49)&255;assert w.font_states[key][0]==(bytes([byte]) if byte else b'')
        for next_x in (0,1,0x100000000):
            w=ViewWorld(image);w.prices[ITEMS]=next_x;compare(w,TEXT,1,0)
            key=(b'STWINFONT17',w.string(w.read(0x4cf8a0,4)))
            assert w.font_states[key][0]==(b'----' if not next_x else b'0' if next_x==0x100000000 else b'1')
        wanted=set();padding=set();reviewed=set()
        for r in json.loads((ROOT/'data/function-extents.json').read_text()):
            entry=int(r['address'],0)
            if entry not in ENTRIES:continue
            reviewed.add(entry)
            span=set(range(entry,int(r['end_exclusive'],0),4));occupied={p for x in r['body_ranges'] for p in range(int(x['start'],0),int(x['end_exclusive'],0),4)}
            wanted|=span;padding|=span-occupied
        assert reviewed==set(ENTRIES),(reviewed,set(ENTRIES))
        missing=wanted-coverage-padding
        if missing:print('missing',','.join(hex(p) for p in sorted(missing)))
        assert not missing,len(missing)
        for p in padding:assert w.read(p,4)==0,hex(p)
        print(f'ListCtrl/chip view: {cases} RAM/defined-return/ordered-call cases, {len(coverage&wanted)}/{len(wanted)} addresses ({len(padding)} zero padding); model/property/text services controlled')

if __name__=='__main__':main()
