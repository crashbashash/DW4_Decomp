int FUN_002caa60(void) {
    return DAT_00586880[0];
}

void * FUN_002caa70(int arg0) {
    igIntList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586880), (MemoryPool *)arg0));
}

/* Created with allocation only when missing. */
int igIntList_GetOrCreateMetaObject(void) {
    if (((int *)g_igIntList_metaObject)[0] == 0) {
        ((int *)g_igIntList_metaObject)[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]))));
    }
    return ((int *)g_igIntList_metaObject)[0];
}

igMetaObject *igIntList_GetMetaObject(void)
{
    igMetaObject *g = g_igIntList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igIntList_EnsureRegistered();
    return g_igIntList_metaObject[0];
}

int igIntList_GetVTable(void) {
    struct Obj_2cab50 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00531b70[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
}

void igIntList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igIntList_Register);
}

void *igIntList_Register(void) {
    FUN_002b5d50();
    return ((void *)igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igIntList_metaObject),
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igIntList_GetMetaObject,
        igIntList_className,
        0x14, /* instance size */
        igIntList_GetVTable,
        igIntList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    ));
}

void thunk_igIntList_GetMetaObject(void) {
    igIntList_GetMetaObject();
}

static inline void releaseField_2cac20(igMemoryRefMetaField *f) {
    f->_refCount = (int)f->_refCount - 1;
    if (((unsigned long long)((long long)(int)f->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(f);
    }
}

void igIntList_InitFields(void) {
    igMetaObject *meta = g_igIntList_metaObject[0];
    igMemoryRefMetaField *field = (igMemoryRefMetaField *)((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)data));
    int index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    field = ((DescriptorCloneView_2cac20 *)field)->Clone(1);
    field->_memType = igIntMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)g_igIntList_dataDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    releaseField_2cac20(field);
}

