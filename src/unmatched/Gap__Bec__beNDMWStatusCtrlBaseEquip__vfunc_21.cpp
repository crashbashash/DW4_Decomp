/* Per-frame state machine of the base equip status window.
 * Matching constructs:
 *  - 'default: return;' first in the outer _st0 switch: with it the scheduler stops hoisting successors into delay slots for the
 *    whole function; two-way splits on _st1 are a switch (case 0 / default), not if/else.
 *  - class VC with 22 dummy virtuals, then v96..v164 for the virtual calls through the +96..+164 slots.
 *  - four holder classes (RefA: the case-12 window; RefB: the select windows; RefC: the decide list;
 *    StringRef: the player-name string), each built at its use site so the cleanup range
 *    starts there; the string holder lives in an inline helper (H::SendName) so its slot is allocated after the holders, and
 *    `#pragma inline_depth(8)` keeps that helper's destructor inline (otherwise a jal __dt__ appears).
 *  - found-window search: for loop over the list with a volatile re-read of _subWindow in the body and a cast-self-assign then arm.
 *  - window header stores go through a float pointer for +88..+96 (the base pointer is reloaded once after the first store).
 *  - list-owner assignment (hl into hw+108) uses int locals declared in the block; the powerSocket slot swap is a switch on
 *    _retCode (case 0/1/2) with locals declared a,b,ps,pos,off and 'b' read before 'a'.
 *  - list byte pushes/sets are macros so the global byte is read at the store, after the bounds test. */
