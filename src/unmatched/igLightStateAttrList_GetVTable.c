/* Stack object, vtable slot read through the object plus a runtime offset. Matches only with the
 * alternate (combat) compiler build. */
typedef struct { int *vt; int pad[7]; } Obj;
int igObject_InitHeader();
extern int DAT_005247a0[4];
extern void * DAT_00586dc8[4];
int igLightStateAttrList_GetVTable(void) {
    Obj o;

    igObject_InitHeader(&o);
    o.vt = &DAT_005247a0[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
