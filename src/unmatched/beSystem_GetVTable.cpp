/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_001489a0(int *, int);
int ObjectRef_Destruct_001c6460(int *, int);
int FUN_001d35d0(int *, int);
int FUN_001d36d0(int *, int);
int FUN_00229350(int *, int);
int FUN_00231030(struct Obj *, int);
int FUN_00342eb0(int *, int);
int StringRef_Destruct_00130720(int *, int);
extern int DAT_0053b510[4];
extern void * DAT_00586dc8[4];
int beSystem_GetVTable(void);
}
int beSystem_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_0053b510[0];
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.w20 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053b510[0];
    FUN_00229350(&obj.w20, -1);
    FUN_001d35d0(&obj.w19, -1);
    FUN_001489a0(&obj.w18, -1);
    FUN_001d36d0(&obj.w17, -1);
    StringRef_Destruct_00130720(&obj.w15, -1);
    StringRef_Destruct_00130720(&obj.w14, -1);
    ObjectRef_Destruct_001c6460(&obj.w13, -1);
    FUN_00342eb0(&obj.w12, -1);
    FUN_00231030(&obj, 0);
    return t;
}
