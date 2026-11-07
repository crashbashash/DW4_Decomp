struct F { int *vt; int pad[1]; int *ref; int pad2[9]; };
extern "C" {
int igObject_InitHeader(struct F *);
int StringChunk_ReleaseHeader(int, int *);
extern int DAT_00537e20[4];
extern int DAT_00537e20[4];
extern void * DAT_00586dc8[4];
int beModelCtrlInfoAI_GetVTable(void);
}
int beModelCtrlInfoAI_GetVTable(void) {
    struct F f;
    int **pr;
    int temp_s0;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(&f);
    f.vt = &DAT_00537e20[0];
    pr = &f.ref;
    *pr = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_00537e20[0];
    if (pr != 0) {
        if (*pr != 0) {
            temp_a1 = *pr - 2;
            temp_v0 = (*pr)[-1] - 1;
            (*pr)[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}
