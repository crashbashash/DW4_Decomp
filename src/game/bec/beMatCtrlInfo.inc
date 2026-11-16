igMetaObject *g_beMatCtrlInfo_metaObject;
igMetaField *g_beMatCtrlInfo_switchgraphMetaField;
igMetaField *g_beMatCtrlInfo_dataListMetaField;
igMetaField *g_beMatCtrlInfo_searchMetaField;

void *beMatCtrlInfo_GetMetaObject(void) {
    igMetaObject *g = g_beMatCtrlInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMatCtrlInfo_EnsureRegistered();
    }
    return g_beMatCtrlInfo_metaObject;
}

int beMatCtrlInfo_GetVTable(void) {
    struct Obj_359b20 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.vt = &g_beMatCtrlInfo_vtable[0];
    obj.w[6] = 0;
    obj.w[7] = 0;
    obj.w[8] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beMatCtrlInfo_vtable[0];
    FUN_00359c50((igSmartPointer<igObject> *)(&obj.w[8]), (short)(-1));
    FUN_00359bd0((igSmartPointer<igObject> *)(&obj.w[7]), (long long)(-1));
    FUN_00343260((igSmartPointer<igObject> *)(&obj.w[6]), -1);
    FUN_0033ec80((struct S_33ec80 *)((int *)&obj), (short)0);
    return t;
}

igSmartPointer<igObject> *FUN_00359bd0(igSmartPointer<igObject> *self, long long delete_storage) {
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

igSmartPointer<igObject> *FUN_00359c50(igSmartPointer<igObject> *self, short delete_storage) {
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

void beMatCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMatCtrlInfo_Register);
}

static igMetaObjectCallback g_beMatCtrlInfo_callbackList[] = { igSwitch_EnsureRegistered, beMatCtrlDataList_EnsureRegistered, beMatCtrlSearchList_EnsureRegistered, 0 };

void *beMatCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMatCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beMatCtrlInfo_GetMetaObjectFunction,
        "beMatCtrlInfo",
        0x28, /* instance size */
        beMatCtrlInfo_GetVTable,
        beMatCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beMatCtrlInfo_callbackList /* callback list */
    );
}

void beMatCtrlInfo_GetMetaObjectFunction(void)
{
    beMatCtrlInfo_GetMetaObject();
}

static FieldFactory g_beMatCtrlInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMatCtrlInfo_fieldTable[] = {
    "_switchgraph",
    "_dataList",
    "_search",
};
static igMetaField **g_beMatCtrlInfo_fieldHandles[] = {
    &g_beMatCtrlInfo_switchgraphMetaField,
    &g_beMatCtrlInfo_dataListMetaField,
    &g_beMatCtrlInfo_searchMetaField,
};
static int g_beMatCtrlInfo_fieldOffsets[] = {
    28,
    32,
    36,
};

void beMatCtrlInfo_InitFields(void) {
    int base;
    void *switchgraph;
    void *dataList;
    void *search;
    void *meta;

    meta = (void *)g_beMatCtrlInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMatCtrlInfo_ctorTable, 3);
    switchgraph = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)switchgraph)->_metaObject = igSwitch_GetOrCreateMetaObject();
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beMatCtrlDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)dataList)->_construct = 1;
    search = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)search)->_metaObject = (int)beMatCtrlSearchList_GetOrCreateMetaObject();
    ((igRefMetaField *)search)->_construct = 1;
    igMetaObject_NameFields(meta, g_beMatCtrlInfo_fieldTable, g_beMatCtrlInfo_fieldHandles, g_beMatCtrlInfo_fieldOffsets, base);
}

