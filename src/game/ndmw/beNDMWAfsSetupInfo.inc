igMetaObject *g_beNDMWAfsSetupInfo_metaObject;
igMetaField *g_beNDMWAfsSetupInfo_insideFilesMetaField;
igMetaField *g_beNDMWAfsSetupInfo_dataListMetaField;

void *beNDMWAfsSetupInfo_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWAfsSetupInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWAfsSetupInfo_EnsureRegistered();
    }
    return g_beNDMWAfsSetupInfo_metaObject;
}

int beNDMWAfsSetupInfo_GetVTable(void) {
    beNDMWAfsSetupInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWAfsSetupInfo_vtable[0];
    obj._name = 0;
    obj._insideFiles = 0;
    obj._dataList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWAfsSetupInfo_vtable[0];
    igSmartPointer_beNDMWAfsSetupDataList_Destruct((igSmartPointer<igObject> *)&obj._dataList, -1);
    igSmartPointer_igAdxAfsFileList_Destruct(&obj._insideFiles, -1);
    igInfo_Destroy((igInfo *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWAfsSetupDataList_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beNDMWAfsSetupInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetupInfo_Register);
}

static igMetaObjectCallback g_beNDMWAfsSetupInfo_callbackList[] = { igAdxAfsFileList_EnsureRegistered, beNDMWAfsSetupDataList_EnsureRegistered, 0 };

CallbackArray *beNDMWAfsSetupInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWAfsSetupInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beNDMWAfsSetupInfo_GetMetaObject,
        "beNDMWAfsSetupInfo",
        0x1c, /* instance size */
        beNDMWAfsSetupInfo_GetVTable,
        beNDMWAfsSetupInfo_InitFields,
        0, /* extra callback item */
        g_beNDMWAfsSetupInfo_callbackList /* callback list */
    );
}

void beNDMWAfsSetupInfo_GetMetaObject(void)
{
    beNDMWAfsSetupInfo_ResolveMetaObject();
}

static FieldFactory g_beNDMWAfsSetupInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWAfsSetupInfo_fieldTable[] = {
    "_insideFiles",
    "_dataList",
};
static igMetaField **g_beNDMWAfsSetupInfo_fieldHandles[] = {
    &g_beNDMWAfsSetupInfo_insideFilesMetaField,
    &g_beNDMWAfsSetupInfo_dataListMetaField,
};
static int g_beNDMWAfsSetupInfo_fieldOffsets[] = {
    20,
    24,
};

void beNDMWAfsSetupInfo_InitFields(void) {
    int base;
    void *dataList;
    void *insideFiles;
    igMetaObject *meta;

    meta = g_beNDMWAfsSetupInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWAfsSetupInfo_ctorTable, 2);
    insideFiles = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)insideFiles)->_metaObject = (int)igAdxAfsFileList_GetOrCreateMetaObject();
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beNDMWAfsSetupDataList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWAfsSetupInfo_fieldTable, g_beNDMWAfsSetupInfo_fieldHandles, g_beNDMWAfsSetupInfo_fieldOffsets, base);
}

