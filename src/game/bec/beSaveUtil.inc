igMetaObject *g_beSaveUtil_metaObject;
igMetaField *g_beSaveUtil_apiMetaField;
igMetaField *g_beSaveUtil_connectCheckMetaField;

void beSaveUtil_CreateInstance(int allocator) {
    beSaveUtil_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588020, allocator);
}

igMetaObject *beSaveUtil_GetOrCreateMetaObject(void) {
    if (g_beSaveUtil_metaObject == 0) {
        g_beSaveUtil_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSaveUtil_metaObject;
}

void *beSaveUtil_GetMetaObject(void) {
    igMetaObject *g = g_beSaveUtil_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSaveUtil_EnsureRegistered();
    }
    return g_beSaveUtil_metaObject;
}

int beSaveUtil_GetVTable(void) {
    struct Obj_346d60 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &g_beSaveUtil_vtable[0];
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beSaveUtil_vtable[0];
    FUN_00346e70((igSmartPointer<igObject> *)&obj.w9, (short)(-1));
    FUN_00346df0((igSmartPointer<igObject> *)&obj.w8, -1);
    FUN_0033f5e0((O_33f5e0 *)&obj, (short)0);
    return t;
}

igSmartPointer<igObject> *FUN_00346df0(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *FUN_00346e70(igSmartPointer<igObject> *self, short delete_storage) {
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

void beSaveUtil_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSaveUtil_Register);
}

static igMetaObjectCallback g_beSaveUtil_callbackList[] = { beSaveApi_EnsureRegistered, beSvConnectCheck_EnsureRegistered, 0 };

void *beSaveUtil_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSaveUtil_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beSaveUtil_GetMetaObjectFunction,
        "beSaveUtil",
        0x28, /* instance size */
        beSaveUtil_GetVTable,
        beSaveUtil_InitFields,
        0, /* extra callback item */
        g_beSaveUtil_callbackList /* callback list */
    );
}

void beSaveUtil_GetMetaObjectFunction(void)
{
    beSaveUtil_GetMetaObject();
}

static FieldFactory g_beSaveUtil_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSaveUtil_fieldTable[] = {
    "_api",
    "_connectCheck",
};
static igMetaField **g_beSaveUtil_fieldHandles[] = {
    &g_beSaveUtil_apiMetaField,
    &g_beSaveUtil_connectCheckMetaField,
};
static int g_beSaveUtil_fieldOffsets[] = {
    32,
    36,
};

void beSaveUtil_InitFields(void) {
    int base;
    void *api;
    void *connectCheck;
    void *meta;

    meta = (void *)g_beSaveUtil_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSaveUtil_ctorTable, 2);
    api = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)api)->_metaObject = (int)beSaveApi_GetOrCreateMetaObject();
    connectCheck = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)connectCheck)->_metaObject = (int)beSvConnectCheck_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beSaveUtil_fieldTable, g_beSaveUtil_fieldHandles, g_beSaveUtil_fieldOffsets, base);
}

