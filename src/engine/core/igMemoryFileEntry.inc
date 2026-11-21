igMetaObject *g_igMemoryFileEntry_metaObject;
igMetaField *g_igMemoryFileEntry_bufferMetaField;
igMetaField *g_igMemoryFileEntry_sizeMetaField;

void * igMemoryFileEntry_Create(int pool) {
    igMemoryFileEntry_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igMemoryFileEntry_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igMemoryFileEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryFileEntry_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryFileEntry_EnsureRegistered();
    return g_igMemoryFileEntry_metaObject;
}

int igMemoryFileEntry_GetVTable(void) {
    igMemoryFileEntry entry;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;
    igObject_InitHeader((igObject *)&entry);
    ps = (char *)&entry._name;
    *(int *)ps = 0;
    entry._vtable = (int)&g_igNamedObject_vtable[0];
    entry._vtable = (int)&g_igMemoryFileEntry_vtable[0];
    s0 = *(int *)((char *)&entry + g_objectSystem->vtableProbeOffset);
    entry._vtable = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*a1), (StringTokenHeader *)a1);
            }
        }
    }
    return s0;
}

void igMemoryFileEntry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMemoryFileEntry_Register);
}

CallbackArray *igMemoryFileEntry_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igMemoryFileEntry_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        (igMetaObjectGetFunction)igNamedObject_GetPublishedMetaObject,
        igMemoryFileEntry_GetMetaObjectFunction,
        "igMemoryFileEntry",
        0x14,
        igMemoryFileEntry_GetVTable,
        igMemoryFileEntry_InitFields,
        0,
        0
    );
}

void igMemoryFileEntry_GetMetaObjectFunction(void) {
    igMemoryFileEntry_GetMetaObject();
}

static FieldFactory g_igMemoryFileEntry_ctorTable[] = {
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igMemoryFileEntry_fieldTable[] = {
    "_buffer",
    "_size",
};
static igMetaField **g_igMemoryFileEntry_fieldDescriptors[] = {
    &g_igMemoryFileEntry_bufferMetaField,
    &g_igMemoryFileEntry_sizeMetaField,
};
static int g_igMemoryFileEntry_fieldOffsets[] = {
    12,
    16,
};

void igMemoryFileEntry_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igMemoryFileEntry_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMemoryFileEntry_ctorTable, 2);
    igMetaObject_NameFields((igMetaObject *)meta, g_igMemoryFileEntry_fieldTable, g_igMemoryFileEntry_fieldDescriptors, g_igMemoryFileEntry_fieldOffsets, first);
}

