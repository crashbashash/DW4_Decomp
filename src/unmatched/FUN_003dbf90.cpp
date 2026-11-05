#include "dw4/reflected.h"
/* _statDisp's class is not reflected; its first-level links are private views. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
typedef struct M { void *f0; void *f4; } M;
typedef struct L { char p[16]; M *n16; } L;
typedef struct K { char p[16]; L *n16; } K;
extern int DAT_00516d30[4], DAT_00516d70[4], DAT_00516d80[4], DAT_00516d90[4], DAT_00516da0[4], DAT_00516db0[4], DAT_00516dc8[4];
int FUN_003d9e70(void *, int);
int FUN_003da7c0(void *);
int beNDMWLoadIntf2ComMdlCtrl__Close(int, int, void *, void *, int);
int beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(int);
int TextOrder_ClearFont(int, void *, int, int);
unsigned char FUN_003dbf90(beNDMWLoadIntf2DataSelIntf *c, int sel) {
    int a = c->_comMdlCtrl;
    int b = c->_textOrder;
    K *n = (K *)c->_statDisp;
    unsigned char r = 0;
    int v;
    switch (sel) {
    default: v = c->_st0; break;
    case 1: v = c->_st1; break;
    case 2: v = c->_st2; break;
    case 3: v = c->_st3; break;
    }
    switch (v) {
    case 0:
        if (c->_isSaveArea == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Close(a, c->_plNo, DAT_00516d70, DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(a, c->_plNo, DAT_00516d80, DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(a, c->_plNo, DAT_00516d90, DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(a, c->_plNo, DAT_00516da0, DAT_00516d30, 1);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 0);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 1);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 2);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 3);
            c->_isSaveArea = 0;
        }
        if (c->_isUpStatWin == 1) {
            FUN_003d9e70(n->n16->n16->f0, 0);
        }
        if (c->_isDownStatWin == 1) {
            FUN_003d9e70(n->n16->n16->f4, 0);
        }
        if (c->_isSelCur == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Close(a, c->_plNo, DAT_00516db0, DAT_00516d30, 1);
        }
        v++;
        break;
    case 1:
        if (c->_isUpStatWin == 1) {
            if ((FUN_003da7c0(n->n16->n16->f0) & 0xFF) != 1) break;
            c->_isUpStatWin = 0;
        }
        if (c->_isDownStatWin == 1) {
            if ((FUN_003da7c0(n->n16->n16->f4) & 0xFF) != 1) break;
            c->_isDownStatWin = 0;
        }
        if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(a) & 0xFF) == 1) {
            r = 1;
            v++;
        }
        break;
    case 2:
        r = 1;
        break;
    }
    switch (sel) {
    default: c->_st0 = v; c->_st3 = 0; c->_st2 = 0; c->_st1 = 0; break;
    case 1: c->_st1 = v; c->_st3 = 0; c->_st2 = 0; break;
    case 2: c->_st2 = v; c->_st3 = 0; break;
    case 3: c->_st3 = v; break;
    }
    return r;
}
} /* extern "C" */
