igMetaObject *g_beShadow01_metaObject;
igMetaField *g_beShadow01_svInfoListMetaField;
igMetaField *g_beShadow01_savePosMetaField;

void beShadow01_CreateInstance(int allocator) {
    beShadow01_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x587F10, allocator);
}

igMetaObject *beShadow01_GetOrCreateMetaObject(void) {
    if (g_beShadow01_metaObject == 0) {
        g_beShadow01_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[5] = 0;
    o.vt = g_beShadow01_vtable;
    o.f[7] = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beShadow01_vtable;
    FUN_00344f90((igSmartPointer<igObject> *)(&o.f[7]), (short)(-1));
    FUN_0033f5e0((O_33f5e0 *)&o, (short)0);
    return r;
}

igSmartPointer<igObject> *FUN_00344f90(igSmartPointer<igObject> *self, short delete_storage) {
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

void beShadow01_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beShadow01_Register);
}

static igMetaObjectCallback g_beShadow01_callbackList[] = { beShadow01InfoList_EnsureRegistered, 0 };

void *beShadow01_Register(void) {
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
    FUN_00187890,
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
    void *meta;

    meta = (void *)g_beShadow01_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beShadow01_ctorTable, 2);
    svInfoList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)svInfoList)->_metaObject = (int)beShadow01InfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)svInfoList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beShadow01_fieldTable, g_beShadow01_fieldHandles, g_beShadow01_fieldOffsets, base);
}

