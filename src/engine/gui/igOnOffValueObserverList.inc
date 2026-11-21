igMetaObject *g_igOnOffValueObserverList_metaObject;

igMetaObject *igOnOffValueObserverList_GetOrCreateMetaObject(void) {
    if (g_igOnOffValueObserverList_metaObject == 0) {
        g_igOnOffValueObserverList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igOnOffValueObserverList_metaObject;
}

igMetaObject *igOnOffValueObserverList_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffValueObserverList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffValueObserverList_EnsureRegistered();
    return g_igOnOffValueObserverList_metaObject;
}

int igOnOffValueObserverList_GetVTable(void) {
    Obj_44c920 o;

    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igOnOffValueObserverList_vtable[0];
    return *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
}

void igOnOffValueObserverList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igOnOffValueObserverList_Register);
}

static igMetaObjectCallback g_igOnOffValueObserverList_callbackList[] = { igOnOffValueObserver_EnsureRegistered, 0 };

CallbackArray *igOnOffValueObserverList_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igOnOffValueObserverList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igOnOffValueObserverList_GetMetaObjectFunction,
        "igOnOffValueObserverList",
        0x14, /* instance size */
        igOnOffValueObserverList_GetVTable,
        0,
        0, /* extra callback item */
        g_igOnOffValueObserverList_callbackList /* callback list */
    );
}

void igOnOffValueObserverList_GetMetaObjectFunction(void) {
    igOnOffValueObserverList_GetMetaObject();
}

