#!/usr/bin/env python3
"""Compare BIND's enum status, channel writes and expiry branch with retail.

Execute 444480..444628 and the real GetValueByName lookup. Enum allocation,
string/list access, named-timer completion and sequence delivery are controlled
leaves. Full scene ordering and the status clock's source remain separate.
"""
import ctypes as C
import random
import tempfile
from pathlib import Path
from native_shared import build_shared
from verify_scriptservices_retail import World, ROOT, BASE
from verify_modelai_retail import Clock

WORK, TIMERS, FIRST, MOVES, META, NAMES, VALUES, CHANNELS, MANAGER, VT, SETSEQ = [
    BASE + 0x900000 + i * 0x1000 for i in range(11)]


class Bind(World):
    def read(self, address, size):
        if address in (0x4fb410, 0x4fb418) and address in self.mem:
            return sum(self.mem.get(address+i, 0) << (8*i) for i in range(size))
        return super().read(address, size)

    def string(self, p):
        p &= 0xffffffff
        out = []
        while self.read(p, 1):
            out.append(self.read(p, 1)); p += 1
        return bytes(out).decode('ascii')

    def call(self, entry, args):
        if entry == 0x32d1f0:
            return 0
        if entry == 0x3c03e0:
            return META
        if entry == 0x3a7e90:
            return self.done
        if entry == 0x22e4b8:
            return C.c_int64(args[0]).value // 60 if C.c_int64(args[0]).value >= 0 else -(-C.c_int64(args[0]).value // 60)
        if entry == 0x3a7a20:
            self.duration = C.c_int64(args[2]).value
            return 0
        if entry == 0x3a8580:
            self.removed = 1
            return 0
        if entry == SETSEQ:
            self.selected = self.string(args[2])
            return 0
        return super().call(entry, args)

    def sample(self, seq, ready, timer, first, done, rows):
        self.done = done; self.selected = None; self.removed = 0; self.duration = None
        covered = self.covered
        self.ee_reset(); self.covered = covered; self.descend = {0x2fba30}
        self.r[16:19] = [WORK, BASE, MANAGER]
        self.r[28], self.r[29] = 0x55c870, 0x1fff000
        self.w(MANAGER, 4, VT); self.w(VT+140, 4, SETSEQ)
        self.w(WORK+68, 1, ready); self.w(WORK+20, 4, self.token(seq))
        self.w(WORK+248, 4, TIMERS); self.list(TIMERS, [0, 0, 0, timer])
        self.w(WORK+252, 4, FIRST); self.list(FIRST, [0, 0, 0, first], 1)
        self.w(WORK+200, 4, MOVES)
        self.list(MOVES, [CHANNELS+i*64 for i in range(len(rows))])
        for i, row in enumerate(rows):
            for j, word in enumerate(row):
                self.w(CHANNELS+i*64+j*4, 4, word)
        self.run_until(0x444480, 0x444628)
        result = [[self.read(CHANNELS+i*64+j*4, 4) for j in range(11)] for i in range(len(rows))]
        return result, self.read(self.read(TIMERS+16, 4)+12, 4), self.read(self.read(FIRST+16, 4)+3, 1), self.selected


BRIDGE = r'''
#include "dw4/statusapply.h"
#include "arenalist.h"
int expiry(long long start,long long duration,long long now){
    dw4_status s;dw4_status_init(&s,0);s.timer[DW4_STATUS_BIND]=60;s.clock_ns=now;
    s.named[DW4_STATUS_BIND]=(dw4_status_clock){1,start,duration};
    int hp=10;dw4_status_tick_result r;dw4_status_tick(&s,0,"SQ_WAIT",&hp,&r);
    return r.sequence && !strcmp(r.sequence,"SQ_WAIT") && !s.timer[DW4_STATUS_BIND];
}
int sample(const char *seq,int ready,int timer,int first,int done,int n,unsigned *rows,unsigned *out){
    dw4_arena *a=dw4_session_arena();unsigned before=dw4_arena_live(a,DW4_REGION_PERSISTENT);
    dw4_handle h=dw4_arena_object_new(a,DW4_REGION_PERSISTENT,dw4_metaobject_find("beNDMWMdlPEBaseInfoWork")->vtable);
    beNDMWMdlPEBaseInfoWork *w=DW4_ARENA_OBJ(a,beNDMWMdlPEBaseInfoWork,h);
    dw4_status s;dw4_status_init(&s,0);s.ready=ready;s.timer[DW4_STATUS_BIND]=timer;s.first[DW4_STATUS_BIND]=first;
    s.named[DW4_STATUS_BIND]=(dw4_status_clock){1,0,done?-1:1000000000};
    /* Arming overrides the controlled completion result, as in a real clock. */
    int hp=10;dw4_status_tick_result r;dw4_status_tick(&s,0,seq,&hp,&r);
    w->_isOnCtrl=ready;w->_seqCodeName=al_string(a,seq);
    w->_timerList=al_new(a,"igIntList",4,DW4_STATUS_TIMER_SLOTS,s.timer);
    w->_moveObjectList=al_new(a,"beModelCtrlMoveObjectList",4,n,NULL);
    int32_t *v=al_words(a,w->_moveObjectList);
    for(int i=0;i<n;i++){
        dw4_handle c=dw4_arena_object_new(a,DW4_REGION_PERSISTENT,dw4_metaobject_find("beModelCtrlMoveObject")->vtable);
        v[i]=(int32_t)c.off;memcpy(dw4_arena_at(a,c,44),rows+11*i,44);
    }
    dw4_status_bind_movement(a,h);
    for(int i=0;i<n;i++){
        memcpy(rows+11*i,dw4_arena_at(a,al_handle(v[i]),44),44);
        /* Randomized payload includes the header; restore it for ownership. */
        beModelCtrlMoveObject *m=DW4_ARENA_OBJ(a,beModelCtrlMoveObject,al_handle(v[i]));
        m->_vtable=dw4_metaobject_find("beModelCtrlMoveObject")->vtable;m->_refCount=1;
        dw4_arena_object_release(a,al_handle(v[i]));
    }
    out[0]=(unsigned)s.timer[DW4_STATUS_BIND];out[1]=s.first[DW4_STATUS_BIND];out[2]=r.sequence && !strcmp(r.sequence,"SQ_WAIT");
    al_drop(a,&w->_moveObjectList);al_drop(a,&w->_timerList);al_free(a,w->_seqCodeName);dw4_arena_object_release(a,h);
    return dw4_arena_live(a,DW4_REGION_PERSISTENT)==before?0:-1;
}
'''


