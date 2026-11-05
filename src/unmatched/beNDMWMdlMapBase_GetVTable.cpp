/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; int f20; int f24; int f28; int f2C; };
extern "C" {
int FUN_003bf2f0(struct Obj *, int);
int igObject_InitHeader(struct Obj *);
extern int DAT_00540a70[4];
extern void * DAT_00586dc8[4];
int beNDMWMdlMapBase_GetVTable(void);
}
int beNDMWMdlMapBase_GetVTable(void) {
    struct Obj obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f18 = 0;
    obj.vt = (&DAT_00540a70[0]);
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_00540a70[0]);
    FUN_003bf2f0(&obj, 0);
    return temp_s0;
}
