#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
typedef struct PropertyRecord { char p12[12]; int f12; } PropertyRecord;
typedef struct PropertyRecordTable { char p16[16]; int *data; } PropertyRecordTable;
typedef struct PropertyRecordHolder { char p12[12]; PropertyRecordTable *f12; } PropertyRecordHolder;
int FUN_00236f80(int, int);
PropertyRecordHolder *FUN_003a9250(int, int *);
int beNDMWItemBase_GetRecordInt(int, int, int *);
PropertyRecord *igProperty_GetRecord(int, int *);
extern int DAT_00519f78[4];
extern int DAT_00519f88[4];
extern int DAT_00519f90[4];
extern int DAT_00519f98[4];
extern int DAT_0058b028[4];
int Gap__Bec__beNDMWStatusPowerSocket__vfunc_30(beNDMWStatusPowerSocket *arg0, int arg1) {
    int s0b;
    int s0;
    int fl;
    PropertyRecordTable *s1;
    int s3;
    int v0;
    int s2;

    s3 = ((int *)((beNDMWItemBaseList *)arg0->_deviceFolder)->_data)[arg1];
    s0 = FUN_00236f80(arg0->_insight, DAT_0058b028[0]);
    s2 = igProperty_GetRecord(arg0->_playerList, &DAT_00519f78[0])->f12;
    fl = (1 << s2) & beNDMWItemBase_GetRecordInt(s3, s0, &DAT_00519f88[0]);
    s1 = FUN_003a9250(arg0->_playerList, &DAT_00519f90[0])->f12;
    s0b = beNDMWItemBase_GetRecordInt(s3, s0, &DAT_00519f90[0]);
    v0 = beNDMWItemBase_GetRecordInt(s3, s0, &DAT_00519f98[0]);
    if ((fl != 0) && (s1->data[s0b] >= v0)) {
        return 1;
    }
    return 0;
}
} /* extern "C" */
