igMetaObject *g_beNDMWItemAbilityChip_metaObject;

beNDMWItemAbilityChip *beNDMWItemAbilityChip_Create(int allocator) {
    beNDMWItemAbilityChip_EnsureRegistered();
    return (beNDMWItemAbilityChip *)igMetaObject_CreateInstance(g_beNDMWItemAbilityChip_metaObject, allocator);
}

void *beNDMWItemAbilityChip_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemAbilityChip_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWItemAbilityChip_EnsureRegistered();
    }
    return g_beNDMWItemAbilityChip_metaObject;
}

int beNDMWItemAbilityChip_GetVTable(void) {
    beNDMWItemAbilityChip obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWItemAbilityChip_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beNDMWItemAbilityChip_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWItemAbilityChip_Register);
}

void *beNDMWItemAbilityChip_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWItemAbilityChip_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemAbilityChip_GetMetaObject,
        "beNDMWItemAbilityChip",
        0x14, /* instance size */
        beNDMWItemAbilityChip_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemAbilityChip_GetMetaObject(void)
{
    beNDMWItemAbilityChip_GetReadyMetaObject();
}

