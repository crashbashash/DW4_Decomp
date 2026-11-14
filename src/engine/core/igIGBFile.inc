void * igIGBFile_Create(int arg0) {
    igIGBFile_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586140), (igMemoryPoolView *)arg0));
}

int igIGBFile_GetOrCreateMetaObject(void) {
    if (((int *)g_igIGBFile_metaObject)[0] == 0) {
        ((int *)g_igIGBFile_metaObject)[0] = (int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return ((int *)g_igIGBFile_metaObject)[0];
}

igMetaObject *igIGBFile_GetMetaObject(void)
{
    igMetaObject *g = g_igIGBFile_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igIGBFile_EnsureRegistered();
    return g_igIGBFile_metaObject[0];
}

int igIGBFile_GetVTable(void) {
    igIGBFile file;
    int temp_s5;

    igDirectory_Construct(&file);
    file._vtable = (int)(&DAT_0052fe50[0]);
    igSmartPointer_igObjectList_Construct(&file._entryPool);
    igSmartPointer_igFile_Construct(&file._file);
    igSmartPointer_igMetaFieldList_Construct(&file._metaFieldListInFile);
    FUN_001a4510(&file._metaObjectListInFile);
    igSmartPointer_igMetaField_Construct(&file.imf);
    igSmartPointer_igMetaField_Construct(&file.smf);
    FUN_00229270(&file._previousResourceFilePath);
    FUN_001510d0(&file._alignmentListInFile);
    igSmartPointer_igMemoryPool_Construct(&file._temporaryMemoryPool);
    igSmartPointer_igMemoryPool_Construct(&file._dataMemoryPool);
    igSmartPointer_igMemoryPool_Construct(&file._objectMemoryPool);
    FUN_001510d0(&file._memoryPoolHandles);
    temp_s5 = *(int *)((char *)&file + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    file._vtable = (int)(&DAT_0052fe40[4]);
    ObjectRef_Destruct_00150eb0(&file._memoryPoolHandles, -1);
    FUN_001509f0(&file._objectMemoryPool, -1);
    FUN_001509f0(&file._dataMemoryPool, -1);
    FUN_001509f0(&file._temporaryMemoryPool, -1);
    ObjectRef_Destruct_00150eb0(&file._alignmentListInFile, -1);
    StringRef_Destruct_00130720(&file._previousResourceFilePath, -1);
    FUN_0014ec50(&file.smf, -1);
    FUN_0014ec50(&file.imf, -1);
    FUN_0013a880(&file._metaObjectListInFile, -1);
    FUN_0014e420(&file._metaFieldListInFile, -1);
    FUN_00150180(&file._file, -1);
    FUN_0014aa70(&file._entryPool, -1);
    igDirectory_Destroy((igDirectory *)&file, 0);
    return temp_s5;
}

igSmartPointer<igObject> *igSmartPointer_igShortListList_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if(self) {
        igObject *object=self->p;
        if(object) {
            --object->_refCount;
            if(((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

igDirectory *igDirectory_Destroy(igDirectory *p, short n) {
    if (p) {
        p->_vtable = (int)&DAT_00530890[0];
        ((igSmartPointer<igObject> *)&p->_loadingSemaphore)->~igSmartPointer();
        ((igSmartPointer<igObject> *)&p->_metaFieldPerObjectIndices)->~igSmartPointer();
        ((igSmartPointer<igObject> *)&p->_refList)->~igSmartPointer();
        ((igSmartPointer<igObject> *)&p->_uniqueEntryList)->~igSmartPointer();
        ((igSmartPointer<igObject> *)&p->_infoList)->~igSmartPointer();
        ((igSmartPointer<igObject> *)&p->_externalDirectoryList)->~igSmartPointer();
        ((igStringRef *)&p->_name)->~igStringRef();
        if (n > 0) thunk_Memory_FreeBuffer((int)p);
    }
    return p;
}

int *igSmartPointer_igMemoryPool_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_igMetaField_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_igMetaFieldList_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_igFile_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_igObjectList_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void *igDirectory_Construct(igIGBFile *arg0) {
    igObject_InitHeader((igObject *)arg0);
    arg0->_vtable = (int)(&DAT_005309b0[0]);
    arg0->_vtable = (int)(&DAT_00524a20[0]);
    arg0->_vtable = (int)(&DAT_005249b0[0]);
    arg0->_vtable = (int)(&DAT_00532590[0]);
    arg0->_vtable = (int)(&DAT_00530890[0]);
    arg0->_name = 0;
    arg0->_externalDirectoryList = 0;
    arg0->_infoList = 0;
    arg0->_uniqueEntryList = 0;
    arg0->_refList = 0;
    arg0->_metaFieldPerObjectIndices = 0;
    arg0->_loadingSemaphore = 0;
    return arg0;
}

void igIGBFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igIGBFile_Register);
}

void igIGBFile_Register(void) {
    CoreLibrary_MarkRegistered();  /* First-use initializer: sets a gp byte flag, then runs five one-time init calls. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igIGBFile_metaObject),
        igDirectory_Register,
        igDirectory_GetPublishedMetaObject,
        igIGBFile_GetMetaObjectFunction,
        igIGBFile_className,
        sizeof(igIGBFile),                           /* Instance size. */
        igIGBFile_GetVTable,
        &igIGBFile_InitFields,
        igIGBFile_StaticInitCallback, /* extra callback item */
        g_igIGBFile_callbackList /* callback list */
    );
}

void igIGBFile_GetMetaObjectFunction(void) {
    igIGBFile_GetMetaObject();
}

igMetaObject *igDirectory_GetPublishedMetaObject(void) {
    return g_igDirectory_metaObject[0];
}

void igIGBFile_InitFields(void) {
    igMetaObject *meta = g_igIGBFile_metaObject[0];
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    igMetaField *clone;
    int index;
    igMetaObject_CreateFields(meta, (igMetaField * (**)(void *))g_igIGBFile_ctorTable, 0x41);
    field = ((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)data));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    clone = (igMetaField *)((igObjectDispatchView *)field)->cloneViaMetadata(1);
    clone->_persistent = 0;
    clone->_externalEnumStorage = (int)DAT_00586148;
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    releaseField(clone);
    field = ((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)text_count));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    clone = (igMetaField *)((igObjectDispatchView *)field)->cloneViaMetadata(1);
    clone->_persistent = 0;
    clone->_externalEnumStorage = (int)DAT_00586150;
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    releaseField(clone);
    field = ((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)text_capacity));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    clone = (igMetaField *)((igObjectDispatchView *)field)->cloneViaMetadata(1);
    clone->_persistent = 0;
    clone->_externalEnumStorage = (int)DAT_00586158;
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    releaseField(clone);
    igIntMetaField_SetDefault((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base))), 0xFADA);
    igIntMetaField_SetDefault((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 1))), 6);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igFile_GetOrCreateMetaObject();
    ((igMetaField *)field)->_persistent = 0;
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 8));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x12))->_persistent = 0;
    igIntMetaField_SetDefault((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x13))), -1);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x15));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x16));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x17));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x18));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x19));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMetaFieldList_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x1A));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMetaObjectList_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x1C));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x1D));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMetaField_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x1E));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMetaField_GetOrCreateMetaObject();
    igIntMetaField_SetDefault((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x24))), -1);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x25));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    igStringMetaField_SetDefaultText((int *)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x27))), 0);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x28));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x2A));
    ((igObjectRefMetaField *)field)->_metaObject = igIntList_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x2C));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    igIntMetaField_SetDefault((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x2E))), -1);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x2F));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    igIntMetaField_SetDefault((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x32))), -1);
    igBoolMetaField_SetDefaultValue((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x36))), 1);
    igBoolMetaField_SetDefaultValue((void **)(((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x37))), 1);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x39));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x3A));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x3B));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x3C));
    ((igObjectRefMetaField *)field)->_metaObject = igObjectList_GetOrCreateMetaObject();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x3F));
    ((igMemoryRefMetaField *)field)->_memType = igCharMetaField_GetDefaultDescriptor();
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x40));
    ((igObjectRefMetaField *)field)->_metaObject = igIntList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, (const char **)&g_igIGBFile_fieldTable[0], (igMetaField ***)&DAT_004c0880[0], &DAT_004c0990[0], base);
}

void igIGBFile_StaticInitCallback(void) {
    igIGBFile_RegisterBlindObjectsConfig();
}

