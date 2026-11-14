void * igQueue_Create(int pool) {
    igQueue_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585AA8), (igMemoryPoolView *)pool));
}

igMetaObject *igQueue_GetOrCreateMetaObject(void) {
    if (g_igQueue_metaObject[0] == 0) {
        g_igQueue_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igQueue_metaObject[0];
}

igMetaObject *igQueue_GetMetaObject(void)
{
    igMetaObject *g = g_igQueue_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igQueue_EnsureRegistered();
    return g_igQueue_metaObject[0];
}

void igQueue_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igQueue_Register);
}

void igQueue_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,
        g_igQueue_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igQueue_GetMetaObjectFunction,
        igQueue_className,
        0xC,
        0,
        igQueue_InitFields,
        0,
        (igMetaObjectCallback *)g_igQueue_callbackList
    );
}

void igQueue_GetMetaObjectFunction(void) {
    igQueue_GetMetaObject();
}

void igQueue_InitFields(void) {
    int base;
    igObjectRefMetaField *threads;
    igMetaObject *meta;

    meta = g_igQueue_metaObject[0];
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, (igMetaField * (**)(void *))&g_igQueue_ctorTable[0], 1);
    threads = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base);
    threads->_metaObject = (int)igThreadList_GetOrCreateMetaObject();
    threads->_construct = 1;
    igMetaObject_NameFields(meta, (const char **)&g_igQueue_fieldTable[0], (igMetaField ***)&g_igQueue_fieldDescriptors[0], &g_igQueue_fieldOffsets[0], base);
    g_igQueue_metaObject[0]->_abstractProxy = (int)igStandardQueue_GetMetaObjectFunction;
}

