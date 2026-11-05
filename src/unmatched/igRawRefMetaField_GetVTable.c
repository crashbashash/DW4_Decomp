/* 0x002bbbc0 - igRawRefMetaField_GetVTable. Stack object with an inlined smart-pointer release (no vtable store before the read). Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
typedef struct { int *vt; int p1; int p2; void *str; int pad[12]; } Obj;
int FUN_00305440();
int StringChunk_ReleaseHeader();
extern int DAT_0052f230[4];
extern void * DAT_00586dc8[4];
int igRawRefMetaField_GetVTable(void) {
    Obj o;
    int r;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    FUN_00305440(&o);
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
