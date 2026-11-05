int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_0053bd60[4];
extern int DAT_0053c070[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[96]; };
int beSvGetFreeSizeApi_GetVTable(void) {
    union U u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p74;
    char *p70;
    char *p78;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053c070[0];
    p70 = &u.b[48];
    *(int *)p70 = 0;
    p74 = &u.b[52];
    *(int *)p74 = 0;
    p78 = &u.b[56];
    *(int *)p78 = 0;
    u.vt = (int)&DAT_0053bd60[0];
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053c070[0];
    if (p78 != 0) {
        v1 = *(int **)p78;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p74 != 0) {
        v1 = *(int **)p74;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p70 != 0) {
        v1 = *(int **)p70;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}
