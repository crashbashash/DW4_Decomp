igMetaObject *g_igBoolList_metaObject;
int g_igBoolList_dataDescriptorCell;

igBoolList *igBoolList_Create(int pool) {
    igBoolList_EnsureRegistered();
    return (igBoolList *)igMetaObject_CreateInstance(g_igBoolList_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igBoolList_GetOrCreateMetaObject(void) {
    if (g_igBoolList_metaObject == 0) {
        g_igBoolList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igBoolList_metaObject;
}

igMetaObject *igBoolList_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBoolList_EnsureRegistered();
    return g_igBoolList_metaObject;
}

int igBoolList_GetVTable(void) {
    igBoolList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igBoolList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igBoolList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBoolList_Register);
}

CallbackArray *igBoolList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igBoolList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        igBoolList_GetMetaObjectFunction,
        "igBoolList",
        0x14,
        igBoolList_GetVTable,
        igBoolList_InitFields,
        0,
        0
    );
}

void igBoolList_GetMetaObjectFunction(void) {
    igBoolList_GetMetaObject();
}


void igBoolList_InitFields(void) {
    igMetaObject *meta = g_igBoolList_metaObject;
    igMemoryRefMetaField *field = (igMemoryRefMetaField *)((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)data));
    int index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)meta->_metaFields, (int)field);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)field)->CloneViaMetadata(1);
    field->_memType = igBoolMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)&g_igBoolList_dataDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)field->_refCount - 1;
    if (((unsigned long long)((long long)(int)field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

