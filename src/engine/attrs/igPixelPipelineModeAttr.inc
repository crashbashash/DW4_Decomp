void FUN_00134b60(int arg0) {
    FUN_00134c30();
    igMetaObject_CreateInstance(*(int *)0x55EF70, arg0);
}

igMetaObject *igPixelPipelineModeAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igPixelPipelineModeAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00134c30();
    return g_igPixelPipelineModeAttr_metaObject[0];
}

int igPixelPipelineModeAttr_GetVTable(void) {
    union U_134bf0 u;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00523200[0]);
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_00134c30(void)
{
    igMetaObject_RunStaticInit(igPixelPipelineModeAttr_Register);
}

void igPixelPipelineModeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPixelPipelineModeAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igPixelPipelineModeAttr_GetMetaObject,
        igPixelPipelineModeAttr_className,
        0x10, /* instance size */
        igPixelPipelineModeAttr_GetVTable,
        &igPixelPipelineModeAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igPixelPipelineModeAttr_GetMetaObject(void) {
    igPixelPipelineModeAttr_GetMetaObject();
}

void igPixelPipelineModeAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)g_igPixelPipelineModeAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486128[0], 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00486148[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00149800);
    igMetaObject_NameFields(temp_s0, &DAT_00486130[0], &DAT_00486138[0], &DAT_00486140[0], temp_s2);
}

