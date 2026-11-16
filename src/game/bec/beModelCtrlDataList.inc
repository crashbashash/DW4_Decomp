igMetaObject *g_beModelCtrlDataList_metaObject;

igMetaObject *beModelCtrlDataList_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlDataList_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beModelCtrlDataList_EnsureRegistered();
    return g_beModelCtrlDataList_metaObject;
}

int beModelCtrlDataList_GetVTable(void) {
    beModelCtrlDataList obj;
    int off;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beModelCtrlDataList_vtable[0];
    off = *(int *)((char *)g_objectSystem + 916);
    return *(int *)((char *)&obj + off);
}

void beModelCtrlDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlDataList_Register);
}

static igMetaObjectCallback g_beModelCtrlDataList_callbackList[] = { beModelCtrlData_EnsureRegistered, 0 };

CallbackArray *beModelCtrlDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beModelCtrlDataList_GetMetaObjectFunction,
        "beModelCtrlDataList",
        0x14, /* instance size */
        beModelCtrlDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beModelCtrlDataList_callbackList /* callback list */
    );
}

void beModelCtrlDataList_GetMetaObjectFunction(void)
{
    beModelCtrlDataList_GetMetaObject();
}

