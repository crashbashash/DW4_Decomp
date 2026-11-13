igMetaObject *FUN_0014d7f0(void) {
    if (g_igIndexArray_metaObject[0] == 0) {
        g_igIndexArray_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igIndexArray_metaObject[0];
}

igMetaObject *igIndexArray_GetMetaObject(void)
{
    igMetaObject *g = g_igIndexArray_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014d890();
    return g_igIndexArray_metaObject[0];
}

void FUN_0014d890(void)
{
    igMetaObject_RunStaticInit(igIndexArray_Register);
}

void igIndexArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igIndexArray_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igIndexArray_GetMetaObject,
        igIndexArray_className,
        0x1C, /* instance size */
        0,
        &igIndexArray_InitFields,
        0, /* extra callback item */
        g_igIndexArray_callbackList /* callback list */
    );
}

void thunk_igIndexArray_GetMetaObject(void) {
    igIndexArray_GetMetaObject();
}

void igIndexArray_InitFields(void) {
    void *temp_s1;
    void *temp_s1_2;
    int temp_s2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)(g_igIndexArray_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igIndexArray_ctorTable[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    FUN_002dc7a0(temp_v0, &DAT_00488db8[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_001493e0);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igMemoryPool_GetOrCreateMetaObject();
    ((igMetaField *)temp_s1_2)->_resetMethod = 3;
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    ((igMetaField *)temp_s1_2)->_deepCopyMethod = 1;
    ((igMetaField *)temp_s1_2)->_shallowCopyMethod = 1;
    igMetaObject_NameFields(temp_s0, &g_igIndexArray_fieldTable[0], &DAT_00488d80[0], &DAT_00488da0[0], temp_s2);
    ((igMetaObject *)g_igIndexArray_metaObject[0])->_abstractProxy = (int)(&thunk_igPsx2IndexArray_GetMetaObject);
}

