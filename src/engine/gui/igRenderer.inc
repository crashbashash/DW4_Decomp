igMetaObject *igRenderer_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRenderer_EnsureRegistered();
    return g_igRenderer_metaObject[0];
}

void igRenderer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRenderer_Register);
}

void igRenderer_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igRenderer_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRenderer_GetMetaObject,
        igRenderer_className,
        0xC, /* instance size */
        0,
        &igRenderer_InitFields,
        0, /* extra callback item */
        g_igRenderer_callbackList /* callback list */
    );
}

void thunk_igRenderer_GetMetaObject(void) {
    igRenderer_GetMetaObject();
}

void igRenderer_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igRenderer_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igRenderer_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0014a040();
    igMetaObject_NameFields(temp_s0, &g_igRenderer_fieldTable[0], &DAT_004cffa8[0], &DAT_004cffb0[0], temp_s2);
}

