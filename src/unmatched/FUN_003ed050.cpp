#include "dw4/reflected.h"
/* _flagWork is the per-player beNDMWLoadSavePlWorkList; _mcUtilCtrl -> _slot is the memory-card slot list. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
#define PLW(common, i) (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(common)->_flagWork)->_data)[i])
#define MCU(common) ((beNDMWMcUtilCtrl *)(common)->_mcUtilCtrl)
int FUN_003f1460(int, int, int);
int FUN_003ed050(beNDMWLoadCtrl2CommonIntf *arg0, int arg1, int arg2, int arg3, int arg4) {
    int s1;
    int s0;
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
        FUN_003f1460(arg0->_mcUtilCtrl, 3, arg3);
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
        FUN_003f1460(arg0->_mcUtilCtrl, 1, arg3);
        s0 += 1;
        break;
    case 3:
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
    case 0: {
        beNDMWLoadSavePlWork *r = PLW(arg0, arg1);
        r->_sysStat0 = s0; r->_sysStat3 = 0; r->_sysStat2 = 0; r->_sysStat1 = 0;
        break; }
    case 1: {
        beNDMWLoadSavePlWork *r = PLW(arg0, arg1);
        r->_sysStat1 = s0; r->_sysStat3 = 0; r->_sysStat2 = 0;
        break; }
    case 2: {
        beNDMWLoadSavePlWork *r = PLW(arg0, arg1);
        r->_sysStat2 = s0; r->_sysStat3 = 0;
        break; }
    case 3:
        PLW(arg0, arg1)->_sysStat3 = s0;
        break;
    }
    return s1;
}
} /* extern "C" */
