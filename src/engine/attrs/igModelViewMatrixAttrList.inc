int FUN_00135540(void) {
    if (DAT_0055efe0[0] == 0) {
        DAT_0055efe0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055efe0[0];
}

igMetaObject *igModelViewMatrixAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixAttrList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00135620();
    return g_igModelViewMatrixAttrList_metaObject[0];
}

int igModelViewMatrixAttrList_GetVTable(void) {
    struct Obj_1355e0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524810[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00135620(void)
{
    igMetaObject_RunStaticInit(igModelViewMatrixAttrList_Register);
}

void igModelViewMatrixAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igModelViewMatrixAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igModelViewMatrixAttrList_GetMetaObject,
        igModelViewMatrixAttrList_className,
        0x14, /* instance size */
        igModelViewMatrixAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igModelViewMatrixAttrList_callbackList /* callback list */
    );
}

void thunk_igModelViewMatrixAttrList_GetMetaObject(void) {
    igModelViewMatrixAttrList_GetMetaObject();
}

