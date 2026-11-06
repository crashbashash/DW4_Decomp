#include "dw4/reflected.h"
extern "C" {
int beNDMWItemBase_GetRecordInt(beNDMWItemRevisionBase *, int, int);
beDataObjObjectList *igProperty_GetRecordFolder(int, int *);
extern int DAT_00518a88[4];
void FUN_003f9f80(int arg0, int arg1, int *arg2, int arg3, int arg4) {
    beNDMWItemRevisionBase *it; int t;
    if (((igObjectList *)igProperty_GetRecordFolder(arg1, &DAT_00518a88[0])->_data)->_count != 0) {
        it = ((beNDMWItemRevisionBase **)((igObjectList *)igProperty_GetRecordFolder(arg1, &DAT_00518a88[0])->_data)->_data)[0];
        if (it != 0) {
            t = beNDMWItemBase_GetRecordInt(it, arg0, arg3); *arg2 += t;
            if (arg4 != 0) {
                t = it->_revision; *arg2 += t;
            }
        }
    }
}
}
