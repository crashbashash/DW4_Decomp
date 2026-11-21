igMetaObject *g_igDependencyMetaField_metaObject;
void *g_igDependencyMetaField_descriptor;

igMetaObject *igDependencyMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igDependencyMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDependencyMetaField_EnsureRegistered();
    return g_igDependencyMetaField_metaObject;
}

int igDependencyMetaField_GetVTable(void) {
    igDependencyMetaField field;
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
    field._vtable = (int)&g_igDependencyMetaField_vtable[0];
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

void igDependencyMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDependencyMetaField_Register);
}

static igMetaObjectCallback g_igDependencyMetaField_callbackList[] = { igDependencyMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igDependencyMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igDependencyMetaField_metaObject,
        Gap::Core::igCompoundMetaField::arkRegisterInternal,
        (igMetaObjectGetFunction)igCompoundMetaField_GetPublishedMetaObject,
        igDependencyMetaField_GetMetaObjectFunction,
        "igDependencyMetaField",
        0x38,
        igDependencyMetaField_GetVTable,
        0,
        0,
        g_igDependencyMetaField_callbackList
    );
}

void igDependencyMetaField_GetMetaObjectFunction(void) {
    igDependencyMetaField_GetMetaObject();
}

void igDependencyMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igDependencyMetaField_descriptor == 0) {
        g_igDependencyMetaField_descriptor = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igDependencyMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        descriptor = (void *)(g_igDependencyMetaField_descriptor);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(Gap::Core::igMetaField::getMetaFieldTypes(), (igObject *)descriptor);
            {
                void *held = (void *)g_igDependencyMetaField_descriptor;
                ((igObject *)held)->_refCount = ((igObject *)held)->_refCount - 1;
                if (((unsigned long long) ((long long) (int) ((igObject *)held)->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)held);
                }
            }
            ((igMetaField *)g_igDependencyMetaField_descriptor)->_internalIndex = (short) (Gap::Core::igMetaField::getMetaFieldTypes()->_count - 1);
            ((Gap::Core::igMetaField *)g_igDependencyMetaField_descriptor)->validate();
        }
    }
}

int igDependencyMetaField_GetDefaultDescriptor(void) {
    if ((*(int *)&g_igDependencyMetaField_descriptor) == 0) {
        igDependencyMetaField_EnsureRegistered();
    }
    return (*(int *)&g_igDependencyMetaField_descriptor);
}

int igDependencyMetaField_GetSize(void) {
    return 8;
}

void igDependencyMetaField_InitDefaults(void *self) {
    igDependencyMetaField_AddSubFields(((igCompoundMetaField *)self)->_fieldList);
}

StringPool *g_stringPool;

void igDependencyMetaField_AddSubFields(int fieldList) {
    void *beforeName;
    void *afterName;
    int *beforeHeader;
    int *afterHeader;
    int beforeRefs;
    int afterRefs;
    int beforePool;
    int afterPool;
    void *beforeField;
    void *afterField;
    void *beforeText;
    void *afterText;

    beforeField = (void *)(((void *)igRawRefMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
    if ("_before" == 0) {
        beforeText = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            beforePool = ((int)StringPool_Allocate(0x10));
            if (beforePool != 0) {
                beforePool = ((int)StringPool_Construct((StringPool *)beforePool));
            }
            g_stringPool = (StringPool *)beforePool;
        }
        beforeText = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)"_before")));
    }
    beforeName = (void *)(beforeText);
    ((Gap::Core::igMetaField *)beforeField)->setFieldName(&beforeName);
    if (beforeName != 0) {
        beforeHeader = (int *)((char *)beforeName - 8);
        beforeRefs = *(int *)((char *)(beforeName) - 4) - 1;
        *(int *)((char *)(beforeName) - 4) = beforeRefs;
        if (beforeRefs == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*beforeHeader), (StringTokenHeader *)beforeHeader);
        }
    }
    ((igMetaField *)beforeField)->_offset = 0;
    ((Gap::Core::igMetaField *)beforeField)->validate();
    ObjectList_AppendRetained((igObjectList *)fieldList, (igObject *)beforeField);
    ((igObject *)beforeField)->_refCount = (int)((int) (((igObject *)beforeField)->_refCount - 1));
    if (((unsigned long long) ((long long) (int) ((igObject *)beforeField)->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)beforeField);
    }
    afterField = (void *)(((void *)igRawRefMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
    if ("_after" == 0) {
        afterText = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            afterPool = ((int)StringPool_Allocate(0x10));
            if (afterPool != 0) {
                afterPool = ((int)StringPool_Construct((StringPool *)afterPool));
            }
            g_stringPool = (StringPool *)afterPool;
        }
        afterText = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)"_after")));
    }
    afterName = (void *)(afterText);
    ((Gap::Core::igMetaField *)afterField)->setFieldName(&afterName);
    if (afterName != 0) {
        afterHeader = (int *)((char *)afterName - 8);
        afterRefs = *(int *)((char *)(afterName) - 4) - 1;
        *(int *)((char *)(afterName) - 4) = afterRefs;
        if (afterRefs == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*afterHeader), (StringTokenHeader *)afterHeader);
        }
    }
    ((igMetaField *)afterField)->_offset = 4;
    ((Gap::Core::igMetaField *)afterField)->validate();
    ObjectList_AppendRetained((igObjectList *)fieldList, (igObject *)afterField);
    ((igObject *)afterField)->_refCount = (int)((int) (((igObject *)afterField)->_refCount - 1));
    if (((unsigned long long) ((long long) (int) ((igObject *)afterField)->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)afterField);
    }
}

