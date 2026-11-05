struct Obj { int *vt; char pad[44]; };
int igObject_InitHeader(struct Obj *);
extern int DAT_00522a10[4];
extern void * DAT_00586dc8[4];
int igTextureFunctionAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00522a10[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
