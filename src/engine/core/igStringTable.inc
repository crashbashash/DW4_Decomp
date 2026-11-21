igMetaObject *g_igStringTable_metaObject;
igMetaField *g_igStringTable_capacityMetaField;
igMetaField *g_igStringTable_hashCapacityMetaField;
igMetaField *g_igStringTable_stringsMetaField;
igMetaField *g_igStringTable_hashIndexMetaField;

void *igStringTable_Create(int pool) {
    igStringTable_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance(g_igStringTable_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igStringTable_GetOrCreateMetaObject(void) {
    if (g_igStringTable_metaObject == 0) {
        g_igStringTable_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igStringTable_metaObject;
}

igMetaObject *igStringTable_GetMetaObject(void)
{
    igMetaObject *g = g_igStringTable_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igStringTable_EnsureRegistered();
    return g_igStringTable_metaObject;
}

int igStringTable_GetVTable(void) {
    igStringTable table;
    int r;
    int *strings;
    int *hashIndex;

    igObject_InitHeader((igObject *)&table);
    table._vtable = (int)&g_igStringTable_vtable[0];
    strings = &table._strings;
    *strings = 0;
    hashIndex = &table._hashIndex;
    *hashIndex = 0;
    r = *(int *)((char *)&table + g_objectSystem->vtableProbeOffset);
    table._vtable = (int)&g_igStringTable_vtable[0];
    ReleaseObjectField(hashIndex);
    ReleaseObjectField(strings);
    return r;
}

igObject **igSmartPointer_igCharListNoClean_Destruct(igObject **self, short flags) {
    igObject *object;

    if (self != 0) {
        object = *self;
        if (object != 0) {
            object->_refCount = object->_refCount - 1;
            if ((object->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
        if (flags > 0) {
            operator delete(self);
        }
    }
    return self;
}

void igStringTable_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igStringTable_Register);
}

static igMetaObjectCallback g_igStringTable_callbackList[] = { Gap::Core::igCharListNoClean::arkRegister, Gap::Core::igIntListNoClean::arkRegister, 0 };

CallbackArray *igStringTable_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igStringTable_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igStringTable_GetMetaObjectFunction,
        "igStringTable",
        0x18,
        igStringTable_GetVTable,
        igStringTable_InitFields,
        0,
        g_igStringTable_callbackList
    );
}

void igStringTable_GetMetaObjectFunction(void) {
    igStringTable_GetMetaObject();
}

static FieldFactory g_igStringTable_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igStringTable_fieldTable[] = {
    "_capacity",
    "_hashCapacity",
    "_strings",
    "_hashIndex",
};
static igMetaField **g_igStringTable_fieldDescriptors[] = {
    &g_igStringTable_capacityMetaField,
    &g_igStringTable_hashCapacityMetaField,
    &g_igStringTable_stringsMetaField,
    &g_igStringTable_hashIndexMetaField,
};
static int g_igStringTable_fieldOffsets[] = {
    8,
    12,
    16,
    20,
};

void igStringTable_InitFields(void) {
    int base;
    void *field2;
    void *field;
    void *meta;

    meta = (void *)g_igStringTable_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igStringTable_ctorTable, 4);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)Gap::Core::igCharListNoClean::getClassTypeLazy();
    ((igRefMetaField *)field)->_construct = 1;
    field2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)Gap::Core::igIntListNoClean::getClassTypeLazy();
    igMetaObject_NameFields((igMetaObject *)meta, g_igStringTable_fieldTable, g_igStringTable_fieldDescriptors, g_igStringTable_fieldOffsets, base);
}

