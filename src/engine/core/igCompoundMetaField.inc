igMetaObject *g_igCompoundMetaField_metaObject;
void *g_igCompoundMetaField_descriptor;
igMetaField *g_igCompoundMetaField_fieldListMetaField;

igMetaObject *igCompoundMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCompoundMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCompoundMetaField_EnsureRegistered();
    return g_igCompoundMetaField_metaObject;
}

void igCompoundMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCompoundMetaField_Register);
}

static igMetaObjectCallback g_igCompoundMetaField_callbackList[] = { igMetaFieldList_EnsureRegistered, igCompoundMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igCompoundMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1,
        &g_igCompoundMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        igCompoundMetaField_GetMetaObjectFunction,
        "igCompoundMetaField",
        0x38,
        0,
        igCompoundMetaField_InitFields,
        0,
        g_igCompoundMetaField_callbackList
    );
}

void igCompoundMetaField_GetMetaObjectFunction(void) {
    igCompoundMetaField_GetMetaObject();
}

static FieldFactory g_igCompoundMetaField_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igCompoundMetaField_fieldTable[] = {
    "_fieldList",
};
static igMetaField **g_igCompoundMetaField_fieldDescriptors[] = {
    &g_igCompoundMetaField_fieldListMetaField,
};
static int g_igCompoundMetaField_fieldOffsets[] = {
    52,
};

void igCompoundMetaField_InitFields(void) {
    int first;
    void *field;
    void *meta;

    meta = (void *)g_igCompoundMetaField_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igCompoundMetaField_ctorTable, 1);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMetaFieldList_GetOrCreateMetaObject();
    ((igRefMetaField *)field)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igCompoundMetaField_fieldTable, g_igCompoundMetaField_fieldDescriptors, g_igCompoundMetaField_fieldOffsets, first);
}


void igCompoundMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;
    igCompoundMetaField *o;
    int t;

    if (g_igCompoundMetaField_descriptor == 0) {
        g_igCompoundMetaField_descriptor = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igCompoundMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        descriptor = (void *)(g_igCompoundMetaField_descriptor);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            o = (igCompoundMetaField *)g_igCompoundMetaField_descriptor;
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            t = igMetaField_GetMetaFieldList()->_count - 1;
            ((igCompoundMetaField *)g_igCompoundMetaField_descriptor)->_internalIndex = (short) t;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igCompoundMetaField_descriptor);
        }
    }
}

int igCompoundMetaField_GetSize(void) {
    return 1;
}

void igCompoundMetaField_InitDefaults(igCompoundMetaField *self)
{
    igCompoundMetaField_AddSubFields(self->_fieldList);
}

void igCompoundMetaField_AddSubFields(int value)
{
}

