typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; char b[144]; };
extern "C" {
int igObject_Destroy(S_ref *);
int StringChunk_ReleaseHeader(int, int *);
int igObject_InitHeader(char *);
extern int DAT_00538b00[4];
extern int DAT_00538d40[4];
extern void * DAT_00586dc8[4];
int beSvPlatDataGC_GetVTable(void);
}
int beSvPlatDataGC_GetVTable(void) {
    union U u;
    int temp_s0;
    char *q0;
    S_ref *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00538b00[0];
    q0 = &u.b[104];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00538b00[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    u.vt = (int)&DAT_00538d40[0];
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s0;
}
