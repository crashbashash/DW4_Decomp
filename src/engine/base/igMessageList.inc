igMetaObject *g_igMessageList_metaObject;

igMetaObject *igMessageList_GetOrCreateMetaObject(void) {
    if (g_igMessageList_metaObject == 0) {
        g_igMessageList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMessageList_metaObject;
}

igMetaObject *igMessageList_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00226420();
    return g_igMessageList_metaObject;
}

int igMessageList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igMessageList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_00226420(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igMessageList_Register);
}

static igMetaObjectCallback g_igMessageList_callbackList[] = { FUN_00226540, 0 };

CallbackArray *igMessageList_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMessageList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igMessageList_GetMetaObjectFunction,
        "igMessageList",
        0x14, /* instance size */
        igMessageList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMessageList_callbackList /* callback list */
    );
}

void igMessageList_GetMetaObjectFunction(void) {
    igMessageList_GetMetaObject();
}

