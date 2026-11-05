/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_0033f560(int *, int);
int FUN_0033f5e0(struct Obj *, int);
extern int DAT_0053b9b0[4];
extern void * DAT_00586dc8[4];
int beStaticInfoCtl_GetVTable(void);
}
int beStaticInfoCtl_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_0053b9b0[0];
    obj.w8 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053b9b0[0];
    FUN_0033f560(&obj.w8, -1);
    FUN_0033f5e0(&obj, 0);
    return t;
}
