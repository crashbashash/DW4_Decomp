igMetaObject *g_igCallStackTable_metaObject;
igMetaField *g_igCallStackTable_capacityMetaField;
igMetaField *g_igCallStackTable_hashCapacityMetaField;
igMetaField *g_igCallStackTable_callStacksMetaField;
igMetaField *g_igCallStackTable_hashIndexMetaField;

igMetaObject *igCallStackTable_GetOrCreateMetaObject(void) {
    if (g_igCallStackTable_metaObject == 0) {
        g_igCallStackTable_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCallStackTable_metaObject;
}

igMetaObject *igCallStackTable_GetMetaObject(void)
{
    igMetaObject *g = g_igCallStackTable_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCallStackTable_EnsureRegistered();
    return g_igCallStackTable_metaObject;
}

int igCallStackTable_GetVTable(void) {
    igCallStackTable table;
    int vtable;
    igObject *q0;
    igObject *q1;

    igObject_InitHeader((igObject *)&table);
    table._vtable = (int)&g_igCallStackTable_vtable[0];
    q1 = (igObject *)&table._callStacks;
    *(int *)q1 = 0;
    q0 = (igObject *)&table._hashIndex;
    *(int *)q0 = 0;
    vtable = *(int *)((char *)&table + g_objectSystem->vtableProbeOffset);
    table._vtable = (int)&g_igCallStackTable_vtable[0];
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        if (q0 != 0) {
            q0->_refCount = (int)((int) (q0->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(igObject **)q1;
        if (q1 != 0) {
            q1->_refCount = (int)((int) (q1->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return vtable;
}

void igCallStackTable_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCallStackTable_Register);
}

static igMetaObjectCallback g_igCallStackTable_callbackList[] = { igUnsignedIntListNoClean_EnsureRegistered, igIntListNoClean_EnsureRegistered, 0 };

CallbackArray *igCallStackTable_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igCallStackTable_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igCallStackTable_GetMetaObjectFunction,
        "igCallStackTable",
        0x18,
        igCallStackTable_GetVTable,
        igCallStackTable_InitFields,
        0,
        g_igCallStackTable_callbackList
    );
}

void igCallStackTable_GetMetaObjectFunction(void) {
    igCallStackTable_GetMetaObject();
}

static FieldFactory g_igCallStackTable_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igCallStackTable_fieldTable[] = {
    "_capacity",
    "_hashCapacity",
    "_callStacks",
    "_hashIndex",
};
static igMetaField **g_igCallStackTable_fieldDescriptors[] = {
    &g_igCallStackTable_capacityMetaField,
    &g_igCallStackTable_hashCapacityMetaField,
    &g_igCallStackTable_callStacksMetaField,
    &g_igCallStackTable_hashIndexMetaField,
};
static int g_igCallStackTable_fieldOffsets[] = {
    8,
    12,
    16,
    20,
};

void igCallStackTable_InitFields(void) {
    int base;
    void *hashIndex;
    void *callStacks;
    void *meta;

    meta = (void *)g_igCallStackTable_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igCallStackTable_ctorTable, 4);
    callStacks = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)callStacks)->_metaObject = (int)igUnsignedIntListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)callStacks)->_construct = 1;
    hashIndex = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)hashIndex)->_metaObject = (int)igIntListNoClean_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igCallStackTable_fieldTable, g_igCallStackTable_fieldDescriptors, g_igCallStackTable_fieldOffsets, base);
}

