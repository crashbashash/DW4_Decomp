/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_00344030(struct Obj *, int);
int FUN_0034c1b0(int *, int);
int FUN_00352fc0(int *, int);
extern int DAT_00537bb0[4];
extern void * DAT_00586dc8[4];
int beModelCtrlInfoRamData_GetVTable(void);
}
int beModelCtrlInfoRamData_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00537bb0[0];
    obj.w4 = 0;
    obj.w5 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00537bb0[0];
    FUN_00352fc0(&obj.w5, -1);
    FUN_0034c1b0(&obj.w4, -1);
    FUN_00344030(&obj, 0);
    return t;
}
