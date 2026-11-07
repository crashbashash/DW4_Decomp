union U { int vt; char b[48]; };
extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(int *);
int igObject_InitHeader(char *);
extern int DAT_0053b150[4];
extern int DAT_0053a0d0[4];
extern int DAT_00524950[4];
extern void * DAT_00586dc8[4];
int bePoint01_GetVTable(void);
}
int bePoint01_GetVTable(void) {
    union U u;
    int r;

    int *v1; int *a1; int v0; int *a0;
    char *pr; char *ps;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053a0d0[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    pr = &u.b[24];
    *(int *)pr = 0;
    u.vt = (int)&DAT_0053b150[0];
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053a0d0[0];
    if (pr != 0) {
        a0 = *(int **)pr;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
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
    return r;
}
