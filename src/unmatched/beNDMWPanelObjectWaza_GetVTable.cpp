/* 0x003be980 — beNDMWPanelObjectWaza_GetVTable. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8).
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_0014aa70(int *, int);
int FUN_003be240(struct Obj *, int);
int ObjectRef_Destruct_00150eb0(int *, int);
extern int DAT_0053e1a0[4];
extern void * DAT_00586dc8[4];
int beNDMWPanelObjectWaza_GetVTable(void);
}
int beNDMWPanelObjectWaza_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w9 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.vt = &DAT_0053e1a0[0];
    obj.w15 = 0;
    obj.w16 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053e1a0[0];
    ObjectRef_Destruct_00150eb0(&obj.w16, -1);
    FUN_0014aa70(&obj.w15, -1);
    FUN_003be240(&obj, 0);
    return t;
}
