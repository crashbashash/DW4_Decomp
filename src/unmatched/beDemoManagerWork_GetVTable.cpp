union U { int vt; char b[16]; };
extern "C" {
int igObject_InitHeader(char *);
int igObject_Destroy(int *);
extern int DAT_005356e0[4];
extern void * DAT_00586dc8[4];
int beDemoManagerWork_GetVTable(void);
}
int beDemoManagerWork_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    int *temp_a0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_005356e0[0];
    ps = &u.b[12];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_005356e0[0];
    if (ps != 0) {
        temp_a0 = *(int **)ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}
