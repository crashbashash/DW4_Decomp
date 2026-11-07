#include "dw4/reflected.h"
extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_InitHeader(beDataObjString *);
extern int DAT_00524950[4];
extern int DAT_005353b0[4];
extern void * DAT_00586dc8[4];
int beDataObjString_GetVTable(void);
}
int beDataObjString_GetVTable(void) {
    beDataObjString obj;
    int temp_s1;
    int *q2;
    int *q3;
    int *temp_a1;
    int *temp_a1_2;
    int temp_v0;
    int temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;

    igObject_InitHeader(&obj);
    q2 = &obj._name;
    *q2 = 0;
    obj._vtable = (int)(&DAT_005353b0[0]);
    q3 = &obj._data;
    *q3 = 0;
    temp_s1 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj._vtable = (int)(&DAT_005353b0[0]);
    if (q3 != 0) {
        temp_v1 = (void *)*q3;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    obj._vtable = (int)(&DAT_00524950[0]);
    if (q2 != 0) {
        temp_v1_2 = (void *)*q2;
        if (temp_v1_2 != 0) {
            temp_a1_2 = (int *)((char *)temp_v1_2 - 8);
            temp_v0_2 = *(int *)((char *)(temp_v1_2) - 4) - 1;
            *(int *)((char *)(temp_v1_2) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
            }
        }
    }
    return temp_s1;
}
