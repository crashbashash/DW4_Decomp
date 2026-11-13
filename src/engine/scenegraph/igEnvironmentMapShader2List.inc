igMetaObject *FUN_001a13e0(void) {
    if (g_igEnvironmentMapShader2List_metaObject[0] == 0) {
        g_igEnvironmentMapShader2List_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igEnvironmentMapShader2List_metaObject[0];
}

igMetaObject *igEnvironmentMapShader2List_GetMetaObject(void)
{
    igMetaObject *g = g_igEnvironmentMapShader2List_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a14c0();
    return g_igEnvironmentMapShader2List_metaObject[0];
}

int igEnvironmentMapShader2List_GetVTable(void) {
    struct Obj_1a1480 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052a730[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001a14c0(void)
{
    igMetaObject_RunStaticInit(igEnvironmentMapShader2List_Register);
}

void igEnvironmentMapShader2List_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igEnvironmentMapShader2List_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igEnvironmentMapShader2List_GetMetaObject,
        igEnvironmentMapShader2List_className,
        0x14, /* instance size */
        igEnvironmentMapShader2List_GetVTable,
        0,
        0, /* extra callback item */
        g_igEnvironmentMapShader2List_callbackList /* callback list */
    );
}

void thunk_igEnvironmentMapShader2List_GetMetaObject(void) {
    igEnvironmentMapShader2List_GetMetaObject();
}

