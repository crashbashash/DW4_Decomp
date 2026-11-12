void *FUN_0034e050(void) {
    igMetaObject *g = g_beNumberCtrlInfoList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034e0e0();
    }
    return g_beNumberCtrlInfoList_metaObject[0];
}

int beNumberCtrlInfoList_GetVTable(void) {
    struct Obj_34e0a0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005382c0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0034e0e0(void)
{
    igMetaObject_RunStaticInit(beNumberCtrlInfoList_Register);
}

void *beNumberCtrlInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumberCtrlInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNumberCtrlInfoList_GetMetaObject,
        beNumberCtrlInfoList_className,
        0x14, /* instance size */
        beNumberCtrlInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNumberCtrlInfoList_callbackList /* callback list */
    );
}

void beNumberCtrlInfoList_GetMetaObject(void)
{
    FUN_0034e050();
}

