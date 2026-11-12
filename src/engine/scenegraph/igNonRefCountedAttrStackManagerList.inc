int FUN_001a51d0(int arg0) {
    FUN_001a52a0();
    return igMetaObject_CreateInstance(*(int *)0x561F90, arg0);
}

igMetaObject *igNonRefCountedAttrStackManagerList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedAttrStackManagerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a52a0();
    return g_igNonRefCountedAttrStackManagerList_metaObject[0];
}

int igNonRefCountedAttrStackManagerList_GetVTable(void) {
    struct Obj_1a5260 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052a230[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001a52a0(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedAttrStackManagerList_Register);
}

void igNonRefCountedAttrStackManagerList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igNonRefCountedAttrStackManagerList_metaObject),
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedAttrStackManagerList_GetMetaObject,
        igNonRefCountedAttrStackManagerList_className,
        0x14, /* instance size */
        igNonRefCountedAttrStackManagerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedAttrStackManagerList_callbackList /* callback list */
    );
}

void thunk_igNonRefCountedAttrStackManagerList_GetMetaObject(void) {
    igNonRefCountedAttrStackManagerList_GetMetaObject();
}

