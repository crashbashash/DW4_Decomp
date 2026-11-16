igMetaObject *g_igDepthWriteStateAttr_metaObject;
igMetaField *g_igDepthWriteStateAttr_enabledMetaField;

igMetaObject *FUN_001382a0(void) {
    if (g_igDepthWriteStateAttr_metaObject == 0) {
        g_igDepthWriteStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igDepthWriteStateAttr_metaObject;
}

igMetaObject *igDepthWriteStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igDepthWriteStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDepthWriteStateAttr_EnsureRegistered();
    return g_igDepthWriteStateAttr_metaObject;
}

int igDepthWriteStateAttr_GetVTable(void) {
    struct Obj_138340 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igDepthWriteStateAttr_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void igDepthWriteStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDepthWriteStateAttr_Register);
}

CallbackArray *igDepthWriteStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igDepthWriteStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igDepthWriteStateAttr_GetMetaObject,
        "igDepthWriteStateAttr",
        0x10, /* instance size */
        igDepthWriteStateAttr_GetVTable,
        &igDepthWriteStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igDepthWriteStateAttr_GetMetaObject(void) {
    igDepthWriteStateAttr_GetMetaObject();
}

static FieldFactory g_igDepthWriteStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igDepthWriteStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igDepthWriteStateAttr_fieldHandles[] = {
    &g_igDepthWriteStateAttr_enabledMetaField,
};
static int g_igDepthWriteStateAttr_fieldOffsets[] = {
    12,
};

void igDepthWriteStateAttr_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igDepthWriteStateAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igDepthWriteStateAttr_ctorTable, 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, g_igDepthWriteStateAttr_fieldTable, g_igDepthWriteStateAttr_fieldHandles, g_igDepthWriteStateAttr_fieldOffsets, temp_s1);
}

