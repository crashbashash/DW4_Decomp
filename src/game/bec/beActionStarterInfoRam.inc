igMetaObject *g_beActionStarterInfoRam_metaObject;

void *beActionStarterInfoRam_GetMetaObject(void) {
    bool ok;
    if (g_beActionStarterInfoRam_metaObject == 0) goto make;
    ok = !!(g_beActionStarterInfoRam_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beActionStarterInfoRam_EnsureRegistered();
done:;
    return g_beActionStarterInfoRam_metaObject;
}

int beActionStarterInfoRam_GetVTable(void) {
    beActionStarterInfoRam obj;
    int vtable;
    igObject **dataListSlot;

    igObject_InitHeader(&obj);
    dataListSlot = (igObject **)&obj._dataList;
    *dataListSlot = 0;
    obj._vtable = (int)&g_beBaseInfoRam_vtable[0];
    obj._vtable = (int)&g_beActionStarterInfoRam_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beBaseInfoRam_vtable[0];
    igObjectRef_Release(dataListSlot);
    return vtable;
}

void beActionStarterInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beActionStarterInfoRam_Register);
}

CallbackArray *beActionStarterInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beActionStarterInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beActionStarterInfoRam_GetMetaObjectFunction,
        "beActionStarterInfoRam",
        0x2c, /* instance size */
        beActionStarterInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beActionStarterInfoRam_GetMetaObjectFunction(void)
{
    beActionStarterInfoRam_GetMetaObject();
}

