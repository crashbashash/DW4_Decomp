igMetaObject *g_beSound_metaObject;
igMetaField *g_beSound_criMetaField;
igMetaField *g_beSound_currentBGMMetaField;
igMetaField *g_beSound_playSEsMetaField;

beSound *beSound_CreateInstance(int allocator) {
    beSound_EnsureRegistered();
    return (beSound *)igMetaObject_CreateInstance(g_beSound_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beSound_GetOrCreateMetaObject(void) {
    if (g_beSound_metaObject == 0) {
        g_beSound_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beSound_metaObject;
}

igMetaObject *beSound_GetMetaObject(void) {
    igMetaObject *g = g_beSound_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beSound_EnsureRegistered();
done:
    return g_beSound_metaObject;
}

int beSound_GetVTable(void) {
    beSound obj;
    int *criSlot;
    int vtable;
    int *currentBGMSlot;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    obj._vtable = (int)&g_beSound_vtable[0];
    criSlot = &obj._cri;
    *criSlot = 0;
    currentBGMSlot = &obj._currentBGM;
    *currentBGMSlot = 0;
    obj._playSEs = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beSound_vtable[0];
    igSmartPointer_bePlaySEList_Destruct((igSmartPointer<igObject> *)(&obj._playSEs), (short)(-1));
    igStringRef_Destruct(currentBGMSlot, -1);
    igSmartPointer_beCri_Destruct((igSmartPointer<igObject> *)((igSmartPointer<igObject> *)((igSmartPointer<igObject> *)criSlot)), (short)(-1));
    beBaseInfoManager_Destroy((beBaseInfoManager *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_bePlaySEList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

void beSound_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSound_Register);
}

static igMetaObjectCallback g_beSound_callbackList[] = { beCri_EnsureRegistered, bePlaySEList_EnsureRegistered, 0 };

CallbackArray *beSound_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSound_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beSound_GetMetaObjectFunction,
        "beSound",
        0x2c, /* instance size */
        beSound_GetVTable,
        beSound_InitFields,
        0, /* extra callback item */
        g_beSound_callbackList /* callback list */
    );
}

void beSound_GetMetaObjectFunction(void)
{
    beSound_GetMetaObject();
}

static FieldFactory g_beSound_ctorTable[] = {
    igObjectRefMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSound_fieldTable[] = {
    "_cri",
    "_currentBGM",
    "_playSEs",
};
static igMetaField **g_beSound_fieldHandles[] = {
    &g_beSound_criMetaField,
    &g_beSound_currentBGMMetaField,
    &g_beSound_playSEsMetaField,
};
static int g_beSound_fieldOffsets[] = {
    32,
    36,
    40,
};

void beSound_InitFields(void) {
    int base;
    void *cri;
    void *playSEs;
    igMetaObject *meta;

    meta = g_beSound_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSound_ctorTable, 3);
    cri = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)cri)->_metaObject = (int)beCri_GetOrCreateMetaObject();
    playSEs = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)playSEs)->_metaObject = (int)bePlaySEList_GetOrCreateMetaObject();
    ((igRefMetaField *)playSEs)->_construct = 1;
    igMetaObject_NameFields(meta, g_beSound_fieldTable, g_beSound_fieldHandles, g_beSound_fieldOffsets, base);
}

