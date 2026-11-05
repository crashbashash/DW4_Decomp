struct W { int *vt; int f[15]; };
int igObject_InitHeader(struct W *);
int FUN_00137260(void *, int);
int FUN_00137530(struct W *, int);
extern int DAT_005238c0[4];
extern char *DAT_00586dc8[4];
int igGeometryAttr1_5_GetVTable(void) {
    struct W o;
    int r;
    igObject_InitHeader(&o);
    o.f[2] = 0;
    o.f[3] = 0;
    o.f[7] = 0;
    o.f[9] = 0;
    o.f[10] = 0;
    o.vt = DAT_005238c0;
    o.f[11] = 0;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_005238c0;
    FUN_00137260(&o.f[11], -1);
    FUN_00137530(&o, 0);
    return r;
}
