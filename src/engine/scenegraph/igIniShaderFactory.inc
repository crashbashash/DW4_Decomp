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
    FUN_0014dd40(&obj.w14, -1);
    FUN_0014dd40(&obj.w13, -1);
    FUN_0019ef30((ObjectRefWord *)&obj.w12, -1);
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
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

ObjectRefWord *FUN_0019ef30(ObjectRefWord *self,int delete_storage) {
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

static igMetaObjectCallback g_igIniShaderFactory_callbackList[] = { igObjectStringMap_EnsureRegistered, igRegistry_EnsureRegistered, igMemoryPool_EnsureRegistered, FUN_0019ebc0, 0 };

CallbackArray *igIniShaderFactory_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igIniShaderFactory_metaObject,
        igShaderFactory_Register,
        igShaderFactory_GetPublishedMetaObject,
        thunk_igIniShaderFactory_GetMetaObject,
        "igIniShaderFactory",
        0x3C, /* instance size */
        igIniShaderFactory_GetVTable,
        &igIniShaderFactory_InitFields,
        0, /* extra callback item */
        g_igIniShaderFactory_callbackList /* callback list */
    );
}

void thunk_igIniShaderFactory_GetMetaObject(void) {
    igIniShaderFactory_GetMetaObject();
}

igMetaObject *FUN_0019f050(void) {
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
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_s1;

    temp_s1 = (void *)g_igIniShaderFactory_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igIniShaderFactory_ctorTable, 9);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igObjectStringMap_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igRegistry_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_2)->_persistent = 0;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igRegistry_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_3)->_persistent = 0;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4)));
    igStringMetaField_SetDefaultText((igMetaField *)temp_v0, 0);
    ((igStringMetaField *)temp_v0)->_persistent = 0;
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5)));
    igIntMetaField_SetDefault((igMetaField *)temp_v0_2, -1);
    ((igIntMetaField *)temp_v0_2)->_persistent = 0;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_4)->_persistent = 0;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 7)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_0019ea00();
    ((igObjectRefMetaField *)temp_s2_5)->_persistent = 0;
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 8)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)igObjectStringMap_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_6)->_construct = 1;
    ((igObjectRefMetaField *)temp_s2_6)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igIniShaderFactory_fieldTable, g_igIniShaderFactory_fieldHandles, g_igIniShaderFactory_fieldOffsets, temp_s0);
}

