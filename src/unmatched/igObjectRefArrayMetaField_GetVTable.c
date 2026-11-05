typedef struct { int *vt; int p1; int p2; void *str; int pad[12]; void *str2; int pad2[3]; } Obj;
int igObjectRefMetaField_Init();
int StringChunk_ReleaseHeader();
extern int DAT_0052ef40[4];
extern int DAT_00532c80[4];
extern int DAT_0052f230[4];
extern void * DAT_00586dc8[4];
int igObjectRefArrayMetaField_GetVTable(void) {
    Obj o;
    int r;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;
    int *temp_a1_2;
    int temp_v0_2;
    void *temp_v1_2;

    igObjectRefMetaField_Init(&o);
    o.vt = &DAT_0052ef40[0];
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00532c80[0];
    if (&o.str2 != 0) {
        temp_v1 = o.str2;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    o.vt = &DAT_0052f230[0];
    if (&o.str != 0) {
        temp_v1_2 = o.str;
        if (temp_v1_2 != 0) {
            temp_a1_2 = (int *)((char *)temp_v1_2 - 8);
            temp_v0_2 = *(int *)((char *)(temp_v1_2) - 4) - 1;
            *(int *)((char *)(temp_v1_2) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
            }
        }
    }
    return r;
}
