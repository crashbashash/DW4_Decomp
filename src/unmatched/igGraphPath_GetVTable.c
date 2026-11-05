typedef struct { int *vt; int p1[1]; int *ref; int pad[5]; } Obj;
int igObject_InitHeader();
int igObject_Destroy();
extern int DAT_0052a810[4];
extern void * DAT_00586dc8[4];
int igGraphPath_GetVTable(void) {
    Obj o;
    int **ps;
    int *temp_a0;
    int temp_s0;

    igObject_InitHeader(&o);
    ps = &o.ref;
    o.vt = &DAT_0052a810[0];
    *ps = 0;
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0052a810[0];
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
