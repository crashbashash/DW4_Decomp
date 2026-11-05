/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; int f20; int f24; int f28; int f2C; int f30; int f34; int f38; int f3C; int f40; int f44; int f48; int f4C; int f50; int f54; int f58; int f5C; int f60; int f64; int f68; int f6C; int f70; int f74; int f78; int f7C; };
extern "C" {
int FUN_003b4050(struct Obj *, int);
int StringRef_Destruct_00130720(int *, int);
int igObject_InitHeader(struct Obj *);
extern int DAT_00540290[4];
extern void * DAT_00586dc8[4];
int beNDMWShopSelect00_GetVTable(void);
}
int beNDMWShopSelect00_GetVTable(void) {
    struct Obj obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f34 = 0;
    obj.f38 = 0;
    obj.f3C = 0;
    obj.f40 = 0;
    obj.f44 = 0;
    obj.f48 = 0;
    obj.f4C = 0;
    obj.f50 = 0;
    obj.f6C = 0;
    obj.vt = (&DAT_00540290[0]);
    obj.f70 = 0;
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_00540290[0]);
    StringRef_Destruct_00130720(&obj.f70, -1);
    FUN_003b4050(&obj, 0);
    return temp_s0;
}
