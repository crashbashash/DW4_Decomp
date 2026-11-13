void beNDMWItemYellowArmor_Create(int arg0) {
    FUN_003c8a40();
    igMetaObject_CreateInstance(*(int *)0x58BF50, arg0);
}

void *beNDMWItemYellowArmor_GetReadyMetaObject(void) {
    bool ok;
    if (g_beNDMWItemYellowArmor_metaObject[0] == 0) goto make;
    ok = !!(g_beNDMWItemYellowArmor_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_003c8a40();
done:;
    return g_beNDMWItemYellowArmor_metaObject[0];
}

int beNDMWItemYellowArmor_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00540880[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003c8a40(void)
{
    igMetaObject_RunStaticInit(beNDMWItemYellowArmor_Register);
}

void *beNDMWItemYellowArmor_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemYellowArmor_metaObject,
        beNDMWItemRevisionBase_Register,
        beNDMWItemRevisionBase_GetPublishedMetaObject,
        beNDMWItemYellowArmor_GetMetaObject,
        beNDMWItemYellowArmor_className,
        0x18, /* instance size */
        beNDMWItemYellowArmor_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemYellowArmor_GetMetaObject(void)
{
    beNDMWItemYellowArmor_GetReadyMetaObject();
}

igMetaObject *FUN_003c8af0(void) {
    return g_beNDMWItemRevisionBase_metaObject[0];
}

