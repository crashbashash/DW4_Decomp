igMetaObject *g_beGeneraterInfo_metaObject;
igMetaField *g_beGeneraterInfo_dataListMetaField;

igMetaObject *beGeneraterInfo_GetMetaObject(void) {
    igMetaObject *g = g_beGeneraterInfo_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beGeneraterInfo_EnsureRegistered();
done:
    return g_beGeneraterInfo_metaObject;
}

int beGeneraterInfo_GetVTable(void) {
    beGeneraterInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beGeneraterInfo_vtable[0];
    obj._dataList_ = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beGeneraterInfo_vtable[0];
    igSmartPointer_beGeneraterDataList_Destruct((igSmartPointer<igObject> *)(&obj._dataList_), (long long)(-1));
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beGeneraterDataList_Destruct(igSmartPointer<igObject> *self, long long delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beGeneraterInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterInfo_Register);
}

static igMetaObjectCallback g_beGeneraterInfo_callbackList[] = { beGeneraterDataList_EnsureRegistered, 0 };

CallbackArray *beGeneraterInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beGeneraterInfo_GetMetaObjectFunction,
        "beGeneraterInfo",
        0x20, /* instance size */
        beGeneraterInfo_GetVTable,
        beGeneraterInfo_InitFields,
        0, /* extra callback item */
        g_beGeneraterInfo_callbackList /* callback list */
    );
}

void beGeneraterInfo_GetMetaObjectFunction(void)
{
    beGeneraterInfo_GetMetaObject();
}

static FieldFactory g_beGeneraterInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beGeneraterInfo_fieldTable[] = {
    "_dataList",
};
static igMetaField **g_beGeneraterInfo_fieldHandles[] = {
    &g_beGeneraterInfo_dataListMetaField,
};
static int g_beGeneraterInfo_fieldOffsets[] = {
    28,
};

void beGeneraterInfo_InitFields(void) {
    int base;
    void *dataList;
    igMetaObject *meta;

    meta = g_beGeneraterInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beGeneraterInfo_ctorTable, 1);
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beGeneraterDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)dataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beGeneraterInfo_fieldTable, g_beGeneraterInfo_fieldHandles, g_beGeneraterInfo_fieldOffsets, base);
}

