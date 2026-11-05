/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; int w[8]; void *p[8]; char b[32]; };
extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(S_ref *);
int igObject_InitHeader(char *);
extern int DAT_00524950[4];
extern int DAT_00537a90[4];
extern void * DAT_00586dc8[4];
int beModelCtrlInfoDataHit_GetVTable(void);
}
int beModelCtrlInfoDataHit_GetVTable(void) {
    union U u;
    int temp_s1;
    void **q2;
    S_ref *q5;
    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&DAT_00537a90[0]);
    q5 = (S_ref *)&u.p[5];
    *(int *)q5 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00537a90[0]);
    if (q5 != 0) {
        q5 = *(S_ref **)q5;
        if (q5 != 0) {
            q5->f4 = (int)((int) (q5->f4 - 1));
            if (((unsigned long long) ((long long) q5->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q5);
            }
        }
    }
    u.w[0] = (int)(&DAT_00524950[0]);
    if (q2 != 0) {
        temp_v1 = *q2;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s1;
}
