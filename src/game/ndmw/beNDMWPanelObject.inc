igMetaObject *beNDMWPanelObject_ResolveMetaObject(void)
{
    igMetaObject *meta = g_beNDMWPanelObject_metaObject[0];
    if (!meta || ((meta->_validity & 4) != 0) == false) {
        FUN_003bec70();
    }
    return g_beNDMWPanelObject_metaObject[0];
}

void FUN_003bec70(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelObject_Register);
}

void *beNDMWPanelObject_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        ((igMetaObject_3bec90 * *)g_beNDMWPanelObject_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWPanelObject_GetMetaObject,
        beNDMWPanelObject_className,
        0x3c, /* instance size */
        0,
        beNDMWPanelObject_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelObject_callbackList /* callback list */
    );
}

void beNDMWPanelObject_GetMetaObject(void)
{
    beNDMWPanelObject_ResolveMetaObject();
}

void beNDMWPanelObject_InitFields(void) {
    int temp_s2;
    void *temp_s1_5;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058b2c8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca630[0], 0x10);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0036a8d0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), 2);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_00364090();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_002b9120();
    temp_s1_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xD));
    ((igObjectRefMetaField *)temp_s1_5)->_metaObject = igIntList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, &DAT_004ca670[0], &DAT_004ca6b0[0], &DAT_004ca6f0[0], temp_s2);
}

int FUN_003bee30(void) {
    if (DAT_0058b350[0] == 0) {
        DAT_0058b350[0] = igMetaEnum_Create(&DAT_00510d58[0], &DAT_004ca730[0], &DAT_004ca760[0], 0xB);
    }
    return DAT_0058b350[0];
}

