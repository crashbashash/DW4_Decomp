union U { int vt; char b[32]; };
extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(void);
int igObject_InitHeader(char *);
extern int DAT_00537830[4];
extern int DAT_00524950[4];
extern void * DAT_00586dc8[4];
int beModelCtrlAIData_GetVTable(void);
}
int beModelCtrlAIData_GetVTable(void) {
    union U u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00524950[0];
    u.vt = (int)&DAT_00537830[0];
    s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00524950[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return s0;
}
