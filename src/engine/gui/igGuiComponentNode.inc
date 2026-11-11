int FUN_0044f540(void) {
    if (DAT_0058c428[0] == 0) {
        DAT_0058c428[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c428[0];
}

igMetaObject *igGuiComponentNode_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentNode_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentNode_RunStaticInit();
    return g_igGuiComponentNode_metaObject[0];
}

int igGuiComponentNode_GetVTable(void) {
    struct Obj_44f5e0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.vt = &DAT_005411d0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_005411d0[0];
    FUN_00195a90(&obj, 0);
    return t;
}

void igGuiComponentNode_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiComponentNode_Register);
}

void igGuiComponentNode_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiComponentNode_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igGuiComponentNode_GetMetaObject,
        igGuiComponentNode_className,
        0x24, /* instance size */
        igGuiComponentNode_GetVTable,
        &igGuiComponentNode_InitFields,
        0, /* extra callback item */
        g_igGuiComponentNode_callbackList /* callback list */
    );
}

void thunk_igGuiComponentNode_GetMetaObject(void) {
    igGuiComponentNode_GetMetaObject();
}

void igGuiComponentNode_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c428[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0488[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0044ff40();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004d0490[0], &DAT_004d0498[0], &DAT_004d04a0[0], temp_s2);
}

