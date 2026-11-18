igMetaObject *g_beSeInfo_metaObject;

void *beSeInfo_GetMetaObject(void) {
    igMetaObject *g = g_beSeInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSeInfo_EnsureRegistered();
    }
    return g_beSeInfo_metaObject;
}

int beSeInfo_GetVTable(void) {
    beSeInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beSeInfo_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSeInfo_vtable[0];
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

void beSeInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSeInfo_Register);
}

CallbackArray *beSeInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSeInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beSeInfo_GetMetaObjectFunction,
        "beSeInfo",
        0x1c, /* instance size */
        beSeInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSeInfo_GetMetaObjectFunction(void)
{
    beSeInfo_GetMetaObject();
}

