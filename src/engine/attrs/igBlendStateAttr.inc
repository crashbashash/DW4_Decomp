igMetaObject *g_igBlendStateAttr_metaObject;
igMetaField *g_igBlendStateAttr_enabledMetaField;

igBlendStateAttr *igBlendStateAttr_CreateInstance(int allocator) {
    igBlendStateAttr_EnsureRegistered();
    return (igBlendStateAttr *)igMetaObject_CreateInstance(*(igMetaObject * *)0x55F348, (igMemoryPoolView *)allocator);
}

igMetaObject *igBlendStateAttr_GetOrCreateMetaObject(void) {
    if (g_igBlendStateAttr_metaObject == 0) {
        g_igBlendStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igBlendStateAttr_metaObject;
}

igMetaObject *igBlendStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBlendStateAttr_EnsureRegistered();
    return g_igBlendStateAttr_metaObject;
}

int igBlendStateAttr_GetVTable(void) {
    struct Obj o;
    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igBlendStateAttr_vtable[0];
    return *(int *)((char *)&o + *(int *)((char *)g_objectSystem + 916));
}

void igBlendStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBlendStateAttr_Register);
}

CallbackArray *igBlendStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBlendStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igBlendStateAttr_GetMetaObject,
        "igBlendStateAttr",
        0x10, /* instance size */
        igBlendStateAttr_GetVTable,
        &igBlendStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBlendStateAttr_GetMetaObject(void) {
    igBlendStateAttr_GetMetaObject();
}

static FieldFactory g_igBlendStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igBlendStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igBlendStateAttr_fieldHandles[] = {
    &g_igBlendStateAttr_enabledMetaField,
};
static int g_igBlendStateAttr_fieldOffsets[] = {
    12,
};

void igBlendStateAttr_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igBlendStateAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igBlendStateAttr_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_igBlendStateAttr_fieldTable, g_igBlendStateAttr_fieldHandles, g_igBlendStateAttr_fieldOffsets, temp_s1);
}

