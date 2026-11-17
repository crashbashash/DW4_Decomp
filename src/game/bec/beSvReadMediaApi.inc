igMetaObject *g_beSvReadMediaApi_metaObject;
igMetaField *g_beSvReadMediaApi_outputGamedataMetaField;
igMetaField *g_beSvReadMediaApi_gameDataMetaField;
igMetaField *g_beSvReadMediaApi_oneSvDataSizeMetaField;
igMetaField *g_beSvReadMediaApi_lodeDataMetaField;
igMetaField *g_beSvReadMediaApi_loadWorkListMetaField;

beSvReadMediaApi *beSvReadMediaApi_Create(int allocator) {
    beSvReadMediaApi_EnsureRegistered();
    return (beSvReadMediaApi *)igMetaObject_CreateInstance(g_beSvReadMediaApi_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beSvReadMediaApi_GetMetaObject(void) {
    if (g_beSvReadMediaApi_metaObject == 0 || !isValid(g_beSvReadMediaApi_metaObject)) beSvReadMediaApi_EnsureRegistered();
    return g_beSvReadMediaApi_metaObject;
}

int beSvReadMediaApi_GetVTable(void) {
    beSvReadMediaApi obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._imageWork = 0;
    obj._mountWork = 0;
    obj._iconWork = 0;
    obj._vtable = (int)&g_beSvReadMediaApi_vtable[0];
    obj._outputGamedata = 0;
    obj._lodeData = 0;
    obj._loadWorkList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beSvReadMediaApi_vtable[0];
    igSmartPointer_igObjectList_Destruct(&obj._loadWorkList, -1);
    igSmartPointer_beSaveDataDeliver_Destruct((igSmartPointer<igObject> *)&obj._lodeData, (short)(-1));
    igSmartPointer_beSvPlatBaseData_Destruct((igSmartPointer<igObject> *)&obj._outputGamedata, (long long)(-1));
    beSaveApi_Destroy((beSaveApi *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beSaveDataDeliver_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

void beSvReadMediaApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvReadMediaApi_Register);
}

static igMetaObjectCallback g_beSvReadMediaApi_callbackList[] = { beSvPlatBaseData_EnsureRegistered, beSaveDataDeliver_EnsureRegistered, igObjectList_EnsureRegistered, 0 };

CallbackArray *beSvReadMediaApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvReadMediaApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvReadMediaApi_GetMetaObjectFunction,
        "beSvReadMediaApi",
        0x58, /* instance size */
        beSvReadMediaApi_GetVTable,
        beSvReadMediaApi_InitFields,
        0, /* extra callback item */
        g_beSvReadMediaApi_callbackList /* callback list */
    );
}

void beSvReadMediaApi_GetMetaObjectFunction(void)
{
    beSvReadMediaApi_GetMetaObject();
}

static FieldFactory g_beSvReadMediaApi_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSvReadMediaApi_fieldTable[] = {
    "_outputGamedata",
    "_gameData",
    "_oneSvDataSize",
    "_lodeData",
    "_loadWorkList",
};
static igMetaField **g_beSvReadMediaApi_fieldHandles[] = {
    &g_beSvReadMediaApi_outputGamedataMetaField,
    &g_beSvReadMediaApi_gameDataMetaField,
    &g_beSvReadMediaApi_oneSvDataSizeMetaField,
    &g_beSvReadMediaApi_lodeDataMetaField,
    &g_beSvReadMediaApi_loadWorkListMetaField,
};
static int g_beSvReadMediaApi_fieldOffsets[] = {
    68,
    64,
    72,
    76,
    80,
};

void beSvReadMediaApi_InitFields(void) {
    int base;
    void *outputGamedata;
    void *gameData;
    void *lodeData;
    void *loadWorkList;
    igMetaObject *meta;

    meta = g_beSvReadMediaApi_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSvReadMediaApi_ctorTable, 5);
    outputGamedata = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)outputGamedata)->_metaObject = (int)beSvPlatBaseData_GetOrCreateMetaObject();
    gameData = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)gameData)->_metaObject = (int)beSaveDataDeliver_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)gameData)->_refCounted = 0;
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 2), 0x10);
    lodeData = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)lodeData)->_metaObject = (int)beSaveDataDeliver_GetOrCreateMetaObject();
    loadWorkList = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)loadWorkList)->_metaObject = (int)igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)loadWorkList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beSvReadMediaApi_fieldTable, g_beSvReadMediaApi_fieldHandles, g_beSvReadMediaApi_fieldOffsets, base);
}

