igMetaObject *g_igNodeListList_metaObject;

igMetaObject *FUN_0019ca30(void) {
    if (g_igNodeListList_metaObject == 0) {
        g_igNodeListList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igNodeListList_metaObject;
}

igMetaObject *igNodeListList_GetMetaObject(void)
{
    igMetaObject *g = g_igNodeListList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019cb10();
    return g_igNodeListList_metaObject;
}

int igNodeListList_GetVTable(void) {
    Obj_19cad0 o;

    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igNodeListList_vtable[0];
    return *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
}

void FUN_0019cb10(void)
{
    igMetaObject_RunStaticInit(igNodeListList_Register);
}

static igMetaObjectCallback g_igNodeListList_callbackList[] = { igNodeList_EnsureRegistered, 0 };

CallbackArray *igNodeListList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igNodeListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igNodeListList_GetMetaObject,
        "igNodeListList",
        0x14, /* instance size */
        igNodeListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNodeListList_callbackList /* callback list */
    );
}

void thunk_igNodeListList_GetMetaObject(void) {
    igNodeListList_GetMetaObject();
}

