igMetaObject *g_beNDMWSaveCtrlInfo_metaObject;

void *beNDMWSaveCtrlInfo_GetMetaObject(void) {
    unsigned char b;
    if (g_beNDMWSaveCtrlInfo_metaObject != 0) {
        b = (g_beNDMWSaveCtrlInfo_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beNDMWSaveCtrlInfo_EnsureRegistered();
done:
    return g_beNDMWSaveCtrlInfo_metaObject;
}

int beNDMWSaveCtrlInfo_GetVTable(void) {
    beNDMWSaveCtrlInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    *(int **)&obj._vtable = &g_beNDMWSaveCtrlInfo_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWSaveCtrlInfo_vtable[0];
    beBaseInfo_Destroy((beBaseInfo *)&obj, 0);
    return vtable;
}

void beNDMWSaveCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveCtrlInfo_Register);
}

CallbackArray *beNDMWSaveCtrlInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWSaveCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWSaveCtrlInfo_GetMetaObjectFunction,
        "beNDMWSaveCtrlInfo",
        0x1c, /* instance size */
        beNDMWSaveCtrlInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWSaveCtrlInfo_GetMetaObjectFunction(void)
{
    beNDMWSaveCtrlInfo_GetMetaObject();
}

