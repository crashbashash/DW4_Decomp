/* igVec2fMetaField_GetVTable: stack object with an inlined smart-pointer release (sibling of igFloatMetaField_GetVTable). */
typedef struct { int *vt; int p1; int p2; void *str; int pad[12]; } Obj;
int igMetaField_Init();
int StringChunk_ReleaseHeader();
extern int DAT_0052f230[4];
extern int DAT_005275e0[4];
extern void * DAT_00586dc8[4];
int igVec2fMetaField_GetVTable(void) {
    Obj o;
    int r;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    igMetaField_Init(&o);
    o.vt = &DAT_005275e0[0];
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0052f230[0];
    if (&o.str != 0) {
        temp_v1 = o.str;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return r;
}
