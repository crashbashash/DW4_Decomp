igMetaObject *g_bePadManager_metaObject;
igMetaField *g_bePadManager_systemMetaField;
igMetaField *g_bePadManager_padListMetaField;
igMetaField *g_bePadManager_kbReceiverMetaField;
igMetaField *g_bePadManager_is1pAllDeviceMetaField;
igMetaField *g_bePadManager_isPadDisableMetaField;

bePadManager *bePadManager_CreateInstance(int allocator) {
    bePadManager_EnsureRegistered();
    return (bePadManager *)igMetaObject_CreateInstance(g_bePadManager_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *bePadManager_GetOrCreateMetaObject(void) {
    if (g_bePadManager_metaObject == 0) {
        g_bePadManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_bePadManager_metaObject;
}

void *bePadManager_GetMetaObject(void) {
    igMetaObject *g = g_bePadManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        bePadManager_EnsureRegistered();
    }
    return g_bePadManager_metaObject;
}

int bePadManager_GetVTable(void) {
    bePadManager obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_bePadManager_vtable[0];
    obj._system = 0;
    obj._padList = 0;
    obj._kbReceiver = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_bePadManager_vtable[0];
    igSmartPointer_beKeyboardReceiver_Destruct((igSmartPointer<igObject> *)&obj._kbReceiver, (short)(-1));
    igSmartPointer_bePadDataList_Destruct((igSmartPointer<igObject> *)&obj._padList, -1);
    igSmartPointer_beSystem_Destruct((igSmartPointer<igObject> *)((igSmartPointer<igObject> *)((igSmartPointer<igObject> *)&obj._system)), (short)(-1));
    igInfoManager_Destroy((igInfoManager *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_bePadDataList_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beKeyboardReceiver_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

void bePadManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(bePadManager_Register);
}

static igMetaObjectCallback g_bePadManager_callbackList[] = { beSystem_EnsureRegistered, bePadDataList_EnsureRegistered, beKeyboardReceiver_EnsureRegistered, 0 };

CallbackArray *bePadManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_bePadManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        bePadManager_GetMetaObjectFunction,
        "bePadManager",
        0x20, /* instance size */
        bePadManager_GetVTable,
        bePadManager_InitFields,
        0, /* extra callback item */
        g_bePadManager_callbackList /* callback list */
    );
}

void bePadManager_GetMetaObjectFunction(void)
{
    bePadManager_GetMetaObject();
}

static FieldFactory g_bePadManager_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_bePadManager_fieldTable[] = {
    "_system",
    "_padList",
    "_kbReceiver",
    "_is1pAllDevice",
    "_isPadDisable",
};
static igMetaField **g_bePadManager_fieldHandles[] = {
    &g_bePadManager_systemMetaField,
    &g_bePadManager_padListMetaField,
    &g_bePadManager_kbReceiverMetaField,
    &g_bePadManager_is1pAllDeviceMetaField,
    &g_bePadManager_isPadDisableMetaField,
};
static int g_bePadManager_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    29,
};

void bePadManager_InitFields(void) {
    int base;
    void *system;
    void *padList;
    void *kbReceiver;
    igMetaObject *meta;

    meta = g_bePadManager_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_bePadManager_ctorTable, 5);
    system = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)system)->_metaObject = (int)beSystem_GetOrCreateMetaObject();
    padList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)padList)->_metaObject = (int)bePadDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)padList)->_construct = 1;
    kbReceiver = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)kbReceiver)->_metaObject = (int)beKeyboardReceiver_GetOrCreateMetaObject();
    ((igRefMetaField *)kbReceiver)->_construct = 1;
    igMetaObject_NameFields(meta, g_bePadManager_fieldTable, g_bePadManager_fieldHandles, g_bePadManager_fieldOffsets, base);
}

