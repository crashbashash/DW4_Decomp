void igUnsignedCharList_Create(int allocator) {
    igUnsignedCharList_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586818), (igMemoryPoolView *)allocator);
}

igMetaObject *igUnsignedCharList_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedCharList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedCharList_EnsureRegistered();
    return g_igUnsignedCharList_metaObject[0];
}

int igUnsignedCharList_GetVTable(void) {
    igUnsignedCharList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igUnsignedCharList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igUnsignedCharList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedCharList_Register);
}

void igUnsignedCharList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igUnsignedCharList_metaObject,
        (igMetaObjectRegisterFunction)igDataList_Register,
        (igMetaObjectGetFunction)igDataList_GetPublishedMetaObject,
        igUnsignedCharList_GetMetaObjectFunction,
        igUnsignedCharList_className,
        0x14,
        igUnsignedCharList_GetVTable,
        igUnsignedCharList_InitFields,
        0,
        0
    );
}

void igUnsignedCharList_GetMetaObjectFunction(void) {
    igUnsignedCharList_GetMetaObject();
}

void igUnsignedCharList_InitFields(void) {
    int index;
    void **found;
    igMemoryRefMetaField *field;
    igMetaObject *meta;

    meta = (igMetaObject *)(g_igUnsignedCharList_metaObject[0]);
    found = (void **)(((void **)igMetaObject_FindFieldByName(meta, data)));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)found);
    field = (igMemoryRefMetaField *)(((igObjectDispatchView *)(found))->CloneViaMetadata((int)(1)));
    field->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)(&g_igUnsignedCharList_dataDescriptorCell[0]);
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)((int)field->_refCount - 1);
    if (((unsigned long long) ((long long)(int)field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

