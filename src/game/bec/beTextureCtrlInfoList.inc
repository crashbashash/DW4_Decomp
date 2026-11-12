G_341aa0 *FUN_00341aa0(void) {
    G_341aa0 *g = DAT_00587c78[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00341b30();
    return DAT_00587c78[0];
}

int beTextureCtrlInfoList_GetVTable(void) {
    struct Obj_341af0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00539690[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00341b30(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlInfoList_Register);
}

void *beTextureCtrlInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTextureCtrlInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beTextureCtrlInfoList_GetMetaObject,
        beTextureCtrlInfoList_className,
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

