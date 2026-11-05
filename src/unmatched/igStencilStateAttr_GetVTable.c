/* stack-object GetVTable accessor; verified by tools/verify.py. */
int igObject_InitHeader(void *);
extern int DAT_00522d90[4];
extern void * DAT_00586dc8[4];
struct Obj { int *vt; char pad[8]; };
int igStencilStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00522d90[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
