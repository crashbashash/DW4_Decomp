int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_00540e30[4];
extern int DAT_00541c40[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[48]; };
int igOnOffModel_GetVTable(void) {
    union U u;
    int temp_s0;
    char *q1;
    void *temp_a0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00540e30[0];
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00541c40[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00540e30[0];
    if (q1 != 0) {
        temp_a0 = *(void **)q1;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}
