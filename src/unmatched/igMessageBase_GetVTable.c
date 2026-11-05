/* 0x00226500 - igMessageBase_GetVTable. Stack object, vtable slot read through the object plus a runtime offset. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
typedef struct { int *vt; int pad[7]; } Obj;
int igObject_InitHeader();
extern int DAT_0052c6e0[4];
extern void * DAT_00586dc8[4];
int igMessageBase_GetVTable(void) {
    Obj o;

    igObject_InitHeader(&o);
    o.vt = &DAT_0052c6e0[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
