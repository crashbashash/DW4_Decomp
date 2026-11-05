struct W { int *vt; int f[11]; };
int FUN_0014f580(struct W *, int);
int igObject_InitHeader(struct W *);
extern int DAT_00526930[4];
extern char *DAT_00586dc8[4];
int igExternalImageEntry_GetVTable(void) {
    struct W o;
    int r;
    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[6] = 0;
    o.f[7] = 0;
    o.f[9] = 0;
    o.vt = DAT_00526930;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_00526930;
    FUN_0014f580(&o, 0);
    return r;
}
