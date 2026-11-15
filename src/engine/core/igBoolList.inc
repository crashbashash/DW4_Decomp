igMetaObject *g_igBoolList_metaObject;
int g_igBoolList_dataDescriptorCell;

void igBoolList_Create(int pool) {
    igBoolList_EnsureRegistered();
    igMetaObject_CreateInstance(g_igBoolList_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igBoolList_GetOrCreateMetaObject(void) {
    if (g_igBoolList_metaObject == 0) {
        g_igBoolList_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igBoolList_metaObject;
}

igMetaObject *igBoolList_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBoolList_EnsureRegistered();
    return g_igBoolList_metaObject;
}

int igBoolList_GetVTable(void) {
    igBoolList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igBoolList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igBoolList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igBoolList_Register);
}

void igBoolList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igBoolList_metaObject,
        (igMetaObjectRegisterFunction)igDataList_Register,
        (igMetaObjectGetFunction)igDataList_GetPublishedMetaObject,
        igBoolList_GetMetaObjectFunction,
        "igBoolList",
        0x14,
        igBoolList_GetVTable,
        igBoolList_InitFields,
        0,
        0
    );
}

void igBoolList_GetMetaObjectFunction(void) {
    igBoolList_GetMetaObject();
}


void igBoolList_InitFields(void) {
    igMetaObject *meta = g_igBoolList_metaObject;
    igMemoryRefMetaField *field = (igMemoryRefMetaField *)((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)data));
    int index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)field)->CloneViaMetadata(1);
    field->_memType = igBoolMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)&g_igBoolList_dataDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)field->_refCount - 1;
    if (((unsigned long long)((long long)(int)field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

