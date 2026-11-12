void FUN_003c8240(int arg0) {
    FUN_003c8310();
    igMetaObject_CreateInstance(*(int *)0x58BF20, arg0);
}

igMetaObject *beNDMWItemImportant_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemImportant_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_003c8310();
done:
    return g_beNDMWItemImportant_metaObject[0];
}

int beNDMWItemImportant_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005406c0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003c8310(void)
{
    igMetaObject_RunStaticInit(beNDMWItemImportant_Register);
}

void *beNDMWItemImportant_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemImportant_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemImportant_GetMetaObject,
        beNDMWItemImportant_className,
        0x14, /* instance size */
        beNDMWItemImportant_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemImportant_GetMetaObject(void)
{
    beNDMWItemImportant_GetReadyMetaObject();
}

