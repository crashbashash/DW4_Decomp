typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; int w[4]; void *p[4]; char b[16]; };
extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(S_ref *);
int igObject_InitHeader(char *);
extern int DAT_00524950[4];
extern int DAT_00533fc0[4];
extern void * DAT_00586dc8[4];
int beAction2Data_GetVTable(void);
}
int beAction2Data_GetVTable(void) {
    union U u;
    int temp_s1;
    void **q2;
    S_ref *q3;
    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&DAT_00533fc0[0]);
    q3 = (S_ref *)&u.p[3];
    *(int *)q3 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00533fc0[0]);
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q3);
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
