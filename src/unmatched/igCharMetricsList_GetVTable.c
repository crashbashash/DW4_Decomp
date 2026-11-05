/* 0x00452830 - igCharMetricsList_GetVTable. Stack object, vtable slot read through the object plus a runtime offset. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
typedef struct { int *vt; int pad[7]; } Obj;
int igObject_InitHeader();
extern int DAT_00541780[4];
extern void * DAT_00586dc8[4];
int igCharMetricsList_GetVTable(void) {
    Obj o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00541780[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
