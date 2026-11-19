igMetaObject *g_igMetaEnum_metaObject;
igMetaField *g_igMetaEnum_nameMetaField;
igMetaField *g_igMetaEnum_namesMetaField;
igMetaField *g_igMetaEnum_valuesMetaField;

void * igMetaEnum_CreateInstance(int allocator) {
    igMetaEnum_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igMetaEnum_metaObject, (igMemoryPoolView *)allocator));
}

igMetaObject *igMetaEnum_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaEnum_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMetaEnum_EnsureRegistered();
    return g_igMetaEnum_metaObject;
}

int igMetaEnum_GetVTable(void) {
    igMetaEnum metaEnum;
    int t;
    igObject *a;
    int *a1;
    int v0;
    char *c;
    void **q4c;
    void **q48;
    void **q50;
    igObject_InitHeader((igObject *)&metaEnum);
    q48 = (void **)&metaEnum._name;
    q4c = (void **)&metaEnum._names;
    q50 = (void **)&metaEnum._values;
    metaEnum._vtable = (int)&g_igMetaEnum_vtable[0];
    *q48 = 0;
    *q4c = 0;
    *q50 = 0;
    t = *(int *)((char *)&metaEnum + g_objectSystem->vtableProbeOffset);
    metaEnum._vtable = (int)&g_igMetaEnum_vtable[0];
    if (q50 != 0) {
        a = (igObject *)*q50;
        if (a != 0) {
            a->_refCount = a->_refCount - 1;
            if ((a->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q4c != 0) {
        a = (igObject *)*q4c;
        if (a != 0) {
            a->_refCount = a->_refCount - 1;
            if ((a->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q48 != 0) {
        c = (char *)*q48;
        if (c != 0) {
            a1 = (int *)(c - 8);
            v0 = *(int *)(c - 4) - 1;
            *(int *)(c - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*a1), (StringTokenHeader *)a1);
            }
        }
    }
    return t;
}

void igMetaEnum_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMetaEnum_Register);
}

static igMetaObjectCallback g_igMetaEnum_callbackList[] = { igStringRefList_EnsureRegistered, igIntList_EnsureRegistered, 0 };

CallbackArray *igMetaEnum_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igMetaEnum_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igMetaEnum_GetMetaObjectFunction,
        "igMetaEnum",
        0x14,
        igMetaEnum_GetVTable,
        igMetaEnum_InitFields,
        0,
        g_igMetaEnum_callbackList
    );
}

void igMetaEnum_GetMetaObjectFunction(void) {
    igMetaEnum_GetMetaObject();
}

static FieldFactory g_igMetaEnum_ctorTable[] = {
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igMetaEnum_fieldTable[] = {
    "_name",
    "_names",
    "_values",
};
static igMetaField **g_igMetaEnum_fieldDescriptors[] = {
    &g_igMetaEnum_nameMetaField,
    &g_igMetaEnum_namesMetaField,
    &g_igMetaEnum_valuesMetaField,
};
static int g_igMetaEnum_fieldOffsets[] = {
    8,
    12,
    16,
};

void igMetaEnum_InitFields(void) {
    int base;
    void *values;
    void *names;
    void *meta;

    meta = (void *)g_igMetaEnum_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMetaEnum_ctorTable, 3);
    names = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)names)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    values = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)values)->_metaObject = igIntList_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igMetaEnum_fieldTable, g_igMetaEnum_fieldDescriptors, g_igMetaEnum_fieldOffsets, base);
}

