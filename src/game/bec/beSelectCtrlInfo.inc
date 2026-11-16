igMetaObject *g_beSelectCtrlInfo_metaObject;

void *beSelectCtrlInfo_GetMetaObject(void) {
    unsigned char b;
    if (g_beSelectCtrlInfo_metaObject != 0) {
        b = (g_beSelectCtrlInfo_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beSelectCtrlInfo_EnsureRegistered();
done:
    return g_beSelectCtrlInfo_metaObject;
}

int beSelectCtrlInfo_GetVTable(void) {
    beSelectCtrlInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beSelectCtrlInfo_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beSelectCtrlInfo_vtable[0];
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

void beSelectCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSelectCtrlInfo_Register);
}

CallbackArray *beSelectCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSelectCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beSelectCtrlInfo_GetMetaObjectFunction,
        "beSelectCtrlInfo",
        0x1c, /* instance size */
        beSelectCtrlInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSelectCtrlInfo_GetMetaObjectFunction(void)
{
    beSelectCtrlInfo_GetMetaObject();
}

