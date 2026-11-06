/* Stack object, vtable slot read through the object plus a runtime offset. Matches only with the
 * alternate (combat) compiler build. C++ translation unit: the unit compiled with exceptions on
 * and retail keeps this function's exception index record, which only the C++ front end emits. */
typedef struct { int *vt; int pad[7]; } Obj;
extern "C" {
int igObject_InitHeader(Obj *);
extern int DAT_00539b40[4];
extern void * DAT_00586dc8[4];
int igAppearanceListList_GetVTable(void);
}
int igAppearanceListList_GetVTable(void) {
    Obj o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00539b40[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
