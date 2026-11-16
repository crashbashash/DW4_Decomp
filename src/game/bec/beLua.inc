igMetaObject *g_beLua_metaObject;
igMetaField *g_beLua_systemMetaField;
igMetaField *g_beLua_infoListMetaField;
igMetaField *g_beLua_luaStateMetaField;
igMetaField *g_beLua_luaGlueMetaField;

beLua *beLua_CreateInstance(int allocator) {
    beLua_EnsureRegistered();
    return (beLua *)igMetaObject_CreateInstance(*(int *)0x589208, allocator);
}

igMetaObject *beLua_GetOrCreateMetaObject(void) {
    if (g_beLua_metaObject == 0) {
        g_beLua_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beLua_metaObject;
}

void *beLua_GetMetaObject(void) {
    igMetaObject *g = g_beLua_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beLua_EnsureRegistered();
    }
    return g_beLua_metaObject;
}

int beLua_GetVTable(void) {
    beLua obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beLua_vtable[0];
    obj._infoList = 0;
    obj._luaState = 0;
    obj._luaGlue = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beLua_vtable[0];
    igSmartPointer_igLuaGlue_Destruct((igSmartPointer<igObject> *)(&obj._luaGlue), -1);
    igSmartPointer_beLuaState_Destruct((igSmartPointer<igObject> *)(&obj._luaState), (short)(-1));
    igSmartPointer_beBaseInfoList_Destruct((igSmartPointer<igObject> *)(&obj._infoList), -1);
    igInfoManager_Destroy(&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beLuaState_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_igLuaGlue_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

void beLua_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLua_Register);
}

static igMetaObjectCallback g_beLua_callbackList[] = { beSystem_EnsureRegistered, beBaseInfoList_EnsureRegistered, beLuaState_EnsureRegistered, igLuaGlue_EnsureRegistered, 0 };

void *beLua_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLua_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beLua_GetMetaObjectFunction,
        "beLua",
        0x20, /* instance size */
        beLua_GetVTable,
        beLua_InitFields,
        0, /* extra callback item */
        g_beLua_callbackList /* callback list */
    );
}

void beLua_GetMetaObjectFunction(void)
{
    beLua_GetMetaObject();
}

static FieldFactory g_beLua_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beLua_fieldTable[] = {
    "_system",
    "_infoList",
    "_luaState",
    "_luaGlue",
};
static igMetaField **g_beLua_fieldHandles[] = {
    &g_beLua_systemMetaField,
    &g_beLua_infoListMetaField,
    &g_beLua_luaStateMetaField,
    &g_beLua_luaGlueMetaField,
};
static int g_beLua_fieldOffsets[] = {
    16,
    20,
    24,
    28,
};

void beLua_InitFields(void) {
    int base;
    void *system;
    void *infoList;
    void *luaState;
    void *luaGlue;
    void *meta;

    meta = (void *)g_beLua_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beLua_ctorTable, 4);
    system = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)system)->_metaObject = (int)beSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)system)->_refCounted = 0;
    infoList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)infoList)->_metaObject = (int)beBaseInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)infoList)->_construct = 1;
    luaState = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)luaState)->_metaObject = (int)beLuaState_GetOrCreateMetaObject();
    luaGlue = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)luaGlue)->_metaObject = igLuaGlue_GetOrCreateMetaObject();
    ((igRefMetaField *)luaGlue)->_construct = 1;
    igMetaObject_NameFields(meta, g_beLua_fieldTable, g_beLua_fieldHandles, g_beLua_fieldOffsets, base);
}

