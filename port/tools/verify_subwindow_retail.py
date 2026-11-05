#!/usr/bin/env python3
"""Compare native SUBWND scalar commands and window-tree updates with retail.

Original 3d60e0/3f6490 instructions execute from the private ELF. Message
contexts, enum lookup, menu-specific virtual updates and list storage are
controlled leaves; this does not execute inventory/shop/save gameplay.
"""
from native_shared import build_shared
import argparse
import ctypes as C
import itertools
from pathlib import Path
import subprocess
import tempfile
from verify_scriptservices_retail import World, BASE, ROOT

OWNER,RAM,CTX,WINDOW,VTABLE,CHILDREN=range(BASE+0x80000,BASE+0x80600,0x100)
UPDATE=BASE+0x90000
from menu_window_ffi import Window, WP, IO, bind_windows
class State(C.Structure):
    _fields_=[(n,C.c_int32) for n in ('active','state','sub','delay','latch','player','mode')]
class Retail(World):
    def __init__(self,image):
        super().__init__(image);self.descend={0x3d60e0,0x3f6490};self.events=[];self.nodes={}
        self.w(OWNER+20,4,CTX);self.w(CTX+20,4,self.token('GENERATE'));self.w(VTABLE+92,4,UPDATE)
    def call(self,e,a):
        a=[v&0xffffffff for v in a]
        if e==0x3bb730:return 1
        if e==0x3b1d70:return 2
        if e==0x38d4a0:return self.key if a[1]==1 else self.mode
        if e==0x38f320:return self.player
        if e==0x38f8f0:return self.token('STATUS')
        if e==0x38f150:self.answer=a[1];return 0
        if e==0x38e670:self.events.append(('dispatch',self.string(a[1]),self.string(a[2])));return 0
        if e==0x38d470:self.events.append(('hold',a[1]));return 0
        if e==0x38ecf0:self.events.append(('defer',self.string(a[1]),self.string(a[2]),a[3]));return 0
        if e==UPDATE:
            p=a[0];self.events.append(('update',self.nodes[p]))
            if self.read(p+28,4)>=2:
                delay=self.read(p+36,4)+1;self.w(p+36,4,delay)
                if delay>=self.nodes[p]%3+1:self.w(p+24,4,0)
            return 0
        if e==0x2ff820:self.events.append(('release',self.nodes[a[0]]));return 0
        if e==0x2d6cf0:
            values=self.values(a[0]);del values[a[1]];self.list(a[0],values);return 0
        return super().call(e,a)
    def command(self,key,s,root):
        self.key=key;self.player=s.player;self.mode=s.mode;self.events=[];self.answer=None
        for offset,k in [(20,'active'),(24,'state'),(28,'sub'),(32,'delay'),(36,'latch')]:self.w(RAM+offset,1 if k=='active' else 4,getattr(s,k))
        self.w(OWNER+36,4,s.player);self.w(OWNER+40,4,s.mode);self.w(OWNER+32,4,WINDOW if root else 0)
        if root:
            for off,k in [(24,'active'),(28,'state'),(32,'sub'),(36,'delay'),(40,'latch')]:self.w(WINDOW+off,4,getattr(root.contents,k))
        assert self.invoke(0x3d60e0,OWNER,RAM,CTX)==1
        vals=[self.read(RAM+off,size) for off,size in [(20,1),(24,4),(28,4),(32,4),(36,4)]]
        vals += [self.read(OWNER+36,4),self.read(OWNER+40,4)]
        return vals
    def tree(self,states):
        self.nodes={};self.events=[]
        ptrs=[BASE+0xa0000+i*0x100 for i in range(4)]
        for i,(active,state,sub,delay,latch) in enumerate(states):
            p=ptrs[i];self.nodes[p]=i;self.w(p,4,VTABLE);self.w(p+4,4,1)
            for off,val in zip([24,28,32,36,40],[active,state,sub,delay,latch]):self.w(p+off,4,val)
            children=[ptrs[1],ptrs[2]] if i==0 else [ptrs[3]] if i==1 else []
            self.w(p+52,4,BASE+0xb0000+i*0x100);self.list(BASE+0xb0000+i*0x100,children)
        self.invoke(0x3f6490,ptrs[0]);return ptrs

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--elf',type=Path,default=ROOT.parent.parent / 'local/extracted/SLUS_208.36')
    path=p.parse_args().elf
    if not path.exists():print('SUBWND retail: private ELF unavailable, skipped');return
    w=Retail(path.read_bytes())
    with tempfile.TemporaryDirectory() as tmp:
        so=Path(tmp)/'menu.so';build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),str(ROOT/'src/menuwindow.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));bind_windows(lib);lib.dw4_menu_window_open.argtypes=[IO,C.c_void_p,C.c_void_p];lib.dw4_menu_window_open.restype=WP
        lib.dw4_menu_window_add.argtypes=[WP,WP];lib.dw4_menu_window_tick.argtypes=[WP,C.c_void_p,C.c_size_t]
        lib.dw4_menu_window_close.argtypes=[WP];lib.dw4_subwindow_generate.argtypes=[C.POINTER(State),C.c_int32,C.c_int32]
        lib.dw4_subwindow_remove.argtypes=[C.POINTER(State),WP]
        commands=0
        @IO
        def noop(node,error,cap):return 0
        for active,mode,player,key,present in itertools.product([0,1],range(11),range(4),[0,1,6],[0,1]):
            s=State(active,3,4,5,6,player,mode)
            root=lib.dw4_menu_window_open(noop,None,None) if present else WP()
            if root:root.contents.state=1;root.contents.sub=7;root.contents.delay=8;root.contents.latch=9
            expected=w.command(key,s,root)
            if key==0:lib.dw4_subwindow_generate(C.byref(s),mode,player)
            elif key==1:
                deferred=lib.dw4_subwindow_remove(C.byref(s),root)
                assert bool(deferred)==bool(active and not present)
                if root:assert [root.contents.state,root.contents.sub,root.contents.delay,root.contents.latch]==[w.read(WINDOW+off,4) for off in (28,32,36,40)]
            else:assert w.answer==s.active
            assert list(getattr(s,n) for n,_ in State._fields_)==expected
            if root:lib.dw4_menu_window_close(root)
            commands+=1
        trees=0
        for root_state,root_active,child_state,child_active,grand_state in itertools.product(range(4),[0,1],range(4),[0,1],range(4)):
            states=[(root_active,root_state,7,0,9),(child_active,child_state,7,0,9),(1,1,7,0,9),(1,grand_state,7,0,9)]
            ptrs=w.tree(states);events=[];keep=[]
            @IO
            def update(node,error,cap):
                n=node.contents;i=n.user or 0;events.append(('update',i))
                if n.state>=2:
                    n.delay+=1
                    if n.delay>=i%3+1:n.active=0
                return 0
            release_type=C.CFUNCTYPE(None,C.c_void_p)
            @release_type
            def release(user):events.append(('release',user or 0))
            for i,values in enumerate(states):
                n=lib.dw4_menu_window_open(update,i,C.cast(release,C.c_void_p));keep.append(n)
                for name,val in zip(['active','state','sub','delay','latch'],values):setattr(n.contents,name,val)
            assert lib.dw4_menu_window_add(keep[0],keep[1])==0
            assert lib.dw4_menu_window_add(keep[0],keep[2])==0
            assert lib.dw4_menu_window_add(keep[1],keep[3])==0
            assert lib.dw4_menu_window_add(keep[3],keep[0])==-1
            error=C.create_string_buffer(256);assert lib.dw4_menu_window_tick(keep[0],error,256)==0,error.value
            assert events==w.events,(states,events,w.events)
            def compare(n,p):
                assert [getattr(n.contents,k) for k in ('active','state','sub','delay','latch')]==[w.read(p+off,4) for off in (24,28,32,36,40)]
                children=w.values(w.read(p+52,4));assert n.contents.count==len(children)
                for i,c in enumerate(children):compare(n.contents.children[i],c)
            compare(keep[0],ptrs[0]);lib.dw4_menu_window_close(keep[0]);trees+=1
        print(f'SUBWND retail: {commands} GENERATE/REMOVE/ISRUN states and {trees} nested-window update/close/prune states match original instructions')
if __name__=='__main__':main()
