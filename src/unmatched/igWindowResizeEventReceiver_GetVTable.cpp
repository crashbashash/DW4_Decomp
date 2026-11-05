extern "C" {
int igObject_InitHeader(void *);
extern int DAT_0052c9f0[4];
extern void *DAT_00586dc8[4];
struct Obj { int *vt; char pad[12]; };
int igWindowResizeEventReceiver_GetVTable(void) {
    struct Obj o;
    igObject_InitHeader(&o);
    o.vt = &DAT_0052c9f0[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
}
