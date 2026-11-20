igMetaObject *g_igUnsignedShortArrayMetaField_metaObject;
igUnsignedShortArrayMetaField *g_igUnsignedShortArrayMetaField_descriptor;
igMetaField *g_igUnsignedShortArrayMetaField_numMetaField;

igMetaField *igUnsignedShortArrayMetaField_Create(igMemoryPoolView *pool) {
    igUnsignedShortArrayMetaField_EnsureRegistered();
    return (igMetaField *)igMetaObject_CreateInstance(g_igUnsignedShortArrayMetaField_metaObject, pool);
}

igMetaObject *igUnsignedShortArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedShortArrayMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedShortArrayMetaField_EnsureRegistered();
    return g_igUnsignedShortArrayMetaField_metaObject;
}

int igUnsignedShortArrayMetaField_GetVTable(void) {
    igUnsignedShortArrayMetaField o;
    int r;
    int *header;
    int count;
    void *name;

    igUnsignedShortMetaField_Init((int **)&o);
    o._vtable = (int)&g_igUnsignedShortArrayMetaField_vtable[0];
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        name = (char *)o._fieldName;
        if (name != 0) {
            header = (int *)((char *)name - 8);
            count = *(int *)((char *)(name) - 4) - 1;
            *(int *)((char *)(name) - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return r;
}

void igUnsignedShortArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igUnsignedShortArrayMetaField_Register);
}

static igMetaObjectCallback g_igUnsignedShortArrayMetaField_callbackList[] = { igUnsignedShortArrayMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igUnsignedShortArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igUnsignedShortArrayMetaField_metaObject,
        igUnsignedShortMetaField_Register,
        igUnsignedShortMetaField_GetPublishedMetaObject,
        igUnsignedShortArrayMetaField_GetMetaObjectFunction,
        "igUnsignedShortArrayMetaField",
        0x38,
        igUnsignedShortArrayMetaField_GetVTable,
        igUnsignedShortArrayMetaField_InitFields,
        0,
        g_igUnsignedShortArrayMetaField_callbackList
    );
}

void igUnsignedShortArrayMetaField_GetMetaObjectFunction(void) {
    igUnsignedShortArrayMetaField_GetMetaObject();
}

igMetaObject *igUnsignedShortMetaField_GetPublishedMetaObject(void) {
    return g_igUnsignedShortMetaField_metaObject;
}

static FieldFactory g_igUnsignedShortArrayMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igUnsignedShortArrayMetaField_fieldTable[] = {
    "_num",
};
static igMetaField **g_igUnsignedShortArrayMetaField_fieldDescriptors[] = {
    &g_igUnsignedShortArrayMetaField_numMetaField,
};
static int g_igUnsignedShortArrayMetaField_fieldOffsets[] = {
    52,
};

void igUnsignedShortArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igUnsignedShortArrayMetaField_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igUnsignedShortArrayMetaField_ctorTable, 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, base), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igUnsignedShortArrayMetaField_fieldTable, g_igUnsignedShortArrayMetaField_fieldDescriptors, g_igUnsignedShortArrayMetaField_fieldOffsets, base);
}


void igUnsignedShortArrayMetaField_CreateDefaultDescriptor(void) {
    igUnsignedShortArrayMetaField *descriptor;
    igUnsignedShortArrayMetaField *p;

    if (g_igUnsignedShortArrayMetaField_descriptor == 0) {
        g_igUnsignedShortArrayMetaField_descriptor = ((igUnsignedShortArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedShortArrayMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        descriptor = g_igUnsignedShortArrayMetaField_descriptor;
        if (descriptor != 0) {
            MetaRefList_AppendRetained(Gap::Core::igMetaField::getMetaFieldTypes(), (igObject *)descriptor);
            p = g_igUnsignedShortArrayMetaField_descriptor;
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long)(long long)p->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(p);
            }
            g_igUnsignedShortArrayMetaField_descriptor->_internalIndex = Gap::Core::igMetaField::getMetaFieldTypes()->_count - 1;
            ((Gap::Core::igMetaField *)g_igUnsignedShortArrayMetaField_descriptor)->validate();
        }
    }
}

