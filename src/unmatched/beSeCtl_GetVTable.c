typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int StringChunk_ReleaseHeader();
int igObject_Destroy();
int igObject_InitHeader();
union U { int vt; int w[4]; void *p[4]; char b[48]; };
extern int DAT_00524950[4];
extern int DAT_0053a0d0[4];
extern int DAT_0053b1f0[4];
extern void * DAT_00586dc8[4];
int beSeCtl_GetVTable(void) {
    union U u;
    int temp_s1;
    void **q2;
    S_ref *q3;

    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_0053a0d0[0]);
    q2 = &u.p[2];
    *q2 = 0;
    q3 = (S_ref *)&u.b[24];
    *(int *)q3 = 0;
    u.w[0] = (int)(&DAT_0053b1f0[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0053a0d0[0]);
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
