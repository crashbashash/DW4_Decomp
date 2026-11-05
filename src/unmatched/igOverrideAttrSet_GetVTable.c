struct F { int *vt; int w[11]; };
int igObject_InitHeader(struct F *);
int FUN_0019c0e0(struct F *, int);
extern int DAT_0052ac70[4];
extern void * DAT_00586dc8[4];
int igOverrideAttrSet_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.w[2] = 0;
    f.w[3] = 0;
    f.w[6] = 0;
    f.w[7] = 0;
    f.vt = &DAT_0052ac70[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_0052ac70[0];
    FUN_0019c0e0(&f, 0);
    return temp_s0;
}
