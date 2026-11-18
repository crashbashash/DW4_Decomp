igMetaObject *g_beNDMWTitle2_metaObject;
igMetaField *g_beNDMWTitle2_padManagerMetaField;
igMetaField *g_beNDMWTitle2_mcUtilCtrlMetaField;
igMetaField *g_beNDMWTitle2_isMakeFileOKMetaField;
igMetaField *g_beNDMWTitle2_selectMetaField;

beNDMWTitle2 *beNDMWTitle2_CreateInstance(int allocator) {
    beNDMWTitle2_EnsureRegistered();
    return (beNDMWTitle2 *)igMetaObject_CreateInstance(g_beNDMWTitle2_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWTitle2_GetOrCreateMetaObject(void) {
    if (g_beNDMWTitle2_metaObject == 0) {
        g_beNDMWTitle2_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWTitle2_metaObject;
}

void *beNDMWTitle2_GetMetaObject(void) {
    unsigned char b;
    if (g_beNDMWTitle2_metaObject != 0) {
        b = (g_beNDMWTitle2_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beNDMWTitle2_EnsureRegistered();
done:
    return g_beNDMWTitle2_metaObject;
}

int beNDMWTitle2_GetVTable(void) {
    beNDMWTitle2 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWTitle2_vtable[0];
    obj._padManager = 0;
    obj._mcUtilCtrl = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWTitle2_vtable[0];
    igSmartPointer_beNDMWMcUtilCtrl_Destruct((igSmartPointer<igObject> *)&obj._mcUtilCtrl, -1);
    igSmartPointer_bePadManager_Destruct((igSmartPointer<igObject> *)&obj._padManager, -1);
    beBaseInfoManager_Destroy((beBaseInfoManager *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMcUtilCtrl_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
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

void beNDMWTitle2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWTitle2_Register);
}

static igMetaObjectCallback g_beNDMWTitle2_callbackList[] = { bePadManager_EnsureRegistered, beNDMWMcUtilCtrl_EnsureRegistered, 0 };

CallbackArray *beNDMWTitle2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWTitle2_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWTitle2_GetMetaObjectFunction,
        "beNDMWTitle2",
        0x34, /* instance size */
        beNDMWTitle2_GetVTable,
        beNDMWTitle2_InitFields,
        0, /* extra callback item */
        g_beNDMWTitle2_callbackList /* callback list */
    );
}

void beNDMWTitle2_GetMetaObjectFunction(void)
{
    beNDMWTitle2_GetMetaObject();
}

static FieldFactory g_beNDMWTitle2_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWTitle2_fieldTable[] = {
    "_padManager",
    "_mcUtilCtrl",
    "_isMakeFileOK",
    "_select",
};
static igMetaField **g_beNDMWTitle2_fieldHandles[] = {
    &g_beNDMWTitle2_padManagerMetaField,
    &g_beNDMWTitle2_mcUtilCtrlMetaField,
    &g_beNDMWTitle2_isMakeFileOKMetaField,
    &g_beNDMWTitle2_selectMetaField,
};
static int g_beNDMWTitle2_fieldOffsets[] = {
    32,
    36,
    40,
    44,
};

void beNDMWTitle2_InitFields(void) {
    int base;
    void *padManager;
    void *mcUtilCtrl;
    igMetaObject *meta;

    meta = g_beNDMWTitle2_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWTitle2_ctorTable, 4);
    padManager = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)padManager)->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    mcUtilCtrl = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)mcUtilCtrl)->_metaObject = (int)beNDMWMcUtilCtrl_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWTitle2_fieldTable, g_beNDMWTitle2_fieldHandles, g_beNDMWTitle2_fieldOffsets, base);
}

