struct Obj { int *vt; char pad[28]; };
int igObject_InitHeader(struct Obj *);
extern int DAT_00531a50[4];
extern void * DAT_00586dc8[4];
int igCharListNoClean_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00531a50[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
