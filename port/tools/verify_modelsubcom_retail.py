#!/usr/bin/env python3
"""Compare typed HITBOX subcommands with retail 39a500's producer.
Allocation and list insertion are controlled; end-frame math and receiver-group
classification execute original instructions. This does not measure scheduling.
"""
import ctypes as C
import random
import tempfile
from pathlib import Path
from native_shared import build_shared
from verify_scriptservices_retail import World, ROOT, BASE

OWNER, COMMAND, BOX, LIST = [BASE+0x700000+i*0x1000 for i in range(4)]
RAM, MGR, SYS, VT, PULSE = [BASE+0x704000+i*0x1000 for i in range(5)]

def bits(x):
    return int.from_bytes(C.c_float(x), 'little')

class Retail(World):
    def call(self, entry, args):
        if entry==0x22fd70:
            self.f[0]=bits(C.c_int64(args[0]).value);return 0
        args=[a & 0xffffffff for a in args]
        if entry in (0x301000,0x2f88e0):return 1
        if entry==0x34f6f0:
            for i in range(0,60,4):self.w(BOX+i,4,0)
            self.w(BOX+4,4,1)
            return BOX
        if entry==0x301e30:
            assert args[:2]==[LIST,BOX]
            self.w(BOX+4,4,self.read(BOX+4,4)+1)
            return 0
        if entry==0x2ff820:return 0 # deallocation leaf; list/state/order are compared below
        if entry==PULSE:
            self.events.extend([C.c_int32(self.read(args[0]+20,4)).value,self.read(args[0]+12,4)])
            return 1
        if entry==0x2d6cf0:
            values=self.values(args[0]);values.pop(args[1]);self.list(args[0],values);return 0
        return super().call(entry,args)
    def make(self, kind, start, length, geometry):
        self.descend=set();self.w(OWNER+8,4,LIST)
        self.w(COMMAND+12,4,kind);self.w(COMMAND+16,4,start);self.w(COMMAND+20,4,length)
        for i,v in enumerate(geometry):self.w(COMMAND+24+4*i,4,v)
        self.invoke(0x39a500,OWNER,COMMAND)
        return [self.read(BOX+i,4) for i in range(8,60,4)]

    def advance_rows(self, rows, frame):
        self.events=[];self.descend={0x399d90,0x3998f0}
        self.w(OWNER+8,4,LIST);self.w(RAM+16,4,MGR);self.w(MGR+16,4,SYS);self.w(SYS+40,4,frame)
        self.w(VT+92,4,PULSE);self.w(VT+96,4,0x3998f0)
        objects=[]
        for i,(kind,start,end,run,one) in enumerate(rows):
            b=BOX+i*0x100;objects.append(b);self.w(b,4,VT);self.w(b+4,4,1)
            for off,v in [(8,one),(12,run),(16,start),(20,kind),(28,end)]:self.w(b+off,1 if off==8 else 4,v)
        self.list(LIST,objects);self.invoke(0x399e20,OWNER,RAM)
        remaining=[]
        for b in self.values(LIST):remaining.extend([self.read(b+20,4),self.read(b+8,1),self.read(b+12,4)])
        return self.events,remaining
    def frame(self, previous, now):
        self.w(SYS+12,4,MGR);self.w(SYS+24,8,previous);self.w(MGR+80,8,now)
        self.ee_reset();self.r[4]=SYS;self.r[28]=0x55c870;self.r[29]=0x1fff000
        self.run_until(0x3a0020,0x3a0074)
        return self.read(SYS+40,4)

