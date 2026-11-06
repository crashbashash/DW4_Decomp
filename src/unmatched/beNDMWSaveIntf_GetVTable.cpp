/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct F { int *vt; int w[11]; };
extern "C" {
int igObject_InitHeader(struct F *);
int FUN_0033dda0(void *, int);
int FUN_0033f5e0(struct F *, int);
extern int DAT_0053eb80[4];
extern void * DAT_00586dc8[4];
int beNDMWSaveIntf_GetVTable(void);
}
int beNDMWSaveIntf_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.w[5] = 0;
    f.vt = &DAT_0053eb80[0];
    f.w[8] = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_0053eb80[0];
    FUN_0033dda0(&f.w[8], -1);
    FUN_0033f5e0(&f, 0);
    return temp_s0;
}
