/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct Obj { int *vt; char pad[28]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
extern int DAT_00535940[4];
extern void * DAT_00586dc8[4];
int beFontGeomAttrPairList_GetVTable(void);
}
int beFontGeomAttrPairList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535940[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
