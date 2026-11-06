/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
union U { int vt; char b[48]; };
extern "C" {
int igObject_Destroy(int *);
int igObject_InitHeader(char *);
extern int DAT_00539e90[4];
extern int DAT_0053c550[4];
extern void * DAT_00586dc8[4];
int beNDMWGameRamInfoRam_GetVTable(void);
}
int beNDMWGameRamInfoRam_GetVTable(void) {
    union U u;
    int temp_s0;
    char *q1;
    int *a0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00539e90[0];
    q1 = &u.b[40];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_0053c550[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00539e90[0];
    if (q1 != 0) {
        a0 = *(int **)q1;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    return temp_s0;
}
