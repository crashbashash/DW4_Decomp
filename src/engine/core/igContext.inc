igMetaObject *igContext_GetMetaObject(void)
{
    igMetaObject *g = g_igContext_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igContext_EnsureRegistered();
    return g_igContext_metaObject[0];
}

void igContext_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igContext_Register);
}

void igContext_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,
        g_igContext_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igContext_GetMetaObjectFunction,
        igContext_className,
        0x14,
        0,
        igContext_InitFields,
        0,
        (igMetaObjectCallback *)g_igContext_callbackList
    );
}

void igContext_GetMetaObjectFunction(void) {
    igContext_GetMetaObject();
}

void igContext_InitFields(void) {
    int base;
    void *extInstances;
    void *extList;
    void *meta;

    meta = (void *)g_igContext_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igContext_ctorTable[0], 3);
    extList = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)extList)->_metaObject = (int)igContextExtInfoList_GetOrCreateMetaObject();
    extInstances = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)extInstances)->_metaObject = (int)igContextExtList_GetOrCreateMetaObject();
    ((igRefMetaField *)extInstances)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igContext_fieldTable[0], (igMetaField ***)&g_igContext_fieldDescriptors[0], &g_igContext_fieldOffsets[0], base);
}

