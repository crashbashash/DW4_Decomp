igMetaObject *g_beTextureCtrlInfoList_metaObject;

igMetaObject *beTextureCtrlInfoList_GetMetaObject(void) {
    igMetaObject *g = g_beTextureCtrlInfoList_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beTextureCtrlInfoList_EnsureRegistered();
    return g_beTextureCtrlInfoList_metaObject;
}

int beTextureCtrlInfoList_GetVTable(void) {
    beTextureCtrlInfoList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beTextureCtrlInfoList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void beTextureCtrlInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlInfoList_Register);
}

static igMetaObjectCallback g_beTextureCtrlInfoList_callbackList[] = { beTextureCtrlInfo_EnsureRegistered, 0 };

CallbackArray *beTextureCtrlInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTextureCtrlInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beTextureCtrlInfoList_GetMetaObjectFunction,
        "beTextureCtrlInfoList",
        0x14, /* instance size */
        beTextureCtrlInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beTextureCtrlInfoList_callbackList /* callback list */
    );
}

void beTextureCtrlInfoList_GetMetaObjectFunction(void)
{
    beTextureCtrlInfoList_GetMetaObject();
}

