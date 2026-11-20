igMetaObject *g_igIntMetaField_metaObject;
void *g_igIntMetaField_descriptor;

/* Same factory shape for an igIntMetaField (52-byte instance). */
igMetaField *igIntMetaField_Create(igMemoryPoolView *pool) {
    void **field;

    if (g_objectSystem->active != 0) {
        igIntMetaField_EnsureRegistered();
        field = ((void **)igMetaObject_CreateInstance((igMetaObject *)((int)g_igIntMetaField_metaObject), pool));
    } else {
        field = ((void **)igObject_AllocateRawStorage(0x34, 0, pool));
        if (field != 0) {
            field = ((void **)igIntMetaField_Construct((igMetaField *)field, 1));
        }
        ((igObjectDispatchView *)field)->InitDefaults();
        ((igObjectDispatchView *)field)->userConstruct(0);
    }
    return (igMetaField *)field;
}

void *igIntMetaField_Clone(void *self, void *src) {
    void *o;
    if (g_objectSystem->active != 0) {
        igIntMetaField_EnsureRegistered();
        return ((void *)igObject_CloneViaMetadata((void **)self, (int)src));
    }
    o = igObject_AllocateRawStorageDefault(0x34, 0);
    if (o != 0) {
        o = ((void *)igIntMetaField_CopyConstruct((int **)o, (int)self));
    }
    return o;
}

igMetaObject *igIntMetaField_GetOrCreateMetaObject(void) {
    if (g_igIntMetaField_metaObject == 0) {
        g_igIntMetaField_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igIntMetaField_metaObject;
}

igMetaObject *igIntMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igIntMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igIntMetaField_EnsureRegistered();
    return g_igIntMetaField_metaObject;
}

int igIntMetaField_GetVTable(void) {
    igIntMetaField field;
    int vtable;
    char *nameSlot;
    int *text;
    int *header;
    int count;

    igIntMetaField_Init((igMetaField *)&field);
    vtable = *(int *)((char *)&field + g_objectSystem->vtableProbeOffset);
    field._vtable = (int)&g_igMetaField_vtable[0];
    nameSlot = (char *)&field._fieldName;
    if (nameSlot != 0) {
        text = *(int **)nameSlot;
        if (text != 0) {
            header = text - 2;
            count = text[-1] - 1;
            text[-1] = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return vtable;
}

void igIntMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igIntMetaField_Register);
}

static igMetaObjectCallback g_igIntMetaField_callbackList[] = { igIntMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igIntMetaField_Register(void) {
    return igMetaObject_RegisterClass(
        0,
        &g_igIntMetaField_metaObject,
        Gap::Core::igMetaField::arkRegisterInternal,
        igMetaField_GetPublishedMetaObject,
        igIntMetaField_GetMetaObjectFunction,
        "igIntMetaField",
        0x34,
        igIntMetaField_GetVTable,
        0,
        0,
        g_igIntMetaField_callbackList
    );
}

void igIntMetaField_GetMetaObjectFunction(void) {
    igIntMetaField_GetMetaObject();
}


void igIntMetaField_CreateDefaultDescriptor(void) {
    void *descriptor;

    if (g_igIntMetaField_descriptor == 0) {
        g_igIntMetaField_descriptor = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igIntMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        descriptor = (void *)(g_igIntMetaField_descriptor);
        if (descriptor != 0) {
            MetaRefList_AppendRetained(Gap::Core::igMetaField::getMetaFieldTypes(), (igObject *)descriptor);
            {
                igObject *held = (igObject *)g_igIntMetaField_descriptor;
                held->_refCount = (int)held->_refCount - 1;
                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            ((igMetaField *)g_igIntMetaField_descriptor)->_internalIndex = (short) (Gap::Core::igMetaField::getMetaFieldTypes()->_count - 1);
            ((Gap::Core::igMetaField *)g_igIntMetaField_descriptor)->validate();
        }
    }
}

int igIntMetaField_GetDefaultDescriptor(void) {
    if (g_igIntMetaField_descriptor == 0) {
        igIntMetaField_EnsureRegistered();
    }
    return (int)g_igIntMetaField_descriptor;
}

