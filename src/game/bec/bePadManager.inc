igMetaObject *g_bePadManager_metaObject;
igMetaField *g_bePadManager_systemMetaField;
igMetaField *g_bePadManager_padListMetaField;
igMetaField *g_bePadManager_kbReceiverMetaField;
igMetaField *g_bePadManager_is1pAllDeviceMetaField;
igMetaField *g_bePadManager_isPadDisableMetaField;

void bePadManager_CreateInstance(int allocator) {
    bePadManager_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588518, allocator);
}

igMetaObject *bePadManager_GetOrCreateMetaObject(void) {
    if (g_bePadManager_metaObject == 0) {
        g_bePadManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    struct Obj_34c980 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &g_bePadManager_vtable[0];
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_bePadManager_vtable[0];
    FUN_0034cab0((igSmartPointer<igObject> *)&obj.w6, (short)(-1));
    FUN_0034ca30((igSmartPointer<igObject> *)&obj.w5, -1);
    FUN_0033dc20((igSmartPointer<igObject> *)((igSmartPointer<igObject> *)((igSmartPointer<igObject> *)&obj.w4)), (short)(-1));
    FUN_00231030(&obj, 0);
    return t;
}

igSmartPointer<igObject> *FUN_0034ca30(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *FUN_0034cab0(igSmartPointer<igObject> *self, short delete_storage) {
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

void bePadManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(bePadManager_Register);
}

static igMetaObjectCallback g_bePadManager_callbackList[] = { beSystem_EnsureRegistered, bePadDataList_EnsureRegistered, beKeyboardReceiver_EnsureRegistered, 0 };

void *bePadManager_Register(void) {
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
    void *meta;

    meta = (void *)g_bePadManager_metaObject;
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

