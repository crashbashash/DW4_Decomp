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
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
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
        thunk_igCompoundList_GetMetaObject,
        "igCompoundList",
        0x14, /* instance size */
        igCompoundList_GetVTable,
        &igCompoundList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igCompoundList_GetMetaObject(void) {
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
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igCompoundList_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igCompoundList_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    igMetaObject_NameFields(temp_s0, g_igCompoundList_fieldTable, g_igCompoundList_fieldHandles, g_igCompoundList_fieldOffsets, temp_s2);
}

igMetaObject *FUN_00225a30(void) {
    return g_igOptBase_metaObject;
}

