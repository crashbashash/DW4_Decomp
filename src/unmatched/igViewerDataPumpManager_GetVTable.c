typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int StringChunk_ReleaseHeader();
int igObject_Destroy();
int igObject_InitHeader();
union U { int vt; int w[8]; void *p[8]; char b[32]; };
extern int DAT_00524950[4];
extern int DAT_00542310[4];
extern void * DAT_00586dc8[4];
int igViewerDataPumpManager_GetVTable(void) {
    union U u;
    int temp_s1;
    void **q2;
    S_ref *q4;

    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&DAT_00542310[0]);
    q4 = (S_ref *)&u.p[4];
    *(int *)q4 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00542310[0]);
    if (q4 != 0) {
        q4 = *(S_ref **)q4;
        if (q4 != 0) {
            q4->f4 = (int)((int) (q4->f4 - 1));
            if (((unsigned long long) ((long long) q4->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q4);
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


