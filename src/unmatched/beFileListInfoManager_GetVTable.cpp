struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int ObjectRef_Destruct_001c6460(int *, int);
int FUN_001d35d0(int *, int);
int FUN_00231030(struct Obj *, int);
int FUN_002bac40(int *, int);
extern int DAT_0053a4e0[4];
extern void * DAT_00586dc8[4];
int beFileListInfoManager_GetVTable(void);
}
int beFileListInfoManager_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_0053a4e0[0];
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w13 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053a4e0[0];
    FUN_001d35d0(&obj.w13, -1);
    FUN_001d35d0(&obj.w12, -1);
    FUN_002bac40(&obj.w11, -1);
    FUN_001d35d0(&obj.w10, -1);
    ObjectRef_Destruct_001c6460(&obj.w9, -1);
    FUN_00231030(&obj, 0);
    return t;
}
