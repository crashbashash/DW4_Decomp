igMetaObject *g_igCharArrayMetaField_metaObject;
igCharArrayMetaField *g_igCharArrayMetaField_descriptor;
igMetaField *g_igCharArrayMetaField_numMetaField;

igMetaField *igCharArrayMetaField_Create(igMemoryPoolView *pool) {
    igCharArrayMetaField_EnsureRegistered();
    return (igMetaField *)igMetaObject_CreateInstance(g_igCharArrayMetaField_metaObject, pool);
}

igMetaObject *igCharArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCharArrayMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCharArrayMetaField_EnsureRegistered();
    return g_igCharArrayMetaField_metaObject;
}

int igCharArrayMetaField_GetVTable(void) {
    igCharArrayMetaField o;
    int r;
    int *header;
    int count;
    void *text;

    igCharMetaField_Init((int **)&o);
    o._vtable = (int)&g_igCharArrayMetaField_vtable[0];
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        text = (char *)o._fieldName;
        if (text != 0) {
            header = (int *)((char *)text - 8);
            count = *(int *)((char *)(text) - 4) - 1;
            *(int *)((char *)(text) - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return r;
}

void igCharArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCharArrayMetaField_Register);
}

static igMetaObjectCallback g_igCharArrayMetaField_callbackList[] = { igCharArrayMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igCharArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igCharArrayMetaField_metaObject,
        igCharMetaField_Register,
        igCharMetaField_GetPublishedMetaObject,
        igCharArrayMetaField_GetMetaObjectFunction,
        "igCharArrayMetaField",
        0x38,
        igCharArrayMetaField_GetVTable,
        igCharArrayMetaField_InitFields,
        0,
        g_igCharArrayMetaField_callbackList
    );
}

void igCharArrayMetaField_GetMetaObjectFunction(void) {
    igCharArrayMetaField_GetMetaObject();
}

igMetaObject *igCharMetaField_GetPublishedMetaObject(void) {
    return g_igCharMetaField_metaObject;
}

static FieldFactory g_igCharArrayMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igCharArrayMetaField_fieldTable[] = {
    "_num",
};
static igMetaField **g_igCharArrayMetaField_fieldDescriptors[] = {
    &g_igCharArrayMetaField_numMetaField,
};
static int g_igCharArrayMetaField_fieldOffsets[] = {
    52,
};

void igCharArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igCharArrayMetaField_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igCharArrayMetaField_ctorTable, 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, base), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igCharArrayMetaField_fieldTable, g_igCharArrayMetaField_fieldDescriptors, g_igCharArrayMetaField_fieldOffsets, base);
}


void igCharArrayMetaField_CreateDefaultDescriptor(void) {
    igCharArrayMetaField *descriptor;
    igCharArrayMetaField *held;

    if (g_igCharArrayMetaField_descriptor == 0) {
        g_igCharArrayMetaField_descriptor = ((igCharArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igCharArrayMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        descriptor = g_igCharArrayMetaField_descriptor;
        if (descriptor != 0) {
            MetaRefList_AppendRetained(Gap::Core::igMetaField::getMetaFieldTypes(), (igObject *)descriptor);
            held = g_igCharArrayMetaField_descriptor;
            held->_refCount -= 1;
            if ((held->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(held);
            }
            g_igCharArrayMetaField_descriptor->_internalIndex = Gap::Core::igMetaField::getMetaFieldTypes()->_count - 1;
            ((Gap::Core::igMetaField *)g_igCharArrayMetaField_descriptor)->validate();
        }
    }
}

