/* 0x002be6b0 - igMetaObject_GetVTable. temporary stack object as a union (byte index folds into the load), alternate compiler -O3 Verified byte-identical by tools/verify.py. */
int StringChunk_ReleaseHeader();
int igMetaObject_Init();
extern int DAT_00532bb0[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[28]; void *p[28]; char b[112]; };
int igMetaObject_GetVTable(void) {
    union U u;
    int *temp_a1;
    int *temp_a1_2;
    int temp_s0;
    int temp_v0;
    int temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;

    igMetaObject_Init(u.b);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00532bb0[0]);
    if (&u.p[24] != 0) {
        temp_v1 = (void *)(u.p[24]);
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    if (&u.p[7] != 0) {
        temp_v1_2 = (void *)(u.p[7]);
        if (temp_v1_2 != 0) {
            temp_a1_2 = (int *)((char *)temp_v1_2 - 8);
            temp_v0_2 = *(int *)((char *)(temp_v1_2) - 4) - 1;
            *(int *)((char *)(temp_v1_2) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
            }
        }
    }
    return temp_s0;
}

