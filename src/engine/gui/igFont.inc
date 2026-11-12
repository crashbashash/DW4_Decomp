igMetaObject *FUN_004507f0(void) {
    if (g_igFont_metaObject[0] == 0) {
        g_igFont_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igFont_metaObject[0];
}

igMetaObject *igFont_GetMetaObject(void)
{
    igMetaObject *g = g_igFont_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFont_EnsureRegistered();
    return g_igFont_metaObject[0];
}

void igFont_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFont_Register);
}

void igFont_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igFont_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igFont_GetMetaObject,
        igFont_className,
        0x1C, /* instance size */
        0,
        &igFont_InitFields,
        0, /* extra callback item */
        g_igFont_callbackList /* callback list */
    );
}

void thunk_igFont_GetMetaObject(void) {
    igFont_GetMetaObject();
}

void igFont_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igFont_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0680[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d0690[0], &DAT_004d06a0[0], &DAT_004d06b0[0], temp_s2);
}

