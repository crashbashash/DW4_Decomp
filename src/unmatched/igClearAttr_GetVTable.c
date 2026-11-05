struct Obj { int *vt; char pad[76]; };
int igObject_InitHeader(struct Obj *);
extern int DAT_00524000[4];
extern void * DAT_00586dc8[4];
int igClearAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524000[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
