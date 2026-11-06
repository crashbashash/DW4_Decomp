int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_0052a160[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[16]; void *p[16]; char b[64]; };
int igAttrStack_GetVTable(void) {
    union U u;
    void **q5;
    int temp_s0;
    void *temp_a0;

    igObject_InitHeader(u.b);
    q5 = &u.p[5];
    u.w[0] = (int)(&DAT_0052a160[0]);
    *q5 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052a160[0]);
    if (q5 != 0) {
        temp_a0 = *q5;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

