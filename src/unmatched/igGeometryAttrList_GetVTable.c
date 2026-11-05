int igObject_InitHeader();
extern int DAT_005245e0[4];
extern void * DAT_00586dc8[4];
int igGeometryAttrList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_005245e0[0];
    return *(int *)((char *)obj + *(int *)((char *)DAT_00586dc8[0] + 916));
}
