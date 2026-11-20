igMetaObject *g_igBlendEquationExt_metaObject;
igMetaField *g_igBlendEquationExt_equationMetaField;

igMetaObject *igBlendEquationExt_GetOrCreateMetaObject(void) {
    if (g_igBlendEquationExt_metaObject == 0) {
        g_igBlendEquationExt_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igBlendEquationExt_metaObject;
}

igMetaObject *igBlendEquationExt_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendEquationExt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBlendEquationExt_EnsureRegistered();
    return g_igBlendEquationExt_metaObject;
}

void igBlendEquationExt_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBlendEquationExt_Register);
}

CallbackArray *igBlendEquationExt_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igBlendEquationExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        igBlendEquationExt_GetMetaObjectFunction,
        "igBlendEquationExt",
        0x18, /* instance size */
        0,
        &igBlendEquationExt_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igBlendEquationExt_GetMetaObjectFunction(void) {
    igBlendEquationExt_GetMetaObject();
}

static FieldFactory g_igBlendEquationExt_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igBlendEquationExt_fieldTable[] = {
    "_equation",
};
static igMetaField **g_igBlendEquationExt_fieldHandles[] = {
    &g_igBlendEquationExt_equationMetaField,
};
static int g_igBlendEquationExt_fieldOffsets[] = {
    20,
};

void igBlendEquationExt_InitFields(void) {
    int fieldStart;
    void *temp_v0;
    igMetaObject *meta;

    meta = g_igBlendEquationExt_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igBlendEquationExt_ctorTable, 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((Gap::Core::igEnumMetaField *)temp_v0)->setDefault(0);
    *(int *)((char *)(temp_v0) + 52) = (int)(&igMetaEnum_GetEmpty);
    igMetaObject_NameFields(meta, g_igBlendEquationExt_fieldTable, g_igBlendEquationExt_fieldHandles, g_igBlendEquationExt_fieldOffsets, fieldStart);
    *(int *)((char *)(g_igBlendEquationExt_metaObject) + 60) = (int)(&igPsx2BlendEquationExt_GetMetaObjectFunction);
}

