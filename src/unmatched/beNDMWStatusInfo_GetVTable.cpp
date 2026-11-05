/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w[7]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_0033ec80(struct Obj *, int);
extern int DAT_0053dbc0[4];
extern void * DAT_00586dc8[4];
int beNDMWStatusInfo_GetVTable(void);
}
int beNDMWStatusInfo_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_0053dbc0[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053dbc0[0];
    FUN_0033ec80(&obj, 0);
    return r;
}
