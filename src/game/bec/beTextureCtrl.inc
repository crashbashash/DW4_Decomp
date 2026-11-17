igMetaObject *g_beTextureCtrl_metaObject;
igMetaField *g_beTextureCtrl_isFirstTimeMetaField;
igMetaField *g_beTextureCtrl_workMetaField;

beTextureCtrl *beTextureCtrl_CreateInstance(int allocator) {
    beTextureCtrl_EnsureRegistered();
    return (beTextureCtrl *)igMetaObject_CreateInstance(g_beTextureCtrl_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beTextureCtrl_GetOrCreateMetaObject(void) {
    if (g_beTextureCtrl_metaObject == 0) {
        g_beTextureCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beTextureCtrl_metaObject;
}

void *beTextureCtrl_GetMetaObject(void) {
    igMetaObject *g = g_beTextureCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beTextureCtrl_EnsureRegistered();
    }
    return g_beTextureCtrl_metaObject;
}

int beTextureCtrl_GetVTable(void) {
    beTextureCtrl obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    obj._vtable = (int)&g_beTextureCtrl_vtable[0];
    obj._work = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beTextureCtrl_vtable[0];
    igSmartPointer_beTextureCtrlWork_Destruct((igSmartPointer<igObject> *)&obj._work, (short)(-1));
    beBaseInfoManager_Destroy((beBaseInfoManager *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beTextureCtrlWork_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

void beTextureCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTextureCtrl_Register);
}

static igMetaObjectCallback g_beTextureCtrl_callbackList[] = { beTextureCtrlWork_EnsureRegistered, 0 };

CallbackArray *beTextureCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTextureCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beTextureCtrl_GetMetaObjectFunction,
        "beTextureCtrl",
        0x28, /* instance size */
        beTextureCtrl_GetVTable,
        beTextureCtrl_InitFields,
        0, /* extra callback item */
        g_beTextureCtrl_callbackList /* callback list */
    );
}

void beTextureCtrl_GetMetaObjectFunction(void)
{
    beTextureCtrl_GetMetaObject();
}

static FieldFactory g_beTextureCtrl_ctorTable[] = {
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beTextureCtrl_fieldTable[] = {
    "_isFirstTime",
    "_work",
};
static igMetaField **g_beTextureCtrl_fieldHandles[] = {
    &g_beTextureCtrl_isFirstTimeMetaField,
    &g_beTextureCtrl_workMetaField,
};
static int g_beTextureCtrl_fieldOffsets[] = {
    32,
    36,
};

void beTextureCtrl_InitFields(void) {
    int base;
    void *work;
    igMetaObject *meta;

    meta = g_beTextureCtrl_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beTextureCtrl_ctorTable, 2);
    work = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)work)->_metaObject = (int)beTextureCtrlWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beTextureCtrl_fieldTable, g_beTextureCtrl_fieldHandles, g_beTextureCtrl_fieldOffsets, base);
}

