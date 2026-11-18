igMetaObject *g_igDepthStateAttr_metaObject;
igMetaField *g_igDepthStateAttr_enabledMetaField;

void FUN_001384a0(int arg0) {
    igDepthStateAttr_EnsureRegistered();
    igMetaObject_CreateInstance(*(igMetaObject * *)0x55F228, (igMemoryPoolView *)arg0);
}

igMetaObject *igDepthStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igDepthStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDepthStateAttr_EnsureRegistered();
    return g_igDepthStateAttr_metaObject;
}

int igDepthStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igDepthStateAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igDepthStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDepthStateAttr_Register);
}

CallbackArray *igDepthStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igDepthStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igDepthStateAttr_GetMetaObject,
        "igDepthStateAttr",
        0x10, /* instance size */
        igDepthStateAttr_GetVTable,
        &igDepthStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igDepthStateAttr_GetMetaObject(void) {
    igDepthStateAttr_GetMetaObject();
}

static FieldFactory g_igDepthStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igDepthStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igDepthStateAttr_fieldHandles[] = {
    &g_igDepthStateAttr_enabledMetaField,
};
static int g_igDepthStateAttr_fieldOffsets[] = {
    12,
};

void igDepthStateAttr_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igDepthStateAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igDepthStateAttr_ctorTable, 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, g_igDepthStateAttr_fieldTable, g_igDepthStateAttr_fieldHandles, g_igDepthStateAttr_fieldOffsets, temp_s1);
}

