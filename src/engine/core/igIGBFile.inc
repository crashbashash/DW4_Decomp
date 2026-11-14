void * igIGBFile_Create(int pool) {
    igIGBFile_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586140), (igMemoryPoolView *)pool));
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
    int vtable;

    igDirectory_Construct(&file);
    file._vtable = (int)(&g_igIGBFile_vtable[0]);
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
    vtable = *(int *)((char *)&file + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    file._vtable = (int)(&g_igInfo_vtable[28]); /* matching construct: igIGBFile's vtable address (it follows igInfo's 28 words) spelled through another symbol, so it is rematerialised rather than reused */
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
    return vtable;
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
        p->_vtable = (int)&g_igDirectory_vtable[0];
        ((igSmartPointer<igObject> *)&p->_loadingSemaphore)->~igSmartPointer();
        ((igSmartPointer<igObject> *)&p->_metaFieldPerObjectIndices)->~igSmartPointer();
        ((igSmartPointer<igObject> *)&p->_refList)->~igSmartPointer();
        ((igSmartPointer<igObject> *)&p->_uniqueEntryList)->~igSmartPointer();
        ((igSmartPointer<igObject> *)&p->_infoList)->~igSmartPointer();
        ((igSmartPointer<igObject> *)&p->_externalDirectoryList)->~igSmartPointer();
        ((igStringRef *)&p->_name)->~igStringRef();
        if (n > 0) Memory_FreeBufferAliasC((int)p);
    }
    return p;
}

int *igSmartPointer_igMemoryPool_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igMetaField_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igMetaFieldList_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igFile_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igObjectList_Construct(int *p)
{
    *p = 0;
    return p;
}

void *igDirectory_Construct(igIGBFile *self) {
    igObject_InitHeader((igObject *)self);
    self->_vtable = (int)(&g_igDataList_vtable[0]);
    self->_vtable = (int)(&g_igObjectListBase_vtable[0]);
    self->_vtable = (int)(&g_igObjectList_vtable[0]);
    self->_vtable = (int)(&g_igDirectoryBase_vtable[0]);
    self->_vtable = (int)(&g_igDirectory_vtable[0]);
    self->_name = 0;
    self->_externalDirectoryList = 0;
    self->_infoList = 0;
    self->_uniqueEntryList = 0;
    self->_refList = 0;
    self->_metaFieldPerObjectIndices = 0;
    self->_loadingSemaphore = 0;
    return self;
}

void igIGBFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igIGBFile_Register);
}

void igIGBFile_Register(void) {
    CoreLibrary_MarkRegistered();  /* First-use initializer: sets a gp byte flag, then runs five one-time init calls. */
    igMetaObject_RegisterClass(
        0,
        g_igIGBFile_metaObject,
        (igMetaObjectRegisterFunction)igDirectory_Register,
        igDirectory_GetPublishedMetaObject,
        igIGBFile_GetMetaObjectFunction,
        igIGBFile_className,
        sizeof(igIGBFile),
        igIGBFile_GetVTable,
        igIGBFile_InitFields,
        igIGBFile_StaticInitCallback,
        (igMetaObjectCallback *)g_igIGBFile_callbackList
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
    clone = (igMetaField *)((igObjectDispatchView *)field)->CloneViaMetadata(1);
    clone->_persistent = 0;
    clone->_externalEnumStorage = (int)g_igIGBFile_dataDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    releaseField(clone);
    field = ((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)text_count));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    clone = (igMetaField *)((igObjectDispatchView *)field)->CloneViaMetadata(1);
    clone->_persistent = 0;
    clone->_externalEnumStorage = (int)g_igIGBFile_countDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    releaseField(clone);
    field = ((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)text_capacity));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    clone = (igMetaField *)((igObjectDispatchView *)field)->CloneViaMetadata(1);
    clone->_persistent = 0;
    clone->_externalEnumStorage = (int)g_igIGBFile_capacityDescriptorCell;
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
    igMetaObject_NameFields(meta, (const char **)&g_igIGBFile_fieldTable[0], (igMetaField ***)&g_igIGBFile_fieldDescriptors[0], &g_igIGBFile_fieldOffsets[0], base);
}

void igIGBFile_StaticInitCallback(void) {
    igIGBFile_RegisterBlindObjectsConfig();
}

