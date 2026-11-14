void igUnsignedIntList_Create(int pool) {
    igUnsignedIntList_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586858), (igMemoryPoolView *)pool);
}

igMetaObject *igUnsignedIntList_GetOrCreateMetaObject(void) {
    if (g_igUnsignedIntList_metaObject[0] == 0) {
        g_igUnsignedIntList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igUnsignedIntList_metaObject[0];
}

igMetaObject *igUnsignedIntList_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedIntList_EnsureRegistered();
    return g_igUnsignedIntList_metaObject[0];
}

int igUnsignedIntList_GetVTable(void) {
    igUnsignedIntList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igUnsignedIntList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igUnsignedIntList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedIntList_Register);
}

void igUnsignedIntList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igUnsignedIntList_metaObject,
        (igMetaObjectRegisterFunction)igDataList_Register,
        (igMetaObjectGetFunction)igDataList_GetPublishedMetaObject,
        igUnsignedIntList_GetMetaObjectFunction,
        igUnsignedIntList_className,
        0x14,
        igUnsignedIntList_GetVTable,
        igUnsignedIntList_InitFields,
        0,
        0
    );
}

void igUnsignedIntList_GetMetaObjectFunction(void) {
    igUnsignedIntList_GetMetaObject();
}

void igUnsignedIntList_InitFields(void) {
    igMetaObject *meta = g_igUnsignedIntList_metaObject[0];
    igMemoryRefMetaField *field = (igMemoryRefMetaField *)((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)data));
    int index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)field)->cloneViaMetadata(1);
    field->_memType = igUnsignedIntMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)g_igUnsignedIntList_dataDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)field->_refCount - 1;
    if (((unsigned long long)((long long)(int)field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

