igMetaObject *g_igMetaObject_metaObject;
igMetaField *g_igMetaObject_idMetaField;
igMetaField *g_igMetaObject_indexMetaField;
igMetaField *g_igMetaObject_majorVersionMetaField;
igMetaField *g_igMetaObject_minorVersionMetaField;
igMetaField *g_igMetaObject_volatileMetaField;
igMetaField *g_igMetaObject_persistentMetaField;
igMetaField *g_igMetaObject_abstractStateMetaField;
igMetaField *g_igMetaObjectNameField;
igMetaField *g_igMetaObject_runTimeSizeMetaField;
igMetaField *g_igMetaObject_validityMetaField;
igMetaField *g_igMetaObject_metaFieldsMetaField;
igMetaField *g_igMetaObject_instanceCountMetaField;
igMetaField *g_igMetaObject_instancesMetaField;
igMetaField *g_igMetaObject_childrenMetaField;
igMetaField *g_igMetaObject_parentMetaField;
igMetaField *g_igMetaObject_abstractProxyMetaField;
igMetaField *g_igMetaObject_writeProxyMetaField;
igMetaField *g_igMetaObject_templateObjectMetaField;
igMetaField *g_igMetaObject_sizeofSizeMetaField;
igMetaField *g_igMetaObject_setupFunctionMetaField;
igMetaField *g_igMetaObject_cleanupFunctionMetaField;
igMetaField *g_igMetaObject_getMetaObjectFunctionMetaField;
igMetaField *g_igMetaObject_requiredAlignmentMetaField;
igMetaField *g_igMetaObject_vTablePointerMetaField;
igMetaField *g_igMetaObject_poolNameMetaField;

igMetaObject *igMetaObject_Create(igMemoryPoolView *allocator) {
    igMetaObject *metaObject;

    if (g_objectSystem->active != 0) {
        igMetaObject_EnsureRegistered();
        metaObject = (igMetaObject *)igMetaObject_CreateInstance(g_igMetaObject_metaObject, allocator);
    } else {
        metaObject = (igMetaObject *)Gap::Core::igObject::operator new(0x64, 0, allocator);
        if (metaObject != 0) {
            metaObject = (igMetaObject *)igMetaObject_Construct(metaObject, 1);
        }
        ((igObjectDispatchView *)(metaObject))->InitDefaults();
        ((igObjectDispatchView *)(metaObject))->userConstruct((int)(0));
    }
    return metaObject;
}

void *igMetaObject_Clone(int source, int pool) {
    void *r;
    if (g_objectSystem->active != 0) {
        igMetaObject_EnsureRegistered();
        r = ((void *)igObject_CloneViaMetadata((void **)source, pool));
    } else {
        r = Gap::Core::igObject::operator new(0x64, 0);
        if (r != 0) {
            r = igMetaObject_CopyConstruct((igMetaObject *)r, (void *)source);
        }
    }
    return r;
}

igMetaObject *igMetaObject_GetOrCreateMetaObject(void) {
    if (g_igMetaObject_metaObject == 0) {
        g_igMetaObject_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMetaObject_metaObject;
}

igMetaObject *igMetaObject_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaObject_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMetaObject_EnsureRegistered();
    return g_igMetaObject_metaObject;
}

int igMetaObject_GetVTable(void) {
    igMetaObject prototype;
    int *header;
    int *nameHeader;
    int vtable;
    int refCount;
    int nameRefCount;
    void *text;
    void *nameText;

    igMetaObject_Init((igMetaObject *)&prototype);
    vtable = *(int *)((char *)&prototype + g_objectSystem->vtableProbeOffset);
    prototype._vtable = (int)&g_igMetaObject_vtable[0];
    if ((void **)&prototype._poolName != 0) {
        text = (void *)((void *)prototype._poolName);
        if (text != 0) {
            header = (int *)((char *)text - 8);
            refCount = *(int *)((char *)(text) - 4) - 1;
            *(int *)((char *)(text) - 4) = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    if ((void **)&prototype._name != 0) {
        nameText = (void *)((void *)prototype._name);
        if (nameText != 0) {
            nameHeader = (int *)((char *)nameText - 8);
            nameRefCount = *(int *)((char *)(nameText) - 4) - 1;
            *(int *)((char *)(nameText) - 4) = nameRefCount;
            if (nameRefCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*nameHeader), (StringTokenHeader *)nameHeader);
            }
        }
    }
    return vtable;
}

void igMetaObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMetaObject_Register);
}

static igMetaObjectCallback g_igMetaObject_callbackList[] = { Gap::Core::__internalObjectList::arkRegister, Gap::Core::__internalNonRefCountedObjectList::arkRegister, Gap::Core::igObject::arkRegister, 0 };

CallbackArray *igMetaObject_Register(void) {
    return igMetaObject_RegisterClass(
        0,
        &g_igMetaObject_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igMetaObject_GetMetaObjectFunction,
        "igMetaObject",
        0x64,
        igMetaObject_GetVTable,
        igMetaObject_InitFields,
        0,
        g_igMetaObject_callbackList
    );
}

void igMetaObject_GetMetaObjectFunction(void) {
    igMetaObject_GetMetaObject();
}

