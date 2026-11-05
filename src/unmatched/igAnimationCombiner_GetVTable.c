struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; };
int igObject_InitHeader(struct Obj *);
int FUN_001a8620();
int FUN_001a8700();
int FUN_001a8780();
int ObjectRef_Destruct_00150eb0();
extern int DAT_00529630[4];
extern void * DAT_00586dc8[4];
int igAnimationCombiner_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.vt = &DAT_00529630[0];
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00529630[0];
    FUN_001a8780(&obj.w14, -1);
    ObjectRef_Destruct_00150eb0(&obj.w13, -1);
    FUN_001a8700(&obj.w12, -1);
    FUN_001a8620(&obj, 0);
    return t;
}
