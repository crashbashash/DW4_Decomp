#include "dw4/reflected.h"
extern "C" {
int SYSgetPlayerNinzu();
int beMessenger_GetObject(int, int);
int beMessenger_SendNamed(int, int *, int, int, int *);
int *igProperty_GetRecordArray(int, int *);
extern int DAT_0050d8f0[4];
extern int DAT_0050d940[4];
extern int DAT_0050d9f0[4];
extern int DAT_0058a1c0[4];
unsigned char FLGisOn(int arg0);
}

unsigned char FLGisOn(int arg0) {
    int temp_v0;
    int *r;

    beMessenger_SendNamed(DAT_0058a1c0[0], &DAT_0050d940[0], 0, 0, &DAT_0050d8f0[0]);
    temp_v0 = beMessenger_GetObject(DAT_0058a1c0[0], 0);
    if (arg0 == 0x3E8) {
        return SYSgetPlayerNinzu() != 0;
    }
    r = igProperty_GetRecordArray(temp_v0, &DAT_0050d9f0[0]);
    return *(unsigned char *)(((igDataList *)r[3])->_data + arg0);
}
