/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_00131bc0(struct Obj *, int);
int FUN_001354b0(int *, int);
int FUN_001374b0(int *, int);
int FUN_0035fcd0(int *, int);
int StringRef_Destruct_00130720(int *, int);
extern int DAT_00535eb0[4];
extern void * DAT_00586dc8[4];
int beGeneraterData_GetVTable(void);
}
int beGeneraterData_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00535eb0[0];
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w13 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00535eb0[0];
    FUN_0035fcd0(&obj.w16, -1);
    StringRef_Destruct_00130720(&obj.w15, -1);
    StringRef_Destruct_00130720(&obj.w13, -1);
    StringRef_Destruct_00130720(&obj.w11, -1);
    StringRef_Destruct_00130720(&obj.w10, -1);
    FUN_001354b0(&obj.w8, -1);
    FUN_001374b0(&obj.w7, -1);
    FUN_00131bc0(&obj, 0);
    return t;
}
