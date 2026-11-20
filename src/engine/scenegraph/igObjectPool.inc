igMetaObject *g_igObjectPool_metaObject;
igMetaField *g_igObjectPool_freeIndexMetaField;
igMetaField *g_igObjectPool_capabilityIncreaseMetaField;
igMetaField *g_igObjectPool_resetModeMetaField;

igMetaObject *igObjectPool_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igObjectPool_EnsureRegistered();
    return g_igObjectPool_metaObject;
}

int igObjectPool_GetVTable(void) {
    struct Obj_196780 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igObjectPool_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igObjectPool_EnsureRegistered(void)
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
        igObjectPool_GetMetaObjectFunction,
        "igObjectPool",
        0x20, /* instance size */
        igObjectPool_GetVTable,
        &igObjectPool_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igObjectPool_GetMetaObjectFunction(void) {
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
    int base;
    void *meta;

    meta = (void *)g_igObjectPool_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igObjectPool_ctorTable, 3);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)))->setDefault(0x32);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)))->setDefault(1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igObjectPool_fieldTable, g_igObjectPool_fieldHandles, g_igObjectPool_fieldOffsets, base);
}

