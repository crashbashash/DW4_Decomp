igMetaObject *g_beNDMWAfsSetup_metaObject;
igMetaField *g_beNDMWAfsSetup_infoListMetaField;
igMetaField *g_beNDMWAfsSetup_customMenuMetaField;
igMetaField *g_beNDMWAfsSetup_subMenuMetaField;
igMetaField *g_beNDMWAfsSetup_subMenuHolderMetaField;

beNDMWAfsSetup *beNDMWAfsSetup_CreateInstance(int allocator) {
    beNDMWAfsSetup_EnsureRegistered();
    return (beNDMWAfsSetup *)igMetaObject_CreateInstance(g_beNDMWAfsSetup_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWAfsSetup_GetOrCreateMetaObject(void) {
    if (g_beNDMWAfsSetup_metaObject == 0) {
        g_beNDMWAfsSetup_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWAfsSetup_metaObject;
}

void *beNDMWAfsSetup_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWAfsSetup_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWAfsSetup_EnsureRegistered();
    }
    return g_beNDMWAfsSetup_metaObject;
}

int beNDMWAfsSetup_GetVTable(void) {
    beNDMWAfsSetup obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    *(int **)&obj._vtable = &g_beNDMWAfsSetup_vtable[0];
    obj._infoList = 0;
    obj._customMenu = 0;
    obj._subMenu = 0;
    obj._subMenuHolder = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWAfsSetup_vtable[0];
    igSmartPointer_igGuiComponent_Destruct((igSmartPointer<igObject> *)&obj._subMenuHolder, -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&obj._subMenu, -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&obj._customMenu, -1);
    igSmartPointer_igInfoList_Destruct((igSmartPointer<igObject> *)&obj._infoList, -1);
    igInfoManager_Destroy((igInfoManager *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_igGuiComponent_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

void beNDMWAfsSetup_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetup_Register);
}

static igMetaObjectCallback g_beNDMWAfsSetup_callbackList[] = { igInfoList_EnsureRegistered, igBoxComponent_RunStaticInit, igGuiComponent_EnsureRegistered, 0 };

CallbackArray *beNDMWAfsSetup_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWAfsSetup_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beNDMWAfsSetup_GetMetaObject,
        "beNDMWAfsSetup",
        0x20, /* instance size */
        beNDMWAfsSetup_GetVTable,
        beNDMWAfsSetup_InitFields,
        0, /* extra callback item */
        g_beNDMWAfsSetup_callbackList /* callback list */
    );
}

void beNDMWAfsSetup_GetMetaObject(void)
{
    beNDMWAfsSetup_ResolveMetaObject();
}

static FieldFactory g_beNDMWAfsSetup_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWAfsSetup_fieldTable[] = {
    "_infoList",
    "_customMenu",
    "_subMenu",
    "_subMenuHolder",
};
static igMetaField **g_beNDMWAfsSetup_fieldHandles[] = {
    &g_beNDMWAfsSetup_infoListMetaField,
    &g_beNDMWAfsSetup_customMenuMetaField,
    &g_beNDMWAfsSetup_subMenuMetaField,
    &g_beNDMWAfsSetup_subMenuHolderMetaField,
};
static int g_beNDMWAfsSetup_fieldOffsets[] = {
    16,
    20,
    24,
    28,
};

void beNDMWAfsSetup_InitFields(void) {
    int base;
    void *subMenuHolder;
    void *subMenu;
    void *customMenu;
    void *infoList;
    igMetaObject *meta;

    meta = g_beNDMWAfsSetup_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWAfsSetup_ctorTable, 4);
    infoList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)infoList)->_metaObject = (int)igInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)infoList)->_construct = 1;
    customMenu = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)customMenu)->_metaObject = (int)igBoxComponent_GetOrCreateMetaObject();
    subMenu = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)subMenu)->_metaObject = (int)igBoxComponent_GetOrCreateMetaObject();
    subMenuHolder = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)subMenuHolder)->_metaObject = (int)igGuiComponent_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWAfsSetup_fieldTable, g_beNDMWAfsSetup_fieldHandles, g_beNDMWAfsSetup_fieldOffsets, base);
}

