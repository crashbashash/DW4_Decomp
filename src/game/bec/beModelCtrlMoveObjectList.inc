igMetaObject *g_beModelCtrlMoveObjectList_metaObject;

igMetaObject *beModelCtrlMoveObjectList_GetOrCreateMetaObject(void) {
    if (g_beModelCtrlMoveObjectList_metaObject == 0) {
        g_beModelCtrlMoveObjectList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beModelCtrlMoveObjectList_metaObject;
}

igMetaObject *beModelCtrlMoveObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_beModelCtrlMoveObjectList_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beModelCtrlMoveObjectList_EnsureRegistered();
    return g_beModelCtrlMoveObjectList_metaObject;
}

int beModelCtrlMoveObjectList_GetVTable(void) {
    struct Obj_352850 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beModelCtrlMoveObjectList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beModelCtrlMoveObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMoveObjectList_Register);
}

static igMetaObjectCallback g_beModelCtrlMoveObjectList_callbackList[] = { beModelCtrlMoveObject_EnsureRegistered, 0 };

void *beModelCtrlMoveObjectList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlMoveObjectList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beModelCtrlMoveObjectList_GetMetaObjectFunction,
        "beModelCtrlMoveObjectList",
        0x14, /* instance size */
        beModelCtrlMoveObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_beModelCtrlMoveObjectList_callbackList /* callback list */
    );
}

void beModelCtrlMoveObjectList_GetMetaObjectFunction(void)
{
    beModelCtrlMoveObjectList_GetMetaObject();
}

