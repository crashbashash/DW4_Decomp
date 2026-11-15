igMetaObject *g_igPointerList_metaObject;
int g_igPointerList_dataDescriptorCell;

void * igPointerList_Create(int allocator) {
    igPointerList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igPointerList_metaObject, (igMemoryPoolView *)allocator));
}

igMetaObject *igPointerList_GetOrCreateMetaObject(void) {
    if (g_igPointerList_metaObject == 0) {
        g_igPointerList_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igPointerList_metaObject;
}

igMetaObject *igPointerList_GetMetaObject(void)
{
    igMetaObject *g = g_igPointerList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPointerList_EnsureRegistered();
    return g_igPointerList_metaObject;
}

int igPointerList_GetVTable(void) {
    igPointerList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igPointerList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igPointerList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPointerList_Register);
}

void igPointerList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igPointerList_metaObject,
        (igMetaObjectRegisterFunction)igDataList_Register,
        (igMetaObjectGetFunction)igDataList_GetPublishedMetaObject,
        igPointerList_GetMetaObjectFunction,
        "igPointerList",
        0x14,
        igPointerList_GetVTable,
        igPointerList_InitFields,
        0,
        0
    );
}

void igPointerList_GetMetaObjectFunction(void) {
    igPointerList_GetMetaObject();
}


void igPointerList_InitFields(void) {
    int index;
    igMetaField *original;
    igMemoryRefMetaField *field;
    igMetaObject *meta;

    meta = (igMetaObject *)g_igPointerList_metaObject;
    original = (igMetaField *)igMetaObject_FindFieldByName(meta, data);
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)original);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)(original))->CloneViaMetadata((int)(1));
    field->_memType = igRawRefMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)(&g_igPointerList_dataDescriptorCell);
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)((int) (field->_refCount - 1));
    if (((unsigned long long) ((long long)(int)field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

