void * igObjectList_Create(int arg0) {
    igObjectList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585B60), (igMemoryPoolView *)arg0));
}

/* Created with allocation only, no field registration, when missing. */
int igObjectList_GetOrCreateMetaObject(void) {
    if (((int *)g_igObjectList_metaObject)[0] == 0) {
        ((int *)g_igObjectList_metaObject)[0] = (int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return ((int *)g_igObjectList_metaObject)[0];
}

igMetaObject *igObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igObjectList_EnsureRegistered();
    return g_igObjectList_metaObject[0];
}

int igObjectList_GetVTable(void) {
    igObjectList obj;

    igObject_InitHeader((igObject *)&obj);
    obj._vtable = (int)&DAT_005249b0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igObjectList_Register);
}

void *igObjectList_Register(void) {
    CoreLibrary_MarkRegistered();
    return ((void *)igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igObjectList_metaObject),
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        igObjectList_GetMetaObjectFunction,
        igObjectList_className,
        0x14, /* instance size */
        igObjectList_GetVTable,
        igObjectList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    ));
}

void igObjectList_GetMetaObjectFunction(void) {
    igObjectList_GetMetaObject();
}

static inline void releaseField_2bd830(igMemoryRefMetaField *f) {
    f->_refCount = (int)f->_refCount - 1;
    if (((unsigned long long)((long long)(int)f->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(f);
    }
}

void igObjectList_InitFields(void) {
    igMetaObject *meta = g_igObjectList_metaObject[0];
    igMemoryRefMetaField *field = (igMemoryRefMetaField *)((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)data));
    int index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    field = (igMemoryRefMetaField *)((igObjectDispatchView *)field)->cloneViaMetadata(1);
    field->_memType = igObjectRefMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)g_igObjectList_dataDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    releaseField_2bd830(field);
}

