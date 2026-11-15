igMetaObject *g_igCharList_metaObject;
int g_igCharList_dataDescriptorCell;

igMetaObject *igCharList_GetPublishedMetaObject(void) {
    return g_igCharList_metaObject;
}

void igCharList_Create(int pool) {
    igCharList_EnsureRegistered();
    igMetaObject_CreateInstance(g_igCharList_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igCharList_GetOrCreateMetaObject(void) {
    if (g_igCharList_metaObject == 0) {
        g_igCharList_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igCharList_metaObject;
}

igMetaObject *igCharList_GetMetaObject(void)
{
    igMetaObject *g = g_igCharList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCharList_EnsureRegistered();
    return g_igCharList_metaObject;
}

int igCharList_GetVTable(void) {
    igCharList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igCharList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igCharList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igCharList_Register);
}

void igCharList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igCharList_metaObject,
        (igMetaObjectRegisterFunction)igDataList_Register,
        (igMetaObjectGetFunction)igDataList_GetPublishedMetaObject,
        igCharList_GetMetaObjectFunction,
        "igCharList",
        0x14,
        igCharList_GetVTable,
        igCharList_InitFields,
        0,
        0
    );
}

void igCharList_GetMetaObjectFunction(void) {
    igCharList_GetMetaObject();
}


void igCharList_InitFields(void) {
    int index;
    void **found;
    igMemoryRefMetaField *field;
    igMetaObject *meta;

    meta = g_igCharList_metaObject;
    found = (void **)igMetaObject_FindFieldByName(meta, data);
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)found);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)found)->CloneViaMetadata(1);
    field->_memType = igCharMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)&g_igCharList_dataDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)((int) (field->_refCount - 1));
    if (((unsigned long long) ((long long) (int) field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

