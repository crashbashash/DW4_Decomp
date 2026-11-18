igMetaObject *g_igControllerList_metaObject;

igMetaObject *igControllerList_GetOrCreateMetaObject(void) {
    if (g_igControllerList_metaObject == 0) {
        g_igControllerList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igControllerList_metaObject;
}

igMetaObject *igControllerList_GetMetaObject(void)
{
    igMetaObject *g = g_igControllerList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igControllerList_EnsureRegistered();
    return g_igControllerList_metaObject;
}

int igControllerList_GetVTable(void) {
    Obj_1463a0 o;

    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igControllerList_vtable[0];
    return *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
}

void igControllerList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igControllerList_Register);
}

static igMetaObjectCallback g_igControllerList_callbackList[] = { igController_EnsureRegistered, 0 };

CallbackArray *igControllerList_Register(void) {
    WindowInputLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igControllerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igControllerList_GetMetaObjectFunction,
        "igControllerList",
        0x14, /* instance size */
        igControllerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igControllerList_callbackList /* callback list */
    );
}

void igControllerList_GetMetaObjectFunction(void) {
    igControllerList_GetMetaObject();
}

