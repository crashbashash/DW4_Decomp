igMetaObject *g_beChangePosTransformInfo_metaObject;

igMetaObject *beChangePosTransformInfo_GetMetaObject(void) {
    igMetaObject *g = g_beChangePosTransformInfo_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beChangePosTransformInfo_EnsureRegistered();
done:
    return g_beChangePosTransformInfo_metaObject;
}

int beChangePosTransformInfo_GetVTable(void) {
    beChangePosTransformInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beChangePosTransformInfo_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beChangePosTransformInfo_vtable[0];
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

void beChangePosTransformInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beChangePosTransformInfo_Register);
}

CallbackArray *beChangePosTransformInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beChangePosTransformInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beChangePosTransformInfo_GetMetaObjectFunction,
        "beChangePosTransformInfo",
        0x1c, /* instance size */
        beChangePosTransformInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beChangePosTransformInfo_GetMetaObjectFunction(void)
{
    beChangePosTransformInfo_GetMetaObject();
}

