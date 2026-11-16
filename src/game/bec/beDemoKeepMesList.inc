igMetaObject *g_beDemoKeepMesList_metaObject;

igMetaObject *beDemoKeepMesList_GetOrCreateMetaObject(void) {
    if (g_beDemoKeepMesList_metaObject == 0) {
        g_beDemoKeepMesList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beDemoKeepMesList_metaObject;
}

igMetaObject *beDemoKeepMesList_GetMetaObject(void)
{
    igMetaObject *g = g_beDemoKeepMesList_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beDemoKeepMesList_EnsureRegistered();
    return g_beDemoKeepMesList_metaObject;
}

int beDemoKeepMesList_GetVTable(void) {
    beDemoKeepMesList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beDemoKeepMesList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void beDemoKeepMesList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDemoKeepMesList_Register);
}

static igMetaObjectCallback g_beDemoKeepMesList_callbackList[] = { beDemoKeepMes_EnsureRegistered, 0 };

CallbackArray *beDemoKeepMesList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDemoKeepMesList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beDemoKeepMesList_GetMetaObjectFunction,
        "beDemoKeepMesList",
        0x14, /* instance size */
        beDemoKeepMesList_GetVTable,
        0,
        0, /* extra callback item */
        g_beDemoKeepMesList_callbackList /* callback list */
    );
}

void beDemoKeepMesList_GetMetaObjectFunction(void)
{
    beDemoKeepMesList_GetMetaObject();
}

