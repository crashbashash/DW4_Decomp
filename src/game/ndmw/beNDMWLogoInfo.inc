igMetaObject *g_beNDMWLogoInfo_metaObject;

void *beNDMWLogoInfo_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLogoInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWLogoInfo_EnsureRegistered();
    }
    return g_beNDMWLogoInfo_metaObject;
}

int beNDMWLogoInfo_GetVTable(void) {
    beNDMWLogoInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    *(int **)&obj._vtable = &g_beNDMWLogoInfo_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWLogoInfo_vtable[0];
    beBaseInfo_Destroy((beBaseInfo *)&obj, 0);
    return vtable;
}

void beNDMWLogoInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLogoInfo_Register);
}

CallbackArray *beNDMWLogoInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLogoInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWLogoInfo_GetMetaObject,
        "beNDMWLogoInfo",
        0x1c, /* instance size */
        beNDMWLogoInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWLogoInfo_GetMetaObject(void)
{
    beNDMWLogoInfo_GetReadyMetaObject();
}

