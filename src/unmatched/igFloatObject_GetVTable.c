struct Obj { int *vt; char pad[12]; };
int igObject_InitHeader(struct Obj *);
extern int DAT_0052bb50[4];
extern void * DAT_00586dc8[4];
int igFloatObject_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052bb50[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
