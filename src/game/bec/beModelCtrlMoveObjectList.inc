igMetaObject *FUN_003527b0(void) {
    if (g_beModelCtrlMoveObjectList_metaObject[0] == 0) {
        g_beModelCtrlMoveObjectList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beModelCtrlMoveObjectList_metaObject[0];
}

igMetaObject *FUN_00352800(void)
{
    igMetaObject *g = g_beModelCtrlMoveObjectList_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00352890();
    return g_beModelCtrlMoveObjectList_metaObject[0];
}

int beModelCtrlMoveObjectList_GetVTable(void) {
    struct Obj_352850 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00537d50[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00352890(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMoveObjectList_Register);
}

void *beModelCtrlMoveObjectList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlMoveObjectList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beModelCtrlMoveObjectList_GetMetaObject,
        beModelCtrlMoveObjectList_className,
        0x14, /* instance size */
        beModelCtrlMoveObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_beModelCtrlMoveObjectList_callbackList /* callback list */
    );
}

void beModelCtrlMoveObjectList_GetMetaObject(void)
{
    FUN_00352800();
}

