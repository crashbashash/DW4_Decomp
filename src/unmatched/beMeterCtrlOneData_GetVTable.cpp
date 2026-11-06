/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_00131bc0(struct Obj *, int);
int FUN_00350b10(int *, int);
int FUN_003573d0(int *, int);
extern int DAT_00536fe0[4];
extern void * DAT_00586dc8[4];
int beMeterCtrlOneData_GetVTable(void);
}
int beMeterCtrlOneData_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00536fe0[0];
    obj.w3 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00536fe0[0];
    FUN_00350b10(&obj.w17, -1);
    FUN_00350b10(&obj.w16, -1);
    FUN_003573d0(&obj.w3, -1);
    FUN_00131bc0(&obj, 0);
    return t;
}
