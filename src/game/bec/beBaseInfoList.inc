igMetaObject *g_beBaseInfoList_metaObject;

igMetaObject *beBaseInfoList_GetOrCreateMetaObject(void) {
    if (g_beBaseInfoList_metaObject == 0) {
        g_beBaseInfoList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beBaseInfoList_metaObject;
}

igMetaObject *beBaseInfoList_GetMetaObject(void) {
    igMetaObject *g = g_beBaseInfoList_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beBaseInfoList_EnsureRegistered();
done:
    return g_beBaseInfoList_metaObject;
}

int beBaseInfoList_GetVTable(void) {
    beBaseInfoList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beBaseInfoList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beBaseInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBaseInfoList_Register);
}

static igMetaObjectCallback g_beBaseInfoList_callbackList[] = { beBaseInfo_EnsureRegistered, 0 };

CallbackArray *beBaseInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beBaseInfoList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beBaseInfoList_GetMetaObjectFunction,
        "beBaseInfoList",
        0x14, /* instance size */
        beBaseInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beBaseInfoList_callbackList /* callback list */
    );
}

void beBaseInfoList_GetMetaObjectFunction(void)
{
    beBaseInfoList_GetMetaObject();
}

