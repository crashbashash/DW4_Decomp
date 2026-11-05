struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
int igObject_InitHeader(struct Obj *);
int FUN_00152b10();
int FUN_00152c10();
int FUN_00152c90();
extern int DAT_005252a0[4];
extern void * DAT_00586dc8[4];
int igPsx2UserUCodeExt_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w4 = 0;
    obj.vt = &DAT_005252a0[0];
    obj.w6 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_005252a0[0];
    FUN_00152c90(&obj.w7, -1);
    FUN_00152c10(&obj.w6, -1);
    FUN_00152b10(&obj, 0);
    return t;
}
