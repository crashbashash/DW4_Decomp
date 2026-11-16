igMetaObject *g_igCharMetaField_metaObject;
void *g_igCharMetaField_descriptor;

void **igCharMetaField_Create(int pool) {
    void **field;

    if (g_objectSystem->active != 0) {
        igCharMetaField_EnsureRegistered();
        field = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g_igCharMetaField_metaObject, (igMemoryPoolView *)pool)));
    } else {
        field = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, (igMemoryPoolView *)pool)));
        if (field != 0) {
            field = (void **)(((void **)igCharMetaField_Construct((int **)field, 1)));
        }
        ((igObjectDispatchView *)(field))->InitDefaults();
        ((igObjectDispatchView *)(field))->userConstruct((int)(0));
    }
    return field;
}

void *igCharMetaField_Clone(void *source, void *copyMode) {
    void *copy;
    if (g_objectSystem->active != 0) {
        igCharMetaField_EnsureRegistered();
        return ((void *)igObject_CloneViaMetadata((void **)source, (int)copyMode));
    }
    copy = igObject_AllocateRawStorageDefault(0x34, 0);
    if (copy) copy = ((void *)igCharMetaField_CopyConstruct((int **)copy, (int)source));
    return copy;
}

igMetaObject *igCharMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCharMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCharMetaField_EnsureRegistered();
    return g_igCharMetaField_metaObject;
}

int igCharMetaField_GetVTable(void) {
    igCharMetaField field;
    int vtable;
    char *name;
    int *text;
    int *header;
    int references;

    igCharMetaField_Init((int **)&field);
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

void igCharMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCharMetaField_Register);
}

static igMetaObjectCallback g_igCharMetaField_callbackList[] = { igCharMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igCharMetaField_Register(void) {
    return igMetaObject_RegisterClass(
        0,
        &g_igCharMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        igCharMetaField_GetMetaObjectFunction,
        "igCharMetaField",
        0x34,
        igCharMetaField_GetVTable,
        0,
        0,
        g_igCharMetaField_callbackList
    );
}

void igCharMetaField_GetMetaObjectFunction(void) {
    igCharMetaField_GetMetaObject();
}


void igCharMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igCharMetaField_descriptor == 0) {
        g_igCharMetaField_descriptor = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igCharMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        descriptor = (void *)(g_igCharMetaField_descriptor);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            {
                igMetaField *held = (igMetaField *)g_igCharMetaField_descriptor;
                held->_refCount = (int)held->_refCount - 1;
                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igMetaField *)g_igCharMetaField_descriptor)->_internalIndex = (short)(igMetaField_GetMetaFieldList()->_count - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igCharMetaField_descriptor);
        }
    }
}

int igCharMetaField_GetDefaultDescriptor(void) {
    if ((*(int *)&g_igCharMetaField_descriptor) == 0) {
        igCharMetaField_EnsureRegistered();
    }
    return (*(int *)&g_igCharMetaField_descriptor);
}

