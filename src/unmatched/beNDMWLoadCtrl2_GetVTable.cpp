/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w[11]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_0033dda0(void *, int);
int FUN_0033f5e0(void *, int);
extern int DAT_0053e900[4];
extern void * DAT_00586dc8[4];
int beNDMWLoadCtrl2_GetVTable(void);
}
int beNDMWLoadCtrl2_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_0053e900[0];
    obj.w[7] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053e900[0];
    FUN_0033dda0(&obj.w[7], -1);
    FUN_0033f5e0(&obj, 0);
    return r;
}
