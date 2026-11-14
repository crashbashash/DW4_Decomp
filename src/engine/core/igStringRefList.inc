void * igStringRefList_Create(int allocator) {
    igStringRefList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5858D8), (igMemoryPoolView *)allocator));
}

igMetaObject *igStringRefList_GetOrCreateMetaObject(void) {
    if (g_igStringRefList_metaObject[0] == 0) {
        g_igStringRefList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igStringRefList_metaObject[0];
}

igMetaObject *igStringRefList_GetMetaObject(void)
{
    igMetaObject *g = g_igStringRefList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igStringRefList_EnsureRegistered();
    return g_igStringRefList_metaObject[0];
}

int igStringRefList_GetVTable(void) {
    igStringRefList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igStringRefList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igStringRefList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringRefList_Register);
}

void igStringRefList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igStringRefList_metaObject,
        (igMetaObjectRegisterFunction)igDataList_Register,
        (igMetaObjectGetFunction)igDataList_GetPublishedMetaObject,
        igStringRefList_GetMetaObjectFunction,
        igStringRefList_className,
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
    int index;
    void **found;
    igMemoryRefMetaField *field;
    igMetaObject *meta;

    meta = (igMetaObject *)(((void * *)g_igStringRefList_metaObject)[0]);
    found = (void **)(((void **)igMetaObject_FindFieldByName(meta, data)));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)found);
    field = (igMemoryRefMetaField *)(((igObjectDispatchView *)(found))->CloneViaMetadata((int)(1)));
    field->_memType = igStringMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)(&g_igStringRefList_dataDescriptorCell[0]);
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)((int)field->_refCount - 1);
    if (((unsigned long long) ((long long)(int)field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

