igMetaObject *igMemoryPool_GetOrCreateMetaObject(void) {
    if (g_igMemoryPool_metaObject[0] == 0) {
        g_igMemoryPool_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igMemoryPool_metaObject[0];
}

igMetaObject *igMemoryPool_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryPool_EnsureRegistered();
    return g_igMemoryPool_metaObject[0];
}

void igMemoryPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryPool_Register);
}

void igMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        1,
        g_igMemoryPool_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igMemoryPool_GetMetaObjectFunction,
        igMemoryPool_className,
        0x70,
        0,
        igMemoryPool_InitFields,
        0,
        0
    );
}

void igMemoryPool_GetMetaObjectFunction(void) {
    igMemoryPool_GetMetaObject();
}

void igMemoryPool_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)(((void * *)g_igMemoryPool_metaObject)[0]);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igMemoryPool_ctorTable[0], 0xE);
    igBoolMetaField_SetDefaultValue((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xC)), 1);
    igBoolMetaField_SetDefaultValue((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xD)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igMemoryPool_fieldTable[0], (igMetaField ***)&g_igMemoryPool_fieldDescriptors[0], &g_igMemoryPool_fieldOffsets[0], base);
    *(int *)((char *)(((void * *)g_igMemoryPool_metaObject)[0]) + 60) = (int)igArenaMemoryPool_GetMetaObjectFunction;
}

