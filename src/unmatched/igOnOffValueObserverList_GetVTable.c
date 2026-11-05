/* 0x0044c920 - igOnOffValueObserverList_GetVTable. Stack object, vtable slot read through the object plus a runtime offset. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
typedef struct { int *vt; int pad[7]; } Obj;
int igObject_InitHeader();
extern int DAT_00541d00[4];
extern void * DAT_00586dc8[4];
int igOnOffValueObserverList_GetVTable(void) {
    Obj o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00541d00[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
