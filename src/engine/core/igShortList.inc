igTDataList<short> *igShortList_Create(igMemoryPoolView *pool) {
    igShortList_EnsureRegistered();
    return (igTDataList<short> *)igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586830), pool);
}

igMetaObject *igShortList_GetOrCreateMetaObject(void) {
    if (g_igShortList_metaObject[0] == 0) {
        g_igShortList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igShortList_metaObject[0];
}

igMetaObject *igShortList_GetMetaObject(void)
{
    igMetaObject *g = g_igShortList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igShortList_EnsureRegistered();
    return g_igShortList_metaObject[0];
}

int igShortList_GetVTable(void) {
    igShortList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igShortList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igShortList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igShortList_Register);
}

void igShortList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igShortList_metaObject,
        (igMetaObjectRegisterFunction)igDataList_Register,
        (igMetaObjectGetFunction)igDataList_GetPublishedMetaObject,
        igShortList_GetMetaObjectFunction,
        igShortList_className,
        0x14,
        igShortList_GetVTable,
        igShortList_InitFields,
        0,
        0
    );
}

void igShortList_GetMetaObjectFunction(void) {
    igShortList_GetMetaObject();
}

void igShortList_InitFields(void) {
    int index;
    void **found;
    igMemoryRefMetaField *field;
    igMetaObject *meta;

    meta = g_igShortList_metaObject[0];
    found = (void **)igMetaObject_FindFieldByName(meta, data);
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)found);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)found)->cloneViaMetadata(1);
    field->_memType = igShortMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)(&g_igShortList_dataDescriptorCell[0]);
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)((int) (field->_refCount - 1));
    if (((unsigned long long) ((long long) (int) field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

