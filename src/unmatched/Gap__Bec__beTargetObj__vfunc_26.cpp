#include "dw4/reflected.h"
extern "C" {
int List_Reserve(void *, int, int);
void Gap__Bec__beTargetObj__vfunc_26(beTargetObj *arg0);
}

void Gap__Bec__beTargetObj__vfunc_26(beTargetObj *arg0) {
    igVec3fList *temp_a0;
    igIntList *temp_a0_2;
    igVec3fList *temp_a0_3;

    ((igVec3fList *)arg0->_playerPosList)->_count = 0;
    temp_a0 = (igVec3fList *)arg0->_playerPosList;
    if (!(0 < temp_a0->_count)) {
        List_Reserve(temp_a0, 0, 0xC);
    }
    ((igIntList *)arg0->_playerRamNoList)->_count = 0;
    temp_a0_2 = (igIntList *)arg0->_playerRamNoList;
    if (!(0 < temp_a0_2->_count)) {
        List_Reserve(temp_a0_2, 0, 4);
    }
    ((igVec3fList *)arg0->_enemyPosList)->_count = 0;
    temp_a0_3 = (igVec3fList *)arg0->_enemyPosList;
    if (!(0 < temp_a0_3->_count)) {
        List_Reserve(temp_a0_3, 0, 0xC);
    }
}
