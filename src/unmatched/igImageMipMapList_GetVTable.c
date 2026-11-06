/* Stack object, vtable slot read through the object plus a runtime offset. Matches only with the
 * alternate (combat) compiler build. */
typedef struct { int *vt; int pad[7]; } Obj;
int igObject_InitHeader();
extern int DAT_005248e0[4];
extern void * DAT_00586dc8[4];
int igImageMipMapList_GetVTable(void) {
    Obj o;

    igObject_InitHeader(&o);
    o.vt = &DAT_005248e0[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
