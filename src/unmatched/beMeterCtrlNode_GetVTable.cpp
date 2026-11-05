/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_00195190(int *, int);
int FUN_00195a90(struct Obj *, int);
extern int DAT_00537120[4];
extern void * DAT_00586dc8[4];
int beMeterCtrlNode_GetVTable(void);
}
int beMeterCtrlNode_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.vt = &DAT_00537120[0];
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00537120[0];
    FUN_00195190(&obj.w9, -1);
    FUN_00195a90(&obj, 0);
    return t;
}
