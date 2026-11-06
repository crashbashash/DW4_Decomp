#include "dw4/reflected.h"
extern "C" {
int FUN_003d9ec0(...);
int FUN_003da5f0(...);
int beNDMWLoadIntf2ComMdlCtrl__StartAt(...);
int beNDMWLoadIntf2ComMdlCtrl__Play(...);
int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(...);
int beNDMWLoadIntf2ComMdlCtrl__Close(...);
int beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(...);
int igStrCmp(...);
typedef struct Ent { int name; int val; int val2; } Ent;
extern Ent DAT_004cec70[16];
extern int DAT_00516ca8[4];
extern int DAT_00516cc0[4];
extern int DAT_00516cd0[4];
extern int DAT_00516cd8[4];
extern int DAT_00516ce8[4];
extern int DAT_00516cf8[4];
extern int DAT_00516d08[4];
extern int DAT_00516d10[4];
extern int DAT_00516d20[4];
extern int DAT_00516d30[4];
extern int DAT_00516d40[4];
extern int DAT_00516d50[4];
extern int DAT_00516d60[4];
}
struct Item { char p0[40]; unsigned char b40; char p1[7]; int f48; };
struct IL { char p[16]; Item **arr; };
struct Cell { char p[12]; IL *f12; };
struct Row { char p[32]; Cell *f32; };
struct RL { char p[16]; Row **arr; };
struct Bk { char p[36]; IL *f36; RL *f40; };
struct Ob { char p[28]; float v28; float v32; float v36; };
struct V3 { float x; float y; float z; };
extern "C" unsigned char FUN_003da7c0(beNDMWLoadIntf2DegiState *arg0) {

    if (arg0->_isEnd == 1) {
        return 1;
    }
    Bk *a1 = (Bk *)arg0->_commonIntf;
    switch (arg0->_st0) {
    case 0:
        break;
    case 1:
        switch (arg0->_st1) {
        case 0: {
            Item *s1;
            if (arg0->_kind == 0) {
                s1 = a1->f40->arr[arg0->_plNo]->f32->f12->arr[arg0->_dataNo];
            } else {
                s1 = a1->f36->arr[arg0->_plNo];
            }
            if (s1->b40 == 1) {
                arg0->_isUseData = 1;
            } else {
                arg0->_isUseData = 0;
            }
            if (arg0->_isUseData == 1) {
                int s0 = 0;
                int s4 = 0;
                Ent *s3 = DAT_004cec70;
            loop_22:
                if (igStrCmp(s3->name, s1->f48) == 0) {
                    s0 = s4;
                } else {
                    s4 += 1;
                    s3 += 1;
                    if (s4 < 16) {
                        goto loop_22;
                    }
                }
                if (arg0->_dispPos == 0) {
                    V3 vb; V3 va;
                    Ob *o = (Ob *)arg0->_comMdlCtrl;
                    vb.x = o->v28; vb.y = o->v32; vb.z = o->v36;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516ca8, DAT_004cec70[s0].val, &vb, 1);
                    o = (Ob *)arg0->_comMdlCtrl;
                    va.x = o->v28; va.y = o->v32; va.z = o->v36;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516cc0, DAT_00516cd0, &va, 1);
                } else {
                    V3 vc;
                    Ob *o = (Ob *)arg0->_comMdlCtrl;
                    vc.x = o->v28; vc.y = o->v32; vc.z = o->v36;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516cd8, DAT_004cec70[s0].val, &vc, 1);
                }
            } else if (arg0->_dispPos == 0) {
                V3 vd; V3 ve;
                Ob *o = (Ob *)arg0->_comMdlCtrl;
                vd.x = o->v28; vd.y = o->v32; vd.z = o->v36;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516ca8, DAT_00516ce8, &vd, 1);
                o = (Ob *)arg0->_comMdlCtrl;
                ve.x = o->v28; ve.y = o->v32; ve.z = o->v36;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516cc0, DAT_00516cf8, &ve, 1);
            } else {
                V3 vf;
                Ob *o = (Ob *)arg0->_comMdlCtrl;
                vf.x = o->v28; vf.y = o->v32; vf.z = o->v36;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516cd8, DAT_00516ce8, &vf, 1);
            }
            arg0->_st1 = arg0->_st1 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            break;
        }
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(arg0->_comMdlCtrl, a1) & 0xFF) == 1) {
                FUN_003d9ec0(arg0);
                arg0->_isEnd = 1;
                arg0->_st0 = 0;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st1 = 0;
            }
            break;
        }
        break;
    case 3: {
        Item *s1;
        if (arg0->_kind == 0) {
            s1 = a1->f40->arr[arg0->_plNo]->f32->f12->arr[arg0->_dataNo];
        } else {
            s1 = a1->f36->arr[arg0->_plNo];
        }
        if (s1->b40 == 1) {
            arg0->_isUseData = 1;
        } else {
            arg0->_isUseData = 0;
        }
        if (arg0->_isUseData == 1) {
            int s0 = 0;
            int s4 = 0;
            Ent *s3 = DAT_004cec70;
        loop_46:
            if (igStrCmp(s3->name, s1->f48) == 0) {
                s0 = s4;
            } else {
                s4 += 1;
                s3 += 1;
                if (s4 < 16) {
                    goto loop_46;
                }
            }
            if (arg0->_dispPos == 0) {
                beNDMWLoadIntf2ComMdlCtrl__Play(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516ca8, DAT_004cec70[s0].val2, 0);
                beNDMWLoadIntf2ComMdlCtrl__Play(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516cc0, DAT_00516d08, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516cd8, DAT_004cec70[s0].val2, 0);
            }
        } else if (arg0->_dispPos == 0) {
            beNDMWLoadIntf2ComMdlCtrl__Play(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516ca8, DAT_00516d10, 0);
            beNDMWLoadIntf2ComMdlCtrl__Play(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516cc0, DAT_00516d20, 0);
        } else {
            beNDMWLoadIntf2ComMdlCtrl__Play(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516cd8, DAT_00516d10, 0);
        }
        FUN_003da5f0(arg0);
        FUN_003d9ec0(arg0);
        arg0->_isEnd = 1;
        arg0->_st0 = 0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    }
    case 2: {
        Item *s1;
        if (arg0->_kind == 0) {
            s1 = a1->f40->arr[arg0->_plNo]->f32->f12->arr[arg0->_dataNo];
        } else {
            s1 = a1->f36->arr[arg0->_plNo];
        }
        if (s1->b40 == 1) {
            arg0->_isUseData = 1;
        } else {
            arg0->_isUseData = 0;
        }
        switch (arg0->_st1) {
        case 0:
            if (arg0->_dispPos == 0) {
                beNDMWLoadIntf2ComMdlCtrl__Close(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516ca8, DAT_00516d30, 1);
                if (arg0->_isUseData == 1) {
                    switch (arg0->_closeKind) {
                    case 0:
                        beNDMWLoadIntf2ComMdlCtrl__Close(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516cc0, DAT_00516d30, 1);
                        break;
                    case 1:
                        beNDMWLoadIntf2ComMdlCtrl__Close(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516cc0, DAT_00516d40, 1);
                        break;
                    case 2:
                        beNDMWLoadIntf2ComMdlCtrl__Close(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516cc0, DAT_00516d50, 1);
                        break;
                    }
                } else {
                    beNDMWLoadIntf2ComMdlCtrl__Close(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516cc0, DAT_00516d60, 1);
                }
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Close(arg0->_comMdlCtrl, arg0->_plNo, DAT_00516cd8, DAT_00516d30, 1);
            }
            FUN_003da5f0(arg0);
            arg0->_st1 = arg0->_st1 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            break;
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(arg0->_comMdlCtrl) & 0xFF) == 1) {
                arg0->_isEnd = 1;
                arg0->_st0 = 0;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st1 = 0;
            }
            break;
        }
        break;
    }
    }
    return arg0->_isEnd;
}
