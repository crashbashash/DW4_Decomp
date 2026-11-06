/* Stack object, vtable slot read through the object plus a runtime offset. */
typedef struct { int *vt; int pad[7]; } Obj;
extern "C" {
int igObject_InitHeader(Obj *);
extern int DAT_0053cba0[4];
extern void * DAT_00586dc8[4];
int beNDMWMcSlotGC_GetVTable(void);
}
int beNDMWMcSlotGC_GetVTable(void) {
    Obj o;

    igObject_InitHeader(&o);
    o.vt = &DAT_0053cba0[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
