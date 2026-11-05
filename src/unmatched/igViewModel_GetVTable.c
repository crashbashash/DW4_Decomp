int igMatrix44f_SetIdentity();
int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_00540e30[4];
extern int DAT_00542040[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[176]; };
int igViewModel_GetVTable(void) {
    union U u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p38;
    igObject_InitHeader(u.b);
    p38 = &u.b[8];
    *(int *)p38 = 0;
    u.vt = (int)&DAT_00542040[0];
    igMatrix44f_SetIdentity(&u.b[12]);
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00540e30[0];
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
