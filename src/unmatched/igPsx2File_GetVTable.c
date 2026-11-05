struct F { int *vt; int w[19]; };
int igObject_InitHeader(struct F *);
int FUN_00130720(void *, int);
int FUN_002c0790(struct F *, int);
extern int DAT_0052dc00[4];
extern void * DAT_00586dc8[4];
int igPsx2File_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.w[2] = 0;
    f.w[9] = 0;
    f.vt = &DAT_0052dc00[0];
    f.w[17] = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_0052dc00[0];
    FUN_00130720(&f.w[17], -1);
    FUN_002c0790(&f, 0);
    return temp_s0;
}
