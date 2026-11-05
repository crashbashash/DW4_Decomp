typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int StringChunk_ReleaseHeader();
int igObject_Destroy();
int igObject_InitHeader();
union U { int vt; char b[32]; };
extern int DAT_005358e0[4];
extern void * DAT_00586dc8[4];
int beFontGeomAttrPair_GetVTable(void) {
    union U u;
    int temp_s2;
    void ** q1;
    void ** q0;
    S_ref * q2;

    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    u.vt = (int)(&DAT_005358e0[0]);
    q0 = (void **)&u.b[8];
    *q0 = 0;
    q1 = (void **)&u.b[12];
    *q1 = 0;
    q2 = (S_ref *)&u.b[16];
    *(int *)q2 = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)(&DAT_005358e0[0]);
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    if (q1 != 0) {
        temp_v1 = *q1;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    if (q0 != 0) {
        temp_v1 = *q0;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s2;
}
