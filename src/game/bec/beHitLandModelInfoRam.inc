igMetaObject *g_beHitLandModelInfoRam_metaObject;

igMetaObject *beHitLandModelInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beHitLandModelInfoRam_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beHitLandModelInfoRam_EnsureRegistered();
done:
    return g_beHitLandModelInfoRam_metaObject;
}

int beHitLandModelInfoRam_GetVTable(void) {
    beHitLandModelInfoRam obj;
    int vtable;
    igObject **dataListSlot;

    igObject_InitHeader(&obj);
    dataListSlot = (igObject **)&obj._dataList;
    *dataListSlot = 0;
    obj._vtable = (int)&g_beBaseInfoRam_vtable[0];
    obj._vtable = (int)&g_beHitLandModelInfoRam_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beBaseInfoRam_vtable[0];
    igObjectRef_Release(dataListSlot);
    return vtable;
}

void beHitLandModelInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beHitLandModelInfoRam_Register);
}

CallbackArray *beHitLandModelInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beHitLandModelInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beHitLandModelInfoRam_GetMetaObjectFunction,
        "beHitLandModelInfoRam",
        0x2c, /* instance size */
        beHitLandModelInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beHitLandModelInfoRam_GetMetaObjectFunction(void)
{
    beHitLandModelInfoRam_GetMetaObject();
}

