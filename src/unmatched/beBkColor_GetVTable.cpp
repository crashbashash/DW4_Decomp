#include "dw4/reflected.h"
union U { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(void *);
int igObject_InitHeader(char *);
extern int DAT_00524950[4];
extern int DAT_0053a170[4];
extern int DAT_0053a0d0[4];
extern void * DAT_00586dc8[4];
int beBkColor_GetVTable(void);
}
int beBkColor_GetVTable(void) {
    union U u;
    int temp_s1;
    void **q2;
    void **q3;
    int *temp_a1;
    int temp_v0_2;
    void *temp_a0;
    void *temp_v1_2;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&DAT_0053a0d0[0]);
    q3 = &u.p[6];
    *q3 = 0;
    u.w[0] = (int)(&DAT_0053a170[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0053a0d0[0]);
    if (q3 != 0) {
        temp_a0 = *q3;
        if (temp_a0 != 0) {
            ((igObject *)temp_a0)->_refCount = (int)((int) (((igObject *)temp_a0)->_refCount - 1));
            if (((unsigned long long) ((long long) (int) ((igObject *)temp_a0)->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    u.w[0] = (int)(&DAT_00524950[0]);
    if (q2 != 0) {
        temp_v1_2 = *q2;
        if (temp_v1_2 != 0) {
            temp_a1 = (int *)((char *)temp_v1_2 - 8);
            temp_v0_2 = *(int *)((char *)(temp_v1_2) - 4) - 1;
            *(int *)((char *)(temp_v1_2) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s1;
}
