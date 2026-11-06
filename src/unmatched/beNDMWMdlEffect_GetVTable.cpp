/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w[11]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_003bf2f0(struct Obj *, int);
extern int DAT_0053e2e0[4];
extern void * DAT_00586dc8[4];
int beNDMWMdlEffect_GetVTable(void);
}
int beNDMWMdlEffect_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_0053e2e0[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053e2e0[0];
    FUN_003bf2f0(&obj, 0);
    return r;
}
