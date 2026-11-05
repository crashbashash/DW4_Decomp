struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
int igObject_InitHeader(struct Obj *);
int FUN_00226db0();
int FUN_0013a880();
int FUN_0014aa70();
extern int DAT_0052c080[4];
extern void * DAT_00586dc8[4];
int igListenerInterface_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c080[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052c080[0];
    FUN_00226db0(&obj.w11, -1);
    FUN_0013a880(&obj.w10, -1);
    FUN_00226db0(&obj.w9, -1);
    FUN_0014aa70(&obj.w8, -1);
    return t;
}
