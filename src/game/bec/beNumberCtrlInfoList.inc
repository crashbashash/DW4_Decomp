igMetaObject *g_beNumberCtrlInfoList_metaObject;

void *beNumberCtrlInfoList_GetMetaObject(void) {
    igMetaObject *g = g_beNumberCtrlInfoList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNumberCtrlInfoList_EnsureRegistered();
    }
    return g_beNumberCtrlInfoList_metaObject;
}

int beNumberCtrlInfoList_GetVTable(void) {
    struct Obj_34e0a0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beNumberCtrlInfoList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beNumberCtrlInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNumberCtrlInfoList_Register);
}

static igMetaObjectCallback g_beNumberCtrlInfoList_callbackList[] = { beNumberCtrlInfo_EnsureRegistered, 0 };

void *beNumberCtrlInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNumberCtrlInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNumberCtrlInfoList_GetMetaObjectFunction,
        "beNumberCtrlInfoList",
        0x14, /* instance size */
        beNumberCtrlInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNumberCtrlInfoList_callbackList /* callback list */
    );
}

void beNumberCtrlInfoList_GetMetaObjectFunction(void)
{
    beNumberCtrlInfoList_GetMetaObject();
}

