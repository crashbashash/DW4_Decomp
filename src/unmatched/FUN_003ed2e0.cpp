#include "dw4/reflected.h"
/* _flagWork is the per-player beNDMWLoadSavePlWorkList; _mcUtilCtrl -> _slot is the memory-card slot list. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
#define PLW(common, i) (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(common)->_flagWork)->_data)[i])
#define MCU(common) ((beNDMWMcUtilCtrl *)(common)->_mcUtilCtrl)
#define MCSLOT(common, i) (((beNDMWMcSlot **)((beNDMWMcSlotList *)MCU(common)->_slot)->_data)[i])
int FUN_003a7a20(int, void *, unsigned long long);
int FUN_003a7e90(int, int *);
int FUN_003ecad0(int, int);
int FUN_003f1460(int, int, int);
extern int DAT_00517e38[4];
int FUN_003ed2e0(beNDMWLoadCtrl2CommonIntf *arg0, int arg1, int arg2, int arg3, int arg4) {
    int s1;
    int s0;
    int a1;
    beNDMWLoadSavePlWork *r;
    beNDMWMcUtilCtrl *m;
    s1 = 0;
    s0 = 0;
    switch (arg4) {
    case 0: s0 = PLW(arg0, arg1)->_sysStat0; break;
    case 1: s0 = PLW(arg0, arg1)->_sysStat1; break;
    case 2: s0 = PLW(arg0, arg1)->_sysStat2; break;
    case 3: s0 = PLW(arg0, arg1)->_sysStat3; break;
    }
    switch (s0) {
    case 0:
        a1 = -1;
        switch (arg0->_kindHard) {
        case 0: a1 = (arg1 << 16) | 0x1003; break;
        case 1: a1 = (arg1 << 16) | 0x2003; break;
        case 2: a1 = (arg1 << 16) | 0x3003; break;
        }
        FUN_003ecad0(arg2, a1);
        FUN_003f1460(arg0->_mcUtilCtrl, 6, arg3);
        s0 += 1;
        break;
    case 1:
        m = MCU(arg0);
        if (m->_isResult == 1) {
            switch (m->_result) {
            case 2: s0 += 1; break;
            default: s1 = 2; break;
            }
        }
        break;
    case 2:
        FUN_003f1460(arg0->_mcUtilCtrl, 0, arg3);
        FUN_003a7a20(arg0->_inforam, &DAT_00517e38[0], 0xB2D05E00ULL);
        s0 += 1;
        break;
    case 3:
        if (MCSLOT(arg0, arg3)->_isConnect == 1) {
            if ((FUN_003a7e90(arg0->_inforam, &DAT_00517e38[0]) & 0xFF) == 1) {
                s0 += 1;
                goto L4;
            }
            break;
        } else {
            s0 += 1;
        }
    case 4:
    L4:
        m = MCU(arg0);
        if (m->_isResult == 1) {
            switch (m->_result) {
            case 2: s1 = 1; break;
            default: s1 = 2; break;
            }
        }
        break;
    }
    switch (arg4) {
    case 0:
        r = PLW(arg0, arg1);
        r->_sysStat0 = s0; r->_sysStat3 = 0; r->_sysStat2 = 0; r->_sysStat1 = 0;
        break;
    case 1:
        r = PLW(arg0, arg1);
        r->_sysStat1 = s0; r->_sysStat3 = 0; r->_sysStat2 = 0;
        break;
    case 2:
        r = PLW(arg0, arg1);
        r->_sysStat2 = s0; r->_sysStat3 = 0;
        break;
    case 3:
        PLW(arg0, arg1)->_sysStat3 = s0;
        break;
    }
    return s1;
}
} /* extern "C" */
