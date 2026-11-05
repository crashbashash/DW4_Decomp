#include "dw4/reflected.h"
extern "C" {
int beMessenger_GetObject(int, int);
int beMessenger_SendNamed(int, int *, int, int, int *);
void *igProperty_GetRecordArray(int, int *);
extern int DAT_0050d8f0[4];
extern int DAT_0050d940[4];
extern int DAT_0050d9f0[4];
extern int DAT_0058a1c0[4];
void FLGset(int arg0, char arg1);
}

void FLGset(int arg0, char arg1) {
    int temp_v1;
    igDataList *temp_a0;

    beMessenger_SendNamed(DAT_0058a1c0[0], &DAT_0050d940[0], 0, 0, &DAT_0050d8f0[0]);
    temp_a0 = (igDataList *)(*(int *)((char *)(igProperty_GetRecordArray(beMessenger_GetObject(DAT_0058a1c0[0], 0), &DAT_0050d9f0[0])) + 12));
    temp_v1 = temp_a0->_count;
    if ((temp_v1 != 0) && (arg0 >= 0) && (arg0 < temp_v1)) {
        *(char *)(arg0 + temp_a0->_data) = arg1;
    }
}
