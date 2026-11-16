igMetaObject *g_beNDMWItemYellowArmor_metaObject;

void beNDMWItemYellowArmor_Create(int allocator) {
    beNDMWItemYellowArmor_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWItemYellowArmor_metaObject, allocator);
}

void *beNDMWItemYellowArmor_GetReadyMetaObject(void) {
    bool ok;
    if (g_beNDMWItemYellowArmor_metaObject == 0) goto make;
    ok = !!(g_beNDMWItemYellowArmor_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNDMWItemYellowArmor_EnsureRegistered();
done:;
    return g_beNDMWItemYellowArmor_metaObject;
}

int beNDMWItemYellowArmor_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beNDMWItemYellowArmor_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beNDMWItemYellowArmor_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWItemYellowArmor_Register);
}

void *beNDMWItemYellowArmor_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWItemYellowArmor_metaObject,
        beNDMWItemRevisionBase_Register,
        beNDMWItemRevisionBase_GetPublishedMetaObject,
        beNDMWItemYellowArmor_GetMetaObject,
        "beNDMWItemYellowArmor",
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

igMetaObject *beNDMWItemRevisionBase_GetPublishedMetaObject(void) {
    return g_beNDMWItemRevisionBase_metaObject;
}

