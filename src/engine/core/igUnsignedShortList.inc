igMetaObject *g_igUnsignedShortList_metaObject;
int g_igUnsignedShortList_dataDescriptorCell;

void igUnsignedShortList_Create(int pool) {
    igUnsignedShortList_EnsureRegistered();
    igMetaObject_CreateInstance(g_igUnsignedShortList_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igUnsignedShortList_GetOrCreateMetaObject(void) {
    if (g_igUnsignedShortList_metaObject == 0) {
        g_igUnsignedShortList_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igUnsignedShortList_metaObject;
}

igMetaObject *igUnsignedShortList_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedShortList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedShortList_EnsureRegistered();
    return g_igUnsignedShortList_metaObject;
}

int igUnsignedShortList_GetVTable(void) {
    igUnsignedShortList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igUnsignedShortList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igUnsignedShortList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedShortList_Register);
}

void igUnsignedShortList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igUnsignedShortList_metaObject,
        (igMetaObjectRegisterFunction)igDataList_Register,
        (igMetaObjectGetFunction)igDataList_GetPublishedMetaObject,
        igUnsignedShortList_GetMetaObjectFunction,
        "igUnsignedShortList",
        0x14,
        igUnsignedShortList_GetVTable,
        igUnsignedShortList_InitFields,
        0,
        0
    );
}

void igUnsignedShortList_GetMetaObjectFunction(void) {
    igUnsignedShortList_GetMetaObject();
}


void igUnsignedShortList_InitFields(void) {
    int index;
    void **found;
    igMemoryRefMetaField *field;
    igMetaObject *meta;

    meta = g_igUnsignedShortList_metaObject;
    found = (void **)igMetaObject_FindFieldByName(meta, data);
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)found);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)found)->CloneViaMetadata(1);
    field->_memType = igUnsignedShortMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)&g_igUnsignedShortList_dataDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)((int) (field->_refCount - 1));
    if (((unsigned long long) ((long long) (int) field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

