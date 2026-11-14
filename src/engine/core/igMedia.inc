igMetaObject *igMedia_GetOrCreateMetaObject(void) {
    if (g_igMedia_metaObject[0] == 0) {
        g_igMedia_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igMedia_metaObject[0];
}

igMetaObject *igMedia_GetMetaObject(void)
{
    igMetaObject *g = g_igMedia_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMedia_EnsureRegistered();
    return g_igMedia_metaObject[0];
}

void igMedia_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMedia_Register);
}

void igMedia_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,
        g_igMedia_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igMedia_GetMetaObjectFunction,
        igMedia_className,
        8,
        0,
        (igMetaObjectCallback)igMedia_InitFields_002c1810,
        igMedia_StaticInitCallback,
        0
    );
}

void igMedia_GetMetaObjectFunction(void) {
    igMedia_GetMetaObject();
}

void igMedia_SetAbstractProxy(void) {
    *(int *)((char *)((*(int *)g_igMedia_metaObject)) + 60) = (int)&igPsx2Media_GetMetaObjectFunction;
    igMetaObject_AddExitCallback((int)&igMedia_ExitCallback);
}

