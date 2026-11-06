#include "dw4/reflected.h"
extern "C" {
struct Rb { char pad[12]; unsigned char b; };
struct Ri { char pad[12]; int n; };
struct Ra { char pad[12]; igDataList *a; };
struct Rb *igProperty_GetRecordByte(int, int *);
struct Ra *igProperty_GetRecordArray(int, int *);
struct Ri *igProperty_GetRecord(int, int *);
int FUN_003f80e0(beNDMWGameRam *, int);
int FUN_003f82a0(beNDMWGameRam *, int, int);
int FUN_003f8990(beNDMWGameRam *, int);
int FUN_003f8c90(beNDMWGameRam *, int, int);
int FUN_003fab90(beNDMWGameRam *, int, int);
extern int DAT_00518760[4];
extern int DAT_00518888[4];
extern int DAT_00518b20[4];
extern unsigned char GPR_005549ec;
void FUN_003f9570(beNDMWGameRam *arg0, int arg1, int arg2) {
    int cnt;
    int i;
    int s1;
    int off;
    int s4;
    int idx;
    igDataList *arr;
    struct Rb *rb;

    s1 = arg0->_commonDataList;
    s4 = ((int *)((igObjectListList *)arg0->_playerDataListList)->_data)[arg1];
    idx = FUN_003f80e0(arg0, arg2);
    FUN_003f82a0(arg0, arg1, idx);
    FUN_003f8990(arg0, arg1);
    FUN_003f8c90(arg0, arg1, 0);
    FUN_003fab90(arg0, arg1, 1);
    rb = igProperty_GetRecordByte(s4, &DAT_00518888[0]);
    rb->b = 1;
    arr = igProperty_GetRecordArray(s4, &DAT_00518b20[0])->a;
    if (arr->_count != 0 && idx >= 0 && idx < arr->_count) {
        *(char *)(idx + arr->_data) = GPR_005549ec;
    }
    cnt = 0;
    i = 0;
    off = 0;
    do {
        if (igProperty_GetRecordByte(*(int *)(((igObjectListList *)arg0->_playerDataListList)->_data + off), &DAT_00518888[0])->b != 0) {
            cnt += 1;
        }
        i += 1;
        off += 4;
    } while (i < 4);
    igProperty_GetRecord(s1, &DAT_00518760[0])->n = cnt;
}
}
