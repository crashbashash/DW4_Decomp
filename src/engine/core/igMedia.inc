igMetaObject *FUN_002c16e0(void) {
    if (g_igMedia_metaObject[0] == 0) {
        g_igMedia_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData)));
    }
    return g_igMedia_metaObject[0];
}

igMetaObject *igMedia_GetMetaObject(void)
{
    igMetaObject *g = g_igMedia_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c1780();
    return g_igMedia_metaObject[0];
}

void FUN_002c1780(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMedia_Register);
}

void igMedia_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igMedia_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMedia_GetMetaObject,
        igMedia_className,
        8, /* instance size */
        0,
        &igMedia_InitFields_002c1810[0],
        thunk_FUN_002ebcf0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMedia_GetMetaObject(void) {
    igMedia_GetMetaObject();
}

void FUN_002c1810(void) {
    *(int *)((char *)((*(int *)g_igMedia_metaObject)) + 60) = (int)&thunk_igPsx2Media_GetMetaObject;
    FUN_002fe480((int)&thunk_FUN_002ebd70);
}

