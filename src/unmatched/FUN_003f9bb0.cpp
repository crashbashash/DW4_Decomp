#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
struct Rb { char pad[12]; unsigned char b; };
struct Ri { char pad[12]; int n; };
struct Rb *igProperty_GetRecordByte(int, int *);
struct Ri *igProperty_GetRecord(int, int *);
extern int DAT_00518760[4];
extern int DAT_00518888[4];
void FUN_003f9bb0(beNDMWGameRam *arg0, int arg1) {
    int cnt;
    int i;
    int s1;
    int off;

    s1 = arg0->_commonDataList;
    igProperty_GetRecordByte(((int *)((igObjectList *)arg0->_playerDataListList)->_data)[arg1], &DAT_00518888[0])->b = 0;
    cnt = 0;
    i = 0;
    off = 0;
    do {
        if (igProperty_GetRecordByte(((int *)(((igObjectList *)arg0->_playerDataListList)->_data + off))[0], &DAT_00518888[0])->b != 0) {
            cnt += 1;
        }
        i += 1;
        off += 4;
    } while (i < 4);
    igProperty_GetRecord(s1, &DAT_00518760[0])->n = cnt;
}
} /* extern "C" */
