igMetaObject *g_igStringRefList_metaObject;
int g_igStringRefList_dataDescriptorCell;

igStringRefList *igStringRefList_Create(int allocator) {
    igStringRefList_EnsureRegistered();
    return (igStringRefList *)igMetaObject_CreateInstance(g_igStringRefList_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igStringRefList_GetOrCreateMetaObject(void) {
    if (g_igStringRefList_metaObject == 0) {
        g_igStringRefList_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
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
    return *(int *)((char *)&list + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igStringRefList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringRefList_Register);
}

void igStringRefList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igStringRefList_metaObject,
        (igMetaObjectRegisterFunction)igDataList_Register,
        (igMetaObjectGetFunction)igDataList_GetPublishedMetaObject,
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
    int index;
    void **found;
    igMemoryRefMetaField *field;
    igMetaObject *meta;

    meta = (igMetaObject *)((void *)g_igStringRefList_metaObject);
    found = (void **)(((void **)igMetaObject_FindFieldByName(meta, data)));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)found);
    field = (igMemoryRefMetaField *)(((igObjectDispatchView *)(found))->CloneViaMetadata((int)(1)));
    field->_memType = igStringMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)(&g_igStringRefList_dataDescriptorCell);
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)((int)field->_refCount - 1);
    if (((unsigned long long) ((long long)(int)field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

