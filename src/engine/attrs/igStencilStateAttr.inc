igMetaObject *g_igStencilStateAttr_metaObject;
igMetaField *g_igStencilStateAttr_enabledMetaField;

igMetaObject *igStencilStateAttr_GetOrCreateMetaObject(void) {
    if (g_igStencilStateAttr_metaObject == 0) {
        g_igStencilStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igStencilStateAttr_metaObject;
}

igMetaObject *igStencilStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igStencilStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igStencilStateAttr_EnsureRegistered();
    return g_igStencilStateAttr_metaObject;
}

int igStencilStateAttr_GetVTable(void) {
    struct Obj_1334d0 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igStencilStateAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igStencilStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igStencilStateAttr_Register);
}

CallbackArray *igStencilStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igStencilStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igStencilStateAttr_GetMetaObjectFunction,
        "igStencilStateAttr",
        0x10, /* instance size */
        igStencilStateAttr_GetVTable,
        &igStencilStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igStencilStateAttr_GetMetaObjectFunction(void) {
    igStencilStateAttr_GetMetaObject();
}

static FieldFactory g_igStencilStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igStencilStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igStencilStateAttr_fieldHandles[] = {
    &g_igStencilStateAttr_enabledMetaField,
};
static int g_igStencilStateAttr_fieldOffsets[] = {
    12,
};

void igStencilStateAttr_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_igStencilStateAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igStencilStateAttr_ctorTable, 1);
    igMetaObject_NameFields(meta, g_igStencilStateAttr_fieldTable, g_igStencilStateAttr_fieldHandles, g_igStencilStateAttr_fieldOffsets, base);
}

