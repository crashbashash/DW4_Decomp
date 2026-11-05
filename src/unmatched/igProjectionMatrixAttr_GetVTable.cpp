extern "C" {
int igObject_InitHeader(void *);
int igMatrix44f_SetIdentity(void *);
extern int DAT_005230e0[4];
extern void *DAT_00586dc8[4];
struct Obj { int *vt; char pad[12]; char rest[64]; };
int igProjectionMatrixAttr_GetVTable(void) {
    struct Obj o;
    igObject_InitHeader(&o);
    o.vt = &DAT_005230e0[0];
    igMatrix44f_SetIdentity(&o.pad[8]);
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
}
