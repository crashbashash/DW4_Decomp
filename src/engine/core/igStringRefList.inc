igMetaObject *g_igStringRefList_metaObject;
int g_igStringRefList_dataDescriptorCell;

igStringRefList *igStringRefList_Create(int allocator) {
    igStringRefList_EnsureRegistered();
    return (igStringRefList *)igMetaObject_CreateInstance(g_igStringRefList_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igStringRefList_GetOrCreateMetaObject(void) {
    if (g_igStringRefList_metaObject == 0) {
        g_igStringRefList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igStringRefList_metaObject;
}

igMetaObject *igStringRefList_GetMetaObject(void)
{
    igMetaObject *g = g_igStringRefList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igStringRefList_EnsureRegistered();
    return g_igStringRefList_metaObject;
}

int igStringRefList_GetVTable(void) {
    igStringRefList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igStringRefList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igStringRefList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igStringRefList_Register);
}

CallbackArray *igStringRefList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igStringRefList_metaObject,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        igStringRefList_GetMetaObjectFunction,
        "igStringRefList",
        0x14,
        igStringRefList_GetVTable,
        igStringRefList_InitFields,
        0,
        0
    );
}

void igStringRefList_GetMetaObjectFunction(void) {
    igStringRefList_GetMetaObject();
}

void igStringRefList_InitFields(void) {
    igMemoryRefMetaField *field;
    int index;
    void **found;
    igMetaObject *meta;

    meta = (igMetaObject *)((void *)g_igStringRefList_metaObject);
    found = (void **)(((void **)igMetaObject_FindFieldByName(meta, data)));
    index = ((Gap::Core::__internalNonRefCountedObjectList *)meta->_metaFields)->find((Gap::Core::igObject *)found);
    field = (igMemoryRefMetaField *)(((igObjectDispatchView *)(found))->CloneViaMetadata((int)(1)));
    field->_memType = (int)Gap::Core::igStringMetaField::getMetaField();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)(&g_igStringRefList_dataDescriptorCell);
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->release();
}

