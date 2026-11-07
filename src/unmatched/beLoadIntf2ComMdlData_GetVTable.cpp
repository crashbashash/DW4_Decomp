union U { int vt; char b[32]; };
extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_InitHeader(char *);
extern int DAT_0053c810[4];
extern void * DAT_00586dc8[4];
int beLoadIntf2ComMdlData_GetVTable(void);
}
int beLoadIntf2ComMdlData_GetVTable(void) {
    union U u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p3C;
    char *p40;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053c810[0];
    p3C = &u.b[12];
    *(int *)p3C = 0;
    p40 = &u.b[16];
    *(int *)p40 = 0;
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053c810[0];
    if (p40 != 0) {
        v1 = *(int **)p40;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (p3C != 0) {
        v1 = *(int **)p3C;
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
