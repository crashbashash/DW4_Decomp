igMetaObject *g_igTextureList_metaObject;

igTextureList *igTextureList_CreateInstance(int allocator) {
    igTextureList_EnsureRegistered();
    return (igTextureList *)igMetaObject_CreateInstance(g_igTextureList_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igTextureList_GetOrCreateMetaObject(void) {
    if (g_igTextureList_metaObject == 0) {
        g_igTextureList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTextureList_metaObject;
}

igMetaObject *igTextureList_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTextureList_EnsureRegistered();
    return g_igTextureList_metaObject;
}

int igTextureList_GetVTable(void) {
    struct Obj_13a400 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igTextureList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igTextureList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureList_Register);
}

static igMetaObjectCallback g_igTextureList_callbackList[] = { igTextureAttr_EnsureRegistered, 0 };

CallbackArray *igTextureList_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igTextureList_GetMetaObjectFunction,
        "igTextureList",
        0x14, /* instance size */
        igTextureList_GetVTable,
        0,
        0, /* extra callback item */
        g_igTextureList_callbackList /* callback list */
    );
}

void igTextureList_GetMetaObjectFunction(void) {
    igTextureList_GetMetaObject();
}

