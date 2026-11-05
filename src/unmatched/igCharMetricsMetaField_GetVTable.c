typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int igObject_Destroy();
int StringChunk_ReleaseHeader();
int igMetaField_Init();
extern int DAT_0052f230[4];
extern int DAT_00531740[4];
extern int DAT_00541680[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[64]; };
int igCharMetricsMetaField_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    int temp_v0;
    int *temp_a1;
    int *temp_v1;
    char *q1;

    igMetaField_Init(u.b);
    u.vt = (int)&DAT_00531740[0];
    q0 = (S_ref *)&u.b[52];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00541680[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00531740[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&DAT_0052f230[0];
    if (&u.b[12] != 0) {
        temp_v1 = *(int **)&u.b[12];
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}
