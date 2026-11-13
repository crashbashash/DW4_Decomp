void FUN_003c83c0(int arg0) {
    FUN_003c8490();
    igMetaObject_CreateInstance(*(int *)0x58BF28, arg0);
}

igMetaObject *beNDMWItemInstant_GetReadyMetaObject(void) {
    if (g_beNDMWItemInstant_metaObject[0] == 0 || !isValid(g_beNDMWItemInstant_metaObject[0])) FUN_003c8490();
    return g_beNDMWItemInstant_metaObject[0];
}

int beNDMWItemInstant_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00540730[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003c8490(void)
{
    igMetaObject_RunStaticInit(beNDMWItemInstant_Register);
}

void *beNDMWItemInstant_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemInstant_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemInstant_GetMetaObject,
        beNDMWItemInstant_className,
        0x18, /* instance size */
        beNDMWItemInstant_GetVTable,
        beNDMWItemInstant_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemInstant_GetMetaObject(void)
{
    beNDMWItemInstant_GetReadyMetaObject();
}

void beNDMWItemInstant_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWItemInstant_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWItemInstant_ctorTable[0], 1);
    igMetaObject_NameFields(temp_s0, &g_beNDMWItemInstant_fieldTable[0], &DAT_004cc0b8[0], &DAT_004cc0c0[0], temp_s1);
}

