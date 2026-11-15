igMetaObject *g_beTextureCtrlInfoList_metaObject;

igMetaObject *FUN_00341aa0(void) {
    igMetaObject *g = g_beTextureCtrlInfoList_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_00341b30();
    return g_beTextureCtrlInfoList_metaObject;
}

int beTextureCtrlInfoList_GetVTable(void) {
    struct Obj_341af0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00539690[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00341b30(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlInfoList_Register);
}

static igMetaObjectCallback g_beTextureCtrlInfoList_callbackList[] = { FUN_00341cb0, 0 };

void *beTextureCtrlInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTextureCtrlInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beTextureCtrlInfoList_GetMetaObject,
        "beTextureCtrlInfoList",
        0x14, /* instance size */
        beTextureCtrlInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beTextureCtrlInfoList_callbackList /* callback list */
    );
}

void beTextureCtrlInfoList_GetMetaObject(void)
{
    FUN_00341aa0();
}

