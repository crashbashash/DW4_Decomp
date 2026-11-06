struct Obj { int *vt; char pad[28]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
extern int DAT_0053cd30[4];
extern void * DAT_00586dc8[4];
int beNDMWLoadSavePlWorkList_GetVTable(void);
}
int beNDMWLoadSavePlWorkList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053cd30[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
