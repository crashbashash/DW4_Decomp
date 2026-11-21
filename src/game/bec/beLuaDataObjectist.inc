igMetaObject *g_beLuaDataObjectist_metaObject;

igMetaObject *beLuaDataObjectist_GetMetaObject(void) {
    if (g_beLuaDataObjectist_metaObject == 0 || !isValid(g_beLuaDataObjectist_metaObject)) beLuaDataObjectist_EnsureRegistered();
    return g_beLuaDataObjectist_metaObject;
}

int beLuaDataObjectist_GetVTable(void) {
    beLuaDataObjectist obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beLuaDataObjectist_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beLuaDataObjectist_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLuaDataObjectist_Register);
}

static igMetaObjectCallback g_beLuaDataObjectist_callbackList[] = { beLuaDataObject_EnsureRegistered, 0 };

CallbackArray *beLuaDataObjectist_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLuaDataObjectist_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beLuaDataObjectist_GetMetaObjectFunction,
        "beLuaDataObjectist",
        0x14, /* instance size */
        beLuaDataObjectist_GetVTable,
        0,
        0, /* extra callback item */
        g_beLuaDataObjectist_callbackList /* callback list */
    );
}

void beLuaDataObjectist_GetMetaObjectFunction(void)
{
    beLuaDataObjectist_GetMetaObject();
}

