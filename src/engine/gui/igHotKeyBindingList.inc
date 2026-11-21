igMetaObject *g_igHotKeyBindingList_metaObject;

igMetaObject *igHotKeyBindingList_GetOrCreateMetaObject(void) {
    if (g_igHotKeyBindingList_metaObject == 0) {
        g_igHotKeyBindingList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igHotKeyBindingList_metaObject;
}

igMetaObject *igHotKeyBindingList_GetMetaObject(void)
{
    igMetaObject *g = g_igHotKeyBindingList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igHotKeyBindingList_RunStaticInit();
    return g_igHotKeyBindingList_metaObject;
}

int igHotKeyBindingList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igHotKeyBindingList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igHotKeyBindingList_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igHotKeyBindingList_Register);
}

static igMetaObjectCallback g_igHotKeyBindingList_callbackList[] = { igHotKeyBinding_RunStaticInit, 0 };

CallbackArray *igHotKeyBindingList_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igHotKeyBindingList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        thunk_igHotKeyBindingList_GetMetaObject,
        "igHotKeyBindingList",
        0x14, /* instance size */
        igHotKeyBindingList_GetVTable,
        0,
        0, /* extra callback item */
        g_igHotKeyBindingList_callbackList /* callback list */
    );
}

void thunk_igHotKeyBindingList_GetMetaObject(void) {
    igHotKeyBindingList_GetMetaObject();
}

