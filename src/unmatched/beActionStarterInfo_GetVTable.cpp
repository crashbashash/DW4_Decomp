/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int p4; int f8; int pc; int p10; int f14; int f18; int f1c; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_0036b430(int *, int);
int FUN_0033ec80(struct Obj *, int);
extern int DAT_00534610[4];
extern void * DAT_00586dc8[4];
int beActionStarterInfo_GetVTable(void);
}
int beActionStarterInfo_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.vt = &DAT_00534610[0];
    obj.f1c = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00534610[0];
    FUN_0036b430(&obj.f1c, -1);
    FUN_0033ec80(&obj, 0);
    return t;
}
