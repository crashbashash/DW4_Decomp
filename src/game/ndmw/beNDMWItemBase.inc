igMetaObject *FUN_003c92c0(void) {
    if (g_beNDMWItemBase_metaObject[0] == 0) {
        g_beNDMWItemBase_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWItemBase_metaObject[0];
}

void *beNDMWItemBase_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWItemBase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c9360();
    }
    return g_beNDMWItemBase_metaObject[0];
}

void FUN_003c9360(void)
{
    igMetaObject_RunStaticInit(beNDMWItemBase_Register);
}

void *beNDMWItemBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWItemBase_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWItemBase_GetMetaObject,
        beNDMWItemBase_className,
        0x14, /* instance size */
        0,
        beNDMWItemBase_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemBase_GetMetaObject(void)
{
    beNDMWItemBase_ResolveMetaObject();
}

void beNDMWItemBase_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWItemBase_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc130[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004cc140[0], &DAT_004cc150[0], &DAT_004cc160[0], temp_s1);
}