def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('model subcommands: private ELF unavailable, skipped');return
    retail=Retail(elf.read_bytes());rng=random.Random(20836)
    with tempfile.TemporaryDirectory() as td:
        td=Path(td);bridge=td/'bridge.c';so=td/'subcommands.so'
        bridge.write_text('''#include "dw4/modelsubcom.h"
#include "arenalist.h"
int sample(int kind,unsigned start,unsigned length,const float *g,unsigned *out){
    dw4_arena *a=dw4_session_arena();unsigned before=dw4_arena_live(a,DW4_REGION_PERSISTENT);
    dw4_handle h=dw4_modelsubcom_new(a);if(!h.off)return -1;
    if(dw4_modelsubcom_hitbox(a,h,kind,start,length,g,g+3)){dw4_modelsubcom_close(a,h);return -1;}
    beModelCtrlSubCom *s=DW4_ARENA_OBJ(a,beModelCtrlSubCom,h);
    int32_t child=al_words(a,s->_comList)[0];
    beModelCtrlSCHitBox *b=DW4_ARENA_OBJ(a,beModelCtrlSCHitBox,al_handle(child));
    memcpy(out,(unsigned char *)b+8,52);dw4_modelsubcom_close(a,h);
    return dw4_arena_live(a,DW4_REGION_PERSISTENT)==before?0:-1;
}

struct pulse {dw4_arena *arena;unsigned *events;int n;};
static int emit(void *u,dw4_handle h){struct pulse *p=u;beModelCtrlSCHitBox *b=DW4_ARENA_OBJ(p->arena,beModelCtrlSCHitBox,h);
    p->events[p->n++]=(unsigned)b->_kind;memcpy(p->events+p->n++,&b->_runFrame,4);return 0;}
int step(unsigned n,const unsigned *input,unsigned frame,unsigned *events,unsigned *out){
    dw4_arena *a=dw4_session_arena();unsigned before=dw4_arena_live(a,DW4_REGION_PERSISTENT);dw4_handle h=dw4_modelsubcom_new(a);
    const float zero[3]={0};if(!h.off)return -1;
    beModelCtrlSubCom *s=DW4_ARENA_OBJ(a,beModelCtrlSubCom,h);
    for(unsigned i=0;i<n;i++){const unsigned *v=input+5*i;
        if(dw4_modelsubcom_hitbox(a,h,(int)v[0],v[1],0,zero,zero))return -1;
        beModelCtrlSCHitBox *b=DW4_ARENA_OBJ(a,beModelCtrlSCHitBox,al_handle(al_words(a,s->_comList)[i]));
        memcpy(&b->_endFrame,v+2,4);memcpy(&b->_runFrame,v+3,4);b->_isOneSet=(unsigned char)v[4];}
    struct pulse p={a,events+1,0};if(dw4_modelsubcom_step(a,h,frame,emit,&p))return -1;events[0]=p.n;
    int count=al_count(a,s->_comList);out[0]=(unsigned)count*3;
    for(int i=0;i<count;i++){beModelCtrlSCHitBox *b=DW4_ARENA_OBJ(a,beModelCtrlSCHitBox,al_handle(al_words(a,s->_comList)[i]));
        out[1+3*i]=(unsigned)b->_kind;out[2+3*i]=b->_isOneSet;memcpy(out+3+3*i,&b->_runFrame,4);}
    igObjectList *l=DW4_ARENA_OBJ(a,igObjectList,al_handle(s->_comList));
    unsigned *tail=l->_capacity?dw4_arena_at(a,al_handle(l->_data),(unsigned)l->_capacity*4):0;
    for(int i=count;i<l->_capacity;i++)if(tail[i])return -1;
    dw4_modelsubcom_close(a,h);return dw4_arena_live(a,DW4_REGION_PERSISTENT)==before?0:-1;
}

''')
        build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),
            '-I'+str(ROOT/'recovered/frontend'),'-I'+str(ROOT/'src'),str(bridge),str(ROOT/'src/modelsubcom.c'),
            str(ROOT/'src/modelai.c'),str(ROOT/'src/random.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.sample.argtypes=[C.c_int32,C.c_uint32,C.c_uint32,C.POINTER(C.c_float),C.POINTER(C.c_uint32)]
        kinds=[-2147483648,-10001,-10000,-9999,-1,0,999,1000,9999,10000,59999,60000,69999,70000,79999,80000,89999,90000,2147483647]
        cases=[(k,s,l) for k in kinds for s,l in [(0,-1),(1,0),(.25,.125),(16777216,1),(-2,-2),(3.5,10.75)]]
        cases += [(rng.randint(-2147483648,2147483647),rng.uniform(-50,50),rng.uniform(-10,50)) for _ in range(256)]
        for kind,start,length in cases:
            geometry=(C.c_float*6)(*[rng.uniform(-10,10) for _ in range(6)])
            expected=retail.make(kind,bits(start),bits(length),[bits(v) for v in geometry])
            out=(C.c_uint32*13)();assert lib.sample(kind,bits(start),bits(length),geometry,out)==0
            assert list(out)==expected,(kind,start,length,list(out),expected)
        lib.step.argtypes=[C.c_uint,C.POINTER(C.c_uint32),C.c_uint32,C.POINTER(C.c_uint32),C.POINTER(C.c_uint32)]
        # No-start, exact-start, first-crossing past end, strict end, adjacent removals,
        # and zero/negative/large frame deltas; then randomized per-entry states.
        schedules=[([(1,bits(s),bits(e),bits(r),one)],bits(d))
            for s,e,r,one,d in [(2,4,0,0,1),(1,4,0,0,1),(1,1,0,0,5),(0,0,0,0,0),
                (0,1,0,1,1),(0,1,0,1,0),(3,4,2,0,-1),(0,2,0,1,10)]]
        schedules += [([(i+1,bits(rng.choice([0,.5,2,5])),bits(rng.choice([0,1,3,10])),bits(rng.choice([0,.25,1,2,8])),rng.randrange(2))
            for i in range(rng.randrange(9))],bits(rng.choice([0,.25,.5,1,3,30,-1]))) for _ in range(512)]
        for rows,frame in schedules:
            flat=[v & 0xffffffff for row in rows for v in row];data=(C.c_uint32*len(flat))(*flat)
            events=(C.c_uint32*32)();out=(C.c_uint32*32)();assert lib.step(len(rows),data,frame,events,out)==0
            expected_events,expected_rows=retail.advance_rows(rows,frame)
            assert list(events)[1:events[0]+1]==expected_events,(rows,frame,list(events),expected_events)
            assert list(out)[1:out[0]+1]==expected_rows,(rows,frame,list(out),expected_rows)
        lib.dw4_modelsubcom_frame.argtypes=[C.c_int64,C.c_int64];lib.dw4_modelsubcom_frame.restype=C.c_uint32
        clocks=[(0,0),(0,16666666),(0,16666667),(0,1000000000),(123456789,123456789),
            (1000000000,0),(-9223372036854775808,9223372036854775807),(9223372036854775807,-9223372036854775808)]
        for _ in range(128):
            start=rng.randrange(-2**63,2**63);clocks.append((start,C.c_int64(start+rng.randrange(-10**10,10**10)).value))
        for previous,now in clocks:assert lib.dw4_modelsubcom_frame(previous,now)==retail.frame(previous,now),(previous,now)
        lib.dw4_model_lock_matrix.argtypes=[C.POINTER(C.c_float)]*3
        for _ in range(128):
            parent=(C.c_float*16)(*[rng.uniform(-30,30) for _ in range(16)]);offset=(C.c_float*3)(*[rng.uniform(-10,10) for _ in range(3)])
            for i,v in enumerate(parent):retail.w(BOX+4*i,4,bits(v))
            for i,v in enumerate(offset):retail.w(COMMAND+4*i,4,bits(v))
            retail.descend=set();retail.invoke(0x190a50,BOX,COMMAND)
            out=(C.c_float*16)();lib.dw4_model_lock_matrix(out,parent,offset)
            assert [bits(v) for v in out]==[retail.read(BOX+4*i,4) for i in range(16)]
        print(f'model scheduler: {len(schedules)} pulse/compaction states, {len(clocks)} System frame samples and 128 node-lock matrices match retail')
    print(f'model subcommands: {len(cases)} typed HITBOX objects match original producer math/groups/geometry; teardown balances')

if __name__=='__main__':main()
