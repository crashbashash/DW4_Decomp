igMetaObject *g_beMeterCtrlInfoList_metaObject;

void *FUN_00356f60(void) {
    igMetaObject *g = g_beMeterCtrlInfoList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00356ff0();
    }
    return g_beMeterCtrlInfoList_metaObject;
}

int beMeterCtrlInfoList_GetVTable(void) {
    int obj[8];

    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_005370b0[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_00356ff0(void)
{
    igMetaObject_RunStaticInit(beMeterCtrlInfoList_Register);
}

static igMetaObjectCallback g_beMeterCtrlInfoList_callbackList[] = { FUN_00357170, 0 };

void *beMeterCtrlInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMeterCtrlInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMeterCtrlInfoList_GetMetaObject,
        "beMeterCtrlInfoList",
        0x14, /* instance size */
        beMeterCtrlInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMeterCtrlInfoList_callbackList /* callback list */
    );
}

void beMeterCtrlInfoList_GetMetaObject(void)
{
    FUN_00356f60();
}

