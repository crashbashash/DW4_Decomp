struct Obj { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; int f20; int f24; int f28; int f2C; };
extern "C" {
int FUN_001958f0(int *, int);
int FUN_00199450(int *, int);
int FUN_0033ec80(struct Obj *, int);
int FUN_0033edb0(int *, int);
int igObject_InitHeader(struct Obj *);
extern int DAT_00539d50[4];
extern void * DAT_00586dc8[4];
int beWeaponInfo_GetVTable(void);
}
int beWeaponInfo_GetVTable(void) {
    struct Obj obj;
    int temp_s2;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.vt = (&DAT_00539d50[0]);
    obj.f1C = 0;
    obj.f20 = 0;
    obj.f24 = 0;
    temp_s2 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_00539d50[0]);
    FUN_0033edb0(&obj.f24, -1);
    FUN_00199450(&obj.f20, -1);
    FUN_001958f0(&obj.f1C, -1);
    FUN_0033ec80(&obj, 0);
    return temp_s2;
}
