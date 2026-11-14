igMetaObject *igLongList_GetOrCreateMetaObject(void) {
    if (g_igLongList_metaObject[0] == 0) {
        g_igLongList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igLongList_metaObject[0];
}

igMetaObject *igLongList_GetMetaObject(void)
{
    igMetaObject *g = g_igLongList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igLongList_EnsureRegistered();
    return g_igLongList_metaObject[0];
}

int igLongList_GetVTable(void) {
    igLongList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igLongList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igLongList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLongList_Register);
}

void igLongList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igLongList_metaObject,
        (igMetaObjectRegisterFunction)igDataList_Register,
        (igMetaObjectGetFunction)igDataList_GetPublishedMetaObject,
        igLongList_GetMetaObjectFunction,
        igLongList_className,
        0x14,
        igLongList_GetVTable,
        igLongList_InitFields,
        0,
        0
    );
}

void igLongList_GetMetaObjectFunction(void) {
    igLongList_GetMetaObject();
}

void igLongList_InitFields(void) {
    int index;
    void **found;
    igMemoryRefMetaField *field;
    igMetaObject *meta;

    meta = g_igLongList_metaObject[0];
    found = (void **)igMetaObject_FindFieldByName(meta, data);
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)found);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)found)->cloneViaMetadata(1);
    field->_memType = igLongMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)(&g_igLongList_dataDescriptorCell[0]);
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)((int) (field->_refCount - 1));
    if (((unsigned long long) ((long long) (int) field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

