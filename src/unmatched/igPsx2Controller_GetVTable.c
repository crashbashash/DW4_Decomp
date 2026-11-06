int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_00524d00[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[28]; void *p[28]; char b[112]; };
int igPsx2Controller_GetVTable(void) {
    union U u;
    void **q8;
    int temp_s0;
    void *temp_a0;

    igObject_InitHeader(u.b);
    q8 = &u.p[8];
    u.w[0] = (int)(&DAT_00524d00[0]);
    *q8 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00524d00[0]);
    if (q8 != 0) {
        temp_a0 = *q8;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

