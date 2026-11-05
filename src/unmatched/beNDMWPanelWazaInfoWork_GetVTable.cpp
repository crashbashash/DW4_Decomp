/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; int f20; int f24; int f28; int f2C; };
extern "C" {
int ObjectRef_Destruct_001c6460(int *, int);
int FUN_003bdd00(int *, int);
int FUN_003bdd80(int *, int);
int FUN_003bde00(int *, int);
int FUN_003bde80(int *, int);
int ObjectRef_Destruct_00150eb0(int *, int);
int StringRef_Destruct_00130720(int *, int);
int igObject_InitHeader(struct Obj *);
extern int DAT_0053d5d0[4];
extern void * DAT_00586dc8[4];
int beNDMWPanelWazaInfoWork_GetVTable(void);
}
int beNDMWPanelWazaInfoWork_GetVTable(void) {
    struct Obj obj;
    int temp_s5;

    igObject_InitHeader(&obj);
    obj.vt = (&DAT_0053d5d0[0]);
    obj.f10 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.f20 = 0;
    obj.f24 = 0;
    obj.f28 = 0;
    obj.f2C = 0;
    temp_s5 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_0053d5d0[0]);
    ObjectRef_Destruct_00150eb0(&obj.f2C, -1);
    ObjectRef_Destruct_001c6460(&obj.f28, -1);
    FUN_003bde80(&obj.f24, -1);
    StringRef_Destruct_00130720(&obj.f20, -1);
    FUN_003bde00(&obj.f18, -1);
    FUN_003bdd80(&obj.f14, -1);
    FUN_003bdd00(&obj.f10, -1);
    return temp_s5;
}
