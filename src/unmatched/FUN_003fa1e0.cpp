#include "dw4/reflected.h"
extern "C" {
struct F { char pad[12]; igObjectList *list; };
int beNDMWItemBase_GetRecordInt(int, int, int);
struct F *igProperty_GetRecordFolder(int, int *);
extern int DAT_00518ad0[4];
void FUN_003fa1e0(int arg0, int arg1, int *arg2, int arg3) {
    int temp_a0;
    int n;
    int i;
    n = igProperty_GetRecordFolder(arg1, &DAT_00518ad0[0])->list->_count;
    for (i = 0; i < n; i++) {
        temp_a0 = ((int *)igProperty_GetRecordFolder(arg1, &DAT_00518ad0[0])->list->_data)[i];
        if (temp_a0 != 0) {
            *arg2 += beNDMWItemBase_GetRecordInt(temp_a0, arg0, arg3);
        }
    }
}
}
