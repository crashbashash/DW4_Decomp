/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_00131aa0(int *, int);
int FUN_00131b20(struct Obj *, int);
int FUN_00132390(int *, int);
int FUN_001d3650(int *, int);
int FUN_003363c0(int *, int);
int FUN_00336440(int *, int);
int ObjectRef_Destruct_001363f0(int *, int);
int StringRef_Destruct_00130720(int *, int);
extern int DAT_00533910[4];
extern void * DAT_00586dc8[4];
int igMovieInfo_GetVTable(void);
}
int igMovieInfo_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00533910[0];
    obj.w5 = 0;
    obj.w12 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w20 = 0;
    obj.w21 = 0;
    obj.w22 = 0;
    obj.w24 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00533910[0];
    ObjectRef_Destruct_001363f0(&obj.w24, -1);
    FUN_00131aa0(&obj.w22, -1);
    FUN_00132390(&obj.w21, -1);
    FUN_001d3650(&obj.w20, -1);
    FUN_00336440(&obj.w18, -1);
    StringRef_Destruct_00130720(&obj.w17, -1);
    FUN_003363c0(&obj.w12, -1);
    StringRef_Destruct_00130720(&obj.w5, -1);
    FUN_00131b20(&obj, 0);
    return t;
}
