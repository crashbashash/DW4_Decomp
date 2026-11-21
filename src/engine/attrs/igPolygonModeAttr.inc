igMetaObject *g_igPolygonModeAttr_metaObject;
igMetaField *g_igPolygonModeAttr_modeMetaField;

igMetaObject *igPolygonModeAttr_GetOrCreateMetaObject(void) {
    if (g_igPolygonModeAttr_metaObject == 0) {
        g_igPolygonModeAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igPolygonModeAttr_metaObject;
}

igMetaObject *igPolygonModeAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igPolygonModeAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPolygonModeAttr_EnsureRegistered();
    return g_igPolygonModeAttr_metaObject;
}

int igPolygonModeAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igPolygonModeAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igPolygonModeAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPolygonModeAttr_Register);
}

CallbackArray *igPolygonModeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPolygonModeAttr_metaObject,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        igPolygonModeAttr_GetMetaObjectFunction,
        "igPolygonModeAttr",
        0x10, /* instance size */
        igPolygonModeAttr_GetVTable,
        &igPolygonModeAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igPolygonModeAttr_GetMetaObjectFunction(void) {
    igPolygonModeAttr_GetMetaObject();
}

static FieldFactory g_igPolygonModeAttr_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igPolygonModeAttr_fieldTable[] = {
    "_mode",
};
static igMetaField **g_igPolygonModeAttr_fieldHandles[] = {
    &g_igPolygonModeAttr_modeMetaField,
};
static int g_igPolygonModeAttr_fieldOffsets[] = {
    12,
};

void igPolygonModeAttr_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;

    meta = g_igPolygonModeAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igPolygonModeAttr_ctorTable, 1);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((Gap::Core::igEnumMetaField *)field)->setDefault(0);
    ((igEnumMetaField *)field)->_getMetaEnumFunction = (int)(&IG_GFX_RENDER_MODE_GetMetaEnum);
    igMetaObject_NameFields(meta, g_igPolygonModeAttr_fieldTable, g_igPolygonModeAttr_fieldHandles, g_igPolygonModeAttr_fieldOffsets, base);
}

