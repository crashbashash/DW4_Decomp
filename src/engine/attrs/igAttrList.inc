igMetaObject *g_igAttrList_metaObject;

igAttrList *igAttrList_Create(igMemoryPoolView *pool) {
    igAttrList_EnsureRegistered();
    return (igAttrList *)igMetaObject_CreateInstance(g_igAttrList_metaObject, pool);
}

igMetaObject *igAttrList_GetOrCreateMetaObject(void) {
    if (g_igAttrList_metaObject == 0) {
        g_igAttrList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAttrList_metaObject;
}

igMetaObject *igAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAttrList_EnsureRegistered();
    return g_igAttrList_metaObject;
}

int igAttrList_GetVTable(void) {
    struct Obj_13afa0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igAttrList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igAttrList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAttrList_Register);
}

static igMetaObjectCallback g_igAttrList_callbackList[] = { igAttr_EnsureRegistered, 0 };

CallbackArray *igAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igAttrList_GetMetaObjectFunction,
        "igAttrList",
        0x14, /* instance size */
        igAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAttrList_callbackList /* callback list */
    );
}

void igAttrList_GetMetaObjectFunction(void) {
    igAttrList_GetMetaObject();
}

