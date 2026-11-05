struct Obj { int *vt; char pad[8]; char *m; char pad2[48]; };
int FUN_0030eb80(struct Obj *);
int StringChunk_ReleaseHeader();
extern int DAT_0052e330[4];
extern int DAT_0052f230[4];
extern void * DAT_00586dc8[4];
int igUnsignedLongArrayMetaField_GetVTable(void) {
    struct Obj obj;
    char *o;
    int *a1;
    int v0;
    int t;
    FUN_0030eb80(&obj);
    obj.vt = &DAT_0052e330[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052f230[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}
