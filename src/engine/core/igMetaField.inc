igMetaObject *igMetaField_GetOrCreateMetaObject(void) {
    if (g_igMetaField_metaObject[0] == 0) {
        g_igMetaField_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igMetaField_metaObject[0];
}

igMetaObject *igMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMetaField_EnsureRegistered();
    return g_igMetaField_metaObject[0];
}

void igMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMetaField_Register);
}

void igMetaField_Register(void) {
    igMetaObject_RegisterClass(
        1,
        g_igMetaField_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igMetaField_GetMetaObjectFunction,
        igMetaField_className,
        0x34,
        0,
        igMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igMetaField_callbackList
    );
}

void igMetaField_GetMetaObjectFunction(void) {
    igMetaField_GetMetaObject();
}

void igMetaField_InitFields(void) {
    int first;
    igObjectRefMetaField *parentField;
    igMetaField *externalEnumField;
    igMemoryRefMetaField *defaultField;
    igMetaField *typeIndexField;
    igMetaField *internalIndexField;
    void *meta;

    meta = (void *)g_igMetaField_metaObject[0];
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igMetaField_ctorTable[0], 0x12);
    ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, first))->_persistent = 0;
    typeIndexField = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 2));
    igShortMetaField_SetDefault((void **)typeIndexField, -1);
    typeIndexField->_persistent = 0;
    internalIndexField = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 3));
    igShortMetaField_SetDefault((void **)internalIndexField, -1);
    internalIndexField->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 4))->_persistent = 0;
    parentField = ((igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 5));
    parentField->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
    parentField->_refCounted = 0;
    parentField->_persistent = 0;
    parentField->_deepCopyMethod = 1;
    parentField->_shallowCopyMethod = 1;
    externalEnumField = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 6));
    externalEnumField->_persistent = 0;
    externalEnumField->_deepCopyMethod = 1;
    defaultField = ((igMemoryRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 7));
    defaultField->_destruct = 1;
    defaultField->_releaseOnCopy = 1;
    defaultField->_releaseOnReset = 1;
    defaultField->_persistent = 0;
    igCharMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 8), 0);
    igBoolMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0xA), 1);
    igCharMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0xB), 1);
    igCharMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0xC), 0);
    igCharMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0xD), 0);
    igCharMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0xE), 0);
    igCharMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0xF), 1);
    igCharMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0x10), 2);
    ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0x11))->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igMetaField_fieldTable[0], (igMetaField ***)&g_igMetaField_fieldDescriptors[0], &g_igMetaField_fieldOffsets[0], first);
}

