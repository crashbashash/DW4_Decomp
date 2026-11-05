#!/usr/bin/env python3
"""Mixed MODELCTRL subcommand scheduling/clear and sound handle admission.
Original instructions run with controlled allocation, virtual media and receiver
leaves. This does not establish audible mixing or whole-scene update order.
"""
import ctypes as C
import random
import tempfile
from pathlib import Path
from native_shared import build_shared
from verify_modelsubcom_retail import Retail, ROOT, BASE, OWNER, BOX, LIST, RAM, MGR, SYS, VT, COMMAND, bits

from ee_core import f_add, f_mul

META, START, FINISH = [BASE+0x780000+i*0x100 for i in range(3)]
class Mixed(Retail):
    def ee_reset(self):
        super().ee_reset();self.vf=[[0]*4 for _ in range(32)];self.vacc=[0]*4
    def step(self,pc,delay=False):
        w=self.read(pc,4);op=w>>26;rs=w>>21&31;rt=w>>16&31
        if op in (0x36,0x3e):
            imm=C.c_int16(w&65535).value;addr=(self.r[rs]+imm)&0xffffffff
            for i in range(4):
                if op==0x36:self.vf[rt][i]=self.read(addr+4*i,4)
                else:self.w(addr+4*i,4,self.vf[rt][i])
            self.covered.add(pc);return pc+4
        if op==0x12 and rs>=16:
            fs=w>>11&31;fd=w>>6&31;fn=w&63
            for c,bit in enumerate((24,23,22,21)):
                if not w>>bit&1:continue
                if fn==0x3c and fd==6:self.vacc[c]=f_mul(self.vf[fs][c],self.vf[rt][0])
                elif fn in (0x3d,0x3e) and fd==2:self.vacc[c]=f_add(self.vacc[c],f_mul(self.vf[fs][c],self.vf[rt][fn-0x3c]))
                elif fn==0x0b:self.vf[fd][c]=f_add(self.vacc[c],f_mul(self.vf[fs][c],self.vf[rt][3]))
                else:raise AssertionError(('unsupported scoped VU instruction',hex(w)))
            self.covered.add(pc);return pc+4
        return super().step(pc,delay)
    def call(self,e,a):
        if getattr(self,'erase_mode',False):
            if e==0x3022c0:return BASE+0x790000
            if e==0x12a4a4:return 0 # the pending name is the original SQ_ERAS
            if e==FINISH:
                assert a[2]&0xffffffff==0x50f1c0
                self.erase_calls+=1;return 0
            raise AssertionError(('unexpected erase leaf',hex(e)))
        if e in (0x34f8e0,0x34f4a0):
            for i in range(0,64,4):self.w(BOX+i,4,0)
            self.w(BOX+4,4,1);return BOX
        if e in (META,START,FINISH):
            row=self.rows[(a[0]-BOX)//0x100]
            if e==META:return 0x70000000+row[0]
            self.events.extend([row[1],int(e==FINISH)])
            return row[5] if e==START else 0
        if e==0x36f8b0:return 1
        if e==0x38e5d0 or e==0x38f830 or e==0x38e060:return 0
        if e==0x38f480:return self.handle & ((1<<64)-1)
        if e==0x38f320:return self.sound_type
        return super().call(e,a)
    def run_rows(self,rows,frame,clear):
        self.rows=rows;self.events=[];self.descend={0x399d90,0x3998f0}
        self.w(OWNER+8,4,LIST);self.w(RAM+16,4,MGR);self.w(MGR+16,4,SYS);self.w(SYS+40,4,frame)
        self.w(0x588800,4,0x70000002)
        objects=[]
        for i,row in enumerate(rows):
            kind,identity,one,run,start,keep,dead,end=row;b=BOX+i*0x100;v=VT+i*0x100
            self.w(b,4,v);self.w(b+4,4,1);self.w(b+8,1,one);self.w(b+12,4,run);self.w(b+16,4,start)
            self.w(b+20,4,identity);self.w(b+28,4,end);self.w(b+56,1,dead)
            self.w(v+88,4,META);self.w(v+92,4,START);self.w(v+96,4,0x3998f0 if kind==1 else 0x36f8b0);self.w(v+100,4,FINISH);objects.append(b)
        self.list(LIST,objects)
        if clear<0:self.invoke(0x399e20,OWNER,RAM)
        elif clear==0:self.invoke(0x399f20,OWNER,RAM)
        else:self.invoke(0x39a130,OWNER,RAM,0x70000000+clear)
        out=[]
        for b in self.values(LIST):
            row=rows[(b-BOX)//0x100];out.extend([row[1],self.read(b+8,1),self.read(b+12,4)])
        return self.events,out
    def sound(self,handle,kind,prior):
        self.handle=handle;self.sound_type=kind;self.descend=set();self.w(RAM+16,4,MGR);self.w(MGR+20,4,1)
        self.w(BOX+24,8,prior);result=self.invoke(0x399c50,BOX,RAM)
        return result,self.read(BOX+24,8)

    def pending_erase(self,active,freeze):
        self.erase_mode=True;self.erase_calls=0;self.descend=set()
        self.w(MGR,4,VT);self.w(VT+140,4,FINISH);self.w(RAM+40,4,1)
        self.w(RAM+20,1,active);self.w(BASE+0x790000+20,4,BASE+0x791000)
        self.w(BASE+0x791000+20,4,self.token('SQ_ERAS'));self.w(BASE+0x791000+69,1,freeze)
        self.invoke(0x395b50,MGR,RAM);self.erase_mode=False
        return self.erase_calls
    def produce(self,effect,start,geometry,dead,follow):
        self.descend=set();self.w(OWNER+8,4,LIST)
        for i,v in enumerate(geometry):self.w(COMMAND+4*i,4,v)
        self.ee_reset();self.r[4:11]=[OWNER,self.token('model'),self.token('sequence'),COMMAND,COMMAND+12,dead,follow]
        self.r[28],self.r[29],self.r[31]=0x55c870,0x1fff000,0xfffffff0;self.f[12]=start
        self.run_until(0x39a250 if effect else 0x39a750,0xfffffff0)
        out=[self.read(BOX+i,4) for i in range(8,60 if effect else 32,4)]
        if effect:out[4]=out[5]=0
        else:out[3]=0
        return out

BRIDGE=r'''
#include "dw4/modelsubcom.h"
#include "arenalist.h"
struct context {dw4_arena *a;const unsigned *rows;unsigned *events;int n;};
static int event(void *u,dw4_handle h,int finish,int *keep){
    struct context *c=u;
    /* IDs live in a temporary lookup, independently of payload geometry. */
    for(unsigned i=0;i<8;i++)if(c->rows[8*i+1]==h.off){
        const unsigned *r=c->rows+8*i;c->events[c->n++]=r[0];c->events[c->n++]=finish;*keep=(int)r[5];return 0;}
    return -1;
}
int mixed(unsigned count,const unsigned *input,unsigned frame,int clear,unsigned *events,unsigned *output){
    dw4_arena *a=dw4_session_arena();unsigned before=dw4_arena_live(a,DW4_REGION_PERSISTENT);dw4_handle h=dw4_modelsubcom_new(a);
    if(!h.off)return -1;unsigned rows[64]={0};float zero[3]={0};beModelCtrlSubCom *s=DW4_ARENA_OBJ(a,beModelCtrlSubCom,h);
    for(unsigned i=0;i<count;i++){
        const unsigned *r=input+8*i;int rc=r[0]==1?dw4_modelsubcom_hitbox(a,h,(int)r[1],r[4],0,zero,zero):
            r[0]==2?dw4_modelsubcom_effect(a,h,"model","sequence",r[4],zero,zero,(unsigned char)r[6],0):dw4_modelsubcom_sound(a,h,"sound",r[4]);
        if(rc)return -1;dw4_handle child=al_handle(al_words(a,s->_comList)[i]);unsigned char *b=dw4_arena_at(a,child,20);
        b[8]=(unsigned char)r[2];memcpy(b+12,r+3,4);rows[8*i]=r[1];rows[8*i+1]=child.off;rows[8*i+5]=r[5];
        if(r[0]==1){beModelCtrlSCHitBox *hit=DW4_ARENA_OBJ(a,beModelCtrlSCHitBox,child);memcpy(&hit->_endFrame,r+7,4);}
    }
    struct context c={a,rows,events+1,0};int rc=clear<0?dw4_modelsubcom_step_events(a,h,frame,event,&c):dw4_modelsubcom_clear_events(a,h,clear,event,&c);
    if(rc)return -1;events[0]=(unsigned)c.n;igDataList *l=al_list(a,s->_comList);output[0]=(unsigned)l->_count*3;
    for(int i=0;i<l->_count;i++){
        dw4_handle child=al_handle(al_words(a,s->_comList)[i]);unsigned char *b=dw4_arena_at(a,child,20);
        for(unsigned j=0;j<count;j++)if(rows[8*j+1]==child.off)output[1+3*i]=rows[8*j];
        output[2+3*i]=b[8];memcpy(output+3+3*i,b+12,4);
    }
    unsigned *tail=l->_capacity?dw4_arena_at(a,al_handle(l->_data),(unsigned)l->_capacity*4):0;
    for(int i=l->_count;i<l->_capacity;i++)if(tail[i])return -1;
    dw4_modelsubcom_close(a,h);return dw4_arena_live(a,DW4_REGION_PERSISTENT)==before?0:-1;
}
int sound(long long handle,int kind,unsigned long long prior,unsigned long long *out){
    dw4_arena *a=dw4_session_arena();unsigned before=dw4_arena_live(a,DW4_REGION_PERSISTENT);dw4_handle h=dw4_modelsubcom_new(a);
    if(dw4_modelsubcom_sound(a,h,"sound",0))return -1;beModelCtrlSubCom *s=DW4_ARENA_OBJ(a,beModelCtrlSubCom,h);
    dw4_handle child=al_handle(al_words(a,s->_comList)[0]);beModelCtrlSCSound *b=DW4_ARENA_OBJ(a,beModelCtrlSCSound,child);memcpy(&b->_sndHandle,&prior,8);
    int keep=dw4_modelsubcom_sound_result(a,child,handle,kind);memcpy(out,&b->_sndHandle,8);dw4_modelsubcom_close(a,h);
    return dw4_arena_live(a,DW4_REGION_PERSISTENT)==before?keep:-1;
}
int producer(int effect,unsigned start,const float *geometry,unsigned dead,unsigned follow,unsigned *out){
    dw4_arena *a=dw4_session_arena();unsigned before=dw4_arena_live(a,DW4_REGION_PERSISTENT);dw4_handle h=dw4_modelsubcom_new(a);
    int rc=effect?dw4_modelsubcom_effect(a,h,"model","sequence",start,geometry,geometry+3,(unsigned char)dead,(unsigned char)follow):dw4_modelsubcom_sound(a,h,"model",start);
    if(rc)return -1;beModelCtrlSubCom *s=DW4_ARENA_OBJ(a,beModelCtrlSubCom,h);dw4_handle child=al_handle(al_words(a,s->_comList)[0]);
    unsigned char *b=dw4_arena_at(a,child,effect?60:32);memcpy(out,b+8,effect?52:24);
    if(effect)out[4]=out[5]=0;else out[3]=0;
    dw4_modelsubcom_close(a,h);return dw4_arena_live(a,DW4_REGION_PERSISTENT)==before?0:-1;
}

'''
def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('model dependencies: private ELF unavailable, skipped');return
    retail=Mixed(elf.read_bytes());rng=random.Random(399940)
    for active in (0,1):
        for freeze in (0,1):assert retail.pending_erase(active,freeze)==int(active and not freeze)
    with tempfile.TemporaryDirectory() as td:
        td=Path(td);source=td/'bridge.c';source.write_text(BRIDGE);so=td/'mixed.so'
        build_shared(['cc','-shared','-fPIC','-std=c99','-I'+str(ROOT/'include'),'-I'+str(ROOT/'src'),'-I'+str(ROOT/'recovered/frontend'),
            str(source),str(ROOT/'src/modelsubcom.c'),str(ROOT/'src/modelai.c'),str(ROOT/'src/random.c'),str(ROOT/'recovered/frontend/eefloat.c'),'-o',str(so)],check=True)
        lib=C.CDLL(str(so));lib.mixed.argtypes=[C.c_uint,C.POINTER(C.c_uint32),C.c_uint32,C.c_int,C.POINTER(C.c_uint32),C.POINTER(C.c_uint32)]
        for case in range(768):
            n=rng.randrange(9);rows=[(rng.randrange(1,4),i+1,rng.randrange(2),bits(rng.choice([0,.5,2,10])),bits(rng.choice([0,1,3,8])),rng.randrange(2),rng.randrange(2),bits(rng.choice([0,1,4,20]))) for i in range(n)]
            rows=[r[:5]+(1,)+r[6:] if r[0]==1 else r for r in rows]
            frame=bits(rng.choice([0,.25,1,5,-1]));clear=rng.choice([-1,-1,0,1,2,3]);flat=[v for r in rows for v in r]
            data=(C.c_uint32*len(flat))(*flat);events=(C.c_uint32*40)();out=(C.c_uint32*40)()
            assert lib.mixed(n,data,frame,clear,events,out)==0
            expected_events,expected_rows=retail.run_rows(rows,frame,clear)
            assert list(events)[1:events[0]+1]==expected_events,(case,rows,clear,list(events),expected_events)
            assert list(out)[1:out[0]+1]==expected_rows,(case,rows,clear,list(out),expected_rows)
        lib.sound.argtypes=[C.c_int64,C.c_int,C.c_uint64,C.POINTER(C.c_uint64)]
        count=0
        for handle in [-2**63,-1,0,1,2**31,2**32+1,0x123456789abcdef,2**63-1]:
            for kind in [-1,0,1,2,3,4,5,0x104]:
                prior=rng.randrange(2**64);out=C.c_uint64();keep=lib.sound(handle,kind,prior,C.byref(out));expected=retail.sound(handle,kind,prior)
                assert (keep,out.value)==expected,(handle,kind,(keep,out.value),expected);count+=1
        lib.producer.argtypes=[C.c_int,C.c_uint32,C.POINTER(C.c_float),C.c_uint,C.c_uint,C.POINTER(C.c_uint32)]
        for i in range(256):
            effect=i%2;start=bits(rng.uniform(-30,60));geometry=(C.c_float*6)(*[rng.uniform(-30,30) for _ in range(6)])
            dead=rng.randrange(256);follow=rng.randrange(256);out=(C.c_uint32*13)()
            assert lib.producer(effect,start,geometry,dead,follow,out)==0
            expected=retail.produce(effect,start,[bits(v) for v in geometry],dead,follow)
            assert list(out)[:len(expected)]==expected,(i,list(out),expected)
        lib.dw4_model_local_matrix.argtypes=[C.POINTER(C.c_float)]*3
        for i in range(256):
            world=(C.c_float*16)(*[rng.uniform(-50,50) for _ in range(16)]);local=(C.c_float*16)(*[rng.uniform(-20,20) for _ in range(16)])
            for j,v in enumerate(world):retail.w(BOX+4*j,4,bits(v))
            for j,v in enumerate(local):retail.w(COMMAND+4*j,4,bits(v))
            retail.descend=set();retail.invoke(0x1906d0,BOX,COMMAND)
            out=(C.c_float*16)();lib.dw4_model_local_matrix(out,world,local)
            assert [bits(v) for v in out]==[retail.read(BOX+4*j,4) for j in range(16)],i
    print('model dependencies: 256 effect/sound producer payloads, 256 full matrix compositions and 4 pending-erase gates match original instructions')
    print(f'model dependencies: 768 mixed activation/sequence/class-clear states and {count} full-width sound-handle states match retail; arena teardown balances')
if __name__=='__main__':main()
