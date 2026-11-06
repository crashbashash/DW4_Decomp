#include "dw4/reflected.h"
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
void Gap__Bec__beNDMWStatusMainSlot__vfunc_34(beNDMWStatusMainSlot *arg0) {
    int *temp_s1;
    int *var_s1_2;
    int temp_v1;
    int var_s1;

    var_s1 = 0;
    temp_v1 = arg0->_retCode;
    if (temp_v1 != -1) {
        var_s1 = ((int *)((beNDMWItemBaseList *)arg0->_apuPocket)->_data)[temp_v1];
    }
    if (var_s1 != 0) {
        temp_s1 = beNDMWItemBase_GetRecordString(var_s1, FUN_00236f80(arg0->_insight, DAT_0058b028[0]), &DAT_00519f40[0]);
        beMessenger_SelectGroup(arg0->_messenger, &DAT_00519c28[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_00519b50[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_005199e0[0]);
        beMessenger_AppendString(arg0->_messenger, temp_s1);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519f30[0]);
        var_s1_2 = &DAT_00519b78[0];
    } else {
        var_s1_2 = &DAT_00519b00[0];
    }
    beMessenger_SelectGroup(arg0->_messenger, &DAT_00519c28[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_00519b50[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_005199e0[0]);
    beMessenger_AppendString(arg0->_messenger, var_s1_2);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519b08[0]);
}
}
