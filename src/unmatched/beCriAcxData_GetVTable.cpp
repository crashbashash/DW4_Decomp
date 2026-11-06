typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; char b[32]; };
extern "C" {
int igObject_Destroy(void);
int StringChunk_ReleaseHeader(int, int *);
int igObject_InitHeader(char *);
extern int DAT_00524950[4];
extern int DAT_00534d70[4];
extern void * DAT_00586dc8[4];
int beCriAcxData_GetVTable(void);
}
int beCriAcxData_GetVTable(void) {
    union U u;
    int temp_s0;
    int temp_v0;
    int *temp_a1;
    int *temp_v1;
    char *q0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00524950[0];
    q0 = &u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00534d70[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00524950[0];
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
    return temp_s0;
}
