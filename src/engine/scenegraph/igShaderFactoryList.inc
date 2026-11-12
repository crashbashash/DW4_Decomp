int FUN_00198fa0(void) {
    if (DAT_00561518[0] == 0) {
        DAT_00561518[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00561518[0];
}

igMetaObject *igShaderFactoryList_GetMetaObject(void)
{
    igMetaObject *g = g_igShaderFactoryList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00199080();
    return g_igShaderFactoryList_metaObject[0];
}

int igShaderFactoryList_GetVTable(void) {
    struct Obj_199040 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052b200[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00199080(void)
{
    igMetaObject_RunStaticInit(igShaderFactoryList_Register);
}

void igShaderFactoryList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igShaderFactoryList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igShaderFactoryList_GetMetaObject,
        igShaderFactoryList_className,
        0x14, /* instance size */
        igShaderFactoryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igShaderFactoryList_callbackList /* callback list */
    );
}

void thunk_igShaderFactoryList_GetMetaObject(void) {
    igShaderFactoryList_GetMetaObject();
}

