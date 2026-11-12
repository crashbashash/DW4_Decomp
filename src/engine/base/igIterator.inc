igMetaObject *igIterator_GetMetaObject(void)
{
    igMetaObject *g = g_igIterator_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002273d0();
    return g_igIterator_metaObject[0];
}

void FUN_002273d0(void)
{
    igMetaObject_RunStaticInit(igIterator_Register);
}

void igIterator_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igIterator_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igIterator_GetMetaObject,
        igIterator_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igIterator_GetMetaObject(void) {
    igIterator_GetMetaObject();
}

igMetaObject *FUN_00227450(void) {
    return g_igIterator_metaObject[0];
}

