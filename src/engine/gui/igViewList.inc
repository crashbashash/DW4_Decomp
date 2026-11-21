igMetaObject *g_igViewList_metaObject;

igMetaObject *igViewList_GetOrCreateMetaObject(void) {
    if (g_igViewList_metaObject == 0) {
        g_igViewList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igViewList_metaObject;
}

igMetaObject *igViewList_GetMetaObject(void)
{
    igMetaObject *g = g_igViewList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igViewList_EnsureRegistered();
    return g_igViewList_metaObject;
}

int igViewList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igViewList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igViewList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igViewList_Register);
}

static igMetaObjectCallback g_igViewList_callbackList[] = { igView_EnsureRegistered, 0 };

CallbackArray *igViewList_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igViewList_GetMetaObjectFunction,
        "igViewList",
        0x14, /* instance size */
        igViewList_GetVTable,
        0,
        0, /* extra callback item */
        g_igViewList_callbackList /* callback list */
    );
}

void igViewList_GetMetaObjectFunction(void) {
    igViewList_GetMetaObject();
}

