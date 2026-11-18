igMetaObject *g_igTransformStack_metaObject;

igMetaObject *igTransformStack_GetOrCreateMetaObject(void) {
    if (g_igTransformStack_metaObject == 0) {
        g_igTransformStack_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTransformStack_metaObject;
}

igMetaObject *igTransformStack_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformStack_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTransformStack_EnsureRegistered();
    return g_igTransformStack_metaObject;
}

int igTransformStack_GetVTable(void) {
    struct Obj_196080 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igTransformStack_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igTransformStack_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTransformStack_Register);
}

static igMetaObjectCallback g_igTransformStack_callbackList[] = { igTransform_EnsureRegistered, 0 };

CallbackArray *igTransformStack_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTransformStack_metaObject,
        igNonRefCountedObjectStack_Register,
        igNonRefCountedObjectStack_GetPublishedMetaObject,
        igTransformStack_GetMetaObjectFunction,
        "igTransformStack",
        0x14, /* instance size */
        igTransformStack_GetVTable,
        0,
        0, /* extra callback item */
        g_igTransformStack_callbackList /* callback list */
    );
}

void igTransformStack_GetMetaObjectFunction(void) {
    igTransformStack_GetMetaObject();
}

