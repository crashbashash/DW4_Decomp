igMetaObject *g_beNDMWLoadIntf2Info_metaObject;

void *beNDMWLoadIntf2Info_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2Info_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWLoadIntf2Info_EnsureRegistered();
    }
    return g_beNDMWLoadIntf2Info_metaObject;
}

int beNDMWLoadIntf2Info_GetVTable(void) {
    beNDMWLoadIntf2Info obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2Info_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2Info_vtable[0];
    beBaseInfo_Destroy((beBaseInfo *)&obj, 0);
    return vtable;
}

void beNDMWLoadIntf2Info_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2Info_Register);
}

CallbackArray *beNDMWLoadIntf2Info_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWLoadIntf2Info_GetMetaObject,
        "beNDMWLoadIntf2Info",
        0x1c, /* instance size */
        beNDMWLoadIntf2Info_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWLoadIntf2Info_GetMetaObject(void)
{
    beNDMWLoadIntf2Info_GetReadyMetaObject();
}

