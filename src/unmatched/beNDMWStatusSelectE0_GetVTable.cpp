/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct W { int *vt; int f[27]; };
extern "C" {
int FUN_003b4050(struct W *, int);
int igObject_InitHeader(struct W *);
extern int DAT_0053f3a0[4];
extern char *DAT_00586dc8[4];
int beNDMWStatusSelectE0_GetVTable(void);
}
int beNDMWStatusSelectE0_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.f[12] = 0;
    o.f[13] = 0;
    o.f[14] = 0;
    o.f[15] = 0;
    o.f[16] = 0;
    o.f[17] = 0;
    o.f[18] = 0;
    o.f[19] = 0;
    o.f[26] = 0;
    o.vt = DAT_0053f3a0;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0053f3a0;
    FUN_003b4050(&o, 0);
    return r;
}
