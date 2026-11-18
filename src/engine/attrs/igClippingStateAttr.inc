igMetaObject *g_igClippingStateAttr_metaObject;
igMetaField *g_igClippingStateAttr_enabledMetaField;

igMetaObject *igClippingStateAttr_GetOrCreateMetaObject(void) {
    if (g_igClippingStateAttr_metaObject == 0) {
        g_igClippingStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igClippingStateAttr_metaObject;
}

igMetaObject *igClippingStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igClippingStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igClippingStateAttr_EnsureRegistered();
    return g_igClippingStateAttr_metaObject;
}

int igClippingStateAttr_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igClippingStateAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igClippingStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igClippingStateAttr_Register);
}

CallbackArray *igClippingStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igClippingStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igClippingStateAttr_GetMetaObjectFunction,
        "igClippingStateAttr",
        0x10, /* instance size */
        igClippingStateAttr_GetVTable,
        &igClippingStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igClippingStateAttr_GetMetaObjectFunction(void) {
    igClippingStateAttr_GetMetaObject();
}

static FieldFactory g_igClippingStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igClippingStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igClippingStateAttr_fieldHandles[] = {
    &g_igClippingStateAttr_enabledMetaField,
};
static int g_igClippingStateAttr_fieldOffsets[] = {
    12,
};

void igClippingStateAttr_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_igClippingStateAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igClippingStateAttr_ctorTable, 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base), 1);
    igMetaObject_NameFields(meta, g_igClippingStateAttr_fieldTable, g_igClippingStateAttr_fieldHandles, g_igClippingStateAttr_fieldOffsets, base);
}

