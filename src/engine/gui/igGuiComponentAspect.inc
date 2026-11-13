igMetaObject *FUN_0044fbb0(void) {
    if (g_igGuiComponentAspect_metaObject[0] == 0) {
        g_igGuiComponentAspect_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igGuiComponentAspect_metaObject[0];
}

igMetaObject *igGuiComponentAspect_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentAspect_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentAspect_EnsureRegistered();
    return g_igGuiComponentAspect_metaObject[0];
}

void igGuiComponentAspect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponentAspect_Register);
}

void igGuiComponentAspect_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igGuiComponentAspect_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igGuiComponentAspect_GetMetaObject,
        igGuiComponentAspect_className,
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

void igGuiComponentAspect_InitFields(void) {
    float v1[3];
    float v2[4];
    void *temp_a0_2;
    void *temp_a0;
    int temp_s2;
    struct GuiAspectMetaField *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igGuiComponentAspect_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igGuiComponentAspect_ctorTable[0], 3);
    temp_s1 = (struct GuiAspectMetaField *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    temp_s1->f56 = (int)FUN_0044f540();
    temp_s1->b60 = 0;
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    v1[0] = 0.0f;
    v1[1] = 0.0f;
    v1[2] = 0.0f;
    FUN_0018e470(temp_a0, v1);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    v2[2] = 1.0f;
    v2[0] = 3.4028235e+38f;
    v2[1] = 3.4028235e+38f;
    FUN_0018e470(temp_a0_2, v2);
    igMetaObject_NameFields(temp_s0, &g_igGuiComponentAspect_fieldTable[0], &DAT_004d0558[0], &DAT_004d0568[0], temp_s2);
}

