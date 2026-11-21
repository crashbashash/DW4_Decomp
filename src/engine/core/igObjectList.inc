igMetaObject *g_igObjectList_metaObject;
int g_igObjectList_dataDescriptorCell;

void * igObjectList_Create(int pool) {
    igObjectList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igObjectList_metaObject, (igMemoryPoolView *)pool));
}

/* Created with allocation only, no field registration, when missing. */
int igObjectList_GetOrCreateMetaObject(void) {
    if ((int)g_igObjectList_metaObject == 0) {
        g_igObjectList_metaObject = (igMetaObject *)(int)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return (int)g_igObjectList_metaObject;
}

igMetaObject *igObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igObjectList_EnsureRegistered();
    return g_igObjectList_metaObject;
}

int igObjectList_GetVTable(void) {
    igObjectList obj;

    igObject_InitHeader((igObject *)&obj);
    obj._vtable = (int)&g_igObjectList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igObjectList_Register);
}

CallbackArray *igObjectList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igObjectList_metaObject,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        igObjectList_GetMetaObjectFunction,
        "igObjectList",
        0x14,
        igObjectList_GetVTable,
        igObjectList_InitFields,
        0,
        0
    );
}

void igObjectList_GetMetaObjectFunction(void) {
    igObjectList_GetMetaObject();
}

void igObjectList_InitFields(void) {
    igMetaObject *meta = g_igObjectList_metaObject;
    igMemoryRefMetaField *field = (igMemoryRefMetaField *)((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)data));
    int index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)meta->_metaFields, (int)field);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)field)->CloneViaMetadata(1);
    field->_memType = (int)Gap::Core::igObjectRefMetaField::getMetaField();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)&g_igObjectList_dataDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)field->_refCount - 1;
    if (((unsigned long long)((long long)(int)field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

