igMetaObject *g_beDemoManager_metaObject;
igMetaField *g_beDemoManager_messengerMetaField;
igMetaField *g_beDemoManager_luaMetaField;
igMetaField *g_beDemoManager_buildDataMetaField;
igMetaField *g_beDemoManager_activeDataListMetaField;
igMetaField *g_beDemoManager_turningOKMetaField;
igMetaField *g_beDemoManager_disableRemoveAllMetaField;
igMetaField *g_beDemoManager_calledRemoveAllMetaField;

beDemoManager *beDemoManager_CreateInstance(int allocator) {
    beDemoManager_EnsureRegistered();
    return (beDemoManager *)igMetaObject_CreateInstance(g_beDemoManager_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beDemoManager_GetOrCreateMetaObject(void) {
    if (g_beDemoManager_metaObject == 0) {
        g_beDemoManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beDemoManager_metaObject;
}

void *beDemoManager_GetMetaObject(void) {
    igMetaObject *g = g_beDemoManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDemoManager_EnsureRegistered();
    }
    return g_beDemoManager_metaObject;
}

int beDemoManager_GetVTable(void) {
    beDemoManager obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beDemoManager_vtable[0];
    obj._name = 0;
    obj._buildData = 0;
    obj._activeDataList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beDemoManager_vtable[0];
    igSmartPointer_beDemoManagerWorkList_Destruct((igSmartPointer<igObject> *)&obj._activeDataList, (short)(-1));
    igSmartPointer_beDemoManagerWork_Destruct((igSmartPointer<igObject> *)&obj._buildData, -1);
    igInfoManager_Destroy((igInfoManager *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beDemoManagerWork_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beDemoManagerWorkList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

void beDemoManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDemoManager_Register);
}

static igMetaObjectCallback g_beDemoManager_callbackList[] = { beMessenger_EnsureRegistered, beLua_EnsureRegistered, beDemoManagerWork_EnsureRegistered, beDemoManagerWorkList_EnsureRegistered, 0 };

CallbackArray *beDemoManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDemoManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beDemoManager_GetMetaObjectFunction,
        "beDemoManager",
        0x24, /* instance size */
        beDemoManager_GetVTable,
        beDemoManager_InitFields,
        0, /* extra callback item */
        g_beDemoManager_callbackList /* callback list */
    );
}

void beDemoManager_GetMetaObjectFunction(void)
{
    beDemoManager_GetMetaObject();
}

static FieldFactory g_beDemoManager_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beDemoManager_fieldTable[] = {
    "_messenger",
    "_lua",
    "_buildData",
    "_activeDataList",
    "_turningOK",
    "_disableRemoveAll",
    "_calledRemoveAll",
};
static igMetaField **g_beDemoManager_fieldHandles[] = {
    &g_beDemoManager_messengerMetaField,
    &g_beDemoManager_luaMetaField,
    &g_beDemoManager_buildDataMetaField,
    &g_beDemoManager_activeDataListMetaField,
    &g_beDemoManager_turningOKMetaField,
    &g_beDemoManager_disableRemoveAllMetaField,
    &g_beDemoManager_calledRemoveAllMetaField,
};
static int g_beDemoManager_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    33,
    34,
};

void beDemoManager_InitFields(void) {
    int base;
    void *messenger;
    void *lua;
    void *buildData;
    void *activeDataList;
    igMetaObject *meta;

    meta = g_beDemoManager_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDemoManager_ctorTable, 7);
    messenger = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)messenger)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    lua = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)lua)->_metaObject = (int)beLua_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)lua)->_refCounted = 0;
    buildData = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)buildData)->_metaObject = (int)beDemoManagerWork_GetOrCreateMetaObject();
    activeDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)activeDataList)->_metaObject = (int)beDemoManagerWorkList_GetOrCreateMetaObject();
    ((igRefMetaField *)activeDataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beDemoManager_fieldTable, g_beDemoManager_fieldHandles, g_beDemoManager_fieldOffsets, base);
}

