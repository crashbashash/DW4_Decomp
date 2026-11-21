igMetaObject *g_igBlendMatrixPaletteAttrList_metaObject;

igMetaObject *igBlendMatrixPaletteAttrList_GetOrCreateMetaObject(void) {
    if (g_igBlendMatrixPaletteAttrList_metaObject == 0) {
        g_igBlendMatrixPaletteAttrList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igBlendMatrixPaletteAttrList_metaObject;
}

igMetaObject *igBlendMatrixPaletteAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatrixPaletteAttrList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBlendMatrixPaletteAttrList_EnsureRegistered();
    return g_igBlendMatrixPaletteAttrList_metaObject;
}

int igBlendMatrixPaletteAttrList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igBlendMatrixPaletteAttrList_vtable[0];
    return *(int *)((char *)obj + g_objectSystem->vtableProbeOffset);
}

void igBlendMatrixPaletteAttrList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBlendMatrixPaletteAttrList_Register);
}

static igMetaObjectCallback g_igBlendMatrixPaletteAttrList_callbackList[] = { Gap::Attrs::igBlendMatrixPaletteAttr::arkRegister, 0 };

CallbackArray *igBlendMatrixPaletteAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBlendMatrixPaletteAttrList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igBlendMatrixPaletteAttrList_GetMetaObjectFunction,
        "igBlendMatrixPaletteAttrList",
        0x14, /* instance size */
        igBlendMatrixPaletteAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igBlendMatrixPaletteAttrList_callbackList /* callback list */
    );
}

void igBlendMatrixPaletteAttrList_GetMetaObjectFunction(void) {
    igBlendMatrixPaletteAttrList_GetMetaObject();
}

