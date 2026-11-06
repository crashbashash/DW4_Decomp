/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
union U { int vt; char b[32]; };
extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(int *);
int igObject_InitHeader(char *);
extern int DAT_00524950[4];
extern int DAT_0053d060[4];
extern void * DAT_00586dc8[4];
int beNDMWLoadIntf2DegiStateCtrl_GetVTable(void);
}
int beNDMWLoadIntf2DegiStateCtrl_GetVTable(void) {
    union U u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p38;
    char *p40;

    igObject_InitHeader(u.b);
    p38 = &u.b[8];
    *(int *)p38 = 0;
    u.vt = (int)&DAT_0053d060[0];
    p40 = &u.b[16];
    *(int *)p40 = 0;
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053d060[0];
    if (p40 != 0) {
        v1 = *(int **)p40;
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
