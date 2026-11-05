/* 0x0042b880 - FUN_0042b880. Sends a named message, reads a record count from the database and posts two string-table messages (9 - reserved - used, and that times the record value); alternate compiler -O3,p. */
#include "dw4/reflected.h"
/* Receiver by the matched caller beNDMWShopCtrl50::vfunc_21: offsets +12/+48/+88/+92 are _messenger/_retCode/_conItemNo/_diskCnt. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int sprintf(char *, int *, int);
int beDataBase_GetRecordInt(int, int, int *, int, int);
int beMessenger_AppendString(int, const char *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetObject(int, int);
int beMessenger_SelectGroup(int, int *);
int beMessenger_SendNamed(int, int *, int *, int, int *);
extern const char DAT_0051b218[];
extern const char DAT_0051b288[];
extern int DAT_0051b3c0[4];
extern int DAT_0051b468[4];
extern int DAT_0051b5d8[4];
extern int DAT_0051b5e8[4];
extern int DAT_0051b660[4];
extern int DAT_0051b690[4];
extern int DAT_0051b6b0[4];
extern const char DAT_0051b6f8[];
void FUN_0042b880(beNDMWShopCtrl50 *owner) {
    char sp40[16];
    int obj;
    int remaining;
    int unitCount;
    beNDMWShopCtrl50 *me;

    me = (beNDMWShopCtrl50 *)owner;
    beMessenger_SendNamed(me->_messenger, &DAT_0051b5d8[0], &DAT_0051b660[0], 0, &DAT_0051b5e8[0]);
    obj = beMessenger_GetObject(me->_messenger, 0);
    remaining = (9 - me->_diskCnt) - me->_retCode;
    unitCount = beDataBase_GetRecordInt(obj, me->_conItemNo, &DAT_0051b690[0], 9, me->_diskCnt);
    sprintf(sp40, &DAT_0051b468[0], remaining);
    beMessenger_SelectGroup(me->_messenger, &DAT_0051b3c0[0]);
    beMessenger_AppendString(me->_messenger, &DAT_0051b6f8[0]);
    beMessenger_AppendString(me->_messenger, &DAT_0051b218[0]);
    beMessenger_AppendString(me->_messenger, sp40);
    beMessenger_DispatchSelected(me->_messenger, &DAT_0051b6b0[0]);
    sprintf(sp40, &DAT_0051b468[0], remaining * unitCount);
    beMessenger_SelectGroup(me->_messenger, &DAT_0051b3c0[0]);
    beMessenger_AppendString(me->_messenger, &DAT_0051b6f8[0]);
    beMessenger_AppendString(me->_messenger, &DAT_0051b288[0]);
    beMessenger_AppendString(me->_messenger, sp40);
    beMessenger_DispatchSelected(me->_messenger, &DAT_0051b6b0[0]);
}
} /* extern "C" */
