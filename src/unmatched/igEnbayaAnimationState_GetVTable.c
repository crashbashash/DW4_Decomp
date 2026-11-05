int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_00529170[4];
extern int DAT_00529550[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[176]; };
int igEnbayaAnimationState_GetVTable(void) {
    union U u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p58;
    char *p48;
    char *pB8;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00529550[0];
    p48 = &u.b[8];
    *(int *)p48 = 0;
    p58 = &u.b[24];
    *(int *)p58 = 0;
    pB8 = &u.b[120];
    *(int *)pB8 = 0;
    u.vt = (int)&DAT_00529170[0];
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00529550[0];
    if (pB8 != 0) {
        v1 = *(int **)pB8;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p58 != 0) {
        v1 = *(int **)p58;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p48 != 0) {
        v1 = *(int **)p48;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}
