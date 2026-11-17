igMetaObject *g_igStackMemoryPool_metaObject;
igMetaField *g_igStackMemoryPool_poolIndexMetaField;
igMetaField *g_igStackMemoryPool_alignmentMetaField;
igMetaField *g_igStackMemoryPool_rawMemoryMetaField;
igMetaField *g_igStackMemoryPool_totalSizeMetaField;
igMetaField *g_igStackMemoryPool_elementSizeMetaField;
igMetaField *g_igStackMemoryPool_stackPtrMetaField;
igMetaField *g_igStackMemoryPool_nextIntMetaField;
igMetaField *g_igStackMemoryPool_isActiveMetaField;
igMetaField *g_igStackMemoryPool_isAlchemyMemoryMetaField;
igMetaField *g_igStackMemoryPool_eventTrackerMetaField;
int g_igMallocMemoryPool_messageLevelMetaEnum;

void *igStackMemoryPool_Create(int pool) {
    igStackMemoryPool_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance(g_igStackMemoryPool_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igStackMemoryPool_GetMetaObject(void)
{
    igMetaObject *g = g_igStackMemoryPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igStackMemoryPool_EnsureRegistered();
    return g_igStackMemoryPool_metaObject;
}

int igStackMemoryPool_GetVTable(void) {
    igStackMemoryPool pool;
    int r;
    igObject **tracker;
    igObject *object;

    igMemoryPool_Initialize((int **)&pool);
    pool._vtable = (int)&g_igStackMemoryPool_vtable[0];
    pool._eventTracker = 0;
    r = *(int *)((char *)&pool + g_objectSystem->vtableProbeOffset);
    pool._vtable = (int)&g_igStackMemoryPool_vtable[0];
    tracker = (igObject **)&pool._eventTracker;
    if (tracker) {
        object = *tracker;
        if (object) {
            --*(int *)&object->_refCount;
            if (((unsigned long long)(long long)*(int *)&object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
    }
    return r;
}

void igStackMemoryPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igStackMemoryPool_Register);
}

static igMetaObjectCallback g_igStackMemoryPool_callbackList[] = { igEventTracker_EnsureRegistered, 0 };

CallbackArray *igStackMemoryPool_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igStackMemoryPool_metaObject,
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        igStackMemoryPool_GetMetaObjectFunction,
        "igStackMemoryPool",
        0x98,
        igStackMemoryPool_GetVTable,
        igStackMemoryPool_InitFields,
        0,
        g_igStackMemoryPool_callbackList
    );
}

void igStackMemoryPool_GetMetaObjectFunction(void) {
    igStackMemoryPool_GetMetaObject();
}

static FieldFactory g_igStackMemoryPool_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igUnsignedShortMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igUnsignedLongMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igStackMemoryPool_fieldTable[] = {
    "_poolIndex",
    "_alignment",
    "_rawMemory",
    "_totalSize",
    "_elementSize",
    "_stackPtr",
    "_nextInt",
    "_isActive",
    "_isAlchemyMemory",
    "_eventTracker",
};
static igMetaField **g_igStackMemoryPool_fieldDescriptors[] = {
    &g_igStackMemoryPool_poolIndexMetaField,
    &g_igStackMemoryPool_alignmentMetaField,
    &g_igStackMemoryPool_rawMemoryMetaField,
    &g_igStackMemoryPool_totalSizeMetaField,
    &g_igStackMemoryPool_elementSizeMetaField,
    &g_igStackMemoryPool_stackPtrMetaField,
    &g_igStackMemoryPool_nextIntMetaField,
    &g_igStackMemoryPool_isActiveMetaField,
    &g_igStackMemoryPool_isAlchemyMemoryMetaField,
    &g_igStackMemoryPool_eventTrackerMetaField,
};
static int g_igStackMemoryPool_fieldOffsets[] = {
    144,
    112,
    116,
    120,
    128,
    132,
    136,
    140,
    141,
    148,
};

void igStackMemoryPool_InitFields(void) {
    int base;
    void *field;
    void *meta;

    meta = (void *)g_igStackMemoryPool_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igStackMemoryPool_ctorTable, 0xA);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, base), -1);
    igUnsignedShortMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1), 4);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 9)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igEventTracker_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igStackMemoryPool_fieldTable, g_igStackMemoryPool_fieldDescriptors, g_igStackMemoryPool_fieldOffsets, base);
}

