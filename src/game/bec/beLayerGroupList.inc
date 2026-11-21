igMetaObject *g_beLayerGroupList_metaObject;

igMetaObject *beLayerGroupList_GetOrCreateMetaObject(void) {
    if (g_beLayerGroupList_metaObject == 0) {
        g_beLayerGroupList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beLayerGroupList_metaObject;
}

void *beLayerGroupList_GetMetaObject(void) {
    igMetaObject *g = g_beLayerGroupList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beLayerGroupList_EnsureRegistered();
    }
    return g_beLayerGroupList_metaObject;
}

int beLayerGroupList_GetVTable(void) {
    beLayerGroupList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beLayerGroupList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beLayerGroupList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLayerGroupList_Register);
}

static igMetaObjectCallback g_beLayerGroupList_callbackList[] = { beLayerGroup_EnsureRegistered, 0 };

CallbackArray *beLayerGroupList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLayerGroupList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beLayerGroupList_GetMetaObjectFunction,
        "beLayerGroupList",
        0x14, /* instance size */
        beLayerGroupList_GetVTable,
        0,
        0, /* extra callback item */
        g_beLayerGroupList_callbackList /* callback list */
    );
}

void beLayerGroupList_GetMetaObjectFunction(void)
{
    beLayerGroupList_GetMetaObject();
}

