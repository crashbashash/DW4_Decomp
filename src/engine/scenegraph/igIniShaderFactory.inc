igMetaObject *g_igIniShaderFactory_metaObject;
igMetaField *g_igIniShaderFactory_implementationNameMetaField;
igMetaField *g_igIniShaderFactory_fileCacheMetaField;
igMetaField *g_igIniShaderFactory_implementationMetaField;
igMetaField *g_igIniShaderFactory_interfaceMetaField;
igMetaField *g_igIniShaderFactory_interfaceFileNameMetaField;
igMetaField *g_igIniShaderFactory_interfaceSectionMetaField;
igMetaField *g_igIniShaderFactory_mpMetaField;
igMetaField *g_igIniShaderFactory_dataMetaField;
igMetaField *g_igIniShaderFactory_cachedObjectsMetaField;

igMetaObject *igIniShaderFactory_GetMetaObject(void)
{
    igMetaObject *g = g_igIniShaderFactory_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igIniShaderFactory_EnsureRegistered();
    return g_igIniShaderFactory_metaObject;
}

int igIniShaderFactory_GetVTable(void) {
    struct Obj_19ed70 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.vt = &g_igIniShaderFactory_vtable[0];
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igIniShaderFactory_vtable[0];
    FUN_0014dd40((igSmartPointer<igObject> *)&obj.w14, -1);
    FUN_0014dd40((igSmartPointer<igObject> *)&obj.w13, -1);
    igSmartPointer_igInterpretedShaderData_Destruct((ObjectRefWord *)&obj.w12, -1);
    igSmartPointer_igMemoryPool_Destruct((igSmartPointer<igObject> *)&obj.w11, -1);
    igStringRef_Destruct((igStringRef *)&obj.w9, -1);
    igSmartPointer_igRegistry_Destruct((igSmartPointer<igObject> *)&obj.w8, -1);
    igSmartPointer_igRegistry_Destruct((igSmartPointer<igObject> *)&obj.w7, -1);
    igStringRef_Destruct((igStringRef *)&obj.w6, -1);
    FUN_00199330((struct T_199330 *)&obj, 0);
    return t;
}

igSmartPointer<igObject> *igSmartPointer_igRegistry_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

ObjectRefWord *igSmartPointer_igInterpretedShaderData_Destruct(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

void igIniShaderFactory_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igIniShaderFactory_Register);
}

static igMetaObjectCallback g_igIniShaderFactory_callbackList[] = { igObjectStringMap_EnsureRegistered, Gap::Core::igRegistry::arkRegister, igMemoryPool_EnsureRegistered, igInterpretedShaderData_EnsureRegistered, 0 };

CallbackArray *igIniShaderFactory_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igIniShaderFactory_metaObject,
        igShaderFactory_Register,
        igShaderFactory_GetPublishedMetaObject,
        igIniShaderFactory_GetMetaObjectFunction,
        "igIniShaderFactory",
        0x3C, /* instance size */
        igIniShaderFactory_GetVTable,
        &igIniShaderFactory_InitFields,
        0, /* extra callback item */
        g_igIniShaderFactory_callbackList /* callback list */
    );
}

void igIniShaderFactory_GetMetaObjectFunction(void) {
    igIniShaderFactory_GetMetaObject();
}

igMetaObject *igShaderFactory_GetPublishedMetaObject(void) {
    return g_igShaderFactory_metaObject;
}

static FieldFactory g_igIniShaderFactory_ctorTable[] = {
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igIniShaderFactory_fieldTable[] = {
    "_implementationName",
    "_fileCache",
    "_implementation",
    "_interface",
    "_interfaceFileName",
    "_interfaceSection",
    "_mp",
    "_data",
    "_cachedObjects",
};
static igMetaField **g_igIniShaderFactory_fieldHandles[] = {
    &g_igIniShaderFactory_implementationNameMetaField,
    &g_igIniShaderFactory_fileCacheMetaField,
    &g_igIniShaderFactory_implementationMetaField,
    &g_igIniShaderFactory_interfaceMetaField,
    &g_igIniShaderFactory_interfaceFileNameMetaField,
    &g_igIniShaderFactory_interfaceSectionMetaField,
    &g_igIniShaderFactory_mpMetaField,
    &g_igIniShaderFactory_dataMetaField,
    &g_igIniShaderFactory_cachedObjectsMetaField,
};
static int g_igIniShaderFactory_fieldOffsets[] = {
    24,
    56,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
};

void igIniShaderFactory_InitFields(void) {
    int base;
    void *fileCacheField;
    void *implementationField;
    void *interfaceField;
    void *mpField;
    void *dataField;
    void *cachedObjectsField;
    void *interfaceFileNameField;
    void *interfaceSectionField;
    void *meta;

    meta = (void *)g_igIniShaderFactory_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igIniShaderFactory_ctorTable, 9);
    fileCacheField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)fileCacheField)->_metaObject = (int)igObjectStringMap_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)fileCacheField)->_construct = 1;
    implementationField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)implementationField)->_metaObject = (int)Gap::Core::igRegistry::getClassTypeLazy();
    ((igObjectRefMetaField *)implementationField)->_persistent = 0;
    interfaceField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)interfaceField)->_metaObject = (int)Gap::Core::igRegistry::getClassTypeLazy();
    ((igObjectRefMetaField *)interfaceField)->_persistent = 0;
    interfaceFileNameField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4)));
    ((Gap::Core::igStringMetaField *)interfaceFileNameField)->setDefault(0);
    ((igStringMetaField *)interfaceFileNameField)->_persistent = 0;
    interfaceSectionField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5)));
    ((Gap::Core::igIntMetaField *)interfaceSectionField)->setDefault(-1);
    ((igIntMetaField *)interfaceSectionField)->_persistent = 0;
    mpField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6)));
    ((igObjectRefMetaField *)mpField)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)mpField)->_persistent = 0;
    dataField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7)));
    ((igObjectRefMetaField *)dataField)->_metaObject = (int)igInterpretedShaderData_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)dataField)->_persistent = 0;
    cachedObjectsField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 8)));
    ((igObjectRefMetaField *)cachedObjectsField)->_metaObject = (int)igObjectStringMap_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)cachedObjectsField)->_construct = 1;
    ((igObjectRefMetaField *)cachedObjectsField)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igIniShaderFactory_fieldTable, g_igIniShaderFactory_fieldHandles, g_igIniShaderFactory_fieldOffsets, base);
}

