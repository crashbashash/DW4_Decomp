struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; int w28; int w29; int w30; int w31; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_001338d0(int *, int);
int FUN_0014caf0(struct Obj *, int);
extern int DAT_0053b740[4];
extern void * DAT_00586dc8[4];
int ParticleArray_GetVTable(void);
}
int ParticleArray_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w17 = 0;
    obj.vt = &DAT_0053b740[0];
    obj.w28 = 0;
    obj.w29 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053b740[0];
    FUN_001338d0(&obj.w29, -1);
    FUN_001338d0(&obj.w28, -1);
    FUN_0014caf0(&obj, 0);
    return t;
}
