/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
long long __divdi3(long long, int);
int beMessenger_AppendFloat(int, float);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_EnqueueSelected(int, int *, int);
int beMessenger_PrepareDelayedSelection(int, int *, int *, int);
int beMessenger_SelectGroup(int, int *);
int beNDMWItemBase_GetRecordInt(int, int, int *);
int beNDMWItemBase_GetRecordString(int, int, int *);
void *igProperty_GetRecord(int, int *);
extern int DAT_005159c0[4];
extern int DAT_005159d8[4];
extern int DAT_00515a20[4];
extern int DAT_00515a30[4];
extern int DAT_00515a38[4];
extern int DAT_00515a40[4];
extern int DAT_00515a48[4];
extern int DAT_00515a58[4];
extern int DAT_00515a60[4];
extern int DAT_00515a70[4];
extern int DAT_00515a80[4];
extern int DAT_00515a88[4];
extern int DAT_00515a98[4];
#include "dw4/reflected.h"
/* property record: integer value at +12 (record class not recovered) */
struct PropertyRecordInt { char p[12]; int value; };
void Gap__Bec__beNDMWPanelObjectWaza__vfunc_22(beNDMWPanelObjectWaza *arg0, int *arg1, long long *arg2) {
    int temp_s2;
    struct PropertyRecordInt *temp_s1;
    int temp_s0;
    int temp_v1;
    int temp_v0;

    *arg2 = 0;
    *arg1 = 0;
    temp_v1 = arg0->_cursor + arg0->_offset;
    if (((int *)((igDataList *)arg0->_listColor)->_data)[temp_v1] == 0) {
        temp_s2 = ((int *)((igObjectList *)arg0->_listFolder)->_data)[temp_v1];
        temp_s1 = (struct PropertyRecordInt *)igProperty_GetRecord(arg0->_playerDataList, &DAT_00515a20[0]);
        temp_v0 = beNDMWItemBase_GetRecordInt(temp_s2, arg0->_manager, &DAT_00515a20[0]);
        if (temp_s1->value >= temp_v0) {
            *arg2 = (long long)beNDMWItemBase_GetRecordInt(temp_s2, arg0->_manager, &DAT_00515a30[0]);
            *arg2 = __divdi3(*arg2 * 0x3B9ACA00LL, 0x3C);
            *arg1 = beNDMWItemBase_GetRecordString(temp_s2, arg0->_manager, &DAT_00515a38[0]);
            temp_s1->value = temp_s1->value - temp_v0;
            temp_s0 = ((struct PropertyRecordInt *)igProperty_GetRecord(arg0->_playerDataList, &DAT_00515a40[0]))->value;
            beMessenger_PrepareDelayedSelection(arg0->_messenger, &DAT_00515a48[0], &DAT_00515a58[0], arg0->_playerNo);
            beMessenger_AppendFloat(arg0->_messenger, (float)(temp_s1->value * 100 / temp_s0));
            beMessenger_EnqueueSelected(arg0->_messenger, &DAT_00515a60[0], 1);
            beMessenger_PrepareDelayedSelection(arg0->_messenger, &DAT_00515a70[0], &DAT_00515a80[0], arg0->_playerNo);
            beMessenger_AppendInt(arg0->_messenger, temp_s1->value);
            beMessenger_EnqueueSelected(arg0->_messenger, &DAT_00515a88[0], 1);
            return;
        }
        beMessenger_SelectGroup(arg0->_messenger, &DAT_005159c0[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_00515a98[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005159d8[0]);
        return;
    }
    beMessenger_SelectGroup(arg0->_messenger, &DAT_005159c0[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_00515a98[0]);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_005159d8[0]);
}
} /* extern "C" */
