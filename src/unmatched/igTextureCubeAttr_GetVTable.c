struct W { int *vt; int f[27]; };
int FUN_00100390();
int FUN_00100400();
int FUN_00132230();
int FUN_00132390();
int FUN_00132410();
int igObject_InitHeader(struct W *);
extern int DAT_00522aa0[4];
extern void * DAT_00586dc8[4];
int igTextureCubeAttr_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.vt = &DAT_00522aa0[0];
    o.f[2] = 0;
    o.f[11] = 0;
    o.f[13] = 0;
    o.f[15] = 0;
    FUN_00100400(&o.f[17], &FUN_00132410, &FUN_00132390, 4, 6);
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00522aa0[0];
    FUN_00100390(&o.f[17], &FUN_00132390, 4, 6);
    FUN_00132230(&o, 0);
    return r;
}
