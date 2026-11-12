int FUN_0019a400(void) {
    if (DAT_005615b8[0] == 0) {
        DAT_005615b8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005615b8[0];
}

igMetaObject *igModelViewMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixAttrPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019a4e0();
    return g_igModelViewMatrixAttrPool_metaObject[0];
}

int igModelViewMatrixAttrPool_GetVTable(void) {
    int obj[8];
    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_0052ae80[0];
    return *(int *)((char *)obj + *(int *)((char *)DAT_00586dc8[0] + 916));
}

void FUN_0019a4e0(void)
{
    igMetaObject_RunStaticInit(igModelViewMatrixAttrPool_Register);
}

void igModelViewMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igModelViewMatrixAttrPool_metaObject),
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igModelViewMatrixAttrPool_GetMetaObject,
        igModelViewMatrixAttrPool_className,
        0x20, /* instance size */
        igModelViewMatrixAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igModelViewMatrixAttrPool_callbackList /* callback list */
    );
}

void thunk_igModelViewMatrixAttrPool_GetMetaObject(void) {
    igModelViewMatrixAttrPool_GetMetaObject();
}

