struct Obj { int *vt; char pad[28]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
extern int DAT_0053c870[4];
extern void * DAT_00586dc8[4];
int beLoadIntf2ComMdlDataList_GetVTable(void);
}
int beLoadIntf2ComMdlDataList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053c870[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
