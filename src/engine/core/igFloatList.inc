void igFloatList_Create(int pool) {
    igFloatList_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586808), (igMemoryPoolView *)pool);
}

igMetaObject *igFloatList_GetOrCreateMetaObject(void) {
    if (g_igFloatList_metaObject[0] == 0) {
        g_igFloatList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igFloatList_metaObject[0];
}

igMetaObject *igFloatList_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFloatList_EnsureRegistered();
    return g_igFloatList_metaObject[0];
}

int igFloatList_GetVTable(void) {
    igFloatList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igFloatList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igFloatList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igFloatList_Register);
}

void igFloatList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igFloatList_metaObject,
        (igMetaObjectRegisterFunction)igDataList_Register,
        (igMetaObjectGetFunction)igDataList_GetPublishedMetaObject,
        igFloatList_GetMetaObjectFunction,
        igFloatList_className,
        0x14,
        igFloatList_GetVTable,
        igFloatList_InitFields,
        0,
        0
    );
}

void igFloatList_GetMetaObjectFunction(void) {
    igFloatList_GetMetaObject();
}

void igFloatList_InitFields(void) {
    int index;
    void **found;
    igMemoryRefMetaField *field;
    void *meta;

    meta = (void *)(((void * *)g_igFloatList_metaObject)[0]);
    found = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)meta, data)));
    index = ObjectPointerList_FindIndex((char *)((igMetaObject *)meta)->_metaFields, (int)found);
    field = (igMemoryRefMetaField *)(((igObjectDispatchView *)(found))->CloneViaMetadata((int)(1)));
    field->_memType = igFloatMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)(&g_igFloatList_dataStorage[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, index, (igMetaField *)field);
    field->_refCount = (int)((int) (field->_refCount - 1));
    if (((unsigned long long) ((long long)(int)field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

