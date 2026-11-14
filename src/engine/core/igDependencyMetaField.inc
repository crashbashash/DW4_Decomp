igMetaObject *igDependencyMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igDependencyMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDependencyMetaField_EnsureRegistered();
    return g_igDependencyMetaField_metaObject[0];
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
    result = *(int *)((char *)&field + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
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
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return result;
}

void igDependencyMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDependencyMetaField_Register);
}

void igDependencyMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igDependencyMetaField_metaObject,
        (igMetaObjectRegisterFunction)igCompoundMetaField_Register,
        (igMetaObjectGetFunction)igCompoundMetaField_GetPublishedMetaObject,
        igDependencyMetaField_GetMetaObjectFunction,
        igDependencyMetaField_className,
        0x38,
        igDependencyMetaField_GetVTable,
        0,
        0,
        (igMetaObjectCallback *)g_igDependencyMetaField_callbackList
    );
}

void igDependencyMetaField_GetMetaObjectFunction(void) {
    igDependencyMetaField_GetMetaObject();
}

void igDependencyMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igDependencyMetaField_descriptor[0] == 0) {
        g_igDependencyMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igDependencyMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        descriptor = (void *)(g_igDependencyMetaField_descriptor[0]);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            {
                void *held = (void *)g_igDependencyMetaField_descriptor[0];
                ((igObject *)held)->_refCount = ((igObject *)held)->_refCount - 1;
                if (((unsigned long long) ((long long) (int) ((igObject *)held)->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igMetaField *)g_igDependencyMetaField_descriptor[0])->_internalIndex = (short) (igMetaField_GetMetaFieldList()->_count - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igDependencyMetaField_descriptor[0]);
        }
    }
}

int igDependencyMetaField_GetDefaultDescriptor(void) {
    if (((int *)g_igDependencyMetaField_descriptor)[0] == 0) {
        igDependencyMetaField_EnsureRegistered();
    }
    return ((int *)g_igDependencyMetaField_descriptor)[0];
}

int igDependencyMetaField_GetSize(void) {
    return 8;
}

void igDependencyMetaField_InitDefaults(void *self) {
    igDependencyMetaField_AddSubFields(((igCompoundMetaField *)self)->_fieldList);
}

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

    beforeField = (void *)(((void *)igRawRefMetaField_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
    if (&text_before[0] == 0) {
        beforeText = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            beforePool = ((int)StringPool_Allocate(0x10));
            if (beforePool != 0) {
                beforePool = ((int)StringPool_Construct((StringPool *)beforePool));
            }
            g_stringPool[0] = beforePool;
        }
        beforeText = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)&text_before[0])));
    }
    beforeName = (void *)(beforeText);
    igMetaField_SetFieldName((igMetaField *)beforeField, &beforeName);
    if (beforeName != 0) {
        beforeHeader = (int *)((char *)beforeName - 8);
        beforeRefs = *(int *)((char *)(beforeName) - 4) - 1;
        *(int *)((char *)(beforeName) - 4) = beforeRefs;
        if (beforeRefs == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*beforeHeader), (int)beforeHeader);
        }
    }
    ((igMetaField *)beforeField)->_offset = 0;
    igMetaField_FinalizeDescriptor((igMetaField *)beforeField);
    ObjectList_AppendRetained((igObjectList *)fieldList, (igObject *)beforeField);
    ((igObject *)beforeField)->_refCount = (int)((int) (((igObject *)beforeField)->_refCount - 1));
    if (((unsigned long long) ((long long) (int) ((igObject *)beforeField)->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(beforeField);
    }
    afterField = (void *)(((void *)igRawRefMetaField_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
    if (&text_after[0] == 0) {
        afterText = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            afterPool = ((int)StringPool_Allocate(0x10));
            if (afterPool != 0) {
                afterPool = ((int)StringPool_Construct((StringPool *)afterPool));
            }
            g_stringPool[0] = afterPool;
        }
        afterText = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)&text_after[0])));
    }
    afterName = (void *)(afterText);
    igMetaField_SetFieldName((igMetaField *)afterField, &afterName);
    if (afterName != 0) {
        afterHeader = (int *)((char *)afterName - 8);
        afterRefs = *(int *)((char *)(afterName) - 4) - 1;
        *(int *)((char *)(afterName) - 4) = afterRefs;
        if (afterRefs == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*afterHeader), (int)afterHeader);
        }
    }
    ((igMetaField *)afterField)->_offset = 4;
    igMetaField_FinalizeDescriptor((igMetaField *)afterField);
    ObjectList_AppendRetained((igObjectList *)fieldList, (igObject *)afterField);
    ((igObject *)afterField)->_refCount = (int)((int) (((igObject *)afterField)->_refCount - 1));
    if (((unsigned long long) ((long long) (int) ((igObject *)afterField)->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(afterField);
    }
}

