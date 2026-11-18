igMetaObject *g_igTransformList_metaObject;

igMetaObject *igTransformList_GetOrCreateMetaObject(void) {
    if (g_igTransformList_metaObject == 0) {
        g_igTransformList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTransformList_metaObject;
}

igMetaObject *igTransformList_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTransformList_EnsureRegistered();
    return g_igTransformList_metaObject;
}

int igTransformList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&g_igTransformList_vtable[0];
    off = g_objectSystem->vtableProbeOffset;
    return *(int *)((char *)tmp + off);
}

void igTransformList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTransformList_Register);
}

static igMetaObjectCallback g_igTransformList_callbackList[] = { igTransform_EnsureRegistered, 0 };

CallbackArray *igTransformList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTransformList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igTransformList_GetMetaObject,
        "igTransformList",
        0x14, /* instance size */
        igTransformList_GetVTable,
        0,
        0, /* extra callback item */
        g_igTransformList_callbackList /* callback list */
    );
}

void thunk_igTransformList_GetMetaObject(void) {
    igTransformList_GetMetaObject();
}

