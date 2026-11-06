struct Obj { int *vt; int w[15]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_001a7580(int *, int);
int FUN_0033e920(int *, int);
int FUN_0034bdc0(int *, int);
int FUN_0034be40(int *, int);
extern int DAT_00538740[4];
extern void * DAT_00586dc8[4];
int beParticleCtrl2InfoRam_GetVTable(void);
}
int beParticleCtrl2InfoRam_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w[9] = 0;
    obj.vt = &DAT_00538740[0];
    obj.w[10] = 0;
    obj.w[11] = 0;
    obj.w[12] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00538740[0];
    FUN_0034be40(&obj.w[12], -1);
    FUN_0034bdc0(&obj.w[11], -1);
    FUN_001a7580(&obj.w[10], -1);
    FUN_0033e920((int *)&obj, 0);
    return t;
}
