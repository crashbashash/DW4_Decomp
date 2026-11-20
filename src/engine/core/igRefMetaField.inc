igMetaObject *igRefMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igRefMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRefMetaField_EnsureRegistered();
    return g_igRefMetaField_metaObject;
}

void igRefMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRefMetaField_Register);
}

static igMetaObjectCallback g_igRefMetaField_callbackList[] = { igRefMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igRefMetaField_Register(void) {
    return igMetaObject_RegisterClass(
        1,
        &g_igRefMetaField_metaObject,
        Gap::Core::igMetaField::arkRegisterInternal,
        igMetaField_GetPublishedMetaObject,
        igRefMetaField_GetMetaObjectFunction,
        "igRefMetaField",
        0x38,
        0,
        igRefMetaField_InitFields,
        0,
        g_igRefMetaField_callbackList
    );
}

void igRefMetaField_GetMetaObjectFunction(void) {
    igRefMetaField_GetMetaObject();
}

static FieldFactory g_igRefMetaField_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igRefMetaField_fieldTable[] = {
    "_construct",
    "_destruct",
};
static igMetaField **g_igRefMetaField_fieldDescriptors[] = {
    &g_igRefMetaField_constructMetaField,
    &g_igRefMetaField_destructMetaField,
};
static int g_igRefMetaField_fieldOffsets[] = {
    52,
    53,
};

void igRefMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igRefMetaField_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igRefMetaField_ctorTable, 2);
    igMetaObject_NameFields((igMetaObject *)meta, g_igRefMetaField_fieldTable, g_igRefMetaField_fieldDescriptors, g_igRefMetaField_fieldOffsets, base);
}


void igRefMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;
    igRefMetaField *o;
    int t;

    if (g_igRefMetaField_descriptor == 0) {
        g_igRefMetaField_descriptor = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igRefMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        descriptor = (void *)(g_igRefMetaField_descriptor);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(Gap::Core::igMetaField::getMetaFieldTypes(), (igObject *)descriptor);
            o = (igRefMetaField *)g_igRefMetaField_descriptor;
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            t = ((__internalObjectList *)Gap::Core::igMetaField::getMetaFieldTypes())->_count - 1;
            ((igRefMetaField *)g_igRefMetaField_descriptor)->_internalIndex = (short) t;
            ((Gap::Core::igMetaField *)g_igRefMetaField_descriptor)->validate();
        }
    }
}

