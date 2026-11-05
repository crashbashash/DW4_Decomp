struct Obj { int *vt; char pad[44]; };
int igObject_InitHeader(struct Obj *);
extern int DAT_00523b20[4];
extern void * DAT_00586dc8[4];
int igFogAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523b20[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
