igMetaObject *g_beNDMWStatusInfo_metaObject;

void *beNDMWStatusInfo_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusInfo_EnsureRegistered();
    }
    return g_beNDMWStatusInfo_metaObject;
}

int beNDMWStatusInfo_GetVTable(void) {
    beNDMWStatusInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    *(int **)&obj._vtable = &g_beNDMWStatusInfo_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatusInfo_vtable[0];
    beBaseInfo_Destroy(&obj, 0);
    return vtable;
}

void beNDMWStatusInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusInfo_Register);
}

void *beNDMWStatusInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWStatusInfo_GetMetaObjectFunction,
        "beNDMWStatusInfo",
        0x1c, /* instance size */
        beNDMWStatusInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusInfo_GetMetaObjectFunction(void)
{
    beNDMWStatusInfo_GetMetaObject();
}

