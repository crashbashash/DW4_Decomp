/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; int f20; int f24; int f28; int f2C; int f30; int f34; int f38; int f3C; int f40; int f44; int f48; int f4C; };
extern "C" {
int FUN_00344030(struct Obj *, int);
int FUN_003b2a10(int *, int);
int FUN_003c4d80(int *, int);
int FUN_003c4e00(int *, int);
int FUN_003c4e80(int *, int);
int igObject_InitHeader(struct Obj *);
extern int DAT_0053ce00[4];
extern void * DAT_00586dc8[4];
int beNDMWLoadCtrl2CommonIntf_GetVTable(void);
}
int beNDMWLoadCtrl2CommonIntf_GetVTable(void) {
    struct Obj obj;
    int temp_s3;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.vt = (&DAT_0053ce00[0]);
    obj.f20 = 0;
    obj.f24 = 0;
    obj.f28 = 0;
    obj.f34 = 0;
    temp_s3 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_0053ce00[0]);
    FUN_003b2a10(&obj.f34, -1);
    FUN_003c4e80(&obj.f28, -1);
    FUN_003c4e00(&obj.f24, -1);
    FUN_003c4d80(&obj.f20, -1);
    FUN_00344030(&obj, 0);
    return temp_s3;
}
