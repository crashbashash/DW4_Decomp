#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(int, int);
int igObject_Destroy(igDataList *);
extern int DAT_00589208[4];
}
/* _wkMatOnList/_wkMatOldOnList are igDataList-layout lists (hypothesis): +4 refcount, +8 count */
extern "C" {
void Gap__Bec__beMatCtrl__vfunc_32(beMatCtrl *arg0);
}
void Gap__Bec__beMatCtrl__vfunc_32(beMatCtrl *arg0) {
    igDataList *temp_a0;
    igDataList *temp_a0_2;
    igDataList *temp_v1;
    igDataList *temp_v1_2;

    arg0->_lua = FUN_00236f80(arg0->_insight, DAT_00589208[0]);
    temp_v1 = (igDataList *)(arg0->_wkMatOnList);
    if (temp_v1 != 0) {
        temp_v1->_count = 0;
        temp_a0 = (igDataList *)(arg0->_wkMatOnList);
        if (temp_a0 != 0) {
            temp_a0->_refCount = temp_a0->_refCount - 1;
            if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_wkMatOnList = 0;
    }
    temp_v1_2 = (igDataList *)(arg0->_wkMatOldOnList);
    if (temp_v1_2 != 0) {
        temp_v1_2->_count = 0;
        temp_a0_2 = (igDataList *)(arg0->_wkMatOldOnList);
        if (temp_a0_2 != 0) {
            temp_a0_2->_refCount = temp_a0_2->_refCount - 1;
            if ((temp_a0_2->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0_2);
            }
        }
        arg0->_wkMatOldOnList = 0;
    }
}
