struct F { int *vt; int pad[2]; int *ref; int pad2[4]; };
int igObject_InitHeader(struct F *);
int igObject_Destroy();
extern int DAT_00538d40[4];
extern void * DAT_00586dc8[4];
int beSvPlatBaseData_GetVTable(void) {
    struct F f;
    int **pr;
    int temp_s0;
    int *o;

    igObject_InitHeader(&f);
    f.vt = &DAT_00538d40[0];
    pr = &f.ref;
    *pr = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_00538d40[0];
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
