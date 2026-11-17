igMetaObject *g_igUnsignedCharList_metaObject;
int g_igUnsignedCharList_dataDescriptorCell;

igUnsignedCharList *igUnsignedCharList_Create(int allocator) {
    igUnsignedCharList_EnsureRegistered();
    return (igUnsignedCharList *)igMetaObject_CreateInstance(g_igUnsignedCharList_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igUnsignedCharList_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedCharList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedCharList_EnsureRegistered();
    return g_igUnsignedCharList_metaObject;
}

int igUnsignedCharList_GetVTable(void) {
    igUnsignedCharList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igUnsignedCharList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igUnsignedCharList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igUnsignedCharList_Register);
}

CallbackArray *igUnsignedCharList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igUnsignedCharList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        igUnsignedCharList_GetMetaObjectFunction,
        "igUnsignedCharList",
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

    meta = (igMetaObject *)(g_igUnsignedCharList_metaObject);
    found = (void **)(((void **)igMetaObject_FindFieldByName(meta, data)));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)found);
    field = (igMemoryRefMetaField *)(((igObjectDispatchView *)(found))->CloneViaMetadata((int)(1)));
    field->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)(&g_igUnsignedCharList_dataDescriptorCell);
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)((int)field->_refCount - 1);
    if (((unsigned long long) ((long long)(int)field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

