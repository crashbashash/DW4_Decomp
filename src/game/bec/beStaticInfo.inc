igMetaObject *g_beStaticInfo_metaObject;

void *beStaticInfo_GetMetaObject(void) {
    igMetaObject *g = g_beStaticInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beStaticInfo_EnsureRegistered();
    }
    return g_beStaticInfo_metaObject;
}

int beStaticInfo_GetVTable(void) {
    beStaticInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beStaticInfo_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beStaticInfo_vtable[0];
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

void beStaticInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beStaticInfo_Register);
}

CallbackArray *beStaticInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beStaticInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beStaticInfo_GetMetaObjectFunction,
        "beStaticInfo",
        0x1c, /* instance size */
        beStaticInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beStaticInfo_GetMetaObjectFunction(void)
{
    beStaticInfo_GetMetaObject();
}

