/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct W { int *vt; int f[11]; };
extern "C" {
int igObject_InitHeader(struct W *);
int FUN_001aa390(int *, int);
int FUN_0033ec80(struct W *, int);
int FUN_00343260(int *, int);
int FUN_0036cc00(int *, int);
extern int DAT_00534270[4];
extern void * DAT_00586dc8[4];
int beAction2Info_GetVTable(void);
}
int beAction2Info_GetVTable(void) {
    struct W o;
    int *p16;
    int r;
    int *p17;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    o.vt = &DAT_00534270[0];
    p16 = &o.f[6];
    *p16 = 0;
    p17 = &o.f[7];
    *p17 = 0;
    o.f[8] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00534270[0];
    FUN_0036cc00(&o.f[8], -1);
    FUN_001aa390(p17, -1);
    FUN_00343260(p16, -1);
    FUN_0033ec80(&o, 0);
    return r;
}
