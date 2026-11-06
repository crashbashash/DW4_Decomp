int StringChunk_ReleaseHeader();
int igObject_InitHeader();
extern int DAT_0052fee0[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[4]; void *p[4]; char b[16]; };
int igFolder_GetVTable(void) {
    union U u;
    void **q;
    int *temp_a1;
    int temp_s0;
    int temp_v0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q = &u.p[2];
    u.w[0] = (int)(&DAT_0052fee0[0]);
    *q = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052fee0[0]);
    if (q != 0) {
        temp_v1 = *q;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

