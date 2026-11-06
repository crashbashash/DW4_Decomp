/* List walk re-fetching the record folder each pass; 0 < cnt gives the slt/beqz head; alternate
 * compiler -O3,p. */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
struct R { char pad[12]; igObjectList *f12; };
int beNDMWItemBase_GetRecordInt(int, int, int);
struct R *igProperty_GetRecordFolder(int, void *);
extern int DAT_00518ab0[4];
void FUN_003fa040(int arg0, int arg1, int *arg2, int arg3) {
    int cnt;
    int a0;
    int i;
    cnt = igProperty_GetRecordFolder(arg1, &DAT_00518ab0[0])->f12->_count;
    i = 0;
    if (0 < cnt) {
        do {
            a0 = ((int *)igProperty_GetRecordFolder(arg1, &DAT_00518ab0[0])->f12->_data)[i];
            if (a0 != 0) {
                *arg2 += beNDMWItemBase_GetRecordInt(a0, arg0, arg3);
            }
            i += 1;
        } while (i < cnt);
    }
}
} /* extern "C" */
