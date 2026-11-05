struct Obj { int *vt; char p4[4]; int f8; char pc[8]; int f14; int f18; int f1c; int f20; char pe[12]; };
int igObject_InitHeader(struct Obj *);
int FUN_00343260(int *, int);
int FUN_0033ec80(struct Obj *, int);
extern int DAT_00538670[4];
extern void * DAT_00586dc8[4];
int beParticleCtrl2Info_GetVTable(void) {
    struct Obj o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f14 = 0;
    o.f18 = 0;
    o.vt = &DAT_00538670[0];
    o.f1c = 0;
    o.f20 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00538670[0];
    FUN_00343260(&o.f20, -1);
    FUN_00343260(&o.f1c, -1);
    FUN_0033ec80(&o, 0);
    return r;
}
