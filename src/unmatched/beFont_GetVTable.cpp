/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_001354b0(int *, int);
int FUN_001489a0(int *, int);
int FUN_001d97f0(int *, int);
int FUN_0033f5e0(struct Obj *, int);
int FUN_00362070(int *, int);
int FUN_003620f0(int *, int);
int ObjectRef_Destruct_00150eb0(int *, int);
int StringRef_Destruct_00130720(int *, int);
extern int DAT_0053a5c0[4];
extern void * DAT_00586dc8[4];
int beFont_GetVTable(void);
}
int beFont_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_0053a5c0[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053a5c0[0];
    StringRef_Destruct_00130720(&obj.w16, -1);
    StringRef_Destruct_00130720(&obj.w15, -1);
    FUN_001489a0(&obj.w14, -1);
    FUN_001354b0(&obj.w13, -1);
    ObjectRef_Destruct_00150eb0(&obj.w12, -1);
    FUN_003620f0(&obj.w11, -1);
    FUN_00362070(&obj.w9, -1);
    FUN_001d97f0(&obj.w8, -1);
    FUN_0033f5e0(&obj, 0);
    return t;
}
