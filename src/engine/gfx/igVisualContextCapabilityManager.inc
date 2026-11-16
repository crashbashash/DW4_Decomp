igMetaObject *g_igVisualContextCapabilityManager_metaObject;
igMetaField *g_igVisualContextCapabilityManager_visualContextMetaField;

unsigned char g_GfxLibrary_registered;

void FUN_00149bc0(void) {
    if (g_GfxLibrary_registered == 0) {
        g_GfxLibrary_registered = 1;
        FUN_0014bbb0();
        FUN_0014bd20();
        FUN_0014c670();
        FUN_0014d5c0();
        FUN_0014d6d0();
        FUN_0014f810();
        FUN_0014f920();
        FUN_0014ff00();
    }
}

void FUN_00149c30(int arg0) {
    FUN_00149d50();
    igMetaObject_CreateInstance(g_igVisualContextCapabilityManager_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igVisualContextCapabilityManager_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualContextCapabilityManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00149d50();
    return g_igVisualContextCapabilityManager_metaObject;
}

int igVisualContextCapabilityManager_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igVisualContextCapabilityManager_vtable[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj.vt = &g_igVisualContextCapabilityManager_vtable[0];
    obj.release();
    return r;
}

void FUN_00149d50(void)
{
    igMetaObject_RunStaticInit(igVisualContextCapabilityManager_Register);
}

static igMetaObjectCallback g_igVisualContextCapabilityManager_callbackList[] = { igVisualContext_EnsureRegistered, 0 };

CallbackArray *igVisualContextCapabilityManager_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVisualContextCapabilityManager_metaObject,
        igCapabilityManager_Register,
        igCapabilityManager_GetPublishedMetaObject,
        thunk_igVisualContextCapabilityManager_GetMetaObject,
        "igVisualContextCapabilityManager",
        0xC, /* instance size */
        igVisualContextCapabilityManager_GetVTable,
        &igVisualContextCapabilityManager_InitFields,
        0, /* extra callback item */
        g_igVisualContextCapabilityManager_callbackList /* callback list */
    );
}

void thunk_igVisualContextCapabilityManager_GetMetaObject(void) {
    igVisualContextCapabilityManager_GetMetaObject();
}

igMetaObject *FUN_00149df0(void) {
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

