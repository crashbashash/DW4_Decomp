int StringChunk_ReleaseHeader();
int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_0053bcf0[4];
extern int DAT_0053c070[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[64]; };
int beSvStartApi_GetVTable(void) {
    union U u;
    int r;
    int *v1; int *a1; int v0; int *a0;
    char *pc; char *pb; char *pa;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053c070[0];
    pa = &u.b[48];
    *(int *)pa = 0;
    pb = &u.b[52];
    *(int *)pb = 0;
    pc = &u.b[56];
    *(int *)pc = 0;
    u.vt = (int)&DAT_0053bcf0[0];
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053c070[0];
    if (pc != 0) {
        a0 = *(int **)pc;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    if (pb != 0) {
        a0 = *(int **)pb;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    if (pa != 0) {
        a0 = *(int **)pa;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    return r;
}
