struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
int igObject_InitHeader(struct Obj *);
int FUN_00164870();
extern int DAT_0052a6d0[4];
extern void * DAT_00586dc8[4];
int igCompressedTransformSequence1_5Data_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052a6d0[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052a6d0[0];
    FUN_00164870(&obj.w5, -1);
    FUN_00164870(&obj.w4, -1);
    FUN_00164870(&obj.w3, -1);
    FUN_00164870(&obj.w2, -1);
    return t;
}
