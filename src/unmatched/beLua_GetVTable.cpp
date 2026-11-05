/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w[7]; };
extern "C" {
int FUN_00231030(struct Obj *, int);
int FUN_0033f560(int *, int);
int FUN_0035b8c0(int *, int);
int FUN_0035b940(int *, int);
int igObject_InitHeader(struct Obj *);
extern int DAT_0053a9e0[4];
extern void * DAT_00586dc8[4];
int beLua_GetVTable(void);
}
int beLua_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.vt = &DAT_0053a9e0[0];
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.w[6] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053a9e0[0];
    FUN_0035b940(&obj.w[6], -1);
    FUN_0035b8c0(&obj.w[5], -1);
    FUN_0033f560(&obj.w[4], -1);
    FUN_00231030(&obj, 0);
    return r;
}
