typedef struct { int *vt; int p1[2]; int *ref; int pad[0]; } Obj;
int igObject_InitHeader();
int igObject_Destroy();
extern int DAT_00529080[4];
extern void * DAT_00586dc8[4];
int igEnbayaTransformSource_GetVTable(void) {
    Obj o;
    int **ps;
    int *temp_a0;
    int temp_s0;

    igObject_InitHeader(&o);
    ps = &o.ref;
    o.vt = &DAT_00529080[0];
    *ps = 0;
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00529080[0];
    if (ps != 0) {
        temp_a0 = *ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}
