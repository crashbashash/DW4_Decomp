igMetaObject *g_igFloatList_metaObject;
int g_igFloatList_dataStorage;

igFloatList *igFloatList_Create(int pool) {
    igFloatList_EnsureRegistered();
    return (igFloatList *)igMetaObject_CreateInstance(g_igFloatList_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igFloatList_GetOrCreateMetaObject(void) {
    if (g_igFloatList_metaObject == 0) {
        g_igFloatList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igFloatList_metaObject;
}

igMetaObject *igFloatList_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFloatList_EnsureRegistered();
    return g_igFloatList_metaObject;
}

int igFloatList_GetVTable(void) {
    igFloatList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igFloatList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igFloatList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFloatList_Register);
}

CallbackArray *igFloatList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igFloatList_metaObject,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        igFloatList_GetMetaObjectFunction,
        "igFloatList",
        0x14,
        igFloatList_GetVTable,
        igFloatList_InitFields,
        0,
        0
    );
}

void igFloatList_GetMetaObjectFunction(void) {
    igFloatList_GetMetaObject();
}

void igFloatList_InitFields(void) {
    int index;
    void **found;
    igMemoryRefMetaField *field;
    void *meta;

    meta = (void *)((void *)g_igFloatList_metaObject);
    found = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)meta, data)));
    index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)((char *)((igMetaObject *)meta)->_metaFields), (int)found);
    field = (igMemoryRefMetaField *)(((igObjectDispatchView *)(found))->CloneViaMetadata((int)(1)));
    field->_memType = (int)Gap::Core::igFloatMetaField::getMetaField();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)(&g_igFloatList_dataStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, index, (igMetaField *)field);
    field->_refCount = (int)((int) (field->_refCount - 1));
    if (((unsigned long long) ((long long)(int)field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

