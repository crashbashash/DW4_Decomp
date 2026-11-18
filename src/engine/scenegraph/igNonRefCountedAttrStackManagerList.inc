int FUN_001a51d0(int arg0) {
    igNonRefCountedAttrStackManagerList_EnsureRegistered();
    return (int)igMetaObject_CreateInstance((igMetaObject *)g_igNonRefCountedAttrStackManagerList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *g_igNonRefCountedAttrStackManagerList_metaObject;

igMetaObject *igNonRefCountedAttrStackManagerList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedAttrStackManagerList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNonRefCountedAttrStackManagerList_EnsureRegistered();
    return g_igNonRefCountedAttrStackManagerList_metaObject;
}

int igNonRefCountedAttrStackManagerList_GetVTable(void) {
    struct Obj_1a5260 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igNonRefCountedAttrStackManagerList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igNonRefCountedAttrStackManagerList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedAttrStackManagerList_Register);
}

static igMetaObjectCallback g_igNonRefCountedAttrStackManagerList_callbackList[] = { igAttrStackManager_EnsureRegistered, 0 };

CallbackArray *igNonRefCountedAttrStackManagerList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igNonRefCountedAttrStackManagerList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        igNonRefCountedAttrStackManagerList_GetMetaObjectFunction,
        "igNonRefCountedAttrStackManagerList",
        0x14, /* instance size */
        igNonRefCountedAttrStackManagerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedAttrStackManagerList_callbackList /* callback list */
    );
}

void igNonRefCountedAttrStackManagerList_GetMetaObjectFunction(void) {
    igNonRefCountedAttrStackManagerList_GetMetaObject();
}

