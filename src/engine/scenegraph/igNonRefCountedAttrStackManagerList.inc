int FUN_001a51d0(int arg0) {
    FUN_001a52a0();
    return igMetaObject_CreateInstance((int)g_igNonRefCountedAttrStackManagerList_metaObject, arg0);
}

igMetaObject *g_igNonRefCountedAttrStackManagerList_metaObject;

igMetaObject *igNonRefCountedAttrStackManagerList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedAttrStackManagerList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a52a0();
    return g_igNonRefCountedAttrStackManagerList_metaObject;
}

int igNonRefCountedAttrStackManagerList_GetVTable(void) {
    struct Obj_1a5260 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052a230[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001a52a0(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedAttrStackManagerList_Register);
}

static igMetaObjectCallback g_igNonRefCountedAttrStackManagerList_callbackList[] = { FUN_001a5640, 0 };

void igNonRefCountedAttrStackManagerList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igNonRefCountedAttrStackManagerList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedAttrStackManagerList_GetMetaObject,
        "igNonRefCountedAttrStackManagerList",
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

