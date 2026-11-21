igMetaObject *g_igLongStack_metaObject;
igMetaField *g_igLongStack_dataMetaField;

igMetaObject *igLongStack_GetOrCreateMetaObject(void) {
    if (g_igLongStack_metaObject == 0) {
        g_igLongStack_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLongStack_metaObject;
}

igMetaObject *igLongStack_GetMetaObject(void)
{
    igMetaObject *g = g_igLongStack_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLongStack_EnsureRegistered();
    return g_igLongStack_metaObject;
}

int igLongStack_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igLongStack_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igLongStack_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLongStack_Register);
}

CallbackArray *igLongStack_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLongStack_metaObject,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        igLongStack_GetMetaObjectFunction,
        "igLongStack",
        0x14, /* instance size */
        igLongStack_GetVTable,
        igLongStack_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igLongStack_GetMetaObjectFunction(void) {
    igLongStack_GetMetaObject();
}

void igLongStack_InitFields(void) {
    int index;
    void **found;
    igMemoryRefMetaField *field;
    igMetaObject *meta;

    meta = g_igLongStack_metaObject;
    found = (void **)igMetaObject_FindFieldByName(meta, "_data");
    index = ((Gap::Core::__internalNonRefCountedObjectList *)meta->_metaFields)->find((Gap::Core::igObject *)found);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)found)->CloneViaMetadata(1);
    field->_memType = (int)Gap::Core::igLongMetaField::getMetaField();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)&g_igLongStack_dataMetaField;
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)((int) (field->_refCount - 1));
    if (((unsigned long long) ((long long) (int) field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

