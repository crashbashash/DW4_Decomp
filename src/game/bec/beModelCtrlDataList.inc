igMetaObject *g_beModelCtrlDataList_metaObject;

igMetaObject *FUN_00356690(void) {
    igMetaObject *g = g_beModelCtrlDataList_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_00356720();
    return g_beModelCtrlDataList_metaObject;
}

int beModelCtrlDataList_GetVTable(void) {
    int tmp[8];
    int off;

    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_00537220[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_00356720(void)
{
    igMetaObject_RunStaticInit(beModelCtrlDataList_Register);
}

static igMetaObjectCallback g_beModelCtrlDataList_callbackList[] = { FUN_00356950, 0 };

void *beModelCtrlDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beModelCtrlDataList_GetMetaObject,
        "beModelCtrlDataList",
        0x14, /* instance size */
        beModelCtrlDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beModelCtrlDataList_callbackList /* callback list */
    );
}

void beModelCtrlDataList_GetMetaObject(void)
{
    FUN_00356690();
}

