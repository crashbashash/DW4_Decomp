igMetaObject *g_beLuaInfo_metaObject;
igMetaField *g_beLuaInfo_dataListMetaField;

igMetaObject *beLuaInfo_GetMetaObject(void)
{
    igMetaObject *g = g_beLuaInfo_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beLuaInfo_EnsureRegistered();
    return g_beLuaInfo_metaObject;
}

int beLuaInfo_GetVTable(void) {
    beLuaInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beLuaInfo_vtable[0];
    obj._dataList_ = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beLuaInfo_vtable[0];
    igSmartPointer_beLuaDataList_Destruct((igSmartPointer<igObject> *)&obj._dataList_, -1);
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beLuaDataList_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void beLuaInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLuaInfo_Register);
}

static igMetaObjectCallback g_beLuaInfo_callbackList[] = { beLuaDataList_EnsureRegistered, 0 };

void *beLuaInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLuaInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beLuaInfo_GetMetaObjectFunction,
        "beLuaInfo",
        0x20, /* instance size */
        beLuaInfo_GetVTable,
        beLuaInfo_InitFields,
        0, /* extra callback item */
        g_beLuaInfo_callbackList /* callback list */
    );
}

void beLuaInfo_GetMetaObjectFunction(void)
{
    beLuaInfo_GetMetaObject();
}

static FieldFactory g_beLuaInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beLuaInfo_fieldTable[] = {
    "_dataList",
};
static igMetaField **g_beLuaInfo_fieldHandles[] = {
    &g_beLuaInfo_dataListMetaField,
};
static int g_beLuaInfo_fieldOffsets[] = {
    28,
};

void beLuaInfo_InitFields(void) {
    int base;
    void *dataList;
    void *meta;

    meta = (void *)g_beLuaInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beLuaInfo_ctorTable, 1);
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beLuaDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)dataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beLuaInfo_fieldTable, g_beLuaInfo_fieldHandles, g_beLuaInfo_fieldOffsets, base);
}

