igMetaObject *g_igLibrary_metaObject;
igMetaField *g_igLibrary_registerFunctionMetaField;

igMetaObject *igLibrary_GetMetaObject(void)
{
    igMetaObject *g = g_igLibrary_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLibrary_EnsureRegistered();
    return g_igLibrary_metaObject;
}

void igLibrary_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLibrary_Register);
}

void igLibrary_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,
        &g_igLibrary_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igLibrary_GetMetaObjectFunction,
        "igLibrary",
        0xC,
        0,
        igLibrary_InitFields,
        0,
        0
    );
}

void igLibrary_GetMetaObjectFunction(void) {
    igLibrary_GetMetaObject();
}

static FieldFactory g_igLibrary_ctorTable[] = {
    (FieldFactory)igRawRefMetaField_Create,
};
static const char *g_igLibrary_fieldTable[] = {
    "_registerFunction",
};
static igMetaField **g_igLibrary_fieldDescriptors[] = {
    &g_igLibrary_registerFunctionMetaField,
};
static int g_igLibrary_fieldOffsets[] = {
    8,
};

void igLibrary_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_igLibrary_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igLibrary_ctorTable, 1);
    igMetaObject_NameFields(meta, g_igLibrary_fieldTable, g_igLibrary_fieldDescriptors, g_igLibrary_fieldOffsets, base);
}

