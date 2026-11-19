igMetaObject *g_igAttr_metaObject;
igMetaField *g_igAttr_cachedUnitIDMetaField;
igMetaField *g_igAttr_cachedAttrIndexMetaField;

igMetaObject *igAttr_GetOrCreateMetaObject(void) {
    if (g_igAttr_metaObject == 0) {
        g_igAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAttr_metaObject;
}

igMetaObject *igAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAttr_EnsureRegistered();
    return g_igAttr_metaObject;
}

void igAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAttr_Register);
}

CallbackArray *igAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igAttr_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igAttr_GetMetaObjectFunction,
        "igAttr",
        0xC, /* instance size */
        0,
        &igAttr_InitFields,
        igAttr_UserRegister, /* extra callback item */
        0 /* callback list */
    );
}

void igAttr_GetMetaObjectFunction(void) {
    igAttr_GetMetaObject();
}

static FieldFactory g_igAttr_ctorTable[] = {
    (FieldFactory)igShortMetaField_Create,
    (FieldFactory)igShortMetaField_Create,
};
static const char *g_igAttr_fieldTable[] = {
    "_cachedUnitID",
    "_cachedAttrIndex",
};
static igMetaField **g_igAttr_fieldHandles[] = {
    &g_igAttr_cachedUnitIDMetaField,
    &g_igAttr_cachedAttrIndexMetaField,
};
static int g_igAttr_fieldOffsets[] = {
    10,
    8,
};

void igAttr_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;

    meta = g_igAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igAttr_ctorTable, 2);
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    igShortMetaField_SetDefault((igMetaField *)field, -1);
    ((igShortMetaField *)field)->_persistent = 0;
    igMetaObject_NameFields(meta, g_igAttr_fieldTable, g_igAttr_fieldHandles, g_igAttr_fieldOffsets, base);
}

void igAttr_UserRegister(void) {
    FUN_0013b800();
    igMetaObject_AddRegistrationCallback((int)&igAttr_RegisterClass);
}

