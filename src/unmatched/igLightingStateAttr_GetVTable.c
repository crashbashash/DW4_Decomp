/* stack-object GetVTable accessor.py. */
int igObject_InitHeader(void *);
extern int DAT_005235e0[4];
extern void * DAT_00586dc8[4];
struct Obj { int *vt; char pad[8]; };
int igLightingStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_005235e0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
