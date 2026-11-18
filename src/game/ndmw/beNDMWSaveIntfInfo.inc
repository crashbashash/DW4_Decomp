igMetaObject *g_beNDMWSaveIntfInfo_metaObject;

igMetaObject *beNDMWSaveIntfInfo_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWSaveIntfInfo_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWSaveIntfInfo_EnsureRegistered();
done:
    return g_beNDMWSaveIntfInfo_metaObject;
}

int beNDMWSaveIntfInfo_GetVTable(void) {
    beNDMWSaveIntfInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    *(int **)&obj._vtable = &g_beNDMWSaveIntfInfo_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWSaveIntfInfo_vtable[0];
    beBaseInfo_Destroy((beBaseInfo *)&obj, 0);
    return vtable;
}

void beNDMWSaveIntfInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveIntfInfo_Register);
}

CallbackArray *beNDMWSaveIntfInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWSaveIntfInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWSaveIntfInfo_GetMetaObjectFunction,
        "beNDMWSaveIntfInfo",
        0x1c, /* instance size */
        beNDMWSaveIntfInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWSaveIntfInfo_GetMetaObjectFunction(void)
{
    beNDMWSaveIntfInfo_GetMetaObject();
}

