void FUN_003c87f0(int arg0) {
    FUN_003c88c0();
    igMetaObject_CreateInstance(*(int *)0x58BF48, arg0);
}

void *beNDMWItemAbilityChip_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemAbilityChip_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c88c0();
    }
    return g_beNDMWItemAbilityChip_metaObject[0];
}

int beNDMWItemAbilityChip_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00540810[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003c88c0(void)
{
    igMetaObject_RunStaticInit(beNDMWItemAbilityChip_Register);
}

void *beNDMWItemAbilityChip_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemAbilityChip_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemAbilityChip_GetMetaObject,
        beNDMWItemAbilityChip_className,
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