def main():
    elf = ROOT.parent.parent / 'local/extracted/SLUS_208.36'
    if not elf.exists():
        print('BIND retail: private ELF unavailable, skipped'); return
    retail = Bind(elf.read_bytes()); rng = random.Random(444480)
    # The ELF's zero-filled status objects are initialized by engine startup.
    retail.run_until(0x2d16c8, 0x2d16e0)
    assert retail.read(0x4fb410,4)==0 and retail.read(0x4fb418,4)==1
    # Load both enum arrays from the private ELF; do not substitute the native
    # name table or reduce lookup to a mocked found/not-found boolean.
    names = [retail.string(retail.read(0x4ca940+4*i, 4)) for i in range(10)]
    retail.w(META+12, 4, NAMES); retail.w(META+16, 4, VALUES)
    retail.list(NAMES, [retail.token(s) for s in names])
    retail.list(VALUES, [retail.read(0x4ca970+4*i, 4) for i in range(10)])
    sequences = names + ['SQ_WAIT', 'SQ_WALK', 'SQ_ATCK', 'SQ_JUMP', 'SQ_FALL', 'SQ_SLEP', 'SQ_SDMG_EXTRA', 'sq_sdmg', '']
    count = 0
    with tempfile.TemporaryDirectory() as td:
        td = Path(td); source = td/'bridge.c'; source.write_text(BRIDGE); so = td/'bind.so'
        build_shared(['cc', '-shared', '-fPIC', '-std=c99', '-I'+str(ROOT/'include'), '-I'+str(ROOT/'src'),
                      str(source), str(ROOT/'src/statusapply.c'), '-o', str(so)], check=True)
        lib = C.CDLL(str(so)); lib.sample.argtypes = [C.c_char_p]+[C.c_int]*5+[C.POINTER(C.c_uint32)]*2
        for seq in sequences:
            for ready in (0, 1):
                for timer, first, done in ((0,0,0),(60,0,0),(60,0,1),(60,1,0),(-1,0,0),(-1,1,1)):
                    for n in (0,1,2,4,7):
                        rows = [[rng.getrandbits(32) for _ in range(11)] for _ in range(n)]
                        data = (C.c_uint32*(n*11))(*(v for row in rows for v in row)); out = (C.c_uint32*3)()
                        expected, remaining, flag, selected = retail.sample(seq,ready,timer,first,done,rows)
                        assert lib.sample(seq.encode(),ready,timer,first,done,n,data,out)==0
                        assert list(data)==[v for row in expected for v in row], (seq,ready,timer,first,done,n)
                        assert list(out)==[remaining,flag,int(selected=='SQ_WAIT')], (seq,list(out),remaining,flag,selected)
                        count += 1
        assert {0x2fbae0,0x2fbb08,0x4445d4,0x44460c,0x444610} <= retail.covered
        clock=Clock(elf.read_bytes()); sampler=Clock(elf.read_bytes()); timer_count=0
        lib.expiry.argtypes=[C.c_int64]*3
        for start in (0,262100,262200,999999900):
            for duration in (-1,0,262144,16666666,1000000000):
                for delta in (0,max(duration-100,0),max(duration,0),max(duration+100,0),max(duration+262144,0)):
                    effective_start=clock.start(start,duration)
                    expected=clock.expired(start+delta)
                    effective_now=sampler.start(start+delta,0)
                    assert lib.expiry(effective_start,duration,effective_now)==expected,(start,duration,delta)
                    timer_count+=1
    print(f'BIND retail: {count} enum/control/timer/channel states match original instructions')
    print(f'BIND retail: {timer_count} strict quantized timer boundaries match original instructions')


if __name__ == '__main__':
    main()
