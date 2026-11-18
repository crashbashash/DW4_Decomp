igMetaObject *g_igTimeAttr_metaObject;
igMetaField *g_igTimeAttr_timeMetaField;

igTimeAttr *igTimeAttr_CreateInstance(int allocator) {
    FUN_00131040();
    return (igTimeAttr *)igMetaObject_CreateInstance(*(igMetaObject * *)0x55EC80, (igMemoryPoolView *)allocator);
}

igMetaObject *FUN_00130f60(void) {
    if (g_igTimeAttr_metaObject == 0) {
        g_igTimeAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTimeAttr_metaObject;
}

igMetaObject *igTimeAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igTimeAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00131040();
    return g_igTimeAttr_metaObject;
}

int igTimeAttr_GetVTable(void) {
    union U_131000 u;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igTimeAttr_vtable[0];
    return *(int *)&u.b[g_objectSystem->vtableProbeOffset];
}

void FUN_00131040(void)
{
    igMetaObject_RunStaticInit(igTimeAttr_Register);
}

CallbackArray *igTimeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTimeAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTimeAttr_GetMetaObject,
        "igTimeAttr",
        0x18, /* instance size */
        igTimeAttr_GetVTable,
        &igTimeAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTimeAttr_GetMetaObject(void) {
    igTimeAttr_GetMetaObject();
}

static FieldFactory g_igTimeAttr_ctorTable[] = {
    (FieldFactory)igLongMetaField_Create,
};
static const char *g_igTimeAttr_fieldTable[] = {
    "_time",
};
static igMetaField **g_igTimeAttr_fieldHandles[] = {
    &g_igTimeAttr_timeMetaField,
};
static int g_igTimeAttr_fieldOffsets[] = {
    16,
};

void igTimeAttr_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igTimeAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igTimeAttr_ctorTable, 1);
    igLongMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s1), 0);
    igMetaObject_NameFields(temp_s0, g_igTimeAttr_fieldTable, g_igTimeAttr_fieldHandles, g_igTimeAttr_fieldOffsets, temp_s1);
}

