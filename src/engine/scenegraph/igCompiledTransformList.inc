int FUN_001a3420(void) {
    if (DAT_00561d28[0] == 0) {
        DAT_00561d28[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00561d28[0];
}

igMetaObject *igCompiledTransformList_GetMetaObject(void)
{
    igMetaObject *g = g_igCompiledTransformList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a3500();
    return g_igCompiledTransformList_metaObject[0];
}

int igCompiledTransformList_GetVTable(void) {
    struct Obj_1a34c0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052a600[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001a3500(void)
{
    igMetaObject_RunStaticInit(igCompiledTransformList_Register);
}

void igCompiledTransformList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igCompiledTransformList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCompiledTransformList_GetMetaObject,
        igCompiledTransformList_className,
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

