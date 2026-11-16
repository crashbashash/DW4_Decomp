igMetaObject *g_beNDMWStageCtlInfoRam_metaObject;

void *beNDMWStageCtlInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStageCtlInfoRam_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStageCtlInfoRam_EnsureRegistered();
    }
    return g_beNDMWStageCtlInfoRam_metaObject;
}

int beNDMWStageCtlInfoRam_GetVTable(void) {
    beNDMWStageCtlInfoRam obj;
    int vtable;
    int *dataListRef;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beBaseInfoRam_vtable[0];
    dataListRef = &obj._dataList;
    *dataListRef = 0;
    *(int **)&obj._vtable = &g_beNDMWStageCtlInfoRam_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beBaseInfoRam_vtable[0];
    if (dataListRef != 0) {
        igRelease((igObject *)*dataListRef);
    }
    return vtable;
}

void beNDMWStageCtlInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStageCtlInfoRam_Register);
}

CallbackArray *beNDMWStageCtlInfoRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStageCtlInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNDMWStageCtlInfoRam_GetMetaObjectFunction,
        "beNDMWStageCtlInfoRam",
        0x2c, /* instance size */
        beNDMWStageCtlInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStageCtlInfoRam_GetMetaObjectFunction(void)
{
    beNDMWStageCtlInfoRam_GetMetaObject();
}

