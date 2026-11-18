igMetaObject *g_igImageMipMapList_metaObject;

igMetaObject *igImageMipMapList_GetOrCreateMetaObject(void) {
    if (g_igImageMipMapList_metaObject == 0) {
        g_igImageMipMapList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igImageMipMapList_metaObject;
}

igMetaObject *igImageMipMapList_GetMetaObject(void)
{
    igMetaObject *g = g_igImageMipMapList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igImageMipMapList_EnsureRegistered();
    return g_igImageMipMapList_metaObject;
}

int igImageMipMapList_GetVTable(void) {
    Obj_133090 o;

    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igImageMipMapList_vtable[0];
    return *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
}

void igImageMipMapList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igImageMipMapList_Register);
}

static igMetaObjectCallback g_igImageMipMapList_callbackList[] = { igImage_EnsureRegistered, 0 };

CallbackArray *igImageMipMapList_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igImageMipMapList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igImageMipMapList_GetMetaObjectFunction,
        "igImageMipMapList",
        0x14, /* instance size */
        igImageMipMapList_GetVTable,
        0,
        0, /* extra callback item */
        g_igImageMipMapList_callbackList /* callback list */
    );
}

void igImageMipMapList_GetMetaObjectFunction(void) {
    igImageMipMapList_GetMetaObject();
}

