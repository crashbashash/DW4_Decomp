igMetaObject *g_igAppearanceList_metaObject;

igMetaObject *igAppearanceList_GetOrCreateMetaObject(void) {
    if (g_igAppearanceList_metaObject == 0) {
        g_igAppearanceList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAppearanceList_metaObject;
}

igMetaObject *igAppearanceList_GetMetaObject(void)
{
    igMetaObject *g = g_igAppearanceList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAppearanceList_EnsureRegistered();
    return g_igAppearanceList_metaObject;
}

int igAppearanceList_GetVTable(void) {
    struct Obj_1a6080 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igAppearanceList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igAppearanceList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAppearanceList_Register);
}

static igMetaObjectCallback g_igAppearanceList_callbackList[] = { igAppearance_EnsureRegistered, 0 };

CallbackArray *igAppearanceList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAppearanceList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igAppearanceList_GetMetaObjectFunction,
        "igAppearanceList",
        0x14, /* instance size */
        igAppearanceList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAppearanceList_callbackList /* callback list */
    );
}

void igAppearanceList_GetMetaObjectFunction(void) {
    igAppearanceList_GetMetaObject();
}

