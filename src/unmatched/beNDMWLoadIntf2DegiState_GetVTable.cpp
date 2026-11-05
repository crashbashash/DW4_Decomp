extern "C" {
int igObject_InitHeader(void *);
extern int DAT_0053cf90[4];
extern void *DAT_00586dc8[4];
struct Obj { int *vt; char pad[76]; };
int beNDMWLoadIntf2DegiState_GetVTable(void) {
    struct Obj o;
    igObject_InitHeader(&o);
    o.vt = &DAT_0053cf90[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
}
