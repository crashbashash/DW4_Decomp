#include "dw4/reflected.h"
typedef struct P { char p0[28]; float x, y, z; } P;
/* Receiver: the data-selection interface object the shared load/save helpers take (beNDMWLoadIntf2DataSelIntf); _comMdlCtrl is the target whose vec3 at +28 is published. */
extern "C" {
int beNDMWLoadIntf2ComMdlCtrl__StartAt(...);
int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(...);
int FUN_003ecad0(...);
extern int DAT_00516db0[4];
extern int DAT_00516e70[4];
extern int DAT_00516e80[4];
extern int DAT_00516e90[4];
extern int DAT_00516ea0[4];
bool FUN_003dd160(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
}
bool FUN_003dd160(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
    float v0[3], v1[3], v2[3], v3[3];
    int s2;
    bool s1;
    int s0;
    P *a0;
    a0 = (P *)arg0->_comMdlCtrl;
    s2 = arg0->_mesWin;
    s1 = 0;
    switch (arg1) {
    default: s0 = arg0->_st0; break;
    case 1: s0 = arg0->_st1; break;
    case 2: s0 = arg0->_st2; break;
    case 3: s0 = arg0->_st3; break;
    }
    switch (s0) {
    case 0:
        if (arg0->_isSelCur == 0) {
            switch (arg0->_svDataSelPoint) {
            case 0: v0[0] = a0->x; v0[1] = a0->y; v0[2] = a0->z; beNDMWLoadIntf2ComMdlCtrl__StartAt(a0, arg0->_plNo, DAT_00516db0, DAT_00516e70, v0, 1); break;
            case 1: v1[0] = a0->x; v1[1] = a0->y; v1[2] = a0->z; beNDMWLoadIntf2ComMdlCtrl__StartAt(a0, arg0->_plNo, DAT_00516db0, DAT_00516e80, v1, 1); break;
            case 2: v2[0] = a0->x; v2[1] = a0->y; v2[2] = a0->z; beNDMWLoadIntf2ComMdlCtrl__StartAt(a0, arg0->_plNo, DAT_00516db0, DAT_00516e90, v2, 1); break;
            case 3: v3[0] = a0->x; v3[1] = a0->y; v3[2] = a0->z; beNDMWLoadIntf2ComMdlCtrl__StartAt(a0, arg0->_plNo, DAT_00516db0, DAT_00516ea0, v3, 1); break;
            }
            arg0->_isSelCur = 1;
        }
        s0 += 1;
        break;
    case 1:
        if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(a0, 2) & 0xFF) == 1) {
            s0 += 1;
            if (arg0->_kind == 0) FUN_003ecad0(s2, (arg0->_plNo << 0x10) | 0x513);
            else FUN_003ecad0(s2, (arg0->_plNo << 0x10) | 0x503);
        }
        break;
    case 2:
        s1 = 1;
        break;
    }
    switch (arg1) {
    default:
        arg0->_st0 = s0; arg0->_st3 = 0; arg0->_st2 = 0; arg0->_st1 = 0;
        break;
    case 1:
        arg0->_st1 = s0; arg0->_st3 = 0; arg0->_st2 = 0;
        break;
    case 2:
        arg0->_st2 = s0; arg0->_st3 = 0;
        break;
    case 3:
        arg0->_st3 = s0;
        break;
    }
    return s1;
}
