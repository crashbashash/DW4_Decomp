void igDoubleMetaField_Create(int pool) {
    igDoubleMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586638), (igMemoryPoolView *)pool);
}

igMetaObject *igDoubleMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igDoubleMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDoubleMetaField_EnsureRegistered();
    return g_igDoubleMetaField_metaObject[0];
}

int igDoubleMetaField_GetVTable(void) {
    igDoubleMetaField field;
    int vtable;
    char *name;
    int *text;
    int *header;
    int references;

    igMetaField_Init((igMetaField *)&field);
    field._vtable = (int)&g_igDoubleMetaField_vtable[0];
    vtable = *(int *)((char *)&field + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    field._vtable = (int)&g_igMetaField_vtable[0];
    name = (char *)&field._fieldName;
    if (name != 0) {
        text = *(int **)name;
        if (text != 0) {
            header = text - 2;
            references = text[-1] - 1;
            text[-1] = references;
            if (references == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return vtable;
}

void igDoubleMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDoubleMetaField_Register);
}

void igDoubleMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igDoubleMetaField_metaObject,
        (igMetaObjectRegisterFunction)igMetaField_Register,
        (igMetaObjectGetFunction)igMetaField_GetPublishedMetaObject,
        igDoubleMetaField_GetMetaObjectFunction,
        igDoubleMetaField_className,
        0x34,
        igDoubleMetaField_GetVTable,
        0,
        0,
        (igMetaObjectCallback *)g_igDoubleMetaField_callbackList
    );
}

void igDoubleMetaField_GetMetaObjectFunction(void) {
    igDoubleMetaField_GetMetaObject();
}

void igDoubleMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igDoubleMetaField_descriptor[0] == 0) {
        g_igDoubleMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igDoubleMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        descriptor = (void *)(g_igDoubleMetaField_descriptor[0]);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            {
                igMetaField *held = (igMetaField *)g_igDoubleMetaField_descriptor[0];
                held->_refCount = (int)held->_refCount - 1;
                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igMetaField *)g_igDoubleMetaField_descriptor[0])->_internalIndex = (short)(igMetaField_GetMetaFieldList()->_count - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igDoubleMetaField_descriptor[0]);
        }
    }
}

int igDoubleMetaField_GetDefaultDescriptor(void) {
    if (((int *)g_igDoubleMetaField_descriptor)[0] == 0) {
        igDoubleMetaField_EnsureRegistered();
    }
    return ((int *)g_igDoubleMetaField_descriptor)[0];
}

