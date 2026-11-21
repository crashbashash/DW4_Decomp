igMetaObject *g_igMatrixStack_metaObject;
igMetaField *g_igMatrixStack_dataMetaField;

igMetaObject *igMatrixStack_GetOrCreateMetaObject(void) {
    if (g_igMatrixStack_metaObject == 0) {
        g_igMatrixStack_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMatrixStack_metaObject;
}

igMetaObject *igMatrixStack_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixStack_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMatrixStack_EnsureRegistered();
    return g_igMatrixStack_metaObject;
}

int igMatrixStack_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igMatrixStack_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igMatrixStack_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMatrixStack_Register);
}

CallbackArray *igMatrixStack_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMatrixStack_metaObject,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        igMatrixStack_GetMetaObjectFunction,
        "igMatrixStack",
        0x14, /* instance size */
        igMatrixStack_GetVTable,
        igMatrixStack_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igMatrixStack_GetMetaObjectFunction(void) {
    igMatrixStack_GetMetaObject();
}

void igMatrixStack_InitFields(void) {
    int index;
    void **found;
    igMemoryRefMetaField *field;
    igMetaObject *meta;

    meta = g_igMatrixStack_metaObject;
    found = (void **)igMetaObject_FindFieldByName(meta, "_data");
    index = ((Gap::Core::__internalNonRefCountedObjectList *)meta->_metaFields)->find((Gap::Core::igObject *)found);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)found)->CloneViaMetadata(1);
    field->_memType = (int)Gap::Math::igMatrix44fMetaField::getMetaField();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)&g_igMatrixStack_dataMetaField;
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    field->_refCount = (int)((int) (field->_refCount - 1));
    if (((unsigned long long) ((long long) (int) field->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(field);
    }
}

