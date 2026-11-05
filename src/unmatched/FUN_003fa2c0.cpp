/* 0x003fa2c0 - FUN_003fa2c0. Shop record accumulator, string-compare variant: adds the record integer and, when the record string equals the key, the item field, through one reused temporary; alternate compiler -O3,p. Verified byte-identical by tools/verify.py. */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
struct ListHolder { int pad[3]; igObjectList *list; };
int beNDMWItemBase_GetRecordInt(beNDMWItemBase *, int, int);
char *beNDMWItemBase_GetRecordString(beNDMWItemBase *, int, int *);
struct ListHolder *igProperty_GetRecordFolder(int, int *);
int igStrCmp(char *, int);
extern int DAT_00518ae0[4];
extern int DAT_00518c88[4];
void FUN_003fa2c0(int arg0, int arg1, int *arg2, int arg3, int arg4) {
    beNDMWItemBase *it; int t;
    if (igProperty_GetRecordFolder(arg1, &DAT_00518ae0[0])->list->_count != 0) {
        it = *(beNDMWItemBase **)igProperty_GetRecordFolder(arg1, &DAT_00518ae0[0])->list->_data;
        if (it != 0) {
            t = beNDMWItemBase_GetRecordInt(it, arg0, arg3); *arg2 += t;
            if (arg4 != 0 && igStrCmp(beNDMWItemBase_GetRecordString(it, arg0, &DAT_00518c88[0]), arg3) == 0) {
                t = *(int *)((char *)it + 20); *arg2 += t;
            }
        }
    }
}
} /* extern "C" */
