igMetaObject *g_igLightStateAttrList_metaObject;

igMetaObject *FUN_00136040(void) {
    if (g_igLightStateAttrList_metaObject == 0) {
        g_igLightStateAttrList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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

    igObject_InitHeader(&o);
    o.vt = &g_igLightStateAttrList_vtable[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igLightStateAttrList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLightStateAttrList_Register);
}

static igMetaObjectCallback g_igLightStateAttrList_callbackList[] = { igLightStateAttr_EnsureRegistered, 0 };

void igLightStateAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLightStateAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igLightStateAttrList_GetMetaObject,
        "igLightStateAttrList",
        0x14, /* instance size */
        igLightStateAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igLightStateAttrList_callbackList /* callback list */
    );
}

void thunk_igLightStateAttrList_GetMetaObject(void) {
    igLightStateAttrList_GetMetaObject();
}

