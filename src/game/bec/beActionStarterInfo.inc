igMetaObject *g_beActionStarterInfo_metaObject;
igMetaField *g_beActionStarterInfo_modelListMetaField;

void *beActionStarterInfo_GetMetaObject(void) {
    igMetaObject *g = g_beActionStarterInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beActionStarterInfo_EnsureRegistered();
    }
    return g_beActionStarterInfo_metaObject;
}

int beActionStarterInfo_GetVTable(void) {
    beActionStarterInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beActionStarterInfo_vtable[0];
    obj._modelList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beActionStarterInfo_vtable[0];
    igSmartPointer_beAsTargetModelDataList_Destruct((igSmartPointer<igObject> *)&obj._modelList, (short)(-1));
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beAsTargetModelDataList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

void beActionStarterInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beActionStarterInfo_Register);
}

static igMetaObjectCallback g_beActionStarterInfo_callbackList[] = { beAsTargetModelDataList_EnsureRegistered, 0 };

CallbackArray *beActionStarterInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beActionStarterInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beActionStarterInfo_GetMetaObjectFunction,
        "beActionStarterInfo",
        0x20, /* instance size */
        beActionStarterInfo_GetVTable,
        beActionStarterInfo_InitFields,
        0, /* extra callback item */
        g_beActionStarterInfo_callbackList /* callback list */
    );
}

void beActionStarterInfo_GetMetaObjectFunction(void)
{
    beActionStarterInfo_GetMetaObject();
}

static FieldFactory g_beActionStarterInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beActionStarterInfo_fieldTable[] = {
    "_modelList",
};
static igMetaField **g_beActionStarterInfo_fieldHandles[] = {
    &g_beActionStarterInfo_modelListMetaField,
};
static int g_beActionStarterInfo_fieldOffsets[] = {
    28,
};

void beActionStarterInfo_InitFields(void) {
    int base;
    void *modelList;
    igMetaObject *meta;

    meta = g_beActionStarterInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beActionStarterInfo_ctorTable, 1);
    modelList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)modelList)->_metaObject = (int)beAsTargetModelDataList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beActionStarterInfo_fieldTable, g_beActionStarterInfo_fieldHandles, g_beActionStarterInfo_fieldOffsets, base);
}

