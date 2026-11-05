typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int StringChunk_ReleaseHeader();
int igObject_Destroy();
int igObject_InitHeader();
union U { int vt; int w[12]; void *p[12]; char b[48]; };
extern int DAT_00539010[4];
extern void * DAT_00586dc8[4];
int beSelectCtrlInfoWork_GetVTable(void) {
    union U u;
    int temp_s1;
    void **q7;
    S_ref *q8;

    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q7 = &u.p[7];
    q8 = (S_ref *)&u.p[8];
    u.w[0] = (int)(&DAT_00539010[0]);
    *q7 = 0;
    *(int *)q8 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00539010[0]);
    if (q8 != 0) {
        q8 = *(S_ref **)q8;
        if (q8 != 0) {
            q8->f4 = (int)((int) (q8->f4 - 1));
            if (((unsigned long long) ((long long) q8->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q8);
            }
        }
    }
    if (q7 != 0) {
        temp_v1 = *q7;
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


