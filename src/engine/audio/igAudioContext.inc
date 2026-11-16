igMetaObject *g_igAudioContext_metaObject;
igMetaField *g_igAudioContext_immediateModeMetaField;

igAudioContext *igAudioContext_CreateInstance(int allocator) {
    igAudioContext_EnsureRegistered();
    return (igAudioContext *)igMetaObject_CreateInstance(g_igAudioContext_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igAudioContext_GetOrCreateMetaObject(void) {
    if (g_igAudioContext_metaObject == 0) {
        g_igAudioContext_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAudioContext_metaObject;
}

igMetaObject *igAudioContext_GetMetaObject(void)
{
    igMetaObject *g = g_igAudioContext_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAudioContext_EnsureRegistered();
    return g_igAudioContext_metaObject;
}

void igAudioContext_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAudioContext_Register);
}

CallbackArray *igAudioContext_Register(void) {
    AudioLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igAudioContext_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAudioContext_GetMetaObject,
        "igAudioContext",
        0xC, /* instance size */
        0,
        &igAudioContext_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAudioContext_GetMetaObject(void) {
    igAudioContext_GetMetaObject();
}

static FieldFactory g_igAudioContext_ctorTable[] = {
    igBoolMetaField_Create,
};
static const char *g_igAudioContext_fieldTable[] = {
    "_immediateMode",
};
static igMetaField **g_igAudioContext_fieldHandles[] = {
    &g_igAudioContext_immediateModeMetaField,
};
static int g_igAudioContext_fieldOffsets[] = {
    8,
};

void igAudioContext_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(g_igAudioContext_metaObject);
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igAudioContext_ctorTable, 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igAudioContext_fieldTable, g_igAudioContext_fieldHandles, g_igAudioContext_fieldOffsets, temp_s1);
    *(int *)((char *)(g_igAudioContext_metaObject) + 60) = (int)(thunk_FUN_00143150);
}

void thunk_FUN_00143150(void) {
    FUN_00143150();
}

