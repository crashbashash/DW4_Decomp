igMetaObject *g_beNDMWPanelWazaInfo_metaObject;

void *beNDMWPanelWazaInfo_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWPanelWazaInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWPanelWazaInfo_EnsureRegistered();
    }
    return g_beNDMWPanelWazaInfo_metaObject;
}

int beNDMWPanelWazaInfo_GetVTable(void) {
    struct Obj_3bd6e0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.vt = &g_beNDMWPanelWazaInfo_vtable[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWPanelWazaInfo_vtable[0];
    FUN_0033ec80(&obj, 0);
    return t;
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

