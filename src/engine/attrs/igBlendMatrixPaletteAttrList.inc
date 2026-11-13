igMetaObject *FUN_00139820(void) {
    if (g_igBlendMatrixPaletteAttrList_metaObject[0] == 0) {
        g_igBlendMatrixPaletteAttrList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igBlendMatrixPaletteAttrList_metaObject[0];
}

igMetaObject *igBlendMatrixPaletteAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatrixPaletteAttrList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00139900();
    return g_igBlendMatrixPaletteAttrList_metaObject[0];
}

int igBlendMatrixPaletteAttrList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_005246c0[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_00139900(void)
{
    igMetaObject_RunStaticInit(igBlendMatrixPaletteAttrList_Register);
}

void igBlendMatrixPaletteAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBlendMatrixPaletteAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igBlendMatrixPaletteAttrList_GetMetaObject,
        igBlendMatrixPaletteAttrList_className,
        0x14, /* instance size */
        igBlendMatrixPaletteAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igBlendMatrixPaletteAttrList_callbackList /* callback list */
    );
}

void thunk_igBlendMatrixPaletteAttrList_GetMetaObject(void) {
    igBlendMatrixPaletteAttrList_GetMetaObject();
}

