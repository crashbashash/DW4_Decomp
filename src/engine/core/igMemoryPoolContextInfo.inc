igMetaObject *g_igMemoryPoolContextInfo_metaObject;
igMetaField *g_igMemoryPoolContextInfo_memoryPoolInfosMetaField;
int g_MemoryContext_metaObject;

void * igMemoryPoolContextInfo_Create(int allocator) {
    igMemoryPoolContextInfo_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igMemoryPoolContextInfo_metaObject, (igMemoryPoolView *)allocator));
}

igMetaObject *igMemoryPoolContextInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPoolContextInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryPoolContextInfo_EnsureRegistered();
    return g_igMemoryPoolContextInfo_metaObject;
}

int igMemoryPoolContextInfo_GetVTable(void) {
    igMemoryPoolContextInfo info;
    char *o;
    igObject *r;
    int *a1;
    int v0;
    int t;
    igObject_InitHeader((igObject *)&info);
    info._name = 0;
    *(int **)&info._vtable = &g_igMemoryPoolContextInfo_vtable[0];
    info._memoryPoolInfos = 0;
    t = *(int *)((char *)&info + g_objectSystem->vtableProbeOffset);
    info._vtable = (int)&g_igMemoryPoolContextInfo_vtable[0];
    if (&info._memoryPoolInfos != 0) {
        r = (igObject *)info._memoryPoolInfos;
        if (r != 0) {
            r->_refCount = r->_refCount - 1;
            if ((r->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(r);
            }
        }
    }
    info._vtable = (int)&g_igNamedObject_vtable[0];
    if (&info._name != 0) {
        o = (char *)info._name;
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

void igMemoryPoolContextInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMemoryPoolContextInfo_Register);
}

static igMetaObjectCallback g_igMemoryPoolContextInfo_callbackList[] = { igMemoryPoolInfoList_EnsureRegistered, 0 };

CallbackArray *igMemoryPoolContextInfo_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igMemoryPoolContextInfo_metaObject,
        igInfo_Register,
        (igMetaObjectGetFunction)igInfo_GetPublishedMetaObject,
        igMemoryPoolContextInfo_GetMetaObjectFunction,
        "igMemoryPoolContextInfo",
        0x18,
        igMemoryPoolContextInfo_GetVTable,
        igMemoryPoolContextInfo_InitFields,
        0,
        g_igMemoryPoolContextInfo_callbackList
    );
}

void igMemoryPoolContextInfo_GetMetaObjectFunction(void) {
    igMemoryPoolContextInfo_GetMetaObject();
}

static FieldFactory g_igMemoryPoolContextInfo_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igMemoryPoolContextInfo_fieldTable[] = {
    "_memoryPoolInfos",
};
static igMetaField **g_igMemoryPoolContextInfo_fieldDescriptors[] = {
    &g_igMemoryPoolContextInfo_memoryPoolInfosMetaField,
};
static int g_igMemoryPoolContextInfo_fieldOffsets[] = {
    20,
};

void igMemoryPoolContextInfo_InitFields(void) {
    int base;
    void *memoryPoolInfos;
    void *meta;

    meta = (void *)g_igMemoryPoolContextInfo_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMemoryPoolContextInfo_ctorTable, 1);
    memoryPoolInfos = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)memoryPoolInfos)->_metaObject = (int)igMemoryPoolInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)memoryPoolInfos)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igMemoryPoolContextInfo_fieldTable, g_igMemoryPoolContextInfo_fieldDescriptors, g_igMemoryPoolContextInfo_fieldOffsets, base);
}

