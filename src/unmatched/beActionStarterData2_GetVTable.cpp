union U { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_InitHeader(char *);
extern int DAT_00524950[4];
extern int DAT_00534480[4];
extern int DAT_005344e0[4];
extern void * DAT_00586dc8[4];
int beActionStarterData2_GetVTable(void);
}
int beActionStarterData2_GetVTable(void) {
    union U u;
    int temp_s1;
    void **q2;
    void **q3;
    int *temp_a1;
    int *temp_a1_2;
    int temp_v0;
    int temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&DAT_005344e0[0]);
    q3 = &u.p[3];
    *q3 = 0;
    u.w[0] = (int)(&DAT_00534480[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_005344e0[0]);
    if (q3 != 0) {
        temp_v1 = *q3;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    u.w[0] = (int)(&DAT_00524950[0]);
    if (q2 != 0) {
        temp_v1_2 = *q2;
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
