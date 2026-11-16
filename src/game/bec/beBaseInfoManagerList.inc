igMetaObject *g_beBaseInfoManagerList_metaObject;

igMetaObject *beBaseInfoManagerList_GetMetaObject(void)
{
    igMetaObject *g = g_beBaseInfoManagerList_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beBaseInfoManagerList_EnsureRegistered();
    return g_beBaseInfoManagerList_metaObject;
}

int beBaseInfoManagerList_GetVTable(void) {
    beBaseInfoManagerList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beBaseInfoManagerList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void beBaseInfoManagerList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBaseInfoManagerList_Register);
}

static igMetaObjectCallback g_beBaseInfoManagerList_callbackList[] = { beBaseInfoManager_EnsureRegistered, 0 };

CallbackArray *beBaseInfoManagerList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beBaseInfoManagerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beBaseInfoManagerList_GetMetaObjectFunction,
        "beBaseInfoManagerList",
        0x14, /* instance size */
        beBaseInfoManagerList_GetVTable,
        0,
        0, /* extra callback item */
        g_beBaseInfoManagerList_callbackList /* callback list */
    );
}

void beBaseInfoManagerList_GetMetaObjectFunction(void)
{
    beBaseInfoManagerList_GetMetaObject();
}

