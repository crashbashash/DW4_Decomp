igMetaObject *g_igFileInfoList_metaObject;

igMetaObject *igFileInfoList_GetOrCreateMetaObject(void) {
    if (g_igFileInfoList_metaObject == 0) {
        g_igFileInfoList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igFileInfoList_metaObject;
}

igMetaObject *igFileInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igFileInfoList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228dd0();
    return g_igFileInfoList_metaObject;
}

int igFileInfoList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igFileInfoList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_00228dd0(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igFileInfoList_Register);
}

static igMetaObjectCallback g_igFileInfoList_callbackList[] = { FUN_002290c0, 0 };

CallbackArray *igFileInfoList_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFileInfoList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igFileInfoList_GetMetaObjectFunction,
        "igFileInfoList",
        0x14, /* instance size */
        igFileInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igFileInfoList_callbackList /* callback list */
    );
}

void igFileInfoList_GetMetaObjectFunction(void) {
    igFileInfoList_GetMetaObject();
}