static FieldFactory g_igMetaObject_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igUnsignedShortMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
};
static const char *g_igMetaObject_fieldTable[] = {
    "_id",
    "_index",
    "_majorVersion",
    "_minorVersion",
    "_volatile",
    "_persistent",
    "_abstractState",
    "_name",
    "_runTimeSize",
    "_validity",
    "_metaFields",
    "_instanceCount",
    "_instances",
    "_children",
    "_parent",
    "_abstractProxy",
    "_writeProxy",
    "_templateObject",
    "_sizeofSize",
    "_setupFunction",
    "_cleanupFunction",
    "_getMetaObjectFunction",
    "_requiredAlignment",
    "_vTablePointer",
    "_poolName",
};
static igMetaField **g_igMetaObject_fieldDescriptors[] = {
    &g_igMetaObject_idMetaField,
    &g_igMetaObject_indexMetaField,
    &g_igMetaObject_majorVersionMetaField,
    &g_igMetaObject_minorVersionMetaField,
    &g_igMetaObject_volatileMetaField,
    &g_igMetaObject_persistentMetaField,
    &g_igMetaObject_abstractStateMetaField,
    &g_igMetaObjectNameField,
    &g_igMetaObject_runTimeSizeMetaField,
    &g_igMetaObject_validityMetaField,
    &g_igMetaObject_metaFieldsMetaField,
    &g_igMetaObject_instanceCountMetaField,
    &g_igMetaObject_instancesMetaField,
    &g_igMetaObject_childrenMetaField,
    &g_igMetaObject_parentMetaField,
    &g_igMetaObject_abstractProxyMetaField,
    &g_igMetaObject_writeProxyMetaField,
    &g_igMetaObject_templateObjectMetaField,
    &g_igMetaObject_sizeofSizeMetaField,
    &g_igMetaObject_setupFunctionMetaField,
    &g_igMetaObject_cleanupFunctionMetaField,
    &g_igMetaObject_getMetaObjectFunctionMetaField,
    &g_igMetaObject_requiredAlignmentMetaField,
    &g_igMetaObject_vTablePointerMetaField,
    &g_igMetaObject_poolNameMetaField,
};
static int g_igMetaObject_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    25,
    26,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
    76,
    80,
    84,
    88,
    92,
    96,
};

void igMetaObject_InitFields(void) {
    int base;
    void *field4;
    void *field5;
    void *field6;
    void *field7;
    void *field;
    void *field2;
    void *field3;
    void *field8;
    void *field9;
    void *field10;
    void *meta;

    meta = (void *)g_igMetaObject_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMetaObject_ctorTable, 0x19);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((Gap::Core::igIntMetaField *)field)->setDefault(-1);
    ((igMetaField *)field)->_persistent = 0;
    field2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((Gap::Core::igIntMetaField *)field2)->setDefault(-1);
    ((igMetaField *)field2)->_persistent = 0;
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)))->setDefault(1);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5)))->setDefault(1);
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7)))->setDefault(0);
    field3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 8)));
    ((Gap::Core::igIntMetaField *)field3)->setDefault(-1);
    ((igMetaField *)field3)->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 9))))->_persistent = 0;
    field4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xA)));
    ((igObjectRefMetaField *)field4)->_metaObject = (int)Gap::Core::__internalObjectList::getClassTypeLazy();
    ((igObjectRefMetaField *)field4)->_construct = 1;
    ((igObjectRefMetaField *)field4)->_destruct = 1;
    ((igObjectRefMetaField *)field4)->_refCounted = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xB))))->_persistent = 0;
    field5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xC)));
    ((igObjectRefMetaField *)field5)->_metaObject = (int)Gap::Core::__internalNonRefCountedObjectList::getClassTypeLazy();
    ((igObjectRefMetaField *)field5)->_destruct = 1;
    ((igObjectRefMetaField *)field5)->_refCounted = 0;
    ((igObjectRefMetaField *)field5)->_persistent = 0;
    field6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xD)));
    ((igObjectRefMetaField *)field6)->_metaObject = (int)Gap::Core::__internalNonRefCountedObjectList::getClassTypeLazy();
    ((igObjectRefMetaField *)field6)->_destruct = 1;
    ((igObjectRefMetaField *)field6)->_refCounted = 0;
    ((igObjectRefMetaField *)field6)->_persistent = 0;
    field7 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xE)));
    ((igObjectRefMetaField *)field7)->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field7)->_refCounted = 0;
    ((igObjectRefMetaField *)field7)->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xF))))->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x10))))->_persistent = 0;
    field8 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x11)));
    ((igObjectRefMetaField *)field8)->_metaObject = (int)((int) Gap::Core::igObject::getClassMeta());
    ((igObjectRefMetaField *)field8)->_destruct = 1;
    ((igObjectRefMetaField *)field8)->_refCounted = 0;
    ((igObjectRefMetaField *)field8)->_persistent = 0;
    field9 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x12)));
    ((Gap::Core::igIntMetaField *)field9)->setDefault(-1);
    ((igMetaField *)field9)->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x13))))->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x14))))->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x15))))->_persistent = 0;
    field10 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x16)));
    ((Gap::Core::igUnsignedShortMetaField *)field10)->setDefault(4);
    ((igMetaField *)field10)->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x17))))->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igMetaObject_fieldTable, g_igMetaObject_fieldDescriptors, g_igMetaObject_fieldOffsets, base);
}

igMetaObject *g_igMetaFieldInfo_metaObject;
int g_igMetaField_resetTypeMetaEnum;

void *igMetaFieldInfo_Create(int pool) {
    igMetaFieldInfo_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance(g_igMetaFieldInfo_metaObject, (igMemoryPoolView *)pool);
}

