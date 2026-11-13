igMetaObject *FUN_003b1dd0(void) {
    if (g_beNDMWWindow_metaObject[0] == 0) {
        g_beNDMWWindow_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWWindow_metaObject[0];
}

void *FUN_003b1e20(void) {
    igMetaObject *g = g_beNDMWWindow_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b1e70();
    }
    return g_beNDMWWindow_metaObject[0];
}

void FUN_003b1e70(void)
{
    igMetaObject_RunStaticInit(beNDMWWindow_Register);
}

void *beNDMWWindow_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWWindow_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWWindow_GetMetaObject,
        beNDMWWindow_className,
        0x50, /* instance size */
        0,
        beNDMWWindow_InitFields,
        0, /* extra callback item */
        g_beNDMWWindow_callbackList /* callback list */
    );
}

void beNDMWWindow_GetMetaObject(void)
{
    FUN_003b1e20();
}

void beNDMWWindow_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s1;

    temp_s1 = (void *)g_beNDMWWindow_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_beNDMWWindow_ctorTable[0], 0x12);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00232840();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s2_2)->_refCounted = 0;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0034c8e0();
    ((igObjectRefMetaField *)temp_s2_3)->_refCounted = 0;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), 1);
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_003b1be0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xC));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_003b1dd0();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xD));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_002b9120();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xE));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_002b9120();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xF));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_002b9120();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x10));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x11));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_002b9120();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &g_beNDMWWindow_fieldTable[0], &DAT_004c9530[0], &DAT_004c9580[0], temp_s0);
}

