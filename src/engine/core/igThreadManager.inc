void * igThreadManager_Create(int arg0) {
    igThreadManager_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585790), (igMemoryPoolView *)arg0));
}

igMetaObject *igThreadManager_GetMetaObject(void)
{
    igMetaObject *g = g_igThreadManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igThreadManager_EnsureRegistered();
    return g_igThreadManager_metaObject[0];
}

void igThreadManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igThreadManager_Register);
}

void igThreadManager_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igThreadManager_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igThreadManager_GetMetaObjectFunction,
        igThreadManager_className,
        0x10, /* instance size */
        0,
        &igThreadManager_InitFields,
        igThreadManager_StaticInitCallback, /* extra callback item */
        g_igThreadManager_callbackList /* callback list */
    );
}

void igThreadManager_GetMetaObjectFunction(void) {
    igThreadManager_GetMetaObject();
}

void igThreadManager_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    ((igMetaObject *)(g_igThreadManager_metaObject[0]))->_volatile = 1;
    temp_s0 = (void *)(g_igThreadManager_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igThreadManager_ctorTable[0], 2);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igNonRefCountedThreadList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igThreadManager_fieldTable[0], (igMetaField ***)&DAT_004bf388[0], &DAT_004bf390[0], temp_s2);
    ((igMetaObject *)(g_igThreadManager_metaObject[0]))->_abstractProxy = (int)igPsx2ThreadManager_GetMetaObjectFunction;
    igMetaObject_AddExitCallback((int)igThreadManager_ExitCallback);
}

