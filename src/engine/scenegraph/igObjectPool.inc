igMetaObject *g_igObjectPool_metaObject;
igMetaField *g_igObjectPool_freeIndexMetaField;
igMetaField *g_igObjectPool_capabilityIncreaseMetaField;
igMetaField *g_igObjectPool_resetModeMetaField;

igMetaObject *igObjectPool_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001967c0();
    return g_igObjectPool_metaObject;
}

int igObjectPool_GetVTable(void) {
    struct Obj_196780 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igObjectPool_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_001967c0(void)
{
    igMetaObject_RunStaticInit(igObjectPool_Register);
}

CallbackArray *igObjectPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igObjectPool_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igObjectPool_GetMetaObject,
        "igObjectPool",
        0x20, /* instance size */
        igObjectPool_GetVTable,
        &igObjectPool_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igObjectPool_GetMetaObject(void) {
    igObjectPool_GetMetaObject();
}

static FieldFactory g_igObjectPool_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igObjectPool_fieldTable[] = {
    "_freeIndex",
    "_capabilityIncrease",
    "_resetMode",
};
static igMetaField **g_igObjectPool_fieldHandles[] = {
    &g_igObjectPool_freeIndexMetaField,
    &g_igObjectPool_capabilityIncreaseMetaField,
    &g_igObjectPool_resetModeMetaField,
};
static int g_igObjectPool_fieldOffsets[] = {
    20,
    24,
    28,
};

void igObjectPool_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igObjectPool_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igObjectPool_ctorTable, 3);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1), 0x32);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igObjectPool_fieldTable, g_igObjectPool_fieldHandles, g_igObjectPool_fieldOffsets, temp_s1);
}

