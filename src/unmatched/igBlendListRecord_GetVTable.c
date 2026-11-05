/* 0x001a2d00 - igBlendListRecord_GetVTable. union stack object; smart-ref slot through a pointer local assigned after the header init; reference-count field read as int; alternate compiler -O3 Verified byte-identical by tools/verify.py. */
int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_0052a670[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[4]; void *p[4]; char b[16]; };
int igBlendListRecord_GetVTable(void) {
    union U u;
    void **q2;
    int temp_s0;
    void *temp_a0;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    u.w[0] = (int)(&DAT_0052a670[0]);
    *q2 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052a670[0]);
    if (q2 != 0) {
        temp_a0 = *q2;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

