igMetaObject *FUN_0044e6b0(void) {
    if (g_igGuiSystemRenderer_metaObject[0] == 0) {
        g_igGuiSystemRenderer_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igGuiSystemRenderer_metaObject[0];
}

igMetaObject *igGuiSystemRenderer_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiSystemRenderer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiSystemRenderer_RunStaticInit();
    return g_igGuiSystemRenderer_metaObject[0];
}

int igGuiSystemRenderer_GetVTable(void) {
    struct Obj_44e750 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00540fb0[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00540fb0[0];
    FUN_00197160(&obj.w6, -1);
    FUN_001d9870(&obj.w5, -1);
    FUN_0044e0e0((Ref **)&obj.w4, -1);
    FUN_00198210(&obj.w3, -1);
    FUN_00230f70(&obj, 0);
    return t;
}

void igGuiSystemRenderer_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiSystemRenderer_Register);
}

void igGuiSystemRenderer_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiSystemRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igGuiSystemRenderer_GetMetaObject,
        igGuiSystemRenderer_className,
        0x1C, /* instance size */
        igGuiSystemRenderer_GetVTable,
        &igGuiSystemRenderer_InitFields,
        0, /* extra callback item */
        g_igGuiSystemRenderer_callbackList /* callback list */
    );
}

void thunk_igGuiSystemRenderer_GetMetaObject(void) {
    igGuiSystemRenderer_GetMetaObject();
}

void igGuiSystemRenderer_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igGuiSystemRenderer_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igGuiSystemRenderer_ctorTable[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019cd50();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0044f210();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_001a38e0();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_00137fb0();
    igMetaObject_NameFields(temp_s0, &g_igGuiSystemRenderer_fieldTable[0], &DAT_004d02a0[0], &DAT_004d02b0[0], temp_s2);
}

