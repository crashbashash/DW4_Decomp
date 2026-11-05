struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
int igObject_InitHeader(struct Obj *);
int FUN_003cafa0();
int FUN_00458dc0();
int FUN_00458e40();
int StringRef_Destruct_00130720();
extern int DAT_00542620[4];
extern void * DAT_00586dc8[4];
int igStatisticsItem_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00542620[0];
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00542620[0];
    FUN_00458e40(&obj.w11, -1);
    FUN_00458dc0(&obj.w10, -1);
    FUN_003cafa0(&obj.w9, -1);
    StringRef_Destruct_00130720(&obj.w7, -1);
    StringRef_Destruct_00130720(&obj.w6, -1);
    return t;
}
