igMetaObject *g_igShadeModelAttr_metaObject;
igMetaField *g_igShadeModelAttr_modeMetaField;

igMetaObject *igShadeModelAttr_GetOrCreateMetaObject(void) {
    if (g_igShadeModelAttr_metaObject == 0) {
        g_igShadeModelAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igShadeModelAttr_metaObject;
}

igMetaObject *igShadeModelAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igShadeModelAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igShadeModelAttr_EnsureRegistered();
    return g_igShadeModelAttr_metaObject;
}

int igShadeModelAttr_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igShadeModelAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igShadeModelAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igShadeModelAttr_Register);
}

CallbackArray *igShadeModelAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igShadeModelAttr_metaObject,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        igShadeModelAttr_GetMetaObjectFunction,
        "igShadeModelAttr",
        0x10, /* instance size */
        igShadeModelAttr_GetVTable,
        &igShadeModelAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igShadeModelAttr_GetMetaObjectFunction(void) {
    igShadeModelAttr_GetMetaObject();
}

static FieldFactory g_igShadeModelAttr_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igShadeModelAttr_fieldTable[] = {
    "_mode",
};
static igMetaField **g_igShadeModelAttr_fieldHandles[] = {
    &g_igShadeModelAttr_modeMetaField,
};
static int g_igShadeModelAttr_fieldOffsets[] = {
    12,
};

int g_igShadeModelAttr_modeDefault = 1;

void igShadeModelAttr_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;

    meta = g_igShadeModelAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igShadeModelAttr_ctorTable, 1);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((Gap::Core::igEnumMetaField *)field)->setDefault(g_igShadeModelAttr_modeDefault);
    ((igEnumMetaField *)field)->_getMetaEnumFunction = (int)(&IG_GFX_SHADING_MODE_GetMetaEnum);
    igMetaObject_NameFields(meta, g_igShadeModelAttr_fieldTable, g_igShadeModelAttr_fieldHandles, g_igShadeModelAttr_fieldOffsets, base);
}