#include "dw4/reflected.h"
#pragma inline_depth(8)
extern "C" {
int FUN_002cb0d0(...);
int igObject_IsKindOf(...);
int FUN_003a9310(...);
int FUN_003b4f50(...);
int FUN_003b51b0(...);
int FUN_00411180(...);
int FUN_004115c0(...);
int FUN_00411750(...);
int List_Resize(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beMessenger_SelectReceivers(...);
int beMessenger_SendNamed(...);
int beNDMWWindow_BindContext(...);
int beNDMWWindow_ClearQueuedText(...);
int beNDMWWindow_PlayQueuedModelClose(...);
int beNDMWWindow_PollCloseComplete(...);
int beNDMWWindow_RequestChildrenClose(...);
int beNDMWWindow_RunMessageScript(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
int igProperty_GetRecordFolder(...);
extern int DAT_004cf670[4];
extern int DAT_005199e0[4];
extern int DAT_005199e8[4];
extern int DAT_00519b00[4];
extern int DAT_00519b08[4];
extern int DAT_00519b50[4];
extern int DAT_00519b90[4];
extern int DAT_00519ba0[4];
extern int DAT_00519ba8[4];
extern int DAT_00519bb8[4];
extern int DAT_00519bc8[4];
extern int DAT_00519bd8[4];
extern int DAT_00519be0[4];
extern int DAT_00519bf0[4];
extern int DAT_00519c00[4];
extern int DAT_00519c10[4];
extern int DAT_00519c18[4];
extern int DAT_00519c28[4];
extern int DAT_00519c30[4];
extern int DAT_00519c40[4];
extern int DAT_00519c50[4];
extern int DAT_00519c60[4];
extern int DAT_00519c70[4];
extern int DAT_00519c80[4];
extern int DAT_00587110[4];
extern int DAT_0058af98[4];
extern unsigned char GPR_005549f8;
extern unsigned char GPR_005549fc;
extern unsigned char GPR_00554a00;
extern unsigned char GPR_00554a04;
extern unsigned char GPR_00554a08;
extern unsigned char GPR_00554c14;
}
struct VC { virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21();
 virtual void v96(); virtual void v100(int); virtual void v104(); virtual void v108(); virtual void v112(); virtual void v116(); virtual void v120(); virtual void v124(); virtual int v128(int); virtual void v132(); virtual void v136(int); virtual void v140(); virtual void v144(); virtual void v148(); virtual void v152(); virtual void v156(); virtual void v160(); virtual void v164(int); };
typedef igObject Obj;
struct RefA { Obj *p; RefA(void *x) { p = (Obj *)x; } ~RefA() { Obj *o; if ((o = p) != 0) { --o->_refCount; if (((unsigned long long)(long long)(int)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o); } } };
struct RefB { Obj *p; RefB(void *x) { p = (Obj *)x; } ~RefB() { Obj *o; if ((o = p) != 0) { --o->_refCount; if (((unsigned long long)(long long)(int)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o); } } };
struct RefC { Obj *p; RefC(void *x) { p = (Obj *)x; } ~RefC() { Obj *o; if ((o = p) != 0) { --o->_refCount; if (((unsigned long long)(long long)(int)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o); } } };
/* Interned-string reference (count at p[-1], header at p[-2]). */
struct StringRef { void *p; StringRef(void *x) { p = x; } ~StringRef() { if (p != 0) { int *hd = (int *)((char *)p - 8); int c = *(int *)((char *)p - 4) - 1; *(int *)((char *)p - 4) = c; if (c == 0) StringChunk_ReleaseHeader(*hd, hd); } } };
extern "C" StringRef StringList_CopyRetained(int, int);
#define SEL(d) beMessenger_SelectGroup(p->_messenger, d)
#define APS(d) beMessenger_AppendString(p->_messenger, d)
#define API(d) beMessenger_AppendInt(p->_messenger, d)
#define DSP(d) beMessenger_DispatchSelected(p->_messenger, d)
#define SUBCOUNT (((igObjectList *)p->_subWindow)->_count)
#define PUSHB(LP, B) { int n_; igUnsignedCharList *l_ = (igUnsignedCharList *)(LP); n_ = l_->_count; if (n_ < l_->_capacity) { l_->_count = n_ + 1; } else { List_Resize(l_, n_ + 1, 1); } ((unsigned char *)l_->_data)[n_] = (B); }
#define SETB(LP, IDX, B) { igUnsignedCharList *l_ = (igUnsignedCharList *)(LP); if (l_->_count != 0 && (IDX) >= 0 && (IDX) < l_->_count) { ((unsigned char *)l_->_data)[(IDX)] = (B); } }
#define SWV(h) ((igObjectList *)*(volatile int *)&(h))
#define FIND(W) { int i_; (W) = 0; for (i_ = 0; i_ < ((igObjectList *)p->_subWindow)->_count; i_++) { (W) = ((int *)SWV(p->_subWindow)->_data)[i_]; if ((W) && igObject_IsKindOf((W), DAT_0058af98[0])) { (W) = (int)(int *)(W); } else { (W) = 0; } if ((W)) break; } }
#define SETSLOT(L, IDX, V_) { Obj *v_ = (V_); Obj *old_; if (v_ != 0) { v_->_refCount = v_->_refCount + 1; } old_ = ((Obj **)(L)->_data)[(IDX)]; if (old_ != 0) { --old_->_refCount; if (((unsigned long long)(long long)(int)old_->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old_); } if ((L)->_count != 0 && (IDX) >= 0 && (IDX) < (L)->_count) { ((Obj **)(L)->_data)[(IDX)] = v_; } }
#define V(p) ((VC *)(p))
#define ADV() { p->_st0 = p->_st0 + 1; p->_st3 = 0; p->_st2 = 0; p->_st1 = 0; }
#define SETST(a, b) { p->_st0 = a; p->_st3 = 0; p->_st2 = 0; p->_st1 = 0; p->_st1 = b; p->_st3 = 0; p->_st2 = 0; }
#define NEXT2() { p->_st2 = p->_st2 + 1; p->_st3 = 0; }
#define REFRESH() { SEL(DAT_00519c10); API(p->_playerNo); DSP(DAT_00519c18); }
#define PUBLISH() { beMessenger_SelectReceivers(p->_messenger, DAT_00519ba0, 0, 0); API(p->_playerNo); DSP(DAT_00519c40); SEL(DAT_00519c10); API(p->_playerNo); DSP(DAT_00519c50); }

struct H {
static inline int PickAlloc(beNDMWStatusCtrlBaseEquip *q) {
    int a = igObject_GetAllocator(q);
    int al;
    if (GPR_00554c14 != 0) { al = a; } else { al = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
    return al;
}
static inline void SendName(beNDMWStatusCtrlBaseEquip *q) {
    StringRef sv(StringList_CopyRetained(*(int *)(FUN_003a9310(q->_playerList, DAT_00519c60) + 12), 0));
    beMessenger_SendNamed(q->_messenger, DAT_00519c70, sv.p, q->_playerNo, DAT_00519c80);
}
static inline void AssignRef(int *slot, Obj *v) {
    Obj *old;
    if (v != 0) { v->_refCount = v->_refCount + 1; }
    old = (Obj *)*slot;
    if (old != 0) { --old->_refCount; if (((unsigned long long)(long long)(int)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old); }
    *slot = (int)v;
}
};

extern "C" void Gap__Bec__beNDMWStatusCtrlBaseEquip__vfunc_21(beNDMWStatusCtrlBaseEquip *p)
{
    switch (p->_st0) {
    default: return;
    case 0: {
        Obj *o;
        SEL(DAT_00519ba0); API(p->_playerNo); DSP(DAT_00519ba8);
        o = (Obj *)beMessenger_GetObject(p->_messenger, 0);
        H::AssignRef(&p->_playerList, o);
        H::AssignRef(&p->_powerSocket, (Obj *)*(int *)(igProperty_GetRecordFolder(p->_playerList, DAT_00519bb8) + 12));
        H::AssignRef(&p->_mainSlot, (Obj *)*(int *)(igProperty_GetRecordFolder(p->_playerList, DAT_00519bc8) + 12));
        H::AssignRef(&p->_subSlot, (Obj *)*(int *)(igProperty_GetRecordFolder(p->_playerList, DAT_00519bd8) + 12));
        H::AssignRef(&p->_wpuPocket, (Obj *)*(int *)(igProperty_GetRecordFolder(p->_playerList, DAT_00519be0) + 12));
        H::AssignRef(&p->_apuPocket, (Obj *)*(int *)(igProperty_GetRecordFolder(p->_playerList, DAT_00519bf0) + 12));
        H::AssignRef(&p->_deviceFolder, (Obj *)*(int *)(igProperty_GetRecordFolder(p->_playerList, DAT_00519c00) + 12));
        switch (p->_st1) { case 0: V(p)->v100(1); FUN_00411750(p); break; default: FUN_004115c0(p, -1); break; }
        {
            int al = H::PickAlloc(p);
            RefB h((Obj *)FUN_003b51b0(al));
            beNDMWWindow_BindContext(h.p, p, p->_insight, p->_playerNo, 0);
            ObjectList_AppendRetained(p->_subWindow, h.p);
            ((beNDMWStatusSelectE1 *)h.p)->_selectMax = p->_kindListMax;
            { float *q = (float *)((beNDMWStatusSelectE1 *)h.p)->_offsetPos; q[0] = -83.0f; q[1] = 148.0f; q[2] = 0.0f; }
            ((beNDMWStatusSelectE1 *)h.p)->_startPoint = p->_kindListPos;
        }
        p->_nowProcKazu = SUBCOUNT;
        ADV();
        p->_st1 = 0; p->_st3 = 0; p->_st2 = 0;
        return;
    }
    case 1:
        switch (p->_st1) {
        case 0:
            switch (p->_st2) {
            case 0:
                V(p)->v104();
                NEXT2();
            case 1:
                V(p)->v112();
                NEXT2();
                p->_st3 = p->_retCode;
            case 2:
                if (SUBCOUNT == p->_nowProcKazu) {
                    if (p->_retCode != -1 && p->_st3 != p->_retCode) { p->_st2 = 1; p->_st3 = 0; return; }
                } else {
                    if (p->_retCode == -1) { ADV(); return; }
                    V(p)->v108();
                    p->_kindListPos = p->_retCode;
                    FUN_004115c0(p, p->_retCode);
                    return;
                }
                break;
            }
            break;
        case 1:
            switch (p->_st2) {
            case 0:
                V(p)->v116();
                p->_nowProcKazu = SUBCOUNT;
                NEXT2();
            case 1:
                if (SUBCOUNT == p->_nowProcKazu) {
                    if (p->_retCode != -1 && p->_st3 != p->_retCode) {
                        if (p->_retCode == 2) { V(p)->v136(-1); } else { REFRESH(); }
                        p->_st3 = p->_retCode;
                        return;
                    }
                } else {
                    int i;
                    REFRESH();
                    for (i = 0; i < 3; i++) { SEL(DAT_00519c28); APS(DAT_00519b50); APS(DAT_004cf670[i]); DSP(DAT_00519c30); }
                    if (p->_retCode == -1) { SETST(0, 1); return; }
                    V(p)->v120();
                    return;
                }
                break;
            }
            break;
        case 2:
            switch (p->_st2) {
            case 0:
                V(p)->v140();
                p->_nowProcKazu = SUBCOUNT;
                NEXT2();
                return;
            case 1:
                V(p)->v144();
                NEXT2();
                p->_st3 = p->_retCode;
            case 2:
                if (SUBCOUNT == p->_nowProcKazu) {
                    if (p->_retCode != -1 && p->_retCode != p->_st3) { p->_st2 = 1; p->_st3 = 0; return; }
                } else {
                    if (p->_retCode != -1) { p->_pocketPos = p->_retCode; NEXT2(); return; }
                    p->_pocketPos = 0;
                    SETST(0, 1);
                    return;
                }
                break;
            case 3:
                V(p)->v148();
                p->_nowProcKazu = SUBCOUNT;
                NEXT2();
                return;
            case 4:
                beNDMWWindow_RunMessageScript(p, DAT_00519b90, 0x7F);
                NEXT2();
                p->_st3 = 0x3E7;
                return;
            case 5:
                if (SUBCOUNT == p->_nowProcKazu) {
                    if (p->_retCode != -1 && p->_st3 != p->_retCode) {
                        if (p->_retCode == 1) { V(p)->v164(-1); } else { REFRESH(); }
                        p->_st3 = p->_retCode;
                        return;
                    }
                } else {
                    REFRESH();
                    SEL(DAT_00519c28); APS(DAT_00519b50); APS(DAT_005199e8); DSP(DAT_00519c30);
                    switch (p->_retCode) {
                    case 0:
                        NEXT2();
                        V(p)->v100(0);
                        FUN_004115c0(p, -1);
                        return;
                    case 1:
                        p->_retCode = -1;
                        V(p)->v156();
                        p->_retCode = p->_pocketPos;
                        V(p)->v104();
                        PUBLISH();
                    default:
                        p->_st1 = 2; p->_st3 = 0; p->_st2 = 0;
                        return;
                    }
                }
                break;
            case 6:
                V(p)->v152();
                p->_nowProcKazu = SUBCOUNT;
                NEXT2();
                p->_st3 = 0x3E7;
            case 7:
                if (SUBCOUNT == p->_nowProcKazu) { V(p)->v164(0); return; }
                REFRESH();
                if (p->_retCode != -1) { V(p)->v156(); PUBLISH(); }
                V(p)->v100(1);
                FUN_00411750(p);
                NEXT2();
                return;
            case 8:
                V(p)->v104();
                FUN_004115c0(p, p->_kindListPos);
                p->_st1 = 2; p->_st3 = 0; p->_st2 = 0;
                return;
            }
            break;
        case 3:
            switch (p->_st2) {
            case 0: {
                int al = H::PickAlloc(p);
                int i;
                RefB hw((Obj *)FUN_003b51b0(al));
                beNDMWWindow_BindContext(hw.p, p, p->_insight, p->_playerNo, 0);
                ObjectList_AppendRetained(p->_subWindow, hw.p);
                ((beNDMWStatusSelectE1 *)hw.p)->_selectMax = p->_kindListMax;
                { float *q = (float *)((beNDMWStatusSelectE1 *)hw.p)->_offsetPos; q[0] = -83.0f; q[1] = 148.0f; q[2] = 0.0f; }
                ((beNDMWStatusSelectE1 *)hw.p)->_startPoint = p->_kindListPos;
                al = H::PickAlloc(p);
                RefC hl((Obj *)FUN_002cb0d0(al));
                for (i = 0; i < p->_kindListMax; i++) {
                    if (i == p->_kindListPos) { PUSHB(hl.p, GPR_005549f8); } else { PUSHB(hl.p, GPR_005549fc); }
                }
                if (p->_kindListPos == 0) {
                    if (((int *)((igObjectList *)p->_powerSocket)->_data)[1] == 0) { SETB(hl.p, 1, GPR_00554a00); }
                    if (((int *)((igObjectList *)p->_powerSocket)->_data)[2] == 0) { SETB(hl.p, 2, GPR_00554a04); }
                } else if (((int *)((igObjectList *)p->_powerSocket)->_data)[p->_kindListPos] == 0) {
                    SETB(hl.p, 0, GPR_00554a08);
                }
                { int l_ = (int)hl.p; beNDMWStatusSelectE1 *w_ = (beNDMWStatusSelectE1 *)hw.p; Obj *old_;
                  if (l_ != 0) { ((Obj *)l_)->_refCount = ((Obj *)l_)->_refCount + 1; }
                  old_ = (Obj *)w_->_decideList;
                  if (old_ != 0) { --old_->_refCount; if (((unsigned long long)(long long)(int)old_->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old_); }
                  w_->_decideList = l_; }
            }
                p->_nowProcKazu = SUBCOUNT;
                NEXT2();
                return;
            case 1:
                V(p)->v104();
                NEXT2();
                p->_st3 = p->_retCode;
            case 2:
                if (SUBCOUNT == p->_nowProcKazu) {
                    if (p->_retCode != -1 && p->_st3 != p->_retCode) {
                        FUN_00411180(p);
                        p->_st2 = 1; p->_st3 = 0;
                        return;
                    }
                } else {
                    SEL(DAT_00519c28); APS(DAT_00519b50); APS(DAT_004cf670[0]); APS(DAT_00519b00); DSP(DAT_00519b08);
                    REFRESH();
                    switch (p->_retCode) { case 0: case 1: case 2: {
                        Obj * b_;
                        Obj * a_;
                        igObjectList * ps_;
                        int pos_;
                        ps_ = (igObjectList *)p->_powerSocket; pos_ = p->_kindListPos;
                        b_ = ((Obj **)ps_->_data)[pos_];
                        a_ = ((Obj **)ps_->_data)[p->_retCode];
                        SETSLOT(ps_, pos_, a_);
                        { int r_ = p->_retCode; igObjectList *ps2_ = (igObjectList *)p->_powerSocket; SETSLOT(ps2_, r_, b_); }
                        if (p->_retCode == 0 || p->_kindListPos == 0) { V(p)->v160(); }
                        PUBLISH();
                        if ((p->_retCode == 0 || p->_kindListPos == 0) && ((beNDMWWindow *)p->_mother)->_entCode == 0) {
                            H::SendName(p);
                        }
                        V(p)->v96();
                    } break; default: break; }
                    SEL(DAT_00519c10); API(p->_playerNo); DSP(DAT_00519c50);
                    SETST(0, 1);
                    return;
                }
                break;
            }
            break;
        case 4:
            switch (p->_st2) {
            case 0:
                V(p)->v100(0);
                FUN_004115c0(p, -1);
                V(p)->v124();
                p->_nowProcKazu = SUBCOUNT;
                NEXT2();
                p->_st3 = 0x3E7;
            case 1: {
                int fw;
                FIND(fw);
                beNDMWStatusCtrlD0 *w = (beNDMWStatusCtrlD0 *)fw;
                if (p->_retCode == -1) {
                    REFRESH();
                    w->_st0 = 2; w->_st3 = 0; w->_st2 = 0; w->_st1 = 0;
                    p->_st2 = 10; p->_st3 = 0;
                    return;
                }
                if (w->_st0 == 1 && w->_st1 == 2) {
                    REFRESH();
                    if (V(p)->v128(p->_retCode) != 0) {
                        p->_st2 = 9; p->_st3 = 0;
                        w->_st0 = 2; w->_st3 = 0; w->_st2 = 0; w->_st1 = 0;
                        return;
                    }
                    p->_st2 = 12; p->_st3 = 0;
                    return;
                }
                V(p)->v136(0);
                return;
            }
            case 9:
                V(p)->v132();
                PUBLISH();
                NEXT2();
                return;
            case 10:
                if (SUBCOUNT != p->_nowProcKazu) {
                    V(p)->v100(1);
                    FUN_00411750(p);
                    NEXT2();
                    return;
                }
                break;
            case 11:
                V(p)->v104();
                SETST(0, 1);
                return;
            case 12: {
                int al = H::PickAlloc(p);
                RefA h((Obj *)FUN_003b4f50(al));
                beNDMWWindow_BindContext(h.p, p, p->_insight, p->_playerNo, 0);
                ObjectList_AppendRetained(p->_subWindow, h.p);
                beNDMWWindow_RunMessageScript(p, DAT_00519b90, 0x82);
            }
                p->_nowProcKazu = SUBCOUNT;
                NEXT2();
                p->_st3 = p->_retCode;
            case 13:
                if (SUBCOUNT != p->_nowProcKazu) {
                    int fw;
                    beNDMWStatusCtrlD0 *w;
                    SEL(DAT_00519c28); APS(DAT_00519b50); APS(DAT_005199e0); APS(DAT_00519b00); DSP(DAT_00519b08);
                    FIND(fw);
                    w = (beNDMWStatusCtrlD0 *)fw;
                    if (w != 0) {
                        p->_retCode = p->_st3;
                        p->_nowProcKazu = SUBCOUNT;
                        w->_st2 = 1; w->_st3 = 0;
                        p->_st2 = 1; p->_st3 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText(p);
        beNDMWWindow_RequestChildrenClose(p);
        ADV();
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) { p->_isRun = 0; }
        break;
    }
}
