igMetaObject *FUN_00453250(void) {
    if (g_igAction_metaObject[0] == 0) {
        g_igAction_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAction_metaObject[0];
}

igMetaObject *igAction_GetMetaObject(void)
{
    igMetaObject *g = g_igAction_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igAction_RunStaticInit();
    return g_igAction_metaObject[0];
}

void igAction_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igAction_Register);
}

void igAction_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igAction_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAction_GetMetaObject,
        igAction_className,
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

