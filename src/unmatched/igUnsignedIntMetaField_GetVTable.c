/* 0x002b6e90 - igUnsignedIntMetaField_GetVTable. temporary stack object as a union (byte index folds into the load), alternate compiler -O3 Verified byte-identical by tools/verify.py. */
int StringChunk_ReleaseHeader();
int igUnsignedIntMetaField_Init();
extern int DAT_0052f230[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[16]; void *p[16]; char b[64]; };
int igUnsignedIntMetaField_GetVTable(void) {
    union U u;
    int *temp_a1;
    int temp_s0;
    int temp_v0;
    void *temp_v1;

    igUnsignedIntMetaField_Init(u.b);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052f230[0]);
    if (&u.p[3] != 0) {
        temp_v1 = (void *)(u.p[3]);
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

