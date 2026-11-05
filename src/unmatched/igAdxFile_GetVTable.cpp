/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_002c0790(struct Obj *, int);
extern int DAT_005337f0[4];
extern void * DAT_00586dc8[4];
int igAdxFile_GetVTable(void);
}
int igAdxFile_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w10 = 0;
    obj.vt = &DAT_005337f0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_005337f0[0];
    FUN_002c0790(&obj, 0);
    return t;
}
