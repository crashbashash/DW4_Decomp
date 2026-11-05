struct Obj { int *vt; char pad[8]; char *m; char pad2[48]; };
int igMetaField_Init(struct Obj *);
int StringChunk_ReleaseHeader();
extern int DAT_005274e0[4];
extern int DAT_0052f230[4];
extern void * DAT_00586dc8[4];
int igVec3fMetaField_GetVTable(void) {
    struct Obj obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igMetaField_Init(&obj);
    obj.vt = &DAT_005274e0[0];
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
