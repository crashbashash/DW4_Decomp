igMetaObject *igDoubleList_GetOrCreateMetaObject(void) {
    if (g_igDoubleList_metaObject[0] == 0) {
        g_igDoubleList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igDoubleList_metaObject[0];
}

igMetaObject *igDoubleList_GetMetaObject(void)
{
    igMetaObject *g = g_igDoubleList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDoubleList_EnsureRegistered();
    return g_igDoubleList_metaObject[0];
}

int igDoubleList_GetVTable(void) {
    igDoubleList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igDoubleList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igDoubleList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDoubleList_Register);
}

void igDoubleList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igDoubleList_metaObject,
        (igMetaObjectRegisterFunction)igDataList_Register,
        (igMetaObjectGetFunction)igDataList_GetPublishedMetaObject,
        igDoubleList_GetMetaObjectFunction,
        igDoubleList_className,
        0x14,
        igDoubleList_GetVTable,
        igDoubleList_InitFields,
        0,
        0
    );
}

void igDoubleList_GetMetaObjectFunction(void) {
    igDoubleList_GetMetaObject();
}

void igDoubleList_InitFields(void) {
    igMetaObject *meta = g_igDoubleList_metaObject[0];
    igMemoryRefMetaField *field = (igMemoryRefMetaField *)((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)data));
    int index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)field)->CloneViaMetadata(1);
    field->_memType = igDoubleMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)g_igDoubleList_dataDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)field->_refCount - 1;
    if (((unsigned long long)((long long)(int)field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

