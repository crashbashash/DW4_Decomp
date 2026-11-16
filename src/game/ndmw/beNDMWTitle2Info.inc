igMetaObject *g_beNDMWTitle2Info_metaObject;

void *beNDMWTitle2Info_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWTitle2Info_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWTitle2Info_EnsureRegistered();
    }
    return g_beNDMWTitle2Info_metaObject;
}

int beNDMWTitle2Info_GetVTable(void) {
    beNDMWTitle2Info obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    *(int **)&obj._vtable = &g_beNDMWTitle2Info_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWTitle2Info_vtable[0];
    beBaseInfo_Destroy((beBaseInfo *)&obj, 0);
    return vtable;
}

void beNDMWTitle2Info_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWTitle2Info_Register);
}

CallbackArray *beNDMWTitle2Info_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWTitle2Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWTitle2Info_GetMetaObjectFunction,
        "beNDMWTitle2Info",
        0x1c, /* instance size */
        beNDMWTitle2Info_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWTitle2Info_GetMetaObjectFunction(void)
{
    beNDMWTitle2Info_GetMetaObject();
}

