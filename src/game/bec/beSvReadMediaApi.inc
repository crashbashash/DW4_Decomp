igMetaObject *g_beSvReadMediaApi_metaObject;
igMetaField *g_beSvReadMediaApi_outputGamedataMetaField;
igMetaField *g_beSvReadMediaApi_gameDataMetaField;
igMetaField *g_beSvReadMediaApi_oneSvDataSizeMetaField;
igMetaField *g_beSvReadMediaApi_lodeDataMetaField;
igMetaField *g_beSvReadMediaApi_loadWorkListMetaField;

void beSvReadMediaApi_Create(int allocator) {
    beSvReadMediaApi_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588238, allocator);
}

igMetaObject *beSvReadMediaApi_GetMetaObject(void) {
    if (g_beSvReadMediaApi_metaObject == 0 || !isValid(g_beSvReadMediaApi_metaObject)) beSvReadMediaApi_EnsureRegistered();
    return g_beSvReadMediaApi_metaObject;
}

int beSvReadMediaApi_GetVTable(void) {
    struct Obj_349300 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.vt = &g_beSvReadMediaApi_vtable[0];
    obj.w17 = 0;
    obj.w19 = 0;
    obj.w20 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beSvReadMediaApi_vtable[0];
    igSmartPointer_igObjectList_Destruct(&obj.w20, -1);
    FUN_003493b0((igSmartPointer<igObject> *)&obj.w19, (short)(-1));
    FUN_00349080((igSmartPointer<igObject> *)&obj.w17, (long long)(-1));
    FUN_00348390((struct S_348390 *)&obj, (short)0);
    return t;
}

igSmartPointer<igObject> *FUN_003493b0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void beSvReadMediaApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvReadMediaApi_Register);
}

static igMetaObjectCallback g_beSvReadMediaApi_callbackList[] = { beSvPlatBaseData_EnsureRegistered, beSaveDataDeliver_EnsureRegistered, igObjectList_EnsureRegistered, 0 };

void *beSvReadMediaApi_Register(void) {
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
    void *meta;

    meta = (void *)g_beSvReadMediaApi_metaObject;
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
    ((igObjectRefMetaField *)loadWorkList)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)loadWorkList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beSvReadMediaApi_fieldTable, g_beSvReadMediaApi_fieldHandles, g_beSvReadMediaApi_fieldOffsets, base);
}

