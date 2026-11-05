#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_00431670(beNDMWShopCtrlEvolve *, int);
int FUN_00433120(int, int, int);
int beDataBase_GetRecordString(int, int, int *);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetObject(int, int);
int beMessenger_SelectGroup(int, int *);
int beMessenger_SelectReceivers(int, int *, int, int);
int beMessenger_SendNamed(int, int *, int *, int, int *);
void *igProperty_GetRecordFolder(int, int *);
extern int DAT_0051b398[4];
extern int DAT_0051b3a0[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b498[4];
extern int DAT_0051b4a0[4];
extern int DAT_0051b5d8[4];
extern int DAT_0051b5e8[4];
extern int DAT_0051bae8[4];
extern int DAT_0051bb28[4];
extern int DAT_0051bb38[4];
extern int DAT_0051bb48[4];
extern int DAT_0051bb60[4];
extern int DAT_0051bb78[4];
extern int DAT_0051bb88[4];
extern int DAT_0051bb90[4];
extern int DAT_0051bba0[4];
void FUN_004313b0(beNDMWShopCtrlEvolve *arg0) {
    int temp_s0;
    int temp_s2_2;
    int temp_s3;
    beNDMWShinkaObjectList *temp_a5;
    beNDMWShinkaObject *temp_s2;

    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
    temp_s0 = beMessenger_GetObject(arg0->_messenger, 0);
    temp_a5 = (beNDMWShinkaObjectList *)((beNDMWShinkaCtrl *)arg0->_shinkaCtrl)->_list;
    temp_s2 = (beNDMWShinkaObject *)((int *)temp_a5->_data)[arg0->_cursor + arg0->_nowPage * 8];
    beMessenger_SendNamed(arg0->_messenger, &DAT_0051b5d8[0], &DAT_0051bae8[0], 0, &DAT_0051b5e8[0]);
    temp_s3 = beMessenger_GetObject(arg0->_messenger, 0);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051bb28[0]);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    temp_s2_2 = arg0->_messenger;
    beMessenger_AppendString(temp_s2_2, beDataBase_GetRecordString(temp_s3, temp_s2->_id, &DAT_0051bb38[0]));
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051bb48[0]);
    beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b398[0], 0, 0);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3a0[0]);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051bb60[0]);
    FUN_00431670(arg0, *(int *)((char *)(igProperty_GetRecordFolder(temp_s0, &DAT_0051bb78[0])) + 12));
    FUN_00431670(arg0, *(int *)((char *)(igProperty_GetRecordFolder(temp_s0, &DAT_0051bb88[0])) + 12));
    FUN_00431670(arg0, *(int *)((char *)(igProperty_GetRecordFolder(temp_s0, &DAT_0051bb90[0])) + 12));
    FUN_00431670(arg0, *(int *)((char *)(igProperty_GetRecordFolder(temp_s0, &DAT_0051bba0[0])) + 12));
    beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b398[0], 0, 0);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3a0[0]);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b498[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b4a0[0]);
    FUN_00433120(arg0->_mother, arg0->_playerNo, 1);
}
} /* extern "C" */
