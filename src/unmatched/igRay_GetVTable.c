struct Obj { int *vt; char pad[44]; };
int igObject_InitHeader(struct Obj *);
extern int DAT_00527f10[4];
extern void * DAT_00586dc8[4];
int igRay_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00527f10[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
