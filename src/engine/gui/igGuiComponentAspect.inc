igMetaObject *g_igGuiComponentAspect_metaObject;
igMetaField *g_igGuiComponentAspect_nodeMetaField;
igMetaField *g_igGuiComponentAspect_minSizeMetaField;
igMetaField *g_igGuiComponentAspect_maxSizeMetaField;

igMetaObject *FUN_0044fbb0(void) {
    if (g_igGuiComponentAspect_metaObject == 0) {
        g_igGuiComponentAspect_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGuiComponentAspect_metaObject;
}

igMetaObject *igGuiComponentAspect_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentAspect_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentAspect_EnsureRegistered();
    return g_igGuiComponentAspect_metaObject;
}

void igGuiComponentAspect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponentAspect_Register);
}

static igMetaObjectCallback g_igGuiComponentAspect_callbackList[] = { igGuiComponentNode_RunStaticInit, 0 };

CallbackArray *igGuiComponentAspect_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igGuiComponentAspect_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igGuiComponentAspect_GetMetaObject,
        "igGuiComponentAspect",
        0x28, /* instance size */
        0,
        &igGuiComponentAspect_InitFields,
        0, /* extra callback item */
        g_igGuiComponentAspect_callbackList /* callback list */
    );
}

void thunk_igGuiComponentAspect_GetMetaObject(void) {
    igGuiComponentAspect_GetMetaObject();
}

static FieldFactory g_igGuiComponentAspect_ctorTable[] = {
    igObjectRefMetaField_Create,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igVec3fMetaField_CreateInstance,
};
static const char *g_igGuiComponentAspect_fieldTable[] = {
    "_node",
    "_minSize",
    "_maxSize",
};
static igMetaField **g_igGuiComponentAspect_fieldHandles[] = {
    &g_igGuiComponentAspect_nodeMetaField,
    &g_igGuiComponentAspect_minSizeMetaField,
    &g_igGuiComponentAspect_maxSizeMetaField,
};
static int g_igGuiComponentAspect_fieldOffsets[] = {
    12,
    16,
    28,
};

void igGuiComponentAspect_InitFields(void) {
    float v1[3];
    float v2[4];
    void *temp_a0_2;
    void *temp_a0;
    int temp_s2;
    struct GuiAspectMetaField *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igGuiComponentAspect_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igGuiComponentAspect_ctorTable, 3);
    temp_s1 = (struct GuiAspectMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    temp_s1->f56 = (int)FUN_0044f540();
    temp_s1->b60 = 0;
    temp_a0 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    v1[0] = 0.0f;
    v1[1] = 0.0f;
    v1[2] = 0.0f;
    igVec3fMetaField_SetDefault(temp_a0, v1);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2));
    v2[2] = 1.0f;
    v2[0] = 3.4028235e+38f;
    v2[1] = 3.4028235e+38f;
    igVec3fMetaField_SetDefault(temp_a0_2, v2);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igGuiComponentAspect_fieldTable, g_igGuiComponentAspect_fieldHandles, g_igGuiComponentAspect_fieldOffsets, temp_s2);
}

