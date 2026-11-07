struct F { int *vt; int pad[1]; int *ref; int pad2[1]; };
extern "C" {
int igObject_InitHeader(struct F *);
int igObject_Destroy(int *);
extern int DAT_005357b0[4];
extern void * DAT_00586dc8[4];
int beFileChkObj_GetVTable(void);
}
int beFileChkObj_GetVTable(void) {
    struct F f;
    int **pr;
    int temp_s0;
    int *o;

    igObject_InitHeader(&f);
    f.vt = &DAT_005357b0[0];
    pr = &f.ref;
    *pr = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_005357b0[0];
    if (pr != 0) {
        if (*pr != 0) {
            o = *pr;
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return temp_s0;
}
