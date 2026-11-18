igMetaObject *g_igCompoundList_metaObject;
igMetaField *g_igCompoundList_countMetaField;
igMetaField *g_igCompoundList_capacityMetaField;
igMetaField *g_igCompoundList_dataMetaField;

igMetaObject *igCompoundList_GetMetaObject(void)
{
    igMetaObject *g = g_igCompoundList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00225900();
    return g_igCompoundList_metaObject;
}

int igCompoundList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igCompoundList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_00225900(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igCompoundList_Register);
}

CallbackArray *igCompoundList_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCompoundList_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igCompoundList_GetMetaObjectFunction,
        "igCompoundList",
        0x14, /* instance size */
        igCompoundList_GetVTable,
        &igCompoundList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igCompoundList_GetMetaObjectFunction(void) {
    igCompoundList_GetMetaObject();
}

static FieldFactory g_igCompoundList_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
};
static const char *g_igCompoundList_fieldTable[] = {
    "_count",
    "_capacity",
    "_data",
};
static igMetaField **g_igCompoundList_fieldHandles[] = {
    &g_igCompoundList_countMetaField,
    &g_igCompoundList_capacityMetaField,
    &g_igCompoundList_dataMetaField,
};
static int g_igCompoundList_fieldOffsets[] = {
    8,
    12,
    16,
};

void igCompoundList_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;

    meta = g_igCompoundList_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igCompoundList_ctorTable, 3);
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igMemoryRefMetaField *)field)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igRefMetaField *)field)->_destruct = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnReset = 1;
    igMetaObject_NameFields(meta, g_igCompoundList_fieldTable, g_igCompoundList_fieldHandles, g_igCompoundList_fieldOffsets, base);
}

igMetaObject *FUN_00225a30(void) {
    return g_igOptBase_metaObject;
}

