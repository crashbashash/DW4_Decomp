#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_00236f80(int, int);
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectGroup(int, int *);
int *beNDMWItemBase_GetRecordString(int, int, int *);
extern int DAT_005199e0[4];
extern int DAT_00519b00[4];
extern int DAT_00519b08[4];
extern int DAT_00519b50[4];
extern int DAT_00519b78[4];
extern int DAT_00519c28[4];
extern int DAT_00519f30[4];
extern int DAT_00519f40[4];
extern int DAT_0058b028[4];
void Gap__Bec__beNDMWStatusSubSlot__vfunc_26(beNDMWStatusSubSlot *a) {
    int *temp_s1;
    int *var_s1_2;
    int temp_v1;
    int var_s1;
    beNDMWItemBaseList *items;

    var_s1 = 0;
    temp_v1 = a->_retCode;
    if (temp_v1 != -1) {
        items = (beNDMWItemBaseList *)a->_subSlot;
        var_s1 = *(int *)(items->_data + (temp_v1 * 4));
    }
    if (var_s1 != 0) {
        temp_s1 = (int *)(beNDMWItemBase_GetRecordString(var_s1, FUN_00236f80(a->_insight, DAT_0058b028[0]), &DAT_00519f40[0]));
        beMessenger_SelectGroup(a->_messenger, &DAT_00519c28[0]);
        beMessenger_AppendString(a->_messenger, &DAT_00519b50[0]);
        beMessenger_AppendString(a->_messenger, &DAT_005199e0[0]);
        beMessenger_AppendString(a->_messenger, temp_s1);
        beMessenger_DispatchSelected(a->_messenger, &DAT_00519f30[0]);
        var_s1_2 = (int *)(&DAT_00519b78[0]);
    } else {
        var_s1_2 = (int *)(&DAT_00519b00[0]);
    }
    beMessenger_SelectGroup(a->_messenger, &DAT_00519c28[0]);
    beMessenger_AppendString(a->_messenger, &DAT_00519b50[0]);
    beMessenger_AppendString(a->_messenger, &DAT_005199e0[0]);
    beMessenger_AppendString(a->_messenger, var_s1_2);
    beMessenger_DispatchSelected(a->_messenger, &DAT_00519b08[0]);
}
} /* extern "C" */
