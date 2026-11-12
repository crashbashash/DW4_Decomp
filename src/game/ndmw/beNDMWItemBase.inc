int FUN_003c92c0(void) {
    if (((int *)DAT_0058bf90)[0] == 0) {
        ((int *)DAT_0058bf90)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058bf90)[0];
}

void *beNDMWItemBase_ResolveMetaObject(void) {
    struct G *g = DAT_0058bf90[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c9360();
    }
    return DAT_0058bf90[0];
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

    temp_s0 = (void *)((int *)DAT_0058bf90)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc130[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004cc140[0], &DAT_004cc150[0], &DAT_004cc160[0], temp_s1);
}

