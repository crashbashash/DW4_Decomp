igMetaObject *g_igDependencyList_metaObject;
int g_igDependencyList_dataDescriptorCell;

igMetaObject *igDependencyList_GetOrCreateMetaObject(void) {
    if (g_igDependencyList_metaObject == 0) {
        g_igDependencyList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igDependencyList_metaObject;
}

igMetaObject *igDependencyList_GetMetaObject(void)
{
    igMetaObject *g = g_igDependencyList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDependencyList_EnsureRegistered();
    return g_igDependencyList_metaObject;
}

int igDependencyList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igDependencyList_vtable[0];
    return *(int *)((char *)obj + g_objectSystem->vtableProbeOffset);
}

void igDependencyList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDependencyList_Register);
}

CallbackArray *igDependencyList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igDependencyList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        igDependencyList_GetMetaObjectFunction,
        "igDependencyList",
        0x14,
        igDependencyList_GetVTable,
        igDependencyList_InitFields,
        0,
        0
    );
}

void igDependencyList_GetMetaObjectFunction(void) {
    igDependencyList_GetMetaObject();
}


void igDependencyList_InitFields(void) {
    int index;
    igMetaField *original;
    igMemoryRefMetaField *field;
    igMetaObject *meta;

    meta = (igMetaObject *)g_igDependencyList_metaObject;
    original = (igMetaField *)igMetaObject_FindFieldByName(meta, data);
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)original);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)(original))->CloneViaMetadata((int)(1));
    field->_memType = igDependencyMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)(&g_igDependencyList_dataDescriptorCell);
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)((int) (field->_refCount - 1));
    if (((unsigned long long) ((long long)(int)field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

