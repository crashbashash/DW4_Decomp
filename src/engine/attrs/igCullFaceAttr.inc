igMetaObject *g_igCullFaceAttr_metaObject;
igMetaField *g_igCullFaceAttr_enabledMetaField;
igMetaField *g_igCullFaceAttr_modeMetaField;

void FUN_00138690(int arg0) {
    igCullFaceAttr_EnsureRegistered();
    igMetaObject_CreateInstance(*(igMetaObject * *)0x55F238, (igMemoryPoolView *)arg0);
}

igMetaObject *FUN_001386d0(void) {
    if (g_igCullFaceAttr_metaObject == 0) {
        g_igCullFaceAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCullFaceAttr_metaObject;
}

igMetaObject *igCullFaceAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igCullFaceAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCullFaceAttr_EnsureRegistered();
    return g_igCullFaceAttr_metaObject;
}

int igCullFaceAttr_GetVTable(void) {
    struct Obj_138770 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igCullFaceAttr_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void igCullFaceAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCullFaceAttr_Register);
}

CallbackArray *igCullFaceAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCullFaceAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igCullFaceAttr_GetMetaObject,
        "igCullFaceAttr",
        0x14, /* instance size */
        igCullFaceAttr_GetVTable,
        &igCullFaceAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igCullFaceAttr_GetMetaObject(void) {
    igCullFaceAttr_GetMetaObject();
}

static FieldFactory g_igCullFaceAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igCullFaceAttr_fieldTable[] = {
    "_enabled",
    "_mode",
};
static igMetaField **g_igCullFaceAttr_fieldHandles[] = {
    &g_igCullFaceAttr_enabledMetaField,
    &g_igCullFaceAttr_modeMetaField,
};
static int g_igCullFaceAttr_fieldOffsets[] = {
    12,
    16,
};

void igCullFaceAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    igMetaObject *temp_s0;

    temp_s0 = g_igCullFaceAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igCullFaceAttr_ctorTable, 2);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0, 0);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00149620);
    igMetaObject_NameFields(temp_s0, g_igCullFaceAttr_fieldTable, g_igCullFaceAttr_fieldHandles, g_igCullFaceAttr_fieldOffsets, temp_s2);
}

