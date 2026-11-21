igMetaObject *g_igFileInfo_metaObject;
igMetaField *g_igFileInfo_externalEntryListMetaField;
igMetaField *g_igFileInfo_infoListMetaField;
igMetaField *g_igFileInfo_fileInfoListMetaField;
igMetaField *g_igFileInfo_cachedFileMetaField;

igMetaObject *igFileInfo_GetOrCreateMetaObject(void) {
    if (g_igFileInfo_metaObject == 0) {
        g_igFileInfo_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igFileInfo_metaObject;
}

igMetaObject *igFileInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igFileInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002290c0();
    return g_igFileInfo_metaObject;
}

int igFileInfo_GetVTable(void) {
    struct Obj_8 obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.w[1] = 0;
    obj.vt = &g_igFileInfo_vtable[0];
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    r = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igFileInfo_vtable[0];
    FUN_00229040((R **)&obj.w[5], -1);
    FUN_00228fc0((ObjectRefWord *)&obj.w[4], -1);
    igSmartPointer_igInfoList_Destruct((igSmartPointer<igObject> *)&obj.w[3], -1);
    igSmartPointer_igDirectory_Destruct((igSmartPointer<igObject> *)&obj.w[2], -1);
    igNamedObject_Destroy((igNamedObject *)&obj, 0);
    return r;
}

/* Deleting destructor; the deletion flag is a signed short. */
ObjectRefWord *FUN_00228fc0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

struct R **FUN_00229040(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void FUN_002290c0(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igFileInfo_Register);
}

static igMetaObjectCallback g_igFileInfo_callbackList[] = { Gap::Core::igDirectory::arkRegister, igInfoList_EnsureRegistered, FUN_00228dd0, igIGBFile_EnsureRegistered, 0 };

CallbackArray *igFileInfo_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFileInfo_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        (igMetaObjectGetFunction)igNamedObject_GetPublishedMetaObject,
        igFileInfo_GetMetaObjectFunction,
        "igFileInfo",
        0x1C, /* instance size */
        igFileInfo_GetVTable,
        &igFileInfo_InitFields,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igFileInfo_callbackList /* callback list */
    );
}

void igFileInfo_GetMetaObjectFunction(void) {
    igFileInfo_GetMetaObject();
}

static FieldFactory g_igFileInfo_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igFileInfo_fieldTable[] = {
    "_externalEntryList",
    "_infoList",
    "_fileInfoList",
    "_cachedFile",
};
static igMetaField **g_igFileInfo_fieldHandles[] = {
    &g_igFileInfo_externalEntryListMetaField,
    &g_igFileInfo_infoListMetaField,
    &g_igFileInfo_fileInfoListMetaField,
    &g_igFileInfo_cachedFileMetaField,
};
static int g_igFileInfo_fieldOffsets[] = {
    12,
    16,
    20,
    24,
};

void igFileInfo_InitFields(void) {
    int base;
    void *field;
    void *field2;
    void *field3;
    void *field4;
    igMetaObject *meta;

    meta = g_igFileInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igFileInfo_ctorTable, 4);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field)->_metaObject = (int)Gap::Core::igDirectory::getClassTypeLazy();
    ((igRefMetaField *)field)->_construct = 1;
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)igInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)field2)->_construct = 1;
    field3 = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)field3)->_metaObject = (int)igFileInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)field3)->_construct = 1;
    field4 = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)field4)->_metaObject = igIGBFile_GetOrCreateMetaObject();
    ((igRefMetaField *)field4)->_construct = 1;
    igMetaObject_NameFields(meta, g_igFileInfo_fieldTable, g_igFileInfo_fieldHandles, g_igFileInfo_fieldOffsets, base);
}

int *FUN_00229260(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

igStringRef *igStringRef_Construct(igStringRef *self)
{
    self->p = 0;
    return self;
}

