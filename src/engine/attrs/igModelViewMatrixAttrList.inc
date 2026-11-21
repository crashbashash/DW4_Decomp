igMetaObject *g_igModelViewMatrixAttrList_metaObject;

igMetaObject *igModelViewMatrixAttrList_GetOrCreateMetaObject(void) {
    if (g_igModelViewMatrixAttrList_metaObject == 0) {
        g_igModelViewMatrixAttrList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igModelViewMatrixAttrList_metaObject;
}

igMetaObject *igModelViewMatrixAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixAttrList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igModelViewMatrixAttrList_EnsureRegistered();
    return g_igModelViewMatrixAttrList_metaObject;
}

int igModelViewMatrixAttrList_GetVTable(void) {
    struct Obj_1355e0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igModelViewMatrixAttrList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igModelViewMatrixAttrList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igModelViewMatrixAttrList_Register);
}

static igMetaObjectCallback g_igModelViewMatrixAttrList_callbackList[] = { igModelViewMatrixAttr_EnsureRegistered, 0 };

CallbackArray *igModelViewMatrixAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igModelViewMatrixAttrList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igModelViewMatrixAttrList_GetMetaObjectFunction,
        "igModelViewMatrixAttrList",
        0x14, /* instance size */
        igModelViewMatrixAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igModelViewMatrixAttrList_callbackList /* callback list */
    );
}

void igModelViewMatrixAttrList_GetMetaObjectFunction(void) {
    igModelViewMatrixAttrList_GetMetaObject();
}

