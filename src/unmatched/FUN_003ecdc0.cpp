#include "dw4/reflected.h"
/* Warning: missing "jr $ra" in last block of FUN_003ecdc0 (.L003ED020). */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {

int FUN_003ecae0(int, int, int);
int FUN_003ecb00(int, int);
int beNDMWLoadIntf2MesWin__GetIsCtrl(int);
int FUN_003ecb80(int);

int FUN_003ecdc0(beNDMWLoadCtrl2CommonIntf *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    int temp_v0;
    int var_s1;
    int var_s0;
    beNDMWLoadSavePlWork *temp_v0_2;
    beNDMWLoadSavePlWork *temp_v0_3;
    beNDMWLoadSavePlWork *temp_v0_4;

    var_s1 = 0;
    var_s0 = 0;
    switch (arg6) {
    case 0:
        var_s0 = (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1])->_sysStat0;
        break;
    case 1:
        var_s0 = (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1])->_sysStat1;
        break;
    case 2:
        var_s0 = (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1])->_sysStat2;
        break;
    case 3:
        var_s0 = (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1])->_sysStat3;
        break;
    }
    switch (var_s0) {
    case 0:
        FUN_003ecb00(arg2, arg3);
        var_s0 += 1;
        break;
    case 1:
        if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(arg2) & 0xFF)) {
            var_s0 += 1;
        }
        break;
    case 2:
        FUN_003ecae0(arg2, arg4, arg5);
        var_s0 += 1;
        break;
    case 3:
        if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(arg2) & 0xFF)) {
            temp_v0 = FUN_003ecb80(arg2);
            switch (temp_v0) {
            case 0:
                var_s1 = 1;
                break;
            case 1:
                var_s1 = 2;
                break;
            }
        }
        break;
    }
    switch (arg6) {
    case 0:
        temp_v0_2 = (beNDMWLoadSavePlWork *)(((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1]);
        temp_v0_2->_sysStat0 = var_s0;
        temp_v0_2->_sysStat3 = 0;
        temp_v0_2->_sysStat2 = 0;
        temp_v0_2->_sysStat1 = 0;
        break;
    case 1:
        temp_v0_3 = (beNDMWLoadSavePlWork *)(((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1]);
        temp_v0_3->_sysStat1 = var_s0;
        temp_v0_3->_sysStat3 = 0;
        temp_v0_3->_sysStat2 = 0;
        break;
    case 2:
        temp_v0_4 = (beNDMWLoadSavePlWork *)(((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1]);
        temp_v0_4->_sysStat2 = var_s0;
        temp_v0_4->_sysStat3 = 0;
        break;
    case 3:
        (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1])->_sysStat3 = var_s0;
        break;
    }
    return var_s1;
}
} /* extern "C" */
