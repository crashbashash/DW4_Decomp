igMetaObject *g_igLightingStateAttr_metaObject;
igMetaField *g_igLightingStateAttr_enabledMetaField;

igLightingStateAttr *igLightingStateAttr_CreateInstance(int allocator) {
    igLightingStateAttr_EnsureRegistered();
    return (igLightingStateAttr *)igMetaObject_CreateInstance(*(igMetaObject * *)0x55F048, (igMemoryPoolView *)allocator);
}

igMetaObject *igLightingStateAttr_GetOrCreateMetaObject(void) {
    if (g_igLightingStateAttr_metaObject == 0) {
        g_igLightingStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLightingStateAttr_metaObject;
}

igMetaObject *igLightingStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igLightingStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLightingStateAttr_EnsureRegistered();
    return g_igLightingStateAttr_metaObject;
}

int igLightingStateAttr_GetVTable(void) {
    struct Obj_135f00 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igLightingStateAttr_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void igLightingStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLightingStateAttr_Register);
}

CallbackArray *igLightingStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLightingStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igLightingStateAttr_GetMetaObject,
        "igLightingStateAttr",
        0x10, /* instance size */
        igLightingStateAttr_GetVTable,
        &igLightingStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igLightingStateAttr_GetMetaObject(void) {
    igLightingStateAttr_GetMetaObject();
}

static FieldFactory g_igLightingStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igLightingStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igLightingStateAttr_fieldHandles[] = {
    &g_igLightingStateAttr_enabledMetaField,
};
static int g_igLightingStateAttr_fieldOffsets[] = {
    12,
};

void igLightingStateAttr_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igLightingStateAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igLightingStateAttr_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_igLightingStateAttr_fieldTable, g_igLightingStateAttr_fieldHandles, g_igLightingStateAttr_fieldOffsets, temp_s1);
}

