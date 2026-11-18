igMetaObject *g_igFogStateAttr_metaObject;
igMetaField *g_igFogStateAttr_enabledMetaField;

igMetaObject *igFogStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igFogStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFogStateAttr_EnsureRegistered();
    return g_igFogStateAttr_metaObject;
}

int igFogStateAttr_GetVTable(void) {
    struct Obj o;
    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igFogStateAttr_vtable[0];
    return *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
}

void igFogStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFogStateAttr_Register);
}

CallbackArray *igFogStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFogStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igFogStateAttr_GetMetaObject,
        "igFogStateAttr",
        0x10, /* instance size */
        igFogStateAttr_GetVTable,
        &igFogStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igFogStateAttr_GetMetaObject(void) {
    igFogStateAttr_GetMetaObject();
}

static FieldFactory g_igFogStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igFogStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igFogStateAttr_fieldHandles[] = {
    &g_igFogStateAttr_enabledMetaField,
};
static int g_igFogStateAttr_fieldOffsets[] = {
    12,
};

void igFogStateAttr_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igFogStateAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igFogStateAttr_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_igFogStateAttr_fieldTable, g_igFogStateAttr_fieldHandles, g_igFogStateAttr_fieldOffsets, temp_s1);
}

