igMetaObject *g_beModelCtrlAIMapList_metaObject;

igMetaObject *beModelCtrlAIMapList_GetOrCreateMetaObject(void) {
    if (g_beModelCtrlAIMapList_metaObject == 0) {
        g_beModelCtrlAIMapList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beModelCtrlAIMapList_metaObject;
}

void *beModelCtrlAIMapList_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlAIMapList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlAIMapList_EnsureRegistered();
    }
    return g_beModelCtrlAIMapList_metaObject;
}

int beModelCtrlAIMapList_GetVTable(void) {
    struct Obj_354250 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beModelCtrlAIMapList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beModelCtrlAIMapList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIMapList_Register);
}

static igMetaObjectCallback g_beModelCtrlAIMapList_callbackList[] = { beModelCtrlAIMap_EnsureRegistered, 0 };

void *beModelCtrlAIMapList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlAIMapList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beModelCtrlAIMapList_GetMetaObjectFunction,
        "beModelCtrlAIMapList",
        0x14, /* instance size */
        beModelCtrlAIMapList_GetVTable,
        0,
        0, /* extra callback item */
        g_beModelCtrlAIMapList_callbackList /* callback list */
    );
}

void beModelCtrlAIMapList_GetMetaObjectFunction(void)
{
    beModelCtrlAIMapList_GetMetaObject();
}

