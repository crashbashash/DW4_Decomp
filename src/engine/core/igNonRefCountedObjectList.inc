igMetaObject *igNonRefCountedObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igNonRefCountedObjectList_EnsureRegistered();
    return g_igNonRefCountedObjectList_metaObject[0];
}

int igNonRefCountedObjectList_GetVTable(void) {
    igNonRefCountedObjectList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igNonRefCountedObjectList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igNonRefCountedObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igNonRefCountedObjectList_Register);
}

void igNonRefCountedObjectList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igNonRefCountedObjectList_metaObject,
        (igMetaObjectRegisterFunction)igDataList_Register,
        (igMetaObjectGetFunction)igDataList_GetPublishedMetaObject,
        igNonRefCountedObjectList_GetMetaObjectFunction,
        igNonRefCountedObjectList_className,
        0x14,
        igNonRefCountedObjectList_GetVTable,
        igNonRefCountedObjectList_InitFields,
        0,
        0
    );
}

void igNonRefCountedObjectList_GetMetaObjectFunction(void) {
    igNonRefCountedObjectList_GetMetaObject();
}

void igNonRefCountedObjectList_InitFields(void) {
    int index;
    void **found;
    igMemoryRefMetaField *field;
    void *meta;

    meta = (void *)(g_igNonRefCountedObjectList_metaObject[0]);
    found = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)meta, data)));
    index = ObjectPointerList_FindIndex((char *)((igMetaObject *)meta)->_metaFields, (int)found);
    field = (igMemoryRefMetaField *)(((igObjectDispatchView *)(found))->cloneViaMetadata((int)(1)));
    field->_memType = igObjectRefMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_refCounted = 0;
    field->_externalEnumStorage = (int)(&g_igNonRefCountedObjectList_dataStorage[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, index, (igMetaField *)field);
    field->_refCount = (int)((int) (field->_refCount - 1));
    if (((unsigned long long) ((long long)(int)field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

