/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w[11]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_00361b00(struct Obj *, int);
extern int DAT_005359b0[4];
extern void * DAT_00586dc8[4];
int beFontImage_GetVTable(void);
}
int beFontImage_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[4] = 0;
    obj.w[6] = 0;
    obj.w[7] = 0;
    obj.vt = &DAT_005359b0[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_005359b0[0];
    FUN_00361b00(&obj, 0);
    return r;
}
