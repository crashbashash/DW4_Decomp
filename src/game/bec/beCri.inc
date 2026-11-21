igMetaObject *g_beCri_metaObject;
igMetaField *g_beCri_systemMetaField;
igMetaField *g_beCri_execDvdErrMetaField;
igMetaField *g_beCri_requestMetaField;
igMetaField *g_beCri_hdBGMMetaField;
igMetaField *g_beCri_hdENVMetaField;
igMetaField *g_beCri_hdSEsMetaField;
igMetaField *g_beCri_infoListMetaField;
igMetaField *g_beCri_lsBinObjsMetaField;
igMetaField *g_beCri_baseVolumeMetaField;
igMetaField *g_beCri_sndfVolumeMetaField;
igMetaField *g_beCri_pauseOnetimeMetaField;
igMetaField *g_beCri_dataTypeMetaField;

beCri *beCri_CreateInstance(int allocator) {
    beCri_EnsureRegistered();
    return (beCri *)igMetaObject_CreateInstance(g_beCri_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beCri_GetOrCreateMetaObject(void) {
    if (g_beCri_metaObject == 0) {
        g_beCri_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beCri_metaObject;
}

void *beCri_GetMetaObject(void) {
    igMetaObject *g = g_beCri_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beCri_EnsureRegistered();
    }
    return g_beCri_metaObject;
}

int beCri_GetVTable(void) {
    beCri obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beCri_vtable[0];
    obj._hdBGM = 0;
    obj._hdENV = 0;
    obj._hdSEs = 0;
    obj._infoList = 0;
    obj._lsBinObjs = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beCri_vtable[0];
    igSmartPointer_igObjectList_Destruct((igSmartPointer<igObject> *)&obj._lsBinObjs, -1);
    igSmartPointer_igInfoList_Destruct((igSmartPointer<igObject> *)&obj._infoList, -1);
    igSmartPointer_beCriHandleList_Destruct((igSmartPointer<igObject> *)(&obj._hdSEs), (short)(-1));
    igSmartPointer_beCriHandle_Destruct((igSmartPointer<igObject> *)(&obj._hdENV), (short)(-1));
    igSmartPointer_beCriHandle_Destruct((igSmartPointer<igObject> *)(&obj._hdBGM), (short)(-1));
    igInfoManager_Destroy((igInfoManager *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beCriHandle_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beCriHandleList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

void beCri_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCri_Register);
}

static igMetaObjectCallback g_beCri_callbackList[] = { beSystem_EnsureRegistered, beCriHandle_EnsureRegistered, beCriHandleList_EnsureRegistered, igInfoList_EnsureRegistered, Gap::Core::igObjectList::arkRegister, 0 };

CallbackArray *beCri_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCri_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beCri_GetMetaObjectFunction,
        "beCri",
        0x48, /* instance size */
        beCri_GetVTable,
        beCri_InitFields,
        0, /* extra callback item */
        g_beCri_callbackList /* callback list */
    );
}

void beCri_GetMetaObjectFunction(void)
{
    beCri_GetMetaObject();
}

static FieldFactory g_beCri_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igLongMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beCri_fieldTable[] = {
    "_system",
    "_execDvdErr",
    "_request",
    "_hdBGM",
    "_hdENV",
    "_hdSEs",
    "_infoList",
    "_lsBinObjs",
    "_baseVolume",
    "_sndfVolume",
    "_pauseOnetime",
    "_dataType",
};
static igMetaField **g_beCri_fieldHandles[] = {
    &g_beCri_systemMetaField,
    &g_beCri_execDvdErrMetaField,
    &g_beCri_requestMetaField,
    &g_beCri_hdBGMMetaField,
    &g_beCri_hdENVMetaField,
    &g_beCri_hdSEsMetaField,
    &g_beCri_infoListMetaField,
    &g_beCri_lsBinObjsMetaField,
    &g_beCri_baseVolumeMetaField,
    &g_beCri_sndfVolumeMetaField,
    &g_beCri_pauseOnetimeMetaField,
    &g_beCri_dataTypeMetaField,
};
static int g_beCri_fieldOffsets[] = {
    16,
    20,
    24,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
};

void beCri_InitFields(void) {
    void *system;
    void *hdBGM;
    void *hdENV;
    void *hdSEs;
    void *infoList;
    void *lsBinObjs;
    void *meta;
    int base;

    meta = (void *)g_beCri_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beCri_ctorTable, 0xC);
    system = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base));
    ((igObjectRefMetaField *)system)->_metaObject = (int)beSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)system)->_refCounted = 0;
    hdBGM = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3));
    ((igObjectRefMetaField *)hdBGM)->_metaObject = (int)beCriHandle_GetOrCreateMetaObject();
    hdENV = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4));
    ((igObjectRefMetaField *)hdENV)->_metaObject = (int)beCriHandle_GetOrCreateMetaObject();
    hdSEs = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5));
    ((igObjectRefMetaField *)hdSEs)->_metaObject = (int)beCriHandleList_GetOrCreateMetaObject();
    ((igRefMetaField *)hdSEs)->_construct = 1;
    infoList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6));
    ((igObjectRefMetaField *)infoList)->_metaObject = (int)igInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)infoList)->_construct = 1;
    lsBinObjs = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7));
    ((igObjectRefMetaField *)lsBinObjs)->_metaObject = (int)Gap::Core::igObjectList::getClassTypeLazy();
    ((igRefMetaField *)lsBinObjs)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beCri_fieldTable, g_beCri_fieldHandles, g_beCri_fieldOffsets, base);
}

