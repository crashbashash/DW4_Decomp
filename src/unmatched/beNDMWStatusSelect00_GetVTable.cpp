struct F { int *vt; int w[27]; };
extern "C" {
int igObject_InitHeader(struct F *);
int FUN_003b4050(struct F *, int);
extern int DAT_0053f480[4];
extern void * DAT_00586dc8[4];
int beNDMWStatusSelect00_GetVTable(void);
}
int beNDMWStatusSelect00_GetVTable(void) {
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
    f.w[19] = 0;
    f.w[26] = 0;
    f.vt = &DAT_0053f480[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_0053f480[0];
    FUN_003b4050(&f, 0);
    return temp_s0;
}
