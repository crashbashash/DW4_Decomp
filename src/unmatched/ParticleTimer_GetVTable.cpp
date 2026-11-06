/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_0019d120(struct Obj *, int);
extern int DAT_0053b7f0[4];
extern void * DAT_00586dc8[4];
int ParticleTimer_GetVTable(void);
}
int ParticleTimer_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w10 = 0;
    obj.vt = &DAT_0053b7f0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053b7f0[0];
    FUN_0019d120(&obj, 0);
    return t;
}
