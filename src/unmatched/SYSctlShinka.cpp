#include "dw4/reflected.h"
extern "C" {
int bePlayer_GetStruct(int);
beDataObjBoolList *igProperty_GetRecordArray(int, int *);
beDataObjIntList *FUN_003a9250(int, int *);
int strcmp(int, int *);
extern int DAT_0050da18[4];
extern int DAT_0050da50[4];
extern int DAT_0050da58[4];
extern int DAT_0050da68[4];
extern int DAT_0050da78[4];
extern int DAT_0050da88[4];
extern unsigned char GPR_005549c4;

int SYSctlShinka(int arg0, int arg1, int arg2) {
    int has;
    int ret;
    igBoolList *b;
    unsigned char *d;
    d = (unsigned char *)((igBoolList *)igProperty_GetRecordArray(bePlayer_GetStruct(arg1 + 1), &DAT_0050da18[0])->_data)->_data; /* matching construct: byte base held in a pointer local keeps the retail operand order of the index add */
    has = d[arg2];
    if (strcmp(arg0, &DAT_0050da50[0]) == 0) {
        if (has != 0) ret = ((int *)((igIntList *)FUN_003a9250(bePlayer_GetStruct(arg1 + 1), &DAT_0050da58[0])->_data)->_data)[arg2];
        else ret = -1;
    } else if (strcmp(arg0, &DAT_0050da68[0]) == 0) {
        if (has != 0) ret = ((int *)((igIntList *)FUN_003a9250(bePlayer_GetStruct(arg1 + 1), &DAT_0050da78[0])->_data)->_data)[arg2];
        else ret = -1;
    } else if (strcmp(arg0, &DAT_0050da88[0]) == 0) {
        if (has != 0) ret = 0;
        else {
            b = (igBoolList *)igProperty_GetRecordArray(bePlayer_GetStruct(arg1 + 1), &DAT_0050da18[0])->_data;
            if (b->_count != 0 && arg2 >= 0 && arg2 < b->_count) ((unsigned char *)b->_data)[arg2] = GPR_005549c4;
            ret = 1;
        }
    } else ret = 0;
    return ret;
}
}
