/* 0x002b7730 - igUnsignedCharArrayMetaField_GetVTable. Stack object with an inlined smart-pointer release. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
typedef struct { int *vt; int p1; int p2; void *str; int pad[12]; } Obj;
int StringChunk_ReleaseHeader();
int igMetaField_Init();
extern int DAT_0052e630[4];
extern int DAT_0052f230[4];
extern void * DAT_00586dc8[4];
int igUnsignedCharArrayMetaField_GetVTable(void) {
    Obj o;
    int *temp_a1;
    int temp_s0;
    int temp_v0;
    void *temp_v1;

    igMetaField_Init(&o);
    o.vt = &DAT_0052e630[0];
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0052f230[0];
    if (&o.str != 0) {
        temp_v1 = (void *)(o.str);
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
