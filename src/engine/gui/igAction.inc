igMetaObject *g_igAction_metaObject;

igMetaObject *igAction_GetOrCreateMetaObject(void) {
    if (g_igAction_metaObject == 0) {
        g_igAction_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAction_metaObject;
}

igMetaObject *igAction_GetMetaObject(void)
{
    igMetaObject *g = g_igAction_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAction_RunStaticInit();
    return g_igAction_metaObject;
}

void igAction_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igAction_Register);
}

CallbackArray *igAction_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igAction_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAction_GetMetaObject,
        "igAction",
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAction_GetMetaObject(void) {
    igAction_GetMetaObject();
}

