igMetaObject *g_igModelViewMatrixAttrList_metaObject;

igMetaObject *FUN_00135540(void) {
    if (g_igModelViewMatrixAttrList_metaObject == 0) {
        g_igModelViewMatrixAttrList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igModelViewMatrixAttrList_metaObject;
}

igMetaObject *igModelViewMatrixAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixAttrList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00135620();
    return g_igModelViewMatrixAttrList_metaObject;
}

int igModelViewMatrixAttrList_GetVTable(void) {
    struct Obj_1355e0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igModelViewMatrixAttrList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_00135620(void)
{
    igMetaObject_RunStaticInit(igModelViewMatrixAttrList_Register);
}

static igMetaObjectCallback g_igModelViewMatrixAttrList_callbackList[] = { igModelViewMatrixAttr_EnsureRegistered, 0 };

CallbackArray *igModelViewMatrixAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igModelViewMatrixAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igModelViewMatrixAttrList_GetMetaObject,
        "igModelViewMatrixAttrList",
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

