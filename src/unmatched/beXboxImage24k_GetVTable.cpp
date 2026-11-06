struct Obj { int *vt; char pad[12]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
extern int DAT_00538c20[4];
extern void * DAT_00586dc8[4];
int beXboxImage24k_GetVTable(void);
}
int beXboxImage24k_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538c20[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
