igMetaObject *g_igIntArrayMetaField_metaObject;
igIntArrayMetaField *g_igIntArrayMetaField_descriptor;
igMetaField *g_igIntArrayMetaField_numMetaField;

igMetaField *igIntArrayMetaField_Create(igMemoryPoolView *pool) {
    igIntArrayMetaField_EnsureRegistered();
    return (igMetaField *)igMetaObject_CreateInstance(g_igIntArrayMetaField_metaObject, pool);
}

igMetaObject *igIntArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igIntArrayMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igIntArrayMetaField_EnsureRegistered();
    return g_igIntArrayMetaField_metaObject;
}

int igIntArrayMetaField_GetVTable(void) {
    igIntArrayMetaField obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igIntMetaField_Init((igMetaField *)&obj);
    obj._vtable = (int)&g_igIntArrayMetaField_vtable[0];
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_igMetaField_vtable[0];
    if (&obj._fieldName != 0) {
        o = (char *)obj._fieldName;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*a1), (StringTokenHeader *)a1);
            }
        }
    }
    return t;
}

void igIntArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igIntArrayMetaField_Register);
}

static igMetaObjectCallback g_igIntArrayMetaField_callbackList[] = { igIntArrayMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igIntArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igIntArrayMetaField_metaObject,
        igIntMetaField_Register,
        igIntMetaField_GetPublishedMetaObject,
        igIntArrayMetaField_GetMetaObjectFunction,
        "igIntArrayMetaField",
        0x38,
        igIntArrayMetaField_GetVTable,
        igIntArrayMetaField_InitFields,
        0,
        g_igIntArrayMetaField_callbackList
    );
}

void igIntArrayMetaField_GetMetaObjectFunction(void) {
    igIntArrayMetaField_GetMetaObject();
}

igMetaObject *igIntMetaField_GetPublishedMetaObject(void) {
    return g_igIntMetaField_metaObject;
}

static FieldFactory g_igIntArrayMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igIntArrayMetaField_fieldTable[] = {
    "_num",
};
static igMetaField **g_igIntArrayMetaField_fieldDescriptors[] = {
    &g_igIntArrayMetaField_numMetaField,
};
static int g_igIntArrayMetaField_fieldOffsets[] = {
    52,
};

void igIntArrayMetaField_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igIntArrayMetaField_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igIntArrayMetaField_ctorTable, 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, first), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igIntArrayMetaField_fieldTable, g_igIntArrayMetaField_fieldDescriptors, g_igIntArrayMetaField_fieldOffsets, first);
}


void igIntArrayMetaField_CreateDefaultDescriptor(void) {
    igIntArrayMetaField *descriptor;
    igIntArrayMetaField *held;

    if (g_igIntArrayMetaField_descriptor == 0) {
        g_igIntArrayMetaField_descriptor = (igIntArrayMetaField *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igIntArrayMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        descriptor = g_igIntArrayMetaField_descriptor;
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            held = g_igIntArrayMetaField_descriptor;
            held->_refCount = held->_refCount - 1;
            if ((held->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(held);
            }
            g_igIntArrayMetaField_descriptor->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igIntArrayMetaField_descriptor);
        }
    }
}

