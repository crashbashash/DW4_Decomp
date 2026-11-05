int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_005257f0[4];
extern int DAT_00530a10[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[32]; };
int igPsx2DisableExt_GetVTable(void) {
    union U u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p38;
    char *p40;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00530a10[0];
    p38 = &u.b[8];
    *(int *)p38 = 0;
    p40 = &u.b[16];
    *(int *)p40 = 0;
    u.vt = (int)&DAT_005257f0[0];
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00530a10[0];
    if (p40 != 0) {
        v1 = *(int **)p40;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p38 != 0) {
        v1 = *(int **)p38;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}
