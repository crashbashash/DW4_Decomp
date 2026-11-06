#include "dw4/reflected.h"
extern "C" {
extern int DAT_00518848[4];
extern int DAT_00518860[4];
extern int DAT_00518a40[4];
extern int DAT_00518b50[4];
extern int DAT_00518c10[4];
extern int DAT_00518c18[4];
typedef struct Rec { int w0; int w4; int w8; int w12; } Rec;
extern Rec *igProperty_GetRecordFolder(int, int *);
extern Rec *igProperty_GetRecord(int, int *);
extern Rec *FUN_003a9250(int, int *);
extern int beNDMWItemBase_GetRecordInt(Rec *, void *, int *);
int FUN_003f93c0(beNDMWGameRam *arg0, int arg1, int arg2) {
    int obj;
    igObjectList *folder;
    igIntList *tbl;
    int base;
    int mask;
    int n;
    int i;
    obj = ((int *)((igIntList *)arg0->_playerDataListList)->_data)[arg1];
    folder = (igObjectList *)igProperty_GetRecordFolder(obj, DAT_00518a40)->w12;
    {
    int t = igProperty_GetRecord(obj, DAT_00518848)->w12;
    if (t == arg2) {
        tbl = (igIntList *)FUN_003a9250(obj, DAT_00518860)->w12;
        base = 0;
    } else {
        tbl = (igIntList *)FUN_003a9250(obj, DAT_00518b50)->w12;
        base = arg2 * 9;
    }
    }
    mask = 1 << arg2;
    n = folder->_count;
    for (i = 0; i < n; i++) {
        Rec *r = (Rec *)((int *)folder->_data)[i];
        if (r->w8 == 0) {
            int f = mask & beNDMWItemBase_GetRecordInt(r, arg0, DAT_00518c10);
            int idx = beNDMWItemBase_GetRecordInt(r, arg0, DAT_00518860);
            int need = beNDMWItemBase_GetRecordInt(r, arg0, DAT_00518c18);
            if (f != 0 && ((int *)tbl->_data)[base + idx] >= need) return 1;
        }
    }
    return 0;
}
}
