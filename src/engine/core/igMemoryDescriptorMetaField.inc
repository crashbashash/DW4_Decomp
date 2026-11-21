igMetaObject *g_igMemoryDescriptorMetaField_metaObject;
void *g_igMemoryDescriptorMetaField_descriptor;

igMetaObject *igMemoryDescriptorMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryDescriptorMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryDescriptorMetaField_EnsureRegistered();
    return g_igMemoryDescriptorMetaField_metaObject;
}

int igMemoryDescriptorMetaField_GetVTable(void) {
    igMemoryDescriptorMetaField field;
    int result;
    igObject *fieldList;
    char *fieldName;
    int *name;
    int *header;
    int refs;

    igMetaField_Init((igMetaField *)&field);
    field._vtable = (int)&g_igCompoundMetaField_vtable[0];
    fieldList = (igObject *)&field._fieldList;
    *(int *)fieldList = 0;
    field._vtable = (int)&g_igMemoryDescriptorMetaField_vtable[0];
    result = *(int *)((char *)&field + g_objectSystem->vtableProbeOffset);
    field._vtable = (int)&g_igCompoundMetaField_vtable[0];
    if (fieldList != 0) {
        fieldList = *(igObject **)fieldList;
        if (fieldList != 0) {
            fieldList->_refCount = (int)((int) (fieldList->_refCount - 1));
            if (((unsigned long long) ((long long)(int) fieldList->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(fieldList);
            }
        }
    }
    fieldName = (char *)&field._fieldName;
    field._vtable = (int)&g_igMetaField_vtable[0];
    if (fieldName != 0) {
        name = *(int **)fieldName;
        if (name != 0) {
            header = name - 2;
            refs = name[-1] - 1;
            name[-1] = refs;
            if (refs == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return result;
}

void igMemoryDescriptorMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMemoryDescriptorMetaField_Register);
}

static igMetaObjectCallback g_igMemoryDescriptorMetaField_callbackList[] = { igMemoryDescriptorMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igMemoryDescriptorMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igMemoryDescriptorMetaField_metaObject,
        Gap::Core::igCompoundMetaField::arkRegisterInternal,
        (igMetaObjectGetFunction)igCompoundMetaField_GetPublishedMetaObject,
        igMemoryDescriptorMetaField_GetMetaObjectFunction,
        "igMemoryDescriptorMetaField",
        0x38,
        igMemoryDescriptorMetaField_GetVTable,
        0,
        0,
        g_igMemoryDescriptorMetaField_callbackList
    );
}

void igMemoryDescriptorMetaField_GetMetaObjectFunction(void) {
    igMemoryDescriptorMetaField_GetMetaObject();
}

void igMemoryDescriptorMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igMemoryDescriptorMetaField_descriptor == 0) {
        g_igMemoryDescriptorMetaField_descriptor = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igMemoryDescriptorMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        descriptor = (void *)(g_igMemoryDescriptorMetaField_descriptor);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(Gap::Core::igMetaField::getMetaFieldTypes(), (igObject *)descriptor);
            {
                void *held = (void *)g_igMemoryDescriptorMetaField_descriptor;
                ((igObject *)held)->_refCount = ((igObject *)held)->_refCount - 1;
                if (((unsigned long long) ((long long) (int) ((igObject *)held)->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)held);
                }
            }
            ((igMetaField *)g_igMemoryDescriptorMetaField_descriptor)->_internalIndex = (short) (Gap::Core::igMetaField::getMetaFieldTypes()->_count - 1);
            ((Gap::Core::igMetaField *)g_igMemoryDescriptorMetaField_descriptor)->validate();
        }
    }
}

/* Vtable slot 25 of igMemoryDescriptorMetaField: the byte size of the field's storage. The array
 * metafields return `_num * element size` from this slot (truncated to the reflected 16-bit
 * `_size`); a memory descriptor stores a single 32-bit reference, so it returns 4. The receiver is
 * not touched, hence no parameters. */
int igMemoryDescriptorMetaField_GetSize(void) {
    return 4;
}

void igMemoryDescriptorMetaField_InitDefaults(void *self) {
    igMemoryDescriptorMetaField_AddSubFields(((igCompoundMetaField *)self)->_fieldList);
}

void igMemoryDescriptorMetaField_AddSubFields(int fieldList) {
    void *fieldName;
    int *header;
    int refs;
    int pool;
    void *field;
    void *name;

    field = (void *)(((void *)igUnsignedIntMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
    if ("_sizeAndStatus" == 0) {
        name = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        name = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)"_sizeAndStatus")));
    }
    fieldName = (void *)(name);
    ((Gap::Core::igMetaField *)field)->setFieldName(&fieldName);
    if (fieldName != 0) {
        header = (int *)((char *)fieldName - 8);
        refs = *(int *)((char *)(fieldName) - 4) - 1;
        *(int *)((char *)(fieldName) - 4) = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
        }
    }
    ((igMetaField *)field)->_offset = 0;
    ((Gap::Core::igMetaField *)field)->validate();
    ((Gap::Core::igObjectList *)fieldList)->append((Gap::Core::igObject *)field);
    ((igObject *)field)->_refCount = (int)((int) (((igObject *)field)->_refCount - 1));
    if (((unsigned long long) ((long long) (int) ((igObject *)field)->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)field);
    }
}

