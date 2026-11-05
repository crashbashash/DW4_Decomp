struct Obj { int *vt; char pad[4]; };
int igObject_InitHeader(struct Obj *);
extern int DAT_00528040[4];
extern void * DAT_00586dc8[4];
int igVectorBlending_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00528040[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
