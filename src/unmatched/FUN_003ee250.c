#include "dw4/reflected.h"

#define PLW(list, off) (*(beNDMWLoadSavePlWork **)((char *)((beNDMWLoadSavePlWorkList *)(list))->_data + (off)))

void FUN_003ee250(beNDMWLoadCtrl2CommonIntf *a, int arg1, int arg2) {
    int temp_a4;
    int var_a7;
    int var_a6;
    int *cnt;
    beNDMWLoadSavePlWork *temp_v1;
    beNDMWLoadSavePlWork *temp_v1_2;
    beNDMWLoadSavePlWork *temp_v1_3;

    var_a7 = 0;
    var_a6 = 0;
    do {
        temp_v1 = PLW(a->_flagWork, var_a6);
        temp_v1->_sysStat0 = 1;
        temp_v1->_sysStat3 = 0;
        temp_v1->_sysStat2 = 0;
        temp_v1->_sysStat1 = 0;
        PLW(a->_flagWork, var_a6)->_isCtrl = 0;
        temp_v1_2 = PLW(a->_flagWork, var_a6);
        cnt = &temp_v1_2->_sysCount0;
        if (*cnt <= 0) {
            *cnt = 0xA;
        }
        var_a7 += 1;
        var_a6 += 4;
    } while (var_a7 < 4);
    temp_a4 = arg1 * 4;
    temp_v1_3 = PLW(a->_flagWork, temp_a4);
    temp_v1_3->_sysStat0 = arg2;
    temp_v1_3->_sysStat3 = 0;
    temp_v1_3->_sysStat2 = 0;
    temp_v1_3->_sysStat1 = 0;
    PLW(a->_flagWork, temp_a4)->_isCtrl = 1;
    PLW(a->_flagWork, temp_a4)->_sysCount0 = 0;
    a->_utilUsePlNo = arg1;
}
