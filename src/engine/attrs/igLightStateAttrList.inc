igMetaObject *g_igLightStateAttrList_metaObject;

igMetaObject *igLightStateAttrList_GetOrCreateMetaObject(void) {
    if (g_igLightStateAttrList_metaObject == 0) {
        g_igLightStateAttrList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLightStateAttrList_metaObject;
}

igMetaObject *igLightStateAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateAttrList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLightStateAttrList_EnsureRegistered();
    return g_igLightStateAttrList_metaObject;
}

int igLightStateAttrList_GetVTable(void) {
    Obj_1360e0 o;

    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igLightStateAttrList_vtable[0];
    return *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
}

void igLightStateAttrList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLightStateAttrList_Register);
}

static igMetaObjectCallback g_igLightStateAttrList_callbackList[] = { igLightStateAttr_EnsureRegistered, 0 };

CallbackArray *igLightStateAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLightStateAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igLightStateAttrList_GetMetaObjectFunction,
        "igLightStateAttrList",
        0x14, /* instance size */
        igLightStateAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igLightStateAttrList_callbackList /* callback list */
    );
}

void igLightStateAttrList_GetMetaObjectFunction(void) {
    igLightStateAttrList_GetMetaObject();
}

