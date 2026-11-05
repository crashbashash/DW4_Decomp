struct Obj { int *vt; int pad[2]; };
struct F { struct Obj obj; int *ref; int pad[12]; };
int igMetaField_Init(struct F *);
int StringChunk_ReleaseHeader();
extern int DAT_0052e130[4];
extern int DAT_0052f230[4];
extern void * DAT_00586dc8[4];
int igVirtualCFuncMetaField_GetVTable(void) {
    struct F f;
    int temp_s0;
    int *temp_a1;
    int temp_v0;

    igMetaField_Init(&f);
    f.obj.vt = &DAT_0052e130[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.obj.vt = &DAT_0052f230[0];
    if (&f.ref != 0) {
        if (f.ref != 0) {
            temp_a1 = f.ref - 2;
            temp_v0 = f.ref[-1] - 1;
            f.ref[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}
