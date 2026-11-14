igMetaObject *igPsx2ThreadManager_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ThreadManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2ThreadManager_EnsureRegistered();
    return g_igPsx2ThreadManager_metaObject[0];
}

int igPsx2ThreadManager_GetVTable(void) {
    igPsx2ThreadManager manager;

    igObject_InitHeader((igObject *)&manager);
    manager._vtable = (int)&DAT_0052d750[0];
    return *(int *)((char *)&manager + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igPsx2ThreadManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2ThreadManager_Register);
}

void igPsx2ThreadManager_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPsx2ThreadManager_metaObject),
        igThreadManager_Register,
        igThreadManager_GetPublishedMetaObject,
        igPsx2ThreadManager_GetMetaObjectFunction,
        igPsx2ThreadManager_className,
        0x10, /* instance size */
        igPsx2ThreadManager_GetVTable,
        &igPsx2ThreadManager_InitFields_002cf3f0[0],     /* Field adder. */
        0,                                               /* extra callback-vector item (none) */
        0                                                /* zero-terminated callback-vector item list (none) */
    );
}

int igThreadManager_GetPublishedMetaObject(void) {
    return ((int *)g_igThreadManager_metaObject)[0];
}

void igPsx2ThreadManager_SetWriteProxy(void) {
    *(int *)((char *)(g_igPsx2ThreadManager_metaObject[0]) + 64) = (int)(&igThreadManager_GetMetaObjectFunction);
}

