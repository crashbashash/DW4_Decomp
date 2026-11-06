/* Stack-object GetVTable accessor. */
int igObject_InitHeader(void *);
extern int DAT_00523c20[4];
extern void * DAT_00586dc8[4];
struct Obj { int *vt; char pad[8]; };
int igDepthWriteStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523c20[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
