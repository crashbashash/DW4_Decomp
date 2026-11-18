igMetaObject *g_beMeterCtrlInfoList_metaObject;

void *beMeterCtrlInfoList_GetMetaObject(void) {
    igMetaObject *g = g_beMeterCtrlInfoList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMeterCtrlInfoList_EnsureRegistered();
    }
    return g_beMeterCtrlInfoList_metaObject;
}

int beMeterCtrlInfoList_GetVTable(void) {
    beMeterCtrlInfoList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beMeterCtrlInfoList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beMeterCtrlInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMeterCtrlInfoList_Register);
}

static igMetaObjectCallback g_beMeterCtrlInfoList_callbackList[] = { beMeterCtrlInfo_EnsureRegistered, 0 };

CallbackArray *beMeterCtrlInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMeterCtrlInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMeterCtrlInfoList_GetMetaObjectFunction,
        "beMeterCtrlInfoList",
        0x14, /* instance size */
        beMeterCtrlInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMeterCtrlInfoList_callbackList /* callback list */
    );
}

void beMeterCtrlInfoList_GetMetaObjectFunction(void)
{
    beMeterCtrlInfoList_GetMetaObject();
}

