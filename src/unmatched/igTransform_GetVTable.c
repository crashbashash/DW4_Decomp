struct W { int *vt; int f[27]; };
int igMatrix44f_SetIdentity();
int FUN_00195a90();
int FUN_001963d0();
int FUN_00196450();
int igObject_InitHeader(struct W *);
extern int DAT_005284f0[4];
extern void * DAT_00586dc8[4];
int igTransform_GetVTable(void) {
    struct W o;
    int r;
    int *pa = (int *)&o;
    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.vt = &DAT_005284f0[0];
    o.f[2] = 0;
    o.f[3] = 0;
    o.f[6] = 0;
    igMatrix44f_SetIdentity((char *)&o + 32);
    pa[25] = 0;
    pa[26] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_005284f0[0];
    FUN_00196450(&o.f[25], -1);
    FUN_001963d0(&o.f[24], -1);
    FUN_00195a90(&o, 0);
    return r;
}
