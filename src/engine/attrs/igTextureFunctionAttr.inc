igMetaObject *g_igTextureFunctionAttr_metaObject;
igMetaField *g_igTextureFunctionAttr_modeMetaField;
igMetaField *g_igTextureFunctionAttr_unitIDMetaField;
igMetaField *g_igTextureFunctionAttr_arg0MetaField;
igMetaField *g_igTextureFunctionAttr_arg1MetaField;
igMetaField *g_igTextureFunctionAttr_typeMetaField;
igMetaField *g_igTextureFunctionAttr_call_stateMetaField;
igMetaField *g_igTextureFunctionAttr_functionTypeMetaField;

igTextureFunctionAttr *igTextureFunctionAttr_Create(igMemoryPoolView *pool) {
    igTextureFunctionAttr_EnsureRegistered();
    return (igTextureFunctionAttr *)igMetaObject_CreateInstance(g_igTextureFunctionAttr_metaObject, pool);
}

igMetaObject *igTextureFunctionAttr_GetOrCreateMetaObject(void) {
    if (g_igTextureFunctionAttr_metaObject == 0) {
        g_igTextureFunctionAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTextureFunctionAttr_metaObject;
}

igMetaObject *igTextureFunctionAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureFunctionAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTextureFunctionAttr_EnsureRegistered();
    return g_igTextureFunctionAttr_metaObject;
}

int igTextureFunctionAttr_GetVTable(void) {
    struct Obj_131d40 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igTextureFunctionAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igTextureFunctionAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureFunctionAttr_Register);
}

CallbackArray *igTextureFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureFunctionAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igTextureFunctionAttr_GetMetaObjectFunction,
        "igTextureFunctionAttr",
        sizeof(igTextureFunctionAttr),                     /* Instance size. */
        igTextureFunctionAttr_GetVTable,
        &igTextureFunctionAttr_InitFields,
        FUN_00131f70, /* extra callback item */
        0 /* callback list */
    );
}

void igTextureFunctionAttr_GetMetaObjectFunction(void) {
    igTextureFunctionAttr_GetMetaObject();
}

static FieldFactory g_igTextureFunctionAttr_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igUnsignedCharMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igTextureFunctionAttr_fieldTable[] = {
    "_mode",
    "_unitID",
    "_arg0",
    "_arg1",
    "_type",
    "_call_state",
    "_functionType",
};
static igMetaField **g_igTextureFunctionAttr_fieldHandles[] = {
    &g_igTextureFunctionAttr_modeMetaField,
    &g_igTextureFunctionAttr_unitIDMetaField,
    &g_igTextureFunctionAttr_arg0MetaField,
    &g_igTextureFunctionAttr_arg1MetaField,
    &g_igTextureFunctionAttr_typeMetaField,
    &g_igTextureFunctionAttr_call_stateMetaField,
    &g_igTextureFunctionAttr_functionTypeMetaField,
};
static int g_igTextureFunctionAttr_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
};

int g_igTextureFunctionAttr_modeDefault = 1;

void igTextureFunctionAttr_InitFields(void) {
    igMetaObject *meta;
    int base;
    struct MetaFieldSetupView *field;
    struct MetaFieldSetupView *field2;
    struct MetaFieldSetupView *t1;
    struct MetaFieldSetupView *t2;
    struct MetaFieldSetupView *t3;
    struct MetaFieldSetupView *t4;

    meta = g_igTextureFunctionAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igTextureFunctionAttr_ctorTable, 7);
    field = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base);
    ((Gap::Core::igEnumMetaField *)field)->setDefault(g_igTextureFunctionAttr_modeDefault);
    field->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    t1 = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base + 1);
    t1->_invarianceFunction = (void (*)())igTextureFunctionAttr_SynchronizeCachedUnitID;
    t2 = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base + 2);
    t2->_getMetaEnumFunction = (void (*)())TEXTURE_ARGUMENT_GetMetaEnum;
    t3 = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base + 3);
    t3->_getMetaEnumFunction = (void (*)())TEXTURE_ARGUMENT_GetMetaEnum;
    t4 = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base + 4);
    t4->_getMetaEnumFunction = (void (*)())TEXTURE_STAGE_TYPE_GetMetaEnum;
    ((Gap::Core::igUnsignedCharMetaField *)(igMetaObject_GetFieldAt(meta, base + 5)))->setDefault(2);
    field2 = (MetaFieldSetupView *)igMetaObject_GetFieldAt(meta, base + 6);
    ((Gap::Core::igEnumMetaField *)field2)->setDefault(0);
    field2->_getMetaEnumFunction = (void (*)())TEXTURE_FUNCTION_TYPE_GetMetaEnum;
    igMetaObject_NameFields(meta, g_igTextureFunctionAttr_fieldTable, g_igTextureFunctionAttr_fieldHandles, g_igTextureFunctionAttr_fieldOffsets, base);
}

void FUN_00131f70(void) {
    FUN_001412a0();
}

