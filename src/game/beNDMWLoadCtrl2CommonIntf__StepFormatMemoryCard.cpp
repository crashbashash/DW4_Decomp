#include "dw4/reflected.h"
/* _flagWork is the per-player beNDMWLoadSavePlWorkList; _mcUtilCtrl -> _slot is the memory-card slot list. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
#define PLW(common, i) (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(common)->_flagWork)->_data)[i])
#define MCU(common) ((beNDMWMcUtilCtrl *)(common)->_mcUtilCtrl)
#define MCSLOT(common, i) (((beNDMWMcSlot **)((beNDMWMcSlotList *)MCU(common)->_slot)->_data)[i])
void FUN_003f1460(int, int, int);

int beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(beNDMWLoadCtrl2CommonIntf *o, int idx, int arg2, int arg3, int mode) {
    int r = 0;
    int v = 0;
    switch (mode) {
    case 0: v = PLW(o, idx)->_sysStat0; break;
    case 1: v = PLW(o, idx)->_sysStat1; break;
    case 2: v = PLW(o, idx)->_sysStat2; break;
    case 3: v = PLW(o, idx)->_sysStat3; break;
    }
    switch (v) {
    case 0:
        FUN_003f1460(o->_mcUtilCtrl, 2, arg3);
        v++;
        MCU(o)->_isFormatRun = 1;
        break;
    case 1: {
        beNDMWMcUtilCtrl *s = MCU(o);
        if (s->_isResult == 1) {
            switch (s->_result) { case 2: r = 1; break; default: r = 2; break; }
        }
        break;
    }
    }
    switch (mode) {
    case 0: {
        beNDMWLoadSavePlWork *it = PLW(o, idx);
        it->_sysStat0 = v;
        it->_sysStat3 = 0;
        it->_sysStat2 = 0;
        it->_sysStat1 = 0;
        break;
    }
    case 1: {
        beNDMWLoadSavePlWork *it = PLW(o, idx);
        it->_sysStat1 = v;
        it->_sysStat3 = 0;
        it->_sysStat2 = 0;
        break;
    }
    case 2: {
        beNDMWLoadSavePlWork *it = PLW(o, idx);
        it->_sysStat2 = v;
        it->_sysStat3 = 0;
        break;
    }
    case 3:
        PLW(o, idx)->_sysStat3 = v;
        break;
    }
    return r;
}
} /* extern "C" */
