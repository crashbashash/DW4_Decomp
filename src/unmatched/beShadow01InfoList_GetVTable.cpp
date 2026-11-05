/* 0x00344a50 - beShadow01InfoList_GetVTable. Stack object, vtable slot read through the object plus a runtime offset. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
typedef struct { int *vt; int pad[7]; } Obj;
extern "C" {
int igObject_InitHeader(Obj *);
extern int DAT_005391b0[4];
extern void * DAT_00586dc8[4];
int beShadow01InfoList_GetVTable(void);
}
int beShadow01InfoList_GetVTable(void) {
    Obj o;

    igObject_InitHeader(&o);
    o.vt = &DAT_005391b0[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
