/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; int f20; int f24; int f28; int f2C; int f30; int f34; int f38; int f3C; int f40; int f44; int f48; int f4C; int f50; int f54; int f58; int f5C; };
extern "C" {
int FUN_0033f5e0(struct Obj *, int);
int FUN_003b2a10(int *, int);
int igObject_InitHeader(struct Obj *);
extern int DAT_005409d0[4];
extern void * DAT_00586dc8[4];
int beNDMWLogo_GetVTable(void);
}
int beNDMWLogo_GetVTable(void) {
    struct Obj obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f18 = 0;
    obj.vt = (&DAT_005409d0[0]);
    obj.f28 = 0;
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_005409d0[0]);
    FUN_003b2a10(&obj.f28, -1);
    FUN_0033f5e0(&obj, 0);
    return temp_s0;
}
