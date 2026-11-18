igMetaObject *g_igNonRefCountedTransformList_metaObject;

igMetaObject *igNonRefCountedTransformList_GetOrCreateMetaObject(void) {
    if (g_igNonRefCountedTransformList_metaObject == 0) {
        g_igNonRefCountedTransformList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igNonRefCountedTransformList_metaObject;
}

igMetaObject *igNonRefCountedTransformList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedTransformList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNonRefCountedTransformList_EnsureRegistered();
    return g_igNonRefCountedTransformList_metaObject;
}

int igNonRefCountedTransformList_GetVTable(void) {
    union U u;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igNonRefCountedTransformList_vtable[0];
    return *(int *)&u.b[g_objectSystem->vtableProbeOffset];
}

void igNonRefCountedTransformList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedTransformList_Register);
}

static igMetaObjectCallback g_igNonRefCountedTransformList_callbackList[] = { igTransform_EnsureRegistered, 0 };

CallbackArray *igNonRefCountedTransformList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igNonRefCountedTransformList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        igNonRefCountedTransformList_GetMetaObjectFunction,
        "igNonRefCountedTransformList",
        0x14, /* instance size */
        igNonRefCountedTransformList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedTransformList_callbackList /* callback list */
    );
}

void igNonRefCountedTransformList_GetMetaObjectFunction(void) {
    igNonRefCountedTransformList_GetMetaObject();
}

