#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(int, int);
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectGroup(int, int *);
int *beNDMWItemBase_GetRecordString(int, int, int *);
extern int DAT_005199e0[16];
extern int DAT_00519b00[16];
extern int DAT_00519b08[16];
extern int DAT_00519b50[16];
extern int DAT_00519b78[16];
extern int DAT_00519c28[16];
extern int DAT_00519f30[16];
extern int DAT_00519f40[16];
extern int DAT_0058b028[16];
void Gap__Bec__beNDMWStatusPowerSocket__vfunc_34(beNDMWStatusPowerSocket *arg0) {
    int *s1;
    int it;
    int idx;
    it = 0;
    idx = arg0->_retCode;
    if (idx != -1) {
        it = ((int *)((igDataList *)arg0->_wpuPocket)->_data)[idx];
    }
    if (it != 0) {
        s1 = beNDMWItemBase_GetRecordString(it, FUN_00236f80(arg0->_insight, DAT_0058b028[0]), &DAT_00519f40[0]);
        beMessenger_SelectGroup(arg0->_messenger, &DAT_00519c28[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_00519b50[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_005199e0[0]);
        beMessenger_AppendString(arg0->_messenger, s1);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519f30[0]);
        s1 = &DAT_00519b78[0];
    } else {
        s1 = &DAT_00519b00[0];
    }
    beMessenger_SelectGroup(arg0->_messenger, &DAT_00519c28[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_00519b50[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_005199e0[0]);
    beMessenger_AppendString(arg0->_messenger, s1);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519b08[0]);
}
}
