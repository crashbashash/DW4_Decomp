igMetaObject *g_beLayerInfoRam_metaObject;

void *beLayerInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beLayerInfoRam_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beLayerInfoRam_EnsureRegistered();
    }
    return g_beLayerInfoRam_metaObject;
}

int beLayerInfoRam_GetVTable(void) {
    beLayerInfoRam obj;
    int vtable;
    igObject **dataListSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beBaseInfoRam_vtable[0];
    dataListSlot = (igObject **)&obj._dataList;
    *dataListSlot = 0;
    obj._vtable = (int)&g_beLayerInfoRam_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beBaseInfoRam_vtable[0];
    igObjectRef_Release(dataListSlot);
    return vtable;
}

void beLayerInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLayerInfoRam_Register);
}

CallbackArray *beLayerInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLayerInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beLayerInfoRam_GetMetaObjectFunction,
        "beLayerInfoRam",
        0x2c, /* instance size */
        beLayerInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beLayerInfoRam_GetMetaObjectFunction(void)
{
    beLayerInfoRam_GetMetaObject();
}

