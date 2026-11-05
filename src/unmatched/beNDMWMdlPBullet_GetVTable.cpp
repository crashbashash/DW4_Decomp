/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct F { int *vt; int w[11]; };
extern "C" {
int igObject_InitHeader(struct F *);
int FUN_003bf2f0(struct F *, int);
extern int DAT_0053e550[4];
extern void * DAT_00586dc8[4];
int beNDMWMdlPBullet_GetVTable(void);
}
int beNDMWMdlPBullet_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.w[5] = 0;
    f.vt = &DAT_0053e550[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_0053e550[0];
    FUN_003bf2f0(&f, 0);
    return temp_s0;
}
