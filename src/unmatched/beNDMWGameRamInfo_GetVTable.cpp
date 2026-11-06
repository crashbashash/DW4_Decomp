struct F { int *vt; int w[7]; };
extern "C" {
int igObject_InitHeader(struct F *);
int FUN_0033ec80(struct F *, int);
extern int DAT_0053c4e0[4];
extern void * DAT_00586dc8[4];
int beNDMWGameRamInfo_GetVTable(void);
}
int beNDMWGameRamInfo_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.w[4] = 0;
    f.w[5] = 0;
    f.vt = &DAT_0053c4e0[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_0053c4e0[0];
    FUN_0033ec80(&f, 0);
    return temp_s0;
}
