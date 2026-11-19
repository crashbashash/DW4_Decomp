igMetaObject *g_igInterpretedShaderData_metaObject;
igMetaField *g_igInterpretedShaderData_factoryMetaField;
igMetaField *g_igInterpretedShaderData_objectMappingsMetaField;

igMetaObject *igInterpretedShaderData_GetOrCreateMetaObject(void) {
    if (g_igInterpretedShaderData_metaObject == 0) {
        g_igInterpretedShaderData_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igInterpretedShaderData_metaObject;
}

igMetaObject *igInterpretedShaderData_GetMetaObject(void)
{
    igMetaObject *g = g_igInterpretedShaderData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igInterpretedShaderData_EnsureRegistered();
    return g_igInterpretedShaderData_metaObject;
}

int igInterpretedShaderData_GetVTable(void) {
    struct Obj_19eaa0 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.vt = &g_igInterpretedShaderData_vtable[0];
    obj.w6 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igInterpretedShaderData_vtable[0];
    FUN_0014dd40((igSmartPointer<igObject> *)&obj.w7, -1);
    igSmartPointer_igShaderFactory_Destruct((ObjectRefWord *)&obj.w6, -1);
    FUN_00194790((int * *)&obj, 0);
    return t;
}

ObjectRefWord *igSmartPointer_igShaderFactory_Destruct(ObjectRefWord *self,int delete_storage) {
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

void igInterpretedShaderData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igInterpretedShaderData_Register);
}

static igMetaObjectCallback g_igInterpretedShaderData_callbackList[] = { igShaderFactory_EnsureRegistered, igObjectStringMap_EnsureRegistered, 0 };

CallbackArray *igInterpretedShaderData_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igInterpretedShaderData_metaObject,
        igTransientShaderData_Register,
        igTransientShaderData_GetPublishedMetaObject,
        igInterpretedShaderData_GetMetaObjectFunction,
        "igInterpretedShaderData",
        0x20, /* instance size */
        igInterpretedShaderData_GetVTable,
        &igInterpretedShaderData_InitFields,
        0, /* extra callback item */
        g_igInterpretedShaderData_callbackList /* callback list */
    );
}

void igInterpretedShaderData_GetMetaObjectFunction(void) {
    igInterpretedShaderData_GetMetaObject();
}

int FUN_0019ec60(void) {
    return ((int)g_igTransientShaderData_metaObject);
}

static FieldFactory g_igInterpretedShaderData_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igInterpretedShaderData_fieldTable[] = {
    "_factory",
    "_objectMappings",
};
static igMetaField **g_igInterpretedShaderData_fieldHandles[] = {
    &g_igInterpretedShaderData_factoryMetaField,
    &g_igInterpretedShaderData_objectMappingsMetaField,
};
static int g_igInterpretedShaderData_fieldOffsets[] = {
    24,
    28,
};

void igInterpretedShaderData_InitFields(void) {
    int base;
    void *objectMappingsField;
    void *factoryField;
    void *meta;

    meta = (void *)g_igInterpretedShaderData_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igInterpretedShaderData_ctorTable, 2);
    factoryField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)factoryField)->_metaObject = (int)igShaderFactory_GetOrCreateMetaObject();
    objectMappingsField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)objectMappingsField)->_metaObject = (int)igObjectStringMap_GetOrCreateMetaObject();
    ((igRefMetaField *)objectMappingsField)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igInterpretedShaderData_fieldTable, g_igInterpretedShaderData_fieldHandles, g_igInterpretedShaderData_fieldOffsets, base);
}

