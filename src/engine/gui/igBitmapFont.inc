igMetaObject *FUN_004524f0(void) {
    if (g_igBitmapFont_metaObject[0] == 0) {
        g_igBitmapFont_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igBitmapFont_metaObject[0];
}

igMetaObject *igBitmapFont_GetMetaObject(void)
{
    igMetaObject *g = g_igBitmapFont_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igBitmapFont_RunStaticInit();
    return g_igBitmapFont_metaObject[0];
}

int igBitmapFont_GetVTable(void) {
    struct Obj_452590 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w5 = 0;
    obj.vt = &DAT_00541610[0];
    obj.w7 = 0;
    obj.w8 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00541610[0];
    FUN_0019aa10(&obj.w8, -1);
    FUN_003619a0(&obj.w7, -1);
    FUN_00361a20(&obj, 0);
    return t;
}

void igBitmapFont_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igBitmapFont_Register);
}

void igBitmapFont_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBitmapFont_metaObject,
        igFont_Register,
        igFont_GetPublishedMetaObject,
        thunk_igBitmapFont_GetMetaObject,
        igBitmapFont_className,
        0x24, /* instance size */
        igBitmapFont_GetVTable,
        &igBitmapFont_InitFields,
        0, /* extra callback item */
        g_igBitmapFont_callbackList /* callback list */
    );
}

void thunk_igBitmapFont_GetMetaObject(void) {
    igBitmapFont_GetMetaObject();
}

igMetaObject *FUN_004526c0(void) {
    return g_igFont_metaObject[0];
}

void igBitmapFont_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igBitmapFont_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igBitmapFont_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00452790();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00132850();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_igBitmapFont_fieldTable[0], &DAT_004d0880[0], &DAT_004d0888[0], temp_s2);
}

