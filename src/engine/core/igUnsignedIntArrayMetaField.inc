igMetaObject *g_igUnsignedIntArrayMetaField_metaObject;
igUnsignedIntArrayMetaField *g_igUnsignedIntArrayMetaField_descriptor;
igMetaField *g_igUnsignedIntArrayMetaField_numMetaField;

igMetaField *igUnsignedIntArrayMetaField_Create(igMemoryPoolView *pool) {
    igUnsignedIntArrayMetaField_EnsureRegistered();
    return (igMetaField *)igMetaObject_CreateInstance(g_igUnsignedIntArrayMetaField_metaObject, pool);
}

igMetaObject *igUnsignedIntArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntArrayMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedIntArrayMetaField_EnsureRegistered();
    return g_igUnsignedIntArrayMetaField_metaObject;
}

int igUnsignedIntArrayMetaField_GetVTable(void) {
    igUnsignedIntArrayMetaField field;
    int result;
    char *fieldName;
    int *name;
    int *header;
    int refs;

    igUnsignedIntMetaField_Init((igMetaField *)&field);
    field._vtable = (int)&g_igUnsignedIntArrayMetaField_vtable[0];
    result = *(int *)((char *)&field + g_objectSystem->vtableProbeOffset);
    field._vtable = (int)&g_igMetaField_vtable[0];
    fieldName = (char *)&field._fieldName;
    if (fieldName != 0) {
        name = *(int **)fieldName;
        if (name != 0) {
            header = name - 2;
            refs = name[-1] - 1;
            name[-1] = refs;
            if (refs == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return result;
}

void igUnsignedIntArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igUnsignedIntArrayMetaField_Register);
}

static igMetaObjectCallback g_igUnsignedIntArrayMetaField_callbackList[] = { igUnsignedIntArrayMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igUnsignedIntArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igUnsignedIntArrayMetaField_metaObject,
        igUnsignedIntMetaField_Register,
        igUnsignedIntMetaField_GetPublishedMetaObject,
        igUnsignedIntArrayMetaField_GetMetaObjectFunction,
        "igUnsignedIntArrayMetaField",
        0x38,
        igUnsignedIntArrayMetaField_GetVTable,
        igUnsignedIntArrayMetaField_InitFields,
        0,
        g_igUnsignedIntArrayMetaField_callbackList
    );
}

void igUnsignedIntArrayMetaField_GetMetaObjectFunction(void) {
    igUnsignedIntArrayMetaField_GetMetaObject();
}

igMetaObject *igUnsignedIntMetaField_GetPublishedMetaObject(void) {
    return g_igUnsignedIntMetaField_metaObject;
}

static FieldFactory g_igUnsignedIntArrayMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igUnsignedIntArrayMetaField_fieldTable[] = {
    "_num",
};
static igMetaField **g_igUnsignedIntArrayMetaField_fieldDescriptors[] = {
    &g_igUnsignedIntArrayMetaField_numMetaField,
};
static int g_igUnsignedIntArrayMetaField_fieldOffsets[] = {
    52,
};

void igUnsignedIntArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igUnsignedIntArrayMetaField_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igUnsignedIntArrayMetaField_ctorTable, 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, base), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igUnsignedIntArrayMetaField_fieldTable, g_igUnsignedIntArrayMetaField_fieldDescriptors, g_igUnsignedIntArrayMetaField_fieldOffsets, base);
}


void igUnsignedIntArrayMetaField_CreateDefaultDescriptor(void) {
    igUnsignedIntArrayMetaField *descriptor;
    igUnsignedIntArrayMetaField *p;

    if (g_igUnsignedIntArrayMetaField_descriptor == 0) {
        g_igUnsignedIntArrayMetaField_descriptor = ((igUnsignedIntArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedIntArrayMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        descriptor = g_igUnsignedIntArrayMetaField_descriptor;
        if (descriptor != 0) {
            MetaRefList_AppendRetained(Gap::Core::igMetaField::getMetaFieldTypes(), (igObject *)descriptor);
            p = g_igUnsignedIntArrayMetaField_descriptor;
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            ((igMetaField *)g_igUnsignedIntArrayMetaField_descriptor)->_internalIndex = (short) (Gap::Core::igMetaField::getMetaFieldTypes()->_count - 1);
            ((Gap::Core::igMetaField *)g_igUnsignedIntArrayMetaField_descriptor)->validate();
        }
    }
}

