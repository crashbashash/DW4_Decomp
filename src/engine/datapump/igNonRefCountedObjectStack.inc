igMetaObject *g_igNonRefCountedObjectStack_metaObject;
igMetaField *g_igNonRefCountedObjectStack_dataMetaField;

igMetaObject *igNonRefCountedObjectStack_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedObjectStack_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNonRefCountedObjectStack_EnsureRegistered();
    return g_igNonRefCountedObjectStack_metaObject;
}

int igNonRefCountedObjectStack_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igNonRefCountedObjectStack_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igNonRefCountedObjectStack_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedObjectStack_Register);
}

CallbackArray *igNonRefCountedObjectStack_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igNonRefCountedObjectStack_metaObject,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        igNonRefCountedObjectStack_GetMetaObjectFunction,
        "igNonRefCountedObjectStack",
        0x14, /* instance size */
        igNonRefCountedObjectStack_GetVTable,
        igNonRefCountedObjectStack_InitFields, /* Field adder. */
        0,                                                  /* extra callback-vector item (none) */
        0                                                   /* zero-terminated callback-vector item list (none) */
    );
}

void igNonRefCountedObjectStack_GetMetaObjectFunction(void) {
    igNonRefCountedObjectStack_GetMetaObject();
}

void igNonRefCountedObjectStack_InitFields(void) {
    int index;
    void **found;
    igMemoryRefMetaField *field;
    igMetaObject *meta;

    meta = g_igNonRefCountedObjectStack_metaObject;
    found = (void **)igMetaObject_FindFieldByName(meta, "_data");
    index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)meta->_metaFields, (int)found);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)found)->CloneViaMetadata(1);
    field->_memType = (int)Gap::Core::igObjectRefMetaField::getMetaField();
    field->_memSize = 0;
    field->_refCounted = 0;
    field->_externalEnumStorage = (int)&g_igNonRefCountedObjectStack_dataMetaField;
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)((int) (field->_refCount - 1));
    if (((unsigned long long) ((long long) (int) field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

