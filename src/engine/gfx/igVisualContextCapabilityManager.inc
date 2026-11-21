igMetaObject *g_igVisualContextCapabilityManager_metaObject;
igMetaField *g_igVisualContextCapabilityManager_visualContextMetaField;

unsigned char g_GfxLibrary_registered;

void GfxLibrary_MarkRegistered(void) {
    if (g_GfxLibrary_registered == 0) {
        g_GfxLibrary_registered = 1;
        igUserUCodeExt_EnsureRegistered();
        igScissorExt_EnsureRegistered();
        igPointSpriteExt_EnsureRegistered();
        igMultiTextureExt_EnsureRegistered();
        igLineWidthExt_EnsureRegistered();
        igDisableExt_EnsureRegistered();
        igDecalExt_EnsureRegistered();
        igBlendEquationExt_EnsureRegistered();
    }
}

igObject *igVisualContextCapabilityManager_Create(igMemoryPoolView *pool) {
    igVisualContextCapabilityManager_EnsureRegistered();
    return igMetaObject_CreateInstance(g_igVisualContextCapabilityManager_metaObject, pool);
}

igMetaObject *igVisualContextCapabilityManager_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualContextCapabilityManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVisualContextCapabilityManager_EnsureRegistered();
    return g_igVisualContextCapabilityManager_metaObject;
}

int igVisualContextCapabilityManager_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igVisualContextCapabilityManager_vtable[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igVisualContextCapabilityManager_vtable[0];
    obj.release();
    return r;
}

void igVisualContextCapabilityManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVisualContextCapabilityManager_Register);
}

static igMetaObjectCallback g_igVisualContextCapabilityManager_callbackList[] = { igVisualContext_EnsureRegistered, 0 };

CallbackArray *igVisualContextCapabilityManager_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVisualContextCapabilityManager_metaObject,
        igCapabilityManager_Register,
        igCapabilityManager_GetPublishedMetaObject,
        igVisualContextCapabilityManager_GetMetaObjectFunction,
        "igVisualContextCapabilityManager",
        0xC, /* instance size */
        igVisualContextCapabilityManager_GetVTable,
        &igVisualContextCapabilityManager_InitFields,
        0, /* extra callback item */
        g_igVisualContextCapabilityManager_callbackList /* callback list */
    );
}

void igVisualContextCapabilityManager_GetMetaObjectFunction(void) {
    igVisualContextCapabilityManager_GetMetaObject();
}

igMetaObject *igCapabilityManager_GetPublishedMetaObject(void) {
    return g_igCapabilityManager_metaObject;
}

static FieldFactory g_igVisualContextCapabilityManager_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igVisualContextCapabilityManager_fieldTable[] = {
    "_visualContext",
};
static igMetaField **g_igVisualContextCapabilityManager_fieldHandles[] = {
    &g_igVisualContextCapabilityManager_visualContextMetaField,
};
static int g_igVisualContextCapabilityManager_fieldOffsets[] = {
    8,
};

void igVisualContextCapabilityManager_InitFields(void) {
    int fieldStart;
    void *temp_s1;
    igMetaObject *meta;

    meta = g_igVisualContextCapabilityManager_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igVisualContextCapabilityManager_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
    ((igMetaField *)temp_s1)->_persistent = 0;
    igMetaObject_NameFields(meta, g_igVisualContextCapabilityManager_fieldTable, g_igVisualContextCapabilityManager_fieldHandles, g_igVisualContextCapabilityManager_fieldOffsets, fieldStart);
}

