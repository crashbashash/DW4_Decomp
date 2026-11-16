igMetaObject *g_igMemoryDictionary_metaObject;
igMetaField *g_igMemoryDictionary_capacityMetaField;
igMetaField *g_igMemoryDictionary_countMetaField;
igMetaField *g_igMemoryDictionary_memoryEntriesMetaField;
igMetaField *g_igMemoryDictionary_cachedIndexMetaField;

void * igMemoryDictionary_Create(int pool) {
    igMemoryDictionary_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igMemoryDictionary_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igMemoryDictionary_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryDictionary_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryDictionary_EnsureRegistered();
    return g_igMemoryDictionary_metaObject;
}

int igMemoryDictionary_GetVTable(void) {
    igMemoryDictionary dictionary;
    int **pr;
    int vtable;
    int *o;

    igObject_InitHeader((igObject *)&dictionary);
    dictionary._vtable = (int)&g_igMemoryDictionary_vtable[0];
    pr = (int **)&dictionary._memoryEntries;
    *pr = 0;
    vtable = *(int *)((char *)&dictionary + g_objectSystem->vtableProbeOffset);
    dictionary._vtable = (int)&g_igMemoryDictionary_vtable[0];
    if (pr != 0) {
        if (*pr != 0) {
            o = *pr;
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return vtable;
}

void igMemoryDictionary_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMemoryDictionary_Register);
}

static igMetaObjectCallback g_igMemoryDictionary_callbackList[] = { igUnsignedIntListNoClean_EnsureRegistered, 0 };

CallbackArray *igMemoryDictionary_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igMemoryDictionary_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igMemoryDictionary_GetMetaObjectFunction,
        "igMemoryDictionary",
        0x18,
        igMemoryDictionary_GetVTable,
        igMemoryDictionary_InitFields,
        0,
        g_igMemoryDictionary_callbackList
    );
}

void igMemoryDictionary_GetMetaObjectFunction(void) {
    igMemoryDictionary_GetMetaObject();
}

static FieldFactory g_igMemoryDictionary_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igMemoryDictionary_fieldTable[] = {
    "_capacity",
    "_count",
    "_memoryEntries",
    "_cachedIndex",
};
static igMetaField **g_igMemoryDictionary_fieldDescriptors[] = {
    &g_igMemoryDictionary_capacityMetaField,
    &g_igMemoryDictionary_countMetaField,
    &g_igMemoryDictionary_memoryEntriesMetaField,
    &g_igMemoryDictionary_cachedIndexMetaField,
};
static int g_igMemoryDictionary_fieldOffsets[] = {
    8,
    12,
    16,
    20,
};

void igMemoryDictionary_InitFields(void) {
    int base;
    void *field;
    void *meta;

    meta = (void *)g_igMemoryDictionary_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMemoryDictionary_ctorTable, 4);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igUnsignedIntListNoClean_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field)->_construct = 1;
    *(char *)((char *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3))) + 38) = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igMemoryDictionary_fieldTable, g_igMemoryDictionary_fieldDescriptors, g_igMemoryDictionary_fieldOffsets, base);
}

