igMetaObject *g_beNDMWPanelWazaInfo_metaObject;

void *beNDMWPanelWazaInfo_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWPanelWazaInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWPanelWazaInfo_EnsureRegistered();
    }
    return g_beNDMWPanelWazaInfo_metaObject;
}

int beNDMWPanelWazaInfo_GetVTable(void) {
    beNDMWPanelWazaInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    *(int **)&obj._vtable = &g_beNDMWPanelWazaInfo_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWPanelWazaInfo_vtable[0];
    beBaseInfo_Destroy(&obj, 0);
    return vtable;
}

void beNDMWPanelWazaInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelWazaInfo_Register);
}

void *beNDMWPanelWazaInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWPanelWazaInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWPanelWazaInfo_GetMetaObject,
        "beNDMWPanelWazaInfo",
        0x1c, /* instance size */
        beNDMWPanelWazaInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWPanelWazaInfo_GetMetaObject(void)
{
    beNDMWPanelWazaInfo_ResolveMetaObject();
}

