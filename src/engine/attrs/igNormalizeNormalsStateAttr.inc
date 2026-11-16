igMetaObject *g_igNormalizeNormalsStateAttr_metaObject;
igMetaField *g_igNormalizeNormalsStateAttr_enabledMetaField;

igMetaObject *FUN_00134fb0(void) {
    if (g_igNormalizeNormalsStateAttr_metaObject == 0) {
        g_igNormalizeNormalsStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igNormalizeNormalsStateAttr_metaObject;
}

igMetaObject *igNormalizeNormalsStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igNormalizeNormalsStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNormalizeNormalsStateAttr_EnsureRegistered();
    return g_igNormalizeNormalsStateAttr_metaObject;
}

int igNormalizeNormalsStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igNormalizeNormalsStateAttr_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void igNormalizeNormalsStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNormalizeNormalsStateAttr_Register);
}

CallbackArray *igNormalizeNormalsStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igNormalizeNormalsStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igNormalizeNormalsStateAttr_GetMetaObject,
        "igNormalizeNormalsStateAttr",
        0x10, /* instance size */
        igNormalizeNormalsStateAttr_GetVTable,
        &igNormalizeNormalsStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igNormalizeNormalsStateAttr_GetMetaObject(void) {
    igNormalizeNormalsStateAttr_GetMetaObject();
}

static FieldFactory g_igNormalizeNormalsStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igNormalizeNormalsStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igNormalizeNormalsStateAttr_fieldHandles[] = {
    &g_igNormalizeNormalsStateAttr_enabledMetaField,
};
static int g_igNormalizeNormalsStateAttr_fieldOffsets[] = {
    12,
};

void igNormalizeNormalsStateAttr_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igNormalizeNormalsStateAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igNormalizeNormalsStateAttr_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_igNormalizeNormalsStateAttr_fieldTable, g_igNormalizeNormalsStateAttr_fieldHandles, g_igNormalizeNormalsStateAttr_fieldOffsets, temp_s1);
}

