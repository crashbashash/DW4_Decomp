struct F { int *vt; int w[11]; };
extern "C" {
int igObject_InitHeader(struct F *);
int FUN_00130720(void *, int);
int FUN_001d97f0(void *, int);
int FUN_00344030(struct F *, int);
extern int DAT_00535b70[4];
extern void * DAT_00586dc8[4];
int beFontInfoData_GetVTable(void);
}
int beFontInfoData_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.vt = &DAT_00535b70[0];
    f.w[3] = 0;
    f.w[9] = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_00535b70[0];
    FUN_00130720(&f.w[9], -1);
    FUN_001d97f0(&f.w[3], -1);
    FUN_00344030(&f, 0);
    return temp_s0;
}
