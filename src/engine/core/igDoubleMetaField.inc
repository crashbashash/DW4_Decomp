igMetaObject *g_igDoubleMetaField_metaObject;
void *g_igDoubleMetaField_descriptor;

igMetaField *igDoubleMetaField_Create(igMemoryPoolView *pool) {
    igDoubleMetaField_EnsureRegistered();
    return (igMetaField *)igMetaObject_CreateInstance(g_igDoubleMetaField_metaObject, pool);
}

igMetaObject *igDoubleMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igDoubleMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDoubleMetaField_EnsureRegistered();
    return g_igDoubleMetaField_metaObject;
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
    vtable = *(int *)((char *)&field + g_objectSystem->vtableProbeOffset);
    field._vtable = (int)&g_igMetaField_vtable[0];
    name = (char *)&field._fieldName;
    if (name != 0) {
        text = *(int **)name;
        if (text != 0) {
            header = text - 2;
            references = text[-1] - 1;
            text[-1] = references;
            if (references == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return vtable;
}

void igDoubleMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDoubleMetaField_Register);
}

static igMetaObjectCallback g_igDoubleMetaField_callbackList[] = { igDoubleMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igDoubleMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igDoubleMetaField_metaObject,
        Gap::Core::igMetaField::arkRegisterInternal,
        igMetaField_GetPublishedMetaObject,
        igDoubleMetaField_GetMetaObjectFunction,
        "igDoubleMetaField",
        0x34,
        igDoubleMetaField_GetVTable,
        0,
        0,
        g_igDoubleMetaField_callbackList
    );
}

void igDoubleMetaField_GetMetaObjectFunction(void) {
    igDoubleMetaField_GetMetaObject();
}


void igDoubleMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igDoubleMetaField_descriptor == 0) {
        g_igDoubleMetaField_descriptor = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igDoubleMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        descriptor = (void *)(g_igDoubleMetaField_descriptor);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(Gap::Core::igMetaField::getMetaFieldTypes(), (igObject *)descriptor);
            {
                igMetaField *held = (igMetaField *)g_igDoubleMetaField_descriptor;
                held->_refCount = (int)held->_refCount - 1;
                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igMetaField *)g_igDoubleMetaField_descriptor)->_internalIndex = (short)(Gap::Core::igMetaField::getMetaFieldTypes()->_count - 1);
            ((Gap::Core::igMetaField *)g_igDoubleMetaField_descriptor)->validate();
        }
    }
}

int igDoubleMetaField_GetDefaultDescriptor(void) {
    if ((*(int *)&g_igDoubleMetaField_descriptor) == 0) {
        igDoubleMetaField_EnsureRegistered();
    }
    return (*(int *)&g_igDoubleMetaField_descriptor);
}

