void * igThreadManager_Create(int allocator) {
    igThreadManager_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585790), (igMemoryPoolView *)allocator));
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
        1,
        g_igThreadManager_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igThreadManager_GetMetaObjectFunction,
        igThreadManager_className,
        0x10,
        0,
        igThreadManager_InitFields,
        igThreadManager_StaticInitCallback,
        (igMetaObjectCallback *)g_igThreadManager_callbackList
    );
}

void igThreadManager_GetMetaObjectFunction(void) {
    igThreadManager_GetMetaObject();
}

void igThreadManager_InitFields(void) {
    int base;
    void *semaField;
    void *threadListField;
    void *meta;

    ((igMetaObject *)(g_igThreadManager_metaObject[0]))->_volatile = 1;
    meta = (void *)(g_igThreadManager_metaObject[0]);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igThreadManager_ctorTable[0], 2);
    threadListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)threadListField)->_metaObject = (int)igNonRefCountedThreadList_GetOrCreateMetaObject();
    ((igRefMetaField *)threadListField)->_construct = 1;
    semaField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)semaField)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    ((igRefMetaField *)semaField)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igThreadManager_fieldTable[0], (igMetaField ***)&g_igThreadManager_fieldDescriptors[0], &g_igThreadManager_fieldOffsets[0], base);
    ((igMetaObject *)(g_igThreadManager_metaObject[0]))->_abstractProxy = (int)igPsx2ThreadManager_GetMetaObjectFunction;
    igMetaObject_AddExitCallback((int)igThreadManager_ExitCallback);
}

