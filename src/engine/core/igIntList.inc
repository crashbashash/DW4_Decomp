igMetaObject *g_igIntList_metaObject;
int g_igIntList_dataDescriptorCell;

igMetaObject *igIntList_GetPublishedMetaObject(void) {
    return g_igIntList_metaObject;
}

igIntList *igIntList_Create(int allocator) {
    igIntList_EnsureRegistered();
    return (igIntList *)igMetaObject_CreateInstance(g_igIntList_metaObject, (igMemoryPoolView *)allocator);
}

/* Created with allocation only when missing. */
int igIntList_GetOrCreateMetaObject(void) {
    if ((int)g_igIntList_metaObject == 0) {
        g_igIntList_metaObject = (igMetaObject *)(int)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return (int)g_igIntList_metaObject;
}

igMetaObject *igIntList_GetMetaObject(void)
{
    igMetaObject *g = g_igIntList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igIntList_EnsureRegistered();
    return g_igIntList_metaObject;
}

int igIntList_GetVTable(void) {
    igIntList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igIntList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igIntList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igIntList_Register);
}

CallbackArray *igIntList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igIntList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        igIntList_GetMetaObjectFunction,
        "igIntList",
        0x14,
        igIntList_GetVTable,
        igIntList_InitFields,
        0,
        0
    );
}

void igIntList_GetMetaObjectFunction(void) {
    igIntList_GetMetaObject();
}

static inline void releaseDataField(igMemoryRefMetaField *f) {
    f->_refCount = (int)f->_refCount - 1;
    if (((unsigned long long)((long long)(int)f->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(f);
    }
}


void igIntList_InitFields(void) {
    igMetaObject *meta = g_igIntList_metaObject;
    igMemoryRefMetaField *field = (igMemoryRefMetaField *)((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)data));
    int index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)field)->CloneViaMetadata(1);
    field->_memType = igIntMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)&g_igIntList_dataDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    releaseDataField(field);
}

