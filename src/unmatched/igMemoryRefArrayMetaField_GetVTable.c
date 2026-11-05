struct Obj { int *vt; int pad[23]; };
int FUN_002bf4c0(struct Obj *, int);
int igMemoryRefMetaField_Init(struct Obj *);
extern int DAT_0052f330[4];
extern void * DAT_00586dc8[4];
int igMemoryRefArrayMetaField_GetVTable(void) {
    struct Obj obj;
    int temp_s0;

    igMemoryRefMetaField_Init(&obj);
    obj.vt = &DAT_0052f330[0];
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052f330[0];
    FUN_002bf4c0(&obj, 0);
    return temp_s0;
}
