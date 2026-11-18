igMetaObject *g_beShadow01_metaObject;
igMetaField *g_beShadow01_svInfoListMetaField;
igMetaField *g_beShadow01_savePosMetaField;

beShadow01 *beShadow01_CreateInstance(int allocator) {
    beShadow01_EnsureRegistered();
    return (beShadow01 *)igMetaObject_CreateInstance(g_beShadow01_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beShadow01_GetOrCreateMetaObject(void) {
    if (g_beShadow01_metaObject == 0) {
        g_beShadow01_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beShadow01_metaObject;
}

void *beShadow01_GetMetaObject(void) {
    igMetaObject *g = g_beShadow01_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beShadow01_EnsureRegistered();
    }
    return g_beShadow01_metaObject;
}

int beShadow01_GetVTable(void) {
    beShadow01 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    obj._vtable = (int)&g_beShadow01_vtable[0];
    obj._svInfoList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beShadow01_vtable[0];
    igSmartPointer_beShadow01InfoList_Destruct((igSmartPointer<igObject> *)(&obj._svInfoList), (short)(-1));
    beBaseInfoManager_Destroy((beBaseInfoManager *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beShadow01InfoList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

void beShadow01_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beShadow01_Register);
}

static igMetaObjectCallback g_beShadow01_callbackList[] = { beShadow01InfoList_EnsureRegistered, 0 };

CallbackArray *beShadow01_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beShadow01_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beShadow01_GetMetaObjectFunction,
        "beShadow01",
        0x30, /* instance size */
        beShadow01_GetVTable,
        beShadow01_InitFields,
        0, /* extra callback item */
        g_beShadow01_callbackList /* callback list */
    );
}

void beShadow01_GetMetaObjectFunction(void)
{
    beShadow01_GetMetaObject();
}

static FieldFactory g_beShadow01_ctorTable[] = {
    igObjectRefMetaField_Create,
    igVec3fMetaField_CreateInstance,
};
static const char *g_beShadow01_fieldTable[] = {
    "_svInfoList",
    "_savePos",
};
static igMetaField **g_beShadow01_fieldHandles[] = {
    &g_beShadow01_svInfoListMetaField,
    &g_beShadow01_savePosMetaField,
};
static int g_beShadow01_fieldOffsets[] = {
    32,
    36,
};

void beShadow01_InitFields(void) {
    int base;
    void *svInfoList;
    igMetaObject *meta;

    meta = g_beShadow01_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beShadow01_ctorTable, 2);
    svInfoList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)svInfoList)->_metaObject = (int)beShadow01InfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)svInfoList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beShadow01_fieldTable, g_beShadow01_fieldHandles, g_beShadow01_fieldOffsets, base);
}

