struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_0033ec80(struct Obj *, int);
int FUN_0035ade0(int *, int);
extern int DAT_00536960[4];
extern void * DAT_00586dc8[4];
int beLuaInfo_GetVTable(void);
}
int beLuaInfo_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_00536960[0];
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00536960[0];
    FUN_0035ade0(&obj.w7, -1);
    FUN_0033ec80(&obj, 0);
    return t;
}
