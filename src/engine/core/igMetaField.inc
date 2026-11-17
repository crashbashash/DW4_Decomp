igMetaObject *g_igMetaField_metaObject;
igMetaField *g_igMetaField_offsetMetaField;
igMetaField *g_fieldNameMember;
igMetaField *g_igMetaField_typeIndexMetaField;
igMetaField *g_igMetaField_internalIndexMetaField;
igMetaField *g_igMetaField_sizeMetaField;
igMetaField *g_igMetaField_parentMetaObjectMetaField;
igMetaField *g_igMetaField_externalEnumStorageMetaField;
igMetaField *g_igMetaField_defaultMetaField;
igMetaField *g_igMetaField_resetMethodMetaField;
igMetaField *g_igMetaField_isRunTimeMetaField;
igMetaField *g_igMetaField_persistentMetaField;
igMetaField *g_igMetaField_shallowCopyMethodMetaField;
igMetaField *g_igMetaField_deepCopyMethodMetaField;
igMetaField *g_igMetaField_constructCopyMethodMetaField;
igMetaField *g_igMetaField_isAlikeExactlyMethodMetaField;
igMetaField *g_igMetaField_isAlikeDeepMethodMetaField;
igMetaField *g_igMetaField_isAlikeShallowMethodMetaField;
igMetaField *g_igMetaField_invarianceFunctionMetaField;

igMetaObject *igMetaField_GetOrCreateMetaObject(void) {
    if (g_igMetaField_metaObject == 0) {
        g_igMetaField_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMetaField_metaObject;
}

igMetaObject *igMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMetaField_EnsureRegistered();
    return g_igMetaField_metaObject;
}

void igMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMetaField_Register);
}

static igMetaObjectCallback g_igMetaField_callbackList[] = { igMetaObject_EnsureRegistered, 0 };

CallbackArray *igMetaField_Register(void) {
    return igMetaObject_RegisterClass(
        1,
        &g_igMetaField_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igMetaField_GetMetaObjectFunction,
        "igMetaField",
        0x34,
        0,
        igMetaField_InitFields,
        0,
        g_igMetaField_callbackList
    );
}

void igMetaField_GetMetaObjectFunction(void) {
    igMetaField_GetMetaObject();
}

static FieldFactory g_igMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igShortMetaField_Create,
    (FieldFactory)igShortMetaField_Create,
    (FieldFactory)igUnsignedShortMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igCharMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igCharMetaField_Create,
    (FieldFactory)igCharMetaField_Create,
    (FieldFactory)igCharMetaField_Create,
    (FieldFactory)igCharMetaField_Create,
    (FieldFactory)igCharMetaField_Create,
    (FieldFactory)igCharMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
};
static const char *g_igMetaField_fieldTable[] = {
    "_offset",
    "_fieldName",
    "_typeIndex",
    "_internalIndex",
    "_size",
    "_parentMetaObject",
    "_externalEnumStorage",
    "_default",
    "_resetMethod",
    "_isRunTime",
    "_persistent",
    "_shallowCopyMethod",
    "_deepCopyMethod",
    "_constructCopyMethod",
    "_isAlikeExactlyMethod",
    "_isAlikeDeepMethod",
    "_isAlikeShallowMethod",
    "_invarianceFunction",
};
static igMetaField **g_igMetaField_fieldDescriptors[] = {
    &g_igMetaField_offsetMetaField,
    &g_fieldNameMember,
    &g_igMetaField_typeIndexMetaField,
    &g_igMetaField_internalIndexMetaField,
    &g_igMetaField_sizeMetaField,
    &g_igMetaField_parentMetaObjectMetaField,
    &g_igMetaField_externalEnumStorageMetaField,
    &g_igMetaField_defaultMetaField,
    &g_igMetaField_resetMethodMetaField,
    &g_igMetaField_isRunTimeMetaField,
    &g_igMetaField_persistentMetaField,
    &g_igMetaField_shallowCopyMethodMetaField,
    &g_igMetaField_deepCopyMethodMetaField,
    &g_igMetaField_constructCopyMethodMetaField,
    &g_igMetaField_isAlikeExactlyMethodMetaField,
    &g_igMetaField_isAlikeDeepMethodMetaField,
    &g_igMetaField_isAlikeShallowMethodMetaField,
    &g_igMetaField_invarianceFunctionMetaField,
};
static int g_igMetaField_fieldOffsets[] = {
    8,
    12,
    16,
    18,
    20,
    24,
    28,
    32,
    36,
    37,
    38,
    39,
    40,
    41,
    42,
    43,
    44,
    48,
};

void igMetaField_InitFields(void) {
    int first;
    igObjectRefMetaField *parentField;
    igMetaField *externalEnumField;
    igMemoryRefMetaField *defaultField;
    igMetaField *typeIndexField;
    igMetaField *internalIndexField;
    void *meta;

    meta = (void *)g_igMetaField_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMetaField_ctorTable, 0x12);
    ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, first))->_persistent = 0;
    typeIndexField = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 2));
    igShortMetaField_SetDefault((igMetaField *)typeIndexField, -1);
    typeIndexField->_persistent = 0;
    internalIndexField = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 3));
    igShortMetaField_SetDefault((igMetaField *)internalIndexField, -1);
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
    igCharMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 8), 0);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0xA), 1);
    igCharMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0xB), 1);
    igCharMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0xC), 0);
    igCharMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0xD), 0);
    igCharMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0xE), 0);
    igCharMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0xF), 1);
    igCharMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0x10), 2);
    ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 0x11))->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igMetaField_fieldTable, g_igMetaField_fieldDescriptors, g_igMetaField_fieldOffsets, first);
}

