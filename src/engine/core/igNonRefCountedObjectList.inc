igMetaObject *g_igNonRefCountedObjectList_metaObject;
int g_igNonRefCountedObjectList_dataStorage;

igMetaObject *igNonRefCountedObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedObjectList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNonRefCountedObjectList_EnsureRegistered();
    return g_igNonRefCountedObjectList_metaObject;
}

int igNonRefCountedObjectList_GetVTable(void) {
    igNonRefCountedObjectList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igNonRefCountedObjectList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igNonRefCountedObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedObjectList_Register);
}

CallbackArray *igNonRefCountedObjectList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igNonRefCountedObjectList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        igNonRefCountedObjectList_GetMetaObjectFunction,
        "igNonRefCountedObjectList",
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

    meta = (void *)(g_igNonRefCountedObjectList_metaObject);
    found = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)meta, data)));
    index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)((char *)((igMetaObject *)meta)->_metaFields), (int)found);
    field = (igMemoryRefMetaField *)(((igObjectDispatchView *)(found))->CloneViaMetadata((int)(1)));
    field->_memType = (int)Gap::Core::igObjectRefMetaField::getMetaField();
    field->_memSize = 0;
    field->_refCounted = 0;
    field->_externalEnumStorage = (int)(&g_igNonRefCountedObjectList_dataStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, index, (igMetaField *)field);
    field->_refCount = (int)((int) (field->_refCount - 1));
    if (((unsigned long long) ((long long)(int)field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

