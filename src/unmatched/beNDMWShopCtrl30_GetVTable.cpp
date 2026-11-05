/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct F { int *vt; int w[23]; };
extern "C" {
int igObject_InitHeader(struct F *);
int FUN_003b6430(struct F *, int);
extern int DAT_0053fdf0[4];
extern void * DAT_00586dc8[4];
int beNDMWShopCtrl30_GetVTable(void);
}
int beNDMWShopCtrl30_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[12] = 0;
    f.w[13] = 0;
    f.w[14] = 0;
    f.w[15] = 0;
    f.w[16] = 0;
    f.w[17] = 0;
    f.w[18] = 0;
    f.vt = &DAT_0053fdf0[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_0053fdf0[0];
    FUN_003b6430(&f, 0);
    return temp_s0;
}
