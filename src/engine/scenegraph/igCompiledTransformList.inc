igMetaObject *g_igCompiledTransformList_metaObject;

igMetaObject *FUN_001a3420(void) {
    if (g_igCompiledTransformList_metaObject == 0) {
        g_igCompiledTransformList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igCompiledTransformList_metaObject;
}

igMetaObject *igCompiledTransformList_GetMetaObject(void)
{
    igMetaObject *g = g_igCompiledTransformList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a3500();
    return g_igCompiledTransformList_metaObject;
}

int igCompiledTransformList_GetVTable(void) {
    struct Obj_1a34c0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igCompiledTransformList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001a3500(void)
{
    igMetaObject_RunStaticInit(igCompiledTransformList_Register);
}

static igMetaObjectCallback g_igCompiledTransformList_callbackList[] = { FUN_001a3700, 0 };

void igCompiledTransformList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCompiledTransformList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCompiledTransformList_GetMetaObject,
        "igCompiledTransformList",
        0x14, /* instance size */
        igCompiledTransformList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCompiledTransformList_callbackList /* callback list */
    );
}

void thunk_igCompiledTransformList_GetMetaObject(void) {
    igCompiledTransformList_GetMetaObject();
}

