union U { int vt; char b[48]; };
extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(int *);
int igObject_InitHeader(char *);
extern int DAT_00524950[4];
extern int DAT_0053a0d0[4];
extern int DAT_0053e020[4];
extern void * DAT_00586dc8[4];
int beNDMWPanelWaza_GetVTable(void);
}
int beNDMWPanelWaza_GetVTable(void) {
    union U u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p38;
    char *p48;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053a0d0[0];
    p38 = &u.b[8];
    *(int *)p38 = 0;
    p48 = &u.b[24];
    *(int *)p48 = 0;
    u.vt = (int)&DAT_0053e020[0];
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053a0d0[0];
    if (p48 != 0) {
        v1 = *(int **)p48;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    u.vt = (int)&DAT_00524950[0];
    if (p38 != 0) {
        v1 = *(int **)p38;
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
